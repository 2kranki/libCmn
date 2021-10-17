// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BPTIndex_internal.h
 *  Generated 09/25/2021 10:00:36
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




#include        <BPTIndex.h>
#include        <BPT_Request.h>
#include        <BlkdRcds16_internal.h>
#include        <JsonIn.h>


#ifndef BPTINDEX_INTERNAL_H
#define BPTINDEX_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    /*      Node Descriptor
     */
    #pragma pack(push, 1)
    typedef struct  BPTIndex_Node_s {
        uint32_t        lbn;                // Index/Leaf LBN
        uint8_t         key[0];             // Fixed Length Key
    } BPTINDEX_NODE;
    #pragma pack(pop)


    #pragma pack(push, 1)
    typedef struct  BPTIndex_rsvd_s {
        // Warning: Do not add a parent lbn here. An index split will then
        // require many more updates. It is better to just maintain the
        // search tree chain in memory to find the parent.
        uint32_t        p0;                 // LBN of block for keys which
        //                                  // are before the first key in
        //                                  // this block. (ie key < 1st_key)
        uint16_t        keyLen;
        uint16_t        keyOff;
        uint8_t         rsvd8;
        // Warning: blockType must be the last field within
        // the reserved area since it is accessed by other
        // routines using blockSize - 1 addressing.
        uint8_t         blockType;          // 'I' for index, 'L' for leaf
    } BPTINDEX_RSVD;
    #pragma pack(pop)




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BPTIndex_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLKDRCDS16_DATA super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    uint32_t        lbn;            // Logical Block Number

    OBJ_ID          *pMgr;          // Block Manager
    P_ERESULT_EXIT5 pReq;           // Block Manager Request Method
};
#pragma pack(pop)

    extern
    struct BPTIndex_class_data_s  BPTIndex_ClassObj;

    extern
    const
    BPTINDEX_VTBL         BPTIndex_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPTINDEX_SINGLETON
    BPTINDEX_DATA * BPTIndex_getSingleton (
        void
    );

    bool            BPTIndex_setSingleton (
     BPTINDEX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    uint8_t *       BPTIndex_getBlock (
        BPTINDEX_DATA *this
    );


    uint16_t        BPTIndex_getKeyLen (
        BPTINDEX_DATA *this
    );

    bool            BPTIndex_setKeyLen (
        BPTINDEX_DATA *this,
        uint16_t        value
    );


    uint16_t        BPTIndex_getKeyOff (
        BPTINDEX_DATA *this
    );

    bool            BPTIndex_setKeyOff (
        BPTINDEX_DATA *this,
        uint16_t        value
    );


    bool            BPTIndex_setManager(
        BPTINDEX_DATA  *this,
        OBJ_ID           *pMgr          // Block Manager
    );


    uint16_t        BPTIndex_getNumRecords (
        BPTINDEX_DATA *this
    );


    OBJ_IUNKNOWN *  BPTIndex_getSuperVtbl (
        BPTINDEX_DATA *this
    );


    ERESULT         BPTIndex_Assign (
        BPTINDEX_DATA *this,
        BPTINDEX_DATA *pOther
    );


    BPTINDEX_DATA * BPTIndex_Copy (
        BPTINDEX_DATA *this
    );


    void            BPTIndex_Dealloc (
        OBJ_ID          objId
    );


    BPTINDEX_DATA * BPTIndex_DeepCopy (
        BPTINDEX_DATA       *this
    );


    /*!
     Search the block for the key and return the index to the record
     if found or the insertion point.
     @param     this    object pointer
     @param     pKey    key pointer
     @param     pInsert insertion record number if not found
     @return    If successful, the index for the found record.
                Otherwise 0 and pInsert contains insertion point.
     */
    uint16_t        BPTIndex_FindByKey (
        BPTINDEX_DATA *this,
        void            *pKey,
        uint16_t        *pInsert
    );


    /*!
     Get the index'th record from the block.
     @param     this    object pointer
     @param     index   reecord number within block relative to 1
     @param     pLen    optional returned record size
     @return    if successful, record which must be freed using mem_Free().  Otherwise,
                NULL.
     @warning   Remember to release the returned record.
     */
    BPTINDEX_NODE * BPTIndex_GetNum (
        BPTINDEX_DATA *this,
        uint32_t        index,          // Relative to 1
        uint16_t        *pLen           // Optional record length
    );


    void            BPTIndex_LruAttach (
        BPTINDEX_DATA *this,
        void            *pData,
        uint32_t        lsn
    );

    void            BPTIndex_LruDetach (
        BPTINDEX_DATA *this
    );


#ifdef  BPTINDEX_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    BPTINDEX_DATA * BPTIndex_ParseJsonObject (
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
    ERESULT         BPTIndex_ParseJsonFields (
        JSONIN_DATA     *pParser,
        BPTINDEX_DATA *pObject
    );
#endif


    void *          BPTIndex_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  BPTINDEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPTIndex_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPTIndex_ToJson (
        BPTINDEX_DATA *this
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
    ERESULT         BPTIndex_ToJsonFields (
        BPTINDEX_DATA *this,
        ASTR_DATA       *pStr
    );
#endif


#ifdef NDEBUG
#else
    bool            BPTIndex_Validate (
        BPTINDEX_DATA *this
    );
#endif


    ERESULT         BPTIndex_Verify (
        BPTINDEX_DATA *this
    );



#ifdef  __cplusplus
}
#endif

#endif  /* BPTINDEX_INTERNAL_H */

