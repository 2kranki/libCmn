// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeBTree.c
 *	Generated 11/12/2018 09:44:16
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
#include        <nodeBTree_internal.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                  D e l e t e  N o d e
    //---------------------------------------------------------------
    
    ERESULT         nodeBTree_DeleteNode(
        NODEBTREE_DATA  *this,
        NODEBTREE_NODE  *pNode
    )
    {
        
        // Do initialization.
        if (NULL == pNode) {
            return ERESULT_INVALID_PARAMETER;
        }
        
        if (pNode->pNode) {
            obj_Release(pNode->pNode);
            pNode->pNode = OBJ_NIL;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D e l e t e  N o d e s
    //---------------------------------------------------------------
    
    /*! Delete all the nodes in the Tree using a Post-order traversal.
        This is the best way to delete the nodes in case the sub-tree
        is right degenerate.
     */
    ERESULT         nodeBTree_DeleteNodes(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode
    )
    {
        NODELNKP_DATA   *pWork;
        uint32_t        index;

        if (pNode) {
            
            pWork = nodeLnkP_getLeftLink(pNode);
            if (pWork) {
                nodeBTree_DeleteNodes(this, pWork);
            }
            
            pWork = nodeLnkP_getRightLink(pNode);
            if (pWork) {
                nodeBTree_DeleteNodes(this, pWork);
            }
            
            nodeLnkP_setLeftLink(pNode, OBJ_NIL);
            nodeLnkP_setMiddle(pNode, OBJ_NIL);
            nodeLnkP_setParent(pNode, OBJ_NIL);
            nodeLnkP_setRightLink(pNode, OBJ_NIL);
            index = nodeLnkP_getIndex(pNode);
            nodeArray_Put(this->pArray, index, OBJ_NIL);
        }

        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                  L e f t - M o s t  C h i l d
    //---------------------------------------------------------------
    
    // The Left-Most Child is the smallest key of the sub-tree from
    // the given node.
    
    NODELNKP_DATA * nodeBTree_LeftMostChild(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode
    )
    {

        // Do initialization.
        if (NULL == pNode) {
            return NULL;
        }
        
        while (nodeLnkP_getLeftLink(pNode)) {
            pNode = nodeLnkP_getLeftLink(pNode);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                  R i g h t - M o s t  C h i l d
    //---------------------------------------------------------------
    
    // The Right-Most Child is the largest key of the sub-tree from
    // the given node.
    
    NODELNKP_DATA * nodeBTree_RightMostChild(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode
    )
    {
        
        // Do initialization.
        if (NULL == pNode) {
            return NULL;
        }
        
        while (nodeLnkP_getRightLink(pNode)) {
            pNode = nodeLnkP_getRightLink(pNode);
        }

        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P a r e n t
    //---------------------------------------------------------------
    
    NODELNKP_DATA * nodeBTree_Parent(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode
    )
    {
        uint32_t        index;
        
        // Do initialization.
        if (OBJ_NIL == pNode) {
            return OBJ_NIL;
        }
        
#ifdef XYZZY
        if (nodeLink_getRightChild(pNode)) {
            pNode = nodeBTree_LeftMostChild(this, pNode);
            index = nodeLink_getLeft(pNode);
            pNode = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
        }
        else {
            pNode = nodeBTree_RightMostChild(this, pNode);
            index = nodeLink_getRight(pNode);
            pNode = (NODELINK_DATA *)nodeArray_Get(this->pArray, index);
        }
#endif

        // Return to caller.
        //return pNode;
        return OBJ_NIL;
    }
    
    
    
    //---------------------------------------------------------------
    //                  I n s e r t  L e f t
    //---------------------------------------------------------------
    
    NODELNKP_DATA * nodeBTree_InsertLeft(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode
    )
    {
        NODELNKP_DATA   *pChild = OBJ_NIL;
        
        // Do initialization.
        if (NULL == pNode) {
            return NULL;
        }

#ifdef XYZZY
        // Insert new node as Left Child of Node.
        pChild = blocks_RecordNew((BLOCKS_DATA *)this);
        if (pChild) {
            pChild->pLeft = pNode->pLeft;
            pChild->fLeft = pNode->fLeft;
            pChild->pRight = pNode;
            pChild->balance = 0;
            pChild->fRightChild = 0;
            pNode->pLeft = pChild;
            pNode->fLeft = NODEBTREE_LINK;
        }
#endif
        
        // Return to caller.
        return pChild;
    }
    
    
    
    //---------------------------------------------------------------
    //                  I n s e r t  R i g h t
    //---------------------------------------------------------------
    
    NODEBTREE_NODE * nodeBTree_InsertRight(
        NODEBTREE_DATA  *this,
        NODEBTREE_NODE  *pNode
    )
    {
        NODEBTREE_NODE  *pChild;
        
        // Do initialization.
        if (NULL == pNode) {
            return NULL;
        }
        
        // Insert new node as Right Child of Node.
        pChild = blocks_RecordNew((BLOCKS_DATA *)this);
        if (pChild) {
            pChild->pRight = pNode->pRight;
            pChild->fRight = pNode->fRight;
            pChild->pLeft = pNode;
            pChild->balance = 0;
            pChild->fRightChild = 1;
            pNode->pRight = pChild;
            pNode->fRight = NODEBTREE_LINK;
        }
        
        // Return to caller.
        return pChild;
    }
    
    
    
    //---------------------------------------------------------------
    //                          R o t a t e
    //---------------------------------------------------------------
    
    /*!
     Rotate the tree at the given node left one rotation.
     */
    
    ERESULT         nodeBTree_RotateLeft(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode
    )
    {
        NODELNKP_DATA   *pParent;
        NODELNKP_DATA   *pLeftTree;         // Left Tree of the Right node
        NODELNKP_DATA   *pRight;
        NODELNKP_DATA   *pWork;
        uint32_t        index;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Nothing to do if there is not a right link.
        if (pNode && nodeLnkP_getRightLink(pNode))
            ;
        else {
            return ERESULT_SUCCESS;
        }
        
#ifdef THREADED_TREE
        //TODO: Currently threads are not adjusted nor passed on.
#endif
        
        // Point to all nodes necessary to do the rotation.
        pRight = nodeLnkP_getRightLink(pNode);
        pParent = nodeLnkP_getParent(pNode);
        pLeftTree = nodeLnkP_getRightLink(pNode);
        while( pLeftTree && nodeLnkP_getLeftLink(pLeftTree) ) {  // Get left-most link.
            pLeftTree = nodeLnkP_getLeftLink(pLeftTree);
        }
        
        // Chain the right child to the node's parent.
        if( pParent ) {
            pWork = nodeLnkP_getLeftLink(pNode);
            if( pWork && (pWork == pNode)) {
                nodeLnkP_setLeftLink(pParent, pRight);
            }
            pWork = nodeLnkP_getRightLink(pNode);
            if( pWork && (pWork == pNode)) {
                nodeLnkP_setRightLink(pParent, pRight);
            }
        }
        else {
            uint32_t        rightIndex;
            NODELNKP_DATA   *pRoot = nodeBTree_getRoot(this);
            rightIndex = nodeLnkP_getIndex(pRight);
            nodeArray_Put(this->pArray, rightIndex, (NODE_DATA *)pRoot);
            nodeArray_Put(this->pArray, 1, (NODE_DATA *)pRight);
        }
        nodeLnkP_setRightLink(pNode, NULL);
        
        // Now add the node after the left-most node of the
        // node's right child.
        nodeLnkP_setLeftLink(pLeftTree, pNode);
        //FIXME: nodeLnkP_setRightLink(pNode, pRight);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         nodeBTree_RotateRight(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode
    )
    {
        NODELNKP_DATA   *pParent;
        NODELNKP_DATA   *pRightTree;
        NODELNKP_DATA   *pLeft;
        uint32_t        index;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (pNode && nodeLnkP_getLeftLink(pNode))
            ;
        else {
            return ERESULT_SUCCESS;
        }
        
#ifdef THREADED_TREE
        //TODO: Currently threads are not adjusted.
#endif
        
        // Point to all nodes necessary to do the rotation.
        pLeft = nodeLnkP_getLeftLink(pNode);
        pParent = nodeLnkP_getParent(pNode);
        pRightTree = nodeLnkP_getLeftLink(pNode);
        while( pRightTree && nodeLnkP_getRightLink(pRightTree) )
            pRightTree = nodeLnkP_getRightLink(pRightTree);

#ifdef XYZZY
        pParent = nodeLnkP_getParent(pNode);
        // Chain the left child to the node's parent.
        if( pParent ) {
            if( pParent->pLeft == pNode )
                pParent->pLeft = pLeft;
            if( pParent->pRight == pNode )
                pParent->pRight = pLeft;
        }
        else
            //FIXME: this->pRoot = pLeft;
        pNode->pLeft = NULL;
        
        // Now add the node after the right-most node of the
        // node's left child.
        pRightTree->pRight = pNode;
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                  V i s i t  N o d e s
    //---------------------------------------------------------------
    
    /*! Visit all the nodes from the given node and below in the Tree
     using a Pre-order traversal.
     */
    ERESULT         nodeBTree_VisitNodeInRecurse(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODELNKP_DATA   *pWork;
        
        if (pNode) {
            pWork = nodeLnkP_getLeftLink(pNode);
            if (pWork) {
                eRc = nodeBTree_VisitNodeInRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            eRc = pScan(pObj, pNode, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
            pWork = nodeLnkP_getRightLink(pNode);
            if (pWork) {
                eRc = nodeBTree_VisitNodeInRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
        }
        
        return eRc;
    }
    
    
    /*! Visit all the nodes from the given node and below in the Tree
        using a Post-order traversal.
     */
    ERESULT         nodeBTree_VisitNodePostRecurse(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODELNKP_DATA   *pWork;
        
        if (pNode) {
            pWork = nodeLnkP_getLeftLink(pNode);
            if (pWork) {
                eRc = nodeBTree_VisitNodePostRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            pWork = nodeLnkP_getRightLink(pNode);
            if (pWork) {
                eRc = nodeBTree_VisitNodePostRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            eRc = pScan(pObj, pNode, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }
        
        return eRc;
    }
    
    
    /*! Visit all the nodes from the given node and below in the Tree
     using a Pre-order traversal.
     */
    ERESULT         nodeBTree_VisitNodePreRecurse(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODELNKP_DATA   *pWork;
        
        if (pNode) {
            eRc = pScan(pObj, pNode, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
            pWork = nodeLnkP_getLeftLink(pNode);
            if (pWork) {
                eRc = nodeBTree_VisitNodePreRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            pWork = nodeLnkP_getRightLink(pNode);
            if (pWork) {
                eRc = nodeBTree_VisitNodePreRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
        }
        
        return eRc;
    }
    
    




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEBTREE_DATA *     nodeBTree_Alloc(
        void
    )
    {
        NODEBTREE_DATA       *this;
        uint32_t        cbSize = sizeof(NODEBTREE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEBTREE_DATA *     nodeBTree_New(
        void
    )
    {
        NODEBTREE_DATA       *this;
        
        this = nodeBTree_Alloc( );
        if (this) {
            this = nodeBTree_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * nodeBTree_getArray(
        NODEBTREE_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            nodeBTree_setArray(
        NODEBTREE_DATA  *this,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
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
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        nodeBTree_getPriority(
        NODEBTREE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            nodeBTree_setPriority(
        NODEBTREE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          R o o t
    //---------------------------------------------------------------
    
    NODELNKP_DATA * nodeBTree_getRoot(
        NODEBTREE_DATA  *this
    )
    {
        
        // Do initialization.
        
        // Return to caller.
        return (NODELNKP_DATA *)nodeArray_Get(this->pArray, 1);
    }
    
    bool            nodeBTree_setRoot(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pValue
    )
    {
        ERESULT         eRc;
        bool            fRc = true;
        
        // Do initialization.
        eRc = nodeArray_Put(this->pArray, 1, (NODE_DATA *)pValue);
        if (ERESULT_FAILED(eRc))
            fRc = false;

        // Return to caller.
        return fRc;
    }
    
    

    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        nodeBTree_getSize(
        NODEBTREE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->size;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * nodeBTree_getStr(
        NODEBTREE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        nodeBTree_setStr(
        NODEBTREE_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  nodeBTree_getSuperVtbl(
        NODEBTREE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
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
    //                          A d d
    //---------------------------------------------------------------
    
    ERESULT         nodeBTree_Add(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode,
        bool            fReplace
    )
    {
        NODELNKP_DATA   *pParent;
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        index = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = nodeArray_AppendNode(this->pArray, (NODE_DATA *)pNode, &index);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        nodeLnkP_setIndex(pNode, index);

        if (1 == nodeArray_getSize(this->pArray)) {
#ifdef THREADED_TREE
            nodeLnkP_setLeftLink(pNode, false);
            nodeLnkP_setLeft(pNode, pNode);
            nodeLnkP_setRightLink(pNode, false);
            nodeLnkP_setRight(pNode, pNode);
#endif
            nodeLnkP_setBalance(pNode, 0);
            return ERESULT_SUCCESS;
        }

        pParent = nodeBTree_getRoot(this);
        while (pParent) {
            eRc = nodeLnkP_Compare(pNode, pParent);
            if (ERESULT_SUCCESS_EQUAL == eRc) {
                if (fReplace) {
                    eRc = nodeLnkP_CopyProperties(pParent, pNode);
                    nodeArray_Put(
                                  this->pArray,
                                  nodeLnkP_getIndex(pNode),
                                  (NODE_DATA *)pNode
                    );
                    return ERESULT_SUCCESS;
                }
                return ERESULT_DATA_ALREADY_EXISTS;
            }
            else if (ERESULT_SUCCESS_LESS_THAN == eRc) {
                if (nodeLnkP_IsLeftLink(pParent))
                    pParent = nodeLnkP_getLeftLink(pParent);
                else {
                    // Insert new node as Left Child of Parent.
                    if (nodeLnkP_IsLeftLink(pParent))
                        nodeLnkP_setLeftLink(pNode, nodeLnkP_getLeftLink(pParent));
                    else
                        nodeLnkP_setLeftThread(pNode, nodeLnkP_getLeftThread(pParent));
#ifdef THREADED_TREE
                    nodeLnkP_setRightThread(pNode, pParent);
#endif
                    nodeLnkP_setParent(pNode, pParent);
                    nodeLnkP_setBalance(pNode, 0);
                    nodeLnkP_setLeftLink(pParent, pNode);
                    break;
                }
            }
            else if (ERESULT_SUCCESS_GREATER_THAN == eRc) {
                if (nodeLnkP_IsRightLink(pParent))
                    pParent = nodeLnkP_getRightLink(pParent);
                else {
                    // Insert new node as Right Child of Parent.
                    if (nodeLnkP_IsRightLink(pParent))
                        nodeLnkP_setRightLink(pNode, nodeLnkP_getRightLink(pParent));
                    else
                        nodeLnkP_setRightThread(pNode, nodeLnkP_getRightThread(pParent));
#ifdef THREADED_TREE
                    nodeLnkP_setLeftThread(pNode, pParent);      // Thread back to Parent
#endif
                    nodeLnkP_setParent(pNode, pParent);
                    nodeLnkP_setBalance(pNode, 0);
                    nodeLnkP_setRightLink(pParent, pNode);  // Parent's Right = Node
                    break;
                }
            }
            else {
                return ERESULT_GENERAL_FAILURE;
            }
        }
        ++this->size;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    

    ERESULT         nodeBTree_AddA(
        NODEBTREE_DATA  *this,
        int32_t         cls,
        const
        char            *pNameA,            // UTF-8
        OBJ_ID          pData
    )
    {
        NODELNKP_DATA   *pNode = NULL;
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNode = nodeLnkP_NewWithUTF8AndClass(pNameA, cls, pData);
        if (pNode) {
            eRc = nodeBTree_Add(this, pNode, false);
        }
        obj_Release(pNode);
        pNode = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
    
    
    

    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = nodeBTree_Assign(this,pOther);
     @endcode 
     @param     this    NODEBTREE object pointer
     @param     pOther  a pointer to another NODEBTREE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         nodeBTree_Assign(
        NODEBTREE_DATA		*this,
        NODEBTREE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeBTree_Validate(pOther) ) {
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
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         nodeBTree_Compare(
        NODEBTREE_DATA     *this,
        NODEBTREE_DATA     *pOther
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
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeBTree_Validate(pOther) ) {
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
        nodeBTree      *pCopy = nodeBTree_Copy(this);
     @endcode 
     @param     this    NODEBTREE object pointer
     @return    If successful, a NODEBTREE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEBTREE_DATA *     nodeBTree_Copy(
        NODEBTREE_DATA       *this
    )
    {
        NODEBTREE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeBTree_New( );
        if (pOther) {
            eRc = nodeBTree_Assign(this, pOther);
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

    void            nodeBTree_Dealloc(
        OBJ_ID          objId
    )
    {
        NODEBTREE_DATA  *this = objId;
        NODELNKP_DATA   *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODEBTREE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif
        
        nodeBTree_DeleteNodes(this, nodeBTree_getRoot(this));

        nodeBTree_setArray(this, OBJ_NIL);
        nodeBTree_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e l e t e
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeBTree_Delete(
        NODEBTREE_DATA  *this,
        NODE_DATA       *pNode
    )
    {
        NODEBTREE_NODE  *pParent;
        NODEBTREE_NODE  *pEntry;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif

#ifdef XYZZY
        // Search the tree for the node.
        pEntry = nodeBTree_getRoot(this);
        while (pEntry) {
            eRc = node_Compare(pNode, pEntry->pNode);
            if (ERESULT_SUCCESS_EQUAL == eRc) {
                goto found;
            }
            else if (ERESULT_SUCCESS_LESS_THAN == eRc) {
                if (pEntry->pLeft)
                    pEntry = pEntry->pLeft;
                else
                    break;
            }
            else if (ERESULT_SUCCESS_GREATER_THAN == eRc) {
                if (pEntry->pRight)
                    pEntry = pEntry->pRight;
                else
                    break;
            }
            else {
                //return ERESULT_GENERAL_FAILURE;
                return OBJ_NIL;
            }
        }
    found:
#endif
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         nodeBTree_Disable(
        NODEBTREE_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeBTree_Validate(this) ) {
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

    ERESULT         nodeBTree_Enable(
        NODEBTREE_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeBTree_Validate(this) ) {
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
    //                          F i n d
    //---------------------------------------------------------------
    
    NODELNKP_DATA * nodeBTree_Find(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode
    )
    {
        NODELNKP_DATA   *pParent;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        pParent = nodeBTree_getRoot(this);
        while (pParent) {
            eRc = nodeLnkP_Compare(pNode, pParent);
            if (ERESULT_SUCCESS_EQUAL == eRc) {
                return pParent;
            }
            else if (ERESULT_SUCCESS_LESS_THAN == eRc) {
                if (nodeLnkP_IsLeftLink(pParent))
                    pParent = nodeLnkP_getLeftLink(pParent);
                else
                    break;
            }
            else if (ERESULT_SUCCESS_GREATER_THAN == eRc) {
                if (nodeLnkP_IsRightLink(pParent))
                    pParent = nodeLnkP_getRightLink(pParent);
                else
                    break;
            }
            else {
                //return ERESULT_DATA_NOT_FOUND;
                return OBJ_NIL;
            }
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    

    //---------------------------------------------------------------
    //                          F i r s t
    //---------------------------------------------------------------
    
    NODELNKP_DATA * nodeBTree_First(
        NODEBTREE_DATA  *this
    )
    {
        NODELNKP_DATA   *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        
        pNode = nodeBTree_getRoot(this);
        pNode = nodeBTree_LeftMostChild(this, pNode);

        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEBTREE_DATA * nodeBTree_Init(
        NODEBTREE_DATA  *this
    )
    {
        uint32_t        cbSize = sizeof(NODEBTREE_DATA);
        ERESULT         eRc;
        
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

        this = (OBJ_ID)blocks_Init((BLOCKS_DATA *)this);    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODEBTREE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                        // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_NODEBTREE);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeBTree_Vtbl);
        
        eRc = blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(NODEBTREE_NODE));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pArray = nodeArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "nodeBTree::sizeof(NODEBTREE_DATA) = %lu\n", sizeof(NODEBTREE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODEBTREE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         nodeBTree_IsEnabled(
        NODEBTREE_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
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
    //                          L a s t
    //---------------------------------------------------------------
    
    NODELNKP_DATA * nodeBTree_Last(
        NODEBTREE_DATA  *this
    )
    {
        NODELNKP_DATA   *pEntry;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        
        pEntry = nodeBTree_getRoot(this);
        pEntry = nodeBTree_RightMostChild(this, pEntry);
        
        // Return to caller.
        return pEntry;
    }
    
    
    
    //---------------------------------------------------------------
    //                       N o d e
    //---------------------------------------------------------------
    
    NODELINK_DATA * nodeBTree_Node(
        NODEBTREE_DATA  *this,
        uint32_t        index
    )
    {
        NODELINK_DATA   *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
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
    //                         N o d e s
    //---------------------------------------------------------------
    
    ERESULT         nodeBTree_Nodes(
        NODEBTREE_DATA  *this,
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
        if( !nodeBTree_Validate(this) ) {
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
    //             P r e  O r d e r  T r a v e r s a l
    //---------------------------------------------------------------
    
    ERESULT         nodeBTree_PreOrderTraversal(
        NODEBTREE_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,
        void            *pArg3
    )
    {
        NODEBTREE_NODE  *pNode1;
        NODEBTREE_NODE  *pNode2;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef XYZZY
        pNode1 = nodeBTree_getRoot(this);
        pNode2 = NULL;

        do {
            // Descend down the bottom of the left branch.
            while (pNode1) {
                pNode2 = pNode1;
                pNode1 = pNode1->pLeft;
                // Scan the left-most node.
                if (pNode2) {
                    eRc = pScan(pObj, pNode2->pNode, pArg3);
                    if (ERESULT_FAILED(eRc))
                        break;
                }
            }
            while (pNode2 && (NULL == pNode1)) {
                do {
                    pNode1 = pNode2;
                    pNode2 = pNode1->pParent;
                } while (pNode2 && !(pNode1 == pNode1->pParent->pLeft));
                if (pNode2) {
                    eRc = pScan(pObj, pNode2->pNode, pArg3);
                    if (ERESULT_FAILED(eRc))
                        break;
                    pNode1 = pNode2->pRight;
                }
            }
        } while (pNode2);
#endif
        
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
        void        *pMethod = nodeBTree_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "nodeBTree", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          nodeBTree_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEBTREE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)nodeBTree_Class();
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
                            return nodeBTree_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return nodeBTree_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return nodeBTree_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return nodeBTree_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == nodeBTree_ToDebugString)
                    return "ToDebugString";
                if (pData == nodeBTree_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                  R i g t  D e g e n e r a t e
    //---------------------------------------------------------------
    
    ERESULT         nodeBTree_RightDegenerate(
        NODEBTREE_DATA  *this
    )
    {
        NODEBTREE_NODE  *pNode;
        NODEBTREE_NODE  *pParent;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef XYZZY
        /* Alter the tree to be right degenerate (ie a singly-
         * linked list using only the right child ptr).
         */
        pNode = nodeBTree_getRoot(this);
        while( pNode ) {
            pParent = pNode->pParent;
            if( pNode->pLeft ) {
                nodeBTree_RotateRight(this, pNode);
                if( pParent ) {
                    if( pParent->pLeft )
                        pNode = pParent->pLeft;
                    else
                        pNode = pParent->pRight;
                }
                else
                    pNode = this->pRoot;
            }
            else
                pNode = pNode->pRight;
        }
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     nodeBTree_ToJSON(
        NODEBTREE_DATA      *this
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{\"objectType\":\"%s\"",
                    pInfo->pClassName
                );
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = nodeBTree_ToDebugString(this,4);
     @endcode 
     @param     this    NODEBTREE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeBTree_ToDebugString(
        NODEBTREE_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
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
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    nodeArray_getSize(this->pArray)
            );

        if (this->pArray) {
            if (((OBJ_DATA *)(this->pArray))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pArray))->pVtbl->pToDebugString(
                                                    this->pArray,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
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
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeBTree_Validate(
        NODEBTREE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_NODEBTREE) )
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


        if( !(obj_getSize(this) >= sizeof(NODEBTREE_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                  V i s i t  N o d e s
    //---------------------------------------------------------------
    
    /*! Visit all the nodes in the Tree using a In-order traversal.
     */
    
    ERESULT         nodeBTree_VisitNodesInParent(
        NODEBTREE_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,
        void            *pArg3
    )
    {
        NODELNKP_DATA   *pNodeP;
        NODELNKP_DATA   *pNodeQ;
        NODELNKP_DATA   *pNodePL;           // Parent's Left Child
        ERESULT         eRc;
        
        /*
         When the traversal process reaches a leaf node, the parent field can
         be used to climb back up the tree.  So, when nodeP is reached from a
         left son, its right subtree must still be traversed; therefore this
         algorithm proceeds to nodeP->right.  When nodeP is reached from its
         right son, both its subtrees have been traversed and this algorithm
         backs up further to nodeP->parent.
         
         In this inorder traversal a node is visited when its left is recog-
         nized as NULL or when it is reached after backing up from its left
         child.
         */
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNodeP = nodeBTree_getRoot(this);
        pNodeQ = NULL;
        
        do {
            // Descend down to the bottom of the left branch.
            while (pNodeP) {
                pNodeQ = pNodeP;
                pNodeP = nodeLnkP_getLeftLink(pNodeP);
            }
            // Scan the left-most node.
            if (pNodeQ) {
                eRc = pScan(pObj, pNodeQ, pArg3);
                if (ERESULT_FAILED(eRc))
                    break;
                pNodeP = nodeLnkP_getRightLink(pNodeQ);
            }
            // nodeQ is current node and nodeP is its right child or NULL.
            while (pNodeQ && (NULL == pNodeP)) {
                // nodeQ has no right child.  Back up until a left son or
                // the tree root is found.
                do {
                    pNodeP = pNodeQ;
                    pNodeQ = nodeLnkP_getParent(pNodeP);
                    if (pNodeQ)
                        pNodePL = nodeLnkP_getLeftLink(pNodeQ);
                    else
                        break;
                } while (pNodeQ && !(pNodeP == pNodePL));
                // Scan the ??? node.
                if (pNodeQ) {
                    eRc = pScan(pObj, pNodeQ, pArg3);
                    if (ERESULT_FAILED(eRc))
                        break;
                    pNodeP = nodeLnkP_getRightLink(pNodeQ);
                }
            }
        } while (pNodeQ);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         nodeBTree_VisitNodesInRecurse(
        NODEBTREE_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeBTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pScan) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =   nodeBTree_VisitNodeInRecurse(
                                              this,
                                              nodeBTree_getRoot(this),
                                              pScan,
                                              pObj,
                                              pArg3
                );
        
        return eRc;
    }
    
    
    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    ERESULT         nodeBTree_VisitNodesPostRecurse(
        NODEBTREE_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeBTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pScan) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =   nodeBTree_VisitNodePostRecurse(
                    this,
                    nodeBTree_getRoot(this),
                    pScan,
                    pObj,
                    pArg3
                );
        
        return eRc;
    }
    
    
    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    ERESULT         nodeBTree_VisitNodesPreRecurse(
        NODEBTREE_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeBTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pScan) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =   nodeBTree_VisitNodePreRecurse(
                                               this,
                                               nodeBTree_getRoot(this),
                                               pScan,
                                               pObj,
                                               pArg3
                );
        
        return eRc;
    }
    
    


    
#ifdef	__cplusplus
}
#endif


