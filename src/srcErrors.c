// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   srcErrors.c
 *	Generated 12/17/2017 07:12:35
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
#include <srcErrors_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    static
    SRCERRORS_DATA  singleton = {{0}};
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ERESULT         srcErrors_DefaultFatalExit(
        OBJ_ID          pObj,
        SRCERRORS_DATA  *pData
    )
    {
        return ERESULT_SUCCESS;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SRCERRORS_DATA * srcErrors_Alloc(
    )
    {
        SRCERRORS_DATA  *this;
        uint32_t        cbSize = sizeof(SRCERRORS_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SRCERRORS_DATA *     srcErrors_New(
    )
    {
        SRCERRORS_DATA       *this;
        
        this = srcErrors_Alloc( );
        if (this) {
            this = srcErrors_Init(this);
        } 
        return this;
    }



    SRCERRORS_DATA * srcErrors_Shared(
    )
    {
        SRCERRORS_DATA  *this = &singleton;
        uint32_t        cbSize = sizeof(SRCERRORS_DATA);
        
        if (obj_getRetainCount(this) == 0) {
            obj_setSize(this, cbSize);
            this = srcErrors_Init( this );
        }
        return this;
    }
    
    
    
    bool            srcErrors_SharedReset(
    )
    {
        SRCERRORS_DATA  *this = &singleton;
        
        while (obj_getRetainCount(this)) {
            obj_Release(this);
        }
        memset(&singleton, 0, sizeof(SRCERRORS_DATA));
        
        return true;
    }
    
    
    


    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         E r r o r s
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * srcErrors_getErrors(
        SRCERRORS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pErrors;
    }
    
    
    bool        srcErrors_setErrors(
        SRCERRORS_DATA  *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pErrors) {
            obj_Release(this->pErrors);
        }
        this->pErrors = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  E x i t  O n  F a t a l
    //---------------------------------------------------------------
    
    bool            srcErrors_getExitOnFatal(
        SRCERRORS_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return this->fExitOnFatal;
    }
    
    
    bool            srcErrors_setExitOnFatal(
        SRCERRORS_DATA  *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
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
    
    bool            srcErrors_getFatal(
        SRCERRORS_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return this->fFatal;
    }
    
    
    bool            srcErrors_setFatal(
        SRCERRORS_DATA  *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
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
    
    bool            srcErrors_setFatalExit(
        SRCERRORS_DATA  *this,
        ERESULT         (*pFatalExit)(OBJ_ID, SRCERRORS_DATA *),
        OBJ_ID          pFatalExitObject
    )
    {
        
        if (OBJ_NIL == this){
            this = srcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pFatalExit = pFatalExit;
        this->pFatalExitObject = pFatalExitObject;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                N u m b e r  o f  E r r o r s
    //---------------------------------------------------------------
    
    uint32_t        srcErrors_getNumErrors(
        SRCERRORS_DATA     *this
    )
    {
        uint32_t            num = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (this->pErrors) {
            num = objArray_getSize(this->pErrors);
        }
        
        return num;
    }

    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        srcErrors_getPriority(
        SRCERRORS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            srcErrors_setPriority(
        SRCERRORS_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
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
    
    uint32_t        srcErrors_getSize(
        SRCERRORS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  srcErrors_getSuperVtbl(
        SRCERRORS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
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
    
    bool        srcErrors_AddErrorA(
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
            this = srcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
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
            pError = srcError_NewFromData(severity, pLocation, pStr);
            mem_Free( pStr );
            pStr = NULL;
        }
        else {
            pError = srcError_NewFromData(severity, pLocation, pStr);
        }
        if (OBJ_NIL == pError) {
            return false;
        }
        eRc = objArray_AppendObj(this->pErrors, pError, NULL);
        obj_Release(pError);
        pError = OBJ_NIL;
        if (ERESULT_FAILED(eRc)) {
            return false;
        }
        
        if (severity == SRCERROR_SEVERITY_FATAL) {
            srcErrors_setFatal(this, true);
            if (this->fExitOnFatal) {
                srcErrors_ExitOnFatal(this);
            }
        }
        
        // Return to caller.
        return true;
    }
    
    
    ERESULT         srcErrors_AddFatal(
        SRCERRORS_DATA  *this,
        SRCERROR_DATA   *pError
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = srcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pError) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = objArray_AppendObj(this->pErrors, pError, NULL);
        if (ERESULT_FAILED(eRc)) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        srcErrors_setFatal(this, true);
        if (this->fExitOnFatal) {
            srcErrors_ExitOnFatal(this);
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         srcErrors_AddFatalA(
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
            this = srcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
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
            pError = srcError_NewFromData(SRCERROR_SEVERITY_FATAL, pLocation, pStr);
            mem_Free( pStr );
            pStr = NULL;
        }
        else {
            pError = srcError_NewFromData(SRCERROR_SEVERITY_FATAL, pLocation, pStr);
        }
        if (OBJ_NIL == pError) {
            return false;
        }
        
        eRc = srcErrors_AddFatal(this, pError);
        obj_Release(pError);
        pError = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         srcErrors_AddFatalArgsA (
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
            this = srcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
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
            pError = srcError_NewFromData(SRCERROR_SEVERITY_FATAL, pLocation, pStr);
            mem_Free( pStr );
            pStr = NULL;
        }
        else {
            pError = srcError_NewFromData(SRCERROR_SEVERITY_FATAL, pLocation, pStr);
        }
        if (OBJ_NIL == pError) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        eRc = srcErrors_AddFatal(this, pError);
        obj_Release(pError);
        pError = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         srcErrors_AddFatalExpectingA(
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
            this = srcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pWrk = AStr_New();
        if (OBJ_NIL == pWrk) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        pTmp = token_getTextAStr(pToken);
        AStr_AppendPrint(
                pWrk,
                "Expecting: %s but found: %s\n",
                pExpected,
                AStr_getData(pTmp)
        );
        obj_Release(pTmp);
        
        pError = srcError_NewFatalFromToken(pToken, pWrk);
        obj_Release(pWrk);
        if (OBJ_NIL == pError) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        eRc = srcErrors_AddFatal(this, pError);
        obj_Release(pError);
        pError = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         srcErrors_AddFatalFromTokenA(
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
            this = srcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
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
            pError = srcError_NewFatalFromTokenA(pToken, pStr);
            mem_Free( pStr );
            pStr = NULL;
        }
        else {
            pError = srcError_NewFatalFromTokenA(pToken, pStr);
        }
        if (OBJ_NIL == pError) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        eRc = srcErrors_AddFatal(this, pError);
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
        ERESULT eRc = srcErrors__Assign(this,pOther);
     @endcode 
     @param     this    SRCERRORS object pointer
     @param     pOther  a pointer to another SRCERRORS object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         srcErrors_Assign(
        SRCERRORS_DATA		*this,
        SRCERRORS_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!srcErrors_Validate(pOther)) {
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
        srcErrors      *pCopy = srcErrors_Copy(this);
     @endcode 
     @param     this    SRCERRORS object pointer
     @return    If successful, a SRCERRORS object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the SRCERRORS object.
     */
    SRCERRORS_DATA *    srcErrors_Copy(
        SRCERRORS_DATA      *this
    )
    {
        SRCERRORS_DATA      *pOther = OBJ_NIL;
        ERESULT             eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = srcErrors_New( );
        if (pOther) {
            eRc = srcErrors_Assign(this, pOther);
            if (ERESULT_FAILED(eRc)) {
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

    void            srcErrors_Dealloc(
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
        if( !srcErrors_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SRCERRORS_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        srcErrors_setErrors(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          E n u m
    //---------------------------------------------------------------

    OBJENUM_DATA *  srcErrors_EnumErrors(
        SRCERRORS_DATA  *this
    )
    {
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
        if (OBJ_NIL == this) {
            this = srcErrors_Shared();
        }
    #ifdef NDEBUG
    #else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
    #endif
        
        if (this->pErrors) {
            pEnum = objArray_Enum(this->pErrors);
        }

        // Put code here...
        
        // Return to caller.
        return pEnum;
    }



    //---------------------------------------------------------------
    //               E x i t  O n  F a t a l
    //---------------------------------------------------------------
    
    void            srcErrors_ExitOnFatal(
        SRCERRORS_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = srcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        if (this->fFatal) {
            srcErrors_Print(this);
            if (this->pFatalExit) {
                eRc = this->pFatalExit(this->pFatalExitObject, this);
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

    SRCERRORS_DATA *   srcErrors_Init(
        SRCERRORS_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SRCERRORS_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SRCERRORS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_SRCERRORS);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&srcErrors_Vtbl);
        this->pFatalExit = srcErrors_DefaultFatalExit;
        
        this->pErrors = objArray_New( );

    #ifdef NDEBUG
    #else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "srcErrors::sizeof(SRCERRORS_DATA) = %lu\n", sizeof(SRCERRORS_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SRCERRORS_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                  L a t e s t  E r r o r
    //---------------------------------------------------------------
    
    SRCERROR_DATA * srcErrors_LatestError(
        SRCERRORS_DATA  *this
    )
    {
        SRCERROR_DATA   *pError = OBJ_NIL;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = srcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pErrors) {
            pError = objArray_GetLast(this->pErrors);
        }
        
        // Return to caller.
        return pError;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P r i n t
    //---------------------------------------------------------------
    
    void            srcErrors_Print(
        SRCERRORS_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        OBJENUM_DATA    *pEnum = OBJ_NIL;
        SRCERROR_DATA   *pError = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = srcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        pEnum = srcErrors_EnumErrors(this);
        if (pEnum) {
            while (objEnum_Remaining(pEnum)) {
                eRc = objEnum_Next(pEnum, 1, (void **)&pError, NULL);
                if (ERESULT_SUCCESSFUL(eRc)) {
                    pStr = srcError_ToString(pError);
                    if (pStr) {
                        fprintf(stderr, "%s", AStr_getData(pStr));
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
        void        *pMethod = srcErrors_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "srcErrors", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          srcErrors_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SRCERRORS_DATA  *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return srcErrors_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == srcErrors_ToDebugString)
                    return "ToDebugString";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = srcErrors_ToDebugString(this,4);
     @endcode 
     @param     this    SRCERRORS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     srcErrors_ToDebugString(
        SRCERRORS_DATA  *this,
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
        if (OBJ_NIL == this) {
            this = srcErrors_Shared();
        }
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = srcErrors_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) %s\n",
                    this,
                    pInfo->pClassName,
                    (srcErrors_getFatal(this) ? "fatal_error(s)" : "")
            );

        pWrkStr = objArray_ToDebugString(this->pErrors, (indent + 3));
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
    
    
    
    ASTR_DATA *     srcErrors_ToJSON(
        SRCERRORS_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!srcErrors_Validate(this)) {
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
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            srcErrors_Validate(
        SRCERRORS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_SRCERRORS) )
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


        if( !(obj_getSize(this) >= sizeof(SRCERRORS_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


