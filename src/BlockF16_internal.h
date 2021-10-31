// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BlockF16_internal.h
 *  Generated 10/22/2021 08:20:43
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




#include        <BlockF16.h>
#include        <JsonIn.h>


#ifndef BLOCKF16_INTERNAL_H
#define BLOCKF16_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




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
        uint16_t        rsvdSize;       // Size of reserved space at top of block
        uint16_t        dataSize;       // original record size
        uint16_t        maxRecords;
        uint16_t        numRecords;
        uint16_t        rsvd16;

        uint8_t         records[0];     // Records within the block
    } DATA_BLOCK;
    #pragma pack(pop)

    #define RcdSize2Actual(size) (((size + 4 - 1) >> 2) << 2)



    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BlockF16_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define BLOCKF16_ALLOC  OBJ_FLAG_USER1

    // Common Data
    DATA_BLOCK      blkHdr;
    DATA_BLOCK      *pBlock;

};
#pragma pack(pop)

    extern
    struct BlockF16_class_data_s  BlockF16_ClassObj;

    extern
    const
    BLOCKF16_VTBL         BlockF16_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BLOCKF16_SINGLETON
    BLOCKF16_DATA * BlockF16_getSingleton (
        void
    );

    bool            BlockF16_setSingleton (
     BLOCKF16_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            BlockF16_setBlockSize (
        BLOCKF16_DATA   *this,
        uint16_t        value
    );


    bool            BlockF16_setReservedSize (
        BLOCKF16_DATA   *this,
        uint16_t        value
    );


    OBJ_IUNKNOWN *  BlockF16_getSuperVtbl (
        BLOCKF16_DATA   *this
    );


    ERESULT         BlockF16_Assign (
        BLOCKF16_DATA   *this,
        BLOCKF16_DATA   *pOther
    );


    BLOCKF16_DATA * BlockF16_Copy (
        BLOCKF16_DATA   *this
    );


    void            BlockF16_Dealloc (
        OBJ_ID          objId
    );


    BLOCKF16_DATA * BlockF16_DeepCopy (
        BLOCKF16_DATA   *this
    );


#ifdef  BLOCKF16_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    BLOCKF16_DATA * BlockF16_ParseJsonObject (
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
    ERESULT         BlockF16_ParseJsonFields (
        JSONIN_DATA     *pParser,
        BLOCKF16_DATA   *pObject
    );
#endif


    void *          BlockF16_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    uint8_t *       BlockF16_RecordAddress (
        BLOCKF16_DATA   *this,
        uint16_t        index           // Relative to 0
    );


#ifdef  BLOCKF16_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BlockF16_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BlockF16_ToJson (
        BLOCKF16_DATA   *this
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
    ERESULT         BlockF16_ToJsonFields (
        BLOCKF16_DATA   *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            BlockF16_Validate (
        BLOCKF16_DATA   *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* BLOCKF16_INTERNAL_H */

