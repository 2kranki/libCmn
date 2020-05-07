// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   szBT.c
 *	Generated 02/25/2020 10:00:27
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
#include        <szBT_internal.h>
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

    ERESULT         szBT_DeleteExit(
        SZBT_DATA       *this,
        SZBT_RECORD     *pRecord,
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        if (this->pDeleteExit) {
            eRc =   this->pDeleteExit(
                                    this->pDeleteObj,
                                    pRecord->node.pKey,
                                    pRecord->node.pValue
                    );
        }

        return eRc;
    }



    //---------------------------------------------------------------
    //                  E n u m  E x i t
    //---------------------------------------------------------------

    ERESULT         szBT_EnumExit(
        SZBT_DATA       *this,
        SZBT_RECORD     *pRecord,
        NODEENUM_DATA   *pEnum
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        //NODE_DATA       *pNode = pRecord->node.pKey;

#ifdef IF_NEEDED
        if (pNode && pEnum) {
            eRc = NodeEnum_AppendObj(pEnum, (NODE_DATA *)pNode);
        }
#endif

        return eRc;
    }



    //---------------------------------------------------------------
    //                  F i n d  E x i t
    //---------------------------------------------------------------

    ERESULT         szBT_FindExit(
        NODEBT_DATA     *this,
        SZBT_RECORD     *pRecord,
        SZBT_FIND       *pFind
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

    SZBT_RECORD *   szBT_FindUnique(
        NODEBT_DATA     *this,
        uint32_t        unique
    )
    {
        LISTDL_DATA     *pList;
        BLOCKS_NODE     *pEntry = NULL;
        SZBT_RECORD     *pRecord = NULL;

        pList = Blocks_getList((BLOCKS_DATA *)this);
        if (pList) {
            pEntry = listdl_Head(pList);
            while (pEntry) {
                pRecord = (SZBT_RECORD *)pEntry->data;
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

    SZBT_RECORD *   szBT_LeftMostChild(
        SZBT_DATA       *this,
        SZBT_RECORD     *pRecord
    )
    {

        // Do initialization.
        if (NULL == pRecord) {
            return NULL;
        }

        if (pRecord) {
            while (pRecord->node.pLink[RBT_LEFT]) {
                pRecord = (SZBT_RECORD *)pRecord->node.pLink[RBT_LEFT];
            }
        }

        // Return to caller.
        return pRecord;
    }



    //---------------------------------------------------------------
    //                  N o d e  C o m p a r e
    //---------------------------------------------------------------

    int             szBT_NodeCmp(
        void            *pKeyA,
        void            *pKeyB
    )
    {
        int             iRc;

        iRc = strcmp((char *)pKeyA, (char *)pKeyB);
        return iRc;
    }



    //---------------------------------------------------------------
    //                  N o d e s  E x i t
    //---------------------------------------------------------------

    ERESULT         szBT_NodesExit(
        NODEBT_DATA     *this,
        SZBT_RECORD     *pRecord,
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

    ERESULT         szBT_VisitExit(
        NODEBT_DATA     *this,
        SZBT_RECORD     *pRecord,
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
    ERESULT         szBT_VisitNodeInRecurse(
        SZBT_DATA       *this,
        SZBT_RECORD     *pRecord,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        SZBT_RECORD     *pWork;

        if (pRecord) {
            pWork = (SZBT_RECORD *)pRecord->node.pLink[RBT_LEFT];
            if (pWork) {
                eRc = szBT_VisitNodeInRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            eRc = pScan(pObj, pRecord->node.pKey, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
            pWork = (SZBT_RECORD *)pRecord->node.pLink[RBT_RIGHT];
            if (pWork) {
                eRc = szBT_VisitNodeInRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
        }

        return eRc;
    }


    /*! Visit all the nodes from the given node and below in the Tree
     using a Post-order traversal.
     */
    ERESULT         szBT_VisitNodePostRecurse(
        SZBT_DATA       *this,
        SZBT_RECORD     *pRecord,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        SZBT_RECORD     *pWork;

        if (pRecord) {
            pWork = (SZBT_RECORD *)pRecord->node.pLink[RBT_LEFT];
            if (pWork) {
                eRc = szBT_VisitNodePostRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            pWork = (SZBT_RECORD *)pRecord->node.pLink[RBT_RIGHT];
            if (pWork) {
                eRc = szBT_VisitNodePostRecurse(this, pWork, pScan, pObj, pArg3);
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
    ERESULT         szBT_VisitNodePreRecurse(
        SZBT_DATA       *this,
        SZBT_RECORD     *pRecord,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        SZBT_RECORD     *pWork;

        if (pRecord) {
            eRc = pScan(pObj, pRecord->node.pKey, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
            pWork = (SZBT_RECORD *)pRecord->node.pLink[RBT_LEFT];
            if (pWork) {
                eRc = szBT_VisitNodePreRecurse(this, pWork, pScan, pObj, pArg3);
                if (ERESULT_FAILED(eRc))
                    return eRc;
            }
            pWork = (SZBT_RECORD *)pRecord->node.pLink[RBT_RIGHT];
            if (pWork) {
                eRc = szBT_VisitNodePreRecurse(this, pWork, pScan, pObj, pArg3);
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

    SZBT_DATA *     szBT_Alloc (
        void
    )
    {
        SZBT_DATA       *this;
        uint32_t        cbSize = sizeof(SZBT_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SZBT_DATA *     szBT_New (
        void
    )
    {
        SZBT_DATA       *this;
        
        this = szBT_Alloc( );
        if (this) {
            this = szBT_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                    D e l e t e  E x i t
    //---------------------------------------------------------------

    bool            szBT_setDeleteExit(
        SZBT_DATA       *this,
        ERESULT         (*pDeleteExit)(OBJ_ID, void *pKey, void *pData),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pDeleteExit = pDeleteExit;
        this->pDeleteObj  = pObj;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        szBT_getPriority (
        SZBT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            szBT_setPriority (
        SZBT_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
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
    
    uint32_t        szBT_getSize (
        SZBT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return (uint32_t)this->tree.size;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  szBT_getSuperVtbl (
        SZBT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T r e e
    //---------------------------------------------------------------

    RBT_TREE *      szBT_getTree (
        SZBT_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return &this->tree;
    }




    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------

    ERESULT         szBT_AddA (
        SZBT_DATA       *this,
        const
        char            *pNameA,            // UTF-8
        void            *pData
    )
    {
        void            *pFound;
        SZBT_RECORD     *pRecord = NULL;
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        int             iRc;
        uint32_t        unique;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pFound = szBT_FindA(this, pNameA);
        if (pFound) {
            return ERESULT_DATA_ALREADY_EXISTS;
         }

        pRecord = Blocks_RecordNew((BLOCKS_DATA *)this, &unique);
        if (NULL == pRecord) {
            return ERESULT_OUT_OF_MEMORY;
        }
        pRecord->node.pKey = (void *)pNameA;
        pRecord->unique = this->unique++;
        pRecord->node.color = RBT_RED;
        pRecord->node.pValue = pData;

        iRc = rbt_InsertNode(&this->tree, (RBT_NODE *)pRecord);
        if (iRc) {
            eRc = ERESULT_SUCCESS;
        }
        else
            eRc = ERESULT_DATA_ALREADY_EXISTS;

        // Return to caller.
        return eRc;
    }


    ERESULT         szBT_AddUpdateA (
        SZBT_DATA       *this,
        const
        char            *pNameA,            // UTF-8
        void            *pData
    )
    {
        void            *pFound;
        SZBT_RECORD     *pRecord = NULL;
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        int             iRc;
        uint32_t        unique;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pFound = szBT_FindA(this, pNameA);
        if (pFound) {
            eRc = szBT_DeleteA(this, pNameA);
        }

        pRecord = Blocks_RecordNew((BLOCKS_DATA *)this, &unique);
        if (NULL == pRecord) {
            return ERESULT_OUT_OF_MEMORY;
        }
        pRecord->node.pKey = (void *)pNameA;
        pRecord->unique = this->unique++;
        pRecord->node.color = RBT_RED;
        pRecord->node.pValue = pData;

        iRc = rbt_InsertNode(&this->tree, (RBT_NODE *)pRecord);
        if (iRc) {
            eRc = ERESULT_SUCCESS;
        }
        else
            eRc = ERESULT_DATA_ALREADY_EXISTS;

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
        ERESULT eRc = szBT_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SZBT object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         szBT_Assign (
        SZBT_DATA		*this,
        SZBT_DATA       *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!szBT_Validate(pOther)) {
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
    ERESULT         szBT_Compare (
        SZBT_DATA     *this,
        SZBT_DATA     *pOther
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
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!szBT_Validate(pOther)) {
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
        szBT      *pCopy = szBT_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SZBT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SZBT_DATA *     szBT_Copy (
        SZBT_DATA       *this
    )
    {
        SZBT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SZBT_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = szBT_New( );
        if (pOther) {
            eRc = szBT_Assign(this, pOther);
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

    void            szBT_Dealloc (
        OBJ_ID          objId
    )
    {
        SZBT_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SZBT_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        // Not needed since all the data is stored in Blocks object
        // whisch will free it.
        //szBT_DeleteAll(this);

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
        szBT      *pDeepCopy = szBT_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SZBT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SZBT_DATA *     szBT_DeepyCopy (
        SZBT_DATA       *this
    )
    {
        SZBT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = szBT_New( );
        if (pOther) {
            eRc = szBT_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------

    ERESULT         szBT_DeleteA (
        SZBT_DATA       *this,
        const
        char            *pNameA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        iRc = rbt_Delete(&this->tree, (void *)pNameA);
        if (iRc)
            eRc = ERESULT_SUCCESS;
        else
            eRc = ERESULT_DATA_NOT_FOUND;

        // Return to caller.
        return eRc;
    }


        ERESULT         szBT_DeleteAll (
            SZBT_DATA       *this
        )
        {
            ERESULT         eRc = ERESULT_SUCCESS;

            // Do initialization.
    #ifdef NDEBUG
    #else
            if (!szBT_Validate(this)) {
                DEBUG_BREAK();
                return ERESULT_INVALID_OBJECT;
            }
    #endif

            rbt_DeleteAll(&this->tree);

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
    ERESULT         szBT_Disable (
        SZBT_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
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
    ERESULT         szBT_Enable (
        SZBT_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
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

    void *          szBT_FindA (
        SZBT_DATA       *this,
        const
        char            *pNameA             // UTF-8
    )
    {
        SZBT_RECORD     record = {0};
        SZBT_RECORD     *pFound = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !szBT_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if(NULL == pNameA) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        record.node.pKey = (void *)pNameA;

        pFound = (SZBT_RECORD *)rbt_FindNode(&this->tree, (RBT_NODE *)&record);

        // Return to caller.
        return pFound ? pFound->node.pValue : NULL;
    }



    //---------------------------------------------------------------
    //                          F o r  E a c h
    //---------------------------------------------------------------

    ERESULT         szBT_ForEach(
        SZBT_DATA       *this,
        P_ERESULT_EXIT4 pScan,
        OBJ_ID          pObj,               // Used as first parameter of scan method
        //                                  // second parameter is key
        //                                  // third parameter is data
        void            *pArg4              // Used as fourth parameter of scan method
    )
    {
        LISTDL_DATA     *pList = NULL;
        BLOCKS_NODE     *pEntry = NULL;
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !szBT_Validate(this) ) {
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
            SZBT_RECORD         *pRecord = (SZBT_RECORD *)pEntry->data;

            eRc =   pScan(pObj, pRecord->node.pKey, pRecord->node.pValue, pArg4);
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

    SZBT_DATA *   szBT_Init (
        SZBT_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SZBT_DATA);
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
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&szBT_Vtbl);
        
        this->unique = 1;
        // Set up Blocks to hold tree data.
        eRc = Blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(SZBT_RECORD));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        Blocks_setDeleteExit(
                        (BLOCKS_DATA *)this,
                        (void *)szBT_DeleteExit,
                        this,               // 1st parameter
                        NULL                // 3rd parameter
        );

        // Set up Red-Black tree to use Blocks to hold its data.
        rbt_Init(
                 &this->tree,
                 (void *)szBT_NodeCmp,
                 (sizeof(SZBT_RECORD) - sizeof(RBT_NODE)),
                 (void *)Blocks_RecordNew,
                 (void *)Blocks_RecordFree,
                 this
        );
        this->tree.pNodeAlloc = (void *)Blocks_RecordNew;
        this->tree.pNodeFree = (void *)Blocks_RecordFree;
        this->tree.pObjAllocFree = this;
        this->tree.dataSize = sizeof(SZBT_RECORD) - sizeof(RBT_NODE);

#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "szBT::sizeof(SZBT_DATA) = %lu\n", 
                sizeof(SZBT_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SZBT_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         szBT_IsEnabled (
        SZBT_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = szBT_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "szBT", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          szBT_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SZBT_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SZBT_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)szBT_Class();
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
                            return szBT_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return szBT_Enable;
                        }
                        break;

#ifdef  SZBT_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return szBT_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return szBT_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return szBT_ToDebugString;
                        }
#ifdef  SZBT_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return szBT_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == szBT_ToDebugString)
                    return "ToDebugString";
#ifdef  SZBT_JSON_SUPPORT
                if (pData == szBT_ToJson)
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
        ASTR_DATA      *pDesc = szBT_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     szBT_ToDebugString (
        SZBT_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!szBT_Validate(this)) {
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
                    szBT_getSize(this),
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
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            szBT_Validate (
        SZBT_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SZBT))
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


        if (!(obj_getSize(this) >= sizeof(SZBT_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                     V e r i f y  T r e e
    //---------------------------------------------------------------

    ERESULT         szBT_VerifyTree(
        SZBT_DATA       *this
    )
    {
        ERESULT         eRc;
        int             iRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !szBT_Validate(this) ) {
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




    
#ifdef	__cplusplus
}
#endif


