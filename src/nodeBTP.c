// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeBTP.c
 *	Generated 11/22/2018 23:21:01
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
#include        <nodeBTP_internal.h>
#include        <listdl.h>
#include        <nodeEnum_internal.h>
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
    
    ERESULT         nodeBTP_DeleteExit(
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pRecord,
        void            *pArg3
    )
    {
        
        if (pRecord->node.pData) {
            obj_Release(pRecord->node.pData);
            pRecord->node.pData = OBJ_NIL;
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                  E n u m  E x i t
    //---------------------------------------------------------------
    
    ERESULT         nodeBTP_EnumExit(
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pRecord,
        NODEENUM_DATA   *pEnum
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = pRecord->node.pData;
        
        if (pNode && pEnum) {
            eRc = nodeEnum_Append(pEnum, (NODE_DATA *)pNode);
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  F i n d  E x i t
    //---------------------------------------------------------------
    
    ERESULT         nodeBTP_FindExit(
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pRecord,
        NODEBTP_FIND    *pFind
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODE_DATA       *pNode = pRecord->node.pData;
        
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
    
    NODEBTP_RECORD * nodeBTP_FindUnique(
        NODEBTP_DATA    *this,
        uint32_t        unique
    )
    {
        LISTDL_DATA     *pList;
        BLOCKS_NODE     *pEntry = NULL;
        NODEBTP_RECORD  *pRecord = NULL;
        
        pList = blocks_getList((BLOCKS_DATA *)this);
        if (pList) {
            pEntry = listdl_Head(pList);
            while (pEntry) {
                pRecord = (NODEBTP_RECORD *)pEntry->data;
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
    
    NODEBTP_RECORD * nodeBTP_LeftMostChild(
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pRecord
    )
    {
        
        // Do initialization.
        if (NULL == pRecord) {
            return NULL;
        }
        
        if (pRecord) {
            while (pRecord->node.pLink[RBT_LEFT]) {
                pRecord = (NODEBTP_RECORD *)pRecord->node.pLink[RBT_LEFT];
            }
        }
        
        // Return to caller.
        return pRecord;
    }
    
    
    
    //---------------------------------------------------------------
    //                  N o d e  C o m p a r e
    //---------------------------------------------------------------
    
    int             nodeBTP_NodeCmp(
        RBT_TREE        *this,
        NODEBTP_RECORD  *pRecordA,
        NODEBTP_RECORD  *pRecordB
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNodeA = pRecordA->node.pData;
        NODE_DATA       *pNodeB = pRecordB->node.pData;

        eRc = node_Compare(pNodeA, pNodeB);
        if (eRc == ERESULT_SUCCESS_EQUAL) {
            return 0;
        }
        else if (eRc == ERESULT_SUCCESS_LESS_THAN) {
            return -1;
        }

        return 1;
    }
    
    
    
    //---------------------------------------------------------------
    //                  N o d e s  E x i t
    //---------------------------------------------------------------
    
    ERESULT         nodeBTP_NodesExit(
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pRecord,
        NODEARRAY_DATA  *pArray
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = pRecord->node.pData;
        
        if (pNode && pArray) {
            eRc = nodeArray_AppendNode(pArray, (NODE_DATA *)pNode, NULL);
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  V i s i t  E x i t
    //---------------------------------------------------------------
    
    ERESULT         nodeBTP_VisitExit(
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pRecord,
        NODEBTP_VISIT   *pParms
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODE_DATA       *pNode;
        
        if (pRecord) {
            pNode = pRecord->node.pData;
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
    ERESULT         nodeBTP_VisitNodeInRecurse(
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pRecord,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEBTP_RECORD  *pWork;
        
        if (pRecord) {
            pWork = (NODEBTP_RECORD *)pRecord->node.pLink[RBT_LEFT];
            if (pWork) {
                eRc = nodeBTP_VisitNodeInRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            eRc = pScan(pObj, pRecord->node.pData, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
            pWork = (NODEBTP_RECORD *)pRecord->node.pLink[RBT_RIGHT];
            if (pWork) {
                eRc = nodeBTP_VisitNodeInRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
        }
        
        return eRc;
    }
    
    
    /*! Visit all the nodes from the given node and below in the Tree
     using a Post-order traversal.
     */
    ERESULT         nodeBTP_VisitNodePostRecurse(
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pRecord,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEBTP_RECORD  *pWork;
        
        if (pRecord) {
            pWork = (NODEBTP_RECORD *)pRecord->node.pLink[RBT_LEFT];
            if (pWork) {
                eRc = nodeBTP_VisitNodePostRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            pWork = (NODEBTP_RECORD *)pRecord->node.pLink[RBT_RIGHT];
            if (pWork) {
                eRc = nodeBTP_VisitNodePostRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            eRc = pScan(pObj, pRecord->node.pData, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }
        
        return eRc;
    }
    
    
    /*! Visit all the nodes from the given node and below in the Tree
     using a Pre-order traversal.
     */
    ERESULT         nodeBTP_VisitNodePreRecurse(
        NODEBTP_DATA    *this,
        NODEBTP_RECORD  *pRecord,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEBTP_RECORD  *pWork;
        
        if (pRecord) {
            eRc = pScan(pObj, pRecord->node.pData, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
            pWork = (NODEBTP_RECORD *)pRecord->node.pLink[RBT_LEFT];
            if (pWork) {
                eRc = nodeBTP_VisitNodePreRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            pWork = (NODEBTP_RECORD *)pRecord->node.pLink[RBT_RIGHT];
            if (pWork) {
                eRc = nodeBTP_VisitNodePreRecurse(this, pWork, pScan, pObj, pArg3);
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

    NODEBTP_DATA *     nodeBTP_Alloc(
        void
    )
    {
        NODEBTP_DATA       *this;
        uint32_t        cbSize = sizeof(NODEBTP_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEBTP_DATA *     nodeBTP_New(
        void
    )
    {
        NODEBTP_DATA       *this;
        
        this = nodeBTP_Alloc( );
        if (this) {
            this = nodeBTP_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        nodeBTP_getPriority(
        NODEBTP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            nodeBTP_setPriority(
        NODEBTP_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
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
    
    NODE_DATA *     nodeBTP_getRoot(
        NODEBTP_DATA    *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        // Return to caller.
        return this->tree.pRoot->pData;
    }
    
    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        nodeBTP_getSize(
        NODEBTP_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  nodeBTP_getSuperVtbl(
        NODEBTP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
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
    
    ERESULT         nodeBTP_Add(
        NODEBTP_DATA    *this,
        NODE_DATA       *pNode,
        bool            fReplace
    )
    {
        NODEBTP_RECORD  *pRecord = NULL;
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        int             iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pRecord = blocks_RecordNew((BLOCKS_DATA *)this);
        if (NULL == pRecord) {
            return ERESULT_OUT_OF_MEMORY;
        }
        obj_Retain(pNode);
        pRecord->node.pData = pNode;
        pRecord->unique = blocks_getUnique((BLOCKS_DATA *)this);
        pRecord->node.color = RBT_RED;

        iRc = rbt_InsertNode(&this->tree, (RBT_NODE *)pRecord);
        if (iRc)
            eRc = ERESULT_SUCCESS;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         nodeBTP_AddA(
        NODEBTP_DATA    *this,
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
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNode = node_NewWithUTF8AndClass(pNameA, cls, pData);
        if (pNode) {
            eRc = nodeBTP_Add(this, pNode, false);
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
        ERESULT eRc = nodeBTP_Assign(this,pOther);
     @endcode 
     @param     this    NODEBTP object pointer
     @param     pOther  a pointer to another NODEBTP object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         nodeBTP_Assign(
        NODEBTP_DATA	*this,
        NODEBTP_DATA    *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeBTP_Validate(pOther) ) {
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
    ERESULT         nodeBTP_Compare(
        NODEBTP_DATA    *this,
        NODEBTP_DATA    *pOther
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
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeBTP_Validate(pOther) ) {
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
        nodeBTP      *pCopy = nodeBTP_Copy(this);
     @endcode 
     @param     this    NODEBTP object pointer
     @return    If successful, a NODEBTP object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEBTP_DATA *  nodeBTP_Copy(
        NODEBTP_DATA    *this
    )
    {
        NODEBTP_DATA    *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeBTP_New( );
        if (pOther) {
            eRc = nodeBTP_Assign(this, pOther);
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

    void            nodeBTP_Dealloc(
        OBJ_ID          objId
    )
    {
        NODEBTP_DATA    *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODEBTP_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         nodeBTP_Disable(
        NODEBTP_DATA    *this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeBTP_Validate(this) ) {
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

    ERESULT         nodeBTP_Enable(
        NODEBTP_DATA	*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeBTP_Validate(this) ) {
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
    
    NODEENUM_DATA * nodeBTP_Enum(
        NODEBTP_DATA    *this
    )
    {
        NODEENUM_DATA   *pEnum = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        pEnum = nodeEnum_New();
        if (pEnum) {
            eRc =   blocks_ForEach(
                                   (BLOCKS_DATA *)this,
                                   (void *)nodeBTP_EnumExit,
                                   this,
                                   pEnum
                                   );
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pEnum);
                pEnum = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pEnum;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeBTP_FindNode(
        NODEBTP_DATA    *this,
        NODE_DATA       *pNode
    )
    {
        NODEBTP_RECORD  *pWork;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
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
        
        pWork = this->pRoot;
        while (pWork) {
            eRc = node_Compare(pNode, pWork->node.pData);
            if (ERESULT_SUCCESS_EQUAL == eRc) {
                return pWork->node.pData;
            }
            else if (ERESULT_SUCCESS_LESS_THAN == eRc) {
                if (pWork->node.pLink[RBT_LEFT])
                    pWork = (NODEBTP_RECORD *)pWork->node.pLink[RBT_LEFT];
                else
                    break;
            }
            else if (ERESULT_SUCCESS_GREATER_THAN == eRc) {
                if (pWork->node.pLink[RBT_RIGHT])
                    pWork = (NODEBTP_RECORD *)pWork->node.pLink[RBT_RIGHT];
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
    //                          I n i t
    //---------------------------------------------------------------

    NODEBTP_DATA *  nodeBTP_Init(
        NODEBTP_DATA    *this
    )
    {
        uint32_t        cbSize = sizeof(NODEBTP_DATA);
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;

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
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODEBTP);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_NODEBTP);      // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeBTP_Vtbl);
        
        eRc = blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(NODEBTP_RECORD));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        blocks_setDeleteExit(
                        (BLOCKS_DATA *)this,
                        (void *)nodeBTP_DeleteExit,
                        this,
                        NULL
        );
        
        rbt_Init(&this->tree, (void *)nodeBTP_NodeCmp);
        this->tree.pNodeAlloc = (void *)blocks_RecordNew;
        this->tree.pNodeFree = (void *)blocks_RecordFree;
        this->tree.pObjAllocFree = this;
        this->tree.dataSize = sizeof(NODEBTP_RECORD) - sizeof(RBT_NODE);

    #ifdef NDEBUG
    #else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "nodeBTP::sizeof(NODEBTP_DATA) = %lu\n", sizeof(NODEBTP_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODEBTP_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         nodeBTP_IsEnabled(
        NODEBTP_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
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
    
    ERESULT         nodeBTP_Nodes(
        NODEBTP_DATA    *this,
        NODEARRAY_DATA  **ppNodes
    )
    {
        NODEARRAY_DATA  *pNodes = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == ppNodes ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNodes = nodeArray_New();
        if (pNodes) {
            eRc =   blocks_ForEach(
                                (BLOCKS_DATA *)this,
                                (void *)nodeBTP_NodesExit,
                                this,
                                pNodes
                    );
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pNodes);
                pNodes = OBJ_NIL;
            }
            else
                nodeArray_SortAscending(pNodes);
        }

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        if (ppNodes) {
            *ppNodes = pNodes;
        }
        return eRc;
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
        void        *pMethod = nodeBTP_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "nodeBTP", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          nodeBTP_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEBTP_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NODEBTP_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)nodeBTP_Class();
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
                            return nodeBTP_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return nodeBTP_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return nodeBTP_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return nodeBTP_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == nodeBTP_ToDebugString)
                    return "ToDebugString";
                if (pData == nodeBTP_ToJSON)
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
    
    ERESULT         nodeBTP_RightDegenerate(
        NODEBTP_DATA    *this
    )
    {
#ifdef XYZZY
        NODELNKP_NODE   *pNode;
        NODELNKP_NODE   *pParent;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef XYZZY
        /* Alter the tree to be right degenerate (ie a singly-
         * linked list using only the right child ptr).
         */
        pNode = nodeBTP_getRoot(this);
        while( pNode ) {
            pParent = nodeLnkP_getParent(pNode);
            if( nodeLnkP_getLeftLink(pNode) ) {
                nodeBTP_RotateRight(this, pNode);
                if( pParent ) {
                    if( nodeLnkP_getLeftLink(pParent) )
                        pNode = nodeLnkP_getLeftLink(pParent);
                    else
                        pNode = nodeLnkP_getRightLink(pParent);
                }
                else
                    pNode = nodeBTP_getRoot(this);
            }
            else
                pNode = nodeLnkP_getRightLink(pNode);
        }
#endif
        
        // Return to caller.
        //return ERESULT_SUCCESS;
        return ERESULT_NOT_IMPLEMENTED;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     nodeBTP_ToJSON(
        NODEBTP_DATA      *this
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
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
        ASTR_DATA      *pDesc = nodeBTP_ToDebugString(this,4);
     @endcode 
     @param     this    NODEBTP object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeBTP_ToDebugString(
        NODEBTP_DATA    *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        LISTDL_DATA     *pList = NULL;
        BLOCKS_NODE     *pEntry = NULL;
        NODEBTP_RECORD  *pRecord;
        NODE_DATA       *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeBTP_Validate(this) ) {
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
                    nodeBTP_getSize(this)
            );

        pList = blocks_getList((BLOCKS_DATA *)this);
        pEntry = listdl_Head(pList);
        while (pEntry) {
            NODEBTP_RECORD      *pRecord = (NODEBTP_RECORD *)pEntry->data;
            RBT_NODE            *pNode = &pRecord->node;
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            }
            eRc = AStr_AppendPrint(
                                   pStr,
                                   "%p  L=%p R=%p %s   D=%p\n",
                                   pNode,
                                   pNode->pLink[RBT_LEFT],
                                   pNode->pLink[RBT_RIGHT],
                                   pNode->color ? "red" : "black",
                                   pNode->pData
                                   );
            if (pNode->pData) {
                pWrkStr = node_ToDebugString(pNode->pData, indent+6);
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
            pEntry = listdl_Next(pList, pEntry);
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
    bool            nodeBTP_Validate(
        NODEBTP_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_NODEBTP) )
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


        if( !(obj_getSize(this) >= sizeof(NODEBTP_DATA)) ) {
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
    
    ERESULT         nodeBTP_VisitNodesInRecurse(
        NODEBTP_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc;
        NODEBTP_VISIT   parms;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeBTP_Validate(this)) {
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
                        (void *)nodeBTP_VisitExit,
                        this,
                        &parms
                );
        
        return eRc;
    }
    
    
    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    
    ERESULT         nodeBTP_VisitNodesPostRecurse(
        NODEBTP_DATA    *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc;
        NODEBTP_VISIT   parms;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeBTP_Validate(this)) {
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
                        (void *)nodeBTP_VisitExit,
                        this,
                        &parms
                );

        return eRc;
    }
    
    
    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    
    ERESULT         nodeBTP_VisitNodesPreRecurse(
        NODEBTP_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc;
        NODEBTP_VISIT   parms;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeBTP_Validate(this)) {
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
                        (void *)nodeBTP_VisitExit,
                        this,
                        &parms
                );

        return eRc;
    }
    
    
    

    
#ifdef	__cplusplus
}
#endif


