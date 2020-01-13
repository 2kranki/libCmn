// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   bpt32lf_internal.h
 *	Generated 01/12/2019 14:04:41
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




#include        <bpt32lf.h>
#include        <JsonIn.h>


#ifndef BPT32LF_INTERNAL_H
#define	BPT32LF_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



    /*      Node Descriptor
     */
#pragma pack(push, 1)
    typedef struct  bpt32lf_Node_s {
        //uint32_t        prev;           // Previous Leaf Node Index
        //uint32_t        next;           // Next Leaf Node Index
        uint32_t        key;
        uint8_t         data[0];
    } BPT32LF_NODE;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
    typedef struct  bpt32lf_block_s {
        uint16_t        blockType;      // BPT32IDX_DATA or BPT32LF_DATA
        uint16_t        rsvd16;
        uint16_t        dataSize;
        uint16_t        actualSize;     // Actual Data Size rounded up
        uint16_t        max;            // Maximum Number of nodes
        uint16_t        used;           // Number of nodes in use
        uint32_t        prev;           // Previous Leaf Node Index
        uint32_t        next;           // Next Leaf Node Index
        BPT32LF_NODE    nodes[0];
    } BPT32LF_BLOCK;
#pragma pack(pop)
    
    

    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct bpt32lf_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define BPT32LF_BLOCK_ALLOC     OBJ_FLAG_USER1

    // Common Data
    //uint16_t        rsvd16;
    uint16_t        dataSize;       // Size of Data in node
    uint16_t        actualSize;     // Actual Data Size rounded up
    uint32_t        blockSize;
    uint32_t        index;          // Block Index Number in Dataset/File
    uint32_t        maxRcds;        // Maximum Number of Records in a Block
    BPT32LF_BLOCK   *pBlock;
    uint32_t        lastKey;
    uint32_t        lastIndex;

    OBJ_ID          *pMgr;          // Block Manager
    P_ERESULT_EXIT4 pReq;           // Block Manager Request Method

};
#pragma pack(pop)

    extern
    struct bpt32lf_class_data_s  bpt32lf_ClassObj;

    extern
    const
    BPT32LF_VTBL         bpt32lf_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPT32LF_SINGLETON
    BPT32LF_DATA *     bpt32lf_getSingleton (
        void
    );

    bool            bpt32lf_setSingleton (
     BPT32LF_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  bpt32lf_getSuperVtbl (
        BPT32LF_DATA     *this
    );


    void            bpt32lf_Dealloc (
        OBJ_ID          objId
    );


    BPT32LF_NODE *  bpt32lf_FindNode (
        BPT32LF_DATA    *this,
        uint32_t        key,
        uint32_t        *pIndex
    );
    
    
    BPT32LF_NODE *  bpt32lf_Index2Node (
        BPT32LF_DATA    *this,
        uint32_t        index
    );
    
    
    BPT32LF_DATA *       bpt32lf_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          bpt32lf_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     bpt32lf_ToJSON (
        BPT32LF_DATA    *this
    );


#ifdef NDEBUG
#else
    bool			bpt32lf_Validate (
        BPT32LF_DATA    *this
    );
#endif


    ERESULT         bpt32lf_Verify (
        BPT32LF_DATA    *this
    );
    
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* BPT32LF_INTERNAL_H */

