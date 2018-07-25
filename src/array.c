// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   array.c
 *	Generated 11/08/2017 09:27:01
 *
 * Todo:
 *  --  Need to deal with overflow in OffsetOf() and
 *      throughout rest of methods
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
#include <array_internal.h>
#include <hex.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    void            array_FreeArray(
        ARRAY_DATA      *this
    )
    {
        if (this->pArray) {
            mem_Free(this->pArray);
            this->pArray = NULL;
            this->max = 0;
            this->size = 0;
        }
    }
    
    
    
    uint32_t       array_OffsetOf(
        ARRAY_DATA      *this,
        uint32_t        index
    )
    {
        uint32_t        offset = 0;
        
        switch (this->elemSize) {
                
            case 1:
                offset = (index - 1);
                break;
                
            case 2:
                offset = ((index - 1) << 1);
                break;
                
            case 4:
                offset = ((index - 1) << 2);
                break;
                
            case 8:
                offset = ((index - 1) << 3);
                break;
                
            case 16:
                offset = ((index - 1) << 4);
                break;
                
            case 32:
                offset = ((index - 1) << 5);
                break;
                
            case 64:
                offset = ((index - 1) << 6);
                break;
                
            case 128:
                offset = ((index - 1) << 7);
                break;
                
            case 256:
                offset = ((index - 1) << 8);
                break;
                
            case 512:
                offset = ((index - 1) << 9);
                break;
                
            case 1024:
                offset = ((index - 1) << 10);
                break;
                
            default:
                offset = ((index - 1) * this->elemSize);
                break;
        }

        return offset;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ARRAY_DATA *     array_Alloc(
    )
    {
        ARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(ARRAY_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ARRAY_DATA *    array_New(
        uint16_t        elemSize        // Element Size in bytes
    )
    {
        ARRAY_DATA       *this;
        
        if (elemSize)
            ;
        else {
            return OBJ_NIL;
        }
        
        this = array_Alloc( );
        if (this) {
            this = array_Init(this);
            if (this) {
                array_setElemSize(this, elemSize);
            }
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint8_t *        array_getData(
        ARRAY_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return this->pArray;
    }
    
    
    //---------------------------------------------------------------
    //                E l e m e n t  S i z e
    //---------------------------------------------------------------
    
    uint16_t        array_getElemSize(
        ARRAY_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return this->elemSize;
    }
    
    
    bool            array_setElemSize(
        ARRAY_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->elemSize = value;
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          M a x
    //---------------------------------------------------------------
    
    uint32_t        array_getMax(
        ARRAY_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return this->max;
    }
    
    
    bool            array_setMax(
        ARRAY_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->max = value;
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        array_getSize(
        ARRAY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        obj_setLastError(this, ERESULT_SUCCESS);
        return this->size;
    }



    uint32_t        array_getSizeInBytes(
        ARRAY_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return array_OffsetOf(this, (this->size + 1));
    }
    
    
    bool            array_setSize(
        ARRAY_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->size = value;
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                      Z e r o  N e w
    //---------------------------------------------------------------
    
    uint16_t        array_getZeroNew(
        ARRAY_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return this->fZeroNew;
    }
    
    
    bool            array_setZeroNew(
        ARRAY_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->fZeroNew = value;
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    


    //===============================================================
    //                          M e t h o d s
    //===============================================================


    bool            array_AdjustSize(
        ARRAY_DATA      *this,
        int32_t         value
    )
    {
        uint32_t        newSize;
        ERESULT         eRc;
        
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        newSize = this->size + value;
        if (value <= this->max) {
            this->size = newSize;
            return true;
        }
        else {
            if (value > 0) {
                eRc = array_Expand(this, value);
                if (ERESULT_HAS_FAILED(eRc)) {
                    return eRc;
                }
            }
        }
        
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                         A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         array_Append(
        ARRAY_DATA      *this,
        ARRAY_DATA      *other
    )
    {
        ERESULT         eRc = ERESULT_INSUFFICIENT_MEMORY;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !array_Validate(other) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (this->elemSize == other->elemSize) {
        }
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = ERESULT_SUCCESS;
        if (other->size) {
            eRc = array_AppendData(this, other->size, other->pArray);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         array_AppendData(
        ARRAY_DATA      *this,
        uint32_t        numElems,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_INSUFFICIENT_MEMORY;
        uint32_t        offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        offset = this->size + 1;
        
        // Check parameters.
        if (numElems) {
            if ((numElems + this->size) >= UINT32_MAX) {
                return ERESULT_DATA_TOO_BIG;
            }
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (NULL == pData) ) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = array_InsertData(this, offset, numElems, pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         array_AppendSpacing(
        ARRAY_DATA      *this,
        uint32_t        numElems
    )
    {
        ERESULT         eRc = ERESULT_INSUFFICIENT_MEMORY;
        uint32_t        offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (numElems) {
            if ((numElems + this->size) >= UINT32_MAX) {
                return ERESULT_DATA_TOO_BIG;
            }
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        offset = this->size + 1;
        
        eRc = array_InsertSpacing(this, offset, numElems);
        
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
        ERESULT eRc = array__Assign(this,pOther);
     @endcode 
     @param     this    ARRAY object pointer
     @param     pOther  a pointer to another ARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         array_Assign(
        ARRAY_DATA		*this,
        ARRAY_DATA      *pOther
    )
    {
        uint32_t        newSize = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !array_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        array_FreeArray(pOther);

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
        newSize = array_OffsetOf(this, (this->max + 1));
        pOther->elemSize = this->elemSize;
        pOther->pArray = mem_Malloc(newSize);
        if (pOther->pArray == NULL) {
            obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return ERESULT_OUT_OF_MEMORY;
        }
        memmove(pOther->pArray, this->pArray, newSize);
        pOther->max = this->max;
        pOther->size = this->size;
        pOther->fZeroNew = this->fZeroNew;

        //goto eom;

        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
    eom:
        return obj_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        array      *pCopy = array_Copy(this);
     @endcode 
     @param     this    ARRAY object pointer
     @return    If successful, a ARRAY object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the ARRAY object.
     */
    ARRAY_DATA *     array_Copy(
        ARRAY_DATA       *this
    )
    {
        ARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = array_New(this->elemSize);
        if (pOther) {
            eRc = array_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        obj_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            array_Dealloc(
        OBJ_ID          objId
    )
    {
        ARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        BREAK_TRUE((obj_getRetainCount(this) > 0));

        array_FreeArray(this);

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
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
     array      *pCopy = array_DeepCopy(this);
     @endcode
     @param     this    ARRAY object pointer
     @return    If successful, a ARRAY object which must be released,
     otherwise OBJ_NIL.
     @warning  Remember to release the returned the ARRAY object.
     */
    ARRAY_DATA *    array_DeepCopy(
        ARRAY_DATA      *this
    )
    {
        ARRAY_DATA      *pOther = OBJ_NIL;
        uint32_t        newSize;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = array_New(this->elemSize);
        if (OBJ_NIL == pOther) {
            obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        
        // Copy our data to the other object.
        newSize = array_OffsetOf(this, (this->max + 1));
        pOther->pArray = mem_Malloc(newSize);
        if (pOther->pArray == NULL) {
            obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
            obj_Release(pOther);
            return OBJ_NIL;
        }
        memmove(pOther->pArray, this->pArray, newSize);
        pOther->max = this->max;
        pOther->size = this->size;
        pOther->fZeroNew = this->fZeroNew;
        obj_setLastError(pOther, ERESULT_SUCCESS);
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         array_Delete(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    )
    {
        uint32_t        shiftSize;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if((0 ==  offset) || (0 ==  numElems)) {
            return ERESULT_INVALID_PARAMETER;
        }
        if ((numElems + offset - 1) > this->size) {
            return ERESULT_DATA_OUT_OF_RANGE;
        }
#endif
        
        // Shift down elements past deletion point if not at end of array.
        shiftSize = (this->size - (numElems + offset - 1));
        if (shiftSize && ((offset + numElems - 1) < this->size)) {
            memmove(
                    array_Ptr(this, offset),
                    array_Ptr(this, (offset + numElems)),
                    array_OffsetOf(this, (shiftSize + 1))
            );
        }
        if (this->fZeroNew && shiftSize) {
            // Zero the end of the array that was left over.
            memset(
                   array_Ptr(this, (offset + shiftSize)),
                   0,
                   array_OffsetOf(this, (numElems + 1))
            );
        }
        this->size -= numElems;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                        E x p a n d
    //---------------------------------------------------------------
    
    ERESULT         array_Expand(
        ARRAY_DATA      *this,
        uint32_t        min
    )
    {
        void            *pWork;
        uint32_t        oldMax;
        uint32_t        oldMaxLen;
        uint32_t        newMax;
        uint32_t        newArraySize;
        
        // Do initialization.
        if( this == NULL )
            return ERESULT_INVALID_OBJECT;
        
        // Expand the Array.
        oldMax = this->max;
        if (min < oldMax) {
            return ERESULT_SUCCESS;
        }
        if (0 == oldMax) {
            newMax = 1;
        }
        else {
            newMax = oldMax << 1;
        }
        while (min > newMax) {
            newMax <<= 1;
        }
        newArraySize = array_OffsetOf(this, (newMax + 1));
        pWork = (void *)mem_Malloc(newArraySize);
        if( NULL == pWork ) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        oldMaxLen = array_OffsetOf(this, (oldMax + 1));
        
        // Copy the old entries into the new array if any.
        if( this->pArray == NULL )
            ;
        else {
            memmove(pWork, this->pArray, oldMaxLen);
        }
        
        // Clear the new entries.
        if (this->fZeroNew) {
            memset((pWork + oldMaxLen), 0, array_OffsetOf(this, (newMax - oldMax)));
        }
        
        this->max = newMax;
        mem_Free(this->pArray);
        this->pArray = pWork;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          G e t
    //---------------------------------------------------------------
    
    ERESULT         array_Get(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems,
        void            *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        // Check parameters.
        if( (offset > this->size) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (numElems) {
            if ((numElems + offset - 1) > this->size) {
                return ERESULT_DATA_OUT_OF_RANGE;
            }
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (NULL == pData) ) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // Copy in given elements.
        if (this->pArray) {
            memmove(
                    pData,
                    array_Ptr(this, offset),
                    array_OffsetOf(this, (numElems + 1))
            );
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    void *          array_GetAddrOf(
        ARRAY_DATA      *this,
        uint32_t        offset              // in elements (relative to 1)
    )
    {
        void            *pVoid = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return pVoid;
        }
        // Check parameters.
        if( offset && (offset <= this->max) )
            ;
        else {
            return pVoid;
        }
#endif
        
        // Copy in given elements.
        if (this->pArray) {
            pVoid = this->pArray + array_OffsetOf(this, offset);
        }
        
        // Return to caller.
        return pVoid;
    }
    
    

    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ARRAY_DATA *   array_Init(
        ARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(ARRAY_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_ARRAY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_ARRAY);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&array_Vtbl);
        
        obj_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->fZeroNew = 1;

    #ifdef NDEBUG
    #else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "array::offsetof(eRc) = %lu\n", offsetof(ARRAY_DATA,eRc));
        //fprintf(stderr, "array::sizeof(ARRAY_DATA) = %lu\n", sizeof(ARRAY_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(ARRAY_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         array_InsertData(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_INSUFFICIENT_MEMORY;
        uint32_t        newSize;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        // Check parameters.
        if (0 == offset) {
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
        if( ((offset-1) > this->size) ) {
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
        if (numElems) {
            if ((numElems + this->size) <= UINT32_MAX)
                ;
            else {
                obj_setLastError(this, ERESULT_DATA_TOO_BIG);
                return ERESULT_DATA_TOO_BIG;
            }
        }
        else {
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
        if( (NULL == pData) ) {
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        newSize = this->size + numElems;
        
        // Make room in array for data in the array if needed.
        eRc = array_Expand(this, newSize);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        
        // Move elements above insertion point if necessary.
        if (offset <= this->size) {
            memmove(
                    array_Ptr(this, (offset + numElems)),
                    array_Ptr(this, offset),
                    array_OffsetOf(this, (this->size - offset + 2))
                    );
        }
        
        // Copy in given elements.
        memmove(
                array_Ptr(this, offset),
                pData,
                array_OffsetOf(this, (numElems + 1))
        );
        this->size += numElems;
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         array_InsertSpacing(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    )
    {
        ERESULT         eRc = ERESULT_INSUFFICIENT_MEMORY;
        uint32_t        newSize;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        // Check parameters.
        if (0 == offset) {
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
        if( ((offset-1) > this->size) ) {
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
        if (numElems) {
            if ((numElems + this->size) >= UINT32_MAX) {
                obj_setLastError(this, ERESULT_DATA_TOO_BIG);
                return ERESULT_DATA_TOO_BIG;
            }
        }
        else {
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        newSize = this->size + numElems;

        // Make room in array for data in the array if needed.
        eRc = array_Expand(this, newSize);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        
        // Move elements above insertion point if necessary.
        if (offset <= this->size) {
            memmove(
                    array_Ptr(this, (offset + numElems)),
                    array_Ptr(this, offset),
                    array_OffsetOf(this, (this->size - offset + 1))
            );
        }
        this->size += numElems;
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                             P t r
    //---------------------------------------------------------------
    
    void *              array_Ptr(
        ARRAY_DATA          *this,
        uint32_t            elem        // Element Number (relative to 1)
    )
    {
        ERESULT             eRc;
        uint8_t             *pData = NULL;
        
        if (0 == elem) {
            return NULL;
        }
        
        if (elem > this->max) {
            eRc = array_Expand(this, elem);
            if (ERESULT_HAS_FAILED(eRc)) {
                return NULL;
            }
        }
        BREAK_FALSE((elem <= this->max));
        
        pData = this->pArray + array_OffsetOf(this, elem);
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return pData;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P u t
    //---------------------------------------------------------------
    
    ERESULT         array_Put(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems,
        void            *pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#ifdef XYZZY
        if( (offset > this->size) ) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (numElems)
            ;
        else {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (NULL == pData) ) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = array_Expand(this, (offset + numElems));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_setLastError(this, eRc);
            return eRc;
        }
        
        // Copy in the given elements.
        if (this->pArray) {
            memmove(
                    array_Ptr(this, offset),
                    pData,
                    array_OffsetOf(this, (numElems + 1))
            );
        }
        
        if ((offset + numElems - 1) > this->size)
            this->size = offset + numElems - 1;
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
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
        void        *pMethod = array_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   OBJTEST object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "array", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          array_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        ARRAY_DATA   *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
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
                        
                    case 'D':
                        if (str_Compare("Delete", (char *)pStr) == 0) {
                            return array_Delete;
                        }
                        break;

                    case 'I':
                        if (str_Compare("InsertData", (char *)pStr) == 0) {
                            return array_InsertData;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return array_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return array_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == array_ToDebugString)
                    return "ToDebugString";
                if (pData == array_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = array_ToDebugString(this,4);
     @endcode 
     @param     this    ARRAY object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     array_ToDebugString(
        ARRAY_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        char            *pMem;
        uint32_t        size;
        HEX_DATA        *pHex = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = array_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) elemSize=%d  size=%d  max=%d  retain=%d\n",
                    this,
                    pInfo->pClassName,
                    array_getElemSize(this),
                    array_getSize(this),
                    array_getMax(this),
                    obj_getRetainCount(this)
            );

        if (this->pArray) {
            pMem = (char *)this->pArray;
            size = array_getSizeInBytes(this);
            j = 1;
            while (size) {
                if (indent) {
                    AStr_AppendCharRepeatW32(pStr, indent, ' ');
                }
                AStr_AppendCharRepeatW32(pStr, 3, ' ');
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
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     array_ToJSON(
        ARRAY_DATA      *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{\"objectType\":\"%s\"",
                    pInfo->pClassName
                );
        
        AStr_AppendA(pStr, "}\n");
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T r u n c a t e
    //---------------------------------------------------------------
    
    ERESULT         array_Truncate(
        ARRAY_DATA    *this,
        uint32_t        len
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        if (len > this->size) {
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
        
        this->size = len;
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            array_Validate(
        ARRAY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_ARRAY) )
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


        if( !(obj_getSize(this) >= sizeof(ARRAY_DATA)) ) {
            obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return false;
        }

        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                       Z e r o
    //---------------------------------------------------------------
    
    ERESULT         array_Zero(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#ifdef XYZZY
        if( (offset > this->size) ) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (numElems)
            ;
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = array_Expand(this, (offset + numElems));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_setLastError(this, eRc);
            return eRc;
        }
        
        // Clear the elements.
        if (this->pArray) {
            memset(
                    array_Ptr(this, offset),
                    '\0',
                    array_OffsetOf(this, (numElems + 1))
                    );
        }
        
        if ((offset + numElems - 1) > this->size)
            this->size = offset + numElems - 1;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    

    
#ifdef	__cplusplus
}
#endif


