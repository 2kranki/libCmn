// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   pplex2.c
 *	Generated 05/25/2015 23:36:46
 *
 * Created on December 30, 2014
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
#include        <pplex2_internal.h>
#include        <pplex3.h>
#include        <ascii.h>
#include        <SrcErrors.h>
#include        <trace.h>
#include        <W32Str.h>


#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    
    /****************************************************************
     * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    
 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/


    // Save the text with the special brackets: %{ %} or %[ %] or %( %)
    // The text may not contain the ending bracket within it. Because
    // we are using a special sequence to bracket the text, we do not
    // need to be concerned about what is in the text.
    W32STR_DATA *   pplex2_SaveText(
        PPLEX2_DATA     *this,
        int32_t         terminatorChar1,    // '%' or '.'
        int32_t         terminatorChar2     // '>' or '}' or ']' or ')'
    )
    {
        bool            fMore = true;
        int32_t         curchr;
        TOKEN_DATA      *pNxtChr = OBJ_NIL;
        W32STR_DATA     *pBuffer;
        
#ifdef NDEBUG
#else
        if( !pplex2_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
        switch (terminatorChar1) {
            case '%':
                break;
            case '.':
                break;
            default:
                DEBUG_BREAK();
                return false;
                break;
        }
        switch (terminatorChar2) {
            case '}':
                break;
            case ']':
                break;
            case ')':
                break;
            case '>':
                break;
            default:
                DEBUG_BREAK();
                return false;
                break;
        }
#endif
        
        pBuffer = W32Str_New( );
        if (OBJ_NIL == pBuffer) {
            SrcErrors_AddFatalA(
                            OBJ_NIL,
                            NULL,
                            "ll1aux_SaveCopyText: failed to create SBUF!"
            );
            obj_Release(pBuffer);
            return OBJ_NIL;
        }
        
        /* Output the union information.
         */
        while( fMore ) {
            pNxtChr = lex_InputLookAhead((LEX_DATA *)this, 1);
            curchr = Token_getChrW32(pNxtChr);
            if ( curchr == -1 ) {
                SrcErrors_AddFatalA(
                                   OBJ_NIL,
                                   NULL,
                                   "ll1aux_SaveCopyText: premature EOF!"
                );
                obj_Release(pBuffer);
                return OBJ_NIL;
            }
            else if (curchr == terminatorChar1) {
                /* Look for term char 1 followed by term char 2. */
                pNxtChr = lex_InputLookAhead((LEX_DATA *)this, 2);
                curchr = Token_getChrW32(pNxtChr);
                if( curchr == terminatorChar2 ) {
                    ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 1);
                    fMore = false;
                }
                else {
                    W32Str_AppendCharW32(pBuffer, 1, terminatorChar1);
                }
            }
            else {
                W32Str_AppendCharW32(pBuffer, 1, curchr);
            }
            ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 1);
        }
        W32Str_AppendCharW32(pBuffer, 1, '\n');
        
        return pBuffer;
    }
    
    
    

    
    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PPLEX2_DATA *   pplex2_Alloc(
    )
    {
        PPLEX2_DATA     *this;
        uint32_t        cbSize = sizeof(PPLEX2_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    PPLEX2_DATA *   pplex2_New(
        uint16_t        k
    )
    {
        PPLEX2_DATA     *cbp;
        
        // Do initialization.
        
        cbp = pplex2_Alloc( );
        if (cbp) {
            cbp = pplex2_Init(cbp,k);
        }
        
        // Return to caller.
        return( cbp );
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================
    
    bool            pplex2_getComments(
        PPLEX2_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !pplex2_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return this->fComments;
    }
    
    
    //---------------------------------------------------------------
    //               L e x i c a l  S c a n n e r
    //---------------------------------------------------------------

    LEX_DATA *      pplex2_getLex(
        PPLEX2_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !pplex2_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (LEX_DATA *)this;
    }



    bool            pplex2_setComments(
        PPLEX2_DATA     *this,
        bool            value
        )
    {
        bool            fRc = true;
        
#ifdef NDEBUG
#else
        if( !pplex2_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->fComments = value;
        
        return fRc;
    }
    
    
    
    bool            pplex2_setKwdSelection(
        PPLEX2_DATA     *this,
        uint16_t        value
    )
    {
        
#ifdef NDEBUG
#else
        if( !pplex2_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->kwdSel = value;
        
        // Return to caller.
        return true;
    }
    
    

    
    //---------------------------------------------------------------
    //                     R e t u r n  N L s
    //---------------------------------------------------------------
    
    bool            pplex2_getReturnNL(
        PPLEX2_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !pplex2_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return obj_IsFlag(this, PPLEX2_RETURN_NL);
    }
    
    
    bool            pplex2_setReturnNL(
        PPLEX2_DATA     *this,
        bool            value
    )
    {
        bool            fRc;
        
#ifdef NDEBUG
#else
        if( !pplex2_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = obj_FlagSet(this, PPLEX2_RETURN_NL, value);
        
        return fRc;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                R e t u r n  W h i t e s p a c e
    //---------------------------------------------------------------
    
    bool            pplex2_getReturnWS (
        PPLEX2_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if (!pplex2_Validate(this)) {
            DEBUG_BREAK();
        }
#endif
        return obj_IsFlag(this, PPLEX2_RETURN_WS);
    }
    
    
    bool            pplex2_setReturnWS (
        PPLEX2_DATA     *this,
        bool            value
    )
    {
        bool            fRc;
        
#ifdef NDEBUG
#else
        if (!pplex2_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = obj_FlagSet(this, PPLEX2_RETURN_WS, value);
        
        return fRc;
    }
    
    
    
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            pplex2_Dealloc (
        OBJ_ID          objId
    )
    {
        PPLEX2_DATA     *this = objId;
        //bool            fRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!pplex2_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------
    
    PPLEX2_DATA *   pplex2_Init(
        PPLEX2_DATA     *this,
        uint16_t        k
    )
    {
        uint32_t        cbSize = sizeof(PPLEX2_DATA);
        bool            fRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);         // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = (PPLEX2_DATA *)lex_Init( (LEX_DATA *)this, k );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&pplex2_Vtbl);
        
        fRc =   lex_setParserFunction(
                                (LEX_DATA *)this,
                                (void *)pplex2_ParseToken,
                                this
                );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !pplex2_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //--------------------------------------------------------------
    //                      P a r s e  T o k e n
    //--------------------------------------------------------------
    
    /* ParseToken() gets the next token from the source file. It
     * saves that token for the file/line/col numbers and then
     * proceeds to build upon it. It accumulates tokens until
     * based on the class/type. When it finds a token which does
     * not belong to that class, it saves the current token
     * string to the string table, and tells the source file
     * to re-use the token which did not match on the next parse.
     * The token returned from this routine has the index of the
     * token string in the string table if it is larger than 1
     * character.
     *
     * This method does not use the Output Token, but uses lex_
     * functions to create the parsed token.
     */

    bool            pplex2_ParseToken(
        PPLEX2_DATA     *this,
        TOKEN_DATA      *pTokenOut          // Optional Output Token
    )
    {
        ERESULT         eRc;
        TOKEN_DATA      *pInput;
        int32_t         cls;
        int32_t         newCls = 0;
        int32_t         chr;
        bool            fMore = true;
        bool            fSaveStr = true;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pplex2_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        while (fMore) {
            pInput = lex_InputLookAhead((LEX_DATA *)this, 1);
            if (pInput) {
                cls = Token_getClass(pInput);
            }
            else {
                pInput = lex_ParseEOF((LEX_DATA *)this);
                cls = Token_getClass(pInput);
                DEBUG_BREAK();
            }
            eRc = lex_ParseTokenSetup((LEX_DATA *)this, pInput);
            if (cls == EOF) {
                fSaveStr = false;
                newCls = LEX_CLASS_EOF;
                break;
            }

            switch (cls) {

                case ASCII_LEXICAL_WHITESPACE:
                    if (obj_IsFlag(this, PPLEX2_RETURN_WS)) {
                        chr = Token_getChrW32(pInput);
                        if (obj_IsFlag(this, PPLEX2_RETURN_NL)) {
                            if ('\n' ==  chr) {
                                newCls = PPLEX_SEP_NL;
                                lex_InputAdvance((LEX_DATA *)this, 1);
                                fMore = false;
                                break;
                            }
                        }
                        pplex2_ParseWhiteSpace(this);
                        newCls = PPLEX_SEP_WHITESPACE;
                        fMore = false;
                    }
                    else {
                        lex_InputAdvance((LEX_DATA *)this, 1);
                    }
                    break;

                case ASCII_LEXICAL_EOL:
                    if (obj_IsFlag(this, PPLEX2_RETURN_NL)) {
                        newCls = PPLEX_SEP_NL;
                        lex_InputAdvance((LEX_DATA *)this, 1);
                        fMore = false;
                    }
                    else {
                        lex_InputAdvance((LEX_DATA *)this, 1);
                    }
                    break;
                    
                case ASCII_LEXICAL_ALPHA_LOWER:
                case ASCII_LEXICAL_ALPHA_UPPER:
                    lex_ParseName((LEX_DATA *)this);
                    newCls = PPLEX_IDENTIFIER;
#ifdef XYZZY
                    pKWD = pplex2_KWSearch(this, lex_getString((LEX_DATA *)this));
                    if (pKWD) {
                        if (pKWD->flags) {
                            if (cbp->kwdSel & pKWD->flags) {
                                newCls = pKWD->value;
                            }
                        }
                        else {
                            newCls = pKWD->value;
                        }
                    }
#endif
                    fMore = false;
                    break;

                case ASCII_LEXICAL_NUMBER:
                    newCls = lex_ParseNumber((LEX_DATA *)this);
                    if (newCls) {
                        uint16_t        type;
                        type = lex_ParseIntegerSuffix((LEX_DATA *)this);
                        Token_setMisc(&this->super.token, type);
                    }
                    fMore = false;
                    break;
                    
                case '!':           /*** '!' ***/
                    newCls = PPLEX_OP_NOT;
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj,2);
                    if( '=' == Token_getClass(pInput)) {
                        newCls = PPLEX_OP_NE;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;

                case '"':           /*** '"' ***/
                    ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 1);
                    while(lex_ParseChrCon((LEX_DATA *)this,'"'))
                        ;
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj,1);
                    cls = Token_getClass(pInput);
                    if (cls == '"') {
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 1);
                        newCls = PPLEX_CONSTANT_STRING;
                        fMore = false;
                        break;
                    }
                    else {
                        SrcErrors_AddFatalFromTokenA(
                                OBJ_NIL,
                                pInput,
                                "Malformed String constant"
                        );
                    }
                    break;
                    
                case '#':           /*** '#' ***/
                    newCls = PPLEX_OP_POUND;
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '#' == cls) {
                        newCls = PPLEX_SPCL_2POUNDS;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 2);
                        fMore = false;
                        break;
                    }
                    ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 1);
                    fMore = false;
                    break;

                case '$':           /*** '$' ***/
                    lex_ParseName((LEX_DATA *)this);
                    newCls = PPLEX_IDENTIFIER;
                    fMore = false;
                    break;
                    
                case '%':           /*** '%' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '%' == cls) {
                        newCls = PPLEX_SPCL_SEPARATOR;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 2);
                        fMore = false;
                        break;
                    }
                    if( '=' == cls) {
                        newCls = PPLEX_OP_ASSIGN_MOD;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 2);
                        fMore = false;
                        break;
                    }
                    if( '[' == cls) {
                        newCls = PPLEX_SPCL_LBRACK;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 2);
                        if (this->kwdSel & PPLEX_LANG_LL1) {
                            W32STR_DATA     *pStr;
                            pStr = pplex2_SaveText(this,'%',']');
                            if (pStr) {
                                uint32_t        token;
                                newCls = PPLEX_CONSTANT_TEXTB;
                                token =     szTbl_StringW32ToToken(
                                                        szTbl_Shared(),
                                                        W32Str_getData(pStr)
                                            );
                                Token_setStrToken(
                                                lex_getToken((LEX_DATA *)this),
                                                token
                                );
                                obj_Release(pStr);
                                fSaveStr = false;
                            }
                        }
                        fMore = false;
                        break;
                    }
                    if( '{' == cls) {
                        newCls = PPLEX_SPCL_LCURL;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 2);
                        if (this->kwdSel & PPLEX_LANG_LL1) {
                            W32STR_DATA     *pStr;
                            pStr = pplex2_SaveText(this,'%','}');
                            if (pStr) {
                                uint32_t        token;
                                newCls = PPLEX_CONSTANT_TEXT;
                                token =     szTbl_StringW32ToToken(
                                                                   szTbl_Shared(),
                                                                   W32Str_getData(pStr)
                                            );
                                Token_setStrToken(
                                                  lex_getToken((LEX_DATA *)this),
                                                  token
                                );
                                obj_Release(pStr);
                                fSaveStr = false;
                            }
                        }
                        fMore = false;
                        break;
                    }
                    if( '(' == cls) {
                        newCls = PPLEX_SPCL_LPAREN;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 2);
                        if (this->kwdSel & PPLEX_LANG_LL1) {
                            W32STR_DATA     *pStr;
                            uint32_t        token;
                            pStr = pplex2_SaveText(this,'%',')');
                            if (pStr) {
                                newCls = PPLEX_CONSTANT_TEXTC;
                                token =     szTbl_StringW32ToToken(
                                                                   szTbl_Shared(),
                                                                   W32Str_getData(pStr)
                                                                   );
                                Token_setStrToken(
                                                  lex_getToken((LEX_DATA *)this),
                                                  token
                                                  );
                                obj_Release(pStr);
                                fSaveStr = false;
                            }
                        }
                        fMore = false;
                        break;
                    }
                    if( ']' == cls) {
                        newCls = PPLEX_SPCL_RBRACK;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 2);
                        fMore = false;
                        break;
                    }
                    if( '}' == cls) {
                        newCls = PPLEX_SPCL_RCURL;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 2);
                        fMore = false;
                        break;
                    }
                    if( ')' == cls) {
                        newCls = PPLEX_SPCL_RPAREN;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 2);
                        fMore = false;
                        break;
                    }
                    if (this->kwdSel & PPLEX_LANG_LL1) {
                        chr = Token_getChrW32(pInput);
                        if( ('g' == chr) || ('G' == chr) ) {
                            newCls = PPLEX_KWD_GOAL;
                            lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                            ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 2);
                            // Eat up rest of symbol. We only need %g or %G.
                            for (;;) {
                                pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 1);
                                cls = Token_getClass(pInput);
                                if( cls == ASCII_LEXICAL_WHITESPACE ) {
                                    break;
                                }
                                lex_InputAdvance((LEX_DATA *)this, 1);
                            }
                            fMore = false;
                            break;
                        }
                        if( ('t' == chr) || ('T' == chr) ) {
                            newCls = PPLEX_KWD_TERM;
                            lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                            ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 2);
                            // Eat up rest of symbol. We only need %g or %G.
                            for (;;) {
                                pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj,1);
                                cls = Token_getClass(pInput);
                                if( cls == ASCII_LEXICAL_WHITESPACE ) {
                                    break;
                                }
                                lex_InputAdvance((LEX_DATA *)this, 1);
                            }
                            fMore = false;
                            break;
                        }
                        chr = Token_getChrW32(pInput);
                    }
                    newCls = PPLEX_OP_MOD;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '&':           /*** '&' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '&' == cls) {
                        newCls = PPLEX_OP_LOG_AND;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '=' == cls) {
                        newCls = PPLEX_OP_ASSIGN_AND;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_OP_AND;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '\'':           /*** '\'' ***/
                    ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 1);
                    if (lex_getMultiCharConstant((LEX_DATA *)this)) {
                        while(lex_ParseChrCon((LEX_DATA *)this,'\''))
                            ;
                    }
                    else {
                        lex_ParseChrCon((LEX_DATA *)this, '\'');
                    }
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 1);
                    cls = Token_getClass(pInput);
                    if (cls == '\'') {
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 1);
                        if (lex_getMultiCharConstant((LEX_DATA *)this)) {
                            newCls = PPLEX_CONSTANT_STRING;
                        }
                        else {
                            newCls = PPLEX_CONSTANT_CHAR;
                        }
                        fMore = false;
                        break;
                    }
                    else {
                        SrcErrors_AddFatalFromTokenA(
                                                     OBJ_NIL,
                                                     pInput,
                                                     "Malformed Character Constant"
                                                     );
                    }
                    break;
                    
                case '(':           /*** '(' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj,2);
                    cls = Token_getClass(pInput);
                    if( ':' == cls) {
                        newCls = PPLEX_SPCL_PAREN_LEFT;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_SEP_LPAREN;
                    ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 1);
                    fMore = false;
                    break;

                case ')':           /*** ')' ***/
                    newCls = PPLEX_SEP_RPAREN;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;

                case '*':           /*** '*' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj,2);
                    cls = Token_getClass(pInput);
                    if( '=' == cls) {
                        newCls = PPLEX_OP_ASSIGN_MUL;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_OP_MUL;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '+':           /*** '+' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '+' == cls) {
                        newCls = PPLEX_OP_INC;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '=' == cls) {
                        newCls = PPLEX_OP_ASSIGN_ADD;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_OP_ADD;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case ',':           /*** ',' ***/
                    newCls = PPLEX_SEP_COMMA;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '-':           /*** '-' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '-' == cls) {
                        newCls = PPLEX_OP_DEC;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '=' == cls) {
                        newCls = PPLEX_OP_ASSIGN_SUB;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '>' == cls) {
                        newCls = PPLEX_SEP_RARROW;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_OP_SUB;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '.':           /*** '.' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '.' == cls) {
                        pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 3);
                        cls = Token_getClass(pInput);
                        if( '.' == cls) {
                            newCls = PPLEX_OP_ELIPSIS;
                            lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                            lex_InputAdvance((LEX_DATA *)this, 3);
                            fMore = false;
                            break;
                        }
                        newCls = PPLEX_OP_RANGE;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '>' == cls) {
                        newCls = PPLEX_SEP_DOT_GT;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_SEP_DOT;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '/':           /*** '/' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '/' == cls) {
                        // Single Line Comment - PPLEX_COMMENT_SINGLE
                        newCls = PPLEX_COMMENT_SINGLE;
                        if (this->fComments) {
                            lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        }
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        for (;;) {
                            pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 1);
                            cls = Token_getClass(pInput);
                            lex_InputAdvance((LEX_DATA *)this, 1);
                            if (cls == ASCII_LEXICAL_EOL) {
                                break;
                            }
                            if (this->fComments) {
                                lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                            }
                        }
//TODO: Finish implementing fComments and write Test for it.
                        if (this->fComments) {
                            fMore = false;
                        }
                        break;
                    }
                    if( '*' == cls) {
                        uint32_t        depth = 1;
                        bool            fMore2 = true;
                        // Multi-line comment - PPLEX_COMMENT_MULTI
                        newCls = PPLEX_COMMENT_SINGLE;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        while (fMore2) {
                            pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 1);
                            cls = Token_getClass(pInput);
                            if (cls == '*') {
                                pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                                cls = Token_getClass(pInput);
                                if (cls == '/') {
                                    lex_InputAdvance((LEX_DATA *)this, 2);
                                    --depth;
                                    if (0 == depth) {
                                        fMore2 = false;
                                    }
                                    continue;
                                }
                            }
                            if (cls == '/') {
                                pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                                cls = Token_getClass(pInput);
                                if (cls == '*') {
                                    lex_InputAdvance((LEX_DATA *)this, 2);
                                    ++depth;
                                    continue;
                                }
                            }
                            lex_InputAdvance((LEX_DATA *)this, 1);
                        }
                        break;
                    }
                    newCls = PPLEX_OP_DIV;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case ':':           /*** ':' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( ':' == cls) {
                        newCls = PPLEX_SPCL_DBLCOLON;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( ')' == cls) {
                        newCls = PPLEX_SPCL_PAREN_RIGHT;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '>' == cls) {
                        newCls = PPLEX_SPCL_COLON_RIGHT;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_SPCL_COLON;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case ';':           /*** ';' ***/
                    newCls = PPLEX_SEP_SEMICOLON;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '<':           /*** '<' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '<' == cls) {
                        pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 3);
                        cls = Token_getClass(pInput);
                        if( '=' == cls) {
                            newCls = PPLEX_OP_ASSIGN_LEFT;
                            lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                            lex_InputAdvance((LEX_DATA *)this, 3);
                            fMore = false;
                            break;
                        }
                        newCls = PPLEX_OP_LEFT;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '-' == cls) {
                        newCls = PPLEX_SEP_LARROW;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '=' == cls) {
                        newCls = PPLEX_OP_LE;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '.' == cls) {
                        if (this->kwdSel & PPLEX_LANG_LL1) {
                            W32STR_DATA     *pStr;
                            pStr = pplex2_SaveText(this,'.','>');
                            if (pStr) {
                                newCls = PPLEX_CONSTANT_TEXTD;
                                Token_setStrW32(
                                    lex_getToken((LEX_DATA *)this),
                                    W32Str_getData(pStr)
                                );
                                obj_Release(pStr);
                                fSaveStr = false;
                            }
                        }
                        newCls = PPLEX_SEP_LT_DOT;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( ':' == cls) {
                        newCls = PPLEX_SPCL_COLON_LEFT;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_OP_LT;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '=':           /*** '=' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '>' == cls) {
                        newCls = PPLEX_SPCL_RARROW;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '=' == cls) {
                        newCls = PPLEX_OP_EQ;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_OP_ASSIGN;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '>':           /*** '>' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '>' == cls) {
                        pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 3);
                        cls = Token_getClass(pInput);
                        if( '=' == cls) {
                            newCls = PPLEX_OP_ASSIGN_RIGHT;
                            lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                            lex_InputAdvance((LEX_DATA *)this, 3);
                            fMore = false;
                            break;
                        }
                        newCls = PPLEX_OP_RIGHT;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '=' == cls) {
                        newCls = PPLEX_OP_GE;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_OP_GT;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '?':           /*** '?' ***/
                    newCls = PPLEX_OP_QUESTION;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '@':           /*** '@' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if ((ASCII_LEXICAL_ALPHA_LOWER == cls)
                        || (ASCII_LEXICAL_ALPHA_UPPER == cls)) {
                        lex_ParseName((LEX_DATA *)this);
                        newCls = PPLEX_IDENTIFIER;
                        fMore = false;
                        break;
                    }
                    if( '(' == cls) {
                        newCls = PPLEX_SPCL_AT_LPAREN;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '[' == cls) {
                        newCls = PPLEX_SPCL_AT_LBRACK;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '{' == cls) {
                        newCls = PPLEX_SPCL_AT_LCURL;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_SEP_AT;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '[':           /*** '[' ***/
                    newCls = PPLEX_SEP_LBRACKET;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                    /*
                     '\\',								// 5C - '\'
                     */
                    
                case ']':           /*** ']' ***/
                    newCls = PPLEX_SEP_RBRACKET;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '^':           /*** '^' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '=' == cls) {
                        newCls = PPLEX_OP_ASSIGN_XOR;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_OP_XOR;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '_':           /*** '_' ***/
                    lex_ParseName((LEX_DATA *)this);
                    newCls = PPLEX_IDENTIFIER;
                    fMore = false;
                    break;
                    
                    /*
                     '`',								// 60 - '`'
                     */
                    
                case '{':           /*** '{' ***/
                    newCls = PPLEX_SEP_LBRACE;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '|':           /*** '|' ***/
                    pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 2);
                    cls = Token_getClass(pInput);
                    if( '=' == cls) {
                        newCls = PPLEX_OP_ASSIGN_OR;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    if( '|' == cls) {
                        newCls = PPLEX_OP_LOG_OR;
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        fMore = false;
                        break;
                    }
                    newCls = PPLEX_OP_OR;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '}':           /*** '}' ***/
                    newCls = PPLEX_SEP_RBRACE;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                case '~':           /*** '~' ***/
                    newCls = PPLEX_OP_NEG;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                    
                default:
                    DEBUG_BREAK();
                    break;
            }

        }
        
        // Return to caller.
        eRc = lex_ParseTokenFinalize((LEX_DATA *)this, newCls, fSaveStr);
        BREAK_FALSE(ERESULT_IS_SUCCESSFUL(eRc));
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                P a r s e  W h i t e  S p a c e
    //---------------------------------------------------------------
    
    bool            pplex2_ParseWhiteSpace(
        PPLEX2_DATA      *this
    )
    {
        int32_t         cls;
        TOKEN_DATA      *pInput;
        int32_t         chr;
        
#ifdef NDEBUG
#else
        if( !pplex2_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        for (;;) {
            pInput = ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 1);
            cls = Token_getClass(pInput);
            chr = Token_getChrW32(pInput);
            if ( chr == '\n' ) {
                break;
            }
            if ( cls == ASCII_LEXICAL_WHITESPACE ) {
                lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
            }
            else
                break;
        }
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          pplex2_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PPLEX2_DATA     *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !pplex2_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(PPLEX2_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
#ifdef XYZZY
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return hex_Disable;
                        }
                        break;
                        
                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return hex_Enable;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return hex_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return hex_ToJSON;
                        }
                        break;
#endif
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            pplex2_Validate(
        PPLEX2_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_PPLEX2) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(PPLEX2_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


