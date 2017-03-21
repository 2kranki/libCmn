// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/* 
 * File:   histBase_internal.h
 *	Generated 02/26/2016 00:57:45
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


#include    "devBase.h"



#ifndef HISTBASE_INTERNAL_H
#define	HISTBASE_INTERNAL_H     1


#include        "histBase.h"
#include        "devBase_internal.h"


#ifdef	__cplusplus
extern "C" {
#endif



#pragma pack(push, 1)
struct histBase_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    DEVBASE_DATA    super;
    DEVBASE_VTBL    *pDevVtbl;
#define HISTBASE_FLAG_LOCKED    5

    // Common Data
    uint32_t        (*pCountFunc)(void *);
    void            *pCountData;
    void            (*pWrapFunc)(void *,HISTBASE_DATA *);
    void            *pWrapData;
    uint16_t        size;		/* maximum number of elements           */
    uint16_t        mask;
    volatile
    uint32_t        numWrite;
    // WARNING - 'array' must be last element of this structure!
    HIST_ENTRY      array[0];

};
#pragma pack(pop)

    extern
    const
    struct histBase_class_data_s	histBase_ClassObj;

    extern
    const
    HISTBASE_VTBL   histBase_Vtbl;


    bool            histBase_Disable(
        HISTBASE_DATA	*this
    );
    
    
    bool            histBase_Enable(
        HISTBASE_DATA	*this
    );
    
    
    // Internal Functions
    void            histBase_Dealloc(
        OBJ_ID          objId
    );



#ifdef NDEBUG
#else
    bool			histBase_Validate(
        HISTBASE_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* HISTBASE_INTERNAL_H */

