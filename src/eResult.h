// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          ERESULT Console Transmit Task (eResult) Header
//****************************************************************
/*
 * Program
 *				Separate eresult (eResult)
 * Purpose
 *				This object provides a standardized way of handling
 *              a separate eresult to run things without complications
 *              of interfering with the main eresult. A eresult may be 
 *              called a eresult on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal eresult. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	05/24/2015 Generated
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





#include        <cmn_defs.h>
#include        <stdarg.h>


#ifndef         ERESULT_H
#define         ERESULT_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct eResult_data_s	ERESULT_DATA;
    
    typedef struct eResult_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fatFCB_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CB_DATA *);
    } ERESULT_VTBL;
    
    

    typedef enum eResult_codes_e {
        /* Codes greater than zero denote successful
         * completion and are user assignable.
         */
        ERESULT_SUCCESS_PARTIAL_DATA        = 7,
        ERESULT_SUCCESS_DATA_EXISTS         = 6,
        ERESULT_SUCCESS_DATA_CHANGED        = 5,
        ERESULT_SUCCESS_3                   = 3,
        ERESULT_SUCCESS_2                   = 2,
        ERESULT_SUCCESS_1                   = 1,
        ERESULT_SUCCESS_0                   = 0,

        //ERESULT_SUCCESS_UNEQUAL             = 4,    // Returned if we can not determine
        //                                          // a < or > relationship
        //ERESULT_SUCCESS_GREATER_THAN        = 3,
        //ERESULT_SUCCESS_LESS_THAN           = 1,
        
        ERESULT_TRUE                        = 1,
        ERESULT_SUCCESS_TRUE                = 1,
        ERESULT_SUCCESS_FALSE               = 0,
        ERESULT_FALSE                       = 0,
        ERESULT_SUCCESS                     = 0,
        //ERESULT_SUCCESS_EQUAL               = 0,
        ERESULT_SUCCESSFUL_COMPLETION       = 0,

        ERESULT_FAILURE                     = -1,
        ERESULT_FAILURE_FALSE               = -1,
        ERESULT_GENERIC                     = -4,
        ERESULT_GENERAL_FAILURE             = -5,
        ERESULT_NOT_IMPLEMENTED             = -6,
        ERESULT_NOT_SUPPORTED               = -7,
        ERESULT_UNKNOWN                     = -8,
        ERESULT_OBJECT_CREATION             = -9,
        ERESULT_INTERNAL_ERROR              = -10,

        ERESULT_INSUFFICIENT_MEMORY         = -16,
        ERESULT_OUT_OF_MEMORY               = -16,
        ERESULT_MEMORY_DESTROYED            = -17,
        ERESULT_MEMORY_EXCEEDED             = -18,
        
        ERESULT_INVALID_PARAMETER           = -32,
        ERESULT_INVALID_FUNCTION            = -33,
        ERESULT_INVALID_REQUEST             = -34,
        ERESULT_INVALID_POINTER             = -35,
        ERESULT_INVALID_OBJECT              = -36,
        ERESULT_INVALID_MEMORY_ADDRESS      = -37,
        ERESULT_INVALID_ENVIRONMENT         = -38,
        ERESULT_INVALID_FORMAT              = -39,
        ERESULT_INVALID_ACCESS_CODE         = -40,
        ERESULT_INVALID_DATA                = -41,
        ERESULT_INVALID_FILE                = -42,
        ERESULT_INVALID_OPCODE              = -43,
        ERESULT_OUT_OF_RANGE                = -44,
        ERESULT_UNSUPPORTED_PARAMETER       = -45,
        ERESULT_INVALID_SYNTAX              = -46,
        ERESULT_INVALID_INDEX               = -47,

        // File Related Errors
        ERESULT_CLOSE_ERROR                 = -64,
        ERESULT_OPEN_ERROR                  = -65,
        ERESULT_IO_ERROR                    = -66,
        ERESULT_SEEK_ERROR                  = -67,
        ERESULT_EOF_ERROR                   = -68,
        ERESULT_WRITE_ERROR                 = -69,
        ERESULT_READ_ERROR                  = -70,
        ERESULT_FILE_NOT_FOUND              = -71,
        ERESULT_PATH_NOT_FOUND              = -72,
        ERESULT_TOO_MANY_OPEN_FILES         = -73,
        ERESULT_ACCESS_DENIED               = -74,
        ERESULT_INVALID_HANDLE              = -75,
        ERESULT_UNKNOWN_UNIT                = -76,
        ERESULT_INVALID_DISK_DRIVE          = -77,
        ERESULT_CANT_DELETE_CUR_DIR         = -78,
        ERESULT_NOT_SAME_DEVICE             = -79,
        ERESULT_NO_MORE_FILES               = -80,
        ERESULT_WRITE_PROTECTED_DISK        = -81,
        ERESULT_DRIVE_NOT_READY             = -82,
        ERESULT_UNKNOWN_COMMAND             = -83,
        ERESULT_BAD_LENGTH                  = -84,
        ERESULT_BAD_CRC                     = -85,
        ERESULT_UNKNOWN_MEDIA_TYPE          = -86,
        ERESULT_SECTOR_NOT_FOUND            = -87,
        ERESULT_PRINTER_OUT_OF_PAPER        = -88,
        ERESULT_WRITE_FAULT                 = -89,
        ERESULT_READ_FAULT                  = -90,
        ERESULT_FILE_LOCK_VIOLATION         = -91,
        ERESULT_DISK_CHANGE_INVALID         = -92,
        ERESULT_FILE_CLOSED                 = -93,
        ERESULT_FILE_ALREADY_EXISTS         = -94,
        ERESULT_PATH_ALREADY_EXISTS         = -95,
        ERESULT_CANNOT_MAKE_DIRECTORY       = -96,
        ERESULT_DISK_FULL                   = -97,
        ERESULT_DIRECTORY_FULL              = -98,
        ERESULT_FILE_OPERATION_FAILED       = -99,
        ERESULT_OUT_OF_BUFFERS              = -100,
        ERESULT_BUFFER_FULL                 = -101,
        ERESULT_BUFFER_TOO_SMALL            = -102,

        ERESULT_INVALID_PASSWORD            = -128,
        
        ERESULT_DATA_ERROR                  = -131,
        ERESULT_DATA_NOT_FOUND              = -132,
        ERESULT_DATA_CHANGED                = -133,
        ERESULT_DATA_ALREADY_EXISTS         = -134,
        ERESULT_DATA_TOO_BIG                = -135,
        ERESULT_DATA_TOO_SMALL              = -136,
        ERESULT_DATA_OUT_OF_RANGE           = -137,
        ERESULT_DATA_MISSING                = -138,
        ERESULT_DATA_SIZE                   = -139,
        ERESULT_KEY_NOT_FOUND               = -140,
        ERESULT_KEY_OUT_OF_RANGE            = -141,
        ERESULT_INDEX_FULL                  = -142,
        ERESULT_BIT_SYNTAX                  = -143,
        ERESULT_HEX_SYNTAX                  = -144,
        ERESULT_OCT_SYNTAX                  = -145,
        ERESULT_OVERFLOW                    = -146,
        ERESULT_UNDERFLOW                   = -147,
        ERESULT_SPECIFICATION               = -148,

        ERESULT_BUSY                        = -256,
        ERESULT_NOT_BUSY                    = -257,
        ERESULT_SHARING_VIOLATION           = -258,
        ERESULT_STOPPING                    = -259,
        ERESULT_STOPPED                     = -260,
        ERESULT_TIMEOUT                     = -261,
        ERESULT_PARSE_ERROR                 = -262,

        ERESULT_USER_START                  = -1024    /* First code for user usage */
        
    } ERESULT_CODES;
    
    
    
