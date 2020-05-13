// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Gen.c
 *	Generated 05/05/2020 09:59:00
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
#include        <Gen_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    
    static
    const
    char        *pModelFileNames[] = {
        "model.obj._internal.h.txt",
        "model.obj._object.c.txt",
        "model.obj.h.txt",
        "model.obj.c.txt",
        NULL
    };
    static
    const
    char        *pModelJsonFileName = "model.obj._json.c.txt";
    static
    const
    char        *pModelTestFileName = "model.obj._test.c.txt";


#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
    static
    const
    char        *pModelDrvDir = "~/Support/genObject/";
    static
    const
    char        *pOutputDrvDir = "~/Support/x/";
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    //TODO: Change to fit
    static
    const
    char        *pModelDrvDir = "~/Support/genObject/";
    static
    const
    char        *pOutputDrvDir = "~/Support/x/";
#endif




 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    const
    char *          Gen_FindExpandA(
        GEN_DATA        *this,
        const
        char            *pNameA
    )
    {
        const
        char            *pStrA = NULL;

        pStrA = Dict_GetA(this->pDict, pNameA);
        return pStrA;
    }




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    GEN_DATA *     Gen_Alloc (
        void
    )
    {
        GEN_DATA       *this;
        uint32_t        cbSize = sizeof(GEN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    GEN_DATA *     Gen_New (
        void
    )
    {
        GEN_DATA       *this;
        
        this = Gen_Alloc( );
        if (this) {
            this = Gen_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      D i c t i o n a r y
    //---------------------------------------------------------------

    DICT_DATA *     Gen_getDict (
        GEN_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDict;
    }


    bool            Gen_setDict (
        GEN_DATA        *this,
        DICT_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
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
    //                  M o d e l  D r v  D i r
    //---------------------------------------------------------------

    const
    char *          Gen_getModelDrvDir (
        GEN_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->pModelDrvDir;
    }


    bool            Gen_setModelDrvDir (
        GEN_DATA        *this,
        const
        char            *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pModelDrvDir = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                  O u t p u t  D r v  D i r
    //---------------------------------------------------------------

    const
    char *          Gen_getOutputDrvDir (
        GEN_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->pOutputDrvDir;
    }


    bool            Gen_setOutputDrvDir (
        GEN_DATA        *this,
        const
        char            *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pOutputDrvDir = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Gen_getPriority (
        GEN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Gen_setPriority (
        GEN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
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
    
    uint32_t        Gen_getSize (
        GEN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Gen_getSuperVtbl (
        GEN_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
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
        ERESULT eRc = Gen_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another GEN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Gen_Assign (
        GEN_DATA		*this,
        GEN_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Gen_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

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
        //pOther->x     = this->x; 

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
    ERESULT         Gen_Compare (
        GEN_DATA     *this,
        GEN_DATA     *pOther
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
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Gen_Validate(pOther)) {
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
        Gen      *pCopy = Gen_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a GEN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    GEN_DATA *     Gen_Copy (
        GEN_DATA       *this
    )
    {
        GEN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef GEN_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Gen_New( );
        if (pOther) {
            eRc = Gen_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //               C r e a t e  M o d e l  P a t h
    //---------------------------------------------------------------

    PATH_DATA *     Gen_CreateModelPath (
        GEN_DATA        *this,
        ASTR_DATA       *pModelFileName
    )
    {
        const
        char            *pModelDriveA = OBJ_NIL;
        const
        char            *pModelDirA = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Gen_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if ((OBJ_NIL == pModelFileName) || (AStr_getSize(pModelFileName) < 15)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        pModelDriveA = Dict_GetA(this->pDict, MODEL_DRIVE);
        pModelDirA   = Dict_GetA(this->pDict, MODEL_DIR);

        pPath = Path_NewFromComponentsA(
                        pModelDriveA,
                        pModelDirA,
                        AStr_getData(pModelFileName),
                        NULL
                );

        // Return to caller.
        return pPath;
    }



    //---------------------------------------------------------------
    //            C r e a t e  O b j e c t  F i l e s
    //---------------------------------------------------------------

    ERESULT         Gen_CreateObjectFIles (
        GEN_DATA        *this,
        NODECLASS_DATA  *pClass,
        bool            fVerbose
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        for (i=0; pModelFileNames[i]; i++) {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = AStr_NewA(pModelFileNames[i]);
            if (pStr) {
                eRc = Gen_ExpandFile(this, pStr, fVerbose);
                obj_Release(pStr);
                pStr = OBJ_NIL;
                if (ERESULT_FAILED(eRc))
                    break;
            }
        }

        if (ERESULT_OK(eRc)) {
            ASTR_DATA       *pStr = OBJ_NIL;
            if (NodeClass_getJson(pClass)) {
                pStr = AStr_NewA(pModelJsonFileName);
                if (pStr) {
                    eRc = Gen_ExpandFile(this, pStr, fVerbose);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
        }

        if (ERESULT_OK(eRc)) {
            ASTR_DATA       *pStr = OBJ_NIL;
            if (NodeClass_getTest(pClass)) {
                pStr = AStr_NewA(pModelTestFileName);
                if (pStr) {
                    eRc = Gen_ExpandFile(this, pStr, fVerbose);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //               C r e a t e  O u t p u t  P a t h
    //---------------------------------------------------------------

    PATH_DATA *     Gen_CreateOutputPath (
        GEN_DATA        *this,
        ASTR_DATA       *pModelFileName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pObjName = OBJ_NIL;
        const
        char            *pOutputDriveA = OBJ_NIL;
        const
        char            *pOutputDirA = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Gen_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if ((OBJ_NIL == pModelFileName) || (AStr_getSize(pModelFileName) < 15)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        pObjName = Dict_FindA(this->pDict, OBJECT_NAME);
        eResult_ErrorFatalOnBool(
                        (OBJ_NIL == pObjName),
                        "Object Name is missing!\n"
        );
        pOutputDriveA = Dict_GetA(this->pDict, OUTPUT_DRIVE);
        pOutputDirA   = Dict_GetA(this->pDict, OUTPUT_DIR);

        eRc = AStr_CompareLeftA(pModelFileName, "model.obj");
        eResult_ErrorFatalOnBool(
                        (eRc != ERESULT_SUCCESS_EQUAL),
                        "Model Path is not \"model.obj.X.txt, %s!\n",
                        AStr_getData(pModelFileName)
        );
        eRc = AStr_CompareRightA(pModelFileName, ".txt");
        eResult_ErrorFatalOnBool(
                        (eRc != ERESULT_SUCCESS_EQUAL),
                        "Model Path is not \"model.obj.X.txt, %s!\n",
                        AStr_getData(pModelFileName)
        );

        eRc =   AStr_Mid(
                       pModelFileName,
                       11,
                       (AStr_getSize(pModelFileName) - 14),
                       &pStr
                );
        eResult_ErrorFatalOnBool(
                        (ERESULT_FAILED(eRc) || (pStr == OBJ_NIL)),
                        "Model Path is not \"model.obj.X.txt, %s!\n",
                        AStr_getData(pModelFileName)
        );
        if ('_' != AStr_CharGetW32(pStr, 1)) {
            eRc = AStr_InsertA(pStr, 1, ".");
        }
        eRc = AStr_InsertA(pStr, 1, AStr_getData(pObjName));
        eResult_ErrorFatalOn(
                        eRc,
                        "Failed to build output filename for %s!\n",
                        AStr_getData(pModelFileName)
        );

        pPath = Path_NewFromComponentsA(
                        pOutputDriveA,
                        pOutputDirA,
                        AStr_getData(pStr),
                        NULL
                );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        // Return to caller.
        return pPath;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Gen_Dealloc (
        OBJ_ID          objId
    )
    {
        GEN_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((GEN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Gen_setDict(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Gen      *pDeepCopy = Gen_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a GEN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    GEN_DATA *     Gen_DeepyCopy (
        GEN_DATA       *this
    )
    {
        GEN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Gen_New( );
        if (pOther) {
            eRc = Gen_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
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
    ERESULT         Gen_Disable (
        GEN_DATA		*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
    ERESULT         Gen_Enable (
        GEN_DATA		*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E x p a n d
    //---------------------------------------------------------------

    ERESULT         Gen_ExpandData (
        GEN_DATA        *this,
        TEXTIN_DATA     *pInput,
        TEXTOUT_DATA    *pOutput,
        uint32_t        *pCnt
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pLine = OBJ_NIL;
        SRCLOC          loc = {0};
        uint32_t        cnt = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pInput) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (OBJ_NIL == pOutput) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        while (true) {
            eRc = TextIn_GetLineAStr(pInput, &pLine, &loc);
            if (ERESULT_FAILED(eRc)) {
                if (ERESULT_EOF_ERROR == eRc)
                    eRc = ERESULT_SUCCESS;
                break;
            } else {
                if (OBJ_NIL != pLine) {
                    eRc = AStr_ExpandVars(pLine, (void *)Gen_FindExpandA, this);
                    if ((OBJ_NIL != pLine) && (AStr_getSize(pLine) != 0)) {
                        eRc = TextOut_PutAStr(pOutput, pLine);
                        if (ERESULT_FAILED(eRc)) {
                            obj_Release(pLine);
                            pLine = OBJ_NIL;
                            break;
                        }
                    }
                    eRc = TextOut_Putc(pOutput, '\n');
                    if (ERESULT_FAILED(eRc)) {
                        obj_Release(pLine);
                        pLine = OBJ_NIL;
                        break;
                    }
                    obj_Release(pLine);
                    pLine = OBJ_NIL;
                    cnt++;
                }
            }
        }

        // Return to caller.
        if (pCnt)
            *pCnt = cnt;
        return eRc;
    }


    ERESULT         Gen_ExpandFile (
        GEN_DATA        *this,
        ASTR_DATA       *pModel,
        bool            fVerbose
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        PATH_DATA       *pModelPath = OBJ_NIL;
        PATH_DATA       *pOutputPath = OBJ_NIL;
        TEXTIN_DATA     *pInput = OBJ_NIL;
        TEXTOUT_DATA    *pOutput = OBJ_NIL;
        uint32_t        cnt = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pModelPath = Gen_CreateModelPath(this, pModel);
        eResult_ErrorFatalOnBool(
                        (OBJ_NIL == pModelPath),
                        "Could not generate Model Path from %s!\n",
                        AStr_getData(pModel)
        );
        pOutputPath = Gen_CreateOutputPath(this, pModel);
        eResult_ErrorFatalOnBool(
                        (OBJ_NIL == pModelPath),
                        "Could not generate Output Path from %s!\n",
                        AStr_getData(pModel)
        );

        pInput = TextIn_NewFromPath(pModelPath, 1, 4);
        eResult_ErrorFatalOnBool(
                        (OBJ_NIL == pInput),
                        "Could not open input file, %s!\n",
                        Path_getData(pModelPath)
        );
        pOutput = TextOut_NewFromPath(pOutputPath);
        eResult_ErrorFatalOnBool(
                        (OBJ_NIL == pOutput),
                        "Could not open input file, %s!\n",
                        Path_getData(pOutputPath)
        );
        if (fVerbose) {
            fprintf(stderr,
                    "\t\t%s -> %s\n",
                    Path_getData(pModelPath),
                    Path_getData(pOutputPath)
            );
        }
        cnt = 0;
        eRc = Gen_ExpandData(this, pInput, pOutput, &cnt);
        if (fVerbose) {
            fprintf(stderr, "\t\t%d lines\n", cnt);
        }

        obj_Release(pInput);
        pInput = OBJ_NIL;
        obj_Release(pOutput);
        pOutput = OBJ_NIL;
        obj_Release(pModelPath);
        pModelPath = OBJ_NIL;
        obj_Release(pOutputPath);
        pOutputPath = OBJ_NIL;

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    GEN_DATA *   Gen_Init (
        GEN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(GEN_DATA);
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_GEN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Gen_Vtbl);

        this->pModelDrvDir  = pModelDrvDir;
        this->pOutputDrvDir = pOutputDrvDir;
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
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Gen::sizeof(GEN_DATA) = %lu\n", 
                sizeof(GEN_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(GEN_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Gen_IsEnabled (
        GEN_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
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
        void        *pMethod = Gen_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Gen", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Gen_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        GEN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(GEN_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Gen_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
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
                            return Gen_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Gen_Enable;
                        }
                        break;

                    case 'P':
#ifdef  GEN_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Gen_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Gen_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Gen_ToDebugString;
                        }
#ifdef  GEN_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Gen_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Gen_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Gen_ToDebugString)
                    return "ToDebugString";
#ifdef  GEN_JSON_SUPPORT
                if (pData == Gen_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
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
    ERESULT         Gen_SetDefaults (
        GEN_DATA        *this
    )
    {
        ERESULT         eRc;
        //ASTR_DATA       *pOS = OBJ_NIL;
        //ASTR_DATA       *pArch = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pStr2 = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        long            clock;
        struct tm       *now;
        char            str[32];

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Gen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Set up DATE and TIME.
        (void) time (&clock);
        now = localtime (&clock);
        snprintf(
                       str,
                       sizeof(str),
                       "%2.2d/%2.2d/%2.2d",
                       now->tm_mon+1,
                       now->tm_mday,
                       now->tm_hour
        );
        pStr = AStr_NewA(str);
        if (pStr) {
            eRc = Dict_AddAStr(this->pDict, GEN_DATE, pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        snprintf(
                 str,
                 sizeof(str),
                 "%2.2d:%2.2d:%2.2d",
                 now->tm_hour,
                 now->tm_min,
                 now->tm_sec
        );
        pStr = AStr_NewA(str);
        if (pStr) {
            eRc = Dict_AddAStr(this->pDict, GEN_TIME, pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        pPath = Path_NewA(this->pModelDrvDir);
        if (pPath) {
            eRc = Path_Split(pPath, &pStr, &pStr2, OBJ_NIL, OBJ_NIL);
            if (pStr) {
                eRc = Dict_AddAStr(this->pDict, MODEL_DRIVE, pStr);
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            if (pStr2) {
                eRc = Dict_AddAStr(this->pDict, MODEL_DIR, pStr2);
                obj_Release(pStr2);
                pStr2 = OBJ_NIL;
            }
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        pPath = Path_NewA(this->pOutputDrvDir);
        if (pPath) {
            eRc = Path_Split(pPath, &pStr, &pStr2, OBJ_NIL, OBJ_NIL);
            if (pStr) {
                eRc = Dict_AddAStr(this->pDict, OUTPUT_DRIVE, pStr);
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            if (pStr2) {
                eRc = Dict_AddAStr(this->pDict, OUTPUT_DIR, pStr2);
                obj_Release(pStr2);
                pStr2 = OBJ_NIL;
            }
            obj_Release(pPath);
            pPath = OBJ_NIL;
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
        ASTR_DATA      *pDesc = Gen_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Gen_ToDebugString (
        GEN_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Gen_Validate(this)) {
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
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    Gen_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    bool            Gen_Validate (
        GEN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_GEN))
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


        if (!(obj_getSize(this) >= sizeof(GEN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


