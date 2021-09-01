// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeTstA.c
 *	Generated 11/10/2019 17:54:48
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
#include        <NodeTstA_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            NodeTstA_task_body (
        void            *pData
    )
    {
        //NODETSTA_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODETSTA_DATA *     NodeTstA_Alloc (
        void
    )
    {
        NODETSTA_DATA       *this;
        uint32_t        cbSize = sizeof(NODETSTA_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODETSTA_DATA *     NodeTstA_New (
        void
    )
    {
        NODETSTA_DATA       *this;
        
        this = NodeTstA_Alloc( );
        if (this) {
            this = NodeTstA_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  A r c h i t e c t u r e s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeTstA_getArches (
        NODETSTA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getArches(NodeTstA_getNodeBase(this));
    }


    bool            NodeTstA_setArches (
        NODETSTA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setArches(NodeTstA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        D e p s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeTstA_getDeps (
        NODETSTA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getDeps(NodeTstA_getNodeBase(this));
    }


    bool            NodeTstA_setDeps (
        NODETSTA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setDeps(NodeTstA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                    E x t e n s i o n
    //---------------------------------------------------------------

    ASTRC_DATA *    NodeTstA_getExt (
        NODETSTA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getExt(NodeTstA_getNodeBase(this));
    }


    bool            NodeTstA_setExt (
        NODETSTA_DATA   *this,
        ASTRC_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setExt(NodeTstA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        N a m e
    //---------------------------------------------------------------

    ASTRC_DATA *    NodeTstA_getName (
        NODETSTA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getName(NodeTstA_getNodeBase(this));
    }


    bool            NodeTstA_setName (
        NODETSTA_DATA   *this,
        ASTRC_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setName(NodeTstA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                           N o d e
    //---------------------------------------------------------------

    NODE_DATA *     NodeTstA_getNode (
        NODETSTA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (NODE_DATA *)this;
    }


    //---------------------------------------------------------------
    //                       N o d e  B a s e
    //---------------------------------------------------------------

    NODEBASE_DATA * NodeTstA_getNodeBase (
        NODETSTA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (NODEBASE_DATA *)this;
    }


    //---------------------------------------------------------------
    //                        O S
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeTstA_getOSs (
        NODETSTA_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getOSs(NodeTstA_getNodeBase(this));
    }


    bool            NodeTstA_setOSs (
        NODETSTA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setOSs(NodeTstA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        NodeTstA_getPriority (
        NODETSTA_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NodeTstA_setPriority (
        NODETSTA_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
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
    
    uint32_t        NodeTstA_getSize (
        NODETSTA_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S r c s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeTstA_getSrcs (
        NODETSTA_DATA   *this
    )
    {

        // Validate the input parameters.
    #ifdef NDEBUG
    #else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
    #endif

        return NodeBase_getSrcs(NodeTstA_getNodeBase(this));
    }


    bool            NodeTstA_setSrcs (
        NODETSTA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    )
    {
    #ifdef NDEBUG
    #else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        return NodeBase_setSrcs(NodeTstA_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * NodeTstA_getStr (
        NODETSTA_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        NodeTstA_setStr (
        NODETSTA_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  NodeTstA_getSuperVtbl (
        NODETSTA_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
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
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = NodeTstA_Assign(this,pOther);
     @endcode 
     @param     this    NODETSTA object pointer
     @param     pOther  a pointer to another NODETSTA object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeTstA_Assign (
        NODETSTA_DATA		*this,
        NODETSTA_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeTstA_Validate(pOther)) {
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

    ERESULT             NodeTstA_CheckContraints (
            NODETSTA_DATA   *this,
            const
            char            *pArch,
            const
            char            *pOS
    )
    {
            ERESULT         eRc;

#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        eRc = NodeBase_CheckConstraints(NodeTstA_getNodeBase(this), pArch, pOS);
        if (ERESULT_FAILED(eRc)) {
            NodeTstA_Disable(this);
        } else {
            NodeTstA_Enable(this);
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
    int             NodeTstA_Compare (
        NODETSTA_DATA   *this,
        NODETSTA_DATA   *pOther
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int             iRc;
        
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeTstA_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        iRc = NodeBase_Compare(NodeTstA_getNodeBase(this), NodeTstA_getNodeBase(pOther));

        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        NodeTstA      *pCopy = NodeTstA_Copy(this);
     @endcode 
     @param     this    NODETSTA object pointer
     @return    If successful, a NODETSTA object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODETSTA_DATA *     NodeTstA_Copy (
        NODETSTA_DATA       *this
    )
    {
        NODETSTA_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeTstA_New( );
        if (pOther) {
            eRc = NodeTstA_Assign(this, pOther);
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

    void            NodeTstA_Dealloc (
        OBJ_ID          objId
    )
    {
        NODETSTA_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODETSTA_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NodeTstA_setStr(this, OBJ_NIL);

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

    ASTR_DATA *     NodeTstA_Deps (
        NODETSTA_DATA   *this,
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
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
    #endif
        
        pStr = AStrCArray_ToStringSep(NodeTstA_getDeps(this), " ", pPrefix, pSuffix);

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
    ERESULT         NodeTstA_Disable (
        NODETSTA_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeTstA_Validate(this)) {
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
    ERESULT         NodeTstA_Enable (
        NODETSTA_DATA	*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeTstA_Validate(this)) {
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

    ASTR_DATA *     NodeTstA_GenMac (
        NODETSTA_DATA   *this,
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
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            //return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
            return OBJ_NIL;
        }
    #endif
        
        // Skip disabled entries.
        if (ERESULT_SUCCESS_FALSE == NodeTstA_IsEnabled(this)) {
            return OBJ_NIL;
        }
        
        // Set up to generate Makefile entry.
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            //return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
            return OBJ_NIL;
        }
        pExt = NodeTstA_getExt(this);

        AStr_AppendPrint(
            pStr,
            "%s += %s\n\n",
            Dict_GetA(pDict, testsVarID),
            AStrC_getData(NodeTstA_getName(this))
        );
        
        if ((AStrC_CompareA(pExt, "c") == 0)
            || (AStrC_CompareA(pExt, "C") == 0)
            || (AStrC_CompareA(pExt, "cpp") == 0)
            || (AStrC_CompareA(pExt, "CPP") == 0)) {
            // First prerequisite must be the Test Program Source.
            ASTR_DATA       *pWrk = AStr_New();
            if (AStrC_CharGetFirstW32(NodeTstA_getName(this)) == '$') {
                AStr_AppendA(pWrk, AStrC_getData(NodeTstA_getName(this)));
            } else {
                AStr_AppendPrint(pWrk,
                                 "$(%s)/%s",
                                 Dict_GetA(pDict, tstSrcVarID),
                                 AStrC_getData(NodeTstA_getName(this))
                );
            }
            AStr_AppendPrint(
                pStr,
                "%s: %s.%s ",
                AStrC_getData(NodeTstA_getName(this)),
                AStr_getData(pWrk),
                AStrC_getData(pExt)
            );
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
            iMax = AStrCArray_getSize(NodeTstA_getDeps(this));
            for (i=0; i<iMax; i++) {
                ASTRC_DATA      *pStrC = AStrCArray_Get(NodeTstA_getDeps(this), i+1);
                if (pStrC) {
                    if (AStrC_CharGetFirstW32(pStrC) == '$') {
                        AStr_AppendA(pStr, AStrC_getData(pStrC));
                        AStr_AppendA(pStr, " ");
                    } else {
                        AStr_AppendPrint(
                                         pStr,
                                         "$(%s)/%s ",
                                         Dict_GetA(pDict, tstSrcVarID),
                                         AStrC_getData(pStrC)
                        );
                    }
                }
            }
            AStr_AppendA(pStr, "\n");
            AStr_AppendPrint(
                pStr,
                "\t$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(%s)/$(@F) $(%s) -I$(%s) -I$(%s)",
                Dict_GetA(pDict, tstBinVarID),
                Dict_GetA(pDict, objsVarID),
                Dict_GetA(pDict, tstSrcVarID),
                Dict_GetA(pDict, srcDirVarID)
            );
            iMax = AStrCArray_getSize(NodeTstA_getSrcs(this));
            for (i=0; i<iMax; i++) {
                ASTRC_DATA      *pStrC = AStrCArray_Get(NodeTstA_getSrcs(this), i+1);
                if (pStrC) {
                    if (AStrC_CharGetFirstW32(pStrC) == '$') {
                        AStr_AppendA(pStr, " ");
                        AStr_AppendA(pStr, AStrC_getData(pStrC));
                    } else {
                        AStr_AppendPrint(
                                         pStr,
                                         " $(%s)/%s",
                                         Dict_GetA(pDict, tstSrcVarID),
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
                    AStrC_getData(NodeTstA_getName(this)),
                    AStrC_getData(NodeTstA_getExt(this))
            );
            DEBUG_BREAK();
            obj_Release(pStr);
            //return eResult_NewStrA(ERESULT_UNSUPPORTED_PARAMETER, "Invalid File Suffix");
            return OBJ_NIL;
        }

        AStr_AppendPrint(
            pStr,
            "\t$(%s)/$(@F) --no_int3\n\n",
            Dict_GetA(pDict, tstBinVarID)
        );

        // Return to caller.
        return pStr;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODETSTA_DATA *   NodeTstA_Init (
        NODETSTA_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODETSTA_DATA);
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
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODETSTA);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeTstA_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "NodeTstA::sizeof(NODETSTA_DATA) = %lu\n", sizeof(NODETSTA_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODETSTA_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeTstA_IsEnabled (
        NODETSTA_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
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
        void        *pMethod = NodeTstA_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeTstA", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeTstA_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODETSTA_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODETSTA_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeTstA_Class();
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
                            return NodeTstA_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeTstA_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeTstA_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return NodeTstA_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeTstA_ToDebugString)
                    return "ToDebugString";
                if (pData == NodeTstA_ToJSON)
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

    ASTR_DATA *     NodeTstA_Srcs (
        NODETSTA_DATA   *this,
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
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
    #endif
        
        pStr = AStrCArray_ToStringSep(NodeTstA_getSrcs(this), " ", pPrefix, pSuffix);

        // Return to caller.
        return pStr;
    }



    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     NodeTstA_ToJSON (
        NODETSTA_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
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
        ASTR_DATA      *pDesc = NodeTstA_ToDebugString(this,4);
     @endcode 
     @param     this    NODETSTA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeTstA_ToDebugString (
        NODETSTA_DATA      *this,
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
        if (!NodeTstA_Validate(this)) {
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
                    NodeTstA_getSize(this)
            );

        pWrkStr =   NodeBase_ToDebugString(NodeTstA_getNodeBase(this), indent+3);
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
    
    
     ASTR_DATA *    NodeTstA_ToString (
        NODETSTA_DATA   *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrk;
        
#ifdef NDEBUG
#else
        if (!NodeTstA_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendA(pStr, "===> TSTA:\n");
            pWrk = NodeBase_ToString(NodeTstA_getNodeBase(this));
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
    bool            NodeTstA_Validate (
        NODETSTA_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODETSTA))
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


        if (!(obj_getSize(this) >= sizeof(NODETSTA_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


