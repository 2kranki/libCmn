// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   genOSX.c
 *	Generated 04/18/2018 09:07:03
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
#include        <genOSX_internal.h>
#include        <fbso.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //  G e n e r a t e  O b j e c t  C o m p i l a t i o n
    //---------------------------------------------------------------
    
    ASTR_DATA *     genOSX_CompileObjectStr(
        GENOSX_DATA     *this,
        const
        char            *pName,             // Object Class Name
        const
        char            *pSrcDir,
        const
        char            *pObjDir
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ(
                this,
                "genOSX_CompileObject(\"%s\", %s",
                pName
                );
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        if (NULL == pSrcDir) {
            pSrcDir = "SRCDIR";
        }
        if (NULL == pObjDir) {
            pObjDir = "OBJDIR";
        }
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        
        if (0 == strcmp(pObjDir, "OBJDIR")) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "OBJS += $(OBJDIR)/%s.o $(OBJDIR)/%s_object.o\n\n",
                                     pName,
                                     pName
                    );
        }
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "$(%s)/%s.o: $(%s)/%s.c\n\n",
                                 pObjDir,
                                 pName,
                                 pSrcDir,
                                 pName
                );
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n",
                                 pObjDir
                );
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "$(%s)/%s_object.o: $(%s)/%s_object.c\n",
                                 pObjDir,
                                 pName,
                                 pSrcDir,
                                 pName
                );
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n\n",
                                 pObjDir
                );
        
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  R o u t i n e  C o m p i l a t i o n
    //---------------------------------------------------------------
    
    ASTR_DATA *     genOSX_CompileRoutineStr(
        GENOSX_DATA     *this,
        const
        char            *pName,             // Object Class Name
        const
        char            *pSrcDir,
        const
        char            *pObjDir
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pFileName = OBJ_NIL;
        ASTR_DATA       *pFileExt = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            //genBase_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
         if (NULL == pSrcDir) {
            pSrcDir = "SRCDIR";
        }
        if (NULL == pObjDir) {
            pObjDir = "OBJDIR";
        }
        pPath = path_NewA(pName);
        if (OBJ_NIL == pPath) {
            genOSX_setLastError(this, ERESULT_INVALID_PARAMETER);
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
            genOSX_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        TRC_OBJ(this, "genOSX_CompileRoutine(\"%s\", %s", pName);

        if (0 == strcmp(pObjDir, "OBJDIR")) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "OBJS += $(%s)/%s.o\n\n",
                                     pObjDir,
                                     AStr_getData(pFileName)
                                     );
        }
        if (AStr_CompareA(pFileExt, "c") == ERESULT_SUCCESS_EQUAL) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.o: $(%s)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n",
                                     pObjDir
                                     );
        }
        else if (AStr_CompareA(pFileExt, "asm") == ERESULT_SUCCESS_EQUAL) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.o: $(%s)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(AS) $(AFLAGS) -c -o $(%s)/$(@F) $<\n\n",
                                     pObjDir
                                     );
        }
        else if (AStr_CompareA(pFileExt, "s") == ERESULT_SUCCESS_EQUAL) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.o: $(%s)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(AS) $(AFLAGS) -o $(%s)/$(@F) $<\n\n",
                                     pObjDir
                                     );
        }
        else if (AStr_CompareA(pFileExt, "cpp") == ERESULT_SUCCESS_EQUAL) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.o: $(SRCDIR)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n",
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
            genOSX_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
        
    // Return to caller.
    obj_Release(pFileExt);
    pFileExt = OBJ_NIL;
    obj_Release(pFileName);
    pFileName = OBJ_NIL;
    obj_Release(pPath);
    pPath = OBJ_NIL;
    genOSX_setLastError(this, ERESULT_SUCCESS);
    return pStr;
}






    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    GENOSX_DATA *     genOSX_Alloc(
        void
    )
    {
        GENOSX_DATA     *this;
        uint32_t        cbSize = sizeof(GENOSX_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    GENOSX_DATA *     genOSX_New(
        NODEHASH_DATA   *pDict
    )
    {
        GENOSX_DATA     *this;
        ERESULT         eRc;
        
        this = genOSX_Alloc( );
        if (this) {
            this = genOSX_Init(this);
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
    //                  D i c t i o n a r y
    //---------------------------------------------------------------
    
    NODEHASH_DATA * genOSX_getDict(
        GENOSX_DATA     *this
    )
    {
        NODEHASH_DATA   *pDict;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pDict = genBase_getDict((GENBASE_DATA *)this);

        genOSX_setLastError(this, genBase_getLastError((GENBASE_DATA *)this));
        return pDict;
    }
    
    
    bool            genOSX_setDict(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pValue
    )
    {
        bool            iRc;
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        iRc = genBase_setDict((GENBASE_DATA *)this, pValue);
        
        genOSX_setLastError(this, genBase_getLastError((GENBASE_DATA *)this));
        return iRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         genOSX_getLastError(
        GENOSX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            genOSX_setLastError(
        GENOSX_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
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
    
    ERESULT         genOSX_setLibIncludePath(
        GENOSX_DATA     *this,
        PATH_DATA *     (*pLibIncludePath)(
                                         GENOSX_DATA *,
                                         const char *,
                                         const char *,
                                         const char *
                        )
    )
    {
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->pLibIncludePath = pLibIncludePath;
        
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          L i b r a r y  I n s t a l l e d  P a t h
    //---------------------------------------------------------------
    
    ERESULT         genOSX_setLibInstalledPath(
        GENOSX_DATA     *this,
        PATH_DATA *     (*pLibInstalledPath)(
                                         GENOSX_DATA *,
                                         const char *,
                                         const char *,
                                         const char *
                        )
    )
    {
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->pLibInstalledPath = pLibInstalledPath;
        
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          L i b r a r y  N a m e
    //---------------------------------------------------------------
    
    ERESULT         genOSX_setLibName(
        GENOSX_DATA     *this,
        ASTR_DATA *     (*pLibName)(
                               GENOSX_DATA *,
                               const char *,
                               const char *
                        )
    )
    {
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->pLibName = pLibName;
        
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------
    
    ASTR_DATA * genOSX_getName(
        GENOSX_DATA *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return this->pName;
    }
    
    
    bool        genOSX_setName(
        GENOSX_DATA *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;
        
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        genOSX_getPriority(
        GENOSX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        genOSX_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            genOSX_setPriority(
        GENOSX_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        genOSX_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        genOSX_getSize(
        GENOSX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        genOSX_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  genOSX_getSuperVtbl(
        GENOSX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        genOSX_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = genOSX__Assign(this,pOther);
     @endcode 
     @param     this    GENOSX object pointer
     @param     pOther  a pointer to another GENOSX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         genOSX_Assign(
        GENOSX_DATA		*this,
        GENOSX_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !genOSX_Validate(pOther) ) {
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
        genOSX_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        genOSX_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return genOSX_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  L i b r a r y  I n c l u d e  P a t h
    //---------------------------------------------------------------
    
    /*!
     Library Include paths can be used for different purposes and
     can refer to different types of subdirectories. This requires
     dictionay entries for "LibIncludePath" and "LibIncludePrefix".
     */
    
    ASTR_DATA *     genOSX_CFlagsLibIncludePath(
        GENOSX_DATA     *this,
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
        TRC_OBJ(this, "genOSX_CFlagsLibIncludePath(\"%s\", %s", pName);
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
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
                                 "CFLAGS += -I%s/src -I%s/src/$(SYS)\n",
                                 path_getData(pLib),
                                 path_getData(pLib)
                );
                
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  L i b r a r y  O b j e c t  P a t h
    //---------------------------------------------------------------
    
    /*!
     Library Include paths can be used for different purposes and
     can refer to different types of subdirectories.
     */
    
    ASTR_DATA *     genOSX_CFlagsLibObjectPath(
        GENOSX_DATA     *this,
        const
        char            *pName              // Library Name
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        NODE_DATA       *pLibObjectPath = OBJ_NIL;
        NODE_DATA       *pLibObjectPrefix = OBJ_NIL;
        OBJ_ID          pPath = OBJ_NIL;
        OBJ_ID          pPrefix = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pLibObjectPath =    nodeHash_FindA(
                                genBase_getDict((GENBASE_DATA *)this),
                                "LibObjectPath"
                            );
        if (NULL == pLibObjectPath) {
            return OBJ_NIL;
        }
        pLibObjectPrefix =  nodeHash_FindA(
                                genBase_getDict((GENBASE_DATA *)this),
                                "LibObjectPrefix"
                            );
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        
        //TODO: Fixme
#ifdef XYZZY
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "CFLAGS_LIBS += -l%s%s -L%s/%s%s\n",
                                 pLibObjectPrefix,
                                 pName,
                                 pLibObjectPath,
                                 (pLibObjectPrefix ? pLibObjectPrefix : ""),
                                 pName
                );
#endif
        
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
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
    ERESULT         genOSX_Compare(
        GENOSX_DATA     *this,
        GENOSX_DATA     *pOther
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
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !genOSX_Validate(pOther) ) {
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
    //  G e n e r a t e  O b j e c t  C o m p i l a t i o n
    //---------------------------------------------------------------
    
    ERESULT         genOSX_CompileObject(
        GENOSX_DATA     *this,
        const
        char            *pName              // Object Class Name
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        const
        char            *pSrcDir;
        const
        char            *pObjDir;
        const
        char            *pObjVar;

        // Do initialization.
        TRC_OBJ(this, "genOSX_CompileObject(\"%s\", %s, %s)", pName, pSrcDir, pObjDir);
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =   textOut_Print(
                           genBase_getOutput((GENBASE_DATA *)this),
                           "%s += $(%S)/%s.o $(%s)/%s_object.o\n\n",
                           pObjVar,
                           pObjDir,
                           pName,
                           pObjDir,
                           pName
                );
#ifdef XYZZY
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "$(%s)/%s.o: $(%s)/%s.c\n\n",
                                 pObjDir,
                                 pName,
                                 pSrcDir,
                                 pName
                );
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n",
                                 pObjDir
                );
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "$(%s)/%s_object.o: $(%s)/%s_object.c\n",
                                 pObjDir,
                                 pName,
                                 pSrcDir,
                                 pName
                );
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n\n",
                                 pObjDir
                );
#endif
        
        // Return to caller.
        genOSX_setLastError(this, eRc);
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  R o u t i n e  C o m p i l a t i o n
    //---------------------------------------------------------------
    
    ASTR_DATA *     genOSX_CompileRoutine(
        GENOSX_DATA    *this,
        const
        char            *pName,                 // Routine File Name
        const
        char            *pSrcDir,
        const
        char            *pObjDir
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pFileName = OBJ_NIL;
        ASTR_DATA       *pFileExt = OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ( this, "genBase_CompileRoutine(\"%s\", %s, %s)", pName, pSrcDir, pObjDir);
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            //genOSX_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        if (NULL == pSrcDir) {
            pSrcDir = "SRCDIR";
        }
        if (NULL == pObjDir) {
            pObjDir = "OBJDIR";
        }
        pPath = path_NewA(pName);
        if (OBJ_NIL == pStr) {
            genOSX_setLastError(this, ERESULT_INVALID_PARAMETER);
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
            genOSX_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "OBJS += $(%s)/%s.o\n\n",
                                 pObjDir,
                                 AStr_getData(pFileName)
                );
        if (AStr_CompareA(pFileExt, "c") == ERESULT_SUCCESS_EQUAL) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.o: $(%s)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n",
                                     pObjDir
                                     );
        }
        else if (AStr_CompareA(pFileExt, "asm") == ERESULT_SUCCESS_EQUAL) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.o: $(%s)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(AS) $(AFLAGS) -c -o $(%s)/$(@F) $<\n\n",
                                     pObjDir
                                     );
        }
        else if (AStr_CompareA(pFileExt, "s") == ERESULT_SUCCESS_EQUAL) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.o: $(%s)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(AS) $(AFLAGS) -o $(%s)/$(@F) $<\n\n",
                                     pObjDir
                                     );
        }
        else if (AStr_CompareA(pFileExt, "cpp") == ERESULT_SUCCESS_EQUAL) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.o: $(SRCDIR)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pName
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n",
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
            genOSX_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
    
        // Return to caller.
        obj_Release(pFileExt);
        pFileExt = OBJ_NIL;
        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }



    //---------------------------------------------------------------
    //  G e n e r a t e  C o m p i l a t i o n  R u l e s
    //---------------------------------------------------------------
    
    ASTR_DATA *     genOSX_CompileRules(
        GENOSX_DATA     *this,
        const
        char            *pSrcDir,
        const
        char            *pObjDir
    )
    {
        //ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ(this, "genOSX_CompileRules( )");
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        if (NULL == pSrcDir) {
            pSrcDir = "SRCDIR";
        }
        if (NULL == pObjDir) {
            pObjDir = "OBJDIR";
        }
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            genOSX_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        genOSX      *pCopy = genOSX_Copy(this);
     @endcode 
     @param     this    GENOSX object pointer
     @return    If successful, a GENOSX object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the GENOSX object.
     */
    GENOSX_DATA *     genOSX_Copy(
        GENOSX_DATA     *this
    )
    {
        GENOSX_DATA     *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = genOSX_New(genOSX_getDict(this));
        if (pOther) {
            eRc = genOSX_Assign(this, pOther);
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

    void            genOSX_Dealloc(
        OBJ_ID          objId
    )
    {
        GENOSX_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((GENOSX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        //genOSX_setBase(this, OBJ_NIL);
        //genOSX_setDict(this, OBJ_NIL);
        genOSX_setName(this, OBJ_NIL);

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

    ERESULT         genOSX_Disable(
        GENOSX_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         genOSX_Enable(
        GENOSX_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
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
    
    PATH_DATA *     genOSX_LibIncludePath(
        GENOSX_DATA     *this,
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
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ(this, "genOSX_LibIncludePath(\"%s\", %s", pName);
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            //genOSX_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        pFullName = this->pLibName(this, pName, pLibNamePrefix);
        if ( OBJ_NIL == pFullName) {
            genOSX_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibName=\"%s\"", AStr_getData(pFullName));
        if ((OBJ_NIL == pLibIncludePath) && genBase_getDict((GENBASE_DATA *)this)) {
            pNode = nodeHash_FindA(genBase_getDict((GENBASE_DATA *)this), "LibIncludePath");
            pLibIncludePath = AStr_getData(node_getData(pNode));
        }
        TRC_OBJ(this, "\tLibIncludePath=\"%s\"", (pLibIncludePath ? pLibIncludePath : ""));
        
        if (pLibIncludePath) {
            pPath = path_NewA(pLibIncludePath);
            if (OBJ_NIL == pPath) {
                genOSX_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                genOSX_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
        genOSX_setLastError(this, eRc);
        return pPath;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  L i b r a r y  I n s t a l l e d  P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *     genOSX_LibInstalledPath(
        GENOSX_DATA     *this,
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
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ(this, "genOSX_LibInstalledPath(\"%s\", %s", pName);
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            //genOSX_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        pFullName = this->pLibName(this, pName, pLibNamePrefix);
        if ( OBJ_NIL == pFullName) {
            genOSX_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibName=\"%s\"", AStr_getData(pFullName));
        if ((OBJ_NIL == pLibInstalledPath) && genBase_getDict((GENBASE_DATA *)this)) {
            pNode = nodeHash_FindA(genBase_getDict((GENBASE_DATA *)this), "LibInstalledPath");
            pLibInstalledPath = AStr_getData(node_getData(pNode));
        }
        TRC_OBJ(this, "\tLibInstalledPath=\"%s\"", (pLibInstalledPath ? pLibInstalledPath : ""));
        
        if (pLibInstalledPath) {
            pPath = path_NewA(pLibInstalledPath);
            if (OBJ_NIL == pPath) {
                genOSX_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                genOSX_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
        genOSX_setLastError(this, eRc);
        return pPath;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  t h e  f u l l  L i b r a r y  N a m e
    //---------------------------------------------------------------
    
    ASTR_DATA *     genOSX_LibName(
        GENOSX_DATA     *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibNamePrefix
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pFullName = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "genOSX_LibName(\"%s\", %s", pName);
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            //genOSX_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        if ((OBJ_NIL == pLibNamePrefix) && genBase_getDict((GENBASE_DATA *)this)) {
            pNode = nodeHash_FindA(genBase_getDict((GENBASE_DATA *)this), "LibNamePrefix");
            pLibNamePrefix = AStr_getData(node_getData(pNode));
        }
        TRC_OBJ(this, "\tLibNamePrefix=\"%s\"", (pLibNamePrefix ? pLibNamePrefix : ""));
        
        if (pLibNamePrefix) {
            pFullName = AStr_NewA(pLibNamePrefix);
            if (OBJ_NIL == pFullName) {
                genOSX_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
            eRc = AStr_AppendA(pFullName, pName);
        }
        else {
            pFullName = AStr_NewA(pName);
            if (OBJ_NIL == pFullName) {
                genOSX_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
        }
        
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return pFullName;
    }
    
    
    
    //---------------------------------------------------------------
    //         G e n e r a t e  F i n a l
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenFinal(
        GENOSX_DATA     *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "\n\n.PHONY: clean\nclean:\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                "\t-cd $(TEMP) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
                );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "\n\n.PHONY: install\ninstall:\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                "\t-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
                );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                "\t-cd $(INSTALL_BASE) ; "
                "[ ! -d $(LIBNAM)/include ] && mkdir -p $(LIBNAM)/include/$(SYS)\n"
                );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "\tcp $(LIBPATH) $(INSTALLDIR)/$(LIBNAM).a\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "\tcp src/*.h $(INSTALLDIR)/include/\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "\tif [ -d src/$(SYS) ]; then \\\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "\t\tcp src/$(SYS)/*.h $(INSTALLDIR)/include/$(SYS)/; \\\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "\tfi\n\n\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                ".PHONY: create_dirs\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "create_dirs:\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "\t[ ! -d $(OBJDIR) ] && mkdir -p $(OBJDIR)\n\n\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                ".PHONY: all\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "all:  clean create_dirs $(LIBPATH)\n\n\n\n"
        );

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          G e n e r a t e  I n i t i a l  H e a d i n g
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenInitial(
        GENOSX_DATA     *this
    )
    {
        NODE_DATA       *pNode;
        ASTR_DATA       *pStr;
        int             i;
        int             iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "# Generated file do not edit!\n"
        );
        if (genBase_getDateTime((GENBASE_DATA *)this)) {
            pStr = dateTime_ToString(genBase_getDateTime((GENBASE_DATA *)this));
            textOut_Print(
                          genBase_getOutput((GENBASE_DATA *)this),
                          "# (%s)\n\n", AStr_getData(pStr)
            );
            obj_Release(pStr);
        }
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "\n"
        );
        //fprintf(pOutput, "CC=clang\n");
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "LIBNAM=%s\n", AStr_getData(this->pName)
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "SYS=macosx\nTEMP=/tmp\nBASEDIR = $(TEMP)/$(LIBNAM)\n\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "CFLAGS_LIBS = \nCFLAGS += -g -Werror -Isrc -Isrc/$(SYS)\n"
        );
        if (genBase_getLibDeps((GENBASE_DATA *)this)) {
            const
            char            *pLibIncludePrefix;
            pNode = nodeHash_FindA(
                            genBase_getDict((GENBASE_DATA *)this),
                            "libIncludePrefix"
                    );
            pLibIncludePrefix = AStr_getData(node_getData(pNode));
            iMax = nodeArray_getSize(genBase_getLibDeps((GENBASE_DATA *)this));
            for (i=0; i<iMax; ++i) {
                pNode = nodeArray_Get(genBase_getLibDeps((GENBASE_DATA *)this), i+1);
                if (pNode) {
                    pStr = node_getData(pNode);
                    textOut_Print(
                            genBase_getOutput((GENBASE_DATA *)this),
                            "CFLAGS += -I../%s%s/src -I../%s%s/src/$(SYS)\n",
                            pLibIncludePrefix,
                            AStr_getData(pStr),
                            pLibIncludePrefix,
                            AStr_getData(pStr)
                            );
                    textOut_Print(
                            genBase_getOutput((GENBASE_DATA *)this),
                            "CFLAGS_LIBS += -l%s -L$(HOME)/Support/lib/$(SYS)/%s%s\n",
                            AStr_getData(pStr),
                            pLibIncludePrefix,
                            AStr_getData(pStr)
                            );
                    obj_Release(pStr);
                }
            }
        }
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "CFLAGS += -D__MACOSX_ENV__\n\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "INSTALLDIR = $(INSTALL_BASE)/$(LIBNAM)\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "LIBDIR = $(BASEDIR)/$(SYS)\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "SRCDIR = ./src\nSRCSYSDIR = ./src/$(SYS)\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "ifdef  NDEBUG\nCFLAGS += -DNDEBUG\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "LIB_FILENAME=$(LIBNAM)R.a\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "OBJDIR = $(LIBDIR)/o/r\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "else   #DEBUG\nCFLAGS += -D_DEBUG \n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "LIB_FILENAME=$(LIBNAM)D.a\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "OBJDIR = $(LIBDIR)/o/d\nendif  #NDEBUG\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      "LIBPATH = $(LIBDIR)/$(LIB_FILENAME)\n\n\n"
        );
        textOut_Print(
                      genBase_getOutput((GENBASE_DATA *)this),
                      ".SUFFIXES:\n.SUFFIXES: .asm .c .o\n\n\n\n\n"
        );

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //         G e n e r a t e  L i b r a r y
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenLibrary(
        GENOSX_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "\n\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "$(LIBPATH):  $(OBJS)\n"
        );
        textOut_Print(genBase_getOutput((GENBASE_DATA *)this),
                "\t-cd $(LIBDIR) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "\tar rc $(LIBPATH) $(OBJS)\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "\n\n\n\n\n"
        );

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //      G e n e r a t e  T h e  E n t i r e  M a k e f i l e
    //---------------------------------------------------------------
#ifdef XYZZY
    ERESULT         genOSX_GenMakefile(
        GENOSX_DATA     *this,
        NODE_DATA       *pNodes,
        SZHASH_DATA     *pDict,
        DATETIME_DATA   *pDateTime,
        TEXTOUT_DATA    *pOutput
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
        NODEHASH_DATA   *pMacosx = OBJ_NIL;
        //NODEHASH_DATA   *pWin32 = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        //DATETIME_DATA   *pDateTime = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
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
        genBase_setDateTime((GENBASE_DATA *)this, pDateTime);
        genBase_setDict((GENBASE_DATA *)this, pDict);
        genBase_setOutput((GENBASE_DATA *)this, pOutput);
        
        pPrimaryHash = node_getData(pNodes);
        BREAK_FALSE((obj_IsKindOf(pPrimaryHash, OBJ_IDENT_NODEHASH)));
        if (pPrimaryHash) {
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
            pNode = nodeHash_FindA(pPrimaryHash, "macosx");
            if (NULL == pNode) {
            }
            else {
                pNode = node_getData(pNode);
                pMacosx = node_getData(pNode);
                BREAK_FALSE((obj_IsKindOf(pMacosx, OBJ_IDENT_NODEHASH)));
            }
        }
        
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
        
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
#endif
    
    
    
    //---------------------------------------------------------------
    //          G e n e r a t e  O b j e c t s
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenObjects(
        GENOSX_DATA     *this
    )
    {
        //ERESULT         eRc;
        NODE_DATA       *pNode;
        NODEHASH_DATA   *pObjects;
        NODEARRAY_DATA  *pArray =  OBJ_NIL;
        //ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        int             i;
        int             iMax;
        const
        char            *pName;

        pObjects = genBase_getObjects((GENBASE_DATA *)this);
        if (pObjects) {
            pArray = nodeHash_Nodes(pObjects);
            if (OBJ_NIL == pArray) {
            }
            else {
                BREAK_FALSE((obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)));
                iMax = nodeArray_getSize(pArray);
                for (i=0; i<iMax; ++i) {
                    pNode = nodeArray_Get(pArray, i+1);
                    if (pNode) {
                        pName = node_getNameUTF8(pNode);
                        pWrk =  genOSX_CompileObjectStr(
                                                      this,
                                                      pName,
                                                      "SRCDIR",
                                                      "OBJDIR"
                                );
                        //FIXME: fprintf(pOutput, "%s", AStr_getData(pWrk));
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                        mem_Free((void *)pName);
                    }
                }
            }
        }

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          G e n e r a t e  O / S  S p e c i f i c
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenOSSpecific(
        GENOSX_DATA     *this
    )
    {
        //ERESULT         eRc;
        NODEHASH_DATA   *pPrimaryHash = OBJ_NIL;
        NODEHASH_DATA   *pSection = OBJ_NIL;
        NAME_DATA       *pName;
        NODE_DATA       *pNode;
        NODEARRAY_DATA  *pArray =  OBJ_NIL;
        int             i;
        int             iMax;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrk;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pPrimaryHash = node_getData(genBase_getNodes((GENBASE_DATA *)this));
        BREAK_FALSE((obj_IsKindOf(pPrimaryHash, OBJ_IDENT_NODEHASH)));
        if (pPrimaryHash) {
            pNode = nodeHash_FindA(pPrimaryHash, "macosx");
            if (OBJ_NIL == pNode) {
            }
            else {
                pSection = node_getData(pNode);
                if (obj_IsKindOf(pSection, OBJ_IDENT_NULL)) {
                    pSection = OBJ_NIL;
                }
                else if (obj_IsKindOf(pSection, OBJ_IDENT_NODEHASH)) {
                }
                else {
                    DEBUG_BREAK();
                }
            }
        }

        // The "macosx" section contains the sub-sections, "headers" and "sources".
        // The "headers" need to be copied to the "macosx" subdirectory of the
        // library header. So, the subdirectory needs to be created as well as
        // the headers copied across.
        
        if (pSection) {
            pArray = nodeHash_Nodes(pSection);
            if (OBJ_NIL == pArray) {
            }
            else {
                iMax = nodeArray_getSize(pArray);
                for (i=0; i<iMax; ++i) {
                    pNode = nodeArray_Get(pArray, i+1);
                    if (pNode) {
                        pName = node_getName(pNode);
                        pStr = name_getStrA(pName);
                        pWrk = AStr_Copy(pStr);
                        if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                        }
                        else if (AStr_CompareRightA(pWrk, ".asm") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                        }
                        else if (AStr_CompareRightA(pWrk, ".s") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                        }
                        else if (AStr_CompareRightA(pWrk, ".S") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                        }
                        else if (AStr_CompareRightA(pWrk, ".cpp") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                        }
#ifdef XYZZY
                        fprintf(
                                pOutput,
                                "OBJS += $(OBJDIR)/%s.o\n",
                                AStr_getData(pWrk)
                                );
                        fprintf(pOutput, "\n");
                        fprintf(pOutput, "\n");
                        fprintf(pOutput,
                                "$(OBJDIR)/%s.o: src/$(SYS)/%s\n",
                                AStr_getData(pWrk),
                                AStr_getData(pStr)
                                );
                        if (AStr_CompareRightA(pStr, ".c") == ERESULT_SUCCESS_EQUAL) {
                            fprintf(pOutput,
                                    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) "
                                    "src/$(SYS)/%s\n",
                                    AStr_getData(pStr)
                                    );
                        }
                        else if (AStr_CompareRightA(pStr, ".asm") == ERESULT_SUCCESS_EQUAL) {
                            fprintf(pOutput,
                                    "\t$(AS) $(AFLAGS) -o $(OBJDIR)/$(@F) "
                                    "src/$(SYS)/%s\n",
                                    AStr_getData(pStr)
                                    );
                        }
                        else if (AStr_CompareRightA(pStr, ".s") == ERESULT_SUCCESS_EQUAL) {
                            fprintf(pOutput,
                                    "\t$(AS) $(AFLAGS) -o $(OBJDIR)/$(@F) "
                                    "src/$(SYS)/%s\n",
                                    AStr_getData(pStr)
                                    );
                        }
                        else if (AStr_CompareRightA(pStr, ".cpp") == ERESULT_SUCCESS_EQUAL) {
                            fprintf(pOutput,
                                    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) "
                                    "src/$(SYS)/%s\n",
                                    AStr_getData(pStr)
                                    );
                        }
                        fprintf(pOutput, "\n");
                        fprintf(pOutput, "\n");
#endif
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                }
            }
#ifdef XYZZY
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
#endif
        }

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //         G e n e r a t e  P r o g r a m s
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenProgram(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pProgram
    )
    {
        //ERESULT         eRc;
        NODE_DATA       *pNode;
        NODEARRAY_DATA  *pLibDeps = OBJ_NIL;
        NODEHASH_DATA   *pObjects = OBJ_NIL;
        NODEARRAY_DATA  *pRoutines = OBJ_NIL;
        NODEHASH_DATA   *pTests = OBJ_NIL;
        NODEHASH_DATA   *pMacosx = OBJ_NIL;
        //NODEHASH_DATA   *pWin32 = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        ASTR_DATA       *pDir = OBJ_NIL;
        //DATETIME_DATA   *pDateTime = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pProgram) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        BREAK_FALSE((obj_IsKindOf(pProgram, OBJ_IDENT_NODEHASH)));
        pNode = nodeHash_FindA(pProgram, "name");
        if (NULL == pNode) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        else {
            pNode = node_getData(pNode);
            pName = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pName, OBJ_IDENT_ASTR)));
        }
        pNode = nodeHash_FindA(pProgram, "sub_dir");
        if (NULL == pNode) {
            pDir = pName;
        }
        else {
            pNode = node_getData(pNode);
            pDir = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pDir, OBJ_IDENT_ASTR)));
        }
        pNode = nodeHash_FindA(pProgram, "lib_deps");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pLibDeps = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pLibDeps, OBJ_IDENT_NODEARRAY)));
        }
        pNode = nodeHash_FindA(pProgram, "objects");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pObjects = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pObjects, OBJ_IDENT_NODEHASH)));
        }
        pNode = nodeHash_FindA(pProgram, "routines");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pRoutines = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pRoutines, OBJ_IDENT_NODEARRAY)));
        }
        pNode = nodeHash_FindA(pProgram, "tests");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pTests = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pTests, OBJ_IDENT_NODEHASH)));
        }
        pNode = nodeHash_FindA(pProgram, "macosx");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pMacosx = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pMacosx, OBJ_IDENT_NODEHASH)));
        }
        
#ifdef XYZZY
        //genOSX_GenInitial(this, pName, pLibDeps, pDateTime, pOutput);
        
        if (pObjects || pRoutines) {
            //FIXME: fprintf(pOutput, "\n");
            //FIXME: fprintf(pOutput, "OBJS_%s =\n", AStr_getData(pName));
            if (pObjects) {
                genOSX_GenObjects(this, pObjects, pOutput);
            }
            if (pRoutines) {
                genOSX_GenRoutines(this, pRoutines, pOutput);
            }
        }
        
        //genOSX_GenOSSpecific(this, pMacosx, pOutput);
        //genOSX_GenLibrary(this, pOutput);
        //genOSX_GenTests(this, pTests, pOutput);
        //genOSX_GenFinal(this, pOutput);
#endif

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    ERESULT         genOSX_GenPrograms(
        GENOSX_DATA     *this
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pNode;
        NODEARRAY_DATA   *pPrograms = OBJ_NIL;
        //NODEARRAY_DATA  *pArray =  OBJ_NIL;
        NODEHASH_DATA   *pHash =  OBJ_NIL;
        //ASTR_DATA       *pStr = OBJ_NIL;
        //ASTR_DATA       *pWrk = OBJ_NIL;
        int             i;
        int             iMax;
        //const
        //char            *pName;
        
        pPrograms = genBase_getPrograms((GENBASE_DATA *)this);
        if (pPrograms) {
            iMax = nodeArray_getSize(pPrograms);
            for (i=0; i<iMax; ++i) {
                pNode = nodeArray_Get(pPrograms, i+1);
                if (pNode) {
                    pHash = node_getData(pNode);
                    BREAK_FALSE((obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)));
                    eRc = genOSX_GenProgram(this, pHash);
                    if (ERESULT_FAILED(eRc)) {
                        DEBUG_BREAK();
                        genOSX_setLastError(this, eRc);
                        return eRc;
                    }
                }
            }
        }
        
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    ERESULT         genOSX_GenProgramsOld(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pPrograms,
        FILE            *pOutput
    )
    {
        NODE_DATA       *pNode;
        NODEARRAY_DATA  *pArray =  OBJ_NIL;
        NODEARRAY_DATA  *pDeps =  OBJ_NIL;
        NODE_DATA       *pDep;
        //NODEHASH_DATA   *pObjects =  OBJ_NIL;
        //NODEHASH_DATA   *pRoutines =  OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pPgmWrk;
        ASTR_DATA       *pProgName;
        int             i;
        int             iMax;
        int             j;
        int             jMax;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (pPrograms) {
            fprintf(pOutput, "\n");
            fprintf(pOutput, "PROGS =\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            pArray = nodeHash_Nodes(pPrograms);
            if (OBJ_NIL == pArray) {
            }
            else {
                BREAK_FALSE((obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)));
                iMax = nodeArray_getSize(pArray);
                for (i=0; i<iMax; ++i) {
                    pNode = nodeArray_Get(pArray, i+1);
                    if (pNode) {
                        ASTR_DATA       *pWrk;
                        BREAK_FALSE((obj_IsKindOf(pNode, OBJ_IDENT_NODE)));
                        pProgName = name_getStrA(node_getName(pNode));
                        pWrk = AStr_Copy(pStr);
                        if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                        }
                        pPgmWrk = AStr_Copy(pWrk);
                        fprintf(pOutput, "PROGS += %s\n", AStr_getData(pWrk));
                        fprintf(pOutput, "\n");
                        fprintf(pOutput, "%s:\n", AStr_getData(pWrk));
                        fprintf(pOutput,
                                "\t$(CC) "
                                "$(CFLAGS) "
                                "$(CFLAGS_LIBS) "
                                "-L$(LIBDIR) "
                                "-Iprograms/%s/src "
                                "$(LIBPATH) "
                                "-o $(OBJDIR)/$(@F) "
                                "programs/%s/src/%s ",
                                AStr_getData(pWrk),
                                AStr_getData(pWrk),
                                AStr_getData(pStr)
                                );
                        pDep = node_getData(pNode);
                        if (pDep) {
                            BREAK_FALSE((obj_IsKindOf(pDep, OBJ_IDENT_NODE)));
                            pDeps = node_getData(pDep);
                        }
                        else {
                            pDeps = OBJ_NIL;
                        }
                        if (pDeps && obj_IsKindOf(pDeps, OBJ_IDENT_NODEARRAY)) {
                            jMax = nodeArray_getSize(pDeps);
                            for (j=0; j<jMax; ++j) {
                                pNode = nodeArray_Get(pDeps, j+1);
                                if (pNode) {
                                    ASTR_DATA       *pWrk;
                                    pWrk = node_getData(pNode);
                                    if (pWrk && obj_IsKindOf(pWrk, OBJ_IDENT_ASTR)) {
                                        fprintf(pOutput,
                                                "programs/%s/%s ",
                                                AStr_getData(pPgmWrk),
                                                AStr_getData(pWrk)
                                                );
                                    }
                                }
                            }
                            obj_Release(pDeps);
                            pDeps = OBJ_NIL;
                            obj_Release(pPgmWrk);
                            pPgmWrk = OBJ_NIL;
                        }
                        fprintf(pOutput, "\n");
                        fprintf(pOutput, "\techo $(OBJDIR)/$(@F)\n");
                        fprintf(pOutput, "\n");
                        fprintf(pOutput, "\n");
                        
                        obj_Release(pWrk);
                    }
                }
                obj_Release(pArray);
                pArray = OBJ_NIL;
            }
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, ".PHONY: programs\n");
            fprintf(pOutput, "programs:  $(PROGS)\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
        }

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          G e n e r a t e  R o u t i n e s
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenRoutines(
        GENOSX_DATA     *this
    )
    {
        //ERESULT         eRc;
        NODE_DATA       *pNode;
        NODEARRAY_DATA  *pRoutines =  OBJ_NIL;
        //NODEARRAY_DATA  *pArray =  OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        int             i;
        int             iMax;
        //const
        //char            *pName;
        
        pRoutines = genBase_getRoutines((GENBASE_DATA *)this);
        if (pRoutines) {
            iMax = nodeArray_getSize(pRoutines);
            for (i=0; i<iMax; ++i) {
                pNode = nodeArray_Get(pRoutines, i+1);
                if (pNode) {
                    pStr = node_getData(pNode);
                    pWrk =  genOSX_CompileRoutineStr(
                                                     this,
                                                     AStr_getData(pStr),
                                                     "SRCDIR",
                                                     "OBJDIR"
                                                     );
                    if (pWrk) {
#ifdef XYZZY
                        fprintf(pOutput, "%s", AStr_getData(pWrk));
#endif
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                    }
#ifndef NDEBUG
                    else {
                        DEBUG_BREAK();
                    }
#endif
                }
            }
        }
        
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //              G e n e r a t e  T e s t s
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenTests(
        GENOSX_DATA     *this
    )
    {
        //ERESULT         eRc;
        NODEHASH_DATA   *pTests =  OBJ_NIL;
#ifdef XYZZY
        NODE_DATA       *pNode;
        NODEARRAY_DATA  *pArray =  OBJ_NIL;
        NODEARRAY_DATA  *pDeps =  OBJ_NIL;
        NODE_DATA       *pDep;
        ASTR_DATA       *pStr;
        int             i;
        int             iMax;
        int             j;
        int             jMax;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pTests = genBase_getTests((GENBASE_DATA *)this);
        if (pTests) {
            //FIXME: Re-implement!
#ifdef XYZZY
            fprintf(pOutput, "\n");
            fprintf(pOutput, "TESTS =\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            pArray = nodeHash_Nodes(pTests);
            if (OBJ_NIL == pArray) {
            }
            else {
                BREAK_FALSE((obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)));
                iMax = nodeArray_getSize(pArray);
                for (i=0; i<iMax; ++i) {
                    pNode = nodeArray_Get(pArray, i+1);
                    if (pNode) {
                        ASTR_DATA       *pWrk;
                        BREAK_FALSE((obj_IsKindOf(pNode, OBJ_IDENT_NODE)));
                        pStr = name_getStrA(node_getName(pNode));
                        pWrk = AStr_Copy(pStr);
                        if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                        }
                        fprintf(pOutput, "TESTS += %s\n", AStr_getData(pWrk));
                        fprintf(pOutput, "\n");
                        fprintf(pOutput, "%s:\n", AStr_getData(pWrk));
                        fprintf(pOutput,
                                "\t$(CC) "
                                "$(CFLAGS) "
                                "$(CFLAGS_LIBS) "
                                "-L$(LIBDIR) "
                                "-Itests "
                                "$(LIBPATH) "
                                "-o $(OBJDIR)/$(@F) "
                                "tests/%s ",
                                AStr_getData(pStr)
                                );
                        pDep = node_getData(pNode);
                        if (pDep) {
                            BREAK_FALSE((obj_IsKindOf(pDep, OBJ_IDENT_NODE)));
                            pDeps = node_getData(pDep);
                        }
                        else {
                            pDeps = OBJ_NIL;
                        }
                        if (pDeps && obj_IsKindOf(pDeps, OBJ_IDENT_NODEARRAY)) {
                            jMax = nodeArray_getSize(pDeps);
                            for (j=0; j<jMax; ++j) {
                                pNode = nodeArray_Get(pDeps, j+1);
                                if (pNode) {
                                    ASTR_DATA       *pWrk;
                                    pWrk = node_getData(pNode);
                                    if (pWrk && obj_IsKindOf(pWrk, OBJ_IDENT_ASTR)) {
                                        fprintf(pOutput,
                                                "tests/%s ",
                                                AStr_getData(pWrk)
                                                );
                                    }
                                }
                            }
                            obj_Release(pDeps);
                            pDeps = OBJ_NIL;
                        }
                        fprintf(pOutput, "\n");
                        fprintf(pOutput, "\t$(OBJDIR)/$(@F) ./tests\n");
                        fprintf(pOutput, "\n");
                        fprintf(pOutput, "\n");
                        
                        obj_Release(pWrk);
                    }
                }
                obj_Release(pArray);
                pArray = OBJ_NIL;
            }
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, ".PHONY: test\n");
            fprintf(pOutput, "test:  $(TESTS)\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
#endif
        }

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    GENOSX_DATA *   genOSX_Init(
        GENOSX_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(GENOSX_DATA);
        
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

        this = (OBJ_ID)genBase_Init((GENBASE_DATA *)this);    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, MAIN_IDENT_GENOSX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                      // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, MAIN_IDENT_GENOSX);   // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&genOSX_Vtbl);
        
        genOSX_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->pLibIncludePath = genOSX_LibIncludePath;
        this->pLibName = genOSX_LibName;

    #ifdef NDEBUG
    #else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "genOSX::offsetof(eRc) = %lu\n", offsetof(GENOSX_DATA,eRc));
        //fprintf(stderr, "genOSX::sizeof(GENOSX_DATA) = %lu\n", sizeof(GENOSX_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(GENOSX_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         genOSX_IsEnabled(
        GENOSX_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            genOSX_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS_FALSE);
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
        void        *pMethod = genOSX_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "genOSX", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          genOSX_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        GENOSX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)genOSX_Class();
                break;
                
        // Query for an address to specific data within the object.
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'C':
                        if (str_Compare("ClassObject", (char *)pStr) == 0) {
                            return (void *)&genOSX_ClassObj;
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
                            return genOSX_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return genOSX_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return genOSX_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return genOSX_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == genOSX_ToDebugString)
                    return "ToDebugString";
                if (pData == genOSX_ToJSON)
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
        ASTR_DATA      *pDesc = genOSX_ToDebugString(this,4);
     @endcode 
     @param     this    GENOSX object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     genOSX_ToDebugString(
        GENOSX_DATA      *this,
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
        if( !genOSX_Validate(this) ) {
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
                    genOSX_getSize(this)
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
        
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     genOSX_ToJSON(
        GENOSX_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
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
        
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            genOSX_Validate(
        GENOSX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, MAIN_IDENT_GENOSX) )
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


        if( !(obj_getSize(this) >= sizeof(GENOSX_DATA)) ) {
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


