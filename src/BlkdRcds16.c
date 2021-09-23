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

    Offset
      0                                     +==========================+
                                            |      Block Header        |
                                            +==========================+
 sizeof(DATA_BLOCK)                         |          Index           |
                                            | (Grows down toward Data) |
                                            +--------------------------+
                                            |   Index 1 - 20 bytes     |
                                            +--------------------------+
 sizeof(DATA_BLOCK) + sizeof(INDEX_RECORD)  |   Index 2 - 30 bytes     |
                                            +==========================+
                                            |                          |
                                            |      Unused Space        |
                                            |                          |
                                            +==========================+
                                            |      Data Records        |
                                            | (Grows up toward Index)  |
                                            +--------------------------+
  blockSize - reserved_size - 20            | Data Record 2 - 30 bytes |
                                            +--------------------------+
  blockSize - reserved_size                 | Data Record 1 - 20 bytes |
                                            +==========================+
                                            |      Reserved Data       |
                                            +==========================+
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
#include        <Endian.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>



// Address of Index Entry for x'th entry (x relative to 0)
#define IndexPtr(x)\
        (INDEX_RECORD *)(((uint8_t *)this->pBlock)+sizeof(DATA_BLOCK)+(x * sizeof(INDEX_RECORD)))


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



    /*!
     Point to a Data Record in the buffer.
     @param     this    object pointer
     @param     index   record index (relative to 1)
     @return    If successful, data record address in block and optionally its size;
                otherwise, NULL.
     */
    void *          BlkdRcds16_DataAddr (
        BLKDRCDS16_DATA *this,
        uint32_t        index
    )
    {
        uint8_t         *pBlockData;
        int32_t         offset = 0;

        offset = BlkdRcds16_DataOffset(this, index, 0);
        if (0 == offset)
            return NULL;

        pBlockData = (((uint8_t *)this->pBlock) + offset);

        // Return to caller.
        return pBlockData;
    }



    //---------------------------------------------------------------
    //                      D a t a  E x p a n d
    //---------------------------------------------------------------

    ERESULT         BlkdRcds16_DataExpand (
        BLKDRCDS16_DATA *this,
        uint32_t        index,              // Relative to 0
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

        dataSize = this->pBlock->index[index - 1].idxSize;
        numShiftRcds = this->pBlock->numRecords - index;

        if( numShiftRcds ) {
            // Shift the data.
            shiftSize = 0;
            for( i=0; i<numShiftRcds; i++ ) {
                shiftSize += this->pBlock->index[index+i].idxSize;
            }
#ifdef IMPLEMENT
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
#endif
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    /*!
     Get a Data Record's offset within the data area. Normally, you would
     supply both the index (relative to 1) and the record size. However,
     if you supply 0 for the index and a record size, then the offset returned
     will be for a first record with that record size. If you supply 1 for
     the index and 0 for the record size, you will get the offset for the
     first record.
     @param     this        object pointer
     @param     index       record index (relative to 1), 0 assumes first record
     @param     recordSize  optional record size for a new record
     @return    If successful, data record address in block and optionally its size;
                otherwise, NULL.
     */
    uint16_t        BlkdRcds16_DataOffset (
        BLKDRCDS16_DATA *this,
        uint16_t        index,
        uint16_t        recordSize
    )
    {
        INDEX_RECORD    *pIndex;
        int32_t         offset = 0;
        int             i;

        // Do initialization.
        if (index > this->pBlock->numRecords)
            return 0;

        offset += BlkdRcds16_getBlockSize(this) - BlkdRcds16_getReservedSize(this);
        if (index) {
            for (i=0; i<=(index-1); i++) {
                pIndex = IndexPtr(i);
                offset -= Endian_GetU16Big(&pIndex->idxSize);
            }
        }
        offset -= recordSize;

        // Return to caller.
        return (uint16_t)(offset & 0xFFFF);
    }



    ERESULT         BlkdRcds16_DataSizeSet (
        BLKDRCDS16_DATA *this,
        uint16_t        index,
        uint16_t        rcdSize
    )
    {
        INDEX_RECORD    *pIndex;
        int32_t         offset;

        // Do initialization.
        if (index == 0) {
            return ERESULT_OUT_OF_RANGE;
        }

        // Set index with record size.
        offset = sizeof(DATA_BLOCK);
        offset += (index - 1) * sizeof(INDEX_RECORD);
        pIndex = (INDEX_RECORD *)(((uint8_t *)this->pBlock) + offset);
        Endian_PutU16Big(&pIndex->idxSize, rcdSize);

        // Return to caller.
        return ERESULT_SUCCESS;
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
    //                   B l o c k   S i z e
    //---------------------------------------------------------------

    uint16_t        BlkdRcds16_getBlockSize (
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        if (NULL == this->pBlock)
            return 0;

        return Endian_GetU16Big(&this->pBlock->cbSize);
    }


    bool            BlkdRcds16_setBlockSize (
        BLKDRCDS16_DATA *this,
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
        if (NULL == this->pBlock)
            return false;

        Endian_PutU16Big(&this->pBlock->cbSize, value);

        return true;
    }



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

    uint16_t        BlkdRcds16_getNumRecords (
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        if (NULL == this->pBlock) {
            return 0;
        }

        return Endian_GetU16Big(&this->pBlock->numRecords);
    }




    bool            BlkdRcds16_setNumRecords (
        BLKDRCDS16_DATA *this,
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

        Endian_PutU16Big(&this->pBlock->numRecords, value);

        return true;
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
    //                   R e s e r v e d   S i z e
    //---------------------------------------------------------------

    uint16_t        BlkdRcds16_getReservedSize (
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        if (NULL == this->pBlock)
            return 0;

        return Endian_GetU16Big(&this->pBlock->rsvdSize);
    }


    bool            BlkdRcds16_setReservedSize (
        BLKDRCDS16_DATA *this,
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
        if (NULL == this->pBlock)
            return false;

        Endian_PutU16Big(&this->pBlock->rsvdSize, value);

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
#endif
        if (NULL == this->pBlock) {
            DEBUG_BREAK();
            return 0;
        }

        return Endian_GetU16Big(&this->pBlock->unusedSize);
    }


    bool            BlkdRcds16_setUnused (
        BLKDRCDS16_DATA *this,
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
        if (NULL == this->pBlock)
            return false;

        Endian_PutU16Big(&this->pBlock->unusedSize, value);

        return true;
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
        uint32_t        *pRcdNum                // OUT - Optional Record Number
    )
    {
        ERESULT         eRc;
        uint16_t        amt;
        uint16_t        rcdNum;
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
        if ((rcdSize + sizeof(INDEX_RECORD)) > BlkdRcds16_getUnused(this)) {
            return ERESULT_DATA_TOO_BIG;
        }

        offset = BlkdRcds16_DataOffset(this, BlkdRcds16_getNumRecords(this), rcdSize);
        pBlockData = (((uint8_t *)this->pBlock) + offset);
        memmove(pBlockData, pData, rcdSize);

        // Update Number of Records.
        rcdNum = BlkdRcds16_getNumRecords(this);
        rcdNum++;
        BlkdRcds16_setNumRecords(this, rcdNum);

        // Set index with record size.
        eRc = BlkdRcds16_DataSizeSet(this, rcdNum, rcdSize);

        // Remove used record space from unused.
        amt = BlkdRcds16_getUnused(this);
        amt -= rcdSize + sizeof(INDEX_RECORD);
        BlkdRcds16_setUnused(this, amt);

        // Return to caller.
        if (pRcdNum) {
            *pRcdNum = rcdNum;
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
        uint16_t        rcdSize;
        uint16_t        rcdNum;
        int32_t         amt;
        uint16_t        numShiftRcds;
        uint16_t        shiftSize;
        uint8_t         *pStart;
        uint8_t         *pShiftTo;
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
        if ((index == 0) || (index > BlkdRcds16_getNumRecords(this))) {
            return ERESULT_OUT_OF_RANGE;
        }
#endif
        rcdSize = BlkdRcds16_RecordSize(this, index);
        BREAK_ZERO(rcdSize);

        // Remove the record.
        if (index == BlkdRcds16_getNumRecords(this)) {
            // If it is the highest record, we only need to
            // adjust the record count and the unused amount.
        }
        else {
            numShiftRcds = BlkdRcds16_getNumRecords(this) - index;
            // Shift the data above the record down.
            shiftSize = 0;
            for( i=0; i<numShiftRcds; i++ ) {
                shiftSize += BlkdRcds16_RecordSize(this, index+i+1);
            }
            if( shiftSize ) {
                // Shift the rcords down.
                pStart = BlkdRcds16_DataAddr(this, BlkdRcds16_getNumRecords(this));
                pShiftTo = pStart + rcdSize;
                memmove(pShiftTo, pStart, shiftSize);
#ifdef NDEBUG
#else
                memset(pStart, 0, rcdSize);
#endif
            }
            // Shift the index up.
            shiftSize = sizeof(INDEX_RECORD) * numShiftRcds;
            if (shiftSize) {
                pStart = (uint8_t *)&this->pBlock->index[index];
                pShiftTo = pStart - sizeof(INDEX_RECORD);
                memmove(pShiftTo, pStart, shiftSize);
#ifdef NDEBUG
#else
                pStart = (uint8_t *)&this->pBlock->index[BlkdRcds16_getNumRecords(this)-1];
                memset(pStart, 0, sizeof(INDEX_RECORD));
#endif
            }
        }

        // Update Number of Records.
        rcdNum = BlkdRcds16_getNumRecords(this);
        rcdNum--;
        BlkdRcds16_setNumRecords(this, rcdNum);

        // Add used record space back to unused.
        amt = BlkdRcds16_getUnused(this);
        amt += rcdSize + sizeof(INDEX_RECORD);
        BlkdRcds16_setUnused(this, amt);

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
        uint16_t        rcdSize;
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
        if ((index == 0) || (index > BlkdRcds16_getNumRecords(this))) {
            return ERESULT_OUT_OF_RANGE;
        }
#endif

        rcdSize = BlkdRcds16_RecordSize(this, index);
        offset = BlkdRcds16_DataOffset(this, index, 0);
        pBlockData = (((uint8_t *)this->pBlock) + offset);
        memmove(pData, pBlockData, rcdSize);

        // Return to caller.
        if (pReturnedSize) {
            *pReturnedSize = rcdSize;
        }
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                  R e c o r d  S i z e
    //---------------------------------------------------------------

    uint16_t        BlkdRcds16_RecordSize (
        BLKDRCDS16_DATA *this,
        uint32_t        index
    )
    {
        INDEX_RECORD    *pIndex;
        int32_t         offset;
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
        if ((index == 0) || (index > BlkdRcds16_getNumRecords(this))) {
            //return ERESULT_OUT_OF_RANGE;
            return size;
        }
#endif

        offset = sizeof(DATA_BLOCK);
        offset += (index - 1) * sizeof(INDEX_RECORD);
        pIndex = (INDEX_RECORD *)(((uint8_t *)this->pBlock) + offset);
        size = Endian_GetU16Big(&pIndex->idxSize);

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
        ERESULT         eRc;
        int32_t         shiftAmt = 0;
        uint32_t        shiftFirstRcd;          // Relative to 1
        uint32_t        shiftLastRcd;           // Relative to 1
        uint16_t        rcdNum;
        int             i;
        uint16_t        numShiftRcds;
        uint16_t        shiftSize;
        uint8_t         *pStart;
        uint8_t         *pShiftTo;

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
        if (index > BlkdRcds16_getNumRecords(this)) {
            return ERESULT_OUT_OF_RANGE;
        }
        if ((rcdSize == 0) || (rcdSize >= DATA_BLOCK_MAX_SIZE)) {
            return ERESULT_DATA_SIZE;
        }
#endif
        if ((rcdSize + sizeof(INDEX_RECORD)) > BlkdRcds16_getUnused(this)) {
            return ERESULT_DATA_TOO_BIG;
        }

        shiftFirstRcd = index + 1;
        shiftLastRcd = BlkdRcds16_getNumRecords(this);
        shiftSize = 0;
        if (index == BlkdRcds16_getUnused(this)) {      // *** Append ***
            numShiftRcds = 0;
            pStart = BlkdRcds16_DataAddr(this, shiftLastRcd) - rcdSize;
            memmove(pStart, pRecord, rcdSize);
            eRc = BlkdRcds16_DataSizeSet(this, shiftLastRcd+1, rcdSize);
        } else {                                        // *** Insert ***
            numShiftRcds = shiftLastRcd - shiftFirstRcd + 1;
            for( i=0; i<numShiftRcds; i++ ) {
                shiftSize += BlkdRcds16_RecordSize(this, index+i+1);
            }
            // Now we shift the records up making a hole for the
            // new record.
            pStart = BlkdRcds16_DataAddr(this, shiftLastRcd);
            pShiftTo = pStart - rcdSize;
            memmove(pShiftTo, pStart, shiftSize);
            // Add the record.
            pStart = BlkdRcds16_DataAddr(this, shiftFirstRcd);
            pStart += BlkdRcds16_RecordSize(this, shiftFirstRcd);
            pStart -= rcdSize;
            memmove(pStart, pRecord, rcdSize);

            // Shift the index down making room for the new entry.
            shiftSize = sizeof(INDEX_RECORD) * numShiftRcds;
            if (shiftSize) {
                pStart = (uint8_t *)&this->pBlock->index[shiftFirstRcd-1];
                pShiftTo = pStart + sizeof(INDEX_RECORD);
                memmove(pShiftTo, pStart, shiftSize);
            }
            eRc = BlkdRcds16_DataSizeSet(this, shiftFirstRcd, rcdSize);
        }

        // Update Number of Records.
        rcdNum = BlkdRcds16_getNumRecords(this);
        rcdNum++;
        BlkdRcds16_setNumRecords(this, rcdNum);

        // Add used record space back to unused.
        shiftAmt = BlkdRcds16_getUnused(this);
        shiftAmt -= rcdSize + sizeof(INDEX_RECORD);
        BlkdRcds16_setUnused(this, shiftAmt);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                  R e c o r d  U p d a t e
    //---------------------------------------------------------------

    ERESULT         BlkdRcds16_RecordUpdate (
        BLKDRCDS16_DATA *this,
        uint32_t        index,
        uint16_t        rcdSize,
        void            *pRecord
    )
    {
        ERESULT         eRc;
        uint16_t        shiftFirstRcd;          // Relative to 1
        uint16_t        shiftLastRcd;           // Relative to 1
        int             i;
        uint16_t        numShiftRcds;
        uint16_t        shiftSize;
        uint8_t         *pStart;
        uint8_t         *pShiftTo;
        uint8_t         *pOldRecord;
        uint16_t        oldRcdSize;
        int32_t         rcdDiff;

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
        if ((index == 0) || (index > BlkdRcds16_getNumRecords(this))) {
            return ERESULT_OUT_OF_RANGE;
        }
#endif
        oldRcdSize = BlkdRcds16_RecordSize(this, index);
        pOldRecord = BlkdRcds16_DataAddr(this, index);
        shiftFirstRcd = index + 1;
        shiftLastRcd = BlkdRcds16_getNumRecords(this);
        shiftSize = 0;
        rcdDiff = rcdSize - oldRcdSize;
        if ((rcdDiff > 0) && (rcdDiff > BlkdRcds16_getUnused(this))) {
            return ERESULT_DATA_TOO_BIG;
        }
        if ((rcdDiff < 0) && ((rcdDiff + oldRcdSize) <= 0)) {
            return ERESULT_DATA_TOO_SMALL;
        }

        if (0 == rcdDiff) {
            pStart = BlkdRcds16_DataAddr(this, index);
            memmove(pStart, pRecord, rcdSize);
        } else {        // Greater than zero
            numShiftRcds = shiftLastRcd - shiftFirstRcd + 1;
            for( i=0; i<numShiftRcds; i++ ) {
                shiftSize += BlkdRcds16_RecordSize(this, index+i+1);
            }
            // Now we shift the records up/down making a hole
            // for the new record.
            pStart = BlkdRcds16_DataAddr(this, shiftLastRcd);
            pShiftTo = pStart - rcdDiff;
            memmove(pShiftTo, pStart, shiftSize);
            // Update the record.
            pStart = pOldRecord;
            pStart -= rcdDiff;
            memmove(pStart, pRecord, rcdSize);
            eRc = BlkdRcds16_DataSizeSet(this, index, rcdSize);
            // Add used record space back to unused.
            shiftSize = BlkdRcds16_getUnused(this);
            shiftSize -= rcdDiff;
            BlkdRcds16_setUnused(this, shiftSize);
        }

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
        if (0 == blockSize) {
            return ERESULT_INVALID_PARAMETER;
        }

        BlkdRcds16_BlockFree(this);

        this->blockSize = blockSize;
        this->rsvdSize = rsvdSize;

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
        BlkdRcds16_setBlockSize(this, blockSize);
        // Warning: The above limits the cbSize to less than 32768 which leaves
        //          the high order bit of cbSize available.
        BlkdRcds16_setUnused(this, (blockSize - sizeof(DATA_BLOCK) - rsvdSize));
        BlkdRcds16_setReservedSize(this, rsvdSize);
        BlkdRcds16_setNumRecords(this, 0);

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
        return ERESULT_NOT_IMPLEMENTED;

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
            //FIXME: pBlockData = BlkdRcds16_RecordPoint(this, i, &rcdSize);
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
                        BlkdRcds16_getBlockSize(this),
                        BlkdRcds16_getReservedSize(this),
                        BlkdRcds16_getUnused(this),
                        BlkdRcds16_getNumRecords(this)
                );
            for (i=0; i<BlkdRcds16_getNumRecords(this); i++) {
                uint16_t        size;
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                size   = BlkdRcds16_RecordSize(this, i+1);
                eRc = AStr_AppendPrint(
                            pStr,
                            "\t\tRecord: %d  Size: %d\n",
                            i+1,
                            size
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


