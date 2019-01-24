// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   bpt32_internal.h
 *	Generated 01/12/2019 14:04:44
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




#include        <bpt32.h>
#include        <bpt32idx_internal.h>
#include        <bpt32lf_internal.h>
#include        <jsonIn.h>
#include        <lru_internal.h>
#include        <rrds_internal.h>


#ifndef BPT32_INTERNAL_H
#define	BPT32_INTERNAL_H



#define     PROPERTY_PATH_OWNED     1
#define     PROPERTY_ROOT_OWNED     1
#define     PROPERTY_STR_OWNED      1



#ifdef	__cplusplus
extern "C" {
#endif


    //          Node Descriptor
#pragma pack(push, 1)
    typedef struct  bpt32_node_s {
        //uint32_t        prev;           // Previous Leaf Node Index
        //uint32_t        next;           // Next Leaf Node Index
        uint32_t        key;
        union {
            uint32_t        index[0];       // Index Block
            uint8_t         data[0];        // Leaf Block
        };
    } BPT32_NODE;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
    typedef struct  bpt32_block_index_s {
        uint16_t        blockType;      // OBJ_IDENT_BPT32IDX or OBJ_IDENT_BPT32LF
        uint16_t        rsvd16;
        uint16_t        max;            // Maximum Number of nodes
        uint16_t        used;           // Number of nodes in use
        uint32_t        index;          // Block Index
        uint32_t        p0;             // Pointer 0
        BPT32_NODE      nodes[0];
    } BPT32_BLOCK_INDEX;
#pragma pack(pop)
    
    
    
#pragma pack(push, 1)
    typedef struct  bpt32_block_s {
        uint16_t        blockType;      // OBJ_IDENT_BPT32IDX or OBJ_IDENT_BPT32LF
        uint16_t        rsvd16;
        uint16_t        dataSize;       // Requested Data Size
        uint16_t        actualSize;     // Actual Data Size rounded up
        uint16_t        max;            // Maximum Number of nodes
        uint16_t        used;           // Number of nodes in use
        uint32_t        prev;           // Previous Leaf Node Index
        uint32_t        next;           // Next Leaf Node Index
        uint32_t        index;          // Block Index
        BPT32_NODE      nodes[0];
    } BPT32_BLOCK;
#pragma pack(pop)
    
    
    
    //                      File Header
    // This header is saved in the 1st record of the file.
#pragma pack(push, 1)
    typedef struct  bpt32_header_s {
        uint16_t        dataSize;       // Size of Data in node
        uint16_t        actualSize;
        uint32_t        blockSize;
        uint32_t        cRecords;       // Number of Records in the File including header
        uint32_t        root;           // Root Block Index
        uint32_t        dataHead;       // Head of Leaf Chain
        uint32_t        dataTail;       // End of Leaf Chain
        uint32_t        deleteHead;     // Head of Free Block Chain
    } BPT32_HEADER;
#pragma pack(pop)
    
    
    

    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct bpt32_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    RRDS_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
    // OBJ_FLAG_USER1 is used in LRU

    // Common Data
    uint32_t        size;		    // maximum number of elements
    uint16_t        rsvd16;
    uint16_t        cLRU;
    uint16_t        cHash;
    uint16_t        dataSize;       // Size of Data in node
    uint32_t        blockSize;
    ASTR_DATA       *pStr;
    PATH_DATA       *pPath;
    OBJ_ID          pRoot;          // Root Record
    BPT32_HEADER    *pHdr;
    
    //          Search Index List
    uint16_t        srchMax;
    uint16_t        srchCur;
    uint32_t        *pSrchStk;

    // Work Block and associated variables
    BPT32_BLOCK     *pBlock;        // Work Block, blockSize in length
    uint32_t        blockLsn;       // Current Node Number in Work Block
    uint32_t        blockIndex;     // Current Index within Work Block
    BPT32_NODE      *pBlockNode;     // Current Node from blockIndex

    ERESULT         (*pBlockRead)(
        OBJ_ID          this,
        uint32_t        recordNum,
        uint8_t         *pData
    );
    ERESULT         (*pBlockWrite)(
        OBJ_ID          this,
        uint32_t        recordNum,
        uint8_t            *pData    /* Data Ptr (if NULL, a FillChar
                                 * record is written)
                                 */
    );
    OBJ_ID          pBlockObject;
    
};
#pragma pack(pop)

    extern
    struct bpt32_class_data_s  bpt32_ClassObj;

    extern
    const
    BPT32_VTBL         bpt32_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPT32_SINGLETON
    BPT32_DATA *     bpt32_getSingleton (
        void
    );

    bool            bpt32_setSingleton (
     BPT32_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  bpt32_getSuperVtbl (
        BPT32_DATA     *this
    );


    void            bpt32_Dealloc (
        OBJ_ID          objId
    );


    ERESULT         bpt32_BlockInit(
        BPT32_BLOCK     *pBlock,
        uint16_t        blockType,      // OBJ_IDENT_BPT32IDX or OBJ_IDENT_BPT32LF
        uint32_t        blockSize,
        uint16_t        dataSize,       // If Index, use sizeof(uint32_t) for this.
        uint32_t        blockIndex
    );
    
    
    ERESULT         bpt32_BlockRead(
        BPT32_DATA      *this,
        uint32_t        lsn
    );
    
    
    ERESULT         bpt32_BlockSearch (
        BPT32_DATA      *this,
        uint32_t        lsn,
        uint32_t        key,
        void            *pData
    );
    
    
    ERESULT         bpt32_BlockSplit(
        BPT32_DATA      *this,
        uint32_t        *pIndex
    );
    
    
    BPT32_NODE *    bpt32_Index2Node (
        BPT32_BLOCK     *pBlock,
        uint32_t        index                // Relative to 0
    );
    
    
    ERESULT         bpt32_NodeDelete (
        BPT32_DATA      *this,
        BPT32_BLOCK     *pBlock,
        uint32_t        key
    );
    
    
    BPT32_NODE *    bpt32_NodeFind (
        BPT32_BLOCK     *pBlock,
        uint32_t        key,
        uint32_t        *pIndex
    );
    
    
    ERESULT         bpt32_NodeInsert (
        BPT32_DATA      *this,
        BPT32_BLOCK     *pBlock,
        uint32_t        key,
        void            *pData
    );
    
    
    BPT32_DATA *       bpt32_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          bpt32_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     bpt32_ToJSON (
        BPT32_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			bpt32_Validate (
        BPT32_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BPT32_INTERNAL_H */

