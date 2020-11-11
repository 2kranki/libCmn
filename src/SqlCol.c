// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   SqlCol.c
 *	Generated 04/25/2020 18:28:59
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
#include        <SqlCol_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            SqlCol_task_body (
        void            *pData
    )
    {
        //SQLCOL_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SQLCOL_DATA *     SqlCol_Alloc (
        void
    )
    {
        SQLCOL_DATA       *this;
        uint32_t        cbSize = sizeof(SQLCOL_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SQLCOL_DATA *     SqlCol_New (
        void
    )
    {
        SQLCOL_DATA       *this;
        
        this = SqlCol_Alloc( );
        if (this) {
            this = SqlCol_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //              C h e c k  E x p r e s s i o n
    //---------------------------------------------------------------

    ASTR_DATA * SqlCol_getCheckExpr (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pCheckExpr;
    }


    bool        SqlCol_setCheckExpr (
        SQLCOL_DATA *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pCheckExpr) {
            obj_Release(this->pCheckExpr);
        }
        this->pCheckExpr = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                  D e f a u l t  V a l u e
    //---------------------------------------------------------------

    ASTR_DATA * SqlCol_getDefVal (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDefVal;
    }


    bool        SqlCol_setDefVal (
        SQLCOL_DATA *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pDefVal) {
            obj_Release(this->pDefVal);
        }
        this->pDefVal = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                  D e s c r i p t i o n
    //---------------------------------------------------------------

    ASTR_DATA * SqlCol_getDesc (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDesc;
    }


    bool        SqlCol_setDesc (
        SQLCOL_DATA *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
    //                        N a m e
    //---------------------------------------------------------------

    ASTR_DATA * SqlCol_getName (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pName;
    }


    bool        SqlCol_setName (
        SQLCOL_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        SqlCol_getPriority (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            SqlCol_setPriority (
        SQLCOL_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
    
    uint32_t        SqlCol_getSize (
        SQLCOL_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  SqlCol_getSuperVtbl (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
        ERESULT eRc = SqlCol_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SQLCOL object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SqlCol_Assign (
        SQLCOL_DATA		*this,
        SQLCOL_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SqlCol_Validate(pOther)) {
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
    int             SqlCol_Compare (
        SQLCOL_DATA     *this,
        SQLCOL_DATA     *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!SqlCol_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        SqlCol      *pCopy = SqlCol_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SQLCOL object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SQLCOL_DATA *     SqlCol_Copy (
        SQLCOL_DATA       *this
    )
    {
        SQLCOL_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SQLCOL_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = SqlCol_New( );
        if (pOther) {
            eRc = SqlCol_Assign(this, pOther);
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

    void            SqlCol_Dealloc (
        OBJ_ID          objId
    )
    {
        SQLCOL_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SQLCOL_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        SqlCol_setCheckExpr(this, OBJ_NIL);
        SqlCol_setDefVal(this, OBJ_NIL);
        SqlCol_setDesc(this, OBJ_NIL);
        SqlCol_setName(this, OBJ_NIL);

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
        SqlCol      *pDeepCopy = SqlCol_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SQLCOL object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SQLCOL_DATA *     SqlCol_DeepyCopy (
        SQLCOL_DATA       *this
    )
    {
        SQLCOL_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = SqlCol_New( );
        if (pOther) {
            eRc = SqlCol_Assign(this, pOther);
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
    ERESULT         SqlCol_Disable (
        SQLCOL_DATA		*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
    ERESULT         SqlCol_Enable (
        SQLCOL_DATA		*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
    //                      F r o m  S t r u c t
    //---------------------------------------------------------------

    ERESULT         SqlCol_FromStruct (
        SQLCOL_DATA        *this,
        SQLCOL_STRUCT   *pStruct
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release any prior data.
        SqlCol_setCheckExpr(this, OBJ_NIL);
        SqlCol_setDefVal(this, OBJ_NIL);
        SqlCol_setDesc(this, OBJ_NIL);
        SqlCol_setName(this, OBJ_NIL);

        if (pStruct->pCheckExpression) {
            this->pCheckExpr = AStr_NewA(pStruct->pCheckExpression);
            if (OBJ_NIL == this->pCheckExpr) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        this->pName = AStr_NewA(pStruct->pName);
        if (OBJ_NIL == this->pName) {
            SqlCol_setCheckExpr(this, OBJ_NIL);
            return ERESULT_OUT_OF_MEMORY;
        }
        if (pStruct->pDefaultValue) {
            this->pDefVal = AStr_NewA(pStruct->pDefaultValue);
            if (OBJ_NIL == this->pDefVal) {
                SqlCol_setCheckExpr(this, OBJ_NIL);
                SqlCol_setName(this, OBJ_NIL);
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        this->pDesc = AStr_NewA(pStruct->pDescription);
        if (OBJ_NIL == this->pDesc) {
            SqlCol_setCheckExpr(this, OBJ_NIL);
            SqlCol_setName(this, OBJ_NIL);
            SqlCol_setDefVal(this, OBJ_NIL);
            return ERESULT_OUT_OF_MEMORY;
        }
        this->decimalPlaces = pStruct->decimalPlaces;
        this->flags         = pStruct->flags;
        this->keySeq        = pStruct->keySequence;
        this->length        = pStruct->length;
        this->lengthMin     = pStruct->minimumLength;
        this->seq           = pStruct->seq;
        this->type          = pStruct->type;

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SQLCOL_DATA *   SqlCol_Init (
        SQLCOL_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SQLCOL_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SQLCOL);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SqlCol_Vtbl);
        
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
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "SqlCol::sizeof(SQLCOL_DATA) = %lu\n", 
                sizeof(SQLCOL_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SQLCOL_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         SqlCol_IsEnabled (
        SQLCOL_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
        void        *pMethod = SqlCol_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SqlCol", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SqlCol_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SQLCOL_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SQLCOL_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SqlCol_Class();
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
                            return SqlCol_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return SqlCol_Enable;
                        }
                        break;

                    case 'P':
#ifdef  SQLCOL_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return SqlCol_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return SqlCol_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return SqlCol_ToDebugString;
                        }
#ifdef  SQLCOL_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return SqlCol_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return SqlCol_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SqlCol_ToDebugString)
                    return "ToDebugString";
#ifdef  SQLCOL_JSON_SUPPORT
                if (pData == SqlCol_ToJson)
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
        ASTR_DATA      *pDesc = SqlCol_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCol_ToDebugString (
        SQLCOL_DATA      *this,
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
        const
        char            *pWrkStrA;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
                    "{%p(%s) retain=%d\n",
                    this,
                    pInfo->pClassName,
                    obj_getRetainCount(this)
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "\tname: %s\n\tdesc: %s\n"
                    "\tlength: %d\n\tlengthMin: %d\n"
                    "\tdecimal_places: %d\n"
                    "\tkeySeq: %d\n\tseq: %d\n"
                    "\tflags: %s %s %s %s %s\n",
                    AStr_getData(this->pName),
                    AStr_getData(this->pDesc),
                    this->length,
                    this->lengthMin,
                    this->decimalPlaces,
                    this->keySeq,
                    this->seq,
                    this->flags & SQLCOL_FLAG_UNIQUE ? "Unique" : "",
                    this->flags & SQLCOL_FLAG_NOT_NULL ? "Not_NULL" : "",
                    this->flags & SQLCOL_FLAG_AUTO_INC ? "Auto_Inc" : "",
                    this->flags & SQLCOL_FLAG_PRIM_KEY ? "Primary_Key" : "",
                    this->flags & SQLCOL_FLAG_NO_TRAIL ? "No_Trail" : ""
            );
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        switch (this->type) {
            case SQLCOL_TYPE_BLOB:
                pWrkStrA = "BLOB";
                break;

            case SQLCOL_TYPE_BOOL:
                pWrkStrA = "BOOL";
                break;

            case SQLCOL_TYPE_CHAR:
                pWrkStrA = "CHAR";
                break;

            case SQLCOL_TYPE_DATE:
                pWrkStrA = "DATE";
                break;

            case SQLCOL_TYPE_FILLER:
                pWrkStrA = "FILLER";
                break;

            case SQLCOL_TYPE_INTEGER:
                pWrkStrA = "INTEGER";
                break;

            case SQLCOL_TYPE_NUMBER:
                pWrkStrA = "NUMBER";
                break;

            case SQLCOL_TYPE_REAL:
                pWrkStrA = "REAL";
                break;

            case SQLCOL_TYPE_TEXT:
                pWrkStrA = "TEXT";
                break;

            case SQLCOL_TYPE_VARCHAR:
                pWrkStrA = "VARCHAR";
                break;

            default:
                pWrkStrA = "==>UNKNOWN<==";
                break;
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "\ttype: 0x%02x - %s\n",
                    this->type,
                    pWrkStrA
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
    bool            SqlCol_Validate (
        SQLCOL_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SQLCOL))
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


        if (!(obj_getSize(this) >= sizeof(SQLCOL_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


