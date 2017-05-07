// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   blkidx16.c
 *	Generated 03/05/2017 09:37:30
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
#include "blkidx16_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    ERESULT         blkidx16_WillNewRecordFit(
        BLKIDX16_DATA   *this,
        uint16_t        recordSize
    )
    {
        uint16_t        unused;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        unused = blkidx16_getUnused(this);
        if (recordSize > unused) {
            blkidx16_setLastError(this, ERESULT_DATA_TOO_BIG);
            return this->eRc;
        }
        if (recordSize > sizeof(INDEX_RECORD)) {
            blkidx16_setLastError(this, ERESULT_DATA_TOO_BIG);
            return this->eRc;
        }
        unused -= sizeof(INDEX_RECORD);
        if (recordSize > sizeof(DATA_RECORD)) {
            blkidx16_setLastError(this, ERESULT_DATA_TOO_BIG);
            return this->eRc;
        }
        
        // Return to caller.
        blkidx16_setLastError(this, ERESULT_SUCCESS);
        return this->eRc;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BLKIDX16_DATA * blkidx16_Alloc(
    )
    {
        BLKIDX16_DATA   *this;
        uint32_t        cbSize = sizeof(BLKIDX16_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BLKIDX16_DATA *     blkidx16_New(
        uint16_t        blockSize,          // Size of the Block
        uint16_t        rsvdSize            // Size of Reserved Area
                                            // within the block
    )
    {
        BLKIDX16_DATA   *this;
        
        this = blkidx16_Alloc();
        if (this) {
            this = blkidx16_Init(this, blockSize, rsvdSize);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         blkidx16_getLastError(
        BLKIDX16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            blkidx16_setLastError(
        BLKIDX16_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        blkidx16_getPriority(
        BLKIDX16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        blkidx16_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            blkidx16_setPriority(
        BLKIDX16_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        blkidx16_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    void *          blkidx16_getReserved(
        BLKIDX16_DATA       *this
    )
    {
        uint8_t             *pData;
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        pData = (uint8_t *)this->pBlock + this->pBlock->cbSize;
        
        blkidx16_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }
    
    
    
    uint32_t        blkidx16_getSize(
        BLKIDX16_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        blkidx16_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }




    ASTR_DATA * blkidx16_getStr(
        BLKIDX16_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        blkidx16_setLastError(this, ERESULT_SUCCESS);
        //return this->pStr;
        return OBJ_NIL;
    }
    
    
    bool        blkidx16_setStr(
        BLKIDX16_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        //if (this->pStr) {
            //obj_Release(this->pStr);
        //}
        //this->pStr = pValue;
        
        blkidx16_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    uint16_t        blkidx16_getUnused(
        BLKIDX16_DATA   *this
    )
    {
        uint16_t        unused;
        
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        unused =  this->pBlock->cbSize - sizeof(INDEX_BLOCK);
        unused -= (this->pBlock->numRecords * sizeof(INDEX_RECORD));
        unused -= this->pBlock->dataSize;
        unused -= this->pBlock->rsvdSize;
        
        return unused;
    }
    
    
    
    
    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A d d  D a t a
    //---------------------------------------------------------------
    
    ERESULT         blkidx16_AddData(
        BLKIDX16_DATA   *this,
        uint16_t        dataSize,
        void            *pData,
        uint16_t        *pIndex
    )
    {
        uint16_t        offset;
        uint16_t        rcdSize = dataSize + sizeof(DATA_RECORD);
        DATA_RECORD     *pDataRcd;
        
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        BREAK_NULL(this->pBlock);
        if ((dataSize == 0) || (pData == NULL)
            || (dataSize > (65535 - sizeof(DATA_RECORD)))) {
            blkidx16_setLastError(this, ERESULT_INVALID_PARAMETER);
            return this->eRc;
        }
#endif
        
        if (ERESULT_FAILED(blkidx16_WillNewRecordFit(this,dataSize))) {
            return this->eRc;
        }
        offset = this->pBlock->cbSize - this->pBlock->rsvdSize - this->pBlock->dataSize;
        offset -= rcdSize;
        this->pBlock->index[this->pBlock->numRecords++].offset = offset;
        pDataRcd = (DATA_RECORD *)((uint8_t *)this->pBlock + offset);
        pDataRcd->size = dataSize;
        memmove(pData, pDataRcd->data, dataSize);
        this->pBlock->dataSize += rcdSize;
        
        if (pIndex) {
            *pIndex = this->pBlock->numRecords;
        }
        blkidx16_setLastError(this, ERESULT_SUCCESS);
        return this->eRc;
    }

    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code:
        ERESULT eRc = blkidx16__Assign(this,pOther);
     @endcode:
     @param:    this    BLKIDX16 object pointer
     @param:    pOther  a pointer to another BLKIDX16 object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         blkidx16_Assign(
        BLKIDX16_DATA		*this,
        BLKIDX16_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return blkidx16_getLastError(this);
        }
        if( !blkidx16_Validate(pOther) ) {
            DEBUG_BREAK();
            return blkidx16_getLastError(pOther);
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
        blkidx16_setLastError(this, ERESULT_SUCCESS);
    //eom:
        //FIXME: Implement the assignment.        
        blkidx16_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return blkidx16_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        blkidx16      *pCopy = blkidx16_Copy(this);
     @endcode:
     @param:    this    BLKIDX16 object pointer
     @return:   If successful, a BLKIDX16 object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the BLKIDX16 object.
     */
    BLKIDX16_DATA *     blkidx16_Copy(
        BLKIDX16_DATA       *this
    )
    {
        BLKIDX16_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = blkidx16_New(this->pBlock->cbSize, this->pBlock->rsvdSize);
        if (pOther) {
            eRc = blkidx16_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        blkidx16_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            blkidx16_Dealloc(
        OBJ_ID          objId
    )
    {
        BLKIDX16_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BLKIDX16_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        blkidx16_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D a t a  S i z e
    //---------------------------------------------------------------

    uint16_t            blkidx16_DataSize(
        BLKIDX16_DATA       *this,
        uint16_t            index
    )
    {
        uint16_t            size;
        uint16_t            offset;
        DATA_RECORD         *pDataRcd;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        BREAK_NULL(this->pBlock);
        if( (index < 1) || (index > this->pBlock->numRecords) ) {
            blkidx16_setLastError(this, ERESULT_OUT_OF_RANGE);
            return this->eRc;
        }
    #endif

        offset = this->pBlock->index[index].offset;
        pDataRcd = (DATA_RECORD *)((uint8_t *)this->pBlock + offset);
        size = pDataRcd->size;

        // Return to caller.
        blkidx16_setLastError(this, ERESULT_SUCCESS);
        return size;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT             blkidx16_Enable(
        BLKIDX16_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return blkidx16_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        blkidx16_setLastError(this, ERESULT_SUCCESS);
        return blkidx16_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BLKIDX16_DATA *   blkidx16_Init(
        BLKIDX16_DATA   *this,
        uint16_t        blockSize,          // Size of the Block
        uint16_t        rsvdSize            // Size of Reserved Area
                                            // within the block
    )
    {
        uint32_t        cbSize = sizeof(BLKIDX16_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BLKIDX16);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_BLKIDX16);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&blkidx16_Vtbl);
        
        blkidx16_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->pBlock = mem_Calloc(1, blockSize);
        if (NULL == this->pBlock) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pBlock->cbSize = blockSize;
        this->pBlock->rsvdSize = rsvdSize;

    #ifdef NDEBUG
    #else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         blkidx16_IsEnabled(
        BLKIDX16_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return blkidx16_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            blkidx16_setLastError(this, ERESULT_SUCCESS_TRUE);
            return blkidx16_getLastError(this);
        }
        
        // Return to caller.
        blkidx16_setLastError(this, ERESULT_SUCCESS_FALSE);
        return blkidx16_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = blkidx16_ToDebugString(this,4);
     @endcode:
     @param:    this    BLKIDX16 object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     blkidx16_ToDebugString(
        BLKIDX16_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blkidx16_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(blkidx16) size=%d\n",
                     this,
                     blkidx16_getSize(this)
            );
        AStr_AppendA(pStr, str);

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
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(blkidx16)}\n", this);
        AStr_AppendA(pStr, str);
        
        blkidx16_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            blkidx16_Validate(
        BLKIDX16_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        // in this yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_BLKIDX16) )
                ;
            else
                return false;
        }
        else
            return false;
        // Now, we have validated that we have a valid pointer in
        // this.


        if( !(obj_getSize(this) >= sizeof(BLKIDX16_DATA)) ) {
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


