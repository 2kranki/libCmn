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

    // Input Data/Routines
    TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID,uint16_t);
    TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID,uint16_t);
    OBJ_ID          pSrcObj;
    
    // Output Data/Routines
    uint16_t        sizeOutputs;
    uint16_t        curOutputs;
    TOKEN_DATA      *pOutputs;
    TOKENLIST_DATA  *pFIFO;             // Token FIFO Queue
    
    // Parse Routines
    //      pParse parses the pInputs into the token passed or ignores the
    //      passed token and uses lex_ParseSetup() and lex_ParseFinish() to
    //      accumulate the token.
    bool            (*pParser)(OBJ_ID, TOKEN_DATA *); // Lexical Parser
    OBJ_ID          pParseObj;
    TOKEN_DATA      token;              // Next Output Token (output of pParser)
    WSTR_DATA       *pStr;              // String from accumulated tokens
    bool            fUseStringTable;
    
    // Error Output Routines
    ERESULT_DATA    *pErrors;
    
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
    void            lex_Dealloc(
        OBJ_ID          objId
    );


    ERESULT         lex_InputNextChar(
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
    
    
    /*** @protected
     ***/
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
    
    
    /*** @protected
     ***/
    /*!
     This routine is generally called by the lexical parser
     and it appends the token data to the string only.
     @param     pToken
                the token of this phrase which will be
                appended to the string
     @return:   If successful, ERESULT_SUCCESSFUL_COMPLETION,
                otherwise ERESULT_ERROR_???.
     */
    ERESULT         lex_ParseAddTokenToString(
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
    );
    
    
    TOKEN_DATA *    lex_ParseEOF(
        LEX_DATA        *cbp
    );
    
    
    /*** @protected
     ***/
    /*!
     This routine is generally called by the lexical parser
     and it finalizes the string being built by the parser
     creating the token to be returned.
     @param     newClass
                newClass will be substituted into the token
                being built if it is non-zero.
     @param     fSaveStr
                If true, the string token is saved into the
                token being built and a new string replaces
                the old one.
     @return:   If successful, ERESULT_SUCCESSFUL_COMPLETION,
                otherwise ERESULT_ERROR_???.
     */
    ERESULT         lex_ParseFinish(
        LEX_DATA        *this,
        int32_t         newClass,
        bool            fSaveStr
    );
    
    
    /*** @protected
     ***/
    /*!
     This routine is generally called by the lexical parser
     and it resets the string and token being built by the
     parser. The string is set to the value contained in the
     token and the token given is saved into the token being
     built.
     @param     pToken
                the first token of this phrase which will be
                saved as the token with its character set
                as the first char of the string.
     @return:   If successful, ERESULT_SUCCESSFUL_COMPLETION,
                otherwise ERESULT_ERROR_???.
     */
    ERESULT         lex_ParseSetup(
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
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

