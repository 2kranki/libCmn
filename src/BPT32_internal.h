// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BPT32_internal.h
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




#include        <BPT32.h>
#include        <BPT32Index_internal.h>
#include        <BPT32Leaf_internal.h>
#include        <JsonIn.h>
#include        <lru_internal.h>
#include        <ObjArray.h>
#include        <RRDS_internal.h>


#ifndef BPT32_INTERNAL_H
#define BPT32_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    //          Block Descriptor
    #pragma pack(push, 1)
    typedef struct  BPT32_blkidx_s {
        OBJ_ID          pBlock;
        uint32_t        blockLsn;       // Current Node Number in Work Block
    } BPT32_BLKIDX;
    #pragma pack(pop)


    //                      File Header
    // This header is saved in the 1st record of the file.
    #pragma pack(push, 1)
    typedef struct  BPT32_header_s {
        uint16_t        dataSize;       // Size of Data in node
        uint16_t        actualSize;
        uint16_t        keyLen;         // Key Length
        uint16_t        keyOff;         // Key Offset within Recorrd
        uint32_t        blockSize;
        uint32_t        cRecords;       // Number of Records in the File including header
        uint32_t        root;           // Root Block Index
        uint32_t        dataHead;       // Head of Leaf Chain
        uint32_t        dataTail;       // End of Leaf Chain
        uint32_t        deleteHead;     // Head of Free Block Chain
    } BPT32_HEADER;
    #pragma pack(pop)



    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BPT32_data_s  {
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
    uint16_t        dataSize;       // Size of Data in node
    uint32_t        blockSize;
    //ASTR_DATA       *pStr;
    PATH_DATA       *pPath;
    OBJ_ID          pRoot;          // Root Record
    BPT32_HEADER    *pHdr;
    OBJARRAY_DATA   *pSrchStk;      // Search Block List

    // Last Key for Sequential Access
    uint32_t        lastLBN;        // Last Logical Block Number
    uint32_t        lastRcd;        // Last Reecord Number

};
#pragma pack(pop)

    extern
    struct BPT32_class_data_s  BPT32_ClassObj;

    extern
    const
    BPT32_VTBL         BPT32_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPT32_SINGLETON
    BPT32_DATA *     BPT32_getSingleton (
        void
    );

    bool            BPT32_setSingleton (
     BPT32_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  BPT32_getSuperVtbl (
        BPT32_DATA     *this
    );


    ERESULT         BPT32_Assign (
        BPT32_DATA    *this,
        BPT32_DATA    *pOther
    );


    ERESULT         BPT32_BlockRequest(
        BPT32_DATA      *this,
        uint32_t        request,
        OBJ_ID          pObj,
        void            *pParm1,
        void            *pParm2,
        void            *pParm3
    );


    BPT32_DATA *       BPT32_Copy (
        BPT32_DATA     *this
    );


    void            BPT32_Dealloc (
        OBJ_ID          objId
    );


    BPT32_DATA *     BPT32_DeepCopy (
        BPT32_DATA       *this
    );


#ifdef  BPT32_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    BPT32_DATA *       BPT32_ParseJsonObject (
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
    ERESULT         BPT32_ParseJsonFields (
        JSONIN_DATA     *pParser,
        BPT32_DATA     *pObject
    );
#endif


    void *          BPT32_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  BPT32_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPT32_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32_ToJson (
        BPT32_DATA      *this
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
    ERESULT         BPT32_ToJsonFields (
        BPT32_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            BPT32_Validate (
        BPT32_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* BPT32_INTERNAL_H */

