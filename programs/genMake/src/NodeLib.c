// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeLib.c
 *	Generated 11/03/2019 08:12:07
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
#include        <NodeLib_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            NodeLib_task_body (
        void            *pData
    )
    {
        //NODELIB_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODELIB_DATA *  NodeLib_Alloc (
        void
    )
    {
        NODELIB_DATA    *this;
        uint32_t        cbSize = sizeof(NODELIB_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODELIB_DATA *  NodeLib_New (
        void
    )
    {
        NODELIB_DATA    *this;
        
        this = NodeLib_Alloc( );
        if (this) {
            this = NodeLib_Init(this);
        } 
        return this;
    }



    ERESULT_DATA *  NodeLib_Parse (
        NODE_DATA       *pNode,
        NODELIB_DATA    **ppBase
    )
    {
        ERESULT_DATA    *pErr = OBJ_NIL;
        NODEHASH_DATA   *pHash;
        NODELIB_DATA    *pLib;

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
        pLib = NodeLib_New();
        if (OBJ_NIL == pLib) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
            return pErr;
        }
        *ppBase = OBJ_NIL;

        pHash = JsonIn_CheckNodeForHash(pNode);
        if (pHash) {
            // Ok, we have a hash, so there might a lot to parse here.

            // Scan off the base parameters.
            pErr = NodeBase_Parse(pNode, (NODEBASE_DATA **)&pLib);
            if (pErr) {
                DEBUG_BREAK();
                obj_Release(pLib);
                return pErr;
            }
            pErr = NodeBase_AddPrefixHdrsA((NODEBASE_DATA *)pLib, "$(SRCDIR)/");
            if (pErr) {
                DEBUG_BREAK();
                obj_Release(pLib);
                return pErr;
            }

            *ppBase = pLib;
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

    ASTRCARRAY_DATA * NodeLib_getArches (
        NODELIB_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getArches(NodeLib_getNodeBase(this));
    }


    bool            NodeLib_setArches (
        NODELIB_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setArches(NodeLib_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        D e p s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeLib_getDeps (
        NODELIB_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getDeps(NodeLib_getNodeBase(this));
    }


    bool            NodeLib_setDeps (
        NODELIB_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setDeps(NodeLib_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        H d r s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeLib_getHdrs (
        NODELIB_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getHdrs(NodeLib_getNodeBase(this));
    }


    bool            NodeLib_setHdrs (
        NODELIB_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setHdrs(NodeLib_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                        N a m e
    //---------------------------------------------------------------

    ASTRC_DATA *    NodeLib_getName (
        NODELIB_DATA    *this
    )
    {

        // Validate the input parameters.
    #ifdef NDEBUG
    #else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
    #endif

        return NodeBase_getName(NodeLib_getNodeBase(this));
    }


    bool            NodeLib_setName (
        NODELIB_DATA    *this,
        ASTRC_DATA      *pValue
    )
    {
    #ifdef NDEBUG
    #else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        return NodeBase_setName(NodeLib_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                           N o d e
    //---------------------------------------------------------------

    NODE_DATA *     NodeLib_getNode (
        NODELIB_DATA    *this
    )
    {

        // Validate the input parameters.
    #ifdef NDEBUG
    #else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
    #endif

        return (NODE_DATA *)this;
    }


    //---------------------------------------------------------------
    //                       N o d e  B a s e
    //---------------------------------------------------------------

    NODEBASE_DATA *     NodeLib_getNodeBase (
        NODELIB_DATA    *this
    )
    {

        // Validate the input parameters.
    #ifdef NDEBUG
    #else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
    #endif

        return (NODEBASE_DATA *)this;
    }


    //---------------------------------------------------------------
    //                        O S
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeLib_getOSs (
        NODELIB_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getOSs(NodeLib_getNodeBase(this));
    }


    bool            NodeLib_setOSs (
        NODELIB_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setOSs(NodeLib_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        NodeLib_getPriority (
        NODELIB_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NodeLib_setPriority (
        NODELIB_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
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
    
    uint32_t        NodeLib_getSize (
        NODELIB_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S r c s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * NodeLib_getSrcs (
        NODELIB_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return NodeBase_getSrcs(NodeLib_getNodeBase(this));
    }


    bool            NodeLib_setSrcs (
        NODELIB_DATA    *this,
        ASTRCARRAY_DATA *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return NodeBase_setSrcs(NodeLib_getNodeBase(this), pValue);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodeLib_getSuperVtbl (
        NODELIB_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
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
        ERESULT eRc = NodeLib_Assign(this,pOther);
     @endcode 
     @param     this    NODELIB object pointer
     @param     pOther  a pointer to another NODELIB object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeLib_Assign (
        NODELIB_DATA		*this,
        NODELIB_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeLib_Validate(pOther)) {
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
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        NodeLib      *pCopy = NodeLib_Copy(this);
     @endcode 
     @param     this    NODELIB object pointer
     @return    If successful, a NODELIB object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODELIB_DATA *     NodeLib_Copy (
        NODELIB_DATA       *this
    )
    {
        NODELIB_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeLib_New( );
        if (pOther) {
            eRc = NodeLib_Assign(this, pOther);
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

    void            NodeLib_Dealloc (
        OBJ_ID          objId
    )
    {
        NODELIB_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODELIB_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeLib_Disable (
        NODELIB_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeLib_Validate(this)) {
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
    ERESULT         NodeLib_Enable (
        NODELIB_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeLib_Validate(this)) {
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

    ASTR_DATA *     NodeLib_GenMacBegin (
        NODELIB_DATA    *this,
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
        if (!NodeLib_Validate(this)) {
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
                     "# Generated file - Edits will be discarded by next file generation!\n");
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
        AStr_AppendPrint(pStr, "LIBNAM=lib%s\n", AStrC_getData(NodeLib_getName(this)));
        AStr_AppendA(pStr, "SYS=macos64\n");
        AStr_AppendA(pStr, "BUILD=./.build\nBASE_OBJ = $(BUILD)/$(LIBNAM)\n");
        AStr_AppendA(pStr, "SRCDIR = ./src\n");
        AStr_AppendA(pStr, "TEST_SRC = ./tests\n");
        AStr_AppendA(pStr, "INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n");
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
        pArrayC = NodeLib_getDeps(this);
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

        AStr_AppendA(pStr, "INSTALL_DIR = $(INSTALL_BASE)/$(LIBNAM)\n");
        AStr_AppendA(pStr, "LIBOBJ = $(BASE_OBJ)/$(SYS)\n");
        AStr_AppendA(pStr, "ifdef  NDEBUG\n");
        AStr_AppendA(pStr, "LIB_FILENAME=$(LIBNAM)R.a\n");
        AStr_AppendA(pStr, "OBJDIR = $(LIBOBJ)/o/r\n");
        AStr_AppendA(pStr, "else   #DEBUG\n");
        AStr_AppendA(pStr, "LIB_FILENAME=$(LIBNAM)D.a\n");
        AStr_AppendA(pStr, "OBJDIR = $(LIBOBJ)/o/d\n");
        AStr_AppendA(pStr, "endif  #NDEBUG\n");
        AStr_AppendA(pStr, "TEST_OBJ = $(OBJDIR)/obj\n");
        AStr_AppendA(pStr, "TEST_BIN = $(OBJDIR)/bin\n");
        AStr_AppendA(pStr, "LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)\n\n");
        
        AStr_AppendA(pStr, ".SUFFIXES:\n");
        AStr_AppendA(pStr, ".SUFFIXES: .asm .c .cpp .o\n\n");

        AStr_AppendPrint(pStr, "%s =\n\n", Dict_GetA(pDict, objsVarID));
        AStr_AppendPrint(pStr, "%s =\n\n", Dict_GetA(pDict, testsVarID));
        AStr_AppendA(pStr, "\n");

        // Return to caller.
        return pStr;
    }
    

    ASTR_DATA *     NodeLib_GenMacEnd (
        NODELIB_DATA    *this,
        DICT_DATA       *pDict
    )
    {
        ASTR_DATA       *pStr =  OBJ_NIL;

            // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
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

        AStr_AppendPrint(pStr, "\n\n$(LIB_PATH):  $(%s)\n",
                         Dict_GetA(pDict, objsVarID));
        AStr_AppendA(pStr, "\t-cd $(LIBOBJ) ; [ -d $(LIB_FILENAME) ]"
                        " && rm $(LIB_FILENAME)\n");
        AStr_AppendPrint(pStr, "\tar rc $(LIB_PATH) $(%s)\n\n\n",
                         Dict_GetA(pDict, objsVarID));

        AStr_AppendA(pStr, ".PHONY: all\n");
        AStr_AppendA(pStr, "all:  create_dirs $(LIB_PATH) check install\n\n\n");

        AStr_AppendA(pStr, ".PHONY: build\n");
        AStr_AppendA(pStr, "build:  create_dirs $(LIB_PATH)\n\n\n");

        AStr_AppendA(pStr, ".PHONY: check\n");
        AStr_AppendPrint(pStr, "check: $(%s)\n\n\n", Dict_GetA(pDict, testsVarID));
         
        AStr_AppendA(pStr, ".PHONY: clean\nclean:\n");
        AStr_AppendA(pStr, "\t-rm -fr $(BUILD)/$(LIBNAM)\n\n\n");

        AStr_AppendA(pStr, ".PHONY: create_dirs\n");
        AStr_AppendA(pStr, "create_dirs:\n");
        AStr_AppendPrint(pStr,
                         "\t-mkdir -p $(BUILD)\n"
                         "\t-mkdir -p $(TEST_OBJ)\n"
                         "\t-mkdir -p $(TEST_BIN)\n\n\n"
        );

        AStr_AppendA(pStr, ".PHONY: install\ninstall:\n");
        AStr_AppendA(pStr, "\t-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n");
        AStr_AppendA(pStr, "\t-cd $(INSTALL_BASE) ; "
                     "[ ! -d $(LIBNAM)/include ] && "
                     "mkdir -p $(LIBNAM)/include/$(SYS)\n");
        AStr_AppendA(pStr, "\tcp $(LIB_PATH) $(INSTALL_DIR)/$(LIBNAM).a\n");
        AStr_AppendA(pStr, "\tcp src/*.h $(INSTALL_DIR)/include/\n");
        AStr_AppendA(pStr, "\tif [ -d src/$(SYS) ]; then \\\n");
        AStr_AppendA(pStr, "\t\tcp src/$(SYS)/*.h $(INSTALL_DIR)/include/$(SYS)/; \\\n");
        AStr_AppendA(pStr, "\tfi\n\n\n");
        
        AStr_AppendA(pStr, ".PHONY: test\n");
        AStr_AppendPrint(pStr, "test: $(%s)\n\n\n", Dict_GetA(pDict, testsVarID));


        // Return to caller.
        return pStr;
    }


        
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODELIB_DATA *   NodeLib_Init (
        NODELIB_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODELIB_DATA);
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
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODELIB);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeLib_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "NodeLib::sizeof(NODELIB_DATA) = %lu\n", sizeof(NODELIB_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODELIB_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeLib_IsEnabled (
        NODELIB_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
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
        void        *pMethod = NodeLib_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeLib", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeLib_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODELIB_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODELIB_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeLib_Class();
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
                            return NodeLib_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeLib_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeLib_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return NodeLib_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeLib_ToDebugString)
                    return "ToDebugString";
                if (pData == NodeLib_ToJSON)
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
    
     ASTR_DATA *     NodeLib_ToJSON (
        NODELIB_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
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
        ASTR_DATA      *pDesc = NodeLib_ToDebugString(this,4);
     @endcode 
     @param     this    NODELIB object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeLib_ToDebugString (
        NODELIB_DATA      *this,
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
        if (!NodeLib_Validate(this)) {
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
                    NodeLib_getSize(this)
            );

        pWrkStr =   NodeBase_ToDebugString(NodeLib_getNodeBase(this), indent+3);
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
    
    
     ASTR_DATA *    NodeLib_ToString (
        NODELIB_DATA    *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrk;
        
#ifdef NDEBUG
#else
        if (!NodeLib_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendA(pStr, "===> LIB:\n");
            pWrk = NodeBase_ToString(NodeLib_getNodeBase(this));
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
    bool            NodeLib_Validate (
        NODELIB_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODELIB))
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


        if (!(obj_getSize(this) >= sizeof(NODELIB_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


