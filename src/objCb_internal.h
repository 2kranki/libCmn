// vi:nu:et:sts=4 ts=4 sw=4

/*
 * File:   objCb_internal.h
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






#ifndef OBJCB_INTERNAL_H
#define	OBJCB_INTERNAL_H


#include    <objCb.h>
#include    <psxLock.h>
#include    <psxSem.h>


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
    struct objCb_data_s	{
        /* Warning - OBJ_DATA must be first in this object!
         */
        OBJ_DATA        super;

        PSXSEM_DATA     *pSemEmpty;
        PSXSEM_DATA     *pSemFull;
        PSXLOCK_DATA    *pLock;
        
        
        // Common Data
        uint16_t        cEntries;	// maximum number of elements
        uint16_t        rsvd;
        volatile
        uint16_t        start;		// index of oldest element
        volatile
        uint16_t        end;		// index at which to write new element
        volatile
        int16_t         numWritten;
        volatile
        int16_t         numRead;

        OBJ_ID          entries[0];

    };
#pragma pack(pop)


    extern
    const
    OBJCB_VTBL      objCb_Vtbl;


    
// Internal Functions
#ifdef RMW_DEBUG
    bool			objCb_Validate(
        OBJCB_DATA      *this
    );
#endif

    void            objCb_Dealloc(
        OBJ_ID          objId
    );


#ifdef	__cplusplus
}
#endif

#endif	/* OBJCB_INTERNAL_H */

