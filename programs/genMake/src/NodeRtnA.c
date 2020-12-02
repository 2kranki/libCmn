// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeRtnA.c
 *	Generated 11/10/2019 10:31:05
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
#include        <NodeRtnA_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            NodeRtnA_task_body (
        void            *pData
    )
    {
        //NODERTNA_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODERTNA_DATA *     NodeRtnA_Alloc (
        void
    )
    {
        NODERTNA_DATA       *this;
        uint32_t        cbSize = sizeof(NODERTNA_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODERTNA_DATA *     NodeRtnA_New (
        void
    )
    {
        NODERTNA_DATA       *this;
        
        this = NodeRtnA_Alloc( );
        if (this) {
            this = NodeRtnA_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  A r c h i t e c t u r e s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeRtnA_getArches (
        NODERTNA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getArches(NodeRtnA_getNodeBase(this));
    }


    bool            NodeRtnA_setArches (
        NODERTNA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setArches(NodeRtnA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        D e p s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeRtnA_getDeps (
        NODERTNA_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getDeps(NodeRtnA_getNodeBase(this));
    }


    bool            NodeRtnA_setDeps (
        NODERTNA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setDeps(NodeRtnA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                    E x t e n s i o n
    //---------------------------------------------------------------

    ASTRC_DATA *    NodeRtnA_getExt (
        NODERTNA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getExt(NodeRtnA_getNodeBase(this));
    }


    bool            NodeRtnA_setExt (
        NODERTNA_DATA   *this,
        ASTRC_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setExt(NodeRtnA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        N a m e
    //---------------------------------------------------------------

    ASTRC_DATA *    NodeRtnA_getName (
        NODERTNA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getName(NodeRtnA_getNodeBase(this));
    }


    bool            NodeRtnA_setName (
        NODERTNA_DATA   *this,
        ASTRC_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setName(NodeRtnA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                           N o d e
    //---------------------------------------------------------------

    NODE_DATA *     NodeRtnA_getNode (
        NODERTNA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (NODE_DATA *)this;
    }


    //---------------------------------------------------------------
    //                       N o d e  B a s e
    //---------------------------------------------------------------

    NODEBASE_DATA * NodeRtnA_getNodeBase (
        NODERTNA_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (NODEBASE_DATA *)this;
    }


    //---------------------------------------------------------------
    //                        O S
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeRtnA_getOSs (
        NODERTNA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getOSs(NodeRtnA_getNodeBase(this));
    }


    bool            NodeRtnA_setOSs (
        NODERTNA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setOSs(NodeRtnA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        NodeRtnA_getSize (
        NODERTNA_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S r c s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeRtnA_getSrcs (
        NODERTNA_DATA   *this
    )
    {

        // Validate the input parameters.
    #ifdef NDEBUG
    #else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
    #endif

        return NodeBase_getSrcs(NodeRtnA_getNodeBase(this));
    }


    bool            NodeRtnA_setSrcs (
        NODERTNA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    )
    {
    #ifdef NDEBUG
    #else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        return NodeBase_setSrcs(NodeRtnA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodeRtnA_getSuperVtbl (
        NODERTNA_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
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
    //                          A p p e n d
    //---------------------------------------------------------------

    /*!
     Append a string to the dependencies.
     @param     this    object pointer
     @param     pStrC   string pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT_DATA *  NodeRtnA_AppendDeps (
        NODERTNA_DATA    *this,
        ASTRC_DATA       *pStrC
    )
    {
        ERESULT_DATA    *pErr = OBJ_NIL;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
    #endif

        pErr = NodeBase_AppendDeps(NodeRtnA_getNodeBase(this), pStrC);
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
        ERESULT eRc = NodeRtnA_Assign(this,pOther);
     @endcode 
     @param     this    NODERTNA object pointer
     @param     pOther  a pointer to another NODERTNA object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeRtnA_Assign (
        NODERTNA_DATA		*this,
        NODERTNA_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeRtnA_Validate(pOther)) {
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
    //                 C h e c k  C o n s t r a i n t s
    //---------------------------------------------------------------

    ERESULT             NodeRtnA_CheckContraints (
        NODERTNA_DATA   *this,
        const
        char            *pArch,
        const
        char            *pOS
    )
    {
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        eRc = NodeBase_CheckConstraints(NodeRtnA_getNodeBase(this), pArch, pOS);
        if (ERESULT_FAILED(eRc)) {
            NodeRtnA_Disable(this);
        } else {
            NodeRtnA_Enable(this);
        }
        
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
    int             NodeRtnA_Compare (
        NODERTNA_DATA   *this,
        NODERTNA_DATA   *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc;
        
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 2;
        }
        if (!NodeRtnA_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return 2;
        }
#endif
        
        iRc = NodeBase_Compare(NodeRtnA_getNodeBase(this), NodeRtnA_getNodeBase(pOther));
        
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        NodeRtnA      *pCopy = NodeRtnA_Copy(this);
     @endcode 
     @param     this    NODERTNA object pointer
     @return    If successful, a NODERTNA object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODERTNA_DATA *     NodeRtnA_Copy (
        NODERTNA_DATA       *this
    )
    {
        NODERTNA_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeRtnA_New( );
        if (pOther) {
            eRc = NodeRtnA_Assign(this, pOther);
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

    void            NodeRtnA_Dealloc (
        OBJ_ID          objId
    )
    {
        NODERTNA_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODERTNA_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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
    //                          D e p s
    //---------------------------------------------------------------

    ASTR_DATA *     NodeRtnA_Deps (
        NODERTNA_DATA   *this,
        const
        char            *pPrefix,
        const
        char            *pSuffix
    )
    {
        ASTR_DATA       *pStr;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
    #endif
        
        pStr = AStrCArray_ToStringSep(NodeRtnA_getDeps(this), " ", pPrefix, pSuffix);

        // Return to caller.
        return pStr;
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
    ERESULT         NodeRtnA_Disable (
        NODERTNA_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeRtnA_Validate(this)) {
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
    ERESULT         NodeRtnA_Enable (
        NODERTNA_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeRtnA_Validate(this)) {
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
    //                    G e n e r a t i o n
    //---------------------------------------------------------------

    ASTR_DATA *     NodeRtnA_GenMac (
        NODERTNA_DATA   *this,
        DICT_DATA       *pDict
    )
    {
        //ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        ASTRC_DATA      *pExt;
        uint32_t        i;
        uint32_t        iMax;

            // Do initialization.
        #ifdef NDEBUG
        #else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            //return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
            return OBJ_NIL;
        }
    #endif
        
        // Skip disabled entries.
        if (ERESULT_SUCCESS_FALSE == NodeRtnA_IsEnabled(this)) {
            return OBJ_NIL;
        }
        
        // Set up to generate Makefile entry.
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            //return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
            return OBJ_NIL;
        }
        pExt = NodeRtnA_getExt(this);

        AStr_AppendPrint(
            pStr,
            "%s += $(%s)/%s.o\n\n",
            Dict_GetA(pDict, objsVarID),
            Dict_GetA(pDict, objDirVarID),
            AStrC_getData(NodeRtnA_getName(this))
        );
        
        if ((AStrC_CompareA(pExt, "c") == 0)
            || (AStrC_CompareA(pExt, "C") == 0)
            || (AStrC_CompareA(pExt, "cpp") == 0)
            || (AStrC_CompareA(pExt, "CPP") == 0)) {
            // First prerequisite must be the Test Program Source.
            ASTR_DATA       *pWrk = AStr_New();
            if (AStrC_CharGetFirstW32(NodeRtnA_getName(this)) == '$') {
                AStr_AppendA(pWrk, AStrC_getData(NodeRtnA_getName(this)));
            } else {
                AStr_AppendPrint(pWrk,
                                 "$(%s)/%s",
                                 Dict_GetA(pDict, srcDirVarID),
                                 AStrC_getData(NodeRtnA_getName(this))
                );
            }
            AStr_AppendPrint(
                pStr,
                "$(%s)/%s.o: %s.%s ",
                Dict_GetA(pDict, objDirVarID),
                AStrC_getData(NodeRtnA_getName(this)),
                AStr_getData(pWrk),
                AStrC_getData(pExt)
            );
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
            iMax = AStrCArray_getSize(NodeRtnA_getDeps(this));
            for (i=0; i<iMax; i++) {
                ASTRC_DATA      *pStrC = AStrCArray_Get(NodeRtnA_getDeps(this), i+1);
                if (pStrC) {
                    if (AStrC_CharGetFirstW32(pStrC) == '$') {
                        AStr_AppendA(pStr, AStrC_getData(pStrC));
                        AStr_AppendA(pStr, " ");
                    } else {
                        AStr_AppendPrint(
                                         pStr,
                                         "$(%s)/%s ",
                                         Dict_GetA(pDict, srcDirVarID),
                                         AStrC_getData(pStrC)
                        );
                    }
                }
            }
            AStr_AppendA(pStr, "\n");
            AStr_AppendPrint(
                pStr,
                "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) -I$(%s)",
                Dict_GetA(pDict, objDirVarID),
                Dict_GetA(pDict, srcDirVarID)
            );
            iMax = AStrCArray_getSize(NodeRtnA_getSrcs(this));
            for (i=0; i<iMax; i++) {
                ASTRC_DATA      *pStrC = AStrCArray_Get(NodeRtnA_getSrcs(this), i+1);
                if (pStrC) {
                    if (AStrC_CharGetFirstW32(pStrC) == '$') {
                        AStr_AppendA(pStr, " ");
                        AStr_AppendA(pStr, AStrC_getData(pStrC));
                    } else {
                        AStr_AppendPrint(
                                         pStr,
                                         " $(%s)/%s",
                                         Dict_GetA(pDict, srcDirVarID),
                                         AStrC_getData(pStrC)
                        );
                    }
                }
            }
            // $< == the name of the first prerequisite
            AStr_AppendA(pStr, " $<\n");
        }
        else {
            fprintf(stderr, "Error: Unsupported file extension for %s.%s\n\n",
                    AStrC_getData(NodeRtnA_getName(this)),
                    AStrC_getData(NodeRtnA_getExt(this))
            );
            DEBUG_BREAK();
            obj_Release(pStr);
            //return eResult_NewStrA(ERESULT_UNSUPPORTED_PARAMETER, "Invalid File Suffix");
            return OBJ_NIL;
        }
        
        if (pStr) {
            AStr_AppendA(pStr, "\n");
        }

        // Return to caller.
        return pStr;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODERTNA_DATA *   NodeRtnA_Init (
        NODERTNA_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODERTNA_DATA);
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
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODERTNA);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeRtnA_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "NodeRtnA::sizeof(NODERTNA_DATA) = %lu\n", sizeof(NODERTNA_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODERTNA_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeRtnA_IsEnabled (
        NODERTNA_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
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
        void        *pMethod = NodeRtnA_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeRtnA", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeRtnA_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODERTNA_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODERTNA_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeRtnA_Class();
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
                            return NodeRtnA_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeRtnA_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeRtnA_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return NodeRtnA_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeRtnA_ToDebugString)
                    return "ToDebugString";
                if (pData == NodeRtnA_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S r c s
    //---------------------------------------------------------------

    ASTR_DATA *     NodeRtnA_Srcs (
        NODERTNA_DATA   *this,
        const
        char            *pPrefix,
        const
        char            *pSuffix
    )
    {
        ASTR_DATA       *pStr;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeRtnA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
    #endif
        
        pStr = AStrCArray_ToStringSep(NodeRtnA_getSrcs(this), " ", pPrefix, pSuffix);

        // Return to caller.
        return pStr;
    }



    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     NodeRtnA_ToJSON (
        NODERTNA_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!NodeRtnA_Validate(this)) {
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
        ASTR_DATA      *pDesc = NodeRtnA_ToDebugString(this,4);
     @endcode 
     @param     this    NODERTNA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeRtnA_ToDebugString (
        NODERTNA_DATA   *this,
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
        if (!NodeRtnA_Validate(this)) {
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
                    NodeRtnA_getSize(this)
            );

        pWrkStr =   NodeBase_ToDebugString(NodeRtnA_getNodeBase(this), indent+3);
        AStr_Append(pStr, pWrkStr);
        obj_Release(pWrkStr);

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
    
    
         ASTR_DATA *    NodeRtnA_ToString (
            NODERTNA_DATA   *this
        )
        {
            ERESULT         eRc;
            ASTR_DATA       *pStr;
            ASTR_DATA       *pWrk;
            
    #ifdef NDEBUG
    #else
            if (!NodeRtnA_Validate(this)) {
                DEBUG_BREAK();
                return OBJ_NIL;
            }
    #endif
            
            pStr = AStr_New();
            if (pStr) {
                eRc =   AStr_AppendA(pStr, "===> RTNA:\n");
                pWrk = NodeBase_ToString(NodeRtnA_getNodeBase(this));
                eRc = AStr_Append(pStr, pWrk);
                obj_Release(pWrk);
                eRc = AStr_AppendA(pStr, "\n\n");
            }
            
            return pStr;
        }
                
                

    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            NodeRtnA_Validate (
        NODERTNA_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODERTNA))
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


        if (!(obj_getSize(this) >= sizeof(NODERTNA_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


