// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   lex_internal.h
 *	Generated 09/07/2015 10:54:22
 *
 * Notes:
 *  --	N/A
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



#include    <lex.h>
#include    <ascii.h>
#include    <objArray.h>
#include    <szTbl.h>
#include    <token_internal.h>
#include    <tokenList.h>


#ifndef LEX_INTERNAL_H
#define	LEX_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif

    

    
#pragma pack(push, 1)
struct lex_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance
#define LEX_INIT_DONE   5
#define LEX_CHECKPOINT  6
    
    ERESULT         eRc;
    ERESULT_DATA    *pErrors;

    // Input Data/Routines
    TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID, uint16_t);
    TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID, uint16_t);
    OBJ_ID          pSrcObj;
    
    // Output Data/Routines
    uint16_t        sizeOutputs;        // Circular Token Queue
    uint16_t        curOutputs;
    TOKEN_DATA      *pOutputs;
    TOKENLIST_DATA  *pFIFO;             // Token FIFO Queue
    TOKENLIST_DATA  *pCheckPoint;       // Token Checkpoint Queue
    
    // Parse Routines
    //      pParse parses the pInputs into the token passed or ignores the
    //      passed token and uses lex_ParseSetup() and lex_ParseFinish() to
    //      accumulate the token.
    bool            (*pParser)(OBJ_ID, TOKEN_DATA *); // Lexical Parser
    OBJ_ID          pParseObj;
    TOKEN_DATA      token;              // Next Output Token (output of pParser)
    WSTR_DATA       *pStr;              // String from accumulated tokens
    uint8_t         fUseStringTable;
    uint8_t         rsvd[3];
    
};
#pragma pack(pop)

    extern
    const
    LEX_VTBL            lex_Vtbl;
    extern
    const
    struct lex_class_data_s
                        lex_ClassObj;



    // Internal Functions
    bool            lex_setLastError(
        LEX_DATA        *this,
        ERESULT         value
    );
    
    
    void            lex_Dealloc(
        OBJ_ID          objId
    );


    ERESULT         lex_TokenNext(
        LEX_DATA		*this
    );
    
    
    /*** @protected
     ***/
    /*!
     Check for a match with the given character and if it does
     advance the input tokens before returning.
     @return:   If successful, a token which must be released
                with obj_Release(), otherwise OBJ_NIL.
     */
    TOKEN_DATA *    lex_MatchInputChr(
        LEX_DATA		*this,
        int32_t         chr
    );
    
    
    /*** @protected
     ***/
    /*!
     Check for a match with the given token class and if it does
     advance the input tokens before returning.
     @return:   If successful, a token which must be released
                with obj_Release(), otherwise OBJ_NIL.
     */
    TOKEN_DATA *    lex_MatchInputCls(
        LEX_DATA		*this,
        int32_t         cls
    );
    
    
    /*** @protected
     ***/
    /*!
     Check for a match with the character range (ie [chrBeg..chrEnd]
     and if it does advance the input tokens before returning.
     chrBeg must be <= chrEnd.
     @return:   If successful, a token which must be released
                with obj_Release(), otherwise OBJ_NIL.
     */
    TOKEN_DATA *    lex_MatchInputRange(
        LEX_DATA		*this,
        int32_t         chrBeg,
        int32_t         chrEnd
    );
    
    
    /*** @protected ***/
    /*!
     Check for a match with the character set (ie nul-terminated list
     of characters) and if it does advance the input tokens before
     returning.
     @return:   If successful, a token which must be released
     with obj_Release(), otherwise OBJ_NIL.
     */
    TOKEN_DATA *    lex_MatchInputSet(
        LEX_DATA		*this,
        int32_t         *pSet
    );
    
    
    /*** @protected ***/
    /*!
     Parse a character constant character not allowing \n or \r.
     */
    bool            lex_ParseChrCon(
        LEX_DATA        *this,
        int32_t         ending
    );
    
    
    /*** @protected ***/
    /*!
     Parse a character constant character allowing \n or \r.
     */
    bool            lex_ParseChrConWS(
        LEX_DATA        *this,
        int32_t         ending
    );
    
    
    bool            lex_ParseDigitHex(
        LEX_DATA        *this
    );
    
    bool            lex_ParseDigitsHex(
        LEX_DATA       *this
    );
    
    
    bool            lex_ParseDigitOct(
        LEX_DATA        *this
    );
    
    bool            lex_ParseDigitsOct(
        LEX_DATA        *this
    );
    
    
    TOKEN_DATA *    lex_ParseEOF(
        LEX_DATA        *cbp
    );
    
    
    uint16_t        lex_ParseIntegerSuffix(
        LEX_DATA        *this
    );
    
    
    bool            lex_ParseName(
        LEX_DATA        *this
    );
    
    
    /*** @protected ***/
    /*!
     Parse a number of varying formats. The first character of the number
     has already been parsed and appended, but not advanced over. So, we
     can look at it and make decisions based on it.
     @return:   If successful, LEX_CONSTANT_* class, otherwise 0. Also,
                 the token string is accumulated.
     */
    uint16_t        lex_ParseNumber(
        LEX_DATA        *this
    );
    
    
    /*** @protected ***/
    /*!
     Append the token data to the parse string and ignore the other
     token properties.
     @param:    this    LEX object pointer
     @param     pToken  pointer to the token of this phrase which
                         will be appended to the string
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         lex_ParseTokenAppendString(
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
    );
    
    
    /*** @protected ***/
    /*!
     Finalize the string being built by the parser creating the token
     to be returned.
     @param:    this    LEX object pointer
     @param     newClass If non-zero, use this class for the token
                         being built.
     @param     fSaveStr If true, the string being built by the parse is saved
                         into the token being built replacing the original string.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         lex_ParseTokenFinalize(
        LEX_DATA        *this,
        int32_t         newClass,
        bool            fSaveStr
    );
    
    
    /*** @protected ***/
    /*!
     Setup the given token as the beginning of the next parse output
     token (ie First element of the next parse) and initialize the ac-
     cumulation string to the contents of the given token.
     @param:    this    LEX object pointer
     @param     pInput  pointer to a token that is used to define the
                         next parsed output token. The string/char within the
                         token is used as the first char/string of the new
                         parsed token.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         lex_ParseTokenSetup(
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
    );
    
    
    /*** @protected ***/
    /*!
     Truncate the parse string accumulated so far.
     @param:    this    LEX object pointer
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         lex_ParseTokenTruncate(
        LEX_DATA        *this
    );
    
    
    
    
#ifdef NDEBUG
#else
    bool			lex_Validate(
        LEX_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* LEX_INTERNAL_H */

