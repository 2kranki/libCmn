// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BPT_internal.h
 *  Generated 09/25/2021 10:01:15
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




#include        <BPT.h>
#include        <BPTIndex_internal.h>
#include        <BPTLeaf_internal.h>
#include        <JsonIn.h>
#include        <lru_internal.h>
#include        <ObjArray.h>
#include        <RRDS_internal.h>


#ifndef BPT_INTERNAL_H
#define BPT_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    //          Block Descriptor
    #pragma pack(push, 1)
    typedef struct  BPT_blkidx_s {
        OBJ_ID          pBlock;
        uint32_t        blockLBN;       // Current Node Number in Work Block
    } BPT_BLKIDX;
    #pragma pack(pop)


    //                      File Header
    // This header is saved in the 1st record of the file.
    #pragma pack(push, 1)
    typedef struct  BPT_header_s {
        uint16_t        keyLen;         // Key Length
        uint16_t        keyOff;         // Key Offset within Recorrd
        uint32_t        blockSize;
        uint32_t        cRecords;       // Number of Records in the File including header
        uint32_t        root;           // Root Block LBN
        uint32_t        dataHead;       // Head of Leaf Chain LBN
        uint32_t        dataTail;       // End of Leaf Chain LBN
        uint32_t        deleteHead;     // Head of Free Block Chain LBN
    } BPT_HEADER;
    #pragma pack(pop)



    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BPT_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    RRDS_DATA       *pIO;
    LRU_DATA        *pLRU;          // LRU Mechanism from RRDS (not owned)
    uint32_t        size;            // maximum number of elements
    uint16_t        rsvd16;
    uint16_t        cLRU;
    uint16_t        cHash;
    uint16_t        keyLen;
    uint16_t        keyOff;
    uint8_t         fMem;
    uint8_t         rsvd8;
    uint32_t        blockSize;
    PATH_DATA       *pPath;
    OBJ_ID          pRoot;          // Root Record
    BPT_HEADER    *pHdr;
    OBJARRAY_DATA   *pSrchStk;      // Block List Search Stack

    // Last Key for Sequential Access
    uint32_t        lastLBN;        // Last Logical Block Number
    uint32_t        lastRcd;        // Last Reecord Number

};
#pragma pack(pop)

    extern
    struct BPT_class_data_s  BPT_ClassObj;

    extern
    const
    BPT_VTBL         BPT_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPT_SINGLETON
    BPT_DATA *    BPT_getSingleton (
        void
    );

    bool            BPT_setSingleton (
     BPT_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  BPT_getSuperVtbl (
        BPT_DATA     *this
    );


    ERESULT         BPT_Assign (
        BPT_DATA    *this,
        BPT_DATA    *pOther
    );


    ERESULT         BPT_BlockRequest(
        BPT_DATA      *this,
        uint32_t        request,
        OBJ_ID          pObj,
        void            *pParm1,
        void            *pParm2,
        void            *pParm3
    );


    /*!
     Search the blocks down to the leaf blocks for a specific key.  If found,
     set up work block for the found key.  If not found, set up work block for
     insertion point in block.  Also, the srchStk will contain all the blocks
     searched to find the leaf block.  So, it can be used for figuring out
     parent blocks.
     @param     this        Object Pointer
     @param     lbn         Block Number to start with
     @param     pKey        [input] key to be looked for
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPT_BlockSearchByKey (
        BPT_DATA      *this,
        uint32_t        lbn,
        uint8_t         *pKey
    );


    BPT_DATA *     BPT_Copy (
        BPT_DATA     *this
    );


    void            BPT_Dealloc (
        OBJ_ID          objId
    );


    BPT_DATA *     BPT_DeepCopy (
        BPT_DATA       *this
    );


    ERESULT         BPT_HeaderRead(
        BPT_DATA      *this,
        PATH_DATA       *pPath
    );


    ERESULT         BPT_HeaderWrite(
        BPT_DATA      *this,
        PATH_DATA       *pPath
    );


#ifdef  BPT_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    BPT_DATA *       BPT_ParseJsonObject (
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
    ERESULT         BPT_ParseJsonFields (
        JSONIN_DATA     *pParser,
        BPT_DATA     *pObject
    );
#endif


    void *          BPT_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         BPT_SetupRRDS(
        BPT_DATA      *this
    );


#ifdef  BPT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPT_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT_ToJson (
        BPT_DATA      *this
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
    ERESULT         BPT_ToJsonFields (
        BPT_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            BPT_Validate (
        BPT_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* BPT_INTERNAL_H */

