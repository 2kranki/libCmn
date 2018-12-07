// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   property.c
 *	Generated 12/02/2018 23:32:21
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
#include        <property_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            property_task_body (
        void            *pData
    )
    {
        //PROPERTY_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PROPERTY_DATA *     property_Alloc (
        void
    )
    {
        PROPERTY_DATA       *this;
        uint32_t        cbSize = sizeof(PROPERTY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    PROPERTY_DATA *     property_New (
        void
    )
    {
        PROPERTY_DATA       *this;
        
        this = property_Alloc( );
        if (this) {
            this = property_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          C l a s s
    //---------------------------------------------------------------
    
    uint32_t        property_getClass (
        PROPERTY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->cls;
    }
    
    
    bool            property_setClass (
        PROPERTY_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->cls = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                    D a t a  N a m e
    //---------------------------------------------------------------
    
    ASTR_DATA * property_getDataName (
        PROPERTY_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDataName;
    }
    
    
    bool            property_setDataName (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef  PROPERTY_DATANAME_OWNED
        obj_Retain(pValue);
        if (this->pDataName) {
            obj_Release(this->pDataName);
        }
#endif
        this->pDataName = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       D e s c r i p t i o n
    //---------------------------------------------------------------
    
    ASTR_DATA * property_getDesc (
        PROPERTY_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDesc;
    }
    
    
    bool            property_setDesc (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef  PROPERTY_DESC_OWNED
        obj_Retain(pValue);
        if (this->pDesc) {
            obj_Release(this->pDesc);
        }
#endif
        this->pDesc = pValue;
        
        return true;
    }
    
    
    ASTR_DATA * property_getDescShort (
        PROPERTY_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDescShort;
    }
    
    
    bool            property_setDescShort (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef  PROPERTY_DESCSHORT_OWNED
        obj_Retain(pValue);
        if (this->pDescShort) {
            obj_Release(this->pDescShort);
        }
#endif
        this->pDescShort = pValue;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                       G e n  I n t e r n a l
    //---------------------------------------------------------------
    
    bool            property_getGenInternal (
        PROPERTY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return this->fGenInternal ? true : false;
    }
    
    
    bool            property_setGenInternal (
        PROPERTY_DATA   *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->shift = fValue ? 1 : 0;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       N a m e
    //---------------------------------------------------------------
    
    ASTR_DATA * property_getName (
        PROPERTY_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pName;
    }
    
    
    bool            property_setName (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef  PROPERTY_NAME_OWNED
        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
#endif
        this->pName = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S h i f t
    //---------------------------------------------------------------
    
    uint32_t        property_getShift (
        PROPERTY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->shift;
    }
    
    
    bool            property_setShift (
        PROPERTY_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->shift = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        property_getSize (
        PROPERTY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  property_getSuperVtbl (
        PROPERTY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                       T y p e
    //---------------------------------------------------------------
    
    ASTR_DATA *     property_getType (
        PROPERTY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pType;
    }
    
    
    bool            property_setType (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef  PROPERTY_NAME_OWNED
        obj_Retain(pValue);
        if (this->pType) {
            obj_Release(this->pType);
        }
#endif
        this->pType = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T y p e  I n t e r n a l
    //---------------------------------------------------------------
    
    ASTR_DATA *     property_getTypeInternal (
        PROPERTY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pTypeInternal;
    }
    
    
    bool            property_setTypeInternal (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef  PROPERTY_NAME_OWNED
        obj_Retain(pValue);
        if (this->pType) {
            obj_Release(this->pType);
        }
#endif
        this->pType = pValue;
        
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
        ERESULT eRc = property_Assign(this,pOther);
     @endcode 
     @param     this    PROPERTY object pointer
     @param     pOther  a pointer to another PROPERTY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         property_Assign (
        PROPERTY_DATA		*this,
        PROPERTY_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!property_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

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
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         property_Compare (
        PROPERTY_DATA     *this,
        PROPERTY_DATA     *pOther
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
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!property_Validate(pOther)) {
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
        property      *pCopy = property_Copy(this);
     @endcode 
     @param     this    PROPERTY object pointer
     @return    If successful, a PROPERTY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PROPERTY_DATA *     property_Copy (
        PROPERTY_DATA       *this
    )
    {
        PROPERTY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = property_New( );
        if (pOther) {
            eRc = property_Assign(this, pOther);
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

    void            property_Dealloc (
        OBJ_ID          objId
    )
    {
        PROPERTY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((PROPERTY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        property_setName(this, OBJ_NIL);

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

    ERESULT         property_Disable (
        PROPERTY_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!property_Validate(this)) {
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

    ERESULT         property_Enable (
        PROPERTY_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!property_Validate(this)) {
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
    //              G e n e r a t e  I n t e r n a l
    //---------------------------------------------------------------
    
    ASTR_DATA *     property_GenInternal (
        PROPERTY_DATA   *this
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pType = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        if (this->pDataName)
            pName = this->pDataName;
        else
            pName = this->pName;
        if (this->pTypeInternal)
            pType = this->pTypeInternal;
        else
            pType = this->pType;
        
        pStr = AStr_New( );
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        
        AStr_AppendPrint(pStr, "\t%s\t\t", AStr_getData(pType));
        if (this->ptrlvl) {
            AStr_AppendCharRepeatW32(pStr, this->ptrlvl, '*');
            AStr_AppendCharRepeatW32(pStr, this->ptrlvl, 'p');
        }
        pWrk = AStr_ToUpperName(pName);
        AStr_AppendPrint(pStr, "%s;", AStr_getData(pWrk));
        
        if (this->pDescShort) {
            AStr_AppendPrint(pStr, "\t\t// %s", AStr_getData(this->pDescShort));
        }

        
        
        // Return to caller.
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PROPERTY_DATA *   property_Init (
        PROPERTY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(PROPERTY_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_PROPERTY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_PROPERTY);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&property_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "property::sizeof(PROPERTY_DATA) = %lu\n", sizeof(PROPERTY_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(PROPERTY_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         property_IsEnabled (
        PROPERTY_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
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
        void        *pMethod = property_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "property", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          property_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PROPERTY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PROPERTY_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)property_Class();
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
                            return property_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return property_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return property_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return property_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == property_ToDebugString)
                    return "ToDebugString";
                if (pData == property_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     property_ToJSON (
        PROPERTY_DATA      *this
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{\"objectType\":\"%s\"",
                    pInfo->pClassName
                );
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = property_ToDebugString(this,4);
     @endcode 
     @param     this    PROPERTY object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     property_ToDebugString (
        PROPERTY_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!property_Validate(this)) {
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
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    property_getSize(this)
            );

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
    bool            property_Validate (
        PROPERTY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_PROPERTY))
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


        if (!(obj_getSize(this) >= sizeof(PROPERTY_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


