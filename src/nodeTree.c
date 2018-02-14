// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeTree.c
 *	Generated 08/04/2015 17:02:38
 *
 * Remarks:
 *  --      For multi-way trees or Forests represented by a binary tree,
 *          traversal is different than normal binary tree traversal.
 *          Inorder traversal of a multi-way tree/forest is postorder
 *          traversal of the binary tree. Postorder of the multi-way
 *          tree/forest is inorder traversal of the binary tree.
 *          Preorder traversal of the multi-way tree/forest is postorder
 *          traversal of the binary tree. (Knuth, ACP, Vol 1, 3rd Ed, page 337)
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        "nodeTree_internal.h"
#include        "name_internal.h"
#include        "node_internal.h"
#include        "nodeArray.h"
#include        "nodeHash.h"
#include        "objList.h"
#include        <stdarg.h>
#include        <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    



 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    ERESULT         nodeTree_PrintNode(
        NODETREE_DATA	*this,
        uint32_t        index,
        uint16_t        indent
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
#ifdef XYZZY
        NODE_DATA       *pChild;
        uint32_t        i;
        uint32_t        iMax;
#endif
        const
        char            *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (indent) {
            ASTR_DATA       *pStr;
            pStr = AStr_NewFromCharA(indent, ' ');
            fprintf(stdout, "%s", AStr_getData(pStr));
            obj_Release(pStr);
        }
        pName = node_getNameUTF8(pNode);
        fprintf(stdout, "%s ", pName);
        mem_Free((void *)pName);
        fprintf(stdout, "\n");
        
#ifdef XYZZY
        iMax = node_ChildCount(pNode);
        for (i=1; i<=iMax; ++i) {
            pChild = node_Child(pNode, i);
            if (pChild) {
                nodeTree_PrintNode(this, pChild, indent+4);
            }
        }
#endif
        
        // Return to caller.
        return true;
    }
    
    

    ERESULT         nodeTree_UpDownNodePost(
        NODETREE_DATA	*this,
        uint32_t        index,              // Current Node
        NODEARRAY_DATA	*pArray
    )
    {
        NODE_DATA       *pNode;
        uint32_t        childIndex;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        pNode = objArray_Get(this->pArray, index);
        if (pNode) {
            childIndex = node_getChild(pNode);
            if (childIndex) {
                nodeArray_AppendNode(pArray, nodeTree_getOpenNode(this), NULL);
                this->eRc = nodeTree_UpDownNodePost(
                                                   this,
                                                   childIndex,
                                                   pArray
                );
                if (ERESULT_FAILED(this->eRc)) {
                    return this->eRc;
                }
                nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_getCloseNode(this), NULL);
            }
            // visit current node.
            nodeArray_AppendNode(pArray, pNode, NULL);
            // Follow Sibling chain.
            childIndex = node_getSibling(pNode);
            if (childIndex) {
                this->eRc = nodeTree_UpDownNodePost(
                                                   this,
                                                   childIndex,
                                                   pArray
                                                   );
                if (ERESULT_FAILED(this->eRc)) {
                    return this->eRc;
                }
            }
        }

        // Return to caller.
        return true;
    }
    
    
    
    /*!
     Visit the root (or current node) then visit each child recursively 
     recording the visits in the given array. Preorder visitation is
     also known as a depth-first traversal.
     @param     this    NODETREE_DATA object pointer
     @param     index   Current Node Index
     @param     pArray  NODEARRAY Pointer where visits will be recorded
     @return    If successful, ERESULT_SUCCESS otherwise an ERESULT_*
     error.
     */
    ERESULT         nodeTree_UpDownNodePre(
        NODETREE_DATA	*this,
        uint32_t        index,              // Current Node
        NODEARRAY_DATA	*pArray
    )
    {
        NODE_DATA       *pEntry;
        NODE_DATA       *pChild;
        uint32_t        childIndex;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        pEntry = objArray_Get(this->pArray, index);
        if (pEntry) {
            nodeArray_AppendNode(pArray, pEntry, NULL);
            childIndex = node_getChild(pEntry);
            if (childIndex) {
                nodeArray_AppendNode(pArray, nodeTree_getOpenNode(this), NULL);
                pChild = objArray_Get(this->pArray, childIndex);
                if (pChild) {
                    nodeTree_UpDownNodePre(this, childIndex, pArray);
                    if (ERESULT_FAILED(this->eRc)) {
                        return this->eRc;
                    }
                }
                nodeArray_AppendNode(pArray, nodeTree_getCloseNode(this), NULL);
            }
            childIndex = node_getSibling(pEntry);
            if (childIndex) {
                pChild = objArray_Get(this->pArray, childIndex);
                if (pChild) {
                    nodeTree_UpDownNodePre(this, childIndex, pArray);
                    if (ERESULT_FAILED(this->eRc)) {
                        return this->eRc;
                    }
                }
            }
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    

    
    //---------------------------------------------------------------
    //                      N o d e  I n o r d e r
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_NodeInorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
            OBJ_ID          ,           // Object supplied below
            NODETREE_DATA   *,          // Our Tree
            NODE_DATA       *,          // Current Node
            uint16_t                    // Indent level * 4
        ),
        OBJ_ID          pObject,
        uint32_t        index,
        uint16_t        indent
    )
    {
        NODE_DATA       *pEntry;
        uint32_t        childIndex;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pEntry = objArray_Get(this->pArray, index);
        if (pEntry) {
            // Follow Child chain.
            childIndex = node_getChild(pEntry);
            if (childIndex) {
                this->eRc = nodeTree_NodeInorder(
                                                   this,
                                                   pVisitor,
                                                   pObject,
                                                   childIndex,
                                                   indent
                                                   );
                if (ERESULT_FAILED(this->eRc)) {
                    return this->eRc;
                }
            }
            // visit current node.
            if (pEntry) {
                pVisitor(pObject, this, pEntry, indent);
            }
            else {
                DEBUG_BREAK();
            }
            if (childIndex) {
                this->eRc = nodeTree_NodeInorder(
                                                   this,
                                                   pVisitor,
                                                   pObject,
                                                   childIndex,
                                                   indent
                                                   );
                if (ERESULT_FAILED(this->eRc)) {
                    return this->eRc;
                }
            }
            // Follow Sibling chain.
            childIndex = node_getSibling(pEntry);
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      N o d e  P o s t o r d e r
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_NodePostorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
                                OBJ_ID,             // Object supplied below
                                NODETREE_DATA *,    // Our Tree
                                NODE_DATA *,        // Current Node
                                uint16_t            // Indent level * 4
                        ),
        OBJ_ID          pObject,
        uint32_t        index,
        uint16_t        indent
    )
    {
        NODE_DATA       *pNode;
        uint32_t        childIndex;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        pNode = objArray_Get(this->pArray, index);
        if (pNode) {
            // Follow Child chain.
            childIndex = node_getChild(pNode);
            if (childIndex) {
                this->eRc = nodeTree_NodePostorder(
                                                  this,
                                                  pVisitor,
                                                  pObject,
                                                  childIndex,
                                                  indent
                                                  );
                if (ERESULT_FAILED(this->eRc)) {
                    return this->eRc;
                }
            }
            // visit current node.
            pVisitor(pObject, this, pNode, indent);
            // Follow Sibling chain.
            childIndex = node_getSibling(pNode);
            if (childIndex) {
                this->eRc = nodeTree_NodePostorder(
                                                  this,
                                                  pVisitor,
                                                  pObject,
                                                  childIndex,
                                                  indent
                                                  );
                if (ERESULT_FAILED(this->eRc)) {
                    return this->eRc;
                }
            }
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    /*!
     Visit the root (or current node) then visit each child recursively.
     This is also known as a depth-first traversal.
     @param     this    NODETREE_DATA object pointer
     @param     pVisitor Function pointer to the routine called as each
                        node is visited
     @param     pObject Object Pointer
     @param     index   Current Node Index
     @param     indent  Current Level Indent
     @return    If successful, ERESULT_SUCCESS otherwise an ERESULT_*
                error.
     */
    ERESULT         nodeTree_NodePreorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
                                 OBJ_ID,             // Object supplied below
                                 NODETREE_DATA *,    // Our Tree
                                 NODE_DATA *,        // Current Node
                                 uint16_t            // Indent level * 4
                                 ),
        OBJ_ID          pObject,
        uint32_t        index,
        uint16_t        indent
    )
    {
        NODE_DATA       *pNode;
        uint32_t        childIndex;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        pNode = objArray_Get(this->pArray, index);
        if (pNode) {
            // visit current node.
            pVisitor(pObject, this, pNode, indent);
            // Follow Child chain.
            childIndex = node_getChild(pNode);
            if (childIndex) {
                this->eRc = nodeTree_NodePreorder(
                                                  this,
                                                  pVisitor,
                                                  pObject,
                                                  childIndex,
                                                  indent+1
                                                  );
                if (ERESULT_FAILED(this->eRc)) {
                    return this->eRc;
                }
            }
            // Follow Sibling chain.
            childIndex = node_getSibling(pNode);
            if (childIndex) {
                this->eRc = nodeTree_NodePreorder(
                                        this,
                                        pVisitor,
                                        pObject,
                                        childIndex,
                                        indent
                            );
                if (ERESULT_FAILED(this->eRc)) {
                    return this->eRc;
                }
            }
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODETREE_DATA *     nodeTree_Alloc(
    )
    {
        NODETREE_DATA   *this;
        uint32_t        cbSize = sizeof(NODETREE_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODETREE_DATA *     nodeTree_New(
    )
    {
        NODETREE_DATA   *this;
        
        // Do initialization.
        
        this = nodeTree_Alloc( );
        if (this) {
            this = nodeTree_Init(this);
        }
        
        // Return to caller.
        return this;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * nodeTree_getArray(
        NODETREE_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            nodeTree_setArray(
        NODETREE_DATA   *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                    C l o s e  N o d e
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeTree_getCloseNode(
        NODETREE_DATA   *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (OBJ_NIL == this->pClose) {
            pNode = node_NewWithUTF8ConAndClass(")", NODE_CLASS_CLOSE, OBJ_NIL);
            if (pNode) {
                this->pClose = pNode;
            }
        }

        return this->pClose;
    }
    

    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_getLastError(
        NODETREE_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->eRc;
    }
    
    
    bool            nodeTree_setLastError(
        NODETREE_DATA   *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    uint32_t        nodeTree_getRootIndex(
        NODETREE_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return 1;
    }
    
    
    
    uint32_t        nodeTree_getSize(
        NODETREE_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->size;
    }



    //---------------------------------------------------------------
    //                    O p e n  N o d e
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeTree_getOpenNode(
        NODETREE_DATA   *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (OBJ_NIL == this->pOpen) {
            pNode = node_NewWithUTF8ConAndClass("(", NODE_CLASS_OPEN, OBJ_NIL);
            if (pNode) {
                this->pOpen = pNode;
            }
        }
        
        return this->pOpen;
    }
    
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          C h i l d
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeTree_Child(
        NODETREE_DATA   *this,
        uint32_t        parent,
        uint32_t        index,
        uint32_t        *pIndex         // Optional Returned Index
    )
    {
        NODE_DATA       *pNode;
        NODE_DATA       *pChild;
        uint32_t        childIndex = 0;
        NODE_DATA       *pNodeReturn = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( !(parent > 0) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        pNode = objArray_Get(this->pArray, parent);
        if (pNode) {
            childIndex = node_getSibling(pNode);
            pChild = objArray_Get(this->pArray, childIndex);
            if (pChild) {
                while (index-- && childIndex) {
                    childIndex = node_getSibling(pChild);
                    if (childIndex) {
                        pChild = objArray_Get(this->pArray, childIndex);
                    }
                }
            }
            if (childIndex) {
                pNodeReturn = objArray_Get(this->pArray, childIndex);
            }
        }
        
        // Return to caller.
        if (pIndex) {
            *pIndex = childIndex;
        }
        this->eRc = objArray_getLastError(this->pArray);
        return pNodeReturn;
    }
    
 
    
    //---------------------------------------------------------------
    //                        C h i l d  A d d
    //---------------------------------------------------------------
    
    uint32_t        nodeTree_ChildAdd(
        NODETREE_DATA   *this,
        uint32_t        parent,
        NODE_DATA       *pNode
    )
    {
        NODE_DATA       *pParent;
        NODE_DATA       *pChild;
        uint32_t        index = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(parent <= objArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
        if( pNode == OBJ_NIL ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif

        // Try adding the root node.
        if (parent == 0) {
            if( !(objArray_getSize(this->pArray) == 0) ) {
                DEBUG_BREAK();
                this->eRc = ERESULT_DATA_ALREADY_EXISTS;
                return 0;
            }
            this->eRc = objArray_AppendObj(this->pArray, pNode, &index);
            if (!ERESULT_FAILED(this->eRc)) {
                node_setIndex(pNode, index);
            }
            else {
                DEBUG_BREAK();
                this->eRc = ERESULT_GENERAL_FAILURE;
                return 0;
            }
            goto eom;
        }
        
        pParent = objArray_Get(this->pArray, parent);
        if (pParent) {
            index = node_getChild(pParent);
            if (index == 0) {     // No children
                this->eRc = objArray_AppendObj(this->pArray, pNode, &index);
                if (!ERESULT_FAILED(this->eRc)) {
                    node_setChild(pParent, index);
                    node_setIndex(pNode, index);
                    node_setParent(pNode, parent);
                }
            }
            else {   // Parent has children, so add to end of child's sibling chain.
                // index points to first child of parent
                for (;;) {
                    pChild = objArray_Get(this->pArray, index);
                    if (node_getSibling(pChild) == 0) {  // End of Sibling Chain
                        this->eRc = objArray_AppendObj(this->pArray, pNode, &index);
                        if (!ERESULT_FAILED(this->eRc)) {
                            node_setSibling(pChild, index);
                            node_setIndex(pNode, index);
                            node_setParent(pNode, parent);
                        }
                        break;
                    }
                    index = node_getSibling(pChild);
                }
            }
        }
        
        // Return to caller.
    eom:
        return index;
    }
    
    
    
    //---------------------------------------------------------------
    //                    C h i l d  C o u n t
    //---------------------------------------------------------------
    
    uint32_t        nodeTree_ChildCount(
        NODETREE_DATA   *this,
        uint32_t        parent
    )
    {
        NODE_DATA       *pParent;
        NODE_DATA       *pChild;
        uint32_t        index;
        uint32_t        count = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(parent <= objArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
        if (parent == 0) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif
        
        pParent = objArray_Get(this->pArray, parent);
        if (pParent) {
            index = node_getChild(pParent);
            if (index == 0) {     // No children
            }
            else {   // Parent has children, so count them.
                // index points to first child of parent
                for (;;) {
                    ++count;
                    pChild = objArray_Get(this->pArray, index);
                    if (node_getSibling(pChild) == 0) {  // End of Sibling Chain
                        break;
                    }
                    index = node_getSibling(pChild);
                }
            }
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
    //eom:
        return count;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C h i l d r e n  A d d
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_ChildrenAdd(
        NODETREE_DATA   *this,
        uint32_t        parent,
        ...                         // NULL Terminated list
    )
    {
        va_list         pList;
        NODE_DATA       *pChild;
        uint32_t        nodeIndex;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        va_start(pList, parent);
        for (;;) {
            pChild = va_arg(pList, NODE_DATA *);
            if (pChild) {
                nodeIndex = nodeTree_ChildAdd(this, parent, pChild);
                if (nodeIndex == 0) {
                    return this->eRc;
                }
            }
            else
                break;
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C h i l d r e n  M o v e
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_ChildrenMove(
        NODETREE_DATA   *this,
        uint32_t        parent,
        uint32_t        index
    )
    {
        uint32_t        idxChild;
        NODE_DATA       *pChild;
        NODE_DATA       *pChildLast = OBJ_NIL;
        NODE_DATA       *pEntry;
        NODE_DATA       *pParent;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !((parent > 0) && (parent <= objArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        if( !((index > 0) && (index <= objArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
#endif
        
        pEntry = nodeTree_Node(this, index);
        if (pEntry == OBJ_NIL) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        
        pParent = nodeTree_Node(this, parent);
        if (pParent == OBJ_NIL) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        if (0 == node_getChild(pParent)) {     // No children to move
            this->eRc = ERESULT_SUCCESS;
            return this->eRc;
        }
        
        // Find last child if any of where to add the children.
        if (pEntry) {
            idxChild = node_getChild(pEntry);
            if (idxChild) {
                for (;;) {
                    pChild = nodeTree_Node(this, idxChild);
                    if (pChild && (node_getSibling(pChild) == 0)) {
                        pChildLast = pChild;
                        break;
                    }
                    idxChild = node_getSibling(pChild);
                }
            }
        }
        
        // We add the children to the index at the end of its children list
        // and adjust the parent in the first level of children added.
        idxChild = node_getChild(pParent);
        node_setChild(pParent, 0);
        if (pChildLast) {
            node_setSibling(pChildLast, idxChild);
        }
        else {
            node_setChild(pEntry, idxChild);
        }
        for (;;) {
            pChild = nodeTree_Node(this, idxChild);
            if (pChild) {
                node_setParent(pChild, index);
            }
            idxChild = node_getSibling(pChild);
            if (0 ==  idxChild) {
                break;
            }
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
    //eom:
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            nodeTree_Dealloc(
        OBJ_ID          objId
    )
    {
        NODETREE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        nodeTree_setArray(this, OBJ_NIL);

        if (this->pClose) {
            obj_Release(this->pClose);
            this->pClose = OBJ_NIL;
        }
        if (this->pOpen) {
            obj_Release(this->pOpen);
            this->pOpen = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODETREE_DATA *   nodeTree_Init(
        NODETREE_DATA       *this
    )
    {
        uint16_t        cbSize = sizeof(NODETREE_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, cbSize, OBJ_IDENT_NODETREE );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeTree_Vtbl);

        this->pArray = objArray_New();
        
    #ifdef NDEBUG
    #else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->size);
    #endif

        return this;
    }

     
    
    //---------------------------------------------------------------
    //                       N o d e
    //---------------------------------------------------------------
    
    NODE_DATA *  nodeTree_Node(
        NODETREE_DATA   *this,
        uint32_t        index
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return pNode;
        }
        if( !((index > 0) && (index <= objArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return pNode;
        }
#endif
        
        pNode = objArray_Get(this->pArray, index);
        this->eRc = objArray_getLastError(this->pArray);
        
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                     N o d e  D e l e t e
    //---------------------------------------------------------------
    
    ERESULT     nodeTree_NodeDelete(
        NODETREE_DATA   *this,
        uint32_t        index       // Relative to 1
    )
    {
        NODE_DATA       *pParent;
        NODE_DATA       *pEntry;
        NODE_DATA       *pChild;
        uint32_t        idxParent;
        uint32_t        idxChild;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif
        
        pEntry = nodeTree_Node(this, index);
        if (pEntry == OBJ_NIL) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            goto eom;
        }
        BREAK_FALSE((obj_getRetainCount(pEntry) ==  1));
        idxParent = node_getParent(pEntry);
        if (idxParent) {                // Not Root
            pParent = nodeTree_Node(this, idxParent);
            if (pParent) {
                // Unlink entry from sibling chain.
                idxChild = node_getChild(pParent);
                if (idxChild == index) {    // index is at head of chain
                    node_setChild(pParent, node_getSibling(pEntry));
                }
                else {
                    while (idxChild) {      // index is in the chain
                        pChild = nodeTree_Node(this, idxChild);
                        if (pChild && (node_getSibling(pChild) == index)) {
                            node_setSibling(pChild, node_getSibling(pEntry));
                            break;
                        }
                        idxChild = node_getSibling(pChild);
                    }
                }
            }
        }
        
        // Now delete all the children ad infinitum.
        for (;;) {
            idxChild = node_getChild(pEntry);
            if (idxChild) {
                pChild = nodeTree_Node(this, idxChild);
                if (pChild) {
                    this->eRc = nodeTree_NodeDelete(this, idxChild);
                    if (ERESULT_FAILED(this->eRc)) {
                        break;
                    }
                }
            }
            else {
                break;
            }
        }
        
        // Now release the entry.
        objArray_Put(this->pArray, index, OBJ_NIL);
        pEntry = OBJ_NIL;
        // NOTE -- We are releasing the entry, but leaving the array position
        //          for it. If we changed the array, then we would have to
        //          re-translate the entire tree.
        
        // Return to caller.
        if (ERESULT_FAILED(this->eRc)) {
        }
        else {
            this->eRc = ERESULT_SUCCESS;
        }
    eom:
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     N o d e  L i n k
    //---------------------------------------------------------------
    
    ERESULT     nodeTree_NodeLinkChild(
        NODETREE_DATA   *this,
        uint32_t        parent,
        uint32_t        index       // Relative to 1
    )
    {
        NODE_DATA       *pParent;
        NODE_DATA       *pEntry;
        NODE_DATA       *pChild;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(parent <= objArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif
        
        pParent = objArray_Get(this->pArray, parent);
        if (pParent) {
            pEntry = objArray_Get(this->pArray, index);
            if (pEntry == OBJ_NIL) {
                this->eRc = ERESULT_INVALID_PARAMETER;
                goto eom;
            }
            if (node_getChild(pParent) == 0) {     // No children
                node_setChild(pParent, index);
                node_setParent(pEntry, parent);
                this->eRc = ERESULT_SUCCESS;
            }
            else {   // Parent has children, so add to end of child's sibling chain.
                pChild = objArray_Get(this->pArray, node_getChild(pParent));
                if (pChild) {
                    while (node_getSibling(pChild)) {
                        pChild = objArray_Get(this->pArray, node_getSibling(pChild));
                    }
                }
                if (pChild) {
                    node_setSibling(pChild, index);
                    node_setParent(pEntry, parent);
                    this->eRc = ERESULT_SUCCESS;
                }
                else {
                    this->eRc = ERESULT_GENERAL_FAILURE;
                }
            }
        }
        else {
            this->eRc = ERESULT_INVALID_PARAMETER;
        }
        
        // Return to caller.
    eom:
        return this->eRc;
    }

    
    
    //---------------------------------------------------------------
    //                     N o d e  N e w
    //---------------------------------------------------------------
    
    uint32_t        nodeTree_NodeNew(
        NODETREE_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        uint32_t        index = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if( pNode == OBJ_NIL ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif
        
        this->eRc = objArray_AppendObj(this->pArray, pNode, &index);
        if (!ERESULT_FAILED(this->eRc)) {
            node_setIndex(pNode, index);
            this->eRc = ERESULT_SUCCESS;
        }
        else {
            this->eRc = ERESULT_GENERAL_FAILURE;
        }
        
        // Return to caller.
        return index;
    }
    
    
    uint32_t    nodeTree_NodeNewUTF8(
        NODETREE_DATA   *this,
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    )
    {
        NODEENTRY_DATA  *pEntry;
        uint32_t        index = 0;
        NODE_DATA       *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        pNode = node_NewWithUTF8ConAndClass(pName, cls, pData);
        if( pNode == OBJ_NIL ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }

        this->eRc = objArray_AppendObj(this->pArray, pNode, &index);
        if (!ERESULT_FAILED(this->eRc)) {
            node_setIndex(pNode, index);
            this->eRc = ERESULT_SUCCESS;
        }
        else {
            this->eRc = ERESULT_GENERAL_FAILURE;
        }
        
        obj_Release(pNode);
        pNode = OBJ_NIL;
        
        // Return to caller.
        return index;
    }
    
    
    
    //---------------------------------------------------------------
    //                     N o d e  P a r e n t
    //---------------------------------------------------------------
    
    uint32_t        nodeTree_NodeParent(
        NODETREE_DATA   *this,
        uint32_t        index
    )
    {
        NODE_DATA       *pEntry;
        uint32_t        parent = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if( index == 0 ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif
        
        pEntry = objArray_Get(this->pArray, index);
        if (pEntry) {
            parent = node_getParent(pEntry);
            this->eRc = ERESULT_SUCCESS;
        }
        else {
            this->eRc = ERESULT_DATA_NOT_FOUND;
        }
        
        // Return to caller.
        return parent;
    }
    
    

    //---------------------------------------------------------------
    //                         N o d e s
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_Nodes(
        NODETREE_DATA	*this,
        NODEARRAY_DATA  **ppNodes
    )
    {
        NODE_DATA       *pEntry;
        NODEARRAY_DATA  *pNodes = OBJ_NIL;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( OBJ_NIL == ppNodes ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
#endif
        
        pNodes = nodeArray_New();
        for (i=0; i<objArray_getSize(this->pArray); ++i) {
            pEntry = objArray_Get(this->pArray, i+1);
            if ( pEntry ) {
                this->eRc = nodeArray_AppendNode(pNodes, pEntry, NULL);
                if (ERESULT_FAILED(this->eRc)) {
                    obj_Release(pNodes);
                    pNodes = OBJ_NIL;
                    goto eom;
                }
            }
        }
        nodeArray_SortAscending(pNodes);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
    eom:
        if (ppNodes) {
            *ppNodes = pNodes;
        }
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P r i n t  T r e e
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_PrintTree(
        NODETREE_DATA	*this
    )
    {
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        printf("\n\n\n");
        nodeTree_PrintNode(this,1,0);
        printf("\n\n\n");
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P r o p e r t y  G e t
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeTree_Property(
        NODETREE_DATA   *this,
        const
        char            *pName
    )
    {
        //ERESULT         eRc;
        NODE_DATA       *pProperty = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pProperty = nodeHash_FindA(this->pProperties, pName);
        }
        
        // Return to caller.
        return pProperty;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P r o p e r t y  A d d
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_PropertyAdd(
        NODETREE_DATA   *this,
        NODE_DATA       *pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pData) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (OBJ_NIL == this->pProperties) {
            this->pProperties = nodeHash_New( 17 );
            if (OBJ_NIL == this->pProperties) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        eRc = nodeHash_Add( this->pProperties, pData );
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //              P r o p e r t y  C o u n t
    //---------------------------------------------------------------
    
    uint16_t        nodeTree_PropertyCount(
        NODETREE_DATA	*this
    )
    {
        uint16_t        num = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (this->pProperties) {
            num = nodeHash_getSize(this->pProperties);
        }
        
        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P r o p e r t i e s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * nodeTree_Properties(
        NODETREE_DATA   *this
    )
    {
        ERESULT         eRc;
        NODEARRAY_DATA  *pProperties = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            eRc = nodeHash_Nodes(this->pProperties, &pProperties);
        }
        
        // Return to caller.
        return pProperties;
    }
    
    
    
    //---------------------------------------------------------------
    //                    S i b l i n g  N e x t
    //---------------------------------------------------------------
    
    NODE_DATA *  nodeTree_SiblingNext(
        NODETREE_DATA   *this,
        uint32_t        sibling       // Relative to 1
    )
    {
        NODE_DATA       *pSibling;
        NODE_DATA       *pEntry = OBJ_NIL;
        uint32_t        childIndex;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(sibling && (sibling <= objArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
    #endif
        this->eRc = ERESULT_GENERAL_FAILURE;
        
        pSibling = objArray_Get(this->pArray, sibling);
        if (pSibling) {
            childIndex = node_getChild(pSibling);
            if (childIndex == 0) {     // No children
                this->eRc = ERESULT_DATA_OUT_OF_RANGE;
            }
            else {
                pEntry = objArray_Get(this->pArray, childIndex);
                this->eRc = ERESULT_SUCCESS;
            }
        }
        
        // Return to caller.
    //eom:
        return pEntry;
}



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------

    ASTR_DATA *     nodeTree_ToDebugString(
        NODETREE_DATA   *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(nodeTree) Size=%d\n",
                     this,
                     this->size
                     );
        AStr_AppendA(pStr, str);

        if (this->pArray) {
            if (((OBJ_DATA *)(this->pArray))->pVtbl->pToDebugString) {
                pWrkStr = ((OBJ_DATA *)(this->pArray))->pVtbl->pToDebugString(
                                                    this->pArray,
                                                    indent+3
                                        );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
        if (this->pProperties) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            AStr_AppendA(pStr, "Properties:\n");
            if (this->pProperties) {
                if (((OBJ_DATA *)(this->pProperties))->pVtbl->pToDebugString) {
                    pWrkStr =   ((OBJ_DATA *)(this->pProperties))->pVtbl->pToDebugString(
                                            this->pProperties,
                                            indent+6
                                );
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
        
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        j = snprintf( str, sizeof(str), " %p(nodeTree)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    

    //---------------------------------------------------------------
    //                T o  L i n e a r i z a t i o n
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * nodeTree_ToLinearizationPost(
        NODETREE_DATA	*this
    )
    {
        NODEARRAY_DATA  *pArray;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        pArray = nodeArray_New();
        if (pArray) {
            nodeArray_AppendNode(pArray, nodeTree_getOpenNode(this), NULL);
            nodeTree_UpDownNodePost(this, 1, pArray);
            nodeArray_AppendNode(pArray, nodeTree_getCloseNode(this), NULL);
            nodeArray_setOther(pArray, this);
        }
        
        // Return to caller.
        return pArray;
    }
    
    
    NODEARRAY_DATA * nodeTree_ToLinearizationPre(
        NODETREE_DATA	*this
    )
    {
        NODEARRAY_DATA  *pArray;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pArray = nodeArray_New();
        if (pArray) {
            nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_getOpenNode(this), NULL);
            nodeTree_UpDownNodePre(this, 1, pArray);
            nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_getCloseNode(this), NULL);
            nodeArray_setOther(pArray, this);
        }
        
        // Return to caller.
        return pArray;
    }
    
    
    
    //---------------------------------------------------------------
    //                        T r e e  A d d
    //---------------------------------------------------------------
    
    uint32_t        nodeTree_TreeAdd(
        NODETREE_DATA   *this,
        uint32_t        parent,
        NODETREE_DATA   *pTree
    )
    {
        NODE_DATA       *pParent;
        NODE_DATA       *pEntry;
        //NODE_DATA       *pChild;
        //uint32_t        childIndex;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(parent && (parent <= objArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
        if( pTree == OBJ_NIL ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif
        
        pParent = objArray_Get(this->pArray, parent);
        if (pParent) {
            pEntry = objArray_Get(pTree->pArray, 1);   // Get Root.
        }
        
        // Return to caller.
    //eom:
        this->eRc = ERESULT_NOT_IMPLEMENTED; //FIXME: REMOVE THIS!
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeTree_Validate(
        NODETREE_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if(this) {
            if ( obj_IsKindOf(this,OBJ_IDENT_NODETREE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(NODETREE_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                      V e r i f y
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_Verify(
        NODETREE_DATA	*this,
        const
        char            **pWhy
    )
    {
        NODE_DATA       *pEntry;
        int             i;
        int             iMax;
        uint32_t        idx;
        ERESULT         eRc = ERESULT_SUCCESS;
        NAME_DATA       *pName;
        const
        char            *pStr = NULL;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        iMax = objArray_getSize(this->pArray);
        for (i=0; i<iMax; ++i) {
            pEntry = objArray_Get(this->pArray, i+1);
            if (pEntry) {
                if (obj_getIdent(pEntry) == OBJ_IDENT_NODE) {
                }
                else {
                    DEBUG_BREAK();
                    pStr = "node entry does not contain a proper NODE!";
                    eRc = ERESULT_FAILURE;
                    break;
                }
                pName = node_getName(pEntry);
                if ((OBJ_NIL == pName) || (obj_getIdent(pName) == OBJ_IDENT_NAME)) {
                }
                else {
                    DEBUG_BREAK();
                    pStr = "node does not contain a NAME!";
                    eRc = ERESULT_FAILURE;
                    break;
                }
                idx = node_getParent(pEntry);
                if (idx && (idx <= iMax)) {
                }
                else if (0 ==  idx)
                    ;
                else {
                    DEBUG_BREAK();
                    pStr = "node entry contains an invalid Parent Index!";
                    eRc = ERESULT_FAILURE;
                    break;
                }
                idx = node_getLeft(pEntry);
                if (idx && (idx <= iMax)) {
                }
                else if (0 ==  idx)
                    ;
                else {
                    DEBUG_BREAK();
                    pStr = "node entry contains an invalid Left Index!";
                    eRc = ERESULT_FAILURE;
                    break;
                }
                idx = node_getRight(pEntry);
                if (idx && (idx <= iMax)) {
                }
                else if (0 ==  idx)
                    ;
                else {
                    DEBUG_BREAK();
                    pStr = "node entry contains an invalid Right Index!";
                    eRc = ERESULT_FAILURE;
                    break;
                }
            }
        }
        
        // Return to caller.
    //eom:
        if (pStr && pWhy) {
            *pWhy = pStr;
        }
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                    V i s i t  B r e a d t h  F i r s t
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_VisitBreadthFirst(
        NODETREE_DATA	*this,
        void            (pVisitor)(
            OBJ_ID          ,               // Object supplied below
            NODETREE_DATA   *,              // Our Tree
            NODE_DATA       *,              // Current Node
            uint16_t                        // Indent level * 4
        ),
        OBJ_ID          pObject
    )
    {
        OBJLIST_DATA    *pQueue = OBJ_NIL;
        NODE_DATA       *pEntry = OBJ_NIL;
        uint16_t        indent = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        return ERESULT_NOT_IMPLEMENTED;     //FIXME: Needs work!
        pQueue = objList_New();
        if (pQueue == OBJ_NIL) {
            DEBUG_BREAK();
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return this->eRc;
        }
        
        pEntry = objArray_Get(this->pArray, 1);    // Get the root.
        if (pEntry == OBJ_NIL) {
            this->eRc = ERESULT_SUCCESS;
            return this->eRc;
        }
        pVisitor(pObject, this, pEntry, indent);
        objList_Add2Head(pQueue, pEntry);
        while (objList_getSize(pQueue)) {
            pEntry = objList_Tail(pQueue);
            objList_DeleteTail(pQueue);
            if (node_getChild(pEntry)) {
                pEntry = objArray_Get(this->pArray, node_getChild(pEntry));
                if (pEntry) {
                    pVisitor(pObject, this, pEntry, indent);
                    objList_Add2Head(pQueue, pEntry);
                }
                while (node_getSibling(pEntry)) {
                    pEntry = objArray_Get(this->pArray, node_getSibling(pEntry));
                    if (pEntry) {
                        pVisitor(pObject, this, pEntry, indent);
                        objList_Add2Head(pQueue, pEntry);
                    }
                }
            }
        }
        
        obj_Release(pQueue);
        pQueue = OBJ_NIL;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                    V i s i t  I n o r d e r
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_VisitInorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
            OBJ_ID          ,           // Object supplied below
            NODETREE_DATA   *,          // Our Tree
            NODE_DATA       *,          // Current Node
            uint16_t                    // Indent level * 4
        ),
        OBJ_ID          pObject
        )
    {
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return ERESULT_NOT_IMPLEMENTED;     //FIXME: Needs work!
        nodeTree_NodeInorder(this, pVisitor, pObject, 1, 0);
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                    V i s i t  P o s t o r d e r
    //---------------------------------------------------------------

    ERESULT         nodeTree_VisitPostorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
                                OBJ_ID,                 // Object supplied below
                                NODETREE_DATA *,        // Our Tree
                                NODE_DATA *,            // Current Node
                                uint16_t                // Indent level * 4
                               ),
        OBJ_ID          pObject
    )
    {
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        nodeTree_NodePostorder(this, pVisitor, pObject, 1, 0);
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                    V i s i t  P r e o r d e r
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_VisitPreorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
                            OBJ_ID,             // Object supplied below
                            NODETREE_DATA *,    // Our Tree
                            NODE_DATA *,        // Current Node
                            uint16_t            // Indent level * 4
                        ),
        OBJ_ID          pObject
    )
    {
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        nodeTree_NodePreorder(this, pVisitor, pObject, 1, 0);
        
        // Return to caller.
        return true;
    }
    
    
    

    
    
#ifdef	__cplusplus
}
#endif


