// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   psxCond_internal.h
 *	Generated 07/05/2016 10:02:43
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



#include    <psxCond.h>
#include    <psxMutex_internal.h>



#ifndef PSXCOND_INTERNAL_H
#define	PSXCOND_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct psxCond_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance
#define PSXCOND_FLAG_COND_INIT      6

    // Common Data
    PSXMUTEX_DATA   *pMutex;
#if defined(__MACOSX_ENV__)
    pthread_cond_t  cond;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
    struct TN_Mutex mutex;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    //HANDLE          m_hSem;
#endif

};
#pragma pack(pop)

    extern
    const
    struct psxCond_class_data_s	psxCond_ClassObj;

    extern
    const
    PSXCOND_VTBL         psxCond_Vtbl;


    // Internal Functions
    void            psxCond_Dealloc(
        OBJ_ID          objId
    );



#ifdef NDEBUG
#else
    bool			psxCond_Validate(
        PSXCOND_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PSXCOND_INTERNAL_H */

