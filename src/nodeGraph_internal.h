// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeGraph_internal.h
 *	Generated 07/14/2016 21:03:24
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



#include    <nodeGraph.h>
#include    <objArray.h>


#ifndef NODEGRAPH_INTERNAL_H
#define	NODEGRAPH_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct nodeGraph_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    NODEHASH_DATA   *pNodes;          // Set of Nodes
    OBJARRAY_DATA   *pArcs;
    uint8_t         fUndirected;
    uint8_t         rsvd8[3];

};
#pragma pack(pop)

    extern
    const
    struct nodeGraph_class_data_s  nodeGraph_ClassObj;

    extern
    const
    NODEGRAPH_VTBL         nodeGraph_Vtbl;


    // Internal Functions
    bool            nodeGraph_setArcs(
        NODEGRAPH_DATA  *this,
        OBJARRAY_DATA   *pValue
    );
    
    
    void            nodeGraph_Dealloc(
        OBJ_ID          objId
    );


    void *          nodeGraph_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );
    
    
#ifdef NDEBUG
#else
    bool			nodeGraph_Validate(
        NODEGRAPH_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODEGRAPH_INTERNAL_H */

