// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   hash32_internal.h
 *	Generated by 06/07/2015 08:07:00
 *
 * Notes:
 *   1	Before including define the following to customize the config bits for
 *		the development environment needed:
 *		_EXPLORER_16		Microchip Explorer 16 board
 *		_MAX32              Diligent MAX 32 board
 *		_NETWORK_SHIELD     Diligent Network Shield
 *
 * Created on September 26, 2014, 3:39 PM
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




#ifndef HASH32_INTERNAL_H
#define	HASH32_INTERNAL_H


#include    <hash32.h>

#ifdef	__cplusplus
extern "C" {
#endif


    /*      Node Descriptor
     */
#pragma pack(push, 1)
    typedef struct  hash32_node_s {
        struct hash32_node_s
                        *pNext;
        void            *pData;
        uint32_t        key;
        uint32_t        hash;
    } HASH32_NODE;
#pragma pack(pop)
    
    
    /* Block Descriptor (2K)
     */
#pragma pack(push, 1)
    typedef struct  hash32_block_s {
        struct hash32_block_s
                        *pNext;
        HASH32_NODE     node[0];
    } HASH32_BLOCK;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
struct hash32_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;

    // Common Data
#ifdef XYZZY        // Thoughts for another version for szStrings
                    // Compare two keys returning -1 if key1 < key2, 0 if key1 == key2,
                    // 1 if key1 > key2
    int             (*pCmp)(const void *pszKey1,const void *pszKey2);
    uint32_t        (*pComputeHash)(const void *pszKey1, int *pLen);
#endif
    
	// Ptr Table Variables
	uint32_t        num;            /* Current Number of Entries */
    uint16_t        cBlock;         // Number of Nodes per Block
    uint16_t        cHash;
	HASH32_NODE     *pDeletedHead;  /* Deleted Nodes Linked List Ptr */
	HASH32_BLOCK    *pBlocks;
	HASH32_NODE     **pHash;        // Main Hash Table

};
#pragma pack(pop)

    extern
    const
    OBJ_IUNKNOWN    hash32_Vtbl;



    // Internal Functions
    bool            hash32_AddBlock(
        HASH32_DATA     *cbp
    );
    
    void            hash32_Dealloc(
        OBJ_ID          objId
    );
    
    HASH32_NODE *   hash32_FindEntry(
        HASH32_DATA     *cbp,
        uint32_t        key
    );
    
    uint16_t        hash32_IndexFromKey(
        HASH32_DATA     *cbp,
        uint32_t        key
    );
    
    HASH32_NODE *   hash32_NodeFromKey(
        HASH32_DATA     *cbp,
        uint32_t        key
    );
    
    
#ifdef NDEBUG
#else
    bool			hash32_Validate(
        HASH32_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* HASH32_INTERNAL_H */

