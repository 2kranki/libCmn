// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   szTbl_internal.h
 *	Generated 06/12/2015 10:58:21
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




#ifndef SZTBL_INTERNAL_H
#define	SZTBL_INTERNAL_H


#include    "szTbl.h"
#include    "szHash_internal.h"
#include    "ptrArray.h"

#ifdef	__cplusplus
extern "C" {
#endif

    
#define SZTBL_BLOCK_SIZE  4096        /* Heap Control Block Size */

    

    /*                      String Node
     */
    /* This control block resides only in memory and is used to define
     * an actual string. When constructing the Node, we will round up
     * the total size to be a multiple of the computer's word length.
     */
#pragma pack(push, 1)
    typedef struct szTbl_node_s {
        uint32_t            hash;       // Hash Code
        uint32_t            ident;      // Unique Identifier
        uint16_t            max;        // Data Buffer Size
        uint16_t            len;        // Current Data Length Used
        uint8_t             data[0];
    } SZTBL_NODE;
#pragma pack(pop)
    
    
    
    /*                    Heap Control Block
     */
    /* This control block resides only in memory and is used to block
     * actual strings in the heap.
     */
    typedef struct szTbl_heap_s {
        uint16_t            cbSize;
        uint16_t            size;
        uint16_t            used;
        uint16_t            rsvd;
        struct szTbl_heap_s *pNext;
        SZTBL_NODE          node[0];
    } SZTBL_HEAP;
    
    
    
#pragma pack(push, 1)
struct szTbl_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;

    // Common Data
    SZHASH_DATA     *pHashTable;
    PTRARRAY_DATA   *pPtrArray;
    SZTBL_HEAP      *pHeap;
    uint32_t        size;           // Number of Entries in table

};
#pragma pack(pop)


    extern
    const
    OBJ_IUNKNOWN    szTbl_Vtbl;



    // Internal Functions
    void            szTbl_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			szTbl_Validate(
        SZTBL_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SZTBL_INTERNAL_H */

