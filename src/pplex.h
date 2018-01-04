// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          PPLEX Console Transmit Task (pplex) Header
//****************************************************************
/*
 * Program
 *			Separate pplex (pplex)
 * Purpose
 *			This object provides an easy way of using ppLex1,
 *          ppLex2, and ppLex3. It simply builds and chains the
 *          selected ppLex's, sets up the token source and provides
 *          the source of all tokens emitted by the internal ppLex
 *          chain.
 *
 *          ppLex2 is always required. It is the base tokenizer
 *          without any reserved words. ppLex3 adds reserved words
 *          for C and Objective-C. ppLex1 adds trigraph support.
 *          Each is written much like a Unix filter with input
 *          and output being well defined and changeable.
 *
 * Remarks
 *	1.      None.
 *
 * History
 *	09/29/2015 Generated
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
#include        <lex.h>
#include        <token.h>




#ifndef         PPLEX_H
#define         PPLEX_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct pplex_data_s	PPLEX_DATA; // Inherits from LEX_DATA

    typedef struct pplex_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in consumer_object.c.
        // Properties:
        // Methods:
    } PPLEX_VTBL;
    

    typedef enum pplex_lang_e {
        PPLEX_LANG_UNKNOWN=0,
        PPLEX_LANG_C=0x8000,
        PPLEX_LANG_CPP=0x4000,
        PPLEX_LANG_LL1=0x0800,
        PPLEX_LANG_MSC=0x2000,
        PPLEX_LANG_OBJC=0x1000,
    } PPLEX_LANG;
    
    
    typedef struct pplex_kwdtbl_entry_s {
        int32_t     value;                    /* Lexical Scan Value */
        uint16_t    flags;                    /* Flags */
        char        *pKwd;                    /* Key Word */
    } PPLEX_KWDTBL_ENTRY;

    
    typedef enum pplex_class_e {
        /* Values below 256 are a character by itself that makes
         * its own token class.
         */
        PPLEX_CLASS_EOF=-1,
        PPLEX_CLASS_UNDEFINED=-2,
        PPLEX_CLASS_UNKNOWN=0,
        
        PPLEX_CLASS_GROUP_LOWEST=256,
        
        PPLEX_CLASS_COMMENT_GROUP=LEX_CLASS_COMMENT_GROUP,
        PPLEX_COMMENT_SINGLE,               // Single Line Comment
        PPLEX_COMMENT_MULTI,                // Multiple Line Comment
        
        PPLEX_CLASS_CONSTANT_GROUP=LEX_CLASS_CONSTANT_GROUP,
        PPLEX_CONSTANT_CHAR,
        PPLEX_CONSTANT_CHAR_WIDE,
        PPLEX_CONSTANT_FLOAT,
        PPLEX_CONSTANT_INTEGER,
        PPLEX_CONSTANT_STRING,
        PPLEX_CONSTANT_STRING_WIDE,
        PPLEX_CONSTANT_TEXT,                // Text surrounded by "%{" ... "%}"
        PPLEX_CONSTANT_TEXTB,               // Text surrounded by "%[" ... "%]"
        PPLEX_CONSTANT_TEXTC,               // Text surrounded by "%(" ... "%)"
        PPLEX_CONSTANT_TEXTD,               // Text surrounded by "<." ... ".>"
        
        PPLEX_IDENTIFIER=LEX_IDENTIFIER,
        
        PPLEX_SEP_AT=LEX_CLASS_SEP_GROUP,   // @
        PPLEX_SEP_COMMA,                    // ,
        PPLEX_SEP_DOT,                      // .
        PPLEX_SEP_DOT_GT,                   // .>
        PPLEX_SEP_LBRACKET,                 // [
        PPLEX_SEP_LBRACE,                   // {
        PPLEX_SEP_LT_DOT,                   // <.
        PPLEX_SEP_LPAREN,                   // (
        PPLEX_SEP_NL,                       // '\n'
        PPLEX_SEP_LARROW,                   // <-
        PPLEX_SEP_RARROW,                   // ->
        PPLEX_SEP_RBRACKET,                 // ]
        PPLEX_SEP_RBRACE,                   // }
        PPLEX_SEP_RPAREN,                   // )
        PPLEX_SEP_SEMICOLON,                // ;
        PPLEX_SEP_WHITESPACE,
        
        PPLEX_OP_ADD=LEX_CLASS_OP_GROUP,    // +
        PPLEX_OP_ADDR,                      // &
        PPLEX_OP_AND,                       // &
        PPLEX_OP_ASSIGN,                    // =
        PPLEX_OP_ASSIGN_ADD,                // +=
        PPLEX_OP_ASSIGN_AND,                // &=
        PPLEX_OP_ASSIGN_DIV,                // /=
        PPLEX_OP_ASSIGN_LEFT,               // <<=
        PPLEX_OP_ASSIGN_MUL,                // *=
        PPLEX_OP_ASSIGN_MOD,                // %=
        PPLEX_OP_ASSIGN_OR,                 // |=
        PPLEX_OP_ASSIGN_RIGHT,              // >>=
        PPLEX_OP_ASSIGN_SUB,                // -=
        PPLEX_OP_ASSIGN_XOR,                // ^=
        PPLEX_OP_DEC,                       // --
        PPLEX_OP_DIV,                       // /
        PPLEX_OP_ELIPSIS,                   // ...
        PPLEX_OP_EQ,                        // ==
        PPLEX_OP_GE,                        // >=
        PPLEX_OP_GT,                        // >
        PPLEX_OP_INC,                       // ++
        PPLEX_OP_LE,                        // <=
        PPLEX_OP_LOG_AND,                   // &&
        PPLEX_OP_LOG_NOT,                   // !
        PPLEX_OP_LOG_OR,                    // ||
        PPLEX_OP_LEFT,                      // <<
        PPLEX_OP_LT,                        // <
        PPLEX_OP_MOD,                       // %
        PPLEX_OP_MUL,                       // *
        PPLEX_OP_NE,                        // !=
        PPLEX_OP_NEG,                       // ~
        PPLEX_OP_NOT,                       // !
        PPLEX_OP_OR,                        // |
        PPLEX_OP_POUND,                     // #
        PPLEX_OP_PTR,                       // * (???)
        PPLEX_OP_QUESTION,                  // ?
        PPLEX_OP_RANGE,                     // ..
        PPLEX_OP_RIGHT,                     // >>
        PPLEX_OP_SUB,                       // -
        PPLEX_OP_XOR,                       // ^
        
        PPLEX_KWD_ASM=LEX_CLASS_KWD_GROUP,
        PPLEX_KWD_ASSIGN,
        PPLEX_KWD_AT_AUTO,                  // OBJC
        PPLEX_KWD_AT_CATCH,                 // OBJC
        PPLEX_KWD_AT_CLASS,                 // OBJC
        PPLEX_KWD_AT_DYNAMIC,               // OBJC
        PPLEX_KWD_AT_ENCODE,                // OBJC
        PPLEX_KWD_AT_END,                   // OBJC
        PPLEX_KWD_AT_FINALLY,               // OBJC
        PPLEX_KWD_AT_IMPLEMENTATION,        // OBJC
        PPLEX_KWD_AT_INTERFACE,             // OBJC
        PPLEX_KWD_AT_OPTIONAL,              // OBJC
        PPLEX_KWD_AT_PKG,                   // OBJC
        PPLEX_KWD_AT_PRIVATE,               // OBJC
        PPLEX_KWD_AT_PROPERTY,              // OBJC
        PPLEX_KWD_AT_PROTECTED,             // OBJC
        PPLEX_KWD_AT_PROTOCOL,              // OBJC
        PPLEX_KWD_AT_PUBLIC,                // OBJC
        PPLEX_KWD_AT_SEL,                   // OBJC
        PPLEX_KWD_AT_SYNC,                  // OBJC
        PPLEX_KWD_AT_SYNTH,                 // OBJC
        PPLEX_KWD_AT_THROW,                 // OBJC
        PPLEX_KWD_AT_TRY,                   // OBJC
        PPLEX_KWD_AUTO,
        PPLEX_KWD_BREAK,
        PPLEX_KWD_BYCOPY,
        PPLEX_KWD_BYREF,
        PPLEX_KWD_CASE,
        PPLEX_KWD_CDECL,
        PPLEX_KWD_CHAR,
        PPLEX_KWD_CLASS,
        PPLEX_KWD_CONST,
        PPLEX_KWD_CONTINUE,
        PPLEX_KWD_DEFAULT,
        PPLEX_KWD_DELETE,
        PPLEX_KWD_DO,
        PPLEX_KWD_DOUBLE,
        PPLEX_KWD_ELSE,
        PPLEX_KWD_EMIT,
        PPLEX_KWD_END,
        PPLEX_KWD_ENTRY,
        PPLEX_KWD_ENUM,
        PPLEX_KWD_EXTERN,
        PPLEX_KWD_FAR,
        PPLEX_KWD_FLOAT,
        PPLEX_KWD_FOR,
        PPLEX_KWD_FORTRAN,
        PPLEX_KWD_FRIEND,
        PPLEX_KWD_GETTER,
        PPLEX_KWD_GOAL,                     // LL1
        PPLEX_KWD_GOTO,
        PPLEX_KWD_ID,
        PPLEX_KWD_IF,
        PPLEX_KWD_IN,
        PPLEX_KWD_INOUT,
        PPLEX_KWD_INT,
        PPLEX_KWD_INT8,
        PPLEX_KWD_INT16,
        PPLEX_KWD_INT32,
        PPLEX_KWD_INT64,
        PPLEX_KWD_INT128,
        PPLEX_KWD_INT256,
        PPLEX_KWD_INTERNAL,                // LL1
        PPLEX_KWD_LONG,
        PPLEX_KWD_NEAR,
        PPLEX_KWD_NEW,
        PPLEX_KWD_NONATOMIC,
        PPLEX_KWD_NSENUM,
        PPLEX_KWD_NSOPTIONS,
        PPLEX_KWD_OFFSETOF,
        PPLEX_KWD_ONEWAY,
        PPLEX_KWD_OPERATOR,
        PPLEX_KWD_OUT,
        PPLEX_KWD_OVERLOAD,
        PPLEX_KWD_PASCAL,
        PPLEX_KWD_PRIVATE,
        PPLEX_KWD_PUBLIC,
        PPLEX_KWD_READONLY,
        PPLEX_KWD_READWRITE,
        PPLEX_KWD_REGISTER,
        PPLEX_KWD_RETAIN,
        PPLEX_KWD_RETURN,
        PPLEX_KWD_SELECT,
        PPLEX_KWD_SELF,
        PPLEX_KWD_SETTER,
        PPLEX_KWD_SHORT,
        PPLEX_KWD_SIGNED,
        PPLEX_KWD_SIZEOF,
        PPLEX_KWD_STATIC,
        PPLEX_KWD_STRONG,
        PPLEX_KWD_STRUCT,
        PPLEX_KWD_SUPER,
        PPLEX_KWD_SWITCH,
        PPLEX_KWD_TERM,                     // LL1
        PPLEX_KWD_THIS,
        PPLEX_KWD_TYPEDEF,
        PPLEX_KWD_UINT8,
        PPLEX_KWD_UINT16,
        PPLEX_KWD_UINT32,
        PPLEX_KWD_UINT64,
        PPLEX_KWD_UINT128,
        PPLEX_KWD_UINT256,
        PPLEX_KWD_UNION,
        PPLEX_KWD_UNSIGNED,
        PPLEX_KWD_VIRTUAL,
        PPLEX_KWD_VOID,
        PPLEX_KWD_VOLATILE,
        PPLEX_KWD_WEAK,
        PPLEX_KWD_WHILE,

        PPLEX_CLASS_SPCL_GROUP=LEX_CLASS_SPCL_GROUP,
        PPLEX_SPCL_AT_LBRACK,               // @[
        PPLEX_SPCL_AT_LCURL,                // @{
        PPLEX_SPCL_AT_LPAREN,               // @(
        PPLEX_SPCL_COLON,                   // :
        PPLEX_SPCL_DBLCOLON,                // ::
        PPLEX_SPCL_LBRACK,                  // %[
        PPLEX_SPCL_LCURL,                   // %{
        PPLEX_SPCL_LPAREN,                  // %(
        PPLEX_SPCL_POUND,                   // #
        PPLEX_SPCL_2POUNDS,                 // ##
        PPLEX_SPCL_QUESTION,                // ? (???)
        PPLEX_SPCL_RARROW,                  // =>
        PPLEX_SPCL_RBRACK,                  // %]
        PPLEX_SPCL_RCURL,                   // %}
        PPLEX_SPCL_RPAREN,                  // %)
        PPLEX_SPCL_SEPARATOR,               // %%
        PPLEX_SPCL_WHITESPACE,              // Used if whitespace is to be passed through
        
        PPLEX_TYPE_METHOD=LEX_CLASS_SPCL_GROUP+50,
        PPLEX_TYPE_NAME,
        
        PPLEX_CLASS_HIGHEST=LEX_CLASS_HIGHEST
    } PPLEX_CLASS;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the pplex including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    PPLEX_DATA *     pplex_Alloc(
        void
    );
    
    
    char *          pplex_ClassToString(
        int32_t         value
    );
    
    
    int32_t         pplex_KWToInt(
        uint16_t        select,
        const
        char            *pValue
    );
    
    
    PPLEX_DATA *     pplex_New(
        uint16_t        k
    );
    
    
    int32_t         pplex_StringToInt(
        const
        char            *pValue
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Add a keyword table that takes precedence over the other internal
        tables by being searched first. If the keyword is found, then the
        token class is taken from the table.  If it is not found, then the
        the internal tables are searched normally.
     */
    bool            pplex_setAuxKwdTable(
        PPLEX_DATA      *this,
        PPLEX_KWDTBL_ENTRY
                        *pAuxKwds,
        uint32_t        cAuxKwds
    );
    
    
    bool            pplex_setDebug(
        PPLEX_DATA      *this,
        bool            fValue
    );
    
    
    bool            pplex_getReturnNL(
        PPLEX_DATA      *this
    );
    
    bool            pplex_setReturnNL(
        PPLEX_DATA      *this,
        bool            fValue
    );
    

    bool            pplex_getReturnWS(
        PPLEX_DATA      *this
    );
    
    bool            pplex_setReturnWS(
        PPLEX_DATA      *this,
        bool            fValue
    );
    

    bool            pplex_setSourceFunction(
        PPLEX_DATA      *this,
        TOKEN_DATA *    (*pSrcChrAdvance)(OBJ_ID, uint16_t),
        TOKEN_DATA *    (*pSrcChrLookAhead)(OBJ_ID, uint16_t),
        OBJ_ID          pSrcObj
    );
    
    
    /*! Add a user exit that takes precedence over the all the keyword
        table searches.  The user exit should set the token class if
        it needs to which is what would have happened had it been found
        in a keyword table.
     
     @return    non-zero if the exit handled the token passed to it. The
                lexical status will be updated as if the token was
                found in a keyword table except the token is not
                changed.  zero indicates to perform the keyword
                table as normal.
     */
    bool            pplex_setKeywordParseFunction(
        PPLEX_DATA     *this,
        bool            (*pUserExit)(OBJ_ID, TOKEN_DATA *),
        OBJ_ID          pUserObj
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Create and chain pplex1..pplex3.
     @param     this        PPLEX Object Pointer
     @param     fLex3       true == create and chain a pplex3
     @param     fLex1       true == create and chain a pplex1
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         pplex_CreateLexers(
        PPLEX_DATA      *this,
        bool            fLex1,
        bool            fLex3
    );
    
    
    /*!
     Create a srcFile object from an AStr and set it up as the source
     for input to the Lexers.
     @param     this    PPLEX Object Pointer
     @param     pStr    a required AStr Object Pointer to be used as
                        input to the Lexer chain
     @param     pPath   an optional Path Object Pointer to be used as
                        path parameter of the tokens created from the
                        pStr object
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         pplex_CreateSourceFromAStr(
        PPLEX_DATA      *this,
        ASTR_DATA       *pStr,
        PATH_DATA       *pPath
    );
    
    
    PPLEX_DATA *    pplex_Init(
        PPLEX_DATA      *this,
        uint16_t        k
    );


    /*!
     Advance in the input token stream num tokens, refilling the
     empty positions in the input queue.
     @param     this    PPLEX Object Pointer
     @return    If successful, the current token which must NOT be
                released, otherwise OBJ_NIL.
     */
    TOKEN_DATA *    pplex_InputAdvance(
        PPLEX_DATA		*this,
        uint16_t        numChrs
    );
    
    
    /*!
     Look Ahead in the token stream to the num'th token in the
     output queue.
     @param     this    PPLEX Object Pointer
     @return    If successful, a token which must NOT be released,
                otherwise OBJ_NIL.
     */
    TOKEN_DATA *    pplex_InputLookAhead(
        PPLEX_DATA      *this,
        uint16_t        num
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @param     this    PPLEX Object Pointer
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *    pplex_ToDebugString(
        PPLEX_DATA     *this,
        int            indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PPLEX_H */

