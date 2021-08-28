// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Lex_internal.h
 *  Generated 05/28/2020 16:45:58
 *
 * Notes:
 *  --  The default parser parses the more common 'C' language lexical
 *      tokens. It starts a new output token at the beginning of the
 *      scan accumulating the first character in the character accumulation
 *      string.  As the parse proceeds, each new accepted input character
 *      is appended to the character acccumulation string. When the end
 *      of the token being scanned is found, a type is established for it.
 *      Finalization creates the new output token from the new type and
 *      the character accumulation string.
 *
 *      We have added exits in the parse process to support supplementing
 *      the parse process or output.
 *
 *      The Pre-Process Exit allows for the default parser to be over-
 *      ridden if needed. It should return 0 to indicate that it parsed
 *      a valid token, 1 to skip the current input token and try the next
 *      one or any other value to just do normal processing within the
 *      default parser.
 *
 *      The Default Exit is called whenever the lead character of the
 *      new output token does not normally begin any known token that
 *      can be parsed. This allows other tokens to be recognized by
 *      an external routine.
 *
 *      The Post-Process Exit allows for the addition of processwing
 *      input tokens that are not recognized by the default parser.
 *      This exit should return 0 to indicate that a valid output token
 *      has been recognized or any other value to indicate that the
 *      input token was not handled.
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


    // This structure is normally used in ParseToken()
    // methods to pass data to subordinate parsers.
    // Each sub-parser assumes that cls1/chr1 has been
    // added to the accumulated string and advanced over.
    // Whereas cls2/chr2 is a lookahead just beyond the
    // first token.
    typedef struct Lex_Parse_Data_s {
        TOKEN_DATA      *pOutput;
        W32STR_DATA     *pStr;      // String from accumulated tokens
        int32_t         clsNew;
        bool            fFinalize;
        bool            fSavStr;
        TOKEN_DATA      token1;
        int32_t         cls1;       // Absorbed token
        W32CHR_T        chr1;
        TOKEN_DATA      token2;
        int32_t         cls2;       // Lookahead token
        W32CHR_T        chr2;
    } LEX_PARSE_DATA;



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
    ERESULT         (*pParser)(OBJ_ID);             // Lexical Parser
    OBJ_ID          pParseObj;
    ERESULT         (*pError)(OBJ_ID, ASTR_DATA *);     // Error Exit
    OBJ_ID          pErrorObj;
    // The default exit is called if the default parser does not find
    // a match for the first token.  It allows for extensions to be added
    // to the default process.
    int             (*pParserDfltExit)(
                                   OBJ_ID,          // pParserExitObj
                                   LEX_DATA *,      // LEX Object Ptr
                                   LEX_PARSE_DATA * // Current Parse Data Ptr
                    );
    OBJ_ID          pParserDfltExitObj;
    // The pre-process exit is called before the first token is analyzed
    // allowing default parsing to be overridden.
    int             (*pParserPreExit)(
                                   OBJ_ID,          // pParserExitObj
                                   LEX_DATA *,      // LEX Object Ptr
                                   LEX_PARSE_DATA * // Current Parse Data Ptr
                    );
    OBJ_ID          pParserPreExitObj;
    // The post-process exit is called when the default parser is about
    // to finalize a token. This exit may ignore the token or continue
    // with the finalization.  Ignoring the token causes the parser to
    // start all over again scanning the next token. This exit could
    // manipulate the internal save token save string if needed.
    // Return codes:
    //      0 == Keep token as is
    //      1 == Reset data area and scan next char
    //      2 == Keep data as is and scan next char
    int             (*pParserPostExit)(
                                   OBJ_ID,          // pParserExitObj
                                   LEX_DATA *,      // LEX Object Ptr
                                   LEX_PARSE_DATA * // Current Parse Data Ptr
                    );
    OBJ_ID          pParserPostExitObj;
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
    LEX_DATA *      Lex_getSingleton (
        void
    );

    bool            Lex_setSingleton (
     LEX_DATA           *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    /*
     This exit is called when a character is not recognized. It allows
     the scan to be enhanced for other characters that are not normally
     handled.
     The exist can call:
            Lex_TokenAppendStringW32(this, data.chr2);
            fRc = Lex_NextInput(this, &data, false);
     as needed to do its own scan if desired. It should return:
        0 == Accept token as scanned,
        1 == Reset data accumulated and scan next char.
        2 == Keep data as it is and scan next char.

     */
    bool            Lex_setParserDfltxit(
        LEX_DATA        *this,
        ERESULT         (*pParser)(OBJ_ID, LEX_DATA *, LEX_PARSE_DATA *),
        OBJ_ID          pParseObj
    );


    /*
     This exit is called just before an output token if finalized and
     allows aspects of it to be over-ridden or even skipped.
     The exist can call:
            Lex_TokenAppendStringW32(this, data.chr2);
            fRc = Lex_NextInput(this, &data, false);
     as needed to do its own scan if desired. It should return:
        0 == Accept token as scanned,
        1 == Reset data accumulated and scan next char.
        2 == Keep data as it is and scan next char.

     */
    bool            Lex_setParserPostExit(
        LEX_DATA        *this,
        ERESULT         (*pParser)(OBJ_ID, LEX_DATA *, LEX_PARSE_DATA *),
        OBJ_ID          pParseObj
    );


    /*
     This exit allows the entire lexical scan to be over-ridden.
     The exit can call:
            Lex_TokenAppendStringW32(this, data.chr2);
            fRc = Lex_NextInput(this, &data, false);
     as needed to do its own scan if desired. It should return:
        0 == Accept what exit scanned.
        1 == Skip to next token and continue scan.
        2 == Continue with default scanner.

     */
    bool            Lex_setParserPreExit(
        LEX_DATA        *this,
        ERESULT         (*pParser)(OBJ_ID, LEX_DATA *, LEX_PARSE_DATA *),
        OBJ_ID          pParseObj
    );


    OBJ_IUNKNOWN * Lex_getSuperVtbl (
        LEX_DATA        *this
    );


    TOKEN_DATA *    Lex_getToken(
        LEX_DATA        *this
    );


    ERESULT         Lex_Assign (
        LEX_DATA        *this,
        LEX_DATA        *pOther
    );


    LEX_DATA *      Lex_Copy (
        LEX_DATA        *this
    );


    void            Lex_Dealloc (
        OBJ_ID          objId
    );


    ERESULT         Lex_DefaultParser(
        OBJ_ID          pObj
    );


    /*!
     Advance in the input token stream num tokens, refilling the
     empty positions in the unparsed input queue.
     @return:   If successful, a token which must NOT be released,
                otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Lex_InputAdvance (
        LEX_DATA        *this,
        uint16_t        num
    );


    /*!
     Look Ahead in the input token stream to the num'th token in the
     unparsed input queue.
     @return:   If successful, a token which must NOT be released,
                otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Lex_InputLookAhead (
        LEX_DATA        *this,
        uint16_t        num
    );


#ifdef  LEX_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    LEX_DATA *      Lex_ParseJsonObject (
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
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData
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
     Advance to the next input token and get the lookahead just beyond it.
     @param     this        object pointer
     @param     pData       input data area pointer
     @param     fSetupToken true == setup the advanced token as the 1st token
                            in this new string
     @return    true if successful, otherwise false
     */
    bool            Lex_NextInput(
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData,
        bool            fSetupToken
    );


    /*!
     Parse a character constant character not allowing \f, \n or \r.
     */
    int             Lex_ParseChrCon (
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData,
        W32CHR_T        ending
    );


    /*** @protected ***/
    /*!
     Parse a character constant character allowing \f,  \n or \r.
     */
    int             Lex_ParseChrConWS (
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData,
        W32CHR_T        ending
    );


    uint16_t        Lex_ParseIntegerSuffix (
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData
    );


    bool            Lex_ParseName (
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData
    );


    /*** @protected ***/
    /*!
     Parse a number of varying formats. The first character of the number
     has already been parsed, appended, and advanced over. So, we can
     look at it and make decisions based on it.
     @return    If successful, LEX_CONSTANT_* class, otherwise 0. Also,
                 the token string is accumulated.
     */
    uint16_t        Lex_ParseNumber (
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData
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
     to be returned in this->token where it is either one W32CHR_T or
     a character string saved in the global szTbl. This allows the
     token to be copied or used for assign(), but must not be freed.
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


    /*** @protected ***/
    /*!
     Append the character data to the parse string.
     @param     this    LEX object pointer
     @param     chr     wide char to be appended to the string
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         Lex_TokenAppendStringW32(
        LEX_DATA        *this,
        W32CHR_T        chr
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

