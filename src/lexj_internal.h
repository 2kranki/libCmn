// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   lexj_internal.h
 *	Generated 07/02/2017 09:15:13
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




#include    <lexj.h>
#include    <lex_internal.h>
#include    <srcFile.h>


#ifndef LEXJ_INTERNAL_H
#define	LEXJ_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct lexj_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    LEX_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    SRCFILE_DATA    *pInput;
    bool            (*pParser)(OBJ_ID, TOKEN_DATA *);
    TOKEN_DATA      token;              // Next Output Token (output of pParser)

};
#pragma pack(pop)

    extern
    const
    struct lexj_class_data_s  lexj_ClassObj;

    extern
    const
    LEXJ_VTBL         lexj_Vtbl;


    // Internal Functions
    bool            lexj_setLastError(
        LEXJ_DATA       *this,
        ERESULT         value
    );
    
    
    void            lexj_Dealloc(
        OBJ_ID          objId
    );

    bool            lexj_ParseTokenJson(
        LEXJ_DATA       *this,
        TOKEN_DATA      *pTokenOut          // Optional Output Token
    );
    
    
    void *          lexj_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );




#ifdef NDEBUG
#else
    bool			lexj_Validate(
        LEXJ_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* LEXJ_INTERNAL_H */

