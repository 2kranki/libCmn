// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BPT32Leaf_internal.h
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




#include        <BPT32Leaf.h>
#include        <BPT32_Request.h>
#include        <BlkdRcds16_internal.h>
#include        <JsonIn.h>


#ifndef BPT32LEAF_INTERNAL_H
#define BPT32LEAF_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    /*      Node Descriptor
     */
#pragma pack(push, 1)
    typedef struct  BPT32Leaf_Node_s {
        uint16_t        rcdLen;         // Record Length
        uint8_t         data[0];
    } BPT32LEAF_NODE;
#pragma pack(pop)
    
    
     
    // BlkdRcds16 Reserved Area
#pragma pack(push, 1)
    typedef struct  BPT32Leaf_rsvd_s {
        uint16_t        keyLen;
        uint16_t        keyOff;
        uint32_t        prevLbn;        // Previous Leaf Logical Block Number
        uint32_t        nextLbn;        // Next Leaf Node Logical Block Number
        uint8_t         rsvd8;
        // Warning: blockType must be the last field within
        // the reserved area since it is accessed by other
        // routines using blockSize - 1 addressing.
        uint8_t         blockType;          // 'I' for index, 'L' for leaf
    } BPT32LEAF_RSVD;
#pragma pack(pop)
    
    


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BPT32Leaf_data_s  {
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
    struct BPT32Leaf_class_data_s  BPT32Leaf_ClassObj;

    extern
    const
    BPT32LEAF_VTBL         BPT32Leaf_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPT32LEAF_SINGLETON
    BPT32LEAF_DATA * BPT32Leaf_getSingleton (
        void
    );

    bool            BPT32Leaf_setSingleton (
     BPT32LEAF_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    uint8_t *       BPT32Leaf_getData (
        BPT32LEAF_DATA  *this
    );


    bool            BPT32Leaf_setKeyLen (
        BPT32LEAF_DATA  *this,
        uint16_t        value
    );


    bool            BPT32Leaf_setKeyOff (
        BPT32LEAF_DATA  *this,
        uint16_t        value
    );


    bool            BPT32Leaf_setManager(
        BPT32LEAF_DATA  *this,
        OBJ_ID          *pMgr           // Block Manager
    );


    OBJ_IUNKNOWN *  BPT32Leaf_getSuperVtbl (
        BPT32LEAF_DATA     *this
    );


    ERESULT         BPT32Leaf_Assign (
        BPT32LEAF_DATA    *this,
        BPT32LEAF_DATA    *pOther
    );


    BPT32LEAF_DATA * BPT32Leaf_Copy (
        BPT32LEAF_DATA     *this
    );


    void            BPT32Leaf_Dealloc (
        OBJ_ID          objId
    );


    BPT32LEAF_DATA * BPT32Leaf_DeepCopy (
        BPT32LEAF_DATA       *this
    );


    void            BPT32Leaf_LruAttach (
        BPT32LEAF_DATA  *this,
        void            *pData,
        uint32_t        lbn
    );


    void            BPT32Leaf_LruDetach (
        BPT32LEAF_DATA  *this
    );


#ifdef  BPT32LEAF_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    BPT32LEAF_DATA *       BPT32Leaf_ParseJsonObject (
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
    ERESULT         BPT32Leaf_ParseJsonFields (
        JSONIN_DATA     *pParser,
        BPT32LEAF_DATA     *pObject
    );
#endif


    void *          BPT32Leaf_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  BPT32LEAF_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPT32Leaf_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32Leaf_ToJson (
        BPT32LEAF_DATA      *this
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
    ERESULT         BPT32Leaf_ToJsonFields (
        BPT32LEAF_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif


#ifdef NDEBUG
#else
    bool            BPT32Leaf_Validate (
        BPT32LEAF_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* BPT32LEAF_INTERNAL_H */

