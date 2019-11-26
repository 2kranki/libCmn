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
    
    const
    char        *pDirObjA = "OBJDIR";
    const
    char        *pDirSrcA = "SRCDIR";
    const
    char        *pObjNameSuffixA = "_object";
    const
    char        *pObjsA = "OBJS";
    const
    char        *pTestNamePrefixA = "test_";
    const
    char        *pTestsA = "TESTS";



 
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
        char            *pObjDir,
        const
        char            *pObjVar
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
            pSrcDir = pDirSrcA;
        }
        if (NULL == pObjDir) {
            pObjDir = pDirObjA;
        }
        if (NULL == pObjVar) {
            pObjDir = "OBJS";
        }
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        
        if (0 == strcmp(pObjDir, pDirObjA)) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "%s += $(%s)/%s.o $(%s)/%s%s.o\n\n",
                                     pObjVar,
                                     pDirObjA,
                                     pName,
                                     pDirObjA,
                                     pName,
                                     pObjNameSuffixA
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
        char            *pObjDir,
        const
        char            *pObjVar
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
            pSrcDir = pDirSrcA;
        }
        if (NULL == pObjDir) {
            pObjDir = pDirObjA;
        }
        if (NULL == pObjVar) {
            pObjDir = "OBJS";
        }
        pPath = path_NewA(pName);
        if (OBJ_NIL == pPath) {
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
            return OBJ_NIL;
        }
        TRC_OBJ(this, "genOSX_CompileRoutine(\"%s\", %s", pName);

        if (0 == strcmp(pObjDir, pDirObjA)) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "%s += $(%s)/%s.o\n\n",
                                     pObjVar,
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
        else {
            obj_Release(pFileExt);
            pFileExt = OBJ_NIL;
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
            obj_Release(pPath);
            pPath = OBJ_NIL;
            obj_Release(pStr);
            pStr = OBJ_NIL;
            return OBJ_NIL;
        }
        
    // Return to caller.
    obj_Release(pFileExt);
    pFileExt = OBJ_NIL;
    obj_Release(pFileName);
    pFileName = OBJ_NIL;
    obj_Release(pPath);
    pPath = OBJ_NIL;
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
        
        return iRc;
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
        GENOSX_DATA     *pOther
    )
    {
        ERESULT         eRc;
        
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
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
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
        //ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        NODE_DATA       *pLibObjectPath = OBJ_NIL;
        NODE_DATA       *pLibObjectPrefix = OBJ_NIL;
        //OBJ_ID          pPath = OBJ_NIL;
        //OBJ_ID          pPrefix = OBJ_NIL;

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
                                0,
                                "LibObjectPath"
                            );
        if (NULL == pLibObjectPath) {
            return OBJ_NIL;
        }
        pLibObjectPrefix =  nodeHash_FindA(
                                genBase_getDict((GENBASE_DATA *)this),
                                0,
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
        return eRc;
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
            pSrcDir = pDirSrcA;
        }
        if (NULL == pObjDir) {
            pObjDir = pDirObjA;
        }
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        
        // Return to caller.
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
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //          G e n e r a t e  C o m p i l a t i o n
    //---------------------------------------------------------------
    
    ASTR_DATA *     genOSX_GenCompileJson(
        GENOSX_DATA    *this,
        const
        char            *pNameA,            // Routine File Name including extension
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,           // If present, adds another Make Flag
        //                                  // variable in addition to CFLAGS
        //                                  // (Default - none)
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
        TRC_OBJ( this, "genOSX_CompileObject(\"%s\")\n", pName);
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
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
        
        pWrkStr =   genOSX_GenCompileRoutine(
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
    
    
    ASTR_DATA *     genOSX_GenCompileObject(
        GENOSX_DATA    *this,
        const
        char            *pNameA,            // Object Name
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,           // If present, adds another Make Flag
        //                                  // variable in addition to CFLAGS
        //                                  // (Default - none)
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
        TRC_OBJ( this, "genOSX_CompileObject(\"%s\")\n", pNameA);
        BREAK_NULL(pNameA);
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
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
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
        
        pFileName = AStr_NewA(pNameA);
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
        pWrkStr =   genOSX_GenCompileRoutine(
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
        obj_Release(pFileExt);
        pFileExt = OBJ_NIL;
        if (pWrkStr) {
            eRc = AStr_Append(pStr, pWrkStr);
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
        }

        eRc = AStr_AppendA(pFileName, ".c");
        pWrkStr =   genOSX_GenCompileRoutine(
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
        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        if (pWrkStr) {
            eRc = AStr_Append(pStr, pWrkStr);
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
        }
        
        
        // Return to caller.
        return pStr;
    }
    
    
    ASTR_DATA *     genOSX_GenCompileRoutine(
        GENOSX_DATA    *this,
        const
        char            *pNameA,            // Routine File Name including extension
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
        TRC_OBJ( this, "genOSX_CompileRoutine(\"%s\")\n", pNameA);
        BREAK_NULL(pNameA);
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            //genOSX_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        if (NULL == pSrcDir) {
            pSrcDir = pDirSrcA;
        }
        if (NULL == pObjDir) {
            pObjDir = pDirObjA;
        }
        if (NULL == pObjVar) {
            pObjVar = pObjsA;
        }
        pPath = path_NewA(pNameA);
        if (OBJ_NIL == pPath) {
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
            return OBJ_NIL;
        }
        
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "%s += $(%s)/%s.o\n\n",
                                 pObjVar,
                                 pObjDir,
                                 AStr_getData(pFileName)
                                 );
        if ((AStr_CompareA(pFileExt, "c") == ERESULT_SUCCESS_EQUAL)
            || (AStr_CompareA(pFileExt, "C") == ERESULT_SUCCESS_EQUAL)) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.o: $(%s)/%s ",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pNameA
                                     );
            if (pSrcDeps) {
                iMax = nodeArray_getSize(pSrcDeps);
                for (i=0; i<iMax; ++i) {
                    NODE_DATA           *pNode;
                    ASTR_DATA           *pWrkStr;
                    pNode = nodeArray_Get(pSrcDeps, (i + 1));
                    if (pNode) {
                        pWrkStr = node_getData(pNode);
                        if (pWrkStr && obj_IsKindOf(pWrkStr, OBJ_IDENT_ASTR)) {
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
                                         "\t$(CC) $(CFLAGS) %s $(%s) -o $(%s)/$(@F) $< ",
                                         (fCO ? "-c" : ""),
                                         pFlgVar,
                                         pObjDir
                                         );
            }
            else {
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "\t$(CC) $(CFLAGS) %s -o $(%s)/$(@F) $< ",
                                         (fCO ? "-c" : ""),
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
                                     "$(%s)/%s.o: $(%s)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pNameA
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(AS) $(AFLAGS) %s -o $(%s)/$(@F) $<",
                                     (fCO ? "-c" : ""),
                                     pObjDir
                                     );
        }
        else if ((AStr_CompareA(pFileExt, "s") == ERESULT_SUCCESS_EQUAL)
                 || (AStr_CompareA(pFileExt, "S") == ERESULT_SUCCESS_EQUAL)) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "$(%s)/%s.o: $(%s)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pNameA
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
                                     "$(%s)/%s.o: $(%s)/%s\n",
                                     pObjDir,
                                     AStr_getData(pFileName),
                                     pSrcDir,
                                     pNameA
                                     );
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t$(CC) $(CFLAGS) %s -o $(%s)/$(@F) $<",
                                     (fCO ? "-c" : ""),
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
            return OBJ_NIL;
        }
        if (!fCO && fExec) {
            eRc = AStr_AppendPrint(pStr, "\n\t$(%s)/$(@F)\n\n", pObjDir);
        }
        else {
            eRc =   AStr_AppendA(pStr, "\n\n");
        }
        
        // Return to caller.
        obj_Release(pFileExt);
        pFileExt = OBJ_NIL;
        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        return pStr;
    }
    
    
    ASTR_DATA *     genOSX_GenCompileTest(
        GENOSX_DATA    *this,
        const
        char            *pNameA,            // Routine File Name including extension
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,           // If present, adds another Make Flag
        //                                  // variable in addition to CFLAGS
        //                                  // (Default - none)
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps           // Object Dependencies (ie files to be
                                            // included in the compile statement, file
                                            // extension must match that of pName above)
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pFileName = OBJ_NIL;
        ASTR_DATA       *pFileExt = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
        TRC_OBJ( this, "genOSX_CompileObject(\"%s\")\n", pName);
        BREAK_NULL(pNameA);
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
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
        
        pPath = path_NewA(pNameA);
        if (OBJ_NIL == pPath) {
            return OBJ_NIL;
        }
        eRc = path_SplitFile(pPath, &pFileName, &pFileExt);
        //BREAK_NULL(pFileName);
        //BREAK_NULL(pFileExt);

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
            eRc = AStr_AppendA(pName, AStr_getData(pFileName));
        }
        else {
            return OBJ_NIL;
        }

        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "%s += %s\n\n",
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
                                                 "$(%s)/%s $(OBJS)",
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
                                 "\t$(CC) $(CFLAGS) $(TEST_FLGS) -o $(%s)/$(@F) $(OBJS) $< ",
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
        eRc =   AStr_AppendA(pStr, "\n");

        eRc = AStr_AppendPrint(pStr, "\t$(%s)/$(@F)\n\n", pObjDir);

        // Return to caller.
        obj_Release(pFileExt);
        pFileExt = OBJ_NIL;
        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pName);
        pName = OBJ_NIL;
        return pStr;
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
        TRC_OBJ(this, "genOSX_LibIncludePath(\"%s\", %s, %s)\n", pName, pLibIncludePath, pLibNamePrefix);
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
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibName=\"%s\"", AStr_getData(pFullName));
        if ((OBJ_NIL == pLibIncludePath) && genBase_getDict((GENBASE_DATA *)this)) {
            pNode = nodeHash_FindA(genBase_getDict((GENBASE_DATA *)this), 0, "LibIncludePath");
            pLibIncludePath = AStr_getData(node_getData(pNode));
        }
        TRC_OBJ(this, "\tLibIncludePath=\"%s\"", (pLibIncludePath ? pLibIncludePath : ""));
        
        if (pLibIncludePath) {
            pPath = path_NewA(pLibIncludePath);
            if (OBJ_NIL == pPath) {
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
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
        TRC_OBJ(this, "genOSX_LibInstalledPath(\"%s\")\n", pName);
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
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibName=\"%s\"", AStr_getData(pFullName));
        if ((OBJ_NIL == pLibInstalledPath) && genBase_getDict((GENBASE_DATA *)this)) {
            pNode = nodeHash_FindA(genBase_getDict((GENBASE_DATA *)this), 0, "LibInstalledPath");
            pLibInstalledPath = AStr_getData(node_getData(pNode));
        }
        TRC_OBJ(this, "\tLibInstalledPath=\"%s\"", (pLibInstalledPath ? pLibInstalledPath : ""));
        
        if (pLibInstalledPath) {
            pPath = path_NewA(pLibInstalledPath);
            if (OBJ_NIL == pPath) {
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
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
            pNode = nodeHash_FindA(genBase_getDict((GENBASE_DATA *)this), 0, "LibNamePrefix");
            pLibNamePrefix = AStr_getData(node_getData(pNode));
        }
        TRC_OBJ(this, "\tLibNamePrefix=\"%s\"", (pLibNamePrefix ? pLibNamePrefix : ""));
        
        if (pLibNamePrefix) {
            pFullName = AStr_NewA(pLibNamePrefix);
            if (OBJ_NIL == pFullName) {
                return OBJ_NIL;
            }
            eRc = AStr_AppendA(pFullName, pName);
        }
        else {
            pFullName = AStr_NewA(pName);
            if (OBJ_NIL == pFullName) {
                return OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pFullName;
    }
    
    
    
    //---------------------------------------------------------------
    //         G e n e r a t e  F i n a l
    //---------------------------------------------------------------
    
    ASTR_DATA *     genOSX_GenFinal(
        GENOSX_DATA     *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        uint16_t        makeType;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return pStr;
        }
#endif
        makeType = genBase_getMakeType((GENBASE_DATA *)this);

        pStr = AStr_New( );
        if (OBJ_NIL == pStr) {
            return pStr;
        }
        
        AStr_AppendA(pStr, "\n\n\n");
        
        switch (makeType) {
            case GENMAKE_TYPE_LIB:
                AStr_AppendA(pStr, "$(LIBPATH):  $(OBJS)\n");
                AStr_AppendA(pStr, "\t-cd $(LIBDIR) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)\n");
                AStr_AppendA(pStr, "\tar rc $(LIBPATH) $(OBJS)\n\n\n\n");
                break;
            case GENMAKE_TYPE_PGM:
                break;
            default:
                break;
        }
        
        AStr_AppendA(pStr, ".PHONY: test\n");
        AStr_AppendA(pStr, "test: $(TESTS)\n\n\n");
        
        AStr_AppendA(pStr, ".PHONY: clean\nclean:\n");
        switch (makeType) {
            case GENMAKE_TYPE_LIB:
                AStr_AppendA(pStr, "\t-cd $(TEMP) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n\n\n");
                break;
            case GENMAKE_TYPE_PGM:
                AStr_AppendA(pStr, "\t-cd $(TEMP) ; [ -d $(PGMNAM) ] && rm -fr $(PGMNAM)\n\n\n");
                break;
            default:
                break;
        }
        
        AStr_AppendA(pStr, ".PHONY: install\ninstall:\n");
        switch (makeType) {
            case GENMAKE_TYPE_LIB:
                AStr_AppendA(pStr, "\t-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n");
                AStr_AppendA(pStr, "\t-cd $(INSTALL_BASE) ; "
                             "[ ! -d $(LIBNAM)/include ] && "
                             "mkdir -p $(LIBNAM)/include/$(SYS)\n");
                AStr_AppendA(pStr, "\tcp $(LIBPATH) $(INSTALLDIR)/$(LIBNAM).a\n");
                AStr_AppendA(pStr, "\tcp src/*.h $(INSTALLDIR)/include/\n");
                AStr_AppendA(pStr, "\tif [ -d src/$(SYS) ]; then \\\n");
                AStr_AppendA(pStr, "\t\tcp src/$(SYS)/*.h $(INSTALLDIR)/include/$(SYS)/; \\\n");
                AStr_AppendA(pStr, "\tfi\n\n\n");
                break;
            case GENMAKE_TYPE_PGM:
                AStr_AppendA(pStr, "\t-cd $(INSTALL_BASE) ; [ -d $(PGMNAM) ] && rm -fr $(PGMNAM)\n");
                AStr_AppendA(pStr, "\tcp $(OBJDIR)/$(PGMNAM) $(INSTALLDIR)/$(PGMNAM)\n\n\n");
                break;
            default:
                break;
        }
        
        switch (makeType) {
            case GENMAKE_TYPE_LIB:
                break;
            case GENMAKE_TYPE_PGM:
                AStr_AppendA(pStr, ".PHONY: link\n");
                pWrk = AStr_NewA("link: $$(OBJS) src/${" mainID "}\n");
                if (pWrk) {
                    eRc = genBase_DictExpand((GENBASE_DATA *)this, pWrk);
                    AStr_AppendPrint(pStr, AStr_getData(pWrk));
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                AStr_AppendPrint(
                                 pStr,
                                 "\tCC -o $(OBJDIR)/$(PGMNAM) "
                                 "$(CFLAGS) $(CFLAGS_LIBS) $^\n\n\n"
                );
                break;
            default:
                break;
        }
        
        AStr_AppendA(pStr, ".PHONY: create_dirs\n");
        AStr_AppendA(pStr, "create_dirs:\n");
        AStr_AppendPrint(pStr,
                    "\t[ ! -d $(%s) ] && mkdir -p $(%s)/tests\n\n\n",
                     pDirObjA,
                     pDirObjA
        );
        
        AStr_AppendA(pStr, ".PHONY: all\n");
        switch (makeType) {
            case GENMAKE_TYPE_LIB:
                AStr_AppendA(pStr, "all:  clean create_dirs $(LIBPATH)\n\n\n\n");
                break;
            case GENMAKE_TYPE_PGM:
                AStr_AppendA(pStr, "all:  clean create_dirs link\n\n\n\n");
                break;
            default:
                break;
        }

        // Return to caller.
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //          G e n e r a t e  I n i t i a l  H e a d i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     genOSX_GenInitial(
        GENOSX_DATA     *this
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pNode;
        ASTR_DATA       *pStr;
        int             i;
        int             iMax;
        ASTR_DATA       *pOut = OBJ_NIL;
        uint16_t        makeType;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return pOut;
        }
#endif
        makeType = genBase_getMakeType((GENBASE_DATA *)this);

        pOut = AStr_New( );
        if (OBJ_NIL == pOut) {
            return pOut;
        }
        
        AStr_AppendA(pOut, "# Generated file - edits may be discarded!\n");
        if (genBase_getDateTime((GENBASE_DATA *)this)) {
            pStr = dateTime_ToString(genBase_getDateTime((GENBASE_DATA *)this));
            AStr_AppendPrint(pOut, "# (%s)\n\n", AStr_getData(pStr));
            obj_Release(pStr);
        }
        AStr_AppendPrint(pOut, "\n");
        
        //AStr_AppendPrint(pOut, "CC=clang\n");
        switch (makeType) {
            case GENMAKE_TYPE_LIB:
                pStr = AStr_NewA("LIBNAM=${" namePrefixID "}${" nameID "}\n");
                if (pStr) {
                    eRc = genBase_DictExpand((GENBASE_DATA *)this, pStr);
                    AStr_AppendPrint(pOut, AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
                AStr_AppendA(pOut, "SYS=macosx\nTEMP=/tmp\nBASEDIR = $(TEMP)/$(LIBNAM)\n\n");
                AStr_AppendA(pOut, "CFLAGS_LIBS = \nCFLAGS += -g -Werror -Isrc -Isrc/$(SYS)\n");
                break;
            case GENMAKE_TYPE_PGM:
                pStr = AStr_NewA("PGMNAM=${" nameID "}\n");
                if (pStr) {
                    eRc = genBase_DictExpand((GENBASE_DATA *)this, pStr);
                    AStr_AppendPrint(pOut, AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
                AStr_AppendA(pOut, "SYS=macosx\nTEMP=/tmp\nBASEDIR = $(TEMP)/$(PGMNAM)\n\n");
                AStr_AppendA(pOut, "CFLAGS_LIBS = \nCFLAGS += -g -Werror -Isrc -Isrc/$(SYS)\n");
                break;
            default:
                break;
        }
        if (genBase_getLibDeps((GENBASE_DATA *)this)) {
            const
            char            *pLibBase;
            ASTR_DATA       *pNamePrefix = OBJ_NIL;
            ASTR_DATA       *pNamePrefixUpper = OBJ_NIL;
            pNode = nodeHash_FindA(
                                   genBase_getDict((GENBASE_DATA *)this),
                                   0,
                                   libBaseID
                    );
            if (pNode) {
                pLibBase = AStr_getData(node_getData(pNode));
                AStr_AppendPrint(pOut, "LIB_BASE = %s\n", pLibBase);
            }
            pNode = nodeHash_FindA(
                            genBase_getDict((GENBASE_DATA *)this),
                            0,
                            namePrefixID
                    );
            pNamePrefix = node_getData(pNode);
            pNamePrefixUpper = AStr_ToUpper(pNamePrefix);
            iMax = nodeArray_getSize(genBase_getLibDeps((GENBASE_DATA *)this));
            for (i=0; i<iMax; ++i) {
                ASTR_DATA       *pUpper = OBJ_NIL;
                pNode = nodeArray_Get(genBase_getLibDeps((GENBASE_DATA *)this), i+1);
                if (pNode) {
                    pStr = node_getData(pNode);
                    if (pStr) {
                        pUpper = AStr_ToUpper(pStr);
                    }
                    AStr_AppendPrint(pOut,
                                     "%s%s_BASE = $(LIB_BASE)/%s%s\n",
                                     AStr_getData(pNamePrefixUpper),
                                     AStr_getData(pUpper),
                                     AStr_getData(pNamePrefix),
                                     AStr_getData(pStr)
                                     );
                    AStr_AppendPrint(pOut,
                            "CFLAGS += -I$(%s%s_BASE)/include\n",
                                     AStr_getData(pNamePrefixUpper),
                                     AStr_getData(pUpper)
                            );
                    AStr_AppendPrint(pOut,
                            "CFLAGS_LIBS += -l%s -L$(%s%s_BASE)\n",
                                     AStr_getData(pStr),
                                     AStr_getData(pNamePrefixUpper),
                                     AStr_getData(pUpper)
                            );
                    obj_Release(pUpper);
                    obj_Release(pStr);
                }
            }
            obj_Release(pNamePrefixUpper);
            obj_Release(pNamePrefix);
        }
        AStr_AppendA(pOut, "CFLAGS += -D__MACOSX_ENV__\n\n");
        AStr_AppendA(pOut, "TEST_FLGS = -Itests $(CFLAGS_LIBS) -lcurses\n\n");
        
        switch (makeType) {
            case GENMAKE_TYPE_LIB:
                AStr_AppendA(pOut, "INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n");
                AStr_AppendA(pOut, "INSTALLDIR = $(INSTALL_BASE)/$(LIBNAM)\n");
                break;
            case GENMAKE_TYPE_PGM:
                AStr_AppendA(pOut, "INSTALL_BASE = $(HOME)/Support/bin\n");
                AStr_AppendA(pOut, "INSTALLDIR = $(INSTALL_BASE)\n");
                break;
            default:
                break;
        }
        AStr_AppendA(pOut, "LIBDIR = $(BASEDIR)/$(SYS)\n");
        AStr_AppendPrint(pOut, "%s = ./src\nSRCSYSDIR = ./src/$(SYS)\n", pDirSrcA);
        AStr_AppendA(pOut, "TEST_SRC = ./tests\n");
        AStr_AppendA(pOut, "ifdef  NDEBUG\nCFLAGS += -DNDEBUG\n");
        AStr_AppendA(pOut, "LIB_FILENAME=$(LIBNAM)R.a\n");
        AStr_AppendPrint(pOut, "%s = $(LIBDIR)/o/r\n", pDirObjA);
        AStr_AppendA(pOut, "else   #DEBUG\nCFLAGS += -D_DEBUG \n");
        AStr_AppendA(pOut, "LIB_FILENAME=$(LIBNAM)D.a\n");
        AStr_AppendPrint(pOut, "%s = $(LIBDIR)/o/d\n", pDirObjA);
        AStr_AppendA(pOut, "endif  #NDEBUG\n");
        AStr_AppendPrint(pOut, "TEST_OBJ = $(%s)/tests\n", pDirObjA);
        AStr_AppendA(pOut, "LIBPATH = $(LIBDIR)/$(LIB_FILENAME)\n\n");
        AStr_AppendA(pOut, ".SUFFIXES:\n.SUFFIXES: .asm .c .o\n\n");
        AStr_AppendPrint(pOut, "%s = \n\n", pObjsA);
        AStr_AppendPrint(pOut, "%s = \n\n", pTestsA);
        AStr_AppendA(pOut, "\n\n\n\n");

        // Return to caller.
        return pOut;
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
                "$(LIBPATH):  $(%s)\n",
                pObjsA
        );
        textOut_Print(genBase_getOutput((GENBASE_DATA *)this),
                "\t-cd $(LIBDIR) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)\n"
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "\tar rc $(LIBPATH) $(%s)\n",
                pObjsA
        );
        textOut_Print(
                genBase_getOutput((GENBASE_DATA *)this),
                "\n\n\n\n\n"
        );

        // Return to caller.
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

        this = (OBJ_ID)genBase_Init((GENBASE_DATA *)this);    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, MAIN_IDENT_GENOSX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                      // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&genOSX_Vtbl);
        
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
        //fprintf(stderr, "genOSX::sizeof(GENOSX_DATA) = %lu\n", sizeof(GENOSX_DATA));
#endif
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
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


