// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   srcFile.c
 *	Generated 12/18/2018 10:08:34
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
#include        <srcFile_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SRCFILE_DATA *  srcFile_Alloc (
        void
    )
    {
        SRCFILE_DATA    *this;
        uint32_t        cbSize = sizeof(SRCFILE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SRCFILE_DATA *  srcFile_New (
        void
    )
    {
        SRCFILE_DATA       *this;
        
        this = srcFile_Alloc( );
        if (this) {
            this = srcFile_Init(this);
        } 
        return this;
    }


    SRCFILE_DATA *  srcFile_NewFromAStr(
        ASTR_DATA       *pStr,        // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        SRCFILE_DATA    *this = OBJ_NIL;
        ERESULT         eRc;
        TOKEN_DATA      *pToken;
        
        this = srcFile_New( );
        if (this) {
            eRc = textIn_SetupAStr((TEXTIN_DATA *)this, pStr, pFilePath, fileIndex, tabSize);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            
            obj_setSize(&this->curchr, sizeof(TOKEN_DATA));
            pToken = token_Init(&this->curchr);
            if (OBJ_NIL == pToken) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            srcFile_InputAdvance(this, this->sizeInputs);
        }
        
        return this;
    }
    
    
    SRCFILE_DATA *  srcFile_NewFromFile(
        FILE            *pFile,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        ERESULT         eRc;
        SRCFILE_DATA    *this = OBJ_NIL;
        TOKEN_DATA      *pToken;

        this = srcFile_New( );
        if (this) {
            eRc = textIn_SetupFile((TEXTIN_DATA *)this, OBJ_NIL, fileIndex, pFile, tabSize);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            
            obj_setSize(&this->curchr, sizeof(TOKEN_DATA));
            pToken = token_Init(&this->curchr);
            if (OBJ_NIL == pToken) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            srcFile_InputAdvance(this, this->sizeInputs);
        }
        
        return this;
    }
    
    
    SRCFILE_DATA *  srcFile_NewFromPath(
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        ERESULT         eRc;
        SRCFILE_DATA    *this = OBJ_NIL;
        TOKEN_DATA      *pToken;

        this = srcFile_New( );
        if (this) {
            eRc = textIn_SetupPath((TEXTIN_DATA *)this, pFilePath, fileIndex, tabSize);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            
            obj_setSize(&this->curchr, sizeof(TOKEN_DATA));
            pToken = token_Init(&this->curchr);
            if (OBJ_NIL == pToken) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            srcFile_InputAdvance(this, this->sizeInputs);
        }
        
        return this;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                    F i l e  I n d e x
    //---------------------------------------------------------------
    
    uint16_t        srcFile_getFileIndex (
        SRCFILE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return textIn_getFileIndex((TEXTIN_DATA *)this);
    }
    
    
    bool            srcFile_setFileIndex (
        SRCFILE_DATA    *this,
        uint16_t        value
    )
    {
        bool            fRc;
        
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = textIn_setFileIndex((TEXTIN_DATA *)this, value);
        
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                         P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *     srcFile_getPath (
        SRCFILE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return textIn_getPath((TEXTIN_DATA *)this);
    }
    
    
    bool            srcFile_setPath (
        SRCFILE_DATA    *this,
        PATH_DATA       *pValue
    )
    {
        bool            fRc;

#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = textIn_setPath((TEXTIN_DATA *)this, pValue);
        
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        srcFile_getPriority (
        SRCFILE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            srcFile_setPriority (
        SRCFILE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                  R e m o v e  N L s
    //---------------------------------------------------------------
    
    bool            srcFile_getRemoveNLs (
        SRCFILE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return textIn_getRemoveNLs((TEXTIN_DATA *)this);
    }
    
    
    bool            srcFile_setRemoveNLs (
        SRCFILE_DATA    *this,
        bool            fValue
    )
    {
        bool            fRc;
        
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = textIn_setRemoveNLs((TEXTIN_DATA *)this, fValue);
        
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        srcFile_getSize (
        SRCFILE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  srcFile_getSuperVtbl (
        SRCFILE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                      T a b  S i z e
    //---------------------------------------------------------------
    
    uint16_t        srcFile_getTabSize (
        SRCFILE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return textIn_getTabSize((TEXTIN_DATA *)this);
    }
    
    
    bool            srcFile_setTabSize (
        SRCFILE_DATA    *this,
        uint16_t        value
    )
    {
        bool            fRc;
        
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = textIn_setTabSize((TEXTIN_DATA *)this, value);
        
        return fRc;
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
        ERESULT eRc = srcFile_Assign(this,pOther);
     @endcode 
     @param     this    SRCFILE object pointer
     @param     pOther  a pointer to another SRCFILE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         srcFile_Assign (
        SRCFILE_DATA		*this,
        SRCFILE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!srcFile_Validate(pOther)) {
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
    ERESULT         srcFile_Compare (
        SRCFILE_DATA     *this,
        SRCFILE_DATA     *pOther
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
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!srcFile_Validate(pOther)) {
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
        srcFile      *pCopy = srcFile_Copy(this);
     @endcode 
     @param     this    SRCFILE object pointer
     @return    If successful, a SRCFILE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCFILE_DATA *     srcFile_Copy (
        SRCFILE_DATA       *this
    )
    {
        SRCFILE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = srcFile_New( );
        if (pOther) {
            eRc = srcFile_Assign(this, pOther);
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

    void            srcFile_Dealloc (
        OBJ_ID          objId
    )
    {
        SRCFILE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SRCFILE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pInputs) {
            mem_Free(this->pInputs);
            this->pInputs = OBJ_NIL;
            this->sizeInputs = 0;
            this->curInputs = 0;
        }
        
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

    ERESULT         srcFile_Disable (
        SRCFILE_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!srcFile_Validate(this)) {
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

    ERESULT         srcFile_Enable (
        SRCFILE_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!srcFile_Validate(this)) {
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

    SRCFILE_DATA *  srcFile_Init (
        SRCFILE_DATA    *this
    )
    {
        uint32_t        cbSize = sizeof(SRCFILE_DATA);
        
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

        this = (OBJ_ID)textIn_Init((TEXTIN_DATA *)this);    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SRCFILE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_SRCFILE);      // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&srcFile_Vtbl);
        
        this->sizeInputs = 4;
        this->pInputs = mem_Calloc(this->sizeInputs, sizeof(TOKEN_DATA));
        if (NULL == this->pInputs) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "srcFile::sizeof(SRCFILE_DATA) = %lu\n", sizeof(SRCFILE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SRCFILE_DATA));
    #endif

        return this;
    }

     
    
    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    srcFile_InputAdvance (
        SRCFILE_DATA    *this,
        uint16_t        numChrs
    )
    {
        uint32_t        i;
        TOKEN_DATA      *pToken = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcFile_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        // Shift inputs.
        for (i=0; i<numChrs; ++i) {
            eRc = srcFile_InputNextChar(this);
        }
        
        pToken = &this->pInputs[this->curInputs];
        
        // Return to caller.
        return pToken;
    }
    
    
    
    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    TOKEN_DATA *    srcFile_InputLookAhead (
        SRCFILE_DATA    *this,
        uint16_t        num
    )
    {
        uint16_t        idx;
        TOKEN_DATA      *pToken = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!srcFile_Validate( this )) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (num > this->sizeInputs) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        idx = (this->curInputs + num - 1) % this->sizeInputs;
        pToken = &this->pInputs[idx];
        
        // Return to caller.
        return pToken;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                  I n p u t  N e x t  C h a r
    //--------------------------------------------------------------
    
    ERESULT             srcFile_InputNextChar(
        SRCFILE_DATA        *this
    )
    {
        ERESULT             eRc;
        TOKEN_DATA          *pToken;
        TEXTIN_CHRLOC       chrLoc;
        W32CHR_T            chr;
        int32_t             cls;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        chr = textIn_NextChar((TEXTIN_DATA *)this);
        if (chr >= 0) {
            cls = ascii_toLexicalClassW32(chr);
        }
        else {
            cls = EOF;
        }
        
        // Add the next char to the queue.
        pToken = &this->pInputs[this->curInputs];
        this->fInit = 1;
        token_InitCharW32(
                          pToken,
                          &this->super.curChr.loc,
                          cls,
                          chr
        );
        this->curInputs = (this->curInputs + 1) % this->sizeInputs;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         srcFile_IsEnabled (
        SRCFILE_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
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
        void        *pMethod = srcFile_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "srcFile", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          srcFile_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SRCFILE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCFILE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)srcFile_Class();
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
                            return srcFile_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return srcFile_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return srcFile_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return srcFile_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == srcFile_ToDebugString)
                    return "ToDebugString";
                if (pData == srcFile_ToJSON)
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
    
     ASTR_DATA *     srcFile_ToJSON (
        SRCFILE_DATA      *this
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!srcFile_Validate(this)) {
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
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = srcFile_ToDebugString(this,4);
     @endcode 
     @param     this    SRCFILE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     srcFile_ToDebugString (
        SRCFILE_DATA      *this,
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
        if (!srcFile_Validate(this)) {
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
                    srcFile_getSize(this)
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
    bool            srcFile_Validate (
        SRCFILE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SRCFILE))
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


        if (!(obj_getSize(this) >= sizeof(SRCFILE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


