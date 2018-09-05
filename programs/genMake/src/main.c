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
#include        <main_internal.h>
#include        <genOSX.h>
#include        <genWIN.h>
#include        <hjson.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    ERESULT         main_ArgLibInclude(
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    );
    ERESULT         main_ArgMacos(
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    );
    ERESULT         main_ArgMsc32(
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    );
    ERESULT         main_ArgMsc64(
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    );
    ERESULT         main_DefaultsMacos(
        MAIN_DATA       *this
    );
    ERESULT         main_DefaultsMsc32(
        MAIN_DATA       *this
    );
    ERESULT         main_DefaultsMsc64(
        MAIN_DATA       *this
    );


    static
    CMDUTL_OPTION       pPgmArgs[] = {
        {
            "file",
            'F',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_PATH,
            offsetof(MAIN_DATA, pFilePath),
            NULL,
            "Set Input File Path"
        },
        {
            "libInclude",
            'I',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_PATH,
            0,
            (void *)main_ArgLibInclude,
            "Set Library Include Base Path"
        },
        {
            "macos",
            'M',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_EXEC,
            0,
            (void *)main_ArgMacos,
            "Generate MacOS Makefile (default)"
        },
        {
            "msc32",
            'S',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_EXEC,
            0,
            (void *)main_ArgMsc32,
            "Generate Msc32 Makefile"
        },
        {
            "msc64",
            'M',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_EXEC,
            0,
            (void *)main_ArgMsc64,
            "Generate Msc64 Makefile"
        },
        {
            "out",
            'o',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_PATH,
            offsetof(MAIN_DATA, pOutputPath),
            NULL,
            "Set Output Base Path"
        },
        {0}
    };
    

    
    
 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                     A r g  R o u t i n e s
    //---------------------------------------------------------------
    
    ERESULT         main_ArgLibInclude(
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
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
        
        //eRc = main_DefaultsMacos(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         main_ArgMacos(
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
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
        
        eRc = main_DefaultsMacos(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         main_ArgMsc32(
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
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
        
        eRc = main_DefaultsMsc32(this);

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         main_ArgMsc64(
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
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
        
        eRc = main_DefaultsMsc64(this);

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //                D e f a u l t  R o u t i n e s
    //---------------------------------------------------------------
    
    ERESULT         main_DefaultsMacos(
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
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->osType = OSTYPE_MACOS;
        pKey = osTypeID;
        pStr = AStr_NewA("macos");
        if (pStr) {
            eRc = nodeHash_AddUpdateA(main_getDict(this), pKey, 0, pStr);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", pKey);
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        // Set up namePrefix default;
        pKey = namePrefixID;
        pStr = AStr_NewA("lib");
        if (pStr) {
            eRc = nodeHash_AddUpdateA(main_getDict(this), pKey, 0, pStr);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", pKey);
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        //FIXME: eRc = nodeHash_AddUpdateA(main_getDict(this), "outBase", "/usr/local/lib");
        if (ERESULT_FAILED(eRc) ) {
            DEBUG_BREAK();
            fprintf(stderr, "FATAL - Failed to add 'outBase' to Dictionary\n");
            exit(EXIT_FAILURE);
        }
        
        pKey = tmpBaseID;
        pStr = AStr_NewA("${TMPDIR}");
        if (pStr) {
            eRc = nodeHash_AddUpdateA(main_getDict(this), pKey, 0, pStr);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", pKey);
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         main_DefaultsMsc32(
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
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->osType = OSTYPE_MSC32;
        pKey = osTypeID;
        pStr = AStr_NewA("msc32");
        if (pStr) {
            eRc = nodeHash_AddUpdateA(main_getDict(this), pKey, 0, pStr);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", pKey);
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        //FIXME: Update this!

        // Set up libPath defaults
        //FIXME: eRc = main_DictAddUpdate(this, "libIncludePath", "..");
        if (ERESULT_FAILED(eRc) ) {
            fprintf(stderr, "FATAL - Failed to add 'libIncludePath' to Dictionary\n");
            exit(EXIT_FAILURE);
        }
        
        // Set up libPrefix default;
        //FIXME: eRc = main_DictAddUpdate(this, "libNamePrefix", "lib");
        if (ERESULT_FAILED(eRc) ) {
            fprintf(stderr, "FATAL - Failed to add 'libIncludePrefix' to Dictionary\n");
            exit(EXIT_FAILURE);
        }
        
        //FIXME: eRc = main_DictAddUpdate(this, "outBase", "\\\\C:\\");
        if (ERESULT_FAILED(eRc) ) {
            fprintf(stderr, "FATAL - Failed to add 'outBase' to Dictionary\n");
            exit(EXIT_FAILURE);
        }
        
        //FIXME: eRc = main_DictAddUpdate(this, "tmpBase", "\\TEMP");
        if (ERESULT_FAILED(eRc) ) {
            fprintf(stderr, "FATAL - Failed to add 'tmpBase' to Dictionary\n");
            exit(EXIT_FAILURE);
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         main_DefaultsMsc64(
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
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->osType = OSTYPE_MSC64;
        pKey = osTypeID;
        pStr = AStr_NewA("msc64");
        if (pStr) {
            eRc = nodeHash_AddUpdateA(main_getDict(this), pKey, 0, pStr);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", pKey);
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        //FIXME: eRc = main_DictAddUpdate(this, "outBase", "\\\\C:\\");
        if (ERESULT_FAILED(eRc) ) {
            fprintf(stderr, "FATAL - Failed to add 'outBase' to Dictionary\n");
            exit(EXIT_FAILURE);
        }
        
        //FIXME: eRc = main_DictAddUpdate(this, "tmpBase", "\\TEMP");
        if (ERESULT_FAILED(eRc) ) {
            fprintf(stderr, "FATAL - Failed to add 'tmpBase' to Dictionary\n");
            exit(EXIT_FAILURE);
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MAIN_DATA *     main_Alloc(
    )
    {
        MAIN_DATA       *this;
        uint32_t        cbSize = sizeof(MAIN_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    MAIN_DATA *     main_New(
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
    
    
    MAIN_DATA *     main_NewFromArgV(
        uint16_t        cArgs,
        char            **ppArgs,
        char            **ppEnv
    )
    {
        MAIN_DATA       *this;
        ERESULT         eRc;
        
        this = main_Alloc( );
        if (this) {
            this = main_Init(this);
            if (this) {
                eRc =   appl_SetupFromArgV(
                                    (APPL_DATA *)this,
                                           cArgs,
                                           ppArgs,
                                           ppEnv,
                                           pPgmArgs
                        );
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
    
    NODEHASH_DATA * main_getDict(
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
        
        main_setLastError(this, ERESULT_SUCCESS);
        return this->pDict;
    }
    
    
    bool            main_setDict(
        MAIN_DATA       *this,
        NODEHASH_DATA   *pValue
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
        
        main_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  F i l e  P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *     main_getFilePath(
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
        
        main_setLastError(this, ERESULT_SUCCESS);
        return this->pFilePath;
    }
    
    
    bool            main_setFilePath(
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
        if (this->pFilePath) {
            obj_Release(this->pFilePath);
        }
        this->pFilePath = pValue;
        
        main_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         main_getLastError(
        MAIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            main_setLastError(
        MAIN_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                      M a k e  T y p e
    //---------------------------------------------------------------
    
    uint16_t        main_getMakeType(
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        main_setLastError(this, ERESULT_SUCCESS);
        return this->makeType;
    }
    
    
    bool            main_setMakeType(
        MAIN_DATA       *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->makeType = value;
        
        main_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N o d e s
    //---------------------------------------------------------------
    
    NODE_DATA *     main_getNodes(
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
        
        main_setLastError(this, ERESULT_SUCCESS);
        return this->pNodes;
    }
    
    
    bool            main_setNodes(
        MAIN_DATA       *this,
        NODE_DATA       *pValue
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
        if (this->pNodes) {
            obj_Release(this->pNodes);
        }
        this->pNodes = pValue;
        
        main_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O/S  T y p e
    //---------------------------------------------------------------
    
    uint16_t        main_getOsType(
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        main_setLastError(this, ERESULT_SUCCESS);
        return this->osType;
    }
    
    
    bool            main_setOsType(
        MAIN_DATA       *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->osType = value;
        
        main_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O u t p u t
    //---------------------------------------------------------------
    
    TEXTOUT_DATA *  main_getOutput(
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
        
        main_setLastError(this, ERESULT_SUCCESS);
        return this->pOutput;
    }
    
    
    bool            main_setOutput(
        MAIN_DATA       *this,
        TEXTOUT_DATA    *pValue
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
        if (this->pOutput) {
            obj_Release(this->pOutput);
        }
        this->pOutput = pValue;
        
        main_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  O u t p u t  P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *     main_getOutputPath(
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
        
        main_setLastError(this, ERESULT_SUCCESS);
        return this->pOutputPath;
    }
    
    
    bool            main_setOutputPath(
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
        if (this->pOutputPath) {
            obj_Release(this->pOutputPath);
        }
        this->pOutputPath = pValue;
        
        main_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        main_getPriority(
        MAIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        main_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            main_setPriority(
        MAIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        main_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                          S i z e
    //---------------------------------------------------------------
    
    uint32_t        main_getSize(
        MAIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        main_setLastError(this, ERESULT_SUCCESS);
        return 0;
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
        ERESULT eRc = main__Assign(this,pOther);
     @endcode
     @param     this    MAIN object pointer
     @param     pOther  a pointer to another MAIN object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         main_Assign(
        MAIN_DATA		*this,
        MAIN_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !main_Validate(pOther) ) {
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
        main_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        main_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return main_getLastError(this);
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
     @return    If successful, a MAIN object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the MAIN object.
     */
    MAIN_DATA *     main_Copy(
        MAIN_DATA       *this
    )
    {
        MAIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
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
        main_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            main_Dealloc(
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
        if( !main_Validate(this) ) {
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
        main_setFilePath(this, OBJ_NIL);
        main_setNodes(this, OBJ_NIL);
        main_setOutputPath(this, OBJ_NIL);

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

    ERESULT         main_Disable(
        MAIN_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            main_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return main_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        main_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E x e c
    //---------------------------------------------------------------

    int             main_Exec(
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        int             iRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        char            *pChrStr;
        bool            fFile = true;

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

        this->pOutput = textOut_NewAStr( );
        if (OBJ_NIL == this->pOutput) {
            fprintf(
                    stderr,
                    "FATAL - Could not open output file, %s!\n\n\n",
                    path_getData(this->pOutputPath)
                    );
            exit(12);
        }
        fFile = false;
        
        for (;;) {
            
            fRc = appl_IsMore((APPL_DATA *)this);
            if (!fRc)
                break;
            
            eRc = appl_ProcessOptions((APPL_DATA *)this);
            if (ERESULT_FAILED(eRc)) {
                appl_Usage((APPL_DATA *)this, "ERROR - Failed to properly parse command line!");
                exit(8);
            }
            
            pChrStr = appl_NextArg((APPL_DATA *)this);
            if (NULL == pStr) {
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
        
        if (fFile) {
            //FIXME: fclose(this->pOut);
            this->pOutput = NULL;
        }
        
        // Return to caller.
        main_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    //---------------------------------------------------------------
    //                  G e n  M a k e  F i l e
    //---------------------------------------------------------------
    
    ERESULT         main_GenMakefile(
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == this->pDict) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        if (OBJ_NIL == this->pNodes) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        if (OBJ_NIL == this->pOutput) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        
        switch (this->osType) {
                
            case OSTYPE_MACOS:
                this->pGen = (OBJ_ID)genOSX_New(this->pDict);
                if (this->pGen) {
                    if (obj_Trace(this) || appl_getDebug((APPL_DATA *)this)) {
                        obj_TraceSet(this->pGen, true);
                    }
                }
                break;
                
            case OSTYPE_MSC32:
            case OSTYPE_MSC64:
                this->pGen = genWIN_New( );
                if (this->pGen) {
                    if (obj_Trace(this) || appl_getDebug((APPL_DATA *)this)) {
                        obj_TraceSet(this->pGen, true);
                    }
                }
                break;
                
            default:
                appl_Usage((APPL_DATA *)this, "ERROR - Failed to indicate type of makefile to generate!");
                exit(8);
        }
        if (OBJ_NIL == this->pGen) {
            fprintf(stderr, "FATAL - Could not create generator object!\n\n\n");
            exit(12);
        }
        eRc =   genBase_GenMakefile(
                                  this->pGen,
                                  this->pNodes,
                                  this->pDict,
                                  appl_getDateTime((APPL_DATA *)this),
                                  this->pOutput
                );
        
        
        // Return to caller.
        main_setLastError(this, eRc);
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    MAIN_DATA *     main_Init(
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

        this = (OBJ_ID)appl_Init((APPL_DATA *)this); // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MAIN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            //obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                      // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_MAIN);     // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&main_Vtbl);
        
        main_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->pDict = nodeHash_New(NODEHASH_TABLE_SIZE_SMALL);
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
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "offsetof(eRc) = %lu\n", offsetof(MAIN_DATA,eRc));
        //fprintf(stderr, "sizeof(MAIN_DATA) = %lu\n", sizeof(MAIN_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(MAIN_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         main_IsEnabled(
        MAIN_DATA		*this
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
        
        if (obj_IsEnabled(this)) {
            main_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        main_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //              P a r s e  A r g s  D e f a u l t
    //---------------------------------------------------------------
    
    ERESULT         main_ParseArgsDefault(
        MAIN_DATA        *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        const
        char            *pKey;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pKey = osTypeID;
#if defined(__MACOSX_ENV__)
        this->osType = OSTYPE_MACOS;
        pStr = AStr_NewA("macos");
#endif
#if defined(__WIN32_ENV__)
        this->osType = OSTYPE_WIN32;
        pStr = AStr_NewA("win32");
#endif
#if defined(__WIN64_ENV__)
        this->osType = OSTYPE_WIN64;
        pStr = AStr_NewA("win64");
#endif
        if (pStr) {
            eRc = nodeHash_AddUpdateA(main_getDict(this), pKey, 0, pStr);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", pKey);
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        eRc = main_DefaultsMacos(this);

        pKey = makeTypeID;
        pStr = AStr_NewA("d");
        if (pStr) {
            eRc = nodeHash_AddUpdateA(main_getDict(this), pKey, 0, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", pKey);
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        pKey = resultTypeID;
        pStr = AStr_NewA("lib");
        if (pStr) {
            eRc = nodeHash_AddUpdateA(main_getDict(this), pKey, 0, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        pKey
                );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        pKey = outBaseID;
#if defined(__MACOSX_ENV__)
        pStr = AStr_NewA("/usr/local/bin");
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        pStr = AStr_NewA("C:/PROGRAMS");
#endif
        if (pStr) {
            eRc = nodeHash_AddUpdateA(main_getDict(this), pKey, 0, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        pKey
                        );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        pKey = srcBaseID;
        pStr = AStr_NewA("./src");
        if (pStr) {
            eRc = nodeHash_AddUpdateA(main_getDict(this), pKey, 0, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        pKey
                        );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        pKey = tmpBaseID;
#if defined(__MACOSX_ENV__)
        pStr = AStr_NewA("${TMPDIR}");
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        pStr = AStr_NewA("${TMP}");
#endif
        if (pStr) {
            eRc = nodeHash_AddUpdateA(main_getDict(this), pKey, 0, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        pKey
                        );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
       this->pOutput = textOut_NewAStr( );
        if (OBJ_NIL == this->pOutput) {
            fprintf(stderr, "FATAL - Failed to create TextOut Object!\n");
            exit(EXIT_FAILURE);
        }

        // Return to caller.
        main_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //              P a r s e  A r g s  L o n g
    //---------------------------------------------------------------
    
    int             main_ParseArgsLong(
        MAIN_DATA       *this,
        int             *pArgC,
        const
        char            ***pppArgV
    )
    {
        ERESULT         eRc;
        PATH_DATA       *pPath = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Do something.
        if (0 == strcmp("--macosx", **pppArgV)) {
            eRc = main_DefaultsMacos(this);
        }
        else if (0 == strcmp("--msc32", **pppArgV)) {
            eRc = main_DefaultsMsc32(this);
        }
        else if (0 == strcmp("--msc64", **pppArgV)) {
            eRc = main_DefaultsMsc64(this);
        }
        else if (0 == strncmp("--input", **pppArgV, 6)) {
            if (*(**pppArgV+6) == '\0') {
                ++*pppArgV;
                --*pArgC;
                if (*pArgC <= 0) {
                    appl_Usage((APPL_DATA *)this, "ERROR: --file is missing the path!\n");
                    exit(8);
                }
                pPath = path_NewA(**pppArgV);
            }
            else {
                **pppArgV += 6;
                if (***pppArgV == '=') {
                    ++**pppArgV;
                    pPath = path_NewA(**pppArgV);
                }
            }
            if (pPath) {
                eRc = path_IsFile(pPath);
                if (ERESULT_FAILED(eRc)) {
                    appl_Usage(
                               (APPL_DATA *)this,
                               "ERROR: --file's path, %s, is not a valid file!\n",
                               **pppArgV
                               );
                    exit(8);
                }
                main_setFilePath(this, pPath);
                obj_Release(pPath);
            }
        }
        else if (0 == strncmp("--out", **pppArgV, 5)) {
            if (*(**pppArgV+5) == '\0') {
                ++*pppArgV;
                --*pArgC;
                if (*pArgC <= 0) {
                    appl_Usage((APPL_DATA *)this, "ERROR: --out is missing the path!\n");
                    exit(8);
                }
                pPath = path_NewA(**pppArgV);
            }
            else {
                pPath = path_NewA(**pppArgV+6);
            }
            if (pPath) {
                main_setOutputPath(this, pPath);
                obj_Release(pPath);
            }
        }
        else {
            appl_Usage(
                       (APPL_DATA *)this,
                       "ERROR: Illegal option, %s!\n",
                       **pppArgV
            );
            exit(8);
        }

        // Return to caller.
        main_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }
    
    
    
    //---------------------------------------------------------------
    //              P a r s e  I n p u t  F i l e
    //---------------------------------------------------------------
    
    ERESULT         main_ParseInputFile(
        MAIN_DATA       *this,
        PATH_DATA       *pPath
    )
    {
        //ERESULT         eRc;
        HJSON_DATA      *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        //NODEHASH_DATA   *pHash;
        NODE_DATA       *pFileNode;
        //NODE_DATA       *pNode;
        //NODEARRAY_DATA  *pArray;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pObj = hjson_NewFromPath(pPath, 4);
        if (pObj) {
            
            if  (appl_getDebug((APPL_DATA *)this)) {
                obj_TraceSet(pObj, true);
            }
            pFileNode = hjson_ParseFileHash(pObj);
            if (pFileNode) {
                this->pNodes = pFileNode;
                if (appl_getDebug((APPL_DATA *)this)) {
                    pStr = node_ToDebugString(pFileNode, 0);
                    fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        

        // Return to caller.
        main_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         main_ParseInputStr(
        MAIN_DATA       *this,
        const
        char            *pStr
    )
    {
        //ERESULT         eRc;
        HJSON_DATA      *pObj = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        NODE_DATA       *pFileNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pObj = hjson_NewA(pStr, 4);
        if (pObj) {
            
            if  (appl_getDebug((APPL_DATA *)this)) {
                obj_TraceSet(pObj, true);
            }
            pFileNode = hjson_ParseFileHash(pObj);
            if (pFileNode) {
                this->pNodes = pFileNode;
                if (appl_getDebug((APPL_DATA *)this)) {
                    pWrk = node_ToDebugString(pFileNode, 0);
                    fprintf(stderr, "%s\n\n\n", AStr_getData(pWrk));
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
            }
            
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //              P r o c e s s  A r g s
    //---------------------------------------------------------------
    
    ERESULT         main_ProcessInit(
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        
        // Return to caller.
        main_setLastError(this, eRc);
        return eRc;
    }
    
    
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
        
        if (!appl_getQuiet((APPL_DATA *)this)) {
            fprintf(stderr, "Processing - %s...\n", AStr_getData(pStr));
        }
        if (appl_getDebug((APPL_DATA *)this)) {
            //FIXME: eRc = main_DictAddUpdate(this, "makeType", "d");
            if (ERESULT_FAILED(eRc) ) {
                fprintf(stderr, "FATAL - Failed to add 'makeType' to Dictionary\n");
                exit(EXIT_FAILURE);
            }
        }
        pPath = path_NewFromAStr(pStr);
        if (OBJ_NIL == pPath) {
            fprintf(stderr, "FATAL - Failed to create path from \n");
            exit(EXIT_FAILURE);
        }
        eRc = path_IsFile(pPath);
        if (ERESULT_FAILED(eRc)) {
            fprintf(
                    stderr,
                    "FATAL - File, %s, does not exist or is not a file!\n",
                    path_getData(pPath)
            );
            exit(EXIT_FAILURE);
        }
        eRc = path_SplitPath(pPath, &pDrive, &pDir, &pFileName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(
                    stderr,
                    "FATAL - Unable to extract directory from File, %s!\n",
                    path_getData(pPath)
            );
            exit(EXIT_FAILURE);
        }
        pArgDir = path_NewFromDriveDirFilename(pDrive, pDir, OBJ_NIL);
        if (OBJ_NIL == pArgDir) {
            fprintf(
                    stderr,
                    "FATAL - Unable to extract directory from File, %s!\n",
                    path_getData(pPath)
                    );
            exit(EXIT_FAILURE);
        }
        //FIXME: eRc = main_DictAddUpdate(this, "srcDir", path_getData(pArgDir));
        if (ERESULT_FAILED(eRc) ) {
            fprintf(stderr, "FATAL - Failed to add 'srcDir' to Dictionary\n");
            exit(EXIT_FAILURE);
        }
        obj_Release(pArgDir);
        pArgDir = OBJ_NIL;
        //FIXME: eRc = main_DictAddUpdate(this, "srcFile", path_getData(pPath));
        if (ERESULT_FAILED(eRc) ) {
            fprintf(stderr, "FATAL - Failed to add 'srcFile' to Dictionary\n");
            exit(EXIT_FAILURE);
        }

        eRc = main_ParseInputFile(this, pPath);
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        eRc = main_GenMakefile(this);
        
        // Return to caller.
        main_setLastError(this, eRc);
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          main_QueryInfo(
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
        if( !main_Validate(this) ) {
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
                            return (void *)&main_ClassObj;
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
                            return main_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return main_Enable;
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
    //             S e t u p  T e x t O u t
    //---------------------------------------------------------------
    
    ERESULT         main_SetupTextOutAStr(
        MAIN_DATA        *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pOutput) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif
        
        this->pOutput = textOut_NewAStr( );
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
     @code:
        ASTR_DATA      *pDesc = main_ToDebugString(this,4);
     @endcode:
     @param:    this    MAIN object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     main_ToDebugString(
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
        if( !main_Validate(this) ) {
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
                     main_getSize(this)
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
        
        main_setLastError(this, ERESULT_SUCCESS);
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
        main_setLastError(this, ERESULT_SUCCESS);
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
        
        fprintf(pOutput, "  --clp              Set type to Command Line Program\n");
        fprintf(pOutput, "                     (Default is Library)\n");
        fprintf(pOutput, "  --macosx           Generate MacOSX nmake file (default)\n");
        fprintf(pOutput, "  --msc32            Generate MSC Win32 nmake file\n");
        fprintf(pOutput, "  --msc64            Generate MSC Win64 nmake file\n");
        fprintf(pOutput, "  (--out | -o) path  Output the generated data to <path>\n");
        
        // Return to caller.
        main_setLastError(this, ERESULT_SUCCESS);
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
      
        fprintf(pOutput, "  %s [options] input_path\n", pNameA);
        
        // Return to caller.
        main_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            main_Validate(
        MAIN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, MAIN_IDENT_MAIN) )
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


