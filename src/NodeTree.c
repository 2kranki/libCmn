// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeTree.c
 *	Generated 01/10/2020 16:43:19
 *
 * Remarks:
 *  --      For multi-way trees or Forests represented by a binary tree,
 *          traversal is different than normal binary tree traversal.
 *          Inorder traversal of a multi-way tree/forest is postorder
 *          traversal of the binary tree. Postorder of the multi-way
 *          tree/forest is inorder traversal of the binary tree.
 *          Preorder traversal of the multi-way tree/forest is postorder
 *          traversal of the binary tree. (Knuth, ACP, Vol 1, 3rd Ed, page 337)
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
#include        <NodeTree_internal.h>
#include        <Name_internal.h>
#include        <Node_internal.h>
#include        <NodeLink_internal.h>
#include        <NodeArray.h>
#include        <NodeHash.h>
#include        <ObjList.h>
#include        <Value.h>
#include        <stdarg.h>
#include        <stdio.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    ERESULT         NodeTree_PrintNode (
        NODETREE_DATA   *this,
        uint32_t        index,
        uint16_t        indent
    )
    {
        NODELINK_DATA   *pNode = OBJ_NIL;
        NODELINK_DATA   *pChild;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        idxChild;
        const
        char            *pName;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pNode = NodeTree_Node(this, index);
        if (OBJ_NIL == pNode) {
        }

        if (indent) {
            ASTR_DATA       *pStr;
            pStr = AStr_NewFromCharA(indent, ' ');
            fprintf(stdout, "%s", AStr_getData(pStr));
            obj_Release(pStr);
        }

        pName = Node_getNameUTF8((NODE_DATA *)pNode);
        fprintf(stdout, "%s ", pName);
        mem_Free((void *)pName);
        fprintf(stdout, "\n");

        iMax = NodeTree_ChildCount(this, index);
        for (i=0; i<iMax; ++i) {
            pChild = NodeTree_Child(this, index, i, &idxChild);
            if (idxChild) {
                NodeTree_PrintNode(this, idxChild, indent+4);
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    ERESULT         NodeTree_UpDownNodePost(
        NODETREE_DATA   *this,
        uint32_t        index,              // Current Node
        NODEARRAY_DATA  *pArray
    )
    {
        NODELINK_DATA   *pNode;
        uint32_t        childIndex;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pNode = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
        if (pNode) {
            childIndex = NodeLink_getChild(pNode);
            if (childIndex) {
                NodeArray_AppendNode(pArray, (NODE_DATA *)NodeTree_getOpenNode(this), NULL);
                eRc = NodeTree_UpDownNodePost(
                                                   this,
                                                   childIndex,
                                                   pArray
                );
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
                NodeArray_AppendNode(pArray, (NODE_DATA *)NodeTree_getCloseNode(this), NULL);
            }
            // visit current node.
            NodeArray_AppendNode(pArray, (NODE_DATA *)pNode, NULL);
            // Follow Sibling chain.
            childIndex = NodeLink_getSibling(pNode);
            if (childIndex) {
                eRc = NodeTree_UpDownNodePost(
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
    ERESULT         NodeTree_UpDownNodePre(
        NODETREE_DATA   *this,
        uint32_t        index,              // Current Node
        NODEARRAY_DATA  *pArray
    )
    {
        NODELINK_DATA   *pEntry;
        NODELINK_DATA   *pChild;
        uint32_t        childIndex;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pEntry = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
        if (pEntry) {
            NodeArray_AppendNode(pArray, (NODE_DATA *)pEntry, NULL);
            childIndex = NodeLink_getChild(pEntry);
            if (childIndex) {
                NodeArray_AppendNode(pArray, (NODE_DATA *)NodeTree_getOpenNode(this), NULL);
                pChild = (NODELINK_DATA *)NodeArray_Get(this->pArray, childIndex);
                if (pChild) {
                    eRc = NodeTree_UpDownNodePre(this, childIndex, pArray);
                    if (ERESULT_FAILED(eRc)) {
                        return eRc;
                    }
                }
                NodeArray_AppendNode(pArray, (NODE_DATA *)NodeTree_getCloseNode(this), NULL);
            }
            childIndex = NodeLink_getSibling(pEntry);
            if (childIndex) {
                pChild = (NODELINK_DATA *)NodeArray_Get(this->pArray, childIndex);
                if (pChild) {
                    eRc = NodeTree_UpDownNodePre(this, childIndex, pArray);
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
    //                  N o d e  P o s t o r d e r
    //---------------------------------------------------------------

    ERESULT         NodeTree_NodePostorder(
        NODETREE_DATA    *this,
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pNode = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
        if (pNode) {
            // Follow Child chain.
            childIndex = NodeLink_getChild(pNode);
            if (childIndex) {
                eRc = NodeTree_NodePostorder(
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
            // visit current node.
            pVisitor(pObject, this, pNode, indent);
            // Follow Sibling chain.
            childIndex = NodeLink_getSibling(pNode);
            if (childIndex) {
                eRc = NodeTree_NodePostorder(
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
    ERESULT         NodeTree_NodePreorder(
        NODETREE_DATA    *this,
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pNode = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
        if (pNode) {
            // visit current node.
            pVisitor(pObject, this, pNode, indent);
            // Follow Child chain.
            childIndex = NodeLink_getChild(pNode);
            if (childIndex) {
                eRc = NodeTree_NodePreorder(
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
            childIndex = NodeLink_getSibling(pNode);
            if (childIndex) {
                eRc = NodeTree_NodePreorder(
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

    NODETREE_DATA *     NodeTree_Alloc (
        void
    )
    {
        NODETREE_DATA       *this;
        uint32_t        cbSize = sizeof(NODETREE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODETREE_DATA *     NodeTree_New (
        void
    )
    {
        NODETREE_DATA       *this;
        
        this = NodeTree_Alloc( );
        if (this) {
            this = NodeTree_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------

    NODEARRAY_DATA * NodeTree_getArray(
        NODETREE_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }


    bool            NodeTree_setArray(
        NODETREE_DATA   *this,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
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

    NODELINK_DATA * NodeTree_getCloseNode(
        NODETREE_DATA   *this
    )
    {
        NODELINK_DATA   *pNode = OBJ_NIL;

#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (OBJ_NIL == this->pClose) {
            pNode = NodeLink_NewWithUTF8ConAndClass(NODE_CLASS_CLOSE, ")", OBJ_NIL);
            if (pNode) {
                this->pClose = pNode;
            }
        }

        return this->pClose;
    }


    bool            NodeTree_setCloseNode(
        NODETREE_DATA   *this,
        NODELINK_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
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

    OBJ_ID          NodeTree_getNodeArrayClass(
        NODETREE_DATA   *this
    )
    {

#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return this->pNodeArrayClass;
    }


    bool          NodeTree_setNodeArrayClass(
        NODETREE_DATA   *this,
        OBJ_ID          pClass
    )
    {

#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pNodeArrayClass = pClass;
        return true;
    }



    //---------------------------------------------------------------
    //                    O p e n  N o d e
    //---------------------------------------------------------------

    NODELINK_DATA * NodeTree_getOpenNode(
        NODETREE_DATA   *this
    )
    {
        NODELINK_DATA   *pNode = OBJ_NIL;

#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (OBJ_NIL == this->pOpen) {
            pNode = NodeLink_NewWithUTF8ConAndClass(NODE_CLASS_OPEN, "(", OBJ_NIL);
            if (pNode) {
                this->pOpen = pNode;
            }
        }

        return this->pOpen;
    }


    bool            NodeTree_setOpenNode(
        NODETREE_DATA   *this,
        NODELINK_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
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



    //---------------------------------------------------------------
    //                          O t h e r
    //---------------------------------------------------------------

    OBJ_ID          NodeTree_getOther(
        NODETREE_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pOther;
    }


    bool            NodeTree_setOther(
        NODETREE_DATA   *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pOther) {
            obj_Release(this->pOther);
        }
        this->pOther = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                    R o o t  I n d e x
    //---------------------------------------------------------------

    uint32_t        NodeTree_getRootIndex(
        NODETREE_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return 1;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        NodeTree_getSize (
        NODETREE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->size;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodeTree_getSuperVtbl (
        NODETREE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
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
        NODETREE_DATA		*this,
        NODETREE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeTree_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C h i l d
    //---------------------------------------------------------------

    NODELINK_DATA * NodeTree_Child(
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
        if( !(parent > 0) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pNode = (NODELINK_DATA *)NodeArray_Get(this->pArray, parent);
        if (pNode) {
            childIndex = NodeLink_getChild(pNode);
            pChild = (NODELINK_DATA *)NodeArray_Get(this->pArray, childIndex);
            if (pChild) {
                while (index-- && childIndex) {
                    childIndex = NodeLink_getSibling(pChild);
                    if (childIndex) {
                        pChild = (NODELINK_DATA *)NodeArray_Get(this->pArray, childIndex);
                    }
                }
            }
            if (childIndex) {
                pNodeReturn = (NODELINK_DATA *)NodeArray_Get(this->pArray, childIndex);
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

    uint32_t        NodeTree_ChildAdd(
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return 0;
        }
        if( !(parent <= NodeArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            return 0;
        }
        if( pNode == OBJ_NIL || (!obj_IsKindOf(pNode, OBJ_IDENT_NODELINK)) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        NodeLink_setChild(pNode, 0);
        NodeLink_setParent(pNode, 0);
        NodeLink_setSibling(pNode, 0);

        // Try adding the root node.
        if (parent == 0) {
            if( !(NodeArray_getSize(this->pArray) == 0) ) {
                DEBUG_BREAK();
                return 0;
            }
            eRc = NodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
            if (!ERESULT_FAILED(eRc)) {
                NodeLink_setIndex(pNode, index);
            }
            else {
                DEBUG_BREAK();
                return 0;
            }
            goto eom;
        }

        pParent = (NODELINK_DATA *)NodeArray_Get(this->pArray, parent);
        if (pParent) {
            index = NodeLink_getChild(pParent);
            if (index == 0) {     // No children
                eRc = NodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
                if (!ERESULT_FAILED(eRc)) {
                    NodeLink_setChild(pParent, index);
                    NodeLink_setIndex(pNode, index);
                    NodeLink_setParent(pNode, parent);
                }
            }
            else {   // Parent has children, so add to end of child's sibling chain.
                // index points to first child of parent
                for (;;) {
                    pChild = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
                    if (NodeLink_getSibling(pChild) == 0) {  // End of Sibling Chain
                        eRc = NodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
                        if (!ERESULT_FAILED(eRc)) {
                            NodeLink_setSibling(pChild, index);
                            NodeLink_setIndex(pNode, index);
                            NodeLink_setParent(pNode, parent);
                        }
                        break;
                    }
                    index = NodeLink_getSibling(pChild);
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

    uint32_t        NodeTree_ChildCount(
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return 0;
        }
        if( !(parent <= NodeArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            return 0;
        }
        if (parent == 0) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pParent = (NODELINK_DATA *)NodeArray_Get(this->pArray, parent);
        if (pParent) {
            index = NodeLink_getChild(pParent);
            if (index == 0) {     // No children
            }
            else {   // Parent has children, so count them.
                // index points to first child of parent
                for (;;) {
                    ++count;
                    pChild = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
                    if (NodeLink_getSibling(pChild) == 0) {  // End of Sibling Chain
                        break;
                    }
                    index = NodeLink_getSibling(pChild);
                }
            }
        }

        // Return to caller.
    //eom:
        return count;
    }



    //---------------------------------------------------------------
    //                      C h i l d r e n  A d d
    //---------------------------------------------------------------

    ERESULT         NodeTree_ChildrenAdd(
        NODETREE_DATA   *this,
        uint32_t        parent,
        ...                         // NULL Terminated list
    )
    {
        va_list         pList;
        NODELINK_DATA   *pChild;
        uint32_t        nodeIndex;
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        va_start(pList, parent);
        for (;;) {
            pChild = va_arg(pList, NODELINK_DATA *);
            if (pChild) {
                nodeIndex = NodeTree_ChildAdd(this, parent, pChild);
                if (nodeIndex == 0) {
                    return ERESULT_GENERAL_FAILURE;
                }
            }
            else
                break;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                     C h i l d r e n  M o v e
    //---------------------------------------------------------------

    ERESULT         NodeTree_ChildrenMove(
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !((parent > 0) && (parent <= NodeArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if( !((index > 0) && (index <= NodeArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pEntry = NodeTree_Node(this, index);
        if (pEntry == OBJ_NIL) {
            return ERESULT_INVALID_PARAMETER;
        }

        pParent = NodeTree_Node(this, parent);
        if (pParent == OBJ_NIL) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (0 == NodeLink_getChild(pParent)) {     // No children to move
            return ERESULT_SUCCESS;
        }

        // Find last child if any of where to add the children.
        if (pEntry) {
            idxChild = NodeLink_getChild(pEntry);
            if (idxChild) {
                for (;;) {
                    pChild = NodeTree_Node(this, idxChild);
                    if (pChild && (NodeLink_getSibling(pChild) == 0)) {
                        pChildLast = pChild;
                        break;
                    }
                    idxChild = NodeLink_getSibling(pChild);
                }
            }
        }

        // We add the children to the index at the end of its children list
        // and adjust the parent in the first level of children added.
        idxChild = NodeLink_getChild(pParent);
        NodeLink_setChild(pParent, 0);
        if (pChildLast) {
            NodeLink_setSibling(pChildLast, idxChild);
        }
        else {
            NodeLink_setChild(pEntry, idxChild);
        }
        for (;;) {
            pChild = NodeTree_Node(this, idxChild);
            if (pChild) {
                NodeLink_setParent(pChild, index);
            }
            idxChild = NodeLink_getSibling(pChild);
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
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         NodeTree_Compare (
        NODETREE_DATA     *this,
        NODETREE_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeTree_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
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
    )
    {
        NODETREE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeTree_New( );
        if (pOther) {
            eRc = NodeTree_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            NodeTree_Dealloc (
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
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODETREE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NodeTree_setArray(this, OBJ_NIL);
        NodeTree_setCloseNode(this, OBJ_NIL);
        NodeTree_setOpenNode(this, OBJ_NIL);
        NodeTree_setOther(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeTree_Disable (
        NODETREE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeTree_Enable (
        NODETREE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODETREE_DATA *   NodeTree_Init (
        NODETREE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODETREE_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODETREE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeTree_Vtbl);
        
        this->pNodeArrayClass = NodeArray_Class( );
        this->pArray = NodeArray_New();
        if (OBJ_NIL == this->pArray) {
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "NodeTree::sizeof(NODETREE_DATA) = %lu\n", sizeof(NODETREE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODETREE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeTree_IsEnabled (
        NODETREE_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                       N o d e
    //---------------------------------------------------------------

    NODELINK_DATA * NodeTree_Node(
        NODETREE_DATA   *this,
        uint32_t        index
    )
    {
        NODELINK_DATA   *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return pNode;
        }
        if( !((index > 0) && (index <= NodeArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            return pNode;
        }
#endif

        pNode = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
        return pNode;
    }



    //---------------------------------------------------------------
    //                     N o d e  D e l e t e
    //---------------------------------------------------------------

    ERESULT     NodeTree_NodeDelete(
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pEntry = NodeTree_Node(this, index);
        if (pEntry == OBJ_NIL) {
            return ERESULT_INVALID_PARAMETER;
        }
        BREAK_FALSE((obj_getRetainCount(pEntry) ==  1));
        idxParent = NodeLink_getParent(pEntry);
        if (idxParent) {                // Not Root
            pParent = NodeTree_Node(this, idxParent);
            if (pParent) {
                // Unlink entry from sibling chain.
                idxChild = NodeLink_getChild(pParent);
                if (idxChild == index) {    // index is at head of chain
                    NodeLink_setChild(pParent, NodeLink_getSibling(pEntry));
                }
                else {
                    while (idxChild) {      // index is in the chain
                        pChild = NodeTree_Node(this, idxChild);
                        if (pChild && (NodeLink_getSibling(pChild) == index)) {
                            NodeLink_setSibling(pChild, NodeLink_getSibling(pEntry));
                            break;
                        }
                        idxChild = NodeLink_getSibling(pChild);
                    }
                }
            }
        }

        // Now delete all the children ad infinitum.
        for (;;) {
            idxChild = NodeLink_getChild(pEntry);
            if (idxChild) {
                pChild = NodeTree_Node(this, idxChild);
                if (pChild) {
                    eRc = NodeTree_NodeDelete(this, idxChild);
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
        NodeArray_Put(this->pArray, index, OBJ_NIL);
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

    ERESULT     NodeTree_NodeLinkChild(
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !(parent <= NodeArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pParent = (NODELINK_DATA *)NodeArray_Get(this->pArray, parent);
        if (pParent) {
            pEntry = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
            if (pEntry == OBJ_NIL) {
                return ERESULT_INVALID_PARAMETER;
            }
            if (NodeLink_getChild(pParent) == 0) {     // No children
                NodeLink_setChild(pParent, index);
                NodeLink_setParent(pEntry, parent);
                eRc = ERESULT_SUCCESS;
            }
            else {   // Parent has children, so add to end of child's sibling chain.
                pChild = (NODELINK_DATA *)NodeArray_Get(this->pArray, NodeLink_getChild(pParent));
                if (pChild) {
                    while (NodeLink_getSibling(pChild)) {
                        pChild = (NODELINK_DATA *)NodeArray_Get(this->pArray, NodeLink_getSibling(pChild));
                    }
                }
                if (pChild) {
                    NodeLink_setSibling(pChild, index);
                    NodeLink_setParent(pEntry, parent);
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

    uint32_t        NodeTree_NodeNew(
        NODETREE_DATA   *this,
        NODELINK_DATA   *pNode
    )
    {
        uint32_t        index = 0;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if((pNode == OBJ_NIL) || (!obj_IsKindOf(pNode, OBJ_IDENT_NODELINK))) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        eRc = NodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
        if (ERESULT_FAILED(eRc)) {
            index = 0;
        }
        else {
            NodeLink_setIndex(pNode, index);
        }

        // Return to caller.
        return index;
    }


    uint32_t    NodeTree_NodeNewUTF8(
        NODETREE_DATA   *this,
        int32_t         cls,
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        //ERESULT         eRc;
        //NODEENTRY_DATA  *pEntry;
        uint32_t        index = 0;
        NODELINK_DATA   *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pNode = NodeLink_NewWithUTF8ConAndClass(cls, pName, pData);
        if( pNode == OBJ_NIL ) {
            DEBUG_BREAK();
            return 0;
        }

        index = NodeTree_NodeNew(this, pNode);

        obj_Release(pNode);
        pNode = OBJ_NIL;

        // Return to caller.
        return index;
    }



    //---------------------------------------------------------------
    //                     N o d e  P a r e n t
    //---------------------------------------------------------------

    uint32_t        NodeTree_NodeParent(
        NODETREE_DATA   *this,
        uint32_t        index
    )
    {
        NODELINK_DATA   *pEntry;
        uint32_t        parent = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if( index == 0 ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pEntry = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
        if (pEntry) {
            parent = NodeLink_getParent(pEntry);
        }

        // Return to caller.
        return parent;
    }



    //---------------------------------------------------------------
    //                         N o d e s
    //---------------------------------------------------------------

    ERESULT         NodeTree_Nodes(
        NODETREE_DATA    *this,
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == ppNodes ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pNodes = NodeArray_New();
        for (i=0; i<NodeArray_getSize(this->pArray); ++i) {
            pEntry = (NODELINK_DATA *)NodeArray_Get(this->pArray, i+1);
            if (pEntry) {
                eRc = NodeArray_AppendNode(pNodes, (NODE_DATA *)pEntry, NULL);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(pNodes);
                    pNodes = OBJ_NIL;
                    goto eom;
                }
            }
        }
        NodeArray_SortAscending(pNodes);

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

    ERESULT         NodeTree_PrintTree(
        NODETREE_DATA    *this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\n\n\n");
        NodeTree_PrintNode(this, 1, 0);
        printf("\n\n\n");

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = NodeTree_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeTree", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeTree_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODETREE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODETREE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeTree_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return NodeTree_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeTree_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeTree_ToDebugString;
                        }
#ifdef  NODETREE_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return NodeTree_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeTree_ToDebugString)
                    return "ToDebugString";
#ifdef  NODETREE_JSON_SUPPORT
                if (pData == NodeTree_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                   S i b l i n g  A d d
    //---------------------------------------------------------------

    uint32_t        NodeTree_SiblingAdd(
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(sibling <= NodeArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            return 0;
        }
        if( pNode == OBJ_NIL  || (!obj_IsKindOf(pNode, OBJ_IDENT_NODELINK))) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        NodeLink_setChild(pNode, 0);
        NodeLink_setParent(pNode, 0);
        NodeLink_setSibling(pNode, 0);

        // Try adding the root node.
        if (sibling == 0) {
            if( !(NodeArray_getSize(this->pArray) == 0) ) {
                DEBUG_BREAK();
                return 0;
            }
            eRc = NodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
            if (!ERESULT_FAILED(eRc)) {
                NodeLink_setIndex(pNode, index);
            }
            else {
                DEBUG_BREAK();
                return 0;
            }
            goto eom;
        }

        pSibling = (NODELINK_DATA *)NodeArray_Get(this->pArray, sibling);
        if (pSibling) {
            index = NodeLink_getSibling(pSibling);
            if (index == 0) {     // No siblings
                eRc = NodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
                if (!ERESULT_FAILED(eRc)) {
                    NodeLink_setSibling(pSibling, index);
                    NodeLink_setIndex(pNode, index);
                    NodeLink_setParent(pNode, NodeLink_getParent(pSibling));
                }
            }
            else {  // Sibling has other siblings, so add to end of sibling chain.
                    // index points to next sibling.
                for (;;) {
                    pSibling = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
                    if (NodeLink_getSibling(pSibling) == 0) {  // End of Sibling Chain
                        eRc = NodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
                        if (!ERESULT_FAILED(eRc)) {
                            NodeLink_setSibling(pSibling, index);
                            NodeLink_setIndex(pNode, index);
                            NodeLink_setParent(pNode, NodeLink_getParent(pSibling));
                        }
                        break;
                    }
                    index = NodeLink_getSibling(pSibling);
                }
            }
        }

        // Return to caller.
    eom:
        return index;
    }



    //---------------------------------------------------------------
    //                  S i b l i n g  C o u n t
    //---------------------------------------------------------------

    uint32_t        NodeTree_SiblingCount(
        NODETREE_DATA   *this,
        uint32_t        node
    )
    {
        NODELINK_DATA   *pSibling;
        uint32_t        count = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(node <= NodeArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            return 0;
        }
        if (node == 0) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pSibling = (NODELINK_DATA *)NodeArray_Get(this->pArray, node);
        if (pSibling) {
            node = NodeLink_getSibling(pSibling);
            if (node == 0) {     // No children
            }
            else {  // Sibling has other siblings, so count them.
                    // index points to next sibling
                for (;;) {
                    ++count;
                    pSibling = (NODELINK_DATA *)NodeArray_Get(this->pArray, node);
                    if (NodeLink_getSibling(pSibling) == 0) {  // End of Sibling Chain
                        break;
                    }
                    node = NodeLink_getSibling(pSibling);
                }
            }
        }

        // Return to caller.
        //eom:
        return count;
    }



    //---------------------------------------------------------------
    //                    S i b l i n g  N e x t
    //---------------------------------------------------------------

    NODELINK_DATA * NodeTree_SiblingNext(
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(sibling && (sibling <= NodeArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            return 0;
        }
    #endif

        pSibling = (NODELINK_DATA *)NodeArray_Get(this->pArray, sibling);
        if (pSibling) {
            childIndex = NodeLink_getChild(pSibling);
            if (childIndex == 0)       // No children
                ;
            else {
                pEntry = (NODELINK_DATA *)NodeArray_Get(this->pArray, childIndex);
            }
        }

        // Return to caller.
    //eom:
        return pEntry;
}



    //---------------------------------------------------------------
    //                  S i b l i n g s  A d d
    //---------------------------------------------------------------

    ERESULT         NodeTree_SiblingsAdd(
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        va_start(pList, node);
        for (;;) {
            pNodeList = va_arg(pList, NODELINK_DATA *);
            if (pNodeList) {
                nodeIndex = NodeTree_SiblingAdd(this, node, pNodeList);
                if (nodeIndex == 0) {
                    return ERESULT_DATA_ERROR;
                }
            }
            else
                break;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
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
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeTree_ToDebugString (
        NODETREE_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    NodeTree_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                T o  L i n e a r i z a t i o n
    //---------------------------------------------------------------

    NODEARRAY_DATA * NodeTree_ToLinearizationPost(
        NODETREE_DATA    *this
    )
    {
        NODEARRAY_DATA  *pArray;
        OBJ_ID          (*pNew)(void);
        OBJ_IUNKNOWN    *pVtbl;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
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
            NodeArray_AppendNode(pArray, (NODE_DATA *)NodeTree_getOpenNode(this), NULL);
            NodeTree_UpDownNodePost(this, 1, pArray);
            NodeArray_AppendNode(pArray, (NODE_DATA *)NodeTree_getCloseNode(this), NULL);
            NodeArray_setOther(pArray, this);
        }

        // Return to caller.
        return pArray;
    }


    NODEARRAY_DATA * NodeTree_ToLinearizationPre(
        NODETREE_DATA    *this
    )
    {
        NODEARRAY_DATA  *pArray;
        OBJ_ID          (*pNew)(void);
        OBJ_IUNKNOWN    *pVtbl;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
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
            NodeArray_AppendNode(pArray, (NODE_DATA *)NodeTree_getOpenNode(this), NULL);
            NodeTree_UpDownNodePre(this, 1, pArray);
            NodeArray_AppendNode(pArray, (NODE_DATA *)NodeTree_getCloseNode(this), NULL);
            NodeArray_setOther(pArray, this);
        }

        // Return to caller.
        return pArray;
    }



    //---------------------------------------------------------------
    //                        T r e e  A d d
    //---------------------------------------------------------------

    uint32_t        NodeTree_TreeAdd(
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if( !(parent && (parent <= NodeArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            return 0;
        }
        if( pTree == OBJ_NIL || (!obj_IsKindOf(pTree, OBJ_IDENT_NODETREE)) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pParent = (NODELINK_DATA *)NodeArray_Get(this->pArray, parent);
        if (pParent) {
            pEntry = (NODELINK_DATA *)NodeArray_Get(pTree->pArray, 1);   // Get Root.
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
    bool            NodeTree_Validate (
        NODETREE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODETREE))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(NODETREE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                      V e r i f y
    //---------------------------------------------------------------

    ERESULT         NodeTree_Verify(
        NODETREE_DATA    *this,
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        iMax = NodeArray_getSize(this->pArray);
        for (i=0; i<iMax; ++i) {
            pEntry = (NODELINK_DATA *)NodeArray_Get(this->pArray, i+1);
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
                pName = Node_getName((NODE_DATA *)pEntry);
                if ((OBJ_NIL == pName) || (obj_getType(pName) == OBJ_IDENT_NAME))
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
                idx = NodeLink_getIndex(pEntry);
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
                idx = NodeLink_getParent(pEntry);
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
                idx = NodeLink_getLeftLink(pEntry);
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
                idx = NodeLink_getRightLink(pEntry);
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

    ERESULT         NodeTree_VisitBreadthFirst(
        NODETREE_DATA    *this,
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pQueue = ObjList_New();
        if (pQueue == OBJ_NIL) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        pEntry = (NODELINK_DATA *)NodeArray_Get(this->pArray, 1);    // Get the root.
        if (pEntry == OBJ_NIL) {
            return ERESULT_SUCCESS;
        }
        Node_setMisc(NodeLink_getNode(pEntry), indent);
        ObjList_Add2Head(pQueue, pEntry);
        while (ObjList_getSize(pQueue)) {
            pEntry = ObjList_Head(pQueue);
            indent = Node_getMisc(NodeLink_getNode(pEntry));
            ObjList_DeleteHead(pQueue);
            pVisitor(pObject, this, pEntry, indent);
            index = NodeLink_getChild(pEntry);
            if (index) {
                pNext = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
                if (pNext) {
                    Node_setMisc(NodeLink_getNode(pNext), indent+1);
                    ObjList_Add2Tail(pQueue, pNext);
                }
            }
            index = NodeLink_getSibling(pEntry);
            if (index) {
                pEntry = (NODELINK_DATA *)NodeArray_Get(this->pArray, index);
                if (pEntry) {
                    Node_setMisc(NodeLink_getNode(pEntry), indent);
                    ObjList_Add2Head(pQueue, pEntry);
                }
            }
        }

        obj_Release(pQueue);
        pQueue = OBJ_NIL;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                    V i s i t  P o s t o r d e r
    //---------------------------------------------------------------

    ERESULT         NodeTree_VisitPostorder(
        NODETREE_DATA    *this,
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        NodeTree_NodePostorder(this, pVisitor, pObject, 1, 0);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                    V i s i t  P r e o r d e r
    //---------------------------------------------------------------

    ERESULT         NodeTree_VisitPreorder(
        NODETREE_DATA    *this,
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
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        NodeTree_NodePreorder(this, pVisitor, pObject, 1, 0);

        // Return to caller.
        return ERESULT_SUCCESS;
    }




    
#ifdef	__cplusplus
}
#endif


