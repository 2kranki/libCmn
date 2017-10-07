// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              A Tree of Nodes (nodeATree) Header
//****************************************************************
/*
 * Program
 *			A Tree of Nodes (nodeATree)
 * Purpose
 *			This object supports creating and manipulating a specified
 *          ordered tree of nodes. Internally, the tree is created using
 *          an array of node pointers. The root is always at index 1 
 *          and the number of children is fixed. So, it is relatively
 *          easy to calculate the index entry given the node parent
 *          and child offset.
 *
 *          Internally, this tree structure is only efficient if most
 *          of the children nodes are occuppied (ie dense tree). If
 *          the tree is sparse, it will waste a significant amount of
 *          memory.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	08/31/2016 Generated
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
#include        <node.h>


#ifndef         NODEATREE_H
#define         NODEATREE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // NODEATREE_DATA is defined in node.h

    typedef struct nodeATree_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeATree_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEATREE_DATA *);
    } NODEATREE_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to nodeATree object if successful, otherwise OBJ_NIL.
     */
    NODEATREE_DATA *     nodeATree_Alloc(
        void
    );
    
    
    /*!
     Create a new tree of given order. An order of 2 gives a binary tree,
     3 gives a ternary tree, etc.
     @param     order  number of children per node
     @return    If successful, an nodeATree object which must be released,
                 otherwise OBJ_NIL.
     @warning   Remember to release the returned nodeATree object.
     */
    NODEATREE_DATA * nodeATree_New(
        uint16_t    order
    );
    
    
    NODE_DATA *     nodeATree_CloseNode(
        void
    );
    
    NODE_DATA *     nodeATree_OpenNode(
        void
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         nodeATree_getLastError(
        NODEATREE_DATA *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Return the index'th child for the parent node.
     Example:
     @code
     NODE_DATA      *pNode = nodeATree_Child(this,1,0);
     @endcode
     Gets first child for root node.
     @param     this    nodeATree object pointer
     @param     parent  parent node index (relative to 1)
     @param     index   child index (0 <= index < order)
     @return    If successful, an Node object, otherwise OBJ_NIL.
     */
    NODE_DATA *  nodeATree_Child(
        NODEATREE_DATA *this,
        uint32_t        parent,         // Relative to 1
        uint32_t        index,          // Relative to zero
        uint32_t        *pIndex         // Optional Returned Index
    );


    /*!
     Add a Child to the given parent if possible. If parent is zero
     and there is no root specified, then the node is added as the root.
     This method is the primary means of adding nodes to the tree.
     When a node is added, its index property is set to the tree index
     that it resides at in the tree. Child index allows a specific
     child to be set or first available (if 0). To add a root, parent
     and child indices must be 0.
     @param     this    nodeATree object pointer
     @param     parent  parent node index (relative to 0, 0 == root)
     @param     index   child index (0 <= index <= order) This index is
                        relative to 1. 0 denotes first available child
                        and must be set if parent index is 0.
     @param     pNode   Non-null Node pointer to be added as a child
     @return    If successful, an Node index, otherwise 0.
     */
    uint32_t    nodeATree_ChildAdd(
        NODEATREE_DATA *this,
        uint32_t        parent,         // Relative to 1
        uint32_t        index,          // Relative to 0
        NODE_DATA       *pNode
    );
    
    
    NODEATREE_DATA * nodeATree_Init(
        NODEATREE_DATA  *this,
        uint16_t        order
    );


    NODE_DATA *  nodeATree_Node(
        NODEATREE_DATA *this,
        uint32_t        index       // Relative to 1
    );
    
    
    NODE_DATA *  nodeATree_Parent(
        NODEATREE_DATA *this,
        uint32_t        index       // Relative to 1 and > 1
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = nodeATree_ToDebugString(this,4);
     @endcode
     @param     this    nodeATree object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    nodeATree_ToDebugString(
        NODEATREE_DATA  *this,
        int             indent
    );
    
    
    /* Convert the tree to an array with open/close nodes interjected to
     * to show the tree structure. An open node is added if the current
     * node has children. A close node is added after all the children
     * are added. The tree is visited in pre-order mode. This can be used
     * to scan the tree as if it was an array looking for patterns.
     */
    NODEARRAY_DATA * nodeATree_ToLinearizationPre(
        NODEATREE_DATA	*this
    );
    
    
    /* Visit the root (or current node) then visit each child recursively.
     */
    ERESULT         nodeATree_VisitPreorder(
        NODEATREE_DATA	*this,
        void            (pVisitor)(
            OBJ_ID,             // Object supplied below
            NODEATREE_DATA *,   // Our Tree
            NODE_DATA *,        // Current Node
            uint16_t            // Indent level * 4
        ),
        OBJ_ID          pObject
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEATREE_H */

