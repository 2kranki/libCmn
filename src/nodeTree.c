// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeTree.c
 *	Generated 08/04/2015 17:02:38
 *
 * Remarks:
 *  --      We use the left pointer of nodeEntry to be nextSibling
 *          and the right index for nextChild.
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
#include        "nodeEntry.h"
#include        "objList.h"
#include        <stdarg.h>
#include        <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    NAME_DATA       closeName = {{0}};
    static
    NODE_DATA       closeNode = {{0}};      // Close Node - ')'
    static
    NAME_DATA       openName  = {{0}};
    static
    NODE_DATA       openNode  = {{0}};      // Open Node - '('


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    ERESULT         nodeTree_PrintNode(
        NODETREE_DATA	*this,
        uint32_t        index,
        uint16_t        indent
    )
    {
        NODEENTRY_DATA  *pNode = OBJ_NIL;
#ifdef XYZZY
        NODEENTRY_DATA  *pChild;
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
        pName = node_getNameUTF8(nodeEntry_getNode(pNode));
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
    
    

#ifdef XYZZY
    ERESULT         nodeTree_UpDownNodePost(
        NODETREE_DATA	*this,
        NODEENTRY_DATA  *pNode,
        NODEARRAY_DATA	*pArray
    )
    {
        NODEENTRY_DATA  *pChild;
        uint32_t        i;
        uint32_t        iMax;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        iMax = nodeEntry_ChildCount(pNode);
        
        if (iMax) {
            nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_OpenNode(), NULL);
            for (i=1; i<=iMax; ++i) {
                pChild = nodeEntry_Child(pNode, i);
                if (pChild) {
                    nodeTree_UpDownNodePost(this, pChild, pArray);
                    if (ERESULT_FAILED(this->eRc)) {
                        return this->eRc;
                    }
                }
            }
            nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_CloseNode(), NULL);
        }
        nodeArray_AppendNode(pArray, (NODE_DATA *)pNode, NULL);
        
        // Return to caller.
        return true;
    }
