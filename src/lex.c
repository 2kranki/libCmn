// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   lex.c
 *	Generated 09/07/2015 10:54:22
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
#include    "lex_internal.h"
#include    <szTbl.h>
#include    <trace.h>
#include    <WStr.h>
#include    <stdarg.h>
#include    <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    bool            lex_DefaultParser(
        OBJ_ID          pObj,
        TOKEN_DATA      *pTokenOut      // Output Token
    )
    {
        LEX_DATA        *this = pObj;
        TOKEN_DATA      *pToken;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);
        token_Assign(pToken, pTokenOut);
        this->pSrcChrAdvance(this->pSrcObj,1);
        
        return true;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LEX_DATA *     lex_Alloc(
    )
    {
        LEX_DATA       *this;
        uint32_t        cbSize = sizeof(LEX_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LEX_DATA *     lex_New(
        uint16_t        k
    )
    {
        LEX_DATA       *this;
        
        this = lex_Alloc( );
        if (this) {
            this = lex_Init(this, k);
        }
        return this;
    }



    const
    int32_t *       lex_WhiteSpaceW(
    )
    {
        return WStr_WhiteSpaceW();
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT_DATA *  lex_getErrors(
        LEX_DATA        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pErrors;
    }
    
    
    bool            lex_setErrors(
        LEX_DATA        *this,
        ERESULT_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pErrors) {
            obj_Release(this->pErrors);
        }
        this->pErrors = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         lex_getLastError(
        LEX_DATA        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            lex_setLastError(
        LEX_DATA        *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    bool            lex_setParserFunction(
        LEX_DATA        *this,
        bool            (*pParser)(OBJ_ID, TOKEN_DATA *),
        OBJ_ID          pParseObj
    )
    {
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pParser = pParser;
        this->pParseObj = pParseObj;
        
        return true;
    }
    
    
    
    bool            lex_setSourceFunction(
        LEX_DATA        *this,
        TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID,uint16_t),
        TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID,uint16_t),
        OBJ_ID          pSrcObj
    )
    {
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pSrcChrAdvance = pSrcChrAdvance;
        this->pSrcChrLookAhead = pSrcChrLookAhead;
        this->pSrcObj = pSrcObj;
        
        return true;
    }
    
    
    
    WSTR_DATA *     lex_getString(
        LEX_DATA        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pStr;
    }
    
    
    TOKEN_DATA *    lex_getToken(
        LEX_DATA        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return &this->token;
    }

    
    
    TOKENLIST_DATA * lex_getTokens(
        LEX_DATA        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pFIFO;
    }
    
    
    bool            lex_setTokens(
        LEX_DATA        *this,
        TOKENLIST_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pFIFO) {
            obj_Release(this->pFIFO);
        }
        this->pFIFO = pValue;
        
        return true;
    }
    
    
    


    
    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            lex_Dealloc(
        OBJ_ID          objId
    )
    {
        LEX_DATA        *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        lex_setTokens(this, OBJ_NIL);
        
        if (this->pStr) {
            obj_Release(this->pStr);
            this->pStr = OBJ_NIL;
        }
        
        if (this->pOutputs) {
            uint16_t        ui16;
            for (ui16=0; ui16<this->sizeOutputs; ++ui16) {
                if (obj_getType(&this->pOutputs[ui16]) == OBJ_IDENT_TOKEN) {
                    token_ReleaseDataIfObj(&this->pOutputs[ui16]);
                }
            }
            mem_Free(this->pOutputs);
            this->pOutputs = NULL;
            this->sizeOutputs = 0;
            this->curOutputs = 0;
        }
        
        token_ReleaseDataIfObj(&this->token);

        obj_setVtbl(this, (OBJ_IUNKNOWN *)this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          E r r o r
    //---------------------------------------------------------------
    
    void            lex_Error(
        LEX_DATA        *this,
        const
        char            *pFileName,
        uint32_t		linnum,
        uint16_t		colnum,
        const
        char			*fmt,
        ...
    )
    {
        va_list 		argsp;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        va_start( argsp, fmt );
        eResult_ErrorArg(this->pErrors, fmt, argsp);
        va_end( argsp );
        
        // Return to caller.
    }
    
    
    void            lex_ErrorFatal(
        LEX_DATA        *this,
        const
        char			*fmt,
        ...
    )
    {
        va_list 		argsp;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        va_start( argsp, fmt );
        eResult_ErrorFatalArg(this->pErrors, fmt, argsp);
        va_end( argsp );

        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    LEX_DATA *      lex_Init(
        LEX_DATA        *this,
        uint16_t        k
    )
    {
        TOKEN_DATA      *pToken;
        uint32_t        cbSize = sizeof(LEX_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        cbSize = obj_getSize(this);         // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = obj_Init(this, cbSize, OBJ_IDENT_LEX );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_HEX);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&lex_Vtbl);
        //obj_setFlags(this, OBJ_FLAG_TRACE);       // For Debugging

        pToken = token_Init(&this->token);
        if (OBJ_NIL == pToken) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->sizeOutputs = k;
        this->pOutputs = mem_Calloc(k, sizeof(TOKEN_DATA));
        if (OBJ_NIL == this->pOutputs) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pStr = WStr_New();
        this->pErrors = eResult_Shared();
        
        lex_setParserFunction(this, lex_DefaultParser, this);
        
    #ifdef NDEBUG
    #else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
        BREAK_NOT_BOUNDARY4(sizeof(LEX_DATA));
    #endif

        return this;
    }

     

    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_InputAdvance(
        LEX_DATA        *this,
        uint16_t        num
    )
    {
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pToken = this->pSrcChrAdvance(this->pSrcObj, num);
        
        // Return to caller.
        return pToken;
    }
    
    
    
    //--------------------------------------------------------------
    //              I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_InputLookAhead(
        LEX_DATA        *this,
        uint16_t        num
    )
    {
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pToken = this->pSrcChrLookAhead(this->pSrcObj, num);
        
        // Return to caller.
        return pToken;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  C h r
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_MatchInputChr(
        LEX_DATA		*this,
        int32_t         chr
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);
        
        if(chr == token_getChrW(pToken) ) {
            scp = token_Copy(pToken);
            (void)this->pSrcChrAdvance(this->pSrcObj,1);
            return scp;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  C l a s s
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_MatchInputCls(
        LEX_DATA		*this,
        int32_t         cls
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);
        
        if(cls == token_getClass(pToken) ) {
            scp = token_Copy(pToken);
            (void)this->pSrcChrAdvance(this->pSrcObj,1);
            return scp;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //               M a t c h  I n p u t  R a n g e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_MatchInputRange(
        LEX_DATA		*this,
        int32_t         chrBeg,
        int32_t         chrEnd
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        int32_t         chr;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);
        
        chr = token_getChrW(pToken);
        if((chr >= chrBeg) && (chr <= chrEnd) ) {
            scp = token_Copy(pToken);
            (void)this->pSrcChrAdvance(this->pSrcObj,1);
            return scp;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  S e t
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_MatchInputSet(
        LEX_DATA		*this,
        int32_t         *pSet
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        int32_t         chr;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (NULL == pSet) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);
        
        chr = token_getChrW(pToken);
        while (*pSet) {
            if(chr == *pSet) {
                scp = token_Copy(pToken);
                (void)this->pSrcChrAdvance(this->pSrcObj,1);
                return scp;
            }
            ++pSet;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P a r s e  C h a r s
    //---------------------------------------------------------------
    
    // The first character of the name has already been parsed, but
    // not advanced. So, we just keep accumulating the proper letters
    // until there are no more that are acceptable.
    
    bool            lex_ParseChrCon(
        LEX_DATA        *this,
        int32_t         ending
    )
    {
        int32_t         cls;
        int32_t         chr;
        TOKEN_DATA      *pInput;
        int             i;
        
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pInput = this->pSrcChrLookAhead(this->pSrcObj, 1);
        cls = token_getClass(pInput);
        chr = token_getChrW(pInput);
        if ((chr == '\n') || (chr == '\r')) {
            return false;
        }
        if (chr == ending) {
            return false;
        }
        if ( cls == '\\') {
            lex_ParseTokenAppendString(this, pInput);
            pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
            cls = token_getClass(pInput);
            switch (cls) {
                    
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    lex_ParseTokenAppendString(this, pInput);
                    this->pSrcChrAdvance(this->pSrcObj, 1);
                    if (lex_ParseDigitOct(this)) {
                        if (lex_ParseDigitOct(this)) {
                        }
                    }
                    return true;
                    
                case '?':
                case 'b':
                case 'f':
                case 'n':
                case 'r':
                case 't':
                case 'v':
                case '\\':
                case '\'':
                case '\"':
                    lex_ParseTokenAppendString(this, pInput);
                    this->pSrcChrAdvance(this->pSrcObj, 1);
                    return true;
                    
                case 'u':
                    lex_ParseTokenAppendString(this, pInput);
                    this->pSrcChrAdvance(this->pSrcObj, 1);
                    for (i=0; i<4; ++i) {
                        if (lex_ParseDigitHex(this)) {
                        }
                        else {
                            //FIXME: ErrorFatal Malformed unicode escape seq
                            return false;
                        }
                    }
                    break;
                    
                case 'U':
                    lex_ParseTokenAppendString(this, pInput);
                    this->pSrcChrAdvance(this->pSrcObj, 1);
                    for (i=0; i<8; ++i) {
                        if (lex_ParseDigitHex(this)) {
                        }
                        else {
                            //FIXME: ErrorFatal Malformed unicode escape seq
                            return false;
                        }
                    }
                    break;
                    
                case 'x':
                    lex_ParseTokenAppendString(this, pInput);
                    this->pSrcChrAdvance(this->pSrcObj, 1);
                    for (i=0; i<2; ++i) {
                        if (lex_ParseDigitHex(this)) {
                        }
                        else {
                            //FIXME: ErrorFatal Malformed unicode escape seq
                            return false;
                        }
                    }
                    break;
                    
                default:
                    return false;
                    break;
            }
        }
        else {
            lex_ParseTokenAppendString(this, pInput);
            this->pSrcChrAdvance(this->pSrcObj, 1);
        }
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  D i g i t
    //---------------------------------------------------------------
    
    bool            lex_ParseDigitHex(
        LEX_DATA        *this
    )
    {
        bool            fRc = false;
        int32_t         cls;
        int32_t         chr;
        TOKEN_DATA      *pInput;
        
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pInput = this->pSrcChrLookAhead(this->pSrcObj, 1);
        cls = token_getClass(pInput);
        chr = token_getChrW(pInput);
        
        if(   ((chr >= '0') && (chr <= '9'))
           || ((chr >= 'a') && (chr <= 'f'))
           || ((chr >= 'A') && (chr <= 'F'))
           ) {
            lex_ParseTokenAppendString(this, pInput);
            this->pSrcChrAdvance(this->pSrcObj, 1);
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    bool            lex_ParseDigitsHex(
        LEX_DATA       *this
    )
    {
        bool            rc = false;
        
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        while (lex_ParseDigitHex(this)) {
        }
        
        // Return to caller.
        return rc;
    }
    
    
    
    bool            lex_ParseDigitOct(
        LEX_DATA        *this
    )
    {
        bool            fRc = false;
        int32_t         cls;
        char            chr;
        TOKEN_DATA      *pInput;
        
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pInput = this->pSrcChrLookAhead(this->pSrcObj, 1);
        cls = token_getClass(pInput);
        chr = token_getChrW(pInput);
        
        if( ((chr >= '0') && (chr <= '7')) ) {
            lex_ParseTokenAppendString(this, pInput);
            this->pSrcChrAdvance(this->pSrcObj, 1);
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    bool            lex_ParseDigitsOct(
        LEX_DATA        *this
    )
    {
        bool            rc = false;
        
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        while (lex_ParseDigitOct(this)) {
        }
        
        // Return to caller.
        return rc;
    }
    
    
    
    //--------------------------------------------------------------
    //                      P a r s e  E O F
    //--------------------------------------------------------------
    
    /*  This routine will save the current character on a queue
     *  where it will be retrieved by NextToken().
     */
    TOKEN_DATA *    lex_ParseEOF(
        LEX_DATA        *this
    )
    {
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        obj_setSize(&this->token, sizeof(TOKEN_DATA));
        pToken =    token_InitCharW(
                        &this->token,
                        NULL,
                        0,
                        0,
                        -1,
                        -1
                    );
        
        // Return to caller.
        return pToken;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                      P a r s e  N u m b e r
    //---------------------------------------------------------------
    
    // The first character of the number has already been parsed and
    // appended, but not advanced over. So, we can look at it and
    // make decisions based on it.
    
    uint16_t        lex_ParseNumber(
        LEX_DATA        *this
    )
    {
        int32_t         chr;
        int32_t         cls;
        int32_t         clsNew = 0;
        TOKEN_DATA      *pInput;
        bool            fRc;
        
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return clsNew;
        }
#endif
        pInput = this->pSrcChrLookAhead(this->pSrcObj, 1);
        cls = token_getClass(pInput);
        chr = token_getChrW(pInput);
        
        switch (chr) {
            case '0':
                pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
                chr = token_getChrW(pInput);
                if ((chr == 'x') || (chr == 'X')) {
                    this->pSrcChrAdvance(this->pSrcObj, 1);
                    if( !lex_ParseDigitsHex(this) ) {
                        lex_setLastError(this, ERESULT_HEX_SYNTAX);
                        return false;
                    }
                    clsNew = LEX_CONSTANT_INTEGER;
                }
                else {
                    fRc = lex_ParseDigitsOct(this);
                    clsNew = LEX_CONSTANT_INTEGER;
                }
                break;
                
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                for (;;) {
                    pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
                    chr = token_getChrW(pInput);
                    if ((chr >= '0') && (chr <= '9')) {
                        lex_ParseTokenAppendString(this, pInput);
                    }
                    else
                        break;
                }
                clsNew = LEX_CONSTANT_INTEGER;
                break;
                
            default:
                break;
        }
        fRc = lex_ParseIntegerSuffix(this);
        
        lex_setLastError(this, ERESULT_SUCCESS);
        return clsNew;
    }
    
    
    /*!
     Look for an integer suffix of [lL][lL]?[uU] | [uU][lL][lL]? on the end
     of an integer parse.
     @return:   integer type as defined by TOKEN_MISC
     */
    uint16_t        lex_ParseIntegerSuffix(
        LEX_DATA        *this
    )
    {
        int16_t         chr;
        int16_t         clsNew = TOKEN_MISC_SI;
        TOKEN_DATA      *pInput;
        
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return clsNew;
        }
#endif
        
        pInput = this->pSrcChrLookAhead(this->pSrcObj, 1);
        chr = token_getChrW(pInput);
        switch (chr) {
            case 'l':
                lex_ParseTokenAppendString(this, pInput);
                clsNew = TOKEN_MISC_SL;
                pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
                chr = token_getChrW(pInput);
                if ('l' == chr) {
                    lex_ParseTokenAppendString(this, pInput);
                    clsNew = TOKEN_MISC_SLL;
                    pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
                    chr = token_getChrW(pInput);
                    if (('u' == chr) || ('U' == chr)) {
                        lex_ParseTokenAppendString(this, pInput);
                        clsNew = TOKEN_MISC_ULL;
                        this->pSrcChrAdvance(this->pSrcObj, 1);
                    }
                    return clsNew;
                }
                if (('u' == chr) || ('U' == chr)) {
                    lex_ParseTokenAppendString(this, pInput);
                    clsNew = TOKEN_MISC_UL;
                    this->pSrcChrAdvance(this->pSrcObj, 1);
                }
                return clsNew;
                break;
                
            case 'L':
                lex_ParseTokenAppendString(this, pInput);
                clsNew = TOKEN_MISC_SL;
                pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
                chr = token_getChrW(pInput);
                if ('L' == chr) {
                    lex_ParseTokenAppendString(this, pInput);
                    clsNew = TOKEN_MISC_SLL;
                    pInput = ((LEX_DATA *)this)->pSrcChrAdvance(this->pSrcObj, 1);
                    chr = token_getChrW(pInput);
                    if (('u' == chr) || ('U' == chr)) {
                        lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                        clsNew = TOKEN_MISC_ULL;
                        this->pSrcChrAdvance(this->pSrcObj, 1);
                    }
                    return clsNew;
                }
                if (('u' == chr) || ('U' == chr)) {
                    lex_ParseTokenAppendString(this, pInput);
                    clsNew = TOKEN_MISC_UL;
                    this->pSrcChrAdvance(this->pSrcObj, 1);
                    return clsNew;
                }
                return clsNew;
                break;
                
            case 'u':
                lex_ParseTokenAppendString(this, pInput);
                clsNew = TOKEN_MISC_UI;
                pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
                chr = token_getChrW(pInput);
                if ('l' == chr) {
                    lex_ParseTokenAppendString(this, pInput);
                    clsNew = TOKEN_MISC_UL;
                    pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
                    chr = token_getChrW(pInput);
                    if ('l' == chr) {
                        lex_ParseTokenAppendString(this, pInput);
                        clsNew = TOKEN_MISC_ULL;
                        this->pSrcChrAdvance(this->pSrcObj, 1);
                    }
                    return clsNew;
                }
                if ('L' == chr) {
                    lex_ParseTokenAppendString(this, pInput);
                    clsNew = TOKEN_MISC_UL;
                    pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
                    chr = token_getChrW(pInput);
                    if ('L' == chr) {
                        lex_ParseTokenAppendString(this, pInput);
                        clsNew = TOKEN_MISC_ULL;
                        this->pSrcChrAdvance(this->pSrcObj, 1);
                    }
                    return clsNew;
                }
                return clsNew;
                break;
                
            case 'U':
                lex_ParseTokenAppendString(this, pInput);
                clsNew = TOKEN_MISC_UI;
                pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
                chr = token_getChrW(pInput);
                if ('l' == chr) {
                    lex_ParseTokenAppendString(this, pInput);
                    clsNew = TOKEN_MISC_UL;
                    pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
                    chr = token_getChrW(pInput);
                    if ('l' == chr) {
                        lex_ParseTokenAppendString(this, pInput);
                        clsNew = TOKEN_MISC_ULL;
                        this->pSrcChrAdvance(this->pSrcObj, 1);
                    }
                    return clsNew;
                }
                if ('L' == chr) {
                    lex_ParseTokenAppendString(this, pInput);
                    clsNew = TOKEN_MISC_UL;
                    pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
                    chr = token_getChrW(pInput);
                    if ('L' == chr) {
                        lex_ParseTokenAppendString(this, pInput);
                        clsNew = TOKEN_MISC_ULL;
                        this->pSrcChrAdvance(this->pSrcObj, 1);
                    }
                    return clsNew;
                }
                return clsNew;
                break;
                
            default:
                break;
        }
        
        return clsNew;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P a r s e  N a m e
    //---------------------------------------------------------------
    
    // The first character of the name has already been parsed, but
    // not advanced. So, we just keep accumulating the proper letters
    // until there are no more that are acceptable.
    
    bool            lex_ParseName(
        LEX_DATA        *this
    )
    {
        int32_t         cls;
        TOKEN_DATA      *pInput;
        
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        for (;;) {
            pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
            cls = token_getClass(pInput);
            if (    (cls == ASCII_LEXICAL_ALPHA_LOWER)
                || (cls == ASCII_LEXICAL_ALPHA_UPPER)
                || (cls == ASCII_LEXICAL_NUMBER)
                || (cls == '_')
                || (cls == '$')
                ) {
                lex_ParseTokenAppendString(this, pInput);
            }
            else
                break;
        }
        
        return true;
    }
    
    
    
    //--------------------------------------------------------------
    //            P a r s e  S t r i n g  T r u n c a t e
    //--------------------------------------------------------------
    
    ERESULT         lex_ParseStringTruncate(
        LEX_DATA        *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        WStr_Truncate(this->pStr, 0);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                      P a r s e  T o k e n
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_ParseToken(
        LEX_DATA        *this
    )
    {
        //TOKEN_DATA      *pInput;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        fRc = this->pParser(this->pParseObj, &this->token);
        
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA           *pStr = token_ToDebugString(&this->token, 0);
            TRC_OBJ( this, "lex_ParseToken:  %s \n", AStr_getData(pStr) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        
        // Return to caller.
        return &this->token;
    }
    
    
    
    //---------------------------------------------------------------
    //                P a r s e  W h i t e  S p a c e
    //---------------------------------------------------------------
    
    /* Parse white space until eol.
     */
    bool            lex_ParseWhiteSpace(
        LEX_DATA        *this
    )
    {
        int32_t         cls;
        TOKEN_DATA      *pInput;
        int32_t         chr;
        
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        for (;;) {
            pInput = this->pSrcChrAdvance(this->pSrcObj, 1);
            cls = token_getClass(pInput);
            chr = token_getChrW(pInput);
            if ( chr == '\n' ) {
                break;
            }
            if ( cls == ASCII_LEXICAL_WHITESPACE ) {
                lex_ParseTokenAppendString(this, pInput);
            }
            else
                break;
        }
        
        return true;
    }
    
    
    
    //--------------------------------------------------------------
    //                  T o k e n  A d v a n c e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_TokenAdvance(
        LEX_DATA		*this,
        uint16_t        numChrs
    )
    {
        uint32_t        i;
        uint16_t        idx;
        TOKEN_DATA      *pToken = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        if (this->pFIFO ) {
            idx = tokenList_getSize(this->pFIFO);
            if (idx) {
                while (numChrs && idx) {
                    tokenList_DeleteHead(this->pFIFO);
                    idx = tokenList_getSize(this->pFIFO);
                    --numChrs;
                }
            }
            if (numChrs > 0) {
            }
            else {
                pToken = tokenList_Head(this->pFIFO);
                if (pToken) {
#ifdef NDEBUG
#else
                    if (obj_Trace(this)) {
                        ASTR_DATA           *pStr = token_ToDebugString(pToken, 0);
                        TRC_OBJ( this, "lex_InputAdvance:  %s \n", AStr_getData(pStr) );
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
#endif
                    return pToken;
                }
            }
        }
        
        if (!obj_IsFlag(this, LEX_INIT_DONE)) {
            for (i=0; i<this->sizeOutputs; ++i) {
                pToken = &this->pOutputs[i];
                token_InitCharW(pToken, "", 1, 1, 0, 0);
            }
            for (i=0; i<this->sizeOutputs; ++i) {
                lex_TokenNext(this);
            }
            obj_FlagOn(this, LEX_INIT_DONE);
        }
        
        // Shift inputs.
        for (i=0; i<numChrs; ++i) {
            lex_TokenNext(this);
        }
        
        // Return to caller.
        pToken = &this->pOutputs[this->curOutputs];
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA           *pStr = token_ToDebugString(pToken, 0);
            TRC_OBJ( this, "lex_InputAdvance:  %s \n", AStr_getData(pStr) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        return pToken;
    }
    
    
    
    //--------------------------------------------------------------
    //               T o k e n  L o o k  A h e a d
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_TokenLookAhead(
        LEX_DATA        *this,
        uint16_t        num
    )
    {
        uint16_t        idx;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pFIFO ) {
            idx = tokenList_getSize(this->pFIFO);
            if (num > idx) {
                num -= idx;
            }
            else {
                pToken = tokenList_Index(this->pFIFO,num);
#ifdef NDEBUG
#else
                if (obj_Trace(this)) {
                    ASTR_DATA           *pStr = token_ToDebugString(pToken, 0);
                    TRC_OBJ( this, "lex_InputLookAhead:  %s \n", AStr_getData(pStr) );
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
#endif
                return pToken;
            }
        }
        
        if (!obj_IsFlag(this, LEX_INIT_DONE)) {
#ifdef NDEBUG
#else
            for (idx=0; idx<this->sizeOutputs; ++idx) {
                pToken = &this->pOutputs[idx];
                token_InitCharW(pToken, "", 1, 1, LEX_CLASS_EOF, 0);
            }
#endif
            for (idx=0; idx<this->sizeOutputs; ++idx) {
                lex_TokenNext(this);
            }
            obj_FlagOn(this, LEX_INIT_DONE);
        }
        
        idx = (this->curOutputs + num - 1) % this->sizeOutputs;
        pToken = &this->pOutputs[idx];
        
        // Return to caller.
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA           *pStr = token_ToDebugString(pToken, 0);
            TRC_OBJ( this, "lex_InputLookAhead:  %s \n", AStr_getData(pStr) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        return pToken;
    }
    
    
    
    //--------------------------------------------------------------
    //              P a r s e  T o k e n  F i n a l i z e
    //--------------------------------------------------------------
    
    /*!
     Finalize the string being built by the parser creating the token
     to be returned.
     @param:    this    LEX object pointer
     @param     newClass If non-zero, use this class for the token
     being built.
     @param     fSaveStr
     If true, the string being built by the parse is saved
     into the token being built replacing the original string.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         lex_ParseTokenFinalize(
        LEX_DATA        *this,
        int32_t         newClass,
        bool            fSaveStr
    )
    {
        ERESULT         eRc;
        uint32_t        strToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        token_setClass(&this->token, newClass);
        if (fSaveStr && this->pStr) {
            if (this->fUseStringTable) {
                eRc =   szTbl_StringWToToken(
                                             szTbl_Shared(),
                                             WStr_getData(this->pStr),
                                             &strToken
                                             );
                BREAK_TRUE(ERESULT_HAS_FAILED(eRc));
            }
            else {
                WSTR_DATA       *pStr;
                pStr = WStr_Copy(this->pStr);
                token_setStringW(&this->token, pStr);
                WStr_Truncate(this->pStr, 0);
                obj_Release(pStr);
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    
    //--------------------------------------------------------------
    //         P a r s e  T o k e n  A p p e n d  S t r i n g
    //--------------------------------------------------------------
    
    ERESULT         lex_ParseTokenAppendString(
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
    )
    {
        uint16_t        type;
        int32_t         chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
        if (OBJ_NIL == pToken) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (this->pStr == OBJ_NIL) {
            this->pStr = WStr_New();
        }
        
        type = token_getType(pToken);
        switch (type) {
            case TOKEN_TYPE_WCHAR:
                chr = token_getChrW(pToken);
                if (chr == '\n') {
                    WStr_AppendA(this->pStr, "\\n");
                }
                if (chr == '\r') {
                    WStr_AppendA(this->pStr, "\\r");
                }
                if (chr == '\t') {
                    WStr_AppendA(this->pStr, "\\t");
                }
                else {
                    WStr_AppendW(this->pStr, 1, &chr);
                }
                break;
                
            case TOKEN_TYPE_INTEGER:
                WStr_Append(this->pStr,token_getStringW(pToken));
                break;
                
            case TOKEN_TYPE_WSTRING:
                WStr_Append(this->pStr,token_getStringW(pToken));
                break;
                
            default:
                DEBUG_BREAK();
                break;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                      T o k e n  N e x t
    //--------------------------------------------------------------
    
    // This method is called when we need to parse a new phrase and
    // save it into the current token.
    
    ERESULT         lex_TokenNext(
        LEX_DATA		*this
    )
    {
        TOKEN_DATA      *pToken;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Release current token data;
        token_ReleaseDataIfObj(&this->pOutputs[this->curOutputs]);
        
        fRc = this->pParser(this->pParseObj, &this->token);
        if (!fRc) {
            return ERESULT_GENERAL_FAILURE;
        }
        // The lexical parser should have called the parse???
        // methods to build the token and it should now reside
        // in this->token.
        
        // Add the next char to the queue.
        pToken = &this->pOutputs[this->curOutputs];
        token_Assign(&this->token, pToken);
        
        this->curOutputs = (this->curOutputs + 1) % this->sizeOutputs;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //--------------------------------------------------------------
    //                      T o k e n  P u s h
    //--------------------------------------------------------------
    
    /*  This routine will save the current character on a queue
     *  where it will be retrieved by NextToken().
     */
    ERESULT         lex_TokenPush(
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (this->pFIFO == OBJ_NIL) {
            this->pFIFO = tokenList_New( );
            if (OBJ_NIL == this->pFIFO) {
                DEBUG_BREAK();
                return ERESULT_INSUFFICIENT_MEMORY;
            }
            
        }
        
        tokenList_Add2Tail(this->pFIFO, pToken);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
        
    //--------------------------------------------------------------
    //                P a r s e  T o k e n  S e t u p
    //--------------------------------------------------------------
    
    /*!
     Setup the given token as the beginning of the next parse output
     token (ie First element of the next parse) and initialize the ac-
     cumulation string to the contents of the given token.
     @param:    this    LEX object pointer
     @param     pInput pointer to a token that is used to define the
                next parsed output token. The string/char within the
                token is used as the first char/string of the new
                parsed token.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         lex_ParseTokenSetup(
        LEX_DATA        *this,
        TOKEN_DATA      *pInput
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        WStr_Truncate(this->pStr, 0);
        if (OBJ_NIL == pInput) {
            DEBUG_BREAK();
            lex_ParseEOF(this);
            return ERESULT_EOF_ERROR;
        }
        eRc = lex_ParseTokenAppendString(this, pInput);
        if(ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        eRc = token_Assign(pInput, &this->token);
        if(ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     lex_ToDebugString(
        LEX_DATA        *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA      *pWrkStr;
        
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
                     "{%p(lex) ",
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
    bool            lex_Validate(
        LEX_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_LEX) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(LEX_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


