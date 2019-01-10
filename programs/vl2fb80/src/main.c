// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   main.c
 *	Generated 12/06/2018 08:18:28
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
#include        <main_internal.h>
#include        <trace.h>



#define     PROPERTY_DIROUT_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    static
    CMDUTL_OPTION       pPgmOptions[] = {
        {
            "backup",
            'n',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_INCR,
            offsetof(MAIN_DATA, fBackup),
            NULL,
            "Backup output file if it exists"
        },
        {
            "ebcdic",
            'e',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_INCR,
            offsetof(MAIN_DATA, fEbcdic),
            NULL,
            "Translate output to ebcdic"
        },
        {
            "ictl",
            'e',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_NUMBER,
            offsetof(MAIN_DATA, fEbcdic),
            NULL,
            "Continuation Column Number"
        },
        {
            "out",
            'o',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_PATH,
            offsetof(MAIN_DATA, pDirOut),
            NULL,
            "Output Directory Path"
        },
        {
            "seq",
            0,
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_INCR,
            offsetof(MAIN_DATA, fSeq),
            NULL,
            "Add sequence numbers to output"
        },
        {0}
    };
    
    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            main_task_body (
        void            *pData
    )
    {
        //MAIN_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MAIN_DATA *     main_Alloc (
        void
    )
    {
        MAIN_DATA       *this;
        uint32_t        cbSize = sizeof(MAIN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    MAIN_DATA *     main_New (
        void
    )
    {
        MAIN_DATA       *this;
        
        this = main_Alloc( );
        if (this) {
            this = main_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      A p p l i c a t i o n
    //---------------------------------------------------------------
    
    APPL_DATA *     main_getAppl(
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return (APPL_DATA *)this;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D i c t i o n a r y
    //---------------------------------------------------------------
    
    NODEBTP_DATA *  main_getDict(
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDict;
    }
    
    
    bool            main_setDict(
        MAIN_DATA       *this,
        NODEBTP_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pDict) {
            obj_Release(this->pDict);
        }
        this->pDict = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  O u t p u t  D i r e c t o r y
    //---------------------------------------------------------------
    
    PATH_DATA *     main_getDirOut(
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDirOut;
    }
    
    
    bool            main_setDirOut(
        MAIN_DATA       *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pDirOut) {
            obj_Release(this->pDirOut);
        }
        this->pDirOut = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        main_getPriority (
        MAIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            main_setPriority (
        MAIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
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
    
    uint32_t        main_getSize (
        MAIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  main_getSuperVtbl (
        MAIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
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
        ERESULT eRc = main_Assign(this,pOther);
     @endcode 
     @param     this    MAIN object pointer
     @param     pOther  a pointer to another MAIN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         main_Assign (
        MAIN_DATA		*this,
        MAIN_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!main_Validate(pOther)) {
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
    ERESULT         main_Compare (
        MAIN_DATA     *this,
        MAIN_DATA     *pOther
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
        if (!main_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!main_Validate(pOther)) {
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
        main      *pCopy = main_Copy(this);
     @endcode 
     @param     this    MAIN object pointer
     @return    If successful, a MAIN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MAIN_DATA *     main_Copy (
        MAIN_DATA       *this
    )
    {
        MAIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = main_New( );
        if (pOther) {
            eRc = main_Assign(this, pOther);
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

    void            main_Dealloc (
        OBJ_ID          objId
    )
    {
        MAIN_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MAIN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        main_setDict(this, OBJ_NIL);
        main_setDirOut(this, OBJ_NIL);

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
    
    ERESULT         main_DictAdd(
        MAIN_DATA       *this,
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (OBJ_NIL == this->pDict) {
            this->pDict = nodeBTP_New( );
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        eRc = nodeBTP_AddA(this->pDict, 0, pName, (void *)pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         main_DictAddA(
        MAIN_DATA       *this,
        const
        char            *pName,
        const
        char            *pData
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pData) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pStr = AStr_NewA(pData);
        if (OBJ_NIL == pStr) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        if (OBJ_NIL == this->pDict) {
            this->pDict = nodeBTP_New( );
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        eRc = nodeBTP_AddA(this->pDict, 0, pName, pStr);
        
        // Return to caller.
        obj_Release(pStr);
        pStr = OBJ_NIL;
        return eRc;
    }
    
    
    ERESULT         main_DictAddUpdate(
        MAIN_DATA       *this,
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (OBJ_NIL == this->pDict) {
            this->pDict = nodeBTP_New( );
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        if (nodeBTP_FindA(this->pDict, 0, pName)) {
            eRc = nodeBTP_DeleteA(this->pDict, 0, pName);
        }
        eRc = nodeBTP_AddA(this->pDict, 0, pName, (void *)pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         main_DictAddUpdateA(
        MAIN_DATA        *this,
        const
        char            *pName,
        const
        char            *pData
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pStr = AStr_NewA(pData);
        if (OBJ_NIL == pStr) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        if (OBJ_NIL == this->pDict) {
            this->pDict = nodeBTP_New( );
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        if (nodeBTP_FindA(this->pDict, 0, pName)) {
            eRc = nodeBTP_DeleteA(this->pDict, 0, pName);
        }
        eRc = nodeBTP_AddA(this->pDict, 0, pName, pStr);
        
        // Return to caller.
        obj_Release(pStr);
        pStr = OBJ_NIL;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         main_Disable (
        MAIN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!main_Validate(this)) {
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

    ERESULT         main_Enable (
        MAIN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!main_Validate(this)) {
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
    //                          E x e c
    //---------------------------------------------------------------
    
    int             main_Exec (
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        int             iRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        char            *pChrStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = main_ParseArgsDefault(this);
        if (ERESULT_FAILED(eRc)) {
            appl_Usage((APPL_DATA *)this, "ERROR - Failed to properly set defaults!");
            exit(8);
        }
        
        for (;;) {
            
            fRc = appl_IsMore((APPL_DATA *)this);
            if (!fRc) {
                break;
            }
            
            eRc = appl_ProcessOptions((APPL_DATA *)this);
            if (ERESULT_FAILED(eRc)) {
                appl_Usage((APPL_DATA *)this, "ERROR - Failed to properly parse command line!");
                exit(8);
            }
            
            pChrStr = appl_NextArg((APPL_DATA *)this);
            if (NULL == pChrStr) {
                break;
            }
            pStr = AStr_NewA(pChrStr);
            iRc = main_ProcessArg(this, pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
            if (iRc) {
                return iRc;
            }
        }
        
        // Return to caller.
        return 0;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    MAIN_DATA *   main_Init (
        MAIN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(MAIN_DATA);
        
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

        this = (OBJ_ID)appl_Init((APPL_DATA *)this);    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MAIN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                      // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_MAIN);     // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&main_Vtbl);
        
        this->pDict = nodeBTP_New( );
        if (OBJ_NIL == this->pDict) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        appl_setUsage(
                      (APPL_DATA *)this,
                      this,
                      (void *)main_UsageDesc,
                      (void *)main_UsageProgLine,
                      (void *)main_UsageOptions
        );

    #ifdef NDEBUG
    #else
        if (!main_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "main::sizeof(MAIN_DATA) = %lu\n", sizeof(MAIN_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(MAIN_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         main_IsEnabled (
        MAIN_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
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
    //              P a r s e  A r g s  D e f a u l t
    //---------------------------------------------------------------
    
    ERESULT         main_ParseArgsDefault (
        MAIN_DATA        *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
      
#if defined(__MACOSX_ENV__)
        pStr = AStr_NewA("$(HOME)/Support/out");
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        pStr = AStr_NewA("C:/out");
#endif
        if (pStr) {
            eRc = nodeBTP_AddA(main_getDict(this), 0, outBaseID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        outBaseID
                        );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        this->fSeq = 1;
        this->seqBgn = 1000;
        this->seqInc = 1000;
        this->ictl = 16;

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    //---------------------------------------------------------------
    //              P r o c e s s  A r g
    //---------------------------------------------------------------
    
    ERESULT         main_ProcessArg(
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    )
    {
        PATH_DATA       *pPath = OBJ_NIL;
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pDrive = OBJ_NIL;
        PATH_DATA       *pDir = OBJ_NIL;
        PATH_DATA       *pFileName = OBJ_NIL;
        PATH_DATA       *pArgDir = OBJ_NIL;
        ASTR_DATA       *pDrvOut = OBJ_NIL;
        PATH_DATA       *pDirOut = OBJ_NIL;
        PATH_DATA       *pPathOut = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (appl_getDebug((APPL_DATA *)this)) {
            if (pStr) {
                fprintf(stderr, "\tArg = (%d)%s\n", AStr_getLength(pStr), AStr_getData(pStr));
            }
            else {
                fprintf(stderr, "\tArg = NULL\n");
            }
        }

        if (!appl_getQuiet((APPL_DATA *)this)) {
            fprintf(stderr, "\tProcessing - %s...\n", AStr_getData(pStr));
        }
        
        pPath = path_NewFromAStr(pStr);
        appl_ErrorFatalOnBool(
                              (OBJ_NIL == pPath),
                              "FATAL - Failed to create path \"from\" \n"
                              );
        eRc = path_Clean(pPath);
        appl_ErrorFatalOnEresult(
                                 eRc,
                                 "FATAL - File, %s, does not exist or is not a file!\n",
                                 path_getData(pPath)
                                 );
        eRc = path_IsFile(pPath);
        appl_ErrorFatalOnEresult(
                                 eRc,
                                 "FATAL - File, %s, does not exist or is not a file!\n",
                                 path_getData(pPath)
                                 );
        eRc = path_SplitPath(pPath, &pDrive, &pDir, &pFileName);
        appl_ErrorFatalOnEresult(
                                 eRc,
                                 "FATAL - Unable to extract directory from File, %s!\n",
                                 path_getData(pPath)
                                 );
        pArgDir = path_NewFromDriveDirFilename(pDrive, pDir, OBJ_NIL);
        appl_ErrorFatalOnBool(
                              (OBJ_NIL == pArgDir),
                              "FATAL - Unable to extract directory from File, %s!\n",
                              path_getData(pPath)
                              );
        eRc = main_DictAddA(this, srcBaseID, (void *)pArgDir);
        appl_ErrorFatalOnEresult(
                                 eRc,
                                 "FATAL - Failed to add 'srcBaseID' to Dictionary!\n"
                                 );

        eRc = main_DictAddA(this, srcFileID, path_getData(pPath));
        appl_ErrorFatalOnEresult(
                                 eRc,
                                 "FATAL - Failed to add 'srcFile' to Dictionary!\n"
        );
        
        eRc = path_SplitPath(this->pDirOut, &pDrvOut, &pDirOut, OBJ_NIL);
        appl_ErrorFatalOnEresult(
                                 eRc,
                                 "FATAL - Unable to extract info from Output Dir, %s!\n",
                                 path_getData(pPath)
                                 );
        if (appl_getDebug((APPL_DATA *)this)) {
            if (pDrvOut) {
                fprintf(stderr, "\tDrvOut = \"%s\"\n", AStr_getData(pDrvOut));
            }
            if (pDirOut) {
                fprintf(stderr, "\tDirOut = \"%s\"\n", path_getData(pDirOut));
            }
        }
        pPathOut = path_NewFromDriveDirFilename(pDrvOut, pDirOut, pFileName);
        appl_ErrorFatalOnBool(
                              (OBJ_NIL == pPathOut),
                              "FATAL - Unable to create output file path, %s!\n",
                              path_getData(pPathOut)
        );
        obj_Release(pDrvOut);
        pDrvOut = OBJ_NIL;
        obj_Release(pDirOut);
        pDirOut = OBJ_NIL;
        eRc = path_Clean(pPathOut);
        eRc = path_IsDir(pPathOut);
        appl_ErrorFatalOnBool(
                              (!ERESULT_FAILED(eRc)),
                              "FATAL - Output file path, %s, is a directory!\n",
                              path_getData(pPathOut)
                              );
        eRc = path_IsFile(pPathOut);
        if (!ERESULT_FAILED(eRc) && this->fBackup) {
            eRc = path_VersionedRename(pPathOut);
        }
        eRc = path_Delete(pPathOut);

        eRc = main_ProcessRecords(this, pPath, pPathOut);
        
        // Return to caller.
        obj_Release(pPathOut);
        pPathOut = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pArgDir);
        pArgDir = OBJ_NIL;
        obj_Release(pDrive);
        pDrive = OBJ_NIL;
        obj_Release(pDir);
        pDrive = OBJ_NIL;
        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                   P r o c e s s  R e c o r d s
    //---------------------------------------------------------------
    
    ERESULT         main_ProcessRecords (
        MAIN_DATA       *this,
        PATH_DATA       *pPathIn,
        PATH_DATA       *pPathOut
    )
    {
        ERESULT         eRc;
        FILEIO_DATA     *pIn;
        RRDS_DATA       *pOut;
        uint32_t        seqNum = this->seqBgn;
        uint8_t         rcdOut[81];
        uint8_t         rcdIn[512];
        uint32_t        rrdsRcd = 0;
        uint32_t        inSize;
        bool            fContinued = false;
        int             beg;
        int             max;
        uint8_t         *pCurChr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPathIn) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (OBJ_NIL == pPathOut) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        rcdOut[80] = '\0';
        if (appl_getVerbose((APPL_DATA *)this)) {
            fprintf(stderr, "\tCreating file, %s\n", path_getData(pPathOut));
        }
        
        pIn = fileio_New( );
        if (OBJ_NIL == pIn) {
            return ERESULT_OUT_OF_MEMORY;
        }
        eRc = fileio_Open(pIn, pPathIn);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pIn);
            return eRc;
        }

        pOut = rrds_New();
        if (OBJ_NIL == pOut) {
            obj_Release(pIn);
            return ERESULT_OUT_OF_MEMORY;
        }
        eRc = rrds_Create(pOut, pPathOut, 0);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pIn);
            obj_Release(pOut);
           return eRc;
        }

        for (;;) {
            // Read the next input record.
            eRc = fileio_Gets(pIn, sizeof(rcdIn), rcdIn);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(pIn);
                obj_Release(pOut);
                return eRc;
            }
            
            // Create one or more output records from it.
            inSize = utf8_StrLenA((const char *)rcdIn);
            if (0 == inSize) {
                break;
            }
            fContinued = false;
            fprintf(stderr, "in:  %3d \"%s\"\n", inSize, rcdIn);
            pCurChr = rcdIn;
            while (inSize) {
                memset(rcdOut, ' ', (71 - 1 + 1));
                beg = 0;
                if (fContinued) {
                    beg = this->ictl - 1;
                }
                max = 71 - beg;
                if (max > inSize)
                    max = inSize;
                //if (beg)
                    //memset(rcdOut, ' ', (beg + 1));
                memmove((rcdOut + beg), pCurChr, max);
                inSize -= max;
                pCurChr += max;
                if (inSize > 0) {
                    fContinued = true;
                    rcdOut[71] = 'X';
                }
                else
                    rcdOut[71] = ' ';
                if (this->fSeq) {
                    char            seq[11];
                    dec_Uint32ToChr(seqNum, seq);
                    memmove(rcdOut+72, seq+2, (80 - 73 + 1));
                    seqNum += this->seqInc;
                }
                else
                    memset(rcdOut+72, ' ', (80 - 73 + 1));
                if (this->fEbcdic) {
                    TranslateAsciiToEbcdic(80, rcdOut);
                }
                fprintf(stderr, "out: %2d \"%s\"\n", rrdsRcd, rcdOut);
                eRc = rrds_RecordWrite(pOut, ++rrdsRcd, rcdOut);
                if (ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    obj_Release(pIn);
                    obj_Release(pOut);
                    return eRc;
                }
            }
        }
        
        eRc = fileio_Close(pIn, false);
        obj_Release(pIn);
        pIn = OBJ_NIL;
        eRc = rrds_Close(pOut, false);
        obj_Release(pOut);
        pOut = OBJ_NIL;

        // Return to caller.
        return ERESULT_SUCCESS;
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
        void        *pMethod = main_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "main", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          main_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MAIN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(MAIN_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)main_Class();
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
                            return main_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return main_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return main_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return main_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == main_ToDebugString)
                    return "ToDebugString";
                if (pData == main_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                  S e t u p  F r o m  A r g V
    //---------------------------------------------------------------
    
    ERESULT         main_SetupFromArgV(
        MAIN_DATA       *this,
        uint16_t        cArgs,
        char            *ppArgV[],
        char            **ppEnv
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = appl_SetupFromArgV((APPL_DATA *)this, cArgs, ppArgV, ppEnv, pPgmOptions);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     main_ToJSON (
        MAIN_DATA      *this
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!main_Validate(this)) {
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
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = main_ToDebugString(this,4);
     @endcode 
     @param     this    MAIN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     main_ToDebugString (
        MAIN_DATA      *this,
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
        if (!main_Validate(this)) {
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
                    main_getSize(this)
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
    //                  U s a g e  H e l p
    //---------------------------------------------------------------
    
    /*!
     Print the program description with a trailing '\n' and leading "  ".
     @param     this        Object Pointer
     @param     pOutput     File to write to
     @param     pPgmPath    Program's Path
     @return    ERESULT_SUCCESS if successful, otherwise, an ERESULT_*
     error code.
     */
    ERESULT         main_UsageDesc(
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pPgmPath
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        fprintf(
                pOutput,
                "  Generate a make or nmake file for the object system created\n"
                "  in libCmn given an input json file.\n"
                );
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    // Note: --debug(-d), --force(-f), --help(-?,-h), --verbose(-v) are already
    //      taken care of in appl_Usage().
    ERESULT         main_UsageOptions(
        MAIN_DATA       *this,
        FILE            *pOutput
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        fprintf(pOutput, "  -b, --backup       Backup the output file if present\n");
        fprintf(pOutput, "  -e, --ebcdic       Translate the output to EBCDIC\n");
        fprintf(pOutput, "  -o, --out dir      Output the generated data to <directory>\n");
        fprintf(pOutput, "  --seq              Generate sequence numbers (default)\n");

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    /*!
     Print the program usage line with a trailing '\n' and leading "  ".
     @param     this        Object Pointer
     @param     pOutput     File to write to
     @param     pPgmPath    Program's Path
     @param     pNameA      Program's name
     @return    ERESULT_SUCCESS if successful, otherwise, an ERESULT_*
     error code.
     */
    ERESULT         main_UsageProgLine(
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pPgmPath,
        const
        char            *pNameA
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        fprintf(pOutput, "  %s [options] input_path(s)\n", pNameA);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            main_Validate (
        MAIN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_MAIN))
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


        if (!(obj_getSize(this) >= sizeof(MAIN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


