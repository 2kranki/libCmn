// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Scanner.c
 *	Generated 03/04/2020 21:17:29
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
#include        <Scanner_internal.h>
#include        <ascii.h>
#include        <AStrArray.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    
    #define  LOOKAHEAD(num)  Scanner_LookAhead(this, num);
    #define  ADVANCE(num)    Scanner_Advance(this, num);




 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /*!
     Add
        : Add '+' Mult
        | Add '-' Mult
        | Mult
        ;
     */
    int32_t         Scanner_Add(
        SCANNER_DATA    *this
    )
    {
        W32CHR_T        chr;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Scanner_Mult(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            if (chr == '+') {
                    ADVANCE(1);
                    iRc2 = Scanner_Mult(this);
                    iRc += iRc2;
            } else if (chr == '-') {
                    ADVANCE(1);
                    iRc2 = Scanner_Mult(this);
                    iRc -= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     And
        : And "&" Eq
        | Eq
        ;
     */
    int32_t         Scanner_And(
        SCANNER_DATA    *this
    )
    {
        W32CHR_T        chr;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Scanner_Eq(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            if (chr == '&') {
                    ADVANCE(1);
                    iRc2 = Scanner_Eq(this);
                    iRc &= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Eq
        : Eq "==" Rel
        | Eq "!=" Rel
        | Rel
        ;
     */
    int32_t         Scanner_Eq(
        SCANNER_DATA    *this
    )
    {
        W32CHR_T        chr;
        W32CHR_T        chr2;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Scanner_Rel(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            chr2 = LOOKAHEAD(2);
            if ((chr == '=') && (chr2 == '=')) {
                ADVANCE(2);
                iRc2 = Scanner_Rel(this);
                if (iRc == iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else if ((chr == '!') && (chr2 == '=')) {
                ADVANCE(2);
                iRc2 = Scanner_Rel(this);
                if (iRc != iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Expr
        : LogicalOr
        ;
     */
    int32_t         Scanner_Expr(
        SCANNER_DATA    *this
    )
    {
        return Scanner_LogicalOr(this);
    }


    /*!
     LogicalAnd
        : LogicalAnd "&&" Or
        | Or
        ;
     */
    int32_t         Scanner_LogicalAnd(
        SCANNER_DATA    *this
    )
    {
        W32CHR_T        chr;
        W32CHR_T        chr2;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Scanner_Or(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            chr2 = LOOKAHEAD(2);
            if ((chr == '&') && (chr2 == '&')) {
                ADVANCE(2);
                iRc2 = Scanner_Or(this);
                if (iRc && iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     LogicalOr
        : LogicalOr "||" LogicalAnd
        | LogicalAnd
        ;
     */
    int32_t         Scanner_LogicalOr(
        SCANNER_DATA    *this
    )
    {
        W32CHR_T        chr;
        W32CHR_T        chr2;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Scanner_LogicalAnd(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            chr2 = LOOKAHEAD(2);
            if ((chr == '|')  && (chr2 == '|')){
                ADVANCE(2);
                iRc2 = Scanner_LogicalAnd(this);
                if (iRc || iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Mult
        : Mult '*' Primary
        | Mult '/' Primary
        | Mult '%' Primary
        | Primary
        ;
     */
    int32_t         Scanner_Mult(
        SCANNER_DATA    *this
    )
    {
        W32CHR_T        chr;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Scanner_Primary(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            if (chr == '*') {
                ADVANCE(1);
                iRc2 = Scanner_Primary(this);
                iRc *= iRc2;
            } else if (chr == '/') {
                ADVANCE(1);
                iRc2 = Scanner_Primary(this);
                iRc /= iRc2;
            } else if (chr == '%') {
                ADVANCE(1);
                iRc2 = Scanner_Primary(this);
                iRc %= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Or
        : Or '|' Xor
        | Xor
        ;
     */
    int32_t         Scanner_Or(
        SCANNER_DATA    *this
    )
    {
        W32CHR_T        chr;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Scanner_Xor(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            if (chr == '|') {
                ADVANCE(1);
                iRc2 = Scanner_Xor(this);
                iRc |= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*
     primary
        : identifier
        | INTEGER
        | FLOAT
        | '(' expr ')'
        ;
     */
    int32_t         Scanner_Primary(
        SCANNER_DATA    *this
    )
    {
        int32_t         iRc = 0;
        W32CHR_T        chr;
        //ERESULT         eRc;
        bool            fRc;

        chr = LOOKAHEAD(1);
        if (chr == '(') {
            ADVANCE(1);
            iRc = Scanner_Expr(this);
            chr = LOOKAHEAD(1);
            if (chr != ')') {
                fprintf(stderr, "ERROR - Expecting ')' but found %c\n", chr);
                exit(4);
            }
            ADVANCE(1);
            return iRc;
        }

        fRc = Scanner_ScanInteger32(this, &iRc);
        if (fRc) {
            return iRc;
        }

#ifdef XYZZY
        switch (chr) {
            case PPLEX_CONSTANT_FLOAT:
                // Process number
                ADVANCE(1);
                return iRc;
                break;
            case PPLEX_IDENTIFIER:
                idxList =   cgmrTree_NodeNewUTF8(
                                                 this->pTree,
                                                 "PrimaryExpr",
                                                 CGMR_NODECLASS_PRIMARY_EXPR,
                                                 OBJ_NIL
                            );
                if (0 == idxList) {
                    srcErrors_AddFatalA(OBJ_NIL, NULL, "Out of Memory");
                }
                TOKEN_DATA          *pTokenNew = Token_Copy(pToken);
                idxNode =   cgmrTree_NodeNewUTF8(
                                                 this->pTree,
                                                 "Id",
                                                 CGMR_NODECLASS_ID,
                                                 pTokenNew
                                                 );
                obj_Release(pTokenNew);
                if (0 == idxNode) {
                    srcErrors_AddFatalA(OBJ_NIL, NULL, "Out of Memory");
                }
                eRc = cgmrTree_NodeLinkChild(this->pTree, idxList, idxNode);
                BREAK_FAILED(eRc);
                ADVANCE(1);
                return iRc;
                break;
            case PPLEX_CONSTANT_INTEGER:
                // Process number
                ADVANCE(1);
                return iRc;
                break;
            case PPLEX_OP_SUB:
                // Process unary '-'
                // Look for and process Integer or Float.
                ADVANCE(1);
                return iRc;
                break;
            case PPLEX_SEP_LPAREN:
                iRc = Scanner_Expr(this);
                // Process unary '-'
                // Look for and process Integer or Float.
                ADVANCE(1);
                return iRc;
                break;
            default:
                // ERROR - Needed ... but found <cls>!
                break;
        }
#endif

        return iRc;
    }


    /*!
     Rel
        : Rel ">=" Shift
        | Rel "<=" Shift
        | Rel '>'  Shift
        | Rel '<'  Shift
        | Shift
        ;
     */
    int32_t         Scanner_Rel(
        SCANNER_DATA    *this
    )
    {
        W32CHR_T        chr;
        W32CHR_T        chr2;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Scanner_Shift(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            chr2 = LOOKAHEAD(2);
            if ((chr == '>') && (chr2 == '=')) {
                ADVANCE(2);
                iRc2 = Scanner_Shift(this);
                if (iRc >= iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else if ((chr == '<') && (chr2 == '=')) {
                ADVANCE(2);
                iRc2 = Scanner_Shift(this);
                if (iRc <= iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else if (chr == '>') {
                ADVANCE(1);
                iRc2 = Scanner_Shift(this);
                if (iRc > iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else if (chr == '<') {
                ADVANCE(1);
                iRc2 = Scanner_Shift(this);
                if (iRc <= iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Shift
        : Shift ">>" Add
        | Shift "<<" Add
        | Add
        ;
     */
    int32_t         Scanner_Shift(
        SCANNER_DATA    *this
    )
    {
        W32CHR_T        chr;
        W32CHR_T        chr2;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Scanner_Add(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            chr2 = LOOKAHEAD(2);
            if ((chr == '<') && (chr2 == '<')) {
                ADVANCE(2);
                iRc2 = Scanner_Rel(this);
                iRc <<= iRc2;
            } else if ((chr == '>') && (chr2 == '>')) {
                ADVANCE(2);
                iRc2 = Scanner_Rel(this);
                iRc >>= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Xor
        : Xor '^' And
        | And
        ;
     */
    int32_t         Scanner_Xor(
        SCANNER_DATA    *this
    )
    {
        W32CHR_T        chr;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Scanner_And(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            if (chr == '^') {
                ADVANCE(1);
                iRc2 = Scanner_And(this);
                iRc ^= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }



#ifdef XYZZY
    bool            Scanner_ParseCmdStr(
        SCANNER_DATA    *cbp,
        char            *pCmdStr,
        uint32_t        *pNumArgs,

    )
    {
        uint16_t        cbSize;
        int             Num = 0;
        int             cArgs = 0;
        char            *pCurCmd;
        char            quote;

        // Do initialization.
        if( pCmdStr == NULL )
            return( false );
        cbp->cArg = 1;
        cbSize = 2 * sizeof(char *);
        cbp->ppArg = (char **)mem_Malloc( cbSize );
        if( cbp->ppArg ) {
            cbp->flags |= GOT_ARGV;
        }
        else
            return false;
        *(cbp->ppArg) = "";     // Set program name.

        // Scan off the each parameter.
        while( *pCmdStr ) {
            pCurCmd = NULL;
            // Pass over white space.
            while( *pCmdStr && ((*pCmdStr == ' ') || (*pCmdStr == '\n')
                                || (*pCmdStr == '\r') || (*pCmdStr == '\t')) )
                ++pCmdStr;
            // Handle Quoted Arguments.
            if( (*pCmdStr == '\"') || (*pCmdStr == '\'') ) {
                quote = *pCmdStr++;
                pCurCmd = pCmdStr;
                while( *pCmdStr && (*pCmdStr != quote) ) {
                    ++pCmdStr;
                }
                if( *pCmdStr ) {
                    *pCmdStr = '\0';
                    ++pCmdStr;
                }
            }
            // Handle Non-Quoted Arguments.
            else if( *pCmdStr ) {
                pCurCmd = pCmdStr;
                // Scan until white space.
                while( *pCmdStr && !((*pCmdStr == ' ') || (*pCmdStr == '\n')
                                     || (*pCmdStr == '\r') || (*pCmdStr == '\t')) ) {
                    ++pCmdStr;
                }
                if( *pCmdStr ) {
                    *pCmdStr = '\0';
                    ++pCmdStr;
                }
            }
            else
                continue;
            // Add the command to the array.
            if( pCurCmd ) {
                ++Num;
                cbp->ppArg = (char **)mem_Realloc( cbp->ppArg, ((Num + 2) * sizeof(char *)) );
                if( cbp->ppArg ) {
                    cbp->ppArg[Num]   = pCurCmd;
                    cbp->ppArg[Num+1] = NULL;
                    ++cbp->cArg;
                }
                else
                    return( false );
            }
        }

        // Return to caller.
        return true;
    }
#endif



#ifdef XYZZY
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
    scanner_ScanWhite(&pCurChr, NULL);

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



#endif



#ifdef XYZZY
    /*!
     Set up an ArgC/ArgV type array given a command line string
     excluding the program name.
     @param     pStrA    Pointer to a UTF-8 Argument character string
     @return    If successful, an AStrArray object which must be
                released containing the Argument Array, otherwise
                OBJ_NIL if an error occurred.
     @warning   Remember to release the returned AStrArray object.
     */
    ASTRARRAY_DATA * scanner_ScanStringToAStrArray(
        const
        char            *pStrA
    )
    {
        ERESULT         eRc;
        bool            fRc;
        char            *pCurCmd;
        uint32_t        cmdLen = 0;
        char            *pCurChr;
        ASTRARRAY_DATA  *pArgs = OBJ_NIL;
        ASTR_DATA       *pArg = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if(pStrA && (utf8_StrLenA(pStrA) > 0))
            ;
        else {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        pArgs = AStrArray_New( );
        if (OBJ_NIL == pArgs) {
            DEBUG_BREAK();
            //return ERESULT_OUT_OF_MEMORY;
            return OBJ_NIL;
        }
        pCurChr = (char *)pStrA;

        // Set up program name argument.
        pArg = AStr_NewA("");
        if (pArg) {
            eRc = AStrArray_AppendStr(pArgs, pArg, NULL);
            obj_Release(pArg);
            pArg = OBJ_NIL;
        }

        // Scan off the each parameter.
        while( pCurChr && *pCurChr ) {
            pCurCmd = NULL;
            cmdLen = 0;

            // Pass over white space.
            fRc = scanner_ScanWhite(&pCurChr, NULL);

            // Handle Quoted Arguments.
            pArg = scanner_ScanStringToAStr(&pCurChr, NULL);
            if (pArg) {
                eRc = AStrArray_AppendStr(pArgs, pArg, NULL);
                obj_Release(pArg);
                pArg = OBJ_NIL;
            }

            // Pass over white space.
            if ((',' == *pCurChr) || ('\t' == *pCurChr)) {
                ++pCurChr;
            }
        }

        // Return to caller.
        return pArgs;
    }
#endif



#ifdef XYZZY
#endif



    bool            Scanner_IsSeparator(
        W32CHR_T        chr

    )
    {
        bool            fRc = false;

        if ((chr == '\0') || (',' == chr) || ascii_isWhiteSpaceW32(chr)) {
            fRc = true;
        }
        return fRc;
    }



    bool            Scanner_IsTerminator(
        SCANNER_DATA    *this,
        W32CHR_T        chr

    )
    {
        bool            fRc = false;

        if (Scanner_IsSeparator(chr) || (this->sep && (this->sep == chr))) {
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

    SCANNER_DATA *     Scanner_Alloc (
        void
    )
    {
        SCANNER_DATA       *this;
        uint32_t        cbSize = sizeof(SCANNER_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SCANNER_DATA *     Scanner_New (
        void
    )
    {
        SCANNER_DATA       *this;
        
        this = Scanner_Alloc( );
        if (this) {
            this = Scanner_Init(this);
        } 
        return this;
    }



    SCANNER_DATA *  Scanner_NewA (
        const
        char            *pStrA
    )
    {
        SCANNER_DATA    *this;
        bool            fRc;

        this = Scanner_New( );
        if (this) {
            fRc = W32StrC_SetupA((W32STRC_DATA *)this, pStrA);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }



    SCANNER_DATA *  Scanner_NewW32 (
        const
        W32CHR_T        *pStrW32
    )
    {
        SCANNER_DATA    *this;
        bool            fRc;

        this = Scanner_New( );
        if (this) {
            fRc = W32StrC_SetupW32((W32STRC_DATA *)this, 0, pStrW32);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return( this );
    }


    SCANNER_DATA *  Scanner_NewFromW32 (
        uint32_t        len,
        const
        W32CHR_T        *pStrW32
    )
    {
        SCANNER_DATA    *this;
        bool            fRc;

        this = Scanner_New( );
        if (this) {
            fRc = W32StrC_SetupW32((W32STRC_DATA *)this, len, pStrW32);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return( this );
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                     S c a n  I n d e x
    //---------------------------------------------------------------

    uint32_t        Scanner_getIndex (
        SCANNER_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return obj_getMisc(this);
    }

    bool            Scanner_setIndex(
        SCANNER_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Scanner_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_setMisc(this, value);

        return true;
    }



    //---------------------------------------------------------------
    //                     S e p e r a t o r
    //---------------------------------------------------------------

    W32CHR_T        Scanner_getSeperator (
        SCANNER_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->sep;
    }


    bool            Scanner_setSeperator (
        SCANNER_DATA    *this,
        W32CHR_T        value
    )
    {
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->sep = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Scanner_getSize (
        SCANNER_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return W32StrC_getSize((W32STRC_DATA *)this);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Scanner_getSuperVtbl (
        SCANNER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                       W 3 2 S t r C
    //---------------------------------------------------------------

    W32STRC_DATA *  Scanner_getW32StrC (
        SCANNER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (W32STRC_DATA *)this;
    }




    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                      A d v a n c e
    //---------------------------------------------------------------

    void            Scanner_Advance (
        SCANNER_DATA    *this,
        int32_t         offset
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return;
        }
#endif

        W32StrC_Advance((W32STRC_DATA *)this, offset);

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
        ERESULT eRc = Scanner_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SCANNER object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Scanner_Assign (
        SCANNER_DATA	*this,
        SCANNER_DATA    *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Scanner_Validate(pOther)) {
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
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                         C a l c
    //---------------------------------------------------------------

    /*!
     Assume that the scanner string is an expression, parse it and
     calculate its answer.
     @param     this    object pointer
     @param     pAnswer pointer where answer is returned
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Scanner_Calc (
        SCANNER_DATA    *this,
        int32_t         *pAnswer
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int32_t         ans = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        ans = Scanner_Expr(this);

        // Return to caller.
        if (pAnswer)
            *pAnswer = ans;
        return eRc;
    }



    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Scanner_Compare (
        SCANNER_DATA    *this,
        SCANNER_DATA    *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Scanner_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        iRc = W32StrC_Compare((W32STRC_DATA *)this, (W32STRC_DATA *)pOther);

        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Scanner      *pCopy = Scanner_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SCANNER object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SCANNER_DATA *     Scanner_Copy (
        SCANNER_DATA       *this
    )
    {
        SCANNER_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SCANNER_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Scanner_New( );
        if (pOther) {
            eRc = Scanner_Assign(this, pOther);
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

    void            Scanner_Dealloc (
        OBJ_ID          objId
    )
    {
        SCANNER_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SCANNER_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

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
        Scanner      *pDeepCopy = Scanner_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SCANNER object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SCANNER_DATA *     Scanner_DeepyCopy (
        SCANNER_DATA       *this
    )
    {
        SCANNER_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Scanner_New( );
        if (pOther) {
            eRc = Scanner_Assign(this, pOther);
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
    ERESULT         Scanner_Disable (
        SCANNER_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
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
    ERESULT         Scanner_Enable (
        SCANNER_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
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
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    uint32_t        Scanner_Hash (
        SCANNER_DATA    *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Return to caller.
        return W32StrC_Hash((W32STRC_DATA *)this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SCANNER_DATA *   Scanner_Init (
        SCANNER_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SCANNER_DATA);
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

        this = (OBJ_ID)W32StrC_Init((W32STRC_DATA *)this);        // Needed for Inheritance
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Scanner_Vtbl);
#ifdef  SCANNER_JSON_SUPPORT
        JsonIn_RegisterClass(W32StrC_Class());
        JsonIn_RegisterClass(Scanner_Class());
#endif

        this->pIsLabelCharW32 = ascii_isLabelCharW32;
        this->pIsLabel1stCharW32 = ascii_isLabelFirstCharW32;

#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Scanner::sizeof(SCANNER_DATA) = %lu\n", 
                sizeof(SCANNER_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SCANNER_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool            Scanner_IsEnabled (
        SCANNER_DATA	*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return false;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return true;
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s  M o r e
    //---------------------------------------------------------------

    bool            Scanner_IsMore (
        SCANNER_DATA    *this
    )
    {
        //ERESULT         eRc = ERESULT_FAILURE;
        W32CHR_T        chr;
        bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return false;
        }
#endif

        fRc = Scanner_ScanWS(this);
        if (fRc) {
            chr = Scanner_LookAhead(this, 1);
            if (chr) {
                return true;
            }
        }

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                       L o o k  A h e a d
    //---------------------------------------------------------------

    W32CHR_T        Scanner_LookAhead(
        SCANNER_DATA    *this,
        uint32_t        offset              // Relative to 1
    )
    {
        //ERESULT         eRc;
        uint32_t        amt = 0;
        W32CHR_T        chr = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        amt = obj_getMisc(this);
        amt += offset - 1;
        if (amt < W32StrC_getLength((W32STRC_DATA *)this))
            chr = ((W32STRC_DATA *)this)->pArray[amt];

        return chr;
    }



    //---------------------------------------------------------------
    //                          M a t c h
    //---------------------------------------------------------------

    bool            Scanner_MatchChr(
        SCANNER_DATA    *this,
        W32CHR_T        chr
    )
    {
        bool            fMatch = true;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        fMatch = W32StrC_MatchChr((W32STRC_DATA *)this, chr);

        return fMatch;
    }


    bool            Scanner_MatchStrA(
        SCANNER_DATA    *this,
        const
        char            *pStrA
    )
    {
        bool            fMatch = true;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        fMatch = W32StrC_MatchStrA((W32STRC_DATA *)this, pStrA);

        return fMatch;
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
        void        *pMethod = Scanner_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Scanner", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Scanner_QueryInfo (
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
        if (!Scanner_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SCANNER_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Scanner_Class();
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
                            return Scanner_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Scanner_Enable;
                        }
                        break;

#ifdef  SCANNER_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Scanner_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Scanner_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Scanner_ToDebugString;
                        }
#ifdef  SCANNER_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Scanner_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Scanner_ToDebugString)
                    return "ToDebugString";
#ifdef  SCANNER_JSON_SUPPORT
                if (pData == Scanner_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------

        void            Scanner_Reset (
            SCANNER_DATA    *this
        )
        {
            //ERESULT         eRc;

            // Do initialization.
    #ifdef NDEBUG
    #else
            if (!Scanner_Validate(this)) {
                DEBUG_BREAK();
                // return ERESULT_INVALID_OBJECT;
                return;
            }
    #endif

            W32StrC_Reset((W32STRC_DATA *)this);

        }



    //---------------------------------------------------------------
    //                    S c a n  S t r i n g
    //---------------------------------------------------------------

    ASTR_DATA *     Scanner_ScanIdentifierToAStr(
        SCANNER_DATA    *this
    )
    {
        bool            fRc = false;
        ASTR_DATA       *pStr = OBJ_NIL;
        W32CHR_T        chr;
        uint32_t        len = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Scanner_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        pStr = AStr_New( );
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }

        // Scan off leading white-space.
        Scanner_ScanWS(this);

        // Scan the paramter.
        chr = Scanner_LookAhead(this, len+1);
        if(chr) {
            if (this->pIsLabel1stCharW32(chr)) {
                AStr_AppendCharW32(pStr, chr);
                len += 1;
                fRc = true;
                for (;;) {
                    chr  = Scanner_LookAhead(this, len+1);
                    if (this->pIsLabelCharW32(chr)) {
                        AStr_AppendCharW32(pStr, chr);
                        len += 1;
                        fRc = true;
                    } else {
                        break;
                    }
                }
            }
        }


        // Return to caller.
    Exit00:
        if (fRc && len) {
            Scanner_Advance(this, len);
        }
        if (!fRc) {
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        return pStr;
    }



    //---------------------------------------------------------------
    //                    S c a n  I n t e g e r 32
    //---------------------------------------------------------------

    bool            Scanner_ScanInteger32(
        SCANNER_DATA    *this,
        int32_t         *pValue             // (returned) Scanned Number
    )
    {
        bool            fRc = false;
        bool            fNegative = false;
        int32_t         value = 0;
        W32CHR_T        chr;
        W32CHR_T        chr2;
        uint32_t        len = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Scanner_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        // Scan off leading white-space.
        Scanner_ScanWS(this);

        chr = Scanner_LookAhead(this, len+1);
        if ('0' == chr) {
            chr2 = Scanner_LookAhead(this, len+2);
            if (('x' == chr2) || ('X' == chr2)) {
                len += 2;
                for (;;) {
                    chr = Scanner_LookAhead(this, len+1);
                    if (ascii_isHexW32(chr)) {
                        value <<= 4;
                        value |= ascii_FromHexW32(chr);
                        len += 1;
                        fRc = true;
                    } else {
                        break;
                    }
                }
                goto Exit;
            } else {
                len += 1;
                for (;;) {
                    chr = Scanner_LookAhead(this, len+1);
                    if( ('0' <= chr) && ('7' >= chr) ) {
                        value = (value << 3) + (chr - '0');
                        len += 1;
                    } else {
                        break;
                    }
                }
                fRc = true;
                goto Exit;
            }
        } else {
            if( '-' == chr ) {
                fNegative = true;
                len += 1;
            }
            else if( '+' == chr ) {
                len += 1;
            }
            for (;;) {
                chr = Scanner_LookAhead(this, len+1);
                if( ('0' <= chr) && ('9' >= chr) ) {
                    value = (value << 3) + (value << 1) + (chr - '0');
                    len += 1;
                    fRc = true;
                }
                else
                    break;
            }
            if( fNegative ) {
                value = -value;
            }
        }


        // Return to caller.
    Exit:
        if (fRc && len) {
            Scanner_Advance(this, len);
        }
        if(pValue) {
            *pValue = value;
        }
        return fRc;
    }



    //---------------------------------------------------------------
    //                    S c a n  S t r i n g
    //---------------------------------------------------------------

    /* CmdStr is scanned one character at a time into the Output
     * buffer supplied. The scan will go until it hits end of line or
     * the end of the string. It will copy at most maxLen characters
     * to the output.
     */
    ASTR_DATA *     Scanner_ScanStringToAStr(
        SCANNER_DATA    *this
    )
    {
        bool            fRc = false;
        W32CHR_T        Quote = 0;
        ASTR_DATA       *pStr = OBJ_NIL;
        W32CHR_T        chr;
        W32CHR_T        chr2;
        uint32_t        len = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Scanner_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        pStr = AStr_New( );
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }

        // Scan off leading white-space.
        Scanner_ScanWS(this);

        // Scan the paramter.
        chr = Scanner_LookAhead(this, len+1);
        if(chr) {
            // Handle Quoted Arguments.
            if( ('"' == chr) || ('\'' == chr) ) {
                Quote = chr;
                len += 1;
                for (;;) {
                    chr = Scanner_LookAhead(this, len+1);
                    if (chr == '\0') {
                        // ERROR - End of String in middle of quoted string
                        fRc = false;
                        goto Exit00;
                    }
                    if( chr == Quote ) {
                        chr2 = Scanner_LookAhead(this, len+2);
                        if( chr2 == Quote ) {
                            len += 2;
                            AStr_AppendCharW32(pStr, Quote);
                            fRc = true;
                        }
                        else {
                            len += 1;
                            break;
                        }
                    }
                    else if( chr == '\\' ) {
                        chr2 = Scanner_LookAhead(this, len+2);
                        if( chr2 == Quote ) {
                            len += 1;
                        } else if( chr2 == '0' ) {
                            len += 2;
                            AStr_AppendCharA(pStr, '\0');
                            fRc = true;
                        } else if( chr2 == 'b' ) {
                            len += 2;
                            AStr_AppendCharA(pStr, '\b');
                            fRc = true;
                            continue;
                        } else if( chr2 == 'f' ) {
                            len += 2;
                            AStr_AppendCharA(pStr, '\f');
                            fRc = true;
                            continue;
                        } else if( chr2 == 'n' ) {
                            len += 2;
                            AStr_AppendCharA(pStr, '\n');
                            fRc = true;
                            continue;
                        } else if( chr2 == 'r' ) {
                            len += 2;
                            AStr_AppendCharA(pStr, '\r');
                            fRc = true;
                            continue;
                        } else if( chr2 == 'x' ) {
                            len += 2;
                            // At this point, we need two more characters of 0..9,a..f,A..F
                            // to give us our hex character.
                            chr  = Scanner_LookAhead(this, len+1);
                            chr2 = Scanner_LookAhead(this, len+2);
                            if (('\0' == chr) || ('\0' == chr2)) {
                                goto Exit00;
                            }
                            chr2 = 0;
                            if (ascii_isHexW32(chr)) {
                                chr2 <<= 4;
                                chr2 |= ascii_FromHexW32(chr);
                                len += 1;
                                fRc = true;
                            } else {
                                fRc = false;
                                goto Exit00;
                            }
                            chr  = Scanner_LookAhead(this, len+1);
                            if (ascii_isHexW32(chr)) {
                                chr2 <<= 4;
                                chr2 |= ascii_FromHexW32(chr);
                                len += 1;
                                fRc = true;
                            } else {
                                fRc = false;
                                goto Exit00;
                            }
                            if (fRc) {
                                AStr_AppendCharW32(pStr, chr2);
                                fRc = true;
                            } else {
                                goto Exit00;
                            }
                            continue;
                        }
                    }
                    else {
                        AStr_AppendCharW32(pStr, chr);
                        len += 1;
                        fRc = true;
                    }
                }
            } else {
                // Handle Non-Quoted Arguments.
                for (;;) {
                    chr  = Scanner_LookAhead(this, len+1);
                    if (Scanner_IsSeparator(chr) || ('"' == chr) || ('\'' == chr)) {
                        break;
                    } else {
                        AStr_AppendCharW32(pStr, chr);
                        len += 1;
                        fRc = true;
                    }
                }
            }
            chr  = Scanner_LookAhead(this, len+1);
            if (chr && Scanner_IsTerminator(this, chr)) {
                len += 1;
            }
        }


        // Return to caller.
    Exit00:
        if (fRc && len) {
            Scanner_Advance(this, len);
        }
        if (!fRc) {
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        return pStr;
    }



        /*!
         Set up an ArgC/ArgV type array given a command line string
         excluding the program name.
         @return    If successful, an AStrArray object which must be
                    released containing the Argument Array, otherwise
                    OBJ_NIL if an error occurred.
         @warning   Remember to release the returned AStrArray object.
         */
        ASTRARRAY_DATA * Scanner_ScanStringToAstrArray(
            SCANNER_DATA    *this
        )
        {
            ERESULT         eRc;
            bool            fRc = false;
            ASTRARRAY_DATA  *pArgs = OBJ_NIL;
            ASTR_DATA       *pArg = OBJ_NIL;
            W32CHR_T        chr;

            // Do initialization.
#ifdef NDEBUG
#else
        if( !Scanner_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
            pArgs = AStrArray_New( );
            if (OBJ_NIL == pArgs) {
                DEBUG_BREAK();
                //return ERESULT_OUT_OF_MEMORY;
                return OBJ_NIL;
            }

            // Set up program name argument.
            pArg = AStr_NewA("");
            if (pArg) {
                eRc = AStrArray_AppendStr(pArgs, pArg, NULL);
                obj_Release(pArg);
                pArg = OBJ_NIL;
            }

            // Scan off the each parameter.
            for (;;) {
                chr  = Scanner_LookAhead(this, 1);
                if (chr) {
                    // Pass over white space.
                    fRc = Scanner_ScanWS(this);

                    // Handle Quoted Arguments.
                    pArg = Scanner_ScanStringToAStr(this);
                    if (pArg) {
                        eRc = AStrArray_AppendStr(pArgs, pArg, NULL);
                        obj_Release(pArg);
                        pArg = OBJ_NIL;
                        fRc = true;
                    }

                    // Pass over terminator.
                    chr  = Scanner_LookAhead(this, 1);
                    if (Scanner_IsSeparator(chr)) {
                        Scanner_Advance(this, 1);
                    }

                }
                else {
                    break;
                }
            }

            // Return to caller.
            if (!fRc) {
                obj_Release(pArgs);
                pArgs = OBJ_NIL;
            }
            return pArgs;
        }



    //---------------------------------------------------------------
    //                    S c a n  W h i t e  S p a c e
    //---------------------------------------------------------------

    bool            Scanner_ScanWS(
        SCANNER_DATA    *this
    )
    {
        W32CHR_T        chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Scanner_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        // Scan off leading white-space.
        for (;;) {
            chr = Scanner_LookAhead(this, 1);
            if (ascii_isWhiteSpaceW32(chr)) {
                Scanner_Advance(this, 1);
            }
            else
                break;
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Scanner_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Scanner_ToDebugString (
        SCANNER_DATA      *this,
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
        if (!Scanner_Validate(this)) {
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
                    Scanner_getSize(this),
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
    bool            Scanner_Validate (
        SCANNER_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SCANNER))
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


        if (!(obj_getSize(this) >= sizeof(SCANNER_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


