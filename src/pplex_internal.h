// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   pplex_internal.h
 *	Generated 09/29/2015 11:29:54
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



#include    <pplex.h>
#include    <lex_internal.h>
#include    <pplex1.h>
#include    <pplex2.h>
#include    <pplex3.h>


#ifndef PPLEX_INTERNAL_H
#define	PPLEX_INTERNAL_H


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct pplex_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    LEX_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance
    // OBJ_FLAG_USER1-OBJ_FLAG_USER4 Reserved for Lex
#define PPLEX_FLAG_DEBUG     OBJ_FLAG_USER5

    // Common Data
    LEX_DATA        *pLex1;
    LEX_DATA        *pLex2;
    LEX_DATA        *pLex3;
    LEX_DATA        *pLex4;
    LEX_DATA        *pLex5;
    SRCFILE_DATA    *pSrc;
    uint16_t        lang;
    uint16_t        k;
    uint8_t         fReturnWS;
    uint8_t         fReturnNL;
    uint8_t         rsvd8[2];
    PPLEX_KWDTBL_ENTRY
                    *pAuxKwds;
    uint32_t        cAuxKwds;
    bool            (*pKwdUserExit)(void *, TOKEN_DATA *);
    void            *pKwdUserObject;

};
#pragma pack(pop)

    extern
    const
    struct pplex_class_data_s  pplex_ClassObj;

    extern
    const
    PPLEX_VTBL      pplex_Vtbl;



    // Internal Functions
    void            pplex_Dealloc(
        OBJ_ID          objId
    );


    void *          pplex_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    bool			pplex_Validate(
        PPLEX_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PPLEX_INTERNAL_H */

