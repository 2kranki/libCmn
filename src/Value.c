// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Value.c
 *	Generated 12/31/2019 15:27:11
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
#include        <Value_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    
    static
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
    void            Value_FreeData (
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
                this->value.data.pData = NULL;
                this->value.data.length = 0;
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
    char *     Value_TypeToString (
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

    VALUE_DATA *     Value_Alloc (
        void
    )
    {
        VALUE_DATA       *this;
        uint32_t        cbSize = sizeof(VALUE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    VALUE_DATA *     Value_New (
        void
    )
    {
        VALUE_DATA       *this;
        
        this = Value_Alloc( );
        if (this) {
            this = Value_Init(this);
        } 
        return this;
    }



    VALUE_DATA *    Value_NewData (
        int32_t         length,
        uint8_t         *pData
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setData(this, length, pData);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewDataFree (
        int32_t         length,
        uint8_t         *pData
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setDataFree(this, length, pData);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewDouble (
        double          value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setDouble(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewI8 (
        int8_t          value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setI8(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewI16 (
        int16_t         value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setI16(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewI32 (
        int32_t         value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setI32(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewI64 (
        int64_t         value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setI64(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewObject (
        OBJ_DATA        *pValue
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setObject(this, pValue);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewU8 (
        uint8_t         value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setU8(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewU16 (
        uint16_t        value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setU16(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewU32 (
        uint32_t        value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setU32(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewU64 (
        uint64_t        value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setU64(this, value);
            if (!fRc) {
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
    //                          D a t a
    //---------------------------------------------------------------

    uint8_t *       Value_getData (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if ((this->type == VALUE_TYPE_DATA) || (this->type == VALUE_TYPE_DATA_FREE)) {
            return this->value.data.pData;
        }
        else {
            return NULL;
        }
    }


    uint32_t        Value_getDataLen (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if ((this->type == VALUE_TYPE_DATA) || (this->type == VALUE_TYPE_DATA_FREE)){
            return this->value.data.length;
        }
        else {
            return 0;
        }
    }


    bool            Value_setData (
        VALUE_DATA      *this,
        uint32_t        length,
        void            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.data.pData = pValue;
        this->value.data.length  = length;
        this->type = VALUE_TYPE_DATA;

        return true;
    }


    bool            Value_setDataFree (
        VALUE_DATA      *this,
        uint32_t        length,
        void            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.data.pData = mem_Malloc(length);
        if (NULL == this->value.data.pData) {
            return false;
        }
        memmove(this->value.data.pData, pValue, length);
        this->value.data.length  = length;
        this->type = VALUE_TYPE_DATA_FREE;

        return true;
    }



    //---------------------------------------------------------------
    //                          D o u b l e
    //---------------------------------------------------------------

    double          Value_getDouble (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_DOUBLE) {
            return this->value.flt;
        }
        else {
            return 0;
        }
    }


    bool            Value_setDouble (
        VALUE_DATA      *this,
        double          value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.flt = value;
        this->type = VALUE_TYPE_DOUBLE;

        return true;
    }



    //---------------------------------------------------------------
    //                        M i s c 1 6
    //---------------------------------------------------------------

    uint16_t        Value_getMisc16 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->misc16;
    }


    bool            Value_setMisc16 (
        VALUE_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->misc16 = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          I n t 8
    //---------------------------------------------------------------

    int8_t          Value_getI8 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_INT8) {
            return this->value.i8;
        }
        else {
            return 0;
        }
    }


    bool            Value_setI8 (
        VALUE_DATA      *this,
        int8_t          value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.i8 = value;
        this->type = VALUE_TYPE_INT8;

        return true;
    }



    //---------------------------------------------------------------
    //                          I n t 1 6
    //---------------------------------------------------------------

    int16_t         Value_getI16 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_INT16) {
            return this->value.i16;
        }
        else {
            return 0;
        }
    }


    bool            Value_setI16 (
        VALUE_DATA      *this,
        int16_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.i16 = value;
        this->type = VALUE_TYPE_INT16;

        return true;
    }



    //---------------------------------------------------------------
    //                          I n t 3 2
    //---------------------------------------------------------------

    int32_t         Value_getI32 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_INT32) {
            return this->value.i32;
        }
        else {
            return 0;
        }
    }


    bool            Value_setI32 (
        VALUE_DATA      *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.i32 = value;
        this->type = VALUE_TYPE_INT32;

        return true;
    }



    //---------------------------------------------------------------
    //                          I n t 6 4
    //---------------------------------------------------------------

    int64_t         Value_getI64 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_INT64) {
            return this->value.i64;
        }
        else {
            return 0;
        }
    }


    bool            Value_setI64 (
        VALUE_DATA      *this,
        int64_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.i64 = value;
        this->type = VALUE_TYPE_INT64;

        return true;
    }



    //---------------------------------------------------------------
    //                          O b j e c t
    //---------------------------------------------------------------

    OBJ_DATA *      Value_getObject (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->type == VALUE_TYPE_OBJECT) {
            return this->value.pObject;
        }
        else {
            return OBJ_NIL;
        }
    }


    bool            Value_setObject (
        VALUE_DATA      *this,
        OBJ_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        Value_FreeData(this);
        this->value.pObject = pValue;
        this->type = VALUE_TYPE_OBJECT;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Value_getSize (
        VALUE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Value_getSuperVtbl (
        VALUE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------

    uint16_t        Value_getType (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->type;
    }


    bool            Value_setType (
        VALUE_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->type = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          U i n t 8
    //---------------------------------------------------------------

    uint8_t         Value_getU8 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_UINT8) {
            return this->value.u8;
        }
        else {
            return 0;
        }
    }


    bool            Value_setU8 (
        VALUE_DATA      *this,
        uint8_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.u8 = value;
        this->type = VALUE_TYPE_UINT8;

        return true;
    }



    //---------------------------------------------------------------
    //                          U i n t 1 6
    //---------------------------------------------------------------

    uint16_t        Value_getU16 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_UINT16) {
            return this->value.u16;
        }
        else {
            return 0;
        }
    }


    bool            Value_setU16 (
        VALUE_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.u16 = value;
        this->type = VALUE_TYPE_UINT16;

        return true;
    }



    //---------------------------------------------------------------
    //                          U i n t 3 2
    //---------------------------------------------------------------

    uint32_t        Value_getU32 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_UINT32) {
            return this->value.u16;
        }
        else {
            return 0;
        }
    }


    bool            Value_setU32 (
        VALUE_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.u32 = value;
        this->type = VALUE_TYPE_UINT32;

        return true;
    }



    //---------------------------------------------------------------
    //                          U i n t 6 4
    //---------------------------------------------------------------

    uint64_t        Value_getU64 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_UINT64) {
            return this->value.u64;
        }
        else {
            return 0;
        }
    }


    bool            Value_setU64 (
        VALUE_DATA      *this,
        uint64_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.u64 = value;
        this->type = VALUE_TYPE_UINT64;

        return true;
    }



    //---------------------------------------------------------------
    //                          U s e r
    //---------------------------------------------------------------

    uint32_t        Value_getUser (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->user;
    }


    bool            Value_setUser (
        VALUE_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->user = value;

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
        ERESULT eRc = Value_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another VALUE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Value_Assign (
        VALUE_DATA		*this,
        VALUE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Value_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        Value_FreeData(pOther);

        // Create a copy of objects and areas in this object placing
        // them in other.
        switch (this->type) {

            case VALUE_TYPE_DOUBLE:
                pOther->value.flt = this->value.flt;
                break;

            case VALUE_TYPE_INT8:
                pOther->value.i8 = this->value.i8;
                break;

            case VALUE_TYPE_INT16:
                pOther->value.i16 = this->value.i16;
                break;

            case VALUE_TYPE_INT32:
                pOther->value.i32 = this->value.i32;
                break;

            case VALUE_TYPE_INT64:
                pOther->value.i64 = this->value.i64;
                break;

            case VALUE_TYPE_UINT8:
                pOther->value.u8 = this->value.u8;
                break;

            case VALUE_TYPE_UINT16:
                pOther->value.u16 = this->value.u16;
                break;

            case VALUE_TYPE_UINT32:
                pOther->value.u32 = this->value.u32;
                break;

            case VALUE_TYPE_UINT64:
                pOther->value.u64 = this->value.u64;
                break;

            case VALUE_TYPE_OBJECT:
                if (this->value.pObject) {
                    if (obj_getVtbl(this->value.pObject)->pCopy) {
                        pOther->value.pObject =
                            obj_getVtbl(this->value.pObject)->pCopy(this->value.pObject);
                    }
                    else {
                        obj_Retain(this->value.pObject);
                        pOther->value.pObject = this->value.pObject;
                    }
                }
                break;

            case VALUE_TYPE_DATA:
                pOther->value.data.pData = this->value.data.pData;
                pOther->value.data.length = this->value.data.length;
                break;

            case VALUE_TYPE_DATA_FREE:
                pOther->value.data.pData = mem_Malloc(this->value.data.length);
                if (NULL == this->value.data.pData) {
                    return ERESULT_OUT_OF_MEMORY;
                }
                memmove(
                        pOther->value.data.pData,
                        this->value.data.pData,
                        this->value.data.length
                );
                pOther->value.data.length = this->value.data.length;
                break;

            default:
                break;
        }
        pOther->type = this->type;
        pOther->user = this->user;

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
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
    ERESULT         Value_Compare (
        VALUE_DATA     *this,
        VALUE_DATA     *pOther
    )
    {
        int             iRc = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Value_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        switch (this->type) {

            case VALUE_TYPE_DOUBLE:
                iRc = (int)(this->value.flt - pOther->value.flt);
                break;

            case VALUE_TYPE_INT8:
                iRc = this->value.i8 - pOther->value.i8;
                break;

            case VALUE_TYPE_INT16:
                iRc = this->value.i16 - pOther->value.i16;
                break;

            case VALUE_TYPE_INT32:
                iRc = this->value.i32 - pOther->value.i32;
                break;

            case VALUE_TYPE_INT64:
                iRc = (int)(this->value.i64 - pOther->value.i64);
                break;

            case VALUE_TYPE_UINT8:
                iRc = this->value.u8 - pOther->value.u8;
                break;

            case VALUE_TYPE_UINT16:
                iRc = this->value.u16 - pOther->value.u16;
                break;

            case VALUE_TYPE_UINT32:
                iRc = this->value.u32 - pOther->value.u32;
                break;

            case VALUE_TYPE_UINT64:
                iRc = (int)(this->value.u64 - pOther->value.u64);
                break;

            case VALUE_TYPE_OBJECT:
                if (this->value.pObject) {
                    if (obj_getVtbl(this->value.pObject)->pCompare
                        && obj_getVtbl(pOther->value.pObject)->pCompare) {
                        eRc = obj_getVtbl(this->value.pObject)->pCompare(this, pOther);
                        return eRc;
                    }
                }
                break;

            case VALUE_TYPE_DATA:
            case VALUE_TYPE_DATA_FREE:
                iRc = this->value.data.length - pOther->value.data.length;
                if (0 == iRc) {
                    iRc =   memcmp(
                                 this->value.data.pData,
                                 pOther->value.data.pData,
                                 this->value.data.length
                            );
                }
                break;

            default:
                break;
        }

        
        if (iRc < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (iRc > 0) {
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
        Value      *pCopy = Value_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a VALUE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    VALUE_DATA *     Value_Copy (
        VALUE_DATA       *this
    )
    {
        VALUE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Value_New( );
        if (pOther) {
            eRc = Value_Assign(this, pOther);
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

    void            Value_Dealloc (
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
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((VALUE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Value_FreeData(this);

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

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Value_Disable (
        VALUE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Value_Validate(this)) {
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
    ERESULT         Value_Enable (
        VALUE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Value_Validate(this)) {
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
    //                          I n i t
    //---------------------------------------------------------------

    VALUE_DATA *   Value_Init (
        VALUE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(VALUE_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_VALUE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Value_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

    #ifdef NDEBUG
    #else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "Value::sizeof(VALUE_DATA) = %lu\n", sizeof(VALUE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(VALUE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Value_IsEnabled (
        VALUE_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
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
        void        *pMethod = Value_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Value", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Value_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        VALUE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(VALUE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Value_Class();
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
                            return Value_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Value_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Value_ToDebugString;
                        }
#ifdef  VALUE_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Value_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Value_ToDebugString)
                    return "ToDebugString";
#ifdef  VALUE_JSON_SUPPORT
                if (pData == Value_ToJson)
                    return "ToJson";
#endif
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
        ASTR_DATA      *pDesc = Value_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Value_ToDebugString (
        VALUE_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
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
                    Value_getSize(this),
                    obj_getRetainCount(this)
            );

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
    bool            Value_Validate (
        VALUE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_VALUE))
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


        if (!(obj_getSize(this) >= sizeof(VALUE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


