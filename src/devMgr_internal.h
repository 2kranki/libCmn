// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/* 
 * File:   devMgr_internal.h
 *	Generated 02/24/2016 11:41:23
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




#include    "devMgr.h"
#include    <listdl.h>
#include    <objArray.h>


#ifndef DEVMGR_INTERNAL_H
#define	DEVMGR_INTERNAL_H
#pragma once



#ifdef	__cplusplus
extern "C" {
#endif

    
#define MAX_DEVICES     16
#define MAX_DEVICE_NAME 16


    typedef struct devMgr_device_s	{
        LISTDL_NODE     list;
        char            name[MAX_DEVICE_NAME];
        OBJ_ID          *pDevice;
    } DEVMGR_DEVICE;
    
    


#pragma pack(push, 1)
struct devMgr_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;

    // Common Data
    DEVMGR_DEVICE   devices[MAX_DEVICES];
    LISTDL_DATA     freeList;       // Free Device Linked List
    LISTDL_DATA     list;           // Device Table

    uint16_t        size;		/* maximum number of elements           */
    uint16_t        reserved;
    OBJARRAY_DATA   *pArray;

    volatile
    int32_t         numRead;
    // WARNING - 'elems' must be last element of this structure!
    uint32_t        elems[0];

};
#pragma pack(pop)

    extern
    const
    struct devMgr_class_data_s	devMgr_ClassObj;

    extern
    const
    DEVMGR_VTBL     devMgr_Vtbl;


    // Internal Functions
    void            devMgr_Dealloc(
        OBJ_ID          objId
    );



#ifdef NDEBUG
#else
    bool			devMgr_Validate(
        DEVMGR_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* DEVMGR_INTERNAL_H */

