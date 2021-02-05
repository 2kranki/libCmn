// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeHash_internal.h
 *	Generated 01/10/2020 16:43:06
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




#include        <NodeHash.h>
#include        <Blocks_internal.h>
#include        <JsonIn.h>
#include        <rbt_tree.h>


#ifndef NODEHASH_INTERNAL_H
#define	NODEHASH_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif


    //                      Hash Record Descriptor

    // The actual node pointer is the pData field of node.

    // Duplicate entries are not allowed in the red-black binary tree (RBT).
    // So, we handle duplicates via a chain off of one entry in the RBT.

#pragma pack(push, 1)
    typedef struct  NodeHash_record_s {
        RBT_NODE        node;           // MUST be first field.
        uint32_t        unique;
        LISTDL_DATA     dups;           // List Head or Node of Duplicate Chain
    } NODEHASH_RECORD;
#pragma pack(pop)





    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeHash_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        unique;         // Unique number given to entries as they are
    //                              // added to the hash table
    uint32_t        size;
    uint32_t        cHash;          // Number of Hash Buckets
    RBT_TREE        *pHash;         // Main Hash Table (each bucket is an RBT to
    //                              // accellerate searches)

};
#pragma pack(pop)

    extern
    struct NodeHash_class_data_s  NodeHash_ClassObj;

    extern
    const
    NODEHASH_VTBL         NodeHash_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODEHASH_SINGLETON
    NODEHASH_DATA * NodeHash_getSingleton (
        void
    );

    bool            NodeHash_setSingleton (
     NODEHASH_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  NodeHash_getSuperVtbl (
        NODEHASH_DATA     *this
    );


    void            NodeHash_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NODEHASH_JSON_SUPPORT
    NODEHASH_DATA * NodeHash_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          NodeHash_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    RBT_TREE *          NodeHash_TreeFromHash (
        NODEHASH_DATA       *this,
        uint32_t            hash
    );


#ifdef NDEBUG
#else
    bool			NodeHash_Validate (
        NODEHASH_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODEHASH_INTERNAL_H */

