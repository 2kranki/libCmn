// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   SrcErrors.c
 *	Generated 12/28/2019 09:57:24
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
#include        <SrcErrors_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            SrcErrors_task_body (
        void            *pData
    )
    {
        //SRCERRORS_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SRCERRORS_DATA *     SrcErrors_Alloc (
        void
    )
    {
        SRCERRORS_DATA       *this;
        uint32_t        cbSize = sizeof(SRCERRORS_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SRCERRORS_DATA *     SrcErrors_New (
        void
    )
    {
        SRCERRORS_DATA       *this;
        
        this = SrcErrors_Alloc( );
        if (this) {
            this = SrcErrors_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  E x i t  O n  F a t a l
    //---------------------------------------------------------------
    
    bool            SrcErrors_getExitOnFatal (
        SRCERRORS_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return this->fExitOnFatal;
    }
    
    
    bool            SrcErrors_setExitOnFatal (
        SRCERRORS_DATA  *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->fExitOnFatal = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F a t a l
    //---------------------------------------------------------------
    
    bool            SrcErrors_getFatal (
        SRCERRORS_DATA  *this
    )
    {
        
        // Validate the input parameters.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
            return this->fFatal;
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return this->fFatal;
    }
    
    
    bool            SrcErrors_setFatal (
        SRCERRORS_DATA  *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->fFatal = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      F a t a l  E x i t
    //---------------------------------------------------------------
    
    bool            SrcErrors_setFatalExit (
        SRCERRORS_DATA  *this,
        OBJMETHOD_DATA  *pFatalExit
    )
    {
        
        if (OBJ_NIL == this){
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pFatalExit);
        if (this->pFatalExit) {
            obj_Release(this->pFatalExit);
        }
        this->pFatalExit = pFatalExit;

        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                N u m b e r  o f  E r r o r s
    //---------------------------------------------------------------
    
    uint32_t        SrcErrors_getNumErrors (
        SRCERRORS_DATA     *this
    )
    {
        uint32_t            num = 0;
        
        // Validate the input parameters.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
            num = ObjArray_getSize((OBJARRAY_DATA *)this);
            return num;
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        num = ObjArray_getSize((OBJARRAY_DATA *)this);
        
        return num;
    }

        
        
    //---------------------------------------------------------------
    //                          P a t h s
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * SrcErrors_getPaths (
        SRCERRORS_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return this->pPaths;
    }


    bool            SrcErrors_setPaths (
        SRCERRORS_DATA  *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pPaths) {
            obj_Release(this->pPaths);
        }
        this->pPaths = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        SrcErrors_getSize (
        SRCERRORS_DATA       *this
    )
    {
        uint32_t            num = 0;

        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        num = ObjArray_getSize((OBJARRAY_DATA *)this);
        
        return num;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  SrcErrors_getSuperVtbl (
        SRCERRORS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
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
    //                              A d d
    //---------------------------------------------------------------
    
    bool        SrcErrors_AddErrorA (
        SRCERRORS_DATA  *this,
        uint16_t        severity,
        const
        SRCLOC          *pLocation,
        const
        char            *pErrorString,
        ...
    )
    {
        ERESULT         eRc;
        SRCERROR_DATA   *pError = OBJ_NIL;
        char            str[512];
        int             size;
        va_list         arg_ptr;
        char            *pStr = str;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        va_start(arg_ptr, pErrorString);
        str[0] = '\0';
        size = vsnprintf( str, sizeof(str), pErrorString, arg_ptr );
        va_end( arg_ptr );
        if (size >= sizeof(str)) {
            ++size;
            pStr = (char *)mem_Malloc(size);
            if( pStr == NULL ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
            va_start( arg_ptr, pErrorString );
            size = vsnprintf( pStr, size, pErrorString, arg_ptr );
            va_end( arg_ptr );
            pError = SrcError_NewFromData(severity, pLocation, pStr);
            mem_Free( pStr );
            pStr = NULL;
        }
        else {
            pError = SrcError_NewFromData(severity, pLocation, pStr);
        }
        if (OBJ_NIL == pError) {
            return false;
        }
        eRc = ObjArray_AppendObj((OBJARRAY_DATA *)this, pError, NULL);
        obj_Release(pError);
        pError = OBJ_NIL;
        if (ERESULT_FAILED(eRc)) {
            return false;
        }
        
        if (severity == SRCERROR_SEVERITY_FATAL) {
            SrcErrors_setFatal(this, true);
            if (this->fExitOnFatal) {
                SrcErrors_ExitOnFatal(this);
            }
        }
        
        // Return to caller.
        return true;
    }
    
    
    ERESULT         SrcErrors_AddFatal (
        SRCERRORS_DATA  *this,
        SRCERROR_DATA   *pError
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pError) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = ObjArray_AppendObj((OBJARRAY_DATA *)this, pError, NULL);
        if (ERESULT_FAILED(eRc)) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        SrcErrors_setFatal(this, true);
        if (this->fExitOnFatal) {
            SrcErrors_ExitOnFatal(this);
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         SrcErrors_AddFatalA (
        SRCERRORS_DATA  *this,
        const
        SRCLOC          *pLocation,
        const
        char            *pErrorString,
        ...
    )
    {
        ERESULT         eRc;
        SRCERROR_DATA   *pError = OBJ_NIL;
        char            str[512];
        int             size;
        va_list         arg_ptr;
        char            *pStr = str;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        va_start(arg_ptr, pErrorString);
        str[0] = '\0';
        size = vsnprintf(str, sizeof(str), pErrorString, arg_ptr);
        va_end( arg_ptr );
        if (size >= sizeof(str)) {
            ++size;
            pStr = (char *)mem_Malloc(size);
            if( pStr == NULL ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
            va_start( arg_ptr, pErrorString );
            size = vsnprintf( pStr, size, pErrorString, arg_ptr );
            va_end( arg_ptr );
            pError = SrcError_NewFromData(SRCERROR_SEVERITY_FATAL, pLocation, pStr);
            mem_Free( pStr );
            pStr = NULL;
        }
        else {
            pError = SrcError_NewFromData(SRCERROR_SEVERITY_FATAL, pLocation, pStr);
        }
        if (OBJ_NIL == pError) {
            return false;
        }
        
        eRc = SrcErrors_AddFatal(this, pError);
        obj_Release(pError);
        pError = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         SrcErrors_AddFatalArgsA (
        SRCERRORS_DATA  *this,
        const
        SRCLOC          *pLocation,
        const
        char            *pErrorString,
        va_list         arg_ptr
    )
    {
        ERESULT         eRc;
        SRCERROR_DATA   *pError = OBJ_NIL;
        char            str[512];
        int             size;
        char            *pStr = str;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        str[0] = '\0';
        size = vsnprintf(str, sizeof(str), pErrorString, arg_ptr);
        if (size >= sizeof(str)) {
            ++size;
            pStr = (char *)mem_Malloc(size);
            if( pStr == NULL ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
            size = vsnprintf( pStr, size, pErrorString, arg_ptr );
            pError = SrcError_NewFromData(SRCERROR_SEVERITY_FATAL, pLocation, pStr);
            mem_Free( pStr );
            pStr = NULL;
        }
        else {
            pError = SrcError_NewFromData(SRCERROR_SEVERITY_FATAL, pLocation, pStr);
        }
        if (OBJ_NIL == pError) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        eRc = SrcErrors_AddFatal(this, pError);
        obj_Release(pError);
        pError = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         SrcErrors_AddFatalExpectingA (
        SRCERRORS_DATA  *this,
        TOKEN_DATA      *pToken,
        const
        char            *pExpected
    )
    {
        ERESULT         eRc;
        SRCERROR_DATA   *pError = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        ASTR_DATA       *pTmp = OBJ_NIL;

        // Do initialization.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pWrk = AStr_New();
        if (OBJ_NIL == pWrk) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        pTmp = Token_getTextAStr(pToken);
        AStr_AppendPrint(
                pWrk,
                "Expecting: %s but found: %s\n",
                pExpected,
                AStr_getData(pTmp)
        );
        obj_Release(pTmp);
        
        pError = SrcError_NewFatalFromToken(pToken, pWrk);
        obj_Release(pWrk);
        if (OBJ_NIL == pError) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        eRc = SrcErrors_AddFatal(this, pError);
        obj_Release(pError);
        pError = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         SrcErrors_AddFatalFromTokenA (
        SRCERRORS_DATA  *this,
        TOKEN_DATA      *pToken,
        const
        char            *pErrorString,
        ...
    )
    {
        ERESULT         eRc;
        SRCERROR_DATA   *pError = OBJ_NIL;
        char            str[512];
        int             size;
        va_list         arg_ptr;
        char            *pStr = str;

        // Do initialization.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        va_start( arg_ptr, pErrorString );
        str[0] = '\0';
        size = vsnprintf( str, sizeof(str), pErrorString, arg_ptr );
        va_end( arg_ptr );
        if (size >= sizeof(str)) {
            ++size;
            pStr = (char *)mem_Malloc(size);
            if( pStr == NULL ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
            va_start( arg_ptr, pErrorString );
            size = vsnprintf( pStr, size, pErrorString, arg_ptr );
            va_end( arg_ptr );
            pError = SrcError_NewFatalFromTokenA(pToken, pStr);
            mem_Free( pStr );
            pStr = NULL;
        }
        else {
            pError = SrcError_NewFatalFromTokenA(pToken, pStr);
        }
        if (OBJ_NIL == pError) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        eRc = SrcErrors_AddFatal(this, pError);
        obj_Release(pError);
        pError = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
        
        
        
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = SrcErrors_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SRCERRORS object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SrcErrors_Assign (
        SRCERRORS_DATA		*this,
        SRCERRORS_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SrcErrors_Validate(pOther)) {
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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             SrcErrors_Compare (
        SRCERRORS_DATA *this,
        SRCERRORS_DATA *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!SrcErrors_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        SrcErrors      *pCopy = SrcErrors_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SRCERRORS object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCERRORS_DATA *     SrcErrors_Copy (
        SRCERRORS_DATA       *this
    )
    {
        SRCERRORS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = SrcErrors_New( );
        if (pOther) {
            eRc = SrcErrors_Assign(this, pOther);
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

    void            SrcErrors_Dealloc (
        OBJ_ID          objId
    )
    {
        SRCERRORS_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

        SrcErrors_setFatalExit(this, OBJ_NIL);
        SrcErrors_setPaths(this, OBJ_NIL);

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
    ERESULT         SrcErrors_Disable (
        SRCERRORS_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!SrcErrors_Validate(this)) {
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
    ERESULT         SrcErrors_Enable (
        SRCERRORS_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!SrcErrors_Validate(this)) {
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
    //                          E n u m
    //---------------------------------------------------------------

    OBJENUM_DATA *  SrcErrors_EnumErrors (
        SRCERRORS_DATA  *this
    )
    {
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
    #ifdef NDEBUG
    #else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
    #endif
        
        pEnum = ObjArray_Enum((OBJARRAY_DATA *)this);

        // Return to caller.
        return pEnum;
    }



    //---------------------------------------------------------------
    //               E x i t  O n  F a t a l
    //---------------------------------------------------------------
    
    void            SrcErrors_ExitOnFatal (
        SRCERRORS_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        if (this->fFatal) {
            SrcErrors_Print(this, stderr);
            if (this->pFatalExit) {
                eRc = ObjMethod_Execute(this->pFatalExit);
                if (ERESULT_FAILED(eRc))
                    return;
            }
            exit(100);
        }

        // Return to caller.
    }
        
        
        
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SRCERRORS_DATA *   SrcErrors_Init (
        SRCERRORS_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SRCERRORS_DATA);
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

        this = (OBJ_ID)ObjArray_Init((OBJARRAY_DATA *)this);    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SRCERRORS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SrcErrors_Vtbl);
        
        this->pPaths = ObjArray_New( );
        if (OBJ_NIL == this->pPaths) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "SrcErrors::sizeof(SRCERRORS_DATA) = %lu\n", sizeof(SRCERRORS_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SRCERRORS_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         SrcErrors_IsEnabled (
        SRCERRORS_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
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
    //                  L a t e s t  E r r o r
    //---------------------------------------------------------------
    
    SRCERROR_DATA * SrcErrors_LatestError (
        SRCERRORS_DATA  *this
    )
    {
        SRCERROR_DATA   *pError = OBJ_NIL;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pError = ObjArray_GetLast((OBJARRAY_DATA *)this);
        
        // Return to caller.
        return pError;
    }
        
        
        
    //---------------------------------------------------------------
    //                      P r i n t
    //---------------------------------------------------------------
    
    void            SrcErrors_Print (
        SRCERRORS_DATA  *this,
        FILE            *pFile
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        OBJENUM_DATA    *pEnum = OBJ_NIL;
        SRCERROR_DATA   *pError = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        pEnum = SrcErrors_EnumErrors(this);
        if (pEnum) {
            while (ObjEnum_Remaining(pEnum)) {
                eRc = ObjEnum_Next(pEnum, 1, (void **)&pError, NULL);
                if (ERESULT_SUCCESSFUL(eRc)) {
                    pStr = SrcError_ToString(pError);
                    if (pStr) {
                        fprintf(pFile, "%s", AStr_getData(pStr));
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                }
                pError = OBJ_NIL;
            }
            obj_Release(pEnum);
            pEnum = OBJ_NIL;
        }
        
        // Return to caller.
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
        void        *pMethod = SrcErrors_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SrcErrors", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SrcErrors_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SRCERRORS_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCERRORS_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SrcErrors_Class();
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
                            return SrcErrors_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return SrcErrors_Enable;
                        }
                        if (str_Compare("ExitOnFatal", (char *)pStr) == 0) {
                            return SrcErrors_ExitOnFatal;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return SrcErrors_ToDebugString;
                        }
#ifdef  SRCERRORS_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return SrcErrors_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SrcErrors_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCERRORS_JSON_SUPPORT
                if (pData == SrcErrors_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      R e s e t
    //---------------------------------------------------------------
    
    void            SrcErrors_Reset (
        SRCERRORS_DATA  *this
    )
    {
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = SrcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        ObjArray_DeleteAll((OBJARRAY_DATA *)this);
        this->fFatal = false;
        
        // Return to caller.
    }
        
        
        
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SrcErrors_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcErrors_ToDebugString (
        SRCERRORS_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcErrors_Validate(this)) {
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
                    "{%p(%s) size=%d retain=%d %s\n",
                    this,
                    pInfo->pClassName,
                    SrcErrors_getSize(this),
                    obj_getRetainCount(this),
                    (SrcErrors_getFatal(this) ? "fatal_error(s)" : "")
            );

        pWrkStr = ObjArray_ToDebugString((OBJARRAY_DATA *)this, (indent + 3));
        if (pWrkStr) {
            AStr_Append(pStr, pWrkStr);
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
        }
        
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
    bool            SrcErrors_Validate (
        SRCERRORS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SRCERRORS))
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


        if (!(obj_getSize(this) >= sizeof(SRCERRORS_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


