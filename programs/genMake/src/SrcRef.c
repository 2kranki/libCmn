// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   SrcRef.c
 *	Generated 12/05/2019 14:04:10
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
#include        <SrcRef_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            SrcRef_task_body (
        void            *pData
    )
    {
        //SRCREF_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SRCREF_DATA *   SrcRef_Alloc (
        void
    )
    {
        SRCREF_DATA     *this;
        uint32_t        cbSize = sizeof(SRCREF_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SRCREF_DATA *   SrcRef_New (
        void
    )
    {
        SRCREF_DATA     *this;
        
        this = SrcRef_Alloc( );
        if (this) {
            this = SrcRef_Init(this);
        } 
        return this;
    }



    SRCREF_DATA *   SrcRef_NewFile (
        ASTRC_DATA      *pDir,
        ASTRC_DATA      *pName,
        ASTRC_DATA      *pSuffix
    )
    {
        SRCREF_DATA       *this;
        
        this = SrcRef_Alloc( );
        if (this) {
            this = SrcRef_Init(this);
            if (this) {
                if (pDir) {
                    SrcRef_setDir(this, pDir);
                }
                if (pName) {
                    SrcRef_setName(this, pName);
                }
                if (pSuffix) {
                    SrcRef_setSuffix(this, pSuffix);
                }
            }
        }
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                    D i r e c t o r y
    //---------------------------------------------------------------
    
    ASTRC_DATA *    SrcRef_getDir (
        SRCREF_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDir;
    }
    
    
    bool            SrcRef_setDir (
        SRCREF_DATA     *this,
        ASTRC_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_DIR_OWNED
        obj_Retain(pValue);
        if (this->pDir) {
            obj_Release(this->pDir);
        }
#endif
        this->pDir = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                     F i l e  N a m e
    //---------------------------------------------------------------
    
    ASTRC_DATA *    SrcRef_getName (
        SRCREF_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pName;
    }
    
    
    bool            SrcRef_setName (
        SRCREF_DATA     *this,
        ASTRC_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_STR_OWNED
        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
#endif
        this->pName = pValue;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        SrcRef_getPriority (
        SRCREF_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            SrcRef_setPriority (
        SRCREF_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
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
    
    uint32_t        SrcRef_getSize (
        SRCREF_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u f f i x
    //---------------------------------------------------------------
    
    ASTRC_DATA *    SrcRef_getSuffix (
        SRCREF_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pSuffix;
    }
    
    
    bool            SrcRef_setSuffix (
        SRCREF_DATA     *this,
        ASTRC_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_SUFFIX_OWNED
        obj_Retain(pValue);
        if (this->pSuffix) {
            obj_Release(this->pSuffix);
        }
#endif
        this->pSuffix = pValue;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  SrcRef_getSuperVtbl (
        SRCREF_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
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
        ERESULT eRc = SrcRef_Assign(this,pOther);
     @endcode 
     @param     this    SRCREF object pointer
     @param     pOther  a pointer to another SRCREF object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SrcRef_Assign (
        SRCREF_DATA		*this,
        SRCREF_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SrcRef_Validate(pOther)) {
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
    ERESULT         SrcRef_Compare (
        SRCREF_DATA     *this,
        SRCREF_DATA     *pOther
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
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SrcRef_Validate(pOther)) {
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
        SrcRef      *pCopy = SrcRef_Copy(this);
     @endcode 
     @param     this    SRCREF object pointer
     @return    If successful, a SRCREF object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCREF_DATA *     SrcRef_Copy (
        SRCREF_DATA       *this
    )
    {
        SRCREF_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = SrcRef_New( );
        if (pOther) {
            eRc = SrcRef_Assign(this, pOther);
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

    void            SrcRef_Dealloc (
        OBJ_ID          objId
    )
    {
        SRCREF_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SRCREF_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        SrcRef_setDir(this, OBJ_NIL);
        SrcRef_setName(this, OBJ_NIL);
        SrcRef_setSuffix(this, OBJ_NIL);

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
    ERESULT         SrcRef_Disable (
        SRCREF_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!SrcRef_Validate(this)) {
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
    ERESULT         SrcRef_Enable (
        SRCREF_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!SrcRef_Validate(this)) {
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
    //                          I n i t
    //---------------------------------------------------------------

    SRCREF_DATA *   SrcRef_Init (
        SRCREF_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SRCREF_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SRCREF);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SrcRef_Vtbl);
        
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
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "SrcRef::sizeof(SRCREF_DATA) = %lu\n", sizeof(SRCREF_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SRCREF_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         SrcRef_IsEnabled (
        SRCREF_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
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
        void        *pMethod = SrcRef_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SrcRef", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SrcRef_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SRCREF_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCREF_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SrcRef_Class();
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
                            return SrcRef_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return SrcRef_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return SrcRef_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return SrcRef_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SrcRef_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == SrcRef_ToJson)
                    return "ToJSON";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
#ifdef  SRCREF_JSON_SUPPORT
     ASTR_DATA *     SrcRef_ToJSON (
        SRCREF_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{\"objectType\":\"%s\"",
                        pInfo->pClassName
                    );
            
            AStr_AppendA(pStr, "}\n");
        }
        
        return pStr;
    }
#endif
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SrcRef_ToDebugString(this,4);
     @endcode 
     @param     this    SRCREF object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcRef_ToDebugString (
        SRCREF_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcRef_Validate(this)) {
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
                    SrcRef_getSize(this)
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
    bool            SrcRef_Validate (
        SRCREF_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SRCREF))
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


        if (!(obj_getSize(this) >= sizeof(SRCREF_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


