// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   SrcError.c
 *	Generated 12/28/2019 09:57:21
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
#include        <SrcError_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            SrcError_task_body (
        void            *pData
    )
    {
        //SRCERROR_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SRCERROR_DATA *     SrcError_Alloc (
        void
    )
    {
        SRCERROR_DATA       *this;
        uint32_t        cbSize = sizeof(SRCERROR_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SRCERROR_DATA * SrcError_New (
        void
    )
    {
        SRCERROR_DATA   *this;
        
        this = SrcError_Alloc( );
        if (this) {
            this = SrcError_Init(this);
        } 
        return this;
    }

    SRCERROR_DATA * SrcError_NewFromData (
        uint16_t        severity,
        const
        SRCLOC          *pLoc,
        const
        char            *pErrorString
    )
    {
        SRCERROR_DATA   *this;

        this = SrcError_New();
        if (this) {
            SrcError_setSeverity(this, severity);
            if (pLoc) {
                SrcError_setLocation(this, pLoc);
            }
            if (pErrorString) {
                this->pErrorStr = AStr_NewA(pErrorString);
                if (OBJ_NIL == this->pErrorStr) {
                    obj_Release(this);
                    return OBJ_NIL;
                }
            }
        }

        return this;
    }



    SRCERROR_DATA * SrcError_NewFatalFromToken (
        TOKEN_DATA      *pToken,
        ASTR_DATA       *pErrorString
    )
    {
        SRCERROR_DATA   *this;
        
        this = SrcError_New( );
        if (this) {
            SrcError_setSeverity(this, SRCERROR_SEVERITY_FATAL);
            if (pToken) {
                SrcError_setLocation(this, token_getLoc(pToken));
            }
            if (pErrorString) {
                this->pErrorStr = AStr_Copy(pErrorString);
                if (OBJ_NIL == this->pErrorStr) {
                    obj_Release(this);
                    return OBJ_NIL;
                }
            }
        }

        return this;
    }
    
    
    
    SRCERROR_DATA * SrcError_NewFatalFromTokenA (
        TOKEN_DATA      *pToken,
        const
        char            *pErrorString
    )
    {
        SRCERROR_DATA   *this;
        
        this = SrcError_New( );
        if (this) {
            SrcError_setSeverity(this, SRCERROR_SEVERITY_FATAL);
            if (pToken) {
                SrcError_setLocation(this, token_getLoc(pToken));
            }
            this->pErrorStr = AStr_NewA(pErrorString);
            if (OBJ_NIL == this->pErrorStr) {
                obj_Release(this);
                return OBJ_NIL;
            }
        }

        return this;
    }

    




    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                    E r r o r  S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * SrcError_getErrorStr (
        SRCERROR_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pErrorStr;
    }
    
    
    bool        SrcError_setErrorStr (
        SRCERROR_DATA *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_ERRORSTR_OWNED
        obj_Retain(pValue);
        if (this->pErrorStr) {
            obj_Release(this->pErrorStr);
        }
#endif
        this->pErrorStr = pValue;
        
        return true;
    }
    
        
        
    //---------------------------------------------------------------
    //                    L o c a t i o n
    //---------------------------------------------------------------
    
    SRCLOC *        SrcError_getLocation (
        SRCERROR_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return &this->loc;
    }


    bool            SrcError_setLocation (
        SRCERROR_DATA   *this,
        const
        SRCLOC          *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !SrcError_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (pValue) {
            memmove(&this->loc, pValue, sizeof(SRCLOC));
        }
        else {
            memset(&this->loc, 0, sizeof(SRCLOC));
        }
        
        return true;
    }

     

    //---------------------------------------------------------------
    //                        S e v e r i t y
    //---------------------------------------------------------------
    
    uint16_t        SrcError_getSeverity (
        SRCERROR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->severity;
    }


    bool            SrcError_setSeverity (
        SRCERROR_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->severity = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        SrcError_getSize (
        SRCERROR_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  SrcError_getSuperVtbl (
        SRCERROR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
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
        ERESULT eRc = SrcError_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SRCERROR object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SrcError_Assign (
        SRCERROR_DATA   *this,
        SRCERROR_DATA   *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SrcError_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        SrcError_setErrorStr(this, OBJ_NIL);

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pErrorStr) {
            pOther->pErrorStr = AStr_Copy(this->pErrorStr);
        }

        // Copy other data from this object to other.
        SrcError_setLocation(pOther, &this->loc);
        pOther->severity = this->severity;
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
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
    ERESULT         SrcError_Compare (
        SRCERROR_DATA     *this,
        SRCERROR_DATA     *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SrcError_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if( OBJ_NIL == pOther ) {
            DEBUG_BREAK();
            return ERESULT_SUCCESS_GREATER_THAN;
        }
        
        if (this->loc.fileIndex == pOther->loc.fileIndex)
            ;
        else {
            if (this->loc.fileIndex < pOther->loc.fileIndex)
                return ERESULT_SUCCESS_LESS_THAN;
            else
                return ERESULT_SUCCESS_GREATER_THAN;
        }
        if (this->loc.offset == pOther->loc.offset)
            ;
        else {
            if (this->loc.offset < pOther->loc.offset)
                return ERESULT_SUCCESS_LESS_THAN;
            else
                return ERESULT_SUCCESS_GREATER_THAN;
        }
        if (this->loc.lineNo == pOther->loc.lineNo)
            ;
        else {
            if (this->loc.lineNo < pOther->loc.lineNo)
                return ERESULT_SUCCESS_LESS_THAN;
            else
                return ERESULT_SUCCESS_GREATER_THAN;
        }
        if (this->loc.colNo == pOther->loc.colNo)
            ;
        else {
            if (this->loc.colNo < pOther->loc.colNo)
                return ERESULT_SUCCESS_LESS_THAN;
            else
                return ERESULT_SUCCESS_GREATER_THAN;
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
        SrcError      *pCopy = SrcError_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SRCERROR object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCERROR_DATA * SrcError_Copy (
        SRCERROR_DATA   *this
    )
    {
        SRCERROR_DATA   *pOther = OBJ_NIL;
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther =    SrcError_NewFromData(
                                 this->severity,
                                 &this->loc,
                                 AStr_getData(this->pErrorStr)
                    );
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }

        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            SrcError_Dealloc (
        OBJ_ID          objId
    )
    {
        SRCERROR_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SRCERROR_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        SrcError_setErrorStr(this, OBJ_NIL);

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
    ERESULT         SrcError_Disable (
        SRCERROR_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!SrcError_Validate(this)) {
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
    ERESULT         SrcError_Enable (
        SRCERROR_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!SrcError_Validate(this)) {
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

    SRCERROR_DATA *   SrcError_Init (
        SRCERROR_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SRCERROR_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SRCERROR);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SrcError_Vtbl);
        
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
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "SrcError::sizeof(SRCERROR_DATA) = %lu\n", sizeof(SRCERROR_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SRCERROR_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         SrcError_IsEnabled (
        SRCERROR_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
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
        void        *pMethod = SrcError_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SrcError", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SrcError_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SRCERROR_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SrcError_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCERROR_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SrcError_Class();
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
                            return SrcError_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return SrcError_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return SrcError_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return SrcError_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SrcError_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == SrcError_ToJson)
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
        ASTR_DATA      *pDesc = SrcError_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcError_ToDebugString (
        SRCERROR_DATA      *this,
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
        if (!SrcError_Validate(this)) {
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
                    "{%p(%s) retain=%d severity=%d "
                    "fileNo=%d LineNo=%d ColNo=%d error=%s\n",
                    this,
                    pInfo->pClassName,
                    obj_getRetainCount(this),
                    this->severity,
                    this->loc.fileIndex,
                    this->loc.lineNo,
                    this->loc.colNo,
                    this->pErrorStr ? AStr_getData(this->pErrorStr) : ""
            );

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
    
    
    ASTR_DATA *     SrcError_ToString (
        SRCERROR_DATA   *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !SrcError_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_New();
        
        switch (this->severity) {
            case SRCERROR_SEVERITY_UNKNOWN:
                AStr_AppendA(pStr, "FATAL - ");
                break;
            case SRCERROR_SEVERITY_INFO:
                AStr_AppendA(pStr, "INFO - ");
                break;
            case SRCERROR_SEVERITY_WARNING:
                AStr_AppendA(pStr, "WARNING - ");
                break;
            case SRCERROR_SEVERITY_FATAL:
                AStr_AppendA(pStr, "FATAL - ");
                break;
        }
        
        eRc =   AStr_AppendPrint(
                               pStr,
                               "(%d,%d,%d) - ",
                               this->loc.fileIndex,
                               this->loc.lineNo,
                               this->loc.colNo
                );
        
        if (this->pErrorStr) {
            AStr_Append(pStr, this->pErrorStr);
        }
        AStr_AppendA(pStr, "!\n");
        
        return pStr;
    }
        
        


    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            SrcError_Validate (
        SRCERROR_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SRCERROR))
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


        if (!(obj_getSize(this) >= sizeof(SRCERROR_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


