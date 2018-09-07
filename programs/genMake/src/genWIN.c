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
        NODEHASH_DATA   *pDict
    )
    {
        GENWIN_DATA     *this;
        ERESULT         eRc;
        
        this = genWIN_Alloc( );
        if (this) {
            this = genWIN_Init(this);
            if (this) {
                eRc = genBase_setDict((GENBASE_DATA *)this, pDict);
            }
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

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
        obj_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        obj_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return obj_getLastError(this);
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
        
        pOther = genWIN_New(genBase_getDict((GENBASE_DATA *)this));
        if (pOther) {
            eRc = genWIN_Assign(this, pOther);
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
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //          G e n e r a t e  C o m p i l a t i o n
    //---------------------------------------------------------------
    
    ASTR_DATA *     genWIN_GenCompileJson(
        GENWIN_DATA     *this,
        const
        char            *pNameA,            // Routine File Name including extension
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps           // Object Dependencies (ie files to be
                                            // included in the compile statement, file
                                            // extension must match that of pName above)
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pName =  OBJ_NIL;
        ASTR_DATA       *pStr =  OBJ_NIL;
        ASTR_DATA       *pWrkStr = OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ( this, "genWIN_GenCompileObject(\"%s\")", pName);
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            //genOSX_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
        if(NULL == pNameA) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        pName = AStr_NewA(pNameA);
        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }
        AStr_AppendA(pName, "_JSON.c");
        
        
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            obj_Release(pName);
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
        
        pWrkStr =   genWIN_GenCompileRoutine(
                                             this,
                                             AStr_getData(pName),
                                             pSrcDir,
                                             pObjDir,
                                             pObjVar,
                                             NULL,
                                             pSrcDeps,
                                             pObjDeps,
                                             true,
                                             false
                                             );
        if (pWrkStr) {
            eRc = AStr_Append(pStr, pWrkStr);
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
        }
        
        // Return to caller.
        obj_Release(pName);
        return pStr;
    }
    
    
    ASTR_DATA *     genWIN_GenCompileObject(
        GENWIN_DATA     *this,
        const
        char            *pName,             // Object Name
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps           // Object Dependencies (ie files to be
                                            // included in the compile statement, file
                                            // extension must match that of pName above)
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        ASTR_DATA       *pWrkStr = OBJ_NIL;
        ASTR_DATA       *pFileName = OBJ_NIL;
        ASTR_DATA       *pFileExt = OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ( this, "genWIN_CompileObject(\"%s\")", pName);
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            //genOSX_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
        if(NULL == pName) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
        
        pFileName = AStr_NewA(pName);
        if (OBJ_NIL == pFileName) {
            DEBUG_BREAK();
            obj_Release(pStr);
            return OBJ_NIL;
        }
        
        pFileExt = AStr_Copy(pFileName);
        if (OBJ_NIL == pFileExt) {
            DEBUG_BREAK();
            obj_Release(pFileName);
            obj_Release(pStr);
            return OBJ_NIL;
        }
        eRc = AStr_AppendA(pFileExt, "_object.c");
        pWrkStr =   genWIN_GenCompileRoutine(
                                             this,
                                             AStr_getData(pFileExt),
                                             pSrcDir,
                                             pObjDir,
                                             pObjVar,
                                             NULL,
                                             NULL,
                                             NULL,
                                             true,
                                             false
                                             );
        if (pWrkStr) {
            eRc = AStr_Append(pStr, pWrkStr);
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
        }
        obj_Release(pFileExt);
        pFileExt = OBJ_NIL;
        
        eRc = AStr_AppendA(pFileName, ".c");
        pWrkStr =   genWIN_GenCompileRoutine(
                                             this,
                                             AStr_getData(pFileName),
                                             pSrcDir,
                                             pObjDir,
                                             pObjVar,
                                             NULL,
                                             pSrcDeps,
                                             pObjDeps,
                                             true,
                                             false
                                             );
        if (pWrkStr) {
            eRc = AStr_Append(pStr, pWrkStr);
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
        }
        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        
        
        // Return to caller.
        return pStr;
    }
    
    
    ASTR_DATA *     genWIN_GenCompileRoutine(
        GENWIN_DATA    *this,
        const
        char            *pName,             // Routine File Name including extension
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,           // If present, adds another Make Flag
        // variable in addition to CFLAGS
        // (Default - none)
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps,          // Object Dependencies (ie files to be
        // included in the compile statement, file
        // extension must match that of pName above)
        bool            fCO,                // true == compile only
        bool            fExec               // true == execute the newly compiled
                                            //          program
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pFileName = OBJ_NIL;
        ASTR_DATA       *pFileExt = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        
        // Do initialization.
        TRC_OBJ( this, "genWIN_CompileRoutine(\"%s\")", pName);
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        if (NULL == pSrcDir) {
            pSrcDir = "SRCDIR";
        }
        if (NULL == pObjDir) {
            pObjDir = "OBJDIR";
        }
        if (NULL == pObjVar) {
            pObjVar = "OBJS";
        }
        pPath = path_NewA(pName);
        if (OBJ_NIL == pPath) {
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
        eRc = path_SplitFile(pPath, &pFileName, &pFileExt);
        BREAK_NULL(pFileName);
        BREAK_NULL(pFileExt);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            obj_Release(pFileExt);
            pFileExt = OBJ_NIL;
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
            obj_Release(pPath);
            pPath = OBJ_NIL;
            obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "%s = $(%s) $(%s)/%s.obj\n\n",
                                 pObjVar,
                                 pObjVar,
                                 pObjDir,
                                 AStr_getData(pFileName)
                                 );
        if ((AStr_CompareA(pFileExt, "c") == ERESULT_SUCCESS_EQUAL)
            || (AStr_CompareA(pFileExt, "C") == ERESULT_SUCCESS_EQUAL)) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.obj: $(%s)/%s ",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            if (pSrcDeps) {
                iMax = nodeArray_getSize(pSrcDeps);
                for (i=0; i<iMax; ++i) {
                    NODE_DATA           *pNode;
                    ASTR_DATA           *pWrkStr;
                    pNode = nodeArray_Get(pSrcDeps, (i + 1));
                    if (pNode) {
                        pWrkStr = node_getData(pNode);
                        if (pWrkStr) {
                            eRc =   AStr_AppendPrint(
                                                     pStr,
                                                     "$(%s)/%s ",
                                                     pSrcDir,
                                                     AStr_getData(pWrkStr)
                                                     );
                        }
                    }
                }
            }
            eRc =   AStr_AppendA(pStr, "\n");
            if (pFlgVar) {
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "\t$(CC) $(CFLAGS) %s $(%s) /out:$(%s)/$(@F) $< ",
                                         (fCO ? "/c" : ""),
                                         pFlgVar,
                                         pObjDir
                                         );
            }
            else {
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "\t$(CC) $(CFLAGS) %s /out:$(%s)/$(@F) $< ",
                                         (fCO ? "/c" : ""),
                                         pObjDir
                                         );
            }
            if (pObjDeps) {
                iMax = nodeArray_getSize(pObjDeps);
                for (i=0; i<iMax; ++i) {
                    NODE_DATA           *pNode;
                    const
                    char                *pStrA;
                    pNode = nodeArray_Get(pObjDeps, (i + 1));
                    if (pNode) {
                        pStrA = AStr_getData((ASTR_DATA *)node_getData(pNode));
                        if (pStrA) {
                            eRc =   AStr_AppendPrint(
                                                     pStr,
                                                     "$(%s)/%s ",
                                                     pSrcDir,
                                                     pStrA
                                                     );
                        }
                    }
                }
            }
        }
        else if ((AStr_CompareA(pFileExt, "asm") == ERESULT_SUCCESS_EQUAL)
                 || (AStr_CompareA(pFileExt, "ASM") == ERESULT_SUCCESS_EQUAL)) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.obj: $(%s)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(AS) $(AFLAGS) %s -o $(%s)/$(@F) $<",
                                     (fCO ? "/c" : ""),
                                     pObjDir
                                     );
        }
        else if ((AStr_CompareA(pFileExt, "s") == ERESULT_SUCCESS_EQUAL)
                 || (AStr_CompareA(pFileExt, "S") == ERESULT_SUCCESS_EQUAL)) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.obj: $(%s)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(AS) $(AFLAGS) -o $(%s)/$(@F) $<",
                                     pObjDir
                                     );
        }
        else if ((AStr_CompareA(pFileExt, "cpp") == ERESULT_SUCCESS_EQUAL)
                 || (AStr_CompareA(pFileExt, "CPP") == ERESULT_SUCCESS_EQUAL)) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.obj: $(SRCDIR)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(CC) $(CFLAGS) %s -o $(%s)/$(@F) $<",
                                     (fCO ? "/c" : ""),
                                     pObjDir
                                     );
        }
        else {
            obj_Release(pFileExt);
            pFileExt = OBJ_NIL;
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
            obj_Release(pPath);
            pPath = OBJ_NIL;
            obj_Release(pStr);
            pStr = OBJ_NIL;
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
        if (!fCO && fExec) {
            eRc = AStr_AppendPrint(pStr, "\n\t$(%s)/$(@F)\n\n", pObjDir);
        }
        else {
            eRc = AStr_AppendA(pStr, "\n\n");
        }
        
        // Return to caller.
        obj_Release(pFileExt);
        pFileExt = OBJ_NIL;
        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    ASTR_DATA *     genWIN_GenCompileTest(
        GENWIN_DATA     *this,
        const
        char            *pNameA,            // Routine File Name including extension
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps           // Object Dependencies (ie files to be
                                            // included in the compile statement, file
                                            // extension must match that of pName above)
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        
        // Do initialization.
        TRC_OBJ(this, "genWIN_CompileObject(\"%s\")", pName);
#ifdef NDEBUG
#else
        if( !genWIN_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
        if(NULL == pNameA) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
        if (NULL == pSrcDir) {
            pSrcDir = "TEST_SRC";
        }
        if (NULL == pObjDir) {
            pObjDir = "TEST_OBJ";
        }
        if (NULL == pObjVar) {
            pObjVar = "TESTS";
        }
        pName = AStr_NewA("test_");
        if (pName) {
            eRc = AStr_AppendA(pName, pNameA);
        }
        else {
            return OBJ_NIL;
        }
        
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "%s = $(%s) %s\n\n",
                                 pObjVar,
                                 pObjVar,
                                 AStr_getData(pName)
                                 );
        
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "%s: $(%s)/%s.c ",
                                 AStr_getData(pName),
                                 pSrcDir,
                                 AStr_getData(pName)
                                 );
        if (pSrcDeps) {
            iMax = nodeArray_getSize(pSrcDeps);
            for (i=0; i<iMax; ++i) {
                NODE_DATA           *pNode;
                ASTR_DATA           *pWrkStr;
                pNode = nodeArray_Get(pSrcDeps, (i + 1));
                if (pNode) {
                    pWrkStr = node_getData(pNode);
                    if (pWrkStr) {
                        eRc =   AStr_AppendPrint(
                                                 pStr,
                                                 "$(%s)/%s ",
                                                 pSrcDir,
                                                 AStr_getData(pWrkStr)
                                                 );
                    }
                }
            }
        }
        eRc =   AStr_AppendA(pStr, "\n");
        
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "\t$(CC) $(CFLAGS) $(TEST_FLGS) /out:$(%s)/$(@F) $< ",
                                 pObjDir
                );
        if (pObjDeps) {
            iMax = nodeArray_getSize(pObjDeps);
            for (i=0; i<iMax; ++i) {
                NODE_DATA           *pNode;
                const
                char                *pStrA;
                pNode = nodeArray_Get(pObjDeps, (i + 1));
                if (pNode) {
                    pStrA = AStr_getData((ASTR_DATA *)node_getData(pNode));
                    if (pStrA) {
                        eRc =   AStr_AppendPrint(
                                                 pStr,
                                                 "$(%s)/%s ",
                                                 pSrcDir,
                                                 pStrA
                                                 );
                    }
                }
            }
        }
        eRc = AStr_AppendA(pStr, "\n");
        
        eRc = AStr_AppendPrint(pStr, "\t$(%s)/$(@F)\n\n", pObjDir);
        
        // Return to caller.
        obj_Release(pName);
        pName = OBJ_NIL;
        return pStr;
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
            obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
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
                obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
        obj_setLastError(this, eRc);
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
            obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
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
                obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
        obj_setLastError(this, eRc);
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
                obj_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
            eRc = AStr_AppendA(pFullName, pName);
        }
        else {
            pFullName = AStr_NewA(pName);
            if (OBJ_NIL == pFullName) {
                obj_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
        }
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
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

        this = (OBJ_ID)genBase_Init((GENBASE_DATA *)this);  // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, MAIN_IDENT_GENWIN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, MAIN_IDENT_GENWIN);       // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&genWIN_Vtbl);
        
        obj_setLastError(this, ERESULT_GENERAL_FAILURE);
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
        //fprintf(stderr, "genWIN::sizeof(GENWIN_DATA) = %lu\n", sizeof(GENWIN_DATA));
#endif
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
        GENWIN_DATA     *this,
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
              
        pInfo = obj_getInfo(this);
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
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
            //this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        //this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


