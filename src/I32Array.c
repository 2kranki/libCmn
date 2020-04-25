// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   I32Array.c
 *	Generated 01/14/2020 18:29:58
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
#include        <I32Array_internal.h>
#include        <file.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            I32Array_task_body (
        void            *pData
    )
    {
        //I32ARRAY_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    I32ARRAY_DATA *     I32Array_Alloc (
        void
    )
    {
        I32ARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(I32ARRAY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    I32ARRAY_DATA *     I32Array_New (
        void
    )
    {
        I32ARRAY_DATA       *this;
        
        this = I32Array_Alloc( );
        if (this) {
            this = I32Array_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      B i g  E n d i a n
    //---------------------------------------------------------------

    bool            I32Array_setBigEndian(
        I32ARRAY_DATA   *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        obj_FlagSet(this, I32ARRAY_FLAG_BIGENDIAN, value);

        return true;
    }



    //---------------------------------------------------------------
    //                           D a t a
    //---------------------------------------------------------------

    int32_t *       I32Array_getData(
        I32ARRAY_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return array_Ptr((ARRAY_DATA *)this, 1);
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        I32Array_getSize (
        I32ARRAY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!I32Array_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return array_getSize((ARRAY_DATA *)this);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  I32Array_getSuperVtbl (
        I32ARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!I32Array_Validate(this)) {
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
    //                          A p p e n d
    //---------------------------------------------------------------

    ERESULT         I32Array_AppendData(
        I32ARRAY_DATA   *this,
        int32_t         data
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc =   array_InsertData(
                                 (ARRAY_DATA *)this,
                                 (array_getSize((ARRAY_DATA *)this) + 1),
                                 1,
                                 &data
                );
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         I32Array_AppendFile(
        I32ARRAY_DATA   *this,
        PATH_DATA       *pPath
    )
    {
        int64_t         size = 0;
        int             chr;
        FILE            *pFile;
        int32_t         data;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        size = file_SizeA(Path_getData(pPath));
        if (-1 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        if (0 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }

        pFile = fopen(Path_getData(pPath), "rb");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( !feof(pFile) ) {
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, I32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF) << 24;
            }
            else {
                data = chr & 0xFF;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, I32ARRAY_FLAG_BIGENDIAN)) {
                data |= (chr & 0xFF) << 16;
            }
            else {
                data |= (chr & 0xFF) << 8;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, I32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF) << 8;
            }
            else {
                data |= (chr & 0xFF) << 16;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, I32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF);
            }
            else {
                data |= (chr & 0xFF) << 24;
            }
            I32Array_AppendData(this, data);
        }
        fclose(pFile);
        pFile = NULL;

        // Return to caller.
        return ERESULT_SUCCESS;
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
        ERESULT eRc = I32Array_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another I32ARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         I32Array_Assign (
        I32ARRAY_DATA		*this,
        I32ARRAY_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!I32Array_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!I32Array_Validate(pOther)) {
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
    ERESULT         I32Array_Compare (
        I32ARRAY_DATA     *this,
        I32ARRAY_DATA     *pOther
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
        if (!I32Array_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!I32Array_Validate(pOther)) {
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
        I32Array      *pCopy = I32Array_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a I32ARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    I32ARRAY_DATA *     I32Array_Copy (
        I32ARRAY_DATA       *this
    )
    {
        I32ARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!I32Array_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = I32Array_New( );
        if (pOther) {
            eRc = I32Array_Assign(this, pOther);
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

    void            I32Array_Dealloc (
        OBJ_ID          objId
    )
    {
        I32ARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!I32Array_Validate(this)) {
            DEBUG_BREAK();
            return;
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
        I32Array      *pDeepCopy = I32Array_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a I32ARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    I32ARRAY_DATA *     I32Array_DeepyCopy (
        I32ARRAY_DATA       *this
    )
    {
        I32ARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!I32Array_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = I32Array_New( );
        if (pOther) {
            eRc = I32Array_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------

    int32_t         I32Array_Delete(
        I32ARRAY_DATA   *this,
        uint32_t        index
    )
    {
        int32_t         data = 0;
        uint32_t        *pData;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if ((index > 0) && (index <= array_getSize((ARRAY_DATA *)this)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pData = array_Ptr((ARRAY_DATA *)this, index);
        if (pData) {
            data = *pData;
            eRc = array_Delete((ARRAY_DATA *)this, index, 1);
            if (ERESULT_HAS_FAILED(eRc)) {
                return 0;
            }
        }

        // Return to caller.
        return data;
    }


    int32_t         I32Array_DeleteFirst(
        I32ARRAY_DATA   *this
    )
    {
        int32_t         data = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        data = I32Array_Delete(this, 1);

        // Return to caller.
        return data;
    }


    int32_t         I32Array_DeleteLast(
        I32ARRAY_DATA   *this
    )
    {
        int32_t         data = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        data = I32Array_Delete(this, array_getSize((ARRAY_DATA *)this));

        // Return to caller.
        return data;
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
    ERESULT         I32Array_Disable (
        I32ARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!I32Array_Validate(this)) {
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
    ERESULT         I32Array_Enable (
        I32ARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!I32Array_Validate(this)) {
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
    //                         G e t
    //---------------------------------------------------------------

    int32_t         I32Array_Get(
        I32ARRAY_DATA   *this,
        uint32_t        index
    )
    {
        int32_t         data = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if ((index > 0) && (index <= array_getSize((ARRAY_DATA *)this))) {
            data = *((uint32_t *)array_Ptr((ARRAY_DATA *)this, index));
        }

        return data;
    }


    int32_t         I32Array_GetFirst(
        I32ARRAY_DATA   *this
    )
    {
        int32_t         data;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        data = I32Array_Get(this, 1);

        return data;
    }


    int32_t         I32Array_GetLast(
        I32ARRAY_DATA   *this
    )
    {
        int32_t         data;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        data = I32Array_Get(this, array_getSize((ARRAY_DATA *)this));

        return data;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    I32ARRAY_DATA *   I32Array_Init (
        I32ARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(I32ARRAY_DATA);
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

        this = (OBJ_ID)array_Init((ARRAY_DATA *)this);          // Needed for Inheritance
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&I32Array_Vtbl);
        array_setElemSize((ARRAY_DATA *)this, sizeof(int32_t));

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
        if (!I32Array_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "I32Array::sizeof(I32ARRAY_DATA) = %lu\n", sizeof(I32ARRAY_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(I32ARRAY_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------

    ERESULT         I32Array_InsertData(
        I32ARRAY_DATA   *this,
        uint32_t        index,
        int32_t         data
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((index > 0) && (index <= array_getSize((ARRAY_DATA *)this)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif

        eRc = array_InsertData((ARRAY_DATA *)this, index, 1, &data);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         I32Array_IsEnabled (
        I32ARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!I32Array_Validate(this)) {
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
        void        *pMethod = I32Array_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "I32Array", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          I32Array_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        I32ARRAY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!I32Array_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(I32ARRAY_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)I32Array_Class();
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
                            return I32Array_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return I32Array_Enable;
                        }
                        break;

#ifdef  I32ARRAY_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return I32Array_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return I32Array_ParseJsonObject;
                        }
                        break;
#endif
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return I32Array_ToDebugString;
                        }
#ifdef  I32ARRAY_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return I32Array_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == I32Array_ToDebugString)
                    return "ToDebugString";
#ifdef  I32ARRAY_JSON_SUPPORT
                if (pData == I32Array_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                            S e t
    //---------------------------------------------------------------

    ERESULT         I32Array_SetData(
        I32ARRAY_DATA   *this,
        uint32_t        index,
        int32_t         data
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if ((index > 0) && (index <= array_getSize((ARRAY_DATA *)this)))
            ;
        else {
            eRc =   array_AppendSpacing(
                                      (ARRAY_DATA *)this,
                                      (index - array_getSize((ARRAY_DATA *)this))
                    );
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
        }

        *((int32_t *)array_Ptr((ARRAY_DATA *)this, index)) = data;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          S o r t
    //---------------------------------------------------------------

    ERESULT         I32Array_SortAscending(
        I32ARRAY_DATA   *this
    )
    {
        uint32_t        i;
        uint32_t        j;
        uint32_t        size = array_getSize((ARRAY_DATA *)this);
        int32_t         *pJ0;
        int32_t         *pJ1;
        int32_t         wrk;

        /*      Insertion Sort from Wikipedia
         *
         *  for i = 1 to length(A)
         *      j = i
         *      while j > 0 and A[j-1] > A[j]
         *          swap A[j] and A[j-1]
         *          j = j - 1
         *      end while
         *  end for
         *
         *  NOTE:   indexing is relative to zero.
         *          adjust as necessary.
         */

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (size < 2) {
            return ERESULT_SUCCESS;
        }

        for (i=1; i<size; ++i) {
            j = i;
            while (j > 0) {
                pJ0 = (int32_t *)array_Ptr((ARRAY_DATA *)this, j);
                pJ1 = (int32_t *)array_Ptr((ARRAY_DATA *)this, j+1);
                if (*pJ0 > *pJ1)
                    ;
                else
                    break;
                wrk = *pJ0;
                *pJ0 = *pJ1;
                *pJ1 = wrk;
                j = j - 1;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = I32Array_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     I32Array_ToDebugString (
        I32ARRAY_DATA   *this,
        int             indent
    )
    {
        ERESULT         eRc;
        int             j;
        int             jMax;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        int32_t         *pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!I32Array_Validate(this)) {
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
                    I32Array_getSize(this),
                    obj_getRetainCount(this)
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        jMax = array_getSize((ARRAY_DATA *)this);
        pData = array_Ptr((ARRAY_DATA *)this, 1);
        if (jMax) {
            for (j=0; j<(jMax-1); ++j) {
                if ((j % 5) == 0) {
                    AStr_AppendA(pStr, "\n");
                    if (indent) {
                        AStr_AppendCharRepeatA(pStr, indent, ' ');
                    }
                }
                AStr_AppendPrint(pStr, "%d,", *pData++);
            }
            if ((j % 5) == 0) {
                AStr_AppendA(pStr, "\n");
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
            }
            AStr_AppendPrint(pStr, "%d\n", *pData++);
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
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            I32Array_Validate (
        I32ARRAY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_I32ARRAY))
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


        if (!(obj_getSize(this) >= sizeof(I32ARRAY_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                  W r i t e  T o  F i l e
    //---------------------------------------------------------------

    ERESULT         I32Array_WriteToFile(
        I32ARRAY_DATA   *this,
        PATH_DATA       *pPath
    )
    {
        FILE            *pFile;
        //uint32_t        index = 0;
        uint32_t        size;
        int32_t         *pData;
        int32_t         data;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !Path_Validate(pPath) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pData = (int32_t *)array_getData((ARRAY_DATA *)this);
        size = array_getSize((ARRAY_DATA *)this);
        pFile = fopen(Path_getData(pPath), "w");
        if (NULL == pFile) {
            return ERESULT_OPEN_ERROR;
        }
        while ( size-- ) {
            data = *pData++;
            if (obj_Flag(this, I32ARRAY_FLAG_BIGENDIAN)) {
                fputc(((data >> 24) & 0xFF), pFile);
                fputc(((data >> 16) & 0xFF), pFile);
                fputc(((data >> 8) & 0xFF), pFile);
                fputc((data & 0xFF), pFile);
            }
            else {
                fputc((data & 0xFF), pFile);
                fputc(((data >> 8) & 0xFF), pFile);
                fputc(((data >> 16) & 0xFF), pFile);
                fputc(((data >> 24) & 0xFF), pFile);
            }
        }
        fclose(pFile);
        pFile = NULL;

        // Return to caller.
        return ERESULT_SUCCESS;
    }




    
#ifdef	__cplusplus
}
#endif


