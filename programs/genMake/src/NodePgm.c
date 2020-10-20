// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodePgm.c
 *	Generated 11/03/2019 08:11:49
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
#include        <NodePgm_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            NodePgm_task_body (
        void            *pData
    )
    {
        //NODEPGM_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEPGM_DATA *  NodePgm_Alloc (
        void
    )
    {
        NODEPGM_DATA    *this;
        uint32_t        cbSize = sizeof(NODEPGM_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEPGM_DATA *  NodePgm_New (
        void
    )
    {
        NODEPGM_DATA    *this;
        
        this = NodePgm_Alloc( );
        if (this) {
            this = NodePgm_Init(this);
        } 
        return this;
    }


    ERESULT_DATA *  NodePgm_Parse (
        NODE_DATA       *pNode,             // Hash Data Node
        NODEPGM_DATA    **ppBase
    )
    {
        //ERESULT         eRc;
        ERESULT_DATA    *pErr = OBJ_NIL;
        NODEHASH_DATA   *pHash;
        NODE_DATA       *pHashItem;
        NODEPGM_DATA    *pPgm;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER,
                                   "Error: Invalid Input Node!");
            return pErr;
        }
        if (!obj_IsKindOf(Node_getData(pNode), OBJ_IDENT_NODEHASH)) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER,
                                   "Error: Missing Input Hash Node!");
            return pErr;
        }
        if (OBJ_NIL == ppBase) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER,
                                   "Error: Missing Base Node Pointer!");
            return pErr;
        }
    #endif
        pPgm = NodePgm_New();
        if (OBJ_NIL == pPgm) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
            return pErr;
        }
        *ppBase = OBJ_NIL;

        pHash = JsonIn_CheckNodeForHash(pNode);
        if (pHash) {
            // Ok, we have a hash, so there might a lot to parse here.

            // Scan off the base parameters.
            pErr = NodeBase_Parse(pNode, (NODEBASE_DATA **)&pPgm);
            if (pErr) {
                DEBUG_BREAK();
                obj_Release(pPgm);
                return pErr;
            }
            pErr = NodeBase_AddPrefixHdrsA((NODEBASE_DATA *)pPgm, "$(SRCDIR)/");
            if (pErr) {
                DEBUG_BREAK();
                obj_Release(pPgm);
                return pErr;
            }

            // Scan off the main program name if present.
            pHashItem = NodeHash_FindA(pHash, 0, "main");
            if (pHashItem) {
                ASTR_DATA       *pStr;
                ASTRC_DATA      *pStrC;
                pStr = JsonIn_CheckNodeDataForString(pHashItem);
                if (pStr) {
                    pStrC = AStrC_NewFromAStr(pStr);
                    NodePgm_setMain(pPgm, pStrC);
                    obj_Release(pStrC);
                    pStrC = OBJ_NIL;
                } else {
                    return eResult_NewStrA(ERESULT_INVALID_SYNTAX,
                                           "Main Program Name must be a string!");
                }
            }
            *ppBase = pPgm;
        }
        
        // Now set up some defaults.
        if (pPgm) {
            uint32_t        i;
            uint32_t        iMax;
            ASTRC_DATA      *pStrC;
            iMax = AStrCArray_getSize(NodePgm_getDeps(pPgm));
            for (i=0; i<iMax; i++) {
                pStrC = AStrCArray_Get(NodePgm_getDeps(pPgm), i+1);
                if (pStrC) {
                    ASTR_DATA       *pLwr = AStrC_ToLower(pStrC);
                    ASTR_DATA       *pUpr = AStrC_ToUpper(pStrC);
                    ASTR_DATA       *pStr = OBJ_NIL;
                    pStr = AStr_NewFromPrint(
                                    "$(LIB%s_BASE)/include/%s_defs.h",
                                    AStr_getData(pUpr),
                                    AStr_getData(pLwr)
                            );
                    pErr =  NodeBase_AppendHdrsA(
                                        NodePgm_getNodeBase(pPgm),
                                        AStr_getData(pStr)
                            );
                    obj_Release(pLwr);
                    obj_Release(pUpr);
                    obj_Release(pStr);
                }
            }
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

    ASTRCARRAY_DATA * NodePgm_getArches (
        NODEPGM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getArches(NodePgm_getNodeBase(this));
    }


    bool            NodePgm_setArches (
        NODEPGM_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setArches(NodePgm_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        D e p s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodePgm_getDeps (
        NODEPGM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getDeps(NodePgm_getNodeBase(this));
    }


    bool            NodePgm_setDeps (
        NODEPGM_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setDeps(NodePgm_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        H d r s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodePgm_getHdrs (
        NODEPGM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getHdrs(NodePgm_getNodeBase(this));
    }


    bool            NodePgm_setHdrs (
        NODEPGM_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setHdrs(NodePgm_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        M a i n
    //---------------------------------------------------------------
    
    ASTRC_DATA *    NodePgm_getMain (
        NODEPGM_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pMain;
    }
    
    
    bool            NodePgm_setMain (
        NODEPGM_DATA    *this,
        ASTRC_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_MAIN_OWNED
        obj_Retain(pValue);
        if (this->pMain) {
            obj_Release(this->pMain);
        }
#endif
        this->pMain = pValue;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                        N a m e
    //---------------------------------------------------------------

    ASTRC_DATA *     NodePgm_getName (
        NODEPGM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getName(NodePgm_getNodeBase(this));
    }


    bool            NodePgm_setName (
        NODEPGM_DATA    *this,
        ASTRC_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setName(NodePgm_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                           N o d e
    //---------------------------------------------------------------

    NODE_DATA *     NodePgm_getNode (
        NODEPGM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (NODE_DATA *)this;
    }


    //---------------------------------------------------------------
    //                       N o d e  B a s e
    //---------------------------------------------------------------

    NODEBASE_DATA *     NodePgm_getNodeBase (
        NODEPGM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (NODEBASE_DATA *)this;
    }


    //---------------------------------------------------------------
    //                        O S
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodePgm_getOSs (
        NODEPGM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getOSs(NodePgm_getNodeBase(this));
    }


    bool            NodePgm_setOSs (
        NODEPGM_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setOSs(NodePgm_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        NodePgm_getPriority (
        NODEPGM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NodePgm_setPriority (
        NODEPGM_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
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
    
    uint32_t        NodePgm_getSize (
        NODEPGM_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S r c s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodePgm_getSrcs (
        NODEPGM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getSrcs(NodePgm_getNodeBase(this));
    }


    bool            NodePgm_setSrcs (
        NODEPGM_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setSrcs(NodePgm_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodePgm_getSuperVtbl (
        NODEPGM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
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
        ERESULT eRc = NodePgm_Assign(this,pOther);
     @endcode 
     @param     this    NODEPGM object pointer
     @param     pOther  a pointer to another NODEPGM object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodePgm_Assign (
        NODEPGM_DATA		*this,
        NODEPGM_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodePgm_Validate(pOther)) {
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
    ERESULT         NodePgm_Compare (
        NODEPGM_DATA     *this,
        NODEPGM_DATA     *pOther
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
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodePgm_Validate(pOther)) {
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
        NodePgm      *pCopy = NodePgm_Copy(this);
     @endcode 
     @param     this    NODEPGM object pointer
     @return    If successful, a NODEPGM object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEPGM_DATA *     NodePgm_Copy (
        NODEPGM_DATA       *this
    )
    {
        NODEPGM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodePgm_New( );
        if (pOther) {
            eRc = NodePgm_Assign(this, pOther);
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

    void            NodePgm_Dealloc (
        OBJ_ID          objId
    )
    {
        NODEPGM_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODEPGM_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NodePgm_setMain(this, OBJ_NIL);

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
    ERESULT         NodePgm_Disable (
        NODEPGM_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodePgm_Validate(this)) {
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
    ERESULT         NodePgm_Enable (
        NODEPGM_DATA	*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodePgm_Validate(this)) {
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

    ASTR_DATA *     NodePgm_GenMacBegin (
        NODEPGM_DATA    *this,
        DICT_DATA       *pDict
    )
    {
        ASTR_DATA       *pStr =  OBJ_NIL;
        ASTRC_DATA      *pStrC =  OBJ_NIL;
        ASTRCARRAY_DATA *pArrayC =  OBJ_NIL;
        DATETIME_DATA   *pDate = OBJ_NIL;
        uint32_t        i;

            // Do initialization.
        #ifdef NDEBUG
        #else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            //return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
            return OBJ_NIL;
        }
    #endif
        
        // Set up to generate Makefile entry.
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            //return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
            return OBJ_NIL;
        }

        AStr_AppendA(pStr,
                     "# Generated file - Edits will be discarded by next generation!\n");
        pDate = DateTime_NewCurrent();
        if (pDate) {
            ASTR_DATA       *pWrk;
            pWrk = DateTime_ToString(pDate);
            AStr_AppendPrint(pStr, "# (%s)\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
            obj_Release(pDate);
            pDate = OBJ_NIL;
        }
        AStr_AppendA(pStr, "\n");

        AStr_AppendA(pStr, ".DEFAULT_GOAL := all\n");
        AStr_AppendA(pStr, "SHELL=/bin/sh\n");
        AStr_AppendA(pStr, "\n");

        //AStr_AppendA(pStr, "CC=clang\n");
        AStr_AppendPrint(pStr, "PGMNAM=%s\n", AStrC_getData(NodePgm_getName(this)));
        AStr_AppendA(pStr, "SYS=macos64\n");
        AStr_AppendA(pStr, "TEMP=/tmp\nBASE_OBJ = $(TEMP)/$(PGMNAM)\n");
        AStr_AppendA(pStr, "SRCDIR = ./src\n");
        AStr_AppendA(pStr, "TEST_SRC = ./tests\n");
        AStr_AppendA(pStr, "INSTALL_BASE = $(HOME)/Support/bin\n");
        AStr_AppendA(pStr, "LIB_BASE = $(HOME)/Support/lib/$(SYS)\n\n");

        AStr_AppendPrint(pStr, "CFLAGS += -g -Werror -I$(%s)\n",
                                Dict_GetA(pDict, srcDirVarID));
        AStr_AppendA(pStr, "ifdef  NDEBUG\n");
        AStr_AppendA(pStr, "CFLAGS += -DNDEBUG\n");
        AStr_AppendA(pStr, "else   #DEBUG\n");
        AStr_AppendA(pStr, "CFLAGS += -D_DEBUG\n");
        AStr_AppendA(pStr, "endif  #NDEBUG\n");
        AStr_AppendA(pStr, "CFLAGS += -D__MACOS64_ENV__\n");
        AStr_AppendA(pStr, "CFLAGS_LIBS = \n");
        pArrayC = NodePgm_getDeps(this);
        if (pArrayC && (AStrCArray_getSize(pArrayC) > 0)) {
            for (i=0; i<AStrCArray_getSize(pArrayC); i++) {
                pStrC = AStrCArray_Get(pArrayC, i+1);
                if (pStrC) {
                    ASTR_DATA       *pStrUpper = AStrC_ToUpper(pStrC);
                    AStr_AppendPrint(pStr, "# lib%s\n", AStrC_getData(pStrC));
                    AStr_AppendPrint(pStr, "LIB%s_BASE = $(LIB_BASE)/lib%s\n",
                                     AStr_getData(pStrUpper),
                                     AStrC_getData(pStrC)
                    );
                    AStr_AppendPrint(pStr, "CFLAGS += -I$(LIB%s_BASE)/include\n",
                                     AStr_getData(pStrUpper)
                    );
                    AStr_AppendPrint(pStr, "CFLAGS_LIBS += -l%s -L$(LIB%s_BASE)\n",
                                     AStrC_getData(pStrC),
                                     AStr_getData(pStrUpper)
                    );
                    obj_Release(pStrUpper);
                }
            }
        }
        AStr_AppendA(pStr, "CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses -lsqlite3\n\n");

        AStr_AppendA(pStr, "LIBOBJ = $(BASE_OBJ)/$(SYS)\n");
        AStr_AppendA(pStr, "ifdef  NDEBUG\n");
        AStr_AppendA(pStr, "LIB_FILENAME=$(PGMNAM)R.a\n");
        AStr_AppendA(pStr, "OBJDIR = $(LIBOBJ)/o/r\n");
        AStr_AppendA(pStr, "else   #DEBUG\n");
        AStr_AppendA(pStr, "LIB_FILENAME=$(PGMNAM)D.a\n");
        AStr_AppendA(pStr, "OBJDIR = $(LIBOBJ)/o/d\n");
        AStr_AppendA(pStr, "endif  #NDEBUG\n");
        AStr_AppendA(pStr, "TEST_OBJ = $(OBJDIR)/tests\n");
        AStr_AppendA(pStr, "TEST_BIN = $(OBJDIR)/tests\n");
        AStr_AppendA(pStr, "LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)\n\n");
        
        AStr_AppendA(pStr, ".SUFFIXES:\n");
        AStr_AppendA(pStr, ".SUFFIXES: .asm .c .cpp .o\n\n");

        AStr_AppendPrint(pStr, "%s =\n\n", Dict_GetA(pDict, objsVarID));
        AStr_AppendPrint(pStr, "%s =\n\n", Dict_GetA(pDict, testsVarID));
        AStr_AppendA(pStr, "\n");

        // Return to caller.
        return pStr;
    }
    

    ASTR_DATA *     NodePgm_GenMacEnd (
        NODEPGM_DATA    *this,
        DICT_DATA       *pDict
    )
    {
        ASTR_DATA       *pStr =  OBJ_NIL;

            // Do initialization.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            //return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
            return OBJ_NIL;
        }
#endif
        
        // Set up to generate Makefile entry.
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            //return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
            return OBJ_NIL;
        }

        AStr_AppendA(pStr, "\n\n.PHONY: test\n");
        AStr_AppendPrint(pStr, "test: $(%s)\n\n\n", Dict_GetA(pDict, testsVarID));
         
        AStr_AppendA(pStr, ".PHONY: clean\nclean:\n");
        AStr_AppendA(pStr, "\t-cd $(TEMP) ; [ -d $(PGMNAM) ] "
                            "&& rm -fr $(PGMNAM)\n\n\n");

        AStr_AppendA(pStr, ".PHONY: install\ninstall:\n");
        AStr_AppendA(pStr, "\t-cd $(INSTALL_BASE) ; [ -d $(PGMNAM) ] "
                            "&& rm -fr $(PGMNAM)\n");
        AStr_AppendPrint(
                pStr,
                "\tcp $(%s)/$(PGMNAM) $(INSTALL_BASE)/$(PGMNAM)\n\n\n",
                Dict_GetA(pDict, objDirVarID)
        );

        AStr_AppendPrint(
                pStr,
                ".PHONY: link\nlink: $(%s) $(%s)/%s\n",
                Dict_GetA(pDict, objsVarID),
                Dict_GetA(pDict, srcDirVarID),
                Dict_GetA(pDict, mainID)
        );
        AStr_AppendPrint(
                pStr,
                "\tCC -o $(%s)/$(PGMNAM) $(CFLAGS) $(CFLAGS_LIBS) $^\n\n\n",
                Dict_GetA(pDict, objDirVarID)
        );

        AStr_AppendA(pStr, ".PHONY: create_dirs\n");
        AStr_AppendA(pStr, "create_dirs:\n");
        AStr_AppendPrint(pStr,
                     "\t[ ! -d $(%s) ] && mkdir -p $(%s)/tests\n\n\n",
                      Dict_GetA(pDict, objDirVarID),
                      Dict_GetA(pDict, objDirVarID)
        );
         
        AStr_AppendA(pStr, ".PHONY: all\n");
        AStr_AppendA(pStr, "all:  clean create_dirs link\n\n\n");

        // Return to caller.
        return pStr;
    }


    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEPGM_DATA *   NodePgm_Init (
        NODEPGM_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODEPGM_DATA);
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
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODEPGM);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodePgm_Vtbl);
        
        this->pMain = AStrC_NewA("mainProgram.c");

    #ifdef NDEBUG
    #else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "NodePgm::sizeof(NODEPGM_DATA) = %lu\n", sizeof(NODEPGM_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODEPGM_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodePgm_IsEnabled (
        NODEPGM_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
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
        void        *pMethod = NodePgm_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodePgm", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodePgm_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEPGM_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEPGM_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodePgm_Class();
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
                            return NodePgm_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodePgm_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodePgm_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return NodePgm_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodePgm_ToDebugString)
                    return "ToDebugString";
                if (pData == NodePgm_ToJSON)
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
    
     ASTR_DATA *     NodePgm_ToJSON (
        NODEPGM_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
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
        ASTR_DATA      *pDesc = NodePgm_ToDebugString(this,4);
     @endcode 
     @param     this    NODEPGM object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodePgm_ToDebugString (
        NODEPGM_DATA      *this,
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
        if (!NodePgm_Validate(this)) {
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
                    NodePgm_getSize(this)
            );

        pWrkStr =   NodeBase_ToDebugString(NodePgm_getNodeBase(this), indent+3);
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
    
    
     ASTR_DATA *     NodePgm_ToString (
        NODEPGM_DATA      *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrk;
        
#ifdef NDEBUG
#else
        if (!NodePgm_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendA(pStr, "===> PGM:\n");
            if (this->pMain) {
                eRc = AStr_AppendPrint(pStr, "main: %s\n", AStrC_getData(this->pMain));
            }
            pWrk = NodeBase_ToString(NodePgm_getNodeBase(this));
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
    bool            NodePgm_Validate (
        NODEPGM_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODEPGM))
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


        if (!(obj_getSize(this) >= sizeof(NODEPGM_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


