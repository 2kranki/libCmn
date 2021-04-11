// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Lexical Scanner (Lex) Header
//****************************************************************
/*
 * Program
 *          Lexical Scanner (Lex)
 * Purpose
 *          This object provides the basis for a Lexical Scanner. It
 *          supports creating an output token from the input and queueing
 *          those output tokens as needed.
 *
 *          From an output point of view, callers to this object can
 *          lookahead to next tokens in the output queue and/or just
 *          process the current token which advances to the next token.
 *          See TokenLookAhead() and TokenAdvance().
 *
 * Remarks
 *  1.      This object is designed to be inherited. See internal
 *          documentation on how to use this object.
 *
 * History
 *  09/07/2015  Generated
 *  05/28/2020  Regenerated
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





#include        <cmn_defs.h>
#include        <AStr.h>
#include        <szTbl.h>
#include        <Token.h>


#ifndef         LEX_H
#define         LEX_H


//#define   LEX_IS_IMMUTABLE     1
//#define   LEX_JSON_SUPPORT     1
//#define   LEX_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Lex_data_s  LEX_DATA;            // Inherits from OBJ
    typedef struct Lex_class_data_s LEX_CLASS_DATA;   // Inherits from OBJ

    typedef struct Lex_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Lex_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEX_DATA *);
    } LEX_VTBL;

    typedef struct Lex_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Lex_object.c.
         // Properties:
         ERESULT_DATA *  (*pGetErrors)(
             LEX_DATA        *this
         );
         bool            (*pSetErrors)(
             LEX_DATA        *this,
             ERESULT_DATA    *pValue
         );

         bool            (*pSetParserFunction)(
             LEX_DATA        *this,
             ERESULT         (*pParser)(OBJ_ID, TOKEN_DATA *),
             OBJ_ID          pParseObj
         );

         bool            (*pSetSourceInput)(
             LEX_DATA        *this,
             TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID,uint16_t),
             TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID,uint16_t),
             OBJ_ID          pSrcObj
         );

         W32STR_DATA *   (*pGetString)(
             LEX_DATA        *this
         );

         TOKEN_DATA *    (*pGetToken)(
             LEX_DATA        *this
         );

         // Methods:
         TOKEN_DATA *    (*pInputAdvance)(
             LEX_DATA        *this,
             uint16_t        numChrs
         );

         TOKEN_DATA *    (*pInputLookAhead)(
             LEX_DATA        *this,
             uint16_t        num
         );

         TOKEN_DATA *    (*pTokenAdvance)(
             LEX_DATA        *this,
             uint16_t        num
         );

         TOKEN_DATA *    (*pTokenLookAhead)(
             LEX_DATA        *this,
             uint16_t        num
         );

         ERESULT         (*pTokenPush)(
             LEX_DATA        *this,
             TOKEN_DATA      *pChr
         );
            } LEX_CLASS_VTBL;


    /*                  Lexical Classes
     Each lexical class represents a particular scanner class. A
     scanner must be able to accept these classes and either pass
     them on or process them. A compiler would generally have to
     process them or flag them as an error.

     These constants consist of all the constants that we need for
     various application. A compiler would not need to accept all
     of them only the ones that make sense for it.
     */
    typedef enum Lex_class_e {
        /* Values below 256 are a character by itself that makes
         * its own token class. All other classes for groups of
         * characters should be allocated in the range above
         * LEX_CLASS_GROUP_LOWEST.
         */
        LEX_CLASS_EOF=-1,
        LEX_CLASS_UNKNOWN=0,
        /*
         Classes 1-255 are meant to represent the individual ASCII
         characters as their own class.  So, a token should have
         the character in both the class and value.
         LEX_CLASS_CHAR
         */

        LEX_CLASS_GROUP_LOWEST=256,
        // Note the following must be kept synchronized with the
        // ascii lexical classes (See ascii.h).
        LEX_CLASS_ALPHA_LOWER=256,          // a-z
        LEX_CLASS_ALPHA_UPPER,              // A-Z
        LEX_CLASS_DELETE,                   // ascii 127
        LEX_CLASS_NUMBER,                   // 0-9
        LEX_CLASS_EOL,                      // '\n'
        LEX_CLASS_WHITESPACE,               // ' ', '\t', '\n', '\r', '\f', '\v'
        LEX_CLASS_UNICODE,                  //  Class for characters not in the
        //                                  //  range 1..255

        LEX_CLASS_COMMENT_GROUP=270,
        LEX_COMMENT_SINGLE,                 //  Single Line Comment
        LEX_COMMENT_MULTI,                  //  Multiple Line Comment

        LEX_CLASS_CONSTANT_GROUP=300,
        LEX_CONSTANT_CHAR,
        LEX_CONSTANT_CHAR_WIDE,
        LEX_CONSTANT_FLOAT,
        LEX_CONSTANT_INTEGER,
        LEX_CONSTANT_STRING,
        LEX_CONSTANT_STRING_WIDE,
        LEX_CONSTANT_TEXT,                  // Text surrounded by "{%" ... "%}"
        LEX_CONSTANT_TEXTB,                 // Text surrounded by "[%" ... "%]"
        LEX_CONSTANT_TEXTC,                 // Text surrounded by "(%" ... "%)"
        LEX_CONSTANT_TEXTD,                 // Text surrounded by "<." ... ".>"
        LEX_CONSTANT_TEXTE,                 // Text surrounded by "{." ... ".}"
        LEX_CONSTANT_TEXTF,                 // Text surrounded by "[." ... ".]"
        LEX_CONSTANT_TEXTG,                 // Text surrounded by "(." ... ".)"

        LEX_IDENTIFIER=400,

        LEX_CLASS_SEP_GROUP=500,
        LEX_SEP_AT,                         // @
        LEX_SEP_COLON,                      // :
        LEX_SEP_COMMA,                      // ,
        LEX_SEP_DOT,                        // .
        LEX_SEP_DOT_GT,                     // .>
        LEX_SEP_LBRACK,                     // [
        LEX_SEP_LBRACE,                     // {
        LEX_SEP_LT_DOT,                     // <.
        LEX_SEP_LPAREN,                     // (
        LEX_SEP_NL,                         // '\n'
        LEX_SEP_WS,                         // ' ' , '\n', '\r', '\t'
        LEX_SEP_LARROW,                     // <-
        LEX_SEP_RARROW,                     // ->
        LEX_SEP_RBRACK,                     // ]
        LEX_SEP_RBRACE,                     // }
        LEX_SEP_RPAREN,                     // )
        LEX_SEP_SEMICOLON,                  // ;

        LEX_CLASS_OP_GROUP=600,
        LEX_OP_ADD,                         // +
        LEX_OP_ADDR,                        // &    (Address)
        LEX_OP_AND,                         // &    (and)
        LEX_OP_ASSIGN,                      // =
        LEX_OP_ASSIGN_ADD,                  // +=
        LEX_OP_ASSIGN_AND,                  // &=
        LEX_OP_ASSIGN_DIV,                  // /=
        LEX_OP_ASSIGN_LEFT,                 // <<=
        LEX_OP_ASSIGN_MUL,                  // *=
        LEX_OP_ASSIGN_MOD,                  // %=
        LEX_OP_ASSIGN_OR,                   // |=
        LEX_OP_ASSIGN_RIGHT,                // >>=
        LEX_OP_ASSIGN_SUB,                  // -=
        LEX_OP_ASSIGN_XOR,                  // ^=
        LEX_OP_DEC,                         // --   (decrement)
        LEX_OP_DIV,                         // /
        LEX_OP_ELIPSIS,                     // ...
        LEX_OP_EQ,                          // ==
        LEX_OP_GE,                          // >=
        LEX_OP_GT,                          // >
        LEX_OP_INC,                         // ++   (increment)
        LEX_OP_LE,                          // <=
        LEX_OP_LOG_AND,                     // &&   (logical and)
        LEX_OP_LOG_NOT,                     // !    (logical not)
        LEX_OP_LOG_OR,                      // ||   (logical or)
        LEX_OP_LEFT,                        // <<   (Shift Left)
        LEX_OP_LT,                          // <
        LEX_OP_MINUS,                       // -    (unary minus)
        LEX_OP_MOD,                         // %    (modulus)
        LEX_OP_MUL,                         // *
        LEX_OP_NE,                          // !=
        LEX_OP_NEG,                         // ~    (2s complement)
        LEX_OP_NOT,                         // !    (1s complement)
        LEX_OP_OR,                          // |
        LEX_OP_POUND,                       // #
        LEX_OP_2POUNDS,                     // ##
        LEX_OP_PTR,                         // *    (???)
        LEX_OP_QUESTION,                    // ?
        LEX_OP_RANGE,                       // ..
        LEX_OP_RIGHT,                       // >> (Shift Right)
        LEX_OP_SUB,                         // -
        LEX_OP_XOR,                         // ^

        LEX_CLASS_KWD_GROUP=700,
        LEX_KWD_ASM,
        LEX_KWD_ASSIGN,
        LEX_KWD_AT_AUTO,
        LEX_KWD_AT_CATCH,
        LEX_KWD_AT_CLASS,
        LEX_KWD_AT_DYNAMIC,
        LEX_KWD_AT_ENCODE,
        LEX_KWD_AT_END,
        LEX_KWD_AT_FINALLY,
        LEX_KWD_AT_IMPLEMENTATION,
        LEX_KWD_AT_INTERFACE,
        LEX_KWD_AT_OPTIONAL,
        LEX_KWD_AT_PKG,
        LEX_KWD_AT_PRIVATE,
        LEX_KWD_AT_PROPERTY,
        LEX_KWD_AT_PROTECTED,
        LEX_KWD_AT_PROTOCOL,
        LEX_KWD_AT_PUBLIC,
        LEX_KWD_AT_SEL,
        LEX_KWD_AT_SYNC,
        LEX_KWD_AT_SYNTH,
        LEX_KWD_AT_THROW,
        LEX_KWD_AT_TRY,
        LEX_KWD_AUTO,
        LEX_KWD_BOOL,
        LEX_KWD_BREAK,
        LEX_KWD_BYCOPY,
        LEX_KWD_BYREF,
        LEX_KWD_CASE,
        LEX_KWD_CCW,
        LEX_KWD_CDECL,
        LEX_KWD_CHAR,
        LEX_KWD_CLASS,
        LEX_KWD_CNOP,
        LEX_KWD_COMPLEX,
        LEX_KWD_CONST,
        LEX_KWD_CONTINUE,
        LEX_KWD_COPY,
        LEX_KWD_CSECT,
        LEX_KWD_DC,
        LEX_KWD_DEFAULT,
        LEX_KWD_DELETE,
        LEX_KWD_DO,
        LEX_KWD_DOUBLE,
        LEX_KWD_DROP,
        LEX_KWD_DS,
        LEX_KWD_DSECT,
        LEX_KWD_ELSE,
        LEX_KWD_EMIT,
        LEX_KWD_END,
        LEX_KWD_ENTRY,
        LEX_KWD_ENUM,
        LEX_KWD_EQU,
        LEX_KWD_EXTERN,
        LEX_KWD_EXTRN,
        LEX_KWD_FALSE,
        LEX_KWD_FAR,
        LEX_KWD_FLOAT,
        LEX_KWD_FOR,
        LEX_KWD_FORTRAN,
        LEX_KWD_FRIEND,
        LEX_KWD_GETTER,
        LEX_KWD_GOAL,
        LEX_KWD_GOTO,
        LEX_KWD_ID,
        LEX_KWD_IF,
        LEX_KWD_IMAGINARY,
        LEX_KWD_IN,
        LEX_KWD_INLINE,
        LEX_KWD_INOUT,
        LEX_KWD_INT,
        LEX_KWD_INT8,
        LEX_KWD_INT16,
        LEX_KWD_INT32,
        LEX_KWD_INT64,
        LEX_KWD_INT128,
        LEX_KWD_INT256,
        LEX_KWD_INTERFACE,
        LEX_KWD_INTERNAL,
        LEX_KWD_LONG,
        LEX_KWD_LTORG,
        LEX_KWD_MACRO,
        LEX_KWD_MEND,
        LEX_KWD_NEAR,
        LEX_KWD_NEW,
        LEX_KWD_NIL,
        LEX_KWD_NONATOMIC,
        LEX_KWD_NSENUM,
        LEX_KWD_NSOPTIONS,
        LEX_KWD_NULL,
        LEX_KWD_OFFSETOF,
        LEX_KWD_ONEWAY,
        LEX_KWD_OPERATOR,
        LEX_KWD_ORG,
        LEX_KWD_OUT,
        LEX_KWD_OVERLOAD,
        LEX_KWD_PASCAL,
        LEX_KWD_PRIVATE,
        LEX_KWD_PUBLIC,
        LEX_KWD_READONLY,
        LEX_KWD_READWRITE,
        LEX_KWD_REGISTER,
        LEX_KWD_RETAIN,
        LEX_KWD_RESTRICT,
        LEX_KWD_RETURN,
        LEX_KWD_RSECT,
        LEX_KWD_SELECT,
        LEX_KWD_SELF,
        LEX_KWD_SETTER,
        LEX_KWD_SHORT,
        LEX_KWD_SIGNED,
        LEX_KWD_SIZEOF,
        LEX_KWD_START,
        LEX_KWD_STATIC,
        LEX_KWD_STRONG,
        LEX_KWD_STRUCT,
        LEX_KWD_SUPER,
        LEX_KWD_SWITCH,
        LEX_KWD_TERM,
        LEX_KWD_THIS,
        LEX_KWD_TRUE,
        LEX_KWD_TYPEDEF,
        LEX_KWD_UINT8,
        LEX_KWD_UINT16,
        LEX_KWD_UINT32,
        LEX_KWD_UINT64,
        LEX_KWD_UINT128,
        LEX_KWD_UINT256,
        LEX_KWD_UNION,
        LEX_KWD_UNSIGNED,
        LEX_KWD_USING,
        LEX_KWD_VIRTUAL,
        LEX_KWD_VOID,
        LEX_KWD_VOLATILE,
        LEX_KWD_WEAK,
        LEX_KWD_WHILE,
        LEX_KWD_WXTRN,

        LEX_CLASS_SPCL_GROUP=1000,
        LEX_SPCL_LBRACK_COLON,              // [:
        LEX_SPCL_LBRACE_COLON,              // {:
        LEX_SPCL_AT_LBRACK,                 // @[
        LEX_SPCL_AT_LBRACE,                 // @{
        LEX_SPCL_AT_LPAREN,                 // @(
        LEX_SPCL_PAREN_LEFT,                // (:
        LEX_SPCL_PAREN_RIGHT,               // :)
        LEX_SPCL_COLON,                     // :
        LEX_SPCL_COLON_RBRACK,              // :]
        LEX_SPCL_COLON_RBRACE,              // :}
        LEX_SPCL_DBLCOLON,                  // ::
        LEX_SPCL_COLON_LEFT,                // <:
        LEX_SPCL_COLON_RIGHT,               // :>
        LEX_SPCL_LBRACK,                    // [%
        LEX_SPCL_LBRACE,                    // {%
        LEX_SPCL_LPAREN,                    // (%
        LEX_SPCL_RARROW,                    // =>
        LEX_SPCL_RBRACK,                    // %]
        LEX_SPCL_RBRACE,                    // %}
        LEX_SPCL_RPAREN,                    // %)
        LEX_SPCL_SEPARATOR,                 // %%

        LEX_CLASS_TYPE_GROUP=1200,
        LEX_TYPE_METHOD,
        LEX_TYPE_NAME,

        LEX_CLASS_HIGHEST=2048,

    } LEX_CLASS;


    // The following defines the flags for the scanner. The first eight flags
    // should be reserved for this object. Inheriting object may use the rest.
    // These flags are used with the Flags property:
    typedef enum Lex_Flags_e {
        LEX_FLAG_UNKNOWN=0,
        LEX_FLAG_MULTICHRCON=0x80000000,            // Allow constants surrounded by
        //                                          // single apostrophies to be
        //                                          // multi-character same as those
        //                                          // surrounded by double apostrophies
        LEX_FLAG_WS=0x40000000,                     /* Return Whitespace */
        LEX_FLAG_NL=0x20000000,                     /* Return NLs */
        LEX_FLAG_CMT=0x20000000,                    /* Return comments */
    } LEX_FLAGS;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LEX_SINGLETON
    LEX_DATA *      Lex_Shared (
        void
    );

    void            Lex_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Lex object if successful, otherwise OBJ_NIL.
     */
    LEX_DATA *      Lex_Alloc (
        void
    );
    
    
    OBJ_ID          Lex_Class (
        void
    );
    
    
    /*!
        Given a lexical value class translate that to a printable string,
        mostly to be used for debugging purposes.
        @return     pointer to string if successful, otherwise
                    "LEX_CLASS_UNKNOWN".
      */
    const
    char *          Lex_ClassToString(
        int32_t         value
    );


    LEX_DATA *      Lex_New (
        void
    );
    
    
