// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   pplex.c
 *	Generated 09/29/2015 11:29:54
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
#include <pplex_internal.h>
#include <srcFile.h>
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    /*          * * * Key Word Table * * *
     */
    
    
    // A binary search is performed on this table. So, it must
    // be kept sorted by key word.
    static
    PPLEX_KWDTBL_ENTRY   kwdTbl[] = {
        // Upper case keywords would go here!
        { PPLEX_KWD_ASM,            PPLEX_LANG_MSC,	    "_asm" },
        { PPLEX_KWD_CDECL,          PPLEX_LANG_MSC,	    "_cdecl" },
        { PPLEX_KWD_EMIT,           PPLEX_LANG_MSC,	    "_emit" },
        { PPLEX_KWD_ENTRY,          PPLEX_LANG_MSC,	    "_entry" },
        { PPLEX_KWD_FAR,            PPLEX_LANG_MSC,	    "_far" },
        { PPLEX_KWD_FORTRAN,        PPLEX_LANG_MSC,	    "_fortran" },
        { PPLEX_KWD_NEAR,           PPLEX_LANG_MSC,	    "_near" },
        { PPLEX_KWD_PASCAL,         PPLEX_LANG_MSC,	    "_pascal" },
        { PPLEX_KWD_AUTO,           PPLEX_LANG_C,		"auto" },
        { PPLEX_KWD_BREAK,          PPLEX_LANG_C,		"break" },
        { PPLEX_KWD_CASE,           PPLEX_LANG_C,		"case" },
        { PPLEX_KWD_CCW,            PPLEX_LANG_ASM360,  "ccw" },
        { PPLEX_KWD_CHAR,           PPLEX_LANG_C,		"char" },
        { PPLEX_KWD_CLASS,          PPLEX_LANG_CPP,	    "class" },
        { PPLEX_KWD_CNOP,           PPLEX_LANG_ASM360,  "cnop" },
        { PPLEX_KWD_CONST,          PPLEX_LANG_C,       "const" },
        { PPLEX_KWD_CONTINUE,       PPLEX_LANG_C,		"continue" },
        { PPLEX_KWD_COPY,           PPLEX_LANG_ASM360,  "copy" },
        { PPLEX_KWD_CSECT,          PPLEX_LANG_ASM360,  "csect" },
        { PPLEX_KWD_DC,             PPLEX_LANG_ASM,     "dc" },
        { PPLEX_KWD_DEFAULT,        PPLEX_LANG_C,		"default" },
        { PPLEX_KWD_DELETE,         PPLEX_LANG_CPP,	    "delete" },
        { PPLEX_KWD_DO,             PPLEX_LANG_C,		"do" },
        { PPLEX_KWD_DS,             PPLEX_LANG_ASM,     "ds" },
        { PPLEX_KWD_DOUBLE,         PPLEX_LANG_C,		"double" },
        { PPLEX_KWD_DROP,           PPLEX_LANG_ASM360,  "drop" },
        { PPLEX_KWD_DSECT,          PPLEX_LANG_ASM360,  "dsect" },
        { PPLEX_KWD_ELSE,           PPLEX_LANG_C,		"else" },
        {
            PPLEX_KWD_END,
            (PPLEX_LANG_C | PPLEX_LANG_ASM),
            "end"
        },
        { PPLEX_KWD_ENTRY,          PPLEX_LANG_ASM,     "entry" },
        { PPLEX_KWD_ENUM,           PPLEX_LANG_C,		"enum" },
        {
            PPLEX_KWD_EXTERN,
            (PPLEX_LANG_C | PPLEX_LANG_ASM),
            "extern"
        },
        { PPLEX_KWD_EXTRN,          PPLEX_LANG_ASM,     "extrn" },
        { PPLEX_KWD_FLOAT,          PPLEX_LANG_C,		"float" },
        { PPLEX_KWD_FOR,            PPLEX_LANG_C,		"for" },
        { PPLEX_KWD_FRIEND,         PPLEX_LANG_CPP,	    "friend" },
        { PPLEX_KWD_GOAL,           PPLEX_LANG_LL1,	    "goal" },
        { PPLEX_KWD_GOTO,           PPLEX_LANG_C,		"goto" },
        { PPLEX_KWD_IF,             PPLEX_LANG_C,		"if" },
        { PPLEX_KWD_INT,            PPLEX_LANG_C,		"int" },
        { PPLEX_KWD_INT128,         PPLEX_LANG_C,		"int128_t" },
        { PPLEX_KWD_INT16,          PPLEX_LANG_C,		"int16_t" },
        { PPLEX_KWD_INT256,         PPLEX_LANG_C,       "int256_t" },
        { PPLEX_KWD_INT32,          PPLEX_LANG_C,		"int32_t" },
        { PPLEX_KWD_INT64,          PPLEX_LANG_C,		"int64_t" },
        { PPLEX_KWD_INT8,           PPLEX_LANG_C,		"int8_t" },
        { PPLEX_KWD_INTERFACE,      PPLEX_LANG_OOBJ,    "interface" },
        { PPLEX_KWD_INTERNAL,       PPLEX_LANG_LL1,     "internal" },
        { PPLEX_KWD_LONG,           PPLEX_LANG_C,		"long" },
        { PPLEX_KWD_LTORG,          PPLEX_LANG_ASM,     "ltorg" },
        { PPLEX_KWD_NEW,            PPLEX_LANG_CPP,	    "new" },
        { PPLEX_KWD_OPERATOR,       PPLEX_LANG_CPP,	    "operator" },
        { PPLEX_KWD_ORG,            PPLEX_LANG_ASM,     "org" },
        { PPLEX_KWD_OVERLOAD,       PPLEX_LANG_CPP,	    "overload" },
        { PPLEX_KWD_PUBLIC,         PPLEX_LANG_CPP,	    "public" },
        { PPLEX_KWD_REGISTER,       PPLEX_LANG_C,		"register" },
        { PPLEX_KWD_RETURN,         PPLEX_LANG_C,		"return" },
        { PPLEX_KWD_RSECT,          PPLEX_LANG_ASM360,  "rsect" },
        { PPLEX_KWD_SELECT,         PPLEX_LANG_C,		"select" },
        { PPLEX_KWD_SHORT,          PPLEX_LANG_C,		"short" },
        { PPLEX_KWD_SIGNED,         PPLEX_LANG_C,		"signed" },
        { PPLEX_KWD_SIZEOF,         PPLEX_LANG_C,		"sizeof" },
        { PPLEX_KWD_START,          PPLEX_LANG_ASM360,	"start" },
        { PPLEX_KWD_STATIC,         PPLEX_LANG_C,       "static" },
        { PPLEX_KWD_STRUCT,         PPLEX_LANG_C,		"struct" },
        { PPLEX_KWD_SWITCH,         PPLEX_LANG_C,		"switch" },
        { PPLEX_KWD_TERM,           PPLEX_LANG_LL1,	    "term" },
        { PPLEX_KWD_THIS,           PPLEX_LANG_C,		"this" },
        { PPLEX_KWD_TYPEDEF,        PPLEX_LANG_C,		"typedef" },
        { PPLEX_KWD_UINT128,        PPLEX_LANG_C,		"uint128_t" },
        { PPLEX_KWD_UINT16,         PPLEX_LANG_C,		"uint16_t" },
        { PPLEX_KWD_UINT256,        PPLEX_LANG_C,		"uint256_t" },
        { PPLEX_KWD_UINT32,         PPLEX_LANG_C,		"uint32_t" },
        { PPLEX_KWD_UINT64,         PPLEX_LANG_C,		"uint64_t" },
        { PPLEX_KWD_UINT8,          PPLEX_LANG_C,		"uint8_t" },
        { PPLEX_KWD_UNION,          PPLEX_LANG_C,		"union" },
        { PPLEX_KWD_UNSIGNED,       PPLEX_LANG_C,		"unsigned" },
        { PPLEX_KWD_USING,          PPLEX_LANG_ASM360,  "using" },
        { PPLEX_KWD_VIRTUAL,        PPLEX_LANG_CPP,	    "virtual" },
        { PPLEX_KWD_VOID,           PPLEX_LANG_C,		"void" },
        { PPLEX_KWD_VOLATILE,       PPLEX_LANG_C,		"volatile" },
        { PPLEX_KWD_WHILE,          PPLEX_LANG_C,		"while" },
        { PPLEX_KWD_WXTRN,          PPLEX_LANG_ASM,     "wxtrn" },
    };
    
    static
    int         cKwdTbl = sizeof(kwdTbl)/sizeof(PPLEX_KWDTBL_ENTRY);
    
    
   
    
    typedef struct xlate_entry_s {
        int32_t     value;					/* Lexical Scan Value */
        char        *kwd;					/* Key Word */
    } XLATE_ENTRY;
    
    static
    XLATE_ENTRY   xlateTbl[] = {
        { PPLEX_CLASS_EOF,	"PPLEX_CLASS_EOF" },
        { PPLEX_CONSTANT_CHAR,	"PPLEX_CONSTANT_CHAR" },
        { PPLEX_CONSTANT_CHAR_WIDE,	"PPLEX_CONSTANT_CHAR_WIDE" },
        { PPLEX_CONSTANT_FLOAT,	"PPLEX_CONSTANT_FLOAT" },
        { PPLEX_CONSTANT_INTEGER,	"PPLEX_CONSTANT_INTEGER" },
        { PPLEX_CONSTANT_STRING,	"PPLEX_CONSTANT_STRING" },
        { PPLEX_CONSTANT_STRING_WIDE,	"PPLEX_CONSTANT_STRING_WIDE" },
        { PPLEX_CONSTANT_TEXT,	"PPLEX_CONSTANT_TEXT" },
        { PPLEX_IDENTIFIER,	"PPLEX_IDENTIFIER" },
        { PPLEX_KWD_ASM,	"PPLEX_KWD_ASM" },
        { PPLEX_KWD_ASSIGN,	"PPLEX_KWD_ASSIGN" },
        { PPLEX_KWD_AT_AUTO,	"PPLEX_KWD_AT_AUTO" },
        { PPLEX_KWD_AT_CATCH,	"PPLEX_KWD_AT_CATCH" },
        { PPLEX_KWD_AT_CLASS,	"PPLEX_KWD_AT_CLASS" },
        { PPLEX_KWD_AT_DYNAMIC,	"PPLEX_KWD_AT_DYNAMIC" },
        { PPLEX_KWD_AT_ENCODE,	"PPLEX_KWD_AT_ENCODE" },
        { PPLEX_KWD_AT_END,	"PPLEX_KWD_AT_END" },
        { PPLEX_KWD_AT_FINALLY,	"PPLEX_KWD_AT_FINALLY" },
        { PPLEX_KWD_AT_IMPLEMENTATION,	"PPLEX_KWD_AT_IMPLEMENTATION" },
        { PPLEX_KWD_AT_INTERFACE,	"PPLEX_KWD_AT_INTERFACE" },
        { PPLEX_KWD_AT_OPTIONAL,	"PPLEX_KWD_AT_OPTIONAL" },
        { PPLEX_KWD_AT_PKG,	"PPLEX_KWD_AT_PKG" },
        { PPLEX_KWD_AT_PRIVATE,	"PPLEX_KWD_AT_PRIVATE" },
        { PPLEX_KWD_AT_PROPERTY,	"PPLEX_KWD_AT_PROPERTY" },
        { PPLEX_KWD_AT_PROTECTED,	"PPLEX_KWD_AT_PROTECTED" },
        { PPLEX_KWD_AT_PROTOCOL,	"PPLEX_KWD_AT_PROTOCOL" },
        { PPLEX_KWD_AT_PUBLIC,	"PPLEX_KWD_AT_PUBLIC" },
        { PPLEX_KWD_AT_SEL,	"PPLEX_KWD_AT_SEL" },
        { PPLEX_KWD_AT_SYNC,	"PPLEX_KWD_AT_SYNC" },
        { PPLEX_KWD_AT_SYNTH,	"PPLEX_KWD_AT_SYNTH" },
        { PPLEX_KWD_AT_THROW,	"PPLEX_KWD_AT_THROW" },
        { PPLEX_KWD_AT_TRY,	"PPLEX_KWD_AT_TRY" },
        { PPLEX_KWD_AUTO,	"PPLEX_KWD_AUTO" },
        { PPLEX_KWD_BOOL,    "PPLEX_KWD_BOOL" },
        { PPLEX_KWD_BREAK,	"PPLEX_KWD_BREAK" },
        { PPLEX_KWD_BYCOPY,	"PPLEX_KWD_BYCOPY" },
        { PPLEX_KWD_BYREF,	"PPLEX_KWD_BYREF" },
        { PPLEX_KWD_CASE,	"PPLEX_KWD_CASE" },
        { PPLEX_KWD_CDECL,	"PPLEX_KWD_CDECL" },
        { PPLEX_KWD_CHAR,	"PPLEX_KWD_CHAR" },
        { PPLEX_KWD_CLASS,	"PPLEX_KWD_CLASS" },
        { PPLEX_KWD_CONST,	"PPLEX_KWD_CONST" },
        { PPLEX_KWD_CONTINUE,	"PPLEX_KWD_CONTINUE" },
        { PPLEX_KWD_DEFAULT,	"PPLEX_KWD_DEFAULT" },
        { PPLEX_KWD_DELETE,	"PPLEX_KWD_DELETE" },
        { PPLEX_KWD_DO,	"PPLEX_KWD_DO" },
        { PPLEX_KWD_DOUBLE,	"PPLEX_KWD_DOUBLE" },
        { PPLEX_KWD_ELSE,	"PPLEX_KWD_ELSE" },
        { PPLEX_KWD_EMIT,	"PPLEX_KWD_EMIT" },
        { PPLEX_KWD_END,	"PPLEX_KWD_END" },
        { PPLEX_KWD_ENTRY,	"PPLEX_KWD_ENTRY" },
        { PPLEX_KWD_ENUM,	"PPLEX_KWD_ENUM" },
        { PPLEX_KWD_EXTERN,	"PPLEX_KWD_EXTERN" },
        { PPLEX_KWD_FAR,	"PPLEX_KWD_FAR" },
        { PPLEX_KWD_FLOAT,	"PPLEX_KWD_FLOAT" },
        { PPLEX_KWD_FOR,	"PPLEX_KWD_FOR" },
        { PPLEX_KWD_FORTRAN,	"PPLEX_KWD_FORTRAN" },
        { PPLEX_KWD_FRIEND,	"PPLEX_KWD_FRIEND" },
        { PPLEX_KWD_GETTER,	"PPLEX_KWD_GETTER" },
        { PPLEX_KWD_GOAL,	"PPLEX_KWD_GOAL" },
        { PPLEX_KWD_GOTO,	"PPLEX_KWD_GOTO" },
        { PPLEX_KWD_ID,	"PPLEX_KWD_ID" },
        { PPLEX_KWD_IF,	"PPLEX_KWD_IF" },
        { PPLEX_KWD_IN,	"PPLEX_KWD_IN" },
        { PPLEX_KWD_INOUT,	"PPLEX_KWD_INOUT" },
        { PPLEX_KWD_INT,	"PPLEX_KWD_INT" },
        { PPLEX_KWD_INT8,	"PPLEX_KWD_INT8" },
        { PPLEX_KWD_INT16,	"PPLEX_KWD_INT16" },
        { PPLEX_KWD_INT32,	"PPLEX_KWD_INT32" },
        { PPLEX_KWD_INT64,	"PPLEX_KWD_INT64" },
        { PPLEX_KWD_INT128,	"PPLEX_KWD_INT128" },
        { PPLEX_KWD_INT256,	"PPLEX_KWD_INT256" },
        { PPLEX_KWD_INTERNAL,	"PPLEX_KWD_INTERNAL" },
        { PPLEX_KWD_LONG,	"PPLEX_KWD_LONG" },
        { PPLEX_KWD_NEAR,	"PPLEX_KWD_NEAR" },
        { PPLEX_KWD_NEW,	"PPLEX_KWD_NEW" },
        { PPLEX_KWD_NONATOMIC,	"PPLEX_KWD_NONATOMIC" },
        { PPLEX_KWD_OFFSETOF,	"PPLEX_KWD_OFFSETOF" },
        { PPLEX_KWD_ONEWAY,	"PPLEX_KWD_ONEWAY" },
        { PPLEX_KWD_OPERATOR,	"PPLEX_KWD_OPERATOR" },
        { PPLEX_KWD_OUT,	"PPLEX_KWD_OUT" },
        { PPLEX_KWD_OVERLOAD,	"PPLEX_KWD_OVERLOAD" },
        { PPLEX_KWD_PASCAL,	"PPLEX_KWD_PASCAL" },
        { PPLEX_KWD_PUBLIC,	"PPLEX_KWD_PUBLIC" },
        { PPLEX_KWD_READONLY,	"PPLEX_KWD_READONLY" },
        { PPLEX_KWD_READWRITE,	"PPLEX_KWD_READWRITE" },
        { PPLEX_KWD_REGISTER,	"PPLEX_KWD_REGISTER" },
        { PPLEX_KWD_RETAIN,	"PPLEX_KWD_RETAIN" },
        { PPLEX_KWD_RETURN,	"PPLEX_KWD_RETURN" },
        { PPLEX_KWD_SELECT,	"PPLEX_KWD_SELECT" },
        { PPLEX_KWD_SELF,	"PPLEX_KWD_SELF" },
        { PPLEX_KWD_SETTER,	"PPLEX_KWD_SETTER" },
        { PPLEX_KWD_SHORT,	"PPLEX_KWD_SHORT" },
        { PPLEX_KWD_SIGNED,	"PPLEX_KWD_SIGNED" },
        { PPLEX_KWD_SIZEOF,	"PPLEX_KWD_SIZEOF" },
        { PPLEX_KWD_STATIC,	"PPLEX_KWD_STATIC" },
        { PPLEX_KWD_STRONG,	"PPLEX_KWD_STRONG" },
        { PPLEX_KWD_STRUCT,	"PPLEX_KWD_STRUCT" },
        { PPLEX_KWD_SUPER,	"PPLEX_KWD_SUPER" },
        { PPLEX_KWD_SWITCH,	"PPLEX_KWD_SWITCH" },
        { PPLEX_KWD_TERM,	"PPLEX_KWD_TERM" },
        { PPLEX_KWD_THIS,	"PPLEX_KWD_THIS" },
        { PPLEX_KWD_TYPEDEF,	"PPLEX_KWD_TYPEDEF" },
        { PPLEX_KWD_UINT8,	"PPLEX_KWD_UINT8" },
        { PPLEX_KWD_UINT16,	"PPLEX_KWD_UINT16" },
        { PPLEX_KWD_UINT32,	"PPLEX_KWD_UINT32" },
        { PPLEX_KWD_UINT64,	"PPLEX_KWD_UINT64" },
        { PPLEX_KWD_UINT128,	"PPLEX_KWD_UINT128" },
        { PPLEX_KWD_UINT256,	"PPLEX_KWD_UINT256" },
        { PPLEX_KWD_UNION,	"PPLEX_KWD_UNION" },
        { PPLEX_KWD_UNSIGNED,	"PPLEX_KWD_UNSIGNED" },
        { PPLEX_KWD_VIRTUAL,	"PPLEX_KWD_VIRTUAL" },
        { PPLEX_KWD_VOID,	"PPLEX_KWD_VOID" },
        { PPLEX_KWD_VOLATILE,	"PPLEX_KWD_VOLATILE" },
        { PPLEX_KWD_WEAK,	"PPLEX_KWD_WEAK" },
        { PPLEX_KWD_WHILE,	"PPLEX_KWD_WHILE" },
        { PPLEX_OP_ADD,	"PPLEX_OP_ADD" },
        { PPLEX_OP_ADDR,	"PPLEX_OP_ADDR" },
        { PPLEX_OP_AND,	"PPLEX_OP_AND" },
        { PPLEX_OP_ASSIGN,	"PPLEX_OP_ASSIGN" },
        { PPLEX_OP_ASSIGN_ADD,	"PPLEX_OP_ASSIGN_ADD" },
        { PPLEX_OP_ASSIGN_AND,	"PPLEX_OP_ASSIGN_AND" },
        { PPLEX_OP_ASSIGN_DIV,	"PPLEX_OP_ASSIGN_DIV" },
        { PPLEX_OP_ASSIGN_LEFT,	"PPLEX_OP_ASSIGN_LEFT" },
        { PPLEX_OP_ASSIGN_MUL,	"PPLEX_OP_ASSIGN_MUL" },
        { PPLEX_OP_ASSIGN_MOD,	"PPLEX_OP_ASSIGN_MOD" },
        { PPLEX_OP_ASSIGN_OR,	"PPLEX_OP_ASSIGN_OR" },
        { PPLEX_OP_ASSIGN_RIGHT,	"PPLEX_OP_ASSIGN_RIGHT" },
        { PPLEX_OP_ASSIGN_SUB,	"PPLEX_OP_ASSIGN_SUB" },
        { PPLEX_OP_ASSIGN_XOR,	"PPLEX_OP_ASSIGN_XOR" },
        { PPLEX_OP_DEC,	"PPLEX_OP_DEC" },
        { PPLEX_OP_DIV,	"PPLEX_OP_DIV" },
        { PPLEX_OP_ELIPSIS,	"PPLEX_OP_ELIPSIS" },
        { PPLEX_OP_EQ,	"PPLEX_OP_EQ" },
        { PPLEX_OP_GE,	"PPLEX_OP_GE" },
        { PPLEX_OP_GT,	"PPLEX_OP_GT" },
        { PPLEX_OP_INC,	"PPLEX_OP_INC" },
        { PPLEX_OP_LE,	"PPLEX_OP_LE" },
        { PPLEX_OP_LOG_AND,	"PPLEX_OP_LOG_AND" },
        { PPLEX_OP_LOG_NOT,	"PPLEX_OP_LOG_NOT" },
        { PPLEX_OP_LOG_OR,	"PPLEX_OP_LOG_OR" },
        { PPLEX_OP_LEFT,	"PPLEX_OP_LEFT" },
        { PPLEX_OP_LT,	"PPLEX_OP_LT" },
        { PPLEX_OP_MOD,	"PPLEX_OP_MOD" },
        { PPLEX_OP_MUL,	"PPLEX_OP_MUL" },
        { PPLEX_OP_NE,	"PPLEX_OP_NE" },
        { PPLEX_OP_NEG,	"PPLEX_OP_NEG" },
        { PPLEX_OP_NOT,	"PPLEX_OP_NOT" },
        { PPLEX_OP_OR,	"PPLEX_OP_OR" },
        { PPLEX_OP_POUND,	"PPLEX_OP_POUND" },
        { PPLEX_OP_PTR,	"PPLEX_OP_PTR" },
        { PPLEX_OP_QUESTION,	"PPLEX_OP_QUESTION" },
        { PPLEX_OP_RANGE,	"PPLEX_OP_RANGE" },
        { PPLEX_OP_RIGHT,	"PPLEX_OP_RIGHT" },
        { PPLEX_OP_SUB,	"PPLEX_OP_SUB" },
        { PPLEX_OP_XOR,	"PPLEX_OP_XOR" },
        { PPLEX_SEP_AT,	"PPLEX_SEP_AT=700" },
        { PPLEX_SEP_COMMA,	"PPLEX_SEP_COMMA" },
        { PPLEX_SEP_DOT,	"PPLEX_SEP_DOT" },
        { PPLEX_SEP_LBRACKET,	"PPLEX_SEP_LBRACKET" },
        { PPLEX_SEP_LBRACE,	"PPLEX_SEP_LBRACE" },
        { PPLEX_SEP_LPAREN,	"PPLEX_SEP_LPAREN" },
        { PPLEX_SEP_NL,	"PPLEX_SEP_NL" },
        { PPLEX_SEP_RARROW,	"PPLEX_SEP_RARROW" },
        { PPLEX_SEP_RBRACKET,	"PPLEX_SEP_RBRACKET" },
        { PPLEX_SEP_RBRACE,	"PPLEX_SEP_RBRACE" },
        { PPLEX_SEP_RPAREN,	"PPLEX_SEP_RPAREN" },
        { PPLEX_SEP_SEMICOLON,	"PPLEX_SEP_SEMICOLON" },
        { PPLEX_SEP_WHITESPACE,	"PPLEX_SEP_WHITESPACE" },
        { PPLEX_SPCL_AT_LBRACK,	"PPLEX_SPCL_AT_LBRACK" },
        { PPLEX_SPCL_AT_LCURL,	"PPLEX_SPCL_AT_LCURL" },
        { PPLEX_SPCL_AT_LPAREN,	"PPLEX_SPCL_AT_LPAREN" },
        { PPLEX_SPCL_COLON,	"PPLEX_SPCL_COLON" },
        { PPLEX_SPCL_DBLCOLON,	"PPLEX_SPCL_DBLCOLON" },
        { PPLEX_SPCL_LBRACK,	"PPLEX_SPCL_LBRACK" },
        { PPLEX_SPCL_LCURL,	"PPLEX_SPCL_LCURL" },
        { PPLEX_SPCL_POUND,	"PPLEX_SPCL_POUND" },
        { PPLEX_SPCL_2POUNDS,	"PPLEX_SPCL_2POUNDS" },
        { PPLEX_SPCL_QUESTION,	"PPLEX_SPCL_QUESTION" },
        { PPLEX_SPCL_RARROW,	"PPLEX_SPCL_RARROW" },
        { PPLEX_SPCL_RBRACK,	"PPLEX_SPCL_RBRACK" },
        { PPLEX_SPCL_RCURL,	"PPLEX_SPCL_RCURL" },
        { PPLEX_SPCL_SEPARATOR,	"PPLEX_SPCL_SEPARATOR" },
        { PPLEX_TYPE_METHOD,	"PPLEX_TYPE_METHOD" },
        { PPLEX_TYPE_NAME,	"PPLEX_TYPE_NAME" },
    };
    
    static
    int         cXlateTbl = sizeof(xlateTbl)/sizeof(XLATE_ENTRY);
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PPLEX_DATA *     pplex_Alloc(
    )
    {
        PPLEX_DATA       *cbp;
        uint32_t        cbSize = sizeof(PPLEX_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    char *          pplex_ClassToString(
        int32_t         value
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        XLATE_ENTRY     *pEntry;
        
        iMax = cXlateTbl;
        for (i=0; i<iMax; ++i) {
            pEntry = &xlateTbl[i];
            if (pEntry->value == value ) {
                return pEntry->kwd;
            };
        }
        
        return  NULL;
    }
    
    
    
    int32_t         pplex_KWToInt(
        uint16_t        select,
        const
        char            *pValue
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        PPLEX_KWDTBL_ENTRY
                        *pEntry;
        
        iMax = cKwdTbl;
        for (i=0; i<iMax; ++i) {
            pEntry = &kwdTbl[i];
            if (0 == strcmp(pEntry->pKwd, pValue)) {
                return pEntry->value;
            };
        }
        
        return -1;
    }
    
    
    
    PPLEX_DATA *    pplex_New(
        uint16_t        k
    )
    {
        PPLEX_DATA       *cbp;
        
        cbp = pplex_Alloc( );
        if (cbp) {
            cbp = pplex_Init( cbp, k);
        } 
        return( cbp );
    }



    int32_t         pplex_StringToInt(
        const
        char            *pValue
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        XLATE_ENTRY     *pEntry;
        
        iMax = cXlateTbl;
        for (i=0; i<iMax; ++i) {
            pEntry = &xlateTbl[i];
            if (0 == strcmp(pEntry->kwd, pValue)) {
                return pEntry->value;
            };
        }
        
        return -1;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    /*! Any table supplied must be sorted in ascending sequence by
     *  keyword.
     */
    bool            pplex_setAuxKwdTable(
        PPLEX_DATA      *this,
        PPLEX_KWDTBL_ENTRY
                        *pAuxKwds,
        uint32_t        cAuxKwds
    )
    {
        
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pAuxKwds = pAuxKwds;
        this->cAuxKwds = cAuxKwds;
        if (this->pLex3) {
            pplex3_setAuxKwdTable(
                                  (PPLEX3_DATA *)this->pLex3,
                                  this->pAuxKwds,
                                  this->cAuxKwds
            );
        }
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * pplex_getArray(
        PPLEX_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return OBJ_NIL; //this->pArray;
    }
    
    
    bool            pplex_setArray(
        PPLEX_DATA     *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        //if (this->pArray) {
            //obj_Release(this->pArray);
        //}
        //this->pArray = pValue;
        
        return true;
    }
    
    
    
    bool            pplex_setDebug(
        PPLEX_DATA      *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !pplex_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        obj_FlagSet(this, PPLEX_FLAG_DEBUG, fValue);
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          L a n g
    //---------------------------------------------------------------
    
    uint16_t        pplex_getLang(
        PPLEX_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        //return this->priority;
        return 0;
    }

    
    bool            pplex_setLang(
        PPLEX_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !pplex_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        pplex2_setKwdSelection(
                   (PPLEX2_DATA *)this->pLex2,
                   value
       );
        if (this->pLex3) {
            pplex3_setKwdSelection(
                                   (PPLEX3_DATA *)this->pLex3,
                                   value
            );
        }

        this->lang = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //               L e x i c a l  S c a n n e r
    //---------------------------------------------------------------

    LEX_DATA *      pplex_getLex(
        PPLEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (LEX_DATA *)this;
    }


    LEX_DATA *      pplex_getLex3(
        PPLEX_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pLex3;
    }
    
    

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        pplex_getPriority(
        PPLEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            pplex_setPriority(
        PPLEX_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        //this->priority = value;
        
        return true;
    }



    //---------------------------------------------------------------
    //              R e t u r n  N e w  L i n e
    //---------------------------------------------------------------
    
    bool            pplex_getReturnNL(
        PPLEX_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        //return this->priority;
        return (this->fReturnNL ? true : false);
    }
    
    
    bool            pplex_setReturnNL(
        PPLEX_DATA      *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        this->fReturnNL = (fValue ? 1 : 0);
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //              R e t u r n  W h i t e  S p a c e
    //---------------------------------------------------------------
    
    bool            pplex_getReturnWS(
        PPLEX_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        //return this->priority;
        return (this->fReturnWS ? true : false);
    }

    
    bool            pplex_setReturnWS(
        PPLEX_DATA      *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        this->fReturnWS = (fValue ? 1 : 0);
        
        return true;
    }
    
    
    
    uint32_t        pplex_getSize(
        PPLEX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }



    bool            pplex_setSourceFunction(
        PPLEX_DATA      *this,
        TOKEN_DATA *    (*pSrcChrAdvance)(OBJ_ID,uint16_t),
        TOKEN_DATA *    (*pSrcChrLookAhead)(OBJ_ID,uint16_t),
        OBJ_ID          pSrcObj
    )
    {
        bool            fRc;
        
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        fRc =   Lex_setSourceInput(
                        (LEX_DATA *)this,
                        pSrcChrAdvance,
                        pSrcChrLookAhead,
                        pSrcObj
                );
        
        return fRc;
    }
    
    
    
    bool            pplex_setKeywordParseFunction(
        PPLEX_DATA      *this,
        bool            (*pUserExit)(OBJ_ID, TOKEN_DATA *),
        OBJ_ID          pUserObj
    )
    {

#ifdef NDEBUG
#else
        if( !pplex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pKwdUserExit = pUserExit;
        this->pKwdUserObject = pUserObj;
        if (this->pLex3) {
            pplex3_setParseFunction(
                                    (PPLEX3_DATA *)this->pLex3,
                                    this->pKwdUserExit,
                                    this->pKwdUserObject
            );
        }
        
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                 C r e a t e  L e x e r s
    //---------------------------------------------------------------
    
    ERESULT         pplex_CreateLexers(
        PPLEX_DATA      *this,
        bool            fLex1,
        bool            fLex3
    )
    {
        bool            fRc;
        //ERESULT         eRc = ERESULT_SUCCESS;
        
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Create the Lexers.
        if (fLex1) {
            this->pLex1 = (LEX_DATA *)pplex1_New();
            if (OBJ_NIL == this->pLex1) {
                DEBUG_BREAK();
                return ERESULT_FAILURE;
            }
        }
        this->pLex2 = (LEX_DATA *)pplex2_New(this->k);
        if (OBJ_NIL == this->pLex2) {
            DEBUG_BREAK();
            obj_Release(this->pLex1);
            this->pLex1 = OBJ_NIL;
            return ERESULT_FAILURE;
        }
        pplex2_setReturnNL((PPLEX2_DATA *)this->pLex2, this->fReturnNL);
        pplex2_setReturnWS((PPLEX2_DATA *)this->pLex2, this->fReturnWS);
        pplex2_setKwdSelection((PPLEX2_DATA *)this->pLex2, this->lang);
        if (fLex3) {
            this->pLex3 = (LEX_DATA *)pplex3_New(this->k);
            if (OBJ_NIL == this->pLex3) {
                DEBUG_BREAK();
                obj_Release(this->pLex1);
                this->pLex1 = OBJ_NIL;
                obj_Release(this->pLex2);
                this->pLex2 = OBJ_NIL;
                return ERESULT_FAILURE;
            }
            pplex3_setKwdSelection((PPLEX3_DATA *)this->pLex3, this->lang);
            pplex3_setAuxKwdTable(
                            (PPLEX3_DATA *)this->pLex3,
                            this->pAuxKwds,
                            this->cAuxKwds
            );
            pplex3_setParseFunction(
                            (PPLEX3_DATA *)this->pLex3,
                            this->pKwdUserExit,
                            this->pKwdUserObject
            );
        }
        
        if (obj_Trace(this)) {
            if (this->pLex1) {
                obj_TraceSet(this->pLex1, true);
            }
            if (this->pLex2) {
                obj_TraceSet(this->pLex2, true);
            }
            if (this->pLex3) {
                obj_TraceSet(this->pLex3, true);
            }
        }

        // Now chain them together using their source methods.
        if (this->pLex3 && this->pLex2) {
            fRc =   Lex_setSourceInput(
                        this->pLex3,
                        (void *)Lex_TokenAdvance,
                        (void *)Lex_TokenLookAhead,
                        this->pLex2
                    );
            if (!fRc) {
                DEBUG_BREAK();
                obj_Release(this->pLex1);
                this->pLex1 = OBJ_NIL;
                obj_Release(this->pLex2);
                this->pLex2 = OBJ_NIL;
                obj_Release(this->pLex3);
                this->pLex3 = OBJ_NIL;
                return ERESULT_FAILURE;
            }
            fRc =   Lex_setSourceInput(
                        (LEX_DATA *)this,
                        (void *)Lex_TokenAdvance,
                        (void *)Lex_TokenLookAhead,
                        this->pLex3
                    );
            if (!fRc) {
                DEBUG_BREAK();
                this->pLex1 = OBJ_NIL;
                obj_Release(this->pLex2);
                this->pLex2 = OBJ_NIL;
                obj_Release(this->pLex3);
                this->pLex3 = OBJ_NIL;
                return ERESULT_FAILURE;
            }
        }
        if (this->pLex2 && this->pLex1) {
            fRc =   Lex_setSourceInput(
                        this->pLex2,
                        (void *)Lex_TokenAdvance,
                        (void *)Lex_TokenLookAhead,
                        this->pLex1
                    );
            if (!fRc) {
                DEBUG_BREAK();
                this->pLex1 = OBJ_NIL;
                obj_Release(this->pLex2);
                this->pLex2 = OBJ_NIL;
                obj_Release(this->pLex3);
                this->pLex3 = OBJ_NIL;
                return ERESULT_FAILURE;
            }
        }
        if (this->pLex2 && (this->pLex3 == OBJ_NIL)) {
            fRc =   Lex_setSourceInput(
                        (LEX_DATA *)this,
                        (void *)Lex_TokenAdvance,
                        (void *)Lex_TokenLookAhead,
                        this->pLex2
                    );
            if (!fRc) {
                DEBUG_BREAK();
                this->pLex1 = OBJ_NIL;
                obj_Release(this->pLex2);
                this->pLex2 = OBJ_NIL;
                obj_Release(this->pLex3);
                this->pLex3 = OBJ_NIL;
                return ERESULT_FAILURE;
            }
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                 C r e a t e  S o u r c e
    //---------------------------------------------------------------
    
    ERESULT         pplex_CreateSourceFromAStr(
        PPLEX_DATA      *this,
        PATH_DATA       *pPath,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        this->pSrc =    srcFile_NewFromAStr(
                                pPath,
                                pStr,
                                1,
                                4                   // tabsize
                        );
        if (OBJ_NIL == this->pSrc) {
            DEBUG_BREAK();
            return ERESULT_FAILURE;
        }
        
        // Now set the srcFile object as the lexer input.
        eRc =   pplex_SetupInputSource(
                                    this,
                                    (void *)srcFile_InputAdvance,
                                    (void *)srcFile_InputLookAhead,
                                    this->pSrc
                );
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this->pSrc);
            this->pSrc = OBJ_NIL;
            return ERESULT_FAILURE;
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         pplex_CreateSourceFromPath(
        PPLEX_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->pSrc =    srcFile_NewFromPath(
                                            pPath,
                                            1,
                                            4                   // tabsize
                        );
        if (OBJ_NIL == this->pSrc) {
            DEBUG_BREAK();
            return ERESULT_FAILURE;
        }
        
        // Now set the srcFile object as the lexer input.
        eRc =   pplex_SetupInputSource(
                                       this,
                                       (void *)srcFile_InputAdvance,
                                       (void *)srcFile_InputLookAhead,
                                       this->pSrc
                );
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this->pSrc);
            this->pSrc = OBJ_NIL;
            return ERESULT_FAILURE;
        }

        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            pplex_Dealloc(
        OBJ_ID          objId
    )
    {
        PPLEX_DATA      *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pLex5) {
            obj_Release(this->pLex5);
            this->pLex5 = OBJ_NIL;
        }
        if (this->pLex4) {
            obj_Release(this->pLex4);
            this->pLex4 = OBJ_NIL;
        }
        if (this->pLex3) {
            obj_Release(this->pLex3);
            this->pLex3 = OBJ_NIL;
        }
        if (this->pLex2) {
            obj_Release(this->pLex2);
            this->pLex2 = OBJ_NIL;
        }
        if (this->pLex1) {
            obj_Release(this->pLex1);
            this->pLex1 = OBJ_NIL;
        }
        if (this->pSrc) {
            obj_Release(this->pSrc);
            this->pSrc = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            pplex_Disable(
        PPLEX_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            pplex_Enable(
        PPLEX_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PPLEX_DATA *    pplex_Init(
        PPLEX_DATA      *this,
        uint16_t        k
    )
    {
        uint32_t        cbSize = sizeof(PPLEX_DATA);
        
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
        
        this = (PPLEX_DATA *)Lex_Init((LEX_DATA *)this);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&pplex_Vtbl);
        
        this->k = k;
        this->lang = -1;
        
    #ifdef NDEBUG
    #else
        if( !pplex_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(sizeof(PPLEX_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            pplex_IsEnabled(
        PPLEX_DATA		*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pplex_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(cbp))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    pplex_InputAdvance(
        PPLEX_DATA		*this,
        uint16_t        numChrs
    )
    {
        TOKEN_DATA      *pToken = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pplex_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        pToken = Lex_InputAdvance((LEX_DATA *)this, numChrs);
        
        // Return to caller.
        return pToken;
    }
    
    
    
    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    TOKEN_DATA *    pplex_InputLookAhead(
        PPLEX_DATA      *this,
        uint16_t        num
    )
    {
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pplex_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pToken = Lex_InputLookAhead((LEX_DATA *)this, num);
        
        // Return to caller.
        return pToken;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          pplex_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PPLEX_DATA      *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !pplex_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(PPLEX_DATA);
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
    //                      S e t u p
    //---------------------------------------------------------------
    
    ERESULT         pplex_SetupInputSource (
        PPLEX_DATA      *this,
        TOKEN_DATA *    (*pSrcChrAdvance)(OBJ_ID,uint16_t),
        TOKEN_DATA *    (*pSrcChrLookAhead)(OBJ_ID,uint16_t),
        OBJ_ID          pSrcObj
    )
    {
        bool            fRc;
        //ERESULT         eRc = ERESULT_SUCCESS;
        
        
#ifdef NDEBUG
#else
        if (!pplex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Now set the srcFile object as the lexer input.
        if (this->pLex1) {
            fRc =   Lex_setSourceInput(
                                          this->pLex1,
                                          (void *)pSrcChrAdvance,
                                          (void *)pSrcChrLookAhead,
                                          pSrcObj
                    );
        }
        else {
            fRc =   Lex_setSourceInput(
                                          this->pLex2,
                                          (void *)pSrcChrAdvance,
                                          (void *)pSrcChrLookAhead,
                                          pSrcObj
                    );
        }
        if (!fRc) {
            DEBUG_BREAK();
            return ERESULT_FAILURE;
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         pplex_SetupMultiCharConstant (
        PPLEX_DATA      *this,
        bool            value
    )
    {
        bool            fRc;
        //ERESULT         eRc = ERESULT_SUCCESS;
        
        
#ifdef NDEBUG
#else
        if (!pplex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Now set the srcFile object as the lexer input.
        if (this->pLex1) {
            fRc =   Lex_setMultiCharConstant(
                        this->pLex1,
                        value
                    );
        }
        if (this->pLex2) {
            fRc =   Lex_setMultiCharConstant(
                        this->pLex2,
                        value
                    );
        }
        if (this->pLex3) {
            fRc =   Lex_setMultiCharConstant(
                        this->pLex3,
                        value
                    );
        }

        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     pplex_ToDebugString(
        PPLEX_DATA      *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        SZSTR_DATA      *pWrkStr;
#endif
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(pplex) side=%d ",
                     cbp,
                     pplex_getSize(cbp)
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
    bool            pplex_Validate(
        PPLEX_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_PPLEX) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(PPLEX_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


