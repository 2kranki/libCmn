// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeTree_internal.h
 *  Generated 11/26/2021 19:19:16
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




#include        <NodeTree.h>
#include        <Blocks_internal.h>
#include        <JsonIn.h>


#ifndef NODETREE_INTERNAL_H
#define NODETREE_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //                      Tree Record Descriptor

    // This record is in memory. It can be written/reead using
    // JSON by translating the pointers to ObjArray indices.

    typedef struct  NodeTree_record_s {
        NODE_DATA       *pNode;
        uint32_t        unique;             // Index into objArray
        uint32_t        childIndex;         // Index into this tree
        uint32_t        parentIndex;        // Index into this tree
        uint32_t        siblingIndex;       // Index into this tree
    } NODETREE_RECORD;


typedef struct  NodeTree_visit_s {
    // Visit the node associated with pRcd;
    void            (*pVisitor)(
        OBJ_ID          ,               // Object supplied below
        NODETREE_DATA   *,              // Our Tree
        NODE_DATA       *,              // Current Node
        uint16_t        ,               // Indent level
        void            *
    );
    OBJ_ID          pObjectVisit;
    // Optionally execute this before descending in the child chain.
    void            (*pChildOpen)(
        OBJ_ID          ,               // Object supplied below
        NODETREE_DATA   *,              // Our Tree
        NODE_DATA       *,              // Current Node
        uint32_t        ,               // Indent level
        void            *
    );
    OBJ_ID          pObjectOpen;
    // Optionally execute this after descending in the child chain.
    void            (*pChildClose)(
        OBJ_ID          ,               // Object supplied below
        NODETREE_DATA   *,              // Our Tree
        NODE_DATA       *,              // Current Node
        uint16_t        ,               // Indent level
        void            *
    );
    OBJ_ID          pObjectClose;
    void            *pOther;
    NODETREE_RECORD *pRcd;
    uint32_t        index;
    uint32_t        level;
} NODETREE_VISIT;




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeTree_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    // Blocks just allocates large blocks of memory and subdivides
    // them into smaller paquets.  Hopefully, this minimizes wasteful
    // memory usage. It also means that the paquets are allocated in
    // memory and stay there until deleted.
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define NODETREE_FLAG_UNIQUE OBJ_FLAG_USER1

    // Common Data
    uint32_t        root;           // Normally 1
    uint32_t        size;           // Maximum number of elements
    NODE_DATA       *pOpen;
    NODE_DATA       *pClose;
    IOBJARRAY       *pNodeArrayClass;
    OBJ_ID          pOther;

#ifdef   NODETREE_LOG
    // Informational and Warning Log Messages
    OBJ_ID          *pLog;
#endif
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
    NODETREE_DATA *     NodeTree_getSingleton (
        void
    );

    bool            NodeTree_setSingleton (
     NODETREE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  NodeTree_getSuperVtbl (
        NODETREE_DATA     *this
    );


    ERESULT         NodeTree_Assign (
        NODETREE_DATA    *this,
        NODETREE_DATA    *pOther
    );


    NODETREE_DATA *       NodeTree_Copy (
        NODETREE_DATA     *this
    );


    void            NodeTree_Dealloc (
        OBJ_ID          objId
    );


    NODETREE_DATA *     NodeTree_DeepCopy (
        NODETREE_DATA       *this
    );


#ifdef  NODETREE_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    NODETREE_DATA *       NodeTree_ParseJsonObject (
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
    ERESULT         NodeTree_ParseJsonFields (
        JSONIN_DATA     *pParser,
        NODETREE_DATA     *pObject
    );
#endif


    void *          NodeTree_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  NODETREE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NodeTree_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeTree_ToJson (
        NODETREE_DATA      *this
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
    ERESULT         NodeTree_ToJsonFields (
        NODETREE_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            NodeTree_Validate (
        NODETREE_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* NODETREE_INTERNAL_H */

