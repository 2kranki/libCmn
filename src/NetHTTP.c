// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NetHTTP.c
 *  Generated 07/02/2021 14:27:37
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
#include        <NetHTTP_internal.h>
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
    void            NetHTTP_task_body (
        void            *pData
    )
    {
        //NETHTTP_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NETHTTP_DATA *     NetHTTP_Alloc (
        void
    )
    {
        NETHTTP_DATA       *this;
        uint32_t        cbSize = sizeof(NETHTTP_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NETHTTP_DATA *     NetHTTP_New (
        void
    )
    {
        NETHTTP_DATA       *this;
        
        this = NetHTTP_Alloc( );
        if (this) {
            this = NetHTTP_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        NetHTTP_getPriority (
        NETHTTP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NetHTTP_setPriority (
        NETHTTP_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
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
    
    uint32_t        NetHTTP_getSize (
        NETHTTP_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * NetHTTP_getStr (
        NETHTTP_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        NetHTTP_setStr (
        NETHTTP_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NetHTTP_getSuperVtbl (
        NETHTTP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
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
        ERESULT eRc = NetHTTP_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NETHTTP object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NetHTTP_Assign (
        NETHTTP_DATA       *this,
        NETHTTP_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NetHTTP_Validate(pOther)) {
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
    int             NetHTTP_Compare (
        NETHTTP_DATA     *this,
        NETHTTP_DATA     *pOther
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
        if (!NetHTTP_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!NetHTTP_Validate(pOther)) {
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
        NetHTTP      *pCopy = NetHTTP_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NETHTTP object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NETHTTP_DATA *     NetHTTP_Copy (
        NETHTTP_DATA       *this
    )
    {
        NETHTTP_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef NETHTTP_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = NetHTTP_New( );
        if (pOther) {
            eRc = NetHTTP_Assign(this, pOther);
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

    void            NetHTTP_Dealloc (
        OBJ_ID          objId
    )
    {
        NETHTTP_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NETHTTP_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NetHTTP_setStr(this, OBJ_NIL);

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
        NetHTTP      *pDeepCopy = NetHTTP_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NETHTTP object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NETHTTP_DATA *     NetHTTP_DeepyCopy (
        NETHTTP_DATA       *this
    )
    {
        NETHTTP_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NetHTTP_New( );
        if (pOther) {
            eRc = NetHTTP_Assign(this, pOther);
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
    ERESULT         NetHTTP_Disable (
        NETHTTP_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
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
    ERESULT         NetHTTP_Enable (
        NETHTTP_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
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

    NETHTTP_DATA *   NetHTTP_Init (
        NETHTTP_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NETHTTP_DATA);
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
        // in the OBJ_INFO at the end of NetHTTP_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NETHTTP);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NetHTTP_Vtbl);
#ifdef  NETHTTP_JSON_SUPPORT
        JsonIn_RegisterClass(NetHTTP_Class());
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
        if (!NetHTTP_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "NetHTTP::sizeof(NETHTTP_DATA) = %lu\n", 
                sizeof(NETHTTP_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NETHTTP_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NetHTTP_IsEnabled (
        NETHTTP_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
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
        void        *pMethod = NetHTTP_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NetHTTP", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NetHTTP_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NETHTTP_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NetHTTP_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NETHTTP_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NetHTTP_Class();
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
                            return NetHTTP_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NetHTTP_Enable;
                        }
                        break;

                    case 'P':
#ifdef  NETHTTP_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return NetHTTP_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return NetHTTP_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NetHTTP_ToDebugString;
                        }
#ifdef  NETHTTP_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return NetHTTP_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return NetHTTP_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NetHTTP_ToDebugString)
                    return "ToDebugString";
#ifdef  NETHTTP_JSON_SUPPORT
                if (pData == NetHTTP_ToJson)
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
        ASTR_DATA      *pDesc = NetHTTP_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetHTTP_ToDebugString (
        NETHTTP_DATA      *this,
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
        if (!NetHTTP_Validate(this)) {
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
                    NetHTTP_getSize(this),
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            NetHTTP_Validate (
        NETHTTP_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NETHTTP))
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


        if (!(obj_getSize(this) >= sizeof(NETHTTP_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


