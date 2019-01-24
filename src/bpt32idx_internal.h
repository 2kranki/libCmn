// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   bpt32idx_internal.h
 *	Generated 01/12/2019 14:04:35
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




#include        <bpt32idx.h>
#include        <jsonIn.h>


#ifndef BPT32IDX_INTERNAL_H
#define	BPT32IDX_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



    /*      Node Descriptor
     */
#pragma pack(push, 1)
    typedef struct  bpt32idx_node_s {
        //uint32_t        prev;           // Previous Leaf Node Index
        //uint32_t        next;           // Next Leaf Node Index
        uint32_t        key;
        uint32_t        index;
    } BPT32IDX_NODE;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
    typedef struct  bpt32idx_block_s {
        uint16_t        blockType;      // BPT32IDX_DATA
        uint16_t        actualSize;     // Actual Data Size rounded up
        uint16_t        max;            // Maximum Number of nodes
        uint16_t        used;           // Number of nodes in use
        uint32_t        p0;             // Pointer 0
        BPT32IDX_NODE   nodes[0];
    } BPT32IDX_BLOCK;
#pragma pack(pop)
    
    
    

    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct bpt32idx_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define BPT32IDX_BLOCK_ALLOC    OBJ_FLAG_USER1

    // Common Data
    uint16_t        rsvd16;
    uint16_t        dataSize;       // Size of Data in node (NOT USED)
    uint32_t        blockSize;
    uint32_t        index;          // Block Index Number in Dataset/File
    uint32_t        maxRcds;        // Maximum Number of Records in a Block
    BPT32IDX_BLOCK  *pBlock;
    
    OBJ_ID          *pMgr;          // Block Manager
    P_ERESULT_EXIT4 pReq;          // Block Manager Request Method
    
};
#pragma pack(pop)

    extern
    struct bpt32idx_class_data_s  bpt32idx_ClassObj;

    extern
    const
    BPT32IDX_VTBL         bpt32idx_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPT32IDX_SINGLETON
    BPT32IDX_DATA * bpt32idx_getSingleton (
        void
    );

    bool            bpt32idx_setSingleton (
     BPT32IDX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  bpt32idx_getSuperVtbl (
        BPT32IDX_DATA     *this
    );


    void            bpt32idx_Dealloc (
        OBJ_ID          objId
    );


    BPT32IDX_NODE * bpt32idx_FindNode (
        BPT32IDX_DATA   *this,
        uint32_t        key,
        uint32_t        *pIndex
    );
    
    
    BPT32IDX_DATA * bpt32idx_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          bpt32idx_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         bpt32idx_Split (
        BPT32IDX_DATA   *this,
        uint32_t        key,
        uint32_t        data,
        uint32_t        nodeIndex,
        BPT32IDX_DATA   **ppNew
    );
    
    
    ASTR_DATA *     bpt32idx_ToJSON (
        BPT32IDX_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			bpt32idx_Validate (
        BPT32IDX_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BPT32IDX_INTERNAL_H */

