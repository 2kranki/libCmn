// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeTree_internal.h
 *	Generated 01/10/2020 16:43:19
 *
 * Notes:
 *  --	Internally NodeTree uses an ObjArray to keep track of all nodes
 *      in the tree, but not their relationships.  The relationships are
 *      maintained in the NODETREE_RECORD(s) which are allocated and kept
 *      in the Blocks part of the object.
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



    //                      Tree Record Descriptor

    // This record is in memory. It can be written/reead using
    // JSON by translating the pointers to ObjArray indices.

    #pragma pack(push, 1)
    typedef struct  NodeTree_record_s {
        uint32_t        objIndex;           // Index into objArray
        uint32_t        childIndex;         // Index into this tree
        uint32_t        parentIndex;        // Index into this tree
        uint32_t        siblingIndex;       // Index into this tree
    } NODETREE_RECORD;
    #pragma pack(pop)



    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeTree_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    OBJARRAY_DATA   *pArray;        // Root
    uint32_t        root;           // Normally 1
    uint32_t        size;           // Maximum number of elements
    NODELINK_DATA   *pOpen;
    NODELINK_DATA   *pClose;
    OBJ_ID          pNodeArrayClass;
    OBJ_ID          pOther;

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


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = NodeTree_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another NODETREE object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         NodeTree_Assign (
        NODETREE_DATA   *this,
        NODETREE_DATA   *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        NodeTree      *pCopy = NodeTree_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a NODETREE object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODETREE_DATA *     NodeTree_Copy (
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
    bool			NodeTree_Validate (
        NODETREE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODETREE_INTERNAL_H */

