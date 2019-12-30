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
#include <dbCsv_internal.h>
#include <ascii.h>
#include <SrcErrors.h>
#include <str.h>
#include <W32Str.h>
#include <stdio.h>
#include <wchar.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ERESULT        errorExit(
    )
    {
        return ERESULT_SUCCESS;
    }
    
    
    
    bool            dbCsv_ParseComment(
        DBCSV_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        W32CHR_T        chr;
        bool            fRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW32(pToken);
        if (chr == '#') {
            srcFile_InputAdvance(this->pSrc, 1);
            this->lenFld = 0;
            while (!(fRc = dbCsv_ParseCRLF(this))) {
                srcFile_InputAdvance(this->pSrc, 1);
            }
            return true;
        }
        
        return false;
    }
    
    
    
    // Look for <cr>[<lf>] or <lf>[<cr>] and discard
    // if found, but return true.
    bool            dbCsv_ParseCRLF(
        DBCSV_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        W32CHR_T        chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW32(pToken);
        if (chr == '\r') {
            srcFile_InputAdvance(this->pSrc, 1);
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            chr = token_getChrW32(pToken);
            if (chr == '\n') {
                srcFile_InputAdvance(this->pSrc, 1);
            }
            this->lenFld = 0;
            return true;
        }
        else if (chr == '\n') {
            srcFile_InputAdvance(this->pSrc, 1);
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            chr = token_getChrW32(pToken);
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
        W32CHR_T        chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW32(pToken);
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
        SrcErrors_AddFatalFromTokenA(
            OBJ_NIL,
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
        
        while( dbCsv_ParseComment(this) )
            ;
        
        if (dbCsv_ParseEOF(this)) {
            return OBJ_NIL;
        }
        
        pStr = dbCsv_ParseField(this);
        if (pStr == OBJ_NIL) {
            return OBJ_NIL;
        }
        ++fieldNo;
        
        pRecord = ObjArray_New();
        if (pRecord == OBJ_NIL) {
            TOKEN_DATA      *pToken;
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            SrcErrors_AddFatalFromTokenA(
                OBJ_NIL,
                pToken,
                "Out of Memory"
            );
            return OBJ_NIL;
        }
        
        eRc = ObjArray_AppendObj(pRecord, pStr, NULL);
        if (ERESULT_HAS_FAILED(eRc)) {
            TOKEN_DATA      *pToken;
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            SrcErrors_AddFatalFromTokenA(
                OBJ_NIL,
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
                SrcErrors_AddFatalFromTokenA(
                    OBJ_NIL,
                    pToken,
                    "Malformed Record at field %d",
                    fieldNo
                );
                return OBJ_NIL;
            }
            ++fieldNo;
            eRc = ObjArray_AppendObj(pRecord, pStr, NULL);
            if (ERESULT_HAS_FAILED(eRc)) {
                TOKEN_DATA      *pToken;
                pToken = srcFile_InputLookAhead(this->pSrc, 1);
                SrcErrors_AddFatalFromTokenA(
                    OBJ_NIL,
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
            SrcErrors_AddFatalFromTokenA(
                                OBJ_NIL,
                                pToken,
                                "Expected line end, but found %lc",
                                token_getChrW32(pToken)
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
        bool            fRc = true;;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pRecords = ObjArray_New();
        if (pRecords == OBJ_NIL) {
            TOKEN_DATA      *pToken;
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            SrcErrors_AddFatalFromTokenA(
                OBJ_NIL,
                pToken,
                "Out of Memory"
            );
            return OBJ_NIL;
        }

#ifdef xyzzy
        pRecord = dbCsv_ParseRecord(this);
        if (pRecord == OBJ_NIL) {
            return OBJ_NIL;
        }
        ++recordNo;
        fRc = true;
        if (this->pRecordProcess) {
            fRc = this->pRecordProcess(this->pRecordData, pRecord);
        }
        if (fRc) {
            eRc = ObjArray_AppendObj(pRecords, pRecord, NULL);
            if (ERESULT_HAS_FAILED(eRc)) {
                TOKEN_DATA      *pToken;
                pToken = srcFile_InputLookAhead(this->pSrc, 1);
                SrcErrors_AddFatalFromTokenA(
                    OBJ_NIL,
                    pToken,
                    "Could not save record"
                );
            }
        }
        obj_Release(pRecord);
        pRecord = OBJ_NIL;
#endif
        
        for (;;) {
            if (dbCsv_ParseEOF(this)) {
                break;
            }
            while (dbCsv_ParseComment(this) || dbCsv_ParseWS(this)) {
            }
            
            pRecord = dbCsv_ParseRecord(this);
            if (pRecord == OBJ_NIL) {
                break;
            }
            ++recordNo;
            fRc = true;
            if (this->pRecordProcess) {
                fRc = this->pRecordProcess(this->pRecordData, pRecord);
            }
            if (fRc) {
                eRc = ObjArray_AppendObj(pRecords, pRecord, NULL);
                if (ERESULT_HAS_FAILED(eRc)) {
                    TOKEN_DATA      *pToken;
                    pToken = srcFile_InputLookAhead(this->pSrc, 1);
                    SrcErrors_AddFatalFromTokenA(
                                        OBJ_NIL,
                                        pToken,
                                        "Could not save record"
                    );
                }
            }
            obj_Release(pRecord);
            pRecord = OBJ_NIL;
        }
        
        if (dbCsv_ParseCRLF(this)) {
        }
        
        if (!dbCsv_ParseEOF(this)) {
            TOKEN_DATA      *pToken;
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            SrcErrors_AddFatalFromTokenA(
                                OBJ_NIL,
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
        W32CHR_T        chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        dbCsv_ParseWS(this);
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW32(pToken);
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
        W32CHR_T        chr;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        dbCsv_ParseWS(this);

        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW32(pToken);
        if (chr == '"') {
            srcFile_InputAdvance(this->pSrc, 1);
        }
        else {
            return pStr;
        }
        
        for (;;) {
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            chr = token_getChrW32(pToken);
            if (dbCsv_ParseTEXTDATA(this)) {
                // Do something, maybe!
            }
            else if (chr == '"') {
                pToken = srcFile_InputLookAhead(this->pSrc, 2);
                chr = token_getChrW32(pToken);
                if (chr == '"') {
                    dbCsv_AppendCharW32ToString(this, '"');
                    srcFile_InputAdvance(this->pSrc, 2);
                }
                else {
                    break;
                }
            }
            else if (chr == this->fieldSeparator) {
                dbCsv_AppendCharW32ToString(this, this->fieldSeparator);
                srcFile_InputAdvance(this->pSrc, 1);
            }
            else if ((chr == '\f') || (chr == '\n') || (chr == '\r') || (chr == '\t')) {
                dbCsv_AppendCharW32ToString(this, chr);
                srcFile_InputAdvance(this->pSrc, 1);
            }
            else if (chr == '\\') {
                pToken = srcFile_InputLookAhead(this->pSrc, 1);
                chr = token_getChrW32(pToken);
                if (chr == '"') {
                    dbCsv_AppendCharW32ToString(this, '"');
                    srcFile_InputAdvance(this->pSrc, 1);
                }
                else {
                    dbCsv_AppendCharW32ToString(this, '\\');
                    srcFile_InputAdvance(this->pSrc, 1);
                }
            }
            else {
                SrcErrors_AddFatalFromTokenA(
                            OBJ_NIL,
                            pToken,
                            "Invalid characters in escaped text"
                );
            }
        }
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW32(pToken);
        if (chr == '"') {
            srcFile_InputAdvance(this->pSrc, 1);
            pStr = AStr_NewW32(this->pFld);
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
        
        pStr = AStr_NewW32(this->pFld);
        this->lenFld = 0;
        return pStr;
    }
    
    
    
    bool            dbCsv_ParseTEXTDATA(
        DBCSV_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        W32CHR_T        chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW32(pToken);
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
        
        dbCsv_AppendCharW32ToString(this, chr);
        srcFile_InputAdvance(this->pSrc, 1);
        
        return true;
    }
    
    

    // Parse White-space
    bool            dbCsv_ParseWS(
        DBCSV_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        W32CHR_T        chr;
        bool            fRc = false;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = token_getChrW32(pToken);
        while ((chr == ' ') || (chr == '\f') || (chr == '\r') || (chr == '\t')) {
            srcFile_InputAdvance(this->pSrc, 1);
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            chr = token_getChrW32(pToken);
            fRc = true;
        }
        
        return fRc;
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
        DBCSV_DATA       *this;
        
        this = dbCsv_Alloc( );
        if (this) {
            this = dbCsv_Init(this);
        } 
        return this;
    }



    DBCSV_DATA *    dbCsv_NewFromAStr(
        ASTR_DATA       *pAStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        DBCSV_DATA       *this;
        
        this = dbCsv_New( );
        if (this) {
            this->pSrc = srcFile_NewFromAStr(pPath, pAStr, 1, tabSize);
            if (OBJ_NIL == this->pSrc) {
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        return this;
    }

    
    
    DBCSV_DATA *    dbCsv_NewFromPath(
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        DBCSV_DATA       *this;
        
        this = dbCsv_New( );
        this->pSrc = srcFile_NewFromPath(pPath, 1, tabSize);
        if (OBJ_NIL == this->pSrc) {
            obj_Release(this);
            return OBJ_NIL;
        }
        return this;
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



    W32CHR_T        dbCsv_getFieldSeparator(
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
        W32CHR_T        value
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
    
    
    
    bool            dbCsv_setRecordProcess(
        DBCSV_DATA      *this,
        bool            (*pRecordProcess)(void *pRecordData, OBJARRAY_DATA *pRecord),
        void            *pRecordData
    )
    {
#ifdef NDEBUG
#else
        if( !dbCsv_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
    
        this->pRecordProcess = pRecordProcess;
        this->pRecordData = pRecordData;
        
        return true;
    }






    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //--------------------------------------------------------------
    //           A p p e n d  T o k e n  T o  S t r i n g
    //--------------------------------------------------------------
    
    ERESULT         dbCsv_AppendCharW32ToString(
        DBCSV_DATA      *this,
        W32CHR_T        chr
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        if ((this->lenFld + 1) < this->sizeFld) {
            this->pFld[this->lenFld++] = chr;
            this->pFld[this->lenFld] = '\0';
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
        DBCSV_DATA      *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !dbCsv_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        if (this->pSrc) {
            obj_Release(this->pSrc);
            this->pSrc = OBJ_NIL;
        }
        
        if (this->pFld) {
            mem_Free(this->pFld);
            this->pFld    = NULL;
            this->sizeFld = 0;
            this->lenFld  = 0;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

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
        DBCSV_DATA       *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (DBCSV_DATA *)obj_Init( this, cbSize, OBJ_IDENT_DBCSV );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(cbp, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)cbp, OBJ_IDENT_DBCSV);
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&dbCsv_Vtbl);
        
        this->sizeFld = DBCSV_FIELD_MAX;
        this->pFld = mem_Calloc(this->sizeFld, sizeof(W32CHR_T));
        if (this->pFld == NULL) {
            this->sizeFld = 0;
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->fieldSeparator = ',';

    #ifdef NDEBUG
    #else
        if( !dbCsv_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->pInputs);
    #endif

        return this;
    }

             
    
    //---------------------------------------------------------------
    //                      P a r s e  F i l e
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * dbCsv_ParseFile(
        DBCSV_DATA		*this
    )
    {
        OBJARRAY_DATA   *pRecords = OBJ_NIL;
        void            *pExit = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbCsv_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //pExit = SrcErrors_getExit(OBJ_NIL);
        SrcErrors_setFatalExit(OBJ_NIL, errorExit, OBJ_NIL);
        
        pRecords = dbCsv_ParseRecords(this);
        if (pRecords == OBJ_NIL) {
            DEBUG_BREAK();
            return pRecords;
        }
        
        SrcErrors_setFatalExit(OBJ_NIL, errorExit, pExit);

        // Return to caller.
        return pRecords;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     dbCsv_ToDebugString(
        DBCSV_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(dbCsv) ",
                     this
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->toDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p}\n", this );
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