#ifndef ERESULT_DEFN
    typedef int32_t ERESULT;            // Error code
#define ERESULT_DEFN 1
#endif
    
#define ERESULT_FAILED(x) (x < 0)
#define ERESULT_HAS_FAILED(x) (x < 0)
#define ERESULT_OK(x) (x >= 0)
#define ERESULT_IS_SUCCESSFUL(x) (x >= 0)
#define ERESULT_SUCCESSFUL(x) (x >= 0)





    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    ERESULT_DATA *  eResult_Alloc(
        void
    );
    

    /*! Issue an error message and terminate the program if the
        given ERESULT is in an error state.  Otherwise, just return.
     */
    void            eResult_ErrorFatalOn(
        ERESULT         eRc,
        const
        char            *fmt,
        ...
    );


    /*! Issue an error message and terminate the program if the
        given bool is true.  Otherwise, just return.
     */
    void            eResult_ErrorFatalOnBool(
        bool            fRc,
        const
        char            *fmt,
        ...
    );


    ERESULT_DATA *  eResult_New(
        void
    );
    
    
    /*!
     Create a new eResult object that contains an error code and an error message. If
     pValue is OBJ_NIL, then an error message will be contructed from the error code.
     @param     eRc     Error Code
     @param     pValue  A string object pointer or OBJ_NIL
     @return    If successful, an eResult object pointer. Otherwise, OBJ_NIL.
     @warning  Remember to release the returned eResult object if present.
     */
    ERESULT_DATA *  eResult_NewAStr(
        ERESULT         eRc,
        ASTR_DATA       *pValue
    );
    
    
    /*!
     Create a new eResult object that contains an error code and an error message. If
     pValue is NULL, then an error message will be contructed from the error code.
     @param     eRc     Error Code
     @param     pValue  A string object pointer or OBJ_NIL
     @return    If successful, an eResult object pointer. Otherwise, OBJ_NIL.
     @warning  Remember to release the returned eResult object if present.
     */
    ERESULT_DATA *  eResult_NewStrA(
        ERESULT         eRc,
        const
        char            *pValue
    );


    ERESULT_DATA *  eResult_Shared(
        void
    );
    
    
    bool            eResult_SharedReset(
        void
    );
    



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------
    
    ASTR_DATA *     eResult_getError(
        ERESULT_DATA    *this
    );
    
    bool            eResult_setError(
        ERESULT_DATA    *this,
        ASTR_DATA       *pValue
    );

    const
    char *          eResult_getErrorA(
        ERESULT_DATA    *this
    );


    /*!
     Shared Result is the ERESULT which is a part of the shared singleton
     and can be used as a process result code.
     */
    ERESULT         eResult_getSharedResult(
        void
    );
    
    bool            eResult_setSharedResult(
        ERESULT         value
    );
    
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT_DATA *  eResult_Init(
        ERESULT_DATA    *this
    );


    void            eResult_Fprint(
        ERESULT_DATA    *this,
        FILE            *pFile
    );

#ifdef	__cplusplus
}
#endif

#endif	/* ERESULT_H */

