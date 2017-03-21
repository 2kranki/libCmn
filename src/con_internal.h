// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   con_internal.h
 * Author: bob
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






#ifndef CON_INTERNAL_H
#define	CON_INTERNAL_H  1


#include    <con.h>
#include    <hex.h>
#include    <psxMutex.h>


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct con_data_s	{
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;
#define CON_FLAG_USEXONXOFF 4
#define CON_FLAG_XON        5
#define CON_FLAG_ADDCR2LF   6
#define CON_FLAG_ADDLF2CR   7
#define CON_FLAG_ECHO       8

    // Common Data
    ERESULT         eRc;
    CHARIO_DATA     *pCharIO;
    uint16_t        lastChar;
    uint16_t        tabSize;
    PSXMUTEX_DATA   *pMutex;
    HEX_DATA        *pHex;

    uint16_t        max;            // Maximum String Length
    uint16_t        cur;            // Current String length
    char            string[0];
    
};
#pragma pack(pop)


    extern
    const
    CON_VTBL        con_Vtbl;

    

    // Internal Functions
#ifdef RMW_DEBUG
    bool			con_Validate(
        CON_DATA        *cbp
    );
#endif
    void            con_Dealloc(
        OBJ_ID          pObj
    );


#ifdef	__cplusplus
}
#endif

#endif	/* CMN_H */

