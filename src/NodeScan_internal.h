// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeScan_internal.h
 *	Generated 12/17/2019 10:10:16
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




#include        <NodeScan.h>
#include        <JsonIn.h>


#ifndef NODESCAN_INTERNAL_H
#define	NODESCAN_INTERNAL_H



#define     PROPERTY_ARRAY_OWNED 1
#define     PROPERTY_CLOSE_OWNED 1
#define     PROPERTY_OPEN_OWNED 1
#define     PROPERTY_TREE_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



    typedef enum tok_typ_e {
        TOK_TYP_EOF=-1,
        TOK_TYP_INVALID=0,
        TOK_TYP_LPAREN=1,
        TOK_TYP_RPAREN=2,
        TOK_TYP_PERCENT=3,
        TOK_TYP_INT=4,
        TOK_TYP_COLON=5,
        TOK_TYP_POUND=6,
        TOK_TYP_PERIOD=7
    } TOK_TYP;
#define TOK_TYP_VALID(x) ((x >= TOK_TYP_LPAREN) && (x <= TOK_TYP_PERIOD))
    
    typedef struct scanner_entry_s {
        int         nodeClass;               // Node Class for comparison
        int         scanLabel;              // Optional index to Returned Node Pointer
    } SCANNER_ENTRY;
    
    // MAX values should be evenly divisible by 8
#define MAX_SCANNER_ENTRIES     32
#define MAX_SCANNER_LABELS      16


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeScan_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        index;      // Scan Index (relative to 0)
    uint32_t        start;      // Scan Start Index (relative to 0)
    NODEARRAY_DATA  *pArray;    // linearalized Tree converted to an array with
    //                          // up/down members.
    NODETREE_DATA   *pTree;     // Tree associated with linearized tree list
    NODE_DATA       *pClose;
    NODE_DATA       *pOpen;

    // ScanF Input
    ASTR_DATA       *pScanInput;
    uint32_t        curChar;
    int32_t         tokInt;
    
    // ScanF Scan Data
    uint32_t        offset;         // Offset within pArray of current scan comparison.
    uint32_t        scanLength;
    int32_t         nodeTypes[MAX_SCANNER_ENTRIES];
    uint32_t        rsvd32_2;
    uint32_t        cLabels;        // Node Labels which are returned Node Pointers if
    //                              // matched
    NODE_DATA       **ppLabels[MAX_SCANNER_LABELS];

};
#pragma pack(pop)

    extern
    struct NodeScan_class_data_s  NodeScan_ClassObj;

    extern
    const
    NODESCAN_VTBL         NodeScan_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODESCAN_SINGLETON
    NODESCAN_DATA * NodeScan_getSingleton (
        void
    );

    bool            NodeScan_setSingleton (
     NODESCAN_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            NodeScan_setNodeClose(
        NODESCAN_DATA   *this,
        NODE_DATA       *pValue
    );
    
    
    bool            NodeScan_setNodeOpen(
        NODESCAN_DATA   *this,
        NODE_DATA       *pValue
    );
    
    
    bool            NodeScan_setTree(
        NODESCAN_DATA   *this,
        NODETREE_DATA   *pValue
    );
    
    
    OBJ_IUNKNOWN *  NodeScan_getSuperVtbl (
        NODESCAN_DATA     *this
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = NodeScan_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another NODESCAN object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         NodeScan_Assign (
        NODESCAN_DATA   *this,
        NODESCAN_DATA   *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        NodeScan      *pCopy = NodeScan_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a NODESCAN object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODESCAN_DATA *  NodeScan_Copy (
        NODESCAN_DATA    *this
    );


    void            NodeScan_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NODESCAN_JSON_SUPPORT
    NODESCAN_DATA * NodeScan_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          NodeScan_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     NodeScan_ToJson (
        NODESCAN_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			NodeScan_Validate (
        NODESCAN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODESCAN_INTERNAL_H */

