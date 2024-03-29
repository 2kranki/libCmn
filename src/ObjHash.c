// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjHash.c
 *	Generated 02/02/2020 09:55:43
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
#include        <ObjHash_internal.h>
#include        <ObjEnum_internal.h>
#include        <stdio.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    uint32_t        sizeTable[24] = {
        1,
        3,
        5,
        7,
        11,
        17,
        37,
        67,
        131,
        257,
        521,
        1031,
        2053,
        4099,
        8209,
        16411,
        32771,
        65537,
        131101,
        262147,
        524309,
        1048583,
        2097169,
        4194319
    };
    static
    uint32_t        cSizeTable = 24;





 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    OBJHASH_NODE *  ObjHash_FindUniqueInt(
        OBJHASH_DATA    *this,
        uint32_t        index
    );

    static
    uint16_t        ObjHash_IndexFromHash(
        OBJHASH_DATA    *this,
        uint32_t        hash
    );

    static
    LISTDL_DATA *   ObjHash_NodeListFromHash(
        OBJHASH_DATA    *this,
        uint32_t        hash
    );



    //---------------------------------------------------------------
    //                  N o d e  H a s h  C h a i n
    //---------------------------------------------------------------

    ERESULT         ObjHash_NodeEnchain(
        OBJHASH_DATA    *this,
        OBJHASH_MAIN    *pMain,
        OBJHASH_NODE    *pNode
    )
    {
        LISTDL_DATA     *pNodeList;
        LISTDL_DATA     *pLevel;

        pLevel = (LISTDL_DATA *)array_GetAddrOf(pMain->pLevels, pNode->scope+1);
        if (NULL == pLevel) {
            return ERESULT_INVALID_PARAMETER;
        }

        // Chain it to the appropriate lists.
        pNodeList = &pMain->pHash[pNode->hash % pMain->cHash];
        listdl_Add2Head(pNodeList, pNode);
        listdl_Add2Head(pLevel, pNode);

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         ObjHash_NodeUnchain(
        OBJHASH_DATA    *this,
        OBJHASH_MAIN    *pMain,
        OBJHASH_NODE    *pNode
    )
    {
        LISTDL_DATA     *pNodeList;
        LISTDL_DATA     *pLevel;

        pLevel = (LISTDL_DATA *)array_GetAddrOf(pMain->pLevels, pNode->scope+1);
        if (NULL == pLevel) {
            return ERESULT_INVALID_PARAMETER;
        }

        // Unchain it from the appropriate lists.
        pNodeList = &pMain->pHash[pNode->hash % pMain->cHash];
        listdl_Delete(pNodeList, pNode);
        listdl_Delete(pLevel, pNode);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                  D e l e t e  E x i t
    //---------------------------------------------------------------

    ERESULT         ObjHash_DeleteExit(
        OBJHASH_DATA    *this,
        OBJHASH_NODE    *pNode,
        void            *pArg3
    )
    {

        if (pNode->pObject) {
            obj_Release(pNode->pObject);
            pNode->pObject = OBJ_NIL;
        }

        return ERESULT_SUCCESS;
    }



    OBJ_ID          ObjHash_DeleteNodeFromList(
        OBJHASH_DATA    *this,
        OBJHASH_NODE    *pNode
    )
    {
        ERESULT         eRc;
        LISTDL_DATA     *pNodeList;
        OBJ_ID          pReturn = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (NULL == pNode) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pNodeList = ObjHash_NodeListFromHash(this, pNode->hash);
        listdl_Delete(pNodeList, pNode);
        pReturn = pNode->pObject;
        pNode->pObject = OBJ_NIL;
        eRc = Blocks_RecordFree((BLOCKS_DATA *)this, pNode);

        // Return to caller.
        return pReturn;
    }



    static
    OBJHASH_NODE *  ObjHash_FindNode(
        OBJHASH_DATA    *this,
        uint32_t        hash,
        OBJ_ID          pObject,
        P_OBJ_COMPARE   pCompare,
        int32_t         index       // (0..n)th entry in chain
    )
    {
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        int             iRc;
        const
        OBJ_IUNKNOWN    *pVtbl;

        // Do initialization.
        pNodeList = ObjHash_NodeListFromHash(this, hash);
        pVtbl = obj_getVtbl(pObject);

        pNode = listdl_Head(pNodeList);
        while ( pNode ) {
            if (pNode->hash == hash) {
                iRc = pCompare(pNode->pObject, pObject);
                if (0 == iRc) {
                    index--;
                    if (index < 0)
                        return pNode;
                }
                if (iRc > 0) {
                    break;
                }
            }
            pNode = listdl_Next(pNodeList, pNode);
        }

        // Return to caller.
        return NULL;
    }



    static
    OBJHASH_NODE *  ObjHash_FindUniqueInt(
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
        for (hash=0; hash<this->main.cHash; ++hash) {
            pNodeList = &this->main.pHash[hash];
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
    uint16_t        ObjHash_IndexFromHash(
        OBJHASH_DATA    *this,
        uint32_t        hash
    )
    {
        uint16_t        index;

        index = hash % this->main.cHash;
        return index;
    }



    static
    LISTDL_DATA *   ObjHash_NodeListFromHash(
        OBJHASH_DATA    *this,
        uint32_t        hash
    )
    {
        LISTDL_DATA     *pNodeList;

        pNodeList = &this->main.pHash[ObjHash_IndexFromHash(this, hash)];
        return( pNodeList );
    }



    //---------------------------------------------------------------
    //                  D e l e t e  E x i t
    //---------------------------------------------------------------

    /*!
     Rebuild the hash index with a different number of Hash Buckets.
     This method allows you to grow or shrink the index dynamically
     as needed.
     @param     this    object pointer
     @param     cHash   number of buckets to use
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
#ifdef XXXXXXXX
    ERESULT         ObjHash_Rehash(
        OBJHASH_DATA    *this,
        uint32_t        cHash
    )
    {
        uint32_t        cHash  = this->cHash;
        uint32_t        cHashIdx  = this->cHashIdx;
        LISTDL_DATA     *pHash = this->pHash;
        uint32_t        newSize;
        uint32_t        i;
        uint32_t        idx;
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;

        // First, allocate new new Hash Index.
        if ((this->cHashIdx + 1) < cSizeTable)
            ;
        else {
            return ERESULT_OUT_OF_MEMORY;
        }
        cHashIdx++;
        cHash = sizeTable[cHashIdx];
        newSize = cHash * sizeof(LISTDL_DATA);
        pHash = (LISTDL_DATA *)mem_Malloc(newSize);
        if (NULL == this->pHash) {
            return ERESULT_OUT_OF_MEMORY;
        }
        for (i=0; i<this->cHash; ++i) {
            listdl_Init(&this->pHash[i], offsetof(OBJHASH_NODE, list));
        }

        if (this->pHash) {
            // Now rehash the hash table nodes.
            for (i=0; i<cHash; ++i) {
                pNodeList = &this->pHash[i];
                pNode = listdl_Head(pNodeList);
                while (pNode) {
                    idx = pNode->hash % cHash;
                    listdl_Add2Head(&pHash[idx], pNode);
                    pNode = listdl_Next(pNodeList, pNode);
                }
            }

            // Now free the old Hash Table.
            mem_Free(this->pHash);
            this->pHash = NULL;
            this->cHash = 0;
        }

        // Make the new Hash Table the active one.
        this->cHashIdx = cHashIdx;
        this->cHash = cHash;
        this->pHash = pHash;

        return ERESULT_SUCCESS;
    }
#endif





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJHASH_DATA *     ObjHash_Alloc (
        void
    )
    {
        OBJHASH_DATA    *this;
        uint32_t        cbSize = sizeof(OBJHASH_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJHASH_DATA *  ObjHash_New (
        void
    )
    {
        OBJHASH_DATA    *this;
        ERESULT         eRc;
        
        this = ObjHash_Alloc( );
        if (this) {
            this = ObjHash_Init(this);
            if (this) {
                eRc = ObjHash_Setup(this, OBJHASH_TABLE_SIZE_XXXXSMALL);
            }
        }
        return this;
    }


    OBJHASH_DATA *  ObjHash_NewWithSize (
        uint16_t        cHash       // [in] Hash Table Size
    )
    {
        OBJHASH_DATA    *this;
        ERESULT         eRc;

        this = ObjHash_Alloc( );
        if (this) {
            this = ObjHash_Init(this);
            if (this) {
                eRc = ObjHash_Setup(this, cHash);
            }
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                   D u p l i c a t e s
    //---------------------------------------------------------------

    bool            ObjHash_getDuplicates(
        OBJHASH_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->fDups ? true : false;
    }


    bool            ObjHash_setDuplicates(
        OBJHASH_DATA    *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fDups = fValue ? 1 : 0;

        return true;
    }



    //---------------------------------------------------------------
    //                          S c o p e
    //---------------------------------------------------------------

    uint32_t        ObjHash_getScopeSize(
        OBJHASH_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return array_getSize(this->main.pLevels);
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        ObjHash_getSize (
        OBJHASH_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Blocks_getNumActive((BLOCKS_DATA *)this);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    BLOCKS_DATA *   ObjHash_getSuper (
        OBJHASH_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif


        return (BLOCKS_DATA *)this;
    }


    OBJ_IUNKNOWN *  ObjHash_getSuperVtbl (
        OBJHASH_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //----------------------------------------------------------
    //                          A d d
    //----------------------------------------------------------

    ERESULT         ObjHash_Add(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;

        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = ObjHash_AddInScope(this, ObjHash_getScopeSize(this)-1, pObject, pIndex);

        // Return to caller.
        return eRc;
    }


    ERESULT         ObjHash_AddInScope(
        OBJHASH_DATA    *this,
        uint32_t        scope,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;
        //LISTDL_DATA     *pNodeList;
        LISTDL_DATA     *pLevel;
        OBJHASH_NODE    *pNode;
        uint32_t        hash;
        uint32_t        unique = 0;
        OBJ_IUNKNOWN    *pVtbl;

        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pVtbl = obj_getVtbl(pObject);
        hash = pVtbl->pHash(pObject);
        pLevel = array_GetAddrOf(this->main.pLevels, scope+1);
        if (NULL == pLevel) {
            return ERESULT_INVALID_PARAMETER;
        }

        if (!this->fDups) {
            pNode = ObjHash_Find(this, pObject);
            if (pNode) {
                return ERESULT_DATA_ALREADY_EXISTS;
            }
        }

        pNode = Blocks_RecordNew((BLOCKS_DATA *)this, &unique);
        if (pNode) {
            // Add it to the table.
            obj_Retain(pObject);
            pNode->pObject = pObject;
            pNode->hash    = hash;
            pNode->unique  = unique;
            pNode->scope   = scope;
            TRC_OBJ(this, "\tAdding %2d:%2d - %p\n", scope, unique, pNode);

            // Chain it to the appropriate lists.
            eRc = ObjHash_NodeEnchain(this, &this->main, pNode);
            if (ERESULT_FAILED(eRc)) {
                return ERESULT_GENERAL_FAILURE;
            }
        }

        // Return to caller.
        if (pIndex)
            *pIndex = unique;
        return ERESULT_SUCCESS;
    }


    ERESULT         ObjHash_AddUnlinked(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    )
    {
        OBJHASH_NODE    *pNode;
        uint32_t        unique = 0;

#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pIndex) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pNode = Blocks_RecordNew((BLOCKS_DATA *)this, &unique);
        if (pNode) {
            obj_Retain(pObject);
            pNode->pObject = pObject;
            pNode->unique  = unique;
        }

        // Add it to the table.

        // Return to caller.
        if (pIndex)
            *pIndex = pNode->unique;
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = ObjHash_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OBJHASH object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ObjHash_Assign (
        OBJHASH_DATA	*this,
        OBJHASH_DATA    *pOther
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        OBJ_IUNKNOWN    *pVtbl;
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        OBJ_ID          pObj;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjHash_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        eRc = ObjHash_Reset(pOther);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        eRc = ObjHash_Setup(pOther, this->main.cHash);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        for (i=0; i<this->main.cHash; ++i) {
            pNodeList = &this->main.pHash[i];
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
                    ObjHash_Add(pOther, pObj, NULL);
                    obj_Release(pObj);
                }
                pNode = listdl_Next(pNodeList, pNode);
            }
        }

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //       C a l c  H a s h  I n d e x  S t a t i s t i c s
    //---------------------------------------------------------------

    ERESULT            ObjHash_CalcHashStats(
        OBJHASH_DATA    *this,
        uint32_t        *pNumBuckets,   // Number of Hash Buckets
        uint32_t        *pNumEmpty,     // Number of Empty Hash Buckets
        uint32_t        *pNumMax,       // Maximum Number in any one Hash Bucket
        uint32_t        *pNumAvg        // Average Number in each Hash Bucket
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL_DATA     *pNodeList;
        uint32_t        i;
        uint32_t        count;
        uint32_t        numEmpty = 0;
        uint32_t        numMax = 0;
        uint32_t        num = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Do the calculations.
        for (i=0; i<this->main.cHash; ++i) {
            pNodeList = &this->main.pHash[i];
            count = listdl_Count(pNodeList);
            if (0 == count) {
                ++numEmpty;
            }
            if (count > numMax) {
                numMax = count;
            }
            num += count;
        }

        // Return to caller.
        if (pNumBuckets)
            *pNumBuckets = this->main.cHash;
        if (pNumEmpty)
            *pNumEmpty = numEmpty;
        if (pNumMax)
            *pNumMax = numMax;
        if (pNumAvg) {
            if (this->main.cHash - numEmpty) {
                *pNumAvg = num / (this->main.cHash - numEmpty);
            }
            else
                *pNumAvg = 0;
        }
        return eRc;
    }



    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             ObjHash_Compare (
        OBJHASH_DATA    *this,
        OBJHASH_DATA    *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!ObjHash_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        ObjHash      *pCopy = ObjHash_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJHASH object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJHASH_DATA *     ObjHash_Copy (
        OBJHASH_DATA       *this
    )
    {
        OBJHASH_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef OBJHASH_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = ObjHash_New( );
        if (pOther) {
            eRc = ObjHash_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            ObjHash_Dealloc (
        OBJ_ID          objId
    )
    {
        OBJHASH_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJHASH_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->main.pLevels) {
            obj_Release(this->main.pLevels);
            this->main.pLevels = OBJ_NIL;
        }
        if (this->main.pHash) {
            mem_Free(this->main.pHash);
            this->main.pHash = NULL;
            this->main.cHash = 0;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        ObjHash      *pDeepCopy = ObjHash_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJHASH object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJHASH_DATA *     ObjHash_DeepyCopy (
        OBJHASH_DATA       *this
    )
    {
        OBJHASH_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjHash_New( );
        if (pOther) {
            eRc = ObjHash_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //----------------------------------------------------------
    //                      D e l e t e
    //----------------------------------------------------------

    OBJ_ID          ObjHash_Delete(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc;
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        uint32_t        hash;
        OBJ_ID          pReturn = OBJ_NIL;
        const
        OBJ_IUNKNOWN    *pVtbl;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pVtbl = obj_getVtbl(pObject);

        hash = pVtbl->pHash(pObject);
        pNodeList = ObjHash_NodeListFromHash(this, hash);

        pNode = ObjHash_FindNode(this, hash, pObject, pVtbl->pCompare, 0);
        if (pNode) {
            listdl_Delete(pNodeList, pNode);
            pReturn = pNode->pObject;
            pNode->pObject = OBJ_NIL;
            eRc = Blocks_RecordFree((BLOCKS_DATA *)this, pNode);
        }

        // Return to caller.
        return pReturn;
    }


    ERESULT         ObjHash_DeleteAll(
        OBJHASH_DATA    *this
    )
    {
        ERESULT         eRc;
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        OBJHASH_NODE    *pNext;
        uint32_t        i;
        OBJ_ID          pReturn = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        for (i=0; i<this->main.cHash; ++i) {
            pNodeList = &this->main.pHash[i];
            pNode = listdl_Head(pNodeList);
            while ( pNode ) {
                pNext = listdl_Next(pNodeList, pNode);
                listdl_Delete(pNodeList, pNode);
                pReturn = pNode->pObject;
                pNode->pObject = OBJ_NIL;
                eRc = Blocks_RecordFree((BLOCKS_DATA *)this, pNode);
                if (pReturn) {
                    obj_Release(pReturn);
                    pReturn = OBJ_NIL;
                }
                pNode = pNext;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    OBJ_ID          ObjHash_DeleteIndex(
        OBJHASH_DATA    *this,
        uint32_t        index
    )
    {
        ERESULT         eRc;
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        OBJ_ID          pReturn = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pNode = ObjHash_FindUniqueInt(this, index);
        if (pNode) {
            pNodeList = ObjHash_NodeListFromHash(this, pNode->hash);
            listdl_Delete(pNodeList, pNode);
            pReturn = pNode->pObject;
            pNode->pObject = OBJ_NIL;
            eRc = Blocks_RecordFree((BLOCKS_DATA *)this, pNode);
        }

        // Return to caller.
        return pReturn;
    }


    ERESULT         ObjHash_DeleteUnlinked(
        OBJHASH_DATA    *this,
        uint32_t        index
    )
    {
        ERESULT         eRc;
        OBJHASH_NODE    *pNode;

#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (0 == index) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pNode = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (pNode) {
            obj_Release(pNode->pObject);
            pNode->pObject = OBJ_NIL;
        }
        eRc = Blocks_RecordFree((BLOCKS_DATA *)this, pNode);

        // Add it to the table.

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjHash_Disable (
        OBJHASH_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjHash_Enable (
        OBJHASH_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      E n u m
    //---------------------------------------------------------------

    OBJENUM_DATA *  ObjHash_Enum(
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
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return pEnum;
        }
#endif

        pEnum = ObjEnum_New();
        if (OBJ_NIL == pEnum) {
            return OBJ_NIL;
        }

        for (i=0; i<this->main.cHash; ++i) {
            pNodeList = &this->main.pHash[i];
            pNode = listdl_Head(pNodeList);
            while (pNode) {
                if (pNode->pObject) {
                    ObjEnum_AppendObj(pEnum, pNode->pObject);
                }
                pNode = listdl_Next(pNodeList, pNode);
            }
        }
        eRc = ObjEnum_SortAscending(pEnum);

        // Return to caller.
        return pEnum;
    }


    //----------------------------------------------------------
    //                        F i n d
    //----------------------------------------------------------

    OBJ_ID          ObjHash_Find(
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
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pVtbl = obj_getVtbl(pObject);

        hash = pVtbl->pHash(pObject);

        pNode = ObjHash_FindNode(this, hash, pObject, pVtbl->pCompare, 0);
        if (pNode) {
            return pNode->pObject;
        }

        // Return to caller.
        return OBJ_NIL;
    }


    OBJ_ID          ObjHash_FindCmp(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject,
        P_OBJ_COMPARE   pCmp
    )
    {
        OBJHASH_NODE    *pNode;
        uint32_t        hash;
        const
        OBJ_IUNKNOWN    *pVtbl;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pVtbl = obj_getVtbl(pObject);

        hash = pVtbl->pHash(pObject);

        pNode = ObjHash_FindNode(this, hash, pObject, pCmp, 0);
        if (pNode) {
            return pNode->pObject;
        }

        // Return to caller.
        return OBJ_NIL;
    }


    OBJ_ID          ObjHash_FindIndex(
        OBJHASH_DATA    *this,
        uint32_t        index
    )
    {
        OBJHASH_NODE    *pNode;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pNode = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (pNode) {
            TRC_OBJ(this, "\tFound %2d - %p\n", index, pNode);
            return pNode->pObject;
        }

        // Return to caller.
        return OBJ_NIL;
    }


    OBJ_ID          ObjHash_Findth(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject,
        uint16_t        index           // 0..n th entry with same name
    )
    {
        OBJHASH_NODE    *pNode;
        uint32_t        hash;
        const
        OBJ_IUNKNOWN    *pVtbl;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pVtbl = obj_getVtbl(pObject);

        hash = pVtbl->pHash(pObject);

        pNode = ObjHash_FindNode(this, hash, pObject, pVtbl->pCompare ,(int32_t)index);
        if (pNode) {
            return pNode->pObject;
        }

        // Return to caller.
        return OBJ_NIL;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJHASH_DATA *   ObjHash_Init (
        OBJHASH_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJHASH_DATA);
        ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this = (OBJ_ID)Blocks_Init((BLOCKS_DATA *)this);        // Needed for Inheritance
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ObjHash_Vtbl);

        ObjHash_setDuplicates(this, true);

        // Allow for fast access to objects.
        eRc = Blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(OBJHASH_NODE));
        if (ERESULT_FAILED(eRc)) {
           DEBUG_BREAK();
           obj_Release(this);
           return this;
        }

        Blocks_setDeleteExit(
                             (BLOCKS_DATA *)this,
                             (void *)ObjHash_DeleteExit,
                             this,
                             NULL
        );
        Blocks_SetupIndex((BLOCKS_DATA *)this);
        
        this->main.pLevels = array_NewWithSize(sizeof(LISTDL_DATA));
        if (OBJ_NIL == this->main.pLevels) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        } else {
            LISTDL_DATA     list;
            // Add Scope 0.
            listdl_Init(&list, offsetof(OBJHASH_NODE, level));
            eRc = array_Push(this->main.pLevels, &list);
        }

#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        fprintf(
                stderr, 
                "ObjHash::sizeof(OBJHASH_DATA) = %lu\n", 
                sizeof(OBJHASH_DATA)
        );
        fprintf(
                stderr,
                "ObjHash::sizeof(OBJHASH_NODE) = %lu\n",
                sizeof(OBJHASH_NODE)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OBJHASH_DATA));
        BREAK_NOT_BOUNDARY4(sizeof(OBJHASH_NODE));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ObjHash_IsEnabled (
        OBJHASH_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
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
        void        *pMethod = ObjHash_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ObjHash", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ObjHash_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJHASH_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJHASH_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ObjHash_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return ObjHash_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ObjHash_Enable;
                        }
                        break;

#ifdef  OBJHASH_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return ObjHash_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return ObjHash_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ObjHash_ToDebugString;
                        }
#ifdef  OBJHASH_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return ObjHash_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ObjHash_ToDebugString)
                    return "ToDebugString";
#ifdef  OBJHASH_JSON_SUPPORT
                if (pData == ObjHash_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                 R e b u i l d  I n d e x
    //---------------------------------------------------------------

    ERESULT            ObjHash_RebuildIndex(
        OBJHASH_DATA    *this,
        uint32_t        cHash           // Number of Hash Buckets
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL_DATA     *pHash;         // New Hash Table
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        uint32_t        i;
        uint32_t        idx;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pHash = mem_Calloc(cHash, sizeof(LISTDL_DATA));
        if (NULL == pHash) {
            return ERESULT_OUT_OF_MEMORY;
        }

        // Create the new index;
        for (i=0; i<this->main.cHash; ++i) {
            pNodeList = &this->main.pHash[i];
            while (listdl_Count(pNodeList)) {
                pNode = listdl_DeleteHead(pNodeList);
                idx = pNode->hash % cHash;
                listdl_Add2Tail(&pHash[idx], pNode);
            }
        }

        // Make the new index active.
        mem_Free(this->main.pHash);
        this->main.pHash = pHash;
        this->main.cHash = cHash;

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------

    /*!
     Reset this object to its beginning state.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjHash_Reset (
        OBJHASH_DATA    *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = ObjHash_DeleteAll(this);

        if (this->main.pHash) {
            mem_Free(this->main.pHash);
            this->main.pHash = NULL;
        }
        this->main.cHash = 0;

        eRc = Blocks_Reset((BLOCKS_DATA *)this);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      S c o p e
    //---------------------------------------------------------------

    ERESULT         ObjHash_ScopeClose (
        OBJHASH_DATA    *this,
        OBJENUM_DATA    **ppEnum
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //LISTDL_DATA     *pNodeList;
        //uint32_t        hash;
        LISTDL_DATA     list;
        OBJHASH_NODE    *pNode;
        OBJHASH_NODE    *pNext;
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjHash_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (ObjHash_getScopeSize(this) <= 1) {
            return ERESULT_DATA_MISSING;
        }

        // Remove the scope.
        eRc = array_Pop(this->main.pLevels, &list);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        if (ppEnum) {
            pEnum = ObjEnum_New();
            if (OBJ_NIL == pEnum) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        // Now remove the scope entries from the table.
        // Now enumerate the scope entries.
        pNode = listdl_Head(&list);
        while (pNode) {
            if (pNode->pObject) {
                if (ppEnum) {
                    ObjEnum_AppendObj(pEnum, pNode->pObject);
                }
                pNext = listdl_Next(&list, pNode);
                eRc = ObjHash_NodeUnchain(this, &this->main, pNode);
                Blocks_RecordFree((BLOCKS_DATA *)this, pNode);
                pNode = pNext;
            }
        }

        // Return to caller.
        if (ppEnum) {
            *ppEnum = pEnum;
        }
        return eRc;
    }


    uint32_t        ObjHash_ScopeCount (
        OBJHASH_DATA    *this,
        uint32_t        scope
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL_DATA     *pList;
        uint32_t        count = 0;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjHash_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        pList = array_GetAddrOf(this->main.pLevels, scope+1);
        count = listdl_Count(pList);

        // Return to caller.
        return count;
    }


    OBJENUM_DATA *  ObjHash_ScopeEnum (
        OBJHASH_DATA    *this,
        uint32_t        scope
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL_DATA     list;
        OBJHASH_NODE    *pNode;
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjHash_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        eRc = array_Get(this->main.pLevels, scope+1, 1, &list);
        if (ERESULT_FAILED(eRc)) {
            return OBJ_NIL;
        }

        pEnum = ObjEnum_New();
        if (OBJ_NIL == pEnum) {
            return OBJ_NIL;
        }

        // Now enumerate the scope entries.
        pNode = listdl_Head(&list);
        while (pNode) {
            if (pNode->pObject) {
                ObjEnum_AppendObj(pEnum, pNode->pObject);
            }
            pNode = listdl_Next(&list, pNode);
        }

        // Return to caller.
        return pEnum;
    }


    int32_t         ObjHash_ScopeOpen (
        OBJHASH_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL_DATA     list;
        uint32_t        level = 0;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjHash_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -1;
        }
#endif

        listdl_Init(&list, offsetof(OBJHASH_NODE, level));
        eRc = array_Push(this->main.pLevels, &list);
        if (ERESULT_OK(eRc)) {
            level = ObjHash_getScopeSize(this) - 1;
        } else {
            level = -1;
        }

        // Return to caller.
        return level;
    }



    //---------------------------------------------------------------
    //                      S e t u p
    //---------------------------------------------------------------

    /*!
     Set up the hash table for this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjHash_Setup (
        OBJHASH_DATA    *this,
        uint16_t        cHash       // [in] Hash Table Size
    )
    {
        ERESULT         eRc;
        uint32_t        cbSize;
        uint32_t        i;
        LISTDL_DATA     list;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Free prior Hash Table.
        if (this->main.pHash) {
            mem_Free(this->main.pHash);
            this->main.pHash = NULL;
            this->main.cHash = 0;
        }

        // Allocate the Hash Table.
        cbSize = cHash * sizeof(LISTDL_DATA);
        this->main.pHash = (LISTDL_DATA *)mem_Malloc( cbSize );
        if (NULL == this->main.pHash) {
           DEBUG_BREAK();
           return ERESULT_OUT_OF_MEMORY;
        }
        for (i=0; i<cHash; ++i) {
           listdl_Init(&this->main.pHash[i], offsetof(OBJHASH_NODE, list));
        }
        this->main.cHash = cHash;

        // Reset to just Scope 0.
        eRc = array_Truncate(this->main.pLevels, 0);
        listdl_Init(&list, offsetof(OBJHASH_NODE, level));
        eRc = array_Push(this->main.pLevels, &list);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                  S e t u p  I n d e x
    //---------------------------------------------------------------

    ERESULT         ObjHash_SetupIndex (
        OBJHASH_DATA    *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = Blocks_SetupIndex((BLOCKS_DATA *)this);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjHash_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjHash_ToDebugString (
        OBJHASH_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        i;
        uint32_t        iMax;
        OBJHASH_NODE    *pNode;


        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjHash_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d  BlockSize=%d\n",
                    this,
                    pInfo->pClassName,
                    ObjHash_getSize(this),
                    obj_getRetainCount(this),
                    Blocks_getBlockSize((BLOCKS_DATA *)this)
            );

        iMax = this->main.cHash;
        for (i=0; i<iMax; i++) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            AStr_AppendPrint(pStr, "Hash List: %2d\n", i);
            pNode = listdl_Head(&this->main.pHash[i]);
            while (pNode) {
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent+8, ' ');
                }
                AStr_AppendPrint(
                                 pStr,
                                 "unique: %2d  scope: %2d\n",
                                 pNode->unique,
                                 pNode->scope
                );
                pNode = listdl_Next(&this->main.pHash[i], pNode);
            }
        }

#ifdef  XYZZY
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            ObjHash_Validate (
        OBJHASH_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OBJHASH))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(OBJHASH_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


