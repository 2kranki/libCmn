// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   szHash_internal.h
 *	Generated 06/11/2015 16:44:27
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




#ifndef SZHASH_INTERNAL_H
#define	SZHASH_INTERNAL_H


#include    <szHash.h>
#include    <listdl.h>
#include    <ptrArray.h>



#ifdef	__cplusplus
extern "C" {
#endif


    //      Node Descriptor
#pragma pack(push, 1)
    typedef struct  szHash_node_s {
        LISTDL_NODE     list;
        uint32_t        hash;
        uint32_t        unique;
        void            *pData;
        //uint16_t        keyLen;
        //uint16_t        rsvd;
        const
        char            *pszKey;
    } SZHASH_NODE;
#pragma pack(pop)
    
    
    // Block Descriptor (2K)
#pragma pack(push, 1)
    typedef struct  szHash_block_s {
        LISTDL_NODE     list;
        SZHASH_NODE     node[0];
    } SZHASH_BLOCK;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
struct szHash_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance
    
    // Compare two keys returning -1 if key1 < key2, 0 if key1 == key2,
    // 1 if key1 > key2
    int             (*pCompare)(const char *pKey1,const char *pKey2);
    int             (*pCompareAW32)(const char *pKey1,const W32CHR_T *pKey2);
    uint32_t        (*pComputeHash)(const char *pszKey1, size_t *pLen);
    uint32_t        (*pComputeHashW32)(const W32CHR_T *pszKey1, size_t *pLen);
    
    // Hash Table Variables
    uint32_t        unique;
    uint32_t        num;            /* Current Number of Entries */
    LISTDL_DATA     freeList;       // Free Node Linked List
    LISTDL_DATA     blocks;
    uint16_t        cBlock;         // Number of Nodes per Block
    uint16_t        cHash;
    LISTDL_DATA     *pHash;         // Main Hash Table
    //PTRARRAY_DATA   *pPtrArray;
    uint8_t         fDups;
    uint8_t         rsvd8[3];

};
#pragma pack(pop)

    extern
    const
    SZHASH_VTBL     szHash_Vtbl;



    // Internal Functions
    void            szHash_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			szHash_Validate(
        SZHASH_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SZHASH_INTERNAL_H */

