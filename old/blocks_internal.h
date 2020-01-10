// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   blocks_internal.h
 *	Generated 09/04/2016 13:13:56
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



#include    <blocks.h>
#include    <listdl.h>


#ifndef BLOCKS_INTERNAL_H
#define	BLOCKS_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
#   define BLKS_BLOCK_SIZE  4096
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#   define BLKS_BLOCK_SIZE  4096
#endif


    // Node/Record Descriptor
#pragma pack(push, 1)
    typedef struct  blocks_node_s {
        LISTDL_NODE     list;
        uint32_t        unique;
        uint32_t        filler;         // Boundary 8
        uint8_t         data[0];
    } BLOCKS_NODE;
#pragma pack(pop)
#define            Node2Ptr(pNode)   ((void *)(pNode->data)
#define            Ptr2Node(pData)   ((BLOCKS_NODE *)\
                                        ((uint8_t *)pData - offsetof(BLOCKS_NODE, data)))

    
    typedef struct blocks_block_s {
        LISTDL_NODE     list;           // Chain for block list
        uint8_t         data[0];        // Nodes
    } BLOCKS_BLOCK;
    
    
    

//#pragma pack(push, 1)
struct blocks_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    LISTDL_DATA     blocks;
    LISTDL_DATA     activeList;
    LISTDL_DATA     freeList;
    uint32_t        blockSize;
    uint32_t        blockAvail;
    uint32_t        recordSize;
    uint32_t        dataSize;
    uint32_t        cRecordsPerBlock;
    uint32_t        cBlocks;
    uint32_t        unique;

    // Record Deletion Exit
    P_ERESULT_EXIT3 pDelete;
    OBJ_ID          pObj;           // Used as first parameter of pDelete
    void            *pArg3;         // Used as third paarameter of pDelete
};
//#pragma pack(pop)

    extern
    const
    struct blocks_class_data_s  blocks_ClassObj;

    extern
    const
    BLOCKS_VTBL         blocks_Vtbl;


    // Internal Functions
    void            blocks_Dealloc(
        OBJ_ID          objId
    );



#ifdef NDEBUG
#else
    bool			blocks_Validate(
        BLOCKS_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BLOCKS_INTERNAL_H */

