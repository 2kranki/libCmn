// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   BlockF16.c
 *  Generated 10/22/2021 08:20:43
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
#include        <BlockF16_internal.h>
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

    uint8_t *       BlockF16_RecordAddress (
        BLOCKF16_DATA   *this,
        uint16_t        index           // Relative to 0
    )
    {
        uint8_t         *pRcd = NULL;

        if (NULL == this->pBlock)
            return NULL;

        pRcd = this->pBlock->records;
        pRcd += index * RcdSize2Actual(this->pBlock->dataSize);

        return pRcd;
    }



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BLOCKF16_DATA *     BlockF16_Alloc (
        void
    )
    {
        BLOCKF16_DATA       *this;
        uint32_t        cbSize = sizeof(BLOCKF16_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BLOCKF16_DATA * BlockF16_New (
        void
    )
    {
        BLOCKF16_DATA   *this;
        
        this = BlockF16_Alloc( );
        if (this) {
            this = BlockF16_Init(this);
        } 
        return this;
    }


    BLOCKF16_DATA * BlockF16_NewWithSizes (
        uint16_t        blockSize,
        uint16_t        rsvdSize,
        uint16_t        dataSize
    )
    {
        ERESULT         eRc;
        BLOCKF16_DATA   *this;

        this = BlockF16_New( );
        if (this) {
            eRc = BlockF16_Setup(this, blockSize, rsvdSize, dataSize);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
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

    uint8_t *       BlockF16_getBlock (
        BLOCKF16_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif


        return (uint8_t *)this->pBlock;
    }


    bool            BlockF16_setBlock (
        BLOCKF16_DATA   *this,
        uint8_t         *pValue
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (obj_Flag(this, BLOCKF16_ALLOC) && this->pBlock) {
            mem_Free(this->pBlock);
            this->pBlock = NULL;
            obj_FlagOff(this, BLOCKF16_ALLOC);
        }

        this->pBlock = (DATA_BLOCK *)pValue;
        if (pValue) {
            memmove(&this->blkHdr, pValue, sizeof(DATA_BLOCK));
        } else {
            memset(&this->blkHdr, 0, sizeof(DATA_BLOCK));
        }

        return (uint8_t *)this->pBlock;
    }



    //---------------------------------------------------------------
    //                   B l o c k   S i z e
    //---------------------------------------------------------------

    uint16_t        BlockF16_getBlockSize (
        BLOCKF16_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->blkHdr.cbSize;
    }


    bool            BlockF16_setBlockSize (
        BLOCKF16_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->blkHdr.cbSize = value;

        return true;
    }



    //---------------------------------------------------------------
    //                      D a t a   S i z e
    //---------------------------------------------------------------

    uint16_t        BlockF16_getDataSize (
        BLOCKF16_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->blkHdr.dataSize;
    }


    bool            BlockF16_setDataSize (
        BLOCKF16_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->blkHdr.cbSize = value;

        return true;
    }



    //---------------------------------------------------------------
    //        M a x i m u m  N u m b e r  o f  R e c o r d s
    //---------------------------------------------------------------

    uint16_t        BlockF16_getMaxRecords(
        BLOCKF16_DATA   *this
    )
    {

    #ifdef NDEBUG
    #else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
    #endif
        if (NULL == this->pBlock) {
            return 0;
        }

        return this->pBlock->maxRecords;
    }



    //---------------------------------------------------------------
    //              N u m b e r  o f  R e c o r d s
    //---------------------------------------------------------------

    uint16_t        BlockF16_getNumRecords(
        BLOCKF16_DATA   *this
    )
    {

    #ifdef NDEBUG
    #else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
    #endif
        if (NULL == this->pBlock) {
            return 0;
        }

        return this->pBlock->numRecords;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        BlockF16_getPriority (
        BLOCKF16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            BlockF16_setPriority (
        BLOCKF16_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                     R e s e r v e d
    //---------------------------------------------------------------

    void *          BlockF16_getReserved(
        BLOCKF16_DATA   *this
    )
    {
        uint16_t        offset;
        uint8_t         *pData = NULL;

    #ifdef NDEBUG
    #else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
    #endif
        if (NULL == this->pBlock) {
            return NULL;
        }

        if (BlockF16_getBlockSize(this) && BlockF16_getReservedSize(this)) {
            offset  = BlockF16_getBlockSize(this);
            offset -= BlockF16_getReservedSize(this);
            pData   = (uint8_t *)this->pBlock;
            pData  += offset;
        }
        return pData;
    }



    //---------------------------------------------------------------
    //                   R e s e r v e d   S i z e
    //---------------------------------------------------------------

    uint16_t        BlockF16_getReservedSize (
        BLOCKF16_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->blkHdr.rsvdSize;
    }


    bool            BlockF16_setReservedSize (
        BLOCKF16_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->blkHdr.rsvdSize = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        BlockF16_getSize (
        BLOCKF16_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  BlockF16_getSuperVtbl (
        BLOCKF16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
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
    //                          A d d
    //---------------------------------------------------------------

    ERESULT         BlockF16_Add (
        BLOCKF16_DATA   *this,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint8_t         *pRcd;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (NULL == this->pBlock)
            return ERESULT_DATA_MISSING;
        if (0 == this->pBlock->dataSize)
            return ERESULT_DATA_MISSING;
        if (this->pBlock->numRecords >= this->pBlock->maxRecords)
            return ERESULT_DATA_TOO_BIG;

        pRcd = BlockF16_RecordAddress(this, this->pBlock->numRecords);
        if (pRcd) {
            memmove(pRcd, pData, this->pBlock->dataSize);
            this->pBlock->numRecords++;
        } else {
            eRc = ERESULT_GENERAL_FAILURE;
        }

        // Return to caller.
        return eRc;
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
        ERESULT eRc = BlockF16_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another BLOCKF16 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         BlockF16_Assign (
        BLOCKF16_DATA       *this,
        BLOCKF16_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BlockF16_Validate(pOther)) {
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
    int             BlockF16_Compare (
        BLOCKF16_DATA     *this,
        BLOCKF16_DATA     *pOther
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
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!BlockF16_Validate(pOther)) {
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
        BlockF16      *pCopy = BlockF16_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BLOCKF16 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BLOCKF16_DATA *     BlockF16_Copy (
        BLOCKF16_DATA       *this
    )
    {
        BLOCKF16_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef BLOCKF16_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = BlockF16_New( );
        if (pOther) {
            eRc = BlockF16_Assign(this, pOther);
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

    void            BlockF16_Dealloc (
        OBJ_ID          objId
    )
    {
        BLOCKF16_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BLOCKF16_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        BlockF16_setBlock(this, NULL);

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
        BlockF16      *pDeepCopy = BlockF16_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BLOCKF16 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BLOCKF16_DATA *     BlockF16_DeepCopy (
        BLOCKF16_DATA       *this
    )
    {
        BLOCKF16_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = BlockF16_New( );
        if (pOther) {
            eRc = BlockF16_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e l e t e
    //---------------------------------------------------------------

    ERESULT         BlockF16_Delete (
        BLOCKF16_DATA   *this,
        uint32_t        index
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint8_t         *pRcd;
        uint8_t         *pRcd2;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((0 == index) || (index > this->blkHdr.numRecords)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (NULL == this->pBlock)
            return ERESULT_DATA_MISSING;
        if (0 == this->pBlock->dataSize)
            return ERESULT_DATA_MISSING;
        if (this->pBlock->numRecords >= this->pBlock->maxRecords)
            return ERESULT_DATA_TOO_BIG;

        // Make room for the record.
        TRC_OBJ(this, "\ti: %d  used: %d\n", index, this->pBlock->numRecords);
        if (index == this->pBlock->numRecords) {
        } else {
            // Shift records left to make room for new one.
            pRcd = BlockF16_RecordAddress(this, index);
            pRcd2 = BlockF16_RecordAddress(this, index+1);
            memmove(
                    pRcd,
                    pRcd2,
                    ((this->pBlock->numRecords - index)
                     * RcdSize2Actual(this->pBlock->dataSize))
            );
        }
        this->pBlock->numRecords--;

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
    ERESULT         BlockF16_Disable (
        BLOCKF16_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
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
    ERESULT         BlockF16_Enable (
        BLOCKF16_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
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
    //                         G e t
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BlockF16_Get (
        BLOCKF16_DATA   *this,
        uint32_t        index,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint8_t         *pRcd;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((0 == index) || (index > this->blkHdr.maxRecords)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pData) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (NULL == this->pBlock)
            return ERESULT_DATA_MISSING;

        pRcd = BlockF16_RecordAddress(this, (index - 1));
        memmove(pData, pRcd, this->pBlock->dataSize);

        // Put code here...

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BLOCKF16_DATA *   BlockF16_Init (
        BLOCKF16_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BLOCKF16_DATA);
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
        // in the OBJ_INFO at the end of BlockF16_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BLOCKF16);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&BlockF16_Vtbl);
#ifdef  BLOCKF16_JSON_SUPPORT
        JsonIn_RegisterClass(BlockF16_Class());
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
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "BlockF16::sizeof(BLOCKF16_DATA) = %lu\n", 
                sizeof(BLOCKF16_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BLOCKF16_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                        I n s e r t
    //---------------------------------------------------------------

    ERESULT         BlockF16_Insert (
        BLOCKF16_DATA   *this,
        uint32_t        index,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint8_t         *pRcd;
        uint8_t         *pRcd2;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pData) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (NULL == this->pBlock)
            return ERESULT_DATA_MISSING;
        if (0 == this->pBlock->dataSize)
            return ERESULT_DATA_MISSING;
        if (this->pBlock->numRecords >= this->pBlock->maxRecords)
            return ERESULT_DATA_TOO_BIG;

        // Make room for the record.
        TRC_OBJ(this, "\ti: %d  used: %d\n", index, this->pBlock->numRecords);
        if (index == this->pBlock->numRecords) {
        } else {
            // Shift records right to make room for new one.
            pRcd = BlockF16_RecordAddress(this, index);
            pRcd2 = BlockF16_RecordAddress(this, index+1);
            memmove(
                    pRcd2,
                    pRcd,
                    ((this->pBlock->numRecords - index)
                     * RcdSize2Actual(this->pBlock->dataSize))
            );
        }
        this->pBlock->numRecords++;

        // Insert the record.
        pRcd = BlockF16_RecordAddress(this, index);
        memmove(pRcd, pData, this->pBlock->dataSize);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         BlockF16_IsEnabled (
        BLOCKF16_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
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
        void        *pMethod = BlockF16_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "BlockF16", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          BlockF16_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BLOCKF16_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(BLOCKF16_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)BlockF16_Class();
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
                            return BlockF16_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return BlockF16_Enable;
                        }
                        break;

                    case 'P':
#ifdef  BLOCKF16_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return BlockF16_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return BlockF16_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return BlockF16_ToDebugString;
                        }
#ifdef  BLOCKF16_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return BlockF16_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return BlockF16_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == BlockF16_ToDebugString)
                    return "ToDebugString";
#ifdef  BLOCKF16_JSON_SUPPORT
                if (pData == BlockF16_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t u p
    //---------------------------------------------------------------

    ERESULT         BlockF16_Setup(
        BLOCKF16_DATA   *this,
        uint16_t        blockSize,
        uint16_t        rsvdSize,
        uint16_t        dataSize
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint16_t        minSize;

#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (0 == blockSize) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        BlockF16_setBlock(this, NULL);

        minSize = sizeof(DATA_BLOCK) + rsvdSize + dataSize;
        if ((blockSize < minSize) || (blockSize > DATA_BLOCK_MAX_SIZE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

        // Set up Block Header.
        this->blkHdr.cbSize = blockSize;
        this->blkHdr.dataSize = dataSize;
        this->blkHdr.rsvdSize = rsvdSize;
        this->blkHdr.maxRecords = (blockSize - sizeof(DATA_BLOCK) - rsvdSize);
        this->blkHdr.maxRecords /= RcdSize2Actual(dataSize);

        this->pBlock = mem_Malloc(blockSize);
        if (this->pBlock) {
            obj_FlagOn(this, BLOCKF16_ALLOC);
            memmove(this->pBlock, &this->blkHdr, sizeof(DATA_BLOCK));
        } else {
            DEBUG_BREAK();
            obj_Release(this);
            return ERESULT_OUT_OF_MEMORY;
        }

        return eRc;
    }



    //---------------------------------------------------------------
    //                          S p l i t
    //---------------------------------------------------------------

    ERESULT         BlockF16_Split (
        BLOCKF16_DATA   *this,
        BLOCKF16_DATA   **ppNewObj,
        BLOCKF16_DATA   *(*pNew)(uint16_t blockSize, uint16_t rsvdSize, uint16_t dataSize)
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        BLOCKF16_DATA   *pNewObj = OBJ_NIL;
        uint32_t        half;
        uint32_t        cNew;
        uint8_t         *pRcd;
        uint8_t         *pRcd2;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == ppNewObj) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (ppNewObj)
            *ppNewObj = OBJ_NIL;
        if (NULL == this->pBlock)
            return ERESULT_DATA_MISSING;
        if (0 == this->pBlock->dataSize)
            return ERESULT_DATA_MISSING;

        half = (this->pBlock->numRecords + 1) >> 1;
        cNew = this->pBlock->numRecords - half;

        if (pNew) {
            pNewObj =   pNew(
                             this->pBlock->cbSize,
                             this->pBlock->rsvdSize,
                             this->pBlock->dataSize
                        );
        } else {
            pNewObj =   BlockF16_NewWithSizes(
                             this->pBlock->cbSize,
                             this->pBlock->rsvdSize,
                             this->pBlock->dataSize
                        );
        }
        if (OBJ_NIL == pNewObj) {
            return ERESULT_OUT_OF_MEMORY;
        }

        // Copy second half of data to new object.
        pRcd = BlockF16_RecordAddress(pNewObj, 0);
        pRcd2 = BlockF16_RecordAddress(this, half);
        memmove(pRcd, pRcd2, (cNew * RcdSize2Actual(this->pBlock->dataSize)));

        // Adjust number of records in each.
        pNewObj->pBlock->numRecords = cNew;
        this->pBlock->numRecords = half;

        // Return to caller.
        if (ppNewObj)
            *ppNewObj = pNewObj;
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BlockF16_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     BlockF16_ToDebugString (
        BLOCKF16_DATA      *this,
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
        uint32_t        *pRcd;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
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
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    BlockF16_getSize(this),
                    obj_getRetainCount(this)
            );
        if (this->pBlock) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            eRc = AStr_AppendPrint(
                        pStr,
                        "blockSize=%d  rsvdSize=%d  dataSize=%d\n",
                        this->pBlock->cbSize,
                        this->pBlock->rsvdSize,
                        this->pBlock->dataSize
                );
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            eRc = AStr_AppendPrint(
                        pStr,
                        "maxReecords=%d  numRecords=%d\n",
                        this->pBlock->maxRecords,
                        this->pBlock->numRecords
                );
            if (this->pBlock->dataSize) {
                for (i=0; i<this->pBlock->numRecords; i++) {
                    uint8_t         *pRcd = BlockF16_RecordAddress(this, i);
                    if (indent) {
                        AStr_AppendCharRepeatA(pStr, indent+8, ' ');
                    }
                    eRc = AStr_AppendPrint(
                                pStr,
                                "Record %d\n",
                                i+1
                        );
                    eRc = AStr_AppendHexData(pStr, pRcd, this->pBlock->dataSize, indent+8);
                }
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
    //                         U p d a t e
    //---------------------------------------------------------------

    ERESULT         BlockF16_Update (
        BLOCKF16_DATA   *this,
        uint32_t        index,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint8_t         *pRcd;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BlockF16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((0 == index) || (index > this->blkHdr.numRecords)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pData) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (NULL == this->pBlock)
            return ERESULT_DATA_MISSING;
        if (0 == this->pBlock->dataSize)
            return ERESULT_DATA_MISSING;

        pRcd = BlockF16_RecordAddress(this, (index - 1));
        memmove(pRcd, pData, this->pBlock->dataSize);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            BlockF16_Validate (
        BLOCKF16_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BLOCKF16))
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


        if (!(obj_getSize(this) >= sizeof(BLOCKF16_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


