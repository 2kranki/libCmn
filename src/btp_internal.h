// vi: nu:noai:ts=4:sw=4

/****************************************************************
 *				Binary Table Manager (BTP) Internal Header       *
 ****************************************************************/


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



#ifndef         BTP_INTERNAL_H
#define         BTP_INTERNAL_H	1


#ifdef	__cplusplus
extern "C" {
#endif
    
    
/****************************************************************
* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include    <btp.h>


/*      Node Descriptor
 */
#pragma pack(push, 1)
typedef struct  btp_node_s {
    struct btp_node_s   *pLeft;
    struct btp_node_s   *pRight;
    struct btp_node_s   *pParent;
    const
    char                *pData;
    uint32_t            unique;
} BTP_NODE;
#pragma pack(pop)


/* Block Descriptor (2K)
 */
#pragma pack(push, 1)
typedef struct  btp_block_s {
    struct btp_block_s  *pNext;
	BTP_NODE            node[0];
} BTP_BLOCK;
#pragma pack(pop)


//#pragma pack(1)
/*                Main Control Block
 */
/* This control block resides only in memory and is used to provide
 * the information necessary to access the HASH data.
 */
#pragma pack(push, 1)
struct btp_data_s {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Compare two keys returning -1 if key1 < key2, 0 if key1 == key2,
    // 1 if key1 > key2
    int             (*pCompare)(const void *pData1,const void *pData2);
    
	// Ptr Table Variables
    uint32_t        unique;
	uint32_t        num;            // Current Number of Entries
    uint16_t        nodesPerBlock;
    uint16_t        bufferSize;
	BTP_BLOCK       *pBlocks;
	BTP_NODE        *pDeletedHead;  /* Deleted Nodes Linked List Ptr */
	BTP_NODE        *pCur;          // Current Node (?)
	BTP_NODE        *pTree;         // Binary Tree
};
#pragma pack(pop)


extern
const
BTP_VTBL            btp_Vtbl;



// Internal Subroutines
    BTP_NODE *      btp_BrotherNode(
        BTP_DATA        *cbp,
        BTP_NODE        *pNode
    );

    void            btp_Dealloc(
        OBJ_ID          objId
    );
    
    BTP_NODE *      btp_FindNode(
        BTP_DATA        *cbp,
        const
        void            *pData
    );

    BTP_DATA *		btp_Init(
        BTP_DATA		*cbp,
        int             (*pCompare)(const void *pData1, const void *pData2)
    );

    bool            btp_IsLeft(
        BTP_DATA        *cbp,
        BTP_NODE        *pNode
    );

    bool            btp_IsRight(
        BTP_DATA        *cbp,
        BTP_NODE        *pNode
    );

    BTP_NODE *      btp_MakeNode(
        BTP_DATA        *cbp,
        const
        void            *pData
    );

    bool            btp_RotateLeft(
        BTP_DATA        *cbp,
        BTP_NODE        *pNode
    );

    bool            btp_RotateRight(
        BTP_DATA        *cbp,
        BTP_NODE        *pNode
    );

    BTP_NODE *      btp_SetLeftNode(
        BTP_DATA        *cbp,
        BTP_NODE        *pNode,
        const
        void            *pData
    );

    BTP_NODE *      btp_SetRightNode(
        BTP_DATA        *cbp,
        BTP_NODE        *pNode,
        const
        void            *pData
    );

    bool			btp_VisitNodePostorderRecursive(
        BTP_DATA        *cbp,
        BTP_NODE        *pNode,
        bool            (*pVisit)(BTP_DATA *cbp, BTP_NODE *pNode)
    );

    bool			btp_VisitNodePreorderRecursive(
        BTP_DATA        *cbp,
        BTP_NODE        *pNode,
        bool            (*pVisit)(BTP_DATA *cbp, BTP_NODE *pNode)
    );

#ifdef NDEBUG
#else
    bool			btp_Validate(
        BTP_DATA     *cbp
    );
#endif


#ifdef	__cplusplus
}
#endif

#endif      // BTP_INTERNAL_H

