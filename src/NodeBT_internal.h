// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeBT_internal.h
 *	Generated 01/10/2020 16:43:13
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




#include        <NodeBT.h>
#include        <Blocks_internal.h>
#include        <JsonIn.h>
#include        <NodeArray.h>
#include        <rbt_tree.h>


#ifndef NODEBT_INTERNAL_H
#define	NODEBT_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



    //      Node Record Descriptor
    typedef struct  nodeBT_record_s     NODEBT_RECORD;
#pragma pack(push, 1)
    struct  nodeBT_record_s {
        // RBT_NODE must be first field in this struct.
        RBT_NODE        node;
        uint32_t        unique;
    };
#pragma pack(pop)



#pragma pack(push, 1)
    typedef struct  nodeBT_find_s {
        uint32_t        unique;
        NODEBT_RECORD   *pRecord;
    } NODEBT_FIND;
#pragma pack(pop)



#pragma pack(push, 1)
    typedef struct  nodeBT_visit_s {
        NODEBT_RECORD   *pRecord;       // Current Record
        P_ERESULT_EXIT3 pScan;
        OBJ_ID          pObj;           // Used as first parameter of scan method
        void            *pArg3;
    } NODEBT_VISIT;
#pragma pack(pop)




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeBT_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    RBT_TREE        tree;
    NODEBT_RECORD   *pRoot;
    uint32_t        size;            // maximum number of elements
    uint32_t        unique;

};
#pragma pack(pop)

    extern
    struct NodeBT_class_data_s  NodeBT_ClassObj;

    extern
    const
    NODEBT_VTBL         NodeBT_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODEBT_SINGLETON
    NODEBT_DATA *   NodeBT_getSingleton (
        void
    );

    bool            NodeBT_setSingleton (
     NODEBT_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  NodeBT_getSuperVtbl (
        NODEBT_DATA     *this
    );


    void            NodeBT_Dealloc (
        OBJ_ID          objId
    );


    ERESULT         NodeBT_DeleteNodes (
        NODEBT_DATA     *this,
        NODELNKP_DATA   *pNode
    );


    NODEBT_RECORD * NodeBT_FindUnique (
        NODEBT_DATA    *this,
        uint32_t        unique
    );


    NODEBT_RECORD * NodeBT_LeftMostChild (
        NODEBT_DATA     *this,
        NODEBT_RECORD   *pNode
    );


#ifdef  NODEBT_JSON_SUPPORT
    NODEBT_DATA *       NodeBT_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          NodeBT_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     NodeBT_ToJson (
        NODEBT_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			NodeBT_Validate (
        NODEBT_DATA       *this
    );
#endif



ERESULT         NodeBT_VisitNodeInRecurse (
    NODEBT_DATA     *this,
    NODEBT_RECORD   *pNode,
    P_ERESULT_EXIT3 pScan,
    OBJ_ID          pObj,            // Used as first parameter of scan method
    void            *pArg3
);


ERESULT         NodeBT_VisitNodePostRecurse (
    NODEBT_DATA     *this,
    NODEBT_RECORD   *pNode,
    P_ERESULT_EXIT3 pScan,
    OBJ_ID          pObj,            // Used as first parameter of scan method
    void            *pArg3
);


ERESULT         NodeBT_VisitNodePreRecurse(
    NODEBT_DATA     *this,
    NODEBT_RECORD   *pNode,
    P_ERESULT_EXIT3 pScan,
    OBJ_ID          pObj,            // Used as first parameter of scan method
    void            *pArg3
);



#ifdef	__cplusplus
}
#endif

#endif	/* NODEBT_INTERNAL_H */

