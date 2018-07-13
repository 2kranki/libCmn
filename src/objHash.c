// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   objHash.c
 *	Generated 10/24/2015 13:59:04
 *
 */

 
/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include    <objHash_internal.h>
#include    <objEnum_internal.h>
#include    <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            objHash_AddBlock(
        OBJHASH_DATA    *this
    );
    
    static
    OBJHASH_NODE *  objHash_FindUniqueInt(
        OBJHASH_DATA    *this,
        uint32_t        index
    );
    
    static
    uint16_t        objHash_IndexFromHash(
        OBJHASH_DATA    *this,
        uint32_t        hash
    );
    
    static
    LISTDL_DATA *   objHash_NodeListFromHash(
        OBJHASH_DATA    *this,
        uint32_t        hash
    );
    
    
    
    /* Expand the current Pointer Array by Inc entries.
     */
    static
    bool            objHash_AddBlock(
        OBJHASH_DATA    *this
    )
    {
        OBJHASH_BLOCK   *pBlock;
        uint32_t        i;
        
        // Do initialization.
        if ( 0 == listdl_Count(&this->freeList) )
            ;
        else {
            return true;
        }
        
        // Get a new block.
        i = sizeof(OBJHASH_BLOCK) + (this->cBlock * sizeof(OBJHASH_NODE));
        pBlock = (OBJHASH_BLOCK *)mem_Malloc( i );
        if( NULL == pBlock ) {
            return false;
        }
        listdl_Add2Tail(&this->blocks, pBlock);
        
        // Now chain the entries to the Free chain.
        for (i=0; i<this->cBlock; ++i) {
            listdl_Add2Tail(&this->freeList, &pBlock->node[i]);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    OBJ_ID          objHash_DeleteNode(
        OBJHASH_DATA    *this,
        OBJHASH_NODE    *pNode
    )
    {
        LISTDL_DATA     *pNodeList;
        OBJ_ID          pReturn = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (NULL == pNode) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pNodeList = objHash_NodeListFromHash(this, pNode->hash);
        listdl_Delete(pNodeList, pNode);
        pReturn = pNode->pObject;
        pNode->pObject = OBJ_NIL;
        listdl_Add2Head(&this->freeList, pNode);
        
        // We need to remove the entry from the appropriate scope level.
        if (this->pScope) {
            uint32_t            next = 0;
            uint32_t            prev = 0;
            OBJHASH_NODE        *pNodeScope;
            
            prev = pNode->scopeNext;
            array_Get(this->pScope, pNode->scopeLvl, 1, &next);
            if (next == pNode->unique) {
                array_Put(this->pScope, pNode->scopeLvl, 1, &prev);
            }
            else {
                for (;;) {
                    pNodeScope = objHash_FindUniqueInt(this, next);
                    if (OBJ_NIL == pNodeScope) {
                        DEBUG_BREAK();
                        break;
                    }
                    if (pNode->unique == pNodeScope->scopeNext) {
                        pNodeScope->scopeNext = prev;
                        break;
                    }
                    prev = pNodeScope->unique;
                    next = pNodeScope->scopeNext;
                }
            }
        }
        
        // Return to caller.
        return pReturn;
    }
    
    
    
    static
    OBJHASH_NODE *  objHash_FindNode(
        OBJHASH_DATA    *this,
        uint32_t        hash,
        OBJ_ID          pObject
    )
    {
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        int             iRc;
        const
        OBJ_IUNKNOWN    *pVtbl;
        
        // Do initialization.
        pNodeList = objHash_NodeListFromHash(this, hash);
        pVtbl = obj_getVtbl(pObject);
        
        pNode = listdl_Head(pNodeList);
        while ( pNode ) {
            if (pNode->hash == hash) {
                iRc = pVtbl->pCompare(pObject, pNode->pObject);
                if (0 == iRc) {
                    return pNode;
                }
                if (iRc < 0) {
                    break;
                }
            }
            pNode = listdl_Next(pNodeList, pNode);
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    
    static
    OBJHASH_NODE *  objHash_FindUniqueInt(
        OBJHASH_DATA    *this,
        uint32_t        index
    )
    {
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        int             iRc;
        uint32_t        hash;

        // Do initialization.
        
        // Since we have no other index, we must search
        // the entire hash until we find the object.
        for (hash=0; hash<this->cHash; ++hash) {
            pNodeList = &this->pHash[hash];
            pNode = listdl_Head(pNodeList);
            while ( pNode ) {
                iRc = index - pNode->unique;
                if (0 == iRc) {
                    return pNode;
                }
                pNode = listdl_Next(pNodeList, pNode);
            }
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    
    static
    uint16_t        objHash_IndexFromHash(
        OBJHASH_DATA    *this,
        uint32_t        hash
    )
    {
        uint16_t        index;
        
        index = hash % this->cHash;
        return index;
    }
    
    
    
    static
    LISTDL_DATA *   objHash_NodeListFromHash(
        OBJHASH_DATA    *this,
        uint32_t        hash
    )
    {
        LISTDL_DATA     *pNodeList;
        
        pNodeList = &this->pHash[objHash_IndexFromHash(this, hash)];
        return( pNodeList );
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJHASH_DATA *     objHash_Alloc(
    )
    {
        OBJHASH_DATA    *this;
        uint32_t        cbSize = sizeof(OBJHASH_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJHASH_DATA * objHash_New(
        uint16_t       cHash       // [in] Hash Table Size
    )
    {
        OBJHASH_DATA    *this;
        
        this = objHash_Alloc( );
        if (this) {
            this = objHash_Init(this, cHash);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                   D u p l i c a t e s
    //---------------------------------------------------------------
    
    bool            objHash_getDuplicates(
        OBJHASH_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->eRc = ERESULT_SUCCESS;
        return this->fDups ? true : false;
    }
    
    
    bool            objHash_setDuplicates(
        OBJHASH_DATA    *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->fDups = fValue ? 1 : 0;
        
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         objHash_getLastError(
        OBJHASH_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->eRc;
    }

    
    bool            objHash_setLastError(
        OBJHASH_DATA    *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }

    
    
    //---------------------------------------------------------------
    //                          S i z e
    //---------------------------------------------------------------
    
    uint32_t        objHash_getSize(
        OBJHASH_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->num;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //----------------------------------------------------------
    //                          A d d
    //----------------------------------------------------------
    
    ERESULT         objHash_Add(
        OBJHASH_DATA    *this,
        OBJ_ID			pObject,
        uint32_t        *pIndex
    )
    {
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        uint32_t        hash;
        OBJ_IUNKNOWN    *pVtbl;
        
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pVtbl = obj_getVtbl(pObject);
        hash = pVtbl->pHash(pObject);
        
        if (!this->fDups) {
            pNode = objHash_Find(this, pObject);
            if (pNode) {
                //fprintf( stderr, "Node Key = %s\n", pNode->pszKey);
                return ERESULT_DATA_ALREADY_EXISTS;
            }
        }
        
        // Determine the entry number.
        if (0 == listdl_Count(&this->freeList)) {
            if ( objHash_AddBlock(this) )
                ;
            else {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        pNode = listdl_DeleteHead(&this->freeList);
        if (NULL == pNode) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Add it to the table.
        obj_Retain(pObject);
        pNode->pObject = pObject;
        pNode->hash    = hash;
        pNode->unique  = ++this->unique;
        if (this->pScope) {
            array_Get(this->pScope, this->scopeLvl, 1, &pNode->scopeNext);
            array_Put(this->pScope, this->scopeLvl, 1, &pNode->unique);
            pNode->scopeLvl = this->scopeLvl;
        }
        
        pNodeList = objHash_NodeListFromHash(this, hash);
        listdl_Add2Head(pNodeList, pNode);
        
        ++this->num;
        
        // Return to caller.
        if (pIndex)
            *pIndex = pNode->unique;
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         objHash_Assign(
        OBJHASH_DATA    *this,
        OBJHASH_DATA    *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        OBJ_IUNKNOWN    *pVtbl;
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        OBJ_ID          pObj;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !objHash_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        //FIXME: Restore this.
#ifdef XYZZY
        // Release any objects that the Other Array has.
        obj_Release(pOther->)
        for (i=0; i<pOther->size; ++i) {
            pItem = pOther->ppArray[i];
            obj_Release(pItem);
            pOther->ppArray[i] = OBJ_NIL;
        }
        pOther->size = 0;
        
        // Increase size of the other array if needed.
        while (pOther->max < this->max) {
            if ((this->max - pOther->max) < 32768) {
                i = this->max - pOther->max;
            }
            else {
                i = 32768;
            }
            objArray_ExpandArray( pOther, i );
        }
#endif

        // Copy over the objects.
        for (i=0; i<this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pNode = listdl_Head(pNodeList);
            while (pNode) {
                pObj = pNode->pObject;
                if (pObj) {
                    pVtbl = obj_getVtbl(pNode->pObject);
                    if (pVtbl->pDeepCopy) {
                        pObj = pVtbl->pDeepCopy(pObj);
                    }
                    else if (pVtbl->pCopy) {
                        pObj = pVtbl->pCopy(pObj);
                    }
                    else {
                        obj_Retain(pObj);
                    }
                    objHash_Add(pOther, pNode->pObject, NULL);
                }
                pNode = listdl_Next(pNodeList, pNode);
            }
        }
        
        // Return to caller.
        this->eRc = eRc;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    OBJHASH_DATA *  objHash_Copy(
        OBJHASH_DATA    *this
    )
    {
        OBJHASH_DATA    *pOther = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
 
        pOther = objHash_New(this->cHash);
        if (OBJ_NIL == pOther) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return OBJ_NIL;
        }
        
        this->eRc = objHash_Assign(this, pOther);
        if (ERESULT_HAS_FAILED(this->eRc)) {
            obj_Release(pOther);
            return OBJ_NIL;
        }
        

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            objHash_Dealloc(
        OBJ_ID          objId
    )
    {
        OBJHASH_DATA    *this = objId;
        OBJHASH_BLOCK   *pBlock;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        eRc = objHash_DeleteAll(this);

        while ( listdl_Count(&this->blocks) ) {
            pBlock = listdl_DeleteHead(&this->blocks);
            mem_Free( pBlock );
        }
        
        if( this->pHash ) {
            mem_Free( this->pHash );
            this->pHash = NULL;
        }
        
        if (this->pScope) {
            obj_Release(this->pScope);
            this->pScope = OBJ_NIL;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = NULL;

        // Return to caller.
    }



    //----------------------------------------------------------
    //                      D e l e t e
    //----------------------------------------------------------
    
    OBJ_ID          objHash_Delete(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject
    )
    {
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        uint32_t        hash;
        OBJ_ID          pReturn = OBJ_NIL;
        const
        OBJ_IUNKNOWN    *pVtbl;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pVtbl = obj_getVtbl(pObject);
        
        hash = pVtbl->pHash(pObject);
        pNodeList = objHash_NodeListFromHash(this, hash);

        pNode = objHash_FindNode(this, hash, pObject);
        if (pNode) {
            pReturn = objHash_DeleteNode(this, pNode);
        }
        
        // Return to caller.
        return pReturn;
    }
    
    
    ERESULT         objHash_DeleteAll(
        OBJHASH_DATA    *this
    )
    {
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        OBJHASH_NODE    *pNext;
        uint32_t        i;
        OBJ_ID          pReturn = OBJ_NIL;
        uint32_t        zero = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=0; i<this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pNode = listdl_Head(pNodeList);
            while ( pNode ) {
                pNext = listdl_Next(pNodeList, pNode);
                listdl_Delete(pNodeList, pNode);
                pReturn = pNode->pObject;
                pNode->pObject = OBJ_NIL;
                listdl_Add2Head(&this->freeList, pNode);
                if (pReturn) {
                    --this->num;
                    obj_Release(pReturn);
                    pReturn = OBJ_NIL;
                }
                pNode = pNext;
            }
        }
        
        // We need to zero all the scope levels if being used.
        if (this->pScope) {
            for (i=0; i<this->scopeLvl; ++i) {
                array_Put(this->pScope, (i + 1), 1, &zero);
            }
            this->scopeLvl = 0;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return ERESULT_SUCCESS;
    }
    
    
    OBJ_ID          objHash_DeleteIndex(
        OBJHASH_DATA    *this,
        uint32_t        index
    )
    {
        OBJHASH_NODE    *pNode;
        OBJ_ID          pReturn = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pNode = objHash_FindUniqueInt(this, index);
        if (pNode) {
            pReturn = objHash_DeleteNode(this, pNode);
        }
        
        // Return to caller.
        return pReturn;
    }
    
    

    //---------------------------------------------------------------
    //                      E n u m
    //---------------------------------------------------------------
    
    OBJENUM_DATA *  objHash_Enum(
        OBJHASH_DATA    *this
    )
    {
        OBJENUM_DATA    *pEnum = OBJ_NIL;
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        uint32_t        i;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return pEnum;
        }
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return pEnum;
        }
#endif
        
        pEnum = objEnum_New();
        if (OBJ_NIL == pEnum) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return OBJ_NIL;
        }
        
        for (i=0; i<this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pNode = listdl_Head(pNodeList);
            while (pNode) {
                objEnum_Append(pEnum, pNode->pObject);
                pNode = listdl_Next(pNodeList, pNode);
            }
        }
        eRc = objEnum_SortAscending(pEnum);
        
        // Return to caller.
        return pEnum;
    }
    
    
    
    //----------------------------------------------------------
    //                        F i n d
    //----------------------------------------------------------
    
    OBJ_ID          objHash_Find(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject
    )
    {
        OBJHASH_NODE    *pNode;
        uint32_t        hash;
        const
        OBJ_IUNKNOWN    *pVtbl;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pVtbl = obj_getVtbl(pObject);
        
        hash = pVtbl->pHash(pObject);
        
        pNode = objHash_FindNode(this, hash, pObject);
        if (pNode) {
            return pNode->pObject;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    OBJ_ID          objHash_FindIndex(
        OBJHASH_DATA    *this,
        uint32_t        index
    )
    {
        OBJHASH_NODE    *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pNode = objHash_FindUniqueInt(this, index);
        if (pNode) {
            return pNode->pObject;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    

    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJHASH_DATA *   objHash_Init(
        OBJHASH_DATA    *this,
        uint16_t        cHash       // [in] Hash Table Size
    )
    {
        uint32_t        cbSize;
        uint32_t        i;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (OBJHASH_DATA *)obj_Init( this, cbSize, OBJ_IDENT_OBJHASH );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(cbp, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)cbp, OBJ_IDENT_OBJHASH);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&objHash_Vtbl);
        
        this->cHash = cHash;
        cbSize = 4096 - sizeof(OBJHASH_BLOCK);
        cbSize /= sizeof(OBJHASH_NODE);
        this->cBlock = cbSize;
        
        // Allocate the Hash Table.
        cbSize = cHash * sizeof(LISTDL_DATA);
        this->pHash = (LISTDL_DATA *)mem_Malloc( cbSize );
        if (NULL == this->pHash) {
            DEBUG_BREAK();
            mem_Free(this);
            this = NULL;
            return this;
        }
        for (i=0; i<cHash; ++i) {
            listdl_Init(&this->pHash[i], offsetof(OBJHASH_NODE, list));
        }
        listdl_Init(&this->freeList, offsetof(OBJHASH_NODE, list));
 
    #ifdef NDEBUG
    #else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "objHash::offsetof(eRc) = %lu\n", offsetof(OBJHASH_DATA,eRc));
        //fprintf(stderr, "objHash::sizeof(OBJHASH_DATA) = %lu\n", sizeof(OBJHASH_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(OBJHASH_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            objHash_IsEnabled(
        OBJHASH_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(this))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
     // Return a method pointer for a string or NULL if not found.
     void        *pMethod = objHash_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode
     @param     objId   OBJHASH object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
     for OBJ_QUERYINFO_TYPE_METHOD, this field points to a
     character string which represents the method name without
     the object name, "name", prefix,
     for OBJ_QUERYINFO_TYPE_PTR, this field contains the
     address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
     OBJ_QUERYINFO_TYPE_INFO: info pointer,
     OBJ_QUERYINFO_TYPE_METHOD: method pointer,
     OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          objHash_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJHASH_DATA    *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)objHash_Class();
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return objHash_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S c o p e  C l o s e
    //---------------------------------------------------------------
    
    ERESULT         objHash_ScopeClose(
        OBJHASH_DATA    *this
    )
    {
        uint32_t        zero = 0;
        uint32_t        nextIndex = 0;
        uint32_t        curIndex = 0;
        OBJHASH_NODE    *pNode;
        OBJ_ID          pReturn = OBJ_NIL;

#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (OBJ_NIL == this->pScope) {
            return ERESULT_NOT_IMPLEMENTED;
        }
        
        array_Get(this->pScope, this->scopeLvl, 1, &curIndex);
        while (curIndex) {
            pNode = objHash_FindUniqueInt(this, curIndex);
            if (OBJ_NIL == pNode) {
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
            }
            nextIndex = pNode->scopeNext;
            pReturn = objHash_DeleteNode(this, pNode);
            if (pReturn) {
                --this->num;
                obj_Release(pReturn);
                pReturn = OBJ_NIL;
            }
            curIndex = nextIndex;
        }
        
        array_Put(this->pScope, this->scopeLvl, 1, &zero);
        this->scopeLvl -= 1;
        
        return this->scopeLvl;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S c o p e  C u r r e n t
    //---------------------------------------------------------------
    
    uint32_t        objHash_ScopeCurrent(
        OBJHASH_DATA    *this
    )
    {
        
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif
        
        return this->scopeLvl;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S c o p e  E n u m
    //---------------------------------------------------------------
    
    OBJENUM_DATA *  objHash_ScopeEnum(
        OBJHASH_DATA    *this,
        uint32_t        level
    )
    {
        OBJENUM_DATA    *pEnum = OBJ_NIL;
        OBJHASH_NODE    *pNode;
        ERESULT         eRc;
        uint32_t        next;
        
        // Do initialization.
        if (NULL == this) {
            return pEnum;
        }
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return pEnum;
        }
#endif
        
        if (NULL == this->pScope) {
            DEBUG_BREAK();
            return pEnum;
        }
        eRc = array_Get(this->pScope, level,  1, &next);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return pEnum;
        }
        pEnum = objEnum_New();
        if (OBJ_NIL == pEnum) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return OBJ_NIL;
        }
        
        while (next) {
            pNode = objHash_FindUniqueInt(this, next);
            if (NULL == pNode) {
                break;
            }
            objEnum_Append(pEnum, pNode->pObject);
            next = pNode->scopeNext;
        }
        eRc = objEnum_SortAscending(pEnum);
        
        // Return to caller.
        return pEnum;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S c o p e  O p e n
    //---------------------------------------------------------------
    
    uint32_t        objHash_ScopeOpen(
        OBJHASH_DATA    *this
    )
    {
        uint32_t        zero = 0;
        
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif
        
        if (OBJ_NIL == this->pScope) {
            BREAK_NOT_ZERO(this->scopeLvl);
            this->pScope = array_New(sizeof(uint32_t));
            if (OBJ_NIL == this->pScope) {
                DEBUG_BREAK();
                this->eRc = ERESULT_OUT_OF_MEMORY;
                return 0;
            }
        }

        this->scopeLvl += 1;
        array_Expand(this->pScope, this->scopeLvl);
        array_Put(this->pScope, this->scopeLvl, 1, &zero);

        return this->scopeLvl;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     objHash_ToDebugString(
        OBJHASH_DATA    *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(objHash) side=%d ",
                     this,
                     objHash_getSize(this)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->toDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            objHash_Validate(
        OBJHASH_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_OBJHASH) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(OBJHASH_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


