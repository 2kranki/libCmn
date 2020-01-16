// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeArray.c
 *	Generated 01/10/2020 13:58:02
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
#include        <NodeArray_internal.h>
#include        <NodeEnum_internal.h>
#include        <I32Array.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            NodeArray_task_body (
        void            *pData
    )
    {
        //NODEARRAY_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEARRAY_DATA *     NodeArray_Alloc (
        void
    )
    {
        NODEARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(NODEARRAY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEARRAY_DATA *     NodeArray_New (
        void
    )
    {
        NODEARRAY_DATA       *this;
        
        this = NodeArray_Alloc( );
        if (this) {
            this = NodeArray_Init(this);
        } 
        return this;
    }



    //---------------------------------------------------------------
    //                        M a t c h  S e t
    //---------------------------------------------------------------

    NODE_DATA *     NodeArray_MatchSet(
        int             (*pCompare)(NODE_DATA *,NODE_DATA *),
        NODE_DATA       *pNode,
        NODE_DATA       **ppNodeSet     // NULL-terminated Set of Nodes
    )
    {
        int             cmp;
        NODE_DATA       *pFound = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (NULL == ppNodeSet) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        while (*ppNodeSet) {
            cmp = pCompare(pNode, *ppNodeSet);
            if(0 == cmp) {
                pFound = *ppNodeSet;
                break;
            }
            ++ppNodeSet;
        }

        // Return to caller.
        return pFound;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------

    OBJARRAY_DATA *  NodeArray_getArray (
        NODEARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }


    bool            NodeArray_setArray (
        NODEARRAY_DATA  *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
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
    //                      C o m p a r e
    //---------------------------------------------------------------

    bool            NodeArray_setCompare (
        NODEARRAY_DATA  *this,
        int             (*pCompare)(NODE_DATA *,NODE_DATA *)
    )
    {
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pCompare = pCompare;

        return true;
    }



    //---------------------------------------------------------------
    //                     o b j A r r a y
    //---------------------------------------------------------------

    OBJARRAY_DATA *  NodeArray_getObjArray (
        NODEARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }



    //---------------------------------------------------------------
    //                        O t h e r
    //---------------------------------------------------------------

    OBJ_ID          NodeArray_getOther (
        NODEARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pOther;
    }


    bool            NodeArray_setOther (
        NODEARRAY_DATA  *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
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
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        NodeArray_getSize (
        NODEARRAY_DATA       *this
    )
    {
        uint32_t        i = 0;

#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->pArray) {
            i = ObjArray_getSize(this->pArray);
        }
        return i;

    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodeArray_getSuperVtbl (
        NODEARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
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
    //                       A p p e n d
    //---------------------------------------------------------------

    ERESULT         NodeArray_Append(
        NODEARRAY_DATA    *this,
        NODEARRAY_DATA    *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        max;
        NODE_DATA       *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !NodeArray_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        max = NodeArray_getSize(pOther);

        for (i=0; i<max; ++i) {
            pNode = NodeArray_Get(pOther, i+1);
            if (pNode) {
                eRc = NodeArray_AppendNode(this, pNode, NULL);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Return to caller.
        return eRc;
    }


    ERESULT         NodeArray_AppendNode(
        NODEARRAY_DATA    *this,
        NODE_DATA       *pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if((pObject == OBJ_NIL) || (!obj_IsKindOf(pObject, OBJ_IDENT_NODE))) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (OBJ_NIL == this->pArray) {
            this->pArray = ObjArray_New();
            if (OBJ_NIL == this->pArray) {
                DEBUG_BREAK();
                return ERESULT_MEMORY_EXCEEDED;
            }
        }

        eRc = ObjArray_AppendObj(this->pArray, pObject, pIndex);

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
        ERESULT eRc = NodeArray_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NODEARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeArray_Assign (
        NODEARRAY_DATA		*this,
        NODEARRAY_DATA     *pOther
    )
    {
        ERESULT     eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeArray_Validate(pOther)) {
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
        eRc = ObjArray_Assign(this->pArray, pOther->pArray);

        // Copy other data from this object to other.
        pOther->pCompare = this->pCompare;

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
    ERESULT         NodeArray_Compare (
        NODEARRAY_DATA     *this,
        NODEARRAY_DATA     *pOther
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
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeArray_Validate(pOther)) {
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
        NodeArray      *pCopy = NodeArray_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODEARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEARRAY_DATA *     NodeArray_Copy (
        NODEARRAY_DATA       *this
    )
    {
        NODEARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeArray_New( );
        if (pOther) {
            eRc = NodeArray_Assign(this, pOther);
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
    //                          C o u n t
    //---------------------------------------------------------------

    uint32_t        NodeArray_Count (
        NODEARRAY_DATA  *this
    )
    {
        uint32_t        i = 0;

#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->pArray) {
            i = ObjArray_getSize(this->pArray);
        }
        return i;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            NodeArray_Dealloc (
        OBJ_ID          objId
    )
    {
        NODEARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODEARRAY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pArray) {
#ifdef NDEBUG
#else
            if (obj_getRetainCount(this->pArray) > 1) {
                DEBUG_BREAK();
            }
#endif
            obj_Release(this->pArray);
            this->pArray = OBJ_NIL;
        }
        if (this->pOther) {
            obj_Release(this->pOther);
            this->pOther = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D e e p  C o p y
    //---------------------------------------------------------------

    NODEARRAY_DATA * NodeArray_DeepCopy (
        NODEARRAY_DATA    *this
    )
    {
        NODEARRAY_DATA  *pOther;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pOther = NodeArray_New();
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }

        pOther->pArray = ObjArray_DeepCopy(this->pArray);
        if (pOther->pArray) {
            pOther->pCompare = this->pCompare;
            return pOther;
        }

        // Return to caller.
        obj_Release(pOther);
        return OBJ_NIL;
    }



    //---------------------------------------------------------------
    //                        D e l e t e
    //---------------------------------------------------------------

    NODE_DATA *     NodeArray_Delete (
        NODEARRAY_DATA    *this,
        uint32_t        index
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_Delete(this->pArray, index);
        }

        // Return to caller.
        return pNode;
    }


    NODE_DATA *     NodeArray_DeleteFirst (
        NODEARRAY_DATA    *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_DeleteFirst(this->pArray);
        }

        // Return to caller.
        return pNode;
    }


    NODE_DATA *     NodeArray_DeleteLast (
        NODEARRAY_DATA    *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_DeleteLast(this->pArray);
        }

        // Return to caller.
        return pNode;
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
    ERESULT         NodeArray_Disable (
        NODEARRAY_DATA        *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeArray_Validate(this)) {
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
    ERESULT         NodeArray_Enable (
        NODEARRAY_DATA        *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeArray_Validate(this)) {
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

    NODEENUM_DATA * NodeArray_Enum (
        NODEARRAY_DATA  *this
    )
    {
        ERESULT         eRc;
        NODEENUM_DATA   *pEnum = OBJ_NIL;
        uint32_t        size;
        uint32_t        index;
        NODE_DATA       *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pEnum = NodeEnum_New();
            size = ObjArray_getSize(this->pArray);
            for (index = 0; index < size; ++index) {
                pNode = ObjArray_Get(this->pArray, index+1);
                eRc = NodeEnum_AppendObj(pEnum, pNode);
            }
        }

        // Return to caller.
        return pEnum;
    }



    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    NODE_DATA *     NodeArray_Find (
        NODEARRAY_DATA  *this,
        NODE_DATA       *pNode
    )
    {
        NODE_DATA       *pWork = OBJ_NIL;
        uint32_t        size;
        uint32_t        i;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( OBJ_NIL == pNode ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif

        size = NodeArray_getSize(this);
        for (i=0; i<size; ++i) {
            pWork = (NODE_DATA *)ObjArray_Get(this->pArray, i+1);
            if (pWork) {
                eRc = Node_Compare(pNode, pWork);
                if( eRc == ERESULT_SUCCESS_EQUAL ) {
                    return pWork;
                }
            }
        }

        // Return to caller.
        return OBJ_NIL;
    }


    NODE_DATA *     NodeArray_FindA (
        NODEARRAY_DATA    *this,
        int32_t         cls,
        const
        char            *pNameA
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        NODE_DATA       *pFound = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( OBJ_NIL == pNameA ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif

        pNode = Node_NewWithUTF8AndClass(cls, pNameA, OBJ_NIL);
        pFound = NodeArray_Find(this, pNode);
        obj_Release(pNode);
        pNode = OBJ_NIL;

        // Return to caller.
        return pFound;
    }



    //---------------------------------------------------------------
    //                     F o r  E a c h
    //---------------------------------------------------------------

    ERESULT         NodeArray_ForEach (
        NODEARRAY_DATA  *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        index;
        uint32_t        size;
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pArray && pScan) {
            size = ObjArray_getSize(this->pArray);
            for (index = 0; index < size; ++index) {
                pNode = ObjArray_Get(this->pArray, (index + 1));
                eRc = pScan(pObj, pNode, pArg3);
                if (ERESULT_FAILED(eRc))
                    break;
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                        G e t
    //---------------------------------------------------------------

    NODE_DATA *     NodeArray_Get (
        NODEARRAY_DATA    *this,
        uint32_t        index       // Relative to 1
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_Get(this->pArray, index);
        }

        // Return to caller.
        return pNode;
    }


    NODE_DATA *     NodeArray_GetFirst (
        NODEARRAY_DATA    *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_GetFirst(this->pArray);
        }

        // Return to caller.
        return pNode;
    }


    NODE_DATA *     NodeArray_GetLast (
        NODEARRAY_DATA    *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_GetLast(this->pArray);
        }

        // Return to caller.
        return pNode;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEARRAY_DATA *   NodeArray_Init (
        NODEARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODEARRAY_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODEARRAY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeArray_Vtbl);
        
        this->pCompare = &Node_Compare;
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
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "NodeArray::sizeof(NODEARRAY_DATA) = %lu\n", sizeof(NODEARRAY_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODEARRAY_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------

    ERESULT         NodeArray_InsertAfter(
        NODEARRAY_DATA    *this,
        uint32_t        index,
        NODE_DATA       *pObject
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if((pObject == OBJ_NIL) || (!obj_IsKindOf(pObject, OBJ_IDENT_NODE))) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (OBJ_NIL == this->pArray) {
            this->pArray = ObjArray_New();
            if (OBJ_NIL == this->pArray) {
                DEBUG_BREAK();
                return ERESULT_MEMORY_EXCEEDED;
            }
        }

        eRc = ObjArray_InsertObj(this->pArray, index, pObject);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeArray_IsEnabled (
        NODEARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
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
    //                          P u t
    //---------------------------------------------------------------

    ERESULT         NodeArray_Put(
        NODEARRAY_DATA  *this,
        uint32_t        index,
        NODE_DATA       *pObject
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pObject == OBJ_NIL)
            ;
        else if (!obj_IsKindOf(pObject, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (OBJ_NIL == this->pArray) {
            this->pArray = ObjArray_New();
            if (OBJ_NIL == this->pArray) {
                DEBUG_BREAK();
                return ERESULT_MEMORY_EXCEEDED;
            }
        }

        eRc = ObjArray_Put(this->pArray, index, pObject);

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
        void        *pMethod = NodeArray_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeArray", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEARRAY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEARRAY_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeArray_Class();
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
                            return NodeArray_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeArray_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeArray_ToDebugString;
                        }
#ifdef  NODEARRAY_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return NodeArray_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeArray_ToDebugString)
                    return "ToDebugString";
#ifdef  NODEARRAY_JSON_SUPPORT
                if (pData == NodeArray_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------

    ERESULT         NodeArray_SortAscending(
        NODEARRAY_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;

        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pArray) {
            eRc = ObjArray_SortAscending(this->pArray, (OBJ_COMPARE)this->pCompare);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                    T o  C l a s s  A r r a y
    //---------------------------------------------------------------

    I32ARRAY_DATA * NodeArray_ToClassArray(
        NODEARRAY_DATA  *this
    )
    {
        int             j;
        I32ARRAY_DATA   *pArray = OBJ_NIL;
        NODE_DATA       *pNode;
        int32_t         chr;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

        pArray = I32Array_New( );

        if (pArray && this->pArray) {
            for (j=0; j<ObjArray_getSize(this->pArray); ++j) {
                pNode = ObjArray_Get(this->pArray, j+1);
                if (pNode) {
                    chr = Node_getClass(pNode);
                }
                else {
                    chr = 0;
                }
                I32Array_AppendData(pArray, chr);
            }
        }


        return pArray;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeArray_ToDebugString (
        NODEARRAY_DATA      *this,
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
        if (!NodeArray_Validate(this)) {
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
                    NodeArray_getSize(this),
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
    
    
    ASTR_DATA *     NodeArray_ToString(
        NODEARRAY_DATA  *this
    )
    {
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrk;
        NODE_DATA       *pNode;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

        pStr = AStr_New();
        AStr_AppendA(pStr, "Array[\n");

        if (this->pArray) {
            for (j=0; j<ObjArray_getSize(this->pArray); ++j) {
                pNode = ObjArray_Get(this->pArray, j+1);
                pWrk = Node_ToString(pNode);
                if (pWrk) {
                    AStr_AppendA(pStr, "  ");
                    AStr_Append(pStr, pWrk);
                    obj_Release(pWrk);
                }
            }
        }

        AStr_AppendA(pStr, "]\n\n");

        return pStr;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            NodeArray_Validate (
        NODEARRAY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODEARRAY))
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


        if (!(obj_getSize(this) >= sizeof(NODEARRAY_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                   V i s i t  A s c e n d i n g
    //---------------------------------------------------------------

    ERESULT         NodeArray_VisitAscending(
        NODEARRAY_DATA    *this,
        ERESULT         (pVisitor)(
                                   OBJ_ID,             // Object supplied below
                                   NODE_DATA *         // Current Node
                        ),
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
;
        }
        BREAK_NULL(this->pArray);
#endif

        iMax = ObjArray_getSize(this->pArray);
        for (i=0; i<iMax; ++i) {
            pNode = ObjArray_Get(this->pArray, (i+1));
            eRc = pVisitor(pObject, pNode);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
        }

        // Return to caller.
        return eRc;
    }




    
#ifdef	__cplusplus
}
#endif


