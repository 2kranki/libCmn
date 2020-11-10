// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeList.c
 *	Generated 01/10/2020 13:58:08
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
#include        <NodeList_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ERESULT         NodeList_EnumExit(
        NODELIST_DATA   *this,
        NODE_DATA       *pNode,
        NODEENUM_DATA   *pEnum
    )
    {
        ERESULT         eRc;

        eRc = NodeEnum_AppendObj(pEnum, pNode);

        return eRc;
    }



    static
    ERESULT         NodeList_NodesExit(
                                       NODELIST_DATA   *this,
                                       NODE_DATA       *pNode,
                                       NODEARRAY_DATA  *pArray
                                       )
    {
        ERESULT         eRc;

        eRc = NodeArray_AppendNode(pArray, pNode, NULL);

        return eRc;
    }





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODELIST_DATA *     NodeList_Alloc (
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



    NODELIST_DATA *     NodeList_New (
        void
    )
    {
        NODELIST_DATA       *this;
        
        this = NodeList_Alloc( );
        if (this) {
            this = NodeList_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                    O b j L i s t
    //---------------------------------------------------------------

    OBJLIST_DATA *  NodeList_getObjList (
        NODELIST_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeList_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (OBJLIST_DATA *)this;
    }



    //---------------------------------------------------------------
    //                       O r d e r e d
    //---------------------------------------------------------------

    bool            NodeList_getOrdered (
        NODELIST_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return ObjList_getOrdered((OBJLIST_DATA *)this);
    }


    bool            NodeList_setOrdered (
        NODELIST_DATA   *this,
        bool            fValue
    )
    {
        bool            fRc = false;
#ifdef NDEBUG
#else
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        fRc = ObjList_setOrdered((OBJLIST_DATA *)this, fValue);

        return fRc;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        NodeList_getPriority (
        NODELIST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeList_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NodeList_setPriority (
        NODELIST_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NodeList_Validate(this)) {
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
    
    uint32_t        NodeList_getSize (
        NODELIST_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeList_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return ObjList_getSize((OBJLIST_DATA *)this);
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * NodeList_getStr (
        NODELIST_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeList_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        NodeList_setStr (
        NODELIST_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeList_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_STR_OWNED
        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
#endif
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodeList_getSuperVtbl (
        NODELIST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeList_Validate(this)) {
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

    ERESULT         NodeList_Add2Head (
        NODELIST_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = ObjList_Add2Head((OBJLIST_DATA *)this, pNode);

        // Return to caller.
        return eRc;
    }


    ERESULT         NodeList_Add2HeadA (
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
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pNode = Node_NewWithUTF8AndClass(cls, pName, pData);
        if (pNode) {
            eRc = ObjList_Add2Head((OBJLIST_DATA *)this, pNode);
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


    ERESULT         NodeList_Add2Tail (
        NODELIST_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((OBJ_NIL == pNode) || obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = ObjList_Add2Tail((OBJLIST_DATA *)this, pNode);

        // Return to caller.
        return eRc;
    }


    ERESULT         NodeList_Add2TailA (
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
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pNode = Node_NewWithUTF8AndClass(cls, pName, pData);
        if (pNode) {
            eRc = ObjList_Add2Tail((OBJLIST_DATA *)this, pNode);
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
        ERESULT eRc = NodeList_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NODELIST object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeList_Assign (
        NODELIST_DATA		*this,
        NODELIST_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeList_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeList_Validate(pOther)) {
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
    ERESULT         NodeList_Compare (
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
        if (!NodeList_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeList_Validate(pOther)) {
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
        NodeList      *pCopy = NodeList_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODELIST object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODELIST_DATA *     NodeList_Copy (
        NODELIST_DATA       *this
    )
    {
        NODELIST_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeList_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeList_New( );
        if (pOther) {
            eRc = NodeList_Assign(this, pOther);
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

    void            NodeList_Dealloc (
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
        if (!NodeList_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODELIST_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NodeList_setStr(this, OBJ_NIL);

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

    ERESULT         NodeList_DeleteA (
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
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef XYZZY
        pEntry = NodeList_FindNodeA(this, cls, pName);
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


    ERESULT         NodeList_DeleteHead (
        NODELIST_DATA   *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = ObjList_DeleteHead((OBJLIST_DATA *)this);

        // Return to caller.
        return eRc;
    }


    ERESULT         NodeList_DeleteTail (
        NODELIST_DATA    *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = ObjList_DeleteTail((OBJLIST_DATA *)this);

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
    ERESULT         NodeList_Disable (
        NODELIST_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeList_Validate(this)) {
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
    ERESULT         NodeList_Enable (
        NODELIST_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeList_Validate(this)) {
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

    NODEENUM_DATA * NodeList_Enum(
        NODELIST_DATA   *this
    )
    {
        ERESULT         eRc;
        NODEENUM_DATA   *pEnum = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        eRc = ObjList_ForEach((OBJLIST_DATA *)this, (void *)NodeList_EnumExit, this, pEnum);
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

    NODE_DATA *     NodeList_FindA(
        NODELIST_DATA   *this,
        int32_t         cls,
        const
        char            *pName
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        OBJLIST_RECORD  *pRecord;
        LISTDL_DATA *   pList;
        int             iRc;


        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeList_Validate(this) ) {
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

        pList = ObjList_getList((OBJLIST_DATA *)this);
        if (NULL == pList)
            return OBJ_NIL;
        if (listdl_Count(pList) < 1) {
            return OBJ_NIL;
        }

        pRecord = listdl_Head(pList);
        while ( pRecord ) {
            iRc = Node_CompareA(pRecord->pObject, cls, pName);
            if (0 == iRc) {
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

    ERESULT         NodeList_ForEach(
        NODELIST_DATA   *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = ObjList_ForEach((OBJLIST_DATA *)this, pScan, pObj, pArg3);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------

    NODE_DATA *     NodeList_Index(
        NODELIST_DATA   *this,
        uint32_t        index
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pNode = ObjList_Index((OBJLIST_DATA *)this, index);

        // Return to caller.
        return pNode;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODELIST_DATA *   NodeList_Init (
        NODELIST_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODELIST_DATA);
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

        this = (OBJ_ID)ObjList_Init((OBJLIST_DATA *)this);      // Needed for Inheritance
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeList_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

    #ifdef NDEBUG
    #else
        if (!NodeList_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "NodeList::sizeof(NODELIST_DATA) = %lu\n", sizeof(NODELIST_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODELIST_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeList_IsEnabled (
        NODELIST_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeList_Validate(this)) {
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

    NODEARRAY_DATA * NodeList_Nodes (
        NODELIST_DATA    *this
    )
    {
        NODEARRAY_DATA  *pKeys;
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        pKeys = NodeArray_New();
        if (pKeys) {
            eRc =   ObjList_ForEach(
                                    (OBJLIST_DATA *)this,
                                    (void *)NodeList_NodesExit,
                                    this,
                                    pKeys
                    );
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pKeys);
                pKeys = OBJ_NIL;
            }
            else {
                NodeArray_SortAscending(pKeys);
            }
        }

        // Return to caller.
        return pKeys;
    }



    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------

    ERESULT         NodeList_SortAscending (
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
        if( !NodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pList = ObjList_getList((OBJLIST_DATA *)this);
        if (NULL == pList)
            return ERESULT_GENERAL_FAILURE;
        if (listdl_Count(pList) < 2) {
            return ERESULT_SUCCESS;
        }

        fRc = listdl_Sort(pList, (void *)Node_Compare);
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
        void        *pMethod = NodeList_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeList", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeList_QueryInfo (
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
        if (!NodeList_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODELIST_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeList_Class();
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
                            return NodeList_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeList_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeList_ToDebugString;
                        }
#ifdef  NODELIST_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return NodeList_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeList_ToDebugString)
                    return "ToDebugString";
#ifdef  NODELIST_JSON_SUPPORT
                if (pData == NodeList_ToJson)
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
        ASTR_DATA      *pDesc = NodeList_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeList_ToDebugString (
        NODELIST_DATA      *this,
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
        if (!NodeList_Validate(this)) {
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
                    NodeList_getSize(this),
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
    bool            NodeList_Validate (
        NODELIST_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODELIST))
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


        if (!(obj_getSize(this) >= sizeof(NODELIST_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


