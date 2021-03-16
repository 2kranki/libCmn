// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Lex_internal.h
 *  Generated 05/28/2020 16:45:58
 *
 * Notes:
 *  --  N/A
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




#include        <Lex.h>
#include        <JsonIn.h>
#include        <ObjArray.h>
#include        <szTbl.h>
#include        <Token_internal.h>
#include        <TokenList.h>


#ifndef LEX_INTERNAL_H
#define LEX_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif



    // Use a uint32_t field for the following:
    typedef enum Lex_Statuses_e {
        LEX_STATUS_UNKNOWN=0,
        LEX_STATUS_INIT       =0x80000000,         /* Initialization accomplished */
        LEX_STATUS_CHECKPOINT =0x40000000,         /* Input Checkpoint is active */
    } LEX_STATUSES;



    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Lex_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        flags;
    uint32_t        statuses;
    ERESULT_DATA    *pErrors;

    // Input Data/Routines
    TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID, uint16_t);
    TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID, uint16_t);
    OBJ_ID          pSrcObj;

    // Output Data/Routines
    uint16_t        sizeOutputs;        // Circular Token Queue Size
    uint16_t        curOutputs;
    TOKEN_DATA      *pOutputs;
    TOKENLIST_DATA  *pFIFO;             // Token FIFO Queue
    TOKENLIST_DATA  *pCheckPoint;       // Token Checkpoint Queue

    // Parse Routines
    //      pParse parses the pInputs into the token passed or ignores the
    //      passed token and uses lex_ParseSetup() and lex_ParseFinish() to
    //      accumulate the token.
    ERESULT         (*pParser)(OBJ_ID, TOKEN_DATA *);   // Lexical Parser
    OBJ_ID          pParseObj;
    ERESULT         (*pError)(OBJ_ID, ASTR_DATA *);     // Error Exit
    OBJ_ID          pErrorObj;
    int             (*pParserExit)(
                                   OBJ_ID,          // pParserExitObj
                                   LEX_DATA *,      // LEX Object Ptr
                                   TOKEN_DATA *,    // Current Token Ptr
                                   int32_t *,       // clsNew return Ptr
                                   W32STR_DATA *    // Output Token Accumulaion String
                    );
    OBJ_ID          pParserExitObj;
    TOKEN_DATA      token;              // Next Output Token (output of pParser)
    W32STR_DATA     *pStr;              // String from accumulated tokens

};
#pragma pack(pop)

    extern
    struct Lex_class_data_s  Lex_ClassObj;

    extern
    const
    LEX_VTBL         Lex_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  LEX_SINGLETON
    LEX_DATA *     Lex_getSingleton (
        void
    );

    bool            Lex_setSingleton (
     LEX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Lex_getSuperVtbl (
        LEX_DATA     *this
    );


    ERESULT         Lex_Assign (
        LEX_DATA    *this,
        LEX_DATA    *pOther
    );


    LEX_DATA *       Lex_Copy (
        LEX_DATA     *this
    );


    void            Lex_Dealloc (
        OBJ_ID          objId
    );


#ifdef  LEX_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    LEX_DATA *       Lex_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Lex_ParseJsonFields (
        JSONIN_DATA     *pParser,
        LEX_DATA        *pObject
    );
