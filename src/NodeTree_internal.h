// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeTree_internal.h
 *	Generated 01/10/2020 16:43:19
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




#include        <NodeTree.h>
#include        <JsonIn.h>
#include        <Node.h>
#include        <NodeHash.h>
#include        <ObjArray.h>
#include        <szTbl.h>


#ifndef NODETREE_INTERNAL_H
#define	NODETREE_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeTree_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    NODEARRAY_DATA  *pArray;        // Root is always at 1
    uint32_t        size;           // Maximum number of elements
    NODELINK_DATA   *pOpen;
    NODELINK_DATA   *pClose;
    OBJ_ID          pNodeArrayClass;

};
#pragma pack(pop)

    extern
    struct NodeTree_class_data_s  NodeTree_ClassObj;

    extern
    const
    NODETREE_VTBL         NodeTree_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODETREE_SINGLETON
    NODETREE_DATA * NodeTree_getSingleton (
        void
    );

    bool            NodeTree_setSingleton (
     NODETREE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            NodeTree_setCloseNode (
        NODETREE_DATA   *this,
        NODELINK_DATA   *pValue
    );

    bool            NodeTree_setDownNode (
        NODETREE_DATA   *cbp,
        NODE_DATA       *pValue
    );

    bool            NodeTree_setOpenNode (
        NODETREE_DATA   *this,
        NODELINK_DATA   *pValue
    );

    bool            NodeTree_setUpNode (
        NODETREE_DATA   *cbp,
        NODE_DATA       *pValue
    );

    OBJ_IUNKNOWN *  NodeTree_getSuperVtbl (
        NODETREE_DATA     *this
    );


    void            NodeTree_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NODETREE_JSON_SUPPORT
    NODETREE_DATA * NodeTree_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          NodeTree_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  NODETREE_JSON_SUPPORT
    ASTR_DATA *     NodeTree_ToJson (
        NODETREE_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			NodeTree_Validate (
        NODETREE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODETREE_INTERNAL_H */

