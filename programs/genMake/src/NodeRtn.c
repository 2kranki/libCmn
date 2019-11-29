// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeRtn.c
 *	Generated 11/03/2019 08:11:37
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
#include        <NodeRtn_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            NodeRtn_task_body (
        void            *pData
    )
    {
        //NODERTN_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODERTN_DATA *     NodeRtn_Alloc (
        void
    )
    {
        NODERTN_DATA       *this;
        uint32_t        cbSize = sizeof(NODERTN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODERTN_DATA *     NodeRtn_New (
        void
    )
    {
        NODERTN_DATA       *this;
        
        this = NodeRtn_Alloc( );
        if (this) {
            this = NodeRtn_Init(this);
        } 
        return this;
    }



    ERESULT_DATA *  NodeRtn_Parse (
        NODE_DATA       *pNode,
        NODERTN_DATA    **ppBase
    )
    {
        ERESULT_DATA    *pErr = OBJ_NIL;
        NODEHASH_DATA   *pHash;
        NODE_DATA       *pHashItem;
        NODERTN_DATA    *pRtn;
        ASTRC_DATA      *pName;
        ASTRC_DATA      *pTestName;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER, "Error: Missing Input Node!");
            return pErr;
        }
        if (OBJ_NIL == ppBase) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER,
                                   "Error: Missing Base Node Pointer!");
            return pErr;
        }
    #endif
        pRtn = NodeRtn_New();
        if (OBJ_NIL == pRtn) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
            return pErr;
        }
        *ppBase = OBJ_NIL;

        pHash = jsonIn_CheckNodeForHash(pNode);
        if (pHash) {
            // Ok, we have a hash, so there might a lot to parse here.

            // Scan off the base parameters.
            pErr = NodeBase_Parse(pNode, (NODEBASE_DATA **)&pRtn);
            if (pErr) {
                DEBUG_BREAK();
                obj_Release(pRtn);
                return pErr;
            }
            pName = NodeRtn_getName(pRtn);
            if (OBJ_NIL == pName) {
                DEBUG_BREAK();
                obj_Release(pRtn);
                return (eResult_NewStrA(ERESULT_INVALID_PARAMETER,
                                       "Error: Routine is missing Name!"));
            }

            // Scan off the test stuff if present.
            pHashItem = nodeHash_FindA(pHash, 0, "test");
            if (pHashItem) {
                FALSE_DATA      *pFalse;
                pFalse = jsonIn_CheckNodeDataForFalse(pHashItem);
                if (pFalse)
                    ;
                else {
                    pHashItem = node_getData(pHashItem);
                    // NodeTest::Parse will provide the NodeTest.
                    pErr = NodeTest_Parse(pHashItem, &pRtn->pTest);
                    if (pErr) {
                        DEBUG_BREAK();
                        obj_Release(pRtn);
                        return pErr;
                    }
                    pTestName = NodeTest_getName(pRtn->pTest);
                    if (OBJ_NIL == pTestName) {
                        pTestName = AStrC_AppendA(pName, "_test");
                        NodeTest_setName(pRtn->pTest, pTestName);
                        obj_Release(pTestName);
                        pTestName = OBJ_NIL;
                    }
                }
            }
            *ppBase = pRtn;
        }

        // Return to caller.
        return pErr;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  A r c h i t e c t u r e s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeRtn_getArches (
        NODERTN_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getArches(NodeRtn_getNodeBase(this));
    }


    bool            NodeRtn_setArches (
        NODERTN_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setArches(NodeRtn_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        D e p s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeRtn_getDeps (
        NODERTN_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getDeps(NodeRtn_getNodeBase(this));
    }


    bool            NodeRtn_setDeps (
        NODERTN_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setDeps(NodeRtn_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        N a m e
    //---------------------------------------------------------------

    ASTRC_DATA *    NodeRtn_getName (
        NODERTN_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getName(NodeRtn_getNodeBase(this));
    }


    bool            NodeRtn_setName (
        NODERTN_DATA    *this,
        ASTRC_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setName(NodeRtn_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                           N o d e
    //---------------------------------------------------------------

    NODE_DATA *     NodeRtn_getNode (
        NODERTN_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (NODE_DATA *)this;
    }


    //---------------------------------------------------------------
    //                       N o d e  B a s e
    //---------------------------------------------------------------

    NODEBASE_DATA *     NodeRtn_getNodeBase (
        NODERTN_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (NODEBASE_DATA *)this;
    }


    //---------------------------------------------------------------
    //                        O S
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeRtn_getOSs (
        NODERTN_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getOSs(NodeRtn_getNodeBase(this));
    }


    bool            NodeRtn_setOSs (
        NODERTN_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setOSs(NodeRtn_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        NodeRtn_getPriority (
        NODERTN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NodeRtn_setPriority (
        NODERTN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          S r c s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeRtn_getSrcs (
        NODERTN_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getSrcs(NodeRtn_getNodeBase(this));
    }


    bool            NodeRtn_setSrcs (
        NODERTN_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setSrcs(NodeRtn_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        NodeRtn_getSize (
        NODERTN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodeRtn_getSuperVtbl (
        NODERTN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T e s t
    //---------------------------------------------------------------
    
    NODETEST_DATA * NodeRtn_getTest (
        NODERTN_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pTest;
    }
    
    
    bool            NodeRtn_setTest (
        NODERTN_DATA    *this,
        NODETEST_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_TEST_OWNED
        obj_Retain(pValue);
        if (this->pTest) {
            obj_Release(this->pTest);
        }
#endif
        this->pTest = pValue;
        
        return true;
    }
            
            
            


    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A p p e n d
    //---------------------------------------------------------------

    ERESULT_DATA *  NodeRtn_AppendDeps (
        NODERTN_DATA	*this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT_DATA    *pErr;
        ASTRC_DATA      *pStrC;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
    #endif

        pStrC = AStrC_NewFromAStr(pStr);
        if (OBJ_NIL == pStrC) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
        }
        pErr = NodeBase_AppendDeps(NodeRtn_getNodeBase(this), pStrC);
        obj_Release(pStrC);
        pStrC = OBJ_NIL;

        // Return to caller.
        return pErr;
    }


    ERESULT_DATA *  NodeRtn_AppendSrcs (
        NODERTN_DATA	*this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT_DATA    *pErr;
        ASTRC_DATA      *pStrC;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
    #endif

        pStrC = AStrC_NewFromAStr(pStr);
        if (OBJ_NIL == pStrC) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
        }
        pErr = NodeBase_AppendSrcs(NodeRtn_getNodeBase(this), pStrC);
        obj_Release(pStrC);
        pStrC = OBJ_NIL;

        // Return to caller.
        return pErr;
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
        ERESULT eRc = NodeRtn_Assign(this,pOther);
     @endcode 
     @param     this    NODERTN object pointer
     @param     pOther  a pointer to another NODERTN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeRtn_Assign (
        NODERTN_DATA	*this,
        NODERTN_DATA    *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeRtn_Validate(pOther)) {
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
    ERESULT         NodeRtn_Compare (
        NODERTN_DATA     *this,
        NODERTN_DATA     *pOther
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
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeRtn_Validate(pOther)) {
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
        NodeRtn      *pCopy = NodeRtn_Copy(this);
     @endcode 
     @param     this    NODERTN object pointer
     @return    If successful, a NODERTN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODERTN_DATA *     NodeRtn_Copy (
        NODERTN_DATA       *this
    )
    {
        NODERTN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeRtn_New( );
        if (pOther) {
            eRc = NodeRtn_Assign(this, pOther);
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

    void            NodeRtn_Dealloc (
        OBJ_ID          objId
    )
    {
        NODERTN_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODERTN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NodeRtn_setTest(this, OBJ_NIL);

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
    ERESULT         NodeRtn_Disable (
        NODERTN_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeRtn_Validate(this)) {
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
    ERESULT         NodeRtn_Enable (
        NODERTN_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeRtn_Validate(this)) {
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

    NODERTN_DATA *   NodeRtn_Init (
        NODERTN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODERTN_DATA);
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

        this = (OBJ_ID)NodeBase_Init((NODEBASE_DATA *)this);    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODERTN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeRtn_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "NodeRtn::sizeof(NODERTN_DATA) = %lu\n", sizeof(NODERTN_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODERTN_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeRtn_IsEnabled (
        NODERTN_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
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
        void        *pMethod = NodeRtn_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeRtn", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeRtn_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODERTN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODERTN_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeRtn_Class();
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
                            return NodeRtn_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeRtn_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeRtn_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return NodeRtn_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeRtn_ToDebugString)
                    return "ToDebugString";
                if (pData == NodeRtn_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     NodeRtn_ToJSON (
        NODERTN_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{\"objectType\":\"%s\"",
                        pInfo->pClassName
                    );
            
            AStr_AppendA(pStr, "}\n");
        }
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeRtn_ToDebugString(this,4);
     @endcode 
     @param     this    NODERTN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeRtn_ToDebugString (
        NODERTN_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeRtn_Validate(this)) {
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
                    NodeRtn_getSize(this)
            );

        pWrkStr =   NodeBase_ToDebugString(NodeRtn_getNodeBase(this), indent+3);
        AStr_Append(pStr, pWrkStr);
        obj_Release(pWrkStr);

        if (this->pTest) {
            if (((OBJ_DATA *)(this->pTest))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pTest))->pVtbl->pToDebugString(
                                                    this->pTest,
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
    bool            NodeRtn_Validate (
        NODERTN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODERTN))
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


        if (!(obj_getSize(this) >= sizeof(NODERTN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


