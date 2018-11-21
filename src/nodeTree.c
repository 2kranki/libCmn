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
#include        "nodeLink_internal.h"
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
        NODELINK_DATA   *pNode = OBJ_NIL;
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
        pName = node_getNameUTF8((NODE_DATA *)pNode);
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
        NODELINK_DATA   *pNode;
        uint32_t        childIndex;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        pNode = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
        if (pNode) {
            childIndex = nodeLink_getChild(pNode);
            if (childIndex) {
                nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_getOpenNode(this), NULL);
                eRc = nodeTree_UpDownNodePost(
                                                   this,
                                                   childIndex,
                                                   pArray
                );
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
                nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_getCloseNode(this), NULL);
            }
            // visit current node.
            nodeArray_AppendNode(pArray, (NODE_DATA *)pNode, NULL);
            // Follow Sibling chain.
            childIndex = nodeLink_getSibling(pNode);
            if (childIndex) {
                eRc = nodeTree_UpDownNodePost(
                                                   this,
                                                   childIndex,
                                                   pArray
                                                   );
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
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
        NODELINK_DATA   *pEntry;
        NODELINK_DATA   *pChild;
        uint32_t        childIndex;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
        if (pEntry) {
            nodeArray_AppendNode(pArray, (NODE_DATA *)pEntry, NULL);
            childIndex = nodeLink_getChild(pEntry);
            if (childIndex) {
                nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_getOpenNode(this), NULL);
                pChild = (NODELINK_DATA *)nodeArray_Get(this->pArray, childIndex);
                if (pChild) {
                    eRc = nodeTree_UpDownNodePre(this, childIndex, pArray);
                    if (ERESULT_FAILED(eRc)) {
                        return eRc;
                    }
                }
                nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_getCloseNode(this), NULL);
            }
            childIndex = nodeLink_getSibling(pEntry);
            if (childIndex) {
                pChild = (NODELINK_DATA *)nodeArray_Get(this->pArray, childIndex);
                if (pChild) {
                    eRc = nodeTree_UpDownNodePre(this, childIndex, pArray);
                    if (ERESULT_FAILED(eRc)) {
                        return eRc;
                    }
                }
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    

    
    //---------------------------------------------------------------
    //                      N o d e  I n o r d e r
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_NodeInorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
            OBJ_ID          ,           // Object supplied below
            NODETREE_DATA   *,          // Our Tree
            NODELINK_DATA   *,          // Current Node
            uint16_t                    // Indent level * 4
        ),
        OBJ_ID          pObject,
        uint32_t        index,
        uint16_t        indent
    )
    {
        NODELINK_DATA   *pEntry;
        uint32_t        childIndex;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
        if (pEntry) {
            // Follow Child chain.
            childIndex = nodeLink_getChild(pEntry);
            if (childIndex) {
                eRc = nodeTree_NodeInorder(
                                                   this,
                                                   pVisitor,
                                                   pObject,
                                                   childIndex,
                                                   indent
                                                   );
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
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
                eRc = nodeTree_NodeInorder(
                                                   this,
                                                   pVisitor,
                                                   pObject,
                                                   childIndex,
                                                   indent
                                                   );
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
            // Follow Sibling chain.
            childIndex = nodeLink_getSibling(pEntry);
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      N o d e  P o s t o r d e r
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_NodePostorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
                                OBJ_ID,             // Object supplied below
                                NODETREE_DATA *,    // Our Tree
                                NODELINK_DATA *,    // Current Node
                                uint16_t            // Indent level * 4
                        ),
        OBJ_ID          pObject,
        uint32_t        index,
        uint16_t        indent
    )
    {
        NODELINK_DATA   *pNode;
        uint32_t        childIndex;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNode = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
        if (pNode) {
            // Follow Child chain.
            childIndex = nodeLink_getChild(pNode);
            if (childIndex) {
                eRc = nodeTree_NodePostorder(
                                                  this,
                                                  pVisitor,
                                                  pObject,
                                                  childIndex,
                                                  indent
                                                  );
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
            // visit current node.
            pVisitor(pObject, this, pNode, indent);
            // Follow Sibling chain.
            childIndex = nodeLink_getSibling(pNode);
            if (childIndex) {
                eRc = nodeTree_NodePostorder(
                                                  this,
                                                  pVisitor,
                                                  pObject,
                                                  childIndex,
                                                  indent
                                                  );
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
                                 NODELINK_DATA *,    // Current Node
                                 uint16_t            // Indent level * 4
                                 ),
        OBJ_ID          pObject,
        uint32_t        index,
        uint16_t        indent
    )
    {
        NODELINK_DATA   *pNode;
        uint32_t        childIndex;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNode = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
        if (pNode) {
            // visit current node.
            pVisitor(pObject, this, pNode, indent);
            // Follow Child chain.
            childIndex = nodeLink_getChild(pNode);
            if (childIndex) {
                eRc = nodeTree_NodePreorder(
                                                  this,
                                                  pVisitor,
                                                  pObject,
                                                  childIndex,
                                                  indent+1
                                                  );
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
            // Follow Sibling chain.
            childIndex = nodeLink_getSibling(pNode);
            if (childIndex) {
                eRc = nodeTree_NodePreorder(
                                        this,
                                        pVisitor,
                                        pObject,
                                        childIndex,
                                        indent
                            );
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
    
    NODEARRAY_DATA * nodeTree_getArray(
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
        NODEARRAY_DATA  *pValue
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
    
    NODELINK_DATA * nodeTree_getCloseNode(
        NODETREE_DATA   *this
    )
    {
        NODELINK_DATA   *pNode = OBJ_NIL;
        
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (OBJ_NIL == this->pClose) {
            pNode = nodeLink_NewWithUTF8ConAndClass(")", NODE_CLASS_CLOSE, OBJ_NIL);
            if (pNode) {
                this->pClose = pNode;
            }
        }

        return this->pClose;
    }
    

    bool            nodeTree_setCloseNode(
        NODETREE_DATA   *this,
        NODELINK_DATA   *pValue
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
        if (this->pClose) {
            obj_Release(this->pClose);
        }
        this->pClose = pValue;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                   N o d e  A r r a y  C l a s s
    //---------------------------------------------------------------
    
    OBJ_ID          nodeTree_getNodeArrayClass(
        NODETREE_DATA   *this
    )
    {
        
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return this->pNodeArrayClass;
    }
    
    
    bool          nodeTree_setNodeArrayClass(
        NODETREE_DATA   *this,
        OBJ_ID          pClass
    )
    {
        
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pNodeArrayClass = pClass;
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                    R o o t  I n d e x
    //---------------------------------------------------------------
    
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
    
    NODELINK_DATA * nodeTree_getOpenNode(
        NODETREE_DATA   *this
    )
    {
        NODELINK_DATA   *pNode = OBJ_NIL;
        
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (OBJ_NIL == this->pOpen) {
            pNode = nodeLink_NewWithUTF8ConAndClass("(", NODE_CLASS_OPEN, OBJ_NIL);
            if (pNode) {
                this->pOpen = pNode;
            }
        }
        
        return this->pOpen;
    }
    
    
    bool            nodeTree_setOpenNode(
        NODETREE_DATA   *this,
        NODELINK_DATA   *pValue
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
        if (this->pOpen) {
            obj_Release(this->pOpen);
        }
        this->pOpen = pValue;
        
        return true;
    }
    
    

    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          C h i l d
    //---------------------------------------------------------------
    
    NODELINK_DATA * nodeTree_Child(
        NODETREE_DATA   *this,
        uint32_t        parent,
        uint32_t        index,
        uint32_t        *pIndex         // Optional Returned Index
    )
    {
        NODELINK_DATA   *pNode;
        NODELINK_DATA   *pChild;
        uint32_t        childIndex = 0;
        NODELINK_DATA   *pNodeReturn = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
        if( !(parent > 0) ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
#endif
        
        pNode = (NODELINK_DATA *)nodeArray_Get(this->pArray, parent);
        if (pNode) {
            childIndex = nodeLink_getSibling(pNode);
            pChild = (NODELINK_DATA *)nodeArray_Get(this->pArray, childIndex);
            if (pChild) {
                while (index-- && childIndex) {
                    childIndex = nodeLink_getSibling(pChild);
                    if (childIndex) {
                        pChild = (NODELINK_DATA *)nodeArray_Get(this->pArray, childIndex);
                    }
                }
            }
            if (childIndex) {
                pNodeReturn = (NODELINK_DATA *)nodeArray_Get(this->pArray, childIndex);
            }
        }
        
        // Return to caller.
        if (pIndex) {
            *pIndex = childIndex;
        }
        return pNodeReturn;
    }
    
 
    
    //---------------------------------------------------------------
    //                        C h i l d  A d d
    //---------------------------------------------------------------
    
    uint32_t        nodeTree_ChildAdd(
        NODETREE_DATA   *this,
        uint32_t        parent,
        NODELINK_DATA   *pNode
    )
    {
        NODELINK_DATA   *pParent;
        NODELINK_DATA   *pChild;
        uint32_t        index = 0;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return 0;
        }
        if( !(parent <= nodeArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
        if( pNode == OBJ_NIL || (!obj_IsKindOf(pNode, OBJ_IDENT_NODELINK)) ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
#endif
        nodeLink_setChild(pNode, 0);
        nodeLink_setParent(pNode, 0);
        nodeLink_setSibling(pNode, 0);

        // Try adding the root node.
        if (parent == 0) {
            if( !(nodeArray_getSize(this->pArray) == 0) ) {
                DEBUG_BREAK();
                obj_setLastError(this, ERESULT_DATA_ALREADY_EXISTS);
                return 0;
            }
            eRc = nodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
            if (!ERESULT_FAILED(eRc)) {
                nodeLink_setIndex(pNode, index);
            }
            else {
                DEBUG_BREAK();
                obj_setLastError(this, ERESULT_GENERAL_FAILURE);
                return 0;
            }
            goto eom;
        }
        
        pParent = (NODELINK_DATA *)nodeArray_Get(this->pArray, parent);
        if (pParent) {
            index = nodeLink_getChild(pParent);
            if (index == 0) {     // No children
                eRc = nodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
                if (!ERESULT_FAILED(eRc)) {
                    nodeLink_setChild(pParent, index);
                    nodeLink_setIndex(pNode, index);
                    nodeLink_setParent(pNode, parent);
                }
            }
            else {   // Parent has children, so add to end of child's sibling chain.
                // index points to first child of parent
                for (;;) {
                    pChild = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
                    if (nodeLink_getSibling(pChild) == 0) {  // End of Sibling Chain
                        eRc = nodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
                        if (!ERESULT_FAILED(eRc)) {
                            nodeLink_setSibling(pChild, index);
                            nodeLink_setIndex(pNode, index);
                            nodeLink_setParent(pNode, parent);
                        }
                        break;
                    }
                    index = nodeLink_getSibling(pChild);
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
        NODELINK_DATA   *pParent;
        NODELINK_DATA   *pChild;
        uint32_t        index;
        uint32_t        count = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return 0;
        }
        if( !(parent <= nodeArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
        if (parent == 0) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
#endif
        
        pParent = (NODELINK_DATA *)nodeArray_Get(this->pArray, parent);
        if (pParent) {
            index = nodeLink_getChild(pParent);
            if (index == 0) {     // No children
            }
            else {   // Parent has children, so count them.
                // index points to first child of parent
                for (;;) {
                    ++count;
                    pChild = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
                    if (nodeLink_getSibling(pChild) == 0) {  // End of Sibling Chain
                        break;
                    }
                    index = nodeLink_getSibling(pChild);
                }
            }
        }
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
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
        NODELINK_DATA   *pChild;
        uint32_t        nodeIndex;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        va_start(pList, parent);
        for (;;) {
            pChild = va_arg(pList, NODELINK_DATA *);
            if (pChild) {
                nodeIndex = nodeTree_ChildAdd(this, parent, pChild);
                if (nodeIndex == 0) {
                    eRc = obj_getLastError(this);
                    return eRc;
                }
            }
            else
                break;
        }
        
        // Return to caller.
        eRc = obj_getLastError(this);
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     C h i l d r e n  M o v e
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_ChildrenMove(
        NODETREE_DATA   *this,
        uint32_t        parent,
        uint32_t        index
    )
    {
        uint32_t        idxChild;
        NODELINK_DATA   *pChild;
        NODELINK_DATA   *pChildLast = OBJ_NIL;
        NODELINK_DATA   *pEntry;
        NODELINK_DATA   *pParent;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !((parent > 0) && (parent <= nodeArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if( !((index > 0) && (index <= nodeArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = nodeTree_Node(this, index);
        if (pEntry == OBJ_NIL) {
            return ERESULT_INVALID_PARAMETER;
        }
        
        pParent = nodeTree_Node(this, parent);
        if (pParent == OBJ_NIL) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (0 == nodeLink_getChild(pParent)) {     // No children to move
            return ERESULT_SUCCESS;
        }
        
        // Find last child if any of where to add the children.
        if (pEntry) {
            idxChild = nodeLink_getChild(pEntry);
            if (idxChild) {
                for (;;) {
                    pChild = nodeTree_Node(this, idxChild);
                    if (pChild && (nodeLink_getSibling(pChild) == 0)) {
                        pChildLast = pChild;
                        break;
                    }
                    idxChild = nodeLink_getSibling(pChild);
                }
            }
        }
        
        // We add the children to the index at the end of its children list
        // and adjust the parent in the first level of children added.
        idxChild = nodeLink_getChild(pParent);
        nodeLink_setChild(pParent, 0);
        if (pChildLast) {
            nodeLink_setSibling(pChildLast, idxChild);
        }
        else {
            nodeLink_setChild(pEntry, idxChild);
        }
        for (;;) {
            pChild = nodeTree_Node(this, idxChild);
            if (pChild) {
                nodeLink_setParent(pChild, index);
            }
            idxChild = nodeLink_getSibling(pChild);
            if (0 ==  idxChild) {
                break;
            }
        }

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    //eom:
        return eRc;
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
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

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

        this->pNodeArrayClass = nodeArray_Class( );
        this->pArray = nodeArray_New();
        if (OBJ_NIL == this->pArray) {
            obj_Release(this);
            return OBJ_NIL;
        }

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
    
    NODELINK_DATA * nodeTree_Node(
        NODETREE_DATA   *this,
        uint32_t        index
    )
    {
        NODELINK_DATA   *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return pNode;
        }
        if( !((index > 0) && (index <= nodeArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return pNode;
        }
#endif
        
        pNode = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
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
        NODELINK_DATA   *pParent;
        NODELINK_DATA   *pEntry;
        NODELINK_DATA   *pChild;
        uint32_t        idxParent;
        uint32_t        idxChild;
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = nodeTree_Node(this, index);
        if (pEntry == OBJ_NIL) {
            return ERESULT_INVALID_PARAMETER;
        }
        BREAK_FALSE((obj_getRetainCount(pEntry) ==  1));
        idxParent = nodeLink_getParent(pEntry);
        if (idxParent) {                // Not Root
            pParent = nodeTree_Node(this, idxParent);
            if (pParent) {
                // Unlink entry from sibling chain.
                idxChild = nodeLink_getChild(pParent);
                if (idxChild == index) {    // index is at head of chain
                    nodeLink_setChild(pParent, nodeLink_getSibling(pEntry));
                }
                else {
                    while (idxChild) {      // index is in the chain
                        pChild = nodeTree_Node(this, idxChild);
                        if (pChild && (nodeLink_getSibling(pChild) == index)) {
                            nodeLink_setSibling(pChild, nodeLink_getSibling(pEntry));
                            break;
                        }
                        idxChild = nodeLink_getSibling(pChild);
                    }
                }
            }
        }
        
        // Now delete all the children ad infinitum.
        for (;;) {
            idxChild = nodeLink_getChild(pEntry);
            if (idxChild) {
                pChild = nodeTree_Node(this, idxChild);
                if (pChild) {
                    eRc = nodeTree_NodeDelete(this, idxChild);
                    if (ERESULT_FAILED(eRc)) {
                        break;
                    }
                }
            }
            else {
                break;
            }
        }
        
        // Now release the entry.
        nodeArray_Put(this->pArray, index, OBJ_NIL);
        pEntry = OBJ_NIL;
        // NOTE -- We are releasing the entry, but leaving the array position
        //          for it. If we changed the array, then we would have to
        //          re-translate the entire tree.
        
        // Return to caller.
        if (ERESULT_FAILED(eRc)) {
        }
        else {
            eRc = ERESULT_SUCCESS;
        }
    eom:
        return eRc;
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
        NODELINK_DATA   *pParent;
        NODELINK_DATA   *pEntry;
        NODELINK_DATA   *pChild;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !(parent <= nodeArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pParent = (NODELINK_DATA *)nodeArray_Get(this->pArray, parent);
        if (pParent) {
            pEntry = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
            if (pEntry == OBJ_NIL) {
                return ERESULT_INVALID_PARAMETER;
            }
            if (nodeLink_getChild(pParent) == 0) {     // No children
                nodeLink_setChild(pParent, index);
                nodeLink_setParent(pEntry, parent);
                eRc = ERESULT_SUCCESS;
            }
            else {   // Parent has children, so add to end of child's sibling chain.
                pChild = (NODELINK_DATA *)nodeArray_Get(this->pArray, nodeLink_getChild(pParent));
                if (pChild) {
                    while (nodeLink_getSibling(pChild)) {
                        pChild = (NODELINK_DATA *)nodeArray_Get(this->pArray, nodeLink_getSibling(pChild));
                    }
                }
                if (pChild) {
                    nodeLink_setSibling(pChild, index);
                    nodeLink_setParent(pEntry, parent);
                    eRc = ERESULT_SUCCESS;
                }
                else {
                    eRc = ERESULT_GENERAL_FAILURE;
                }
            }
        }
        else {
            eRc = ERESULT_INVALID_PARAMETER;
        }
        
        // Return to caller.
    eom:
        return eRc;
    }

    
    
    //---------------------------------------------------------------
    //                     N o d e  N e w
    //---------------------------------------------------------------
    
    uint32_t        nodeTree_NodeNew(
        NODETREE_DATA   *this,
        NODELINK_DATA   *pNode
    )
    {
        uint32_t        index = 0;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if((pNode == OBJ_NIL) || (!obj_IsKindOf(pNode, OBJ_IDENT_NODELINK))) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
#endif
        
        eRc = nodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
        if (!ERESULT_FAILED(eRc)) {
            nodeLink_setIndex(pNode, index);
            obj_setLastError(this, ERESULT_SUCCESS);
        }
        else {
            obj_setLastError(this, ERESULT_GENERAL_FAILURE);
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
        //NODEENTRY_DATA  *pEntry;
        uint32_t        index = 0;
        NODELINK_DATA   *pNode;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        pNode = nodeLink_NewWithUTF8ConAndClass(pName, cls, pData);
        if( pNode == OBJ_NIL ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }

        eRc = nodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
        if (!ERESULT_FAILED(eRc)) {
            nodeLink_setIndex(pNode, index);
            obj_setLastError(this, ERESULT_SUCCESS);
        }
        else {
            obj_setLastError(this, ERESULT_GENERAL_FAILURE);
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
        NODELINK_DATA   *pEntry;
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
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
#endif
        
        pEntry = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
        if (pEntry) {
            parent = nodeLink_getParent(pEntry);
            obj_setLastError(this, ERESULT_SUCCESS);
        }
        else {
            obj_setLastError(this, ERESULT_DATA_NOT_FOUND);
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
        NODELINK_DATA   *pEntry;
        NODEARRAY_DATA  *pNodes = OBJ_NIL;
        uint32_t        i;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == ppNodes ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNodes = nodeArray_New();
        for (i=0; i<nodeArray_getSize(this->pArray); ++i) {
            pEntry = (NODELINK_DATA *)nodeArray_Get(this->pArray, i+1);
            if (pEntry) {
                eRc = nodeArray_AppendNode(pNodes, (NODE_DATA *)pEntry, NULL);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(pNodes);
                    pNodes = OBJ_NIL;
                    goto eom;
                }
            }
        }
        nodeArray_SortAscending(pNodes);
        
        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        if (ppNodes) {
            *ppNodes = pNodes;
        }
        return eRc;
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
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        printf("\n\n\n");
        nodeTree_PrintNode(this,1,0);
        printf("\n\n\n");
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                   S i b l i n g  A d d
    //---------------------------------------------------------------
    
    uint32_t        nodeTree_SiblingAdd(
        NODETREE_DATA   *this,
        uint32_t        sibling,
        NODELINK_DATA   *pNode
    )
    {
        //NODELINK_DATA   *pParent;
        NODELINK_DATA   *pSibling;
        uint32_t        index = 0;
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(sibling <= nodeArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
        if( pNode == OBJ_NIL  || (!obj_IsKindOf(pNode, OBJ_IDENT_NODELINK))) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
#endif
        nodeLink_setChild(pNode, 0);
        nodeLink_setParent(pNode, 0);
        nodeLink_setSibling(pNode, 0);

        // Try adding the root node.
        if (sibling == 0) {
            if( !(nodeArray_getSize(this->pArray) == 0) ) {
                DEBUG_BREAK();
                obj_setLastError(this, ERESULT_DATA_ALREADY_EXISTS);
                return 0;
            }
            eRc = nodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
            if (!ERESULT_FAILED(eRc)) {
                nodeLink_setIndex(pNode, index);
            }
            else {
                DEBUG_BREAK();
                obj_setLastError(this, ERESULT_GENERAL_FAILURE);
                return 0;
            }
            goto eom;
        }
        
        pSibling = (NODELINK_DATA *)nodeArray_Get(this->pArray, sibling);
        if (pSibling) {
            index = nodeLink_getSibling(pSibling);
            if (index == 0) {     // No siblings
                eRc = nodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
                if (!ERESULT_FAILED(eRc)) {
                    nodeLink_setSibling(pSibling, index);
                    nodeLink_setIndex(pNode, index);
                    nodeLink_setParent(pNode, nodeLink_getParent(pSibling));
                }
            }
            else {  // Sibling has other siblings, so add to end of sibling chain.
                    // index points to next sibling.
                for (;;) {
                    pSibling = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
                    if (nodeLink_getSibling(pSibling) == 0) {  // End of Sibling Chain
                        eRc = nodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
                        if (!ERESULT_FAILED(eRc)) {
                            nodeLink_setSibling(pSibling, index);
                            nodeLink_setIndex(pNode, index);
                            nodeLink_setParent(pNode, nodeLink_getParent(pSibling));
                        }
                        break;
                    }
                    index = nodeLink_getSibling(pSibling);
                }
            }
        }
        
        // Return to caller.
    eom:
        obj_setLastError(this, eRc);
        return index;
    }
    
    
    
    //---------------------------------------------------------------
    //                  S i b l i n g  C o u n t
    //---------------------------------------------------------------
    
    uint32_t        nodeTree_SiblingCount(
        NODETREE_DATA   *this,
        uint32_t        node
    )
    {
        NODELINK_DATA   *pSibling;
        uint32_t        count = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(node <= nodeArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
        if (node == 0) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
#endif
        
        pSibling = (NODELINK_DATA *)nodeArray_Get(this->pArray, node);
        if (pSibling) {
            node = nodeLink_getSibling(pSibling);
            if (node == 0) {     // No children
            }
            else {  // Sibling has other siblings, so count them.
                    // index points to next sibling
                for (;;) {
                    ++count;
                    pSibling = (NODELINK_DATA *)nodeArray_Get(this->pArray, node);
                    if (nodeLink_getSibling(pSibling) == 0) {  // End of Sibling Chain
                        break;
                    }
                    node = nodeLink_getSibling(pSibling);
                }
            }
        }
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        //eom:
        return count;
    }
    
    
    
    //---------------------------------------------------------------
    //                    S i b l i n g  N e x t
    //---------------------------------------------------------------
    
    NODELINK_DATA * nodeTree_SiblingNext(
        NODETREE_DATA   *this,
        uint32_t        sibling       // Relative to 1
    )
    {
        NODELINK_DATA   *pSibling;
        NODELINK_DATA   *pEntry = OBJ_NIL;
        uint32_t        childIndex;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(sibling && (sibling <= nodeArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
    #endif
        obj_setLastError(this, ERESULT_GENERAL_FAILURE);
        
        pSibling = (NODELINK_DATA *)nodeArray_Get(this->pArray, sibling);
        if (pSibling) {
            childIndex = nodeLink_getChild(pSibling);
            if (childIndex == 0) {     // No children
                obj_setLastError(this, ERESULT_DATA_OUT_OF_RANGE);
            }
            else {
                pEntry = (NODELINK_DATA *)nodeArray_Get(this->pArray, childIndex);
                obj_setLastError(this, ERESULT_SUCCESS);
            }
        }
        
        // Return to caller.
    //eom:
        return pEntry;
}



    //---------------------------------------------------------------
    //                  S i b l i n g s  A d d
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_SiblingsAdd(
        NODETREE_DATA   *this,
        uint32_t        node,
        ...             // NULL Terminated list of nodes
    )
    {
        va_list         pList;
        NODELINK_DATA   *pNodeList;
        uint32_t        nodeIndex;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        va_start(pList, node);
        for (;;) {
            pNodeList = va_arg(pList, NODELINK_DATA *);
            if (pNodeList) {
                nodeIndex = nodeTree_SiblingAdd(this, node, pNodeList);
                if (nodeIndex == 0) {
                    return obj_getLastError(this);
                }
            }
            else
                break;
        }
        
        // Return to caller.
        return obj_getLastError(this);
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
        OBJ_ID          (*pNew)(void);
        OBJ_IUNKNOWN    *pVtbl;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pVtbl = obj_getVtbl(this->pNodeArrayClass);
        if (NULL == pVtbl->pQueryInfo) {
            return OBJ_NIL;
        }
        pNew = pVtbl->pQueryInfo(this->pNodeArrayClass, OBJ_QUERYINFO_TYPE_METHOD, "New");
        if (NULL == pNew) {
            return OBJ_NIL;
        }
        pArray = pNew();
        if (pArray) {
            nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_getOpenNode(this), NULL);
            nodeTree_UpDownNodePost(this, 1, pArray);
            nodeArray_AppendNode(pArray, (NODE_DATA *)nodeTree_getCloseNode(this), NULL);
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
        OBJ_ID          (*pNew)(void);
        OBJ_IUNKNOWN    *pVtbl;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pVtbl = obj_getVtbl(this->pNodeArrayClass);
        if (NULL == pVtbl->pQueryInfo) {
            return OBJ_NIL;
        }
        pNew = pVtbl->pQueryInfo(this->pNodeArrayClass, OBJ_QUERYINFO_TYPE_METHOD, "New");
        if (NULL == pNew) {
            return OBJ_NIL;
        }
        pArray = pNew();
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
        NODELINK_DATA   *pParent;
        NODELINK_DATA   *pEntry;
        //NODELINK_DATA   *pChild;
        //uint32_t        childIndex;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if( !(parent && (parent <= nodeArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
        if( pTree == OBJ_NIL || (!obj_IsKindOf(pTree, OBJ_IDENT_NODETREE)) ) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
#endif
        
        pParent = (NODELINK_DATA *)nodeArray_Get(this->pArray, parent);
        if (pParent) {
            pEntry = (NODELINK_DATA *)nodeArray_Get(pTree->pArray, 1);   // Get Root.
        }
        
        // Return to caller.
    //eom:
        return ERESULT_NOT_IMPLEMENTED;     //FIXME: REMOVE THIS!
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeTree_Validate(
        NODETREE_DATA   *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this,OBJ_IDENT_NODETREE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(NODETREE_DATA)) ) {
            return false;
        }

        // Return to caller.
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
        NODELINK_DATA   *pEntry;
        int             i;
        int             iMax;
        uint32_t        idx;
        ERESULT         eRc = ERESULT_SUCCESS;
        NAME_DATA       *pName;
        const
        char            *pStr = NULL;
        OBJ_IUNKNOWN    *pVtbl;
        
        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        iMax = nodeArray_getSize(this->pArray);
        for (i=0; i<iMax; ++i) {
            pEntry = (NODELINK_DATA *)nodeArray_Get(this->pArray, i+1);
            if (pEntry) {
                if (obj_IsKindOf(pEntry, OBJ_IDENT_NODELINK))
                    ;
                else {
                    pVtbl = obj_getVtbl(pEntry);
                    if (pVtbl->pToDebugString) {
                        ASTR_DATA           *pStr = OBJ_NIL;
                        pStr = pVtbl->pToDebugString(pEntry, 4);
                        if (pStr) {
                            fprintf(stderr, "%s\n\n", AStr_getData(pStr));
                            obj_Release(pStr);
                            pStr = OBJ_NIL;
                        }
                    }
                    DEBUG_BREAK();
                    pStr = "node entry does not contain a proper NODE!";
                    eRc = ERESULT_FAILURE;
                    break;
                }
                pName = node_getName((NODE_DATA *)pEntry);
                if ((OBJ_NIL == pName) || (obj_getIdent(pName) == OBJ_IDENT_NAME))
                    ;
                else {
                    pVtbl = obj_getVtbl(pEntry);
                    if (pVtbl->pToDebugString) {
                        ASTR_DATA           *pStr = OBJ_NIL;
                        pStr = pVtbl->pToDebugString(pEntry, 4);
                        if (pStr) {
                            fprintf(stderr, "%s\n\n", AStr_getData(pStr));
                            obj_Release(pStr);
                            pStr = OBJ_NIL;
                        }
                    }
                    DEBUG_BREAK();
                    pStr = "node does not contain a NAME!";
                    eRc = ERESULT_FAILURE;
                    break;
                }
                idx = nodeLink_getIndex(pEntry);
                if (idx && (idx == (i + 1)))
                    ;
                else if (0 ==  idx)
                    ;
                else {
                    DEBUG_BREAK();
                    pStr = "node entry contains an invalid ndex!";
                    eRc = ERESULT_FAILURE;
                    break;
                }
                idx = nodeLink_getParent(pEntry);
                if (idx && (idx <= iMax))
                    ;
                else if (0 ==  idx)
                    ;
                else {
                    DEBUG_BREAK();
                    pStr = "node entry contains an invalid Parent Index!";
                    eRc = ERESULT_FAILURE;
                    break;
                }
                idx = nodeLink_getLeftLink(pEntry);
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
                idx = nodeLink_getRightLink(pEntry);
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
            NODELINK_DATA   *,              // Current Node
            uint16_t                        // Indent level * 4
        ),
        OBJ_ID          pObject
    )
    {
        OBJLIST_DATA    *pQueue = OBJ_NIL;
        NODELINK_DATA   *pEntry = OBJ_NIL;
        NODELINK_DATA   *pNext = OBJ_NIL;
        uint32_t        index = 0;
        uint16_t        indent = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pQueue = objList_New();
        if (pQueue == OBJ_NIL) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        
        pEntry = (NODELINK_DATA *)nodeArray_Get(this->pArray, 1);    // Get the root.
        if (pEntry == OBJ_NIL) {
            return ERESULT_SUCCESS;
        }
        objList_Add2Head(pQueue, pEntry);
        while (objList_getSize(pQueue)) {
            pEntry = objList_Head(pQueue);
            objList_DeleteHead(pQueue);
            pVisitor(pObject, this, pEntry, indent);
            index = nodeLink_getChild(pEntry);
            if (index) {
                pNext = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
                if (pNext) {
                    objList_Add2Tail(pQueue, pNext);
                }
            }
            index = nodeLink_getSibling(pEntry);
            if (index) {
                pEntry = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
                if (pEntry) {
                    objList_Add2Head(pQueue, pEntry);
                }
            }
        }
        
        obj_Release(pQueue);
        pQueue = OBJ_NIL;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                    V i s i t  I n o r d e r
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_VisitInorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
            OBJ_ID          ,           // Object supplied below
            NODETREE_DATA   *,          // Our Tree
            NODELINK_DATA   *,          // Current Node
            uint16_t                    // Indent level * 4
        ),
        OBJ_ID          pObject
        )
    {
        
        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        nodeTree_NodeInorder(this, pVisitor, pObject, 1, 0);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                    V i s i t  P o s t o r d e r
    //---------------------------------------------------------------

    ERESULT         nodeTree_VisitPostorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
                                OBJ_ID,                 // Object supplied below
                                NODETREE_DATA *,        // Our Tree
                                NODELINK_DATA *,        // Current Node
                                uint16_t                // Indent level * 4
                               ),
        OBJ_ID          pObject
    )
    {
        
        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        nodeTree_NodePostorder(this, pVisitor, pObject, 1, 0);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                    V i s i t  P r e o r d e r
    //---------------------------------------------------------------
    
    ERESULT         nodeTree_VisitPreorder(
        NODETREE_DATA	*this,
        void            (pVisitor)(
                            OBJ_ID,             // Object supplied below
                            NODETREE_DATA *,    // Our Tree
                            NODELINK_DATA *,    // Current Node
                            uint16_t            // Indent level * 4
                        ),
        OBJ_ID          pObject
    )
    {
        
        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !nodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        nodeTree_NodePreorder(this, pVisitor, pObject, 1, 0);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    

    
    
#ifdef	__cplusplus
}
#endif