#endif
    
    
    
    /*!
     Visit the root (or current node) then visit each child recursively 
     recording the visits in the given array. Preorder visitation is
     also known as a depth-first traversal.
     @param:    this    NODETREE_DATA object pointer
     @param:    index   Current Node Index
     @param:    pArray  NODEARRAY Pointer where visits will be recorded
     @return:   If successful, ERESULT_SUCCESS otherwise an ERESULT_*
     error.
     */
    ERESULT         nodeTree_UpDownNodePre(
        NODETREE_DATA	*this,
        uint32_t        index,              // Current Node
        NODEARRAY_DATA	*pArray
    )
    {
        NODEENTRY_DATA  *pEntry;
        NODEENTRY_DATA  *pChild;
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
            nodeArray_AppendNode(pArray, nodeEntry_getNode(pEntry), NULL);
            childIndex = nodeEntry_getChild(pEntry);
            if (childIndex) {
                nodeArray_AppendNode(pArray, nodeTree_OpenNode(), NULL);
                pChild = objArray_Get(this->pArray, childIndex);
                if (pChild) {
                    nodeTree_UpDownNodePre(this, childIndex, pArray);
                    if (ERESULT_FAILED(this->eRc)) {
                        return this->eRc;
                    }
                }
                nodeArray_AppendNode(pArray, nodeTree_CloseNode(), NULL);
            }
            childIndex = nodeEntry_getSibling(pEntry);
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
    //                       N o d e  E n t r y
    //---------------------------------------------------------------
    
    NODEENTRY_DATA * nodeTree_NodeEntry(
        NODETREE_DATA   *this,
        uint32_t        index
    )
    {
        NODEENTRY_DATA  *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( !((index > 0) && (index <= objArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        pEntry = objArray_Get(this->pArray, index);
        this->eRc = objArray_getLastError(this->pArray);
        
        return pEntry;
    }
    
    
    
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
        NODEENTRY_DATA  *pNode;
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
            // Follow Child chain.
            childIndex = nodeEntry_getChild(pNode);
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
            pVisitor(pObject, this, nodeEntry_getNode(pNode), indent);
            // Follow Sibling chain.
            childIndex = nodeEntry_getSibling(pNode);
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
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
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
        NODEENTRY_DATA  *pNode;
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
            childIndex = nodeEntry_getChild(pNode);
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
            // Follow Sibling chain.
            childIndex = nodeEntry_getSibling(pNode);
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
            pVisitor(pObject, this, nodeEntry_getNode(pNode), indent);
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    /*!
     Visit the root (or current node) then visit each child recursively.
     This is also known as a depth-first traversal.
     @param:    this    NODETREE_DATA object pointer
     @param:    pVisitor Function pointer to the routine called as each
     node is visited
     @param:    pObject Object Pointer
     @param:    index   Current Node Index
     @param:    indent  Current Level Indent
     @return:   If successful, ERESULT_SUCCESS otherwise an ERESULT_*
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
        NODEENTRY_DATA  *pNode;
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
            pVisitor(pObject, this, nodeEntry_getNode(pNode), indent);
            // Follow Child chain.
            childIndex = nodeEntry_getChild(pNode);
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
            // Follow Sibling chain.
            childIndex = nodeEntry_getSibling(pNode);
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
    
    
    
    NODE_DATA *     nodeTree_CloseNode(
    )
    {
        NODE_DATA       *pNode;
        
        if (0 == obj_getSize(&closeNode)) {
            name_InitUTF8Con(&closeName, ")");
            pNode = node_InitWithName(&closeNode, &closeName, OBJ_NIL);
            if (!(pNode == &closeNode)) {
                DEBUG_BREAK();
            }
            node_setClass(&closeNode, NODE_CLASS_CLOSE);
        }
        
        return &closeNode;
    }
    
    
    NODE_DATA *     nodeTree_OpenNode(
    )
    {
        NODE_DATA       *pNode;
        
        if (0 == obj_getSize(&openNode)) {
            name_InitUTF8Con(&openName, "(");
            pNode = node_InitWithName(&openNode, &openName, OBJ_NIL);
            if (!(pNode == &openNode)) {
                DEBUG_BREAK();
            }
            node_setClass(&openNode, NODE_CLASS_OPEN);
        }
        
        return &openNode;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

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
        NODEENTRY_DATA  *pNode;
        NODEENTRY_DATA  *pChild;
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
            childIndex = nodeEntry_getSibling(pNode);
            pChild = objArray_Get(this->pArray, childIndex);
            if (pChild) {
                while (index-- && childIndex) {
                    childIndex = nodeEntry_getSibling(pChild);
                    if (childIndex) {
                        pChild = objArray_Get(this->pArray, childIndex);
                    }
                }
            }
            if (childIndex) {
                pNodeReturn = nodeEntry_getNode(objArray_Get(this->pArray, childIndex));
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
        NODEENTRY_DATA  *pParent;
        NODEENTRY_DATA  *pEntry;
        NODEENTRY_DATA  *pChild;
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
            pEntry = nodeEntry_New(pNode);
            if (pEntry) {
                this->eRc = objArray_AppendObj(this->pArray, pEntry, &index);
                if (!ERESULT_FAILED(this->eRc)) {
                    nodeEntry_setIndex(pEntry, index);
                    node_setIndex(pNode, index);
                }
                obj_Release(pEntry);
            }
            goto eom;
        }
        
        pParent = objArray_Get(this->pArray, parent);
        if (pParent) {
            index = nodeEntry_getChild(pParent);
            if (index == 0) {     // No children
                pEntry = nodeEntry_New(pNode);
                if (pEntry) {
                    this->eRc = objArray_AppendObj(this->pArray, pEntry, &index);
                    if (!ERESULT_FAILED(this->eRc)) {
                        nodeEntry_setChild(pParent, index);
                        nodeEntry_setIndex(pEntry, index);
                        node_setIndex(pNode, index);
                        nodeEntry_setParent(pEntry,parent);
                    }
                    obj_Release(pEntry);
                }
            }
            else {   // Parent has children, so add to end of child's sibling chain.
                // index points to first child of parent
                for (;;) {
                    pChild = objArray_Get(this->pArray, index);
                    if (nodeEntry_getSibling(pChild) == 0) {  // End of Sibling Chain
                        pEntry = nodeEntry_New(pNode);
                        if (pEntry) {
                            this->eRc = objArray_AppendObj(this->pArray, pEntry, &index);
                            if (!ERESULT_FAILED(this->eRc)) {
                                nodeEntry_setSibling(pChild, index);
                                nodeEntry_setIndex(pEntry, index);
                                node_setIndex(pNode, index);
                                nodeEntry_setParent(pEntry,parent);
                            }
                            obj_Release(pEntry);
                        }
                        break;
                    }
                    index = nodeEntry_getSibling(pChild);
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
        NODEENTRY_DATA  *pParent;
        NODEENTRY_DATA  *pChild;
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
            index = nodeEntry_getChild(pParent);
            if (index == 0) {     // No children
            }
            else {   // Parent has children, so count them.
                // index points to first child of parent
                for (;;) {
                    ++count;
                    pChild = objArray_Get(this->pArray, index);
                    if (nodeEntry_getSibling(pChild) == 0) {  // End of Sibling Chain
                        break;
                    }
                    index = nodeEntry_getSibling(pChild);
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
        NODEENTRY_DATA  *pChild;
        NODEENTRY_DATA  *pChildLast = OBJ_NIL;
        NODEENTRY_DATA  *pEntry;
        NODEENTRY_DATA  *pParent;
        
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
        
        pEntry = nodeTree_NodeEntry(this, index);
        if (pEntry == OBJ_NIL) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        
        pParent = nodeTree_NodeEntry(this, parent);
        if (pParent == OBJ_NIL) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        if (0 == nodeEntry_getChild(pParent)) {     // No children to move
            this->eRc = ERESULT_SUCCESS;
            return this->eRc;
        }
        
        // Find last child if any of where to add the children.
        if (pEntry) {
            idxChild = nodeEntry_getChild(pEntry);
            if (idxChild) {
                for (;;) {
                    pChild = nodeTree_NodeEntry(this, idxChild);
                    if (pChild && (nodeEntry_getSibling(pChild) == 0)) {
                        pChildLast = pChild;
                        break;
                    }
                    idxChild = nodeEntry_getSibling(pChild);
                }
            }
        }
        
        // We add the children to the index at the end of its children list
        // and adjust the parent in the first level of children added.
        idxChild = nodeEntry_getChild(pParent);
        nodeEntry_setChild(pParent, 0);
        if (pChildLast) {
            nodeEntry_setSibling(pChildLast, idxChild);
        }
        else {
            nodeEntry_setChild(pEntry, idxChild);
        }
        for (;;) {
            pChild = nodeTree_NodeEntry(this, idxChild);
            if (pChild) {
                nodeEntry_setParent(pChild, index);
            }
            idxChild = nodeEntry_getSibling(pChild);
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
        NODEENTRY_DATA  *pEntry;
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
        
        pEntry = objArray_Get(this->pArray, index);
        pNode = nodeEntry_getNode(pEntry);
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
        NODEENTRY_DATA  *pParent;
        NODEENTRY_DATA  *pEntry;
        NODEENTRY_DATA  *pChild;
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
        
        pEntry = nodeTree_NodeEntry(this, index);
        if (pEntry == OBJ_NIL) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            goto eom;
        }
        idxParent = nodeEntry_getParent(pEntry);
        if (idxParent) {                // Not Root
            pParent = nodeTree_NodeEntry(this, idxParent);
            if (pParent) {
                // Unlink entry from sibling chain.
                idxChild = nodeEntry_getChild(pParent);
                if (idxChild == index) {    // index is at head of chain
                    nodeEntry_setChild(pParent, nodeEntry_getSibling(pEntry));
                }
                else {
                    while (idxChild) {      // index is in the chain
                        pChild = nodeTree_NodeEntry(this, idxChild);
                        if (pChild && (nodeEntry_getSibling(pChild) == index)) {
                            nodeEntry_setSibling(pChild, nodeEntry_getSibling(pEntry));
                            break;
                        }
                        idxChild = nodeEntry_getSibling(pChild);
                    }
                }
            }
        }
        
        // Now delete all the children ad infinitum.
        for (;;) {
            idxChild = nodeEntry_getChild(pEntry);
            if (idxChild) {
                pChild = nodeTree_NodeEntry(this, idxChild);
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
        NODEENTRY_DATA  *pParent;
        NODEENTRY_DATA  *pEntry;
        NODEENTRY_DATA  *pChild;
        
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
            if (nodeEntry_getChild(pParent) == 0) {     // No children
                nodeEntry_setChild(pParent, index);
                nodeEntry_setParent(pEntry,parent);
                this->eRc = ERESULT_SUCCESS;
            }
            else {   // Parent has children, so add to end of child's sibling chain.
                pChild = objArray_Get(this->pArray, nodeEntry_getChild(pParent));
                if (pChild) {
                    while (nodeEntry_getSibling(pChild)) {
                        pChild = objArray_Get(this->pArray, nodeEntry_getSibling(pChild));
                    }
                }
                if (pChild) {
                    nodeEntry_setSibling(pChild, index);
                    nodeEntry_setParent(pEntry,parent);
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
        NODEENTRY_DATA  *pEntry;
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
        
        pEntry = nodeEntry_New(pNode);
        if (pEntry) {
            this->eRc = objArray_AppendObj(this->pArray, pEntry, &index);
            if (!ERESULT_FAILED(this->eRc)) {
                nodeEntry_setIndex(pEntry, index);
                node_setIndex(pNode, index);
                this->eRc = ERESULT_SUCCESS;
            }
            else {
                this->eRc = ERESULT_GENERAL_FAILURE;
            }
            obj_Release(pEntry);
        }
        else {
            this->eRc = ERESULT_OUT_OF_MEMORY;
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

        pEntry = nodeEntry_New(pNode);
        if (pEntry) {
            this->eRc = objArray_AppendObj(this->pArray, pEntry, &index);
            if (!ERESULT_FAILED(this->eRc)) {
                nodeEntry_setIndex(pEntry, index);
                node_setIndex(pNode, index);
                this->eRc = ERESULT_SUCCESS;
            }
            else {
                this->eRc = ERESULT_GENERAL_FAILURE;
            }
            obj_Release(pEntry);
        }
        else {
            this->eRc = ERESULT_OUT_OF_MEMORY;
        }
        
        if (pNode) {
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
        
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
        NODEENTRY_DATA  *pEntry;
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
            parent = nodeEntry_getParent(pEntry);
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
        NODEENTRY_DATA  *pEntry;
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
                this->eRc = nodeArray_AppendNode(pNodes, nodeEntry_getNode(pEntry), NULL);
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
        return true;
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
        ERESULT         eRc;
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
            eRc = nodeHash_FindA(this->pProperties, pName, &pProperty);
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
        NODEENTRY_DATA  *pSibling;
        NODEENTRY_DATA  *pEntry = OBJ_NIL;
        uint32_t        childIndex;
        NODE_DATA       *pNode = OBJ_NIL;
        
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
            childIndex = nodeEntry_getChild(pSibling);
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
        if (pEntry) {
            pNode = nodeEntry_getNode(pEntry);
        }
        return pNode;
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
            AStr_AppendCharRepeatW(pStr, indent, ' ');
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
    
#ifdef XYZZY
    NODEARRAY_DATA * nodeTree_ToLinearizationPost(
        NODETREE_DATA	*cbp
    )
    {
        NODEARRAY_DATA  *pArray;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pArray = nodeArray_New();
        if (pArray) {
            nodeArray_AppendNode(pArray, nodeTree_OpenNode(), NULL);
            nodeTree_UpDownNodePost(cbp, cbp->pRootNode, pArray);
            nodeArray_AppendNode(pArray, nodeTree_CloseNode(), NULL);
        }
        
        // Return to caller.
        return pArray;
    }
#endif
    
    
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
            nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_OpenNode(), NULL);
            nodeTree_UpDownNodePre(this, 1, pArray);
            nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_CloseNode(), NULL);
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
        NODEENTRY_DATA  *pParent;
        NODEENTRY_DATA  *pEntry;
        //NODEENTRY_DATA  *pChild;
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
        NODEENTRY_DATA  *pEntry = OBJ_NIL;
        uint16_t        indent = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
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
        pVisitor(pObject, this, nodeEntry_getNode(pEntry), indent);
        objList_Add2Head(pQueue, pEntry);
        while (objList_getSize(pQueue)) {
            pEntry = objList_Tail(pQueue);
            objList_DeleteTail(pQueue);
            if (nodeEntry_getChild(pEntry)) {
                pEntry = objArray_Get(this->pArray, nodeEntry_getChild(pEntry));
                if (pEntry) {
                    pVisitor(pObject, this, nodeEntry_getNode(pEntry), indent);
                    objList_Add2Head(pQueue, pEntry);
                }
                while (nodeEntry_getSibling(pEntry)) {
                    pEntry = objArray_Get(this->pArray, nodeEntry_getSibling(pEntry));
                    if (pEntry) {
                        pVisitor(pObject, this, nodeEntry_getNode(pEntry), indent);
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


