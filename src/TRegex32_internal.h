// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   TRegex32_internal.h
 *	Generated 12/19/2019 23:09:03
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




#include        <TRegex32.h>
#include        <jsonIn.h>


#ifndef TREGEX32_INTERNAL_H
#define	TREGEX32_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif


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
        W32CHR_T        ch;     // the character itself
        W32CHR_T        *ccl;   //  OR  a pointer to characters in class
        uint32_t        index;  //  OR  an index into characters in class
    };
} regex_t;




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct TRegex32_data_s	{
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
    W32CHR_T        ccl_buf[MAX_CHAR_CLASS_LEN];
    uint32_t        maxCompiled;
    uint32_t        sizeCompiled;
    regex_t         *pCompiled;

};
#pragma pack(pop)

    extern
    struct TRegex32_class_data_s  TRegex32_ClassObj;

    extern
    const
    TREGEX32_VTBL         TRegex32_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TREGEX32_SINGLETON
    TREGEX32_DATA * TRegex32_getSingleton (
        void
    );

    bool            TRegex32_setSingleton (
     TREGEX32_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  TRegex32_getSuperVtbl (
        TREGEX32_DATA     *this
    );


    void            TRegex32_Dealloc (
        OBJ_ID          objId
    );


#ifdef  TREGEX32_JSON_SUPPORT
    TREGEX32_DATA * TRegex32_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          TRegex32_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     TRegex32_ToJson (
        TREGEX32_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			TRegex32_Validate (
        TREGEX32_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TREGEX32_INTERNAL_H */

