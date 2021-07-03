// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NetIO.c
 *  Generated 07/02/2021 14:27:06
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
#include        <NetIO_internal.h>
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
    void            NetIO_task_body (
        void            *pData
    )
    {
        //NETIO_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NETIO_DATA *     NetIO_Alloc (
        void
    )
    {
        NETIO_DATA       *this;
        uint32_t        cbSize = sizeof(NETIO_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NETIO_DATA *     NetIO_New (
        void
    )
    {
        NETIO_DATA       *this;
        
        this = NetIO_Alloc( );
        if (this) {
            this = NetIO_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        NetIO_getPriority (
        NETIO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NetIO_setPriority (
        NETIO_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
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
    
    uint32_t        NetIO_getSize (
        NETIO_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * NetIO_getStr (
        NETIO_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        NetIO_setStr (
        NETIO_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  NetIO_getSuperVtbl (
        NETIO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
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
        ERESULT eRc = NetIO_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NETIO object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NetIO_Assign (
        NETIO_DATA       *this,
        NETIO_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NetIO_Validate(pOther)) {
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
    //                     C l o s e
    //---------------------------------------------------------------

    ERESULT         NetIO_Close (
        NETIO_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (!obj_Flag(this, NETIO_FLAG_OPEN)) {
            return ERESULT_OPEN_ERROR;
        }

        // ???

        obj_FlagOff(this, NETIO_FLAG_OPEN);

        // Return to caller.
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
    int             NetIO_Compare (
        NETIO_DATA     *this,
        NETIO_DATA     *pOther
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
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!NetIO_Validate(pOther)) {
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
        NetIO      *pCopy = NetIO_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NETIO object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NETIO_DATA *     NetIO_Copy (
        NETIO_DATA       *this
    )
    {
        NETIO_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef NETIO_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = NetIO_New( );
        if (pOther) {
            eRc = NetIO_Assign(this, pOther);
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

    void            NetIO_Dealloc (
        OBJ_ID          objId
    )
    {
        NETIO_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NETIO_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NetIO_setStr(this, OBJ_NIL);

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
        NetIO      *pDeepCopy = NetIO_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NETIO object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NETIO_DATA *     NetIO_DeepyCopy (
        NETIO_DATA       *this
    )
    {
        NETIO_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NetIO_New( );
        if (pOther) {
            eRc = NetIO_Assign(this, pOther);
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
    ERESULT         NetIO_Disable (
        NETIO_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
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
    ERESULT         NetIO_Enable (
        NETIO_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
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

    NETIO_DATA *   NetIO_Init (
        NETIO_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NETIO_DATA);
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
        // in the OBJ_INFO at the end of NetIO_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NETIO);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NetIO_Vtbl);
#ifdef  NETIO_JSON_SUPPORT
        JsonIn_RegisterClass(NetIO_Class());
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
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "NetIO::sizeof(NETIO_DATA) = %lu\n", 
                sizeof(NETIO_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NETIO_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NetIO_IsEnabled (
        NETIO_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
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
    //                     O p e n
    //---------------------------------------------------------------

    ERESULT         NetIO_Open (
        NETIO_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (obj_Flag(this, NETIO_FLAG_OPEN)) {
            return ERESULT_OPEN_ERROR;
        }

        memset(&this->addr_info, 0, sizeof(struct addrinfo));
        this->addr_info.ai_family = AF_UNSPEC;
        this->addr_info.ai_socktype = SOCK_STREAM;
        this->addr_info.ai_flags = AI_PASSIVE;          // use my IP

        obj_FlagOn(this, NETIO_FLAG_OPEN);

        // Return to caller.
        return eRc;
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
        void        *pMethod = NetIO_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NetIO", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NetIO_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NETIO_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NetIO_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NETIO_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NetIO_Class();
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
                            return NetIO_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NetIO_Enable;
                        }
                        break;

                    case 'P':
#ifdef  NETIO_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return NetIO_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return NetIO_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NetIO_ToDebugString;
                        }
#ifdef  NETIO_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return NetIO_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return NetIO_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NetIO_ToDebugString)
                    return "ToDebugString";
#ifdef  NETIO_JSON_SUPPORT
                if (pData == NetIO_ToJson)
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
        ASTR_DATA      *pDesc = NetIO_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetIO_ToDebugString (
        NETIO_DATA      *this,
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
        if (!NetIO_Validate(this)) {
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
                    NetIO_getSize(this),
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
    bool            NetIO_Validate (
        NETIO_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NETIO))
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


        if (!(obj_getSize(this) >= sizeof(NETIO_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


