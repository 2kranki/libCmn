// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   textIn.c
 *	Generated 11/23/2017 23:46:18
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
#include    <textIn_internal.h>
#include    <ascii.h>
#include    <szTbl.h>
#include    <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ERESULT         textIn_FileGetc(
        TEXTIN_DATA     *this,
        W32CHR_T        *pChar
    )
    {
        W32CHR_T        chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        chr = fgetwc(this->pFile);
        if( chr == ASCII_CPM_EOF ) {
            while ((chr = fgetwc(this->pFile)) != EOF) {
            }
        }
        *pChar = chr;
        
        return ERESULT_SUCCESS;
    }
    
    
    
    static
    ERESULT         textIn_u8ArrayGetc(
        TEXTIN_DATA     *this,
        W32CHR_T        *pChar
    )
    {
        char            chrs[8];
        W32CHR_T        chr = -1;
        uint32_t        len;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textIn_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        chrs[0] = 0;
        ++this->fileOffset;
        chrs[0] = u8Array_Get(this->pU8Array, (uint32_t)this->fileOffset);
        if (0 == chrs[0]) {
            *pChar = EOF;
            return ERESULT_EOF_ERROR;
        }
        if (chrs[0] > 0x7F) {
            len = utf8_ChrLen(chrs[0]);
            --len;
            chr = 1;
            while (len--) {
                ++this->fileOffset;
                chrs[chr++] = u8Array_Get(this->pU8Array, (uint32_t)this->fileOffset);
                if (0 == chrs[0]) {
                    *pChar = EOF;
                    return ERESULT_EOF_ERROR;
                }
            }
            len = utf8_Utf8ToW32(chrs, &chr);
        }
        if( chr == ASCII_CPM_EOF ) {
            this->fileOffset = u8Array_getSize(this->pU8Array);
            chr = EOF;
        }
        *pChar = chr;
        
        return ERESULT_SUCCESS;
    }
    
    
    
    static
    W32CHR_T        textIn_UnicodeGetc(
        TEXTIN_DATA     *this
    )
    {
        ERESULT         eRc;
        W32CHR_T        chr = EOF;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textIn_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        switch (this->type) {
                
            case TEXTIN_TYPE_FILE:
                eRc = textIn_FileGetc(this, &chr);
                if (ERESULT_HAS_FAILED(eRc) || (chr == EOF) || feof(this->pFile)) {
                    chr = EOF;
                }
                break;
                
            case TEXTIN_TYPE_ASTR:
                chr = AStr_CharGetW32(this->pAStr, (uint32_t)this->fileOffset++ );
                if( chr == ASCII_CPM_EOF ) {
                    this->fileOffset = AStr_getLength(this->pAStr);
                    chr = EOF;
                }
                break;
                
            case TEXTIN_TYPE_U8ARRAY:
                eRc = textIn_u8ArrayGetc(this, &chr);
                if (ERESULT_HAS_FAILED(eRc)) {
                    chr = EOF;
                }
                break;
                
            case TEXTIN_TYPE_WSTR:
                chr = WStr_CharGetW32(this->pWStr, (uint32_t)this->fileOffset++ );
                if( chr == ASCII_CPM_EOF ) {
                    this->fileOffset = WStr_getLength(this->pWStr);
                    chr = EOF;
                }
                break;
                
            default:
                chr = EOF;
                break;
        }
        
        return chr;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TEXTIN_DATA *   textIn_Alloc(
    )
    {
        TEXTIN_DATA     *this;
        uint32_t        cbSize = sizeof(TEXTIN_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TEXTIN_DATA *     textIn_New(
    )
    {
        TEXTIN_DATA       *this;
        
        this = textIn_Alloc( );
        if (this) {
            this = textIn_Init(this, OBJ_NIL, 0);
        } 
        return this;
    }


    TEXTIN_DATA *   textIn_NewFromAStr(
        ASTR_DATA       *pStr,          // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        TEXTIN_DATA     *this = OBJ_NIL;
        
        this = textIn_Alloc( );
        if (this) {
            this = textIn_InitAStr(this, pStr, pFilePath, tabSize);
        }
        
        return this;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         textIn_getLastError(
        TEXTIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            textIn_setLastError(
        TEXTIN_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                           P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *     textIn_getPath(
        TEXTIN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        textIn_setLastError(this, ERESULT_SUCCESS);
        return this->pPath;
    }
    
    
    bool            textIn_setPath(
        TEXTIN_DATA     *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        this->pPath = pValue;
        
        textIn_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        textIn_getPriority(
        TEXTIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        textIn_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            textIn_setPriority(
        TEXTIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        textIn_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        textIn_getSize(
        TEXTIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        textIn_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     textIn_getStr(
        TEXTIN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        textIn_setLastError(this, ERESULT_SUCCESS);
        return this->pAStr;
    }
    
    
    bool            textIn_setStr(
        TEXTIN_DATA     *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pAStr) {
            obj_Release(this->pAStr);
        }
        this->pAStr = pValue;
        
        textIn_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  textIn_getSuperVtbl(
        TEXTIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        textIn_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = textIn__Assign(this,pOther);
     @endcode 
     @param     this    TEXTIN object pointer
     @param     pOther  a pointer to another TEXTIN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         textIn_Assign(
        TEXTIN_DATA		*this,
        TEXTIN_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !textIn_Validate(pOther) ) {
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
        textIn_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        textIn_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return textIn_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        textIn      *pCopy = textIn_Copy(this);
     @endcode 
     @param     this    TEXTIN object pointer
     @return    If successful, a TEXTIN object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the TEXTIN object.
     */
    TEXTIN_DATA *     textIn_Copy(
        TEXTIN_DATA       *this
    )
    {
        TEXTIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = textIn_New( );
        if (pOther) {
            eRc = textIn_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        textIn_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            textIn_Dealloc(
        OBJ_ID          objId
    )
    {
        TEXTIN_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if ((this->type == TEXTIN_TYPE_ASTR) && (this->pAStr)) {
            obj_Release(this->pAStr);
            this->pAStr = OBJ_NIL;
        }
        
        if ((this->type == TEXTIN_TYPE_FILE) && (this->pFile)) {
            fclose(this->pFile);
            this->pFile = NULL;
        }
        
        if ((this->type == TEXTIN_TYPE_U8ARRAY) && (this->pU8Array)) {
            obj_Release(this->pU8Array);
            this->pU8Array = OBJ_NIL;
        }
        
        if ((this->type == TEXTIN_TYPE_WSTR) && (this->pWStr)) {
            obj_Release(this->pWStr);
            this->pWStr = OBJ_NIL;
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

    ERESULT         textIn_Disable(
        TEXTIN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        textIn_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         textIn_Enable(
        TEXTIN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        textIn_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TEXTIN_DATA *   textIn_Init(
        TEXTIN_DATA     *this,
        PATH_DATA       *pPath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        uint32_t        cbSize = sizeof(TEXTIN_DATA);
        ERESULT         eRc;
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TEXTIN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_TEXTIN);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&textIn_Vtbl);
        
        textIn_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->flags  |= FLG_EOF;
        if (pPath) {
            this->pPath  = path_Copy(pPath);
            eRc =   szTbl_StringToString(
                                         szTbl_Shared(),
                                         path_getData(this->pPath),
                                         &this->pPathA
                    );
        }
        this->lineNo  = 1;
        this->colNo   = 0;
        this->tabSize = tabSize;

    #ifdef NDEBUG
    #else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "textIn::offsetof(eRc) = %lu\n", offsetof(TEXTIN_DATA,eRc));
        //fprintf(stderr, "textIn::sizeof(TEXTIN_DATA) = %lu\n", sizeof(TEXTIN_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(TEXTIN_DATA));
    #endif

        return this;
    }

     
    TEXTIN_DATA *  textIn_InitAStr(
        TEXTIN_DATA     *this,
        ASTR_DATA       *pStr,        // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize       // Tab Spacing if any (0 will default to 4)
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_Retain(pStr);
        
        this = textIn_Init(this, pFilePath, tabSize);
        if (OBJ_NIL == this) {
            //obj_Release(this);
            obj_Release(pStr);
            return OBJ_NIL;
        }
        
        // Open the file.
        this->type = TEXTIN_TYPE_ASTR;
        this->pAStr = pStr;
        this->flags &= ~FLG_EOF;
        this->flags |= FLG_OPN;
        this->fileOffset = 1;
        
        return this;
    }
    
    
    
    TEXTIN_DATA *  textIn_InitFile(
        TEXTIN_DATA     *this,
        FILE            *pFile,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pFile) {
            fprintf( stderr, "Fatal Error - Missing input source file path.\n" );
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = textIn_Init(this, OBJ_NIL, tabSize);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        // Open the file.
        this->type = TEXTIN_TYPE_FILE;
        this->pFile = pFile;
        this->flags &= ~FLG_EOF;
        this->flags |= FLG_OPN;
        this->flags |= FLG_FILE;
        
        return this;
    }
    
    
    
    TEXTIN_DATA *  textIn_InitPath(
        TEXTIN_DATA     *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        char            *pszFileName;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pFilePath) {
            fprintf( stderr, "Fatal Error - Missing input source file path.\n" );
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = textIn_Init(this, pFilePath, tabSize);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        // Open the file.
        this->type = TEXTIN_TYPE_FILE;
        pszFileName = path_CStringA(pFilePath);
        if (pszFileName) {
            this->pFile = fopen( pszFileName, "r" );
            if (NULL == this->pFile) {
                fprintf(    stderr,
                        "Fatal Error - Could not open Input File - %s.\n",
                        pszFileName
                        );
                obj_Release(this);
                return OBJ_NIL;
            }
            this->flags &= ~FLG_EOF;
            this->flags |= FLG_OPN;
            mem_Free(pszFileName);
            pszFileName = NULL;
        }
        else {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        return this;
    }
    
    
    
    TEXTIN_DATA *  textIn_InitU8Array(
        TEXTIN_DATA     *this,
        U8ARRAY_DATA    *pBuffer,       // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pBuffer) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_Retain(pBuffer);
        
        this = textIn_Init(this, pFilePath, tabSize);
        if (OBJ_NIL == this) {
            obj_Release(this);
            obj_Release(pBuffer);
            return OBJ_NIL;
        }
        
        // Open the file.
        this->type = TEXTIN_TYPE_U8ARRAY;
        this->pU8Array = pBuffer;
        this->flags &= ~FLG_EOF;
        this->flags |= FLG_OPN;
        
        return this;
    }
    
    
    
    TEXTIN_DATA *  textIn_InitWStr(
        TEXTIN_DATA     *this,
        WSTR_DATA       *pWStr,         // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pWStr) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_Retain(pWStr);
        
        this = textIn_Init(this, pFilePath, tabSize);
        if (OBJ_NIL == this) {
            obj_Release(this);
            obj_Release(pWStr);
            return OBJ_NIL;
        }
        
        // Open the file.
        this->type = TEXTIN_TYPE_WSTR;
        this->pWStr = pWStr;
        this->flags &= ~FLG_EOF;
        this->flags |= FLG_OPN;
        this->fileOffset = 1;
        
        return this;
    }
    
    
    

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         textIn_IsEnabled(
        TEXTIN_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            textIn_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        textIn_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                     L o c a t i o n
    //---------------------------------------------------------------
    
    ERESULT         textIn_Location(
        TEXTIN_DATA     *this,
        const
        char            **ppPath,
        uint32_t        *pLineNo,
        uint16_t        *pColNo
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (ppPath)
            *ppPath = this->pPathA;
        if (pLineNo)
            *pLineNo = this->lineNo;
        if (pColNo)
            *pColNo = this->colNo;
        
        // Return to caller.
        textIn_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //--------------------------------------------------------------
    //                      N e x t  C h a r
    //--------------------------------------------------------------
    
    ERESULT             textIn_NextChar(
        TEXTIN_DATA         *this,
        W32CHR_T            *pChar
    )
    {
        W32CHR_T            chr;
        int32_t             cls;
        ERESULT             eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !textIn_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        chr = textIn_UnicodeGetc(this);
        if (chr > 0) {
            switch (chr) {
                    
                case '\b':
                    if (this->colNo) {
                        --this->colNo;
                    }
                    break;
                    
                case '\f':
                case '\n':
                    ++this->lineNo;
                    this->colNo = 0;
                    break;
                    
                case '\r':
                    this->colNo = 0;
                    break;
                    
                case '\t':
                    if( this->tabSize ) {
                        chr = ' ';
                        if( ((this->colNo-1) % this->tabSize) )
                            this->colNo += ((this->colNo-1) % this->tabSize);
                        else
                            this->colNo += this->tabSize;
                    }
                    else {
                        ++this->colNo;
                    }
                    break;
                    
                case EOF:
                    eRc = ERESULT_EOF_ERROR;
                    break;
                    
                default:
                    if (chr) {
                        ++this->colNo;
                    }
                    break;
            }
        }
        if (chr >= 0) {
            cls = ascii_toLexicalClassW32(chr);
        }
        else {
            cls = EOF;
        }
        
        // Return to caller.
        if (pChar)
            *pChar = chr;
        if (chr == EOF)
            eRc = ERESULT_DATA_NOT_FOUND;
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
        void        *pMethod = textIn_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "textIn", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          textIn_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TEXTIN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
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
                            return textIn_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return textIn_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return textIn_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return textIn_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == textIn_ToDebugString)
                    return "ToDebugString";
                if (pData == textIn_ToJSON)
                    return "ToJSON";
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
        ASTR_DATA      *pDesc = textIn_ToDebugString(this,4);
     @endcode 
     @param     this    TEXTIN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     textIn_ToDebugString(
        TEXTIN_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = textIn_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    textIn_getSize(this)
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
        
        textIn_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     textIn_ToJSON(
        TEXTIN_DATA      *this
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !textIn_Validate(this) ) {
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
        
        textIn_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            textIn_Validate(
        TEXTIN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_TEXTIN) )
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


        if( !(obj_getSize(this) >= sizeof(TEXTIN_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


