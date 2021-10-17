// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BPTLeaf_internal.h
 *  Generated 09/23/2021 12:52:17
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




#include        <BPTLeaf.h>
#include        <BPT_Request.h>
#include        <BlkdRcds16_internal.h>
#include        <JsonIn.h>


#ifndef BPTLEAF_INTERNAL_H
#define BPTLEAF_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    /*      Node Descriptor
     */
#pragma pack(push, 1)
    typedef struct  BPTLeaf_Node_s {
        uint16_t        rcdLen;         // Record Length
        uint8_t         data[0];
    } BPTLEAF_NODE;
#pragma pack(pop)
    
    
     
    // BlkdRcds16 Reserved Area
#pragma pack(push, 1)
    typedef struct  BPTLeaf_rsvd_s {
        // Warning: Do not add a parent lbn here. An index split will then
        // require many more updates. It is better to just maintain the
        // search tree chain in memory to find the parent.
        uint16_t        keyLen;
        uint16_t        keyOff;
        uint32_t        prevLbn;        // Previous Leaf Logical Block Number
        uint32_t        nextLbn;        // Next Leaf Node Logical Block Number
        uint8_t         rsvd8;
        // Warning: blockType must be the last field within
        // the reserved area since it is accessed by other
        // routines using blockSize - 1 addressing.
        uint8_t         blockType;          // 'I' for index, 'L' for leaf
    } BPTLEAF_RSVD;
#pragma pack(pop)
    
    


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BPTLeaf_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLKDRCDS16_DATA super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        lbn;            // Logical Block Number
    uint32_t        lastRcd;        // Last Key Record Number
    uint32_t        lastLBN;        // Last Key Logical Block Number

    OBJ_ID          *pMgr;          // Block Manager
    P_ERESULT_EXIT5 pReq;           // Block Manager Request Method
};
#pragma pack(pop)

    extern
    struct BPTLeaf_class_data_s  BPTLeaf_ClassObj;

    extern
    const
    BPTLEAF_VTBL         BPTLeaf_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPTLEAF_SINGLETON
    BPTLEAF_DATA * BPTLeaf_getSingleton (
        void
    );

    bool            BPTLeaf_setSingleton (
     BPTLEAF_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    uint8_t *       BPTLeaf_getData (
        BPTLEAF_DATA  *this
    );


    bool            BPTLeaf_setKeyLen (
        BPTLEAF_DATA  *this,
        uint16_t        value
    );


    bool            BPTLeaf_setKeyOff (
        BPTLEAF_DATA  *this,
        uint16_t        value
    );


    bool            BPTLeaf_setManager(
        BPTLEAF_DATA  *this,
        OBJ_ID          *pMgr           // Block Manager
    );


    OBJ_IUNKNOWN *  BPTLeaf_getSuperVtbl (
        BPTLEAF_DATA     *this
    );


    ERESULT         BPTLeaf_Assign (
        BPTLEAF_DATA    *this,
        BPTLEAF_DATA    *pOther
    );


    BPTLEAF_DATA * BPTLeaf_Copy (
        BPTLEAF_DATA     *this
    );


    void            BPTLeaf_Dealloc (
        OBJ_ID          objId
    );


    BPTLEAF_DATA * BPTLeaf_DeepCopy (
        BPTLEAF_DATA       *this
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
    uint16_t        BPTLeaf_FindByKey (
        BPTLEAF_DATA  *this,
        void            *pKey,
        uint16_t        *pInsert
    );


    void            BPTLeaf_LruAttach (
        BPTLEAF_DATA  *this,
        void            *pData,
        uint32_t        lbn
    );


    void            BPTLeaf_LruDetach (
        BPTLEAF_DATA  *this
    );


#ifdef  BPTLEAF_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    BPTLEAF_DATA *       BPTLeaf_ParseJsonObject (
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
    ERESULT         BPTLeaf_ParseJsonFields (
        JSONIN_DATA     *pParser,
        BPTLEAF_DATA  *pObject
    );
#endif


    void *          BPTLeaf_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  BPTLEAF_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPTLeaf_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPTLeaf_ToJson (
        BPTLEAF_DATA      *this
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
    ERESULT         BPTLeaf_ToJsonFields (
        BPTLEAF_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif


#ifdef NDEBUG
#else
    bool            BPTLeaf_Validate (
        BPTLEAF_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* BPTLEAF_INTERNAL_H */

