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
        
        if (this->pBlock->used < 4) {
            // Do a sequential search.
            for (i=0; i<this->pBlock->used; ++i) {
                pNode = &this->pBlock->nodes[i];
                if (key == pNode->key) {
                    break;
                }
                if (key < pNode->key) {
                    pNode = NULL;
                    break;
                }
                pNode = NULL;
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
                pNode = NULL;
            }
            if( High == Low ) {
                i = Low;
                pNode = &this->pBlock->nodes[i];
                rc = key - pNode->key;
                if(rc == 0)
                    ;
                else
                    pNode = NULL;
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

    BPT32IDX_DATA *     bpt32idx_Alloc (
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



    BPT32IDX_DATA *     bpt32idx_New (
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
    
    
    
    //---------------------------------------------------------------
    //                    B l o c k  E x i t s
    //---------------------------------------------------------------
    
    bool            bpt32idx_setBlockExits(
        BPT32IDX_DATA    *this,
        ERESULT         (*pBlockEmpty)(
                            OBJ_ID          pBlockObject,
                            BPT32IDX_DATA    *pValue
                        ),
        ERESULT         (*pBlockFlush)(
                            OBJ_ID          pBlockObject,
                            BPT32IDX_DATA    *pValue
                        ),
        ERESULT         (*pBlockIndexChanged)(
                            OBJ_ID          pBlockObject,
                            BPT32IDX_DATA    *pValue
                        ),
        ERESULT         (*pBlockSplit)(
                            OBJ_ID          pBlockObject,
                            BPT32IDX_DATA   *pOld,
                            BPT32IDX_DATA   *pNew
                        ),
        OBJ_ID          pBlockObject
    )
    {
#ifdef NDEBUG
#else
        if( !bpt32idx_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pBlockEmpty = pBlockEmpty;
        this->pBlockFlush = pBlockFlush;
        this->pBlockIndexChanged = pBlockIndexChanged;
        this->pBlockSplit = pBlockSplit;
        this->pBlockObject = pBlockObject;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N e x t
    //---------------------------------------------------------------
    
    uint32_t        bpt32idx_getNext (
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
        
        return this->pBlock->next;
    }
    
    
    bool            bpt32idx_setNext (
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
        
        this->pBlock->next = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P a r e n t
    //---------------------------------------------------------------
    
    uint32_t        bpt32idx_getParent (
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
        
        return this->pBlock->parent;
    }
    
    
    bool            bpt32idx_setParent (
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
        
        this->pBlock->parent = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r e v
    //---------------------------------------------------------------
    
    uint32_t        bpt32idx_getPrev (
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
        
        return this->pBlock->prev;
    }
    
    
    bool            bpt32idx_setPrev (
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
        
        this->pBlock->prev = value;
        
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
    //               R e c o r d  N u m b e r
    //---------------------------------------------------------------
    
    uint32_t        bpt32idx_getRecordNumber (
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
        
        return this->rcdNum;
    }
    
    
    bool            bpt32idx_setRecordNumber (
        BPT32IDX_DATA    *this,
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
        
        this->rcdNum = value;
        
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
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         bpt32idx_Compare (
        BPT32IDX_DATA     *this,
        BPT32IDX_DATA     *pOther
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
        if (!bpt32idx_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!bpt32idx_Validate(pOther)) {
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

        if (this->pBlock) {
            mem_Free(this->pBlock);
            this->pBlock = NULL;
        }

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
        
        if (pNode) {
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
    ERESULT         bpt32idx_Disable (
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
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------
    
    ERESULT         bpt32idx_Find (
        BPT32IDX_DATA   *this,
        uint32_t        key,
        uint32_t        *pData
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
        
        if (pNode) {
            if (pData) {
                *pData = pNode->index;
            }
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
        if (this->rcdNum && this->pBlockFlush)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_REQUEST;
        }
#endif
        
        if (this->pBlockFlush) {
            eRc =   this->pBlockFlush(this->pBlockObject, this);
        }
        
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
        //this->pArray = objArray_New( );

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
        uint32_t        data
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
        
        pNode = bpt32idx_FindNode(this, key, &i);
        
        if (pNode) {
            return eRc;
        }
        else {
            for (; i<this->pBlock->used; ++i) {
                pNode = &this->pBlock->nodes[i];
                if (key < pNode->key) {
                    pNode = NULL;
                    break;
                }
                pNode = NULL;
            }
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
                pNode->index = data;
                ++this->pBlock->used;
            }
            else {
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
            }
            eRc = ERESULT_SUCCESS;
            if ((0 == i) && this->pBlockIndexChanged) {
                // Inserting data in 0th position (ie block key)
                eRc = this->pBlockIndexChanged(this->pBlockObject, this);
            }
        }
        
        // Return to caller.
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

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return bpt32idx_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return bpt32idx_ToJSON;
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
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //----------------------------------------------------------
    //                      S e t u p
    //----------------------------------------------------------
    
    ERESULT         bpt32idx_SetupSizes(
        BPT32IDX_DATA   *this,
        uint32_t        blockSize,
        uint16_t        dataSize
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
        if (dataSize > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (dataSize > (blockSize - sizeof(BPT32IDX_BLOCK))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        this->blockSize = blockSize;
        this->dataSize = dataSize;
        this->maxRcds = (blockSize - sizeof(BPT32IDX_BLOCK));
        this->maxRcds /=  sizeof(BPT32IDX_NODE);
        
        this->pBlock = mem_Calloc(1, blockSize);
        if (NULL == this->pBlock) {
            return ERESULT_OUT_OF_MEMORY;
        }
        this->pBlock->blkType = OBJ_IDENT_BPT32IDX;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S p l i t
    //---------------------------------------------------------------
    
    ERESULT         bpt32idx_Split (
        BPT32IDX_DATA   *this,
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
        if (this->pBlock->used < 2) {
            DEBUG_BREAK();
            return ERESULT_DATA_TOO_SMALL;
        }
#endif
        
        half = this->pBlock->used >> 1;
        cNew = this->pBlock->used - half;
        
        pNew = bpt32idx_New( );
        if (OBJ_NIL == pNew) {
            return ERESULT_OUT_OF_MEMORY;
        }
        eRc = bpt32idx_SetupSizes(pNew, this->blockSize, this->dataSize);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pNew);
            return eRc;
        }
        
        // Copy second half of data to new object.
        memmove(
                &pNew->pBlock->nodes[0],
                &this->pBlock->nodes[half],
                (cNew * sizeof(BPT32IDX_NODE))
        );
        pNew->pBlock->used = cNew;
        this->pBlock->used = half;
        
        if (this->pBlockSplit) {
            eRc = this->pBlockSplit(this->pBlockObject, this, pNew);
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
                               "\tblockSize=%d maxRcds=%d rcdNum=%d\n",
                               this->blockSize,
                               this->maxRcds,
                               this->rcdNum
                               );

        if (this->pBlock) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            eRc = AStr_AppendPrint(
                                   pStr,
                                   "\tprev=%d next=%d parent=%d\n",
                                   this->pBlock->prev,
                                   this->pBlock->next,
                                   this->pBlock->parent
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
        
        if (pNode) {
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


    
    
    
#ifdef	__cplusplus
}
#endif


