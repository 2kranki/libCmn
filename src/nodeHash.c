// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeHash.c
 *	Generated 07/22/2015 10:03:31
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
#include <nodeHash_internal.h>
#include <nodeArray.h>
#include <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            nodeHash_AddBlock(
        NODEHASH_DATA   *this
    );
    
    static
    uint16_t        nodeHash_IndexFromHash(
        NODEHASH_DATA   *this,
        uint32_t        hash
    );
    
    static
    LISTDL_DATA *   nodeHash_NodeListFromHash(
        NODEHASH_DATA   *this,
        uint32_t        hash
    );
    
    
    
    /* Expand the current Pointer Array by Inc entries.
     */
    static
    bool            nodeHash_AddBlock(
        NODEHASH_DATA   *this
    )
    {
        NODEHASH_BLOCK  *pBlock;
        uint32_t        i;
        
        // Do initialization.
        if ( 0 == listdl_Count(&this->freeList) )
            ;
        else {
            return true;
        }
        
        // Get a new block.
        i = sizeof(NODEHASH_BLOCK) + (this->cBlock * sizeof(NODEHASH_NODE));
        pBlock = (NODEHASH_BLOCK *)mem_Malloc( i );
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
    
    
    
    /*!
     Find the nodeHash which contains the name given.
     @return    If successful, return the hash node pointer; otherwise return NULL.
     */
    static
    NODEHASH_NODE * nodeHash_FindNodeHash(
        NODEHASH_DATA   *this,
        NAME_DATA       *pName
    )
    {
        ERESULT         eRc;
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pNode;
        uint32_t        hash;
        
        // Do initialization.
        hash = name_getHash(pName);
        pNodeList = nodeHash_NodeListFromHash(this, hash);
        
        pNode = listdl_Head(pNodeList);
        while ( pNode ) {
            if (node_getHash(pNode->pNode) == hash) {
                eRc = name_Compare(pName, node_getName(pNode->pNode));
                if (ERESULT_SUCCESS_EQUAL == eRc) {
                    return pNode;
                }
#ifdef XYZZY
                // WARNING: Entries are not sorted currently.
                if (ERESULT_SUCCESS_GREATER_THAN == eRc) {
                    break;
                }
#endif
            }
            pNode = listdl_Next(pNodeList, pNode);
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    static
    uint16_t        nodeHash_IndexFromHash(
        NODEHASH_DATA   *this,
        uint32_t        hash
    )
    {
        uint16_t        index;
        
        index = hash % this->cHash;
        return index;
    }
    
    
    
    static
    LISTDL_DATA *   nodeHash_NodeListFromHash(
        NODEHASH_DATA   *this,
        uint32_t        hash
    )
    {
        LISTDL_DATA     *pNodeList;
        
        pNodeList = &this->pHash[nodeHash_IndexFromHash(this, hash)];
        return( pNodeList );
    }
    
    
    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEHASH_DATA * nodeHash_Alloc(
    )
    {
        NODEHASH_DATA   *this;
        uint32_t        cbSize = sizeof(NODEHASH_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEHASH_DATA * nodeHash_New(
        uint16_t        cHash           // [in] Hash Table Size
    )
    {
        NODEHASH_DATA   *this;
        
        this = nodeHash_Alloc( );
        if (this) {
            this = nodeHash_Init(this, cHash);
        }
        
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        nodeHash_getPriority(
        NODEHASH_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            nodeHash_setPriority(
        NODEHASH_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        //cbp->priority = value;
        return true;
    }



    //---------------------------------------------------------------
    //                           S i z e
    //---------------------------------------------------------------
    
    uint32_t        nodeHash_getSize(
        NODEHASH_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return this->size;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------

    ERESULT         nodeHash_Add(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
    #endif

        pEntry = nodeHash_FindNodeHash(this, node_getName(pNode));
        if (pEntry && !obj_IsFlag(this, NODEHASH_FLAG_DUPS)) {
            DEBUG_BREAK();
            return ERESULT_DATA_ALREADY_EXISTS;
        }
        
        // Determine the entry number.
        if (0 == listdl_Count(&this->freeList)) {
            if ( nodeHash_AddBlock(this) )
                ;
            else {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        pEntry = listdl_DeleteHead(&this->freeList);
        if (NULL == pEntry) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Add it to the table.
        obj_Retain(pNode);
        pEntry->pNode = pNode;
        
        pNodeList = nodeHash_NodeListFromHash(this, node_getHash(pNode));
        listdl_Add2Tail(pNodeList, pEntry);
        
        ++this->size;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         nodeHash_AddA(
        NODEHASH_DATA    *this,
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNode = node_NewWithUTF8AndClass(pName, cls, pData);
        if (OBJ_NIL == pNode) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        eRc = nodeHash_Add(this, pNode);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         nodeHash_AddUpdate(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = nodeHash_FindNodeHash(this, node_getName(pNode));
        if (pEntry) {
            obj_Release(pEntry->pNode);
            //pEntry->pNode = OBJ_NIL;
            obj_Retain(pNode);
            pEntry->pNode = pNode;
            return ERESULT_SUCCESS;
        }
        
        // Determine the entry number.
        if (0 == listdl_Count(&this->freeList)) {
            if ( nodeHash_AddBlock(this) )
                ;
            else {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        pEntry = listdl_DeleteHead(&this->freeList);
        if (NULL == pEntry) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Add it to the table.
        obj_Retain(pNode);
        pEntry->pNode = pNode;
        
        pNodeList = nodeHash_NodeListFromHash(this, node_getHash(pNode));
        listdl_Add2Tail(pNodeList, pEntry);
        
        ++this->size;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         nodeHash_AddUpdateA(
        NODEHASH_DATA    *this,
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNode = node_NewWithUTF8AndClass(pName, cls, pData);
        if (OBJ_NIL == pNode) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        eRc = nodeHash_AddUpdate(this, pNode);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
    
    

    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    NODEHASH_DATA * nodeHash_Copy(
        NODEHASH_DATA	*this
    )
    {
        NODEHASH_DATA   *pOther;
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        uint32_t        i;
        NODE_DATA       *pItem;
        OBJ_IUNKNOWN    *pVtbl;
        ERESULT         eRc;
        bool            fRelease;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeHash_New(this->cHash);
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }

        for (i=0; i<this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pEntry = listdl_Head(pNodeList);
            while ( pEntry ) {
                pItem = pEntry->pNode;
                if (pItem) {
                    fRelease = false;
                    pVtbl = obj_getVtbl(pItem);
                    if (pVtbl->pCopy) {
                        pItem = pVtbl->pCopy(pItem);
                        fRelease = true;
                    }
                    else {
                        obj_Retain(pItem);
                    }
                    eRc = nodeHash_Add(pOther, pItem);
                    if (ERESULT_HAS_FAILED(eRc)) {
                        obj_Release(pOther);
                        return OBJ_NIL;
                    }
                    if (fRelease) {
                        obj_Release(pItem);
                    }
                }
                pEntry = listdl_Next(pNodeList, pEntry);
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------
    
    void            nodeHash_Dealloc(
        OBJ_ID          objId
    )
    {
        NODEHASH_DATA   *this = objId;
        LISTDL_DATA     *pNodeList;
        NODEHASH_BLOCK  *pBlock;
        NODEHASH_NODE   *pEntry;
        uint32_t        i;
        
        // Do initialization.
        if (NULL == this) {
            return;
        }
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        // Release all the nodes.
        for (i=0; i<this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pEntry = listdl_Head(pNodeList);
            while ( pEntry ) {
                obj_Release(pEntry->pNode);
                pEntry->pNode = OBJ_NIL;
                pEntry = listdl_Next(pNodeList, pEntry);
            }
        }
        
        while ( listdl_Count(&this->blocks) ) {
            pBlock = listdl_DeleteHead(&this->blocks);
            mem_Free( pBlock );
        }
        
        if( this->pHash ) {
            mem_Free( this->pHash );
            this->pHash = NULL;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                      D e e p  C o p y
    //---------------------------------------------------------------
    
    NODEHASH_DATA * nodeHash_DeepCopy(
        NODEHASH_DATA    *this
    )
    {
        NODEHASH_DATA   *pOther;
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        uint32_t        i;
        NODE_DATA       *pItem;
        OBJ_IUNKNOWN    *pVtbl;
        ERESULT         eRc;
        bool            fRelease;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeHash_New(this->cHash);
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        for (i=0; i<this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pEntry = listdl_Head(pNodeList);
            while ( pEntry ) {
                pItem = pEntry->pNode;
                if (pItem) {
                    fRelease = false;
                    pVtbl = obj_getVtbl(pItem);
                    if (pVtbl->pDeepCopy) {
                        pItem = pVtbl->pDeepCopy(pItem);
                        fRelease = true;
                    }
                    else if (pVtbl->pCopy) {
                        pItem = pVtbl->pCopy(pItem);
                        fRelease = true;
                    }
                    else {
                        obj_Retain(pItem);
                    }
                    eRc = nodeHash_Add(pOther, pItem);
                    if (ERESULT_HAS_FAILED(eRc)) {
                        obj_Release(pOther);
                        return OBJ_NIL;
                    }
                    if (fRelease) {
                        obj_Release(pItem);
                    }
                }
                pEntry = listdl_Next(pNodeList, pEntry);
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         nodeHash_Delete(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = nodeHash_FindNodeHash(this, node_getName(pNode));
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        pNodeList = nodeHash_NodeListFromHash(this, node_getHash(pNode));
        obj_Release(pEntry->pNode);
        pEntry->pNode = OBJ_NIL;
        listdl_Delete(pNodeList, pEntry);
        listdl_Add2Tail(&this->freeList, pEntry);
        --this->size;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         nodeHash_DeleteA(
        NODEHASH_DATA	*this,
        const
        char            *pName
    )
    {
        //ERESULT         eRc;
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        NAME_DATA       *pNameObj = OBJ_NIL;
        uint32_t        hash;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNameObj = name_NewUTF8(pName);
        if(OBJ_NIL == pNameObj) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        hash = name_getHash(pNameObj);
        pEntry = nodeHash_FindNodeHash(this, pNameObj);
        obj_Release(pNameObj);
        pNameObj = OBJ_NIL;
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        pNodeList = nodeHash_NodeListFromHash(this, hash);
        obj_Release(pEntry->pNode);
        pEntry->pNode = OBJ_NIL;
        listdl_Delete(pNodeList, pEntry);
        listdl_Add2Tail(&this->freeList, pEntry);
        --this->size;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         nodeHash_DeleteName(
        NODEHASH_DATA   *this,
        NAME_DATA       *pName
    )
    {
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pName) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = nodeHash_FindNodeHash(this, pName);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        pNodeList = nodeHash_NodeListFromHash(this, name_getHash(pName));
        listdl_Delete(pNodeList, pEntry);
        listdl_Add2Tail(&this->freeList, pEntry);
        --this->size;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    NODE_DATA *     nodeHash_Find(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( OBJ_NIL == pNode ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
#endif
        
        // Return to caller.
        return nodeHash_FindName(this, node_getName(pNode));
    }
    
    
    NODE_DATA *     nodeHash_FindA(
        NODEHASH_DATA	*this,
        const
        char            *pName
    )
    {
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        NAME_DATA       *pNameObj = OBJ_NIL;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
    #endif
        
        pNameObj = name_NewUTF8(pName);
        if(OBJ_NIL == pNameObj) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        pEntry = nodeHash_FindNodeHash(this, pNameObj);
        obj_Release(pNameObj);
        pNameObj = OBJ_NIL;
        if (pEntry) {
            obj_setLastError(this, ERESULT_SUCCESS);
            return pEntry->pNode;
        }

        // Return to caller.
        obj_setLastError(this, ERESULT_DATA_NOT_FOUND);
        return OBJ_NIL;
    }


    NODE_DATA *     nodeHash_FindName(
        NODEHASH_DATA   *this,
        NAME_DATA       *pName
    )
    {
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
#endif
        
        pEntry = nodeHash_FindNodeHash(this, pName);
        if (pEntry) {
            obj_setLastError(this, ERESULT_SUCCESS);
            return pEntry->pNode;
        }
        
        // Return to caller.
        obj_setLastError(this, ERESULT_DATA_NOT_FOUND);
        return OBJ_NIL;
    }
    
    

    //---------------------------------------------------------------
    //                          F o r  E a c h
    //---------------------------------------------------------------
    
    ERESULT         nodeHash_ForEach(
        NODEHASH_DATA	*this,
        P_VOIDEXIT2_BE  pScan,
        OBJ_ID          pObj            // Used as first parameter of scan method
    )
    {
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        uint32_t        i;
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
       
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        for (i=0; i<this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pEntry = listdl_Head(pNodeList);
            while ( pEntry ) {
                eRc = pScan(pObj,pEntry->pNode);
                if (ERESULT_HAS_FAILED(eRc)) {
                    break;
                }
                pEntry = listdl_Next(pNodeList, pEntry);
            }
            if (ERESULT_HAS_FAILED(eRc)) {
                break;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEHASH_DATA * nodeHash_Init(
        NODEHASH_DATA   *this,
        uint16_t        cHash           // [in] Hash Table Size
    )
    {
        uint32_t        cbSize;
        uint32_t        i;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_NODEHASH );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeHash_Vtbl);
        
        this->cHash = cHash;
        cbSize = HASH_BLOCK_SIZE - sizeof(NODEHASH_BLOCK);
        cbSize /= sizeof(NODEHASH_NODE);
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
            listdl_Init(&this->pHash[i], offsetof(NODEHASH_NODE, list));
        }
        listdl_Init(&this->freeList, offsetof(NODEHASH_NODE, list));
        
    #ifdef NDEBUG
    #else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pHash);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                         N o d e s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * nodeHash_Nodes(
        NODEHASH_DATA	*this
    )
    {
        NODEARRAY_DATA  *pKeys;
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        uint32_t        i;
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pKeys = nodeArray_New();
        for (i=0; i<this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pEntry = listdl_Head(pNodeList);
            while ( pEntry ) {
                eRc = nodeArray_AppendNode(pKeys, pEntry->pNode, NULL);
                if (ERESULT_HAS_FAILED(eRc)) {
                    break;
                }
                pEntry = listdl_Next(pNodeList, pEntry);
            }
            if (ERESULT_HAS_FAILED(eRc)) {
                break;
            }
        }
        nodeArray_SortAscending(pKeys);
        
        // Return to caller.
        obj_setLastError(this, eRc);
        return pKeys;
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
     void        *pMethod = nodeHash_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a
                        character string which represents the method name without
                        the object name, "nodeHash", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          nodeHash_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEHASH_DATA   *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return nodeHash_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == nodeHash_ToDebugString) {
                    return "ToDebugString";
                }
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     nodeHash_ToDebugString(
        NODEHASH_DATA   *this,
        int             indent
    )
    {
        uint32_t        i;
        //uint32_t        j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        NODE_DATA       *pNode;
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        pInfo = obj_getInfo(this);

        pStr = AStr_New();
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        AStr_AppendPrint(
                     pStr,
                     "{%p(%s) Size=%d\n",
                     this,
                     pInfo->pClassName,
                     this->size
                     );
        
        for (i=0; i<this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pEntry = listdl_Head(pNodeList);
            while ( pEntry ) {
                pNode = pEntry->pNode;
                if (((OBJ_DATA *)(pNode))->pVtbl->pToDebugString) {
                    pWrkStr =   ((OBJ_DATA *)(pNode))->pVtbl->pToDebugString(
                                            pNode,
                                            indent+3
                                );
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
                pEntry = listdl_Next(pNodeList, pEntry);
            }
        }
        
        AStr_AppendCharRepeatA(pStr, 1, '\n');
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        AStr_AppendPrint( pStr, "%p(%s)}\n", this, pInfo->pClassName);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeHash_Validate(
        NODEHASH_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_NODEHASH) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(NODEHASH_DATA)) ) {
            obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return false;
        }

        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


