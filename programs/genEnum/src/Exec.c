// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Exec.c
 *  Generated 10/31/2021 18:53:12
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
#include        <Exec_internal.h>
#include        <JsonIn.h>
#include        <TextIn.h>
#include        <TextOut.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.


 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Exec_task_body (
        void            *pData
    )
    {
        //EXEC_DATA  *this = pData;
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    EXEC_DATA *     Exec_Alloc (
        void
    )
    {
        EXEC_DATA       *this;
        uint32_t        cbSize = sizeof(EXEC_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    EXEC_DATA *     Exec_New (
        void
    )
    {
        EXEC_DATA       *this;
        
        this = Exec_Alloc( );
        if (this) {
            this = Exec_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------

    ASTRARRAY_DATA * Exec_getArray (
        EXEC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }


    bool            Exec_setArray (
        EXEC_DATA       *this,
        ASTRARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------

    U16ARRAY_DATA * Exec_getIndex (
        EXEC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pIndex;
    }


    bool            Exec_setIndex (
        EXEC_DATA       *this,
        U16ARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pIndex) {
            obj_Release(this->pIndex);
        }
        this->pIndex = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Exec_getPriority (
        EXEC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Exec_setPriority (
        EXEC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
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
    
    uint32_t        Exec_getSize (
        EXEC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                   S o r t e d  A r r a y
    //---------------------------------------------------------------

    ASTRARRAY_DATA * Exec_getSorted (
        EXEC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pSorted;
    }


    bool            Exec_setSorted (
        EXEC_DATA       *this,
        ASTRARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pSorted) {
            obj_Release(this->pSorted);
        }
        this->pSorted = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                         S t a r t
    //---------------------------------------------------------------

    ASTR_DATA *     Exec_getStart (
        EXEC_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pStart;
    }


    bool            Exec_setStart (
        EXEC_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStart) {
            obj_Release(this->pStart);
        }
        this->pStart = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     Exec_getStr (
        EXEC_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool            Exec_setStr (
        EXEC_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  Exec_getSuperVtbl (
        EXEC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
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
        ERESULT eRc = Exec_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another EXEC object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Exec_Assign (
        EXEC_DATA       *this,
        EXEC_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Exec_Validate(pOther)) {
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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Exec_Compare (
        EXEC_DATA     *this,
        EXEC_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Exec_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Exec      *pCopy = Exec_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a EXEC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    EXEC_DATA *     Exec_Copy (
        EXEC_DATA       *this
    )
    {
        EXEC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef EXEC_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Exec_New( );
        if (pOther) {
            eRc = Exec_Assign(this, pOther);
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
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Exec_Dealloc (
        OBJ_ID          objId
    )
    {
        EXEC_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((EXEC_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Exec_setArray(this, OBJ_NIL);
        Exec_setIndex(this, OBJ_NIL);
        Exec_setSorted(this, OBJ_NIL);
        Exec_setStart(this, OBJ_NIL);
        Exec_setStr(this, OBJ_NIL);

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
        Exec      *pDeepCopy = Exec_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a EXEC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    EXEC_DATA *     Exec_DeepCopy (
        EXEC_DATA       *this
    )
    {
        EXEC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Exec_New( );
        if (pOther) {
            eRc = Exec_Assign(this, pOther);
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
    ERESULT         Exec_Disable (
        EXEC_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
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
    ERESULT         Exec_Enable (
        EXEC_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E x e c
    //---------------------------------------------------------------

    /*!
     Create the document.
     @param     this        object pointer
     @param     pInputPath  input path pointer
     @param     pOutputPath output path pointer
     @param     pPrefixA    object name prefix
     @param     pNameA      enumeration name
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Exec_Exec (
        EXEC_DATA       *this,
        PATH_DATA       *pInputPath,
        PATH_DATA       *pOutputPath,
        const
        char            *pPrefixA,
        const
        char            *pNameA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TEXTIN_DATA     *pIn = OBJ_NIL;
        //TEXTOUT_DATA    *pOut;
        ASTRARRAY_DATA  *pArray = OBJ_NIL;
        ASTRARRAY_DATA  *pSorted = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        bool            fJson = false;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (pInputPath) {
            eRc = Path_IsFile(pInputPath);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            pIn = TextIn_NewFromPath(pInputPath, 0, 4);
            if (OBJ_NIL == pIn) {
                return ERESULT_FILE_NOT_FOUND;
            }
        }
#ifdef XYZZY
        if (pOutputPath) {
            eRc = Path_IsFile(pOutputPath);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            pOut = TextOut_NewFromPath(pOutputPath, 0, 4);
            if (OBJ_NIL == pIn) {
                return ERESULT_FILE_NOT_FOUND;
            }
        }
#endif

        pArray = Exec_ReadFileOld(this, pIn);
        obj_Release(pIn);
        pIn = OBJ_NIL;
        if (OBJ_NIL == pArray) {
            return ERESULT_GENERAL_FAILURE;
        }

        pSorted = AStrArray_Copy(pArray);
        if (OBJ_NIL == pSorted) {
            obj_Release(pArray);
            pArray = OBJ_NIL;
            return ERESULT_GENERAL_FAILURE;
        }
        eRc = AStrArray_SortAscending(pSorted);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        this->pArray = pArray;
        this->pSorted = pSorted;
        iMax = AStrArray_getSize(pSorted);
        this->pIndex = U16Array_NewMinSize(this->maxIndex);
        if (this->pIndex) {
            for (i=0; i<iMax; i++) {
                ASTR_DATA       *pStr = AStrArray_Get(this->pSorted, i+1);
                if (pStr) {
                    eRc = U16Array_Put(this->pIndex, obj_getMisc(pStr)+1, i+1);
                }
            }
        }

        eRc = Exec_GenEnum(this, pInputPath, pPrefixA, pNameA);
        eRc = Exec_GenTables(this, pInputPath, pPrefixA, pNameA);
        eRc = Exec_GenRoutines(this, pInputPath, pPrefixA, pNameA);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      G e n e r a t e
    //---------------------------------------------------------------

    /*!
     Generate the enum constant.
     @param     this        object pointer
     @param     pInputPath  input path pointer
     @param     pPrefixA    object name prefix
     @param     pNameA      enumeration name
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Exec_GenEnum (
        EXEC_DATA       *this,
        PATH_DATA       *pInputPath,
        const
        char            *pPrefixA,
        const
        char            *pNameA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        iMax;
        FILE            *pOut = stdout;
        ASTR_DATA       *pCapsPrefix = OBJ_NIL;
        ASTR_DATA       *pCapsName = OBJ_NIL;
        PATH_DATA       *pFileName = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pCapsName = AStr_NewUpperA(pNameA);
        pCapsPrefix = AStr_NewUpperA(pPrefixA);
        eRc = Path_SplitPath(pInputPath, OBJ_NIL, OBJ_NIL, &pFileName);

        fprintf(pOut, "\n\n\n");
        fprintf(pOut, "\t/* The following enum was generated from:\n");
        fprintf(pOut, "\t * \"%s\"\n", Path_getData(pFileName));
        fprintf(pOut, "\t * If you want to change this enum, you\n");
        fprintf(pOut, "\t * should alter the above file and\n");
        fprintf(pOut, "\t * regenerate using genEnum!\n");
        fprintf(pOut, "\t */\n\n");
        fprintf(pOut, "\ttypedef enum %s_%s_e {\n", pPrefixA, pNameA);
        iMax = AStrArray_getSize(this->pArray);
        for (i=0; i<iMax; i++) {
            ASTR_DATA       *pLine = AStrArray_Get(this->pArray, i+1);
            if (pLine) {
                if (this->pStart) {
                    fprintf(
                            pOut,
                            "\t\t%s_%s_%s=%s+%d,\n",
                            AStr_getData(pCapsPrefix),
                            AStr_getData(pCapsName),
                            AStr_getData(pLine),
                            AStr_getData(this->pStart),
                            obj_getMisc(pLine)
                    );
                } else {
                    fprintf(
                            pOut,
                            "\t\t%s_%s_%s=%d,\n",
                            AStr_getData(pCapsPrefix),
                            AStr_getData(pCapsName),
                            AStr_getData(pLine),
                            obj_getMisc(pLine)
                    );
                }
            }
        }

        fprintf(pOut, "\t} %s_%sS;\n\n", AStr_getData(pCapsPrefix), AStr_getData(pCapsName));
        fprintf(pOut, "\n\n\n");

        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        obj_Release(pCapsName);
        obj_Release(pCapsPrefix);

        // Return to caller.
        return eRc;
    }


    /*!
     Generate the routines for the tables.
     @param     this        object pointer
     @param     pPrefixA    object name prefix
     @param     pNameA      enumeration name
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Exec_GenRoutines (
        EXEC_DATA       *this,
        PATH_DATA       *pInputPath,
        const
        char            *pPrefixA,
        const
        char            *pNameA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        FILE            *pOut = stdout;
        ASTR_DATA       *pCapsPrefix = OBJ_NIL;
        ASTR_DATA       *pCapsName = OBJ_NIL;
        PATH_DATA       *pFileName = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pCapsName = AStr_NewUpperA(pNameA);
        pCapsPrefix = AStr_NewUpperA(pPrefixA);
        eRc = Path_SplitPath(pInputPath, OBJ_NIL, OBJ_NIL, &pFileName);

        fprintf(pOut, "\t/* The following routine was generated from:\n");
        fprintf(pOut, "\t * \"%s\"\n", Path_getData(pFileName));
        fprintf(pOut, "\t * If you want to change it, you\n");
        fprintf(pOut, "\t * should alter the above file and\n");
        fprintf(pOut, "\t * regenerate using genEnum!\n");
        fprintf(pOut, "\t */\n\n");

        fprintf(pOut, "\t// Given an enum value, return its character format.\n");
        fprintf(pOut, "\tconst\n");
        fprintf(pOut, "\tchar *\t\t\t%s_%sToDesc (\n", pPrefixA, pNameA);
        fprintf(pOut, "\t\tuint32_t\t\tvalue\n");
        fprintf(pOut, "\t)\n");
        fprintf(pOut, "\t{\n");
        if (this->pStart) {
            fprintf(
                    pOut,
                    "\t\tif ((value - %s) >= c%s_%s_index) {\n",
                    AStr_getData(this->pStart),
                    pPrefixA,
                    pNameA
            );
        } else {
            fprintf(pOut, "\t\tif (value >= c%s_%s_index) {\n", pPrefixA, pNameA);
        }
        fprintf(pOut, "\t\t\treturn \"<<<Unknown Enum Value>>>\";\n");
        fprintf(pOut, "\t\t}\n");
#ifdef XYZZY
        fprintf(pOut, "\t\treturn p%s_%s_desc[value];\n", pPrefixA, pNameA);
#else
        if (this->pStart) {
            fprintf(
                    pOut,
                    "\t\tif (%s_%s_index[value - %s]) {\n",
                    pPrefixA,
                    pNameA,
                    AStr_getData(this->pStart)
            );
            fprintf(
                    pOut,
                    "\t\t\treturn %s_%s_entries[%s_%s_index[value - %s] - 1].pDesc;\n",
                    pPrefixA,
                    pNameA,
                    pPrefixA,
                    pNameA,
                    AStr_getData(this->pStart)
            );
        } else {
            fprintf(
                    pOut,
                    "\t\tif (%s_%s_index[value]) {\n",
                    pPrefixA,
                    pNameA
            );
            fprintf(
                    pOut,
                    "\t\t\treturn %s_%s_entries[%s_%s_index[value] - 1].pDesc;\n",
                    pPrefixA,
                    pNameA,
                    pPrefixA,
                    pNameA
            );
        }
        fprintf(pOut, "\t\t} else {\n");
        fprintf(pOut, "\t\t\treturn \"<<<Unknown Enum Value>>>\";\n");
        fprintf(pOut, "\t\t}\n");
#endif
        fprintf(pOut, "\t}\n\n");

        fprintf(pOut, "\t// Given an enum value, return its name.\n");
        fprintf(pOut, "\tconst\n");
        fprintf(pOut, "\tchar *\t\t\t%s_%sToName (\n", pPrefixA, pNameA);
        fprintf(pOut, "\t\tuint32_t\t\tvalue\n");
        fprintf(pOut, "\t)\n");
        fprintf(pOut, "\t{\n");
        if (this->pStart) {
            fprintf(
                    pOut,
                    "\t\tif ((value - %s) >= c%s_%s_index) {\n",
                    AStr_getData(this->pStart),
                    pPrefixA,
                    pNameA
            );
        } else {
            fprintf(pOut, "\t\tif (value >= c%s_%s_index) {\n", pPrefixA, pNameA);
        }
        fprintf(pOut, "\t\t\treturn NULL;\n");
        fprintf(pOut, "\t\t}\n");
        if (this->pStart) {
            fprintf(
                    pOut,
                    "\t\tif (%s_%s_index[value - %s]) {\n",
                    pPrefixA,
                    pNameA,
                    AStr_getData(this->pStart)
            );
            fprintf(
                    pOut,
                    "\t\t\treturn %s_%s_entries[%s_%s_index[value - %s] - 1].pName;\n",
                    pPrefixA,
                    pNameA,
                    pPrefixA,
                    pNameA,
                    AStr_getData(this->pStart)
            );
        } else {
            fprintf(
                    pOut,
                    "\t\tif (%s_%s_index[value]) {\n",
                    pPrefixA,
                    pNameA
            );
            fprintf(
                    pOut,
                    "\t\t\treturn %s_%s_entries[%s_%s_index[value] - 1].pName;\n",
                    pPrefixA,
                    pNameA,
                    pPrefixA,
                    pNameA
            );
        }
        fprintf(pOut, "\t\t} else {\n");
        fprintf(pOut, "\t\t\treturn NULL;\n");
        fprintf(pOut, "\t\t}\n");
        fprintf(pOut, "\t}\n");

        fprintf(pOut, "\n\n\n");

        fprintf(pOut, "\t/* The following routine was generated from:\n");
        fprintf(pOut, "\t * \"%s\"\n", Path_getData(pFileName));
        fprintf(pOut, "\t * If you want to change it, you\n");
        fprintf(pOut, "\t * should alter the above file and\n");
        fprintf(pOut, "\t * regenerate using genEnum!\n");
        fprintf(pOut, "\t */\n\n");

        fprintf(pOut, "\t// Given an enum description, return its value + 1 or\n");
        fprintf(pOut, "\t// 0 for not found.\n");
        fprintf(pOut, "\tconst\n");
        fprintf(pOut, "\tuint32_t\t\t%s_DescTo%s (\n", pPrefixA, pNameA);
        fprintf(pOut, "\t\tchar\t\t\t*pDesc\n");
        fprintf(pOut, "\t)\n");
        fprintf(pOut, "\t{\n");
        fprintf(pOut, "\t\tint\t\t\tiRc;\n");
        fprintf(pOut, "\t\tuint32_t\t\tiMax = c%s_%s_entries;\n", pPrefixA, pNameA);
        fprintf(pOut, "\t\tuint32_t\t\ti    = 0;\n");
        fprintf(pOut, "\t\tuint32_t\t\thigh = 0;\n");
        fprintf(pOut, "\t\tuint32_t\t\tlow  = 0;\n");
        fprintf(pOut, "\t\tuint32_t\t\tmid  = 0;\n\n");
        fprintf(pOut, "\t\tif (iMax > 10) {\n");
        fprintf(pOut, "\t\t\tfor (i=0; i<iMax; i++) {\n");
        fprintf(
                pOut,
                "\t\t\t\tiRc = strcmp(pDesc, %s_%s_entries[i].pDesc);\n",
                pPrefixA,
                pNameA
        );
        fprintf(pOut, "\t\t\t\tif (0 == iRc) {\n");
        fprintf(
                pOut,
                "\t\t\t\t\treturn %s_%s_entries[i].value + 1;\n",
                pPrefixA,
                pNameA
        );
        fprintf(pOut, "\t\t\t\t}\n");
        fprintf(pOut, "\t\t\t\tif (iRc < 0) {\n");
        fprintf(pOut, "\t\t\t\t\tbreak;\n");
        fprintf(pOut, "\t\t\t\t}\n");
        fprintf(pOut, "\t\t\t}\n");
        fprintf(pOut, "\t\t} else {\n");
        fprintf(pOut, "\t\t\thigh = iMax - 1;\n");
        fprintf(pOut, "\t\t\twhile (low < high) {\n");
        fprintf(pOut, "\t\t\t\tmid = (high + low) / 2;\n");
        fprintf(pOut, "\t\t\t\ti = mid + 1;\n");
        fprintf(
                pOut,
                "\t\t\t\tiRc = strcmp(pDesc, %s_%s_entries[i].pDesc);\n",
                pPrefixA,
                pNameA
        );
        fprintf(pOut, "\t\t\t\tif (iRc < 0) {\n");
        fprintf(pOut, "\t\t\t\t\thigh = mid;\n");
        fprintf(pOut, "\t\t\t\t} else if (iRc == 0) {\n");
        fprintf(
                pOut,
                "\t\t\t\t\treturn %s_%s_entries[i].value + 1;\n",
                pPrefixA,
                pNameA
        );
        fprintf(pOut, "\t\t\t\t} else {\n");
        fprintf(pOut, "\t\t\t\t\tlow = mid + 1;\n");
        fprintf(pOut, "\t\t\t\t}\n");
        fprintf(pOut, "\t\t\t}\n");
        fprintf(pOut, "\t\t\tif( high == low ) {\n");
        fprintf(pOut, "\t\t\t\ti = low;\n");
        fprintf(
                pOut,
                "\t\t\t\tiRc = strcmp(pDesc, %s_%s_entries[i].pDesc);\n",
                pPrefixA,
                pNameA
        );
        fprintf(pOut, "\t\t\t\tif (0 == iRc) {\n");
        fprintf(
                pOut,
                "\t\t\t\t\treturn %s_%s_entries[i].value + 1;\n",
                pPrefixA,
                pNameA
        );
        fprintf(pOut, "\t\t\t\t}\n");
        fprintf(pOut, "\t\t\t}\n");
        fprintf(pOut, "\t\t}\n");
        fprintf(pOut, "\t\treturn 0;\n");
        fprintf(pOut, "\t}\n");
        fprintf(pOut, "\n\n\n");

        fprintf(pOut, "\n\n\n");

        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        obj_Release(pCapsName);
        obj_Release(pCapsPrefix);

        // Return to caller.
        return eRc;
    }


    /*!
     Generate the constant tables.
     @param     this        object pointer
     @param     pInputPath  input path pointer
     @param     pPrefixA    object name prefix
     @param     pNameA      enumeration name
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Exec_GenTables (
        EXEC_DATA       *this,
        PATH_DATA       *pInputPath,
        const
        char            *pPrefixA,
        const
        char            *pNameA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        iMax;
        FILE            *pOut = stdout;
        ASTR_DATA       *pCapsPrefix = OBJ_NIL;
        ASTR_DATA       *pCapsName = OBJ_NIL;
        PATH_DATA       *pFileName = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pCapsName = AStr_NewUpperA(pNameA);
        pCapsPrefix = AStr_NewUpperA(pPrefixA);
        eRc = Path_SplitPath(pInputPath, OBJ_NIL, OBJ_NIL, &pFileName);

        fprintf(pOut, "\n\n\n");
        fprintf(pOut, "\t/* The following tables were generated from:\n");
        fprintf(pOut, "\t * \"%s\"\n", Path_getData(pFileName));
        fprintf(pOut, "\t * If you want to change this enum, you\n");
        fprintf(pOut, "\t * should alter the above file and\n");
        fprintf(pOut, "\t * regenerate using genEnum!\n");
        fprintf(pOut, "\t */\n\n");

        fprintf(pOut, "\t// This table is in enum order and provides\n");
        fprintf(pOut, "\t// the index + 1 into the %s_%s_entries\n", pPrefixA, pNameA);
        fprintf(pOut, "\t// table. 0 means no enum entry.\n");
        fprintf(pOut, "\tconst\n");
        fprintf(
                pOut,
                "\tuint16_t\t%s_%s_index[%d] = {\n",
                pPrefixA,
                pNameA,
                this->maxIndex
        );
        iMax = this->maxIndex;
        for (i=0; i<iMax; i++) {
            uint16_t        index = U16Array_Get(this->pIndex, i+1);
            fprintf(pOut, "\t\t%d,\n", index);
        }
        fprintf(pOut, "\t};\n\n\n");
        fprintf(pOut, "\tconst\n");
        fprintf(
                pOut,
                "\tuint32_t\tc%s_%s_index = %d;\n\n\n\n\n",
                pPrefixA,
                pNameA,
                iMax
        );

        fprintf(pOut, "\ttypedef struct {\n");
        fprintf(pOut, "\t\tconst\n");
        fprintf(pOut, "\t\tchar\t\t\t*pDesc;\n");
        fprintf(pOut, "\t\tchar\t\t\t*pName;\n");
        fprintf(pOut, "\t\tuint32_t\t\tvalue;\n");
        fprintf(pOut, "\t} %s_%s_entry;\n\n", pPrefixA, pNameA);
        fprintf(pOut, "\t// This table is in alphanumeric order to be searched\n");
        fprintf(pOut, "\t// with a sequential or binary search by description.\n\n");
        fprintf(pOut, "\tconst\n");
        fprintf(pOut, "\t%s_%s_entry\t%s_%s_entries[] = {\n", pPrefixA, pNameA, pPrefixA, pNameA);
        iMax = AStrArray_getSize(this->pSorted);
        for (i=0; i<iMax; i++) {
            ASTR_DATA       *pLine = AStrArray_Get(this->pSorted, i+1);
            if (pLine) {
                if (this->pStart) {
                    fprintf(
                            pOut,
                            "\t\t{\"%s_%s_%s\", \"%s\", %s+%d},\n",
                            AStr_getData(pCapsPrefix),
                            AStr_getData(pCapsName),
                            AStr_getData(pLine),
                            AStr_getData(pLine),
                            AStr_getData(this->pStart),
                            obj_getMisc(pLine)
                    );
                } else {
                    fprintf(
                            pOut,
                            "\t\t{\"%s_%s_%s\", \"%s\", %d},\n",
                            AStr_getData(pCapsPrefix),
                            AStr_getData(pCapsName),
                            AStr_getData(pLine),
                            AStr_getData(pLine),
                            obj_getMisc(pLine)
                    );
                }
            }
        }
        fprintf(pOut, "\t};\n");
        fprintf(
                pOut,
                "\tuint32_t\tc%s_%s_entries = %d;\n\n\n\n\n",
                pPrefixA,
                pNameA,
                iMax
        );
        fprintf(pOut, "\n\n\n\n\n");


        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        obj_Release(pCapsName);
        obj_Release(pCapsPrefix);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    EXEC_DATA *   Exec_Init (
        EXEC_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(EXEC_DATA);
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
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of Exec_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_EXEC);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Exec_Vtbl);
#ifdef  EXEC_JSON_SUPPORT
        JsonIn_RegisterClass(Exec_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Exec::sizeof(EXEC_DATA) = %lu\n", 
                sizeof(EXEC_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(EXEC_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Exec_IsEnabled (
        EXEC_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
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
        void        *pMethod = Exec_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Exec", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Exec_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        EXEC_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(EXEC_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Exec_Class();
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
                            return Exec_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Exec_Enable;
                        }
                        break;

                    case 'P':
#ifdef  EXEC_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Exec_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Exec_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Exec_ToDebugString;
                        }
#ifdef  EXEC_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Exec_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Exec_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Exec_ToDebugString)
                    return "ToDebugString";
#ifdef  EXEC_JSON_SUPPORT
                if (pData == Exec_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      R e a d  F i l e
    //---------------------------------------------------------------

    /*!
     Read the input file into an array.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ASTRARRAY_DATA * Exec_ReadFileOld (
        EXEC_DATA       *this,
        TEXTIN_DATA     *pIn
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pLine = OBJ_NIL;
        SRCLOC          loc = {0};
        uint32_t        lineNo = 0;
        W32CHR_T        chrW;
        ASTRARRAY_DATA  *pArray = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Exec_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pArray;
        }
#endif
        pArray = AStrArray_New();
        if (OBJ_NIL == pArray) {
            //return ERESULT_OUT_OF_MEMORY;
            return pArray;
        }

        for (;;) {
            eRc = TextIn_GetLineAStr(pIn, &pLine, &loc);
            if (ERESULT_FAILED(eRc))
                break;
            if (pLine) {
                AStr_Trim(pLine);
                TRC_OBJ(this,"\t%d : (%d)%s\n", lineNo, AStr_getLength(pLine), AStr_getData(pLine));
                if ( AStr_getLength(pLine) && (AStr_CharGetFirstW32(pLine) == '#')) {
                    obj_Release(pLine);
                    pLine = OBJ_NIL;
                    continue;
                }
                if (AStr_getLength(pLine) > 0) {
                    ASTR_DATA       *pStr = OBJ_NIL;
                    chrW = AStr_CharGetLastW32(pLine);
                    if (',' == chrW) {
                        eRc = AStr_Truncate(pLine, (AStr_getLength(pLine) - 1));
                    }
                    pStr = AStr_ToUpper(pLine);
                    obj_setMisc(pStr, lineNo);
                    TRC_OBJ(
                            this,
                            "\tAppend %d : (%d)%s\n",
                            lineNo,
                            AStr_getLength(pStr),
                            AStr_getData(pStr)
                    );
                    if (AStr_getLength(pStr)) {
                        eRc = AStrArray_AppendStr(pArray, pStr, NULL);
                    }
                    lineNo++;
                    obj_Release(pStr);
                    //pStr = OBJ_NIL;
                } else {
                    lineNo++;
                }
                obj_Release(pLine);
                pLine = OBJ_NIL;
            }
        }
        this->maxIndex = lineNo;

        // Return to caller.
        return pArray;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Exec_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Exec_ToDebugString (
        EXEC_DATA      *this,
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
        if (!Exec_Validate(this)) {
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
                    Exec_getSize(this),
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
    bool            Exec_Validate (
        EXEC_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_EXEC))
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


        if (!(obj_getSize(this) >= sizeof(EXEC_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    

    
#ifdef  __cplusplus
}
#endif


