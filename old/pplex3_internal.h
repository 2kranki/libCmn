// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   pplex3_internal.h
 *	Generated 09/17/2015 10:00:30
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




#ifndef PPLEX3_INTERNAL_H
#define	PPLEX3_INTERNAL_H


#include    <pplex3.h>
#include    <ObjArray.h>
#include    <Lex_internal.h>
#include    <Token_internal.h>

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct pplex3_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    LEX_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    uint16_t        kwdSel;         // Kewword Class Selection
    bool            (*pUserExit)(void *, TOKEN_DATA *);
    void            *pUserObject;
    
    PPLEX_KWDTBL_ENTRY
                    *pAuxKwds;
    uint32_t        cAuxKwds;
};
#pragma pack(pop)

    extern
    const
    PPLEX3_VTBL     pplex3_Vtbl;



    // Internal Functions
    uint32_t        pplex3_getFlags(
        PPLEX3_DATA     *this
    );

    bool            pplex3_setFlags(
        PPLEX3_DATA     *this,
        uint32_t        value
    );


    PPLEX3_DATA *   pplex_getLex3(
        PPLEX_DATA      *this
    );
    
    
    void            pplex3_Dealloc(
        OBJ_ID          objId
    );

    
    bool            pplex3_ParseToken(
        PPLEX3_DATA     *this,
        TOKEN_DATA      *pTokenOut
    );

    
    void *          pplex3_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    bool			pplex3_Validate(
        PPLEX3_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PPLEX3_INTERNAL_H */

