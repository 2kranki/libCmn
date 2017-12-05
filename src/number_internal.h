// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   number_internal.h
 *	Generated 10/22/2015 16:41:21
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




#ifndef NUMBER_INTERNAL_H
#define	NUMBER_INTERNAL_H


#include    <number.h>

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct number_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
#define NUMBER_FLAG_SIGNED  OBJ_FLAG_USER1

    // Common Data
    uint16_t        reserved;
    uint16_t        type;               // See NUMBER_TYPE;
    union {
        int16_t         i16;                // int16
        int32_t         i32;                // int32
        int64_t			i64;                // int64
//        int128_t		i128;               // int128
        uint16_t        u16;                // uint16
        uint32_t        u32;                // uint32
        uint64_t		u64;                // uint64
//        uint128_t		u128;               // uint128
        double          flt;
    };

};
#pragma pack(pop)

    extern
    const
    NUMBER_VTBL     number_Vtbl;



    // Internal Functions
    void            number_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			number_Validate(
        NUMBER_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NUMBER_INTERNAL_H */

