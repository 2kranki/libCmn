// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   TRegex_internal.h
 *	Generated 12/19/2019 23:08:58
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




#include        <TRegex.h>
#include        <JsonIn.h>
#include        <array.h>
#include        <ptrArray.h>


#ifndef TREGEX_INTERNAL_H
#define	TREGEX_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



    /* Definitions: */

    /* max length of character-class buffer */
    #define CCLBUFLEN 20
    /* max number of nested groups */
    #define MAXGROUPS 5

     typedef uint_fast8_t    Modifiers;
     typedef uint_fast8_t    Quantifier;
#define QUANTIFIER_MAX UINT_FAST8_MAX

     /* enum for all the types a char in a char class can be */
    typedef enum ClassCharType_e {
         CCL_END,       /* terminator of CHARCLASS sequence */
         CCL_METABSL,   /* metabackslash; note that metachars don't work in char classes */
         CCL_CHARRANGE  /* literal character range: single characters count as a range */
     } ClassCharType;

     /* a char that can go inside a CHARCLASS (represented by [])*/
     typedef struct ClassChar_s {
         ClassCharType type;
         union {
             int            meta; /* METABSL/INVMETABSL: index in Metabsls */
             struct { /* CHARRANGE */
                 char           first; /* first char in range */
                 char           last; /* last char in range */
             };
         };
     } ClassChar;

     /* the different types that each regex token can be */
     typedef enum TokenType_e {
         TOKEN_END, /* the end of the regex or lookaround */
         TOKEN_GROUP, /* group */
         TOKEN_CGROUP, /* capturing group */
         TOKEN_LOOKAROUND, /* lookaround */
         TOKEN_INVLOOKAROUND, /* inverted lookaround */
         TOKEN_METABSL, /* metabackslash: meta character sequences that begin with backslash */
         TOKEN_METACHAR, /* a metachar, such as $ */
         TOKEN_CHARCLASS, /* a character class that is surrounded by [...] */
         TOKEN_INVCHARCLASS, /* a character class that is inverted by placing a ^ at the start [^...] */
         TOKEN_CHAR /* a literal character */
     } TokenType;

    /* struct for each regex token */
    typedef struct re_Token_s {
        int         index;      // Index in pTolens for this token.
        TokenType type;
        union {
            int         grouplen;   /* END/GROUP/CGROUP/LOOKAROUND/INVLOOKAROUND:
                                    length of the group */
            int         meta;       /* METABSL/INVMETABSL/METACHAR:
                                    index in metabsls/metachars */
            ClassChar* ccl;        /* CHARCLASS/INVCHARCLASS:
                                    a pointer to characters in class (pointer to
                                    somewhere in cclbuf) */
            char       ch;         /* CHAR: the character itself */
        };
        Modifiers      modifiers;
        Quantifier     quantifierMin;
        Quantifier     quantifierMax;
        bool           greedy;     /* whether the token is greedy (takes up as
                                    many characters as possible) or lazy (takes
                                    up as few characters as possible) */
        bool           atomic;     /* whether the token is atomic (cannot change
                                    if the rest of the regex fails) or not;
                                    sometimes known as possessive */
    } re_Token;


    // MatchData is stack entry for compiling patterns with
    // GROUP/CGROUP/LOOKAROUND/INVLOOKAROUND tokens
    typedef struct MatchData_s {
        int             position;
        Quantifier      count;
    } MatchData;



    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct TRegex_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    /*  The sizes of the two static arrays below substantiates the dynamic
        RAM usage of this module.
        MAX_REGEXP_OBJECTS is the max number of symbols in the expression.
        MAX_CHAR_CLASS_LEN determines the size of buffer for chars in all
        char-classes in the expression.
     */
    ClassChar       cclbuf[CCLBUFLEN];  /* buffer in which character class strings
                                            are stored */
    int             ccli;               /* index into buffer */
    uint32_t        maxTokens;
    uint32_t        sizeTokens;
    re_Token        *pTokens;         // array of tokens in regex
    PTRARRAY_DATA   *pTokenStack;
    
};
#pragma pack(pop)

    extern
    struct TRegex_class_data_s  TRegex_ClassObj;

    extern
    const
    TREGEX_VTBL         TRegex_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TREGEX_SINGLETON
    TREGEX_DATA *   TRegex_getSingleton (
        void
    );

    bool            TRegex_setSingleton (
     TREGEX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  TRegex_getSuperVtbl (
        TREGEX_DATA     *this
    );


    void            TRegex_Dealloc (
        OBJ_ID          objId
    );


    ERESULT         TRegex_DeleteTokens(
        TREGEX_DATA     *this
    );


    ERESULT         TRegex_ExpandTokens(
        TREGEX_DATA     *this,
        int             num
    );


#ifdef  TREGEX_JSON_SUPPORT
    TREGEX_DATA *   TRegex_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          TRegex_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     TRegex_ToJson (
        TREGEX_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			TRegex_Validate (
        TREGEX_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TREGEX_INTERNAL_H */

