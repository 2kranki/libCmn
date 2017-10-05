// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   pwr2Array_internal.h
 *	Generated 08/25/2015 20:42:16
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




#ifndef PWR2ARRAY_INTERNAL_H
#define	PWR2ARRAY_INTERNAL_H


#include    <pwr2Array.h>

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct pwr2Array_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint16_t        reserved;
    struct {
        uint16_t        dontZero:1;
        uint16_t        rsvd:9;
        uint16_t        powerOf2:6;     // Element Size as power of two
        //                              // 0 == 1, 1 == 2, 2 == 4, ...
    };

    uint32_t        max;
    uint32_t        size;
    uint8_t         *pArray;

};
#pragma pack(pop)

    extern
    const
    PWR2ARRAY_VTBL  pwr2Array_Vtbl;
    extern
    const
    struct pwr2Array_class_data_s   pwr2Array_ClassObj;



    // Internal Functions
    void            pwr2Array_Dealloc(
        OBJ_ID              objId
    );

    ERESULT             pwr2Array_Expand(
        PWR2ARRAY_DATA      *cbp
    );
    
    void *              pwr2Array_Ptr(
        PWR2ARRAY_DATA      *cbp,
        uint32_t            elem        // Element Number (relative to 1)
    );
    
    
    void *          pwr2Array_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );
    
    
#ifdef NDEBUG
#else
    bool			pwr2Array_Validate(
        PWR2ARRAY_DATA      *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PWR2ARRAY_INTERNAL_H */

