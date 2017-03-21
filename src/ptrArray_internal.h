// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ptrArray_internal.h
 *	Generated 07/02/2015 10:57:54
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




#ifndef PTRARRAY_INTERNAL_H
#define	PTRARRAY_INTERNAL_H


#include    <ptrArray.h>

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct ptrArray_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;

    // Common Data
    uint32_t        size;		// Number of elements
    uint32_t        max;        // Number of Array Elements
    uint8_t         **ppArray;

};
#pragma pack(pop)

    extern
    const
    OBJ_IUNKNOWN    ptrArray_Vtbl;



    // Internal Functions
    void            ptrArray_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			ptrArray_Validate(
        PTRARRAY_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PTRARRAY_INTERNAL_H */

