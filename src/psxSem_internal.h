// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   psxSem_internal.h
 *	Generated 02/11/2016 10:46:36
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




#include    <psxSem.h>


#ifndef PSXSEM_INTERNAL_H
#define	PSXSEM_INTERNAL_H


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct psxSem_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    ASTR_DATA       *pName;
    int32_t         count;
    int32_t         max;
    int32_t         wakeups;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    HANDLE          m_hSem;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
    struct TN_Sem   sem;
#endif

};
#pragma pack(pop)

    extern
    const
    PSXSEM_VTBL     psxSem_Vtbl;



    // Internal Functions
    void            psxSem_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			psxSem_Validate(
        PSXSEM_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PSXSEM_INTERNAL_H */

