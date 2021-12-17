// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  An Unordered Tree of Nodes (NodeTree) Header
//****************************************************************
/*
 * Program
 *          An Unordered Tree of Nodes (NodeTree)
 * Purpose
 *          This object provides for an un-ordered tree of nodes.
 *          Un-ordered means that the tree nodes are not in order
 *          by name (ie key). They are in order by placement.
 *
 *          This method of representation is called "The Binary
 *          Tree Representation of Trees", section 2.3.2 of
 *          "Fundamental Algorithms" (3rd Ed), Donald Knuth.
 *
 * Remarks
 *  1.      This object uses OBJ_FLAG_USER1.
 *  2.      Because this implementation uses a parent, child
 *          and sibling pointers, it does support shared sub-
 *          trees (since there is only 1 parent pointer).
 *  3,      The left pointer of the unordered binary tree is
 *          for the child pointer and the right pointer is used
 *          for the next Sibling.  All pointers are numeric
 *          indices starting from 1.
 *  4.      By using NodeNew() and NodeLinkChild() together, one
 *          can build a tree from the bottom up which is consist-
 *          ent with recursive descent parsing. In this case, you
 *          must add the root first before using NodeNew() and
 *          NodeLinkChild().
 *
 * History
 *  08/04/2015  Generated
 *  09/19/2016  Added NodeNew(), NodeLinkChild(), and other functions
 *              that allowed the internal structure of the tree to
 *              be separate from the Node.
 *  02/18/2018  Changed traversals which were based on binary trees to
 *              the appropriate scan for multi-way trees. See Knuth,
 *              pg 337.  Also, changed node's child and sibling indices
 *              to left and right indices respectively which mirrors
 *              Knuth's definition.
 *  07/01/2018  Changed base node to nodeLink for all the nodes of the
 *              tree.
 *  12/13/2018  Removed the inorder traversal of the tree. See p. 336
 *              of "Fundamental Algorithms", Donald Knuth, 3rd Edition.
 *  01/10/2020  Regenerated
 *  11/26/2021  Regenerated and changed to no longer require NodeLink.
 *              The node linkage is internal to the tree now. This
 *              a Node or its derivitive to be used.
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
#include        <Node.h>
#include        <NodeArray.h>


#ifndef         NODETREE_H
#define         NODETREE_H


//#define   NODETREE_IS_IMMUTABLE     1
#define   NODETREE_JSON_SUPPORT       1
//#define   NODETREE_SINGLETON        1
#define       NODETREE_LOG   1


#ifdef   NODETREE_LOG
#include        <logInterface.h>
#endif



#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeTree_data_s  NODETREE_DATA;          // Inherits from Blocks
    typedef struct NodeTree_class_data_s NODETREE_CLASS_DATA;  // Inherits from OBJ

    typedef struct NodeTree_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //NodeTree_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeTree_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODETREE_DATA *);
    } NODETREE_VTBL;

    typedef struct NodeTree_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeTree_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODETREE_DATA *);
    } NODETREE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODETREE_SINGLETON
    NODETREE_DATA * NodeTree_Shared (
        void
    );

    void            NodeTree_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeTree object if successful, otherwise OBJ_NIL.
     */
    NODETREE_DATA * NodeTree_Alloc (
        void
    );
    
    
    OBJ_ID          NodeTree_Class (
        void
    );
    
    
    NODETREE_DATA * NodeTree_New (
        void
    );
    
    
#ifdef  NODETREE_JSON_SUPPORT
    NODETREE_DATA * NodeTree_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NODETREE_DATA * NodeTree_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef NODETREE_LOG
    /*! @property   Log
        Allows information and warning messages to be issued.
     */
    bool            NodeTree_setLog (
        NODETREE_DATA   *this,
        OBJ_ID          pObj
    );
