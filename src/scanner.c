// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   scanner.c
 *	Generated 07/26/2018 19:55:39
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
#include        <scanner_internal.h>
#include        <ascii.h>
#include        <hex.h>
#include        <trace.h>
#include        <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            scanner_task_body(
        void            *pData
    )
    {
        //SCANNER_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SCANNER_DATA *  scanner_Alloc(
        void
    )
    {
        SCANNER_DATA    *this;
        uint32_t        cbSize = sizeof(SCANNER_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SCANNER_DATA *     scanner_New(
        void
    )
    {
        SCANNER_DATA       *this;
        
        this = scanner_Alloc( );
        if (this) {
            this = scanner_Init(this);
        } 
        return this;
    }



    //---------------------------------------------------------------
    //                    S c a n D a t e
    //---------------------------------------------------------------

    /* CmdStr is scanned one character at a time into the Output
     * buffer supplied. The scan will go until it hits end of line
     * the end of the string. It will copy at most maxLen characters
     * to the output.
     NOTE: This only accepets ascii characters at this point.
     */
    bool            scanner_ScanDate(
        char            **ppCmdStr,         // NUL terminated string pointer
        uint32_t        *pScannedLen,       // (returned) Scanned Length
                                            // (not including leading whitespace)
        uint32_t        *pValue             // (returned) Scanned Number
    )
    {
        bool            fRc = false;
        char            *pCurChr = NULL;
        uint32_t        cOutput = 0;
        //char            Quote = 0;
        char            dd10 = 0;
        char            dd1  = 0;
        char            mm10 = 0;
        char            mm1  = 0;
        uint8_t         mm = 0;
        uint8_t         dd = 0;
        //uint16_t        yyyy = 0;
        //uint8_t         wday = 0;
        //char            szDate[11] = "MM/DD/YYYY";
        
        // Do initialization.
        if( NULL == ppCmdStr ) {
            fRc = false;
            goto Exit00;
        }
        pCurChr = *ppCmdStr;
        //W32CHR_T        chr;
        //int             chrLen = 0;

        // Scan off leading white-space.
        scanWhite( &pCurChr, NULL );
        
        // Scan the paramter.
        if( *pCurChr ) {
            // MM
            if( ('0' <= *pCurChr) || ('1' >= *pCurChr) ) {
                mm10 = *pCurChr;
                ++pCurChr;
            }
            else
                return false;
            if( ('0' <= *pCurChr) || ('1' >= *pCurChr) ) {
                mm1 = *pCurChr;
                ++pCurChr;
            }
            // DD
            if( (*pCurChr >= '0') || (*pCurChr <= '3') ) {
                dd10 = *pCurChr;
                ++pCurChr;
            }
            else
                return false;
            if( (*pCurChr >= '0') || ('1' >= *pCurChr) ) {
                dd1 = *pCurChr;
                ++pCurChr;
            }
            
            if( ('0' <= *pCurChr) || ('1' >= *pCurChr) ) {
                mm = *pCurChr - '0';
                ++pCurChr;
            }
            else {
                return false;
            }
            if( ('0' <= *pCurChr) || ('9' >= *pCurChr) ) {
                mm *= 10;
                mm += *pCurChr - '0';
                ++pCurChr;
            }
            else {
                return false;
            }
            if ( !((mm > 0) && (mm < 13)) ) {
                return false;
            }
            if( '/' == *pCurChr ) {
                ++pCurChr;
            }
            else {
                return false;
            }
            
            // DD/
            if( ('0' <= *pCurChr) || ('3' >= *pCurChr) ) {
                dd += *pCurChr - '0';
                ++pCurChr;
            }
            if( ('0' <= *pCurChr) || ('9' >= *pCurChr) ) {
                dd *= 10;
                dd += *pCurChr - '0';
                ++pCurChr;
            }
        }
        
        
        // Return to caller.
        fRc = true;
    Exit00:
        if( ppCmdStr ) {
            *ppCmdStr = pCurChr;
        }
        if( pScannedLen ) {
            *pScannedLen = cOutput;
        }
        return( fRc );
    }
    
    
    
    //---------------------------------------------------------------
    //                    S c a n D e c
    //---------------------------------------------------------------

    bool            scanner_ScanDec32(
        char            **ppCmdStr,         // NUL terminated string pointer
        uint32_t        *pScannedLen,       // (returned) Scanned Length
        uint32_t        *pValue             // (returned) Scanned Number
    )
    {
        bool            fRc = false;
        char            *pCurChr = NULL;
        bool            fNegative = false;
        uint32_t        cLen = 0;
        uint32_t        cDec = 0;
        uint32_t        value = 0;
        W32CHR_T        chr;
        int             chrLen = 0;

        // Do initialization.
        if( NULL == ppCmdStr ) {
            fRc = false;
            goto Exit00;
        }
        pCurChr = *ppCmdStr;
        
        // Scan off leading white-space.
        scanWhite( &pCurChr, &cLen );

        chrLen = utf8_Utf8ToW32(pCurChr, &chr);
        if (0 == chrLen) {
            goto Exit00;
        }
        
        if ( ('0' == chr) && (('x' == *(pCurChr+1)) || ('X' == *(pCurChr+1))) ) {
            pCurChr += 2;
            cLen += 2;
            fRc = scanHex32(&pCurChr, &cDec, &value);
            cLen += cDec;
            goto Exit00;
        }
        
        if( '-' == chr ) {
            fNegative = true;
            cLen += chrLen;
            pCurChr += chrLen;
        }
        
        for (;;) {
            chrLen = utf8_Utf8ToW32(pCurChr, &chr);
            if (chrLen) {
                if( ('0' <= chr) && ('9' >= chr) ) {
                    value = (value << 3) + (value << 1) + (chr - '0');
                    ++cDec;
                    cLen += chrLen;
                    pCurChr += chrLen;
                }
                else
                    break;
            }
            else
                break;
        }
        
        if (chrLen) {
            if( ('\0' == chr) || ('\t' == chr) || (',' == chr) || (' ' == chr) ) {
                if( cDec ) {
                    fRc = true;
                    if( fNegative ) {
                        value = -value;
                    }
                }
            }
        }
        else {
            if ('\0' == *pCurChr) {
                fRc = true;
                if( fNegative ) {
                    value = -value;
                }
            }
        }
        
        // Return to caller.
    Exit00:
        if( ppCmdStr ) {
            *ppCmdStr = pCurChr;
        }
        if( pScannedLen ) {
            *pScannedLen = cLen;
        }
        if( pValue ) {
            *pValue = value;
        }
        return( fRc );
    }
    
    
    
    //---------------------------------------------------------------
    //                      S c a n H e x
    //---------------------------------------------------------------

    bool            scanner_ScanHex32(
        char            **ppCmdStr,         // NUL terminated string pointer
        uint32_t        *pScannedLen,       // (returned) Scanned Length
        uint32_t        *pValue             // (returned) Scanned Number
    )
    {
        bool            fRc = false;
        char            *pCurChr = NULL;
        uint32_t        cLen = 0;
        uint32_t        cHex = 0;
        uint32_t        value = 0;
        W32CHR_T        chr;
        int             chrLen = 0;

        // Do initialization.
        if( NULL == ppCmdStr ) {
            fRc = false;
            goto Exit00;
        }
        pCurChr = *ppCmdStr;
        
        // Scan off leading white-space.
        scanWhite( &pCurChr, &cLen );
        
        // Scan off each parameter.
        for (;;) {
            chrLen = utf8_Utf8ToW32(pCurChr, &chr);
            if (chrLen) {
                if (ascii_isHexW32(chr)) {
                    if( ('0' <= chr) && ('9' >= chr) ) {
                        value = (value << 4) + (chr - '0');
                        ++cHex;
                    }
                    else if( ('a' <= chr) && ('f' >= chr) ) {
                        value = (value << 4) + (chr - 'a' + 10);
                        ++cHex;
                    }
                    else if( ('A' <= chr) && ('F' >= chr) ) {
                        value = (value << 4) + (chr - 'A' + 10);
                        ++cHex;
                    }
                    cLen += chrLen;
                    pCurChr += chrLen;
                }
                else
                    break;
            }
            else
                break;
        }
        
        
        // Return to caller.
        if( cHex ) {
            fRc = true;
        }
    Exit00:
        if( ppCmdStr ) {
            *ppCmdStr = pCurChr;
        }
        if( pScannedLen ) {
            *pScannedLen = cLen;
        }
        if( pValue ) {
            *pValue = value;
        }
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S c a n O c t
    //---------------------------------------------------------------
    
    bool            scanner_ScanOct32(
        char            **ppCmdStr,         // NUL terminated string pointer
        uint32_t        *pScannedLen,       // (returned) Scanned Length
        uint32_t        *pValue             // (returned) Scanned Number
    )
    {
        bool            fRc = false;
        char            *pCurChr = NULL;
        uint32_t        cLen = 0;
        uint32_t        cHex = 0;
        uint32_t        value = 0;
        W32CHR_T        chr;
        int             chrLen = 0;
        
        // Do initialization.
        if( NULL == ppCmdStr ) {
            fRc = false;
            goto Exit00;
        }
        pCurChr = *ppCmdStr;
        
        // Scan off leading white-space.
        scanWhite( &pCurChr, &cLen );
        
        // Scan off each parameter.
        for (;;) {
            chrLen = utf8_Utf8ToW32(pCurChr, &chr);
            if (chrLen) {
                if( ('0' <= chr) && ('7' >= chr) ) {
                    value = (value << 3) + (chr - '0');
                    ++cHex;
                    cLen += chrLen;
                    pCurChr += chrLen;
                }
                else
                    break;
            }
            else
                break;
        }
        
        // Return to caller.
        if( cHex ) {
            fRc = true;
        }
    Exit00:
        if( ppCmdStr ) {
            *ppCmdStr = pCurChr;
        }
        if( pScannedLen ) {
            *pScannedLen = cLen;
        }
        if( pValue ) {
            *pValue = value;
        }
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                    S c a n S t r i n g
    //---------------------------------------------------------------

    /* CmdStr is scanned one character at a time into the Output
     * buffer supplied. The scan will go until it hits end of line or
     * the end of the string. It will copy at most maxLen characters
     * to the output.
     */
    ASTR_DATA *     scanner_ScanStringToAStr(
        char            **ppCmdStr,         // NUL terminated string pointer
        uint32_t        *pScannedLen        // [out] Scanned Length
        //                                  //      (not including leading whitespace)
    )
    {
        bool            fRc = false;
        char            *pCurChr = NULL;
        uint32_t        cOutput = 0;
        char            Quote = 0;
        uint32_t        hexNumber;
        ASTR_DATA       *pStr = OBJ_NIL;
        //W32CHR_T        chr;
        //int             chrLen;
        
        // Do initialization.
        if(NULL == ppCmdStr) {
            return OBJ_NIL;
        }
        pCurChr = *ppCmdStr;
        pStr = AStr_New( );
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        
        // Scan off leading white-space.
        scanWhite(&pCurChr, NULL);
        
        // Scan the paramter.
        if( *pCurChr ) {
            // Handle Quoted Arguments.
            if( ('"' == *pCurChr) || ('\'' == *pCurChr) ) {
                Quote = *pCurChr++;
                while( *pCurChr ) {
                    if( *pCurChr == Quote ) {
                        if( *(pCurChr+1) == Quote ) {
                            pCurChr += 2;
                            AStr_AppendCharA(pStr, Quote);
                            ++cOutput;
                        }
                        else {
                            break;
                        }
                    }
                    else if( *pCurChr == '\\' ) {
                        if( *(pCurChr + 1) == Quote ) {
                            ++pCurChr;
                        }
                        if( *(pCurChr+1) == '0' ) {
                            pCurChr += 2;
                            AStr_AppendCharA(pStr, '\0');
                            ++cOutput;
                            continue;
                        }
                        if( *(pCurChr+1) == 'b' ) {
                            pCurChr += 2;
                            AStr_AppendCharA(pStr, '\b');
                            ++cOutput;
                            continue;
                        }
                        if( *(pCurChr+1) == 'f' ) {
                            pCurChr += 2;
                            AStr_AppendCharA(pStr, '\f');
                            ++cOutput;
                            continue;
                        }
                        if( *(pCurChr+1) == 'n' ) {
                            pCurChr += 2;
                            AStr_AppendCharA(pStr, '\n');
                            ++cOutput;
                            continue;
                        }
                        if( *(pCurChr + 1) == 'r' ) {
                            pCurChr += 2;
                            AStr_AppendCharA(pStr, '\r');
                            ++cOutput;
                            continue;
                        }
                        if( *(pCurChr + 1) == 'x' ) {
                            pCurChr += 2;
                            // At this point, we need two more characters of 0..9,a..f,A..F
                            // to give us our hex character.
                            if (('\0' == *pCurChr) || ('\0' == *(pCurChr+1))) {
                                return false;
                            }
                            fRc = hex_ScanUint32A(2, pCurChr, &hexNumber);
                            if (fRc) {
                                AStr_AppendCharA(pStr, (char)hexNumber);
                                ++cOutput;
                                pCurChr += 2;
                            }
                            else {
                                return false;
                            }
                            continue;
                        }
                    }
                    else {
                        AStr_AppendCharA(pStr, *pCurChr);
                        ++cOutput;
                        ++pCurChr;
                    }
                }
                if( *pCurChr ) {
                    //                *pCurChr = '\0';
                    ++pCurChr;
                }
            }
            // Handle Non-Quoted Arguments.
            else {
                while( *pCurChr
                      && !(('=' == *pCurChr) || (',' == *pCurChr)
                           || (' ' == *pCurChr) || ('\t' == *pCurChr))
                      ) {
                    AStr_AppendCharA(pStr, *pCurChr);
                    ++cOutput;
                    ++pCurChr;
                }
                while( *pCurChr
                            && !(('=' == *pCurChr) || (',' == *pCurChr)
                            || (' ' == *pCurChr) || ('\t' == *pCurChr)) ) {
                    ++pCurChr;
                }
            }
        }
        
        
        // Return to caller.
        fRc = true;
    Exit00:
        if( ppCmdStr ) {
            *ppCmdStr = pCurChr;
        }
        if( pScannedLen ) {
            *pScannedLen = cOutput;
        }
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                    S c a n W h i t e
    //---------------------------------------------------------------

    bool            scanner_ScanWhite(
        char            **ppCmdStr,         // NUL terminated string pointer
        uint32_t        *pScannedLen        // (returned) Scanned Length
    )
    {
        bool            fRc = 0;
        char            *pCurChr = NULL;
        uint32_t        cLen = 0;
        int             chrLen = 0;
        W32CHR_T        chr;

        // Do initialization.
        if( NULL == ppCmdStr ) {
            fRc = false;
            goto Exit00;
        }
        pCurChr = *ppCmdStr;
        
        // Scan off leading white-space.
        for (;;) {
            chrLen = utf8_Utf8ToW32(pCurChr, &chr);
            if (chrLen) {
                if (ascii_isWhiteSpaceW32(chr)) {
                    pCurChr += chrLen;
                    cLen += chrLen;
                }
                else
                    break;
            }
            else
                break;
        }
        
        // Return to caller.
        fRc = true;
    Exit00:
        if( ppCmdStr ) {
            *ppCmdStr = pCurChr;
        }
        if( pScannedLen ) {
            *pScannedLen = cLen;
        }
        return( fRc );
    }
    
    
    


    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        scanner_getPriority(
        SCANNER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        obj_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            scanner_setPriority(
        SCANNER_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        scanner_getSize(
        SCANNER_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        obj_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * scanner_getStr(
        SCANNER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        scanner_setStr(
        SCANNER_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  scanner_getSuperVtbl(
        SCANNER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        obj_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = scanner__Assign(this,pOther);
     @endcode 
     @param     this    SCANNER object pointer
     @param     pOther  a pointer to another SCANNER object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         scanner_Assign(
        SCANNER_DATA		*this,
        SCANNER_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !scanner_Validate(pOther) ) {
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
        obj_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        obj_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return obj_getLastError(this);
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
    ERESULT         scanner_Compare(
        SCANNER_DATA     *this,
        SCANNER_DATA     *pOther
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
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !scanner_Validate(pOther) ) {
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
        
        obj_setLastError(this, eRc);
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        scanner      *pCopy = scanner_Copy(this);
     @endcode 
     @param     this    SCANNER object pointer
     @return    If successful, a SCANNER object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the SCANNER object.
     */
    SCANNER_DATA *     scanner_Copy(
        SCANNER_DATA       *this
    )
    {
        SCANNER_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = scanner_New( );
        if (pOther) {
            eRc = scanner_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        obj_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            scanner_Dealloc(
        OBJ_ID          objId
    )
    {
        SCANNER_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SCANNER_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        scanner_setStr(this, OBJ_NIL);

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

    ERESULT         scanner_Disable(
        SCANNER_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         scanner_Enable(
        SCANNER_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SCANNER_DATA *   scanner_Init(
        SCANNER_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SCANNER_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SCANNER);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_SCANNER);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&scanner_Vtbl);
        
        obj_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "scanner::sizeof(SCANNER_DATA) = %lu\n", sizeof(SCANNER_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SCANNER_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         scanner_IsEnabled(
        SCANNER_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            obj_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS_FALSE);
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
        void        *pMethod = scanner_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "scanner", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          scanner_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SCANNER_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)scanner_Class();
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
                            return scanner_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return scanner_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return scanner_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return scanner_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == scanner_ToDebugString)
                    return "ToDebugString";
                if (pData == scanner_ToJSON)
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
        ASTR_DATA      *pDesc = scanner_ToDebugString(this,4);
     @endcode 
     @param     this    SCANNER object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     scanner_ToDebugString(
        SCANNER_DATA      *this,
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
        if( !scanner_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    scanner_getSize(this)
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     scanner_ToJSON(
        SCANNER_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !scanner_Validate(this) ) {
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            scanner_Validate(
        SCANNER_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_SCANNER) )
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


        if( !(obj_getSize(this) >= sizeof(SCANNER_DATA)) ) {
            obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return false;
        }

        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


