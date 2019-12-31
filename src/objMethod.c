// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjMethod.c
 *	Generated 12/15/2019 14:20:32
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
#include        <ObjMethod_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            ObjMethod_task_body (
        void            *pData
    )
    {
        //OBJMETHOD_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJMETHOD_DATA *     ObjMethod_Alloc (
        void
    )
    {
        OBJMETHOD_DATA       *this;
        uint32_t        cbSize = sizeof(OBJMETHOD_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJMETHOD_DATA *     ObjMethod_New (
        void
    )
    {
        OBJMETHOD_DATA  *this;
        
        this = ObjMethod_Alloc( );
        if (this) {
            this = ObjMethod_Init(this);
        } 
        return this;
    }



    OBJMETHOD_DATA * ObjMethod_NewObjectA(
        OBJ_ID          pObject,
        const
        char            *pMethodA
    )
    {
        OBJMETHOD_DATA  *this;
        const
        OBJ_INFO        *pInfo;
        OBJ_IUNKNOWN    *pUnk;
        void            *pMethod;

        if (OBJ_NIL == pObject) {
            return OBJ_NIL;
        }
        if (NULL == pMethodA) {
            return OBJ_NIL;
        }
        
        pUnk = obj_getVtbl(pObject);
        if (pUnk && pUnk->pQueryInfo) {
            pMethod =   pUnk->pQueryInfo(
                                         pObject,
                                         OBJ_QUERYINFO_TYPE_METHOD,
                                         (void *)pMethodA
                        );
            if (NULL == pMethod) {
                return OBJ_NIL;
            }
        }
        else {
            return OBJ_NIL;
        }
        pInfo = obj_getInfo(pObject);
        if (NULL == pInfo) {
            return OBJ_NIL;
        }

        this = ObjMethod_New( );
        if (this) {
            ObjMethod_setObject(this, pObject);
            this->pMethod = pMethod;
            this->pObjectName = AStr_NewA(pInfo->pClassName);
            if (OBJ_NIL == this->pObjectName) {
                obj_Release(this);
                this = OBJ_NIL;
                return this;
            }
            this->pMethodName = AStr_NewA(pMethodA);
            if (OBJ_NIL == this->pMethodName) {
                obj_Release(this);
                this = OBJ_NIL;
                return this;
            }
        }
        
        return this;
    }

    



    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      D e s c r i p t i o n
    //---------------------------------------------------------------
    
    ASTR_DATA * ObjMethod_getDesc(
        OBJMETHOD_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ObjMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDesc;
    }
    
    
    bool        ObjMethod_setDesc(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !ObjMethod_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pDesc) {
            obj_Release(this->pDesc);
        }
        this->pDesc = pValue;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                          M e t h o d
    //---------------------------------------------------------------
    
    void *          ObjMethod_getMethod(
        OBJMETHOD_DATA  *this
    )
    {
        OBJ_IUNKNOWN    *pUnk;
        void            *pMethod = NULL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ObjMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pUnk = obj_getVtbl(this->pObject);
        if (pUnk && pUnk->pQueryInfo) {
            pMethod =   pUnk->pQueryInfo(
                            this->pObject,
                            OBJ_QUERYINFO_TYPE_METHOD,
                            (void *)AStr_getData(this->pMethodName)
                        );
        }
        
        return pMethod;
    }
    
    
    
    //---------------------------------------------------------------
    //                     M e t h o d  N a m e
    //---------------------------------------------------------------
    
    ASTR_DATA *     ObjMethod_getMethodName(
        OBJMETHOD_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ObjMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pMethodName;
    }
    
    
    bool            ObjMethod_setMethodName(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !ObjMethod_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pMethodName) {
            obj_Release(this->pMethodName);
        }
        this->pMethodName = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O b j e c t
    //---------------------------------------------------------------
    
    OBJ_ID          ObjMethod_getObject(
        OBJMETHOD_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ObjMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pObject;
    }
    
    
    bool            ObjMethod_setObject(
        OBJMETHOD_DATA  *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !ObjMethod_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pObject) {
            obj_Release(this->pObject);
        }
        this->pObject = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O b j e c t  N a m e
    //---------------------------------------------------------------
    
    ASTR_DATA *     ObjMethod_getObjectName(
        OBJMETHOD_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ObjMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pObjectName;
    }
    
    
    bool            ObjMethod_setObjectName(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !ObjMethod_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pObjectName) {
            obj_Release(this->pObjectName);
        }
        this->pObjectName = pValue;
        
        return true;
    }
    
        
        
    //---------------------------------------------------------------
    //                          O t h e r
    //---------------------------------------------------------------
    
    OBJ_ID          ObjMethod_getOther(
        OBJMETHOD_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ObjMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pOther;
    }
    
    
    bool        ObjMethod_setOther(
        OBJMETHOD_DATA  *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !ObjMethod_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pOther) {
            obj_Release(this->pOther);
        }
        this->pOther = pValue;
        
        return true;
    }
        
            
            
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        ObjMethod_getSize (
        OBJMETHOD_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ObjMethod_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  ObjMethod_getSuperVtbl (
        OBJMETHOD_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjMethod_Validate(this)) {
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
        ERESULT eRc = ObjMethod_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OBJMETHOD object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ObjMethod_Assign (
        OBJMETHOD_DATA		*this,
        OBJMETHOD_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjMethod_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjMethod_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        if (pOther->pDesc) {
            obj_Release(pOther->pDesc);
            pOther->pDesc = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pDesc) {
            if (obj_getVtbl(this->pDesc)->pCopy) {
                pOther->pDesc = obj_getVtbl(this->pDesc)->pCopy(this->pDesc);
            }
            else {
                obj_Retain(this->pDesc);
                pOther->pDesc = this->pDesc;
            }
        }
        if (this->pMethodName) {
            if (obj_getVtbl(this->pMethodName)->pCopy) {
                pOther->pMethodName = obj_getVtbl(this->pMethodName)->pCopy(this->pMethodName);
            }
            else {
                obj_Retain(this->pMethodName);
                pOther->pMethodName = this->pMethodName;
            }
        }
        if (this->pObjectName) {
            if (obj_getVtbl(this->pObjectName)->pCopy) {
                pOther->pObjectName = obj_getVtbl(this->pObjectName)->pCopy(this->pObjectName);
            }
            else {
                obj_Retain(this->pObjectName);
                pOther->pObjectName = this->pObjectName;
            }
        }

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
    ERESULT         ObjMethod_Compare (
        OBJMETHOD_DATA     *this,
        OBJMETHOD_DATA     *pOther
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
        if (!ObjMethod_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjMethod_Validate(pOther)) {
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
        ObjMethod      *pCopy = ObjMethod_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJMETHOD object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJMETHOD_DATA *     ObjMethod_Copy (
        OBJMETHOD_DATA       *this
    )
    {
        OBJMETHOD_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjMethod_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjMethod_New( );
        if (pOther) {
            eRc = ObjMethod_Assign(this, pOther);
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

    void            ObjMethod_Dealloc (
        OBJ_ID          objId
    )
    {
        OBJMETHOD_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ObjMethod_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJMETHOD_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        ObjMethod_setDesc(this, OBJ_NIL);
        ObjMethod_setMethodName(this, OBJ_NIL);
        ObjMethod_setObject(this, OBJ_NIL);
        ObjMethod_setObjectName(this, OBJ_NIL);

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
    ERESULT         ObjMethod_Disable (
        OBJMETHOD_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ObjMethod_Validate(this)) {
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
    ERESULT         ObjMethod_Enable (
        OBJMETHOD_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ObjMethod_Validate(this)) {
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
    //                      E x e c u t e
    //---------------------------------------------------------------

    /*!
     Execute the object's method.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjMethod_Execute (
        OBJMETHOD_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        void            *pExec;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ObjMethod_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        pExec = this->pMethod;
        if (NULL == pExec) {
            pExec = ObjMethod_getMethod(this);
        }
        if (pExec) {
            eRc = ((P_OBJ_EXEC)this->pMethod)(this->pObject);
        }
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJMETHOD_DATA *   ObjMethod_Init (
        OBJMETHOD_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJMETHOD_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJMETHOD);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ObjMethod_Vtbl);
        
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
        if (!ObjMethod_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "ObjMethod::sizeof(OBJMETHOD_DATA) = %lu\n", sizeof(OBJMETHOD_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OBJMETHOD_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ObjMethod_IsEnabled (
        OBJMETHOD_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjMethod_Validate(this)) {
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
        void        *pMethod = ObjMethod_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ObjMethod", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ObjMethod_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJMETHOD_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ObjMethod_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJMETHOD_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ObjMethod_Class();
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
                            return ObjMethod_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ObjMethod_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ObjMethod_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return ObjMethod_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ObjMethod_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == ObjMethod_ToJson)
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
        ASTR_DATA      *pDesc = ObjMethod_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjMethod_ToDebugString (
        OBJMETHOD_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjMethod_Validate(this)) {
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
                    ObjMethod_getSize(this),
                    obj_getRetainCount(this)
            );

        if (this->pObjectName) {
            if (indent) {
                AStr_AppendCharRepeatW32(pStr, indent, ' ');
            }
            eRc =   AStr_AppendPrint(pStr, " objectName:\n");
            if (((OBJ_DATA *)(this->pObjectName))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pObjectName))->pVtbl->pToDebugString(
                                                    this->pObjectName,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }

        if (this->pMethodName) {
            if (indent) {
                AStr_AppendCharRepeatW32(pStr, indent, ' ');
            }
            eRc =   AStr_AppendPrint(pStr, " methodName:\n");
            if (((OBJ_DATA *)(this->pMethodName))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pMethodName))->pVtbl->pToDebugString(
                                                    this->pMethodName,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
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
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            ObjMethod_Validate (
        OBJMETHOD_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OBJMETHOD))
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


        if (!(obj_getSize(this) >= sizeof(OBJMETHOD_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


