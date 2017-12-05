// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeTree_internal.h
 *	Generated 08/04/2015 17:02:38
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




#include    <nodeTree.h>
#include    <node.h>
#include    <nodeHash.h>
#include    <objArray.h>
#include    <szTbl.h>


#ifndef NODETREE_INTERNAL_H
#define	NODETREE_INTERNAL_H


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct nodeTree_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    ERESULT         eRc;
    OBJARRAY_DATA   *pArray;        // Root is always at 1
    NODEHASH_DATA   *pProperties;
    uint32_t        size;           // Maximum number of elements
    
};
#pragma pack(pop)

    extern
    const
    struct nodeTree_class_data_s  nodeTree_ClassObj;
    
    extern
    const
    NODETREE_VTBL   nodeTree_Vtbl;



    // Internal Functions
    void            nodeTree_Dealloc(
        OBJ_ID          objId
    );

    bool            nodeTree_setDownNode(
        NODETREE_DATA   *cbp,
        NODE_DATA       *pValue
    );
    
    bool            nodeTree_setLastError(
        NODETREE_DATA   *this,
        ERESULT         value
    );
    
    bool            nodeTree_setUpNode(
        NODETREE_DATA   *cbp,
        NODE_DATA       *pValue
    );
    
    void *          nodeTree_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );
    
    
#ifdef NDEBUG
#else
    bool			nodeTree_Validate(
        NODETREE_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODETREE_INTERNAL_H */

