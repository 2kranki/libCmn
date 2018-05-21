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
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            genOSX_task_body(
        void            *pData
    )
    {
        //GENOSX_DATA  *this = pData;
        
    }
#endif



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
        void
    )
    {
        GENOSX_DATA       *this;
        
        this = genOSX_Alloc( );
        if (this) {
            this = genOSX_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                        B a s e
    //---------------------------------------------------------------
    
    GENBASE_DATA *  genOSX_getBase(
        GENOSX_DATA     *this
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
        return this->pBase;
    }
    
    
    bool        genOSX_setBase(
        GENOSX_DATA     *this,
        GENBASE_DATA    *pValue
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
        if (this->pBase) {
            obj_Release(this->pBase);
        }
        this->pBase = pValue;
        
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D i c t i o n a r y
    //---------------------------------------------------------------
    
    SZHASH_DATA *   genOSX_getDict(
        GENOSX_DATA     *this
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
        return this->pDict;
    }
    
    
    bool            genOSX_setDict(
        GENOSX_DATA     *this,
        SZHASH_DATA     *pValue
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
        if (this->pDict) {
            obj_Release(this->pDict);
        }
        this->pDict = pValue;
        
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return true;
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
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * genOSX_getStr(
        GENOSX_DATA     *this
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
        return this->pStr;
    }
    
    
    bool        genOSX_setStr(
        GENOSX_DATA     *this,
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
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return true;
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
    
    ASTR_DATA *     genOSX_CompileObject(
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
        TRC_OBJ(this, "genOSX_CompileObject(\"%s\", %s, %s)", pName, pSrcDir, pObjDir);
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
    
    ASTR_DATA *     genOSX_CompileRoutine(
        GENOSX_DATA    *this,
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
        if (0 == strcmp(pObjDir, "OBJDIR")) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "OBJS += $(%s)/%s.o\n\n",
                                     pObjDir,
                                     pFileName
                                     );
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
        ERESULT         eRc;
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
        GENOSX_DATA       *this
    )
    {
        GENOSX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = genOSX_New( );
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

        genOSX_setBase(this, OBJ_NIL);
        genOSX_setDict(this, OBJ_NIL);
        genOSX_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //             D i c t i o n a r y  M e t h o d s
    //---------------------------------------------------------------
    
    ERESULT         genOSX_DictAdd(
        GENOSX_DATA     *this,
        const
        char            *pName,
        const
        char            *pData
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
#endif
        
        if (OBJ_NIL == this->pDict) {
            this->pDict = szHash_New(SZHASH_TABLE_SIZE_SMALL);
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        if (szHash_FindA(this->pDict, pName)) {
            eRc = szHash_DeleteA(this->pDict, pName);
        }
        eRc = szHash_AddA(this->pDict, pName, (void *)pData);
        
        // Return to caller.
        return eRc;
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
    //         G e n e r a t e  F i n a l
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenFinal(
        GENOSX_DATA     *this,
        FILE            *pOutput
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
        
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, ".PHONY: clean\n");
        fprintf(pOutput, "clean:\n");
        fprintf(
                pOutput,
                "\t-cd $(TEMP) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
                );
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, ".PHONY: install\n");
        fprintf(pOutput, "install:\n");
        fprintf(
                pOutput,
                "\t-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
                );
        fprintf(
                pOutput,
                "\t-cd $(INSTALL_BASE) ; "
                "[ ! -d $(LIBNAM)/include ] && mkdir -p $(LIBNAM)/include/$(SYS)\n"
                );
        fprintf(pOutput, "\tcp $(LIBPATH) $(INSTALLDIR)/$(LIBNAM).a\n");
        fprintf(pOutput, "\tcp src/*.h $(INSTALLDIR)/include/\n");
        fprintf(pOutput, "\tif [ -d src/$(SYS) ]; then \\\n");
        fprintf(pOutput, "\t\tcp src/$(SYS)/*.h $(INSTALLDIR)/include/$(SYS)/; \\\n");
        fprintf(pOutput, "\tfi\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, ".PHONY: create_dirs\n");
        fprintf(pOutput, "create_dirs:\n");
        fprintf(pOutput, "\t[ ! -d $(OBJDIR) ] && mkdir -p $(OBJDIR)\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, ".PHONY: all\n");
        fprintf(pOutput, "all:  clean create_dirs $(LIBPATH)\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          G e n e r a t e  I n i t i a l  H e a d i n g
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenInitial(
        GENOSX_DATA     *this,
        ASTR_DATA       *pName,
        NODEARRAY_DATA  *pLibDeps,
        DATETIME_DATA   *pDateTime,
        FILE            *pOutput
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
        
        fprintf(pOutput, "# Generated file do not edit!\n");
        pStr = dateTime_ToString(pDateTime);
        fprintf(pOutput, "# (%s)\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        fprintf(pOutput, "\n");
        //fprintf(pOutput, "CC=clang\n");
        fprintf(pOutput, "LIBNAM=%s\n", AStr_getData(pName));
        fprintf(pOutput, "SYS=macosx\n");
        fprintf(pOutput, "TEMP=/tmp\n");
        fprintf(pOutput, "BASEDIR = $(TEMP)/$(LIBNAM)\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "CFLAGS_LIBS = \n");
        fprintf(pOutput, "CFLAGS += -g -Werror -Isrc -Isrc/$(SYS)\n");
        if (pLibDeps) {
            char            *pLibIncludePrefix = szHash_FindA(genBase_getDict(this->pBase), "libIncludePrefix");
            iMax = nodeArray_getSize(pLibDeps);
            for (i=0; i<iMax; ++i) {
                pNode = nodeArray_Get(pLibDeps, i+1);
                if (pNode) {
                    pStr = node_getData(pNode);
                    fprintf(
                            pOutput,
                            "CFLAGS += -I../%s%s/src -I../%s%s/src/$(SYS)\n",
                            pLibIncludePrefix,
                            AStr_getData(pStr),
                            pLibIncludePrefix,
                            AStr_getData(pStr)
                            );
                    fprintf(
                            pOutput,
                            "CFLAGS_LIBS += -l%s -L$(HOME)/Support/lib/$(SYS)/%s%s\n",
                            AStr_getData(pStr),
                            pLibIncludePrefix,
                            AStr_getData(pStr)
                            );
                    obj_Release(pStr);
                }
            }
        }
        fprintf(pOutput,"CFLAGS += -D__MACOSX_ENV__\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n");
        fprintf(pOutput, "INSTALLDIR = $(INSTALL_BASE)/$(LIBNAM)\n");
        fprintf(pOutput, "LIBDIR = $(BASEDIR)/$(SYS)\n");
        fprintf(pOutput, "SRCDIR = ./src\n");
        fprintf(pOutput, "SRCSYSDIR = ./src/$(SYS)\n");
        fprintf(pOutput, "ifdef  NDEBUG\n");
        fprintf(pOutput, "CFLAGS += -DNDEBUG \n");
        fprintf(pOutput, "LIB_FILENAME=$(LIBNAM)R.a\n");
        fprintf(pOutput, "OBJDIR = $(LIBDIR)/o/r\n");
        fprintf(pOutput, "else   #DEBUG\n");
        fprintf(pOutput, "CFLAGS += -D_DEBUG \n");
        fprintf(pOutput, "LIB_FILENAME=$(LIBNAM)D.a\n");
        fprintf(pOutput, "OBJDIR = $(LIBDIR)/o/d\n");
        fprintf(pOutput, "endif  #NDEBUG\n");
        fprintf(pOutput, "LIBPATH = $(LIBDIR)/$(LIB_FILENAME)\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, ".SUFFIXES:\n");
        fprintf(pOutput, ".SUFFIXES: .asm .c .o\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //         G e n e r a t e  L i b r a r y
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenLibrary(
        GENOSX_DATA     *this,
        FILE            *pOutput
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
        
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "$(LIBPATH):  $(OBJS)\n");
        fprintf(pOutput,
                "\t-cd $(LIBDIR) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)\n"
                );
        fprintf(pOutput, "\tar rc $(LIBPATH) $(OBJS)\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");
        fprintf(pOutput, "\n");

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //      G e n e r a t e  T h e  E n t i r e  M a k e f i l e
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenMakefile(
        GENOSX_DATA     *this,
        NODE_DATA       *pNodes,
        SZHASH_DATA     *pDict,
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
        NODEHASH_DATA   *pMacosx = OBJ_NIL;
        NODEHASH_DATA   *pWin32 = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        DATETIME_DATA   *pDateTime = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !genOSX_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pDateTime = genBase_getDateTime(this->pBase);
        
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
                BREAK_FALSE((obj_IsKindOf(pPrograms, OBJ_IDENT_NODEHASH)));
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
            pNode = nodeHash_FindA(pPrimaryHash, "win32");
            if (NULL == pNode) {
            }
            else {
                pNode = node_getData(pNode);
                pWin32 = node_getData(pNode);
                BREAK_FALSE((obj_IsKindOf(pWin32, OBJ_IDENT_NODEHASH)));
            }
        }
        
        genOSX_GenInitial(this, pName, pLibDeps, pDateTime, pOutput);
        genOSX_GenObjects(this, pObjects, pRoutines, pOutput);
        genOSX_GenOSSpecific(this, pMacosx, pOutput);
        genOSX_GenLibrary(this, pOutput);
        if (pPrograms) {
            genOSX_GenPrograms(this, pPrograms, pOutput);
        }
        genOSX_GenTests(this, pTests, pOutput);
        genOSX_GenFinal(this, pOutput);
        
        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //          G e n e r a t e  O b j e c t s
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenObjects(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pObjects,
        NODEARRAY_DATA  *pRoutines,
        FILE            *pOutput
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pNode;
        NODEARRAY_DATA  *pArray =  OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        int             i;
        int             iMax;
        const
        char            *pName;

        fprintf(pOutput, "\n");
        fprintf(pOutput, "OBJS =\n");
        if (pObjects) {
            eRc = nodeHash_Nodes(pObjects, &pArray);
            if (ERESULT_FAILED(eRc)) {
            }
            else {
                BREAK_FALSE((obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)));
                iMax = nodeArray_getSize(pArray);
                for (i=0; i<iMax; ++i) {
                    pNode = nodeArray_Get(pArray, i+1);
                    if (pNode) {
                        pName = node_getNameUTF8(pNode);
                        pWrk =  genBase_CompileObject(
                                                      this->pBase,
                                                      pName,
                                                      "SRCDIR",
                                                      "OBJDIR"
                                );
                        fprintf(pOutput, "%s", AStr_getData(pWrk));
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                        mem_Free((void *)pName);
                    }
                }
            }
        }
        if (pRoutines) {
            iMax = nodeArray_getSize(pRoutines);
            for (i=0; i<iMax; ++i) {
                pNode = nodeArray_Get(pRoutines, i+1);
                if (pNode) {
                    pStr = node_getData(pNode);
                    pWrk =  genBase_CompileRoutine(
                                                   this->pBase,
                                                   AStr_getData(pStr),
                                                   "SRCDIR",
                                                   "OBJDIR"
                                                   );
                    fprintf(pOutput, "%s", AStr_getData(pWrk));
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
            }
        }

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //     G e n e r a t e  O / S  S p e c i f i c
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenOSSpecific(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pSection,
        FILE            *pOutput
    )
    {
        ERESULT         eRc;
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
        
        // The "macosx" section contains the sub-sections, "headers" and "sources".
        // The "headers" need to be copied to the "macosx" subdirectory of the
        // library header. So, the subdirectory needs to be created as well as
        // the headers copied across.
        
        if (pSection) {
            eRc = nodeHash_Nodes(pSection, &pArray);
            if (ERESULT_FAILED(eRc)) {
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
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                }
            }
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
        }

        // Return to caller.
        genOSX_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //         G e n e r a t e  P r o g r a m s
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenPrograms(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pPrograms,
        FILE            *pOutput
    )
    {
        ERESULT         eRc;
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
            eRc = nodeHash_Nodes(pPrograms, &pArray);
            if (ERESULT_FAILED(eRc)) {
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
    //              G e n e r a t e  T e s t s
    //---------------------------------------------------------------
    
    ERESULT         genOSX_GenTests(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pTests,
        FILE            *pOutput
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pNode;
        NODEARRAY_DATA  *pArray =  OBJ_NIL;
        NODEARRAY_DATA  *pDeps =  OBJ_NIL;
        NODE_DATA       *pDep;
        ASTR_DATA       *pStr;
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
        
        if (pTests) {
            fprintf(pOutput, "\n");
            fprintf(pOutput, "TESTS =\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            fprintf(pOutput, "\n");
            eRc = nodeHash_Nodes(pTests, &pArray);
            if (ERESULT_FAILED(eRc)) {
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, MAIN_IDENT_GENOSX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_GENOSX);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&genOSX_Vtbl);
        
        genOSX_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

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
              
        pInfo = genOSX_Vtbl.iVtbl.pInfo;
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


