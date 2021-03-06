// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BlkdRcds16_internal.h
 *	Generated 12/22/2019 10:06:17
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




#include        <BlkdRcds16.h>
#include        <JsonIn.h>


#ifndef BLKDRCDS16_INTERNAL_H
#define	BLKDRCDS16_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
    typedef struct index_record_s {
        uint16_t        idxSize;        // Size of Data including this header
        //              Bit 0x8000 of idxSize is available.
        uint16_t        idxOffset;      // Offset of DATA_RECORD within block
        //              Bit 0x8000 of idxOffset is available.
    } INDEX_RECORD;
#pragma pack(pop)
    
    
    
    //                      Main Control Block
    /* This control block resides at the beginning of block and is
     * the information necessary to access the block data. The block
     * size is limited to 32,768.
     * The block index immediately follows the DATA_BLOCK and builds towards
     * the data. The data is added at the top of the block towards the
     * index. The reserved area is just above the data or at the end of block.
     * WARNING -- Only use offsets, NO pointers/addresses within the block!
     */
        
#pragma pack(push, 1)
    typedef struct data_block_s {
        uint16_t        cbSize;         // Total Size of BLock excluding this header
#define DATA_BLOCK_MAX_SIZE 0x7FFF
#define DATA_BLOCK_SPLIT    0x8000
        uint16_t        unusedSize;     // Amount of Data Unused
//              Bit 0x8000 is available.
        uint16_t        rsvdSize;       // Reserved amount at Top of Block
//              Bit 0x8000 is available.
        uint16_t        numRecords;
//              Bit 0x8000 is available.
        uint32_t        begin;          // Beginning record number within file of the
        //                              // First Record in this block
        uint32_t        next;           // Block number of next block
        INDEX_RECORD    index[0];       // Index
    } DATA_BLOCK;
#pragma pack(pop)
        
            
            

    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BlkdRcds16_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        blockSize;
    uint16_t        rsvdSize;
    ASTR_DATA       *pStr;
    DATA_BLOCK      *pBlock;
    uint8_t         fAlloc;
    uint8_t         rsvd8[3];

};
#pragma pack(pop)

    extern
    struct BlkdRcds16_class_data_s  BlkdRcds16_ClassObj;

    extern
    const
    BLKDRCDS16_VTBL         BlkdRcds16_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BLKDRCDS16_SINGLETON
    BLKDRCDS16_DATA *     BlkdRcds16_getSingleton (
        void
    );

    bool            BlkdRcds16_setSingleton (
     BLKDRCDS16_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  BlkdRcds16_getSuperVtbl (
        BLKDRCDS16_DATA     *this
    );


    void            BlkdRcds16_Dealloc (
        OBJ_ID          objId
    );


#ifdef  BLKDRCDS16_JSON_SUPPORT
    BLKDRCDS16_DATA *       BlkdRcds16_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          BlkdRcds16_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     BlkdRcds16_ToJson (
        BLKDRCDS16_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			BlkdRcds16_Validate (
        BLKDRCDS16_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BLKDRCDS16_INTERNAL_H */

