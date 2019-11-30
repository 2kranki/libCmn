// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   GenMac.c
 *	Generated 11/23/2019 12:07:26
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
#include        <GenMac_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            GenMac_task_body (
        void            *pData
    )
    {
        //GENMAC_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    GENMAC_DATA *     GenMac_Alloc (
        void
    )
    {
        GENMAC_DATA       *this;
        uint32_t        cbSize = sizeof(GENMAC_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    GENMAC_DATA *     GenMac_New (
        void
    )
    {
        GENMAC_DATA       *this;
        
        this = GenMac_Alloc( );
        if (this) {
            this = GenMac_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      G e n B a s e
    //---------------------------------------------------------------
    
    GENBASE_DATA *  GenMac_getGenBase (
        GENMAC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return (GENBASE_DATA *)this;
    }
        
        
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        GenMac_getPriority (
        GENMAC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            GenMac_setPriority (
        GENMAC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
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
    
    uint32_t        GenMac_getSize (
        GENMAC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * GenMac_getStr (
        GENMAC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        GenMac_setStr (
        GENMAC_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  GenMac_getSuperVtbl (
        GENMAC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
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
        ERESULT eRc = GenMac_Assign(this,pOther);
     @endcode 
     @param     this    GENMAC object pointer
     @param     pOther  a pointer to another GENMAC object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         GenMac_Assign (
        GENMAC_DATA		*this,
        GENMAC_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!GenMac_Validate(pOther)) {
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
    ERESULT         GenMac_Compare (
        GENMAC_DATA     *this,
        GENMAC_DATA     *pOther
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
        if (!GenMac_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!GenMac_Validate(pOther)) {
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
        GenMac      *pCopy = GenMac_Copy(this);
     @endcode 
     @param     this    GENMAC object pointer
     @return    If successful, a GENMAC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    GENMAC_DATA *     GenMac_Copy (
        GENMAC_DATA       *this
    )
    {
        GENMAC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = GenMac_New( );
        if (pOther) {
            eRc = GenMac_Assign(this, pOther);
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

    void            GenMac_Dealloc (
        OBJ_ID          objId
    )
    {
        GENMAC_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((GENMAC_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        GenMac_setStr(this, OBJ_NIL);

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
    ERESULT         GenMac_Disable (
        GENMAC_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!GenMac_Validate(this)) {
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
    ERESULT         GenMac_Enable (
        GENMAC_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!GenMac_Validate(this)) {
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

    ERESULT_DATA *  GenMac_GenBuildTest (
        GENMAC_DATA     *this,
        NODETSTA_DATA   *pTest
    )
    {
        //ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        ASTRC_DATA      *pSuffix;
        ASTRC_DATA      *pSrcDirPrefix;
        ASTRC_DATA      *pTstDirPrefix;

            // Do initialization.
        #ifdef NDEBUG
        #else
        if (!GenMac_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if (OBJ_NIL == pTest) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
        if (!obj_IsKindOf(pTest, OBJ_IDENT_NODETSTA)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
    #endif
        
        // Skip disabled entries.
        if (!NodeTstA_IsEnabled(pTest)) {
            return OBJ_NIL;
        }
        
        // Set up to generate Makefile entry.
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
        }
        pSuffix = NodeTstA_getSuffix(pTest);
        pSrcDirPrefix = AStrC_NewFromPrint("$(%s)/", AStrC_getData(this->pSrcDir));
        pTstDirPrefix = AStrC_NewFromPrint("$(%s)/", AStrC_getData(this->pTstDir));

        AStr_AppendPrint(
            pStr,
            "%s += %s\n\n",
            AStrC_getData(this->pTstVar),
            AStrC_getData(NodeTstA_getName(pTest))
        );
        if ((AStrC_CompareA(pSuffix, "c") == ERESULT_SUCCESS_EQUAL)
            || (AStrC_CompareA(pSuffix, "C") == ERESULT_SUCCESS_EQUAL)
            || (AStrC_CompareA(pSuffix, "cpp") == ERESULT_SUCCESS_EQUAL)
            || (AStrC_CompareA(pSuffix, "CPP") == ERESULT_SUCCESS_EQUAL)) {
            ASTR_DATA       *pDeps = NodeTstA_Deps(pTest, AStrC_getData(pTstDirPrefix));
            ASTR_DATA       *pSrcs = NodeTstA_Srcs(pTest, AStrC_getData(pTstDirPrefix));
            AStr_AppendPrint(
                pStr,
                "%s: %s%s.%s ",
                AStrC_getData(NodeTstA_getName(pTest)),
                AStrC_getData(pTstDirPrefix),
                AStrC_getData(NodeTstA_getName(pTest)),
                AStrC_getData(pSuffix)
            );
            if (pDeps) {
                AStr_AppendPrint(pStr, "%s", AStr_getData(pDeps));
            }
            AStr_AppendA(pStr, "\n");
            AStr_AppendPrint(
                pStr,
                "\t$(CC) $(CFLAGS) $(TEST_FLGS) -o $(%s)/$(@F) $(%s)",
                AStrC_getData(this->pTstBin),
                AStrC_getData(this->pObjVar)
            );
            if (pSrcs) {
                AStr_AppendPrint(pStr, " %s", AStr_getData(pSrcs));
            }
            AStr_AppendA(pStr, " $<\n");
            AStr_AppendPrint(
                pStr,
                "\t$(%s)/$(@F)\n\n",
                AStrC_getData(this->pTstBin)
            );
            obj_Release(pDeps);
            obj_Release(pSrcs);
        }
        else {
            obj_Release(pSrcDirPrefix);
            obj_Release(pTstDirPrefix);
            obj_Release(pStr);
            return eResult_NewStrA(ERESULT_UNSUPPORTED_PARAMETER, "Invalid File Suffix");
        }
        GenBase_Output(GenMac_getGenBase(this), pStr);
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        // Return to caller.
        obj_Release(pSrcDirPrefix);
        obj_Release(pTstDirPrefix);
        return OBJ_NIL;
    }



    ERESULT_DATA *  GenMac_GenCompileRtn (
        GENMAC_DATA     *this,
        NODERTNA_DATA   *pRtn
    )
    {
        ASTR_DATA       *pStr =  OBJ_NIL;
        ASTRC_DATA      *pSuffix;
        ASTRC_DATA      *pSrcDirPrefix;

            // Do initialization.
        #ifdef NDEBUG
        #else
        if (!GenMac_Validate(this)) {
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
        
        // Skip disabled entries.
        if (!NodeRtnA_IsEnabled(pRtn)) {
            return OBJ_NIL;
        }
        
        // Set up to generate Makefile entry.
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
        }
        pSuffix = NodeRtnA_getSuffix(pRtn);
        pSrcDirPrefix = AStrC_NewFromPrint("$(%s)/", AStrC_getData(this->pSrcDir));

        AStr_AppendPrint(
            pStr,
            "%s += $(%s)/%s.o\n\n",
            AStrC_getData(this->pObjVar),
            AStrC_getData(this->pObjDir),
            AStrC_getData(NodeRtnA_getName(pRtn))
        );
        if ((AStrC_CompareA(pSuffix, "c") == ERESULT_SUCCESS_EQUAL)
           || (AStrC_CompareA(pSuffix, "C") == ERESULT_SUCCESS_EQUAL)) {
            ASTR_DATA       *pDeps = NodeRtnA_Deps(pRtn, AStrC_getData(pSrcDirPrefix));
            ASTR_DATA       *pSrcs = NodeRtnA_Srcs(pRtn, AStrC_getData(pSrcDirPrefix));
            AStr_AppendPrint(
                pStr,
                "$(%s)/%s.o: %s%s.%s ",
                AStrC_getData(this->pObjDir),
                AStrC_getData(NodeRtnA_getName(pRtn)),
                AStrC_getData(pSrcDirPrefix),
                AStrC_getData(NodeRtnA_getName(pRtn)),
                AStrC_getData(pSuffix)
            );
            if (pDeps) {
                AStr_AppendPrint(
                    pStr,
                    "%s",
                    AStr_getData(pDeps)
                );
            }
            AStr_AppendPrint(pStr, "\n");
            AStr_AppendPrint(
                pStr,
                "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $< ",
                AStrC_getData(this->pObjDir)
            );
            if (pSrcs) {
                AStr_AppendPrint(
                    pStr,
                    "%s",
                    AStr_getData(pSrcs)
                );
            }
            AStr_AppendPrint(pStr, "\n\n");
            obj_Release(pDeps);
            obj_Release(pSrcs);
        }
        else if (  (AStrC_CompareA(pSuffix, "asm") == ERESULT_SUCCESS_EQUAL)
                || (AStrC_CompareA(pSuffix, "ASM") == ERESULT_SUCCESS_EQUAL)
                || (AStrC_CompareA(pSuffix, "s") == ERESULT_SUCCESS_EQUAL)
                || (AStrC_CompareA(pSuffix, "S") == ERESULT_SUCCESS_EQUAL)) {
           AStr_AppendPrint(
               pStr,
               "$(%s)/%s.o: %s%s.%s ",
               AStrC_getData(this->pObjDir),
               AStrC_getData(NodeRtnA_getName(pRtn)),
               AStrC_getData(pSrcDirPrefix),
               AStrC_getData(NodeRtnA_getName(pRtn)),
               AStrC_getData(pSuffix)
           );
           AStr_AppendPrint(
               pStr,
               "\t$(AS) $(AFLAGS) -o $(%s)/$(@F) $< ",
               AStrC_getData(this->pObjDir)
           );
           AStr_AppendPrint(pStr, "\n\n");
        }
        //TODO: Put in support for other language types.
        /*****
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
         ***/
        GenBase_Output(GenMac_getGenBase(this), pStr);
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        // Return to caller.
        obj_Release(pSrcDirPrefix);
        return OBJ_NIL;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    GENMAC_DATA *   GenMac_Init (
        GENMAC_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(GENMAC_DATA);
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

        this = (OBJ_ID)GenBase_Init((GENBASE_DATA *)this);  // Needed for Inheritance
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&GenMac_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

    #ifdef NDEBUG
    #else
        if (!GenMac_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "GenMac::sizeof(GENMAC_DATA) = %lu\n", sizeof(GENMAC_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(GENMAC_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         GenMac_IsEnabled (
        GENMAC_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
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
        void        *pMethod = GenMac_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "GenMac", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          GenMac_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        GENMAC_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(GENMAC_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)GenMac_Class();
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
                            return GenMac_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return GenMac_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return GenMac_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return GenMac_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == GenMac_ToDebugString)
                    return "ToDebugString";
                if (pData == GenMac_ToJSON)
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
    
     ASTR_DATA *     GenMac_ToJSON (
        GENMAC_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
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
        ASTR_DATA      *pDesc = GenMac_ToDebugString(this,4);
     @endcode 
     @param     this    GENMAC object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     GenMac_ToDebugString (
        GENMAC_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenMac_Validate(this)) {
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
                    GenMac_getSize(this)
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            GenMac_Validate (
        GENMAC_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_GENMAC))
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


        if (!(obj_getSize(this) >= sizeof(GENMAC_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


