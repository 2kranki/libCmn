// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   CsvFile.c
 *	Generated 12/30/2019 11:06:40
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
#include        <CsvFile_internal.h>
#include        <ascii.h>
#include        <SrcErrors.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    ERESULT        CsvFile_ErrorExit (
        CSVFILE_DATA    *this
    )
    {
        return ERESULT_SUCCESS;
    }



    bool            CsvFile_ParseComment(
        CSVFILE_DATA    *this
    )
    {
        TOKEN_DATA      *pToken;
        W32CHR_T        chr;
        bool            fRc;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CsvFile_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = Token_getChrW32(pToken);
        if (chr == '#') {
            srcFile_InputAdvance(this->pSrc, 1);
            this->lenFld = 0;
            while (!(fRc = CsvFile_ParseCRLF(this))) {
                srcFile_InputAdvance(this->pSrc, 1);
            }
            return true;
        }

        return false;
    }



    // Look for <cr>[<lf>] or <lf>[<cr>] and discard
    // if found, but return true.
    bool            CsvFile_ParseCRLF(
        CSVFILE_DATA    *this
    )
    {
        TOKEN_DATA      *pToken;
        W32CHR_T        chr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CsvFile_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = Token_getChrW32(pToken);
        if (chr == '\r') {
            srcFile_InputAdvance(this->pSrc, 1);
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            chr = Token_getChrW32(pToken);
            if (chr == '\n') {
                srcFile_InputAdvance(this->pSrc, 1);
            }
            this->lenFld = 0;
            return true;
        }
        else if (chr == '\n') {
            srcFile_InputAdvance(this->pSrc, 1);
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            chr = Token_getChrW32(pToken);
            if (chr == '\r') {
                srcFile_InputAdvance(this->pSrc, 1);
            }
            this->lenFld = 0;
            return true;
        }

        return false;
    }



    bool            CsvFile_ParseEOF(
        CSVFILE_DATA    *this
    )
    {
        TOKEN_DATA      *pToken;
        W32CHR_T        chr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CsvFile_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = Token_getChrW32(pToken);
        if (chr == EOF) {
            srcFile_InputAdvance(this->pSrc, 1);
            this->lenFld = 0;
            return true;
        }

        return false;
    }



    ASTR_DATA *     CsvFile_ParseField(
        CSVFILE_DATA    *this
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        TOKEN_DATA      *pToken;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CsvFile_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = CsvFile_ParseStringEscaped(this);
        if (pStr) {
            return pStr;
        }
        pStr = CsvFile_ParseStringNonEscaped(this);
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



    OBJARRAY_DATA * CsvFile_ParseRecord(
        CSVFILE_DATA    *this
    )
    {
        int             fieldNo = 0;
        ERESULT         eRc;
        OBJARRAY_DATA   *pRecord = OBJ_NIL;
        ASTR_DATA       *pStr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CsvFile_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        while( CsvFile_ParseComment(this) )
            ;

        if (CsvFile_ParseEOF(this)) {
            return OBJ_NIL;
        }

        pStr = CsvFile_ParseField(this);
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
            if (!CsvFile_ParseSEP(this)) {
                break;
            }
            pStr = CsvFile_ParseField(this);
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

        if (!CsvFile_ParseCRLF(this)) {
            TOKEN_DATA      *pToken;
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            SrcErrors_AddFatalFromTokenA(
                                OBJ_NIL,
                                pToken,
                                "Expected line end, but found %lc",
                                Token_getChrW32(pToken)
            );
        }

        return pRecord;
    }



    OBJARRAY_DATA * CsvFile_ParseRecords(
        CSVFILE_DATA    *this
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
        if( !CsvFile_Validate( this ) ) {
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
        pRecord = CsvFile_ParseRecord(this);
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
            if (CsvFile_ParseEOF(this)) {
                break;
            }
            while (CsvFile_ParseComment(this) || CsvFile_ParseWS(this)) {
            }

            pRecord = CsvFile_ParseRecord(this);
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

        if (CsvFile_ParseCRLF(this)) {
        }

        if (!CsvFile_ParseEOF(this)) {
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



    bool            CsvFile_ParseSEP(
        CSVFILE_DATA    *this
    )
    {
        TOKEN_DATA      *pToken;
        W32CHR_T        chr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CsvFile_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        CsvFile_ParseWS(this);
        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = Token_getChrW32(pToken);
        if (chr == this->fieldSeparator) {
            this->lenFld = 0;
            srcFile_InputAdvance(this->pSrc, 1);
            return true;
        }

        return false;
    }



    ASTR_DATA *     CsvFile_ParseStringEscaped(
        CSVFILE_DATA    *this
    )
    {
        TOKEN_DATA      *pToken;
        W32CHR_T        chr;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CsvFile_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        CsvFile_ParseWS(this);

        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = Token_getChrW32(pToken);
        if (chr == '"') {
            srcFile_InputAdvance(this->pSrc, 1);
        }
        else {
            return pStr;
        }

        for (;;) {
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            chr = Token_getChrW32(pToken);
            if (CsvFile_ParseTEXTDATA(this)) {
                // Do something, maybe!
            }
            else if (chr == '"') {
                pToken = srcFile_InputLookAhead(this->pSrc, 2);
                chr = Token_getChrW32(pToken);
                if (chr == '"') {
                    CsvFile_AppendCharW32ToString(this, '"');
                    srcFile_InputAdvance(this->pSrc, 2);
                }
                else {
                    break;
                }
            }
            else if (chr == this->fieldSeparator) {
                CsvFile_AppendCharW32ToString(this, this->fieldSeparator);
                srcFile_InputAdvance(this->pSrc, 1);
            }
            else if ((chr == '\f') || (chr == '\n') || (chr == '\r') || (chr == '\t')) {
                CsvFile_AppendCharW32ToString(this, chr);
                srcFile_InputAdvance(this->pSrc, 1);
            }
            else if (chr == '\\') {
                pToken = srcFile_InputLookAhead(this->pSrc, 1);
                chr = Token_getChrW32(pToken);
                if (chr == '"') {
                    CsvFile_AppendCharW32ToString(this, '"');
                    srcFile_InputAdvance(this->pSrc, 1);
                }
                else {
                    CsvFile_AppendCharW32ToString(this, '\\');
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
        chr = Token_getChrW32(pToken);
        if (chr == '"') {
            srcFile_InputAdvance(this->pSrc, 1);
            pStr = AStr_NewW32(this->pFld);
            this->lenFld = 0;
        }

        return pStr;
    }



    ASTR_DATA *     CsvFile_ParseStringNonEscaped(
        CSVFILE_DATA    *this
    )
    {
        bool            fRc = false;
        int             i = 0;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CsvFile_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        while ((fRc = CsvFile_ParseTEXTDATA(this))) {
            ++i;
        }

        pStr = AStr_NewW32(this->pFld);
        this->lenFld = 0;
        return pStr;
    }



    bool            CsvFile_ParseTEXTDATA(
        CSVFILE_DATA    *this
    )
    {
        TOKEN_DATA      *pToken;
        W32CHR_T        chr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!CsvFile_Validate( this)) {
            DEBUG_BREAK();
        }
#endif

        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = Token_getChrW32(pToken);
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

        CsvFile_AppendCharW32ToString(this, chr);
        srcFile_InputAdvance(this->pSrc, 1);

        return true;
    }



    // Parse White-space
    bool            CsvFile_ParseWS(
        CSVFILE_DATA    *this
    )
    {
        TOKEN_DATA      *pToken;
        W32CHR_T        chr;
        bool            fRc = false;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
        }
#endif

        pToken = srcFile_InputLookAhead(this->pSrc, 1);
        chr = Token_getChrW32(pToken);
        while ((chr == ' ') || (chr == '\f') || (chr == '\r') || (chr == '\t')) {
            srcFile_InputAdvance(this->pSrc, 1);
            pToken = srcFile_InputLookAhead(this->pSrc, 1);
            chr = Token_getChrW32(pToken);
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

    CSVFILE_DATA *   CsvFile_Alloc (
        void
    )
    {
        CSVFILE_DATA    *this;
        uint32_t        cbSize = sizeof(CSVFILE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    CSVFILE_DATA *   CsvFile_New (
        void
    )
    {
        CSVFILE_DATA    *this;
        
        this = CsvFile_Alloc( );
        if (this) {
            this = CsvFile_Init(this);
        } 
        return this;
    }



    CSVFILE_DATA *  CsvFile_NewFromAStr(
       ASTR_DATA       *pAStr,         // Buffer of file data
       PATH_DATA       *pPath,
       uint16_t        tabSize         // Tab Spacing if any
    )
    {
       CSVFILE_DATA    *this;

       this = CsvFile_New( );
       if (this) {
           this->pSrc = srcFile_NewFromAStr(pPath, pAStr, 1, tabSize);
           if (OBJ_NIL == this->pSrc) {
               obj_Release(this);
               return OBJ_NIL;
           }
       }
       return this;
    }



    CSVFILE_DATA *  CsvFile_NewFromPath(
       PATH_DATA       *pPath,
       uint16_t        tabSize         // Tab Spacing if any
    )
    {
       CSVFILE_DATA    *this;

       this = CsvFile_New( );
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

    //---------------------------------------------------------------
    //                  H a s  H e a d e r
    //---------------------------------------------------------------

    bool            CsvFile_getHasHeader (
        CSVFILE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->fHasHeader ? true : false;
    }


    bool            CsvFile_setHasHeader (
        CSVFILE_DATA    *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fHasHeader = value ? 1 : 0;

        return true;
    }



    //---------------------------------------------------------------
    //                 F i e l d  S e p e r a t o r
    //---------------------------------------------------------------
    
    W32CHR_T        CsvFile_getFieldSeparator (
        CSVFILE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->fieldSeparator;
    }


    bool            CsvFile_setFieldSeparator (
        CSVFILE_DATA    *this,
        W32CHR_T        value
    )
    {
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fieldSeparator = value;

        return true;
    }



    //---------------------------------------------------------------
    //                            S i z e
    //---------------------------------------------------------------
    
    uint32_t        CsvFile_getSize (
        CSVFILE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------

    bool            CsvFile_setRecordProcess(
        CSVFILE_DATA    *this,
        bool            (*pRecordProcess)(void *pRecordData, OBJARRAY_DATA *pRecord),
        void            *pRecordData
    )
    {
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        this->pRecordProcess = pRecordProcess;
        this->pRecordData = pRecordData;

        return true;
    }

    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  CsvFile_getSuperVtbl (
        CSVFILE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //--------------------------------------------------------------
    //           A p p e n d  T o k e n  T o  S t r i n g
    //--------------------------------------------------------------

    ERESULT         CsvFile_AppendCharW32ToString(
        CSVFILE_DATA    *this,
        W32CHR_T        chr
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !CsvFile_Validate(this) ) {
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
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = CsvFile_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another CSVFILE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         CsvFile_Assign (
        CSVFILE_DATA    *this,
        CSVFILE_DATA    *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!CsvFile_Validate(pOther)) {
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
    ERESULT         CsvFile_Compare (
        CSVFILE_DATA     *this,
        CSVFILE_DATA     *pOther
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
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!CsvFile_Validate(pOther)) {
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
        CsvFile      *pCopy = CsvFile_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a CSVFILE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    CSVFILE_DATA *  CsvFile_Copy (
        CSVFILE_DATA    *this
    )
    {
        CSVFILE_DATA    *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = CsvFile_New( );
        if (pOther) {
            eRc = CsvFile_Assign(this, pOther);
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

    void            CsvFile_Dealloc (
        OBJ_ID          objId
    )
    {
        CSVFILE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((CSVFILE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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
    ERESULT         CsvFile_Disable (
        CSVFILE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!CsvFile_Validate(this)) {
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
    ERESULT         CsvFile_Enable (
        CSVFILE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!CsvFile_Validate(this)) {
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

    CSVFILE_DATA *   CsvFile_Init (
        CSVFILE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(CSVFILE_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_CSVFILE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&CsvFile_Vtbl);
        
        this->sizeFld = CSVFILE_FIELD_MAX;
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
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "CsvFile::sizeof(CSVFILE_DATA) = %lu\n", sizeof(CSVFILE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(CSVFILE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         CsvFile_IsEnabled (
        CSVFILE_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
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
    //                      P a r s e  F i l e
    //---------------------------------------------------------------

    OBJARRAY_DATA * CsvFile_ParseFile(
        CSVFILE_DATA    *this
    )
    {
        OBJARRAY_DATA   *pRecords = OBJ_NIL;
        OBJMETHOD_DATA  *pMethod = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !CsvFile_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pMethod = ObjMethod_NewObjectA(this, "ErrorExit");
        SrcErrors_setFatalExit(OBJ_NIL, pMethod);

        pRecords = CsvFile_ParseRecords(this);
        if (pRecords == OBJ_NIL) {
            DEBUG_BREAK();
            return pRecords;
        }

        SrcErrors_setFatalExit(OBJ_NIL, OBJ_NIL);

        // Return to caller.
        return pRecords;
    }



    //---------------------------------------------------------------
    //                P a r s e  J s o n  O b j e c t
    //---------------------------------------------------------------
    
#ifdef  CSVFILE_JSON_SUPPORT
     CSVFILE_DATA * CsvFile_ParseJsonObject (
         JSONIN_DATA     *pParser
    )
    {
        return OBJ_NIL;
    }
#endif
        
        
        
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
        void        *pMethod = CsvFile_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "CsvFile", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          CsvFile_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        CSVFILE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(CSVFILE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)CsvFile_Class();
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
                            return CsvFile_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return CsvFile_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return CsvFile_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return CsvFile_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == CsvFile_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == CsvFile_ToJson)
                    return "ToJson";
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
    
#ifdef  CSVFILE_JSON_SUPPORT
     ASTR_DATA *  CsvFile_ToJson (
        CSVFILE_DATA    *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!CsvFile_Validate(this)) {
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
        ASTR_DATA      *pDesc = CsvFile_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     CsvFile_ToDebugString (
        CSVFILE_DATA    *this,
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
        if (!CsvFile_Validate(this)) {
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
                    CsvFile_getSize(this),
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
    bool            CsvFile_Validate (
        CSVFILE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_CSVFILE))
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


        if (!(obj_getSize(this) >= sizeof(CSVFILE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


