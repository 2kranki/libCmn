// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   disk_internal.h
 *	Generated 10/27/2018 13:52:20
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




#include        <disk.h>
#include        <JsonIn.h>


#ifndef DISK_INTERNAL_H
#define	DISK_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct disk_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        reserved;
    ASTR_DATA       *pStr;

    volatile
    int32_t         numRead;
    // WARNING - 'elems' must be last element of this structure!
    uint32_t        elems[0];

};
#pragma pack(pop)

    extern
    const
    struct disk_class_data_s  disk_ClassObj;

    extern
    const
    DISK_VTBL         disk_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  disk_getSuperVtbl(
        DISK_DATA     *this
    );


    void            disk_Dealloc(
        OBJ_ID          objId
    );


    DISK_DATA *       disk_ParseObject(
        JSONIN_DATA     *pParser
    );


    void *          disk_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     disk_ToJSON(
        DISK_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			disk_Validate(
        DISK_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* DISK_INTERNAL_H */

