// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   HashT_internal.h
 *  Generated 12/12/2021 15:40:13
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




#include        <HashT.h>
#include        <array.h>
#include        <Blocks_internal.h>
#include        <JsonIn.h>


#ifndef HASHT_INTERNAL_H
#define HASHT_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    //      Hash Node Descriptor
    #pragma pack(push, 1)
    typedef struct  HashT_Node_s {
        LISTDL_NODE     list;               // Hash Chain
        LISTDL_NODE     level;              // Level Chain
        uint32_t        hash;
        uint32_t        unique;
        uint8_t         data[0];
    } HASHT_NODE;
    #pragma pack(pop)


    // Block Descriptor
    #pragma pack(push, 1)
    typedef struct  HashT_block_s {
        LISTDL_NODE     list;
        HASHT_NODE      node[0];
    } HASHT_BLOCK;
    #pragma pack(pop)





    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct HashT_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        dataSize;       // Data Size in bytes
    uint32_t        unique;         // Unique number given to entries as they are
    //                              // added to the hash table
    uint32_t        num;            // Current Number of Active Entries
    uint8_t         fDups;          // true == Allow Duplicate Names
    uint8_t         rsvd8[3];
    uint32_t        cBlock;         // Number of Nodes per Block
    uint32_t        cHash;          // Number of Hash Buckets
    uint32_t        cHashIdx;       // Hash Bucket Size Index
    uint32_t        scopeLvl;       /* Scope Level Number (0 = Global) */
    LISTDL_DATA     blocks;
    LISTDL_DATA     freeList;       // Free Node Linked List
    LISTDL_DATA     *pHash;         // Main Hash Table
    ARRAY_DATA      *pLevels;       // Level Table

    ASTR_DATA       *pStr;
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;

#ifdef   HASHT_LOG
    // Informational and Warning Log Messages
    OBJ_ID          *pLog;
#endif

    int             (*pCompare)(void *, void *);

    P_ERESULT_EXIT3 pDelete;
    OBJ_ID          pDeleteObj;     // Used as first parameter of scan method
    //                              // second parameter is data to be deleted
    void            *pDeleteArg3;   // Used as third parameter of scan method
};
#pragma pack(pop)

    extern
    struct HashT_class_data_s  HashT_ClassObj;

    extern
    const
    HASHT_VTBL         HashT_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  HASHT_SINGLETON
    HASHT_DATA *     HashT_getSingleton (
        void
    );

    bool            HashT_setSingleton (
     HASHT_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    HASHT_DATA *  HashT_getSuper (
        HASHT_DATA     *this
    );


    OBJ_IUNKNOWN *  HashT_getSuperVtbl (
        HASHT_DATA     *this
    );


    ERESULT         HashT_Assign (
        HASHT_DATA    *this,
        HASHT_DATA    *pOther
    );


    HASHT_DATA *       HashT_Copy (
        HASHT_DATA     *this
    );


    void            HashT_Dealloc (
        OBJ_ID          objId
    );


    HASHT_DATA *     HashT_DeepCopy (
        HASHT_DATA       *this
    );


#ifdef  HASHT_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    HASHT_DATA *       HashT_ParseJsonObject (
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
    ERESULT         HashT_ParseJsonFields (
        JSONIN_DATA     *pParser,
        HASHT_DATA     *pObject
    );
#endif


    void *          HashT_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  HASHT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = HashT_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     HashT_ToJson (
        HASHT_DATA      *this
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
    ERESULT         HashT_ToJsonFields (
        HASHT_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            HashT_Validate (
        HASHT_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* HASHT_INTERNAL_H */

