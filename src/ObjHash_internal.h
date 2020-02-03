// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ObjHash_internal.h
 *	Generated 02/02/2020 09:55:43
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




#include        <ObjHash.h>
#include        <array.h>
#include        <Blocks_internal.h>
#include        <JsonIn.h>
#include        <listdl.h>
#include        <rbt_tree.h>
#include        <u32Array.h>


#ifndef OBJHASH_INTERNAL_H
#define	OBJHASH_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif


#define HASH_SCOPE_INC   1              /* Incremental Scope Size */

    //      Hash Node Descriptor
#pragma pack(push, 1)
    typedef struct  ObjHash_Node_s {
        LISTDL_NODE     list;
        uint32_t        hash;
        uint32_t        unique;
        OBJ_ID          pObject;        // OBJ_NIL == deleted node
    } OBJHASH_NODE;
#pragma pack(pop)


    // Block Descriptor
#pragma pack(push, 1)
    typedef struct  ObjHash_block_s {
        LISTDL_NODE     list;
        OBJHASH_NODE    node[0];
    } OBJHASH_BLOCK;
#pragma pack(pop)




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct ObjHash_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        unique;         // Unique number given to entries as they are
    //                              // added to the hash table
    uint32_t        num;            // Current Number of Entries
    uint8_t         fDups;          // true == Allow Duplicate Names
    uint8_t         rsvd8[3];
    uint32_t        cBlock;         // Number of Nodes per Block
    uint32_t        cHash;          // Number of Hash Buckets
    uint32_t        cHashIdx;       // Hash Bucket Size Index
    uint32_t        scopeLvl;       /* Scope Level Number (0 = Global) */
    LISTDL_DATA     blocks;
    LISTDL_DATA     freeList;       // Free Node Linked List
    LISTDL_DATA     *pHash;         // Main Hash Table

};
#pragma pack(pop)

    extern
    struct ObjHash_class_data_s  ObjHash_ClassObj;

    extern
    const
    OBJHASH_VTBL         ObjHash_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OBJHASH_SINGLETON
    OBJHASH_DATA *  ObjHash_getSingleton (
        void
    );

    bool            ObjHash_setSingleton (
     OBJHASH_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  ObjHash_getSuperVtbl (
        OBJHASH_DATA     *this
    );


    ERESULT         ObjHash_Assign (
        OBJHASH_DATA    *this,
        OBJHASH_DATA    *pOther
    );


    OBJHASH_DATA *  ObjHash_Copy (
        OBJHASH_DATA    *this
    );


    void            ObjHash_Dealloc (
        OBJ_ID          objId
    );


#ifdef  OBJHASH_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    OBJHASH_DATA *  ObjHash_ParseJsonObject (
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
    ERESULT         ObjHash_ParseJsonFields (
        JSONIN_DATA     *pParser,
        OBJHASH_DATA     *pObject
    );
#endif


    void *          ObjHash_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    /*!
     Reset this object to its beginning state.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjHash_Reset (
        OBJHASH_DATA    *this
    );


    /*!
     Set up the hash table for this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjHash_Setup (
        OBJHASH_DATA    *this,
        uint16_t        cHash       // [in] Hash Table Size
    );


#ifdef  OBJHASH_JSON_SUPPORT
    ASTR_DATA *     ObjHash_ToJson (
        OBJHASH_DATA    *this
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
    ERESULT         ObjHash_ToJsonFields (
        OBJHASH_DATA    *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			ObjHash_Validate (
        OBJHASH_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJHASH_INTERNAL_H */

