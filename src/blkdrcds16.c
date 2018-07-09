// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   blkdrcds16.c
 *	Generated 03/10/2017 19:43:23
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
#include "blkdrcds16_internal.h"
#include <hex.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BLKDRCDS16_DATA * blkdrcds16_Alloc(
    )
    {
        BLKDRCDS16_DATA *this;
        uint32_t        cbSize = sizeof(BLKDRCDS16_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    uint16_t		blkdrcds16_CalcBlockSize(
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
        if (dataSize && (dataSize < 32768)) {
        }
        else {
            return 0;
        }
        
        cbSize  = sizeof(DATA_BLOCK);
        cbSize += rsvdSize;
        cbSize += dataSize;
        
        if( cbSize > 32768 ) {
            cbSize = 0;                 // TOO Big!
        }
        
        // Return to caller.
        return cbSize;
    }
    
    
    
    uint16_t		blkdrcds16_CalcDataSize(
        uint16_t        blockSize,
        uint16_t        rsvdSize
    )
    {
        uint32_t        cbSize;
        
        // Do initialization.
        cbSize = sizeof(DATA_BLOCK) + rsvdSize;
        if (cbSize > 32768) {
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

    
    
    BLKDRCDS16_DATA *     blkdrcds16_New(
    )
    {
        BLKDRCDS16_DATA       *this;
        
        this = blkdrcds16_Alloc();
        if (this) {
            this = blkdrcds16_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint8_t *       blkdrcds16_getData(
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return (uint8_t *)this->pBlock;
    }
    
    
    bool            blkdrcds16_setData(
        BLKDRCDS16_DATA *this,
        uint8_t         *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pBlock = (DATA_BLOCK *)pValue;
        
        return true;
    }
    
    

    ERESULT         blkdrcds16_getLastError(
        BLKDRCDS16_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            blkdrcds16_setLastError(
        BLKDRCDS16_DATA *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        blkdrcds16_getNumRecords(
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
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
        
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return this->pBlock->numRecords;
    }
    
    
    
    uint16_t        blkdrcds16_getPriority(
        BLKDRCDS16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            blkdrcds16_setPriority(
        BLKDRCDS16_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        blkdrcds16_getSize(
        BLKDRCDS16_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    uint16_t        blkdrcds16_getUnused(
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
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
        
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = blkdrcds16__Assign(this,pOther);
     @endcode
     @param     this    BLKDRCDS16 object pointer
     @param     pOther  a pointer to another BLKDRCDS16 object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         blkdrcds16_Assign(
        BLKDRCDS16_DATA		*this,
        BLKDRCDS16_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return blkdrcds16_getLastError(this);
        }
        if( !blkdrcds16_Validate(pOther) ) {
            DEBUG_BREAK();
            return blkdrcds16_getLastError(pOther);
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
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
    //eom:
        //FIXME: Implement the assignment.        
        blkdrcds16_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return blkdrcds16_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        blkdrcds16      *pCopy = blkdrcds16_Copy(this);
     @endcode
     @param     this    BLKDRCDS16 object pointer
     @return    If successful, a BLKDRCDS16 object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the BLKDRCDS16 object.
     */
    BLKDRCDS16_DATA *     blkdrcds16_Copy(
        BLKDRCDS16_DATA       *this
    )
    {
        BLKDRCDS16_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = blkdrcds16_New( );
        if (pOther) {
            eRc = blkdrcds16_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            blkdrcds16_Dealloc(
        OBJ_ID          objId
    )
    {
        BLKDRCDS16_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pBlock) {
            mem_Free(this->pBlock);
            this->pBlock = NULL;
        }
        
#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BLKDRCDS16_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         blkdrcds16_Disable(
        BLKDRCDS16_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return blkdrcds16_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BLKDRCDS16_DATA * blkdrcds16_Init(
        BLKDRCDS16_DATA *this
    )
    {
        uint32_t        cbSize = sizeof(BLKDRCDS16_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BLKDRCDS16);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_BLKDRCDS16); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&blkdrcds16_Vtbl);
        
        blkdrcds16_setLastError(this, ERESULT_GENERAL_FAILURE);
        
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(sizeof(BLKDRCDS16_DATA));
#endif
        
        return this;
    }
    
    
    BLKDRCDS16_DATA * blkdrcds16_InitWithSizes(
        BLKDRCDS16_DATA *this,
        uint16_t        blockSize,
        uint16_t        rsvdSize
    )
    {
        uint16_t        minSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = blkdrcds16_Init(this);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        minSize = sizeof(DATA_BLOCK) + sizeof(INDEX_RECORD)
                + sizeof(DATA_BLOCK) + rsvdSize + 1;
        if ((blockSize < minSize) || (blockSize > 32768)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pBlock = mem_Malloc(blockSize);
        if (this->pBlock) {
        }
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pBlock->cbSize = blockSize - sizeof(DATA_BLOCK);
        // Warning: The above limits the cbSize to less than 32768 which leaves
        //          the high order bit of cbSize available.
        this->pBlock->unusedSize = blockSize - sizeof(DATA_BLOCK) - rsvdSize;
        this->pBlock->rsvdSize = rsvdSize;
        this->pBlock->numRecords = 0;

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         blkdrcds16_IsEnabled(
        BLKDRCDS16_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            blkdrcds16_setLastError(this, ERESULT_SUCCESS_TRUE);
            return blkdrcds16_getLastError(this);
        }
        
        // Return to caller.
        blkdrcds16_setLastError(this, ERESULT_SUCCESS_FALSE);
        return blkdrcds16_getLastError(this);
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
     void        *pMethod = $P_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a
                        character string which represents the method name without
                        the object name, "$P", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          blkdrcds16_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BLKDRCDS16_DATA *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)blkdrcds16_Class();
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
                            return blkdrcds16_Disable;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return blkdrcds16_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == blkdrcds16_ToDebugString)
                    return "ToDebugString";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       R e c o r d  A d d
    //---------------------------------------------------------------
    
    ERESULT         blkdrcds16_RecordAdd(
        BLKDRCDS16_DATA *this,
        uint16_t        rcdSize,
        void            *pData,
        uint16_t        *pIndex             // Optional Output Index
    )
    {
        uint16_t        offset = 0;
        uint8_t         *pBlockData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pBlock) {
        }
        else {
            this->eRc = ERESULT_GENERAL_FAILURE;
            return this->eRc;
        }
        if ((rcdSize == 0) || (rcdSize >= 32768)) {
            blkdrcds16_setLastError(this, ERESULT_DATA_SIZE);
            return this->eRc;
        }
        if ((rcdSize + sizeof(INDEX_RECORD)) > this->pBlock->unusedSize) {
            blkdrcds16_setLastError(this, ERESULT_DATA_TOO_BIG);
            return this->eRc;
        }
#endif
        
        offset = sizeof(DATA_BLOCK);
        offset += (this->pBlock->numRecords * sizeof(INDEX_RECORD));
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
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return blkdrcds16_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                  R e c o r d  D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         blkdrcds16_RecordDelete(
        BLKDRCDS16_DATA	*this,
        uint16_t        index
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
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pBlock) {
        }
        else {
            this->eRc = ERESULT_GENERAL_FAILURE;
            return this->eRc;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            this->eRc = ERESULT_OUT_OF_RANGE;
            return this->eRc;
        }
#endif
        
        dataOffset = this->pBlock->index[index-1].idxOffset;
        dataSize = this->pBlock->index[index-1].idxSize;
        numShiftRcds = this->pBlock->numRecords - index;
        
        if( numShiftRcds ) {
            // Shift the data.
            shiftSize = 0;
            for( i=0; i<numShiftRcds; ++i ) {
                shiftSize += this->pBlock->index[index+i].idxSize;
            }
            if( shiftSize ) {
                start = (uint8_t *)this->pBlock
                        + this->pBlock->index[this->pBlock->numRecords - 1].idxOffset;
                shiftTo = start + dataSize;
                memmove( shiftTo, start, shiftSize );
            }
            // Shift the index.
            shiftSize = sizeof(INDEX_RECORD) * numShiftRcds;
            if( shiftSize ) {
                start = (uint8_t *)&this->pBlock->index[index];
                shiftTo = (uint8_t *)&this->pBlock->index[index-1];
                memmove( shiftTo, start, shiftSize );
                // Adjust the index for new offsets.
                for( i=0; i<numShiftRcds; ++i ) {
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
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  R e c o r d  G e t
    //---------------------------------------------------------------
    
    ERESULT         blkdrcds16_RecordGet(
        BLKDRCDS16_DATA	*this,
        uint16_t        index,
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
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pBlock) {
        }
        else {
            this->eRc = ERESULT_GENERAL_FAILURE;
            return this->eRc;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            this->eRc = ERESULT_OUT_OF_RANGE;
            return this->eRc;
        }
#endif
        
        pIndex = (INDEX_RECORD *)(&this->pBlock->index[index-1]);
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
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  R e c o r d  G e t  S i z e
    //---------------------------------------------------------------
    
    ERESULT         blkdrcds16_RecordGetSize(
        BLKDRCDS16_DATA	*this,
        uint16_t        index,
        uint16_t        *pSize
    )
    {
        INDEX_RECORD    *pIndex;
        uint16_t        size;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pBlock) {
        }
        else {
            this->eRc = ERESULT_GENERAL_FAILURE;
            return this->eRc;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            this->eRc = ERESULT_OUT_OF_RANGE;
            return this->eRc;
        }
#endif
        
        pIndex = (INDEX_RECORD *)(&this->pBlock->index[index-1]);
        size = pIndex->idxSize;
        
        // Return to caller.
        if (pSize) {
            *pSize = size;
        }
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  R e c o r d  U p d a t e
    //---------------------------------------------------------------
    
    ERESULT         blkdrcds16_RecordUpdate(
        BLKDRCDS16_DATA	*this,
        uint16_t        index,
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
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pBlock) {
        }
        else {
            this->eRc = ERESULT_GENERAL_FAILURE;
            return this->eRc;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            this->eRc = ERESULT_OUT_OF_RANGE;
            return this->eRc;
        }
        if (dataSize > (this->pBlock->unusedSize + this->pBlock->index[index-1].idxSize)) {
            this->eRc = ERESULT_DATA_TOO_BIG;
            return this->eRc;
        }
#endif
        
        pIndex = (INDEX_RECORD *)(&this->pBlock->index[index-1]);
        shiftFirstRcd = index + 1;
        shiftLastRcd = this->pBlock->numRecords;
        
        if( dataSize == pIndex->idxSize ) {
        }
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
        memmove( start, pData, dataSize);
       
        // Return to caller.
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = blkdrcds16_ToDebugString(this,4);
     @endcode
     @param     this    BLKDRCDS16 object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     blkdrcds16_ToDebugString(
        BLKDRCDS16_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        HEX_DATA        *pHex = OBJ_NIL;
        char            *pMem;
        uint32_t        size;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blkdrcds16_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(blkdrcds16)",
                     this
            );
        AStr_AppendA(pStr, str);
        if (this->pBlock) {
            str[0] = '\0';
            j = snprintf(
                         str,
                         sizeof(str),
                         "  size=%d  %s numRecords=%d\n",
                         this->pBlock->cbSize & 0x7FFF,
                         (this->pBlock->cbSize & 0x8000) ? "Split-Active" : "",
                         this->pBlock->numRecords
                         );
            AStr_AppendA(pStr, str);
        }
        else {
            AStr_AppendA(pStr, "\n");
        }

        if (this->pBlock) {
            pMem = (char *)this->pBlock;
            size = this->pBlock->cbSize + sizeof(DATA_BLOCK);
            while (size) {
                if (indent) {
                    AStr_AppendCharRepeatW32(pStr, indent+3, ' ');
                }
                j = hex_put16BytesObj_64(
                                         pHex,
                                         (uint64_t)pMem,
                                         size,
                                         (void *)pMem,
                                         pStr,
                                         (void *)AStr_AppendCharA
                                         );
                AStr_AppendA(pStr, "\n");
                if (size > 16) {
                    size -= 16;
                    pMem += 16;
                }
                else
                    break;
            }
        }
        
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(blkdrcds16)}\n", this);
        AStr_AppendA(pStr, str);
        
        blkdrcds16_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            blkdrcds16_Validate(
        BLKDRCDS16_DATA *this
    )
    {
 
        // WARNING: We have not established that we have a valid pointer
        //          in 'this' yet.
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_BLKDRCDS16) )
                ;
            else {
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if( !(obj_getSize(this) >= sizeof(BLKDRCDS16_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


