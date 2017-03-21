// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeTree_internal.h
 *	Generated 08/04/2015 17:02:38
 *
 * Notes:
 *  --	N/A
 *
 */

/*
 * COPYRIGHT  - (C) Copyright 2015  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */




#include    <nodeTree.h>
#include    <node.h>
#include    <nodeHash.h>
#include    <objArray.h>
#include    <szTbl.h>


#ifndef NODETREE_INTERNAL_H
#define	NODETREE_INTERNAL_H


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct nodeTree_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    ERESULT         eRc;
    OBJARRAY_DATA   *pArray;        // Root is always at 1
    NODEHASH_DATA   *pProperties;
    uint32_t        size;           // Maximum number of elements
    
};
#pragma pack(pop)

    extern
    const
    struct nodeTree_class_data_s  nodeTree_ClassObj;
    
    extern
    const
    OBJ_IUNKNOWN    nodeTree_Vtbl;



    // Internal Functions
    void            nodeTree_Dealloc(
        OBJ_ID          objId
    );

    bool            nodeTree_setDownNode(
        NODETREE_DATA   *cbp,
        NODE_DATA       *pValue
    );
    
    bool            nodeTree_setLastError(
        NODETREE_DATA   *this,
        ERESULT         value
    );
    
    bool            nodeTree_setUpNode(
        NODETREE_DATA   *cbp,
        NODE_DATA       *pValue
    );
    
    
#ifdef NDEBUG
#else
    bool			nodeTree_Validate(
        NODETREE_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODETREE_INTERNAL_H */

