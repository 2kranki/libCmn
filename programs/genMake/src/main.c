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
#include        <dbprs.h>
#include        <genOSX.h>
#include        <genWIN.h>
#include        <hjson.h>
#include        <srcErrors.h>
#include        <srcParse.h>
#include        <trace.h>



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
            "file",
            'f',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_PATH,
            offsetof(MAIN_DATA, pFilePath),
            NULL,
            "Input File Path"
        },
        {
            "libInclude",
            'I',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_PATH,
            0,
            (void *)main_ArgLibInclude,
            "Library Include Base Path"
        },
        {
            "macos",
            'X',
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
            "Output File Path"
        },
        {
            "dirtmp",
            't',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_PATH,
            offsetof(MAIN_DATA, pOutputPath),
            NULL,
            "Temporary Directory Base Path"
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

        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->osType = OSTYPE_MACOS;

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         main_DefaultsMsc32(
        MAIN_DATA       *this
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
        
        this->osType = OSTYPE_MSC32;

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
            eRc = nodeHash_AddUpdateA(main_getDict(this), 0, pKey, pStr);
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
                eRc = main_SetupFromArgV(this, cArgs, ppArgs, ppEnv);
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
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O u t  T y p e
    //---------------------------------------------------------------
    
    uint16_t        main_getOutType(
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
        
        return this->outType;
    }
    
    
    bool            main_setOutType(
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
        
        this->outType = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P a r s e r
    //---------------------------------------------------------------
    
    DBPRS_DATA *    main_getParser(
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
        
        return this->pPrs;
    }
    
    
    bool            main_setParser(
        MAIN_DATA       *this,
        DBPRS_DATA      *pValue
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
        if (this->pPrs) {
            obj_Release(this->pPrs);
        }
        this->pPrs = pValue;
        
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

        return 0;
    }



    //---------------------------------------------------------------
    //                          S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     main_getStr(
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
        
        if (OBJ_NIL == this->pOutput) {
            return OBJ_NIL;
        }
        
        return textOut_getStr(this->pOutput);
    }
    
    

    //---------------------------------------------------------------
    //                          V e r b o s e
    //---------------------------------------------------------------
    
    int             main_getVerbose(
        MAIN_DATA       *this
    )
    {
        int             iRc = -1;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return iRc;
        }
#endif
        
        iRc = appl_getVerbose((APPL_DATA *)this);
        
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
        ERESULT eRc = main__Assign(this,pOther);
     @endcode
     @param     this    MAIN object pointer
     @param     pOther  a pointer to another MAIN object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         main_Assign(
        MAIN_DATA		*this,
        MAIN_DATA       *pOther
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

        if (this->pGen) {
            obj_Release(this->pGen);
            this->pGen = OBJ_NIL;
        }
        main_setDict(this, OBJ_NIL);
        main_setFilePath(this, OBJ_NIL);
        main_setNodes(this, OBJ_NIL);
        main_setOutput(this, OBJ_NIL);
        main_setOutputPath(this, OBJ_NIL);
        main_setParser(this, OBJ_NIL);

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
            this->pDict = nodeHash_NewWithSize(NODEHASH_TABLE_SIZE_SMALL);
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        eRc = nodeHash_AddA(this->pDict, 0, pName, (void *)pData);
        
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
            this->pDict = nodeHash_NewWithSize(NODEHASH_TABLE_SIZE_SMALL);
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        eRc = nodeHash_AddA(this->pDict, 0, pName, pStr);
        
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
            this->pDict = nodeHash_NewWithSize(NODEHASH_TABLE_SIZE_SMALL);
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        if (nodeHash_FindA(this->pDict, 0, pName)) {
            eRc = nodeHash_DeleteA(this->pDict, 0, pName);
        }
        eRc = nodeHash_AddA(this->pDict, 0, pName, (void *)pData);
        
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
            this->pDict = nodeHash_NewWithSize(NODEHASH_TABLE_SIZE_SMALL);
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        if (nodeHash_FindA(this->pDict, 0, pName)) {
            eRc = nodeHash_DeleteA(this->pDict, 0, pName);
        }
        eRc = nodeHash_AddA(this->pDict, 0, pName, pStr);
        
        // Return to caller.
        obj_Release(pStr);
        pStr = OBJ_NIL;
        return eRc;
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
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !main_Validate(this) ) {
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

    int             main_Exec(
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
    //                  G e n  M a k e  F i l e
    //---------------------------------------------------------------
    
    ERESULT         main_GenMakefile(
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODEHASH_DATA   *pHash = OBJ_NIL;
        NODEHASH_DATA   *pHashWrk = OBJ_NIL;
        GENBASE_DATA    *pGen;
        //FIXME: DBPRS_DATA      *pPrs;

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
#endif
        
        // Set up the O/S Generator.
        switch (this->osType) {
                
            case OSTYPE_MACOS:
                pGen = (OBJ_ID)genOSX_New(this->pDict);
                if (pGen) {
                    if (obj_Trace(this) || appl_getDebug((APPL_DATA *)this)) {
                        obj_TraceSet(pGen, true);
                    }
                }
                break;
                
            case OSTYPE_MSC32:
            case OSTYPE_MSC64:
                pGen = (OBJ_ID)genWIN_New(this->pDict);
                if (pGen) {
                    if (obj_Trace(this) || appl_getDebug((APPL_DATA *)this)) {
                        obj_TraceSet(pGen, true);
                    }
                }
                break;
                
            default:
                appl_Usage(
                        (APPL_DATA *)this,
                        "ERROR - Failed to indicate type of makefile to generate!\n\n\n"
                );
                exit(8);
        }
        if (OBJ_NIL == pGen) {
            fprintf(stderr, "FATAL - Could not create generator object!\n\n\n");
            exit(12);
        }
        
        // Set up a Parser and Generator for the input.
        //FIXME: pPrs = dbprs_NewWithDictAndGen(this->pDict, pGen);
        /*
        if (OBJ_NIL == pPrs) {
            fprintf(stderr, "FATAL - Could not create database parser object!\n\n\n");
            exit(12);
        }
         */
        //FIXME: dbprs_setNodes(pPrs, this->pNodes);
        
        pHash = node_getData(this->pNodes);
        if (!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
        
        // Handle "library" or "program" section of source file.
        pNode = nodeHash_FindA(pHash, 0, "library");
        if (pNode) {
            if (main_getVerbose(this)) {
                fprintf(stderr, "Generating Library Header...\n");
            }
            pHashWrk = jsonIn_CheckNodeDataForHash(pNode);
            if (pHashWrk) {
                genBase_setMakeType(pGen, GENMAKE_TYPE_LIB);
                //FIXME: eRc = dbprs_ParseLibrary(pPrs, pHashWrk);
                if (ERESULT_FAILED(eRc)) {
                    fprintf(
                            stderr,
                            "FATAL - Could not parse \"library\" "
                            "node in database hash object!\n\n\n"
                            );
                    exit(12);
                }
                main_setOutType(this, OUTTYPE_LIB);
            }
            else {
                fprintf(
                        stderr,
                        "FATAL - Found \"library\" "
                        "node in database, but it is not a hash object!\n\n\n"
                        );
                exit(12);
            }
        }
        else {
            pNode = nodeHash_FindA(node_getData(this->pNodes), 0, "program");
            if (pNode) {
                if (main_getVerbose(this)) {
                    fprintf(stderr, "Generating Program Header...\n");
                }
                pHashWrk = jsonIn_CheckNodeDataForHash(pNode);
                if (pHashWrk) {
                    genBase_setMakeType(pGen, GENMAKE_TYPE_PGM);
                    //FIXME: eRc = dbprs_ParseProgram(pPrs, pHashWrk);
                    if (ERESULT_FAILED(eRc)) {
                        fprintf(
                                stderr,
                                "FATAL - Could not parse \"program\" "
                                "node in database hash object!\n\n\n"
                                );
                        exit(12);
                    }
                    main_setOutType(this, OUTTYPE_CLP);
                }
                else {
                    fprintf(
                            stderr,
                            "FATAL - Found \"program\" "
                            "node in database, but it is not a hash object!\n\n\n"
                            );
                    exit(12);
                }
            }
            else {
                fprintf(
                        stderr,
                        "FATAL - Could not find \"library\" or"
                        " \"program\" node in database hash object!\n\n\n"
                        );
                exit(12);
            }
        }

        // Handle "objects" section of source file.
        pNode = nodeHash_FindA(node_getData(this->pNodes), 0, "objects");
        if (pNode) {
            NODEARRAY_DATA  *pArray = OBJ_NIL;
            if (main_getVerbose(this)) {
                fprintf(stderr, "Generating Object(s) compile/testing...\n");
            }
            pHashWrk = jsonIn_CheckNodeDataForHash(pNode);
            if (pHashWrk) {
                //FIXME: eRc = dbprs_ParseObjects(pPrs, pHashWrk, &pArray);
                if (ERESULT_FAILED(eRc)) {
                    fprintf(
                            stderr,
                            "FATAL - Could not parse \"objects\" "
                            "node in database hash object!\n\n\n"
                            );
                    exit(12);
                }
                //TODO: Do something with pArray!
            }
            else {
                fprintf(
                        stderr,
                        "FATAL - Found \"objects\" "
                        "node in database, but it is not a hash object!\n\n\n"
                        );
                exit(12);
            }
        }
        
        // Handle "routines" section of source file.
        pNode = nodeHash_FindA(node_getData(this->pNodes), 0, "routines");
        if (pNode) {
            if (main_getVerbose(this)) {
                fprintf(stderr, "Generating Routine(s) compilation...\n");
            }
            pArray = jsonIn_CheckNodeDataForArray(pNode);
            if (pArray) {
                //FIXME: eRc = dbprs_ParseRoutines(pPrs, pArray);
            }
            else {
                fprintf(
                        stderr,
                        "FATAL - Found \"routines\" "
                        "node in database, but it is not an array object!\n\n\n"
                        );
                exit(12);
            }
        }
        
        // Handle "tests" section of source file.
        pNode = nodeHash_FindA(node_getData(this->pNodes), 0, "tests");
        if (pNode) {
            if (main_getVerbose(this)) {
                fprintf(stderr, "Generating extra Tests...\n");
            }
            pArray = jsonIn_CheckNodeDataForArray(pNode);
            if (pArray) {
                //FIXME: eRc = dbprs_ParseTests(pPrs, pArray);
            }
            else {
                fprintf(
                        stderr,
                        "FATAL - Found \"tests\" "
                        "node in database, but it is not an array object!\n\n\n"
                        );
                exit(12);
            }
        }
        
        // Handle O/S section of source file.
        switch (this->osType) {
                
            case OSTYPE_MACOS:
                pNode = nodeHash_FindA(node_getData(this->pNodes), 0, "macosx");
                if (pNode) {
                    if (main_getVerbose(this)) {
                        fprintf(stderr, "Generating MacOS routines...\n");
                    }
                    pArray = jsonIn_CheckNodeDataForArray(pNode);
                    if (pArray) {
                        //FIXME: eRc = dbprs_ParseRoutines(pPrs, pArray);
                    }
                    else {
                        fprintf(
                                stderr,
                                "FATAL - Found \"macosx\" "
                                "node in database, but it is not an array object!\n\n\n"
                                );
                        exit(12);
                    }
                }
                
                break;
                
            case OSTYPE_MSC32:
                pNode = nodeHash_FindA(node_getData(this->pNodes), 0, "win32");
                if (pNode) {
                    if (main_getVerbose(this)) {
                        fprintf(stderr, "Generating Win32 routines...\n");
                    }
                    pArray = jsonIn_CheckNodeDataForArray(pNode);
                    if (pArray) {
                        //FIXME: eRc = dbprs_ParseRoutines(pPrs, pArray);
                    }
                    else {
                        fprintf(
                                stderr,
                                "FATAL - Found \"win32\" "
                                "node in database, but it is not an array object!\n\n\n"
                                );
                        exit(12);
                    }
                }
                break;
                
            case OSTYPE_MSC64:
                pNode = nodeHash_FindA(node_getData(this->pNodes), 0, "win64");
                if (pNode) {
                    if (main_getVerbose(this)) {
                        fprintf(stderr, "Generating Win64 routines...\n");
                    }
                    pArray = jsonIn_CheckNodeDataForArray(pNode);
                    if (pArray) {
                        //FIXME: eRc = dbprs_ParseRoutines(pPrs, pArray);
                    }
                    else {
                        fprintf(
                                stderr,
                                "FATAL - Found \"win64\" "
                                "node in database, but it is not an array object!\n\n\n"
                                );
                        exit(12);
                    }
                }
                break;
                
            default:
                appl_Usage(
                           (APPL_DATA *)this,
                           "ERROR - Failed to indicate type of makefile to generate!\n\n\n"
                           );
                exit(8);
        }
        
        // Generate the trailing part of the Makefile.
        //FIXME: eRc = dbprs_Finalize(pPrs);
        
        //FIXME: pStr = dbprs_getStr(pPrs);
        if (pStr) {
            textOut_PutA(this->pOutput, AStr_getData(pStr));
        }
        
        // Return to caller.
        //FIXME: obj_Release(pPrs);
        //FIXME: pPrs = OBJ_NIL;
        obj_Release(pGen);
        pGen = OBJ_NIL;
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
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&main_Vtbl);
        
        this->pDict = nodeHash_NewWithSize(NODEHASH_TABLE_SIZE_SMALL);
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
        ((APPL_DATA *)this)->iVerbose++;
        
    #ifdef NDEBUG
    #else
        if( !main_Validate(this) ) {
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
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
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
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
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
            eRc = nodeHash_AddA(main_getDict(this), 0, osTypeID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", osTypeID);
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        eRc = main_DefaultsMacos(this);

        pStr = AStr_NewA("d");
        if (pStr) {
            eRc = nodeHash_AddA(main_getDict(this), 0, makeTypeID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(stderr, "FATAL - Failed to add '%s' to Dictionary\n", makeTypeID);
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        pStr = AStr_NewA("lib");
        if (pStr) {
            eRc = nodeHash_AddA(main_getDict(this), 0, resultTypeID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        resultTypeID
                );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
#if defined(__MACOSX_ENV__)
        pStr = AStr_NewA("$(HOME)/Support/lib/$(SYS)");
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        pStr = AStr_NewA("C:/PROGRAMS");
#endif
        if (pStr) {
            eRc = nodeHash_AddA(main_getDict(this), 0, libBaseID, pStr);
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
        
#if defined(__MACOSX_ENV__)
        pStr = AStr_NewA("$(HOME)/Support/bin");
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        pStr = AStr_NewA("C:/PROGRAMS");
#endif
        if (pStr) {
            eRc = nodeHash_AddA(main_getDict(this), 0, outBaseID, pStr);
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
        
        pStr = AStr_NewA("./src");
        if (pStr) {
            eRc = nodeHash_AddA(main_getDict(this), 0, srcBaseID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        srcBaseID
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
            eRc = nodeHash_AddA(main_getDict(this), 0, tmpBaseID, pStr);
            if (ERESULT_FAILED(eRc) ) {
                fprintf(
                        stderr,
                        "FATAL - Failed to add '%s' to Dictionary\n",
                        tmpBaseID
                        );
                exit(EXIT_FAILURE);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
        NODEHASH_DATA   *pHash;
        NODE_DATA       *pFileNode;
        SRCPARSE_DATA   *pParser;

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
                    pStr = node_ToString(pFileNode);
                    fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        srcErrors_ExitOnFatal(OBJ_NIL);
        
        if (this->pNodes) {
            pHash = node_getData(this->pNodes);
            if (OBJ_NIL == pHash) {
                fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
                exit(12);
            }
            if (!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
                fprintf(stderr, "ERROR - Missing JSON Hash to process\n\n\n");
                exit(12);
            }
        }
        else {
            fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
            exit(12);
        }
        
        // Scan the JSON Node structure for consistancy with defined grammar.
        pParser = srcParse_New();
        if (OBJ_NIL == pParser) {
            fprintf(stderr, "ERROR - Unable to create Source Scanner!\n\n\n");
            exit(12);
        }
        obj_Release(pParser);
        pParser = OBJ_NIL;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         main_ParseInputStr(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        //ERESULT         eRc;
        HJSON_DATA      *pObj = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        NODE_DATA       *pFileNode;
        NODEHASH_DATA   *pHash;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pStrA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pObj = hjson_NewA(pStrA, 4);
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
        srcErrors_ExitOnFatal(OBJ_NIL);

        if (this->pNodes) {
            pHash = node_getData(this->pNodes);
            if (OBJ_NIL == pHash) {
                fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
                exit(12);
            }
            if (!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
                fprintf(stderr, "ERROR - Missing JSON Hash to process\n\n\n");
                exit(12);
            }
        }
        else {
            fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
            exit(12);
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
        return eRc;
    }
    
    
    /*!
     Process each command line argument, parsing the HJSON file and
     generating the Makefile.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
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
        PATH_DATA       *pMakefile = OBJ_NIL;
        PATH_DATA       *pMakepath = OBJ_NIL;

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
        TRC_OBJ(this, "main_ProcessArg(%s)\n", AStr_getData(pStr));
        
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
        
        eRc = main_DictAddA(this, srcFileID, path_getData(pPath));
        if (ERESULT_FAILED(eRc) ) {
            DEBUG_BREAK();
            fprintf(stderr, "FATAL - Failed to add 'srcFile' to Dictionary\n");
            exit(EXIT_FAILURE);
        }

        eRc = main_ParseInputFile(this, pPath);
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        // Create the output file path if given.
        if (OBJ_NIL == this->pOutputPath) {
            pMakefile = path_NewA("Makefile.${" osTypeID "}.txt");
            if (OBJ_NIL == pMakefile) {
                DEBUG_BREAK();
                fprintf(
                        stderr,
                        "FATAL - Unable to create Makefile name!\n"
                        );
                exit(EXIT_FAILURE);
            }
            pMakepath = path_NewFromDriveDirFilename(pDrive, pDir, pMakefile);
            if (OBJ_NIL == pMakefile) {
                DEBUG_BREAK();
                fprintf(
                        stderr,
                        "FATAL - Unable to create Makepath!\n"
                        );
                exit(EXIT_FAILURE);
            }
            eRc = path_ExpandVars(pMakepath, this->pDict);
            if (ERESULT_FAILED(eRc) ) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to expand Makepath\n");
                exit(EXIT_FAILURE);
            }
            eRc = path_IsFile(pMakepath);
            if (!ERESULT_FAILED(eRc) && this->fBackup) {
                eRc = path_VersionedRename(pMakepath);
            }
            this->pOutputPath = pMakepath;
            this->pOutput = textOut_NewFromPath(pMakepath);
            if (OBJ_NIL == this->pOutput) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to open \n");
                exit(EXIT_FAILURE);
            }
            obj_Release(pMakefile);
            pMakefile = OBJ_NIL;
        }
        if (!appl_getQuiet((APPL_DATA *)this)) {
            fprintf(stderr, "\t\tCreating %s\n", path_getData(this->pOutputPath));
        }

        // Generate the Makefile.
        eRc = main_GenMakefile(this);
        
        obj_Release(this->pOutput);
        this->pOutput = OBJ_NIL;
        
        // Return to caller.
        obj_Release(pMakepath);
        pMakepath = OBJ_NIL;
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
     @code
        ASTR_DATA      *pDesc = main_ToDebugString(this,4);
     @endcode
     @param     this    MAIN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
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
        
        fprintf(pOutput, "  --clp              Set type to Command Line Program\n");
        fprintf(pOutput, "                     (Default is Library)\n");
        fprintf(pOutput, "  --macos            Generate MacOSX nmake file (default)\n");
        fprintf(pOutput, "  --msc32            Generate MSC Win32 nmake file\n");
        fprintf(pOutput, "  --msc64            Generate MSC Win64 nmake file\n");
        fprintf(pOutput, "  (--out | -o) path  Output the generated data to <path>\n");
        
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
      
        fprintf(pOutput, "  %s [options] input_path\n", pNameA);
        
        // Return to caller.
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
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


