// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   dbCsv.c
 *	Generated 09/25/2015 21:26:41
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
#include "dbCsv_internal.h"
#include "ascii.h"
#include "str.h"
#include "wstr.h"
#include <stdio.h>
#include <wchar.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    
    
    // Look for <cr>[<lf>] or <lf>[<cr>] and discard
    // if found, but return true.
    bool            dbCsv_ParseCRLF(
        DBCSV_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW(pToken);
        if (chr == '\r') {
            srcFile_InputAdvance(this->pSrc, 1);
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            chr = token_getChrW(pToken);
            if (chr == '\n') {
                srcFile_InputAdvance(this->pSrc, 1);
            }
            this->lenFld = 0;
            return true;
        }
        else if (chr == '\n') {
            srcFile_InputAdvance(this->pSrc, 1);
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            chr = token_getChrW(pToken);
            if (chr == '\r') {
                srcFile_InputAdvance(this->pSrc, 1);
            }
            this->lenFld = 0;
            return true;
        }
        
        return false;
    }
    
    
    
    bool            dbCsv_ParseEOF(
        DBCSV_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW(pToken);
        if (chr == EOF) {
            srcFile_InputAdvance(this->pSrc, 1);
            this->lenFld = 0;
            return true;
        }
        
        return false;
    }
    
    
    
    ASTR_DATA *     dbCsv_ParseField(
        DBCSV_DATA      *this
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        TOKEN_DATA      *pToken;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = dbCsv_ParseStringEscaped(this);
        if (pStr) {
            return pStr;
        }
        pStr = dbCsv_ParseStringNonEscaped(this);
        if (pStr) {
            return pStr;
        }
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        token_ErrorFatalFLC(
                              pToken,
                              "Missing Field data"
        );
        
        return pStr;
    }

    
    
    OBJARRAY_DATA * dbCsv_ParseRecord(
        DBCSV_DATA      *this
    )
    {
        int             fieldNo = 0;
        ERESULT         eRc;
        OBJARRAY_DATA   *pRecord = OBJ_NIL;
        ASTR_DATA       *pStr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (dbCsv_ParseEOF(this)) {
            return OBJ_NIL;
        }
        
        pStr = dbCsv_ParseField(this);
        if (pStr == OBJ_NIL) {
            return OBJ_NIL;
        }
        ++fieldNo;
        
        pRecord = objArray_New();
        if (pRecord == OBJ_NIL) {
            TOKEN_DATA      *pToken;
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            token_ErrorFatalFLC(
                                pToken,
                                  "Out of memory"
            );
            return OBJ_NIL;
        }
        
        eRc = objArray_AppendObj(pRecord, pStr, NULL);
        if (ERESULT_HAS_FAILED(eRc)) {
            TOKEN_DATA      *pToken;
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            token_ErrorFatalFLC(
                                pToken,
                "Could not save field to record"
            );
        }
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        for (;;) {
            if (!dbCsv_ParseSEP(this)) {
                break;
            }
            pStr = dbCsv_ParseField(this);
            if (pStr == OBJ_NIL) {
                TOKEN_DATA      *pToken;
                pToken = srcFile_InputLookAhead(this->pSrc, 1);
                token_ErrorFatalFLC(
                                    pToken,
                                      "Malformed Record at field %d",
                                      fieldNo
                );
                return OBJ_NIL;
            }
            ++fieldNo;
            eRc = objArray_AppendObj(pRecord, pStr, NULL);
            if (ERESULT_HAS_FAILED(eRc)) {
                TOKEN_DATA      *pToken;
                pToken = srcFile_InputLookAhead(this->pSrc, 1);
                token_ErrorFatalFLC(
                                    pToken,
                                      "Could not save field to record"
                );
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        if (!dbCsv_ParseCRLF(this)) {
            TOKEN_DATA      *pToken;
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            token_ErrorFatalFLC(
                                pToken,
                                "Expected line end, but found %lc",
                                token_getChrW(pToken)
                                );
        }

        return pRecord;
    }
    
    
    
    OBJARRAY_DATA * dbCsv_ParseRecords(
        DBCSV_DATA      *this
    )
    {
        int             recordNo = 0;
        ERESULT         eRc;
        OBJARRAY_DATA   *pRecords = OBJ_NIL;
        OBJARRAY_DATA   *pRecord = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        pRecord = dbCsv_ParseRecord(this);
        if (pRecord == OBJ_NIL) {
            return OBJ_NIL;
        }
        ++recordNo;
        
        pRecords = objArray_New();
        if (pRecords == OBJ_NIL) {
            TOKEN_DATA      *pToken;
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            token_ErrorFatalFLC(
                                  pToken,
                                  "Out of memory"
            );
            return OBJ_NIL;
        }
        
        eRc = objArray_AppendObj(pRecords, pRecord, NULL);
        if (ERESULT_HAS_FAILED(eRc)) {
            TOKEN_DATA      *pToken;
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            token_ErrorFatalFLC(
                                  pToken,
                                  "Could not save record"
                                  );
        }
        obj_Release(pRecord);
        pRecord = OBJ_NIL;
        
        for (;;) {
            if (dbCsv_ParseEOF(this)) {
                break;
            }
            pRecord = dbCsv_ParseRecord(this);
            if (pRecord == OBJ_NIL) {
                break;
            }
            ++recordNo;
            eRc = objArray_AppendObj(pRecords, pRecord, NULL);
            if (ERESULT_HAS_FAILED(eRc)) {
                TOKEN_DATA      *pToken;
                pToken = srcFile_InputLookAhead(this->pSrc, 1);
                token_ErrorFatalFLC(
                                    pToken,
                                    "Could not save record"
                );
            }
            obj_Release(pRecord);
            pRecord = OBJ_NIL;
        }
        
        if (dbCsv_ParseCRLF(this)) {
        }
        
        if (!dbCsv_ParseEOF(this)) {
            TOKEN_DATA      *pToken;
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            token_ErrorFatalFLC(
                                pToken,
                                "Malformed file, missing EOF at record %d",
                                recordNo
            );
        }
        
        return pRecords;
    }
    
    
    
    bool            dbCsv_ParseSEP(
        DBCSV_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW(pToken);
        if (chr == this->fieldSeparator) {
            this->lenFld = 0;
            srcFile_InputAdvance(this->pSrc, 1);
            return true;
        }
        
        return false;
    }
    
    

    ASTR_DATA *     dbCsv_ParseStringEscaped(
        DBCSV_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         chr;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW(pToken);
        if (chr == '"') {
            srcFile_InputAdvance(this->pSrc, 1);
        }
        else {
            return pStr;
        }
        
        for (;;) {
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            chr = token_getChrW(pToken);
            if (dbCsv_ParseTEXTDATA(this)) {
                // Do something, maybe!
            }
            else if (chr == '"') {
                pToken = srcFile_InputLookAhead(this->pSrc, 2);
                chr = token_getChrW(pToken);
                if (chr == '"') {
                    dbCsv_AppendCharToString(this, '"');
                    srcFile_InputAdvance(this->pSrc, 2);
                }
                else {
                    break;
                }
            }
            else if (dbCsv_ParseSEP(this)) {
                dbCsv_AppendCharToString(this, this->fieldSeparator);
            }
            else if ((chr == '\f') || (chr == '\n') || (chr == '\r') || (chr == '\t')) {
                dbCsv_AppendCharToString(this, chr);
                srcFile_InputAdvance(this->pSrc, 1);
            }
            else if (chr == '\\') {
                pToken = srcFile_InputLookAhead(this->pSrc, 1);
                chr = token_getChrW(pToken);
                if (chr == '"') {
                    dbCsv_AppendCharToString(this, '"');
                    srcFile_InputAdvance(this->pSrc, 1);
                }
                else {
                    dbCsv_AppendCharToString(this, '\\');
                    srcFile_InputAdvance(this->pSrc, 1);
                }
            }
            else {
                token_ErrorFatalFLC(
                            pToken,
                            "Invalid characters in escaped text"
                );
            }
        }
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW(pToken);
        if (chr == '"') {
            srcFile_InputAdvance(this->pSrc, 1);
            pStr = AStr_NewW(this->pFld);
            this->lenFld = 0;
        }
        
        return pStr;
    }
    
    
    
    ASTR_DATA * dbCsv_ParseStringNonEscaped(
        DBCSV_DATA      *this
    )
    {
        bool            fRc = false;
        int             i = 0;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        while ((fRc = dbCsv_ParseTEXTDATA(this))) {
            ++i;
        }
        
        pStr = AStr_NewW(this->pFld);
        this->lenFld = 0;
        return pStr;
    }
    
    
    
    bool            dbCsv_ParseTEXTDATA(
        DBCSV_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW(pToken);
        if( (chr == this->fieldSeparator) || (chr == '"') ) {
            return false;
        }
        if( (chr == ASCII_LF) || (chr == ASCII_CR) || (chr == ASCII_TAB) ) {
            return false;
        }
        if( (chr >= ' ') && (chr < ASCII_DEL) )
            ;
        else if (chr > 128)
            ;
        else {
            return false;
        }
        
        dbCsv_AppendCharToString(this, chr);
        srcFile_InputAdvance(this->pSrc, 1);
        
        return true;
    }
    
    
    

    
    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    DBCSV_DATA *     dbCsv_Alloc(
    )
    {
        DBCSV_DATA       *cbp;
        uint32_t        cbSize = sizeof(DBCSV_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    DBCSV_DATA *     dbCsv_New(
    )
    {
        DBCSV_DATA       *cbp;
        
        cbp = dbCsv_Alloc( );
        if (cbp) {
            cbp = dbCsv_Init( cbp );
        } 
        return( cbp );
    }



    DBCSV_DATA *    dbCsv_NewAStr(
        ASTR_DATA       *pAStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        DBCSV_DATA       *cbp;
        
        cbp = dbCsv_Alloc( );
        if (cbp) {
            cbp = dbCsv_InitAStr( cbp, pAStr, pPath, tabSize );
        }
        return( cbp );
    }

    
    
    DBCSV_DATA *    dbCsv_NewFile(
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        DBCSV_DATA       *cbp;
        
        cbp = dbCsv_Alloc( );
        if (cbp) {
            cbp = dbCsv_InitFile( cbp, pPath, tabSize );
        }
        return( cbp );
    }
    
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool            dbCsv_getHasHeader(
        DBCSV_DATA      *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        return cbp->fHasHeader;
    }

    bool            dbCsv_setHasHeader(
        DBCSV_DATA      *cbp,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        cbp->fHasHeader = fValue;

        return true;
    }



    int32_t         dbCsv_getFieldSeparator(
        DBCSV_DATA      *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->fieldSeparator;
    }
    
    bool            dbCsv_setFieldSeparator(
        DBCSV_DATA      *cbp,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        cbp->fieldSeparator = value;
        
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //--------------------------------------------------------------
    //           A p p e n d  T o k e n  T o  S t r i n g
    //--------------------------------------------------------------
    
    ERESULT         dbCsv_AppendCharToString(
        DBCSV_DATA      *cbp,
        int32_t         chr
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        if ((cbp->lenFld + 1) < cbp->sizeFld) {
            cbp->pFld[cbp->lenFld++] = chr;
            cbp->pFld[cbp->lenFld] = '\0';
        }
        else
            return ERESULT_DATA_TOO_BIG;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            dbCsv_Dealloc(
        OBJ_ID          objId
    )
    {
        DBCSV_DATA      *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        if (cbp->pSrc) {
            obj_Release(cbp->pSrc);
            cbp->pSrc = OBJ_NIL;
        }
        
        if (cbp->pFld) {
            mem_Free(cbp->pFld);
            cbp->pFld    = NULL;
            cbp->sizeFld = 0;
            cbp->lenFld  = 0;
        }

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            dbCsv_Disable(
        DBCSV_DATA		*cbp
    )
    {

        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !dbCsv_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(cbp);
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DBCSV_DATA *   dbCsv_Init(
        DBCSV_DATA       *cbp
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(cbp);
        cbp = (DBCSV_DATA *)obj_Init( cbp, cbSize, OBJ_IDENT_DBCSV );
        if (OBJ_NIL == cbp) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        //obj_setSize(cbp, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)cbp, OBJ_IDENT_DBCSV);
        obj_setVtbl(cbp, &dbCsv_Vtbl);
        
        cbp->sizeFld = DBCSV_FIELD_MAX;
        cbp->pFld = mem_Calloc(cbp->sizeFld, sizeof(int32_t));
        if (cbp->pFld == NULL) {
            cbp->sizeFld = 0;
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        cbp->fieldSeparator = ',';

    #ifdef NDEBUG
    #else
        if( !dbCsv_Validate( cbp ) ) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->pInputs);
    #endif

        return cbp;
    }

     
    DBCSV_DATA *    dbCsv_InitFile(
        DBCSV_DATA      *this,
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pPath) {
            fprintf( stderr, "Fatal Error - Missing input source file path.\n" );
            return OBJ_NIL;
        }
        
        this = dbCsv_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this->pSrc = srcFile_Alloc();
        this->pSrc = srcFile_InitFile(this->pSrc, pPath, tabSize, false, false);
        if (OBJ_NIL == this->pSrc) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        return this;
    }
    
    
    
    DBCSV_DATA *    dbCsv_InitAStr(
        DBCSV_DATA      *this,
        ASTR_DATA       *pAStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pAStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this = dbCsv_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this->pSrc = srcFile_Alloc();
        this->pSrc = srcFile_InitAStr(this->pSrc, pAStr, pPath, tabSize, false, false);
        if (OBJ_NIL == this->pSrc) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        return this;
    }
    
    
    DBCSV_DATA *    dbCsv_InitWStr(
        DBCSV_DATA      *this,
        WSTR_DATA       *pWStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pWStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this = dbCsv_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this->pSrc = srcFile_InitWStr(this->pSrc, pWStr, pPath, tabSize, false, false);
        if (OBJ_NIL == this->pSrc) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        return this;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                      P a r s e  F i l e
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * dbCsv_ParseFile(
        DBCSV_DATA		*cbp
    )
    {
        OBJARRAY_DATA   *pRecords = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pRecords = dbCsv_ParseRecords(cbp);
        if (pRecords == OBJ_NIL) {
            DEBUG_BREAK();
            return pRecords;
        }
        
        // Return to caller.
        return pRecords;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     dbCsv_ToDebugString(
        DBCSV_DATA      *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == cbp) {
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
                     "{%p(dbCsv) ",
                     cbp
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (cbp->pData) {
            if (((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString(
                                                    cbp->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            dbCsv_Validate(
        DBCSV_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_DBCSV) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(DBCSV_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


