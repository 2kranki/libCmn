// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   u8Array_internal.h
 *	Generated 08/07/2015 09:47:23
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




#ifndef U8ARRAY_INTERNAL_H
#define	U8ARRAY_INTERNAL_H


#include        <u8Array.h>
#include        <array_internal.h>
#include        <JsonIn.h>


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct u8Array_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance
#define U8ARRAY_FLAG_BIGENDIAN OBJ_FLAG_USER1

    // Common Data
    uint32_t        misc;
    ARRAY_DATA      *pData;

};
#pragma pack(pop)

    extern
    const
    U8ARRAY_VTBL    u8Array_Vtbl;



    // Internal Functions
    void            u8Array_Dealloc(
        OBJ_ID          objId
    );

    U8ARRAY_DATA *  u8Array_ParseJsonObject(
        JSONIN_DATA     *pParser
    );


#ifdef NDEBUG
#else
    bool			u8Array_Validate(
        U8ARRAY_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* U8ARRAY_INTERNAL_H */

