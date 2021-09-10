// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Lex.c
 *  Generated 05/28/2020 16:45:58
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
#include        <Lex_internal.h>
#include        <ascii.h>
#include        <dec.h>
#include        <SrcErrors.h>
#include        <trace.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    typedef struct xlate_entry_s {
        int32_t     value;                    /* Lexical Scan Value */
        char        kwd[32];                  /* Key Word */
    } XLATE_ENTRY;

    static
    XLATE_ENTRY   xlateTbl[] = {
        { LEX_GROUP_ALPHA_LOWER, "LEX_GROUP_ALPHA_LOWER"},
        { LEX_GROUP_ALPHA_UPPER, "LEX_GROUP_ALPHA_UPPER"},
        { LEX_GROUP_DELETE, "LEX_GROUP_DELETE"},
        { LEX_GROUP_NUMBER, "LEX_GROUP_NUMBER"},
        { LEX_GROUP_EOL, "LEX_GROUP_EOL"},
        { LEX_GROUP_WHITESPACE, "LEX_GROUP_WHITESPACE"},
        { LEX_GROUP_UNICODE, "LEX_GROUP_UNICODE"},
        { LEX_COMMENT_SINGLE, "LEX_COMMENT_SINGLE"},
        { LEX_COMMENT_MULTI, "LEX_COMMENT_MULTI"},
        { LEX_CONSTANT_CHAR,    "LEX_CONSTANT_CHAR" },
        { LEX_CONSTANT_CHAR_WIDE,    "LEX_CONSTANT_CHAR_WIDE" },
        { LEX_CONSTANT_FLOAT,    "LEX_CONSTANT_FLOAT" },
        { LEX_CONSTANT_INTEGER,    "LEX_CONSTANT_INTEGER" },
        { LEX_CONSTANT_STRING,    "LEX_CONSTANT_STRING" },
        { LEX_CONSTANT_STRING_WIDE,    "LEX_CONSTANT_STRING_WIDE" },
        { LEX_CONSTANT_TEXT,    "LEX_CONSTANT_TEXT" },
        { LEX_IDENTIFIER,    "LEX_IDENTIFIER" },
        { LEX_KWD_ASM,    "LEX_KWD_ASM" },
        { LEX_KWD_ASSIGN,    "LEX_KWD_ASSIGN" },
        { LEX_KWD_AT_AUTO,    "LEX_KWD_AT_AUTO" },
        { LEX_KWD_AT_CATCH,    "LEX_KWD_AT_CATCH" },
        { LEX_KWD_AT_CLASS,    "LEX_KWD_AT_CLASS" },
        { LEX_KWD_AT_DYNAMIC,    "LEX_KWD_AT_DYNAMIC" },
        { LEX_KWD_AT_ENCODE,    "LEX_KWD_AT_ENCODE" },
        { LEX_KWD_AT_END,    "LEX_KWD_AT_END" },
        { LEX_KWD_AT_FINALLY,    "LEX_KWD_AT_FINALLY" },
        { LEX_KWD_AT_IMPLEMENTATION,    "LEX_KWD_AT_IMPLEMENTATION" },
        { LEX_KWD_AT_INTERFACE,    "LEX_KWD_AT_INTERFACE" },
        { LEX_KWD_AT_OPTIONAL,    "LEX_KWD_AT_OPTIONAL" },
        { LEX_KWD_AT_PKG,    "LEX_KWD_AT_PKG" },
        { LEX_KWD_AT_PRIVATE,    "LEX_KWD_AT_PRIVATE" },
        { LEX_KWD_AT_PROPERTY,    "LEX_KWD_AT_PROPERTY" },
        { LEX_KWD_AT_PROTECTED,    "LEX_KWD_AT_PROTECTED" },
        { LEX_KWD_AT_PROTOCOL,    "LEX_KWD_AT_PROTOCOL" },
        { LEX_KWD_AT_PUBLIC,    "LEX_KWD_AT_PUBLIC" },
        { LEX_KWD_AT_SEL,    "LEX_KWD_AT_SEL" },
        { LEX_KWD_AT_SYNC,    "LEX_KWD_AT_SYNC" },
        { LEX_KWD_AT_SYNTH,    "LEX_KWD_AT_SYNTH" },
        { LEX_KWD_AT_THROW,    "LEX_KWD_AT_THROW" },
        { LEX_KWD_AT_TRY,    "LEX_KWD_AT_TRY" },
        { LEX_KWD_AUTO,    "LEX_KWD_AUTO" },
        { LEX_KWD_BOOL,    "LEX_KWD_BOOL" },
        { LEX_KWD_BREAK,    "LEX_KWD_BREAK" },
        { LEX_KWD_BYCOPY,    "LEX_KWD_BYCOPY" },
        { LEX_KWD_BYREF,    "LEX_KWD_BYREF" },
        { LEX_KWD_CASE,    "LEX_KWD_CASE" },
        { LEX_KWD_CDECL,    "LEX_KWD_CDECL" },
        { LEX_KWD_CHAR,    "LEX_KWD_CHAR" },
        { LEX_KWD_CLASS,    "LEX_KWD_CLASS" },
        { LEX_KWD_CONST,    "LEX_KWD_CONST" },
        { LEX_KWD_CONTINUE,    "LEX_KWD_CONTINUE" },
        { LEX_KWD_DEFAULT,    "LEX_KWD_DEFAULT" },
        { LEX_KWD_DELETE,    "LEX_KWD_DELETE" },
        { LEX_KWD_DO,    "LEX_KWD_DO" },
        { LEX_KWD_DOUBLE,    "LEX_KWD_DOUBLE" },
        { LEX_KWD_ELSE,    "LEX_KWD_ELSE" },
        { LEX_KWD_EMIT,    "LEX_KWD_EMIT" },
        { LEX_KWD_END,    "LEX_KWD_END" },
        { LEX_KWD_ENTRY,    "LEX_KWD_ENTRY" },
        { LEX_KWD_ENUM,    "LEX_KWD_ENUM" },
        { LEX_KWD_EXTERN,    "LEX_KWD_EXTERN" },
        { LEX_KWD_FAR,    "LEX_KWD_FAR" },
        { LEX_KWD_FLOAT,    "LEX_KWD_FLOAT" },
        { LEX_KWD_FOR,    "LEX_KWD_FOR" },
        { LEX_KWD_FORTRAN,    "LEX_KWD_FORTRAN" },
        { LEX_KWD_FRIEND,    "LEX_KWD_FRIEND" },
        { LEX_KWD_GETTER,    "LEX_KWD_GETTER" },
        { LEX_KWD_GOAL,    "LEX_KWD_GOAL" },
        { LEX_KWD_GOTO,    "LEX_KWD_GOTO" },
        { LEX_KWD_ID,    "LEX_KWD_ID" },
        { LEX_KWD_IF,    "LEX_KWD_IF" },
        { LEX_KWD_IN,    "LEX_KWD_IN" },
        { LEX_KWD_INOUT,    "LEX_KWD_INOUT" },
        { LEX_KWD_INT,    "LEX_KWD_INT" },
        { LEX_KWD_INT8,    "LEX_KWD_INT8" },
        { LEX_KWD_INT16,    "LEX_KWD_INT16" },
        { LEX_KWD_INT32,    "LEX_KWD_INT32" },
        { LEX_KWD_INT64,    "LEX_KWD_INT64" },
        { LEX_KWD_INT128,    "LEX_KWD_INT128" },
        { LEX_KWD_INT256,    "LEX_KWD_INT256" },
        { LEX_KWD_INTERNAL,    "LEX_KWD_INTERNAL" },
        { LEX_KWD_LONG,    "LEX_KWD_LONG" },
        { LEX_KWD_NEAR,    "LEX_KWD_NEAR" },
        { LEX_KWD_NEW,    "LEX_KWD_NEW" },
        { LEX_KWD_NONATOMIC,    "LEX_KWD_NONATOMIC" },
        { LEX_KWD_OFFSETOF,    "LEX_KWD_OFFSETOF" },
        { LEX_KWD_ONEWAY,    "LEX_KWD_ONEWAY" },
        { LEX_KWD_OPERATOR,    "LEX_KWD_OPERATOR" },
        { LEX_KWD_OUT,    "LEX_KWD_OUT" },
        { LEX_KWD_OVERLOAD,    "LEX_KWD_OVERLOAD" },
        { LEX_KWD_PASCAL,    "LEX_KWD_PASCAL" },
        { LEX_KWD_PUBLIC,    "LEX_KWD_PUBLIC" },
        { LEX_KWD_READONLY,    "LEX_KWD_READONLY" },
        { LEX_KWD_READWRITE,    "LEX_KWD_READWRITE" },
        { LEX_KWD_REGISTER,    "LEX_KWD_REGISTER" },
        { LEX_KWD_RETAIN,    "LEX_KWD_RETAIN" },
        { LEX_KWD_RETURN,    "LEX_KWD_RETURN" },
        { LEX_KWD_SELECT,    "LEX_KWD_SELECT" },
        { LEX_KWD_SELF,    "LEX_KWD_SELF" },
        { LEX_KWD_SETTER,    "LEX_KWD_SETTER" },
        { LEX_KWD_SHORT,    "LEX_KWD_SHORT" },
        { LEX_KWD_SIGNED,    "LEX_KWD_SIGNED" },
        { LEX_KWD_SIZEOF,    "LEX_KWD_SIZEOF" },
        { LEX_KWD_STATIC,    "LEX_KWD_STATIC" },
        { LEX_KWD_STRONG,    "LEX_KWD_STRONG" },
        { LEX_KWD_STRUCT,    "LEX_KWD_STRUCT" },
        { LEX_KWD_SUPER,    "LEX_KWD_SUPER" },
        { LEX_KWD_SWITCH,    "LEX_KWD_SWITCH" },
        { LEX_KWD_TERM,    "LEX_KWD_TERM" },
        { LEX_KWD_THIS,    "LEX_KWD_THIS" },
        { LEX_KWD_TYPEDEF,    "LEX_KWD_TYPEDEF" },
        { LEX_KWD_UINT8,    "LEX_KWD_UINT8" },
        { LEX_KWD_UINT16,    "LEX_KWD_UINT16" },
        { LEX_KWD_UINT32,    "LEX_KWD_UINT32" },
        { LEX_KWD_UINT64,    "LEX_KWD_UINT64" },
        { LEX_KWD_UINT128,    "LEX_KWD_UINT128" },
        { LEX_KWD_UINT256,    "LEX_KWD_UINT256" },
        { LEX_KWD_UNION,    "LEX_KWD_UNION" },
        { LEX_KWD_UNSIGNED,    "LEX_KWD_UNSIGNED" },
        { LEX_KWD_VIRTUAL,    "LEX_KWD_VIRTUAL" },
        { LEX_KWD_VOID,    "LEX_KWD_VOID" },
        { LEX_KWD_VOLATILE,    "LEX_KWD_VOLATILE" },
        { LEX_KWD_WEAK,    "LEX_KWD_WEAK" },
        { LEX_KWD_WHILE,    "LEX_KWD_WHILE" },
        { LEX_OP_ADD,    "LEX_OP_ADD" },
        { LEX_OP_ADDR,    "LEX_OP_ADDR" },
        { LEX_OP_AND,    "LEX_OP_AND" },
        { LEX_OP_ASSIGN,    "LEX_OP_ASSIGN" },
        { LEX_OP_ASSIGN_ADD,    "LEX_OP_ASSIGN_ADD" },
        { LEX_OP_ASSIGN_AND,    "LEX_OP_ASSIGN_AND" },
        { LEX_OP_ASSIGN_DIV,    "LEX_OP_ASSIGN_DIV" },
        { LEX_OP_ASSIGN_LEFT,    "LEX_OP_ASSIGN_LEFT" },
        { LEX_OP_ASSIGN_MUL,    "LEX_OP_ASSIGN_MUL" },
        { LEX_OP_ASSIGN_MOD,    "LEX_OP_ASSIGN_MOD" },
        { LEX_OP_ASSIGN_OR,    "LEX_OP_ASSIGN_OR" },
        { LEX_OP_ASSIGN_RIGHT,    "LEX_OP_ASSIGN_RIGHT" },
        { LEX_OP_ASSIGN_SUB,    "LEX_OP_ASSIGN_SUB" },
        { LEX_OP_ASSIGN_XOR,    "LEX_OP_ASSIGN_XOR" },
        { LEX_OP_COLON,    "LEX_OP_COLON" },
        { LEX_OP_DEC,    "LEX_OP_DEC" },
        { LEX_OP_DIV,    "LEX_OP_DIV" },
        { LEX_OP_ELIPSIS,    "LEX_OP_ELIPSIS" },
        { LEX_OP_EQ,    "LEX_OP_EQ" },
        { LEX_OP_GE,    "LEX_OP_GE" },
        { LEX_OP_GT,    "LEX_OP_GT" },
        { LEX_OP_INC,    "LEX_OP_INC" },
        { LEX_OP_LE,    "LEX_OP_LE" },
        { LEX_OP_LOG_AND,    "LEX_OP_LOG_AND" },
        { LEX_OP_LOG_NOT,    "LEX_OP_LOG_NOT" },
        { LEX_OP_LOG_OR,    "LEX_OP_LOG_OR" },
        { LEX_OP_LEFT,    "LEX_OP_LEFT" },
        { LEX_OP_LT,    "LEX_OP_LT" },
        { LEX_OP_MOD,    "LEX_OP_MOD" },
        { LEX_OP_MUL,    "LEX_OP_MUL" },
        { LEX_OP_NE,    "LEX_OP_NE" },
        { LEX_OP_NEG,    "LEX_OP_NEG" },
        { LEX_OP_NOT,    "LEX_OP_NOT" },
        { LEX_OP_OR,    "LEX_OP_OR" },
        { LEX_OP_POUND,    "LEX_OP_POUND" },
        { LEX_OP_2POUNDS,    "LEX_OP_2POUNDS" },
        { LEX_OP_PTR,    "LEX_OP_PTR" },
        { LEX_OP_QUESTION,    "LEX_OP_QUESTION" },
        { LEX_OP_RANGE,    "LEX_OP_RANGE" },
        { LEX_OP_RIGHT,    "LEX_OP_RIGHT" },
        { LEX_OP_SUB,    "LEX_OP_SUB" },
        { LEX_OP_XOR,    "LEX_OP_XOR" },
        { LEX_SEP_AT,    "LEX_SEP_AT=700" },
        { LEX_SEP_COMMA,    "LEX_SEP_COMMA" },
        { LEX_SEP_DOT,    "LEX_SEP_DOT" },
        { LEX_SEP_LBRACK,    "LEX_SEP_LBRACK" },
        { LEX_SEP_LBRACE,    "LEX_SEP_LBRACE" },
        { LEX_SEP_LPAREN,    "LEX_SEP_LPAREN" },
        { LEX_SEP_NL,    "LEX_SEP_NL" },
        { LEX_SEP_RARROW,    "LEX_SEP_RARROW" },
        { LEX_SEP_RBRACK,    "LEX_SEP_RBRACK" },
        { LEX_SEP_RBRACE,    "LEX_SEP_RBRACE" },
        { LEX_SEP_RPAREN,    "LEX_SEP_RPAREN" },
        { LEX_SEP_SEMICOLON,    "LEX_SEP_SEMICOLON" },
        { LEX_SPCL_AT_LBRACK,    "LEX_SPCL_AT_LBRACK" },
        { LEX_SPCL_AT_LBRACE,    "LEX_SPCL_AT_LBRACE" },
        { LEX_SPCL_AT_LPAREN,    "LEX_SPCL_AT_LPAREN" },
        { LEX_SPCL_DBLCOLON,    "LEX_SPCL_DBLCOLON" },
        { LEX_SPCL_LBRACK,    "LEX_SPCL_LBRACK" },
        { LEX_SPCL_LBRACE,    "LEX_SPCL_LBRACE" },
        { LEX_SPCL_RARROW,    "LEX_SPCL_RARROW" },
        { LEX_SPCL_RBRACK,    "LEX_SPCL_RBRACK" },
        { LEX_SPCL_RBRACE,    "LEX_SPCL_RBRACE" },
        { LEX_SPCL_SEPARATOR,    "LEX_SPCL_SEPARATOR" },
        { LEX_TYPE_METHOD,    "LEX_TYPE_METHOD" },
        { LEX_TYPE_NAME,    "LEX_TYPE_NAME" },
    };

    static
    int         cXlateTbl = sizeof(xlateTbl)/sizeof(XLATE_ENTRY);




 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    TOKEN_DATA *    Lex_DefaultAdvance(
        LEX_DATA        *this,
        uint16_t        numChrs
    )
    {

        // Do initialization.

        Token_Init(&this->token);
        Token_SetupCharW32(&this->token, NULL, LEX_CLASS_EOF, -1);

        // Return to caller.
        return &this->token;
    }



    TOKEN_DATA *    Lex_DefaultLookAhead(
        LEX_DATA        *this,
        uint16_t        numChrs
    )
    {

        // Do initialization.

        Token_Init(&this->token);
        Token_SetupCharW32(&this->token, NULL, LEX_CLASS_EOF, -1);

        // Return to caller.
        return &this->token;
    }



    //---------------------------------------------------------------
    //                      N e x t  I n p u t
    //---------------------------------------------------------------

    bool            Lex_NextAccept(
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData,
        bool            fAppend
    )
    {
        bool            fRc;

        // Do initialization.

        TRC_OBJ(
                this,
                "\tNextAccept char: (0%02Xx) '%lc'\n",
                pData->chr2,
                pData->chr2
        );
        if (fAppend) {
            Lex_TokenAppendStringW32(this, pData->chr2);
        }
#ifdef NDEBUG
#else
        {
            char       *pStrA = W32Str_CStringA(this->pStr, NULL);
            TRC_OBJ(
                    this,
                    "\t\tString: \"%s\"\n",
                    pStrA
            );
            mem_Free(pStrA);
        }
#endif
        fRc = Lex_NextInput(this, pData, false);

        // Return to caller.
        return fRc;
    }



    /*!
     Advance to the next input token and get the lookahead just beyond it.
     */
    bool            Lex_NextInput(
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData,
        bool            fSetupToken
    )
    {
        ERESULT         eRc;
        TOKEN_DATA      *pToken = OBJ_NIL;

#ifdef NDEBUG
#else
        if( !Lex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        // The first char becomes the foundation for the
        // output token.
        pToken = Lex_InputLookAhead(this, 1);
        if (OBJ_NIL == pToken) {
            pToken = Lex_SetupTokenEOF(this);
            DEBUG_BREAK();
        }
        eRc = Token_Assign(pToken, &pData->token1);
        pData->cls1 = Token_getClass(pToken);
        pData->chr1 = Token_getChrW32(pToken);
        if (fSetupToken) {
            eRc = Lex_ParseTokenSetup(this, pToken);
        }
        Lex_InputAdvance(this, 1);
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "\tToken1: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
#endif

        // Now grab a second token for lookahead purposes.
        pToken = Lex_InputLookAhead(this, 1);
        if (pToken)
            ;
        else {
            pToken = Lex_SetupTokenEOF(this);
            DEBUG_BREAK();          // This should never happen!
        }
        eRc = Token_Assign(pToken, &pData->token2);
        pData->cls2 = Token_getClass(pToken);
        pData->chr2 = Token_getChrW32(pToken);
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "\tToken2: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
#endif

        return true;
    }



    ERESULT         Lex_DefaultParser(
        OBJ_ID          pObj
    )
    {
        LEX_DATA        *this = pObj;
        ERESULT         eRc;
        bool            fRc;
        TOKEN_DATA      *pToken = OBJ_NIL;
        LEX_PARSE_DATA  data = {0};
        bool            fMore = true;
        int             iRc;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Lex_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        TRC_OBJ(this, "Lex_DefaultParser:\n");
    try_again:
        data.pOutput = Lex_getToken(this);
        data.pStr = this->pStr;
        data.clsNew = LEX_CLASS_UNKNOWN;
        data.fFinalize = true;
        data.fSavStr = true;
        Token_Init(&data.token1);
        Token_Init(&data.token2);

        // Note: Lex_NextInput() only returns the token type,
        //      TOKEN_TYPE_W32CHAR, in both the advanced and
        //      lookahead tokens.
    while_more:
        while (fMore) {
            fRc = Lex_NextInput(this, &data, true);
            data.clsNew = data.cls1;
            if (data.cls1 == EOF) {
                data.fSavStr = false;
                data.clsNew = LEX_CLASS_EOF;
                break;
            }

            /*
             This exit allows the entire lexical scan to be over-ridden.
             The exist can call:
                    Lex_TokenAppendStringW32(this, data.chr2);
                    fRc = Lex_NextInput(this, &data, false);
             as needed to do its own scan if desired. It should return:
                0 == Accept what exit scanned
                1 == Skip to next input token and continue scan.
                2 == Continue with default scanner.

             */
            if (this->pParserPreExit) {
                int         iRc;
                iRc =   this->pParserPreExit(
                                        this->pParserPreExitObj,
                                        this,
                                        &data
                        );
                if (0 == iRc) {
                    fMore = false;          // Accept scan.
                    continue;
                } else if (1 == iRc) {
                    continue;               // Skip to next character.
                }
            }


            /* Note: If we are looking for a 1 char token,
                    we can simply return. If it is a 2 char
                    token, we must advance the input 1 char
                    and then return. We can advance directly
                    without using Lex_NextInput(). If the
                    token will be greater than 2 chars then,
                    We use Lex_NextInput() to advance until
                    we get to the last char of that token
                    in the lookahead, then we advance directly
                    on the last char.
             */
            switch (data.cls1) {

                case ASCII_LEXICAL_WHITESPACE:
                    if (this->flags & LEX_FLAG_WS) {
                        if ('\n' ==  data.chr1) {
                            data.clsNew = LEX_SEP_NL;
                            fMore = false;
                            break;
                        }
                        Lex_ParseWhiteSpace(this, &data);
                        data.clsNew = LEX_SEP_WS;
                        fMore = false;
                        for (;;) {
                            if (data.chr2 == '\n') {
                                if (this->flags & LEX_FLAG_WS) {
                                    Lex_TokenAppendStringW32(this, data.chr2);
                                }
                                break;
                            }
                            if (data.cls2 == ASCII_LEXICAL_WHITESPACE) {
                                if (this->flags & LEX_FLAG_WS) {
                                    Lex_TokenAppendStringW32(this, data.chr2);
                                }
                            }
                            else
                                break;
                            fRc = Lex_NextInput(this, &data, false);
                        }
                    }
                    break;

                case ASCII_LEXICAL_EOL:
                    if (this->flags & LEX_FLAG_NL) {
                        data.clsNew = LEX_SEP_NL;
                        fMore = false;
                    }
                    break;

                case '_':
                case ASCII_LEXICAL_ALPHA_LOWER:
                case ASCII_LEXICAL_ALPHA_UPPER:
                    TRC_OBJ(this, "\tScanning rest of Identifier...\n");
                    // The output token consists of the first token and
                    // the output accumulation string is only the first
                    // token's character.
                    while (ascii_isLabelCharW32(data.chr2)) {
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    }
                    data.clsNew = LEX_IDENTIFIER;
                    fMore = false;
                    break;

                case ASCII_LEXICAL_NUMBER:      // 0-9
                    data.clsNew = Lex_ParseNumber(this, &data);
                    fMore = false;
                    break;

                case '!':           /*** '!' ***/
                    data.clsNew = LEX_OP_NOT;
                    if ('=' == data.chr2) {
                        data.clsNew = LEX_OP_NE;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    }
                    fMore = false;
                    break;

                case '"':           /*** '"' ***/
                    Lex_ParseTokenTruncate(this);
                    fMore = false;
                    data.clsNew = LEX_CONSTANT_STRING;
                    if (data.cls2 == '"') {         // Empty String
                        fRc = Lex_NextInput(this, &data, false);
                    } else {
                        // Token starts with 2nd initial token.
                        while ((iRc = Lex_ParseChrCon(this, &data, '"')) == 1)
                            ;
                        if (iRc == 0) {
                            fRc = Lex_NextInput(this, &data, false);
                        } else {
                            SrcErrors_AddFatalFromTokenA(
                                                         OBJ_NIL,
                                                         pToken,
                                                         "Malformed String constant"
                                                         );
                        }
                    }
                    break;

                case '#':           /*** '#' ***/
                    data.clsNew = LEX_OP_POUND;
                    fMore = false;
                    if ('#' == data.cls2) {
                        data.clsNew = LEX_OP_2POUNDS;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    }
                    break;

                case '%':           /*** '%' ***/
                    data.clsNew = LEX_OP_MOD;
                    fMore = false;
                    if ('=' == data.cls2) {
                        data.clsNew = LEX_OP_ASSIGN_MOD;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    } else if ('%' == data.cls2) {
                        if (this->flags & LEX_FLAG_SPCL_GROUP) {
                            data.clsNew = LEX_SPCL_SEPARATOR;
                            Lex_TokenAppendStringW32(this, data.chr2);
                            fRc = Lex_NextInput(this, &data, false);
                        }
                    }
                    break;

                case '&':           /*** '&' ***/
                    data.clsNew = LEX_OP_AND;
                    fMore = false;
                    if ('&' == data.cls2) {
                        data.clsNew = LEX_OP_LOG_AND;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    } else if ('=' == data.cls2) {
                        data.clsNew = LEX_OP_ASSIGN_AND;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    }
                    break;

                case '(':           /*** '(' ***/
                    data.clsNew = LEX_SEP_LPAREN;
                    fMore = false;
                    if (this->flags & LEX_FLAG_SPCL_GROUP) {
                        if (':' == data.cls2) {
                            data.clsNew = LEX_SPCL_PAREN_LEFT;
                            Lex_TokenAppendStringW32(this, data.chr2);
                            fRc = Lex_NextInput(this, &data, false);
                        }
                    }
                    break;

                case ')':           /*** ')' ***/
                    data.clsNew = LEX_SEP_RPAREN;
                    fMore = false;
                    break;

                case '*':           /*** '*' ***/
                    data.clsNew = LEX_OP_MUL;
                    fMore = false;
                    if ('=' == data.cls2) {
                        data.clsNew = LEX_OP_ASSIGN_MUL;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    }
                    break;

                case '+':           /*** '+' ***/
                    data.clsNew = LEX_OP_ADD;
                    fMore = false;
                    if ('+' == data.cls2) {
                        data.clsNew = LEX_OP_INC;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    } else if ('=' == data.cls2) {
                        data.clsNew = LEX_OP_ASSIGN_ADD;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    }
                    break;

                case ',':           /*** ',' ***/
                    data.clsNew = LEX_SEP_COMMA;
                    fMore = false;
                    break;

                case '-':           /*** '-' ***/
                    data.clsNew = LEX_OP_SUB;
                    fMore = false;
                    if ('-' == data.cls2) {
                        data.clsNew = LEX_OP_DEC;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    } else if ('=' == data.cls2) {
                        data.clsNew = LEX_OP_ASSIGN_SUB;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    } else if ('>' == data.cls2) {
                        data.clsNew = LEX_SEP_RARROW;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    }
                    break;

                case '.':           /*** '.' ***/
                    data.clsNew = LEX_SEP_DOT;
                    fMore = false;
                    if ('.' == data.cls2) {
                        data.clsNew = LEX_OP_RANGE;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                        if ('.' == data.cls2) {
                            data.clsNew = LEX_OP_ELIPSIS;
                            Lex_TokenAppendStringW32(this, data.chr2);
                            fRc = Lex_NextInput(this, &data, false);
                        }
                    } else if ('>' == data.cls2) {
                        if (this->flags & LEX_FLAG_SPCL_GROUP) {
                            data.clsNew = LEX_SEP_DOT_GT;
                            Lex_TokenAppendStringW32(this, data.chr2);
                            fRc = Lex_NextInput(this, &data, false);
                        }
                    }
                    break;

                case '/':           /*** '/' ***/
                    data.clsNew = LEX_OP_DIV;
                    fMore = false;
                    if ('=' == data.cls2) {
                        data.clsNew = LEX_OP_ASSIGN_DIV;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    } else if ('/' == data.cls2) {
                        data.clsNew = LEX_COMMENT_SINGLE;
                        if (this->flags & LEX_FLAG_CMT) {
                            Lex_TokenAppendStringW32(this, data.chr2);
                        } else {
                            Lex_ParseTokenTruncate(this);
                        }
                        fRc = Lex_NextInput(this, &data, false);
                        for (;;) {
                            if (data.cls2 == LEX_CLASS_EOF) {
                                SrcErrors_AddFatalFromTokenA(
                                                    OBJ_NIL,
                                                    pToken,
                                                    "Premature EOF in single-line comment"
                                );
                            }
                            if (data.cls2 == ASCII_LEXICAL_EOL) {
                                break;
                            }
                            if (this->flags & LEX_FLAG_CMT) {
                                Lex_TokenAppendStringW32(this, data.chr2);
                            }
                            fRc = Lex_NextInput(this, &data, false);
                        }
                        if (!(this->flags & LEX_FLAG_CMT)) {
                            fMore = true;
                        }
                        break;
                    }
                    else if ('*' == data.cls2) {        // 42 02Ax
                        uint32_t        depth = 1;
                        bool            fMore2 = true;
                        bool            fAppend = !(0 == (this->flags & LEX_FLAG_CMT));
                        data.clsNew = LEX_COMMENT_MULTI;
                        if (!fAppend) {
                            Lex_ParseTokenTruncate(this);
                        }
                        if (fAppend) {
                            Lex_TokenAppendStringW32(this, data.chr2);
                        }
                        fRc = Lex_NextInput(this, &data, false);
                        TRC_OBJ(this, "\tFound /* and accepted, now loop for */...\n");
                        while (fMore2) {
                            switch (data.chr2) {
                                case -1:
                                    SrcErrors_AddFatalFromTokenA(
                                                        OBJ_NIL,
                                                        pToken,
                                                        "Premature EOF in Multi-line comment"
                                    );
                                    fMore2 = false;
                                    break;

                                case '*':
                                    TRC_OBJ(this, "\tFound *, now looking for /...\n");
                                    fRc = Lex_NextAccept(this, &data, fAppend);
                                    if (data.chr2 == '/') {         // 47 02Fx
                                        TRC_OBJ(this, "\tFound / of */, checking depth...\n");
                                        /*
                                        if (this->flags & LEX_FLAG_CMT) {
                                            Lex_TokenAppendStringW32(this, data.chr2);
                                        }
                                        fRc = Lex_NextInput(this, &data, false);
                                         */
                                        --depth;
                                        TRC_OBJ(this, "\t\tdepth: %d\n", depth);
                                        if (0 == depth) {
                                            fMore2 = false;
                                            fRc = Lex_NextAccept(this, &data, fAppend);
                                        }
                                    } else {
                                        TRC_OBJ(this, "\tDid not Find / of */, \n");
                                    }
                                    break;

                                case '/':
                                    TRC_OBJ(this, "\tFound / of /*...\n");
                                    fRc = Lex_NextAccept(this, &data, fAppend);
                                    if (data.chr2 == '*') {         // 42 02Ax
                                        TRC_OBJ(this, "\tFound * of /*...\n");
                                        ++depth;
                                        TRC_OBJ(this, "\t\tdepth: %d\n", depth);
                                    } else {
                                        TRC_OBJ(this, "\tDid not find * of /*...\n");
                                    }
                                    break;

                                default:
                                    fRc = Lex_NextAccept(this, &data, fAppend);
                                    break;
                            }   // switch
                        }   // while
                        if (!(this->flags & LEX_FLAG_CMT)) {
                            fMore = true;
                        }
                    }
                    break;

                case ':':           /*** ':' ***/
                    data.clsNew = LEX_OP_COLON;
                    fMore = false;
                    if (this->flags & LEX_FLAG_SPCL_GROUP) {
                        if (':' == data.cls2) {
                            data.clsNew = LEX_SPCL_DBLCOLON;
                            Lex_TokenAppendStringW32(this, data.chr2);
                            fRc = Lex_NextInput(this, &data, false);
                        } else if (')' == data.cls2) {
                            data.clsNew = LEX_SPCL_PAREN_RIGHT;
                            Lex_TokenAppendStringW32(this, data.chr2);
                            fRc = Lex_NextInput(this, &data, false);
                        } else if ('>' == data.cls2) {
                            data.clsNew = LEX_SPCL_COLON_RIGHT;
                            Lex_TokenAppendStringW32(this, data.chr2);
                            fRc = Lex_NextInput(this, &data, false);
                        }
                    }
                    break;

                case ';':           /*** ';' ***/
                    data.clsNew = LEX_SEP_SEMICOLON;
                    fMore = false;
                    break;

                case '<':           /*** '<' ***/
                    data.clsNew = LEX_OP_LT;
                    fMore = false;
                    switch (data.cls2) {
                        case '<':
                            data.clsNew = LEX_OP_LEFT;
                            Lex_TokenAppendStringW32(this, data.chr2);
                            fRc = Lex_NextInput(this, &data, false);
                            if ('=' == data.cls2) {
                                data.clsNew = LEX_OP_ASSIGN_LEFT;
                                Lex_TokenAppendStringW32(this, data.chr2);
                                fRc = Lex_NextInput(this, &data, false);
                            }
                            break;
                        case '-':
                            if (this->flags & LEX_FLAG_SPCL_GROUP) {
                                data.clsNew = LEX_SEP_LARROW;
                                Lex_TokenAppendStringW32(this, data.chr2);
                                fRc = Lex_NextInput(this, &data, false);
                                break;
                            }
                        case '=':
                            data.clsNew = LEX_OP_LE;
                            Lex_TokenAppendStringW32(this, data.chr2);
                            fRc = Lex_NextInput(this, &data, false);
                            break;
                        case '.':
                            if (this->flags & LEX_FLAG_SPCL_GROUP) {
                                data.clsNew = LEX_SEP_LT_DOT;
                                Lex_TokenAppendStringW32(this, data.chr2);
                                fRc = Lex_NextInput(this, &data, false);
                                break;
                            }
                        case ':':
                            if (this->flags & LEX_FLAG_SPCL_GROUP) {
                                data.clsNew = LEX_SPCL_COLON_LEFT;
                                Lex_TokenAppendStringW32(this, data.chr2);
                                fRc = Lex_NextInput(this, &data, false);
                            }
                            break;
                        default:
                            break;
                    }
                    break;

                case '=':           /*** '=' ***/
                    data.clsNew = LEX_OP_ASSIGN;
                    fMore = false;
                    if ('>' == data.cls2) {
                        if (this->flags & LEX_FLAG_SPCL_GROUP) {
                            data.clsNew = LEX_SPCL_RARROW;
                            Lex_TokenAppendStringW32(this, data.chr2);
                            fRc = Lex_NextInput(this, &data, false);
                            break;
                        }
                    } else if ('=' == data.cls2) {
                        data.clsNew = LEX_OP_EQ;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                        break;
                    }
                    break;

                case '>':           /*** '>' ***/
                    data.clsNew = LEX_OP_GT;
                    fMore = false;
                    if ('>' == data.cls2) {
                        data.clsNew = LEX_OP_RIGHT;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        Lex_NextInput(this, &data, false);
                        if ('=' == data.cls2) {
                            data.clsNew = LEX_OP_ASSIGN_RIGHT;
                            Lex_TokenAppendStringW32(this, data.chr2);
                            fRc = Lex_NextInput(this, &data, false);
                        }
                    } else if ('=' == data.cls2) {
                        data.clsNew = LEX_OP_GE;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    }
                    break;

                case '?':           /*** '?' ***/
                    data.clsNew = LEX_OP_QUESTION;
                    fMore = false;
                    break;

                case '@':           /*** '@' ***/
                    data.clsNew = LEX_SEP_AT;
                    fMore = false;
                    break;

                case '[':           /*** '[' ***/
                    data.clsNew = LEX_SEP_LBRACK;
                    fMore = false;
                    break;

                    /*
                     '\\',                                // 5C - '\'
                     */

                case ']':           /*** ']' ***/
                    data.clsNew = LEX_SEP_RBRACK;
                    fMore = false;
                    break;

                case '^':           /*** '^' ***/
                    data.clsNew = LEX_OP_XOR;
                    fMore = false;
                    if ('=' == data.cls2) {
                        data.clsNew = LEX_OP_ASSIGN_XOR;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    }
                    break;

                    /*
                     '`',                                // 60 - '`'
                     */

                case '{':           /*** '{' ***/
                    data.clsNew = LEX_SEP_LBRACE;
                    fMore = false;
                    break;

                case '|':           /*** '|' ***/
                    data.clsNew = LEX_OP_OR;
                    fMore = false;
                    if ('=' == data.cls2) {
                        data.clsNew = LEX_OP_ASSIGN_OR;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    }
                    else if ('|' == data.cls2) {
                        data.clsNew = LEX_OP_LOG_OR;
                        Lex_TokenAppendStringW32(this, data.chr2);
                        fRc = Lex_NextInput(this, &data, false);
                    }
                    break;

                case '}':           /*** '}' ***/
                    data.clsNew = LEX_SEP_RBRACE;
                    fMore = false;
                    break;

                case '~':           /*** '~' ***/
                    data.clsNew = LEX_OP_NEG;
                    fMore = false;
                    break;

                default:
                    if (this->pParserDfltExit) {
                        int         iRc;
                        iRc =   this->pParserDfltExit(
                                                      this->pParserDfltExitObj,
                                                      this,
                                                      &data
                                                      );
                        switch (iRc) {
                            case 1:             // Reset data and scan next char.
                                goto try_again;
                            case 2:             // Keep data as it is and scan next char.
                                goto while_more;
                            default:            // Accept token as scanned
                                break;
                        }
                    }
                    // We will pass the token out and let the caller
                    // deal with it.
                    fMore = false;
                    break;
            }

        }

        // Set up the output token.
        if (this->pParserPostExit) {
            int         iRc;
            iRc =   this->pParserPostExit(
                                          this->pParserPostExitObj,
                                          this,
                                          &data
                                          );
            switch (iRc) {
                case 1:             // Reset data and scan next char.
                    goto try_again;
                case 2:             // Keep data as it is and scan next char.
                    goto while_more;
                default:            // Accept token as scanned
                    break;
            }
        }
        if (data.fFinalize) {
            eRc = Lex_ParseTokenFinalize(this, data.clsNew, data.fSavStr);
            BREAK_FALSE(ERESULT_OK(eRc));
        }

        // Return to caller.
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Token_ToString(Lex_getToken(this));
            TRC_OBJ(this, "...Lex_DefaultParser token=%s", AStr_getData(pStr));
            obj_Release(pStr);
        }
#endif

        return ERESULT_SUCCESS;
    }





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LEX_DATA *     Lex_Alloc (
        void
    )
    {
        LEX_DATA       *this;
        uint32_t        cbSize = sizeof(LEX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    const
    char *          Lex_ClassToString(
        int32_t         value
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        XLATE_ENTRY     *pEntry;

        if (-1 == value) {
            return "LEX_CLASS_EOF";
        }
        if (0 == value) {
            return "LEX_CLASS_UNKNOWN";
        }
        if ((value > 0) && (value < 256)) {
            return "LEX_CLASS_CHAR";
        }
        iMax = cXlateTbl;
        for (i=0; i<iMax; ++i) {
            pEntry = &xlateTbl[i];
            if (pEntry->value == value ) {
                return pEntry->kwd;
            };
        }

        return  "LEX_CLASS_UNKNOWN";
    }



    LEX_DATA *     Lex_New (
        void
    )
    {
        LEX_DATA       *this;
        
        this = Lex_Alloc( );
        if (this) {
            this = Lex_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  C h e c k  P o i n t
    //---------------------------------------------------------------

    TOKENLIST_DATA * Lex_getCheckPoint (
        LEX_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pCheckPoint;
    }


    bool            Lex_setCheckPoint (
        LEX_DATA        *this,
        TOKENLIST_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pCheckPoint) {
            obj_Release(this->pCheckPoint);
        }
        this->pCheckPoint = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                         E r r o r s
    //---------------------------------------------------------------

    ERESULT_DATA *  Lex_getErrors(
        LEX_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
        }
#endif

        return this->pErrors;
    }


    bool            Lex_setErrors(
        LEX_DATA        *this,
        ERESULT_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
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
    //                         F I F O
    //---------------------------------------------------------------

    TOKENLIST_DATA * Lex_getFIFO (
        LEX_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pFIFO;
    }


    bool            Lex_setFIFO (
        LEX_DATA        *this,
        TOKENLIST_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
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



    //---------------------------------------------------------------
    //                      F l a g s
    //---------------------------------------------------------------

    uint32_t        Lex_getFlags(
        LEX_DATA        *this
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
        }
#endif

        return this->flags;
    }


    bool            Lex_setFlags(
        LEX_DATA        *this,
        uint32_t        value
    )
    {

#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->flags = value;

        return true;
    }



    //---------------------------------------------------------------
    //  A l l o w  M u l t i - b y t e  C h a r  C o n s t a n t s
    //---------------------------------------------------------------

    bool            Lex_getMultiCharConstant (
        LEX_DATA        *this
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
        }
#endif
        return this->flags & LEX_FLAG_MULTICHRCON;
    }


    bool            Lex_setMultiCharConstant (
        LEX_DATA        *this,
        bool            value
    )
    {

#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value)
            this->flags |= LEX_FLAG_MULTICHRCON;
        else
            this->flags &= ~LEX_FLAG_MULTICHRCON;

        return true;
    }



    //---------------------------------------------------------------
    //                      P a r s e r
    //---------------------------------------------------------------

    bool            Lex_setParserFunction(
        LEX_DATA        *this,
        ERESULT         (*pParser)(OBJ_ID),
        OBJ_ID          pParseObj
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pParser = pParser;
        this->pParseObj = pParseObj;

        return true;
    }


    bool            Lex_setParserDfltExit(
        LEX_DATA        *this,
        ERESULT         (*pParser)(OBJ_ID, LEX_DATA *, LEX_PARSE_DATA *),
        OBJ_ID          pParseObj
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pParserDfltExit = pParser;
        this->pParserDfltExitObj = pParseObj;

        return true;
    }


    bool            Lex_setParserPostExit(
        LEX_DATA        *this,
        ERESULT         (*pParser)(OBJ_ID, LEX_DATA *, LEX_PARSE_DATA *),
        OBJ_ID          pParseObj
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pParserPostExit = pParser;
        this->pParserPostExitObj = pParseObj;

        return true;
    }


    bool            Lex_setParserPreExit(
        LEX_DATA        *this,
        ERESULT         (*pParser)(OBJ_ID, LEX_DATA *, LEX_PARSE_DATA *),
        OBJ_ID          pParseObj
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pParserPreExit = pParser;
        this->pParserPreExitObj = pParseObj;

        return true;
    }



    //---------------------------------------------------------------
    //                    S o u r c e  I n p u t
    //---------------------------------------------------------------

    bool            Lex_setSourceInput(
        LEX_DATA        *this,
        TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID,uint16_t),
        TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID,uint16_t),
        OBJ_ID          pSrcObj
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pSrcChrAdvance = pSrcChrAdvance;
        this->pSrcChrLookAhead = pSrcChrLookAhead;
        obj_Retain(pSrcObj);
        if (this->pSrcObj) {
            obj_Release(this->pSrcObj);
        }
        this->pSrcObj = pSrcObj;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Lex_getSize (
        LEX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    W32STR_DATA *   Lex_getStr (
        LEX_DATA        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool            Lex_setStr (
        LEX_DATA        *this,
        W32STR_DATA     *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Lex_getSuperVtbl (
        LEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T o k e n
    //---------------------------------------------------------------

    TOKEN_DATA *    Lex_getToken(
        LEX_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
        }
#endif

        return &this->token;
    }





    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Lex_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another LEX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Lex_Assign (
        LEX_DATA       *this,
        LEX_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Lex_Validate(pOther)) {
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
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //--------------------------------------------------------------
    //                 C h e c k  I n p u t
    //--------------------------------------------------------------

    bool            Lex_CheckInputChr(
        LEX_DATA        *this,
        W32CHR_T        chr
    )
    {
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);

        if (chr == Token_getChrW32(pToken)) {
            return true;
        }

        // Return to caller.
        return false;
    }



    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  C l a s s e s
    //--------------------------------------------------------------

    bool            Lex_CheckInputCls(
        LEX_DATA        *this,
        int32_t         cls
    )
    {
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);

        if(cls == Token_getClass(pToken) ) {
            return true;
        }

        // Return to caller.
        return false;
    }


    bool            Lex_CheckInputClasses(
        LEX_DATA        *this,
        int32_t         *pClasses
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         cls;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj, 1);
        cls = Token_getClass(pToken);

        while (*pClasses) {
            if(cls == *pClasses) {
                return true;
            }
            ++pClasses;
        }

        // Return to caller.
        return false;
    }


    bool            Lex_CheckInputRange(
        LEX_DATA        *this,
        W32CHR_T        chrBeg,
        W32CHR_T        chrEnd
    )
    {
        W32CHR_T        chr;
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);

        chr = Token_getChrW32(pToken);
        if((chr >= chrBeg) && (chr <= chrEnd) ) {
            return true;
        }

        // Return to caller.
        return false;
    }


    bool            Lex_CheckInputSet(
        LEX_DATA        *this,
        W32CHR_T        *pSet
    )
    {
        TOKEN_DATA      *pToken = OBJ_NIL;
        W32CHR_T        chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == pSet) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);

        chr = Token_getChrW32(pToken);
        while (*pSet) {
            if(chr == *pSet) {
                return true;
            }
            ++pSet;
        }

        // Return to caller.
        return false;
    }



    //--------------------------------------------------------------
    //                      C h e c k p o i n t
    //--------------------------------------------------------------

    ERESULT         Lex_Checkpoint(
        LEX_DATA        *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->statuses & LEX_STATUS_CHECKPOINT) {
            DEBUG_BREAK();
            return ERESULT_DATA_ALREADY_EXISTS;
        }
