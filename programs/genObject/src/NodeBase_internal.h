// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeBase_internal.h
 *	Generated 12/18/2019 23:30:06
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




#include        <NodeBase.h>
#include        <JsonIn.h>
#include        <Node_internal.h>


#ifndef NODEBASE_INTERNAL_H
#define	NODEBASE_INTERNAL_H



#define     PROPERTY_DEPS_OWNED 1
#define     PROPERTY_DESC_OWNED 1
#define     PROPERTY_HDRS_OWNED 1
#define     PROPERTY_NAME_OWNED 1
#define     PROPERTY_EXT_OWNED 1
#define     PROPERTY_REQARCHES_OWNED 1
#define     PROPERTY_REQOSS_OWNED 1
#define     PROPERTY_SRCLOC_OWNED 1
#define     PROPERTY_SRCS_OWNED 1




#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeBase_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    NODE_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTRCARRAY_DATA *pArches;
    ASTRCARRAY_DATA *pDeps;
    ASTRC_DATA      *pDesc;
    ASTRCARRAY_DATA *pHdrs;
    ASTRC_DATA      *pName;
    ASTRCARRAY_DATA *pOSs;
    ASTRCARRAY_DATA *pSrcs;
    ASTRC_DATA      *pExt;          // File Name Extension (optional)
    SRCLOC_DATA     *pSrcLoc;

};
#pragma pack(pop)

    extern
    struct NodeBase_class_data_s  NodeBase_ClassObj;

    extern
    const
    NODEBASE_VTBL         NodeBase_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODEBASE_SINGLETON
    NODEBASE_DATA * NodeBase_getSingleton (
        void
    );

    bool            NodeBase_setSingleton (
     NODEBASE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  NodeBase_getSuperVtbl (
        NODEBASE_DATA     *this
    );


    void            NodeBase_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NODEBASE_JSON_SUPPORT
    NODEBASE_DATA * NodeBase_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          NodeBase_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     NodeBase_ToJson (
        NODEBASE_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			NodeBase_Validate (
        NODEBASE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODEBASE_INTERNAL_H */

