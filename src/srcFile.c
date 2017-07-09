// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   srcFile.c
 *	Generated 06/17/2015 11:21:15
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
#include    "srcFile_internal.h"
#include    "ascii.h"
#include    "szTbl.h"
#include    "trace.h"
#include    "utf8.h"
#include    <stdio.h>
#include    <wchar.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    int32_t         srcFile_UnicodeGetc(
        SRCFILE_DATA    *this
    );
    
    
    static
    ERESULT         srcFile_FileGetc(
        SRCFILE_DATA    *this,
        int32_t         *pChar
    )
    {
        int32_t         chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) ) {
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
    ERESULT         srcFile_u8ArrayGetc(
        SRCFILE_DATA    *this,
        int32_t         *pChar
    )
    {
        char            chrs[8];
        int32_t         chr = -1;
        uint32_t        len;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) ) {
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
            len = utf8_Utf8ToWC(chrs, &chr);
        }
        if( chr == ASCII_CPM_EOF ) {
            this->fileOffset = u8Array_getSize(this->pU8Array);
            chr = EOF;
        }
        *pChar = chr;
        
        return ERESULT_SUCCESS;
    }
    
    
    
    static
    int32_t         srcFile_UnicodeGetc(
        SRCFILE_DATA    *this
    )
    {
        ERESULT         eRc;
        int32_t         chr = EOF;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        switch (this->type) {
                
            case OBJ_IDENT_FILE:
                eRc = srcFile_FileGetc(this, &chr);
                if (ERESULT_HAS_FAILED(eRc) || (chr == EOF) || feof(this->pFile)) {
                    chr = EOF;
                }
                break;
                
            case OBJ_IDENT_FBSI:
                eRc = fbsi_Getwc(this->pFbsi, &chr );
                if (ERESULT_HAS_FAILED(eRc)) {
                    chr = EOF;
                }
                if( chr == ASCII_CPM_EOF ) {
                    while ((chr != EOF) && ERESULT_IS_SUCCESSFUL(eRc)) {
                        eRc = fbsi_Getwc(this->pFbsi, &chr );
                    }
                    chr = EOF;
                }
                break;
                
            case OBJ_IDENT_ASTR:
                chr = AStr_CharGetW(this->pAStr, (uint32_t)this->fileOffset++ );
                if( chr == ASCII_CPM_EOF ) {
                    this->fileOffset = AStr_getLength(this->pAStr);
                    chr = EOF;
                }
                break;
                
            case OBJ_IDENT_U8ARRAY:
                eRc = srcFile_u8ArrayGetc(this, &chr);
                if (ERESULT_HAS_FAILED(eRc)) {
                    chr = EOF;
                }
                break;
                
            case OBJ_IDENT_WSTR:
                chr = WStr_CharGetW(this->pWStr, (uint32_t)this->fileOffset++ );
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

    SRCFILE_DATA *     srcFile_Alloc(
    )
    {
        SRCFILE_DATA    *this;
        uint32_t        cbSize = sizeof(SRCFILE_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool            srcFile_getExpandTabs(
        SRCFILE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return (this->flags & FLG_TAB) ? true : false;
    }
    
    
    bool            srcFile_setExpandTabs(
        SRCFILE_DATA    *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (value) {
            this->flags |= FLG_TAB;
        }
        else {
            this->flags &= ~FLG_TAB;
        }
        
        return true;
    }
    
    
    
    bool            srcFile_getReuse(
        SRCFILE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) )
            return false;
#endif
        
        // Return to caller.
        return this->fReuse;
    }
    
    
    bool            srcFile_setReuse(
        SRCFILE_DATA    *this,
        bool            fValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) )
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
    
    
    
    bool            srcFile_getStripCR(
        SRCFILE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) )
            return false;
#endif
        
        // Return to caller.
        return this->fStripCR;
    }
    
    
    bool            srcFile_setStripCR(
        SRCFILE_DATA    *this,
        bool            fValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) )
            return false;
