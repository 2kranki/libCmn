// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   value.c
 *	Generated 08/26/2017 09:50:28
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
#include    <value_internal.h>
#include    <hex.h>
#include    <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    const
    char            *pTypeStr[] = {
        "VALUE_TYPE_UNKNOWN",
        "VALUE_TYPE_FLOAT",         
        "VALUE_TYPE_DOUBLE",
        "VALUE_TYPE_INT16",
        "VALUE_TYPE_INT32",
        "VALUE_TYPE_INT64",
        //VALUE_TYPE_INT128,
        "VALUE_TYPE_UINT16",
        "VALUE_TYPE_UINT32",
        "VALUE_TYPE_UINT64",
        //VALUE_TYPE_UINT128,
        "VALUE_TYPE_OBJECT",
        "VALUE_TYPE_DATA",
        "VALUE_TYPE_DATA_FREE",
        NULL
    };


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    void            value_FreeData(
        VALUE_DATA      *this
    )
    {
        
        switch (this->type) {
                
            case VALUE_TYPE_INT16:
                break;
                
            case VALUE_TYPE_INT32:
                break;
                
            case VALUE_TYPE_INT64:
                break;
                
            case VALUE_TYPE_UINT16:
                break;
                
            case VALUE_TYPE_UINT32:
                break;
                
            case VALUE_TYPE_UINT64:
                break;
                
            case VALUE_TYPE_OBJECT:
                if (this->value.pObject) {
                    obj_Release(this->value.pObject);
                    this->value.pObject = OBJ_NIL;
                }
                break;
                
            case VALUE_TYPE_DATA:
                break;
                
            case VALUE_TYPE_DATA_FREE:
                if (this->value.data.pData) {
                    mem_Free(this->value.data.pData);
                    this->value.data.pData = NULL;
                }
                this->value.data.length = 0;
                break;
                
        }
        this->type = VALUE_TYPE_UNKNOWN;
        
    }


    
    const
    char *     value_TypeToString(
        VALUE_DATA      *this,
        uint16_t        type
    )
    {
        
        // Do initialization.
        if (type >= VALUE_TYPE_HIGHEST) {
            return "";
        }
        
        // Return to caller.
        return pTypeStr[type];
    }
    
    
    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    VALUE_DATA *     value_Alloc(
    )
    {
        VALUE_DATA      *this;
        uint32_t        cbSize = sizeof(VALUE_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    VALUE_DATA *    value_New(
    )
    {
        VALUE_DATA      *this;
        
        this = value_Alloc();
        if (this) {
            this = value_Init(this);
        } 
        return this;
    }


    VALUE_DATA *    value_NewData(
        int32_t         length,
        uint8_t         *pData
    )
    {
        VALUE_DATA      *this;
        
        this = value_Alloc();
        if (this) {
            this = value_InitData(this, length, pData);
        }
        return this;
    }
    
    
    VALUE_DATA *    value_NewDataFree(
        int32_t         length,
        uint8_t         *pData
    )
    {
        VALUE_DATA      *this;
        
        this = value_Alloc();
        if (this) {
            this = value_InitDataFree(this, length, pData);
        }
        return this;
    }
    
    
    VALUE_DATA *    value_NewI16(
        int16_t         value
    )
    {
        VALUE_DATA      *this;
        
        this = value_Alloc();
        if (this) {
            this = value_InitI16(this, value);
        }
        return this;
    }
    
    
    VALUE_DATA *    value_NewI32(
        int32_t         value
    )
    {
        VALUE_DATA      *this;
        
        this = value_Alloc();
        if (this) {
            this = value_InitI32(this, value);
        }
        return this;
    }
    
    
    VALUE_DATA *    value_NewI64(
        int64_t         value
    )
    {
        VALUE_DATA      *this;
        
        this = value_Alloc();
        if (this) {
            this = value_InitI64(this, value);
        }
        return this;
    }
    
    
    VALUE_DATA *    value_NewObject(
        OBJ_DATA        *pValue
    )
    {
        VALUE_DATA      *this;
        
        this = value_Alloc();
        if (this) {
            this = value_InitObject(this, pValue);
        }
        return this;
    }
    
    
    VALUE_DATA *    value_NewU16(
        uint16_t        value
    )
    {
        VALUE_DATA      *this;
        
        this = value_Alloc();
        if (this) {
            this = value_InitI16(this, value);
        }
        return this;
    }
    
    
    VALUE_DATA *    value_NewU32(
        uint32_t        value
    )
    {
        VALUE_DATA      *this;
        
        this = value_Alloc();
        if (this) {
            this = value_InitU32(this, value);
        }
        return this;
    }
    
    
    VALUE_DATA *    value_NewU64(
        uint64_t        value
    )
    {
        VALUE_DATA      *this;
        
        this = value_Alloc();
        if (this) {
            this = value_InitU64(this, value);
        }
        return this;
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          D a t a
    //---------------------------------------------------------------
    
    uint8_t *       value_getData(
        VALUE_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if ((this->type == VALUE_TYPE_DATA) || (this->type == VALUE_TYPE_DATA_FREE)){
            value_setLastError(this, ERESULT_SUCCESS);
            return this->value.data.pData;
        }
        else {
            value_setLastError(this, ERESULT_DATA_MISSING);
            return NULL;
        }
    }
    

    uint32_t        value_getDataLen(
        VALUE_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if ((this->type == VALUE_TYPE_DATA) || (this->type == VALUE_TYPE_DATA_FREE)){
            value_setLastError(this, ERESULT_SUCCESS);
            return this->value.data.length;
        }
        else {
            value_setLastError(this, ERESULT_DATA_MISSING);
            return 0;
        }
    }
    
    

    //---------------------------------------------------------------
    //                          I n t 1 6
    //---------------------------------------------------------------
    
    int16_t         value_getI16(
        VALUE_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (this->type == VALUE_TYPE_INT16) {
            value_setLastError(this, ERESULT_SUCCESS);
            return this->value.i16;
        }
        else {
            value_setLastError(this, ERESULT_DATA_MISSING);
            return 0;
        }
    }
    
    
    bool            value_setI16(
        VALUE_DATA      *this,
        int16_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        value_FreeData(this);
        this->value.i16 = value;
        this->type = VALUE_TYPE_INT16;
        
        value_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n t 3 2
    //---------------------------------------------------------------
    
    int32_t         value_getI32(
        VALUE_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (this->type == VALUE_TYPE_INT32) {
            value_setLastError(this, ERESULT_SUCCESS);
            return this->value.i32;
        }
        else {
            value_setLastError(this, ERESULT_DATA_MISSING);
            return 0;
        }
    }
    
    
    bool            value_setI32(
        VALUE_DATA      *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        value_FreeData(this);
        this->value.i32 = value;
        this->type = VALUE_TYPE_INT32;
        
        value_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n t 6 4
    //---------------------------------------------------------------
    
    int64_t         value_getI64(
        VALUE_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (this->type == VALUE_TYPE_INT64) {
            value_setLastError(this, ERESULT_SUCCESS);
            return this->value.i64;
        }
        else {
            value_setLastError(this, ERESULT_DATA_MISSING);
            return 0;
        }
    }
    
    
    bool            value_setI64(
        VALUE_DATA      *this,
        int64_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        value_FreeData(this);
        this->value.i64 = value;
        this->type = VALUE_TYPE_INT64;
        
        value_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         value_getLastError(
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            value_setLastError(
        VALUE_DATA      *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                          O b j e c t
    //---------------------------------------------------------------
    
    OBJ_DATA *      value_getObject(
        VALUE_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->type == VALUE_TYPE_OBJECT) {
            value_setLastError(this, ERESULT_SUCCESS);
            return this->value.pObject;
        }
        else {
            value_setLastError(this, ERESULT_DATA_MISSING);
            return OBJ_NIL;
        }
    }
    
    
    bool            value_setObject(
        VALUE_DATA      *this,
        OBJ_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        value_FreeData(this);
        this->value.pObject = pValue;
        this->type = VALUE_TYPE_OBJECT;
        
        value_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------
    
    uint16_t        value_getType(
        VALUE_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        value_setLastError(this, ERESULT_SUCCESS);
        return this->type;
    }
    
    
    bool            value_setType(
        VALUE_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->type = value;
        
        value_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          U i n t 1 6
    //---------------------------------------------------------------
    
    uint16_t        value_getU16(
        VALUE_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (this->type == VALUE_TYPE_UINT16) {
            value_setLastError(this, ERESULT_SUCCESS);
            return this->value.u16;
        }
        else {
            value_setLastError(this, ERESULT_DATA_MISSING);
            return 0;
        }
    }
    
    
    bool            value_setU16(
        VALUE_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        value_FreeData(this);
        this->value.u16 = value;
        this->type = VALUE_TYPE_UINT16;
        
        value_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          U i n t 3 2
    //---------------------------------------------------------------
    
    uint32_t        value_getU32(
        VALUE_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (this->type == VALUE_TYPE_UINT32) {
            value_setLastError(this, ERESULT_SUCCESS);
            return this->value.u16;
        }
        else {
            value_setLastError(this, ERESULT_DATA_MISSING);
            return 0;
        }
    }
    
    
    bool            value_setU32(
        VALUE_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        value_FreeData(this);
        this->value.u32 = value;
        this->type = VALUE_TYPE_UINT32;
        
        value_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          U i n t 6 4
    //---------------------------------------------------------------
    
    uint64_t        value_getU64(
        VALUE_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (this->type == VALUE_TYPE_UINT64) {
            value_setLastError(this, ERESULT_SUCCESS);
            return this->value.u64;
        }
        else {
            value_setLastError(this, ERESULT_DATA_MISSING);
            return 0;
        }
    }
    
    
    bool            value_setU64(
        VALUE_DATA      *this,
        uint64_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        value_FreeData(this);
        this->value.u64 = value;
        this->type = VALUE_TYPE_UINT64;
        
        value_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = value__Assign(this,pOther);
     @endcode
     @param     this    VALUE object pointer
     @param     pOther  a pointer to another VALUE object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         value_Assign(
        VALUE_DATA		*this,
        VALUE_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !value_Validate(pOther) ) {
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
        value_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        value_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return value_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        value      *pCopy = value_Copy(this);
     @endcode
     @param     this    VALUE object pointer
     @return    If successful, a VALUE object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the VALUE object.
     */
    VALUE_DATA *     value_Copy(
        VALUE_DATA       *this
    )
    {
        VALUE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = value_New( );
        if (pOther) {
            eRc = value_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        value_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            value_Dealloc(
        OBJ_ID          objId
    )
    {
        VALUE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((VALUE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        value_FreeData(this);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         value_Disable(
        VALUE_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            value_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return value_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        value_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         value_Enable(
        VALUE_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        value_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    VALUE_DATA *   value_Init(
        VALUE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(VALUE_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_VALUE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_VALUE);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&value_Vtbl);
        
        value_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "offsetof(eRc) = %lu\n", offsetof(VALUE_DATA,eRc));
        fprintf(stderr, "sizeof(VALUE_DATA) = %lu\n", sizeof(VALUE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(VALUE_DATA));
    #endif

        return this;
    }

     
    VALUE_DATA *    value_InitData(
        VALUE_DATA      *this,
        int32_t         length,
        uint8_t         *pData
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = value_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = VALUE_TYPE_DATA;
        this->value.data.length = length;
        this->value.data.pData = pData;
        
        return this;
    }
    
    
    VALUE_DATA *    value_InitDataFree(
        VALUE_DATA      *this,
        int32_t         length,
        uint8_t         *pData
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = value_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = VALUE_TYPE_DATA_FREE;
        this->value.data.length = length;
        this->value.data.pData = pData;
        
        return this;
    }
    
    
    VALUE_DATA *    value_InitI8(
        VALUE_DATA      *this,
        int8_t          value
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = value_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = VALUE_TYPE_INT8;
        this->value.i8 = value;
        
        return this;
    }
    
    
   VALUE_DATA *    value_InitI16(
        VALUE_DATA      *this,
        int16_t         i16
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = value_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = VALUE_TYPE_INT16;
        this->value.i16 = i16;
        
        return this;
    }
    
    
    VALUE_DATA *    value_InitI32(
        VALUE_DATA     *this,
        int32_t         i32
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = value_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = VALUE_TYPE_INT32;
        this->value.i32 = i32;
        
        return this;
    }
    
    
    VALUE_DATA *    value_InitI64(
        VALUE_DATA      *this,
        int64_t         i64
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = value_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = VALUE_TYPE_INT64;
        this->value.i64 = i64;
        
        return this;
    }
    
    
    VALUE_DATA *    value_InitObject(
        VALUE_DATA      *this,
        OBJ_DATA        *pValue
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = value_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = VALUE_TYPE_OBJECT;
        value_setObject(this, pValue);
        
        return this;
    }
    
    
    VALUE_DATA *    value_InitU8(
        VALUE_DATA      *this,
        uint8_t         value
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = value_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = VALUE_TYPE_UINT8;
        this->value.u8 = value;
        
        return this;
    }
    
    
    VALUE_DATA *    value_InitU16(
        VALUE_DATA      *this,
        uint16_t        value
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = value_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = VALUE_TYPE_UINT16;
        this->value.u16 = value;
        
        return this;
    }
    
    
    VALUE_DATA *    value_InitU32(
        VALUE_DATA      *this,
        uint32_t        value
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = value_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = VALUE_TYPE_UINT32;
        this->value.u32 = value;
        
        return this;
    }
    
    
    VALUE_DATA *    value_InitU64(
        VALUE_DATA      *this,
        uint64_t        value
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = value_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = VALUE_TYPE_UINT64;
        this->value.u64 = value;
        
        return this;
    }
    
    

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         value_IsEnabled(
        VALUE_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            value_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        value_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          value_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        VALUE_DATA      *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
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
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return value_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return value_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return value_ToDebugString;
                        }
#ifdef XYZZY
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return value_ToJSON;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
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
        ASTR_DATA      *pDesc = value_ToDebugString(this,4);
     @endcode
     @param     this    VALUE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     value_ToDebugString(
        VALUE_DATA      *this,
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
        if( !value_Validate(this) ) {
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
                     "{%p(value) type=%s\n",
                     this,
                     value_TypeToString(this, this->type)
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(value)}\n", this);
        AStr_AppendA(pStr, str);
        
        value_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            value_Validate(
        VALUE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_VALUE) )
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


        if( !(obj_getSize(this) >= sizeof(VALUE_DATA)) ) {
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


