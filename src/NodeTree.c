// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeTree.c
 *  Generated 11/26/2021 19:19:16
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
#include        <NodeTree_internal.h>
#include        <JsonIn.h>
#include        <array.h>
#include        <NodeArray.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.

    typedef struct Index_Search_s {
        NODE_DATA       *pNode;
        uint32_t        index;
    } INDEX_SEARCH;
 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                  D e l e t e  E x i t
    //---------------------------------------------------------------

    ERESULT         NodeTree_DeleteExit(
        NODETREE_DATA   *this,
        NODETREE_RECORD *pRecord,
        void            *pArg3
    )
    {

        if (pRecord->pNode) {
            obj_Release(pRecord->pNode);
            pRecord->pNode = OBJ_NIL;
        }

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //            I n d e x  S e a r c h  E x i t
    //---------------------------------------------------------------

    ERESULT         NodeTree_IndexSearchExit(
        NODETREE_DATA   *this,
        NODETREE_RECORD *pRecord,
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        INDEX_SEARCH    *pSrch = pArg3;

        if (pRecord->pNode == pSrch->pNode) {
            pSrch->index = pRecord->unique;
            eRc = ERESULT_FAILURE;          // Stop search.
        }

        return eRc;
    }



    //---------------------------------------------------------------
    //                   R e c o r d  N e w
    //---------------------------------------------------------------

    NODETREE_RECORD * NodeTree_RecordNew(
        NODETREE_DATA   *this,
        uint32_t        parent,
        NODE_DATA       *pNode
    )
    {
        //ERESULT         eRc;
        NODETREE_RECORD *pRcd = NULL;
        uint32_t        indexRcd = 0;


        pRcd = Blocks_RecordNew((BLOCKS_DATA *)this, &indexRcd);
        if (NULL == pRcd) {
            return 0;
        }
        pRcd->unique = indexRcd;
        pRcd->childIndex = 0;
        pRcd->parentIndex = parent;
        pRcd->siblingIndex = 0;
        obj_Retain(pNode);
        pRcd->pNode = pNode;
        if (obj_Flag(this, NODETREE_FLAG_UNIQUE)) {
            Node_setUnique(pNode, indexRcd);
        }

        return pRcd;
    }



    //---------------------------------------------------------------
    //                      N o d e  V i s i t o r s
    //---------------------------------------------------------------

    ERESULT         NodeTree_NodeAdd (
        OBJ_ID          pObj,
        NODETREE_DATA   *pTree,
        NODE_DATA       *pNode,
        uint16_t        level,
        void            *pOther
    )
    {
        NODEARRAY_DATA  *pArray = pOther;

        NodeArray_AppendNode(pArray, pNode, NULL);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    ERESULT         NodeTree_NodeClose (
        OBJ_ID          pObj,
        NODETREE_DATA   *pTree,
        NODE_DATA       *pNode,
        uint16_t        level,
        void            *pOther
    )
    {
        NODEARRAY_DATA  *pArray = pOther;

        NodeArray_AppendNode(pArray, NodeTree_getNodeClose(pTree), NULL);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    ERESULT         NodeTree_NodeCount (
        NODETREE_DATA   *this,
        uint32_t        index,
        uint16_t        indent,
        void            *pOther
    )
    {
        NODETREE_RECORD *pRcd = NULL;

        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (pRcd) {
            (*((uint32_t *)pOther))++;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         NodeTree_NodeOpen (
        OBJ_ID          pObj,
        NODETREE_DATA   *pTree,
        NODE_DATA       *pNode,
        uint16_t        level,
        void            *pOther
    )
    {
        NODEARRAY_DATA  *pArray = pOther;

        NodeArray_AppendNode(pArray, NodeTree_getNodeOpen(pTree), NULL);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    ERESULT         NodeTree_NodePrint (
        NODETREE_DATA   *this,
        uint32_t        index,
        uint16_t        indent,
        void            *pOther
    )
    {
        NODETREE_RECORD *pRcd = NULL;
        const
        char            *pNameA;

        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (pRcd) {
            if (indent) {
                ASTR_DATA       *pStr;
                pStr = AStr_NewFromCharA(indent, ' ');
                fprintf(stdout, "%s", AStr_getData(pStr));
                obj_Release(pStr);
            }
            pNameA = Node_getNameUTF8(pRcd->pNode);
            fprintf(stdout, "%s ", pNameA);
            mem_Free((void *)pNameA);
            pNameA = NULL;
            fprintf(stdout, "\n");
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    ERESULT         NodeTree_NodeUpDownPost(
        NODETREE_DATA   *this,
        uint32_t        index,              // Current Node
        NODEARRAY_DATA  *pArray
    )
    {
        NODETREE_RECORD *pRcd = NULL;
        //NODETREE_RECORD *pRcdChild = NULL;
        uint32_t        childIndex;
        ERESULT         eRc;

        //FIXME: Verify this is the correct translation.
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (pRcd) {

            // Follow the Child chain.
            childIndex = pRcd->childIndex;
            if (childIndex) {
                NodeArray_AppendNode(pArray, NodeTree_getNodeOpen(this), NULL);
                eRc = NodeTree_NodeUpDownPost(
                                                   this,
                                                   childIndex,
                                                   pArray
                );
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
                NodeArray_AppendNode(pArray, NodeTree_getNodeClose(this), NULL);
            }

            // visit current node.
            NodeArray_AppendNode(pArray, pRcd->pNode, NULL);

            // Follow Sibling chain.
            if (pRcd->siblingIndex) {
                eRc =   NodeTree_NodeUpDownPost(
                                              this,
                                              pRcd->siblingIndex,
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



    //---------------------------------------------------------------
    //                  N o d e  P o s t O r d e r
    //---------------------------------------------------------------

    ERESULT         NodeTree_NodePostOrder(
        NODETREE_DATA   *this,
        NODETREE_VISIT  *pVisit
    )
    {
        NODETREE_RECORD *pRcd;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (0 == pVisit->index) {
            return ERESULT_SUCCESS;
        }
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, pVisit->index);
        if (NULL == pRcd) {
            return ERESULT_FAILURE;
        }

        // Follow Child chain.
        if (pRcd->childIndex) {
            pVisit->index = pRcd->childIndex;
            pVisit->level++;
            if (pVisit->pChildOpen) {
                pVisit->pChildOpen(
                                 pVisit->pObjectOpen,
                                 this,
                                 pRcd->pNode,
                                 pVisit->level,
                                 pVisit->pOther
                );
            }
            eRc = NodeTree_NodePostOrder(this, pVisit);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            pVisit->level--;
            if (pVisit->pChildClose) {
                pVisit->pChildClose(
                                 pVisit->pObjectClose,
                                 this,
                                 pRcd->pNode,
                                 pVisit->level,
                                 pVisit->pOther
                );
            }
        }

        // visit current node.
        if (pVisit->pVisitor) {
            pVisit->pVisitor(
                             pVisit->pObjectVisit,
                             this,
                             pRcd->pNode,
                             pVisit->level,
                             pVisit->pOther
            );
        }

        // Follow Sibling chain.
        if (pRcd->siblingIndex) {
            pVisit->index = pRcd->siblingIndex;
            eRc = NodeTree_NodePostOrder(this, pVisit);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    /*!
     Visit the root (or current node) then visit each child recursively.
     This is also known as a depth-first traversal.
     @param     this    NODETREE_DATA object pointer
     @param     pVisit  Visit Information
     @return    If successful, ERESULT_SUCCESS otherwise an ERESULT_*
                error.
     */
    ERESULT         NodeTree_NodePreOrder(
        NODETREE_DATA   *this,
        NODETREE_VISIT  *pVisit
    )
    {
        NODETREE_RECORD *pRcd;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (0 == pVisit->index) {
            return ERESULT_SUCCESS;
        }
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, pVisit->index);
        if (NULL == pRcd) {
            return ERESULT_FAILURE;
        }

        // visit current node.
        if (pVisit->pVisitor) {
            pVisit->pVisitor(
                             pVisit->pObjectVisit,
                             this,
                             pRcd->pNode,
                             pVisit->level,
                             pVisit->pOther
            );
        }

        // Follow Child chain.
        if (pRcd->childIndex) {
            pVisit->index = pRcd->childIndex;
            pVisit->level++;
            if (pVisit->pChildOpen) {
                pVisit->pChildOpen(
                                 pVisit->pObjectOpen,
                                 this,
                                 pRcd->pNode,
                                 pVisit->level,
                                 pVisit->pOther
                );
            }
            eRc = NodeTree_NodePreOrder(this, pVisit);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            if (pVisit->pChildClose) {
                pVisit->pChildClose(
                                 pVisit->pObjectClose,
                                 this,
                                 pRcd->pNode,
                                 pVisit->level,
                                 pVisit->pOther
                );
            }
            pVisit->level--;
        }

        // Follow Sibling chain.
        if (pRcd->siblingIndex) {
            pVisit->index = pRcd->siblingIndex;
            eRc = NodeTree_NodePreOrder(this, pVisit);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }





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
    //                    C l o s e  N o d e
    //---------------------------------------------------------------

    NODE_DATA *     NodeTree_getNodeClose(
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

        if (OBJ_NIL == this->pClose) {
            this->pClose = Node_NewWithUTF8ConAndClass(NODE_CLASS_CLOSE, ")", OBJ_NIL);
        }

        return this->pClose;
    }


    bool            NodeTree_setNodeClose(
        NODETREE_DATA   *this,
        NODE_DATA       *pValue
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
    //                          L o g
    //---------------------------------------------------------------

#ifdef   NODETREE_LOG
    bool            NodeTree_setLog (
        NODETREE_DATA   *this,
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pLog = pObj;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                   N o d e  A r r a y  C l a s s
    //---------------------------------------------------------------

    IOBJARRAY *     NodeTree_getNodeArrayClass(
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
        IOBJARRAY       *pClass
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

    NODE_DATA *     NodeTree_getNodeOpen(
        NODETREE_DATA   *this
    )
    {
        //NODE_DATA       *pNode = OBJ_NIL;

#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (OBJ_NIL == this->pOpen) {
            this->pOpen = Node_NewWithUTF8ConAndClass(NODE_CLASS_OPEN, "(", OBJ_NIL);
        }

        return this->pOpen;
    }


    bool            NodeTree_setNodeOpen(
        NODETREE_DATA   *this,
        NODE_DATA       *pValue
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

    uint32_t        NodeTree_getRootIndex (
        NODETREE_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->root;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        NodeTree_getPriority (
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

        //return this->priority;
        return 0;
    }


    bool            NodeTree_setPriority (
        NODETREE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
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

        return Blocks_getNumActive((BLOCKS_DATA *)this);
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
    
  
    OBJ_DATA *      NodeTree_getSuper (
        NODETREE_DATA   *this
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

        
        return (OBJ_DATA *)this;
    }

    

    //---------------------------------------------------------------
    //                      U n i q u e
    //---------------------------------------------------------------

    bool            NodeTree_getUnique (
        NODETREE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        if (obj_Flag(this, NODETREE_FLAG_UNIQUE))
            return true;
        else
            return false;
    }


    bool            NodeTree_setUnique (
        NODETREE_DATA   *this,
        bool            fValue
    )
    {

#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        obj_FlagSet(this, NODETREE_FLAG_UNIQUE, fValue ? true : false);

        return true;
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
        NODETREE_DATA       *this,
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

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

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
        //pOther->x     = this->x; 

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

    NODE_DATA *     NodeTree_Child(
        NODETREE_DATA   *this,
        uint32_t        parent,
        uint32_t        index,
        uint32_t        *pIndex         // Optional Returned Index
    )
    {
        uint32_t        childIndex = 0;
        NODE_DATA       *pNodeReturn = OBJ_NIL;
        NODETREE_RECORD *pRcdParent = NULL;
        NODETREE_RECORD *pRcdChild = NULL;
        //NODETREE_RECORD *pRcd = NULL;

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

        pRcdParent = Blocks_RecordGetUnique((BLOCKS_DATA *)this, parent);
        if (pRcdParent) {
            if (pRcdParent->childIndex) {
                // Parent has children, look into the child's sibling chain.
                childIndex = pRcdParent->childIndex;
                while (index-- && childIndex) {
                    pRcdChild = Blocks_RecordGetUnique((BLOCKS_DATA *)this, childIndex);
                    childIndex = pRcdChild->siblingIndex;
                    if (0 == index) {
                        pNodeReturn = pRcdChild->pNode;
                    }
                }
            }
        }

        // Return to caller.
        if (pIndex) {
            *pIndex = pRcdChild->siblingIndex;
        }
        return pNodeReturn;
    }



    //---------------------------------------------------------------
    //                        C h i l d  A d d
    //---------------------------------------------------------------

    uint32_t        NodeTree_ChildAdd(
        NODETREE_DATA   *this,
        uint32_t        parent,
        NODE_DATA       *pNode
    )
    {
        NODETREE_RECORD *pRcdParent = NULL;
        NODETREE_RECORD *pRcdChild = NULL;
        NODETREE_RECORD *pRcd = NULL;
        uint32_t        index = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return 0;
        }
        if( pNode == OBJ_NIL || (!obj_IsKindOf(pNode, OBJ_IDENT_NODE)) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        // Try adding the root node.
        if (parent == 0) {
            if( !(Blocks_getNumActive((BLOCKS_DATA *)this) == 0) ) {
                DEBUG_BREAK();
                return 0;
            }
            pRcd = NodeTree_RecordNew(this, parent, pNode);
            if (pRcd) {
                this->root = pRcd->unique;
                return pRcd->unique;
            } else {
                DEBUG_BREAK();
                return 0;
            }
        }

        pRcdParent = Blocks_RecordGetUnique((BLOCKS_DATA *)this, parent);
        if (pRcdParent) {
            if (pRcdParent->childIndex == 0) {     // No children
                Node_setUnique(pNode, index);
                pRcd = NodeTree_RecordNew(this, parent, pNode);
                if (pRcd) {
                    pRcdParent->childIndex = pRcd->unique;
                    return pRcd->unique;
                } else {
                    DEBUG_BREAK();
                    return 0;
                }
            }
            else {
                // Parent has children, so add to end of child's sibling chain.
                // index points to first child of parent.
                index = pRcdParent->childIndex;
                while (index) {
                    pRcdChild = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
                    if (pRcdChild->siblingIndex == 0) {  // End of Sibling Chain
                        break;
                    }
                    index = pRcdChild->siblingIndex;
                }
                if (pRcdChild && (pRcdChild->siblingIndex == 0)) {  // End of Sibling Chain
                    pRcd = NodeTree_RecordNew(this, parent, pNode);
                    if (pRcd) {
                        pRcdChild->siblingIndex = pRcd->unique;
                        return pRcd->unique;
                    } else {
                        DEBUG_BREAK();
                        return 0;
                    }
                    //break;
                }
            }
        }

        // Return to caller.
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
        NODETREE_RECORD *pRcdParent = NULL;
        NODETREE_RECORD *pRcdChild = NULL;
        uint32_t        index = 0;
        uint32_t        count = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return 0;
        }
        if (parent == 0) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pRcdParent = Blocks_RecordGetUnique((BLOCKS_DATA *)this, parent);
        if (pRcdParent) {
            index = pRcdParent->childIndex;
            while (index) {
                pRcdChild = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
                count++;
                if (pRcdChild->siblingIndex == 0) {  // End of Sibling Chain
                    break;
                }
                index = pRcdChild->siblingIndex;
            }
        }

        // Return to caller.
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
        NODE_DATA       *pChild;
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
            pChild = va_arg(pList, NODE_DATA *);
            if (pChild) {
                nodeIndex = NodeTree_ChildAdd(this, parent, pChild);
                if (nodeIndex == 0) {
                    return ERESULT_GENERAL_FAILURE;
                }
            }
            else
                break;
        }
        va_end(pList);

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
        //ERESULT         eRc;
        NODETREE_RECORD *pRcdParent = NULL;
        NODETREE_RECORD *pRcdChild = NULL;
        uint32_t        idxChild;
        NODETREE_RECORD *pRcdChildLast = NULL;
        NODETREE_RECORD *pRcd = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (pRcd == NULL) {
            return ERESULT_INVALID_PARAMETER;
        }

        pRcdParent = Blocks_RecordGetUnique((BLOCKS_DATA *)this, parent);
        if (pRcdParent == NULL) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (0 == pRcdParent->childIndex) {     // No children to move
            return ERESULT_SUCCESS;
        }

        // Find last child if any of where to add the children.
        if (pRcd) {
            idxChild = pRcd->childIndex;
            if (idxChild) {
                for (;;) {
                    pRcdChild = Blocks_RecordGetUnique((BLOCKS_DATA *)this, idxChild);
                    if (pRcdChild && (pRcdChild->siblingIndex == 0)) {
                        pRcdChildLast = pRcdChild;
                        break;
                    }
                    idxChild = pRcdChild->siblingIndex;
                }
            }
        }

        // We add the children to the index at the end of its children list
        // and adjust the parent in the first level of children added.
        idxChild = pRcdParent->childIndex;
        pRcdParent->childIndex = 0;
        if (pRcdChildLast) {
            pRcdChildLast->siblingIndex = idxChild;
        }
        else {
            pRcd->childIndex = idxChild;
        }
        while (idxChild) {
            pRcdChild = Blocks_RecordGetUnique((BLOCKS_DATA *)this, idxChild);
            if (pRcdChild) {
                pRcdChild->parentIndex = index;
            }
            idxChild = pRcdChild->siblingIndex;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             NodeTree_Compare (
        NODETREE_DATA     *this,
        NODETREE_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef  NODETREE_SINGLETON
        if (OBJ_NIL == this) {
            this = NodeTree_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!NodeTree_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
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
        
#ifdef NODETREE_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = NodeTree_New( );
        if (pOther) {
            eRc = NodeTree_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
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
        //ERESULT         eRc;

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
        NodeTree_setNodeClose(this, OBJ_NIL);
        NodeTree_setNodeOpen(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        NodeTree      *pDeepCopy = NodeTree_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODETREE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODETREE_DATA *     NodeTree_DeepCopy (
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
        return pOther;
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
        NODETREE_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  NODETREE_SINGLETON
        if (OBJ_NIL == this) {
            this = NodeTree_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
        NODETREE_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  NODETREE_SINGLETON
        if (OBJ_NIL == this) {
            this = NodeTree_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   NODETREE_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
        }
#endif
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODETREE_DATA * NodeTree_Init (
        NODETREE_DATA   *this
    )
    {
        uint32_t        cbSize = sizeof(NODETREE_DATA);
        ERESULT         eRc;
        bool            fRc;
        
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

        this = (OBJ_ID)Blocks_Init((BLOCKS_DATA *)this);   // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of NodeTree_object.c
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODETREE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeTree_Vtbl);
#ifdef  NODETREE_JSON_SUPPORT
        JsonIn_RegisterClass(NodeTree_Class());
#endif

        fRc =   Blocks_setDeleteExit(
                                   (BLOCKS_DATA *)this,
                                   (void *)NodeTree_DeleteExit,
                                   this,
                                   NULL
                );
        eRc = Blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(NODETREE_RECORD));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this->pNodeArrayClass = NodeArray_Class( );

        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "NodeTree::sizeof(NODETREE_DATA) = %lu\n", 
                sizeof(NODETREE_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODETREE_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeTree_IsEnabled (
        NODETREE_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  NODETREE_SINGLETON
        if (OBJ_NIL == this) {
            this = NodeTree_Shared();
        }
#endif
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

    NODE_DATA *     NodeTree_Node(
        NODETREE_DATA   *this,
        uint32_t        index
    )
    {
        NODETREE_RECORD *pRcd = NULL;
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return pNode;
        }
#endif

        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (pRcd) {
            pNode = pRcd->pNode;
        }

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
        NODETREE_RECORD *pParent;
        uint32_t        indexParent;
        NODETREE_RECORD *pRcd;
        NODETREE_RECORD *pChild;
        uint32_t        indexChild;
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (NULL == pRcd) {
            return ERESULT_INVALID_PARAMETER;
        }
        BREAK_TRUE((OBJ_NIL == pRcd->pNode));
        BREAK_TRUE((obj_getRetainCount(pRcd->pNode) <  1));
        indexParent = pRcd->parentIndex;
        if (indexParent) {              // Not Root
            pParent = Blocks_RecordGetUnique((BLOCKS_DATA *)this, indexParent);
            if (pParent) {
                // Unlink entry from sibling chain.
                if (pParent->childIndex == index) {     // index is at head of chain
                    pParent->childIndex = pRcd->siblingIndex;
                } else {                                // index in in chain somewhere
                    indexChild = pParent->childIndex;
                    while (indexChild) {
                        pChild = Blocks_RecordGetUnique((BLOCKS_DATA *)this, indexChild);
                        if (pChild) {
                            if (pChild->siblingIndex == index) {
                                pChild->siblingIndex = pRcd->siblingIndex;
                                break;
                            }
                        } else {
                            // No child record for index value!
                            DEBUG_BREAK();
                            return ERESULT_GENERAL_FAILURE;
                        }
                        indexChild = pChild->siblingIndex;
                    }
                }
            } else {
                // No parent record for non-root entry!
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
            }
        } else {                        // Root
            if (pRcd->unique == this->root) {

            } else {
                // No parent and not root!
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
            }
        }

        // Now delete all the children ad infinitum.
        for (;;) {
            indexChild = pRcd->childIndex;
            if (indexChild) {
                pChild = Blocks_RecordGetUnique((BLOCKS_DATA *)this, indexChild);
                if (pChild) {
                    eRc = NodeTree_NodeDelete(this, indexChild);
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
        if (pRcd->pNode) {
            obj_Release(pRcd->pNode);
            pRcd->pNode = OBJ_NIL;
        }
        // NOTE -- We are releasing the entry, but leaving the array position
        //          for it. If we changed the array, then we would have to
        //          re-translate the entire tree.

        // Return to caller.
        if (ERESULT_FAILED(eRc)) {
        } else {
            eRc = ERESULT_SUCCESS;
        }
    eom:
        return eRc;
    }



    //---------------------------------------------------------------
    //                       N o d e  I n d e x
    //---------------------------------------------------------------

    uint32_t        NodeTree_NodeIndex(
        NODETREE_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        INDEX_SEARCH    srch = {0};

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeTree_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        srch.pNode = pNode;
        Blocks_ForEach(
                       (BLOCKS_DATA *)this,
                       (void *)NodeTree_IndexSearchExit,
                       this,
                       &srch
        );

        return srch.index;
    }


    uint32_t        NodeTree_NodeIndexChild(
        NODETREE_DATA   *this,
        uint32_t        index
    )
    {
        NODETREE_RECORD *pRcd = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (pRcd) {
            index = pRcd->childIndex;
        } else {
            index = 0;
        }

        return index;
    }


    uint32_t        NodeTree_NodeIndexParent(
        NODETREE_DATA   *this,
        uint32_t        index
    )
    {
        NODETREE_RECORD *pRcd = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (pRcd) {
            index = pRcd->parentIndex;
        } else {
            index = 0;
        }

        return index;
    }


    uint32_t        NodeTree_NodeIndexSibling(
        NODETREE_DATA   *this,
        uint32_t        index
    )
    {
        NODETREE_RECORD *pRcd = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (pRcd) {
            index = pRcd->siblingIndex;
        } else {
            index = 0;
        }

        return index;
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
        NODETREE_RECORD *pRcdParent = NULL;
        NODETREE_RECORD *pRcd = NULL;
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
        if (NULL == pRcd) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (pRcd->childIndex || pRcd->parentIndex || pRcd->siblingIndex) {
            return ERESULT_DATA_ALREADY_EXISTS;
        }

        if (parent) {
            pRcdParent = Blocks_RecordGetUnique((BLOCKS_DATA *)this, parent);
            if (NULL == pRcdParent) {
                return ERESULT_INVALID_PARAMETER;
            }
        } else {
            if (0 == this->root) {
                this->root = index;
                return ERESULT_SUCCESS;
            } else {
                return ERESULT_DATA_ALREADY_EXISTS;
            }
        }

        if (pRcdParent->childIndex == 0) {     // No children
            if (obj_Flag(this, NODETREE_FLAG_UNIQUE)) {
                Node_setUnique(pRcd->pNode, index);
            }
            pRcdParent->childIndex = pRcd->unique;
            return ERESULT_SUCCESS;
        }
        else {
            uint32_t        indexChild;
            NODETREE_RECORD *pRcdChild = NULL;
            // Parent has children, so add to end of child's sibling chain.
            // index points to first child of parent.
            indexChild = pRcdParent->childIndex;
            while (indexChild) {
                pRcdChild = Blocks_RecordGetUnique((BLOCKS_DATA *)this, indexChild);
                if (pRcdChild->siblingIndex == 0) {  // End of Sibling Chain
                    break;
                }
                indexChild = pRcdChild->siblingIndex;
            }
            if (pRcdChild && (pRcdChild->siblingIndex == 0)) {  // End of Sibling Chain
                pRcdChild->siblingIndex = pRcd->unique;
                return ERESULT_SUCCESS;
            }
        }

        // Return to caller.
        return ERESULT_FAILURE;
    }



    //---------------------------------------------------------------
    //                     N o d e  N e w
    //---------------------------------------------------------------

    uint32_t        NodeTree_NodeNew(
        NODETREE_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        //ERESULT         eRc;
        NODETREE_RECORD *pRcd = NULL;
        uint32_t        index = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if((pNode == OBJ_NIL) || (!obj_IsKindOf(pNode, OBJ_IDENT_NODE))) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pRcd = NodeTree_RecordNew(this, 0, pNode);
        if (pRcd) {
            index = pRcd->unique;
        }

        // Return to caller.
        return index;
    }



    uint32_t        NodeTree_NodeNewUTF8(
        NODETREE_DATA   *this,
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData,
        uint32_t        child1,
        uint32_t        child2
    )
    {
        ERESULT         eRc;
        NODETREE_RECORD *pRcd = NULL;
        uint32_t        index = 0;
        NODE_DATA       *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pNode = Node_NewWithUTF8AndClass(cls, pNameA, pData);
        if (pNode) {
            pRcd = NodeTree_RecordNew(this, 0, pNode);
            if (pRcd) {
                index = pRcd->unique;
                if (index && child1) {
                    eRc = NodeTree_NodeLinkChild(this, index, child1);
                    if (ERESULT_OK(eRc) && child2) {
                        eRc = NodeTree_NodeLinkChild(this, index, child2);
                    }
                }
            }
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }

        // Return to caller.
        return index;
    }



    //---------------------------------------------------------------
    //                         N o d e s
    //---------------------------------------------------------------

    NODEARRAY_DATA * NodeTree_Nodes(
        NODETREE_DATA   *this
    )
    {
        NODEARRAY_DATA  *pNodes = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;
        uint32_t        jMax;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        pNodes = NodeArray_New();
        iMax = NodeTree_getSize(this);
        jMax = Blocks_getMaxRecords((BLOCKS_DATA *)this);
        for (i=0,j=0; i<iMax && j<jMax; j++) {
            // Remember that Blocks' record numbers may not be contiguous!
            NODETREE_RECORD *pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, j+1);
            if (pRcd) {
                if (pRcd->pNode) {
                    eRc = NodeArray_AppendNode(pNodes, pRcd->pNode, NULL);
                    if (ERESULT_FAILED(eRc)) {
                        obj_Release(pNodes);
                        pNodes = OBJ_NIL;
                        break;
                    }
                    i++;
                }
            }
        }
        if (pNodes) {
            NodeArray_SortAscending(pNodes);
        }

        // Return to caller.
        return pNodes;
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
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

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

                    case 'P':
#ifdef  NODETREE_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return NodeTree_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return NodeTree_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeTree_ToDebugString;
                        }
#ifdef  NODETREE_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return NodeTree_ToJsonFields;
                        }
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
        NODE_DATA       *pNode
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        NODETREE_RECORD *pRcdSibling = NULL;
        NODETREE_RECORD *pRcd = NULL;
        uint32_t        index = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( pNode == OBJ_NIL  || (!obj_IsKindOf(pNode, OBJ_IDENT_NODE))) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (0 == sibling) {
            if (0 == this->root) {
                pRcd = NodeTree_RecordNew(this, 0, pNode);
                if (pRcd) {
                    this->root = pRcd->unique;
                    this->root = pRcd->unique;
                    return pRcd->unique;
                } else {
                    DEBUG_BREAK();
                    return 0;
                }
            } else {
                // Error - No Sibling was supplied!
                DEBUG_BREAK();
                return 0;
            }
        }

        pRcdSibling = Blocks_RecordGetUnique((BLOCKS_DATA *)this, sibling);
        if (pRcdSibling) {
            // Parent has sibling(s), so add to end of sibling chain.
            index = pRcdSibling->siblingIndex;
            while (index) {
                pRcdSibling = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);
                if (pRcdSibling->siblingIndex == 0) {  // End of Sibling Chain
                    break;
                }
                index = pRcdSibling->siblingIndex;
            }
            if (pRcdSibling && (0 == pRcdSibling->siblingIndex)) {
                pRcd = NodeTree_RecordNew(this, pRcdSibling->parentIndex, pNode);
                if (pRcd) {
                    pRcdSibling->siblingIndex = pRcd->unique;
                    return pRcd->unique;
                } else {
                    DEBUG_BREAK();
                    return 0;
                }
            }
        } else {
            // Internal Failure - No Blocks record for index!
            DEBUG_BREAK();
            return 0;
        }

        // Return to caller.
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
        NODETREE_RECORD *pRcdSibling = NULL;
        uint32_t        count = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if (node == 0) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        pRcdSibling = Blocks_RecordGetUnique((BLOCKS_DATA *)this, node);
        if (pRcdSibling) {
            node = pRcdSibling->siblingIndex;
            if (node == 0) {     // No children
            }
            else {  // Sibling has other siblings, so count them.
                    // index points to next sibling
                while (node) {
                    ++count;
                    pRcdSibling = Blocks_RecordGetUnique((BLOCKS_DATA *)this, node);
                    node = pRcdSibling->siblingIndex;
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

    NODE_DATA *     NodeTree_SiblingNext(
        NODETREE_DATA   *this,
        uint32_t        sibling       // Relative to 1
    )
    {
        NODETREE_RECORD *pRcdSibling = NULL;
        uint32_t        siblingIndex;
        NODE_DATA       *pEntry = OBJ_NIL;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
    #endif

        pRcdSibling = Blocks_RecordGetUnique((BLOCKS_DATA *)this, sibling);
        if (pRcdSibling) {
            siblingIndex = pRcdSibling->siblingIndex;
            if (0 == siblingIndex)       // No children
                ;
            else {
                pRcdSibling = Blocks_RecordGetUnique((BLOCKS_DATA *)this, siblingIndex);
                pEntry = pRcdSibling->pNode;
            }
        }

        // Return to caller.
        return pEntry;
}



    //---------------------------------------------------------------
    //                  S i b l i n g s  A d d
    //---------------------------------------------------------------

    ERESULT         NodeTree_SiblingsAdd(
        NODETREE_DATA   *this,
        uint32_t        index,
        ...             // NULL Terminated list of nodes
    )
    {
        va_list         pList;
        NODE_DATA       *pNodeList;
        uint32_t        nodeIndex;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        va_start(pList, index);
        for (;;) {
            pNodeList = va_arg(pList, NODE_DATA *);
            if (pNodeList) {
                nodeIndex = NodeTree_SiblingAdd(this, index, pNodeList);
                if (nodeIndex == 0) {
                    return ERESULT_DATA_ERROR;
                }
                index = nodeIndex;
            }
            else
                break;
        }
        va_end(pList);

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
        NODETREE_DATA   *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;
        uint32_t        jMax;

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
                    "{%p(%s) size=%d retain=%d cNodes=%d\n",
                    this,
                    pInfo->pClassName,
                    NodeTree_getSize(this),
                    obj_getRetainCount(this),
                    NodeTree_getSize(this)
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        eRc = AStr_AppendPrint(pStr, "Nodes:\n");
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        eRc = AStr_AppendPrint(pStr, "entry index child sibling parent\n");

        iMax = NodeTree_getSize(this);
        jMax = Blocks_getMaxRecords((BLOCKS_DATA *)this);
        for (i=0,j=0; i<iMax && j<jMax; j++) {
            // Remember that Blocks' record numbers may not be contiguous!
            NODETREE_RECORD *pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, j+1);
            const
            char            *pStrA;
            if (pRcd) {
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent+4, ' ');
                }
                if (pRcd->pNode) {
                    pStrA = Node_getNameUTF8(pRcd->pNode);
                } else {
                    pStrA = mem_Calloc(1,1);
                }
                eRc =   AStr_AppendPrint(
                                       pStr,
                                       " %3d  %2d     %2d    %2d     %2d   %s\n",
                                         j+1,
                                         pRcd->unique,
                                         pRcd->childIndex,
                                         pRcd->siblingIndex,
                                         pRcd->parentIndex,
                                         pStrA
                        );
                mem_Free((void *)pStrA);
                pStrA = NULL;
                i++;
            }
        }

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
        NODETREE_VISIT  visit;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        if (0 == this->root)
            return OBJ_NIL;

        pVtbl = obj_getVtbl(this->pNodeArrayClass);
        if (NULL == pVtbl->pQueryInfo) {
            return OBJ_NIL;
        }
        pNew = pVtbl->pQueryInfo(this->pNodeArrayClass, OBJ_QUERYINFO_TYPE_METHOD, "New");
        if (NULL == pNew) {
            return OBJ_NIL;
        }
        pArray = pNew();

        visit.pVisitor      = (void *)NodeTree_NodeAdd;
        visit.pObjectVisit  = this;
        visit.pChildOpen    = (void *)NodeTree_NodeOpen;
        visit.pObjectOpen   = this;
        visit.pChildClose   = (void *)NodeTree_NodeClose;
        visit.pObjectClose  = this;
        visit.pOther        = pArray;
        visit.index         = this->root;
        visit.level         = 0;

        if (pArray) {
            NodeArray_AppendNode(pArray, NodeTree_getNodeOpen(this), NULL);
            NodeTree_NodePostOrder(this, &visit);
            NodeArray_AppendNode(pArray, NodeTree_getNodeClose(this), NULL);
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
        NODETREE_VISIT  visit;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        if (0 == this->root)
            return OBJ_NIL;

        pVtbl = obj_getVtbl(this->pNodeArrayClass);
        if (NULL == pVtbl->pQueryInfo) {
            return OBJ_NIL;
        }
        pNew = pVtbl->pQueryInfo(this->pNodeArrayClass, OBJ_QUERYINFO_TYPE_METHOD, "New");
        if (NULL == pNew) {
            return OBJ_NIL;
        }
        pArray = pNew();

        visit.pVisitor      = (void *)NodeTree_NodeAdd;
        visit.pObjectVisit  = this;
        visit.pChildOpen    = (void *)NodeTree_NodeOpen;
        visit.pObjectOpen   = this;
        visit.pChildClose   = (void *)NodeTree_NodeClose;
        visit.pObjectClose  = this;
        visit.pOther        = pArray;
        visit.index         = this->root;
        visit.level         = 0;

        if (pArray) {
            NodeArray_AppendNode(pArray, NodeTree_getNodeOpen(this), NULL);
            NodeTree_NodePreOrder(this, &visit);
            NodeArray_AppendNode(pArray, NodeTree_getNodeClose(this), NULL);
            NodeArray_setOther(pArray, this);
        }

        // Return to caller.
        return pArray;
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
        } else {
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

    /*
     Blocks's index numbers do not have to be contiguous nor does the
     root have to be index 1. Verify must insure that there are no
     back indices.  Subtrees may have multiple parents.
     */
    ERESULT         NodeTree_Verify(
        NODETREE_DATA   *this,
        const
        char            **pWhy
    )
    {
        //NODE_DATA       *pEntry;
        ERESULT         eRc = ERESULT_SUCCESS;
        //NAME_DATA       *pName;
        const
        char            *pStr = NULL;
        //OBJ_IUNKNOWN    *pVtbl;
        NODETREE_RECORD *pRcd;
        uint32_t        index;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;
        uint32_t        jMax;

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

        index = this->root;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, index);


        iMax = Blocks_getNumActive((BLOCKS_DATA *)this);
        jMax = Blocks_getMaxRecords((BLOCKS_DATA *)this);
        for (i=0,j=0; i<iMax && j<jMax; j++) {
            pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, i+1);
            if (pRcd) {
                i++;
            }
        }

#ifdef XYZZY
        iMax = ObjArray_getSize(this->pArray);
        for (i=0; i<iMax; ++i) {
            pEntry = (NODELINK_DATA *)ObjArray_Get(this->pArray, i+1);
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
                pName = NodeLink_getName(pEntry);
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
#endif

        // Return to caller.
    //eom:
        if (pStr && pWhy) {
            *pWhy = pStr;
        }
        return eRc;
    }



    //---------------------------------------------------------------
    //                          V i s i t
    //---------------------------------------------------------------

    ERESULT         NodeTree_VisitBreadthFirst(
        NODETREE_DATA   *this,
        void            (*pVisitor)(
            OBJ_ID          ,               // Object supplied below
            NODETREE_DATA   *,              // Our Tree
            NODE_DATA       *,              // Current Node
            uint16_t        ,               // Indent level
            void            *               // optional other data
        ),
        OBJ_ID          pObject,
        void            *pOther
    )
    {
        ERESULT         eRc;
        ARRAY_DATA      *pQueue = OBJ_NIL;
        NODETREE_VISIT  visit = {0};
        NODETREE_VISIT  visit2 = {0};
        //NODETREE_VISIT  pVisit;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (0 == this->root)
            return ERESULT_SUCCESS;

        pQueue = array_NewWithSize(sizeof(NODETREE_VISIT));
        if (pQueue == OBJ_NIL) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        visit.index = this->root;
        if (visit.index) {
            visit.pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, visit.index);
            if (visit.pRcd) {
                array_Enqueue(pQueue, &visit);
            }
        }
        while (array_getSize(pQueue)) {
            eRc = array_Dequeue(pQueue, &visit);
            if (ERESULT_OK(eRc)) {
                pVisitor(pObject, this, visit.pRcd->pNode, visit.level, visit.pOther);
                visit2.index = visit.pRcd->childIndex;
                if (visit2.index) {
                    visit2.pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, visit2.index);
                    visit2.level = visit.level + 1;
                    eRc = array_Enqueue(pQueue, &visit2);
                }
                visit2.index = visit.pRcd->siblingIndex;
                if (visit2.index) {
                    visit2.pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)this, visit2.index);
                    visit2.level = visit.level;
                    // Since this is a sibling, we need to visit it next.
                    eRc = array_Push(pQueue, &visit2);
                }
            }
        }

        obj_Release(pQueue);
        pQueue = OBJ_NIL;

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         NodeTree_VisitPostOrder(
        NODETREE_DATA    *this,
        void            (*pVisitor)(
                                OBJ_ID,                 // Object supplied below
                                NODETREE_DATA *,        // Our Tree
                                NODE_DATA *,            // Current Node
                                uint16_t  ,             // Indent level
                                void *
                               ),
        OBJ_ID          pObject,
        void            *pOther
    )
    {
        NODETREE_VISIT  visit;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeTree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (0 == this->root)
            return ERESULT_SUCCESS;

        visit.pVisitor      = pVisitor;
        visit.pObjectVisit  = pObject;
        visit.pChildOpen    = NULL;
        visit.pChildClose   = NULL;
        visit.pOther        = pOther;
        visit.index         = this->root;
        visit.level         = 0;

        NodeTree_NodePostOrder(this, &visit);

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         NodeTree_VisitPreOrder(
        NODETREE_DATA    *this,
        void            (*pVisitor)(
                            OBJ_ID,             // Object supplied below
                            NODETREE_DATA *,    // Our Tree
                            NODE_DATA *,        // Current Node
                            uint16_t ,          // Indent level
                            void *
                        ),
        OBJ_ID          pObject,
        void            *pOther
    )
    {
        NODETREE_VISIT  visit;

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
        if (0 == this->root)
            return ERESULT_SUCCESS;

        visit.pVisitor      = pVisitor;
        visit.pObjectVisit  = pObject;
        visit.pChildOpen    = NULL;
        visit.pChildClose   = NULL;
        visit.pOther        = pOther;
        visit.index         = this->root;
        visit.level         = 0;
        NodeTree_NodePreOrder(this, &visit);

        // Return to caller.
        return ERESULT_SUCCESS;
    }




    
#ifdef  __cplusplus
}
#endif


