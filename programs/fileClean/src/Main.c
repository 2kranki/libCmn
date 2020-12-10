// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   main.c
 *	Generated 07/17/2017 14:59:49
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
#include        <Main_internal.h>
#include        <Dir.h>
#include        <File.h>
#include        <JsonIn.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    ERESULT         Main_Defaults (
        MAIN_DATA       *this
    );


    static
    CMDUTL_OPTION       pPgmOptions[] = {
        {
            "backup",
            'n',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_INCR,
            0,                              // Constant
            offsetof(MAIN_DATA, fBackup),
            NULL,
            "Backup output file if it exists"
        },
        {
            "file",
            'f',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_PATH,
            0,                              // Constant
            offsetof(MAIN_DATA, pFilePath),
            NULL,
            "Input File Path"
        },
        {
            "out",
            'o',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_PATH,
            0,                              // Constant
            offsetof(MAIN_DATA, pOutputPath),
            NULL,
            "Output File Path"
        },
        {
            "recurse",
            'r',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_INCR,
            0,                              // Constant
            offsetof(MAIN_DATA, fBackup),
            NULL,
            "Backup output file if it exists"
        },
        {0}
    };
    

    
    
 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                D e f a u l t  R o u t i n e s
    //---------------------------------------------------------------
    
    ERESULT         Main_Defaults (
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = OBJ_NIL;
        const
        char            *pKey;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        /********
        this->osType = OSTYPE_MSC64;
        pKey = osTypeID;
        pStr = AStr_NewA("msc64");
        if (pStr) {
            eRc = NodeHash_AddUpdateA(Dict_getNodeHash(Main_getDict(this)), 0, pKey, pStr);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", pKey);
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        //FIXME: eRc = Dict_AddUpdate(this, "outBase", "\\\\C:\\");
        if (ERESULT_FAILED(eRc) ) {
            fprintf(stderr, "FATAL - Failed to add 'outBase' to Dictionary\n");
            exit(EXIT_FAILURE);
        }
        
        //FIXME: eRc = Dict_AddUpdate(this, "tmpBase", "\\TEMP");
        if (ERESULT_FAILED(eRc) ) {
            fprintf(stderr, "FATAL - Failed to add 'tmpBase' to Dictionary\n");
            exit(EXIT_FAILURE);
        }
         *****/
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MAIN_DATA *     Main_Alloc (
    )
    {
        MAIN_DATA       *this;
        uint32_t        cbSize = sizeof(MAIN_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    MAIN_DATA *     Main_New (
        void
    )
    {
        MAIN_DATA       *this;
        
        this = Main_Alloc( );
        if (this) {
            this = Main_Init(this);
        }
        return this;
    }
    
    
    MAIN_DATA *     Main_NewFromArgV(
        uint16_t        cArgs,
        char            **ppArgs,
        char            **ppEnv
    )
    {
        MAIN_DATA       *this;
        ERESULT         eRc;
        
        this = Main_Alloc( );
        if (this) {
            this = Main_Init(this);
            if (this) {
                eRc = Main_SetupFromArgV(this, cArgs, ppArgs, ppEnv);
            }
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      A p p l i c a t i o n
    //---------------------------------------------------------------
    
    APPL_DATA *     Main_getAppl (
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return (APPL_DATA *)this;
    }
    
    
    
    //---------------------------------------------------------------
    //                  F i l e  P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *     Main_getFilePath (
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pFilePath;
    }
    
    
    bool            Main_setFilePath (
        MAIN_DATA       *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pFilePath) {
            obj_Release(this->pFilePath);
        }
        this->pFilePath = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N o d e s
    //---------------------------------------------------------------
    
    NODE_DATA *     Main_getNodes (
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pNodes;
    }
    
    
    bool            Main_setNodes (
        MAIN_DATA       *this,
        NODE_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pNodes) {
            obj_Release(this->pNodes);
        }
        this->pNodes = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O u t p u t
    //---------------------------------------------------------------
    
    TEXTOUT_DATA *  Main_getOutput (
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pOutput;
    }
    
    
    bool            Main_setOutput (
        MAIN_DATA       *this,
        TEXTOUT_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pOutput) {
            obj_Release(this->pOutput);
        }
        this->pOutput = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  O u t p u t  P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *     Main_getOutputPath (
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pOutputPath;
    }
    
    
    bool            Main_setOutputPath (
        MAIN_DATA       *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pOutputPath) {
            obj_Release(this->pOutputPath);
        }
        this->pOutputPath = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Main_getPriority (
        MAIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Main_setPriority (
        MAIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          S i z e
    //---------------------------------------------------------------
    
    uint32_t        Main_getSize (
        MAIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     Main_getStr (
        MAIN_DATA       *this
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (OBJ_NIL == this->pOutput) {
            return OBJ_NIL;
        }
        
        if (TextOut_IsString(this->pOutput))
            pStr = TextOut_getStr(this->pOutput);
        
        return pStr;
    }
    
    

    //---------------------------------------------------------------
    //                          V e r b o s e
    //---------------------------------------------------------------
    
    int             Main_getVerbose (
        MAIN_DATA       *this
    )
    {
        int             iRc = -1;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return iRc;
        }
#endif
        
        iRc = Appl_getVerbose((APPL_DATA *)this);
        
        return iRc;
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
        ERESULT eRc = Main__Assign(this,pOther);
     @endcode
     @param     this    MAIN object pointer
     @param     pOther  a pointer to another MAIN object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         Main_Assign (
        MAIN_DATA		*this,
        MAIN_DATA       *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !Main_Validate(pOther) ) {
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
    //               C h e c k  I n p u t  P a t h
    //---------------------------------------------------------------

    PATH_DATA *     Main_CheckInputPath (
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pDrive = OBJ_NIL;
        PATH_DATA       *pDir = OBJ_NIL;
        PATH_DATA       *pFileName = OBJ_NIL;
        PATH_DATA       *pArgDir = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        TRC_OBJ(this, "Main_CreateOutputPath(%s)\n", pStr ? AStr_getData(pStr) : "");
        
        pPath = Path_NewFromAStr(pStr);
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == pPath),
                    "FATAL - Failed to create path \"from\" \n"
        );
        eRc = Path_Clean(pPath);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - File, %s, does not exist or is not a file!\n",
                    Path_getData(pPath)
        );
        eRc = Path_IsFile(pPath);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - File, %s, does not exist or is not a file!\n",
                    Path_getData(pPath)
        );
        eRc = Path_SplitPath(pPath, &pDrive, &pDir, &pFileName);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - Unable to extract directory from File, %s!\n",
                    Path_getData(pPath)
        );
        pArgDir = Path_NewFromDriveDirFilename(pDrive, pDir, OBJ_NIL);
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == pArgDir),
                    "FATAL - Unable to extract directory from File, %s!\n",
                    Path_getData(pPath)
        );

        // Return to caller.
        obj_Release(pArgDir);
        pArgDir = OBJ_NIL;
        obj_Release(pDrive);
        pDrive = OBJ_NIL;
        obj_Release(pDir);
        pDrive = OBJ_NIL;
        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        return pPath;
    }
            
            
            
    //---------------------------------------------------------------
    //                   C l e a n  F i l e
    //---------------------------------------------------------------

    ERESULT             Main_CleanFile (
        MAIN_DATA           *this,
        PATH_DATA           *pPath
    )
    {
        ERESULT             eRc = ERESULT_SUCCESS;
        FILE                *pFileIn = NULL;
        FILE                *pFileOut = NULL;
        PATH_DATA           *pPathOut = OBJ_NIL;
        ASTR_DATA           *pDrive = OBJ_NIL;
        PATH_DATA           *pDir = OBJ_NIL;
        PATH_DATA           *pFileName = OBJ_NIL;
        const
        char                *pFileNameA = "file_clean_temp";
        const
        char                *pFileExtA = "txt";
        uint32_t            TotalRead = 0;
        uint32_t            TotalWrite = 0;
        int32_t             chrWrk;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
#endif
        eRc = Path_Clean(pPath);
        if (ERESULT_FAILED(eRc)) {
            goto Exit00;
        }
        eRc = Path_SplitPath(pPath, &pDrive, &pDir, &pFileName);
        if (ERESULT_FAILED(eRc)) {
            goto Exit00;
        }

        // Open the input file.
        pFileIn = fopen(Path_getData(pPath), "rb");
        if (NULL == pFileIn) {
            if (Appl_getDebug(Main_getAppl(this))) {
                fprintf(stderr, "ERROR - Could not open %s!\n\n\n", Path_getData(pPath));
            }
            eRc = ERESULT_OPEN_ERROR;
            goto Exit00;
        }

        // Open the output file.
        pPathOut =  Path_NewFromComponentsA(
                                            pDrive ? AStr_getData(pDrive) : NULL,
                                            pDir ? Path_getData(pDir) : NULL,
                                            pFileNameA,
                                            pFileExtA
                    );
        if (OBJ_NIL == pPathOut) {
            if (Appl_getDebug(Main_getAppl(this))) {
                fprintf(stderr, "ERROR - Out of memory!\n\n\n");
            }
            eRc = ERESULT_OPEN_ERROR;
            goto Exit00;
        }
        pFileOut = fopen(Path_getData(pPathOut), "w");
        if (NULL == pFileOut) {
            if (Appl_getDebug(Main_getAppl(this))) {
                fprintf(stderr, "ERROR - Could not open %s!\n\n\n", Path_getData(pPath));
            }
            eRc = ERESULT_OPEN_ERROR;
            goto Exit00;
        }

        // Remove high order bits and insure Linux/Unix style EOL.
        for ( ;; ) {

            // Get the next byte.
            chrWrk = fgetc(pFileIn);
            if (-1 == chrWrk)               // EOF
                break;
            ++TotalRead;
            chrWrk &= 0x7F;
            if( chrWrk == 0x1A )            //*** CP/M EOF ***
                break;
            if( (chrWrk >= ' ') && (chrWrk < 0x7F) )
                ;
            else if( (chrWrk == '\f' ) || (chrWrk == '\n') || (chrWrk == '\t') )
                ;
            else
                continue;

            // Put the byte.
            fputc(chrWrk, pFileOut);
            ++TotalWrite;
        }

        // Close the file and do clean up.
        fclose(pFileIn);
        pFileIn = NULL;
        fclose(pFileOut);
        pFileOut = NULL;
        if (Appl_getDebug(Main_getAppl(this)))
            goto Exit00;
        eRc = File_DeleteA(Path_getData(pPath));
        if (ERESULT_OK(eRc)) {
            eRc = File_RenameA(Path_getData(pPathOut), Path_getData(pPath));
        }
        if( !Appl_getQuiet(Main_getAppl(this)) || Appl_getDebug(Main_getAppl(this)) ) {
            fprintf( stderr, "\t\tTotal Characters Read    = %d\n", TotalRead );
            fprintf( stderr, "\t\tTotal Characters Written = %d\n", TotalWrite );
        }

        // Return to Caller.
        eRc = ERESULT_SUCCESS;
    Exit00:
        if (pFileIn) {
            fclose(pFileIn);
            pFileIn = NULL;
        }
        if (pFileOut) {
            fclose(pFileOut);
            pFileOut = NULL;
        }
        obj_Release( pPathOut );
        obj_Release( pDrive );
        obj_Release( pDir );
        obj_Release( pFileName );
        return eRc;
    }



    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        main      *pCopy = Main_Copy(this);
     @endcode
     @param     this    MAIN object pointer
     @return    If successful, a MAIN object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the MAIN object.
     */
    MAIN_DATA *     Main_Copy (
        MAIN_DATA       *this
    )
    {
        MAIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Main_New( );
        if (pOther) {
            eRc = Main_Assign(this, pOther);
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
    //               C r e a t e  O u t p u t  P a t h
    //---------------------------------------------------------------

    PATH_DATA *     Main_CreateOutputPath (
        MAIN_DATA       *this,
        ASTR_DATA       *pStr,
        const
        char            *pOsNameA
    )
    {
        PATH_DATA       *pPath = OBJ_NIL;
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pDrive = OBJ_NIL;
        PATH_DATA       *pDir = OBJ_NIL;
        PATH_DATA       *pFileName = OBJ_NIL;
        PATH_DATA       *pMakefile = OBJ_NIL;
        PATH_DATA       *pMakepath = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        pPath = Path_NewFromAStr(pStr);
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == pPath),
                    "FATAL - Failed to create path \"from\" \n"
        );
        eRc = Path_Clean(pPath);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - File, %s, does not exist or is not a file!\n",
                    Path_getData(pPath)
        );
        eRc = Path_SplitPath(pPath, &pDrive, &pDir, &pFileName);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - Unable to extract directory from File, %s!\n",
                    Path_getData(pPath)
        );

        // Create the output file path if given.
        pMakefile = Path_NewA("Makefile.");
        if (OBJ_NIL == pMakefile) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL - Unable to create Makefile name!\n"
                    );
            exit(EXIT_FAILURE);
        }
        eRc = Path_AppendA(pMakefile, this->pOsName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(
                    stderr,
                    "FATAL - Unable to create Makefile name!\n"
                    );
            exit(EXIT_FAILURE);
        }
        eRc = Path_AppendA(pMakefile, ".txt");
        if (ERESULT_FAILED(eRc)) {
            fprintf(
                    stderr,
                    "FATAL - Unable to create Makefile name!\n"
                    );
            exit(EXIT_FAILURE);
        }
        pMakepath = Path_NewFromDriveDirFilename(pDrive, pDir, pMakefile);
        if (OBJ_NIL == pMakefile) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL - Unable to create Makepath!\n"
                    );
            exit(EXIT_FAILURE);
        }
        /*
        eRc = Path_ExpandVars(pMakepath, (void *)Dict_GetA, this->pDict);
        if (ERESULT_FAILED(eRc) ) {
            DEBUG_BREAK();
            fprintf(stderr, "FATAL - Failed to expand Makepath\n");
            exit(EXIT_FAILURE);
        }
         */
        eRc = Path_IsFile(pMakepath);
        if (!ERESULT_FAILED(eRc) && this->fBackup) {
            eRc = Path_VersionedRename(pMakepath);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to back up old Makefile\n");
                exit(EXIT_FAILURE);
            }
        }
        
        // Return to caller.
        obj_Release(pMakefile);
        pMakefile = OBJ_NIL;
        obj_Release(pDrive);
        pDrive = OBJ_NIL;
        obj_Release(pDir);
        pDrive = OBJ_NIL;
        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        return pMakepath;
    }
        
        
        
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Main_Dealloc (
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
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MAIN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pGen) {
            obj_Release(this->pGen);
            this->pGen = OBJ_NIL;
        }
        Main_setFilePath(this, OBJ_NIL);
        Main_setNodes(this, OBJ_NIL);
        Main_setOutput(this, OBJ_NIL);
        Main_setOutputPath(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i r S c a n
    //---------------------------------------------------------------

    ERESULT         Main_DirScan(
        MAIN_DATA	    *this,
        const
        char            *pPathA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        DIR_DATA        *pScanner = OBJ_NIL;
        PATH_DATA       *pPath;
        const
        char            *pDirA;
        const
        char            *pPatternA;

        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pPatternA = "*.wav";
        pDirA = getenv("HOME");

        pScanner = Dir_New( );
        if (OBJ_NIL == pScanner) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }

        pPath = Path_NewA(pPathA);
        //eRc = Dir_ScanDir(pScanner, pPath, (void *)&DirScanner, this, NULL);
        obj_Release(pPath);
        pPath = OBJ_NIL;

        obj_Release(pScanner);
        pScanner = OBJ_NIL;

        return eRc;
    }



    ERESULT         DirScanner (
        MAIN_DATA	    *this,
        DIRENTRY_DATA   *pEntry,
        void            *pData
    )
    {
        ERESULT         eRc;
        PATH_DATA       *pPath;
        char            *pStr;
        struct stat     statbuf;
        const
        char            *pPatternA = pData;

        // The directory scan just passes all the directory
        // entries.  So, we will be do a match.
        if (pPatternA) {
            eRc = DirEntry_MatchA(pEntry, pPatternA);
            if (ERESULT_FAILED(eRc)) {
                return true;
            }
        }

        pPath = DirEntry_getFullPath(pEntry);
        if (pPath) {
            pStr = AStr_CStringA((ASTR_DATA *)pPath, NULL);
            if (pStr) {
                fprintf(
                        stderr,
                        "\tname: %s  type: %d\n",
                        pStr,
                        DirEntry_getType(pEntry)
                        );

                if (-1 == stat(pStr, &statbuf))
                    fprintf(stderr, "\tERROR - Could not stat: %s!\n", pStr);
                else {
                    //fprintf(stderr, "\tname: (%d)%s\n", statbuf->d_namlen, pDirent->d_name);
                }

                mem_Free(pStr);
                pStr = NULL;
            }
        }

        return true;
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         Main_Disable (
        MAIN_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !Main_Validate(this) ) {
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
    //                          E x e c
    //---------------------------------------------------------------

    int             Main_Exec (
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
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        eRc = Main_ParseArgsDefault(this);
        if (ERESULT_FAILED(eRc)) {
            Appl_Usage((APPL_DATA *)this, "ERROR - Failed to properly set defaults!");
            exit(8);
        }

        for (;;) {
            
            fRc = Appl_IsMore((APPL_DATA *)this);
            if (!fRc) {
                break;
            }
            
            eRc = Appl_ProcessOptions((APPL_DATA *)this);
            if (ERESULT_FAILED(eRc)) {
                Appl_Usage((APPL_DATA *)this, "ERROR - Failed to properly parse command line!");
                exit(8);
            }
            
            pChrStr = Appl_NextArg((APPL_DATA *)this);
            if (NULL == pChrStr) {
                break;
            }
            pStr = AStr_NewA(pChrStr);
            iRc = Main_ProcessArg(this, pStr);
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

    MAIN_DATA *     Main_Init (
        MAIN_DATA       *this
    )
    {
        //ERESULT         eRc;
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

        this = (OBJ_ID)Appl_Init((APPL_DATA *)this); // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MAIN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            //obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                      // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Main_Vtbl);
        
    #ifdef NDEBUG
    #else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "sizeof(MAIN_DATA) = %lu\n", sizeof(MAIN_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(MAIN_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Main_IsEnabled (
        MAIN_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
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

    /*! Set default values for arguments just prior to them being parsed.
     This is called by Appl_SetupFromArgV() and Appl_SetupFromStr().
     Parsed arguments may replace any value set here.
@return    If successful, then ERESULT_SUCESS. Otherwise, an ERESULT_*
                error. Note: this is ignored in Appl.
     */
    ERESULT         Main_ParseArgsDefault (
        MAIN_DATA        *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pOS = OBJ_NIL;
        ASTR_DATA       *pArch = OBJ_NIL;
        ASTR_DATA       *pStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        /****
        if (pOS) {
            eRc = NodeHash_AddA(Dict_getNodeHash(Main_getDict(this)), 0, osTypeID, pOS);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", osTypeID);
                exit(EXIT_FAILURE);
            }
            obj_Release(pOS);
            pOS = OBJ_NIL;
        }
        if (pArch) {
            eRc = NodeHash_AddA(Dict_getNodeHash(Main_getDict(this)), 0, osArchID, pArch);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", osArchID);
                exit(EXIT_FAILURE);
            }
            obj_Release(pArch);
            pArch = OBJ_NIL;
        }
        eRc = Main_DefaultsMacos64(this);

        pStr = AStr_NewA("d");
        if (pStr) {
            eRc = NodeHash_AddA(Dict_getNodeHash(Main_getDict(this)), 0, makeTypeID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", makeTypeID);
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        pStr = AStr_NewA("$(HOME)/Support/lib/$(SYS)");
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        pStr = AStr_NewA("C:/PROGRAMS");
#endif
        if (pStr) {
            eRc = NodeHash_AddA(Dict_getNodeHash(Main_getDict(this)), 0, libBaseID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        libBaseID
                        );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        pStr = AStr_NewA("$(HOME)/Support/bin");
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        pStr = AStr_NewA("C:/PROGRAMS");
#endif
        if (pStr) {
            eRc = NodeHash_AddA(Dict_getNodeHash(Main_getDict(this)), 0, pgmBaseID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        pgmBaseID
                        );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        pStr = AStr_NewA("./src");
        if (pStr) {
            eRc = NodeHash_AddA(Dict_getNodeHash(Main_getDict(this)), 0, srcDirID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        srcDirID
                        );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
#if defined(__MACOSX_ENV__)
        pStr = AStr_NewA("${TMPDIR}");
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        pStr = AStr_NewA("${TMP}");
#endif
        if (pStr) {
            eRc = NodeHash_AddA(Dict_getNodeHash(Main_getDict(this)), 0, tmpDirID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        tmpDirID
                        );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        pStr = AStr_NewA("./tests");
        if (pStr) {
            eRc = NodeHash_AddA(Dict_getNodeHash(Main_getDict(this)), 0, tstSrcID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        tstSrcID
                        );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
         ***/
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    //---------------------------------------------------------------
    //              P r o c e s s  A r g s
    //---------------------------------------------------------------
    
    ERESULT         Main_ProcessInit (
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        
        // Return to caller.
        return eRc;
    }
    
    
    /*!
     Process each command line argument.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Main_ProcessArg (
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        PATH_DATA       *pPath = OBJ_NIL;
        PATH_DATA       *pFileName = OBJ_NIL;
        PATH_DATA       *pMakepath = OBJ_NIL;
        ASTR_DATA       *pWrk;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        TRC_OBJ(this, "Main_ProcessArg(%s)\n", pStr ? AStr_getData(pStr) : "");

        if (!Appl_getQuiet((APPL_DATA *)this)) {
            fprintf(stderr, "\tProcessing - %s...\n", AStr_getData(pStr));
        }
        
        pPath = Main_CheckInputPath(this, pStr);
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == pPath),
                    "FATAL - Failed to create path \"from\" \n"
        );

        eRc = Main_CleanFile(this, pPath);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - Failed to clean: %s",
                    Path_getData(pPath)
        );

        if (!Appl_getQuiet((APPL_DATA *)this)) {
            fprintf(stderr, "\t\t%s cleaned.\n", Path_getData(pMakepath));
        }

        // Return to caller.
        obj_Release(pMakepath);
        pMakepath = OBJ_NIL;
        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          Main_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MAIN_DATA   *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
                // Query for an address to specific data within the object.
                // This should be used very sparingly since it breaks the
                // object's encapsulation.
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
                        
                    case 'C':
                        if (str_Compare("ClassObject", (char *)pStr) == 0) {
                            return (void *)&Main_ClassObj;
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

#ifdef XYZZY
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return Main_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Main_Enable;
                        }
                        break;
#endif

                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                  S e t u p  F r o m  A r g V
    //---------------------------------------------------------------
    
    ERESULT         Main_SetupFromArgV (
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
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = Appl_SetupFromArgV((APPL_DATA *)this, cArgs, ppArgV, ppEnv, pPgmOptions);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //             S e t u p  T e x t O u t
    //---------------------------------------------------------------
    
    ERESULT         Main_SetupTextOutAStr (
        MAIN_DATA        *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pOutput) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif
        
        this->pOutput = TextOut_NewAStr( );
        if (OBJ_NIL == this->pOutput) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = Main_ToDebugString(this,4);
     @endcode
     @param     this    MAIN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Main_ToDebugString (
        MAIN_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(main) size=%d\n",
                     this,
                     Main_getSize(this)
            );
        AStr_AppendA(pStr, str);

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
        j = snprintf(str, sizeof(str), " %p(main)}\n", this);
        AStr_AppendA(pStr, str);
        
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
    ERESULT         Main_UsageDesc (
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pPgmPath
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        fprintf(
                pOutput, 
                "  Clean up old CP/M ascii text files to conform to\n"
                "  Unix/MacOS standards.\n"
        );
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    // Note: --debug(-d), --force(-f), --help(-?,-h), --verbose(-v) are already
    //      taken care of in appl_Usage().
    ERESULT         Main_UsageOptions (
        MAIN_DATA       *this,
        FILE            *pOutput
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        fprintf(pOutput, "  (--recurse | -r)   Recurse the subdirectores\n");

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
    ERESULT         Main_UsageProgLine (
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
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
      
        fprintf(pOutput, "  %s [options] input_path(s)...\n", pNameA);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            Main_Validate (
        MAIN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_MAIN) )
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


        if( !(obj_getSize(this) >= sizeof(MAIN_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


