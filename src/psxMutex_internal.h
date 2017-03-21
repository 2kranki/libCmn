// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   psxMutex_internal.h
 *	Generated 02/11/2016 10:46:32
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




#ifndef PSXMUTEX_INTERNAL_H
#define	PSXMUTEX_INTERNAL_H


#include    "psxMutex.h"
#include    <pthread.h>

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct psxMutex_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;
#define PSXMUTEX_FLAG_LOCKED    6

    // Common Data
#if defined(__APPLE__)
    pthread_mutex_t mutex;
#endif
#if defined(__TNEO__)
    struct TN_Mutex mutex;
#endif

};
#pragma pack(pop)

    extern
    const
    PSXMUTEX_VTBL   psxMutex_Vtbl;



    // Internal Functions
    void            psxMutex_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			psxMutex_Validate(
        PSXMUTEX_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PSXMUTEX_INTERNAL_H */

