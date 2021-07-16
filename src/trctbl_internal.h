// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/* 
 * File:   trctbl_internal.h
 * Author: bob
 *
 * Notes:
 *   1	Before including define the following to customize the config bits for
 *		the development environment needed:
 *		_EXPLORER_16		Microchip Explorer 16 board
 *		_MAX32              Diligent MAX 32 board
 *		_NETWORK_SHIELD     Diligent Network Shield
 *
 * Created on December 26, 2014
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






#ifndef TRCTBL_INTERNAL_H
#define	TRCTBL_INTERNAL_H


#include    <cmn_defs.h>
#include    <trctbl.h>


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push,1)
    struct trctbl_data_s	{
        /* Warning - OBJ_DATA must be first in this object!
         */
        OBJ_DATA        super;
#define TRCTBL_FLAG_LOCKED      OBJ_FLAG_USER1
#define TRCTBL_FLAG_IGNORE      OBJ_FLAG_USER2   /* Ignore any adds or puts */
        
        // Common Data
#ifdef USE_PIC32
        struct TN_Mutex lock;
#endif

        uint16_t        size;
        uint16_t        end;
        uint32_t        numWritten;
        TRCTBL_ENTRY    entries[0];

    };
#pragma pack(pop)


    extern
    const
    OBJ_IUNKNOWN    trctbl_Vtbl;

    
    

// Internal Functions
#ifdef RMW_DEBUG
bool			trctbl_Validate(
	TRCTBL_DATA     *cbp
);
#endif

    void        trctbl_Dealloc(
        OBJ_ID      objId
    );
    


#ifdef	__cplusplus
}
#endif

#endif	/* TRCTBL_INTERNAL_H */

