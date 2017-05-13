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
#include    <wstr.h>
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
        if( !lex_Validate( this ) ) {
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
        LEX_DATA       *cbp;
        uint32_t        cbSize = sizeof(LEX_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
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
        LEX_DATA        *cbp
                                     )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lex_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pErrors;
    }
    
    
    bool            lex_setErrors(
        LEX_DATA        *cbp,
        ERESULT_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !lex_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pErrors) {
            obj_Release(cbp->pErrors);
        }
        cbp->pErrors = pValue;
        
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
        if( !lex_Validate( this ) ) {
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
        if( !lex_Validate( this ) ) {
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
        if( !lex_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return &this->token;
    }

    
    
    TOKENLIST_DATA * lex_getTokens(
        LEX_DATA        *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lex_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pFIFO;
    }
    
    
    bool            lex_setTokens(
        LEX_DATA        *cbp,
        TOKENLIST_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !lex_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pFIFO) {
            obj_Release(cbp->pFIFO);
        }
        cbp->pFIFO = pValue;
        
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
        if( !lex_Validate( this ) ) {
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
        LEX_DATA        *cbp,
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
        if( !lex_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        va_start( argsp, fmt );
        eResult_ErrorArg(cbp->pErrors, fmt, argsp);
        va_end( argsp );
        
        // Return to caller.
    }
    
    
    void            lex_ErrorFatal(
        LEX_DATA        *cbp,
        const
        char			*fmt,
        ...
    )
    {
        va_list 		argsp;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        va_start( argsp, fmt );
        eResult_ErrorFatalArg(cbp->pErrors, fmt, argsp);
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
    #endif

        return this;
    }

     

    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_InputAdvance(
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
        if( !lex_Validate( this ) ) {
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
                lex_InputNextChar(this);
            }
            obj_FlagOn(this, LEX_INIT_DONE);
        }
        
        // Shift inputs.
        for (i=0; i<numChrs; ++i) {
            lex_InputNextChar(this);
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
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_InputLookAhead(
        LEX_DATA        *this,
        uint16_t        num
    )
    {
        uint16_t        idx;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate( this ) ) {
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
                lex_InputNextChar(this);
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
    //                  I n p u t  N e x t  C h a r
    //--------------------------------------------------------------
    
    // This method is called when we need to parse a new phrase and
    // save it into the current token.
    
    ERESULT         lex_InputNextChar(
        LEX_DATA		*this
    )
    {
        TOKEN_DATA      *pToken;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate( this ) ) {
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
        return ERESULT_SUCCESSFUL_COMPLETION;
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
        if( !lex_Validate( this ) ) {
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
        if( !lex_Validate( this ) ) {
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
        if( !lex_Validate( this ) ) {
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
        if( !lex_Validate( this ) ) {
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
    
    
    
    //--------------------------------------------------------------
    //           P a r s e  A d d  T o k e n  T o  S t r i n g
    //--------------------------------------------------------------
    
    /*  This routine will save the current character on a queue
     *  where it will be retrieved by NextToken().
     */
    ERESULT         lex_ParseAddTokenToString(
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
    )
    {
        uint16_t        type;
        int32_t         chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate( this ) ) {
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
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                      P a r s e  E O F
    //--------------------------------------------------------------
    
    /*  This routine will save the current character on a queue
     *  where it will be retrieved by NextToken().
     */
    TOKEN_DATA *    lex_ParseEOF(
        LEX_DATA        *cbp
    )
    {
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        obj_setSize(&cbp->token, sizeof(TOKEN_DATA));
        pToken =    token_InitCharW(
                        &cbp->token,
                        NULL,
                        0,
                        0,
                        -1,
                        -1
                    );
        
        // Return to caller.
        return pToken;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                      P a r s e  F i n i s h
    //--------------------------------------------------------------
    
    /* This routine will finalize the token to be returned from
     * the lexical analysis phase.
     */
    ERESULT         lex_ParseFinish(
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
        if( !lex_Validate( this ) ) {
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
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                      P a r s e  S e t u p
    //--------------------------------------------------------------
    
    /*  This routine will save the current token character on a queue
     *  where it will be retrieved by NextToken().
     */
    ERESULT         lex_ParseSetup(
        LEX_DATA        *this,
        TOKEN_DATA      *pInput
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate( this ) ) {
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
        eRc = lex_ParseAddTokenToString(this, pInput);
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
        return ERESULT_SUCCESSFUL_COMPLETION;
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
        if( !lex_Validate( this ) ) {
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
    
    
    
    
    //--------------------------------------------------------------
    //                      P u s h  T o k e n
    //--------------------------------------------------------------
    
    /*  This routine will save the current character on a queue
     *  where it will be retrieved by NextToken().
     */
    ERESULT         lex_PushToken(
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate( this ) ) {
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
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                   S o u r c e  A d v a n c e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_SrcAdvance(
        LEX_DATA        *this,
        uint16_t        num
    )
    {
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pToken = this->pSrcChrAdvance(this->pSrcObj,num);
        
        // Return to caller.
        return pToken;
    }
    
    
    
    //--------------------------------------------------------------
    //               S o u r c e  L o o k  A h e a d
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lex_SrcLookAhead(
        LEX_DATA        *this,
        uint16_t        num
    )
    {
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lex_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pToken = this->pSrcChrLookAhead(this->pSrcObj,num);
        
        // Return to caller.
        return pToken;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     lex_ToDebugString(
        LEX_DATA        *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA      *pWrkStr;
        
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
                     "{%p(lex) ",
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
    bool            lex_Validate(
        LEX_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_LEX) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(LEX_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


