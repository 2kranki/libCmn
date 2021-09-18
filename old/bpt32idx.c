// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   bpt32idx.c
 *	Generated 01/12/2019 14:04:35
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
#include        <bpt32idx_internal.h>
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
    BPT32IDX_NODE * bpt32idx_FindNode (
        BPT32IDX_DATA   *this,
        uint32_t        key,
        uint32_t        *pIndex
    )
    {
        //ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32IDX_NODE   *pNode = NULL;
        uint32_t        i = 0;
        uint32_t        High = 0;
        uint32_t        Low = 0;
        uint32_t        Mid;
        int             rc;
        
        // Do initialization.
        if (0 == this->pBlock->used) {
            if (pIndex)
                *pIndex = 0;
            return NULL;
        }
        pNode = &this->pBlock->nodes[0];
        if (key < pNode->key) {
            if (pIndex)
                *pIndex = 0;
            return NULL;
        }

        if (this->pBlock->used < 10) {
            // Do a sequential search.
            for (i=0; i<this->pBlock->used; ++i) {
                pNode = &this->pBlock->nodes[i];
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
                pNode = &this->pBlock->nodes[i];
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
                i = Low;
                pNode = &this->pBlock->nodes[i];
                rc = key - pNode->key;
            }
        }
        
        // Return to caller.
        if (pIndex)
            *pIndex = i;
        return pNode;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BPT32IDX_DATA * bpt32idx_Alloc (
        void
    )
    {
        BPT32IDX_DATA       *this;
        uint32_t        cbSize = sizeof(BPT32IDX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BPT32IDX_DATA * bpt32idx_New (
        void
    )
    {
        BPT32IDX_DATA       *this;
        
        this = bpt32idx_Alloc( );
        if (this) {
            this = bpt32idx_Init(this);
        } 
        return this;
    }


    BPT32IDX_DATA * bpt32idx_NewWithSizes (
        uint32_t        blockSize,
        uint32_t        dataSize,
        uint32_t        index,                  // Block Index Number
        bool            fAllocate,              // true == allocate a buffer
        OBJ_ID          pMgr
    )
    {
        BPT32IDX_DATA   *this;
        ERESULT         eRc;
        
        this = bpt32idx_New( );
        if (this) {
            eRc = bpt32idx_Setup(this, blockSize, dataSize, index, fAllocate);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                return OBJ_NIL;
            }
            if (pMgr) {
                bpt32idx_setManager(this, pMgr);
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
    
    uint8_t *       bpt32idx_getBlock (
        BPT32IDX_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        
        return (uint8_t *)this->pBlock;
    }
    
    
    bool            bpt32idx_setBlock (
        BPT32IDX_DATA   *this,
        uint8_t         *pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (obj_Flag(this, BPT32IDX_BLOCK_ALLOC) && this->pBlock) {
            mem_Free(this->pBlock);
            this->pBlock = NULL;
            obj_FlagOff(this, BPT32IDX_BLOCK_ALLOC);
        }
        
        return (uint8_t *)this->pBlock;
    }

    
    
    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    uint32_t        bpt32idx_getIndex (
        BPT32IDX_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->index;
    }
    
    
    bool            bpt32idx_setIndex (
        BPT32IDX_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->index = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      M a n a g e r
    //---------------------------------------------------------------
    
    bool            bpt32idx_setManager(
        BPT32IDX_DATA    *this,
        OBJ_ID           *pMgr          // Block Manager
    )
    {
        OBJ_IUNKNOWN    *pVtbl;

#ifdef NDEBUG
#else
        if( !bpt32idx_Validate(this) ) {
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
    //                         P 0
    //---------------------------------------------------------------
    
    uint32_t        bpt32idx_getP0 (
        BPT32IDX_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->pBlock->p0;
    }
    
    
    bool            bpt32idx_setP0 (
        BPT32IDX_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pBlock->p0 = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        bpt32idx_getPriority (
        BPT32IDX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            bpt32idx_setPriority (
        BPT32IDX_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
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
    
    uint32_t        bpt32idx_getSize (
        BPT32IDX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  bpt32idx_getSuperVtbl (
        BPT32IDX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
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
        ERESULT eRc = bpt32idx_Assign(this,pOther);
     @endcode 
     @param     this    BPT32IDX object pointer
     @param     pOther  a pointer to another BPT32IDX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         bpt32idx_Assign (
        BPT32IDX_DATA		*this,
        BPT32IDX_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!bpt32idx_Validate(pOther)) {
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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             bpt32idx_Compare (
        BPT32IDX_DATA   *this,
        BPT32IDX_DATA   *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!bpt32idx_Validate(pOther)) {
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
        bpt32idx      *pCopy = bpt32idx_Copy(this);
     @endcode 
     @param     this    BPT32IDX object pointer
     @return    If successful, a BPT32IDX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT32IDX_DATA *     bpt32idx_Copy (
        BPT32IDX_DATA       *this
    )
    {
        BPT32IDX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = bpt32idx_New( );
        if (pOther) {
            eRc = bpt32idx_Assign(this, pOther);
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
    ERESULT         bpt32idx_CopyFrom (
        BPT32IDX_DATA   *this,
        void            *pData
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
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

    void            bpt32idx_Dealloc (
        OBJ_ID          objId
    )
    {
        BPT32IDX_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BPT32IDX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        bpt32idx_setBlock(this, NULL);

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
    ERESULT         bpt32idx_Delete (
        BPT32IDX_DATA    *this,
        uint32_t        key
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32IDX_NODE   *pNode = NULL;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (0 == this->pBlock->used) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        
        pNode = bpt32idx_FindNode(this, key, &i);
        
        if (pNode && (pNode->key == key)) {
            // Shift the entries beyond this one left if needed.
            if (i == (this->pBlock->used - 1))
                ;
            else {
                if (this->pBlock->used > 1) {
                    memmove(
                            &this->pBlock->nodes[i],
                            &this->pBlock->nodes[i+1],
                            ((this->pBlock->used - i) * sizeof(BPT32IDX_NODE))
                    );
                }
            }
            eRc = ERESULT_SUCCESS;
            --this->pBlock->used;
#ifdef MAYBE_FIX_ME
            if ((0 == this->pBlock->used) && this->pBlockEmpty) {
                // Inserting data in 0th position (ie block key)
                eRc = this->pBlockIndexChanged(this->pBlockObject, this);
            }
            else {
                if ((0 == i) && this->pBlockIndexChanged) {
                    // Inserting data in 0th position (ie block key)
                    eRc = this->pBlockIndexChanged(this->pBlockObject, this);
                }
            }
#endif
        }
        else
            eRc = ERESULT_DATA_NOT_FOUND;
        
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
    ERESULT         bpt32idx_Disable (
        BPT32IDX_DATA	*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!bpt32idx_Validate(this)) {
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
    ERESULT         bpt32idx_Enable (
        BPT32IDX_DATA	*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!bpt32idx_Validate(this)) {
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
    //                          F i n d
    //---------------------------------------------------------------
    
    ERESULT         bpt32idx_FindIndex (
        BPT32IDX_DATA   *this,
        uint32_t        index,
        uint32_t        *pKey
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32IDX_NODE   *pNode = NULL;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=0; i<this->pBlock->used; ++i) {
            pNode = &this->pBlock->nodes[i];
            if (index == pNode->index) {
                break;
            }
            pNode = NULL;
        }
        
        if (pNode) {
            if (pKey) {
                *pKey = pNode->key;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         bpt32idx_FindKey (
        BPT32IDX_DATA   *this,
        uint32_t        key,
        uint32_t        *pData
    )
    {
        //ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        //BPT32IDX_NODE   *pNode = NULL;
        //uint32_t        index = 0;
        uint32_t        iMax;
        uint32_t        i;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (key < this->pBlock->nodes[0].key) {
            if (pData) {
                *pData = this->pBlock->p0;
            }
            return ERESULT_SUCCESS;
        }
        
        iMax = this->pBlock->used;
        for (i=0; (i<iMax - 1); ++i) {
            if ((key >= this->pBlock->nodes[i].key)
                && (key < this->pBlock->nodes[i+1].key)) {
                if (pData) {
                    *pData = this->pBlock->nodes[i].index;
                }
                return ERESULT_SUCCESS;
            }
        }
        
        // Return to caller.
        if (pData) {
            *pData = this->pBlock->nodes[this->pBlock->used-1].index;
        }
        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //                          F l u s h
    //---------------------------------------------------------------
    
    ERESULT         bpt32idx_Flush (
        BPT32IDX_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_INVALID_REQUEST;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#ifdef MAYBE_FIX_ME
        if (this->rcdNum && this->pBlockFlush)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_REQUEST;
        }
#endif
#endif
        
#ifdef MAYBE_FIX_ME
        if (this->pBlockFlush) {
            eRc =   this->pBlockFlush(this->pBlockObject, this);
        }
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                           G e t
    //---------------------------------------------------------------
    
    ERESULT         bpt32idx_Get (
        BPT32IDX_DATA    *this,
        uint32_t        index,          // Relative to 1
        uint32_t        *pKey,
        uint32_t        *pData
    )
    {
        BPT32IDX_NODE   *pNode = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((0 == index) || !((index - 1) < this->pBlock->used)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNode = &this->pBlock->nodes[index - 1];
        if (pNode) {
            *pKey = pNode->key;
            if (pData) {
                *pData = pNode->index;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BPT32IDX_DATA *   bpt32idx_Init (
        BPT32IDX_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BPT32IDX_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BPT32IDX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_BPT32IDX);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&bpt32idx_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = ObjArray_New( );

    #ifdef NDEBUG
    #else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "bpt32idx::sizeof(BPT32IDX_DATA) = %lu\n", sizeof(BPT32IDX_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BPT32IDX_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         bpt32idx_Insert (
        BPT32IDX_DATA   *this,
        uint32_t        key,
        uint32_t        *pData,
        BPT32IDX_DATA   **ppNew
    )
    {
        ERESULT         eRc = ERESULT_DATA_ALREADY_EXISTS;
        BPT32IDX_NODE   *pNode = NULL;
        uint32_t        i;
        BPT32IDX_DATA   *pNew = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNode = bpt32idx_FindNode(this, key, &i);
        
        if (pNode && (pNode->key == key)) {
            return eRc;
        }
        else {
            if (this->pBlock->used < this->pBlock->max) {
                if (i == this->pBlock->used)
                    ;
                else {
                    // Shift records right to make room for new node.
                    memmove(
                            &this->pBlock->nodes[i+1],
                            &this->pBlock->nodes[i],
                            ((this->pBlock->used - i) * sizeof(BPT32IDX_NODE))
                            );
                }
                pNode = &this->pBlock->nodes[i];
                if (pNode) {
                    pNode->key = key;
                    pNode->index = *pData;
                    ++this->pBlock->used;
                    eRc = this->pReq(this->pMgr, this, (void *)BPT32_REQUEST_WRITE, NULL);
                }
                else {
                    DEBUG_BREAK();
                    return ERESULT_GENERAL_FAILURE;
                }
                eRc = ERESULT_SUCCESS;
            }
            else {
                eRc = bpt32idx_Split(this, key, *pData, i, &pNew);
            }
        }
        
        // Return to caller.
        if (ppNew)
            *ppNew = pNew;
        else
            obj_Release(pNew);
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         bpt32idx_IsEnabled (
        BPT32IDX_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
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
    
    void            bpt32idx_lruAttach (
        BPT32IDX_DATA   *this,
        void            *pData,
        uint32_t        lsn
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return;
        }
#endif
        
        if (obj_Flag(this, BPT32IDX_BLOCK_ALLOC)) {
            mem_Free(this->pBlock);
            obj_FlagOff(this, BPT32IDX_BLOCK_ALLOC);
        }
        this->pBlock = pData;
        this->index = lsn;
        
        // Return to caller.
    }
    
    
    void            bpt32idx_lruDetach (
        BPT32IDX_DATA   *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = bpt32idx_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "bpt32idx", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          bpt32idx_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BPT32IDX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPT32IDX_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)bpt32idx_Class();
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
                            return bpt32idx_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return bpt32idx_Enable;
                        }
                        break;

                    case 'L':
                        if (str_Compare("LRU_Attach", (char *)pStr) == 0) {
                            return bpt32idx_lruAttach;
                        }
                        if (str_Compare("LRU_Detach", (char *)pStr) == 0) {
                            return bpt32idx_lruDetach;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return bpt32idx_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return bpt32idx_ToJSON;
                        }
                        break;
                        
                    case 'V':
                        if (str_Compare("Verify", (char *)pStr) == 0) {
                            return bpt32idx_Verify;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == bpt32idx_ToDebugString)
                    return "ToDebugString";
                if (pData == bpt32idx_ToJSON)
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
    
    ERESULT         bpt32idx_Read (
        BPT32IDX_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_INVALID_REQUEST;
        OBJ_IUNKNOWN    *pVtbl;
        ERESULT         (*pRead)(OBJ_ID, OBJ_ID, uint32_t, void *);
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
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
        
        if (this->pMgr && obj_Flag(this, BPT32IDX_BLOCK_ALLOC)) {
            pVtbl = obj_getVtbl(this->pMgr);
            pRead = pVtbl->pQueryInfo(
                                      this->pMgr,
                                      OBJ_QUERYINFO_TYPE_METHOD,
                                      "IndexBlockRequest"
                    );
            if (pRead) {
                eRc = pRead(this->pMgr, this, BPT32_REQUEST_READ, NULL);
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //----------------------------------------------------------
    //                      S e t u p
    //----------------------------------------------------------
    
    ERESULT         bpt32idx_Setup(
        BPT32IDX_DATA   *this,
        uint32_t        blockSize,
        uint32_t        dataSize,
        uint32_t        index,
        bool            fAllocate
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (blockSize > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (sizeof(uint32_t) > (blockSize - sizeof(BPT32IDX_BLOCK))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        this->blockSize = blockSize;
        this->dataSize = sizeof(uint32_t);
        this->maxRcds = (blockSize - sizeof(BPT32IDX_BLOCK));
        this->maxRcds /=  sizeof(BPT32IDX_NODE);
        this->index = index;
        
        if (fAllocate) {
            this->pBlock = mem_Calloc(1, blockSize);
            if (NULL == this->pBlock) {
                return ERESULT_OUT_OF_MEMORY;
            }
            obj_FlagOn(this, BPT32IDX_BLOCK_ALLOC);
            this->pBlock->blockType = OBJ_IDENT_BPT32IDX;
            this->pBlock->actualSize = ROUNDUP4(this->dataSize);
            this->pBlock->max = this->maxRcds;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S p l i t
    //---------------------------------------------------------------
    
    ERESULT         bpt32idx_Split (
        BPT32IDX_DATA   *this,
        uint32_t        key,
        uint32_t        data,
        uint32_t        nodeIndex,
        BPT32IDX_DATA   **ppNew
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32IDX_DATA   *pNew = OBJ_NIL;
        uint32_t        half;
        uint32_t        cNew;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        half = (this->pBlock->used + 1) >> 1;
        cNew = this->pBlock->used - half;
        
        if (this->pMgr) {
            eRc = this->pReq(
                             this->pMgr,
                             this,
                             (void *)BPT32_REQUEST_NEW_INDEX,
                             &pNew
                    );
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pNew);
                return eRc;
            }
            if (OBJ_NIL == pNew) {
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
            }
            // Now pNew should have a new index block which is already assigned an index.
        }
        
        // Copy second half of data to new object.
        memmove(
                &pNew->pBlock->nodes[0],
                &this->pBlock->nodes[half],
                (cNew * sizeof(BPT32IDX_NODE))
        );
        pNew->pBlock->used = cNew;
        this->pBlock->used = half;
        
        // Insert new node which should work because of the split.
        if (nodeIndex > half) {
            eRc = bpt32idx_Insert(pNew, key, &data, NULL);
        }
        else {
            eRc = bpt32idx_Insert(this, key, &data, NULL);
        }

        if (this->pMgr) {
            eRc = this->pReq(this->pMgr, this, (void *)BPT32_REQUEST_WRITE, NULL);
            eRc = this->pReq(this->pMgr, pNew, (void *)BPT32_REQUEST_WRITE, NULL);
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
        if (ppNew) {
            *ppNew = pNew;
        }
        else
            obj_Release(pNew);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     bpt32idx_ToJSON (
        BPT32IDX_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
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
        ASTR_DATA      *pDesc = bpt32idx_ToDebugString(this,4);
     @endcode 
     @param     this    BPT32IDX object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     bpt32idx_ToDebugString (
        BPT32IDX_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        int             i;
        BPT32IDX_NODE   *pNode = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
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
                               "{%p(%s) dataSize=%d nodeSize=%d\n",
                               this,
                               pInfo->pClassName,
                               this->dataSize,
                               sizeof(BPT32IDX_NODE)
                );
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                               pStr,
                               "\tblockSize=%d  maxRcds=%d  used=%d  index=%d\n",
                               this->blockSize,
                               this->pBlock->max,
                               this->pBlock->used,
                               this->index
                               );

        if (this->pBlock) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            eRc = AStr_AppendPrint(
                                   pStr,
                                   "\tp0=%d\n",
                                   this->pBlock->p0
                    );
            for (i=0; i<this->pBlock->used; ++i) {
                pNode = &this->pBlock->nodes[i];
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent+3, ' ');
                }
                eRc = AStr_AppendPrint(
                                       pStr,
                                       "\tkey=%d data=%d\n",
                                       pNode->key,
                                       pNode->index
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
    
    ERESULT         bpt32idx_Update (
        BPT32IDX_DATA   *this,
        uint32_t        key,
        uint32_t        data
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32IDX_NODE   *pNode = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNode = bpt32idx_FindNode(this, key, NULL);
        
        if (pNode && (pNode->key == key)) {
            pNode->index = data;
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
    bool            bpt32idx_Validate (
        BPT32IDX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BPT32IDX))
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


        if (!(obj_getSize(this) >= sizeof(BPT32IDX_DATA))) {
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
    ERESULT         bpt32idx_Verify (
        BPT32IDX_DATA   *this
    )
    {
        //ERESULT         eRc;
        uint32_t        key = 0;
        uint32_t        i;
        uint32_t        iMax;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32idx_Validate(this)) {
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
            if (key < this->pBlock->nodes[i].key)
                ;
            else
                return ERESULT_GENERAL_FAILURE;
            key = this->pBlock->nodes[i].key;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    

    
#ifdef	__cplusplus
}
#endif


