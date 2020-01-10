// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeBTP_internal.h
 *	Generated 11/22/2018 23:21:01
 *
 * Notes:
 *  --	Remember that you can access all the active records via the
 *      blocks list.  See blocks_getList().
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




#include        <nodeBTP.h>
#include        <Blocks_internal.h>
#include        <JsonIn.h>
#include        <NodeArray.h>
#include        <rbt_tree.h>


#ifndef NODEBTP_INTERNAL_H
#define	NODEBTP_INTERNAL_H




#ifdef	__cplusplus
extern "C" {
#endif


    //      Node Record Descriptor
    typedef struct  nodeBTP_record_s NODEBTP_RECORD;
#pragma pack(push, 1)
    struct  nodeBTP_record_s {
        // RBT_NODE must be first field in this struct.
        RBT_NODE        node;
        uint32_t        unique;
    };
#pragma pack(pop)


    
#pragma pack(push, 1)
    typedef struct  nodeBTP_find_s {
        uint32_t        unique;
        NODEBTP_RECORD  *pRecord;
    } NODEBTP_FIND;
#pragma pack(pop)
    
    

#pragma pack(push, 1)
    typedef struct  nodeBTP_visit_s {
        NODEBTP_RECORD  *pRecord;       // Current Record
        P_ERESULT_EXIT3 pScan;
        OBJ_ID          pObj;           // Used as first parameter of scan method
        void            *pArg3;
    } NODEBTP_VISIT;
#pragma pack(pop)
    
    
    

    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct nodeBTP_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    RBT_TREE        tree;
    NODEBTP_RECORD  *pRoot;
    uint32_t        size;		    // maximum number of elements
    ASTR_DATA       *pStr;
    uint32_t        unique;

};
#pragma pack(pop)

    extern
    struct nodeBTP_class_data_s  nodeBTP_ClassObj;

    extern
    const
    NODEBTP_VTBL         nodeBTP_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODEBTP_SINGLETON
    NODEBTP_DATA *     nodeBTP_getSingleton (
        void
    );

    bool            nodeBTP_setSingleton (
     NODEBTP_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  nodeBTP_getSuperVtbl (
        NODEBTP_DATA     *this
    );


    void            nodeBTP_Dealloc (
        OBJ_ID          objId
    );


    ERESULT         nodeBTP_DeleteNodes (
        NODEBTP_DATA    *this,
        NODELNKP_DATA   *pNode
    );
    
    
    NODEBTP_RECORD * nodeBTP_FindUnique (
        NODEBTP_DATA    *this,
        uint32_t        unique
    );
    
    
    NODEBTP_RECORD * nodeBTP_LeftMostChild (
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pNode
    );
    
    
    NODEBTP_DATA *  nodeBTP_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    void *          nodeBTP_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     nodeBTP_ToJson (
        NODEBTP_DATA      *this
    );


#ifdef NDEBUG
#else
    bool			nodeBTP_Validate (
        NODEBTP_DATA       *this
    );
#endif


    ERESULT         nodeBTP_VisitNodeInRecurse (
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pNode,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    
    ERESULT         nodeBTP_VisitNodePostRecurse (
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pNode,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    
    ERESULT         nodeBTP_VisitNodePreRecurse(
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pNode,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* NODEBTP_INTERNAL_H */

