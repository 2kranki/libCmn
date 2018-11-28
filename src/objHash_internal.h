// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   objHash_internal.h
 *	Generated 11/27/2018 11:34:09
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




#include        <objHash.h>
#include        <array.h>
#include        <blocks_internal.h>
#include        <jsonIn.h>
#include        <listdl.h>
#include        <rbt_tree.h>
#include        <u32Array.h>


#ifndef OBJHASH_INTERNAL_H
#define	OBJHASH_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


    //                      Hash Record Descriptor
    
    // Duplicate entries are not allowed in the red-black binary tree (RBT).
    // So, we handle duplicates via a chain off of one entry in the RBT.
    
#pragma pack(push, 1)
    typedef struct  objHash_record_s {
        RBT_NODE        node;
        uint32_t        hash;
        uint32_t        unique;
        LISTDL_DATA     dups;           // List Head or Node of Duplicate Chain
    } OBJHASH_RECORD;
#pragma pack(pop)
    
    


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct objHash_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define OBJHASH_FLAG_DUPS  OBJ_FLAG_USER5  /* true == allow duplicates */

    // Common Data
    uint32_t        unique;         // Unique number given to entries as they are
    //                              // added to the hash table
    uint32_t        size;
    uint32_t        cHash;          // Number of Hash Buckets
    uint32_t        scopeLvl;       /* Scope Level Number (0 = Global) */
    RBT_TREE        *pHash;         // Main Hash Table
    
};
#pragma pack(pop)

    extern
    struct objHash_class_data_s  objHash_ClassObj;

    extern
    const
    OBJHASH_VTBL         objHash_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OBJHASH_SINGLETON
    OBJHASH_DATA *     objHash_getSingleton(
        void
    );

    bool            objHash_setSingleton(
     OBJHASH_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  objHash_getSuperVtbl(
        OBJHASH_DATA     *this
    );


    void            objHash_Dealloc(
        OBJ_ID          objId
    );


    OBJHASH_RECORD * objHash_FindRecord(
        OBJHASH_DATA    *this,
        uint32_t        hash,
        OBJ_ID          pObject
    );
    
    
    OBJHASH_DATA *  objHash_ParseObject(
        JSONIN_DATA     *pParser
    );


    void *          objHash_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     objHash_ToJSON(
        OBJHASH_DATA      *this
    );


    RBT_TREE *      objHash_TreeFromHash (
        OBJHASH_DATA    *this,
        uint32_t        hash
    );
    
    


#ifdef NDEBUG
#else
    bool			objHash_Validate(
        OBJHASH_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJHASH_INTERNAL_H */

