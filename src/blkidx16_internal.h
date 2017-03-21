// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   blkidx16_internal.h
 *	Generated 03/05/2017 09:37:30
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




#include    <blkidx16.h>


#ifndef BLKIDX16_INTERNAL_H
#define	BLKIDX16_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif



    //                      Record Control Block
    // WARNING -- Only use offsets, NO pointers/addresses within the block!
#pragma pack(push, 1)
    typedef struct data_record_s {
        uint16_t        size;           // Size of Data
        uint8_t         data[0];
    } DATA_RECORD;
#pragma pack(pop)
    
#pragma pack(push, 1)
    typedef struct index_record_s {
        uint16_t        offset;         // Offset of Data within block
    } INDEX_RECORD;
#pragma pack(pop)
    
    
    
    //                      Main Control Block
    /* This control block resides only in memory and is used to provide
     * the information necessary to access the block data.
     * The block index is at the beginning of block and builds towards
     * the data. The data is added at the top of the block towards the
     * index. The reserved area is just above the data.
     * WARNING -- Only use offsets, NO pointers/addresses within the block!
     */
    
    
#pragma pack(push, 1)
    typedef struct index_block_s {
        uint16_t        cbSize;         // Size of BLock including this header
        uint16_t        cbFlags;
        uint16_t        dataSize;       // Amount of Data Used
        uint16_t        rsvdSize;       // Reserved amount at Top of Block
        uint16_t        numRecords;
        INDEX_RECORD    index[0];       // Index
    } INDEX_BLOCK;
#pragma pack(pop)
    
    
    
    

#pragma pack(push, 1)
struct blkidx16_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    INDEX_BLOCK     *pBlock;

};
#pragma pack(pop)

    extern
    const
    struct blkidx16_class_data_s  blkidx16_ClassObj;

    extern
    const
    BLKIDX16_VTBL         blkidx16_Vtbl;


    // Internal Functions
    void            blkidx16_Dealloc(
        OBJ_ID          objId
    );

    bool            blkidx16_setLastError(
        BLKIDX16_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			blkidx16_Validate(
        BLKIDX16_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BLKIDX16_INTERNAL_H */

