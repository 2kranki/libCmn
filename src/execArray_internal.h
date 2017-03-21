// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/* 
 * File:   execArray_internal.h
 *	Generated 10/02/2015 13:17:50
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




#ifndef EXECARRAY_INTERNAL_H
#define	EXECARRAY_INTERNAL_H


#include    <execArray.h>
#include    <objArray.h>
#include    <ptrArray.h>

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct execArray_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    OBJARRAY_DATA   *pObjects;
    PTRARRAY_DATA   *pMethods;

};
#pragma pack(pop)

    extern
    const
    EXECARRAY_VTBL  execArray_Vtbl;



    // Internal Functions
    void            execArray_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			execArray_Validate(
        EXECARRAY_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* EXECARRAY_INTERNAL_H */

