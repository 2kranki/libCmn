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
        
        {ERESULT_INVALID_PARAMETER,         "Invalid Parameter"},
        {ERESULT_INVALID_FUNCTION,          "Invalid Function"},
        {ERESULT_INVALID_REQUEST,           "Invalid Request"},
        {ERESULT_INVALID_POINTER,           "Invalid Pointer"},
        {ERESULT_INVALID_OBJECT,            "Invalid Object"},
        {ERESULT_INVALID_MEMORY_ADDRESS,    "Invalid Memory Address"},
        {ERESULT_INVALID_ENVIRONMENT,       "Invalid Environment"},
        {ERESULT_INVALID_FORMAT,            "Invalid Format"},
        {ERESULT_INVALID_ACCESS_CODE,       "Invalid Access Code"},
        {ERESULT_INVALID_DATA,              "Invalid Data"},
        {ERESULT_INVALID_FILE,              "Invalid File"},
        {ERESULT_INVALID_OPCODE,            "Invalid Opcode"},
        {ERESULT_OUT_OF_RANGE,              "Out of Range"},
        {ERESULT_UNSUPPORTED_PARAMETER,     "Unsupported Parameter"},
        {ERESULT_INVALID_SYNTAX,            "Invalid Syntax"},

        // File Related Errors
        {ERESULT_CLOSE_ERROR,               "Close Error"},
        {ERESULT_OPEN_ERROR,                "Open Error"},
        {ERESULT_IO_ERROR,                  "I/O Error"},
        {ERESULT_SEEK_ERROR,                "Seek Error"},
        {ERESULT_EOF_ERROR,                 "EOF Error"},
        {ERESULT_WRITE_ERROR,               "Write Error"},
        {ERESULT_READ_ERROR,                "Read Error"},
        {ERESULT_FILE_NOT_FOUND,            "File Not Found"},
        {ERESULT_PATH_NOT_FOUND,            "Path Not Found"},
        {ERESULT_TOO_MANY_OPEN_FILES,       "Too Many Open Files"},
        {ERESULT_ACCESS_DENIED,             "Access Denied"},
        {ERESULT_INVALID_HANDLE,            "Invalid Handle"},
        {ERESULT_UNKNOWN_UNIT,              "Unknown Unit"},
        {ERESULT_INVALID_DISK_DRIVE,        "Invalid Disk Drive"},
        {ERESULT_CANT_DELETE_CUR_DIR,       "Can't delete current directory"},
        {ERESULT_NOT_SAME_DEVICE,           "Not same device"},
        {ERESULT_NO_MORE_FILES,             "No More Files"},
        {ERESULT_WRITE_PROTECTED_DISK,      "Write Protected Disk"},
        {ERESULT_DRIVE_NOT_READY,           "Drive Not Ready"},
        {ERESULT_UNKNOWN_COMMAND,           "Unknown Command"},
        {ERESULT_BAD_LENGTH,                "Bad Length"},
        {ERESULT_BAD_CRC,                   "Bad CRC"},
        {ERESULT_UNKNOWN_MEDIA_TYPE,        "Unknown Media Type"},
        {ERESULT_SECTOR_NOT_FOUND,          "Sector Not Found"},
        {ERESULT_PRINTER_OUT_OF_PAPER,      "Printer out of paper"},
        {ERESULT_WRITE_FAULT,               "Write Fault"},
        {ERESULT_READ_FAULT,                "Read Fault"},
        {ERESULT_FILE_LOCK_VIOLATION,       "File Lock Validation"},
        {ERESULT_DISK_CHANGE_INVALID,       "Invalid Disk Change"},
        {ERESULT_FILE_CLOSED,               "File Closed"},
        {ERESULT_FILE_ALREADY_EXISTS,       "File already exists"},
        {ERESULT_PATH_ALREADY_EXISTS,       "Path already exists"},
        {ERESULT_CANNOT_MAKE_DIRECTORY,     "Cannot make directory"},
        {ERESULT_DISK_FULL,                 "Disk Full"},
        {ERESULT_DIRECTORY_FULL,            "Directory Full"},
        {ERESULT_FILE_OPERATION_FAILED,     "File operation failed"},
        {ERESULT_OUT_OF_BUFFERS,            "Out of Buffers"},
        {ERESULT_BUFFER_FULL,               "Buffer Full"},
        {ERESULT_BUFFER_TOO_SMALL,          "Buffer Too Small"},

        {ERESULT_INVALID_PASSWORD,          "Invalid Password"},
        
        {ERESULT_DATA_ERROR,                "Data Error"},
        {ERESULT_DATA_NOT_FOUND,            "Data Not Found"},
        {ERESULT_DATA_CHANGED,              "Data Changed"},
        {ERESULT_DATA_ALREADY_EXISTS,       "Data Already Exists"},
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
        uint32_t        i;
        uint32_t        iMax = cErrorTable;

        /* Search the array.
         */
        for (i=0; i<iMax; i++) {
            if (Key == errorTable[i].errorCode)
                return &errorTable[i];
        }

        // Return to caller.
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
        
        // Do initialization.
        
        this = eResult_Alloc( );
        if (this) {
            this = eResult_Init(this);
            if (this) {
                this->eRc = eRc;
                if (pValue) {
                    eResult_setError(this, pValue);
                }
            }
        }
        
        // Return to caller.
        return this;
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

        if (pValue) {
            this = eResult_New( );
            if (this) {
                this->eRc = eRc;
                if (pValue) {
                    pStr = AStr_NewA(pValue);
                    eResult_setError(this, pStr);
                    obj_Release(pStr);
                }
            }
        } else {
            return eResult_NewAStr(eRc, OBJ_NIL);
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
        void
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
    
    
    
    void            eResult_ErrorFatalOnBool(
        bool            fRc,
        const
        char            *fmt,
        ...
    )
    {
        va_list         argsp;

        if (fRc) {
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
        
        eResult_setError(this, OBJ_NIL);

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
        ERESULT_DATA   *this,
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
        
        va_start(argsp, fmt);
        
        fprintf(
                    stderr,
                    "Error: %s line: %d col: %d  ",
                    (pFileName ? pFileName : ""),
                    linnum,
                    colnum
        );
        vfprintf(stderr, fmt, argsp);
        
        ++this->numErrors;
        if (this->numErrors > this->maxErrors) {
            eResult_ErrorFatal(this, "Too many errors");
        }
        
    }
    
    
    
    void            eResult_ErrorFLCArg(
        ERESULT_DATA   *this,
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
        vfprintf(stderr, fmt, argsp);
        
        ++this->numErrors;
        if (this->numErrors > this->maxErrors) {
            eResult_ErrorFatal(this, "Too many errors");
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
        ERESULT_DATA    *this
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
    //                          P r i n t
    //---------------------------------------------------------------

    void            eResult_Fprint(
        ERESULT_DATA    *this,
        FILE            *pFile
    )
    {
        ERROR_ENTRY     *pErrMsg;
        const
        char            *pMsg = NULL;

        if (OBJ_NIL == this) {
            return;
        }
#ifdef NDEBUG
#else
        if( !eResult_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        pMsg = "";
        pErrMsg = SearchErrors(this->eRc);
        if (pErrMsg) {
            if (pErrMsg->errorCode == this->eRc)
                pMsg = pErrMsg->pError;
        }

        if (this->pMsg) {
            fprintf(pFile, "Error: %s (%d) - %s\n\n", pMsg, this->eRc,
                    AStr_getData(this->pMsg));
        } else {
            fprintf(pFile, "Error: %s (%d)\n\n", pMsg, this->eRc);
        }
        
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


