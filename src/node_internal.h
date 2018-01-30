// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   node_internal.h
 *	Generated 06/30/2015 22:51:43
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



#include    <name.h>
#include    <node.h>
#include    <nodeArray.h>
#include    <nodeHash.h>
#include    <listdl.h>
#include    <szTbl.h>


#ifndef NODE_INTERNAL_H
#define	NODE_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


    
#pragma pack(push, 1)
struct node_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;
#define NODE_DUP_NAME   OBJ_FLAG_USER1   /* We allocated Name */

    // Common Data
    ERESULT         eRc;
    int32_t         cls;
    int32_t         type;
    uint32_t        index;
    NAME_DATA       *pName;
    uint32_t        leftIndex;
    uint32_t        middleIndex;
    uint32_t        parentIndex;
    uint32_t        rightIndex;
    OBJ_ID          pData;
    OBJ_ID          pOther;
    NODEARRAY_DATA  *pProperties;
    OBJ_ID          pExtra;

};
#pragma pack(pop)

    extern
    const
    NODE_VTBL       node_Vtbl;

    extern
    const
    struct node_class_data_s   node_ClassObj;
    


    // Internal Functions
    
    bool            node_setName(
        NODE_DATA       *cbp,
        NAME_DATA       *pValue
    );
    
    
    void            node_Dealloc(
        OBJ_ID          objId
    );

    
    NODE_DATA *     node_Init(
        NODE_DATA       *cbp
    );

    
    NODE_DATA *     node_InitWithName(
        NODE_DATA       *cbp,
        NAME_DATA       *pName,
        OBJ_ID          pData
    );

    
    NODE_DATA *     node_InitWithPtr(
        NODE_DATA       *this,
        const
        void            *pValue,
        OBJ_ID          pData
    );
    
    
    void *          node_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    bool			node_Validate(
        NODE_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODE_INTERNAL_H */

