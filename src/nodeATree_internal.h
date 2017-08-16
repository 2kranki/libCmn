// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeATree_internal.h
 *	Generated 08/31/2016 21:21:55
 *
 * Notes:
 *  --	Where B denotes the tree order (2 == binary, 3 == ternary, etc)
 *      The first entry is the root followed by its children to the formula:
 *      first_child_index = (B * j) - (B - 2)
 *      last_child_index  = (B * j) - (B - 2) + (B - 1)
 *      parent_index = (j + (B-2)) / B
 *      sibling_index = (j + (B-2)) % B
 *      size_of_array_needed = (B^(L + 1) - 1) / (B - 1) 
 *                             where L is the number of levels
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



#include    <nodeATree.h>
#include    <node_internal.h>
#include    <objArray_internal.h>


#ifndef NODEATREE_INTERNAL_H
#define	NODEATREE_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct nodeATree_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    uint16_t        B;
    uint16_t        B_2;            // B - 2
    OBJARRAY_DATA   *pArray;
    ERESULT         eRc;            // Last Error

};
#pragma pack(pop)

    extern
    const
    struct nodeATree_class_data_s  nodeATree_ClassObj;

    extern
    const
    NODEATREE_VTBL         nodeATree_Vtbl;


    // Internal Functions
    void            nodeATree_Dealloc(
        OBJ_ID          objId
    );


    void *          nodeATree_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );
    
    
#ifdef NDEBUG
#else
    bool			nodeATree_Validate(
        NODEATREE_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODEATREE_INTERNAL_H */

