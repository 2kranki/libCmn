// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   szData.c
 *	Generated 02/07/2018 09:15:58
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
#include <szData_internal.h>
#include <szTbl.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            szData_task_body (
        void            *pData
    )
    {
        //SZDATA_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SZDATA_DATA *   szData_Alloc (
    )
    {
        SZDATA_DATA     *this;
        uint32_t        cbSize = sizeof(SZDATA_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SZDATA_DATA *   szData_New (
    )
    {
        SZDATA_DATA       *this;
        
        this = szData_Alloc( );
        if (this) {
            this = szData_Init(this);
        } 
        return this;
    }


    SZDATA_DATA *   szData_NewA (
        const
        char            *pName
    )
    {
        SZDATA_DATA       *this;
        
        this = szData_NewA_AStr(pName, OBJ_NIL);
        
        return this;
    }
    
    
    SZDATA_DATA *   szData_NewA_AStr (
        const
        char            *pName,
        ASTR_DATA       *pStr
    )
    {
        SZDATA_DATA       *this;
        
        this = szData_Alloc( );
        if (this) {
            this = szData_Init(this);
            if (this) {
                this->token = szTbl_StringToToken(OBJ_NIL, pName);
                if (this->token)
                    ;
                else {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
                if (pStr) {
                    szData_setData(this, pStr);
                }
            }
        }
        
        return this;
    }
    
    
    SZDATA_DATA *   szData_NewFromToken (
        uint32_t        token
    )
    {
        SZDATA_DATA     *this;
        const
        char            *pStr;
        
        this = szData_Alloc( );
        if (this) {
            this = szData_Init(this);
            if (this) {
                pStr = szTbl_TokenToString(OBJ_NIL, token);
                if (pStr) {
                    this->token = token;
                }
                else {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }
        
        return this;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          C l a s s
    //---------------------------------------------------------------
    
    int32_t         szData_getClass (
        SZDATA_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->cls;
    }
    
    
    bool            szData_setClass (
        SZDATA_DATA     *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->cls = value;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          D a t a
    //---------------------------------------------------------------
    
    OBJ_ID          szData_getData (
        SZDATA_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pData;
    }
    
    
    bool            szData_setData (
        SZDATA_DATA     *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pData) {
            obj_Release(this->pData);
        }
        this->pData = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------
    
    const
    char *          szData_getName (
        SZDATA_DATA     *this
    )
    {
        const
        char            *pStr = NULL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        pStr = szTbl_TokenToString(OBJ_NIL, this->token);
        
        return pStr;
    }

    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  szData_getSuperVtbl(
        SZDATA_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
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
        ERESULT eRc = szData__Assign(this,pOther);
     @endcode 
     @param     this    SZDATA object pointer
     @param     pOther  a pointer to another SZDATA object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         szData_Assign (
        SZDATA_DATA     *this,
        SZDATA_DATA     *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !szData_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        if (pOther->pData) {
            obj_Release(pOther->pData);
            pOther->pData = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        pOther->token = this->token;
        pOther->cls = this->cls;
        if (this->pData) {
            if (obj_getVtbl(this->pData)->pCopy) {
                pOther->pData = obj_getVtbl(this->pData)->pCopy(this->pData);
            }
            else {
                obj_Retain(this->pData);
                pOther->pData = this->pData;
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
    
    ERESULT         szData_Compare (
        SZDATA_DATA     *this,
        SZDATA_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        const
        char            *pStr1;
        const
        char            *pStr2;
        
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !szData_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (this->token == pOther->token) {
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
    
    ERESULT         szData_CompareA(
        SZDATA_DATA     *this,
        const
        char            *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        const
        char            *pStr1;

#ifdef NDEBUG
#else
        if( !szData_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pOther ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        i = strcmp(pStr1, pOther);
        
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
        szData      *pCopy = szData_Copy(this);
     @endcode 
     @param     this    SZDATA object pointer
     @return    If successful, a SZDATA object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the SZDATA object.
     */
    SZDATA_DATA *   szData_Copy(
        SZDATA_DATA     *this
    )
    {
        SZDATA_DATA     *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = szData_New( );
        if (pOther) {
            eRc = szData_Assign(this, pOther);
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

    void            szData_Dealloc(
        OBJ_ID          objId
    )
    {
        SZDATA_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SZDATA_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        szData_setData(this, OBJ_NIL);

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

    ERESULT         szData_Disable(
        SZDATA_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !szData_Validate(this) ) {
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

    ERESULT         szData_Enable(
        SZDATA_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !szData_Validate(this) ) {
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
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        szData_Hash(
        SZDATA_DATA     *this
    )
    {
        uint32_t        hash = 0;
        
#ifdef NDEBUG
#else
        if( !szData_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (this->token) {
            hash = szTbl_TokenToHash(OBJ_NIL, this->token);
        }
        
        return hash;
    }
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SZDATA_DATA *   szData_Init(
        SZDATA_DATA     *this
    )
    {
        uint32_t        cbSize = sizeof(SZDATA_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SZDATA);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_SZDATA);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&szData_Vtbl);
        
    #ifdef NDEBUG
    #else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "szData::offsetof(eRc) = %lu\n", offsetof(SZDATA_DATA,eRc));
        //fprintf(stderr, "szData::sizeof(SZDATA_DATA) = %lu\n", sizeof(SZDATA_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SZDATA_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         szData_IsEnabled(
        SZDATA_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
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
        void        *pMethod = szData_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "szData", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          szData_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SZDATA_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)szData_Class();
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
                            return szData_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return szData_Enable;
                        }
                        break;

                    case 'P':
                        if (str_Compare("ParseObject", (char *)pStr) == 0) {
                            return szData_ParseObject;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return szData_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return szData_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == szData_ToDebugString)
                    return "ToDebugString";
                if (pData == szData_ToJSON)
                    return "ToJson";
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
        ASTR_DATA      *pDesc = szData_ToDebugString(this,4);
     @endcode 
     @param     this    SZDATA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     szData_ToDebugString(
        SZDATA_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        const
        char            *pStrA = "";
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        if (this->token) {
            pStrA = szTbl_TokenToString(OBJ_NIL, this->token);
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) name=(%d)%s\n",
                    this,
                    pInfo->pClassName,
                    this->token,
                    pStrA
            );
        
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
    bool            szData_Validate(
        SZDATA_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_SZDATA) )
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


        if( !(obj_getSize(this) >= sizeof(SZDATA_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


