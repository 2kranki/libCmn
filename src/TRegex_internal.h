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
#include        <jsonIn.h>
#include        <array.h>


#ifndef TREGEX_INTERNAL_H
#define	TREGEX_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif


/*
 *
 * Mini regex-module inspired by Rob Pike's regex code described in:
 *
 * http://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html
 *
 *
 *
 * Supports:
 * ---------
 *   '.'        Dot, matches any character
 *   '^'        Start anchor, matches beginning of string
 *   '$'        End anchor, matches end of string
 *   '*'        Asterisk, match zero or more (greedy)
 *   '+'        Plus, match one or more (greedy)
 *   '?'        Question, match zero or one (non-greedy)
 *   '[abc]'    Character class, match if one of {'a', 'b', 'c'}
 *   '[^abc]'   Inverted class, match if NOT one of {'a', 'b', 'c'} -- NOTE: feature is currently broken!
 *   '[a-zA-Z]' Character ranges, the character set of the ranges { a-z | A-Z }
 *   '\s'       Whitespace, \t \f \r \n \v and spaces
 *   '\S'       Non-whitespace
 *   '\w'       Alphanumeric, [a-zA-Z0-9_]
 *   '\W'       Non-alphanumeric
 *   '\d'       Digits, [0-9]
 *   '\D'       Non-digits
 *
 *
 */



/* Definitions: */

#define MAX_CHAR_CLASS_LEN      64    // Max length of character-class buffer in.


    typedef enum regex_types_e {
        UNUSED=0,
        DOT, BEGIN, END, QUESTIONMARK, STAR, PLUS,
        CHAR, CHAR_CLASS, INV_CHAR_CLASS,
        DIGIT, NOT_DIGIT,
        ALPHA, NOT_ALPHA,
        WHITESPACE, NOT_WHITESPACE,
        BRANCH
    } REGEX_TYPES;

    typedef struct regex_t {
        uint8_t       type;         // REGEX_TYPES: CHAR, STAR, etc.
        union {
            unsigned char   ch;     // the character itself
            uint8_t         *ccl;   //  OR  a pointer to characters in class
            uint32_t        index;  //  OR  an index into characters in class
        };
    } regex_t;




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
    unsigned char   ccl_buf[MAX_CHAR_CLASS_LEN];
    uint32_t        maxCompiled;
    uint32_t        sizeCompiled;
    regex_t         *pCompiled;

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