#endif


    bool            Lex_ParseWhiteSpace(
        LEX_DATA        *this
    );


    void *          Lex_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  LEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Lex_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex_ToJson (
        LEX_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Lex_ToJsonFields (
        LEX_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif


    ERESULT         Lex_TokenNext (
        LEX_DATA        *this
    );


    /*!
     Check for a match with the given character.
     @return    If successful, true; otherwise, false.
     */
    bool            Lex_CheckInputChr(
        LEX_DATA        *this,
        W32CHR_T        chr
    );


    /*!
     Check for a match with the given token class.
     @return    If successful, true; otherwise, false.
    */
    bool            Lex_CheckInputCls (
       LEX_DATA        *this,
       int32_t         cls
    );


    /*!
    Check for a match with the character classes (ie nul-terminated list
    of character classes).
     @return    If successful, true; otherwise, false.
    */
    bool            Lex_CheckInputClasses(
       LEX_DATA        *this,
       int32_t         *pClasses
    );


    /*** @protected
    ***/
    /*!
    Check for a match with the character range (ie [chrBeg..chrEnd]
    and if it does advance the input tokens before returning.
    chrBeg must be <= chrEnd.
     @return    If successful, true; otherwise, false.
    */
    bool            Lex_CheckInputRange (
       LEX_DATA        *this,
       W32CHR_T        chrBeg,
       W32CHR_T        chrEnd
    );


    /*** @protected ***/
    /*!
    Check for a match with the character set (ie nul-terminated list
    of characters) and if it does advance the input tokens before
    returning.
     @return    If successful, true; otherwise, false.
    */
    bool            Lex_CheckInputSet (
       LEX_DATA        *this,
       W32CHR_T        *pSet
    );


    /*** @protected
     ***/
    /*!
     Check for a match with the given character and if it does
     advance the input tokens before returning.
     @return    If successful, a token which must be released
                with obj_Release(), otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Lex_MatchInputChr (
        LEX_DATA        *this,
        W32CHR_T        chr
    );


    /*** @protected
     ***/
    /*!
     Check for a match with the given token class and if it does
     advance the input tokens before returning.
     @return    If successful, a token which must be released
                with obj_Release(), otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Lex_MatchInputCls (
        LEX_DATA        *this,
        int32_t         cls
    );


    /*!
    Check for a match with the character classes (ie nul-terminated list
    of character classes) and if it does advance the input tokens before
    returning.
    @return    If successful, a token which must be released
               with obj_Release(), otherwise OBJ_NIL.
    */
    TOKEN_DATA *    Lex_MatchInputClasses(
        LEX_DATA        *this,
        int32_t         *pClasses
    );


    /*** @protected
     ***/
    /*!
     Check for a match with the character range (ie [chrBeg..chrEnd]
     and if it does advance the input tokens before returning.
     chrBeg must be <= chrEnd.
     @return    If successful, a token which must be released
                with obj_Release(), otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Lex_MatchInputRange (
        LEX_DATA        *this,
        W32CHR_T        chrBeg,
        W32CHR_T        chrEnd
    );


    /*** @protected ***/
    /*!
     Check for a match with the character set (ie nul-terminated list
     of characters) and if it does advance the input tokens before
     returning.
     @return    If successful, a token which must be released
                with obj_Release(), otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Lex_MatchInputSet (
        LEX_DATA        *this,
        W32CHR_T        *pSet
    );


    /*** @protected ***/
    /*!
     Parse a character constant character not allowing \n or \r.
     */
    bool            Lex_ParseChrCon (
        LEX_DATA        *this,
        W32CHR_T        ending
    );


    /*** @protected ***/
    /*!
     Parse a character constant character allowing \n or \r.
     */
    bool            Lex_ParseChrConWS (
        LEX_DATA        *this,
        W32CHR_T        ending
    );


    bool            Lex_ParseDigitHex (
        LEX_DATA        *this
    );

    bool            Lex_ParseDigitsHex (
        LEX_DATA       *this
    );


    bool            Lex_ParseDigitOct (
        LEX_DATA        *this
    );

    bool            Lex_ParseDigitsOct (
        LEX_DATA        *this
    );


    uint16_t        Lex_ParseIntegerSuffix (
        LEX_DATA        *this
    );


    bool            Lex_ParseName (
        LEX_DATA        *this
    );


    /*** @protected ***/
    /*!
     Parse a number of varying formats. The first character of the number
     has already been parsed and appended, but not advanced over. So, we
     can look at it and make decisions based on it.
     @return    If successful, LEX_CONSTANT_* class, otherwise 0. Also,
                 the token string is accumulated.
     */
    uint16_t        Lex_ParseNumber (
        LEX_DATA        *this
    );


    /*** @protected ***/
    /*!
     Append the token data to the parse string and ignore the other
     token properties.
     @param     this    LEX object pointer
     @param     pToken  pointer to the token of this phrase which
                         will be appended to the string
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         Lex_ParseTokenAppendString (
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
    );


    /*** @protected ***/
    /*!
     Finalize the string being built by the parser creating the token
     to be returned.
     @param     this    LEX object pointer
     @param     newClass If non-zero, use this class for the token
                         being built.
     @param     fSaveStr If true, the string being built by the parse is saved
                         into the token being built replacing the original string.
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         Lex_ParseTokenFinalize (
        LEX_DATA        *this,
        int32_t         newClass,
        bool            fSaveStr
    );


    /*** @protected ***/
    /*!
     Setup the given token as the beginning of the next parse output
     token (ie First element of the next parse) and initialize the ac-
     cumulation string to the contents of the given token.
     @param     this    LEX object pointer
     @param     pToken  pointer to a token that is used to define the
                         next parsed output token. The string/char within the
                         token is used as the first char/string of the new
                         parsed token.
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         Lex_ParseTokenSetup (
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
    );


    /*** @protected ***/
    /*!
     Truncate the parse string accumulated so far.
     @param     this    LEX object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         Lex_ParseTokenTruncate (
        LEX_DATA        *this
    );


    /*** @protected ***/
    /*!
     Set up the internal token to represent EOF.
     @param     this    LEX object pointer
     @return    If successful, internal token pointer; otherwise, OBJ_NIL.
     */
    TOKEN_DATA *    Lex_SetupTokenEOF (
        LEX_DATA        *this
    );




#ifdef NDEBUG
#else
    bool            Lex_Validate (
        LEX_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* LEX_INTERNAL_H */

