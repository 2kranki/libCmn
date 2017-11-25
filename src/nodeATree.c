// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeATree.c
 *	Generated 08/31/2016 21:21:55
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
#include "nodeATree_internal.h"
#include <name_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    NAME_DATA       closeName = {{0}};
    static
    NODE_DATA       closeNode = {{0}};          // Close Node - ')'
    static
    NAME_DATA       openName  = {{0}};
    static
    NODE_DATA       openNode  = {{0}};          // Open Node - '('
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /*!
     Calculate First Child index given the parent.
     @param     this    nodeATree object pointer
     @param     index   parent node index (relative to 1)
     @return    If successful, an Node index, otherwise 0.
     */
    uint32_t        nodeATree_FirstChildIndex(
        NODEATREE_DATA  *this,
        uint32_t        index       // Relative to 1
    )
    {
        uint32_t        ans;
        
        ans = (this->B * index) - this->B_2;
        
        return ans;
    }



    /*!
     Calculate Parent index given a Child Index.
     @param     this    nodeATree object pointer
     @param     index   child node index (relative to 1)
     @return    If successful, an Node index, otherwise 0.
     */
    uint32_t        nodeATree_ParentIndex(
        NODEATREE_DATA  *this,
        uint32_t        index       // Relative to 1
    )
    {
        uint32_t        ans;
        
        ans = (this->B_2 + index) / this->B;
        
        return ans;
    }
    
    
    
    ERESULT         nodeATree_NodePreorder(
        NODEATREE_DATA  *this,
        void            (pVisitor)(
                                 OBJ_ID,             // Object supplied below
                                 NODEATREE_DATA *,   // Our Tree
                                 NODE_DATA *,        // Current Node
                                 uint16_t            // Indent level * 4
                                 ),
        OBJ_ID          pObject,
        uint32_t        index,
        uint16_t        indent
    )
    {
        NODE_DATA       *pNode;
        NODE_DATA       *pChild;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        childIndex;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        pNode = objArray_Get(this->pArray, index);
        pVisitor(pObject, this, (NODE_DATA *)pNode, indent);
        
        iMax = this->B;
        for (i=0; i<iMax; ++i) {
            pChild = nodeATree_Child(this, index, i, &childIndex);
            if (pChild) {
                nodeATree_NodePreorder(this, pVisitor, pObject, childIndex, indent+4);
            }
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    ERESULT         nodeATree_UpDownNodePre(
        NODEATREE_DATA  *this,
        uint32_t        index,
        NODEARRAY_DATA	*pArray
    )
    {
        NODE_DATA       *pNode;
        NODE_DATA       *pChild;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        childIndex;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        iMax = this->B;
        
        pNode = objArray_Get(this->pArray, index);
        nodeArray_AppendNode(pArray, pNode, NULL);
        if (iMax) {
            nodeArray_AppendNode(pArray, nodeATree_OpenNode(), NULL);
            for (i=0; i<iMax; ++i) {
                pChild = nodeATree_Child(this, index, i, &childIndex);
                if (pChild) {
                    nodeATree_UpDownNodePre(this, childIndex, pArray);
                }
            }
            nodeArray_AppendNode(pArray, nodeATree_CloseNode(), NULL);
        }
        
        // Return to caller.
        return true;
    }
    
    
    

    
    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEATREE_DATA * nodeATree_Alloc(
    )
    {
        NODEATREE_DATA  *this;
        uint32_t        cbSize = sizeof(NODEATREE_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEATREE_DATA * nodeATree_New(
        uint16_t        order
    )
    {
        NODEATREE_DATA  *this;
        
        this = nodeATree_Alloc( );
        if (this) {
            this = nodeATree_Init(this, order);
        } 
        return this;
    }



    NODE_DATA *     nodeATree_CloseNode(
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

    
    NODE_DATA *     nodeATree_OpenNode(
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

    OBJARRAY_DATA * nodeATree_getArray(
        NODEATREE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            nodeATree_setArray(
        NODEATREE_DATA  *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
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
    
    
    
    ERESULT         nodeATree_getLastError(
        NODEATREE_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return this->eRc;
    }
    
    
    
    uint32_t        nodeATree_getOrder(
        NODEATREE_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return this->B;
    }
    
    
    
    uint16_t        nodeATree_getPriority(
        NODEATREE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            nodeATree_setPriority(
        NODEATREE_DATA  *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

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
        ERESULT eRc = nodeATree__Assign(this,pOther);
     @endcode
     @param     this    NODEATREE object pointer
     @param     pOther  a pointer to another NODEATREE object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         nodeATree_Assign(
        NODEATREE_DATA		*this,
        NODEATREE_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeATree_Validate(pOther) ) {
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
        
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;

        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        nodeATree      *pCopy = nodeATree_Copy(this);
     @endcode
     @param     this    NODEATREE object pointer
     @return    If successful, a NODEATREE object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the NODEATREE object.
     */
    NODEATREE_DATA *     nodeATree_Copy(
        NODEATREE_DATA       *this
    )
    {
        NODEATREE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeATree_New(this->B);
        if (pOther) {
            eRc = nodeATree_Assign(this, pOther);
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

    void            nodeATree_Dealloc(
        OBJ_ID          objId
    )
    {
        NODEATREE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODEATREE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pArray) {
            obj_Release(this->pArray);
            this->pArray = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      C h i l d
    //---------------------------------------------------------------

    NODE_DATA *  nodeATree_Child(
        NODEATREE_DATA *this,
        uint32_t        parent,
        uint32_t        index,          // Relative to zero
        uint32_t        *pIndex         // Optional Returned Index
    )
    {
        NODE_DATA       *pNode;
        uint32_t        value;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( !((parent > 0) && (parent <= objArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
        if( !(index < this->B) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
    #endif
        value = nodeATree_FirstChildIndex(this, parent);
        value += index;

        pNode = objArray_Get(this->pArray, value);

        // Return to caller.
        if (pIndex) {
            *pIndex = value;
        }
        this->eRc = objArray_getLastError(this->pArray);
        return pNode;
    }


    uint32_t        nodeATree_ChildAdd(
        NODEATREE_DATA *this,
        uint32_t        parent,
        uint32_t        index,
        NODE_DATA       *pNode
    )
    {
        uint32_t        value;
        NODE_DATA       *pChild;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return 0;
        }
        if( !(parent <= objArray_getSize(this->pArray)) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
        if( !(index <= this->B) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
        if (parent == 0) {
            if( !(index == 0) ) {
                DEBUG_BREAK();
                this->eRc = ERESULT_INVALID_PARAMETER;
                return 0;
            }
        }
        if( pNode == OBJ_NIL ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif
        value = nodeATree_FirstChildIndex(this, parent);
        value += index;
        if (parent == 0) {
            value = 1;
        }
        
        if (index == 0) {
            for (int i=0; i<this->B; ++i) {
                pChild = objArray_Get(this->pArray, value+i);
                if (pChild) {
                    continue;
                }
                value += i;
                break;
            }
        }
        else {
            pChild = objArray_Get(this->pArray, value);
            if (pChild) {
                this->eRc = ERESULT_DATA_ALREADY_EXISTS;
                value = 0;
                return value;
            }
        }
        
        node_setIndex(pNode, value);
        this->eRc = objArray_Put(this->pArray, value, pNode);
        
        // Return to caller.
    //eom:
        return value;
    }
    
    

    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEATREE_DATA * nodeATree_Init(
        NODEATREE_DATA  *this,
        uint16_t        order
    )
    {
        uint32_t        cbSize = sizeof(NODEATREE_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (order < 2) {
            DEBUG_BREAK();
            obj_Release(this);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODEATREE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_NODEATREE);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeATree_Vtbl);
        
        this->B = order;
        this->B_2 = order - 2;
        this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            nodeATree_IsEnabled(
        NODEATREE_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(this))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                       N o d e
    //---------------------------------------------------------------
    
    NODE_DATA *  nodeATree_Node(
        NODEATREE_DATA  *this,
        uint32_t        index
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if( !((index > 0) && (index <= objArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif
        
        pNode = objArray_Get(this->pArray, index);
        
        // Return to caller.
        this->eRc = objArray_getLastError(this->pArray);
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                       P a r e n t
    //---------------------------------------------------------------
    
    NODE_DATA *  nodeATree_Parent(
        NODEATREE_DATA  *this,
        uint32_t        index
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if( !((index > 1) && (index <= objArray_getSize(this->pArray))) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif
        index = nodeATree_ParentIndex(this, index);
        
        pNode = objArray_Get(this->pArray, index);
        
        // Return to caller.
        this->eRc = objArray_getLastError(this->pArray);
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = nodeATree_ToDebugString(this,4);
     @endcode
     @param     this    NODEATREE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeATree_ToDebugString(
        NODEATREE_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
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
                     "{%p(nodeATree) B=%d ",
                     this,
                     this->B
            );
        AStr_AppendA(pStr, str);

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
        
        j = snprintf(str, sizeof(str), " %p(nodeATree)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                T o  L i n e a r i z a t i o n
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * nodeATree_ToLinearizationPre(
        NODEATREE_DATA	*this
    )
    {
        NODEARRAY_DATA  *pArray;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pArray = nodeArray_New();
        if (pArray) {
            nodeArray_AppendNode(pArray, nodeATree_OpenNode(), NULL);
            nodeATree_UpDownNodePre(this, 1, pArray);
            nodeArray_AppendNode(pArray, nodeATree_CloseNode(), NULL);
        }
        
        // Return to caller.
        return pArray;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeATree_Validate(
        NODEATREE_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_NODEATREE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(NODEATREE_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                    V i s i t  P r e o r d e r
    //---------------------------------------------------------------
    
    ERESULT         nodeATree_VisitPreorder(
        NODEATREE_DATA	*this,
        void            (pVisitor)(
                              OBJ_ID,             // Object supplied below
                              NODEATREE_DATA *,   // Our Tree
                              NODE_DATA *,        // Current Node
                              uint16_t            // Indent level * 4
                              ),
        OBJ_ID          pObject
        )
    {
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == this) {
            this->eRc = ERESULT_SUCCESS;
            return this->eRc;
        }
#ifdef NDEBUG
#else
        if( !nodeATree_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        eRc = nodeATree_NodePreorder(this, pVisitor, pObject, 1, 0);
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


