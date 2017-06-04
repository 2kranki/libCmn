// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   token_internal.h
 *	Generated 05/26/2015 13:40:16
 *
 * Notes:
 *   1	Before including define the following to customize the config bits for
 *		the development environment needed:
 *		_EXPLORER_16		Microchip Explorer 16 board
 *		_MAX32              Diligent MAX 32 board
 *		_NETWORK_SHIELD     Diligent Network Shield
 *
 * Created on September 26, 2014, 3:39 PM
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




#ifndef TOKEN_INTERNAL_H
#define	TOKEN_INTERNAL_H


#include    "token.h"

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct token_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;

    // Common Data
    const
    char            *pFileName;
	uint32_t        lineNo; 			/* Source Input Line Number */
    int32_t         cls;				/* Character/Token Class (Optional) */
	uint16_t        misc;
	uint16_t        colNo;				/* Source Input Column Number */
	uint16_t        len;				/* Character/Token Length (Optional) */
	uint16_t        offset;				/* offset into token string (Optional) */
    uint16_t        type;               /* Type in union below*/
    uint16_t        rsvd;
    union {
        int32_t         wchr[2];            // Wide Character w/ NUL
        int64_t			integer;			/* Integer */
        OBJ_ID			pObj;               /* an object */
        uint32_t        strToken;
    };
    const
    int32_t         zero;				/* Used to return a zero length string */

};
#pragma pack(pop)

    extern
    const
    TOKEN_VTBL      token_Vtbl;



    // Internal Functions
    void            token_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			token_Validate(
        TOKEN_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TOKEN_INTERNAL_H */

