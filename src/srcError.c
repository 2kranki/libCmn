// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   srcError.c
 *	Generated 12/17/2017 07:12:30
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
#include <srcError_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            srcError_task_body(
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

    SRCERROR_DATA *     srcError_Alloc(
    )
    {
        SRCERROR_DATA   *this;
        uint32_t        cbSize = sizeof(SRCERROR_DATA);
        
        // Do initialization.
        
        this = obj_Alloc(cbSize);
        
        // Return to caller.
        return this;
    }



    SRCERROR_DATA * srcError_New(
        void
    )
    {
        SRCERROR_DATA   *this;
        
        this = srcError_Alloc( );
        if (this) {
            this = srcError_Init(this);
        }
        return this;
    }
    
    
    
    SRCERROR_DATA * srcError_NewFromData(
        uint16_t        severity,
        const
        SRCLOC          *pLoc,
        const
        char            *pErrorString
    )
    {
        SRCERROR_DATA   *this;

        this = srcError_Alloc( );
        if (this) {
            this = srcError_Init(this);
            if (this) {
                srcError_setSeverity(this, severity);
                if (pLoc) {
                    srcError_setLocation(this, pLoc);
                }
                if (pErrorString) {
                    this->pErrorStr = AStr_NewA(pErrorString);
                    if (OBJ_NIL == this->pErrorStr) {
                        obj_Release(this);
                        return OBJ_NIL;
                    }
                }
            }
        } 
        return this;
    }



    SRCERROR_DATA * srcError_NewFatalFromToken(
        TOKEN_DATA      *pToken,
        ASTR_DATA       *pErrorString
    )
    {
        SRCERROR_DATA   *this;
        
        this = srcError_Alloc( );
        if (this) {
            this = srcError_Init(this);
            if (this) {
                srcError_setSeverity(this, SRCERROR_SEVERITY_FATAL);
                if (pToken) {
                    srcError_setLocation(this, token_getLoc(pToken));
                }
                if (pErrorString) {
                    this->pErrorStr = AStr_Copy(pErrorString);
                    if (OBJ_NIL == this->pErrorStr) {
                        obj_Release(this);
                        return OBJ_NIL;
                    }
                }
            }
        }
        return this;
    }
    
    
    
    SRCERROR_DATA * srcError_NewFatalFromTokenA(
        TOKEN_DATA      *pToken,
        const
        char            *pErrorString
    )
    {
        SRCERROR_DATA   *this;
        
        this = srcError_Alloc( );
        if (this) {
            this = srcError_Init(this);
            if (this) {
                srcError_setSeverity(this, SRCERROR_SEVERITY_FATAL);
                if (pToken) {
                    srcError_setLocation(this, token_getLoc(pToken));
                }
                this->pErrorStr = AStr_NewA(pErrorString);
                if (OBJ_NIL == this->pErrorStr) {
                    obj_Release(this);
                    return OBJ_NIL;
                }
            }
        }
        return this;
    }

    


    
    
    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                     E r r o r  S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     srcError_getErrorStr(
        SRCERROR_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pErrorStr;
    }
    
    
    bool            srcError_setErrorStr(
        SRCERROR_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
        ASTR_DATA       *pStr;
        
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
       
        if (pValue) {
            pStr = AStr_Copy(pValue);
            if (OBJ_NIL == pStr) {
                return false;
            }
        }
        //obj_Retain(pValue);
        
        if (this->pErrorStr) {
            obj_Release(this->pErrorStr);
        }
        this->pErrorStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                     L o c a t i o n
    //---------------------------------------------------------------
    
    SRCLOC *        srcError_getLocation(
        SRCERROR_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return &this->loc;
    }
    
    
    bool            srcError_setLocation(
        SRCERROR_DATA   *this,
        const
        SRCLOC          *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
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
    //                          S e v e r i t y
    //---------------------------------------------------------------
    
    uint16_t        srcError_getSeverity(
        SRCERROR_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->severity;
    }


    bool            srcError_setSeverity(
        SRCERROR_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
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
    
    uint32_t        srcError_getSize(
        SRCERROR_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  srcError_getSuperVtbl(
        SRCERROR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
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
        ERESULT eRc = srcError__Assign(this,pOther);
     @endcode 
     @param     this    SRCERROR object pointer
     @param     pOther  a pointer to another SRCERROR object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         srcError_Assign(
        SRCERROR_DATA		*this,
        SRCERROR_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !srcError_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        srcError_setErrorStr(pOther, OBJ_NIL);

        // Create a copy of objects and areas in this object placing
        // them in other.
        
        if (this->pErrorStr) {
            if (obj_getVtbl(this->pErrorStr)->pCopy) {
                pOther->pErrorStr = obj_getVtbl(this->pErrorStr)->pCopy(this->pErrorStr);
            }
            else {
                obj_Retain(this->pErrorStr);
                pOther->pErrorStr = this->pErrorStr;
            }
        }

        // Copy other data from this object to other.
        pOther->severity = this->severity;
        srcError_setLocation(pOther, &this->loc);
        
        //goto eom;

        // Return to caller.
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C o m p a r e
    //---------------------------------------------------------------
    
    ERESULT         srcError_Compare(
        SRCERROR_DATA   *this,
        SRCERROR_DATA   *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !srcError_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
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

        // Return to caller.
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        srcError      *pCopy = srcError_Copy(this);
     @endcode 
     @param     this    SRCERROR object pointer
     @return    If successful, a SRCERROR object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the SRCERROR object.
     */
    SRCERROR_DATA *     srcError_Copy(
        SRCERROR_DATA       *this
    )
    {
        SRCERROR_DATA       *pOther = OBJ_NIL;
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther =    srcError_NewFromData(
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

    void            srcError_Dealloc(
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
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SRCERROR_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        srcError_setErrorStr(this, OBJ_NIL);

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

    ERESULT         srcError_Disable(
        SRCERROR_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !srcError_Validate(this) ) {
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

    ERESULT         srcError_Enable(
        SRCERROR_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !srcError_Validate(this) ) {
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

    SRCERROR_DATA *   srcError_Init(
        SRCERROR_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SRCERROR_DATA);
        
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
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_SRCERROR);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&srcError_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "srcError::offsetof(eRc) = %lu\n", offsetof(SRCERROR_DATA,eRc));
        //fprintf(stderr, "srcError::sizeof(SRCERROR_DATA) = %lu\n", sizeof(SRCERROR_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SRCERROR_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         srcError_IsEnabled(
        SRCERROR_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
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
        void        *pMethod = srcError_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "srcError", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          srcError_QueryInfo(
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
        if( !srcError_Validate(this) ) {
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
                            return srcError_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return srcError_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return srcError_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == srcError_ToDebugString)
                    return "ToDebugString";
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
        ASTR_DATA      *pDesc = srcError_ToDebugString(this,4);
     @endcode 
     @param     this    SRCERROR object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     srcError_ToDebugString(
        SRCERROR_DATA   *this,
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
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = srcError_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) fileNo=%d LineNo=%d ColNo=%d error=%s\n",
                    this,
                    pInfo->pClassName,
                    this->loc.fileIndex,
                    this->loc.lineNo,
                    this->loc.colNo,
                    AStr_getData(this->pErrorStr)
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
    
    
    ASTR_DATA *     srcError_ToString(
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
        if( !srcError_Validate(this) ) {
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
            AStr_AppendA(pStr, AStr_getData(this->pErrorStr));
        }
        AStr_AppendA(pStr, "!\n");
        
        return pStr;
    }
    
    

    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            srcError_Validate(
        SRCERROR_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_SRCERROR) )
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


        if( !(obj_getSize(this) >= sizeof(SRCERROR_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


