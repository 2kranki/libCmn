// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   TextIn.c
 *	Generated 01/21/2020 22:03:13
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
#include        <TextIn_internal.h>
#include        <ascii.h>
#include        <szTbl.h>
#include        <utf8.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ERESULT         TextIn_FileGetc (
        TEXTIN_DATA     *this,
        W32CHR_T        *pChar
    )
    {
        W32CHR_T        chr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
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
    ERESULT         TextIn_u8ArrayGetc (
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
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        chrs[0] = 0;
        ++this->curChr.loc.offset;
        chrs[0] = u8Array_Get(this->pU8Array, (uint32_t)this->curChr.loc.offset);
        if (0 == chrs[0]) {
            *pChar = EOF;
            return ERESULT_EOF_ERROR;
        }
        if (chrs[0] > 0x7F) {
            len = utf8_ChrLen(chrs[0]);
            --len;
            chr = 1;
            while (len--) {
                ++this->curChr.loc.offset;
                chrs[chr++] = u8Array_Get(this->pU8Array, (uint32_t)this->curChr.loc.offset);
                if (0 == chrs[0]) {
                    *pChar = EOF;
                    return ERESULT_EOF_ERROR;
                }
            }
            len = utf8_Utf8ToW32(chrs, &chr);
        }
        if( chr == ASCII_CPM_EOF ) {
            this->curChr.loc.offset = u8Array_getSize(this->pU8Array);
            chr = EOF;
        }
        *pChar = chr;

        return ERESULT_SUCCESS;
    }



    static
    W32CHR_T        TextIn_UnicodeGetc (
        TEXTIN_DATA     *this
    )
    {
        ERESULT         eRc;
        W32CHR_T        chr = EOF;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        switch (this->type) {

            case TEXTIN_TYPE_FILE:
                eRc = TextIn_FileGetc(this, &chr);
                if (ERESULT_HAS_FAILED(eRc) || (chr == EOF) || feof(this->pFile)) {
                    chr = EOF;
                }
                break;

            case TEXTIN_TYPE_ASTR:
                chr = AStr_CharGetW32(this->pAStr, (uint32_t)this->curChr.loc.offset++);
                if ((chr == ASCII_CPM_EOF) || (chr == EOF)){
                    this->curChr.loc.offset = AStr_getLength(this->pAStr);
                    chr = EOF;
                }
                break;

            case TEXTIN_TYPE_U8ARRAY:
                eRc = TextIn_u8ArrayGetc(this, &chr);
                if (ERESULT_HAS_FAILED(eRc)) {
                    chr = EOF;
                }
                break;

            case TEXTIN_TYPE_WSTR:
                chr = W32Str_CharGetW32(this->pWStr, (uint32_t)this->curChr.loc.offset++ );
                if( chr == ASCII_CPM_EOF ) {
                    this->curChr.loc.offset = W32Str_getLength(this->pWStr);
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

    TEXTIN_DATA *     TextIn_Alloc (
        void
    )
    {
        TEXTIN_DATA       *this;
        uint32_t        cbSize = sizeof(TEXTIN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TEXTIN_DATA *     TextIn_New (
        void
    )
    {
        TEXTIN_DATA       *this;
        
        this = TextIn_Alloc( );
        if (this) {
            this = TextIn_Init(this);
        } 
        return this;
    }

    TEXTIN_DATA *   TextIn_NewFromAStr (
        PATH_DATA       *pFilePath,
        ASTR_DATA       *pStr,          // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        TEXTIN_DATA     *this = OBJ_NIL;
        ERESULT         eRc;

        this = TextIn_New( );
        if (this) {
            eRc = TextIn_SetupAStr(this, pFilePath, pStr, fileIndex, tabSize);
        }

        return this;
    }


    TEXTIN_DATA *   TextIn_NewFromFile (
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        FILE            *pFile,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        TEXTIN_DATA     *this = OBJ_NIL;
        ERESULT         eRc;

        this = TextIn_New( );
        if (this) {
            eRc = TextIn_SetupFile(this, pFilePath, fileIndex, pFile, tabSize);
        }

        return this;
    }


    TEXTIN_DATA *   TextIn_NewFromPath (
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        TEXTIN_DATA     *this = OBJ_NIL;
        ERESULT         eRc;

        this = TextIn_New( );
        if (this) {
            eRc = TextIn_SetupPath(this, pFilePath, fileIndex, tabSize);
        }

        return this;
    }





    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //              8 0  C o l u m n  C a r d s
    //---------------------------------------------------------------

    bool            TextIn_getCols80 (
        TEXTIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return this->fCols80;
    }


    bool            TextIn_setCols80 (
        TEXTIN_DATA     *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fCols80 = fValue ? 1 : 0;

        return true;
    }



    //---------------------------------------------------------------
    //                    F i l e  I n d e x
    //---------------------------------------------------------------

    uint16_t        TextIn_getFileIndex (
        TEXTIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->curChr.loc.fileIndex;
    }


    bool            TextIn_setFileIndex (
        TEXTIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->curChr.loc.fileIndex = value;

        return true;
    }



    //---------------------------------------------------------------
    //                           P a t h
    //---------------------------------------------------------------

    PATH_DATA *     TextIn_getPath (
        TEXTIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pPath;
    }


    bool            TextIn_setPath (
        TEXTIN_DATA     *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        this->pPath = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                  R e m o v e  N L s
    //---------------------------------------------------------------

    bool            TextIn_getRemoveNLs (
        TEXTIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->fStripNL;
    }


    bool            TextIn_setRemoveNLs (
        TEXTIN_DATA     *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fStripNL = fValue ? 1 : 0;

        return true;
    }



    //---------------------------------------------------------------
    //  C h e c k  8 0  C o l u m n  C a r d  S e q u e n c e  N u m
    //---------------------------------------------------------------

    bool            TextIn_getSeq80 (
        TEXTIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return this->fSeq80;
    }


    bool            TextIn_setSeq80 (
        TEXTIN_DATA     *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fSeq80 = fValue ? 1 : 0;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        TextIn_getSize (
        TEXTIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * TextIn_getStr (
        TEXTIN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pAStr;
    }
    
    
    bool        TextIn_setStr (
        TEXTIN_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_STR_OWNED
        obj_Retain(pValue);
        if (this->pAStr) {
            obj_Release(this->pAStr);
        }
#endif
        this->pAStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  TextIn_getSuperVtbl (
        TEXTIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                       T a b  S i z e
    //---------------------------------------------------------------

    uint16_t        TextIn_getTabSize (
        TEXTIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->tabSize;
    }


    bool            TextIn_setTabSize (
        TEXTIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->tabSize = value;

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
        ERESULT eRc = TextIn_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another TEXTIN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         TextIn_Assign (
        TEXTIN_DATA		*this,
        TEXTIN_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!TextIn_Validate(pOther)) {
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
    //                        C l o s e
    //---------------------------------------------------------------

    ERESULT         TextIn_Close (
        TEXTIN_DATA   *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        switch (this->type) {

            case TEXTIN_TYPE_ASTR:
                if (this->pAStr) {
                    obj_Release(this->pAStr);
                    this->pAStr = OBJ_NIL;
                }
                break;

            case TEXTIN_TYPE_FILE:
                if (this->pFile) {
                    if (0 == this->fFile) {
                        fclose(this->pFile);
                    }
                    this->pFile = NULL;
                }
                break;

            case TEXTIN_TYPE_U8ARRAY:
                if (this->pU8Array) {
                    obj_Release(this->pU8Array);
                    this->pU8Array = OBJ_NIL;
                }
                break;

            case TEXTIN_TYPE_WSTR:
                if (this->pWStr) {
                    obj_Release(this->pWStr);
                    this->pWStr = OBJ_NIL;
                }
                break;

       }
        this->fFile = 0;
        this->fOpen = 0;
        this->type = TEXTIN_TYPE_UNKNOWN;

        if (this->pSidx) {
            sidxe_Reset(this->pSidx);
        }

        // Return to caller.
        return ERESULT_SUCCESS;
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
    ERESULT         TextIn_Compare (
        TEXTIN_DATA     *this,
        TEXTIN_DATA     *pOther
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
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!TextIn_Validate(pOther)) {
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
        TextIn      *pCopy = TextIn_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TEXTIN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TEXTIN_DATA *     TextIn_Copy (
        TEXTIN_DATA       *this
    )
    {
        TEXTIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = TextIn_New( );
        if (pOther) {
            eRc = TextIn_Assign(this, pOther);
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

    void            TextIn_Dealloc (
        OBJ_ID          objId
    )
    {
        TEXTIN_DATA     *this = objId;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((TEXTIN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        eRc = TextIn_Close(this);
        TextIn_setPath(this, OBJ_NIL);

        if (this->pSidx) {
            obj_Release(this->pSidx);
            this->pSidx = OBJ_NIL;
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
        TextIn      *pDeepCopy = TextIn_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TEXTIN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TEXTIN_DATA *     TextIn_DeepyCopy (
        TEXTIN_DATA       *this
    )
    {
        TEXTIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = TextIn_New( );
        if (pOther) {
            eRc = TextIn_Assign(this, pOther);
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
    ERESULT         TextIn_Disable (
        TEXTIN_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
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
    ERESULT         TextIn_Enable (
        TEXTIN_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
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
    //                          G e t  L i n e
    //---------------------------------------------------------------

    //TODO: Think about returning an AStrC or W32StrC instead of the
    // buffer to allow for long lines.
    //TODO: Terminate line with '\0'.
    ERESULT         TextIn_GetLine (
        TEXTIN_DATA     *this,
        char            *pBuffer,
        int             size,
        SRCLOC          *pLoc
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        W32CHR_T        chr;
        int             chrSize;
        SRCLOC          loc = {0};
        char            chrData[11];
        bool            fMore = true;
        bool            fLoc = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pBuffer) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (size > 1)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        *pBuffer = '\0';
        --size;                         // Allow space for trailing NUL.

        while (fMore) {
            chr = TextIn_NextChar(this);
            switch (chr) {
                case '\n':
                    fMore = false;
                    break;
                case '\r':
                    break;
                case ASCII_CPM_EOF:
                case EOF:
                    eRc = ERESULT_EOF_ERROR;
                    fMore = false;
                    break;
                default:
                    if (!fLoc) {
                        loc = this->curChr.loc;
                        fLoc = true;
                    }
                    chrSize = utf8_W32ToChrCon(chr, chrData);
                    if (chrSize && (chrSize < size)) {
                        str_Concat(pBuffer, size, chrData);
                        pBuffer += chrSize;
                        size -= chrSize;
                    }
                    else {
                        fMore = false;
                        this->savChr = this->curChr;
                        obj_FlagOn(this, TEXTIN_FLAG_SAVCHR);
                    }
                    break;
            }
        }

        // Return to caller.
        if (pLoc) {
            *pLoc = loc;
        }
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TEXTIN_DATA *   TextIn_Init (
        TEXTIN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(TEXTIN_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TEXTIN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&TextIn_Vtbl);
        
        #if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
                this->pSidx = sidxe_NewWithMax(3072);
                if (OBJ_NIL == this->pSidx) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }
        #endif
        #if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
                this->pSidx = sidxe_NewWithMax(3072);
                if (OBJ_NIL == this->pSidx) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }
        #endif

#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        fprintf(
                stderr, 
                "TextIn::sizeof(TEXTIN_DATA) = %lu\n", 
                sizeof(TEXTIN_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(TEXTIN_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         TextIn_IsEnabled (
        TEXTIN_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
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
    //                     L o c a t i o n
    //---------------------------------------------------------------

    ERESULT         TextIn_Location (
        TEXTIN_DATA     *this,
        uint16_t        *pFilenameIndex,
        size_t          *pOffset,
        uint32_t        *pLineNo,
        uint16_t        *pColNo
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (pFilenameIndex)
            *pFilenameIndex = this->filenameIndex;
        if (pOffset)
            *pOffset = this->curChr.loc.offset;
        if (pLineNo)
            *pLineNo = this->curChr.loc.lineNo;
        if (pColNo)
            *pColNo = this->curChr.loc.colNo;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //--------------------------------------------------------------
    //                      N e x t  C h a r
    //--------------------------------------------------------------

    W32CHR_T            TextIn_NextChar (
        TEXTIN_DATA         *this
    )
    {
        W32CHR_T            chr = 0;
        ERESULT             eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextIn_Validate( this ) ) {
            DEBUG_BREAK();
            return -2;
        }
#endif

    again:
        switch (this->state) {
            case TEXTIN_STATE_IN_TAB:
                if (this->curChr.loc.colNo % this->tabSize) {
                    chr = ' ';
                    ++this->curChr.loc.colNo;
                    break;
                }
                this->state = TEXTIN_STATE_NORMAL;

            case TEXTIN_STATE_NORMAL:
                if (obj_Flag(this, TEXTIN_FLAG_SAVCHR)) {
                    this->curChr = this->savChr;
                    obj_FlagOff(this, TEXTIN_FLAG_SAVCHR);
                    break;
                }
                else {
                    chr = TextIn_UnicodeGetc(this);
                }
                if (chr > 0) {
                    switch (chr) {

                        case '\b':
                            if (this->curChr.loc.colNo) {
                                --this->curChr.loc.colNo;
                            }
                            break;

                        case 0x85:              // Unicode NEL
                            chr = '\n';

                        case '\f':
                        case '\n':
                            ++this->curChr.loc.lineNo;
                            this->curChr.loc.colNo = 0;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
                            sidxe_Add(this->pSidx, &this->curChr.loc);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
                            sidxe_Add(this->pSidx, &this->curChr.loc);
#endif
                            if (this->fStripNL && ('\n' == chr))
                                goto again;
                            break;

                        case '\r':
                            this->curChr.loc.colNo = 0;
                            if (this->fStripCR)
                                goto again;
                            break;

                        case '\t':
                            if( this->tabSize ) {
                                chr = ' ';
                                ++this->curChr.loc.colNo;
                                this->state = TEXTIN_STATE_IN_TAB;
                            }
                            else {
                                ++this->curChr.loc.colNo;
                            }
                            break;

                        case EOF:
                            eRc = ERESULT_EOF_ERROR;
                            break;

                        default:
                            if (chr) {
                                ++this->curChr.loc.colNo;
                            }
                            break;
                    }
                }
                break;

            default:
                break;
        }

        if (chr >= 0) {
            this->curChr.cls = ascii_toLexicalClassW32(chr);
        }
        else {
            this->curChr.cls = EOF;
        }

        // Return to caller.
        return chr;
    }


    ERESULT         TextIn_NextChrLoc (
        TEXTIN_DATA     *this,
        TEXTIN_CHAR     *pChr
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        TextIn_NextChar(this);
        if (pChr) {
            *pChr = this->curChr;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
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
        void        *pMethod = TextIn_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "TextIn", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          TextIn_QueryInfo (
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
        if (!TextIn_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TEXTIN_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)TextIn_Class();
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
                            return TextIn_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return TextIn_Enable;
                        }
                        break;

#ifdef  TEXTIN_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return TextIn_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return TextIn_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return TextIn_ToDebugString;
                        }
#ifdef  TEXTIN_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return TextIn_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == TextIn_ToDebugString)
                    return "ToDebugString";
#ifdef  TEXTIN_JSON_SUPPORT
                if (pData == TextIn_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t u p
    //---------------------------------------------------------------

    ERESULT         TextIn_SetupBase(
        TEXTIN_DATA     *this,
        PATH_DATA       *pPath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = TextIn_Close(this);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        TextIn_setPath(this, OBJ_NIL);

        // We must reset all the fields here.
        this->type = TEXTIN_TYPE_UNKNOWN;
        this->tabSize = tabSize;
        this->state = TEXTIN_STATE_NORMAL;
        this->fFile = 0;
        this->fOpen = 0;
        this->fStripCR = 0;
        this->fStripNL = 0;
        this->fAtEOF = 1;
        if (pPath) {
            this->pPath  = path_Copy(pPath);
            if (OBJ_NIL == this->pPath) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
            path_Clean(this->pPath);
            this->pPathA =  szTbl_StringToString(
                                        szTbl_Shared(),
                                        path_getData(this->pPath)
                            );
        }
        this->curChr.loc.lineNo  = 1;
        this->curChr.loc.colNo   = 0;
        this->state = TEXTIN_STATE_NORMAL;

        return ERESULT_SUCCESS;
    }


    ERESULT         TextIn_SetupAStr(
        TEXTIN_DATA     *this,
        PATH_DATA       *pFilePath,
        ASTR_DATA       *pStr,        // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize       // Tab Spacing if any (0 will default to 4)
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = TextIn_SetupBase(this, pFilePath, tabSize);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }

        // Open the file.
        this->type = TEXTIN_TYPE_ASTR;
        obj_Retain(pStr);
        this->pAStr = pStr;
        this->fAtEOF = 0;
        this->fOpen = 1;
        this->curChr.loc.fileIndex = fileIndex;
        this->curChr.loc.offset = 1;    // AStr is relative to 1.

        return ERESULT_SUCCESS;
    }


    ERESULT         TextIn_SetupFile (
        TEXTIN_DATA     *this,
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        FILE            *pFile,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pFile) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = TextIn_SetupBase((TEXTIN_DATA *)this, pFilePath, tabSize);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }

        // Open the file.
        this->type = TEXTIN_TYPE_FILE;
        this->pFile = pFile;
        this->fAtEOF = 0;
        this->fOpen = 1;
        this->fFile = 1;

        return ERESULT_SUCCESS;
    }


    ERESULT         TextIn_SetupPath (
        TEXTIN_DATA     *this,
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        char            *pszFileName;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pFilePath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = TextIn_SetupBase((TEXTIN_DATA *)this, pFilePath, tabSize);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        // Open the file.
        this->type = TEXTIN_TYPE_FILE;
        pszFileName = path_CStringA(this->pPath);
        if (pszFileName) {
            this->pFile = fopen(pszFileName, "r");
            if (NULL == this->pFile) {
                mem_Free(pszFileName);
                return ERESULT_FILE_NOT_FOUND;
            }
            this->fAtEOF = 0;
            this->fFile = 0;
            this->fOpen = 1;
            mem_Free(pszFileName);
            pszFileName = NULL;
        }
        else {
            eRc = ERESULT_GENERAL_FAILURE;
        }

        return eRc;
    }


    ERESULT  TextIn_SetupU8Array (
        TEXTIN_DATA     *this,
        U8ARRAY_DATA    *pBuffer,       // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pBuffer) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = TextIn_SetupBase((TEXTIN_DATA *)this, pFilePath, tabSize);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        // Open the file.
        this->type = TEXTIN_TYPE_U8ARRAY;
        obj_Retain(pBuffer);
        this->pU8Array = pBuffer;
        this->fAtEOF = 0;
        this->fOpen = 1;

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = TextIn_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     TextIn_ToDebugString (
        TEXTIN_DATA      *this,
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
        if (!TextIn_Validate(this)) {
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
                    TextIn_getSize(this),
                    obj_getRetainCount(this)
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
    bool            TextIn_Validate (
        TEXTIN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_TEXTIN))
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


        if (!(obj_getSize(this) >= sizeof(TEXTIN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