#endif


    /*! @property   Node Array Class
        provides the class to be used when creating an array of
        nodes which will be returned to the method caller.  The
        default is "ObjArray".
     */
    IOBJARRAY *     NodeTree_getNodeArrayClass (
        NODETREE_DATA   *this
    );

    bool            NodeTree_setNodeArrayClass (
        NODETREE_DATA   *this,
        IOBJARRAY       *pClass
    );


    NODE_DATA *     NodeTree_getNodeClose (
        NODETREE_DATA   *this
    );


    NODE_DATA *     NodeTree_getNodeOpen (
        NODETREE_DATA   *this
    );


    uint32_t        NodeTree_getRootIndex (
        NODETREE_DATA   *this
    );


    /*! @property   Size
        is the count of nodes in the tree.
     */
    uint32_t        NodeTree_getSize (
        NODETREE_DATA   *this
    );


    /*! @property   Unique
        indicates if the Node's unique property be set
        with the index number assigned to it in the tree.
        thiss property defaults to false.
     */
    bool            NodeTree_getUnique (
        NODETREE_DATA    *this
    );

    bool            NodeTree_setUnique (
        NODETREE_DATA   *this,
        bool            fValue
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Return the index'th child for the parent node.
     Example:
     @code
     NODE_DATA      *pNode = NodeTree_Child(this, 1, 0, NULL);
     @endcode
     Gets first child for root node.
     @param     this    object pointer
     @param     parent  parent node index (relative to 1)
     @param     index   child index (0 <= index < order)
     @return    If successful, an Node object, otherwise OBJ_NIL.
     */
    NODE_DATA *     NodeTree_Child (
        NODETREE_DATA  *this,
        uint32_t       parent,      // Relative to 1
        uint32_t       index,       // Relative to zero
        uint32_t       *pIndex      // Optional Returned Index
    );


    /*!
     Add a Child to the given parent if possible. If parent is zero
     and there is no root specified, then the node is added as the root.
     This method is the primary means of adding nodes to the tree.
     When a node is added, its index property is set to the tree index
     that it resides at in the tree. Child index allows a specific
     child to be set or first available (if 0).
     @param     this    object pointer
     @param     parent  parent node index (relative to 1)
     @param     pNode   Non-null Node pointer to be added as a child
     @return    If successful, an Node index, otherwise 0.
     */
    uint32_t        NodeTree_ChildAdd (
        NODETREE_DATA   *this,
        uint32_t        parent,         // Relative to 1
        NODE_DATA       *pNode
    );


    /*!
     Get the number of next level Children for a specified parent node. This
     only counts the number of children directly attached to the parent not
     any lower levels (ie parent->child->childs_child).
     @param     this    object pointer
     @param     parent  parent node index (relative to 0, 0 == root)
     @return    If successful, child count and LastError == ERESULT_SUCCESS,
                otherwise 0 and LastError == ERESULT_* error code.
     */
    uint32_t        NodeTree_ChildCount (
        NODETREE_DATA   *this,
        uint32_t        parent          // Relative to 1
    );


    /*!
     Add a group of Children to the given parent at once. The first node provided
     will be added as a child of the parent and the remaining nodes will be added
     as siblings to that child node. So, all the nodes added will be at the same
     level in the tree.
     Example:
     @code
     ERESULT        eRc = nodeTree_ChildrenAdd(pObject,1,pNode2,pNode3,NULL);
     Node2 will be a child of the root node and Node3 will be a sibling of
     Node2.
     @endcode
     @param     this    object pointer
     @param     parent  parent node index (relative to 0, 0 == root)
                        relative to 1. 0 denotes first available child
                        and must be set if parent index is 0.
     @return    LastError (If successful, LastError == ERESULT_SUCCESS,
                otherwise LastError == ERESULT_* error code).
     */
    ERESULT         NodeTree_ChildrenAdd (
        NODETREE_DATA   *this,
        uint32_t        parent,
        ...                         // NULL Terminated list of Nodes
    );


    /*!
     Move the Parent's Children to the given index's children. This moves the children
     including their children ad infinitum to be added to the children of the given
     index.
     @param     this    object pointer
     @param     parent  parent node index (relative to 1)
     @param     index   destination node index (relative to 1)
     @return    LastError (If successful, LastError == ERESULT_SUCCESS,
                otherwise LastError == ERESULT_* error code).
     */
    ERESULT         NodeTree_ChildrenMove (
        NODETREE_DATA   *this,
        uint32_t        parent,
        uint32_t        index
    );


    ERESULT         NodeTree_Disable (
        NODETREE_DATA   *this
    );


    ERESULT         NodeTree_Enable (
        NODETREE_DATA   *this
    );

   
    NODETREE_DATA * NodeTree_Init (
        NODETREE_DATA   *this
    );


    /*!
     Given a node index return its node.
     @param     this    NODETREE_DATA object pointer
     @param     index   node index (relative to 1)
     @return    If successful, an Node object, otherwise OBJ_NIL.
     */
    NODE_DATA *     NodeTree_Node (
        NODETREE_DATA   *this,
        uint32_t        index       // Relative to 1
    );


    /*!
     Delete the given tree node and its children. Any siblings should
     stay with the parent.
     @param     this    object pointer
     @param     index   node index (relative to 1)
     @return    If successful, ERESULT_SUCCESS; otherwise an ERESULT_* error code.
     */
    ERESULT         NodeTree_NodeDelete (
        NODETREE_DATA   *this,
        uint32_t        index       // Relative to 1
    );


    /*!
     Given a node return its node index.
     Node(), NodeIndex(), NodeIndexChild(), NodeIndexParent(),
     NodeIndexSibling() allow for complete tree traversal.
     @param     this    NODETREE_DATA object pointer
     @param     pNode   Non-null Node pointer
     @return    If successful, an Node object, otherwise OBJ_NIL.
     */
    uint32_t        NodeTree_NodeIndex (
        NODETREE_DATA   *this,
        NODE_DATA       *pNode
    );


    /*!
     Given a node index return its child node index.
     Node(), NodeIndex(), NodeIndexChild(), NodeIndexParent(),
     NodeIndexSibling() allow for complete tree traversal.
     @param     this    NODETREE_DATA object pointer
     @param     index   node index (relative to 1)
     @return    If successful, an Node object, otherwise OBJ_NIL.
     */
    uint32_t        NodeTree_NodeIndexChild (
        NODETREE_DATA   *this,
        uint32_t        index       // Relative to 1
    );


    /*!
     Given a node index return its parent node index.
     Node(), NodeIndex(), NodeIndexChild(), NodeIndexParent(),
     NodeIndexSibling() allow for complete tree traversal.
     @param     this    NODETREE_DATA object pointer
     @param     index   node index (relative to 1)
     @return    If successful, an Node object, otherwise OBJ_NIL.
     */
    uint32_t        NodeTree_NodeIndexParent (
        NODETREE_DATA   *this,
        uint32_t        index       // Relative to 1
    );


    /*!
     Given a node index return its parent node index.
     Node(), NodeIndex(), NodeIndexChild(), NodeIndexParent(),
     NodeIndexSibling() allow for complete tree traversal.
     @param     this    NODETREE_DATA object pointer
     @param     index   node index (relative to 1)
     @return    If successful, an Node object, otherwise OBJ_NIL.
     */
    uint32_t        NodeTree_NodeIndexSibling (
        NODETREE_DATA   *this,
        uint32_t        index       // Relative to 1
    );


    /*!
     Link the given tree node as a child of the specified parent.
     This method is the means to link nodes created with NodeNew()
     back into the main tree.
     @param     this    object pointer
     @param     parent  parent node index (relative to 1)
     @param     child   child index (2 <= index <= order) This index is
                        relative to 1.
     @return    LastError (If successful, LastError == ERESULT_SUCCESS,
                otherwise LastError == ERESULT_* error code).
     */
    ERESULT         NodeTree_NodeLinkChild (
        NODETREE_DATA   *this,
        uint32_t        parent,
        uint32_t        child           // Relative to 1
    );


    /*!
     Add the given node to the tree without linking it in the main tree.
     This allows us to create a sub-tree that we can then merge back
     into the main tree using NodeLinkChild().
     @param     this    object pointer
     @param     pNode   Non-null Node pointer to be added as a child
     @return    If successful, a Node index, otherwise 0.
     @warning   If we fail to add this node into the main tree, then
                we will lose it and its subtree for other processing.
     */
    uint32_t        NodeTree_NodeNew (
        NODETREE_DATA   *this,
        NODE_DATA       *pNode
    );

    uint32_t        NodeTree_NodeNewUTF8(
        NODETREE_DATA   *this,
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData,
        uint32_t        child1,
        uint32_t        child2
    );


    /*!
     Add a node to the end of the sibling chain for the given sibling if
     possible. If sibling is zero and there is no root defined, then the
     node is added as the root.

     This method is the secondary means of adding nodes to the tree.
     When a node is added, its index property is set to the tree index
     that it resides at in the tree.

     Using this method, you can add another tree to the root (node index
     1) since all siblings of the root are other trees.

     @param     this    object pointer
     @param     sibling sibling node index to be added to (relative to 1)
     @param     pNode   Non-null Node pointer to be added as a sibling
     @return    If successful, an Node index, otherwise 0.
     */
    uint32_t        NodeTree_SiblingAdd (
        NODETREE_DATA   *this,
        uint32_t        sibling,            // Relative to 1
        NODE_DATA       *pNode
    );


    /*!
     Get the number of siblings that are beyond the given node. This
     only counts the number of siblings directly attached to the node.

     If you call this method using 1 (ie root) for the node index, you
     will get back the number of trees in this forest less the root's
     tree.
     @param     this    object pointer
     @param     node    node index (relative to 0, 0 == root)
     @return    If successful, child count and LastError == ERESULT_SUCCESS,
                otherwise 0 and LastError == ERESULT_* error code.
     */
    uint32_t        NodeTree_SiblingCount (
        NODETREE_DATA   *this,
        uint32_t        node            // Relative to 1
    );


    /*!
     Given a node return its next sibling.
     Example:
     @code
     NODE_DATA      *pNode = NodeTree_SiblingNext(this, 3);
     @endcode
     Gets the next sibling for node 3.
     @param     this    NODETREE_DATA object pointer
     @param     sibling current sibling node index (relative to 1)
     @return    If successful, an Node object, otherwise OBJ_NIL.
     */
    NODE_DATA *     NodeTree_SiblingNext (
        NODETREE_DATA   *this,
        uint32_t        sibling         // Relative to 1
    );


    /*!
     Add a group of nodes to the given node at once as siblings.
     Example:
     @code
     ERESULT        eRc = nodeTree_ChildrenAdd(pObject,1,pNode2,pNode3,NULL);
     Node2 will be a sibling of the root node and Node3 will be a sibling of
     Node2 and the root node.
     @endcode
     @param     this    object pointer
     @param     node    node index (relative to 1, 0 == root)
     @return    LastError (If successful, LastError == ERESULT_SUCCESS,
                otherwise LastError == ERESULT_* error code).
     */
    ERESULT         NodeTree_SiblingsAdd(
        NODETREE_DATA   *this,
        uint32_t        node,
        ...                         // NULL Terminated list
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
        NODETREE_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeTree_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeTree_ToDebugString (
        NODETREE_DATA   *this,
        int             indent
    );
    

    /*! Convert the tree to an array with open/close nodes interjected to
        to show the tree structure. An open node is added if the current
        node has children. A close node is added after all the children
        are added. The tree is visited in post-order mode. This can be used
        to scan the tree as if it was an array looking for patterns.
     @param     this    object pointer
     @return    If successful, an ObjArray of NodeLink objects which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned ObjArray object.
     */
    NODEARRAY_DATA * NodeTree_ToLinearizationPost (
        NODETREE_DATA   *this
    );


    /*! Convert the tree to an array with open/close nodes interjected to
        to show the tree structure. An open node is added if the current
        node has children. A close node is added after all the children
        are added. The tree is visited in pre-order mode. This can be used
        to scan the tree as if it was an array looking for patterns.
        The other property of the node array contains a pointer to this
        tree.
     @param     this    object pointer
     @return    If successful, an ObjArray of NodeLink objects which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned ObjArray object.
     */
    NODEARRAY_DATA * NodeTree_ToLinearizationPre (
        NODETREE_DATA   *this
    );


    /*!
     Visit every node on each level of the tree level by level.
     This is also known as a breadth-first traversal.
     @param     this     object pointer
     @param     pVisitor Function pointer to the routine called as each
                        node is visited
     @return    If success, ERESULT_SUCCESS. Otherwise an ERESULT_*
                error code.
     @warning   This routine uses the Misc1 field in the object. So, it
                should not be used for anyuthing if this traversal is
                used.
     */
    ERESULT         NodeTree_VisitBreadthFirst(
        NODETREE_DATA    *this,
        void            (*pVisitor)(
            OBJ_ID          ,               // Object supplied below
            NODETREE_DATA   *,              // Our Tree
            NODE_DATA       *,              // Current Node
            uint16_t         ,              // Indent level
            void            *               // other data
        ),
        OBJ_ID          pObject,
        void            *pOther
    );


    /*!
     Visit each node in post order which conforms to "Polish Notation".
     @param     this     object pointer
     @param     pVisitor Function pointer to the routine called as each
                node is visited
     @return    LastError (If successful, LastError == ERESULT_SUCCESS,
                otherwise LastError == ERESULT_* error code).
     */
    ERESULT         NodeTree_VisitPostOrder(
        NODETREE_DATA    *this,
        void            (*pVisitor)(
                                   OBJ_ID,              // Object supplied below
                                   NODETREE_DATA *,     // Our Tree
                                   NODE_DATA *,         // Current Node
                                   uint16_t ,           // Indent level
                                   void *               // other data
                                   ),
        OBJ_ID          pObject,
        void            *pOther
    );


    /*!
     Visit the root (or current node) then visit each child recursively.
     This is also known as a depth-first traversal or Dynastic order.
     @param     this     object pointer
     @param     pVisitor Function pointer to the routine called as each
                        node is visited
     @return    LastError (If successful, LastError == ERESULT_SUCCESS,
                otherwise LastError == ERESULT_* error code).
     */
    ERESULT         NodeTree_VisitPreOrder(
        NODETREE_DATA    *this,
        void            (*pVisitor)(
                                   OBJ_ID,              // Object supplied below
                                   NODETREE_DATA *,     // Our Tree
                                   NODE_DATA *,         // Current Node
                                   uint16_t ,           // Indent level
                                   void *               // other data
                                  ),
        OBJ_ID          pObject,
        void            *pOther
    );




#ifdef  __cplusplus
}
#endif

#endif  /* NODETREE_H */

