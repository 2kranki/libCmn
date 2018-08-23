// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   cloprs.c
 *	Generated 08/22/2018 12:43:41
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
#include        <cloprs_internal.h>
#include        <scanner.h>
#include        <trace.h>
#include        <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    int             cloprs_is_dashdash(
        const
        char            *pArg
    )
    {
        return pArg != NULL && pArg[0] == '-' && pArg[1] == '-' && pArg[2] == '\0';
    }
    
    
    
    static
    int             cloprs_is_shortopt(
        const
        char            *pArg
    )
    {
        return pArg != NULL && pArg[0] == '-' && pArg[1] != '-' && pArg[1] != '\0';
    }
    
    
    
    static
    int             cloprs_is_longopt(
        const
        char            *pArg
    )
    {
        return pArg != NULL && pArg[0] == '-' && pArg[1] == '-' && pArg[2] != '\0';
    }
    
    
    
    //---------------------------------------------------------------
    //                  E r r o r  H a n d l e r s
    //---------------------------------------------------------------
    
    ASTR_DATA *     cloprs_ErrorMissing(
        CLOPRS_DATA     *this,
        const
        char            *pOption
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_NewA("FATAL - Missing option - ");
        if (pStr) {
            AStr_AppendA(pStr, pOption);
            AStr_AppendA(pStr, "\n");
        }

        // Return to caller.
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //               F i n d  A r g u m e n t
    //---------------------------------------------------------------
    
    CLO_OPTION *    cloprs_ArgFindLong(
        CLOPRS_DATA     *this,
        const
        char            *pLong
    )
    {
        int             iRc = 0;
        CLO_OPTION      *pClo = NULL;
        int             i = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        // Search Group Args.
        if (this->cGroupArgs && this->pGroupArgs) {
            for (i=0; i<this->cGroupArgs; ++i) {
                if (this->pGroupArgs[i].pArgLong) {
                    iRc = str_Compare(pLong, this->pGroupArgs[i].pArgLong);
                    if (0 == iRc) {
                        pClo = &this->pGroupArgs[i];
                        return pClo;
                    }
                }
            }
        }
        
        // Search Program Args.
        if (this->cProgramArgs && this->pProgramArgs) {
            for (i=0; i<this->cProgramArgs; ++i) {
                if (this->pProgramArgs[i].pArgLong) {
                    iRc = str_Compare(pLong, this->pProgramArgs[i].pArgLong);
                    if (0 == iRc) {
                        pClo = &this->pProgramArgs[i];
                        return pClo;
                    }
                }
            }
        }
        
        return pClo;
    }
    
    
    
    CLO_OPTION *    cloprs_ArgFindShort(
        CLOPRS_DATA     *this,
        char            chr
    )
    {
        int             iRc = 0;
        CLO_OPTION      *pClo = NULL;
        int             i = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        // Search Group Args.
        if (this->cGroupArgs && this->pGroupArgs) {
            for (i=0; i<this->cGroupArgs; ++i) {
                if (this->pGroupArgs[i].argChr) {
                    iRc = chr - this->pGroupArgs[i].argChr;
                    if (0 == iRc) {
                        pClo = &this->pGroupArgs[i];
                        return pClo;
                    }
                }
            }
        }
        
        // Search Program Args.
        if (this->cProgramArgs && this->pProgramArgs) {
            for (i=0; i<this->cProgramArgs; ++i) {
                if (this->pProgramArgs[i].argChr) {
                    iRc = chr - this->pProgramArgs[i].argChr;
                    if (0 == iRc) {
                        pClo = &this->pProgramArgs[i];
                        return pClo;
                    }
                }
            }
        }
        
        return pClo;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    CLOPRS_DATA *     cloprs_Alloc(
        void
    )
    {
        CLOPRS_DATA     *this;
        uint32_t        cbSize = sizeof(CLOPRS_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //                      A r g v  T o  A S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     cloprs_ArgvToAStr(
        int             cArgs,
        const
        char            **ppArgs
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        uint32_t        i;
        
        if (cArgs) {
            pStr = AStr_NewA(*ppArgs);
            if (pStr) {
                for(i=1; i<cArgs; ++i) {
                    eRc = AStr_AppendA(pStr, " ");
                    if (ERESULT_FAILED(eRc)) {
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                        break;
                    }
                    eRc = AStr_AppendA(pStr, ppArgs[i]);
                    if (ERESULT_FAILED(eRc)) {
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                        break;
                    }
                }
            }
        }
        return pStr;
    }
    
    
    
    CLOPRS_DATA *   cloprs_New(
        void
    )
    {
        CLOPRS_DATA     *this;
        
        this = cloprs_Alloc( );
        if (this) {
            this = cloprs_Init(this);
        } 
        return this;
    }



    CLOPRS_DATA *  cloprs_NewFromArgV(
        int             cArgs,
        const
        char            *ppArgs[],
        const
        char            **ppEnv
    )
    {
        CLOPRS_DATA     *this;
        ERESULT         eRc;
        
        this = cloprs_Alloc( );
        if (this) {
            this = cloprs_Init(this);
            if (this) {
                eRc = cloprs_SetupFromArgV(this, cArgs, ppArgs, ppEnv);
            }
        }
        return this;
    }
    
    
    
    /*! Set up an ArgC/ArgV type array given a command line string
     excluding the program name.
     @param     pCmdStrA    Pointer to a UTF-8 Argument character string
     @return    If successful, an AStrArray object which must be
     released containing the Argument Array, otherwise
     OBJ_NIL if an error occurred.
     @warning   Remember to release the returned AStrArray object.
     */
    //FIXME:   We need to make this aware of the Array and Hash allowed in
    //FIXME:   in parameters since they may have whitespace between elements.
    ASTRARRAY_DATA * cloprs_StringToArray(
        const
        char            *pCmdStrA
    )
    {
        ERESULT         eRc;
        bool            fRc;
        char            *pCurCmd;
        uint32_t        cmdLen = 0;
        char            *pCurChr;
        ASTRARRAY_DATA  *pArgs = OBJ_NIL;
        ASTR_DATA       *pArg = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(pCmdStrA && (utf8_StrLenA(pCmdStrA) > 0))
            ;
        else {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        pArgs = AStrArray_New( );
        if (OBJ_NIL == pArgs) {
            DEBUG_BREAK();
            //return ERESULT_OUT_OF_MEMORY;
            return OBJ_NIL;
        }
        pCurChr = (char *)pCmdStrA;
        
        // Set up program name argument.
        pArg = AStr_NewA("");
        if (pArg) {
            eRc = AStrArray_AppendStr(pArgs, pArg, NULL);
            obj_Release(pArg);
            pArg = OBJ_NIL;
        }
        
        // Scan off the each parameter.
        while( pCurChr && *pCurChr ) {
            pCurCmd = NULL;
            cmdLen = 0;
            
            // Pass over white space.
            fRc = scanner_ScanWhite(&pCurChr, NULL);
            
            // Handle Quoted Arguments.
            pArg = scanner_ScanStringToAStr(&pCurChr, NULL);
            if (pArg) {
                eRc = AStrArray_AppendStr(pArgs, pArg, NULL);
                obj_Release(pArg);
                pArg = OBJ_NIL;
            }
            
        }
        
        // Return to caller.
        return pArgs;
    }
    
    
    


    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      A r g s
    //---------------------------------------------------------------
    
    ASTRARRAY_DATA * cloprs_getArgs(
        CLOPRS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArgs;
    }
    
    
    bool            cloprs_setArgs(
        CLOPRS_DATA     *this,
        ASTRARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pArgs) {
            obj_Release(this->pArgs);
        }
        this->pArgs = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          A r g  D e f s
    //---------------------------------------------------------------
    
    bool            cloprs_setArgDefs(
        CLOPRS_DATA     *this,
        uint16_t        cProgramArgs,
        CLO_OPTION      *pProgramArgs,
        uint16_t        cGroupArgs,
        CLO_OPTION      *pGroupArgs
    )
    {
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->cProgramArgs = cProgramArgs;
        this->pProgramArgs = pProgramArgs;
        this->cGroupArgs = cGroupArgs;
        this->pGroupArgs = pGroupArgs;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          E n v
    //---------------------------------------------------------------
    
    ASTRARRAY_DATA * cloprs_getEnv(
        CLOPRS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pEnv;
    }
    
    
    bool            cloprs_setEnv(
        CLOPRS_DATA     *this,
        ASTRARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pEnv) {
            obj_Release(this->pEnv);
        }
        this->pEnv = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        cloprs_getPriority(
        CLOPRS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        obj_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            cloprs_setPriority(
        CLOPRS_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                P r o g r a m  P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *     cloprs_getProgramPath(
        CLOPRS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pProgramPath;
    }
    
    
    bool            cloprs_setProgramPath(
        CLOPRS_DATA     *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pProgramPath) {
            obj_Release(this->pProgramPath);
        }
        this->pProgramPath = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        cloprs_getSize(
        CLOPRS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        obj_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * cloprs_getStr(
        CLOPRS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        cloprs_setStr(
        CLOPRS_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  cloprs_getSuperVtbl(
        CLOPRS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        obj_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = cloprs__Assign(this,pOther);
     @endcode 
     @param     this    CLOPRS object pointer
     @param     pOther  a pointer to another CLOPRS object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         cloprs_Assign(
        CLOPRS_DATA		*this,
        CLOPRS_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !cloprs_Validate(pOther) ) {
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
        obj_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        obj_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return obj_getLastError(this);
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
    ERESULT         cloprs_Compare(
        CLOPRS_DATA     *this,
        CLOPRS_DATA     *pOther
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
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !cloprs_Validate(pOther) ) {
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
        
        obj_setLastError(this, eRc);
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        cloprs      *pCopy = cloprs_Copy(this);
     @endcode 
     @param     this    CLOPRS object pointer
     @return    If successful, a CLOPRS object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the CLOPRS object.
     */
    CLOPRS_DATA *     cloprs_Copy(
        CLOPRS_DATA       *this
    )
    {
        CLOPRS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = cloprs_New( );
        if (pOther) {
            eRc = cloprs_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        obj_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            cloprs_Dealloc(
        OBJ_ID          objId
    )
    {
        CLOPRS_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        cloprs_setArgs(this, OBJ_NIL);
        cloprs_setEnv(this, OBJ_NIL);
        cloprs_setProgramPath(this, OBJ_NIL);
        cloprs_setStr(this, OBJ_NIL);

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

    ERESULT         cloprs_Disable(
        CLOPRS_DATA     *this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         cloprs_Enable(
        CLOPRS_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    CLOPRS_DATA *   cloprs_Init(
        CLOPRS_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(CLOPRS_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_CLOPRS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_CLOPRS);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&cloprs_Vtbl);
        
        obj_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "cloprs::sizeof(CLOPRS_DATA) = %lu\n", sizeof(CLOPRS_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(CLOPRS_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         cloprs_IsEnabled(
        CLOPRS_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            obj_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                  N e x t  A r g u m e n t
    //---------------------------------------------------------------
    
    ASTR_DATA *     cloprs_NextArg(
        CLOPRS_DATA     *this
    )
    {
        ASTR_DATA       *pData = OBJ_NIL;
        ERESULT         eRc = ERESULT_DATA_MISSING;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->nextArg <= AStrArray_getSize(this->pArgs)) {
            pData = AStrArray_Get(this->pArgs, this->nextArg);
            if (pData) {
                ++this->nextArg;
                eRc = ERESULT_SUCCESS;
            }
        }
        
        // Return to caller.
        obj_setLastError(this, eRc);
        return pData;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  A r g u m e n t s
    //---------------------------------------------------------------
    
    ERESULT         cloprs_ParseArgs(
        CLOPRS_DATA     *this
    )
    {
        ERESULT         eRc;
        int             wrkArgC = 0;
        int             i;
#ifdef XYZZY
        int             offset;
        int             len;
        char            wrkstr[64];
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == this->pArgs) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_DATA_MISSING);
            return ERESULT_DATA_MISSING;
        }
#endif
        TRC_OBJ(this,"%s:\n", __func__);
        wrkArgC = AStrArray_getSize(this->pArgs);
#ifdef NDEBUG
#else
        if (wrkArgC < 1) {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_DATA_MISSING);
            return ERESULT_DATA_MISSING;
        }
#endif
        
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            fprintf(stdout, "\tcArgs = %d\n", wrkArgC);
            for (i=0; i<wrkArgC; ++i) {
                ASTR_DATA           *pStr = OBJ_NIL;
                pStr = AStrArray_Get(this->pArgs, (i+1));
                if (pStr) {
                    fprintf(stderr, "\targ[%d]=\"%s\"\n", i, AStr_getData(pStr));
                }
            }
            fprintf(stdout, "\n");
        }
#endif
        
        // Process the arguments skipping the program path.
        while (this->nextArg <= wrkArgC) {
            ASTR_DATA           *pStr = OBJ_NIL;
            ASTR_DATA           *pWrk = OBJ_NIL;
            uint32_t            len = 0;
            pStr = AStrArray_Get(this->pArgs, this->nextArg);
            if (pStr) {
                len = AStr_getLength(pStr);
                if (ERESULT_SUCCESS_EQUAL == AStr_CompareLeftA(pStr, "--not-")) {
                    if (6 == len) {
                        //FIXME: appl_Usage(this, "ERROR - Missing flag");
                        exit(8);
                    }
                    eRc = AStr_Right(pStr, (len - 6), &pWrk);
                    if (!ERESULT_FAILED(eRc)) {
                        eRc = cloprs_ParseArgsLong(this, false, pWrk);
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                    }
                }
                else if (ERESULT_SUCCESS_EQUAL == AStr_CompareLeftA(pStr, "--")) {
                    if (2 == len) {
                        // End of Option Scanning
                        break;
                    }
                    eRc = AStr_Right(pStr, (len - 2), &pWrk);
                    if (!ERESULT_FAILED(eRc)) {
                        eRc = cloprs_ParseArgsLong(this, true, pWrk);
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                    }
                }
                else if (ERESULT_SUCCESS_EQUAL == AStr_CompareLeftA(pStr, "-")) {
                    if (1 == len) {
                        //FIXME: appl_Usage(this, "ERROR - Missing flag");
                        exit(8);
                    }
                }
                else {
                    break;
                }
                ++this->nextArg;
            }
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         cloprs_ParseArgsLong(
        CLOPRS_DATA     *this,
        bool            fTrue,
        ASTR_DATA       *pArg
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pName = OBJ_NIL;
        ASTR_DATA       *pData = OBJ_NIL;
        uint32_t        idxEql = 0;
        uint32_t        len = 0;
        CLO_OPTION      *pClo = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        len = AStr_getLength(pArg);
        eRc = AStr_CharFindNextW32(pArg, &idxEql, '=');
        if (ERESULT_FAILED(eRc)) {
            pName = AStr_Copy(pArg);
        }
        else {
            if (1 == idxEql) {
                //FIXME: appl_Usage(this, "ERROR - Missing flag - %s", AStr_getData(pArg));
                exit(8);
            }
            eRc = AStr_Left(pArg, (idxEql - 1), &pName);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            if (idxEql < len) {
                eRc = AStr_Right(pArg, (len - idxEql), &pData);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(pName);
                    return eRc;
                }
            }
            else {
                //FIXME: appl_Usage(this, "ERROR - Missing data - %s", AStr_getData(pArg));
                exit(8);
            }
        }
        
        pClo = cloprs_ArgFindLong(this, AStr_getData(pName));
        if (NULL == pClo) {
            //FIXME: appl_Usage(this, "ERROR - Unknown flag - %s", AStr_getData(pName));
            exit(8);
        }
        
        if (pClo) {
            void            *pPtr = (uint8_t *)this + pClo->offset;
            if (0 == pClo->offset) {
                pPtr = NULL;
            }
            switch (pClo->type) {
                case CLO_ARG_BOOL:             // uint8_t - 0 or 1
                    if (pPtr) {
                        if (fTrue) {
                            *((uint8_t *)pPtr) = 1;
                        }
                        else {
                            *((uint8_t *)pPtr) = 0;
                        }
                    }
                    break;
                case CLO_ARG_EXEC:             // Execute given routine
                    break;
                case CLO_ARG_EXEC_PARM:        // Execute given routine
                    if (OBJ_NIL == pData) {
                        if (this->nextArg < AStrArray_getSize(this->pArgs)) {
                            pData = AStrArray_Get(this->pArgs, this->nextArg);
                            if (pData) {
                                pData = AStr_Copy(pData);
                                ++this->nextArg;
                            }
                        }
                    }
                    break;
                case CLO_ARG_INCR:             // uint16_t - Every occurence increases the
                    //                          // associated value (default is 0);
                    if (pPtr) {
                        if (fTrue) {
                            *((uint16_t *)pPtr) += 1;
                        }
                        else {
                            *((uint16_t *)pPtr) -= 1;
                        }
                    }
                    break;
                case CLO_ARG_NUMBER:           // Number pointer
                    break;
                case CLO_ARG_PATH:             // Path pointer
                    if (OBJ_NIL == pData) {
                        if (this->nextArg < AStrArray_getSize(this->pArgs)) {
                            pData = AStrArray_Get(this->pArgs, this->nextArg);
                            if (pData) {
                                pData = AStr_Copy(pData);
                                ++this->nextArg;
                            }
                        }
                    }
                    if (pData && pPtr) {
                        *((PATH_DATA **)pPtr) = path_NewFromAStr(pData);
                    }
                    else {
                        //FIXME: appl_Usage(this, "ERROR - Missing Path for --%s", pClo->pArgLong);
                        exit(8);
                    }
                    break;
                case CLO_ARG_STRING:           // AStr pointer
                    if (OBJ_NIL == pData) {
                        if (this->nextArg < AStrArray_getSize(this->pArgs)) {
                            pData = AStrArray_Get(this->pArgs, this->nextArg);
                            if (pData) {
                                pData = AStr_Copy(pData);
                                ++this->nextArg;
                            }
                        }
                    }
                    if (pData && pPtr) {
                        *((ASTR_DATA **)pPtr) = pData;
                        pData = OBJ_NIL;
                    }
                    else {
                        //FIXME: appl_Usage(this, "ERROR - Missing Path for --%s", pClo->pArgLong);
                        exit(8);
                    }
                    break;
                default:
                    break;
            }
            if (pClo->pExec) {
                eRc = pClo->pExec(this, pData);
                if (ERESULT_FAILED(eRc)) {
                    //FIXME: appl_Usage(this, "ERROR - Execute Routine for --%s failed!", pClo->pArgLong);
                    exit(8);
                }
            }
        }
        
        // Return to caller.
        obj_Release(pName);
        obj_Release(pData);
        return eRc;
    }
    
    
    ERESULT         cloprs_ParseArgsShort(
        CLOPRS_DATA     *this,
        int             *pArgC,
        const
        char            ***pppArgV
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        const
        char            *pWrk = **pppArgV + 1;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        while (*pWrk) {
            switch(tolower(*pWrk)) {
                case '?':
                case 'h':
                    //FIXME: appl_Usage(this, NULL);
                    exit(4);
                    break;
                case 'd':
                    //FIXME: ++this->fDebug;
                    break;
                default:
                    //FIXME: if (this->pParseArgsShort) {
                        //FIXME: eRc = this->pParseArgsShort(this->pObjPrs, pArgC, pppArgV);
                    //FIXME: }
                    break;
            }
            ++pWrk;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                 S e t u p  F r o m  A r g V
    //---------------------------------------------------------------
    
    /*!
     Set up to parse the given input resetting any prior parse data.
     @param     this    object pointer
     @param     cArgs   number of charater strings in ppArgs
     @param     ppArgV  point to a charater string array
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
     an ERESULT_* error code
     */
    ERESULT         cloprs_SetupFromArgV(
        CLOPRS_DATA     *this,
        uint16_t        cArgs,
        const
        char            *ppArgV[],
        const
        char            **ppEnv
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTRARRAY_DATA  *pArgs;
        PATH_DATA       *pPath;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Set program defaults here.
        //FIXME: if (this->pParseArgsDefaults) {
            //FIXME: eRc = this->pParseArgsDefaults(this->pObjPrs);
        //FIXME: }
        
        // Reset any prior parse data.
        cloprs_setArgs(this, OBJ_NIL);
        cloprs_setProgramPath(this, OBJ_NIL);
        cloprs_setEnv(this, OBJ_NIL);
        
        pArgs = AStrArray_NewFromArgV(cArgs, ppArgV);
        if (pArgs) {
            cloprs_setArgs(this, pArgs);        // Reset any prior data.
            obj_Release(pArgs);
            pArgs = OBJ_NIL;
        }
        else {
            eRc = ERESULT_OUT_OF_MEMORY;
        }
        if ((cArgs > 0) && ppArgV && ppArgV[0]) {
            pPath = path_NewA(ppArgV[0]);
            cloprs_setProgramPath(this, pPath);
            obj_Release(pPath);
        }
        if (ppEnv) {
            pArgs = AStrArray_NewFromArrayA(ppEnv);
            if (pArgs) {
                cloprs_setEnv(this, pArgs);
                obj_Release(pArgs);
            }
        }
        this->nextArg = 2;
        
        return eRc;
    }
    
    
    bool            cloprs_SetupFromStr(
        CLOPRS_DATA     *this,
        char            *pCmdStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
#ifdef XYZZY
        uint16_t        cbSize;
        int             Num = 0;
#endif
        char            *pCurChr;
#ifdef XYZZY
        char            *pCurCmd;
        char            quote;
        int             cArg = 1;
        char            **pArgV = NULL;
#endif
        ASTRARRAY_DATA  *pArgs;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(NULL == pCmdStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // Set up to scan the parameters.
        pArgs = AStrArray_New( );
        if(NULL == pArgs) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        pCurChr = pCmdStr;
        
        // Set program defaults here;
        //FIXME: if (this->pParseArgsDefaults) {
            //FIXME: eRc = this->pParseArgsDefaults(this->pObjPrs);
        //FIXME: }
        
        // Reset any prior parse data.
        cloprs_setArgs(this, OBJ_NIL);
        cloprs_setProgramPath(this, OBJ_NIL);
        cloprs_setEnv(this, OBJ_NIL);
        
        
        // Analyze input string to calculate array needed.
#ifdef XYZZY
        this->cArg = 1;
        //TODO: cbSize = 2 * sizeof(char *);
        this->ppArg = (char **)mem_Malloc( cbSize );
#ifdef XYZZY
        if( this->ppArg ) {
            this->flags |= GOT_ARGV;
        }
        else
            return false;
#endif
        *(this->ppArg) = "";     // Set program name.
        
        // Scan off the each parameter.
        while( *pCmdStr ) {
            pCurCmd = NULL;
            
            // Pass over white space.
            while( *pCmdStr && ((*pCmdStr == ' ') || (*pCmdStr == '\n')
                                || (*pCmdStr == '\r') || (*pCmdStr == '\t')) )
                ++pCmdStr;
            
            // Handle Quoted Arguments.
            if( (*pCmdStr == '\"') || (*pCmdStr == '\'') ) {
                quote = *pCmdStr++;
                pCurCmd = pCmdStr;
                while( *pCmdStr && (*pCmdStr != quote) ) {
                    ++pCmdStr;
                }
                if( *pCmdStr ) {
                    *pCmdStr = '\0';
                    ++pCmdStr;
                }
            }
            
            // Handle Non-Quoted Arguments.
            else if( *pCmdStr ) {
                pCurCmd = pCmdStr;
                // Scan until white space.
                while( *pCmdStr && !((*pCmdStr == ' ') || (*pCmdStr == '\n')
                                     || (*pCmdStr == '\r') || (*pCmdStr == '\t')) ) {
                    ++pCmdStr;
                }
                if( *pCmdStr ) {
                    *pCmdStr = '\0';
                    ++pCmdStr;
                }
            }
            else
                continue;
            
            // Add the command to the array.
            if( pCurCmd ) {
                ++Num;
                this->ppArg = (char **)mem_Realloc( this->ppArg, ((Num + 2) * sizeof(char *)) );
                if( this->ppArg ) {
                    this->ppArg[Num]   = pCurCmd;
                    this->ppArg[Num+1] = NULL;
                    ++this->cArg;
                }
                else
                    return( false );
            }
        }
#endif
        
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
        void        *pMethod = cloprs_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "cloprs", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          cloprs_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        CLOPRS_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)cloprs_Class();
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
                            return cloprs_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return cloprs_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return cloprs_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return cloprs_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == cloprs_ToDebugString)
                    return "ToDebugString";
                if (pData == cloprs_ToJSON)
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
    
     ASTR_DATA *     cloprs_ToJSON(
        CLOPRS_DATA      *this
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !cloprs_Validate(this) ) {
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = cloprs_ToDebugString(this,4);
     @endcode 
     @param     this    CLOPRS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     cloprs_ToDebugString(
        CLOPRS_DATA      *this,
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
        if( !cloprs_Validate(this) ) {
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
                    cloprs_getSize(this)
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            cloprs_Validate(
        CLOPRS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_CLOPRS) )
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


        if( !(obj_getSize(this) >= sizeof(CLOPRS_DATA)) ) {
            obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return false;
        }

        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


