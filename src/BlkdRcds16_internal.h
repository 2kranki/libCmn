// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BlkdRcds16_internal.h
 *  Generated 09/18/2021 09:48:13
 *
 * Notes:
 *  --  N/A
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
#define BLKDRCDS16_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
    typedef struct index_record_s {
        uint16_t        idxSize;        // Size of Data including this header
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
        uint16_t        cbSize;         // Total Size of BLock including this header
#define DATA_BLOCK_MAX_SIZE 0xFFFF
        uint16_t        unusedSize;     // Amount of Data Unused between Index and
        //                              // data records
        uint16_t        rsvdSize;       // Reserved amount at Top of Block
        uint16_t        numRecords;
        INDEX_RECORD    index[0];       // Index
    } DATA_BLOCK;
#pragma pack(pop)



    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BlkdRcds16_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    uint16_t        blockSize;
    uint16_t        rsvdSize;
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
    BLKDRCDS16_DATA * BlkdRcds16_getSingleton (
        void
    );

    bool            BlkdRcds16_setSingleton (
     BLKDRCDS16_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    uint16_t        BlkdRcds16_getBlockSize (
        BLKDRCDS16_DATA *this
    );

    bool            BlkdRcds16_setBlockSize (
        BLKDRCDS16_DATA *this,
        uint16_t        value
    );


    uint16_t        BlkdRcds16_getNumRecords (
        BLKDRCDS16_DATA *this
    );

    bool            BlkdRcds16_setNumRecords (
        BLKDRCDS16_DATA *this,
        uint16_t        value
    );


    uint16_t        BlkdRcds16_getReservedSize (
        BLKDRCDS16_DATA *this
    );

    bool            BlkdRcds16_setReservedSize (
        BLKDRCDS16_DATA *this,
        uint16_t        value
    );


    uint16_t        BlkdRcds16_getUnused (
        BLKDRCDS16_DATA *this
    );

    bool            BlkdRcds16_setUnused (
        BLKDRCDS16_DATA *this,
        uint16_t        value
    );


    OBJ_IUNKNOWN *  BlkdRcds16_getSuperVtbl (
        BLKDRCDS16_DATA *this
    );


    ERESULT         BlkdRcds16_Assign (
        BLKDRCDS16_DATA *this,
        BLKDRCDS16_DATA *pOther
    );


    BLKDRCDS16_DATA * BlkdRcds16_Copy (
        BLKDRCDS16_DATA *this
    );


    /*!
     Point to a Data Record in the buffer.
     @param     this    object pointer
     @param     index   record index (relative to 1)
     @return    If successful, data record address in block and optionally its size;
                otherwise, NULL.
     */
    void *          BlkdRcds16_DataAddr (
        BLKDRCDS16_DATA *this,
        uint32_t        index
    );


    /*!
     Get a Data Record's offset within the data area. Normally, you would
     supply both the index (relative to 1) and the record size. However,
     if you supply 0 for the index and a record size, then the offset returned
     will be for a first record with that record size. If you supply 1 for
     the index and 0 for the record size, you will get the offset for the
     first record.
     @param     this        object pointer
     @param     index       record index (relative to 1), 0 assumes first record
     @param     recordSize  optional record size for a new record
     @return    If successful, data record address in block and optionally its size;
                otherwise, NULL.
     */
    uint16_t        BlkdRcds16_DataOffset (
        BLKDRCDS16_DATA *this,
        uint16_t        index,
        uint16_t        recordSize
    );


    void            BlkdRcds16_Dealloc (
        OBJ_ID          objId
    );


    BLKDRCDS16_DATA * BlkdRcds16_DeepCopy (
        BLKDRCDS16_DATA       *this
    );


#ifdef  BLKDRCDS16_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    BLKDRCDS16_DATA *       BlkdRcds16_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BlkdRcds16_ParseJsonFields (
        JSONIN_DATA     *pParser,
        BLKDRCDS16_DATA     *pObject
    );
#endif


    void *          BlkdRcds16_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    uint16_t        BlkdRcds16_RecordGetOffset (
        BLKDRCDS16_DATA *this,
        uint16_t        index
    );


#ifdef  BLKDRCDS16_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BlkdRcds16_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BlkdRcds16_ToJson (
        BLKDRCDS16_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BlkdRcds16_ToJsonFields (
        BLKDRCDS16_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            BlkdRcds16_Validate (
        BLKDRCDS16_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* BLKDRCDS16_INTERNAL_H */

