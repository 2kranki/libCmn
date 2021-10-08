// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BPT32Index_internal.h
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




#include        <BPT32Index.h>
#include        <BPT32_Request.h>
#include        <BlkdRcds16_internal.h>
#include        <JsonIn.h>


#ifndef BPT32INDEX_INTERNAL_H
#define BPT32INDEX_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    /*      Node Descriptor
     */
    #pragma pack(push, 1)
    typedef struct  BPT32Index_Node_s {
        uint32_t        lbn;                // Index/Leaf LBN
        uint8_t         key[0];             // Fixed Length Key
    } BPT32INDEX_NODE;
    #pragma pack(pop)


    #pragma pack(push, 1)
    typedef struct  BPT32Index_rsvd_s {
        uint16_t        keyLen;
        uint16_t        keyOff;
        uint8_t         rsvd8;
        // Warning: blockType must be the last field within
        // the reserved area since it is accessed by other
        // routines using blockSize - 1 addressing.
        uint8_t         blockType;          // 'I' for index, 'L' for leaf
    } BPT32INDEX_RSVD;
    #pragma pack(pop)




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BPT32Index_data_s  {
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
    struct BPT32Index_class_data_s  BPT32Index_ClassObj;

    extern
    const
    BPT32INDEX_VTBL         BPT32Index_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPT32INDEX_SINGLETON
    BPT32INDEX_DATA * BPT32Index_getSingleton (
        void
    );

    bool            BPT32Index_setSingleton (
     BPT32INDEX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    uint8_t *       BPT32Index_getBlock (
        BPT32INDEX_DATA *this
    );


    uint16_t        BPT32Index_getKeyLen (
        BPT32INDEX_DATA *this
    );

    bool            BPT32Index_setKeyLen (
        BPT32INDEX_DATA *this,
        uint16_t        value
    );


    uint16_t        BPT32Index_getKeyOff (
        BPT32INDEX_DATA *this
    );

    bool            BPT32Index_setKeyOff (
        BPT32INDEX_DATA *this,
        uint16_t        value
    );


    bool            BPT32Index_setManager(
        BPT32INDEX_DATA  *this,
        OBJ_ID           *pMgr          // Block Manager
    );


    uint16_t        BPT32Index_getNumRecords (
        BPT32INDEX_DATA *this
    );


    OBJ_IUNKNOWN *  BPT32Index_getSuperVtbl (
        BPT32INDEX_DATA     *this
    );


    ERESULT         BPT32Index_Assign (
        BPT32INDEX_DATA    *this,
        BPT32INDEX_DATA    *pOther
    );


    BPT32INDEX_DATA * BPT32Index_Copy (
        BPT32INDEX_DATA     *this
    );


    void            BPT32Index_Dealloc (
        OBJ_ID          objId
    );


    BPT32INDEX_DATA * BPT32Index_DeepCopy (
        BPT32INDEX_DATA       *this
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
    uint8_t *       BPT32Index_GetNum (
        BPT32INDEX_DATA *this,
        uint32_t        index,          // Relative to 1
        uint16_t        *pLen           // Optional record length
    );


    void            BPT32Index_LruAttach (
        BPT32INDEX_DATA *this,
        void            *pData,
        uint32_t        lsn
    );

    void            BPT32Index_LruDetach (
        BPT32INDEX_DATA *this
    );


#ifdef  BPT32INDEX_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    BPT32INDEX_DATA *       BPT32Index_ParseJsonObject (
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
    ERESULT         BPT32Index_ParseJsonFields (
        JSONIN_DATA     *pParser,
        BPT32INDEX_DATA     *pObject
    );
#endif


    void *          BPT32Index_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  BPT32INDEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPT32Index_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32Index_ToJson (
        BPT32INDEX_DATA      *this
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
    ERESULT         BPT32Index_ToJsonFields (
        BPT32INDEX_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            BPT32Index_Validate (
        BPT32INDEX_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* BPT32INDEX_INTERNAL_H */

