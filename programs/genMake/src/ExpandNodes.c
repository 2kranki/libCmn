// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ExpandNodes.c
 *	Generated 11/10/2019 17:43:09
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
#include        <ExpandNodes_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            ExpandNodes_task_body (
        void            *pData
    )
    {
        //EXPANDNODES_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    EXPANDNODES_DATA *     ExpandNodes_Alloc (
        void
    )
    {
        EXPANDNODES_DATA       *this;
        uint32_t        cbSize = sizeof(EXPANDNODES_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    EXPANDNODES_DATA *     ExpandNodes_New (
        void
    )
    {
        EXPANDNODES_DATA       *this;
        
        this = ExpandNodes_Alloc( );
        if (this) {
            this = ExpandNodes_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                     D e p e n d e n c i e s
    //---------------------------------------------------------------
    
    ASTRCARRAY_DATA *   ExpandNodes_getDeps (
        EXPANDNODES_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDeps;
    }
    
    
    bool                ExpandNodes_setDeps (
        EXPANDNODES_DATA    *this,
        ASTRCARRAY_DATA     *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_DEPS_OWNED
        obj_Retain(pValue);
        if (this->pDeps) {
            obj_Release(this->pDeps);
        }
#endif
        this->pDeps = pValue;
        
        return true;
    }
        
            
            
    //---------------------------------------------------------------
    //                     D i c t i o n a r y
    //---------------------------------------------------------------
    
    DICT_DATA *         ExpandNodes_getDict (
        EXPANDNODES_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDict;
    }
    
    
    bool                ExpandNodes_setDict (
        EXPANDNODES_DATA    *this,
        DICT_DATA           *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_DICT_OWNED
        obj_Retain(pValue);
        if (this->pDict) {
            obj_Release(this->pDict);
        }
#endif
        this->pDict = pValue;
        
        return true;
    }
    
        
        
    //---------------------------------------------------------------
    //                   L i b r a r y  O b j e c t
    //---------------------------------------------------------------
    
    NODELIB_DATA *      ExpandNodes_getLib (
        EXPANDNODES_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pLib;
    }
    
    
    bool                ExpandNodes_setLib (
        EXPANDNODES_DATA    *this,
        NODELIB_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_LIB_OWNED
        obj_Retain(pValue);
        if (this->pLib) {
            obj_Release(this->pLib);
        }
#endif
        this->pLib = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P r o g r a m  O b j e c t
    //---------------------------------------------------------------
    
    NODEPGM_DATA *      ExpandNodes_getPgm (
        EXPANDNODES_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pPgm;
    }
    
    
    bool                ExpandNodes_setPgm (
        EXPANDNODES_DATA    *this,
        NODEPGM_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_PGM_OWNED
        obj_Retain(pValue);
        if (this->pPgm) {
            obj_Release(this->pPgm);
        }
#endif
        this->pPgm = pValue;
        
        return true;
    }
    
        
        
    //---------------------------------------------------------------
    //                  R o u t i n e  A r r a y
    //---------------------------------------------------------------
    
    NODEARRAY_DATA *    ExpandNodes_getRtns (
        EXPANDNODES_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pRtns;
    }
    
    
    bool                ExpandNodes_setRtns (
        EXPANDNODES_DATA    *this,
        NODEARRAY_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_RTNS_OWNED
        obj_Retain(pValue);
        if (this->pRtns) {
            obj_Release(this->pRtns);
        }
#endif
        this->pRtns = pValue;
        
        return true;
    }
        
            
            
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        ExpandNodes_getSize (
        EXPANDNODES_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  ExpandNodes_getSuperVtbl (
        EXPANDNODES_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                  T e s t s  A r r a y
    //---------------------------------------------------------------
    
    NODEARRAY_DATA *    ExpandNodes_getTests (
        EXPANDNODES_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pTests;
    }
    
    
    bool                ExpandNodes_setTests (
        EXPANDNODES_DATA    *this,
        NODEARRAY_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_TESTS_OWNED
        obj_Retain(pValue);
        if (this->pTests) {
            obj_Release(this->pTests);
        }
#endif
        this->pTests = pValue;
        
        return true;
    }
            
                
                


    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A p p e n d
    //---------------------------------------------------------------

    /*!
     Accumulate the Routine objects in the Routine Array.
     @param     this    object pointer
     @return    if successful, OBJ_NIL.  Otherwise, an ERESULT_DATA *
                error code which must be released.
     */
    ERESULT_DATA *      ExpandNodes_AppendRtn (
        EXPANDNODES_DATA    *this,
        NODERTNA_DATA       *pRtn
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if (OBJ_NIL == pRtn) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
        if (!obj_IsKindOf(pRtn, OBJ_IDENT_NODERTNA)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
#endif
        
        eRc = NodeArray_AppendNode(this->pRtns, NodeRtnA_getNode(pRtn), NULL);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return  eResult_NewStrA(
                                   ERESULT_GENERAL_FAILURE,
                                   "Routine array append failed!"
                    );
        }

        // Return to caller.
        return OBJ_NIL;
    }


    /*!
     Accumulate the Test objects in the Test Array.
     @param     this    object pointer
     @return    if successful, OBJ_NIL.  Otherwise, an ERESULT_DATA *
                error code which must be released.
     */
    ERESULT_DATA *      ExpandNodes_AppendTest (
        EXPANDNODES_DATA    *this,
        NODETSTA_DATA       *pTst
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if (OBJ_NIL == pTst) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
        if (!obj_IsKindOf(pTst, OBJ_IDENT_NODETSTA)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
#endif
        
        eRc = NodeArray_AppendNode(this->pTests, NodeTstA_getNode(pTst), NULL);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return  eResult_NewStrA(
                                   ERESULT_GENERAL_FAILURE,
                                   "Test array append failed!"
                    );
        }

        // Return to caller.
        return OBJ_NIL;
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
        ERESULT eRc = ExpandNodes_Assign(this,pOther);
     @endcode 
     @param     this    EXPANDNODES object pointer
     @param     pOther  a pointer to another EXPANDNODES object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ExpandNodes_Assign (
        EXPANDNODES_DATA		*this,
        EXPANDNODES_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ExpandNodes_Validate(pOther)) {
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
    //                  C h e c k  N o d e s
    //---------------------------------------------------------------

    ERESULT_DATA *      ExpandNodes_CheckNodes (
        EXPANDNODES_DATA    *this,
        const
        char                *pArch,
        const
        char                *pOS
    )
    {
        uint32_t            i;
        uint32_t            iMax;
        NODERTNA_DATA       *pRtnA;
        NODETSTA_DATA       *pTstA;
        //ERESULT_DATA        *pErr;
        ERESULT             eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
#endif
        
        iMax = NodeArray_getSize(this->pRtns);
        for (i=0; i<iMax; i++) {
            pRtnA = (NODERTNA_DATA *)NodeArray_Get(this->pRtns, i+1);
            if (OBJ_NIL == pRtnA) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_OBJECT,
                                       "Routine Array missing element");
            }
            if (!obj_IsKindOf(pRtnA, OBJ_IDENT_NODERTNA)) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_OBJECT,
                                       "Routine Array missing element");
            }
            eRc = NodeRtnA_CheckContraints(pRtnA, pArch, pOS);
        }

        iMax = NodeArray_getSize(this->pTests);
        for (i=0; i<iMax; i++) {
            pTstA = (NODETSTA_DATA *)NodeArray_Get(this->pTests, i+1);
            if (OBJ_NIL == pTstA) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_OBJECT,
                                       "Routine Array missing element");
            }
            if (!obj_IsKindOf(pTstA, OBJ_IDENT_NODETSTA)) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_OBJECT,
                                       "Routine Array missing element");
            }
            eRc = NodeTstA_CheckContraints(pTstA, pArch, pOS);
        }

        // Return to caller.
        return OBJ_NIL;
    }



    //---------------------------------------------------------------
    //                      C l e a n
    //---------------------------------------------------------------

    /*!
     Remove all stored data.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ExpandNodes_Clean (
        EXPANDNODES_DATA        *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        ExpandNodes_setLib(this, OBJ_NIL);
        ExpandNodes_setPgm(this, OBJ_NIL);
        ExpandNodes_setRtns(this, OBJ_NIL);
        ExpandNodes_setTests(this, OBJ_NIL);

        this->pRtns = NodeArray_New( );
        if (OBJ_NIL == this->pRtns) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        this->pTests = NodeArray_New( );
        if (OBJ_NIL == this->pTests) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
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
    ERESULT         ExpandNodes_Compare (
        EXPANDNODES_DATA     *this,
        EXPANDNODES_DATA     *pOther
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
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ExpandNodes_Validate(pOther)) {
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
        ExpandNodes      *pCopy = ExpandNodes_Copy(this);
     @endcode 
     @param     this    EXPANDNODES object pointer
     @return    If successful, a EXPANDNODES object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    EXPANDNODES_DATA *     ExpandNodes_Copy (
        EXPANDNODES_DATA       *this
    )
    {
        EXPANDNODES_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ExpandNodes_New( );
        if (pOther) {
            eRc = ExpandNodes_Assign(this, pOther);
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

    void            ExpandNodes_Dealloc (
        OBJ_ID          objId
    )
    {
        EXPANDNODES_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((EXPANDNODES_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        ExpandNodes_setDict(this, OBJ_NIL);
        ExpandNodes_setLib(this, OBJ_NIL);
        ExpandNodes_setPgm(this, OBJ_NIL);
        ExpandNodes_setRtns(this, OBJ_NIL);
        ExpandNodes_setTests(this, OBJ_NIL);
        ExpandNodes_setDeps(this, OBJ_NIL);

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
    ERESULT         ExpandNodes_Disable (
        EXPANDNODES_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ExpandNodes_Validate(this)) {
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
    ERESULT         ExpandNodes_Enable (
        EXPANDNODES_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
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
    //                  E x p a n d  O b j e c t
    //---------------------------------------------------------------

    /*!
     Expand an object into several nodes, some optional.
     @param     this    object pointer
     @param     pObj    Input Object Node
     @return    if successful, OBJ_NIL.  Otherwise, an ERESULT_DATA *
                error code which must be released.
     */
    ERESULT_DATA *      ExpandNodes_ExpandObj (
        EXPANDNODES_DATA    *this,
        NODEOBJ_DATA        *pObj
    )
    {
        ERESULT_DATA        *pErr = OBJ_NIL;
        ERESULT             eRc;
        NODERTN_DATA        *pRtn  = OBJ_NIL;
        NODERTNA_DATA       *pRtnA = OBJ_NIL;
        NODETSTA_DATA       *pTstA = OBJ_NIL;
        NODETEST_DATA       *pTest = OBJ_NIL;
        ASTRC_DATA          *pName;
        ASTRC_DATA          *pNameWrk;
        ASTRC_DATA          *pExt = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if (OBJ_NIL == pObj) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
        if (!obj_IsKindOf(pObj, OBJ_IDENT_NODEOBJ)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
#endif
        
        pErr = NodeBase_MergeDeps(NodeObj_getNodeBase(pObj), this->pDeps);
        pName = NodeObj_getName(pObj);

        pRtnA = NodeRtnA_New();
        if (OBJ_NIL == pRtnA) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
        }
        eRc = NodeBase_Assign(NodeObj_getNodeBase(pObj), NodeRtnA_getNodeBase(pRtnA));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_GENERAL_FAILURE, "Object assign failed!");
        }
        NodeRtnA_setName(pRtnA, pName);
        pErr = ExpandNodes_AppendRtn(this, pRtnA);
        obj_Release(pRtnA);
        pRtnA = OBJ_NIL;
        if (pErr) {
            DEBUG_BREAK();
            return  pErr;
        }
        
        pRtnA = NodeRtnA_New();
        if (OBJ_NIL == pRtnA) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
        }
        eRc = NodeBase_Assign(NodeObj_getNodeBase(pObj), NodeRtnA_getNodeBase(pRtnA));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_GENERAL_FAILURE, "Object assign failed!");
        }
        pNameWrk = AStrC_AppendA(pName, "_object");
        NodeRtnA_setName(pRtnA, pNameWrk);
        obj_Release(pNameWrk);
        pNameWrk = OBJ_NIL;
        pExt = NodeRtnA_getExt(pRtnA);
        pErr = ExpandNodes_AppendRtn(this, pRtnA);
        obj_Release(pRtnA);
        pRtnA = OBJ_NIL;
        if (pErr) {
            DEBUG_BREAK();
            return  pErr;
        }

        pRtn = NodeObj_getJson(pObj);
        if (pRtn) {
            pErr = NodeBase_MergeDeps(NodeRtn_getNodeBase(pRtn), NodeObj_getDeps(pObj));
            pErr = ExpandNodes_ExpandRtn(this, pRtn);
            if (pErr) {
                return pErr;
            }
        }
        
        pTest = NodeObj_getTest(pObj);
        if (pTest) {
            pErr = NodeBase_MergeDeps(NodeTest_getNodeBase(pTest), NodeObj_getDeps(pObj));
            pNameWrk = NodeTest_getName(pTest);
            pTstA = NodeTstA_New();
            if (OBJ_NIL == pTstA) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
            }
            eRc =   NodeBase_Assign(
                                  NodeTest_getNodeBase(pTest),
                                  NodeTstA_getNodeBase(pTstA)
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_GENERAL_FAILURE, "Test assign failed!");
            }
            if (pNameWrk) {
                NodeTstA_setName(pTstA, pNameWrk);
            } else {
                pNameWrk = AStrC_AppendA(pName, "_test");
                NodeTstA_setName(pTstA, pNameWrk);
            }
            pErr = ExpandNodes_AppendTest(this, pTstA);
            obj_Release(pTstA);
            pTstA = OBJ_NIL;
            if (pErr) {
                DEBUG_BREAK();
                return  pErr;
            }
        }

        // Return to caller.
        return OBJ_NIL;
    }



    //---------------------------------------------------------------
    //                  E x p a n d  O b j e c t s
    //---------------------------------------------------------------

    ERESULT_DATA *      ExpandNodes_ExpandObjs (
        EXPANDNODES_DATA    *this,
        NODEARRAY_DATA      *pObjs
    )
    {
        uint32_t            i;
        uint32_t            iMax;
        NODEOBJ_DATA        *pObj;
        ERESULT_DATA        *pErr;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if (OBJ_NIL == pObjs) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
    #endif
        
    iMax = NodeArray_getSize(pObjs);
    for (i=0; i<iMax; i++) {
        pObj = (NODEOBJ_DATA *)NodeArray_Get(pObjs, i+1);
        if (OBJ_NIL == pObj) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT,
                                   "Routine Array missing element");
        }
        if (!obj_IsKindOf(pObj, OBJ_IDENT_NODEOBJ)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT,
                                   "Routine Array missing element");
        }
        pErr = ExpandNodes_ExpandObj(this, pObj);
        if (pErr) {
            DEBUG_BREAK();
            return pErr;
        }
    }
        
        // Return to caller.
        return OBJ_NIL;
    }



    //---------------------------------------------------------------
    //                  E x p a n d  R o u t i n e
    //---------------------------------------------------------------

    ERESULT_DATA *      ExpandNodes_ExpandRtn (
        EXPANDNODES_DATA    *this,
        NODERTN_DATA        *pRtn
    )
    {
        ERESULT_DATA        *pErr;
        ERESULT             eRc;
        NODERTNA_DATA       *pRtnA = OBJ_NIL;
        NODETSTA_DATA       *pTstA = OBJ_NIL;
        NODETEST_DATA       *pTest = OBJ_NIL;
        ASTRC_DATA          *pName;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if (OBJ_NIL == pRtn) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
        if (!obj_IsKindOf(pRtn, OBJ_IDENT_NODERTN)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
    #endif
        pName = NodeRtn_getName(pRtn);
        pErr = NodeBase_MergeDeps(NodeRtn_getNodeBase(pRtn), this->pDeps);

        pRtnA = NodeRtnA_New();
        if (OBJ_NIL == pRtnA) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
        }
        eRc = NodeBase_Assign(NodeRtn_getNodeBase(pRtn), NodeRtnA_getNodeBase(pRtnA));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_GENERAL_FAILURE, "Routine assign failed!");
        }
        NodeRtnA_setName(pRtnA, pName);
        pErr = ExpandNodes_AppendRtn(this, pRtnA);
        obj_Release(pRtnA);
        pRtnA = OBJ_NIL;
        if (pErr) {
            DEBUG_BREAK();
            return  pErr;
        }

        pTest = NodeRtn_getTest(pRtn);
        if (pTest) {
            pTstA = NodeTstA_New();
            if (OBJ_NIL == pTstA) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
            }
            pErr = NodeBase_MergeDeps(NodeTest_getNodeBase(pTest), NodeRtn_getDeps(pRtn));
            eRc =   NodeBase_Assign(
                                  NodeTest_getNodeBase(pTest),
                                  NodeTstA_getNodeBase(pTstA)
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_GENERAL_FAILURE, "Test assign failed!");
            }
            pErr = ExpandNodes_AppendTest(this, pTstA);
            obj_Release(pTstA);
            pTstA = OBJ_NIL;
            if (pErr) {
                DEBUG_BREAK();
                return  pErr;
            }
        }

        // Return to caller.
        return OBJ_NIL;
    }



    //---------------------------------------------------------------
    //                  E x p a n d  R o u t i n e s
    //---------------------------------------------------------------

    /*!
     Expand the Routine Nodes to RtnA and TstA nodes as needed.
     @param     this    object pointer
     @param     pRtns   Input Routine Node Array
     @return    if successful, OBJ_NIL.  Otherwise, an ERESULT_DATA *
                error code which must be released.
     */
    ERESULT_DATA *      ExpandNodes_ExpandRtns (
        EXPANDNODES_DATA    *this,
        NODEARRAY_DATA      *pRtns
    )
    {
        uint32_t            i;
        uint32_t            iMax;
        NODERTN_DATA        *pRtn;
        ERESULT_DATA        *pErr;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if (OBJ_NIL == pRtns) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
    #endif
        
        iMax = NodeArray_getSize(pRtns);
        for (i=0; i<iMax; i++) {
            pRtn = (NODERTN_DATA *)NodeArray_Get(pRtns, i+1);
            if (OBJ_NIL == pRtn) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_OBJECT,
                                       "Routine Array missing element");
            }
            if (!obj_IsKindOf(pRtn, OBJ_IDENT_NODERTN)) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_OBJECT,
                                       "Routine Array missing element");
            }
            pErr = ExpandNodes_ExpandRtn(this, pRtn);
            if (pErr) {
                DEBUG_BREAK();
                return pErr;
            }
        }

        // Return to caller.
        return OBJ_NIL;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    EXPANDNODES_DATA *   ExpandNodes_Init (
        EXPANDNODES_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(EXPANDNODES_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_EXPANDNODES);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ExpandNodes_Vtbl);
        
        this->pRtns = NodeArray_New( );
        if (OBJ_NIL == this->pRtns) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pTests = NodeArray_New( );
        if (OBJ_NIL == this->pTests) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pDeps = AStrCArray_New( );
        if (OBJ_NIL == this->pDeps) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "ExpandNodes::sizeof(EXPANDNODES_DATA) = %lu\n", sizeof(EXPANDNODES_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(EXPANDNODES_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ExpandNodes_IsEnabled (
        EXPANDNODES_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
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
        void        *pMethod = ExpandNodes_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ExpandNodes", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ExpandNodes_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        EXPANDNODES_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(EXPANDNODES_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ExpandNodes_Class();
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
                            return ExpandNodes_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ExpandNodes_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ExpandNodes_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return ExpandNodes_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ExpandNodes_ToDebugString)
                    return "ToDebugString";
                if (pData == ExpandNodes_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                     S e t u p  D e p s
    //---------------------------------------------------------------

    /*!
     Set up the external dependencies from the Program or Library
     definitions.
     @param     this    object pointer
     @param     pDict   Dictionary pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ExpandNodes_SetupDeps (
        EXPANDNODES_DATA    *this,
        DICT_DATA           *pDict
    )
    {
        ASTRCARRAY_DATA     *pArray = OBJ_NIL;
        ERESULT             eRc;
        const
        char                *pSrcDirA;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pDict) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pSrcDirA = Dict_GetA(pDict, srcDirVarID);
        
        // Merge Headers.
        if (this->pLib) {
            pArray = NodeLib_getHdrs(this->pLib);
        } else if (this->pPgm) {
            pArray = NodePgm_getHdrs(this->pPgm);
        }
        if (pArray) {
            uint32_t        i;
            uint32_t        iMax = AStrCArray_getSize(pArray);
            ASTR_DATA       *pStr = AStr_New();
            for (i=0; i<iMax; i++) {
                ASTRC_DATA      *pWrkC = AStrCArray_Get(pArray, i+1);
                const
                char            *pStrA;
                if ('$' == AStrC_CharGetFirstW32(pWrkC))
                    pStrA = AStrC_getData(pWrkC);
                else {
                    AStr_AppendA(pStr, pSrcDirA);
                    AStr_AppendA(pStr, "/");
                    AStr_AppendA(pStr, AStrC_getData(pWrkC));
                    pStrA = AStr_getData(pStr);
                }
                if (0 == AStrCArray_FindA(this->pDeps, pStrA)) {
                    eRc = AStrCArray_AppendA(this->pDeps, pStrA, NULL);
                }
                AStr_Truncate(pStr, 0);
            }
            obj_Release(pStr);
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------

    /*!
     Sort the arrays.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ExpandNodes_Sort (
        EXPANDNODES_DATA    *this
    )
    {
        OBJARRAY_DATA       *pArray;
        ERESULT             eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pArray = NodeArray_getObjArray(this->pRtns);
        eRc = ObjArray_SortAscending(pArray, (P_OBJ_COMPARE)NodeBase_Compare);
        
        pArray = NodeArray_getObjArray(this->pTests);
        eRc = ObjArray_SortAscending(pArray, (P_OBJ_COMPARE)NodeBase_Compare);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     ExpandNodes_ToJSON (
        EXPANDNODES_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
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
        ASTR_DATA      *pDesc = ExpandNodes_ToDebugString(this,4);
     @endcode 
     @param     this    EXPANDNODES object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ExpandNodes_ToDebugString (
        EXPANDNODES_DATA *this,
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
        if (!ExpandNodes_Validate(this)) {
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
                    ExpandNodes_getSize(this)
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
    
    
    ASTR_DATA *     ExpandNodes_ToString (
        EXPANDNODES_DATA *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrk = OBJ_NIL;
        NODERTNA_DATA   *pRtnA = OBJ_NIL;
        NODETSTA_DATA   *pTstA = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ExpandNodes_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        eRc = AStr_AppendPrint(pStr, "==================  ExpandNodes Output "
                               "=================\n");

        if (this->pLib) {
            pWrk = NodeLib_ToString(this->pLib);
            if (pWrk) {
                eRc = AStr_Append(pStr, pWrk);
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
                AStr_AppendA(pStr, "\n");
            }
        }
        if (this->pPgm) {
            pWrk = NodePgm_ToString(this->pPgm);
            if (pWrk) {
                eRc = AStr_Append(pStr, pWrk);
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
                AStr_AppendA(pStr, "\n");
            }
        }
        if (this->pRtns) {
            iMax = NodeArray_getSize(this->pRtns);
            if (iMax > 0) {
                eRc = AStr_AppendPrint(pStr, "-----------------  ExpandNodes %d Routines "
                                       "-----------------\n", iMax);
            }
            for (i=0; i<iMax; i++) {
                pRtnA = (NODERTNA_DATA *)NodeArray_Get(this->pRtns, i+1);
                if (pRtnA) {
                    pWrk = NodeRtnA_ToString(pRtnA);
                    if (pWrk) {
                        eRc = AStr_Append(pStr, pWrk);
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                        AStr_AppendA(pStr, "\n");
                    }
                }
            }
            AStr_AppendA(pStr, "\n");
        }
        if (this->pTests) {
            iMax = NodeArray_getSize(this->pTests);
            if (iMax > 0) {
                eRc = AStr_AppendPrint(pStr, "-----------------  ExpandNodes %d Tests "
                                       "-----------------\n", iMax);
            }
            for (i=0; i<iMax; i++) {
                pTstA = (NODETSTA_DATA *)NodeArray_Get(this->pTests, i+1);
                if (pTstA) {
                    pWrk = NodeTstA_ToString(pTstA);
                    if (pWrk) {
                        eRc = AStr_Append(pStr, pWrk);
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                        AStr_AppendA(pStr, "\n");
                    }
                }
            }
            AStr_AppendA(pStr, "\n");
        }

        return pStr;
    }
        
            


    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            ExpandNodes_Validate (
        EXPANDNODES_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_EXPANDNODES))
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


        if (!(obj_getSize(this) >= sizeof(EXPANDNODES_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


