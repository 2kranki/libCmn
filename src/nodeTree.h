// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          an Unordered Tree of Nodes (nodeTree) Header
//****************************************************************
/*
 * Program
 *			Unordered Tree of Nodes (nodeTree)
 * Purpose
 *			This object provides for an un-ordered tree of nodes.
 *          Un-ordered means that the tree nodes are not in order
 *          by name (ie key). They are in order by placement.
 *
 * Remarks
 *  1,      The left pointer of nodeEntry is used for nextSibling
 *          and the right index for nextChild.
 *  2.      By using NodeNew() and NodeLinkChild() together, one
 *          can build a tree from the bottom up which is consist-
 *          ent with recursive descent parsing. In this case, you
 *          must add the root first before using NodeNew() and
 *          NodeLinkChild().
 *
 * History
 *	08/04/2015 Generated
 *	09/19/2016 Added NodeNew(), NodeLinkChild(), and other functions
 *              that allowed the internal structure of the tree to
 *              be separate from the Node.
 *
 * References
 *  --      Tenenbaum, Langsam, and Augenstein, "Data Structures Using C", 
 *          1990, Prentice-Hall
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






#include        <cmn_defs.h>
#include        <node.h>
#include        <szTbl.h>


#ifndef         NODETREE_H
#define         NODETREE_H


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    typedef struct nodeTree_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        // Methods:
    } NODETREE_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    NODETREE_DATA * nodeTree_Alloc(
    );
    
    
    NODE_DATA *     nodeTree_CloseNode(
    );
    
    
    NODETREE_DATA * nodeTree_New(
    );
    
    
    NODE_DATA *     nodeTree_OpenNode(
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         nodeTree_getLastError(
        NODETREE_DATA   *this
    );
    
    
    uint32_t        nodeTree_getSize(
        NODETREE_DATA   *this
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Return the index'th child for the parent node.
     Example:
     @code:
     NODE_DATA      *pNode = nodeTree_Child(this,1,0);
     @endcode:
     Gets first child for root node.
     @param:    this    NODETREE_DATA object pointer
     @param:    parent  parent node index (relative to 1)
     @param:    index   child index (0 <= index < order)
     @return:   If successful, an Node object, otherwise OBJ_NIL.
     */
    NODE_DATA *     nodeTree_Child(
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
     child to be set or first available (if 0). To add a root, parent
     and child indices must be 0.
     @param:    this    NODETREE_DATA object pointer
     @param:    parent  parent node index (relative to 0, 0 == root)
     @param:    index   child index (0 <= index <= order) This index is
     relative to 1. 0 denotes first available child
     and must be set if parent index is 0.
     @param:    pNode   Non-null Node pointer to be added as a child
     @return:   If successful, an Node index, otherwise 0.
     */
    uint32_t    nodeTree_ChildAdd(
        NODETREE_DATA   *this,
        uint32_t        parent,         // Relative to 1
        NODE_DATA       *pNode
    );
    
    
    /*!
     Get the number of next level Children for a specified parent node. This
     only counts the number of children directly attached to the parent not
     any lower levels (ie parent->child->childs_child).
     @param:    this    NODETREE_DATA object pointer
     @param:    parent  parent node index (relative to 0, 0 == root)
     @return:   If successful, child count and LastError == ERESULT_SUCCESS, 
                otherwise 0 and LastError == ERESULT_* error code.
     */
    uint32_t    nodeTree_ChildCount(
        NODETREE_DATA   *this,
        uint32_t        parent          // Relative to 1
    );
    
    
    /*!
     Add a group of Children to the given parent at once. The first node provided
     will be added as a child of the parent and the remaining nodes will be added
     as siblings to that child node. So, all the nodes added will be at the same
     level in the tree.
     Example:
     @code:
     ERESULT        eRc = nodeTree_ChildrenAdd(pObject,1,pNode2,pNode3,NULL);
     Node2 will be a child of the root node and Node3 will be a sibling of
     Node2.
     @endcode:
     @param:    this    NODETREE_DATA object pointer
     @param:    parent  parent node index (relative to 0, 0 == root)
     relative to 1. 0 denotes first available child
     and must be set if parent index is 0.
     @param:    pNode   Non-null Node pointer to be added as a child
     @return:   If successful, an Node index, otherwise 0.
     */
    ERESULT         nodeTree_ChildrenAdd(
        NODETREE_DATA   *this,
        uint32_t        parent,
        ...                         // NULL Terminated list
    );
    
    
    NODETREE_DATA * nodeTree_Init(
        NODETREE_DATA   *this
    );


    NODE_DATA *  nodeTree_Node(
        NODETREE_DATA   *this,
        uint32_t        index       // Relative to 1
    );
    
    
    /*!
     Link the given tree node as a child of the specified parent.
     This method is the means to link nodes created with NodeNew()
     back into the main tree. 
     @param:    this    NODETREE_DATA object pointer
     @param:    parent  parent node index (relative to 0, 0 == root)
     @param:    index   child index (2 <= index <= order) This index is
                        relative to 1.
     @return:   If successful, an Node index, otherwise 0.
     */
    ERESULT     nodeTree_NodeLinkChild(
        NODETREE_DATA   *this,
        uint32_t        parent,
        uint32_t        index       // Relative to 1
    );
    
    
    /*!
     Add the given node to the tree without linking it in the main tree.
     This allows us to create a sub-tree that we can then merge back
     into the main tree using NodeLinkChild().
     @param:    this    NODETREE_DATA object pointer
     @param:    pNode   Non-null Node pointer to be added as a child
     @return:   If successful, a Node index, otherwise 0.
     @warning:  If we fail to add this node into the main tree, then
                we will lose it and its subtree for other processing.
     */
    uint32_t    nodeTree_NodeNew(
        NODETREE_DATA   *this,
        NODE_DATA       *pNode
    );
    
    
    /*!
     Create a new node and add it to the tree without linking it in 
     the main tree.  This allows us to create a sub-tree that we can
     then merge back into the main tree using NodeLinkChild().
     @param:    this    NODETREE_DATA object pointer
     @param:    pName   Non-null NAME_DATA pointer
     @param:    cls     Node class
     @param:    pData   Optional Object to be associated with the new
                        Node
     @return:   If successful, a Node index, otherwise 0.
     @warning:  If we fail to add this node into the main tree, then
                we will lose it and its subtree for other processing.
     */
    uint32_t    nodeTree_NodeNewUTF8(
        NODETREE_DATA   *this,
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    );
    
    
    uint32_t        nodeTree_NodeParent(
        NODETREE_DATA   *this,
        uint32_t        index
    );
    
    
    ERESULT         nodeTree_Nodes(
        NODETREE_DATA	*this,
        NODEARRAY_DATA  **ppNodes
    );
    
    
    ERESULT         nodeTree_PrintTree(
        NODETREE_DATA	*this
    );
    
    
    NODE_DATA *     nodeTree_Property(
        NODETREE_DATA   *this,
        const
        char            *pName
    );
    
    
    ERESULT         nodeTree_PropertyAdd(
        NODETREE_DATA   *this,
        NODE_DATA       *pData
    );
    
    
    uint16_t        nodeTree_PropertyCount(
        NODETREE_DATA	*this
    );
    
    
    NODEARRAY_DATA * nodeTree_Properties(
        NODETREE_DATA   *this
    );
    
    
    /*!
     Given a node return its next sibling.
     Example:
     @code:
     NODE_DATA      *pNode = nodeTree_SiblingNext(this,3);
     @endcode:
     Gets the next sibling for node 3.
     @param:    this    NODETREE_DATA object pointer
     @param:    sibling current sibling node index (relative to 1)
     @return:   If successful, an Node object, otherwise OBJ_NIL.
     */
    NODE_DATA *  nodeTree_SiblingNext(
        NODETREE_DATA   *this,
        uint32_t        sibling         // Relative to 1
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = nodeTree_ToDebugString(pObject,4);
     @endcode:
     @param:    this    NODETREE_DATA object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeTree_ToDebugString(
        NODETREE_DATA   *this,
        int             indent
    );
    
    
    /* Convert the tree to an array with open/close nodes interjected to
     * to show the tree structure. An open node is added if the current
     * node has children. A close node is added after all the children
     * are added. The tree is visited in post-order mode. This can be used
     * to scan the tree as if it was an array looking for patterns.
     */
    NODEARRAY_DATA * nodeTree_ToLinearizationPost(
        NODETREE_DATA	*this
    );

    
    /* Convert the tree to an array with open/close nodes interjected to
     * to show the tree structure. An open node is added if the current
     * node has children. A close node is added after all the children
     * are added. The tree is visited in pre-order mode. This can be used
     * to scan the tree as if it was an array looking for patterns.
     */
    NODEARRAY_DATA * nodeTree_ToLinearizationPre(
        NODETREE_DATA	*this
    );
    
    
    /*!
     Visit the root (or current node) then visit each child recursively.
     This is also known as a depth-first traversal.
     @param:    this     NODETREE_DATA object pointer
     @param:    pVisitor Function pointer to the routine called as each
     node is visited
     @return:   If successful, ERESULT_SUCCESS otherwise an ERESULT_*
     error.
     */
    ERESULT         nodeTree_VisitBreadthFirst(
        NODETREE_DATA	*this,
        void            (pVisitor)(
            OBJ_ID          ,               // Object supplied below
            NODE_DATA       *,              // Current Node
            uint16_t                        // Indent level * 4
        ),
        OBJ_ID          pObject
    );
    
    
    /* Visit each child then the root (or current node) recursively.
     */
    ERESULT         nodeTree_VisitInorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
                                   OBJ_ID,             // Object supplied below
                                   NODE_DATA *,        // Current Node
                                   uint16_t            // Indent level * 4
                                   ),
        OBJ_ID          pObject
    );
    
    
    /* Visit each child then the root (or current node) recursively.
     */
    ERESULT         nodeTree_VisitPostorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
                                   OBJ_ID,             // Object supplied below
                                   NODE_DATA *,        // Current Node
                                   uint16_t            // Indent level * 4
                                   ),
        OBJ_ID          pObject
    );
    

    /*!
     Visit the root (or current node) then visit each child recursively.
     This is also known as a depth-first traversal.
     @param:    this     NODETREE_DATA object pointer
     @param:    pVisitor Function pointer to the routine called as each
                        node is visited
     @return:   If successful, ERESULT_SUCCESS otherwise an ERESULT_*
                error.
     */
    ERESULT         nodeTree_VisitPreorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
                                  OBJ_ID,             // Object supplied below
                                  NODE_DATA *,        // Current Node
                                  uint16_t            // Indent level * 4
                                  ),
        OBJ_ID          pObject
    );
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* NODETREE_H */

