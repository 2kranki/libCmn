// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeHash_internal.h
 *	Generated 07/22/2015 10:03:31
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



#include    <nodeHash.h>
#include    <listdl.h>
#include    <str.h>


#ifndef NODEHASH_INTERNAL_H
#define	NODEHASH_INTERNAL_H


#ifdef	__cplusplus
extern "C" {
#endif

#define HASH_BLOCK_SIZE  4096
    
    
    //      Hash Node Descriptor
#pragma pack(push, 1)
    typedef struct  nodeHash_node_s {
        LISTDL_NODE     list;
        uint32_t        hash;
        NODE_DATA       *pNode;
    } NODEHASH_NODE;
#pragma pack(pop)
    
    
    // Block Descriptor (2K)
#pragma pack(push, 1)
    typedef struct  nodeHash_block_s {
        LISTDL_NODE     list;
        NODEHASH_NODE   node[0];
    } NODEHASH_BLOCK;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
struct nodeHash_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    uint32_t        size;
    uint32_t        unique;

    LISTDL_DATA     freeList;       // Free Node Linked List
    LISTDL_DATA     blocks;
    uint32_t        cBlock;         // Number of Nodes per Block
    uint32_t        cHash;
    LISTDL_DATA     *pHash;         // Main Hash Table

};
#pragma pack(pop)

    extern
    const
    NODEHASH_VTBL   nodeHash_Vtbl;



    // Internal Functions
    void            nodeHash_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			nodeHash_Validate(
        NODEHASH_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODEHASH_INTERNAL_H */

