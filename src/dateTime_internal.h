// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   DateTime_internal.h
 *	Generated 08/25/2016 08:11:34
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



#include    <dateTime.h>


#ifndef DATETIME_INTERNAL_H
#define	DATETIME_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct dateTime_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    uint64_t        time;           // UTC Date & Time encoded to binary
    //                              // See DateTime_FromUInt64() & DateTime_ToUInt64()
    //                              // for details.

};
#pragma pack(pop)

    extern
    const
    struct dateTime_class_data_s  DateTime_ClassObj;

    extern
    const
    DATETIME_VTBL         dateTime_Vtbl;


    // Internal Functions
    int64_t         dateTime_getTime(
        DATETIME_DATA   *this
    );
    
    bool            dateTime_setTime(
        DATETIME_DATA   *this,
        int64_t         value
    );
    
    
    void            dateTime_Dealloc(
        OBJ_ID          objId
    );


    void *          dateTime_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );
    

#ifdef NDEBUG
#else
    bool			dateTime_Validate(
        DATETIME_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* DATETIME_INTERNAL_H */

