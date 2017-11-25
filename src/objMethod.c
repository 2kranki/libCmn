// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   objMethod.c
 *	Generated 10/28/2017 08:51:04
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
#include <objMethod_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            objMethod_task_body(
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

    OBJMETHOD_DATA * objMethod_Alloc(
    )
    {
        OBJMETHOD_DATA  *this;
        uint32_t        cbSize = sizeof(OBJMETHOD_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJMETHOD_DATA * objMethod_New(
    )
    {
        OBJMETHOD_DATA       *this;
        
        this = objMethod_Alloc( );
        if (this) {
            this = objMethod_Init(this);
        } 
        return this;
    }


    OBJMETHOD_DATA * objMethod_NewObjectA(
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

        this = objMethod_Alloc( );
        if (this) {
            this = objMethod_Init(this);
            if (this) {
                objMethod_setObject(this, pObject);
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
        }
        return this;
    }

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      D e s c r i p t i o n
    //---------------------------------------------------------------
    
    ASTR_DATA * objMethod_getDesc(
        OBJMETHOD_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        objMethod_setLastError(this, ERESULT_SUCCESS);
        return this->pDesc;
    }
    
    
    bool        objMethod_setDesc(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pDesc) {
            obj_Release(this->pDesc);
        }
        this->pDesc = pValue;
        
        objMethod_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT     objMethod_getLastError(
        OBJMETHOD_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool        objMethod_setLastError(
        OBJMETHOD_DATA  *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                          M e t h o d
    //---------------------------------------------------------------
    
    void *          objMethod_getMethod(
        OBJMETHOD_DATA  *this
    )
    {
        OBJ_IUNKNOWN    *pUnk;
        void            *pMethod = NULL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        objMethod_setLastError(this, ERESULT_DATA_NOT_FOUND);
        pUnk = obj_getVtbl(this->pObject);
        if (pUnk && pUnk->pQueryInfo) {
            pMethod =   pUnk->pQueryInfo(
                            this->pObject,
                            OBJ_QUERYINFO_TYPE_METHOD,
                            (void *)AStr_getData(this->pMethodName)
                        );
            if (pMethod) {
                objMethod_setLastError(this, ERESULT_SUCCESS);
            }
        }
        
        return pMethod;
    }
    
    
    
    //---------------------------------------------------------------
    //                     M e t h o d  N a m e
    //---------------------------------------------------------------
    
    ASTR_DATA *     objMethod_getMethodName(
        OBJMETHOD_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        objMethod_setLastError(this, ERESULT_SUCCESS);
        return this->pMethodName;
    }
    
    
    bool            objMethod_setMethodName(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pMethodName) {
            obj_Release(this->pMethodName);
        }
        this->pMethodName = pValue;
        
        objMethod_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O b j e c t
    //---------------------------------------------------------------
    
    OBJ_ID          objMethod_getObject(
        OBJMETHOD_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        objMethod_setLastError(this, ERESULT_SUCCESS);
        return this->pObject;
    }
    
    
    bool            objMethod_setObject(
        OBJMETHOD_DATA  *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pObject) {
            obj_Release(this->pObject);
        }
        this->pObject = pValue;
        
        objMethod_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O b j e c t  N a m e
    //---------------------------------------------------------------
    
    ASTR_DATA *     objMethod_getObjectName(
        OBJMETHOD_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        objMethod_setLastError(this, ERESULT_SUCCESS);
        return this->pObjectName;
    }
    
    
    bool            objMethod_setObjectName(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pObjectName) {
            obj_Release(this->pObjectName);
        }
        this->pObjectName = pValue;
        
        objMethod_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      U s e r  D a t a
    //---------------------------------------------------------------
    
    uint32_t        objMethod_getUser32(
        OBJMETHOD_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->eRc = ERESULT_SUCCESS;
        return this->user32;
    }
    
    
    bool            objMethod_setUser32(
        OBJMETHOD_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->user32 = value;
        
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
        ERESULT eRc = objMethod__Assign(this,pOther);
     @endcode 
     @param     this    OBJMETHOD object pointer
     @param     pOther  a pointer to another OBJMETHOD object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         objMethod_Assign(
        OBJMETHOD_DATA	*this,
        OBJMETHOD_DATA  *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !objMethod_Validate(pOther) ) {
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
        objMethod_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        objMethod_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return objMethod_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        objMethod      *pCopy = objMethod_Copy(this);
     @endcode 
     @param     this    OBJMETHOD object pointer
     @return    If successful, a OBJMETHOD object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the OBJMETHOD object.
     */
    OBJMETHOD_DATA *     objMethod_Copy(
        OBJMETHOD_DATA       *this
    )
    {
        OBJMETHOD_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = objMethod_New( );
        if (pOther) {
            eRc = objMethod_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        objMethod_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            objMethod_Dealloc(
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
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJMETHOD_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        objMethod_setDesc(this, OBJ_NIL);
        objMethod_setMethodName(this, OBJ_NIL);
        objMethod_setObject(this, OBJ_NIL);
        objMethod_setObjectName(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         objMethod_Disable(
        OBJMETHOD_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            objMethod_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return objMethod_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        objMethod_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         objMethod_Enable(
        OBJMETHOD_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        objMethod_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJMETHOD_DATA *   objMethod_Init(
        OBJMETHOD_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJMETHOD_DATA);
        
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
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_OBJMETHOD);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&objMethod_Vtbl);
        
        objMethod_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "objMethod::offsetof(eRc) = %lu\n", offsetof(OBJMETHOD_DATA,eRc));
        //fprintf(stderr, "objMethod::sizeof(OBJMETHOD_DATA) = %lu\n", sizeof(OBJMETHOD_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(OBJMETHOD_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         objMethod_IsEnabled(
        OBJMETHOD_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            objMethod_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        objMethod_setLastError(this, ERESULT_SUCCESS_FALSE);
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
     void        *pMethod = objMethod_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode
     @param     objId   OBJTEST object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                         for OBJ_QUERYINFO_TYPE_METHOD, this field points to a
                         character string which represents the method name without
                         the object name, "objMethod", prefix,
                         for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                         address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                 OBJ_QUERYINFO_TYPE_INFO: info pointer,
                 OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                 OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          objMethod_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJMETHOD_DATA   *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
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
                            return objMethod_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return objMethod_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return objMethod_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return objMethod_ToJSON;
                        }
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
        ASTR_DATA      *pDesc = objMethod_ToDebugString(this,4);
     @endcode 
     @param     this    OBJMETHOD object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     objMethod_ToDebugString(
        OBJMETHOD_DATA  *this,
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
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = objMethod_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{%p(%s)\n",
                    this,
                    pInfo->pClassName
               );

        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(pStr, " objectName:\n");
        if (this->pObjectName) {
            if (((OBJ_DATA *)(this->pObjectName))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pObjectName))->pVtbl->pToDebugString(
                                                    this->pObjectName,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(pStr, " methodName:\n");
        if (this->pMethodName) {
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "%p(%s)}\n",
                                 this,
                                 pInfo->pClassName
                );

        objMethod_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     objMethod_ToJSON(
        OBJMETHOD_DATA  *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pStr2;
        const
        OBJ_INFO        *pInfo;
        OBJ_IUNKNOWN    *pUnk;
        ASTR_DATA *     (*pToJSON)(OBJ_ID);
        
#ifdef NDEBUG
#else
        if( !objMethod_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                     pStr,
                     "{\"objectType\":\"%s\",",
                     pInfo->pClassName
                );
        
        pUnk = obj_getVtbl(this->pDesc);
        if (pUnk && pUnk->pQueryInfo) {
            pToJSON =   pUnk->pQueryInfo(
                                   this->pDesc,
                                   OBJ_QUERYINFO_TYPE_METHOD,
                                   "To_JSON"
                       );
            if (pToJSON) {
                pStr2 = pToJSON(this->pDesc);
                if (pStr2) {
                    AStr_AppendPrint(pStr, "\"desc\":$s,\n", AStr_getData(pStr2));
                    obj_Release(pStr2);
                    pStr2 = OBJ_NIL;
                }
            }
        }
        
        pUnk = obj_getVtbl(this->pMethodName);
        if (pUnk && pUnk->pQueryInfo) {
            pToJSON =   pUnk->pQueryInfo(
                                         this->pMethodName,
                                         OBJ_QUERYINFO_TYPE_METHOD,
                                         "To_JSON"
                                         );
            if (pToJSON) {
                pStr2 = pToJSON(this->pMethodName);
                if (pStr2) {
                    AStr_AppendPrint(pStr, "\"method\": $s,\n", AStr_getData(pStr2));
                    obj_Release(pStr2);
                    pStr2 = OBJ_NIL;
                }
            }
        }
        
        pUnk = obj_getVtbl(this->pObjectName);
        if (pUnk && pUnk->pQueryInfo) {
            pToJSON =   pUnk->pQueryInfo(
                                         this->pObjectName,
                                         OBJ_QUERYINFO_TYPE_METHOD,
                                         "To_JSON"
                                         );
            if (pToJSON) {
                pStr2 = pToJSON(this->pObjectName);
                if (pStr2) {
                    AStr_AppendPrint(pStr, "\"name\": $s,\n", AStr_getData(pStr2));
                    obj_Release(pStr2);
                    pStr2 = OBJ_NIL;
                }
            }
        }
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            objMethod_Validate(
        OBJMETHOD_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_OBJMETHOD) )
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


        if( !(obj_getSize(this) >= sizeof(OBJMETHOD_DATA)) ) {
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


