// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Test.c
 *  Generated 08/29/2021 09:18:10
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
#include        <Test_internal.h>
#include        <JsonIn.h>
#include        <psxThread.h>
#include        <SrcErrors.h>
#include        <szTbl.h>
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
    void            Test_task_body (
        void            *pData
    )
    {
        //TEST_DATA  *this = pData;
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TEST_DATA *     Test_Alloc (
        void
    )
    {
        TEST_DATA       *this;
        uint32_t        cbSize = sizeof(TEST_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TEST_DATA *     Test_New (
        void
    )
    {
        TEST_DATA       *this;
        
        this = Test_Alloc( );
        if (this) {
            this = Test_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  A l l o w  I n t 3
    //---------------------------------------------------------------

    bool            Test_getAllowInt3 (
        TEST_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->fAllowInt3;
    }


    bool            Test_setAllowInt3 (
        TEST_DATA       *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fAllowInt3 = fValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Test_getPriority (
        TEST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Test_setPriority (
        TEST_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
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
    
    uint32_t        Test_getSize (
        TEST_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Test_getStr (
        TEST_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Test_setStr (
        TEST_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  Test_getSuperVtbl (
        TEST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
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
        ERESULT eRc = Test_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another TEST object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Test_Assign (
        TEST_DATA       *this,
        TEST_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Test_Validate(pOther)) {
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
    int             Test_Compare (
        TEST_DATA     *this,
        TEST_DATA     *pOther
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
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Test_Validate(pOther)) {
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
        Test      *pCopy = Test_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TEST object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TEST_DATA *     Test_Copy (
        TEST_DATA       *this
    )
    {
        TEST_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef TEST_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Test_New( );
        if (pOther) {
            eRc = Test_Assign(this, pOther);
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

    void            Test_Dealloc (
        OBJ_ID          objId
    )
    {
        TEST_DATA       *this = objId;
        //ERESULT         eRc;
        int             iExitCode;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif
        iExitCode = this->iExitCode;

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((TEST_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Test_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
        if (iExitCode)
            exit(iExitCode);
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Test      *pDeepCopy = Test_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TEST object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TEST_DATA *     Test_DeepCopy (
        TEST_DATA       *this
    )
    {
        TEST_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Test_New( );
        if (pOther) {
            eRc = Test_Assign(this, pOther);
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
    ERESULT         Test_Disable (
        TEST_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
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
    ERESULT         Test_Enable (
        TEST_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
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
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Test_Exec (
        TEST_DATA       *this,
        const
        char            *pNameA,
        ERESULT         (*pExec)(TEST_DATA *, const char *),
        ERESULT         (*pSetup)(TEST_DATA *),
        ERESULT         (*pTearDown)(TEST_DATA *)
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pExec) {
            this->iExitCode = 12;
            exit(this->iExitCode);
        }
#endif

        if (pSetup) {
            eRc = pSetup(this);
        } else {
            eRc = Test_Setup(this);
        }
        if (ERESULT_FAILED(eRc)) {
            fprintf(
                    stderr,
                    "\x1b[1m\x1b[31mFATAL\x1b[0m: Setup failed for %s!\n\n\n",
                    pNameA ? pNameA : "Unknown"
            );
            exit(4);
        }

        eRc = pExec(this, pNameA);
        if (ERESULT_FAILED(eRc)) {
            fprintf(
                    stderr,
                    "\x1b[1m\x1b[31mFATAL\x1b[0m: Exec failed for %s!\n\n\n",
                    pNameA ? pNameA : "Unknown"
            );
            exit(4);
        }

        if (pTearDown) {
            eRc = pTearDown(this);
        } else {
            eRc = Test_TearDown(this);
        }
        if (ERESULT_FAILED(eRc)) {
            fprintf(
                    stderr,
                    "\x1b[1m\x1b[31mFATAL\x1b[0m: TearDown failed for %s!\n\n\n",
                    pNameA ? pNameA : "Unknown"
            );
            exit(4);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       F o r  C o n d i t i o n
    //---------------------------------------------------------------

    ERESULT         Test_ForFail (
        TEST_DATA       *this,
        ERESULT         eRc2,
        const
        char            *pErrorA,
        const
        char            *pFilePathA,
        size_t          iLine
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc = 1;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (ERESULT_OK(eRc2)) {
            fprintf(
                    stderr,
                    "\x1b[1m\x1b[31mERROR\x1b[0m: Failure failed: %s file: %s line: %ld\n\n",
                    pErrorA ? pErrorA : "",
                    pFilePathA,
                    iLine
            );
            this->iExitCode = 8;
            if (this->pFatalExit) {
                iRc = this->pFatalExit(this->pFatalObject, this);
            }
            if (iRc) {
                if (cmn_AmIBeingDebugged() && Test_getAllowInt3(this)) {
                    __asm__("int $3\n" : : );
                }
                exit(this->iExitCode);
            }
        }

        // Return to caller.
        return eRc;
    }


    ERESULT         Test_ForFalse (
        TEST_DATA       *this,
        bool            fValue,
        const
        char            *pErrorA,
        const
        char            *pFilePathA,
        size_t          iLine
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc = 1;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (fValue) {
            fprintf(
                    stderr,
                    "\x1b[1m\x1b[31mERROR\x1b[0m: False failed: %s file: %s line: %ld\n\n",
                    pErrorA ? pErrorA : "",
                    pFilePathA,
                    iLine
            );
            this->iExitCode = 8;
            if (this->pFatalExit) {
                iRc = this->pFatalExit(this->pFatalObject, this);
            }
            if (iRc) {
                if (cmn_AmIBeingDebugged() && Test_getAllowInt3(this)) {
                    __asm__("int $3\n" : : );
                }
                exit(this->iExitCode);
            }
        }

        // Return to caller.
        return eRc;
    }


    ERESULT         Test_ForNotNull (
        TEST_DATA       *this,
        void            *pValue,
        const
        char            *pErrorA,
        const
        char            *pFilePathA,
        size_t          iLine
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc = 1;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (NULL == pValue) {
            fprintf(
                    stderr,
                    "\x1b[1m\x1b[31mERROR\x1b[0m: NULL failed: %s file: %s line: %ld\n\n",
                    pErrorA ? pErrorA : "",
                    pFilePathA,
                    iLine
            );
            this->iExitCode = 8;
            if (this->pFatalExit) {
                iRc = this->pFatalExit(this->pFatalObject, this);
            }
            if (iRc) {
                if (cmn_AmIBeingDebugged() && Test_getAllowInt3(this)) {
                    __asm__("int $3\n" : : );
                }
                exit(this->iExitCode);
            }
        }

        // Return to caller.
        return eRc;
    }


    ERESULT         Test_ForNull (
        TEST_DATA       *this,
        void            *pValue,
        const
        char            *pErrorA,
        const
        char            *pFilePathA,
        size_t          iLine
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc = 1;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (pValue) {
            fprintf(
                    stderr,
                    "\x1b[1m\x1b[31mERROR\x1b[0m: NULL failed: %s file: %s line: %ld\n\n",
                    pErrorA ? pErrorA : "",
                    pFilePathA,
                    iLine
            );
            this->iExitCode = 8;
            if (this->pFatalExit) {
                iRc = this->pFatalExit(this->pFatalObject, this);
            }
            if (iRc) {
                if (cmn_AmIBeingDebugged() && Test_getAllowInt3(this)) {
                    __asm__("int $3\n" : : );
                }
                exit(this->iExitCode);
            }
        }

        // Return to caller.
        return eRc;
    }


    ERESULT         Test_ForSucess (
        TEST_DATA       *this,
        ERESULT         eRc2,
        const
        char            *pErrorA,
        const
        char            *pFilePathA,
        size_t          iLine
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc = 1;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (ERESULT_FAILED(eRc2)) {
            fprintf(
                    stderr,
                    "\x1b[1m\x1b[31mERROR\x1b[0m: Success failed: %s file: %s line: %ld\n\n",
                    pErrorA ? pErrorA : "",
                    pFilePathA,
                    iLine
            );
            this->iExitCode = 8;
            if (this->pFatalExit) {
                iRc = this->pFatalExit(this->pFatalObject, this);
            }
            if (iRc) {
                if (cmn_AmIBeingDebugged() && Test_getAllowInt3(this)) {
                    __asm__("int $3\n" : : );
                }
                exit(this->iExitCode);
            }
        }

        // Return to caller.
        return eRc;
    }


    ERESULT         Test_ForTrue (
        TEST_DATA       *this,
        bool            fValue,
        const
        char            *pErrorA,
        const
        char            *pFilePathA,
        size_t          iLine
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc = 1;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (!fValue) {
            fprintf(
                    stderr,
                    "\x1b[1m\x1b[31mERROR\x1b[0m: True failed: %s file: %s line: %ld\n\n",
                    pErrorA ? pErrorA : "",
                    pFilePathA,
                    iLine
            );
            this->iExitCode = 8;
            if (this->pFatalExit) {
                iRc = this->pFatalExit(this->pFatalObject, this);
            }
            if (iRc) {
                if (cmn_AmIBeingDebugged() && Test_getAllowInt3(this)) {
                    __asm__("int $3\n" : : );
                }
                exit(8);
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TEST_DATA *   Test_Init (
        TEST_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(TEST_DATA);
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
        // in the OBJ_INFO at the end of Test_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TEST);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Test_Vtbl);
#ifdef  TEST_JSON_SUPPORT
        JsonIn_RegisterClass(Test_Class());
#endif

        this->fAllowInt3 = true;

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
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Test::sizeof(TEST_DATA) = %lu\n", 
                sizeof(TEST_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(TEST_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Test_IsEnabled (
        TEST_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
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
        void        *pMethod = Test_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Test", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Test_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TEST_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(TEST_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Test_Class();
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
                            return Test_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Test_Enable;
                        }
                        break;

                    case 'P':
#ifdef  TEST_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Test_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Test_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Test_ToDebugString;
                        }
#ifdef  TEST_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Test_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Test_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Test_ToDebugString)
                    return "ToDebugString";
#ifdef  TEST_JSON_SUPPORT
                if (pData == Test_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                        S e t u p
    //---------------------------------------------------------------

    ERESULT         Test_Setup (
        TEST_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        mem_Init( );
        trace_Shared( );

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                   T e a r  D o w n
    //---------------------------------------------------------------

    ERESULT         Test_TearDown (
        TEST_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        szTbl_SharedReset( );
        SrcErrors_SharedReset( );
        JsonIn_RegisterReset();
        trace_SharedReset( );
        if (mem_Dump( ) ) {
            fprintf(
                    stderr,
                    "\x1b[1m"
                    "\x1b[31m"
                    "ERROR: "
                    "\x1b[0m"
                    "Leaked memory areas were found!\n\n\n\n\n"
            );
            this->iExitCode = 4;
            return 0;
        }
        mem_Release( );

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Test_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Test_ToDebugString (
        TEST_DATA      *this,
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
        if (!Test_Validate(this)) {
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
                    Test_getSize(this),
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
    bool            Test_Validate (
        TEST_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_TEST))
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


        if (!(obj_getSize(this) >= sizeof(TEST_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                          W a i t
    //---------------------------------------------------------------

    ERESULT         Test_Wait (
        TEST_DATA       *this,
        uint32_t        msWait
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Test_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (Test_getAllowInt3(this)) {
            psxThread_Wait(msWait);
        }

        // Return to caller.
        return eRc;
    }




    
#ifdef  __cplusplus
}
#endif


