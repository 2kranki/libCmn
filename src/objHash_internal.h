// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   objHash_internal.h
 *	Generated 10/24/2015 13:59:04
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




#ifndef OBJHASH_INTERNAL_H
#define	OBJHASH_INTERNAL_H


#include    <objHash.h>
#include    <listdl.h>

#ifdef	__cplusplus
extern "C" {
#endif


    //      Node Descriptor
#pragma pack(push, 1)
    typedef struct  objHash_node_s {
        LISTDL_NODE     list;
        uint32_t        hash;
        uint32_t        unique;
        OBJ_ID          pObject;
    } OBJHASH_NODE;
#pragma pack(pop)
    
    
    // Block Descriptor
#pragma pack(push, 1)
    typedef struct  objHash_block_s {
        LISTDL_NODE     list;
        OBJHASH_NODE    node[0];
    } OBJHASH_BLOCK;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
struct objHash_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;

    // Common Data
    uint32_t        unique;
    uint32_t        num;            /* Current Number of Entries */
    LISTDL_DATA     freeList;       // Free Node Linked List
    LISTDL_DATA     blocks;
    uint16_t        cBlock;         // Number of Nodes per Block
    uint16_t        cHash;
    LISTDL_DATA     *pHash;         // Main Hash Table

};
#pragma pack(pop)

    extern
    const
    OBJHASH_VTBL    objHash_Vtbl;



    // Internal Functions
    void            objHash_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			objHash_Validate(
        OBJHASH_DATA    *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJHASH_INTERNAL_H */

