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
#include    <AStr.h>
#include    <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif

    ASTR_DATA *    AStr_NewA(
        const
        char			*pszIn			/* Input String Pointer */
    );


    ASTR_DATA *    AStr_NewFromPrint(
        const
        char            *pFormat,
        ...
    );

    
    

    static
    ERESULT_DATA    singleton = {{0}};
    
    
    typedef struct {
        int         errorCode;
        const
        char        *pError;
    } ERROR_ENTRY;
    
    ERROR_ENTRY     errorTable[] = {
        {ERESULT_SUCCESS_PARTIAL_DATA,      NULL},
        {ERESULT_SUCCESS_DATA_EXISTS,       NULL},
        {ERESULT_SUCCESS_DATA_CHANGED,      NULL},
        {ERESULT_SUCCESS_3,                 NULL},
        {ERESULT_SUCCESS_2,                 NULL},
        {ERESULT_SUCCESS_1,                 NULL},
        {ERESULT_SUCCESS_0,                 NULL},

        {ERESULT_SUCCESS_UNEQUAL,           NULL},  // Returned if we can not determine
        //                                          // a < or > relationship
        {ERESULT_SUCCESS_GREATER_THAN,      NULL},
        {ERESULT_SUCCESS_EQUAL,             NULL},
        {ERESULT_SUCCESS_LESS_THAN,         NULL},
        
        {ERESULT_TRUE,                      NULL},
        {ERESULT_SUCCESS_TRUE,              NULL},
        {ERESULT_SUCCESS_FALSE,             NULL},
        {ERESULT_FALSE,                     NULL},
        {ERESULT_SUCCESS,                   NULL},
        {ERESULT_SUCCESSFUL_COMPLETION,     NULL},

        {ERESULT_FAILURE,                   "Failure"},
        {ERESULT_FAILURE_FALSE,             "Failure - False"},
        {ERESULT_GENERIC,                   "Generic"},
        {ERESULT_GENERAL_FAILURE,           "General Failure"},
        {ERESULT_NOT_IMPLEMENTED,           "Not Implemented"},
        {ERESULT_NOT_SUPPORTED,             "Not Supported"},
        {ERESULT_UNKNOWN,                   "Unknown"},
        {ERESULT_OBJECT_CREATION,           "Object Creation"},
        {ERESULT_INTERNAL_ERROR,            "Internal Failure"},

        {ERESULT_INSUFFICIENT_MEMORY,       "Insufficient Memory"},
        {ERESULT_OUT_OF_MEMORY,             "Out of Memory"},
        {ERESULT_MEMORY_DESTROYED,          "Memory destroyed"},
        {ERESULT_MEMORY_EXCEEDED,           "Memory exceeded"},
        
        {ERESULT_INVALID_PARAMETER,         NULL},
        {ERESULT_INVALID_FUNCTION,          NULL},
        {ERESULT_INVALID_REQUEST,           NULL},
        {ERESULT_INVALID_POINTER,           NULL},
        {ERESULT_INVALID_OBJECT,            NULL},
        {ERESULT_INVALID_MEMORY_ADDRESS,    NULL},
        {ERESULT_INVALID_ENVIRONMENT,       NULL},
        {ERESULT_INVALID_FORMAT,            NULL},
        {ERESULT_INVALID_ACCESS_CODE,       NULL},
        {ERESULT_INVALID_DATA,              NULL},
        {ERESULT_INVALID_FILE,              NULL},
        {ERESULT_INVALID_OPCODE,            NULL},
        {ERESULT_OUT_OF_RANGE,              NULL},
        {ERESULT_UNSUPPORTED_PARAMETER,     NULL},
        {ERESULT_INVALID_SYNTAX,            NULL},

        // File Related Errors
        {ERESULT_CLOSE_ERROR,               NULL},
        {ERESULT_OPEN_ERROR,                NULL},
        {ERESULT_IO_ERROR,                  NULL},
        {ERESULT_SEEK_ERROR,                NULL},
        {ERESULT_EOF_ERROR,                 NULL},
        {ERESULT_WRITE_ERROR,               NULL},
        {ERESULT_READ_ERROR,                NULL},
        {ERESULT_FILE_NOT_FOUND,            NULL},
        {ERESULT_PATH_NOT_FOUND,            NULL},
        {ERESULT_TOO_MANY_OPEN_FILES,       NULL},
        {ERESULT_ACCESS_DENIED,             NULL},
        {ERESULT_INVALID_HANDLE,            NULL},
        {ERESULT_UNKNOWN_UNIT,              NULL},
        {ERESULT_INVALID_DISK_DRIVE,        NULL},
        {ERESULT_CANT_DELETE_CUR_DIR,       NULL},
        {ERESULT_NOT_SAME_DEVICE,           NULL},
        {ERESULT_NO_MORE_FILES,             NULL},
        {ERESULT_WRITE_PROTECTED_DISK,      NULL},
        {ERESULT_DRIVE_NOT_READY,           NULL},
        {ERESULT_UNKNOWN_COMMAND,           NULL},
        {ERESULT_BAD_LENGTH,                NULL},
        {ERESULT_BAD_CRC,                   NULL},
        {ERESULT_UNKNOWN_MEDIA_TYPE,        NULL},
        {ERESULT_SECTOR_NOT_FOUND,          NULL},
        {ERESULT_PRINTER_OUT_OF_PAPER,      NULL},
        {ERESULT_WRITE_FAULT,               NULL},
        {ERESULT_READ_FAULT,                NULL},
        {ERESULT_FILE_LOCK_VIOLATION,       NULL},
        {ERESULT_DISK_CHANGE_INVALID,       NULL},
        {ERESULT_FILE_CLOSED,               NULL},
        {ERESULT_FILE_ALREADY_EXISTS,       NULL},
        {ERESULT_PATH_ALREADY_EXISTS,       NULL},
        {ERESULT_CANNOT_MAKE_DIRECTORY,     NULL},
        {ERESULT_DISK_FULL,                 NULL},
        {ERESULT_DIRECTORY_FULL,            NULL},
        {ERESULT_FILE_OPERATION_FAILED,     NULL},
        {ERESULT_OUT_OF_BUFFERS,            NULL},
        {ERESULT_BUFFER_FULL,               NULL},
        {ERESULT_BUFFER_TOO_SMALL,          NULL},

        {ERESULT_INVALID_PASSWORD,          NULL},
        
        {ERESULT_DATA_ERROR,                NULL},
        {ERESULT_DATA_NOT_FOUND,            NULL},
        {ERESULT_DATA_CHANGED,              NULL},
        {ERESULT_DATA_ALREADY_EXISTS,       NULL},
        {ERESULT_DATA_TOO_BIG,              NULL},
        {ERESULT_DATA_TOO_SMALL,            NULL},
        {ERESULT_DATA_OUT_OF_RANGE,         NULL},
        {ERESULT_DATA_MISSING,              NULL},
        {ERESULT_DATA_SIZE,                 NULL},
        {ERESULT_KEY_NOT_FOUND,             NULL},
        {ERESULT_KEY_OUT_OF_RANGE,          NULL},
        {ERESULT_INDEX_FULL,                NULL},
        {ERESULT_BIT_SYNTAX,                NULL},
        {ERESULT_HEX_SYNTAX,                NULL},
        {ERESULT_OCT_SYNTAX,                NULL},
        {ERESULT_OVERFLOW,                  "Overflow"},
        {ERESULT_UNDERFLOW,                 "Underflow"},
        {ERESULT_SPECIFICATION,             NULL},

        {ERESULT_BUSY,                      NULL},
        {ERESULT_NOT_BUSY,                  NULL},
        {ERESULT_SHARING_VIOLATION,         NULL},
        {ERESULT_STOPPING,                  NULL},
        {ERESULT_STOPPED,                   NULL},
        {ERESULT_TIMEOUT,                   NULL},
        {ERESULT_PARSE_ERROR,               NULL},
    };

    const
    int         cErrorTable = sizeof(errorTable)/sizeof(ERROR_ENTRY);

 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    ERROR_ENTRY  *  SearchErrors(
        int             Key
    )
    {
        size_t          High = cErrorTable - 1;
        size_t          Low = 0;
        size_t          Mid;
        int             rc;

        /* Search the array.
         */
        while (Low < High) {
            Mid = (High + Low) / 2;
            rc = Key - errorTable[Mid].errorCode;
            if( rc < 0 )
                High = Mid;
            else if( rc == 0 )
                return &errorTable[Mid];
            else
                Low = Mid + 1;
        }
        if (High == Low) {
            rc = Key - errorTable[Low].errorCode;
            if( rc == 0 )
                return &errorTable[Low];
        }

        /* Return to caller.
         */
        return NULL;
    }

    


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
        ERESULT         eRc,
        ASTR_DATA       *pValue
    )
    {
        ERESULT_DATA    *this;
        ERROR_ENTRY     *pError;
        
        // Do initialization.
        
        this = eResult_Alloc( );
        if (this) {
            this = eResult_Init(this);
            if (this && pValue) {
                this->eRc = eRc;
                if (pValue) {
                    eResult_setError(this, pValue);
                } else {
                    pError = SearchErrors(eRc);
                    if (pError) {
                        if (pError->pError) {
                            pValue = AStr_NewFromPrint("Error: %s!\n", pError->pError);
                        } else {
                            pValue = AStr_NewFromPrint("Error: %d - Undocumented Error!\n");
                        }
                    }
                    eResult_setError(this, pValue);
                }
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



    ERESULT_DATA *  eResult_NewStrA(
        ERESULT         eRc,
        const
        char            *pValue
    )
    {
        ERESULT_DATA    *this = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Do initialization.

        if (pValue)
            pStr = AStr_NewA(pValue);
        if (pStr) {
            this = eResult_New( );
            if (this) {
                this->eRc = eRc;
                eResult_setError(this, pStr);
            }
        }
        else {
            return eResult_NewAStr(eRc, OBJ_NIL);
        }

        // Return to caller.
        return this;
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

    const
    char *          eResult_getErrorA(
        ERESULT_DATA    *this
    )
    {
        const
        char            *pMsgA = NULL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !eResult_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        if (this->pMsg) {
            pMsgA = AStr_getData(this->pMsg);
        }
        
        return pMsgA;
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


