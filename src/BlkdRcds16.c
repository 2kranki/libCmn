// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   BlkdRcds16.c
 *  Generated 09/18/2021 09:48:13
 *
 */

/*
 The record grows from the bottom up.  The index grows from the top
 down. The unused space is the space in-between. To get the valid
 offset to the next data record, we must add back in the size of
 block header and the index.  The reserved area is beyond the index
 and data areas. So, it does not affect these calculations.

            +--------------------------+
            |      Block Header        |
            +--------------------------+
            |          Index           |
            | (Grows down toward Data) |
            +--------------------------+
            |      Unused Space        |
            +--------------------------+
            |      Data Records        |
            | (Grows up toward Index)  |
            +--------------------------+
            |      Reserved Data       |
            +--------------------------+
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
#include        <BlkdRcds16_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.


 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    void            BlkdRcds16_BlockFree (
        BLKDRCDS16_DATA *this
    )
    {
        if ( this->fAlloc && this->pBlock) {
            mem_Free(this->pBlock);
            this->pBlock = NULL;
            this->fAlloc = 0;
        }
    }


    //---------------------------------------------------------------
    //                      D a t a  S h i f t
    //---------------------------------------------------------------

    ERESULT         BlkdRcds16_DataShift (
        BLKDRCDS16_DATA *this,
        uint32_t        index,
        uint32_t        amt
    )
    {
        uint16_t        dataOffset;
        uint16_t        dataSize;
        uint16_t        numShiftRcds;
        uint16_t        shiftSize;
        uint8_t         *start;
        uint8_t         *shiftTo;
        int             i;

        // Do initialization.

        dataOffset = this->pBlock->index[index - 1].idxOffset;
        dataSize = this->pBlock->index[index - 1].idxSize;
        numShiftRcds = this->pBlock->numRecords - index;

        if( numShiftRcds ) {
            // Shift the data.
            shiftSize = 0;
            for( i=0; i<numShiftRcds; i++ ) {
                shiftSize += this->pBlock->index[index+i].idxSize;
            }
            if( shiftSize ) {
                start = (uint8_t *)this->pBlock
                        + this->pBlock->index[this->pBlock->numRecords - 1].idxOffset;
                shiftTo = start + dataSize;
                memmove(shiftTo, start, shiftSize);
            }
            // Shift the index.
            shiftSize = sizeof(INDEX_RECORD) * numShiftRcds;
            if( shiftSize ) {
                start = (uint8_t *)&this->pBlock->index[index];
                shiftTo = (uint8_t *)&this->pBlock->index[index-1];
                memmove( shiftTo, start, shiftSize );
                // Adjust the index for new offsets.
                for( i=0; i<numShiftRcds; i++ ) {
                    this->pBlock->index[index-1+i].idxOffset += dataSize;
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    void *          BlkdRcds16_RecordPoint (
        BLKDRCDS16_DATA *this,
        uint32_t        index,
        uint16_t        *pReturnedSize
    )
    {
        INDEX_RECORD    *pIndex;
        uint16_t        size;
        uint8_t         *pBlockData;

        if (index >= this->pBlock->numRecords)
            return NULL;

        pIndex = (INDEX_RECORD *)(&this->pBlock->index[index - 1]);
        size = pIndex->idxSize;
        pBlockData = (((uint8_t *)this->pBlock) + pIndex->idxOffset);

        // Return to caller.
        if (pReturnedSize) {
            *pReturnedSize = size;
        }
        return pBlockData;
    }




    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BLKDRCDS16_DATA *     BlkdRcds16_Alloc (
        void
    )
    {
        BLKDRCDS16_DATA       *this;
        uint32_t        cbSize = sizeof(BLKDRCDS16_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    uint16_t        BlkdRcds16_CalcFromRecordSize(
        uint16_t        rsvdSize,
        uint16_t        numRecords,
        uint16_t        recordSize              // Average Record Size
    )
    {
        uint32_t        cbSize;
        uint32_t        dataSize;

        // Do initialization.
        dataSize  = recordSize + sizeof(INDEX_RECORD);
        dataSize *= numRecords;
        if (dataSize && (dataSize < DATA_BLOCK_MAX_SIZE))
            ;
        else {
            return 0;
        }

        cbSize  = sizeof(DATA_BLOCK);
        cbSize += rsvdSize;
        cbSize += dataSize;

        if (cbSize > DATA_BLOCK_MAX_SIZE) {
            cbSize = 0;                 // TOO Big!
        }

        // Return to caller.
        return cbSize;
    }



    uint16_t        BlkdRcds16_CalcUseableSizeFromBlockSize(
        uint16_t        blockSize,
        uint16_t        rsvdSize
    )
    {
        uint32_t        cbSize;

        // Do initialization.
        cbSize = sizeof(DATA_BLOCK) + rsvdSize;
        if (cbSize > DATA_BLOCK_MAX_SIZE) {
            return 0;
        }
        if (blockSize < cbSize) {
            return 0;
        }

        cbSize  = blockSize;
        cbSize -= sizeof(DATA_BLOCK);
        cbSize -= rsvdSize;

        // Return to caller.
        return cbSize;
    }



    BLKDRCDS16_DATA *     BlkdRcds16_New (
        void
    )
    {
        BLKDRCDS16_DATA       *this;
        
        this = BlkdRcds16_Alloc( );
        if (this) {
            this = BlkdRcds16_Init(this);
        } 
        return this;
    }


    BLKDRCDS16_DATA * BlkdRcds16_NewWithBlockSize (
        uint16_t        blockSize,
        uint16_t        rsvdSize
    )
    {
        BLKDRCDS16_DATA *this;
        ERESULT         eRc;

        this = BlkdRcds16_New( );
        if (this) {
            eRc = BlkdRcds16_SetupWithBlockSize(this, blockSize, rsvdSize, NULL);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        return this;
    }


    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                       D a t a
    //---------------------------------------------------------------

    uint8_t *       BlkdRcds16_getData(
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        return (uint8_t *)this->pBlock;
    }


    bool            BlkdRcds16_setData(
        BLKDRCDS16_DATA *this,
        uint8_t         *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pBlock = (DATA_BLOCK *)pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                N u m b e r  o f  R e c o r d s
    //---------------------------------------------------------------

    uint16_t        BlkdRcds16_getNumRecords(
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if (this->pBlock) {
        }
        else {
            return 0;
        }
#endif

        return this->pBlock->numRecords;
    }


     //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        BlkdRcds16_getPriority (
        BLKDRCDS16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            BlkdRcds16_setPriority (
        BLKDRCDS16_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
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
    
    uint32_t        BlkdRcds16_getSize (
        BLKDRCDS16_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * BlkdRcds16_getStr (
        BLKDRCDS16_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        BlkdRcds16_setStr (
        BLKDRCDS16_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  BlkdRcds16_getSuperVtbl (
        BLKDRCDS16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                         U n u s e d
    //---------------------------------------------------------------

    uint16_t        BlkdRcds16_getUnused(
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if (this->pBlock) {
        }
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->pBlock->unusedSize;
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
        ERESULT eRc = BlkdRcds16_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another BLKDRCDS16 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         BlkdRcds16_Assign (
        BLKDRCDS16_DATA       *this,
        BLKDRCDS16_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BlkdRcds16_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

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
        //pOther->x     = this->x; 

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
    int             BlkdRcds16_Compare (
        BLKDRCDS16_DATA     *this,
        BLKDRCDS16_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!BlkdRcds16_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        BlkdRcds16      *pCopy = BlkdRcds16_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BLKDRCDS16 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BLKDRCDS16_DATA *     BlkdRcds16_Copy (
        BLKDRCDS16_DATA       *this
    )
    {
        BLKDRCDS16_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef BLKDRCDS16_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = BlkdRcds16_New( );
        if (pOther) {
            eRc = BlkdRcds16_Assign(this, pOther);
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

    void            BlkdRcds16_Dealloc (
        OBJ_ID          objId
    )
    {
        BLKDRCDS16_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BLKDRCDS16_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        BlkdRcds16_setStr(this, OBJ_NIL);
        BlkdRcds16_BlockFree(this);

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
        BlkdRcds16      *pDeepCopy = BlkdRcds16_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BLKDRCDS16 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BLKDRCDS16_DATA *     BlkdRcds16_DeepCopy (
        BLKDRCDS16_DATA       *this
    )
    {
        BLKDRCDS16_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = BlkdRcds16_New( );
        if (pOther) {
            eRc = BlkdRcds16_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
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
    ERESULT         BlkdRcds16_Disable (
        BLKDRCDS16_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
    ERESULT         BlkdRcds16_Enable (
        BLKDRCDS16_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BLKDRCDS16_DATA *   BlkdRcds16_Init (
        BLKDRCDS16_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BLKDRCDS16_DATA);
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of BlkdRcds16_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BLKDRCDS16);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&BlkdRcds16_Vtbl);
#ifdef  BLKDRCDS16_JSON_SUPPORT
        JsonIn_RegisterClass(BlkdRcds16_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "BlkdRcds16::sizeof(BLKDRCDS16_DATA) = %lu\n", 
                sizeof(BLKDRCDS16_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BLKDRCDS16_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         BlkdRcds16_IsEnabled (
        BLKDRCDS16_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
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
        void        *pMethod = BlkdRcds16_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "BlkdRcds16", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          BlkdRcds16_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BLKDRCDS16_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(BLKDRCDS16_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)BlkdRcds16_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return BlkdRcds16_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return BlkdRcds16_Enable;
                        }
                        break;

                    case 'P':
#ifdef  BLKDRCDS16_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return BlkdRcds16_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return BlkdRcds16_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return BlkdRcds16_ToDebugString;
                        }
#ifdef  BLKDRCDS16_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return BlkdRcds16_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return BlkdRcds16_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == BlkdRcds16_ToDebugString)
                    return "ToDebugString";
#ifdef  BLKDRCDS16_JSON_SUPPORT
                if (pData == BlkdRcds16_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                  R e c o r d  A p p e n d
    //---------------------------------------------------------------

    ERESULT         BlkdRcds16_RecordAppend (
        BLKDRCDS16_DATA *this,
        uint16_t        rcdSize,
        void            *pData,
        uint32_t        *pIndex             // Optional Output Index
    )
    {
        uint16_t        offset = 0;
        uint8_t         *pBlockData;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pBlock) {
            return ERESULT_GENERAL_FAILURE;
        }
        if ((rcdSize == 0) || (rcdSize >= DATA_BLOCK_MAX_SIZE)) {
            return ERESULT_DATA_SIZE;
        }
#endif
        if ((rcdSize + sizeof(INDEX_RECORD)) > this->pBlock->unusedSize) {
            return ERESULT_DATA_TOO_BIG;
        }

        offset = sizeof(DATA_BLOCK);
        offset += (this->pBlock->numRecords * sizeof(INDEX_RECORD)); // Record Index
        offset += this->pBlock->unusedSize;
        offset -= rcdSize;
        pBlockData = (((uint8_t *)this->pBlock) + offset);
        memmove(pBlockData, pData, rcdSize);
        this->pBlock->unusedSize -= rcdSize + sizeof(INDEX_RECORD);
        this->pBlock->index[this->pBlock->numRecords].idxOffset = offset;
        this->pBlock->index[this->pBlock->numRecords].idxSize = rcdSize;
        ++this->pBlock->numRecords;

        // Return to caller.
        if (pIndex) {
            *pIndex = this->pBlock->numRecords;
        }
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                  R e c o r d  D e l e t e
    //---------------------------------------------------------------

    ERESULT         BlkdRcds16_RecordDelete (
        BLKDRCDS16_DATA *this,
        uint32_t        index
    )
    {
        uint16_t        dataOffset;
        uint16_t        dataSize;
        uint16_t        numShiftRcds;
        uint16_t        shiftSize;
        uint8_t         *start;
        uint8_t         *shiftTo;
        int             i;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pBlock) {
            return ERESULT_GENERAL_FAILURE;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            return ERESULT_OUT_OF_RANGE;
        }
#endif

        dataOffset = this->pBlock->index[index - 1].idxOffset;
        dataSize = this->pBlock->index[index - 1].idxSize;
        numShiftRcds = this->pBlock->numRecords - index;

        if( numShiftRcds ) {
            // Shift the data.
            shiftSize = 0;
            for( i=0; i<numShiftRcds; i++ ) {
                shiftSize += this->pBlock->index[index+i].idxSize;
            }
            if( shiftSize ) {
                start = (uint8_t *)this->pBlock
                        + this->pBlock->index[this->pBlock->numRecords - 1].idxOffset;
                shiftTo = start + dataSize;
                memmove(shiftTo, start, shiftSize);
            }
            // Shift the index.
            shiftSize = sizeof(INDEX_RECORD) * numShiftRcds;
            if( shiftSize ) {
                start = (uint8_t *)&this->pBlock->index[index];
                shiftTo = (uint8_t *)&this->pBlock->index[index-1];
                memmove( shiftTo, start, shiftSize );
                // Adjust the index for new offsets.
                for( i=0; i<numShiftRcds; i++ ) {
                    this->pBlock->index[index-1+i].idxOffset += dataSize;
                }
            }
        }

        // Give the record space back.
        this->pBlock->unusedSize += (dataSize + sizeof(INDEX_RECORD));
        --this->pBlock->numRecords;
        this->pBlock->index[this->pBlock->numRecords].idxOffset = 0;
        this->pBlock->index[this->pBlock->numRecords].idxSize = 0;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                  R e c o r d  G e t
    //---------------------------------------------------------------

    ERESULT         BlkdRcds16_RecordGet (
        BLKDRCDS16_DATA *this,
        uint32_t        index,
        uint16_t        dataSize,
        void            *pData,
        uint16_t        *pReturnedSize
    )
    {
        INDEX_RECORD    *pIndex;
        uint16_t        size;
        uint8_t         *pBlockData;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pBlock) {
            return ERESULT_GENERAL_FAILURE;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            return ERESULT_OUT_OF_RANGE;
        }
#endif

        pIndex = (INDEX_RECORD *)(&this->pBlock->index[index - 1]);
        size = pIndex->idxSize;
        pBlockData = (((uint8_t *)this->pBlock) + pIndex->idxOffset);

        size = size < dataSize ? size : dataSize;
        if (pData && size) {
            memmove(pData, pBlockData, size);
        }

        // Return to caller.
        if (pReturnedSize) {
            *pReturnedSize = size;
        }
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                  R e c o r d  G e t  O f f s e t
    //---------------------------------------------------------------

    uint16_t        BlkdRcds16_RecordGetOffset (
        BLKDRCDS16_DATA *this,
        uint16_t        index
    )
    {
        INDEX_RECORD    *pIndex;
        uint16_t        size = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return size;
        }
        if (NULL == this->pBlock) {
            //return ERESULT_GENERAL_FAILURE;
            return size;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            return ERESULT_OUT_OF_RANGE;
        }
#endif

        pIndex = (INDEX_RECORD *)(&this->pBlock->index[index - 1]);
        size = pIndex->idxOffset;

        // Return to caller.
        return size;
    }



    //---------------------------------------------------------------
    //                  R e c o r d  G e t  S i z e
    //---------------------------------------------------------------

    uint16_t        BlkdRcds16_RecordGetSize (
        BLKDRCDS16_DATA *this,
        uint32_t        index
    )
    {
        INDEX_RECORD    *pIndex;
        uint16_t        size = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return size;
        }
        if (NULL == this->pBlock) {
            //return ERESULT_GENERAL_FAILURE;
            return size;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            return ERESULT_OUT_OF_RANGE;
        }
#endif

        pIndex = (INDEX_RECORD *)(&this->pBlock->index[index - 1]);
        size = pIndex->idxSize;

        // Return to caller.
        return size;
    }



    //---------------------------------------------------------------
    //                  R e c o r d  I n s e r t
    //---------------------------------------------------------------

    ERESULT         BlkdRcds16_RecordInsert (
        BLKDRCDS16_DATA *this,
        uint32_t        index,
        uint16_t        rcdSize,
        void            *pRecord
    )
    {
        INDEX_RECORD    *pIndex;
        uint16_t        dataShiftAmt = 0;
        uint16_t        dataShiftOff = 0;
        uint32_t        shiftFirstRcd;          // Relative to 1
        uint32_t        shiftLastRcd;           // Relative to 1
        uint32_t        shiftAmt;
        uint8_t         *start;
        uint8_t         *shiftTo;
        int             i;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pBlock) {
            return ERESULT_GENERAL_FAILURE;
        }
        if (index > this->pBlock->numRecords) {
            return ERESULT_OUT_OF_RANGE;
        }
        if ((rcdSize == 0) || (rcdSize >= DATA_BLOCK_MAX_SIZE)) {
            return ERESULT_DATA_SIZE;
        }
#endif
        if ((rcdSize + sizeof(INDEX_RECORD)) > this->pBlock->unusedSize) {
            return ERESULT_DATA_TOO_BIG;
        }

        shiftFirstRcd = index + 1;
        shiftLastRcd = this->pBlock->numRecords;
        pIndex = (INDEX_RECORD *)(&this->pBlock->index[shiftFirstRcd - 1]);

        // Expand the index.
        start = (uint8_t *)pIndex;
        shiftTo = (uint8_t *)(pIndex + 1);
        shiftAmt = (shiftLastRcd - shiftFirstRcd) * sizeof(INDEX_RECORD);
        if (shiftAmt)
            memmove(shiftTo, start, shiftAmt);

        // Now add the record.
        pIndex->idxSize = rcdSize;
        start = (uint8_t *)this->pBlock + pIndex->idxOffset;
        memmove(start, pRecord, rcdSize);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                  R e c o r d  U p d a t e
    //---------------------------------------------------------------

    ERESULT         BlkdRcds16_RecordUpdate (
        BLKDRCDS16_DATA *this,
        uint32_t        index,
        uint16_t        dataSize,
        void            *pData
    )
    {
        INDEX_RECORD    *pIndex;
        uint16_t        dataShiftAmt = 0;
        uint16_t        dataShiftOff = 0;
        uint16_t        shiftFirstRcd;          // Relative to 1
        uint16_t        shiftLastRcd;           // Relative to 1
        uint8_t         *start;
        uint8_t         *shiftTo;
        int             i;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pBlock) {
            return ERESULT_GENERAL_FAILURE;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            return ERESULT_OUT_OF_RANGE;
        }
#endif
        if (dataSize > (this->pBlock->unusedSize + this->pBlock->index[index-1].idxSize)) {
            return ERESULT_DATA_TOO_BIG;
        }

        pIndex = (INDEX_RECORD *)(&this->pBlock->index[index - 1]);
        shiftFirstRcd = index + 1;
        shiftLastRcd = this->pBlock->numRecords;

        if( dataSize == pIndex->idxSize )
            ;
        else {
            if (dataSize < pIndex->idxSize) {
                dataShiftOff = pIndex->idxSize - dataSize;
                if( (index < this->pBlock->numRecords) && dataShiftOff ) {
                    // Shift the data towards the end of the block closing the hole.
                    dataShiftAmt = 0;
                    for( i=shiftFirstRcd; i<=shiftLastRcd; ++i ) {
                        dataShiftAmt += this->pBlock->index[i-1].idxSize;
                    }
                    if( dataShiftAmt ) {
                        start = (uint8_t *)this->pBlock
                                + this->pBlock->index[shiftLastRcd-1].idxOffset;
                        shiftTo = start + dataShiftOff;
                        memmove( shiftTo, start, dataShiftAmt );
                    }
                    // Adjust the index for new offsets.
                    for( i=shiftFirstRcd; i<=shiftLastRcd; ++i ) {
                        this->pBlock->index[i-1].idxOffset += dataShiftOff;
                    }
                }
                pIndex->idxOffset += dataShiftOff;
            }
            else {
                dataShiftOff = dataSize - pIndex->idxSize;
                if( (index < this->pBlock->numRecords) && dataShiftOff ) {
                    // Shift the data towards the beginning of the block to make more room.
                    dataShiftAmt = 0;
                    for( i=shiftFirstRcd; i<=shiftLastRcd; ++i ) {
                        dataShiftAmt += this->pBlock->index[i-1].idxSize;
                    }
                    if( dataShiftAmt ) {
                        start = (uint8_t *)this->pBlock
                                + this->pBlock->index[shiftLastRcd-1].idxOffset;
                        shiftTo = start - dataShiftOff;
                        memmove( shiftTo, start, dataShiftAmt );
                    }
                    // Adjust the index for new offsets.
                    for( i=shiftFirstRcd; i<=shiftLastRcd; ++i ) {
                        this->pBlock->index[i-1].idxOffset -= dataShiftOff;
                    }
                }
                pIndex->idxOffset -= dataShiftOff;
            }
            this->pBlock->unusedSize += pIndex->idxSize;
            this->pBlock->unusedSize -= dataSize;
        }

        pIndex->idxSize = dataSize;
        start = (uint8_t *)this->pBlock + pIndex->idxOffset;
        memmove(start, pData, dataSize);

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    //---------------------------------------------------------------
    //             S e t u p  W i t h  B l o c k  S i z e
    //---------------------------------------------------------------

    ERESULT         BlkdRcds16_SetupWithBlockSize (
        BLKDRCDS16_DATA *this,
        uint16_t        blockSize,
        uint16_t        rsvdSize,
        void            *pBlock
    )
    {
        uint16_t        minSize;

        #ifdef NDEBUG
        #else
                if (!BlkdRcds16_Validate(this)) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_OBJECT;
                }
        #endif

        BlkdRcds16_BlockFree(this);

        this->blockSize = blockSize;
        this->rsvdSize = rsvdSize;
        if (0 == blockSize) {
            return ERESULT_SUCCESS;
        }

        minSize = sizeof(DATA_BLOCK) + sizeof(INDEX_RECORD)
                + rsvdSize + 1;
        if ((blockSize < minSize) || (blockSize > DATA_BLOCK_MAX_SIZE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

        if (NULL == pBlock) {
            this->pBlock = mem_Malloc(blockSize);
            if (this->pBlock) {
                this->fAlloc = 1;
            }
        } else {
            this->pBlock = pBlock;
        }
        if (this->pBlock) {
        }
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return ERESULT_OUT_OF_MEMORY;
        }
        this->pBlock->cbSize = blockSize;
        // Warning: The above limits the cbSize to less than 32768 which leaves
        //          the high order bit of cbSize available.
        this->pBlock->unusedSize = blockSize - sizeof(DATA_BLOCK) - rsvdSize;
        this->pBlock->rsvdSize = rsvdSize;
        this->pBlock->numRecords = 0;

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          S p l i t
    //---------------------------------------------------------------

    ERESULT         BlkdRcds16_Split (
        BLKDRCDS16_DATA *this,
        BLKDRCDS16_DATA **ppUpper
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        INDEX_RECORD    *pIndex;
        uint16_t        size;
        uint32_t        amt = 0;
        uint32_t        half;           // Half of the unused space
        uint32_t        i;
        uint32_t        j;
        uint32_t        jMax;
        uint8_t         *pBlockData;
        BLKDRCDS16_DATA *pUpper = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pBlock) {
            return ERESULT_GENERAL_FAILURE;
        }
        if (NULL == ppUpper) {
            return ERESULT_GENERAL_FAILURE;
        }
#endif

        half = this->pBlock->cbSize - sizeof(DATA_BLOCK) - this->pBlock->rsvdSize;
        half -= this->pBlock->numRecords * sizeof(INDEX_RECORD);
        half /= 2;
        if (half >= this->pBlock->unusedSize) {
            // No, reason to split since we have lots of space left.
            goto exit00;
        }

        for (i=0; i<this->pBlock->numRecords; i++) {
            pIndex = (INDEX_RECORD *)(&this->pBlock->index[i]);
            if ((amt + pIndex->idxSize) < half)
                amt += pIndex->idxSize;
            else
                break;
        }
        // i gives the record close to the middle.

        pUpper = BlkdRcds16_NewWithBlockSize(this->pBlock->cbSize, this->pBlock->rsvdSize);
        if (OBJ_NIL == pUpper) {
            eRc = ERESULT_OUT_OF_MEMORY;
        }

        jMax = this->pBlock->numRecords;
        i++;
        for (j=i; j<jMax; j++) {
            uint16_t            rcdSize = 0;
            pBlockData = BlkdRcds16_RecordPoint(this, i, &rcdSize);
            if (pBlockData && rcdSize) {
                eRc = BlkdRcds16_RecordAppend(pUpper, rcdSize, pBlockData, NULL);
                if (ERESULT_OK(eRc)) {
                    eRc = BlkdRcds16_RecordDelete(pUpper, i);
                    if (ERESULT_FAILED(eRc)) {
                        obj_Release(pUpper);
                        pUpper = OBJ_NIL;
                        eRc = ERESULT_GENERAL_FAILURE;
                        goto exit00;
                    }
                } else {
                    obj_Release(pUpper);
                    pUpper = OBJ_NIL;
                    eRc = ERESULT_GENERAL_FAILURE;
                    goto exit00;
                }
            }
        }

        // Return to caller.
    exit00:
        if (ppUpper) {
            *ppUpper = pUpper;
        }
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BlkdRcds16_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     BlkdRcds16_ToDebugString (
        BLKDRCDS16_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
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
                    "{%p(%s) size=%d retain=%d  blockOverhead: %d  recordOverhead: %d\n",
                    this,
                    pInfo->pClassName,
                    BlkdRcds16_getSize(this),
                    obj_getRetainCount(this),
                    sizeof(DATA_BLOCK),
                    sizeof(INDEX_RECORD)
            );

        if (this->pBlock) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            eRc = AStr_AppendPrint(
                        pStr,
                        "\tBlocksize: %d  Reserved: %d  Unused: %d  NumRecords: %d\n",
                        this->pBlock->cbSize,
                        this->pBlock->rsvdSize,
                        this->pBlock->unusedSize,
                        this->pBlock->numRecords
                );
            for (i=0; i<this->pBlock->numRecords; i++) {
                uint16_t        size;
                uint16_t        offset;
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                offset = BlkdRcds16_RecordGetOffset(this, i+1);
                size   = BlkdRcds16_RecordGetSize(this, i+1);
                eRc = AStr_AppendPrint(
                            pStr,
                            "\t\tRecord: %d  Size: %d  Offset: %d\n",
                            i+1,
                            size,
                            offset
                    );
            }
        }

#ifdef  XYZZY
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    bool            BlkdRcds16_Validate (
        BLKDRCDS16_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BLKDRCDS16))
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


        if (!(obj_getSize(this) >= sizeof(BLKDRCDS16_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


