// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   eResult.c
 *	Generated 05/24/2015 10:53:28
 *
 * Created on December 30, 2014
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
#include    "eResult_internal.h"
#include    <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    static
    ERESULT_DATA    singleton = {{0}};
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/


    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ERESULT_DATA *  eResult_Alloc(
    )
    {
        ERESULT_DATA    *this;
        uint32_t        cbSize = sizeof(ERESULT_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ERESULT_DATA *  eResult_New(
    )
    {
        ERESULT_DATA    *this;
        
        // Do initialization.
        
        this = eResult_Alloc( );
        if (this) {
            this = eResult_Init(this);
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    ERESULT_DATA *  eResult_NewAStr(
        ASTR_DATA       *pValue
    )
    {
        ERESULT_DATA    *this;
        
        // Do initialization.
        
        this = eResult_Alloc( );
        if (this) {
            this = eResult_Init(this);
            if (this && pValue) {
                eResult_setError(this, pValue);
            }
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    ERESULT_DATA *	eResult_Shared(
    )
    {
        ERESULT_DATA    *this = &singleton;
        uint32_t        cbSize = sizeof(ERESULT_DATA);
        
        if (obj_getRetainCount(this) == 0) {
            obj_setSize(this, cbSize);
            this = eResult_Init( this );
        }
        return this;
    }
    
    
    
    bool            eResult_SharedReset(
    )
    {
        ERESULT_DATA    *this = &singleton;
        
        while (obj_getRetainCount(this)) {
            obj_Release(this);
        }
        memset(&singleton, 0, sizeof(ERESULT_DATA));
        
        return true;
    }
    
    
    
    ERESULT         eResult_getSharedLastResult(
    )
    {
        ERESULT_DATA     *this = eResult_Shared();
        
        return this->eRc;
    }

    
    bool            eResult_setSharedLastResult(
        ERESULT         value
    )
    {
        ERESULT_DATA     *this = eResult_Shared();

        this->eRc = value;
        
        return true;
    }
    
    
    
    void            eResult_ErrorFatalOn(
        ERESULT         eRc,
        const
        char            *fmt,
        ...
    )
    {
        va_list         argsp;
        
        if (ERESULT_FAILED(eRc)) {
            va_start( argsp, fmt );
            fprintf( stderr, "Fatal Error:  " );
            vfprintf( stderr, fmt, argsp );
            va_end( argsp );
            fprintf( stderr, "\n\n\n" );
            exit( 100 );
        }
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ASTR_DATA *     eResult_getError(
        ERESULT_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !eResult_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pMsg;
    }

    
    bool            eResult_setError(
        ERESULT_DATA    *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !eResult_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pMsg) {
            obj_Release(this->pMsg);
            // this->pMsg = OBJ_NIL;
        }
        this->pMsg = pValue;
        
        return true;
    }



    ERESULT        eResult_getErrorNum(
        ERESULT_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !eResult_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->eRc;
    }
    
    
    bool            eResult_setErrorNum(
        ERESULT_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !eResult_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    uint32_t        eResult_getSize(
        ERESULT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !eResult_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return 0;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            eResult_Dealloc(
        OBJ_ID          objId
    )
    {
        ERESULT_DATA    *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !eResult_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         E r r o r
    //---------------------------------------------------------------
    
#ifdef XYZZY
    void            eResult_Error(
        ERESULT_DATA   *cbp,
        const
        char			*fmt,
        ...
    )
    {
        va_list 		argsp;
        
        
        va_start( argsp, fmt );
        
        fprintf( stderr, "Error:  " );
        vfprintf( stderr, fmt, argsp );
        
        ++cbp->numErrors;
        if (cbp->numErrors > cbp->maxErrors) {
            eResult_ErrorFatal(cbp, "Too many errors");
        }
        
    }
    
    
    
    void            eResult_ErrorArg(
        ERESULT_DATA   *cbp,
        const
        char			*fmt,
        va_list 		argsp
    )
    {
        
        fprintf( stderr, "Error:  " );
        vfprintf( stderr, fmt, argsp );
        
        ++cbp->numErrors;
        if (cbp->numErrors > cbp->maxErrors) {
            eResult_ErrorFatal(cbp, "Too many errors");
        }
        
    }
    
    

    void            eResult_ErrorFLC(
        ERESULT_DATA   *cbp,
        const
        char            *pFileName,
        uint32_t		linnum,
        uint16_t		colnum,
        const
        char			*fmt,
        ...
    )
    {
        va_list 		argsp;
        
        va_start( argsp, fmt );
        
        fprintf(
                    stderr,
                    "Error: %s line: %d col: %d  ",
                    (pFileName ? pFileName : ""),
                    linnum,
                    colnum
        );
        vfprintf( stderr, fmt, argsp );
        
        ++cbp->numErrors;
        if (cbp->numErrors > cbp->maxErrors) {
            eResult_ErrorFatal(cbp, "Too many errors");
        }
        
    }
    
    
    
    void            eResult_ErrorFLCArg(
        ERESULT_DATA   *cbp,
        const
        char            *pFileName,
        uint32_t		linnum,
        uint16_t		colnum,
        const
        char			*fmt,
        va_list 		argsp
    )
    {
        
        fprintf(
                    stderr,
                    "Error: %s line: %d col: %d  ",
                    (pFileName ? pFileName : ""),
                    linnum,
                    colnum
        );
        vfprintf( stderr, fmt, argsp );
        
        ++cbp->numErrors;
        if (cbp->numErrors > cbp->maxErrors) {
            eResult_ErrorFatal(cbp, "Too many errors");
        }
        
    }
#endif
    
    
    
    
    //---------------------------------------------------------------
    //                       F a t a l  E r r o r
    //---------------------------------------------------------------
    
#ifdef XYZZY
    void            eResult_ErrorFatal(
        ERESULT_DATA    *cbp,
        const
        char			*fmt,
        ...
    )
    {
        va_list 		argsp;
        
        va_start( argsp, fmt );
        fprintf( stderr, "Fatal Error:  " );
        vfprintf( stderr, fmt, argsp );
        va_end( argsp );
        fprintf( stderr, "\n\n\n" );
        
        exit( 99 );
    }
    

    
    void            eResult_ErrorFatalArg(
        ERESULT_DATA    *cbp,
        const
        char			*fmt,
        va_list 		argsp
    )
    {
        
        fprintf( stderr, "Fatal Error:  " );
        vfprintf( stderr, fmt, argsp );
        fprintf( stderr, "\n\n\n" );
        
        exit( 99 );
    }
    

    
    void            eResult_ErrorFatalFLC(
        ERESULT_DATA    *cbp,
        const
        char            *pFileName,
        uint32_t		linnum,
        uint16_t		colnum,
        const
        char			*fmt,
        ...
    )
    {
        va_list 		argsp;
        
        va_start( argsp, fmt );
        fprintf(
                stderr,
                "Fatal Error: %s line: %d col: %d  ",
                (pFileName ? pFileName : ""),
                linnum,
                colnum
        );
        vfprintf( stderr, fmt, argsp );
        va_end( argsp );
        fprintf( stderr, "\n\n\n" );
        
        exit( 99 );
    }
    

    
    void            eResult_ErrorFatalFLCArg(
        ERESULT_DATA    *cbp,
        const
        char            *pFileName,
        uint32_t		linnum,
        uint16_t		colnum,
        const
        char			*fmt,
        va_list 		argsp
    )
    {
        
        fprintf(
                stderr,
                "Fatal Error: %s line: %d col: %d  ",
                (pFileName ? pFileName : ""),
                linnum,
                colnum
        );
        vfprintf( stderr, fmt, argsp );
        fprintf( stderr, "\n\n\n" );
        
        exit( 99 );
    }
#endif
    
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ERESULT_DATA *   eResult_Init(
        ERESULT_DATA       *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_ERESULT );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&eResult_Vtbl);
        
        this->numErrors = 0;

    #ifdef NDEBUG
    #else
        if( !eResult_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            eResult_Validate(
        ERESULT_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_ERESULT) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(ERESULT_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


