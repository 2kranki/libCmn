// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Number.c
 *  Generated 05/23/11 11:24:01
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
#include        <Number_internal.h>
#include        <dec.h>
#include        <trace.h>






#ifdef  __cplusplus
extern "C" {
#endif
    
    typedef struct Number_type_desc_s {
        uint32_t        type;
        const
        char            *desc;
    } NUMBER_TYPE_DESC;

    static
    NUMBER_TYPE_DESC    descs[] = {
#if defined(__MACOSX_ENV__)  || defined(__MACOS64_ENV__)
        {NUMBER_TYPE_FLOAT, "NUMBER_TYPE_FLOAT"},
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        {NUMBER_TYPE_FLOAT, "NUMBER_TYPE_FLOAT"},
#endif
        {NUMBER_TYPE_INT16, "NUMBER_TYPE_INT16"},
        {NUMBER_TYPE_INT32, "NUMBER_TYPE_INT32"},
        {NUMBER_TYPE_INT64, "NUMBER_TYPE_INT64"},
        {NUMBER_TYPE_UINT16, "NUMBER_TYPE_UINT16"},
        {NUMBER_TYPE_UINT32, "NUMBER_TYPE_UINT32"},
        {NUMBER_TYPE_UINT64, "NUMBER_TYPE_UINT64"},
        {0, NULL}
    };
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Number_task_body (
        void            *pData
    )
    {
        //NUMBER_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NUMBER_DATA *     Number_Alloc (
        void
    )
    {
        NUMBER_DATA       *this;
        uint32_t        cbSize = sizeof(NUMBER_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    uint32_t        Number_DescToType(
        const char      *pValue
    )
    {
        NUMBER_TYPE_DESC  *pDesc = descs;

        while (pDesc->type) {
            if (0 == strcmp(pValue, pDesc->desc))
                return pDesc->type;
            pDesc++;
        }

        return NUMBER_TYPE_UNKNOWN;
    }



    NUMBER_DATA *     Number_New (
        void
    )
    {
        NUMBER_DATA       *this;
        
        this = Number_Alloc( );
        if (this) {
            this = Number_Init(this);
        } 
        return this;
    }


    NUMBER_DATA *   Number_NewA(
        const
        char            *pStr
    )
    {
        NUMBER_DATA     *this;

        this = Number_New( );
        if (this) {
            this->type = NUMBER_TYPE_INT64;
            this->i64 = dec_getInt64A(pStr);
        }
        return this;
    }


    NUMBER_DATA *   Number_NewInt16(
        int16_t         value
    )
    {
        NUMBER_DATA     *this;

        this = Number_New( );
        if (this) {
            this->type = NUMBER_TYPE_INT16;
            this->i16 = value;
        }
        return this;
    }


    NUMBER_DATA *   Number_NewInt32(
        int32_t         value
    )
    {
        NUMBER_DATA     *this;

        this = Number_New( );
        if (this) {
            this->type = NUMBER_TYPE_INT32;
            this->i32 = value;
        }
        return this;
    }


    NUMBER_DATA *   Number_NewInt64(
        int64_t         value
    )
    {
        NUMBER_DATA     *this;

        this = Number_New( );
        if (this) {
            this->type = NUMBER_TYPE_INT64;
            this->i64 = value;
        }
        return this;
    }


    NUMBER_DATA *   Number_NewUint16(
        uint16_t        value
    )
    {
        NUMBER_DATA     *this;

        this = Number_New( );
        if (this) {
            this->type = NUMBER_TYPE_UINT16;
            this->u16 = value;
        }
        return this;
    }


    NUMBER_DATA *   Number_NewUint32(
        uint32_t        value
    )
    {
        NUMBER_DATA     *this;

        this = Number_New( );
        if (this) {
            this->type = NUMBER_TYPE_UINT32;
            this->u32 = value;
        }
        return this;
    }


    NUMBER_DATA *   Number_NewUint64(
        uint64_t        value
    )
    {
        NUMBER_DATA     *this;

        this = Number_New( );
        if (this) {
            this->type = NUMBER_TYPE_UINT64;
            this->u64 = value;
        }
        return this;
    }



    const char *   Number_TypeToDesc(
        uint32_t        value
    )
    {
        NUMBER_TYPE_DESC  *pDesc = descs;

        while (pDesc->type) {
            if (value == pDesc->type)
                return pDesc->desc;
            pDesc++;
        }

        return "NUMBER_TYPE_UNKNOWN";
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Number_getSize (
        NUMBER_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Number_getSuperVtbl (
        NUMBER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                         T y p e
    //---------------------------------------------------------------

    uint16_t        Number_getType (
        NUMBER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->type;
    }


    bool            Number_setType (
        NUMBER_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->type = value;

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
        ERESULT eRc = Number_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NUMBER object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Number_Assign (
        NUMBER_DATA       *this,
        NUMBER_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Number_Validate(pOther)) {
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
        pOther->type     = this->type;
        pOther->u64      = this->u64;

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
    ERESULT         Number_Compare (
        NUMBER_DATA     *this,
        NUMBER_DATA     *pOther
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
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Number_Validate(pOther)) {
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
    
   
     ERESULT         Number_CompareA(
         NUMBER_DATA     *this,
         const
         char            *pOther
     )
     {
         int             i = 0;
         ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
         int64_t         integer;

 #ifdef NDEBUG
 #else
         if( !Number_Validate(this) ) {
             DEBUG_BREAK();
             return ERESULT_INVALID_OBJECT;
         }
         if( NULL == pOther ) {
             DEBUG_BREAK();
             return ERESULT_INVALID_PARAMETER;
         }
 #endif

         integer = dec_getInt64A(pOther);
         switch (this->type) {
             case NUMBER_TYPE_INT16:          // int16_t
                 i = this->i16 - (int16_t)integer;
                 break;

             case NUMBER_TYPE_INT32:          // int32_t
                 i = this->i32 - (int32_t)integer;
                 break;

             case NUMBER_TYPE_INT64:          // int64_t
                 i = (int)(this->i64 - integer);
                 break;

                 //case NUMBER_TYPE_INT128:         // int128_t
             case NUMBER_TYPE_UINT16:         // uint16_t
                 i = this->u16 - (uint16_t)integer;
                 break;

             case NUMBER_TYPE_UINT32:         // uint32_t
                 i = this->u32 - (uint32_t)integer;
                 break;

             case NUMBER_TYPE_UINT64:         // uint64_t
                 i = (int)(this->u64 - integer);
                 break;

             default:
                 break;
         }

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
        Number      *pCopy = Number_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NUMBER object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NUMBER_DATA *     Number_Copy (
        NUMBER_DATA       *this
    )
    {
        NUMBER_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef NUMBER_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Number_New( );
        if (pOther) {
            eRc = Number_Assign(this, pOther);
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

    void            Number_Dealloc (
        OBJ_ID          objId
    )
    {
        NUMBER_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NUMBER_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

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
        Number      *pDeepCopy = Number_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NUMBER object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NUMBER_DATA *     Number_DeepyCopy (
        NUMBER_DATA       *this
    )
    {
        NUMBER_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Number_New( );
        if (pOther) {
            eRc = Number_Assign(this, pOther);
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
    ERESULT         Number_Disable (
        NUMBER_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

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
    ERESULT         Number_Enable (
        NUMBER_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



        //---------------------------------------------------------------
        //                          F l o a t
        //---------------------------------------------------------------

        double          Number_Float(
            NUMBER_DATA     *this
        )
        {

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !Number_Validate( this ) ) {
                DEBUG_BREAK();
            }
    #endif

            if (this->type == NUMBER_TYPE_FLOAT) {
                return this->flt;
            }

            return 0;
        }



        //---------------------------------------------------------------
        //                          I 1 6
        //---------------------------------------------------------------

        int16_t         Number_I16(
            NUMBER_DATA     *this
        )
        {

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !Number_Validate( this ) ) {
                DEBUG_BREAK();
            }
    #endif

            switch (this->type) {
                case NUMBER_TYPE_INT16:
                    return (int16_t)this->i16;
                    break;

                case NUMBER_TYPE_INT32:
                    return (int16_t)this->i32;
                    break;

                case NUMBER_TYPE_INT64:
                    return (int16_t)this->i64;
                    break;

                case NUMBER_TYPE_UINT16:
                    return (int16_t)this->u16;
                    break;

                case NUMBER_TYPE_UINT32:
                    return (int16_t)this->u32;
                    break;

                case NUMBER_TYPE_UINT64:
                    return (int16_t)this->u64;
                    break;

            }

            return 0;
        }



        //---------------------------------------------------------------
        //                          I 3 2
        //---------------------------------------------------------------

        int32_t         Number_I32(
            NUMBER_DATA     *this
        )
        {

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !Number_Validate( this ) ) {
                DEBUG_BREAK();
            }
    #endif

            switch (this->type) {
                case NUMBER_TYPE_INT16:
                    return (int32_t)this->i16;
                    break;

                case NUMBER_TYPE_INT32:
                    return (int32_t)this->i32;
                    break;

                case NUMBER_TYPE_INT64:
                    return (int32_t)this->i64;
                    break;

                case NUMBER_TYPE_UINT16:
                    return (int32_t)this->u16;
                    break;

                case NUMBER_TYPE_UINT32:
                    return (int32_t)this->u32;
                    break;

                case NUMBER_TYPE_UINT64:
                    return (int32_t)this->u64;
                    break;

            }

            return 0;
        }



    //---------------------------------------------------------------
    //                          I 6 4
    //---------------------------------------------------------------

    int64_t         Number_I64(
        NUMBER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Number_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        switch (this->type) {
            case NUMBER_TYPE_INT16:
                return (int64_t)this->i16;
                break;

            case NUMBER_TYPE_INT32:
                return (int64_t)this->i32;
                break;

            case NUMBER_TYPE_INT64:
                return (int64_t)this->i64;
                break;

            case NUMBER_TYPE_UINT16:
                return (int64_t)this->u16;
                break;

            case NUMBER_TYPE_UINT32:
                return (int64_t)this->u32;
                break;

            case NUMBER_TYPE_UINT64:
                return (int64_t)this->u64;
                break;

        }

        return 0;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NUMBER_DATA *   Number_Init (
        NUMBER_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NUMBER_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NUMBER);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Number_Vtbl);
        
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
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Number::sizeof(NUMBER_DATA) = %lu\n", 
                sizeof(NUMBER_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NUMBER_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Number_IsEnabled (
        NUMBER_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
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
        void        *pMethod = Number_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Number", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Number_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NUMBER_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NUMBER_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Number_Class();
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
                            return Number_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Number_Enable;
                        }
                        break;

                    case 'P':
#ifdef  NUMBER_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Number_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Number_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Number_ToDebugString;
                        }
#ifdef  NUMBER_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Number_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Number_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Number_ToDebugString)
                    return "ToDebugString";
#ifdef  NUMBER_JSON_SUPPORT
                if (pData == Number_ToJson)
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
        ASTR_DATA      *pDesc = Number_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Number_ToDebugString (
        NUMBER_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Number_Validate(this)) {
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
                    Number_getSize(this),
                    obj_getRetainCount(this)
            );

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
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        switch (this->type) {

#if defined(__MACOSX_ENV__)  || defined(__MACOS64_ENV__)
            case NUMBER_TYPE_FLOAT:
                AStr_AppendPrint(
                             pStr,
                             "dbl=%e\n",
                             this->flt
                    );
                break;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
            case NUMBER_TYPE_FLOAT:
                AStr_AppendPrint(
                             pStr,
                             "dbl=%e\n",
                             this->flt
                    );
                break;
#endif

            case NUMBER_TYPE_INT16:
                AStr_AppendPrint(
                             pStr,
                             "i16=%d\n",
                             this->i16
                             );
                break;

            case NUMBER_TYPE_INT32:
                AStr_AppendPrint(
                             pStr,
                             "i32=%d\n",
                             this->i32
                             );
                break;

            case NUMBER_TYPE_INT64:
                AStr_AppendPrint(
                             pStr,
                             "i64=%lld\n",
                             this->i64
                             );
                break;

            case NUMBER_TYPE_UINT16:
                AStr_AppendPrint(
                             pStr,
                             "u16=%d\n",
                             this->u16
                             );
                break;

            case NUMBER_TYPE_UINT32:
                AStr_AppendPrint(
                             pStr,
                             "u32=%d\n",
                             this->u32
                             );
                break;

            case NUMBER_TYPE_UINT64:
                AStr_AppendPrint(
                             pStr,
                             "u64=%lld\n",
                             this->u64
                             );
                break;

            default:
                AStr_AppendA(pStr, "unknown number type!\n");
                break;
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
        //                          U 1 6
        //---------------------------------------------------------------

        uint16_t        Number_U16(
            NUMBER_DATA     *this
        )
        {

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !Number_Validate( this ) ) {
                DEBUG_BREAK();
            }
    #endif

            switch (this->type) {
                case NUMBER_TYPE_INT16:
                    return (uint16_t)this->i16;
                    break;

                case NUMBER_TYPE_INT32:
                    return (uint16_t)this->i32;
                    break;

                case NUMBER_TYPE_INT64:
                    return (uint16_t)this->i64;
                    break;

                case NUMBER_TYPE_UINT16:
                    return (uint16_t)this->u16;
                    break;

                case NUMBER_TYPE_UINT32:
                    return (uint16_t)this->u32;
                    break;

                case NUMBER_TYPE_UINT64:
                    return (uint16_t)this->u64;
                    break;

            }

            return 0;
        }



        //---------------------------------------------------------------
        //                          U 3 2
        //---------------------------------------------------------------

        uint32_t        Number_U32(
            NUMBER_DATA     *this
        )
        {

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !Number_Validate( this ) ) {
                DEBUG_BREAK();
            }
    #endif

            switch (this->type) {
                case NUMBER_TYPE_INT16:
                    return (uint32_t)this->i16;
                    break;

                case NUMBER_TYPE_INT32:
                    return (uint32_t)this->i32;
                    break;

                case NUMBER_TYPE_INT64:
                    return (uint32_t)this->i64;
                    break;

                case NUMBER_TYPE_UINT16:
                    return (uint32_t)this->u16;
                    break;

                case NUMBER_TYPE_UINT32:
                    return (uint32_t)this->u32;
                    break;

                case NUMBER_TYPE_UINT64:
                    return (uint32_t)this->u64;
                    break;

            }

            return 0;
        }



    //---------------------------------------------------------------
    //                          U 6 4
    //---------------------------------------------------------------

    uint64_t        Number_U64(
        NUMBER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Number_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        switch (this->type) {
            case NUMBER_TYPE_INT16:
                return (uint64_t)this->i16;
                break;

            case NUMBER_TYPE_INT32:
                return (uint64_t)this->i32;
                break;

            case NUMBER_TYPE_INT64:
                return (uint64_t)this->i64;
                break;

            case NUMBER_TYPE_UINT16:
                return (uint64_t)this->u16;
                break;

            case NUMBER_TYPE_UINT32:
                return (uint64_t)this->u32;
                break;

            case NUMBER_TYPE_UINT64:
                return (uint64_t)this->u64;
                break;

        }

        return 0;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Number_Validate (
        NUMBER_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NUMBER))
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


        if (!(obj_getSize(this) >= sizeof(NUMBER_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