#endif
        
        this->fStripCR = fValue;
        
        // Return to caller.
        return true;
    }
    
    
    
    uint16_t        srcFile_getTabSize(
        SRCFILE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        return this->tabSize;
    }

    bool            srcFile_setTabSize(
        SRCFILE_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        this->tabSize = value;
        return true;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            srcFile_Dealloc(
        OBJ_ID          objId
    )
    {
        SRCFILE_DATA    *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !srcFile_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if ((this->type == OBJ_IDENT_FBSI) && (this->pFbsi)) {
            obj_Release(this->pFbsi);
            this->pFbsi = OBJ_NIL;
        }
        
        if ((this->type == OBJ_IDENT_FILE) && (this->pFile)) {
            fclose(this->pFile);
            this->pFile = NULL;
        }
        
        if ((this->type == OBJ_IDENT_ASTR) && (this->pAStr)) {
            obj_Release(this->pAStr);
            this->pAStr = OBJ_NIL;
        }
        
        if ((this->type == OBJ_IDENT_U8ARRAY) && (this->pU8Array)) {
            obj_Release(this->pU8Array);
            this->pU8Array = OBJ_NIL;
        }
        
        if ((this->type == OBJ_IDENT_WSTR) && (this->pWStr)) {
            obj_Release(this->pWStr);
            this->pWStr = OBJ_NIL;
        }
        
        if (this->pPath) {
            obj_Release(this->pPath);
            this->pPath = OBJ_NIL;
        }
        
        if (this->pTokens) {
            obj_Release(this->pTokens);
            this->pTokens = OBJ_NIL;
        }
        
        if (this->pInputs) {
            mem_Free(this->pInputs);
            this->pInputs = OBJ_NIL;
            this->sizeInputs = 0;
            this->curInputs = 0;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SRCFILE_DATA *  srcFile_Init(
        SRCFILE_DATA    *this,
        PATH_DATA       *pPath,
        uint16_t		tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs,
        bool            fRemoveNLs
    )
    {
        TOKEN_DATA      *pToken;
        ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_SRCFILE );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&srcFile_Vtbl);

        obj_setSize( &this->curchr, sizeof(TOKEN_DATA) );
        pToken = token_Init(&this->curchr);
        if (OBJ_NIL == pToken) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        if( fRemoveNLs )
            this->flags |= FLG_NNL;
        if( fExpandTabs )
            this->flags |= FLG_TAB;
        this->flags  |= FLG_EOF;
        if (pPath) {
            this->pPath  = path_Copy(pPath);
            eRc =   szTbl_StringToString(
                                szTbl_Shared(),
                                path_getData(this->pPath),
                                &this->pFileName
                    );
        }
        this->lineNo  = 1;
        this->colNo   = 0;
        this->tabSize = tabSize;
        
        this->sizeInputs = 4;
        this->pInputs = mem_Calloc(this->sizeInputs, sizeof(TOKEN_DATA));
        if (NULL == this->pInputs) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !srcFile_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->lineNo);
    #endif

        return this;
    }

     

    SRCFILE_DATA *  srcFile_InitFile(
        SRCFILE_DATA    *cbp,
        PATH_DATA       *pFilePath,
        uint16_t		tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs,
        bool            fRemoveNLs
    )
    {
        char            *pszFileName;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pFilePath) {
            fprintf( stderr, "Fatal Error - Missing input source file path.\n" );
            obj_Release(cbp);
            return OBJ_NIL;
        }
        
        cbp = srcFile_Init( cbp, pFilePath, tabSize, fExpandTabs, fRemoveNLs );
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        // Open the file.
        cbp->type = OBJ_IDENT_FILE;
        pszFileName = path_CStringA(pFilePath);
        if (pszFileName) {
            cbp->pFile = fopen( pszFileName, "r" );
            if (NULL == cbp->pFile) {
                fprintf(    stderr,
                            "Fatal Error - Could not open Input File - %s.\n",
                            pszFileName
                );
                obj_Release(cbp);
                return OBJ_NIL;
            }
            cbp->flags &= ~FLG_EOF;
            cbp->flags |= FLG_OPN;
            mem_Free(pszFileName);
            pszFileName = NULL;
        }
        else {
            obj_Release(cbp);
            return OBJ_NIL;
        }
        
        srcFile_InputAdvance(cbp, cbp->sizeInputs);
        
        return cbp;
    }
    
    
    
    SRCFILE_DATA *  srcFile_InitAStr(
        SRCFILE_DATA    *this,
        ASTR_DATA       *pStr,        // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t		tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs,
        bool            fRemoveNLs
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
        
        this = srcFile_Init( this, pFilePath, tabSize, fExpandTabs, fRemoveNLs );
        if (OBJ_NIL == this) {
            //obj_Release(this);
            obj_Release(pStr);
            return OBJ_NIL;
        }
        
        // Open the file.
        this->type = OBJ_IDENT_ASTR;
        this->pAStr = pStr;
        this->flags &= ~FLG_EOF;
        this->flags |= FLG_OPN;
        this->fileOffset = 1;
        
        srcFile_InputAdvance(this, this->sizeInputs);
        
        return this;
    }
    
    
    
    SRCFILE_DATA *  srcFile_InitU8Array(
        SRCFILE_DATA    *cbp,
        U8ARRAY_DATA    *pBuffer,       // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t		tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs,
        bool            fRemoveNLs
    )
    {
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pBuffer) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        obj_Retain(pBuffer);
        
        cbp = srcFile_Init( cbp, pFilePath, tabSize, fExpandTabs, fRemoveNLs );
        if (OBJ_NIL == cbp) {
            obj_Release(cbp);
            obj_Release(pBuffer);
            return OBJ_NIL;
        }
        
        // Open the file.
        cbp->type = OBJ_IDENT_U8ARRAY;
        cbp->pU8Array = pBuffer;
        cbp->flags &= ~FLG_EOF;
        cbp->flags |= FLG_OPN;
        
        srcFile_InputAdvance(cbp, cbp->sizeInputs);
        
        return cbp;
    }
    
    
    
    SRCFILE_DATA *  srcFile_InitWStr(
        SRCFILE_DATA    *cbp,
        WSTR_DATA       *pWStr,         // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t		tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs,
        bool            fRemoveNLs
    )
    {
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pWStr) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        obj_Retain(pWStr);
        
        cbp = srcFile_Init( cbp, pFilePath, tabSize, fExpandTabs, fRemoveNLs );
        if (OBJ_NIL == cbp) {
            obj_Release(cbp);
            obj_Release(pWStr);
            return OBJ_NIL;
        }
        
        // Open the file.
        cbp->type = OBJ_IDENT_WSTR;
        cbp->pWStr = pWStr;
        cbp->flags &= ~FLG_EOF;
        cbp->flags |= FLG_OPN;
        cbp->fileOffset = 1;
        
        srcFile_InputAdvance(cbp, cbp->sizeInputs);
        
        return cbp;
    }
    
    
    
    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    srcFile_InputAdvance(
        SRCFILE_DATA    *this,
        uint16_t        numChrs
    )
    {
        uint32_t        i;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        // Shift inputs.
        for (i=0; i<numChrs; ++i) {
            srcFile_InputNextChar(this);
        }
        
        pToken = &this->pInputs[this->curInputs];
        
        // Return to caller.
        return pToken;
    }
    
    
    
    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    TOKEN_DATA *    srcFile_InputLookAhead(
        SRCFILE_DATA    *this,
        uint16_t        num
    )
    {
        uint16_t        idx;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) ) {
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
        int32_t             chr;
        TOKEN_DATA          *pToken;
        int32_t             cls;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcFile_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        chr = srcFile_UnicodeGetc(this);
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
                    
                default:
                    if (chr) {
                        ++this->colNo;
                    }
                    break;
            }
        }
        if (chr >= 0) {
            cls = ascii_toLexicalClassW(chr);
        }
        else {
            cls = EOF;
        }
        
        // Add the next char to the queue.
        pToken = &this->pInputs[this->curInputs];
        obj_FlagOff(pToken, OBJ_FLAG_INIT);
        token_InitCharW(
                       pToken,
                       this->pFileName,
                       this->lineNo,
                       this->colNo,
                       cls,
                       chr
        );
        this->curInputs = (this->curInputs + 1) % this->sizeInputs;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     srcFile_ToDebugString(
        SRCFILE_DATA    *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(srcFile) path=%s ",
                     this,
                     path_getData(this->pPath)
                     );
        AStr_AppendA(pStr, str);
        
        switch (this->type) {
                
            case OBJ_IDENT_FILE:
                AStr_AppendA(pStr, "Type=FILE\n");
                break;
                
            case OBJ_IDENT_FBSI:
                AStr_AppendA(pStr, "Type=FBSI\n");
                break;
                
            case OBJ_IDENT_ASTR:
                AStr_AppendA(pStr, "Type=AStr\n");
                if (this->pAStr) {
                    if (((OBJ_DATA *)(this->pAStr))->pVtbl->pToDebugString) {
                        pWrkStr =   ((OBJ_DATA *)(this->pAStr))->pVtbl->pToDebugString(
                                                        this->pAStr,
                                                        indent+3
                                    );
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                    }
                }
                break;
                
            case OBJ_IDENT_U8ARRAY:
                AStr_AppendA(pStr, "Type=U8Array\n");
                if (this->pAStr) {
                    if (((OBJ_DATA *)(this->pU8Array))->pVtbl->pToDebugString) {
                        pWrkStr =   ((OBJ_DATA *)(this->pU8Array))->pVtbl->pToDebugString(
                                                        this->pU8Array,
                                                        indent+3
                                    );
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                    }
                }
                break;
                
            case OBJ_IDENT_WSTR:
                AStr_AppendA(pStr, "Type=WStr\n");
                if (this->pAStr) {
                    if (((OBJ_DATA *)(this->pWStr))->pVtbl->pToDebugString) {
                        pWrkStr =   ((OBJ_DATA *)(this->pWStr))->pVtbl->pToDebugString(
                                                        this->pWStr,
                                                        indent+3
                                    );
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                    }
                }
                break;
                
            default:
                AStr_AppendA(pStr, "Type=UNKNOWN\n");
                DEBUG_BREAK();
                break;
        }
        
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf( str, sizeof(str), " %p(srcFile)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            srcFile_Validate(
        SRCFILE_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_SRCFILE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(SRCFILE_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


