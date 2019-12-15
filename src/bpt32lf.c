// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   bpt32lf.c
 *	Generated 01/12/2019 14:04:41
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
#include        <bpt32lf_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      F i n d  N o d e
    //---------------------------------------------------------------
    
    /*!
     This method is responsible for locating the smallest key in the
     block greater than or equal to the search key.  So, the index
     returned points to the node where the key was found or where the
     key should be inserted.
     @param this        Object Pointer
     @param key         search key
     @param pIndex      Optional pointer to index of found key or
     insertion point returned
     @warning   Since this method returns the place to insert the key
     if it is not found, you must always check whether the
     returned node is equal to the search key or not after
     receiving the results of this method.
     */
    BPT32LF_NODE *  bpt32lf_FindNode (
        BPT32LF_DATA    *this,
        uint32_t        key,
        uint32_t        *pIndex
    )
    {
        //ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32LF_NODE    *pNode = NULL;
        uint32_t        i = 0;
        uint32_t        High = 0;
        uint32_t        Low = 0;
        uint32_t        Mid;
        int             rc;
        
        // Do initialization.
        
        if (this->pBlock->used < 4) {
            // Do a sequential search.
            for (i=0; i<this->pBlock->used; ++i) {
                pNode = bpt32lf_Index2Node(this, i);
                if (key <= pNode->key) {
                    break;
                }
            }
        }
        else {
            // Do a binary search.
            High = this->pBlock->used - 1;
            while( Low < High ) {
                Mid = (High + Low) / 2;
                i = Mid;
                pNode = bpt32lf_Index2Node(this, Mid);
                rc = key - pNode->key;
                if( rc < 0 )
                    High = Mid;
                else if( rc == 0 ) {
                    break;
                }
                else
                    Low = Mid + 1;
            }
            if( High == Low ) {
                pNode = bpt32lf_Index2Node(this, Low);
                i = Low;
                rc = key - pNode->key;
                if (rc > 0)
                    ++i;
            }
        }
        
        // Return to caller.
        if (pIndex)
            *pIndex = i;
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                      N o d e  F r o m  I n d e x
    //---------------------------------------------------------------
    
    BPT32LF_NODE *  bpt32lf_Index2Node (
        BPT32LF_DATA    *this,
        uint32_t        index               // Relative to 0
    )
    {
        BPT32LF_NODE    *pNode = NULL;
        uint32_t        i = 0;
        
        if (index == 0) {
            return this->pBlock->nodes;
        }
        
        i = index * (sizeof(BPT32LF_NODE) + this->actualSize);
        pNode = (BPT32LF_NODE *)(((uint8_t *)this->pBlock->nodes) + i);
        
        // Return to caller.
        return pNode;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BPT32LF_DATA *     bpt32lf_Alloc (
        void
    )
    {
        BPT32LF_DATA       *this;
        uint32_t        cbSize = sizeof(BPT32LF_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BPT32LF_DATA *  bpt32lf_New (
        void
    )
    {
        BPT32LF_DATA       *this;
        
        this = bpt32lf_Alloc( );
        if (this) {
            this = bpt32lf_Init(this);
        } 
        return this;
    }


    BPT32LF_DATA *  bpt32lf_NewWithSizes (
        uint32_t        blockSize,
        uint16_t        dataSize,
        uint32_t        index,
        bool            fAllocate,
        OBJ_ID          pMgr
    )
    {
        BPT32LF_DATA    *this;
        ERESULT         eRc;
        
        this = bpt32lf_New( );
        if (this) {
            eRc = bpt32lf_Setup(this, blockSize, dataSize, index, fAllocate);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            if (pMgr) {
                bpt32lf_setManager(this, pMgr);
            }
        }
        return this;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          B l o c k
    //---------------------------------------------------------------
    
    uint8_t *       bpt32lf_getBlock (
        BPT32LF_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        
        return (uint8_t *)this->pBlock;
    }
    
    
    bool            bpt32lf_setBlock (
        BPT32LF_DATA    *this,
        uint8_t         *pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (obj_Flag(this, BPT32LF_BLOCK_ALLOC) && this->pBlock) {
            mem_Free(this->pBlock);
            this->pBlock = NULL;
            obj_FlagOff(this, BPT32LF_BLOCK_ALLOC);
        }
        
        return (uint8_t *)this->pBlock;
    }
    
    

    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    uint32_t        bpt32lf_getIndex (
        BPT32LF_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->index;
    }
    
    
    bool            bpt32lf_setIndex (
        BPT32LF_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->index = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                    L a s t  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        bpt32lf_getLastIndex (
        BPT32LF_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->lastIndex + 1;
    }
    
    

    //---------------------------------------------------------------
    //                      M a n a g e r
    //---------------------------------------------------------------
    
    bool            bpt32lf_setManager(
        BPT32LF_DATA    *this,
        OBJ_ID          *pMgr          // Block Manager
    )
    {
        OBJ_IUNKNOWN    *pVtbl;
        
#ifdef NDEBUG
#else
        if( !bpt32lf_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pMgr = pMgr;
        if (pMgr) {
            pVtbl = obj_getVtbl(pMgr);
            this->pReq =    pVtbl->pQueryInfo(
                                              pMgr,
                                              OBJ_QUERYINFO_TYPE_METHOD,
                                              "BlockRequest"
                                              );
            if (NULL == this->pReq) {
                this->pMgr = OBJ_NIL;
                return false;
            }
        }
        else
            this->pReq = NULL;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N e x t
    //---------------------------------------------------------------
    
    uint32_t        bpt32lf_getNext (
        BPT32LF_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->pBlock->next;
    }
    
    
    bool            bpt32lf_setNext (
        BPT32LF_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pBlock->next = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r e v
    //---------------------------------------------------------------
    
    uint32_t        bpt32lf_getPrev (
        BPT32LF_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->pBlock->prev;
    }
    
    
    bool            bpt32lf_setPrev (
        BPT32LF_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pBlock->prev = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        bpt32lf_getPriority (
        BPT32LF_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            bpt32lf_setPriority (
        BPT32LF_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        bpt32lf_getSize (
        BPT32LF_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->pBlock->used;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  bpt32lf_getSuperVtbl (
        BPT32LF_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = bpt32lf_Assign(this,pOther);
     @endcode 
     @param     this    BPT32LF object pointer
     @param     pOther  a pointer to another BPT32LF object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         bpt32lf_Assign (
        BPT32LF_DATA		*this,
        BPT32LF_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!bpt32lf_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         bpt32lf_Compare (
        BPT32LF_DATA     *this,
        BPT32LF_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!bpt32lf_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        bpt32lf      *pCopy = bpt32lf_Copy(this);
     @endcode 
     @param     this    BPT32LF object pointer
     @return    If successful, a BPT32LF object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT32LF_DATA *     bpt32lf_Copy (
        BPT32LF_DATA       *this
    )
    {
        BPT32LF_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = bpt32lf_New( );
        if (pOther) {
            eRc = bpt32lf_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o p y  F r o m
    //---------------------------------------------------------------
    
    /*!
     Overlay the block data with the given data.
     @param     this    object pointer
     @param     pData   pointer to new data
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         bpt32lf_CopyFrom (
        BPT32LF_DATA   *this,
        void           *pData
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pData) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((NULL == this->pBlock) || (0 == this->blockSize)) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif
        
        memmove(this->pBlock, pData, this->blockSize);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            bpt32lf_Dealloc (
        OBJ_ID          objId
    )
    {
        BPT32LF_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BPT32LF_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        bpt32lf_setBlock(this, NULL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D e l e t e
    //---------------------------------------------------------------
    
    /*!
     Delete the entry if found.
     @param     this    object pointer
     @param     key     key of entry to be deleted
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         bpt32lf_Delete (
        BPT32LF_DATA    *this,
        uint32_t        key
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32LF_NODE    *pNode = NULL;
        uint32_t        i;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (0 == this->pBlock->used) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        
        pNode = bpt32lf_FindNode(this, key, &i);

        if (pNode) {
            // Shift the entries beyond this one left if needed.
            if (i == (this->pBlock->used - 1))
                ;
            else {
                if (this->pBlock->used > 1) {
                    memmove(
                            bpt32lf_Index2Node(this, i),
                            bpt32lf_Index2Node(this, i+1),
                            ((this->pBlock->used - i)
                             * (sizeof(BPT32LF_NODE) + this->actualSize))
                    );
                }
            }
            eRc = ERESULT_SUCCESS;
            --this->pBlock->used;
        }
        
        // Return to caller.
        return eRc;
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
    ERESULT         bpt32lf_Disable (
        BPT32LF_DATA    *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!bpt32lf_Validate(this)) {
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
    ERESULT         bpt32lf_Enable (
        BPT32LF_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!bpt32lf_Validate(this)) {
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
    //                      F i n d
    //---------------------------------------------------------------
    
    ERESULT         bpt32lf_FindKey (
        BPT32LF_DATA    *this,
        uint32_t        key,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32LF_NODE    *pNode = NULL;
        uint32_t        index;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNode = bpt32lf_FindNode(this, key, &index);
        
        if (pNode  && (pNode->key == key)) {
            if (pData) {
                memmove(pData, pNode->data, this->dataSize);
            }
            this->lastKey = key;
            this->lastIndex = index;
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F l u s h
    //---------------------------------------------------------------
    
    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         bpt32lf_Flush (
        BPT32LF_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_INVALID_REQUEST;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->index && this->pMgr)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_REQUEST;
        }
#endif
        
        if (this->pMgr && this->pReq && obj_Flag(this, BPT32LF_BLOCK_ALLOC)) {
            eRc = this->pReq(this->pMgr, this, (void *)BPT32_REQUEST_WRITE, NULL);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                           G e t
    //---------------------------------------------------------------
    
    ERESULT         bpt32lf_Get (
        BPT32LF_DATA    *this,
        uint32_t        index,          // Relative to 1
        uint32_t        *pKey,
        void            *pData
    )
    {
        BPT32LF_NODE    *pNode = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((0 == index) || !((index - 1) < this->pBlock->used)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNode = bpt32lf_Index2Node(this, (index - 1));
        if (pNode) {
            this->lastKey = pNode->key;
            this->lastIndex = index - 1;
            if (pKey)
                *pKey = pNode->key;
            if (pData) {
                memmove(pData, pNode->data, this->dataSize);
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BPT32LF_DATA *   bpt32lf_Init (
        BPT32LF_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BPT32LF_DATA);
        //ERESULT         eRc;
        
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BPT32LF);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_BPT32LF);    // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&bpt32lf_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "bpt32lf::sizeof(BPT32LF_DATA) = %lu\n", sizeof(BPT32LF_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BPT32LF_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         bpt32lf_Insert (
        BPT32LF_DATA    *this,
        uint32_t        key,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32LF_NODE    *pNode = NULL;
        uint32_t        i;
        //BPT32LF_DATA    *pNew = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        TRC_OBJ(this, "bpt32lf_Insert  index=%d  key=%d\n", this->index, key);
        TRC_OBJ(this, "\tmax: %d  used: %d\n", this->pBlock->max, this->pBlock->used);
#endif
        
        pNode = bpt32lf_FindNode(this, key, &i);
        
        if (pNode && (pNode->key == key)) {
            TRC_OBJ(this, "\tkey already exists\n");
            return eRc;
        }
        else {
            if (this->pBlock->used < this->pBlock->max) {
                TRC_OBJ(this, "\tLeaf has empty space, inserting at %d\n", i);
                if (i == this->pBlock->used)
                    ;
                else {
                    // Shift records right to make room for new node.
                    memmove(
                            bpt32lf_Index2Node(this, i+1),
                            bpt32lf_Index2Node(this, i),
                            ((this->pBlock->used - i)
                             * (sizeof(BPT32LF_NODE) + this->actualSize))
                    );
                }
                pNode = bpt32lf_Index2Node(this, i);
                if (pNode) {
                    pNode->key = key;
                    if (pData)
                        memmove(pNode->data, pData, this->pBlock->dataSize);
                    else
                        memset(pNode->data, 0, this->pBlock->dataSize);
                    ++this->pBlock->used;
                    TRC_OBJ(this, "\tKey inserted at %d, used: %d  max: %d\n",
                            i, this->pBlock->used, this->pBlock->max);
                    if (this->pMgr && this->pReq) {
                        eRc = this->pReq(this->pMgr, this, (void *)BPT32_REQUEST_WRITE, NULL);
                    }
                }
                else {
                    DEBUG_BREAK();
                    return ERESULT_GENERAL_FAILURE;
                }
                this->lastKey = key;
                this->lastIndex = i;
                eRc = ERESULT_SUCCESS;
            }
            else {
                TRC_OBJ(this, "\tLeaf is full!\n");
                eRc = bpt32lf_Split(this, key, pData, i);
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         bpt32lf_IsEnabled (
        BPT32LF_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
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
    //                          L R U
    //---------------------------------------------------------------
    
    void            bpt32lf_lruAttach (
        BPT32LF_DATA    *this,
        void            *pData,
        uint32_t        lsn
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return;
        }
#endif
        
        if (obj_Flag(this, BPT32LF_BLOCK_ALLOC)) {
            mem_Free(this->pBlock);
            obj_FlagOff(this, BPT32LF_BLOCK_ALLOC);
        }
        this->pBlock = pData;
        this->index = lsn;
        
        // Return to caller.
    }
    
    
    void            bpt32lf_lruDetach (
        BPT32LF_DATA    *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return;
        }
#endif
        
        this->pBlock = NULL;
        this->index = 0;
        
        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                          N e x t
    //---------------------------------------------------------------
    
    ERESULT         bpt32lf_NextKey (
        BPT32LF_DATA    *this,
        uint32_t        *pKey,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32LF_NODE    *pNode = NULL;
        //uint32_t        index;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNode = bpt32lf_Index2Node(this, this->lastIndex);
        
        if (pNode  && (pNode->key == this->lastKey)) {
            ++this->lastIndex;
            if (this->lastIndex < this->pBlock->used) {
                pNode = bpt32lf_Index2Node(this, this->lastIndex);
                if (pNode) {
                    this->lastKey = pNode->key;
                    if (pKey) {
                        *pKey = pNode->key;
                    }
                    if (pData) {
                        memmove(pData, pNode->data, this->dataSize);
                    }
                    eRc = ERESULT_SUCCESS;
                }
            }
            else
                return ERESULT_EOF_ERROR;
        }
        
        // Return to caller.
        return eRc;
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
        void        *pMethod = bpt32lf_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "bpt32lf", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          bpt32lf_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BPT32LF_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPT32LF_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)bpt32lf_Class();
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
                            return bpt32lf_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return bpt32lf_Enable;
                        }
                        break;

                    case 'L':
                        if (str_Compare("LRU_Attach", (char *)pStr) == 0) {
                            return bpt32lf_lruAttach;
                        }
                        if (str_Compare("LRU_Detach", (char *)pStr) == 0) {
                            return bpt32lf_lruDetach;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return bpt32lf_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return bpt32lf_ToJSON;
                        }
                        break;
                        
                    case 'V':
                        if (str_Compare("Verify", (char *)pStr) == 0) {
                            return bpt32lf_Verify;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == bpt32lf_ToDebugString)
                    return "ToDebugString";
                if (pData == bpt32lf_ToJSON)
                    return "ToJson";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e a d
    //---------------------------------------------------------------
    
    ERESULT         bpt32lf_Read (
        BPT32LF_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_INVALID_REQUEST;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->index && this->pMgr)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_REQUEST;
        }
#endif
        
        if (this->pMgr && this->pReq && obj_Flag(this, BPT32LF_BLOCK_ALLOC)) {
            eRc = this->pReq(this->pMgr, this, (void *)BPT32_REQUEST_READ, NULL);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //----------------------------------------------------------
    //                      S e t u p
    //----------------------------------------------------------
    
    ERESULT         bpt32lf_Setup(
        BPT32LF_DATA    *this,
        uint32_t        blockSize,
        uint16_t        dataSize,
        uint32_t        index,
        bool            fAllocate
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (blockSize > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (dataSize > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (dataSize > (blockSize - sizeof(BPT32LF_BLOCK))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        this->blockSize = blockSize;
        this->dataSize = dataSize;
        this->actualSize = ROUNDUP4(dataSize);
        this->maxRcds = (blockSize - sizeof(BPT32LF_BLOCK));
        this->maxRcds /=  (sizeof(BPT32LF_NODE) + this->actualSize);
        this->index = index;
        
        if (fAllocate) {
            this->pBlock = mem_Calloc(1, blockSize);
            if (NULL == this->pBlock) {
                return ERESULT_OUT_OF_MEMORY;
            }
            obj_FlagOn(this, BPT32LF_BLOCK_ALLOC);
            this->pBlock->blockType = OBJ_IDENT_BPT32LF;
            this->pBlock->dataSize = dataSize;
            this->pBlock->actualSize = ROUNDUP4(dataSize);
            this->pBlock->max = this->maxRcds;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S p l i t
    //---------------------------------------------------------------
    
    ERESULT         bpt32lf_Split (
        BPT32LF_DATA    *this,
        uint32_t        key,
        void            *pData,
        uint32_t        nodeIndex
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32LF_DATA    *pNew = OBJ_NIL;
        BPT32LF_DATA    *pNext = OBJ_NIL;
        uint32_t        half;
        uint32_t        cNew;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pBlock->used < 2) {
            DEBUG_BREAK();
            return ERESULT_DATA_TOO_SMALL;
        }
        TRC_OBJ(this, "bpt32lf_Split  index=%d  key=%d\n", this->index, key);
#endif
        if (this->pMgr && this->pReq)
            ;
        else
            return ERESULT_INVALID_REQUEST;
        
        half = (this->pBlock->used + 1) >> 1;
        cNew = this->pBlock->used - half;

        if (this->pMgr) {
            eRc = this->pReq(this->pMgr, this, (void *)BPT32_REQUEST_NEW_LEAF, &pNew);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pNew);
                return eRc;
            }
            if (OBJ_NIL == pNew) {
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
            }
            // Now pNew should have a new leaf which is already assigned an index.
        }
        
        // Copy second half of data to new object.
        memmove(
                pNew->pBlock->nodes,
                bpt32lf_Index2Node(this, half),
                (cNew * (sizeof(BPT32LF_NODE) + this->actualSize))
        );
        pNew->pBlock->used = cNew;
        this->pBlock->used = half;
        
        // Insert new node which should work because of this split.
        if (nodeIndex > half) {
            eRc = bpt32lf_Insert(pNew, key, pData);
        }
        else {
            eRc = bpt32lf_Insert(this, key, pData);
        }
        
        // Now Adjust the leaf chain pointers.
        pNew->pBlock->prev = this->index;
        pNew->pBlock->next = this->pBlock->next;
        this->pBlock->next = pNew->index;
        
        // Write the both leaves back out.
        if (this->pMgr) {
            eRc = this->pReq(this->pMgr, pNew, (void *)BPT32_REQUEST_WRITE, NULL);
            eRc = this->pReq(this->pMgr, this, (void *)BPT32_REQUEST_WRITE, NULL);
        }
        
        // Adjust the chained block after the new block to point back to it
        // or the data tail index.
        if (this->pMgr) {
            if (pNew->pBlock->next) {
                pNext = bpt32lf_New();
                if (pNext) {
                    bpt32lf_setIndex(pNext, pNew->pBlock->next);
                    eRc = this->pReq(this->pMgr, pNext, (void *)BPT32_REQUEST_READ, NULL);
                    if (!ERESULT_FAILED(eRc)) {
                        pNext->pBlock->prev = pNew->index;
                        eRc = this->pReq(this->pMgr, pNext, (void *)BPT32_REQUEST_WRITE, NULL);
                    }
                    obj_Release(pNext);
                }
            }
            else {
                eRc = this->pReq(this->pMgr, pNew, (void *)BPT32_REQUEST_TAIL, NULL);
            }
        }

        // Notify manager that a split occurred.
        if (this->pMgr) {
            eRc =   this->pReq(
                             this->pMgr,
                             this,                      // Lefthand Block
                             (void *)BPT32_REQUEST_SPLIT,
                             pNew                       // Righthand Block
                    );
        }
        
        // Return to caller.
        obj_Release(pNew);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     bpt32lf_ToJSON (
        BPT32LF_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{\"objectType\":\"%s\"",
                        pInfo->pClassName
                    );
            
            AStr_AppendA(pStr, "}\n");
        }
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = bpt32lf_ToDebugString(this,4);
     @endcode 
     @param     this    BPT32LF object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     bpt32lf_ToDebugString (
        BPT32LF_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        int             i;
        BPT32LF_NODE    *pNode = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
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
        if (this->pBlock) {
            eRc = AStr_AppendPrint(
                                   pStr,
                                   "{%p(%s) dataSize=%d actualSize=%d nodeSize=%d\n",
                                   this,
                                   pInfo->pClassName,
                                   this->pBlock->dataSize,
                                   this->pBlock->actualSize,
                                   (this->pBlock->actualSize + sizeof(BPT32LF_NODE))
                                   );
        }
        else {
            eRc = AStr_AppendPrint(
                                   pStr,
                                   "{%p(%s) dataSize=%d actualSize=%d nodeSize=%d\n",
                                   this,
                                   pInfo->pClassName,
                                   this->dataSize,
                                   this->actualSize,
                                   (this->actualSize + sizeof(BPT32LF_NODE))
                                   );
        }
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        if (this->pBlock) {
            eRc = AStr_AppendPrint(
                                   pStr,
                                   "\tblockSize=%d  max=%d  used=%d  index=%d  "
                                   "prev=%d next=%d\n",
                                   this->blockSize,
                                   this->pBlock->max,
                                   this->pBlock->used,
                                   this->index,
                                   this->pBlock->prev,
                                   this->pBlock->next
                                   );
        }
        else {
            eRc = AStr_AppendPrint(
                                   pStr,
                                   "\tblockSize=%d  max=%d  index=%d\n",
                                   this->blockSize,
                                   this->maxRcds,
                                   this->index
                                   );
        }

        if (this->pBlock) {
            for (i=0; i<this->pBlock->used; ++i) {
                pNode = bpt32lf_Index2Node(this, i);
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent+3, ' ');
                }
                eRc = AStr_AppendPrint(
                                       pStr,
                                       "\tkey=%d\n",
                                       pNode->key
                        );
            }
        }
        
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
    //                          U p d a t e
    //---------------------------------------------------------------
    
    ERESULT         bpt32lf_Update (
        BPT32LF_DATA    *this,
        uint32_t        key,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32LF_NODE    *pNode = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNode = bpt32lf_FindNode(this, key, NULL);

        if (pNode) {
            memmove(pNode->data, pData, this->dataSize);
            eRc = ERESULT_SUCCESS;
        }
        else
            eRc = ERESULT_DATA_NOT_FOUND;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            bpt32lf_Validate (
        BPT32LF_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BPT32LF))
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


        if (!(obj_getSize(this) >= sizeof(BPT32LF_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                       V e r i f y
    //---------------------------------------------------------------
    
    /*!
     Verify as much of this object as we can.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         bpt32lf_Verify (
        BPT32LF_DATA    *this
    )
    {
        //ERESULT         eRc;
        uint32_t        key = 0;
        uint32_t        i;
        uint32_t        iMax;
        BPT32LF_NODE    *pNode = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32lf_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (this->pBlock->used <= this->pBlock->max)
            ;
        else
            return ERESULT_GENERAL_FAILURE;
        
        iMax = this->pBlock->used;
        for (i=0; i<iMax; ++i) {
            pNode = bpt32lf_Index2Node(this, i);
            if (key < pNode->key)
                ;
            else
                return ERESULT_GENERAL_FAILURE;
            key = pNode->key;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    

    
#ifdef	__cplusplus
}
#endif


