// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeScan_internal.h
 *	Generated 10/16/2015 09:19:12
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



#include    <nodeScan.h>
#include    <nodeArray.h>


#ifndef NODESCAN_INTERNAL_H
#define	NODESCAN_INTERNAL_H


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct nodeScan_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    uint32_t        index;
    NODEARRAY_DATA  *pArray;    // Tree converted to array with up/down members.

};
#pragma pack(pop)

    extern
    const
    NODESCAN_VTBL   nodeScan_Vtbl;
    extern
    const
    struct nodeScan_class_data_s   nodeScan_ClassObj;



    // Internal Functions
    void            nodeScan_Dealloc(
        OBJ_ID          objId
    );


    void *          nodeScan_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );
    
    
#ifdef NDEBUG
#else
    bool			nodeScan_Validate(
        NODESCAN_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODESCAN_INTERNAL_H */

