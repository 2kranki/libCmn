// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          An Array of Nodes (NodeArray) Header
//****************************************************************
/*
 * Program
 *			An Array of Nodes (NodeArray)
 * Purpose
 *          This object provides an array of node pointers. It
 *          does not store the actual node, just a pointer to
 *          it.
 *
 * Remarks
 *    1.    You can create a Queue of Nodes by using AddToTop()
 *          to add nodes to the queue and DeleteFromBottom() to
 *          remove nodes from the queue.
 *    2.    You can create a Stack of Nodes by using AddToTop()
 *          to add nodes to the stack and DeleteFromTop() to
 *          remove nodes from the stack.
 *
 * History
 *  08/08/2015 Generated
 *	01/10/2020 Regenerated
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





#include        <cmn_defs.h>
#include        <AStr.h>
#include        <I32Array.h>
#include        <Node.h>
#include        <NodeEnum.h>
#include        <ObjArray.h>
#include        <W32Str.h>


#ifndef         NODEARRAY_H
#define         NODEARRAY_H


#define   NODEARRAY_JSON_SUPPORT 1
//#define   NODEARRAY_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    //typedef struct NodeArray_data_s	NODEARRAY_DATA;         // Inherits from OBJARRAY
    //typedef struct NodeArray_class_data_s NODEARRAY_CLASS_DATA;

    typedef struct NodeArray_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEARRAY_DATA *);
    } NODEARRAY_VTBL;

    typedef struct NodeArray_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEARRAY_DATA *);
    } NODEARRAY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEARRAY_SINGLETON
    NODEARRAY_DATA * NodeArray_Shared (
        void
    );

    void            NodeArray_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeArray object if successful, otherwise OBJ_NIL.
     */
    NODEARRAY_DATA * NodeArray_Alloc (
        void
    );
    
    
    OBJ_ID          NodeArray_Class (
        void
    );
    
    
    /*!
     Search the given NULL-terminated Set of Nodes for a node that
     matches the given node using the comparison routine provided.
     @return    If successful, the node that matches from the list,
                 otherwise OBJ_NIL.
     */
    NODE_DATA *     NodeArray_MatchSet (
        int             (*pCompare)(NODE_DATA *,NODE_DATA *),
        NODE_DATA       *pNode,
        NODE_DATA       **ppNodeSet         // NULL-terminated Set of Nodes
    );


    NODEARRAY_DATA * NodeArray_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            NodeArray_setCompare (
        NODEARRAY_DATA  *this,
        int             (*pCompare)(NODE_DATA *,NODE_DATA *)
    );


    OBJARRAY_DATA *  NodeArray_getObjArray (
        NODEARRAY_DATA  *this
    );


    OBJ_ID          NodeArray_getOther (
        NODEARRAY_DATA  *this
    );

    bool            NodeArray_setOther (
        NODEARRAY_DATA  *this,
        OBJ_ID          pValue
    );


    uint32_t        NodeArray_getSize (
        NODEARRAY_DATA    *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         NodeArray_AddToTop (
        NODEARRAY_DATA  *this,
        NODE_DATA       *pObject,
        uint32_t        *pIndex
    );


    /*!
     Append the contents of the other array to this array. This is
     the same as AddToTop() of each element of the other array.
     @return    If successful, return ERESULT_SUCCESSFUL_COMPLETION
                otherwise an eResult error code.
     */
    ERESULT         NodeArray_Append (
        NODEARRAY_DATA  *this,
        NODEARRAY_DATA  *pOther
    );

    ERESULT         NodeArray_AppendNode (
        NODEARRAY_DATA  *this,
        NODE_DATA       *pObject,
        uint32_t        *pIndex
    );


    /*!
     Assign the contents of this array to the other array. The
     contents of the other array are released. Then we simply
     retain them so that they are in both arrays.
     @return    If successful, return ERESULT_SUCCESSFUL_COMPLETION
                otherwise an eResult error code.
     */
    ERESULT         NodeArray_Assign (
        NODEARRAY_DATA    *this,
        NODEARRAY_DATA    *pOther
    );


    /*!
     Copy this array. Any element of the array that has a copy method
     will have that used to create a new object. Otherwise, the object
     is just retained and added to the new array.
     @return    If successful, return a new array that must be released
                 otherwise return OBJ_NIL.
     */
    NODEARRAY_DATA * NodeArray_Copy (
        NODEARRAY_DATA  *this
    );


    NODEARRAY_DATA * NodeArray_DeepCopy (
        NODEARRAY_DATA  *this
    );


    /*!
     Remove the index'th element from the array and return it.
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODE_DATA *     NodeArray_Delete (
        NODEARRAY_DATA  *this,
        uint32_t        index
    );


    // DeleteFromBottom() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    NODE_DATA *     NodeArray_DeleteFirst (
        NODEARRAY_DATA  *this
    );


    // DeleteFromTop() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    NODE_DATA *     NodeArray_DeleteLast (
        NODEARRAY_DATA  *this
    );


    /*! Create an enumerator for the array.
     @return    If successful, an ENUM object is returned.  Otherwise,
                 OBJ_NIL.
     @warning   Remember to release the returned ENUM object.
     */
    NODEENUM_DATA * NodeArray_Enum (
        NODEARRAY_DATA  *this
    );


    /*!
     Find the first occurrence of a node in the array by name.
     @return    If successful, ERESULT_SUCCESS is returned and
                ppNode will contain the node ptr otherwise an error code
                will be returned.
     */
    NODE_DATA *     NodeArray_Find (
        NODEARRAY_DATA  *this,
        NODE_DATA       *pNode
    );

    NODE_DATA *     NodeArray_FindA (
        NODEARRAY_DATA  *this,
        int32_t         cls,
        const
        char             *pName
    );


    /*!
     Scan the array applying the given routine to each member of the
     array.  Second parameter to the Scan routine is the actual node
     address. Halt the scan if an error return code is returned
     by the scan routine.
     @param     this    Object Pointer
     @param     pScan   Scan Routine Address
     @param     pObj    First Parameter for the Scan Routine (optional)
     @param     pArg3   Third Parameter for the Scan Routine (optional)
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         NodeArray_ForEach (
        NODEARRAY_DATA  *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );


    NODE_DATA *     NodeArray_Get (
        NODEARRAY_DATA  *this,
        uint32_t        index       // Relative to 1
    );

    NODE_DATA *     NodeArray_GetFirst (
        NODEARRAY_DATA  *this
    );

    NODE_DATA *     NodeArray_GetLast (
        NODEARRAY_DATA  *this
    );


    NODEARRAY_DATA * NodeArray_Init (
        NODEARRAY_DATA  *this
    );


    ERESULT         NodeArray_Put (
        NODEARRAY_DATA  *this,
        uint32_t        index,
        NODE_DATA       *pObject
    );


    ERESULT         NodeArray_SortAscending (
        NODEARRAY_DATA    *this
    );


    /*!
     Create an new int32_t array of the classes from all nodes in this array.
     The relative position of each class in the new array should coincide with
     the relative position of the node in this array.
     @return    If successful, an i32Array object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned i32Array object.
     */
    I32ARRAY_DATA * NodeArray_ToClassArray (
        NODEARRAY_DATA  *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeArray_ToDebugString (
        NODEARRAY_DATA     *this,
        int             indent
    );
    
    
    ASTR_DATA *     NodeArray_ToString(
        NODEARRAY_DATA  *this
    );


    /*!
     Visit each node of the array in ascending index order.  Terminate
     the visiting is an ERESULT_* error code is returned by the visitor.
     @return    If successful, ERESULT_SUCCESS is returned,
                otherwise an ERESULT_* error code.
     */
    ERESULT         NodeArray_VisitAscending(
        NODEARRAY_DATA    *this,
        ERESULT         (pVisitor)(
                                   OBJ_ID,             // Object supplied below
                                   NODE_DATA *         // Current Node
                        ),
        OBJ_ID          pObject
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEARRAY_H */

