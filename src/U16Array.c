// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   U16Array.c
 *	Generated 02/18/2020 11:52:34
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
#include        <U16Array_internal.h>
#include        <file.h>
#include        <Path_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            U16Array_task_body (
        void            *pData
    )
    {
        //U16ARRAY_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    U16ARRAY_DATA *     U16Array_Alloc (
        void
    )
    {
        U16ARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(U16ARRAY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    U16ARRAY_DATA *     U16Array_New (
        void
    )
    {
        U16ARRAY_DATA       *this;
        
        this = U16Array_Alloc( );
        if (this) {
            this = U16Array_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                            A r r a y
    //---------------------------------------------------------------

    ARRAY_DATA *    U16Array_getArray (
        U16ARRAY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (ARRAY_DATA *)this;
    }



    //---------------------------------------------------------------
    //                      B i g  E n d i a n
    //---------------------------------------------------------------
    
    bool            U16Array_getBigEndian (
        U16ARRAY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->fBigEndian;
    }


    bool            U16Array_setBigEndian (
        U16ARRAY_DATA   *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value)
            this->fBigEndian = 1;
        else
            this->fBigEndian = 0;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        U16Array_getSize (
        U16ARRAY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return array_getSize((ARRAY_DATA *)this);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  U16Array_getSuperVtbl (
        U16ARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
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
    //                       A p p e n d
    //---------------------------------------------------------------

    ERESULT         U16Array_AppendData (
        U16ARRAY_DATA    *this,
        uint16_t        data
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Array_Validate(this) ) {
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


    ERESULT         U16Array_AppendFile(
        U16ARRAY_DATA    *this,
        PATH_DATA       *pPath
    )
    {
        int64_t         size = 0;
        int             chr;
        FILE            *pFile;
        uint16_t        data;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Array_Validate(this) ) {
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
            if (this->fBigEndian) {
                data = (chr & 0xFF) << 8;
            }
            else {
                data = chr & 0xFF;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (this->fBigEndian) {
                data |= chr & 0xFF;
            }
            else {
                data |= (chr & 0xFF) << 8;
            }
            U16Array_AppendData(this, data);
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
        ERESULT eRc = U16Array_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another U16ARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         U16Array_Assign (
        U16ARRAY_DATA		*this,
        U16ARRAY_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!U16Array_Validate(pOther)) {
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
    ERESULT         U16Array_Compare (
        U16ARRAY_DATA     *this,
        U16ARRAY_DATA     *pOther
    )
    {
        int             i = 0;
        int             iMax;

#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!U16Array_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (U16Array_getSize(this) == U16Array_getSize(pOther))
            ;
        else {
            return ERESULT_SUCCESS_UNEQUAL;
        }

        iMax = U16Array_getSize(this);
        for (i=0; i<iMax; i++) {
            if (U16Array_Get(this, i+1) == U16Array_Get(pOther, i+1))
                ;
            else {
                return ERESULT_SUCCESS_UNEQUAL;
            }
        }

        return ERESULT_SUCCESS_EQUAL;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        U16Array      *pCopy = U16Array_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a U16ARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    U16ARRAY_DATA *     U16Array_Copy (
        U16ARRAY_DATA       *this
    )
    {
        U16ARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef U16ARRAY_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = U16Array_New( );
        if (pOther) {
            eRc = U16Array_Assign(this, pOther);
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

    void            U16Array_Dealloc (
        OBJ_ID          objId
    )
    {
        U16ARRAY_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((U16ARRAY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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
        U16Array      *pDeepCopy = U16Array_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a U16ARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    U16ARRAY_DATA *     U16Array_DeepyCopy (
        U16ARRAY_DATA       *this
    )
    {
        U16ARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = U16Array_New( );
        if (pOther) {
            eRc = U16Array_Assign(this, pOther);
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

    uint16_t         U16Array_Delete (
        U16ARRAY_DATA    *this,
        uint32_t        index
    )
    {
        uint16_t        data = 0;
        uint16_t        *pData;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Array_Validate(this) ) {
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


    uint16_t         U16Array_DeleteFirst (
        U16ARRAY_DATA    *this
    )
    {
        uint16_t        data = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        data = U16Array_Delete(this, 1);

        // Return to caller.
        return data;
    }


    uint16_t         U16Array_DeleteLast (
        U16ARRAY_DATA    *this
    )
    {
        uint16_t        data = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        data = U16Array_Delete(this, array_getSize((ARRAY_DATA *)this));

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
    ERESULT         U16Array_Disable (
        U16ARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
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
    ERESULT         U16Array_Enable (
        U16ARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
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

    uint16_t         U16Array_Get (
        U16ARRAY_DATA    *this,
        uint32_t        index
    )
    {
        uint16_t        data;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Array_Validate(this) ) {
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

        data = *((uint16_t *)array_Ptr((ARRAY_DATA *)this, index));

        return data;
    }


    uint16_t        U16Array_GetFirst (
        U16ARRAY_DATA    *this
    )
    {
        uint16_t        data;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        data = U16Array_Get(this, 1);

        return data;
    }


    uint16_t         U16Array_GetLast (
        U16ARRAY_DATA    *this
    )
    {
        uint16_t        data;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        data = U16Array_Get(this, array_getSize((ARRAY_DATA *)this));

        return data;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    U16ARRAY_DATA *   U16Array_Init (
        U16ARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(U16ARRAY_DATA);
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
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&U16Array_Vtbl);
        
        array_setElemSize((ARRAY_DATA *)this, 2);
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
        if (!U16Array_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "U16Array::sizeof(U16ARRAY_DATA) = %lu\n", 
                sizeof(U16ARRAY_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(U16ARRAY_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------

    ERESULT         U16Array_Insert (
        U16ARRAY_DATA   *this,
        uint32_t        index,
        uint16_t        data
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Array_Validate(this) ) {
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
        return ERESULT_SUCCESSFUL_COMPLETION;
    }



    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         U16Array_IsEnabled (
        U16ARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
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
        void        *pMethod = U16Array_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "U16Array", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          U16Array_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        U16ARRAY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(U16ARRAY_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)U16Array_Class();
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
                            return U16Array_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return U16Array_Enable;
                        }
                        break;

#ifdef  U16ARRAY_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return U16Array_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return U16Array_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return U16Array_ToDebugString;
                        }
#ifdef  U16ARRAY_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return U16Array_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == U16Array_ToDebugString)
                    return "ToDebugString";
#ifdef  U16ARRAY_JSON_SUPPORT
                if (pData == U16Array_ToJson)
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

    ERESULT         U16Array_SetData (
        U16ARRAY_DATA   *this,
        uint32_t        index,
        uint16_t        data
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Array_Validate(this) ) {
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

        *((uint16_t *)array_Ptr((ARRAY_DATA *)this, index)) = data;

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
        ASTR_DATA      *pDesc = U16Array_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     U16Array_ToDebugString (
        U16ARRAY_DATA   *this,
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
        uint16_t        *pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Array_Validate(this)) {
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
                    "{%p(%s) size=%d retain=%d data=[\n",
                    this,
                    pInfo->pClassName,
                    U16Array_getSize(this),
                    obj_getRetainCount(this)
            );

        jMax = array_getSize((ARRAY_DATA *)this);
        pData = array_Ptr((ARRAY_DATA *)this, 1);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        if (jMax) {
            for (j=0; j<(jMax-1); ++j) {
                if ((j % 8) == 0) {
                    if (j != 0) {
                        AStr_AppendA(pStr, "\n");
                    }
                    if (indent) {
                        AStr_AppendCharRepeatA(pStr, indent, ' ');
                    }
                    AStr_AppendA(pStr, "\t");
                }
                AStr_AppendPrint(pStr, "%u,", *pData++);
            }
            if ((j % 8) == 0) {
                if (j != 0) {
                    AStr_AppendA(pStr, "\n");
                }
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                AStr_AppendA(pStr, "\t");
            }
            AStr_AppendPrint(pStr, "%u]\n", *pData);
        }

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
    bool            U16Array_Validate (
        U16ARRAY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_U16ARRAY))
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


        if (!(obj_getSize(this) >= sizeof(U16ARRAY_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                  W r i t e  T o  F i l e
    //---------------------------------------------------------------

    ERESULT         U16Array_WriteToFile (
        U16ARRAY_DATA   *this,
        PATH_DATA       *pPath
    )
    {
        FILE            *pFile;
        uint32_t        index = 0;
        uint32_t        size;
        uint16_t        *pData;
        uint16_t        data;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !Path_Validate(pPath) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pData = (uint16_t *)array_getData((ARRAY_DATA *)this);
        size = array_getSize((ARRAY_DATA *)this);
        pFile = fopen(Path_getData(pPath), "w");
        if (NULL == pFile) {
            return ERESULT_OPEN_ERROR;
        }
        while ( index < size ) {
            data = pData[index++];
            if (this->fBigEndian) {
                fputc(((data >> 8) & 0xFF), pFile);
                fputc((data & 0xFF), pFile);
            }
            else {
                fputc((data & 0xFF), pFile);
                fputc(((data >> 8) & 0xFF), pFile);
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