#ifdef  LEX_JSON_SUPPORT
    LEX_DATA *      Lex_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LEX_DATA *      Lex_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT_DATA *  Lex_getErrors (
        LEX_DATA        *this
    );

    bool            Lex_setErrors (
        LEX_DATA        *this,
        ERESULT_DATA    *pValue
    );

    /*! These are the input flags that should be used before any
        processing of tokens is done to control the tokenization
        process. One bit might be used to say return tokens for
        newlines or don't for instance.
     */
    uint32_t        Lex_getFlags (
        LEX_DATA        *this
    );

    bool            Lex_setFlags (
        LEX_DATA        *this,
        uint32_t        value
    );


    /*
     If true, allow constants surrounded by single apostrophies to be
     multi-character same as those surrounded by double apostrophies.
     Default is false.
     */
    bool            Lex_getMultiCharConstant (
        LEX_DATA        *this
    );

    bool            Lex_setMultiCharConstant (
        LEX_DATA        *this,
        bool            value
    );


    bool            Lex_setParserFunction (
        LEX_DATA        *this,
        ERESULT         (*pParser)(OBJ_ID, TOKEN_DATA *),
        OBJ_ID          pParseObj
    );


    bool            Lex_setSourceInput (
        LEX_DATA        *this,
        TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID,uint16_t),
        TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID,uint16_t),
        OBJ_ID          pSrcObj
    );


    uint32_t        Lex_getStatuses (
        LEX_DATA        *this
    );

    bool            Lex_setStatuses (
        LEX_DATA        *this,
        uint32_t        value
    );


    W32STR_DATA *   Lex_getString (
        LEX_DATA        *this
    );


    TOKEN_DATA *    Lex_getToken (
        LEX_DATA        *this
    );





    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     This routine starts/restarts the checkpoint process for backtracking
     parsers by accumulating all tokens which are advanced over. The
     accumulated tokens can be re-used by calling the Restore() method
     or abandoned by the Discard() method. If a restart is being requested,
     it is the same as a Discard() followed by a Checkpoint().
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_???.
     */
    ERESULT         Lex_Checkpoint (
        LEX_DATA        *this
    );


    LEX_DATA *      Lex_Init (
        LEX_DATA        *this
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


    /*!
     This routine restarts the token flow from the last checkpoint and
     terminates the checkpoint process.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_???.
     */
    ERESULT         Lex_Restart (
        LEX_DATA        *this
    );


    /*!
     Setup or expand the size of the lookahead queue and preload the
     queue with data.
     @param     this    object pointer
     @param     k       size of lookahead queue (Use a power of 2 if
                        at all possible for this.)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     @warning   You must establish the Source Input methods prior to
                calling this method, because it creates the queue and
                loads it with data (calling the Source Input methods).
     */
    ERESULT         Lex_SetupQueue (
        LEX_DATA        *this,
        uint16_t        k
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
        LEX_DATA        *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = Lex_ToDebugString(this,4);
     @endcode
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex_ToDebugString (
        LEX_DATA        *this,
        int             indent
    );


    /*!
     Advance in the output token stream num tokens, refilling the
     empty positions in the parsed output queue.
     @param     this    object pointer
     @param     num     number of tokens to advance
     @return:   If successful, a token which must NOT be released,
                otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Lex_TokenAdvance (
        LEX_DATA        *this,
        uint16_t        num
    );


    /*!
     Look Ahead in the token stream to the num'th token in the
     parsed output queue.
     @param     this    object pointer
     @param     num     number of tokens to lookahead to
     @return:   If successful, a token which must NOT be released,
                otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Lex_TokenLookAhead (
        LEX_DATA        *this,
        uint16_t        num
    );


    /*!
     This routine adds the given token onto the tail of the
     FIFO output queue. Both, InputAdvance() and InputLookAhead(),
     return from this queue first if it contains any tokens
     before looking at the parsed input queue.
     @return:   If successful, ERESULT_SUCCESSFUL_COMPLETION,
                otherwise ERESULT_ERROR_???.
     */
    ERESULT         Lex_TokenPush (
        LEX_DATA        *this,
        TOKEN_DATA      *pChr
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* LEX_H */

