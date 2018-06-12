// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   genWIN.c
 *	Generated 04/18/2018 09:07:15
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
#include        <genWIN_internal.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    GENWIN_DATA *     genWIN_Alloc(
        void
    )
    {
        GENWIN_DATA       *this;
        uint32_t        cbSize = sizeof(GENWIN_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    GENWIN_DATA *     genWIN_New(
        void
    )
    {
        GENWIN_DATA       *this;
        
        this = genWIN_Alloc( );
        if (this) {
            this = genWIN_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         genWIN_getLastError(
        GENWIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            genWIN_setLastError(
        GENWIN_DATA   *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //          L i b r a r y  I n c l u d e  P a t h
    //---------------------------------------------------------------
    
    ERESULT         genWIN_setLibIncludePath(
        GENWIN_DATA    *this,
        PATH_DATA *     (*pLibIncludePath)(
                                         GENWIN_DATA *,
                                         const char *,
                                         const char *,
                                         const char *
                                         )
    )
    {
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->pLibIncludePath = pLibIncludePath;
        
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          L i b r a r y  I n s t a l l e d  P a t h
    //---------------------------------------------------------------
    
    ERESULT         genWIN_setLibInstalledPath(
        GENWIN_DATA    *this,
        PATH_DATA *     (*pLibInstalledPath)(
                                         GENWIN_DATA *,
                                         const char *,
                                         const char *,
                                         const char *
                        )
    )
    {
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->pLibInstalledPath = pLibInstalledPath;
        
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          L i b r a r y  N a m e
    //---------------------------------------------------------------
    
    ERESULT         genWIN_setLibName(
        GENWIN_DATA    *this,
        ASTR_DATA *     (*pLibName)(
                                   GENWIN_DATA *,
                                   const char *,
                                   const char *
                                   )
    )
    {
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->pLibName = pLibName;
        
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        genWIN_getPriority(
        GENWIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        genWIN_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            genWIN_setPriority(
        GENWIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        genWIN_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        genWIN_getSize(
        GENWIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        genWIN_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * genWIN_getStr(
        GENWIN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        genWIN_setStr(
        GENWIN_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  genWIN_getSuperVtbl(
        GENWIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        genWIN_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = genWIN__Assign(this,pOther);
     @endcode 
     @param     this    GENWIN object pointer
     @param     pOther  a pointer to another GENWIN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         genWIN_Assign(
        GENWIN_DATA		*this,
        GENWIN_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !genWIN_Validate(pOther) ) {
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
        genWIN_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        genWIN_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return genWIN_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  L i b r a r y  I n c l u d e  P a t h
    //---------------------------------------------------------------
    
    /*!
     Library Include paths can be used for different purposes and
     can refer to different types of subdirectories. This requires
     dictionay entries for "LibIncludePath" and "LibIncludePrefix".
     */
    
    ASTR_DATA *     genWIN_CFlagsLibIncludePath(
        GENWIN_DATA   *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibIncludePath,
        const
        char            *pLibNamePrefix
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        PATH_DATA       *pLib = OBJ_NIL;
        ASTR_DATA       *pFullName =  OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ(
                this,
                "genWIN_CFlagsLibIncludePath(\"%s\", %s",
                pName
                );
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pFullName = this->pLibName(this, pName, pLibNamePrefix);
        if (pLib) {
            return OBJ_NIL;
        }
        pLib = this->pLibIncludePath(this, pName, pLibIncludePath, pLibNamePrefix);
        if (pLib) {
            return OBJ_NIL;
        }
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "CFLAGS = $(CFLAGS) /I%s\\src /I%s\\src\\$(SYS)\n",
                                 path_getData(pLib),
                                 path_getData(pLib)
                                 );
        
        // Return to caller.
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  L i b r a r y  O b j e c t  P a t h
    //---------------------------------------------------------------
    
    /*!
     Library Include paths can be used for different purposes and
     can refer to different types of subdirectories.
     */
    
    ASTR_DATA *     genWIN_CFlagsLibObjectPath(
        GENWIN_DATA    *this,
        const
        char            *pName              // Library Name
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        char            *pLibObjectPath = NULL;
        char            *pLibObjectPrefix = NULL;
        
        // Do initialization.
        TRC_OBJ(
                this,
                "genWIN_CFlagsLibObjectPath(\"%s\", %s",
                pName
                );
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pLibObjectPath   = szHash_FindA(this->pDict, "LibObjectPath");
        if (NULL == pLibObjectPath) {
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibObjectPath=\"%s\"", pLibObjectPath);
        pLibObjectPrefix = szHash_FindA(this->pDict, "LibObjectPrefix");
        TRC_OBJ(this, "\tLibObjectPrefix=\"%s\"", (pLibObjectPrefix ? pLibObjectPrefix : ""));
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "LIBS = $(LIBS) "
                                 "$(INSTALL_BASE)\\%s%s\\%s%s.lib\n",
                                 (pLibObjectPrefix ? pLibObjectPrefix : ""),
                                 pName,
                                 (pLibObjectPrefix ? pLibObjectPrefix : ""),
                                 pName
                                 );
        
        // Return to caller.
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return pStr;
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
    ERESULT         genWIN_Compare(
        GENWIN_DATA     *this,
        GENWIN_DATA     *pOther
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
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !genWIN_Validate(pOther) ) {
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
        
        this->eRc = eRc;
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        genWIN      *pCopy = genWIN_Copy(this);
     @endcode 
     @param     this    GENWIN object pointer
     @return    If successful, a GENWIN object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the GENWIN object.
     */
    GENWIN_DATA *     genWIN_Copy(
        GENWIN_DATA       *this
    )
    {
        GENWIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = genWIN_New( );
        if (pOther) {
            eRc = genWIN_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            genWIN_Dealloc(
        OBJ_ID          objId
    )
    {
        GENWIN_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((GENWIN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        genWIN_setStr(this, OBJ_NIL);

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

    ERESULT         genWIN_Disable(
        GENWIN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         genWIN_Enable(
        GENWIN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //      G e n e r a t e  T h e  E n t i r e  M a k e f i l e
    //---------------------------------------------------------------
    
    ERESULT         genWIN_GenMakefile(
        GENWIN_DATA     *this,
        NODE_DATA       *pNodes,
        SZHASH_DATA     *pDict,
        DATETIME_DATA   *pDateTime,
        FILE            *pOutput
    )
    {
        //ERESULT         eRc;
        NODE_DATA       *pNode;
        NODEARRAY_DATA  *pLibDeps = OBJ_NIL;
        NODEHASH_DATA   *pPrimaryHash = OBJ_NIL;
        NODEHASH_DATA   *pObjects = OBJ_NIL;
        NODEHASH_DATA   *pPrograms = OBJ_NIL;
        NODEARRAY_DATA  *pRoutines = OBJ_NIL;
        NODEHASH_DATA   *pTests = OBJ_NIL;
        //NODEHASH_DATA   *pMacosx = OBJ_NIL;
        //NODEHASH_DATA   *pWin32 = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        //DATETIME_DATA   *pDateTime = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pNodes) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (OBJ_NIL == pDict) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pOutput) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        this->pDict = pDict;
        this->pOutput = pOutput;
        
        pPrimaryHash = node_getData(pNodes);
        if (OBJ_NIL == pPrimaryHash) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        BREAK_FALSE((obj_IsKindOf(pPrimaryHash, OBJ_IDENT_NODEHASH)));
        pNode = nodeHash_FindA(pPrimaryHash, "name");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pName = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pName, OBJ_IDENT_ASTR)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "lib_deps");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pLibDeps = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pLibDeps, OBJ_IDENT_NODEARRAY)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "objects");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pObjects = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pObjects, OBJ_IDENT_NODEHASH)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "routines");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pRoutines = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pRoutines, OBJ_IDENT_NODEARRAY)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "programs");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pPrograms = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pPrograms, OBJ_IDENT_NODEARRAY)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "tests");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pTests = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pTests, OBJ_IDENT_NODEHASH)));
        }
#ifdef XYZZZY
        pNode = nodeHash_FindA(pPrimaryHash, "win32");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pMacosx = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pMacosx, OBJ_IDENT_NODEHASH)));
        }
#endif
        
#ifdef XYZZZY
        genOSX_GenInitial(this, pName, pLibDeps, pDateTime, pOutput);
        
        if (pObjects || pRoutines) {
            fprintf(pOutput, "\n");
            fprintf(pOutput, "OBJS =\n");
            if (pObjects) {
                genOSX_GenObjects(this, pObjects, pOutput);
            }
            if (pRoutines) {
                genOSX_GenRoutines(this, pRoutines, pOutput);
            }
        }
        
        genOSX_GenOSSpecific(this, pMacosx, pOutput);
        genOSX_GenLibrary(this, pOutput);
        if (pPrograms) {
            //genOSX_GenPrograms(this, pPrograms, pOutput);
        }
        genOSX_GenTests(this, pTests, pOutput);
        genOSX_GenFinal(this, pOutput);
#endif

        // Return to caller.
        genWIN_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  L i b r a r y  I n c l u d e  P a t h
    //---------------------------------------------------------------
    
    /*!
     Generate the Library Path given a name, the libraries super
     directory and an optional prefix.  The library super directory
     and optional library prefix name can either be supplied as a
     parameter of the method or they can be provided by the internal
     dictionary.  The dictionary will be accessed for "LibIncludePath"
     or "LibNamePrefix" if their respective method parameter is NULL.
     The diotionary entries for either can be over-ridden by passing
     "" instead of NULL.
     @param     this    object pointer
     @param     pName   library name
     @param     pLibIncludePath Optional directory which contains the
     library.  If NULL, then "LibIncludePath" must
     be present in the dictionary.
     @param     pLibNamePrefix  Optional prefix to the library name
     such as "lib".  If NULL, then "LibNamePrefix"
     will be used if present in the dictionary.
     */
    
    PATH_DATA *     genWIN_LibIncludePath(
        GENWIN_DATA    *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibIncludePath,
        const
        char            *pLibNamePrefix
    )
    {
        ERESULT         eRc;
        PATH_DATA       *pPath =  OBJ_NIL;
        ASTR_DATA       *pFullName = OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ(
                this,
                "genWIN_LibIncludePath(\"%s\", %s",
                pName
                );
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pFullName = this->pLibName(this, pName, pLibNamePrefix);
        if ( OBJ_NIL == pFullName) {
            genWIN_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibName=\"%s\"", AStr_getData(pFullName));
        if ((OBJ_NIL == pLibIncludePath) && this->pDict) {
            pLibIncludePath = szHash_FindA(this->pDict, "LibIncludePath");
        }
        TRC_OBJ(this, "\tLibIncludePath=\"%s\"", (pLibIncludePath ? pLibIncludePath : ""));
        
        if (pLibIncludePath) {
            pPath = path_NewA(pLibIncludePath);
            if (OBJ_NIL == pPath) {
                genWIN_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                genWIN_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
        genWIN_setLastError(this, eRc);
        return pPath;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  L i b r a r y  I n s t a l l e d  P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *     genWIN_LibInstalledPath(
        GENWIN_DATA    *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibInstalledPath,
        const
        char            *pLibNamePrefix
    )
    {
        ERESULT         eRc;
        PATH_DATA       *pPath =  OBJ_NIL;
        ASTR_DATA       *pFullName = OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ(
                this,
                "genBase_LibInstalledPath(\"%s\", %s",
                pName
                );
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pFullName = this->pLibName(this, pName, pLibNamePrefix);
        if ( OBJ_NIL == pFullName) {
            genWIN_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibName=\"%s\"", AStr_getData(pFullName));
        if ((OBJ_NIL == pLibInstalledPath) && this->pDict) {
            pLibInstalledPath = szHash_FindA(this->pDict, "LibInstalledPath");
        }
        TRC_OBJ(this, "\tLibInstalledPath=\"%s\"", (pLibInstalledPath ? pLibInstalledPath : ""));
        
        if (pLibInstalledPath) {
            pPath = path_NewA(pLibInstalledPath);
            if (OBJ_NIL == pPath) {
                genWIN_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                genWIN_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
        genWIN_setLastError(this, eRc);
        return pPath;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  t h e  f u l l  L i b r a r y  N a m e
    //---------------------------------------------------------------
    
    ASTR_DATA *     genWIN_LibName(
        GENWIN_DATA    *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibNamePrefix
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pFullName = OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ(this, "genWIN_LibName(\"%s\", %s", pName);
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        if ((OBJ_NIL == pLibNamePrefix) && this->pDict) {
            pLibNamePrefix = szHash_FindA(this->pDict, "LibNamePrefix");
        }
        TRC_OBJ(this, "\tLibNamePrefix=\"%s\"", (pLibNamePrefix ? pLibNamePrefix : ""));
        
        if (pLibNamePrefix) {
            pFullName = AStr_NewA(pLibNamePrefix);
            if (OBJ_NIL == pFullName) {
                genWIN_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
            eRc = AStr_AppendA(pFullName, pName);
        }
        else {
            pFullName = AStr_NewA(pName);
            if (OBJ_NIL == pFullName) {
                genWIN_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
        }
        
        // Return to caller.
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return pFullName;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    GENWIN_DATA *   genWIN_Init(
        GENWIN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(GENWIN_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, MAIN_IDENT_GENWIN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_GENWIN);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&genWIN_Vtbl);
        
        genWIN_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "genWIN::offsetof(eRc) = %lu\n", offsetof(GENWIN_DATA,eRc));
        fprintf(stderr, "genWIN::sizeof(GENWIN_DATA) = %lu\n", sizeof(GENWIN_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(GENWIN_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         genWIN_IsEnabled(
        GENWIN_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            genWIN_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        genWIN_setLastError(this, ERESULT_SUCCESS_FALSE);
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
        void        *pMethod = genWIN_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "genWIN", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          genWIN_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        GENWIN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)genWIN_Class();
                break;
                
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

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return genWIN_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return genWIN_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return genWIN_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return genWIN_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == genWIN_ToDebugString)
                    return "ToDebugString";
                if (pData == genWIN_ToJSON)
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
        ASTR_DATA      *pDesc = genWIN_ToDebugString(this,4);
     @endcode 
     @param     this    GENWIN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     genWIN_ToDebugString(
        GENWIN_DATA      *this,
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
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = genWIN_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    genWIN_getSize(this)
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
        
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     genWIN_ToJSON(
        GENWIN_DATA      *this
    )
    {
        ERESULT         eRc;
//        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{\"objectType\":\"%s\"",
                    pInfo->pClassName
                );
        
        AStr_AppendA(pStr, "}\n");
        
        genWIN_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            genWIN_Validate(
        GENWIN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, MAIN_IDENT_GENWIN) )
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


        if( !(obj_getSize(this) >= sizeof(GENWIN_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