#endif

        if (this->pCheckPoint) {
            TokenList_DeleteAll(this->pCheckPoint);
        }
        else {
            this->pCheckPoint = TokenList_New();
        }
        this->statuses |= LEX_STATUS_CHECKPOINT;

        // Return to caller.
        return ERESULT_SUCCESS;
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
    int             Lex_Compare (
        LEX_DATA        *this,
        LEX_DATA        *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Lex_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Lex      *pCopy = Lex_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEX_DATA *     Lex_Copy (
        LEX_DATA       *this
    )
    {
        LEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef LEX_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Lex_New( );
        if (pOther) {
            eRc = Lex_Assign(this, pOther);
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

    void            Lex_Dealloc (
        OBJ_ID          objId
    )
    {
        LEX_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LEX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Lex_setSourceInput(this, NULL, NULL, OBJ_NIL);
        Lex_setCheckPoint(this, OBJ_NIL);
        Lex_setErrors(this, OBJ_NIL);
        Lex_setFIFO(this, OBJ_NIL);
        Lex_setStr(this, OBJ_NIL);
        if (this->pOutputs) {
            mem_Free(this->pOutputs);
            this->pOutputs = NULL;
        }

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
        Lex      *pDeepCopy = Lex_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEX_DATA *     Lex_DeepyCopy (
        LEX_DATA       *this
    )
    {
        LEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Lex_New( );
        if (pOther) {
            eRc = Lex_Assign(this, pOther);
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
    ERESULT         Lex_Disable (
        LEX_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }



    //--------------------------------------------------------------
    //                       D i s c a r d
    //--------------------------------------------------------------

    ERESULT         Lex_Discard(
        LEX_DATA        *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->statuses & LEX_STATUS_CHECKPOINT) {
            TokenList_DeleteAll(this->pCheckPoint);
            this->statuses &= ~LEX_STATUS_CHECKPOINT;
        }
        else {
            return ERESULT_DATA_ERROR;
        }

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
    ERESULT         Lex_Enable (
        LEX_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    LEX_DATA *   Lex_Init (
        LEX_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LEX_DATA);
        ERESULT         eRc;
        TOKEN_DATA      *pToken;

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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LEX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Lex_Vtbl);

        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

        pToken = Token_Init(&this->token);
        if (OBJ_NIL == pToken) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this->pStr = W32Str_New();
        if (OBJ_NIL == this->pStr) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        eRc = Lex_SetupQueue(this, 4);

        this->pErrors = eResult_Shared();

        Lex_setParserFunction(
                              this,
                              Lex_DefaultParser,
                              this
        );

#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Lex::sizeof(LEX_DATA) = %lu\n", 
                sizeof(LEX_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(LEX_DATA));
#endif

        return this;
    }

     

    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------

    TOKEN_DATA *    Lex_InputAdvance(
        LEX_DATA        *this,
        uint16_t        num
    )
    {
        TOKEN_DATA      *pToken = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pSrcChrAdvance) {
            pToken = this->pSrcChrAdvance(this->pSrcObj, num);
        } else {
            pToken = Lex_DefaultAdvance(this, num);
        }

        // Return to caller.
        return pToken;
    }



    //--------------------------------------------------------------
    //              I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------

    TOKEN_DATA *    Lex_InputLookAhead(
        LEX_DATA        *this,
        uint16_t        num
    )
    {
        TOKEN_DATA      *pToken = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pSrcChrLookAhead) {
            pToken = this->pSrcChrLookAhead(this->pSrcObj, num);
        } else {
            pToken = Lex_DefaultLookAhead(this, num);
        }

        // Return to caller.
        return pToken;
    }



    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Lex_IsEnabled (
        LEX_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  C h r
    //--------------------------------------------------------------

    TOKEN_DATA *    Lex_MatchInputChr(
        LEX_DATA        *this,
        W32CHR_T        chr
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);

        if(chr == Token_getChrW32(pToken) ) {
            scp = Token_Copy(pToken);
            (void)this->pSrcChrAdvance(this->pSrcObj,1);
            return scp;
        }

        // Return to caller.
        return OBJ_NIL;
    }



    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  C l a s s e s
    //--------------------------------------------------------------

    TOKEN_DATA *    Lex_MatchInputCls(
        LEX_DATA        *this,
        int32_t         cls
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);

        if(cls == Token_getClass(pToken) ) {
            scp = Token_Copy(pToken);
            (void)this->pSrcChrAdvance(this->pSrcObj,1);
            return scp;
        }

        // Return to caller.
        return OBJ_NIL;
    }


    TOKEN_DATA *    Lex_MatchInputClasses(
        LEX_DATA        *this,
        int32_t         *pClasses
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        TOKEN_DATA      *pToken;
        int32_t         cls;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);
        cls = Token_getClass(pToken);

        while (*pClasses) {
            if(cls == *pClasses) {
                scp = Token_Copy(pToken);
                (void)this->pSrcChrAdvance(this->pSrcObj,1);
                return scp;
            }
            ++pClasses;
        }

        // Return to caller.
        return OBJ_NIL;
    }



    //--------------------------------------------------------------
    //               M a t c h  I n p u t  R a n g e
    //--------------------------------------------------------------

    TOKEN_DATA *    Lex_MatchInputRange(
        LEX_DATA        *this,
        W32CHR_T        chrBeg,
        W32CHR_T        chrEnd
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        W32CHR_T        chr;
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj, 1);

        chr = Token_getChrW32(pToken);
        if((chr >= chrBeg) && (chr <= chrEnd) ) {
            scp = Token_Copy(pToken);
            (void)this->pSrcChrAdvance(this->pSrcObj,1);
            return scp;
        }

        // Return to caller.
        return OBJ_NIL;
    }



    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  S e t
    //--------------------------------------------------------------

    TOKEN_DATA *    Lex_MatchInputSet(
        LEX_DATA        *this,
        W32CHR_T        *pSet
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        W32CHR_T        chr;
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
        if (NULL == pSet) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        pToken = this->pSrcChrLookAhead(this->pSrcObj,1);

        chr = Token_getChrW32(pToken);
        while (*pSet) {
            if(chr == *pSet) {
                scp = Token_Copy(pToken);
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

    // The first character of the character constant has already been
    // parsed, but not advanced. So, we just keep accumulating the proper
    // letters until there are no more that are acceptable.

    int             Lex_ParseChrCon(
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData,
        W32CHR_T        endingChar
    )
    {
        int             i;
        bool            fRc;

#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (pData->cls2 == LEX_CLASS_EOF) {
            return -1;
        }
        if (pData->chr2 == endingChar) {
            return 0;
        }
        if ((pData->chr2 == '\n') || (pData->chr2 == '\r')
            || (pData->chr2 == '\t') || (pData->chr2 == '\f')) {
            Lex_TokenAppendStringW32(this, '\\');
            switch (pData->chr2) {
                case '\f':
                    Lex_TokenAppendStringW32(this, 'f');
                    break;
                case '\n':
                    Lex_TokenAppendStringW32(this, 'n');
                    break;
                case '\r':
                    Lex_TokenAppendStringW32(this, 'r');
                    break;
                case '\t':
                    Lex_TokenAppendStringW32(this, 't');
                    break;
            }
            fRc = Lex_NextInput(this, pData, false);
            return 1;
        }
        if ( pData->chr2 == '\\') {
            Lex_TokenAppendStringW32(this, pData->chr2);
            fRc = Lex_NextInput(this, pData, false);
            switch (pData->chr2) {

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    for (i=0; i<2; ++i) {
                        if (ascii_isOctalW32(pData->chr2)) {
                            Lex_TokenAppendStringW32(this, pData->chr2);
                            fRc = Lex_NextInput(this, pData, false);
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
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    return true;

                case 'u':
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    for (i=0; i<4; ++i) {
                        if (ascii_isHexW32(pData->chr2)) {
                            Lex_TokenAppendStringW32(this, pData->chr2);
                            fRc = Lex_NextInput(this, pData, false);
                        } else {
                            SrcErrors_AddFatalA(
                                                OBJ_NIL,
                                                &pData->token2.data.src,
                                                "Malformed Unicode Escape Sequence - \\uHH"
                                                );
                            return false;
                        }
                    }
                    break;

                case 'U':
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    for (i=0; i<8; ++i) {
                        if (ascii_isHexW32(pData->chr2)) {
                            Lex_TokenAppendStringW32(this, pData->chr2);
                            fRc = Lex_NextInput(this, pData, false);
                        } else {
                            SrcErrors_AddFatalA(
                                                OBJ_NIL,
                                                &pData->token2.data.src,
                                                "Malformed Unicode Escape Sequence - \\UHHHH"
                                                );
                            return false;
                        }
                    }
                    break;

                case 'x':
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    for (i=0; i<2; ++i) {
                        if (ascii_isHexW32(pData->chr2)) {
                            Lex_TokenAppendStringW32(this, pData->chr2);
                            fRc = Lex_NextInput(this, pData, false);
                        } else {
                            SrcErrors_AddFatalA(
                                                OBJ_NIL,
                                                &pData->token2.data.src,
                                                "Malformed Unicode Escape Sequence - \\xHH"
                            );
                            return false;
                        }
                    }
                    break;

                default:
                    return false;
                    break;
            }
        } else {
            Lex_TokenAppendStringW32(this, pData->chr2);
            fRc = Lex_NextInput(this, pData, false);
        }

        return 1;
    }


    int             Lex_ParseChrConWS(
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData,
        W32CHR_T        ending
    )
    {
        int             i;
        bool            fRc;

#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (pData->cls2 == LEX_CLASS_EOF) {
            return -1;
        }
        if (pData->chr2 == ending) {
            return 0;
        }
        if ((pData->chr2 == '\n') || (pData->chr2 == '\r')
            || (pData->chr2 == '\t') || (pData->chr2 == '\f')) {
            Lex_TokenAppendStringW32(this, '\\');
            switch (pData->chr2) {
                case '\f':
                    Lex_TokenAppendStringW32(this, 'f');
                    break;
                case '\n':
                    Lex_TokenAppendStringW32(this, 'n');
                    break;
                case '\r':
                    Lex_TokenAppendStringW32(this, 'r');
                    break;
                case '\t':
                    Lex_TokenAppendStringW32(this, 't');
                    break;
            }
            fRc = Lex_NextInput(this, pData, false);
            return 1;
        }
        if ( pData->chr2 == '\\') {
            Lex_TokenAppendStringW32(this, pData->chr2);
            fRc = Lex_NextInput(this, pData, false);
            switch (pData->chr2) {

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    for (i=0; i<2; ++i) {
                        if (ascii_isOctalW32(pData->chr2)) {
                            Lex_TokenAppendStringW32(this, pData->chr2);
                            fRc = Lex_NextInput(this, pData, false);
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
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    return true;

                case 'u':
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    for (i=0; i<4; ++i) {
                        if (ascii_isHexW32(pData->chr2)) {
                            Lex_TokenAppendStringW32(this, pData->chr2);
                            fRc = Lex_NextInput(this, pData, false);
                        } else {
                            SrcErrors_AddFatalA(
                                                OBJ_NIL,
                                                &pData->token2.data.src,
                                                "Malformed Unicode Escape Sequence - \\uHH"
                                                );
                            return false;
                        }
                    }
                    break;

                case 'U':
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    for (i=0; i<8; ++i) {
                        if (ascii_isHexW32(pData->chr2)) {
                            Lex_TokenAppendStringW32(this, pData->chr2);
                            fRc = Lex_NextInput(this, pData, false);
                        } else {
                            SrcErrors_AddFatalA(
                                                OBJ_NIL,
                                                &pData->token2.data.src,
                                                "Malformed Unicode Escape Sequence - \\UHHHH"
                                                );
                            return false;
                        }
                    }
                    break;

                case 'x':
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    for (i=0; i<2; ++i) {
                        if (ascii_isHexW32(pData->chr2)) {
                            Lex_TokenAppendStringW32(this, pData->chr2);
                            fRc = Lex_NextInput(this, pData, false);
                        } else {
                            SrcErrors_AddFatalA(
                                                OBJ_NIL,
                                                &pData->token2.data.src,
                                                "Malformed Unicode Escape Sequence - \\xHH"
                            );
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
            Lex_TokenAppendStringW32(this, pData->chr2);
            fRc = Lex_NextInput(this, pData, false);
        }

        return true;
    }



    //---------------------------------------------------------------
    //              P a r s e  I n t e g e r  S u f f i x
    //---------------------------------------------------------------

    /*!
     Look for an integer suffix of [lL][lL]?[uU] | [uU][lL][lL]? on the end
     of an integer parse.
     @return:   integer type as defined by TOKEN_MISC
     */
    uint16_t        Lex_ParseIntegerSuffix(
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData
    )
    {
        int16_t         clsNew = 0;
        bool            fRc;
        W32CHR_T        chr;

#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return clsNew;
        }
#endif

        chr = ascii_toLowerW32(pData->chr2);
        switch (pData->chr2) {
            case 'l':
                clsNew = TOKEN_MISC_SL;
                Lex_TokenAppendStringW32(this, pData->chr2);
                fRc = Lex_NextInput(this, pData, false);
                chr = ascii_toLowerW32(pData->chr2);
                if ('l' == chr) {
                    clsNew = TOKEN_MISC_SLL;
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    chr = ascii_toLowerW32(pData->chr2);
                    if ('u' == chr) {
                        clsNew = TOKEN_MISC_ULL;
                        Lex_TokenAppendStringW32(this, pData->chr2);
                        fRc = Lex_NextInput(this, pData, false);
                    }
                }
                else if ('u' == chr) {
                    clsNew = TOKEN_MISC_UL;
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                }
                break;

            case 'u':
                clsNew = TOKEN_MISC_UI;
                Lex_TokenAppendStringW32(this, pData->chr2);
                fRc = Lex_NextInput(this, pData, false);
                chr = ascii_toLowerW32(pData->chr2);
                if ('l' == chr) {
                    clsNew = TOKEN_MISC_UL;
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    chr = ascii_toLowerW32(pData->chr2);
                    if ('l' == chr) {
                        clsNew = TOKEN_MISC_ULL;
                        Lex_TokenAppendStringW32(this, pData->chr2);
                        fRc = Lex_NextInput(this, pData, false);
                    }
                }
                break;

            default:
                break;
        }

        return clsNew;
    }



    //---------------------------------------------------------------
    //                      P a r s e  N u m b e r
    //---------------------------------------------------------------

    // The first character of the number has already been parsed,
    // appended, and advanced over. So, we can look at it and
    // make decisions based on it.

    // number   : (integer | fixed | floating)
    //          ;
    // integer  : [1-9] [0-9]* suffix?
    //          | '0' [xX] [0-9a-fA-F]*
    //          | '0' [bB] [01]*
    //          | '0' [0-9]*                // Octal
    //          ;
    // suffix   : [lL][lL]?[uU] | [uU][lL][lL]?
    //          ;
    // fixed    : integer '.' [0-9]+
    // float    : fixed exp
    // exp      : ('e' | 'E') ('-' | '+')? [0-9]+
    //          ;


    uint16_t        Lex_ParseNumber(
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData
    )
    {
        bool            fRc = true;
        uint16_t        iRc;

#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return pData->clsNew;
        }
#endif
        switch (pData->chr1) {
            case '0':
                // Must be hex, octal, or bit integer.
                if ((pData->chr2 == 'x') || (pData->chr2 == 'X')) {
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    if (ascii_isHexW32(pData->chr2))
                        ;
                    else {
                        SrcErrors_AddFatalA(
                                            OBJ_NIL,
                                            &pData->token2.data.src,
                                            "Malformed Hexadecimal Integer"
                                            );
                    }
                    while (fRc && ascii_isHexW32(pData->chr2)) {
                        Lex_TokenAppendStringW32(this, pData->chr2);
                        fRc = Lex_NextInput(this, pData, false);
                    }
                    pData->clsNew = LEX_CONSTANT_INTEGER;
                }
                if ((pData->chr2 == 'b') || (pData->chr2 == 'B')) {
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                    if ((pData->chr2 >= '0') && (pData->chr2 <= '1'))
                        ;
                    else {
                        SrcErrors_AddFatalA(
                                            OBJ_NIL,
                                            &pData->token2.data.src,
                                            "Malformed Bit Integer"
                                            );
                    }
                    while (fRc && (pData->chr2 >= '0') && (pData->chr2 <= '1')) {
                        Lex_TokenAppendStringW32(this, pData->chr2);
                        fRc = Lex_NextInput(this, pData, false);
                    }
                    pData->clsNew = LEX_CONSTANT_INTEGER;
                }
                else {
                    while (fRc && ascii_isOctalW32(pData->chr2)) {
                        Lex_TokenAppendStringW32(this, pData->chr2);
                        fRc = Lex_NextInput(this, pData, false);
                    }
                    pData->clsNew = LEX_CONSTANT_INTEGER;
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
                    if (ascii_isNumericW32(pData->chr2)) {
                        Lex_TokenAppendStringW32(this, pData->chr2);
                    }
                    else
                        break;
                    fRc = Lex_NextInput(this, pData, false);
                }
                if ('.' == pData->chr2)
                    ;
                else {
                    iRc = Lex_ParseIntegerSuffix(this, pData);
                    if (iRc) {
                        Token_setMisc(&this->token, iRc);
                    }
                    pData->clsNew = LEX_CONSTANT_INTEGER;
                    return pData->clsNew;
                }
                break;

            default:
                break;
        }

        if (pData->chr2 == '.') {
            Lex_TokenAppendStringW32(this, pData->chr2);
            fRc = Lex_NextInput(this, pData, false);
            if (fRc && ascii_isNumericW32(pData->chr2))
                ;
            else {
                SrcErrors_AddFatalA(
                                    OBJ_NIL,
                                    &pData->token2.data.src,
                                    "Malformed Decimal Value"
                                    );
            }
            for (;;) {
                if (fRc && ascii_isNumericW32(pData->chr2)) {
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                }
                else {
                    break;
                }
            }
            if ((pData->chr2 == 'e') || (pData->chr2 == 'E')) {
                Lex_TokenAppendStringW32(this, pData->chr2);
                fRc = Lex_NextInput(this, pData, false);
                // Need to parse (+ | -) digit+
                if ((pData->chr2 == '+') || (pData->chr2 == '-')) {
                    Lex_TokenAppendStringW32(this, pData->chr2);
                    fRc = Lex_NextInput(this, pData, false);
                }
                if (fRc && ascii_isNumericW32(pData->chr2))
                    ;
                else {
                    SrcErrors_AddFatalA(
                                        OBJ_NIL,
                                        &pData->token2.data.src,
                                        "Malformed Exponent"
                                        );
                }
                for (;;) {
                    if (fRc && ascii_isNumericW32(pData->chr2)) {
                        Lex_TokenAppendStringW32(this, pData->chr2);
                        fRc = Lex_NextInput(this, pData, false);
                    }
                    else {
                        break;
                    }
                }
            }
            pData->clsNew = LEX_CONSTANT_FLOAT;
       }

        return pData->clsNew;
    }



    //--------------------------------------------------------------
    //                      P a r s e  T o k e n
    //--------------------------------------------------------------

    TOKEN_DATA *    Lex_ParseToken(
        LEX_DATA        *this
    )
    {
        //TOKEN_DATA      *pInput;
        ERESULT         eRc;
        //bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pParser) {
            eRc = this->pParser(this->pParseObj);
            if (ERESULT_FAILED(eRc)) {
                return OBJ_NIL;
            }
        } else {
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA           *pStr = Token_ToString(&this->token);
            TRC_OBJ( this, "Lex_ParseToken:  %s \n", AStr_getData(pStr) );
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

    /*!
     Parse white space until eol or non-whitespace character.
     */
    bool            Lex_ParseWhiteSpace(
        LEX_DATA        *this,
        LEX_PARSE_DATA  *pData
    )
    {

#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        for (;;) {
            if ( pData->chr2 == '\n' ) {
                if (this->flags & LEX_FLAG_WS) {
                    Lex_TokenAppendStringW32(this, pData->chr2);
                }
                break;
            }
            if ( pData->cls2 == ASCII_LEXICAL_WHITESPACE ) {
                if (this->flags & LEX_FLAG_WS) {
                    Lex_TokenAppendStringW32(this, pData->chr2);
                }
            }
            else
                break;
            Lex_NextInput(this, pData, false);
        }

        return true;
    }



    //--------------------------------------------------------------
    //              P a r s e  T o k e n  F i n a l i z e
    //--------------------------------------------------------------

    /*!
     Finalize the string being built by the parser creating the token
     to be returned in this->token where it is either one W32CHR_T or
     a character string saved in the global szTbl. This allows the
     token to be copied or used for assign(), but must not be freed.
     @param     this     object pointer
     @param     newClass If non-zero, use this class for the token
                being built.
     @param     fSaveStr
                If true, the string being built by the parse is saved
                into the token being built replacing the original string.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         Lex_ParseTokenFinalize(
        LEX_DATA        *this,
        int32_t         newClass,
        bool            fSaveStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        uint32_t        strToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        Token_setClass(&this->token, newClass);
        if (fSaveStr && this->pStr) {
            uint32_t        strlen = W32Str_getLength(this->pStr);
            if ((strlen == 0) || (strlen > 1)) {
                strToken =  szTbl_StringW32ToToken(
                                     OBJ_NIL,
                                     W32Str_getData(this->pStr)
                            );
                BREAK_ZERO(strToken);
                fRc = Token_setStrToken(&this->token, strToken);
                BREAK_FALSE(fRc);
            } else if (strlen == 1) {
                fRc = Token_setChrW32(&this->token, W32Str_CharGetW32(this->pStr, 1));
                BREAK_FALSE(fRc);
            } else {
                eRc = ERESULT_GENERAL_FAILURE;
            }
        }
        if (this->pStr) {
            W32Str_Truncate(this->pStr, 0);
        }

        // Return to caller.
        return eRc;
    }




    //--------------------------------------------------------------
    //         P a r s e  T o k e n  A p p e n d  S t r i n g
    //--------------------------------------------------------------

    ERESULT         Lex_ParseTokenAppendString(
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
    )
    {
        uint16_t        type;
        W32CHR_T        chr;
        uint32_t        cStrNum = 32;
        char            strNum[32];
        char            *pStrNum = strNum;
        const
        char            *pStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
        if ((OBJ_NIL == pToken) || !obj_IsKindOf(pToken, OBJ_IDENT_TOKEN)) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        type = Token_getType(pToken);
        switch (type) {
            case TOKEN_TYPE_CHAR:
            case TOKEN_TYPE_W32CHAR:
                chr = Token_getChrW32(pToken);
                switch (chr) {
                    case '\b':
                        W32Str_AppendA(this->pStr, "\\b");
                        break;
                    case '\f':
                        W32Str_AppendA(this->pStr, "\\f");
                        break;
                    case '\n':
                        W32Str_AppendA(this->pStr, "\\n");
                        break;
                    case '\r':
                        W32Str_AppendA(this->pStr, "\\r");
                        break;
                    case '\t':
                        W32Str_AppendA(this->pStr, "\\t");
                        break;
                    case '\v':
                        W32Str_AppendA(this->pStr, "\\v");
                        break;
                    default:
                        W32Str_AppendW32(this->pStr, 1, &chr);
                        break;
                }
                break;

            case TOKEN_TYPE_INTEGER:
                strNum[0] = '\0';
                dec_putInt64A(Token_getInteger(pToken), &cStrNum, &pStrNum);
                W32Str_AppendA(this->pStr, strNum);
                break;

            case TOKEN_TYPE_STRTOKEN:
                pStr = szTbl_TokenToString(szTbl_Shared(), Token_getStrToken(pToken));
                W32Str_AppendA(this->pStr, pStr);
                break;

            default:
                DEBUG_BREAK();
                break;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         Lex_TokenAppendStringW32(
        LEX_DATA        *this,
        W32CHR_T        chr
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif

        switch (chr) {
            case '\b':
                W32Str_AppendA(this->pStr, "\\b");
                break;
            case '\f':
                W32Str_AppendA(this->pStr, "\\f");
                break;
            case '\n':
                W32Str_AppendA(this->pStr, "\\n");
                break;
            case '\r':
                W32Str_AppendA(this->pStr, "\\r");
                break;
            case '\t':
                W32Str_AppendA(this->pStr, "\\t");
                break;
            case '\v':
                W32Str_AppendA(this->pStr, "\\v");
                break;
            default:
                W32Str_AppendW32(this->pStr, 1, &chr);
                break;
        }

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
     This sets up this->pStr and this->token.
     @param     this    object pointer
     @param     pInput pointer to a token that is used to define the
                next parsed output token. The string/char within the
                token is used as the first char/string of the new
                parsed token.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_*.
     */
    ERESULT         Lex_ParseTokenSetup(
        LEX_DATA        *this,
        TOKEN_DATA      *pInput
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pStr == OBJ_NIL) {
            this->pStr = W32Str_New();
        } else {
            W32Str_Truncate(this->pStr, 0);
        }

        if (OBJ_NIL == pInput) {
            DEBUG_BREAK();
            Lex_SetupTokenEOF(this);
            return ERESULT_EOF_ERROR;
        }
        
        eRc = Token_Assign(pInput, &this->token);
        if(ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        eRc = Lex_TokenAppendStringW32(this, Token_getChrW32(pInput));
        if(ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //--------------------------------------------------------------
    //            P a r s e  T o k e n  T r u n c a t e
    //--------------------------------------------------------------

    ERESULT         Lex_ParseTokenTruncate(
        LEX_DATA        *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pStr) {
            W32Str_Truncate(this->pStr, 0);
        }

        // Return to caller.
        return ERESULT_SUCCESS;
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
        void        *pMethod = Lex_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Lex", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Lex_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LEX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(LEX_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Lex_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return Lex_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Lex_Enable;
                        }
                        break;

                    case 'P':
#ifdef  LEX_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Lex_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Lex_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Lex_ToDebugString;
                        }
#ifdef  LEX_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Lex_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Lex_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Lex_ToDebugString)
                    return "ToDebugString";
#ifdef  LEX_JSON_SUPPORT
                if (pData == Lex_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //--------------------------------------------------------------
    //                          R e s t a r t
    //--------------------------------------------------------------

    ERESULT         Lex_Restart(
        LEX_DATA        *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->statuses & LEX_STATUS_CHECKPOINT) {
            TokenList_Prepend(this->pFIFO, this->pCheckPoint);
            TokenList_DeleteAll(this->pCheckPoint);
            this->statuses &= ~LEX_STATUS_CHECKPOINT;
        }
        else {
            return ERESULT_DATA_ERROR;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                S e t u p  T o k e n  Q u e u e
    //---------------------------------------------------------------

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
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint16_t        savedSize;
        TOKEN_DATA      *pOutputs;
        TOKEN_DATA      *pToken;
        uint32_t        i;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (k <= this->sizeOutputs) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        savedSize = this->sizeOutputs;
        pOutputs = this->pOutputs;

        this->sizeOutputs = k;
        this->pOutputs = mem_Calloc(k, sizeof(TOKEN_DATA));
        if (NULL == this->pOutputs) {
            DEBUG_BREAK();
            obj_Release(this);
            return ERESULT_OUT_OF_MEMORY;
        }

        for (i=0; i<this->sizeOutputs; ++i) {
            pToken = &this->pOutputs[i];
            pToken = Token_Init(pToken);
            Token_SetupCharW32(pToken, NULL, 0, 0);
        }
        if (pOutputs && (this->statuses & LEX_STATUS_INIT)) {
            memmove(this->pOutputs, pOutputs, (savedSize * sizeof(TOKEN_DATA)));
        }
        if (pOutputs) {
            mem_Free(pOutputs);
            pOutputs = NULL;
        }

        // Return to caller.
        return eRc;
    }



    //--------------------------------------------------------------
    //                  S e t u p  T o k e n  E O F
    //--------------------------------------------------------------

    TOKEN_DATA *    Lex_SetupTokenEOF(
        LEX_DATA        *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        obj_setSize(&this->token, sizeof(TOKEN_DATA));
        Token_SetupCharW32(
            &this->token,
            NULL,
            -1,
            -1
        );

        // Return to caller.
        return &this->token;
    }



    //--------------------------------------------------------------
    //                  T o k e n  A d v a n c e
    //--------------------------------------------------------------

    TOKEN_DATA *    Lex_TokenAdvance(
        LEX_DATA        *this,
        uint16_t        numTokens
    )
    {
        uint32_t        i;
        uint16_t        idx;
        TOKEN_DATA      *pToken = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
        if ((numTokens - 1) < this->sizeOutputs)
            ;
        else {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        if (this->pFIFO ) {
            idx = TokenList_getSize(this->pFIFO);
            if (idx) {
                while (numTokens && idx) {
                    if (this->statuses & LEX_STATUS_CHECKPOINT) {
                        pToken = TokenList_Head(this->pFIFO);
                        TokenList_Add2Head(this->pCheckPoint, pToken);
                    }
                    TokenList_DeleteHead(this->pFIFO);
                    idx = TokenList_getSize(this->pFIFO);
                    --numTokens;
                }
            }
            if (numTokens > 0) {
            }
            else {
                pToken = TokenList_Head(this->pFIFO);
                if (pToken) {
#ifdef NDEBUG
#else
                    if (obj_Trace(this)) {
                        ASTR_DATA           *pStr = Token_ToDebugString(pToken, 0);
                        TRC_OBJ( this, "Lex_InputAdvance:  %s \n", AStr_getData(pStr) );
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
#endif
                    return pToken;
                }
            }
        }

        if (0 == (this->statuses & LEX_STATUS_INIT)) {
            for (i=0; i<this->sizeOutputs; ++i) {
                Lex_TokenNext(this);
            }
            this->statuses |= LEX_STATUS_INIT;
        }

        // Get the token needed.
        idx = (this->curOutputs + numTokens - 1) % this->sizeOutputs;
        pToken = &this->pOutputs[idx];

        // Shift inputs.
        for (i=0; i<numTokens; ++i) {
            Lex_TokenNext(this);
        }
        //pToken = &this->pOutputs[this->curOutputs];

        // Return to caller.
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA           *pStr = Token_ToDebugString(pToken, 0);
            TRC_OBJ( this, "Lex_InputAdvance:  (%d) %s \n", idx, AStr_getData(pStr) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        return pToken;
    }



    //--------------------------------------------------------------
    //               T o k e n  L o o k  A h e a d
    //--------------------------------------------------------------

    TOKEN_DATA *    Lex_TokenLookAhead(
        LEX_DATA        *this,
        uint16_t        numTokens
    )
    {
        uint16_t        idx;
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pFIFO ) {
            idx = TokenList_getSize(this->pFIFO);
            if (numTokens > idx) {
                numTokens -= idx;
            }
            else {
                pToken = TokenList_Index(this->pFIFO, numTokens);
#ifdef NDEBUG
#else
                if (obj_Trace(this)) {
                    ASTR_DATA           *pStr = Token_ToDebugString(pToken, 0);
                    TRC_OBJ( this, "Lex_InputLookAhead:  %s \n", AStr_getData(pStr) );
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
#endif
                return pToken;
            }
        }

        if (!(this->statuses & LEX_STATUS_INIT)) {
            for (idx=0; idx<this->sizeOutputs; ++idx) {
                Lex_TokenNext(this);
            }
            this->statuses |= LEX_STATUS_INIT;
        }

        idx = (this->curOutputs + numTokens - 1) % this->sizeOutputs;
        pToken = &this->pOutputs[idx];

        // Return to caller.
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA           *pStr = Token_ToString(pToken);
            TRC_OBJ(this, "...Lex_TokenLookAhead:  (%d) %s \n", idx, AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        return pToken;
    }



    //--------------------------------------------------------------
    //                      T o k e n  N e x t
    //--------------------------------------------------------------

    // This method is called when we need to parse a new phrase and
    // save it into the current token.

    ERESULT         Lex_TokenNext(
        LEX_DATA        *this
    )
    {
        TOKEN_DATA      *pToken;
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        //bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pParser) {
            eRc = this->pParser(this->pParseObj);
        }
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        // The lexical parser should have called the parse???
        // methods to build the token and it should now reside
        // in this->token.

        // Add the next token to the queue.
        pToken = &this->pOutputs[this->curOutputs];
        Token_Assign(&this->token, pToken);
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA           *pStr = Token_ToString(pToken);
            TRC_OBJ(this, "...Lex_TokenNext:  (%d) %s", this->curOutputs, AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif

        this->curOutputs = (this->curOutputs + 1) % this->sizeOutputs;
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            TRC_OBJ(this, "\t\tcurOutputs:  %d\n\n", this->curOutputs);
        }
#endif

        // Return to caller.
        return eRc;
    }



    //--------------------------------------------------------------
    //                      T o k e n  P u s h
    //--------------------------------------------------------------

    /*  This routine will save the current character on a queue
     *  where it will be retrieved by NextToken().
     */
    ERESULT         Lex_TokenPush(
        LEX_DATA        *this,
        TOKEN_DATA      *pToken
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pFIFO == OBJ_NIL) {
            this->pFIFO = TokenList_New( );
            if (OBJ_NIL == this->pFIFO) {
                DEBUG_BREAK();
                return ERESULT_INSUFFICIENT_MEMORY;
            }

        }

        TokenList_Add2Tail(this->pFIFO, pToken);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
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
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex_ToDebugString (
        LEX_DATA      *this,
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
        if (!Lex_Validate(this)) {
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
                    Lex_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    bool            Lex_Validate (
        LEX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_LEX))
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


        if (!(obj_getSize(this) >= sizeof(LEX_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


