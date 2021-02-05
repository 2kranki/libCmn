// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeBT.c
 *	Generated 01/10/2020 16:43:13
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
#include        <NodeBT_internal.h>
#include        <ascii.h>
#include        <listdl.h>
#include        <NodeEnum_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                  D e l e t e  E x i t
    //---------------------------------------------------------------

    ERESULT         NodeBT_DeleteExit(
        NODEBT_DATA     *this,
        NODEBT_RECORD   *pRecord,
        void            *pArg3
    )
    {

        if (pRecord->node.pKey) {
            obj_Release(pRecord->node.pKey);
            pRecord->node.pKey = OBJ_NIL;
        }
        if (pRecord->node.pValue) {
            obj_Release(pRecord->node.pValue);
            pRecord->node.pValue = OBJ_NIL;
        }

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                  E n u m  E x i t
    //---------------------------------------------------------------

    ERESULT         NodeBT_EnumExit(
        NODEBT_DATA     *this,
        NODEBT_RECORD   *pRecord,
        NODEENUM_DATA   *pEnum
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = pRecord->node.pKey;

        if (pNode && pEnum) {
            eRc = NodeEnum_AppendObj(pEnum, (NODE_DATA *)pNode);
        }

        return eRc;
    }



    //---------------------------------------------------------------
    //                  F i n d  E x i t
    //---------------------------------------------------------------

    ERESULT         NodeBT_FindExit(
        NODEBT_DATA     *this,
        NODEBT_RECORD   *pRecord,
        NODEBT_FIND     *pFind
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODE_DATA       *pNode = pRecord->node.pKey;

        if (pNode) {
            if (pFind->unique == pRecord->unique) {
                pFind->pRecord = pRecord;
                return ERESULT_DATA_NOT_FOUND;
            }
        }

        return eRc;
    }



    //---------------------------------------------------------------
    //                  F i n d  U n i q u e
    //---------------------------------------------------------------

    NODEBT_RECORD * NodeBT_FindUnique(
        NODEBT_DATA     *this,
        uint32_t        unique
    )
    {
        LISTDL_DATA     *pList;
        BLOCKS_NODE     *pEntry = NULL;
        NODEBT_RECORD   *pRecord = NULL;

        pList = Blocks_getList((BLOCKS_DATA *)this);
        if (pList) {
            pEntry = listdl_Head(pList);
            while (pEntry) {
                pRecord = (NODEBT_RECORD *)pEntry->data;
                if (unique == pRecord->unique) {
                    break;
                }
                pEntry = listdl_Next(pList, pEntry);
            }
        }

        return pRecord;
    }



    //---------------------------------------------------------------
    //                  L e f t - M o s t  C h i l d
    //---------------------------------------------------------------

    // The Left-Most Child is the smallest key of the sub-tree from
    // the given node.

    NODEBT_RECORD * NodeBT_LeftMostChild(
        NODEBT_DATA     *this,
        NODEBT_RECORD   *pRecord
    )
    {

        // Do initialization.
        if (NULL == pRecord) {
            return NULL;
        }

        if (pRecord) {
            while (pRecord->node.pLink[RBT_LEFT]) {
                pRecord = (NODEBT_RECORD *)pRecord->node.pLink[RBT_LEFT];
            }
        }

        // Return to caller.
        return pRecord;
    }



    //---------------------------------------------------------------
    //                  N o d e s  E x i t
    //---------------------------------------------------------------

    ERESULT         NodeBT_NodesExit(
        NODEBT_DATA     *this,
        NODEBT_RECORD   *pRecord,
        NODEARRAY_DATA  *pArray
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = pRecord->node.pKey;

        if (pNode && pArray) {
            eRc = NodeArray_AppendNode(pArray, (NODE_DATA *)pNode, NULL);
        }

        return eRc;
    }



    //---------------------------------------------------------------
    //                  V i s i t  E x i t
    //---------------------------------------------------------------

    ERESULT         NodeBT_VisitExit(
        NODEBT_DATA     *this,
        NODEBT_RECORD   *pRecord,
        NODEBT_VISIT    *pParms
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODE_DATA       *pNode;

        if (pRecord) {
            pNode = pRecord->node.pKey;
            if (pNode) {
                if (pParms->pScan) {
                    eRc = pParms->pScan(pParms->pObj, pNode, pParms->pArg3);
                }
            }
        }

        return eRc;
    }



    //---------------------------------------------------------------
    //                  V i s i t  N o d e s
    //---------------------------------------------------------------

    /*! Visit all the nodes from the given node and below in the Tree
     using a Pre-order traversal.
     */
    ERESULT         NodeBT_VisitNodeInRecurse(
        NODEBT_DATA     *this,
        NODEBT_RECORD   *pRecord,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEBT_RECORD   *pWork;

        if (pRecord) {
            pWork = (NODEBT_RECORD *)pRecord->node.pLink[RBT_LEFT];
            if (pWork) {
                eRc = NodeBT_VisitNodeInRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            eRc = pScan(pObj, pRecord->node.pKey, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
            pWork = (NODEBT_RECORD *)pRecord->node.pLink[RBT_RIGHT];
            if (pWork) {
                eRc = NodeBT_VisitNodeInRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
        }

        return eRc;
    }


    /*! Visit all the nodes from the given node and below in the Tree
     using a Post-order traversal.
     */
    ERESULT         NodeBT_VisitNodePostRecurse(
        NODEBT_DATA     *this,
        NODEBT_RECORD   *pRecord,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEBT_RECORD   *pWork;

        if (pRecord) {
            pWork = (NODEBT_RECORD *)pRecord->node.pLink[RBT_LEFT];
            if (pWork) {
                eRc = NodeBT_VisitNodePostRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            pWork = (NODEBT_RECORD *)pRecord->node.pLink[RBT_RIGHT];
            if (pWork) {
                eRc = NodeBT_VisitNodePostRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            eRc = pScan(pObj, pRecord->node.pKey, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }

        return eRc;
    }


    /*! Visit all the nodes from the given node and below in the Tree
     using a Pre-order traversal.
     */
    ERESULT         NodeBT_VisitNodePreRecurse(
        NODEBT_DATA     *this,
        NODEBT_RECORD   *pRecord,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEBT_RECORD   *pWork;

        if (pRecord) {
            eRc = pScan(pObj, pRecord->node.pKey, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
            pWork = (NODEBT_RECORD *)pRecord->node.pLink[RBT_LEFT];
            if (pWork) {
                eRc = NodeBT_VisitNodePreRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            pWork = (NODEBT_RECORD *)pRecord->node.pLink[RBT_RIGHT];
            if (pWork) {
                eRc = NodeBT_VisitNodePreRecurse(this, pWork, pScan, pObj, pArg3);
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

    NODEBT_DATA *     NodeBT_Alloc (
        void
    )
    {
        NODEBT_DATA       *this;
        uint32_t        cbSize = sizeof(NODEBT_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEBT_DATA *     NodeBT_New (
        void
    )
    {
        NODEBT_DATA       *this;
        
        this = NodeBT_Alloc( );
        if (this) {
            this = NodeBT_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          R o o t
    //---------------------------------------------------------------

    NODE_DATA *     NodeBT_getRoot(
        NODEBT_DATA     *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        // Return to caller.
        return this->tree.pRoot->pKey;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        NodeBT_getSize (
        NODEBT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return (uint32_t)this->tree.size;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodeBT_getSuperVtbl (
        NODEBT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
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

    ERESULT         NodeBT_Add(
        NODEBT_DATA     *this,
        NODE_DATA       *pNode,
        bool            fReplace
    )
    {
        NODEBT_RECORD   *pRecord = NULL;
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        int             iRc;
        uint32_t        unique;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pRecord = Blocks_RecordNew((BLOCKS_DATA *)this, &unique);
        if (NULL == pRecord) {
            return ERESULT_OUT_OF_MEMORY;
        }
        pRecord->node.pKey = pNode;
        pRecord->unique = unique;
        pRecord->node.color = RBT_RED;

        iRc = rbt_InsertNode(&this->tree, (RBT_NODE *)pRecord);
        if (iRc) {
            obj_Retain(pNode);
            eRc = ERESULT_SUCCESS;
        }
        else
            eRc = ERESULT_DATA_ALREADY_EXISTS;

        // Return to caller.
        return eRc;
    }


    ERESULT         NodeBT_AddA(
        NODEBT_DATA     *this,
        int32_t         cls,
        const
        char            *pNameA,            // UTF-8
        OBJ_ID          pData
    )
    {
        NODE_DATA       *pNode = NULL;
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pNode = Node_NewWithUTF8AndClass(cls, pNameA, pData);
        if (pNode) {
            eRc = NodeBT_Add(this, pNode, false);
        }
        obj_Release(pNode);
        pNode = OBJ_NIL;

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      A d d  U p d a t e
    //---------------------------------------------------------------

    ERESULT         NodeBT_AddUpdate(
        NODEBT_DATA     *this,
        NODE_DATA       *pNode,
        bool            fReplace
    )
    {
        NODE_DATA       *pFound;
        NODEBT_RECORD   *pRecord = NULL;
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        int             iRc;
        uint32_t        unique;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pFound = NodeBT_Find(this, pNode);
        if (pFound) {
            eRc = NodeBT_Delete(this, pNode);
        }

        pRecord = Blocks_RecordNew((BLOCKS_DATA *)this, &unique);
        if (NULL == pRecord) {
            return ERESULT_OUT_OF_MEMORY;
        }
        pRecord->node.pKey = pNode;
        pRecord->unique = unique;
        pRecord->node.color = RBT_RED;

        iRc = rbt_InsertNode(&this->tree, (RBT_NODE *)pRecord);
        if (iRc) {
            obj_Retain(pNode);
            eRc = ERESULT_SUCCESS;
        }
        else
            eRc = ERESULT_DATA_ALREADY_EXISTS;

        // Return to caller.
        return eRc;
    }


    ERESULT         NodeBT_AddUpdateA(
        NODEBT_DATA     *this,
        int32_t         cls,
        const
        char            *pNameA,            // UTF-8
        OBJ_ID          pData
    )
    {
        NODE_DATA       *pNode = NULL;
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pNode = Node_NewWithUTF8AndClass(cls, pNameA, pData);
        if (pNode) {
            eRc = NodeBT_AddUpdate(this, pNode, false);
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
        ERESULT eRc = NodeBT_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NODEBT object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeBT_Assign (
        NODEBT_DATA		*this,
        NODEBT_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeBT_Validate(pOther)) {
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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             NodeBT_Compare (
        NODEBT_DATA     *this,
        NODEBT_DATA     *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!NodeBT_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        NodeBT      *pCopy = NodeBT_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODEBT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEBT_DATA *     NodeBT_Copy (
        NODEBT_DATA       *this
    )
    {
        NODEBT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeBT_New( );
        if (pOther) {
            eRc = NodeBT_Assign(this, pOther);
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

    void            NodeBT_Dealloc (
        OBJ_ID          objId
    )
    {
        NODEBT_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODEBT_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------

    ERESULT         NodeBT_Delete (
        NODEBT_DATA     *this,
        NODE_DATA       *pNode
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        iRc = rbt_Delete(&this->tree, pNode);
        if (iRc)
            eRc = ERESULT_SUCCESS;
        else
            eRc = ERESULT_DATA_NOT_FOUND;

        // Return to caller.
        return eRc;
    }


    ERESULT         NodeBT_DeleteA (
        NODEBT_DATA     *this,
        int32_t         cls,
        const
        char            *pNameA             // UTF-8
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(NULL == pNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pNode = Node_NewWithUTF8AndClass(cls, pNameA, OBJ_NIL);
        if (pNode) {
            eRc = NodeBT_Delete(this, pNode);
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }

        // Return to caller.
        return eRc;
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
    ERESULT         NodeBT_Disable (
        NODEBT_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeBT_Validate(this)) {
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
    ERESULT         NodeBT_Enable (
        NODEBT_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeBT_Validate(this)) {
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
    //                         E n u m
    //---------------------------------------------------------------

    NODEENUM_DATA * NodeBT_Enum (
        NODEBT_DATA     *this
    )
    {
        NODEENUM_DATA   *pEnum = OBJ_NIL;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        pEnum = NodeEnum_New();
        if (pEnum) {
            eRc =   Blocks_ForEach(
                                   (BLOCKS_DATA *)this,
                                   (void *)NodeBT_EnumExit,
                                   this,
                                   pEnum
                                   );
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pEnum);
                pEnum = OBJ_NIL;
            }
        }
        NodeEnum_SortAscending(pEnum);

        // Return to caller.
        return pEnum;
    }



    //---------------------------------------------------------------
    //     E x p a n d  E n v i r o n m e n t  V a r i a b l e s
    //---------------------------------------------------------------

    /*!
     Substitute environment variables into the current string using a BASH-like
     syntax.  Variable names should have the syntax of:
     '$' '{'[a-zA-Z_][a-zA-Z0-9_]* '}'.
     Substitutions are not rescanned after insertion.
     @param     this    object pointer
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
     is returned.
     */
    ERESULT         NodeBT_ExpandVars (
        NODEBT_DATA     *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;
        uint32_t        i = 0;
        uint32_t        iBegin;
        uint32_t        len;
        uint32_t        lenPrefix;
        uint32_t        lenSuffix;
        int32_t         chr;
        bool            fMore = true;
        //PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        ASTR_DATA       *pData = OBJ_NIL;
        const
        char            *pEnvVar = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if(!NodeBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (0 == AStr_getLength(pStr)) {
            return ERESULT_SUCCESS;
        }

        // Expand Environment variables.
        while (fMore) {
            fMore = false;
            eRc = AStr_CharFindNextW32(pStr, &i, '$');
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            else {
                chr = AStr_CharGetW32(pStr, i+1);
                if (chr == '{') {
                    i += 2;
                    iBegin = i;
                    eRc = AStr_CharFindNextW32(pStr, &i, '}');
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_PARSE_ERROR;
                    }
                    len = i - iBegin;
                    eRc = AStr_Mid(pStr, iBegin, len, &pName);
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    lenPrefix = 2;
                    lenSuffix = 1;

                    // Find the name from the Dictionary.
                do_replace:
                    pNode = NodeBT_FindA(this, 0, AStr_getData(pName));
                    if (OBJ_NIL == pNode) {
                        obj_Release(pName);
                        return ERESULT_DATA_NOT_FOUND;
                    }
                    obj_Release(pName);
                    pName = OBJ_NIL;
                    pData = Node_getData(pNode);
                    if((OBJ_NIL == pData) || !obj_IsKindOf(pData, OBJ_IDENT_ASTR)) {
                        DEBUG_BREAK();
                        return ERESULT_DATA_MISSING;
                    }

                    // Substitute the name from the Dictionary.
                    eRc =   AStr_Remove(
                                        pStr,
                                        (iBegin - lenPrefix),
                                        (len + lenPrefix + lenSuffix)
                                        );
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    eRc = AStr_InsertA(pStr, (iBegin - lenPrefix), AStr_getData(pData));
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    i = iBegin - lenPrefix + AStr_getSize(pData);
                    pEnvVar = NULL;
                    pData = OBJ_NIL;
                    pNode = OBJ_NIL;
                    fMore = true;
                }
                else if (chr == '$') {
                    eRc = AStr_Remove(pStr, i, 1);
                    ++i;
                    fMore = true;
                    continue;
                }
                else {
                    //chr = AStr_CharGetW32(pStr, i+1);
                    if (ascii_isLabelFirstCharW32(chr)) {
                        ++i;
                        iBegin = i;
                        for (;;) {
                            ++i;
                            chr = AStr_CharGetW32(pStr, i);
                            if (!ascii_isLabelCharW32(chr)) {
                                break;
                            }
                        }
                        len = i - iBegin;
                        eRc = AStr_Mid(pStr, iBegin, len, &pName);
                        if (ERESULT_FAILED(eRc)) {
                            return ERESULT_OUT_OF_MEMORY;
                        }
                        lenPrefix = 1;
                        lenSuffix = 0;

                        goto do_replace;

                    }
                    else
                        return ERESULT_PARSE_ERROR;
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    NODE_DATA *     NodeBT_Find (
        NODEBT_DATA     *this,
        NODE_DATA       *pNode
    )
    {
        NODEBT_RECORD   record = {.node.pKey = pNode};
        NODEBT_RECORD   *pWork;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
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

        pWork = (NODEBT_RECORD *)rbt_FindNode(&this->tree, (RBT_NODE *)&record);
        if (pWork) {
            return pWork->node.pKey;
        }

        // Return to caller.
        return OBJ_NIL;
    }


    NODE_DATA *     NodeBT_FindA (
        NODEBT_DATA     *this,
        int32_t         cls,
        const
        char            *pNameA             // UTF-8
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        NODE_DATA       *pFound = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if(NULL == pNameA) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pNode = Node_NewWithUTF8AndClass(cls, pNameA, OBJ_NIL);
        if (pNode) {
            pFound = NodeBT_Find(this, pNode);
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }

        // Return to caller.
        return pFound;
    }



    //---------------------------------------------------------------
    //                          F o r  E a c h
    //---------------------------------------------------------------

    ERESULT         NodeBT_ForEach(
        NODEBT_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,               // Used as first parameter of scan method
        void            *pArg3              // Used as third parameter of scan method
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL_DATA     *pList = NULL;
        BLOCKS_NODE     *pEntry = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pList = Blocks_getList((BLOCKS_DATA *)this);
        pEntry = listdl_Head(pList);
        while (pEntry) {
            NODEBT_RECORD       *pRecord = (NODEBT_RECORD *)pEntry->data;

            eRc =   pScan(pObj, pRecord->node.pKey, pArg3);
            if (ERESULT_FAILED(eRc))
                break;

            pEntry = listdl_Next(pList, pEntry);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEBT_DATA *   NodeBT_Init (
        NODEBT_DATA     *this
    )
    {
        uint32_t        cbSize = sizeof(NODEBT_DATA);
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

        this = (OBJ_ID)Blocks_Init((BLOCKS_DATA *)this);        // Needed for Inheritance
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeBT_Vtbl);

        // Set up Blocks to hold tree data.
        eRc = Blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(NODEBT_RECORD));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        Blocks_setDeleteExit(
                        (BLOCKS_DATA *)this,
                        (void *)NodeBT_DeleteExit,
                        this,               // 1st parameter
                        NULL                // 3rd parameter
        );

        // Set up Red-Black tree to use Blocks to hold its data.
        rbt_Init(
                 &this->tree,
                 (void *)Node_Compare,
                 (sizeof(NODEBT_RECORD) - sizeof(RBT_NODE)),
                 (void *)Blocks_RecordNew,
                 (void *)Blocks_RecordFree,
                 this
        );
        this->tree.pNodeAlloc = (void *)Blocks_RecordNew;
        this->tree.pNodeFree = (void *)Blocks_RecordFree;
        this->tree.pObjAllocFree = this;
        this->tree.dataSize = sizeof(NODEBT_RECORD) - sizeof(RBT_NODE);

    #ifdef NDEBUG
    #else
        if (!NodeBT_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "NodeBT::sizeof(NODEBT_DATA) = %lu\n", sizeof(NODEBT_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODEBT_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeBT_IsEnabled (
        NODEBT_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
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
    //                         N o d e s
    //---------------------------------------------------------------

    NODEARRAY_DATA * NodeBT_Nodes(
        NODEBT_DATA     *this
    )
    {
        NODEARRAY_DATA  *pNodes = OBJ_NIL;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        pNodes = NodeArray_New();
        if (pNodes) {
            eRc =   Blocks_ForEach(
                                (BLOCKS_DATA *)this,
                                (void *)NodeBT_NodesExit,
                                this,
                                pNodes
                    );
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pNodes);
                pNodes = OBJ_NIL;
            }
            else
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
        void        *pMethod = NodeBT_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeBT", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeBT_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEBT_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEBT_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeBT_Class();
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
                            return NodeBT_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeBT_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeBT_ToDebugString;
                        }
#ifdef  NODEBT_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return NodeBT_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeBT_ToDebugString)
                    return "ToDebugString";
#ifdef  NODEBT_JSON_SUPPORT
                if (pData == NodeBT_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeBT_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeBT_ToDebugString (
        NODEBT_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        LISTDL_DATA     *pList = NULL;
        BLOCKS_NODE     *pEntry = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
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
                    NodeBT_getSize(this),
                    obj_getRetainCount(this)
            );

        pList = Blocks_getList((BLOCKS_DATA *)this);
        pEntry = listdl_Head(pList);
        while (pEntry) {
            NODEBT_RECORD       *pRecord = (NODEBT_RECORD *)pEntry->data;
            OBJ_DATA            *pData;

            pData = pRecord->node.pKey;
            if (pData) {
                if (((OBJ_DATA *)(pData))->pVtbl->pToDebugString) {
                    ASTR_DATA   *pWrkStr =  ((OBJ_DATA *)(pData))->pVtbl->pToDebugString(
                                                        pData,
                                                        indent+4
                                            );
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }

            pEntry = listdl_Next(pList, pEntry);
        }

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
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            NodeBT_Validate (
        NODEBT_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODEBT))
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


        if (!(obj_getSize(this) >= sizeof(NODEBT_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                     V e r i f y  T r e e
    //---------------------------------------------------------------

    ERESULT         NodeBT_VerifyTree(
        NODEBT_DATA     *this
    )
    {
        ERESULT         eRc;
        int             iRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeBT_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        iRc = rbt_VerifyTree(&this->tree, rbt_getRoot(&this->tree));
        if (iRc)
            eRc = ERESULT_SUCCESS;
        else
            eRc = ERESULT_DATA_ERROR;

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                  V i s i t  N o d e s
    //---------------------------------------------------------------

    /*! Visit all the nodes in the Tree using a In-order traversal.
     */

    ERESULT         NodeBT_VisitNodesInRecurse(
        NODEBT_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc;
        NODEBT_VISIT    parms;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pScan) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        parms.pScan = pScan;
        parms.pObj = pObj;
        parms.pArg3 = pArg3;

        eRc =   rbt_VisitNodeInRecurse(
                        &this->tree,
                        this->tree.pRoot,
                        (void *)NodeBT_VisitExit,
                        this,
                        &parms
                );

        return eRc;
    }


    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */

    ERESULT         NodeBT_VisitNodesPostRecurse(
        NODEBT_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc;
        NODEBT_VISIT    parms;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pScan) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        parms.pScan = pScan;
        parms.pObj = pObj;
        parms.pArg3 = pArg3;

        eRc =   rbt_VisitNodePostRecurse(
                        &this->tree,
                        this->tree.pRoot,
                        (void *)NodeBT_VisitExit,
                        this,
                        &parms
                );

        return eRc;
    }


    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */

    ERESULT         NodeBT_VisitNodesPreRecurse(
        NODEBT_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc;
        NODEBT_VISIT    parms;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pScan) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        parms.pScan = pScan;
        parms.pObj = pObj;
        parms.pArg3 = pArg3;

        eRc =   rbt_VisitNodePreRecurse(
                        &this->tree,
                        this->tree.pRoot,
                        (void *)NodeBT_VisitExit,
                        this,
                        &parms
                );

        return eRc;
    }




    
#ifdef	__cplusplus
}
#endif


