// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NetHTTPA.c
 *  Generated 07/07/2021 09:55:22
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
#include        <NetHTTPA_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            NetHTTPA_task_body (
        void            *pData
    )
    {
        //NETHTTPA_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NETHTTPA_DATA *     NetHTTPA_Alloc (
        void
    )
    {
        NETHTTPA_DATA       *this;
        uint32_t        cbSize = sizeof(NETHTTPA_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NETHTTPA_DATA *     NetHTTPA_New (
        void
    )
    {
        NETHTTPA_DATA       *this;
        
        this = NetHTTPA_Alloc( );
        if (this) {
            this = NetHTTPA_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                           B o d y
    //---------------------------------------------------------------

    VALUE_DATA *    NetHTTPA_getBody (
        NETHTTPA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pBody;
    }


    bool            NetHTTPA_setBody (
        NETHTTPA_DATA   *this,
        VALUE_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pBody) {
            obj_Release(this->pBody);
        }
        this->pBody = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          C o d e
    //---------------------------------------------------------------

    uint16_t        NetHTTPA_getCode (
        NETHTTPA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->code;
    }


    bool            NetHTTPA_setCode (
        NETHTTPA_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->code = value;

        return true;
    }



    //---------------------------------------------------------------
    //                 M a j o r  R e l e a s e
    //---------------------------------------------------------------

    uint16_t        NetHTTPA_getMajorRelease (
        NETHTTPA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->majRel;
    }


    bool            NetHTTPA_setMajorRelease (
        NETHTTPA_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->majRel = value;

        return true;
    }



    //---------------------------------------------------------------
    //                  M i m e  T y p e
    //---------------------------------------------------------------

    ASTR_DATA *     NetHTTPA_getMimeType (
        NETHTTPA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pMimeType;
    }


    bool            NetHTTPA_setMimeType (
        NETHTTPA_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pMimeType) {
            obj_Release(this->pMimeType);
        }
        this->pMimeType = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                 M i n o r  R e l e a s e
    //---------------------------------------------------------------

    uint16_t        NetHTTPA_getMinorRelease (
        NETHTTPA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->minRel;
    }


    bool            NetHTTPA_setMinorRelease (
        NETHTTPA_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->minRel = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        NetHTTPA_getPriority (
        NETHTTPA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NetHTTPA_setPriority (
        NETHTTPA_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        NetHTTPA_getSize (
        NETHTTPA_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NetHTTPA_getSuperVtbl (
        NETHTTPA_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
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
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = NetHTTPA_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NETHTTPA object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NetHTTPA_Assign (
        NETHTTPA_DATA       *this,
        NETHTTPA_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NetHTTPA_Validate(pOther)) {
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
    int             NetHTTPA_Compare (
        NETHTTPA_DATA     *this,
        NETHTTPA_DATA     *pOther
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
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!NetHTTPA_Validate(pOther)) {
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
        NetHTTPA      *pCopy = NetHTTPA_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NETHTTPA object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NETHTTPA_DATA *     NetHTTPA_Copy (
        NETHTTPA_DATA       *this
    )
    {
        NETHTTPA_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef NETHTTPA_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = NetHTTPA_New( );
        if (pOther) {
            eRc = NetHTTPA_Assign(this, pOther);
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

    void            NetHTTPA_Dealloc (
        OBJ_ID          objId
    )
    {
        NETHTTPA_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NETHTTPA_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NetHTTPA_setBody(this, OBJ_NIL);
        NetHTTPA_setMimeType(this, OBJ_NIL);

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
        NetHTTPA      *pDeepCopy = NetHTTPA_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NETHTTPA object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NETHTTPA_DATA *     NetHTTPA_DeepyCopy (
        NETHTTPA_DATA       *this
    )
    {
        NETHTTPA_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NetHTTPA_New( );
        if (pOther) {
            eRc = NetHTTPA_Assign(this, pOther);
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
    ERESULT         NetHTTPA_Disable (
        NETHTTPA_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
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
    ERESULT         NetHTTPA_Enable (
        NETHTTPA_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
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
    //                          I n i t
    //---------------------------------------------------------------

    NETHTTPA_DATA *   NetHTTPA_Init (
        NETHTTPA_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NETHTTPA_DATA);
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
        // in the OBJ_INFO at the end of NetHTTPA_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NETHTTPA);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NetHTTPA_Vtbl);
#ifdef  NETHTTPA_JSON_SUPPORT
        JsonIn_RegisterClass(NetHTTPA_Class());
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
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "NetHTTPA::sizeof(NETHTTPA_DATA) = %lu\n", 
                sizeof(NETHTTPA_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NETHTTPA_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NetHTTPA_IsEnabled (
        NETHTTPA_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
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
        void        *pMethod = NetHTTPA_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NetHTTPA", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NetHTTPA_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NETHTTPA_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NETHTTPA_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NetHTTPA_Class();
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
                            return NetHTTPA_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NetHTTPA_Enable;
                        }
                        break;

                    case 'P':
#ifdef  NETHTTPA_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return NetHTTPA_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return NetHTTPA_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NetHTTPA_ToDebugString;
                        }
#ifdef  NETHTTPA_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return NetHTTPA_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return NetHTTPA_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NetHTTPA_ToDebugString)
                    return "ToDebugString";
#ifdef  NETHTTPA_JSON_SUPPORT
                if (pData == NetHTTPA_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e t u p
    //---------------------------------------------------------------

    ERESULT         NetHTTPA_Setup (
        NETHTTPA_DATA   *this,
        uint16_t        code,
        uint16_t        majRel,
        uint16_t        minRel,
        const
        char            *pMimeTypeA,
        VALUE_DATA      *pBody
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (0 == strcmp(pMimeTypeA, "html"))
            ;
        else if (0 == strcmp(pMimeTypeA, "gif"))
            ;
        else if (0 == strcmp(pMimeTypeA, "jpeg"))
            ;
        else if (0 == strcmp(pMimeTypeA, "png"))
            ;
        else if (0 == strcmp(pMimeTypeA, "text"))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        this->code = code;
        this->majRel = majRel;
        this->minRel = minRel;

        NetHTTPA_setBody(this, OBJ_NIL);
        if (pBody) {
            obj_Retain(pBody);
            this->pBody = pBody;
        }

        NetHTTPA_setMimeType(this, OBJ_NIL);
        if (pMimeTypeA) {
            this->pMimeType = AStr_NewA(pMimeTypeA);
            if (OBJ_NIL == this->pMimeType) {
                eRc = ERESULT_OUT_OF_MEMORY;
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NetHTTPA_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetHTTPA_ToDebugString (
        NETHTTPA_DATA      *this,
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
        if (!NetHTTPA_Validate(this)) {
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
                    NetHTTPA_getSize(this),
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
    
    
    ASTR_DATA *     NetHTTPA_ToString (
        NETHTTPA_DATA   *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        uint32_t        i;
        uint32_t        size;
        const
        uint8_t         *pData8;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }

        eRc = AStr_AppendPrint(
                    pStr,
                    "%d HTTP/%d.%d\n\r",
                    this->code,
                    this->majRel,
                    this->minRel
            );

        if (this->pMimeType) {
            if (0 == AStr_CompareA(this->pMimeType, "gif")) {
                eRc = AStr_AppendPrint(pStr, "Content-Type: image/gif\n\r");
            }
            else if (0 == AStr_CompareA(this->pMimeType, "html")) {
                eRc = AStr_AppendPrint(pStr, "Content-Type: text/html\n\r");
            }
            else if (0 == AStr_CompareA(this->pMimeType, "jpeg")) {
                eRc = AStr_AppendPrint(pStr, "Content-Type: image/jpeg\n\r");
            }
            else if (0 == AStr_CompareA(this->pMimeType, "png")) {
                eRc = AStr_AppendPrint(pStr, "Content-Type: image/png\n\r");
            }
            else if (0 == AStr_CompareA(this->pMimeType, "text")) {
                eRc = AStr_AppendPrint(pStr, "Content-Type: text/plain\n\r");
            }
        }

        if (this->pBody) {
            size = Value_getDataLen(this->pBody);
            eRc = AStr_AppendPrint(pStr, "Content-Length: %d\n\r\n\r", size);
            pData8 = Value_getData(this->pBody);
            for (i=0; i<size; i++) {
                eRc = AStr_AppendPrint(pStr, "%c", *pData8++);
            }
        }

        eRc = AStr_AppendPrint(pStr, "\n\r");

        return pStr;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            NetHTTPA_Validate (
        NETHTTPA_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NETHTTPA))
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


        if (!(obj_getSize(this) >= sizeof(NETHTTPA_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


