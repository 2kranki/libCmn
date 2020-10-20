// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   SrcFiles.c
 *  Generated 10/19/2020 16:14:31
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
#include        <SrcFiles_internal.h>
#include        <trace.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            SrcFiles_task_body (
        void            *pData
    )
    {
        //SRCFILES_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SRCFILES_DATA * SrcFiles_Alloc (
        void
    )
    {
        SRCFILES_DATA   *this;
        uint32_t        cbSize = sizeof(SRCFILES_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SRCFILES_DATA * SrcFiles_New (
        void
    )
    {
        SRCFILES_DATA   *this;
        
        this = SrcFiles_Alloc( );
        if (this) {
            this = SrcFiles_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    OBJARRAY_DATA *     SrcFiles_getPaths(
        SRCFILES_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcFiles_Validate(this) )
            return false;
#endif

        // Return to caller.
        return this->pPaths;
    }


    bool            SrcFiles_setPaths(
        SRCFILES_DATA   *this,
        OBJARRAY_DATA   *pValue
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcFiles_Validate(this) )
            return false;
#endif

        obj_Retain(pValue);
        if (this->pPaths) {
            obj_Release(this->pPaths);
            //this->pPaths = OBJ_NIL;
        }
        this->pPaths = pValue;

        // Return to caller.
        return true;
    }



    bool            SrcFiles_getReuse(
        SRCFILES_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcFiles_Validate(this) )
            return false;
#endif

        // Return to caller.
        return this->fReuse;
    }


    bool            SrcFiles_setReuse(
        SRCFILES_DATA   *this,
        bool            fValue
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcFiles_Validate(this) )
            return false;
#endif

        if (fValue) {
            this->fReuse = true;
        }
        else {
            this->fReuse = false;
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  SrcFiles_getSuperVtbl (
        SRCFILES_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
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
        ERESULT eRc = SrcFiles_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SRCFILES object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SrcFiles_Assign (
        SRCFILES_DATA       *this,
        SRCFILES_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SrcFiles_Validate(pOther)) {
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
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         SrcFiles_Compare (
        SRCFILES_DATA     *this,
        SRCFILES_DATA     *pOther
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
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SrcFiles_Validate(pOther)) {
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
        SrcFiles      *pCopy = SrcFiles_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SRCFILES object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCFILES_DATA *     SrcFiles_Copy (
        SRCFILES_DATA       *this
    )
    {
        SRCFILES_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SRCFILES_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = SrcFiles_New( );
        if (pOther) {
            eRc = SrcFiles_Assign(this, pOther);
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

    void            SrcFiles_Dealloc (
        OBJ_ID          objId
    )
    {
        SRCFILES_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SRCFILES_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        SrcFiles_setPaths(this, OBJ_NIL);
        if (this->pStack) {
            obj_Release(this->pStack);
            this->pStack = OBJ_NIL;
            this->pTop = OBJ_NIL;
        }


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
        SrcFiles      *pDeepCopy = SrcFiles_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SRCFILES object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCFILES_DATA *     SrcFiles_DeepyCopy (
        SRCFILES_DATA       *this
    )
    {
        SRCFILES_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = SrcFiles_New( );
        if (pOther) {
            eRc = SrcFiles_Assign(this, pOther);
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
    ERESULT         SrcFiles_Disable (
        SRCFILES_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
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
    ERESULT         SrcFiles_Enable (
        SRCFILES_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
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

    SRCFILES_DATA *   SrcFiles_Init (
        SRCFILES_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SRCFILES_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SRCFILES);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SrcFiles_Vtbl);
        
        this->pStack = ObjArray_New( );
        if (OBJ_NIL == this->pStack) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "SrcFiles::sizeof(SRCFILES_DATA) = %lu\n", 
                sizeof(SRCFILES_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SRCFILES_DATA));
#endif

        return this;
    }

     

    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------

    TOKEN_DATA *    SrcFiles_InputAdvance(
        SRCFILES_DATA   *this,
        uint16_t        numChrs
    )
    {
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !SrcFiles_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pToken = SrcFile_InputAdvance(this->pTop, numChrs);

        // Return to caller.
        return pToken;
    }



    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------

    TOKEN_DATA *    SrcFiles_InputLookAhead(
        SRCFILES_DATA   *this,
        uint16_t        num
    )
    {
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !SrcFiles_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pToken = SrcFile_InputLookAhead(this->pTop, num);

        // Return to caller.
        return pToken;
    }



    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         SrcFiles_IsEnabled (
        SRCFILES_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
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
    //                          N e w  S r c
    //---------------------------------------------------------------

    ERESULT         SrcFiles_NewSrcFromAStr (
        SRCFILES_DATA   *this,
        PATH_DATA       *pFilePath,     // [in] doc only
        ASTR_DATA       *pAStr,         // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        SRCFILE_DATA    *pSrc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pSrc = SrcFile_NewFromAStr(pFilePath, pAStr, fileIndex, tabSize);
        if (OBJ_NIL == pSrc) {
            obj_Release(this);
            return ERESULT_OUT_OF_MEMORY;
        }
        SrcFiles_StackPush(this, pSrc);
        obj_Release(pSrc);
        pSrc = OBJ_NIL;

        return ERESULT_SUCCESS;
    }


    ERESULT         SrcFiles_NewSrcFromFile (
        SRCFILES_DATA   *this,
        FILE            *pFile,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        SRCFILE_DATA    *pSrc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pSrc = SrcFile_NewFromFile(pFile, fileIndex, tabSize);
        if (OBJ_NIL == pSrc) {
            obj_Release(this);
            return ERESULT_OUT_OF_MEMORY;
        }
        SrcFiles_StackPush(this, pSrc);
        obj_Release(pSrc);
        pSrc = OBJ_NIL;

        return ERESULT_SUCCESS;
    }


    ERESULT         SrcFiles_NewSrcFromPath (
        SRCFILES_DATA   *this,
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        SRCFILE_DATA    *pSrc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pSrc = SrcFile_NewFromPath(pFilePath, fileIndex, tabSize);
        if (OBJ_NIL == pSrc) {
            obj_Release(this);
            return ERESULT_OUT_OF_MEMORY;
        }
        SrcFiles_StackPush(this, pSrc);
        obj_Release(pSrc);
        pSrc = OBJ_NIL;

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                         P a t h
    //---------------------------------------------------------------

    /*!
     Get a path given its index.
     @param     this    object pointer
     @param     index   path name index (relative to 1)
     @return    if successful, path object pointer.  Otherwise, OBJ_NIL.
     */
    PATH_DATA *     SrcFiles_Path (
        SRCFILES_DATA   *this,
        uint16_t        index
    )
    {
        //ERESULT         eRc;
        PATH_DATA       *pPath = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        if (this->pPaths) {
            pPath = ObjArray_Get(this->pPaths, index);
        }

        // Return to caller.
        return pPath;
    }


    /*!
     Add a path to the paths if it is not already there and return its index.
     @param     this    object pointer
     @param     pPath   path name object
     @return    if successful, the path name index relative to 1.
                Otherwise, 0.
     */
    uint16_t        SrcFiles_PathAdd (
        SRCFILES_DATA   *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        iMax;
        PATH_DATA       *pPathF = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif
        if (OBJ_NIL == this->pPaths) {
            this->pPaths = ObjArray_New( );
            if (OBJ_NIL == this->pPaths) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        iMax = ObjArray_getSize(this->pPaths);
        for (i=0; i < iMax; i++) {
            pPathF = (PATH_DATA *)ObjArray_Get(this->pPaths, i+1);
            if (pPathF && (ERESULT_SUCCESS_EQUAL == Path_Compare(pPath, pPathF))) {
                return i+1;
            }
        }

        i = 0;
        eRc = ObjArray_AppendObj(this->pPaths, pPath, &i);
        if (ERESULT_FAILED(eRc)) {
            return 0;
        }

        // Return to caller.
        return i;
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
        void        *pMethod = SrcFiles_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SrcFiles", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SrcFiles_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SRCFILES_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SrcFiles_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SRCFILES_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SrcFiles_Class();
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
                            return SrcFiles_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return SrcFiles_Enable;
                        }
                        break;

                    case 'P':
#ifdef  SRCFILES_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return SrcFiles_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return SrcFiles_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return SrcFiles_ToDebugString;
                        }
#ifdef  SRCFILES_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return SrcFiles_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return SrcFiles_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SrcFiles_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCFILES_JSON_SUPPORT
                if (pData == SrcFiles_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S t a c k  G e t
    //---------------------------------------------------------------

    SRCFILE_DATA *  SrcFiles_StackGet(
        SRCFILES_DATA   *cbp,
        uint16_t        index
    )
    {
        SRCFILE_DATA    *pItem = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !SrcFiles_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        pItem = ObjArray_Get(cbp->pStack, index);

        // Return to caller.
        return pItem;
    }



    //---------------------------------------------------------------
    //                      S t a c k  P o p
    //---------------------------------------------------------------

    ERESULT         SrcFiles_StackPop(
        SRCFILES_DATA   *this
    )
    {
        SRCFILE_DATA    *pItem = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !SrcFiles_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        /* Pop 1 element from the top of the parse stack.
         */
        if( ObjArray_getSize(this->pStack) ) {
            pItem = ObjArray_DeleteLast(this->pStack);
            obj_Release(pItem);
            pItem = OBJ_NIL;
            this->pTop = ObjArray_GetLast(this->pStack);
        }
        else {
            return ERESULT_DATA_NOT_FOUND;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      S t a c k  P u s h
    //---------------------------------------------------------------

    ERESULT          SrcFiles_StackPush(
        SRCFILES_DATA   *this,
        SRCFILE_DATA    *pItem
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !SrcFiles_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if  ((NULL == pItem) || !(obj_IsKindOf(pItem, OBJ_IDENT_SRCFILE))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (OBJ_NIL == this->pStack) {
            this->pStack = ObjArray_New( );
            if (OBJ_NIL == this->pStack) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        eRc = ObjArray_AppendObj(this->pStack, pItem, NULL);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        this->pTop = pItem;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      S t a c k  T o p
    //---------------------------------------------------------------

    SRCFILE_DATA *  SrcFiles_StackTop(
        SRCFILES_DATA   *this
    )
    {
        SRCFILE_DATA    *pItem = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !SrcFiles_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        pItem = this->pTop;

        // Return to caller.
        return pItem;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SrcFiles_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcFiles_ToDebugString (
        SRCFILES_DATA      *this,
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
        if (!SrcFiles_Validate(this)) {
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

#ifdef  XYZZY        
        if (this->pData) {
            ASTR_DATA       *pWrkStr = OBJ_NIL;
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
    bool            SrcFiles_Validate (
        SRCFILES_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SRCFILES))
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


        if (!(obj_getSize(this) >= sizeof(SRCFILES_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


