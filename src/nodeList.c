// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeList.c
 *	Generated 11/23/2018 17:15:11
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
#include        <nodeList_internal.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ERESULT         nodeList_EnumExit(
        NODELIST_DATA   *this,
        NODE_DATA       *pNode,
        NODEENUM_DATA   *pEnum
    )
    {
        ERESULT         eRc;
        
        eRc = nodeEnum_Append(pEnum, pNode);
        
        return eRc;
    }

    
    
    static
    ERESULT         nodeList_NodesExit(
                                       NODELIST_DATA   *this,
                                       NODE_DATA       *pNode,
                                       NODEARRAY_DATA  *pArray
                                       )
    {
        ERESULT         eRc;
        
        eRc = nodeArray_AppendNode(pArray, pNode, NULL);
        
        return eRc;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODELIST_DATA *     nodeList_Alloc(
        void
    )
    {
        NODELIST_DATA       *this;
        uint32_t        cbSize = sizeof(NODELIST_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODELIST_DATA *     nodeList_New(
        void
    )
    {
        NODELIST_DATA       *this;
        
        this = nodeList_Alloc( );
        if (this) {
            this = nodeList_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                       O r d e r e d
    //---------------------------------------------------------------
    
    bool            nodeList_getOrdered(
        NODELIST_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return objList_getOrdered((OBJLIST_DATA *)this);
    }
 
    
    bool            nodeList_setOrdered(
        NODELIST_DATA   *this,
        bool            fValue
    )
    {
        bool            fRc = false;
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
       
        fRc = objList_setOrdered((OBJLIST_DATA *)this, fValue);
        
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        nodeList_getPriority(
        NODELIST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            nodeList_setPriority(
        NODELIST_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
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
    
    uint32_t        nodeList_getSize(
        NODELIST_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return objList_getSize((OBJLIST_DATA *)this);
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * nodeList_getStr(
        NODELIST_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        nodeList_setStr(
        NODELIST_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
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
    
    OBJ_IUNKNOWN *  nodeList_getSuperVtbl(
        NODELIST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
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
    
    ERESULT         nodeList_Add2Head(
        NODELIST_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = objList_Add2Head((OBJLIST_DATA *)this, pNode);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         nodeList_Add2HeadA(
        NODELIST_DATA   *this,
        int32_t         cls,
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNode = node_NewWithUTF8AndClass(cls, pName, pData);
        if (pNode) {
            eRc = objList_Add2Head((OBJLIST_DATA *)this, pNode);
            if (ERESULT_FAILED(eRc))
                ;
            else {
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         nodeList_Add2Tail(
        NODELIST_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((OBJ_NIL == pNode) || obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = objList_Add2Tail((OBJLIST_DATA *)this, pNode);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         nodeList_Add2TailA(
        NODELIST_DATA   *this,
        int32_t         cls,
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNode = node_NewWithUTF8AndClass(cls, pName, pData);
        if (pNode) {
            eRc = objList_Add2Tail((OBJLIST_DATA *)this, pNode);
            if (ERESULT_FAILED(eRc))
                ;
            else {
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
        }
        
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
        ERESULT eRc = nodeList_Assign(this,pOther);
     @endcode 
     @param     this    NODELIST object pointer
     @param     pOther  a pointer to another NODELIST object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         nodeList_Assign(
        NODELIST_DATA		*this,
        NODELIST_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeList_Validate(pOther) ) {
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
    ERESULT         nodeList_Compare(
        NODELIST_DATA     *this,
        NODELIST_DATA     *pOther
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
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeList_Validate(pOther) ) {
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
        nodeList      *pCopy = nodeList_Copy(this);
     @endcode 
     @param     this    NODELIST object pointer
     @return    If successful, a NODELIST object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODELIST_DATA *     nodeList_Copy(
        NODELIST_DATA       *this
    )
    {
        NODELIST_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeList_New( );
        if (pOther) {
            eRc = nodeList_Assign(this, pOther);
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

    void            nodeList_Dealloc(
        OBJ_ID          objId
    )
    {
        NODELIST_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODELIST_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        nodeList_setStr(this, OBJ_NIL);

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
    
    ERESULT         nodeList_DeleteA(
        NODELIST_DATA   *this,
        int32_t         cls,
        const
        char            *pName
    )
    {
        ERESULT         eRc = ERESULT_NOT_IMPLEMENTED;
        //OBJLIST_RECORD  *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
       
#ifdef XYZZY
        pEntry = nodeList_FindNodeA(this, cls, pName);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        obj_Release(pEntry->pNode);
        pEntry->pNode = OBJ_NIL;
        listdl_Delete(&this->list, pEntry);
        listdl_Add2Tail(&this->freeList, pEntry);
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         nodeList_DeleteHead(
        NODELIST_DATA   *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = objList_DeleteHead((OBJLIST_DATA *)this);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         nodeList_DeleteTail(
        NODELIST_DATA    *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = objList_DeleteTail((OBJLIST_DATA *)this);
        
        // Return to caller.
        return eRc;
    }

    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         nodeList_Disable(
        NODELIST_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeList_Validate(this) ) {
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

    ERESULT         nodeList_Enable(
        NODELIST_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeList_Validate(this) ) {
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
    //                        E n u m
    //---------------------------------------------------------------
    
    NODEENUM_DATA * nodeList_Enum(
        NODELIST_DATA   *this
    )
    {
        ERESULT         eRc;
        NODEENUM_DATA   *pEnum = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        eRc = objList_ForEach((OBJLIST_DATA *)this, (void *)nodeList_EnumExit, this, pEnum);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pEnum);
            pEnum = OBJ_NIL;
        }
        
        // Return to caller.
        return pEnum;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeList_FindA(
        NODELIST_DATA   *this,
        int32_t         cls,
        const
        char            *pName
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        OBJLIST_RECORD  *pRecord;
        LISTDL_DATA *   pList;
        ERESULT         eRc;

        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        pList = objList_getList((OBJLIST_DATA *)this);
        if (NULL == pList)
            return OBJ_NIL;
        if (listdl_Count(pList) < 1) {
            return OBJ_NIL;
        }
        
        pRecord = listdl_Head(pList);
        while ( pRecord ) {
            eRc = node_CompareA(pRecord->pObject, cls, pName);
            if (ERESULT_SUCCESS_EQUAL == eRc) {
                pNode = pRecord->pObject;
                break;
            }
            pRecord = listdl_Next(pList, pRecord);
        }

        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                        F o r  E a c h
    //---------------------------------------------------------------
    
    ERESULT         nodeList_ForEach(
        NODELIST_DATA   *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = objList_ForEach((OBJLIST_DATA *)this, pScan, pObj, pArg3);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeList_Index(
        NODELIST_DATA   *this,
        uint32_t        index
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pNode = objList_Index((OBJLIST_DATA *)this, index);
        
        // Return to caller.
        return pNode;
    }
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODELIST_DATA *   nodeList_Init(
        NODELIST_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODELIST_DATA);
        
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

        this = (OBJ_ID)objList_Init((OBJLIST_DATA *)this);   // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODELIST);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_NODELIST);     // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeList_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "nodeList::sizeof(NODELIST_DATA) = %lu\n", sizeof(NODELIST_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODELIST_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         nodeList_IsEnabled(
        NODELIST_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
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
    
    NODEARRAY_DATA * nodeList_Nodes(
        NODELIST_DATA    *this
    )
    {
        NODEARRAY_DATA  *pKeys;
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        
        pKeys = nodeArray_New();
        if (pKeys) {
            eRc =   objList_ForEach(
                                    (OBJLIST_DATA *)this,
                                    (void *)nodeList_NodesExit,
                                    this,
                                    pKeys
                    );
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pKeys);
                pKeys = OBJ_NIL;
            }
            else {
                nodeArray_SortAscending(pKeys);
            }
        }
        
        // Return to caller.
        return pKeys;
    }
    
    
    
    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------
    
    ERESULT         nodeList_SortAscending(
        NODELIST_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        bool            fRc;
        LISTDL_DATA *   pList;

        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pList = objList_getList((OBJLIST_DATA *)this);
        if (NULL == pList)
            return ERESULT_GENERAL_FAILURE;
        if (listdl_Count(pList) < 2) {
            return ERESULT_SUCCESS;
        }
        
        fRc = listdl_Sort(pList, (void *)node_Compare);
        if (fRc)
            eRc = ERESULT_SUCCESS;
        
        // Return to caller.
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
        void        *pMethod = nodeList_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "nodeList", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          nodeList_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODELIST_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODELIST_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)nodeList_Class();
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
                            return nodeList_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return nodeList_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return nodeList_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return nodeList_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == nodeList_ToDebugString)
                    return "ToDebugString";
                if (pData == nodeList_ToJSON)
                    return "ToJSON";
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
        ASTR_DATA      *pDesc = nodeList_ToDebugString(this,4);
     @endcode 
     @param     this    NODELIST object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeList_ToDebugString(
        NODELIST_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
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
                    nodeList_getSize(this)
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
    bool            nodeList_Validate(
        NODELIST_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_NODELIST) )
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


        if( !(obj_getSize(this) >= sizeof(NODELIST_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


