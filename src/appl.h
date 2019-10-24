// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Application Control (appl) Header
//****************************************************************
/*
 * Program
 *			Application Control (appl)
 * Purpose
 *			This object provides the basis for an application.
 *          It helps in scanning the arguments given and provides
 *          various support functions needed by most applications.
 *          It is meant to be inherited by an object which is
 *          specialized for the actual application.
 *
 * Remarks
 *	1.      Argument switches, --force(f), --debug(-d), --verbose(-v),
 *          and --help(-?,-h), are handled by this object. However,
 *          the supplied options provided will override these in the
 *          search.
 *  2.      --debug will cause this object's trace flag to be turned
 *          on.
 *  3.      This object is intended to be inherited by another
 *          object which would add the specialization needed by
 *          the particular application.
 *  4.      Normal Program flow looks like:
 *                appl_SetupFromArgV()
 *                ParseArgsDefaults()       // Parse options and do option
 *                                          // execs() per cmdutl
 *                do {
 *                    appl_ProcessOptions() // Merge in the next set of options
 *                    if (!appl_IsMore())
 *                        break
 *                    appl_NextArg()
 *                    // process this argument
 *                } (forever)
 *
 * History
 *	06/05/2017 Generated
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
#include        <AStr.h>
#include        <AStrArray.h>
#include        <cmdutl.h>
#include        <dateTime.h>
#include        <node.h>


#ifndef         APPL_H
#define         APPL_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct appl_data_s	APPL_DATA;    // Inherits from OBJ.

    typedef struct appl_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in appl_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(APPL_DATA *);
    } APPL_VTBL;

    
    
#ifdef XYZZY
    typedef enum appl_arg_class_e {
        APPL_ARG_UNKNOWN=0,
        APPL_ARG_PROGRAM,           //
        APPL_ARG_GROUP,             // Execute given routine
    } APPL_ARG_CLASS;

    
    typedef enum appl_arg_type_e {
        //APPL_ARG_UNKNOWN=0,       // Defined above
        APPL_ARG_BOOL=1,            // uint8_t - 0 or 1 (No other parameters)
        APPL_ARG_EXEC,              // Execute given routine w/o parameter
        APPL_ARG_EXEC_PARM,         // Execute given routine w/parameter (either
        //                          // from '=' or following parameter
        APPL_ARG_INCR,              // uint16_t - Every occurence increases the
        //                          // associated value (default is 0). This
        //                          // should be used for boolean parameters as
        //                          // well as integer parameters such as iVerbose.
        APPL_ARG_NUMBER,            // Number object parameter
        APPL_ARG_PATH,              // Path object parameter
        APPL_ARG_STRING,            // AStr object parameter
    } APPL_ARG_TYPE;

    
    typedef struct appl_clo_s    {
        W32CHR_T        argChr;             // UTF-8 Argument Character (optional)
        //                                  // (Use 0 if not needed.)
        const
        char            *pArgLong;          // UTF-8 Long Argument Name (required)
        uint16_t        cls;                // Argument Class (See APPL_ARG_CLASS above.)
        uint16_t        type;               // Argument Type (See APPL_ARG_TYPE above.)
        uint32_t        offset;             // Offset of Argument Data
        //                                  // (0 == do not use this)
        ERESULT         (*pExec)(           // Method to execute if APPL_ARG_EXEC
                            OBJ_ID,
                            ASTR_DATA *         // Data Ptr for arg
                        );
        //                                  // of APPL_DATA
        const
        char            *pDesc;             // Argument Description
    } APPL_CLO;
#endif

    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Get the Object's singleton object.
     @return    pointer to appl object if successful, otherwise OBJ_NIL.
     */
    APPL_DATA *     appl_Shared(
        void
    );
    
    void            appl_SharedReset(
        void
    );
    
    
    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to appl object if successful, otherwise OBJ_NIL.
     */
    APPL_DATA *     appl_Alloc(
        void
    );
    
    
    void            appl_ErrorFatal(
        const
        char            *fmt,
        ...
    );
    
    void            appl_ErrorFatalArg(
        const
        char            *fmt,
        va_list         argsp
    );
    
    /*!
     If eRc shows failure then issue error message and abend (abnormal
     termination of program).  Otherwise, do nothing.
     @param     eRc     An eresult success/failure code (see eresult.h)
     @param     fmt     fprint format string
     @param     argsp   va_list argument pointer
     */
    void            appl_ErrorFatalArgOnEresult(
        ERESULT         eRc,
        const
        char            *fmt,
        va_list         argsp
    );
    
    /*!
     If fRc is non-zero then issue error message and abend (abnormal
     termination of program).  Otherwise, do nothing.
     @param     fRc     An boolean success/failure code
     @param     fmt     fprint format string
     */
    void            appl_ErrorFatalOnBool(
        bool            fRc,
        const
        char            *fmt,
        ...
    );
    
    /*!
     If eRc shows failure then issue error message and abend (abnormal
     termination of program).  Otherwise, do nothing.
     @param     eRc     An eresult success/failure code (see eresult.h)
     @param     fmt     fprint format string
     */
    void            appl_ErrorFatalOnEresult(
        ERESULT         eRc,
        const
        char            *fmt,
        ...
    );
    
    void            appl_ErrorFatalFLC(
        const
        char            *pFileName,
        uint32_t        linnum,
        uint16_t        colnum,
        const
        char            *fmt,
        ...
    );
    
    void            appl_ErrorFatalFLCArg(
        const
        char            *pFileName,
        uint32_t        linnum,
        uint16_t        colnum,
        const
        char            *fmt,
        va_list         argsp
    );
    

    APPL_DATA *     appl_New(
        void
    );
    
    APPL_DATA *     appl_NewFromArgV(
        int             cArgs,
        const
        char            *ppArgs[],
        const
        char            **ppEnv
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            appl_setArgDefs(
        APPL_DATA       *this,
        CMDUTL_OPTION   *pProgramArgs
    );
    
    
    CMDUTL_DATA *   appl_getCmd(
        APPL_DATA       *this
    );
    
    
    DATETIME_DATA * appl_getDateTime(
        APPL_DATA       *this
    );
    
    
    bool            appl_getDebug(
        APPL_DATA       *this
    );
    

    bool            appl_getForce(
        APPL_DATA       *this
    );
    
    
    PATH_DATA *     appl_getProgramPath(
        APPL_DATA       *this
    );
    
    bool            appl_setProgramPath(
        APPL_DATA       *this,
        PATH_DATA       *pValue
    );

    
    bool            appl_getQuiet(
        APPL_DATA       *this
    );
    
    
    bool            appl_setUsage(
        APPL_DATA       *this,
        OBJ_ID          pObj,
        ERESULT         (*pUsageDesc)(OBJ_ID, FILE *, PATH_DATA *),
        ERESULT         (*pUsageProgLine)(OBJ_ID, FILE *, PATH_DATA *, const char *),
        ERESULT         (*pUsageOptions)(OBJ_ID, FILE *)
    );

    
    int             appl_getVerbose(
        APPL_DATA     *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    int             appl_Exec(
        APPL_DATA       *this
    );

    
    /*!
     Exit from the application performing any cleanup needed.
     @param     this        Object Pointer
     @param     exitCode    exit code passed to O/S
     */
    void            appl_Exit(
        APPL_DATA       *this,
        int             exitCode
    );
    
    
    APPL_DATA *     appl_Init(
        APPL_DATA       *this
    );


    /*!
     Check to see if there are more options or arguments left to parse.
     @param     this        Object Pointer
     @return:   true if there are more options or arguments to parse,
                otherwise, false.
     */
    bool            appl_IsMore(
        APPL_DATA       *this
    );
    
    
    char *          appl_NextArg(
        APPL_DATA       *this
    );
    
    
    uint16_t        appl_NumberOfProperties(
        APPL_DATA       *this
    );

    
    /*!
     Parse and merge the next set of zero or more options per their option
     definitions. The parsing stops when the next argument is reached or
     there are no more options and arguments.
     @param     this        object pointer
     and
     @return:   If successful, ERESULT_SUCCESS and the appropriate argument
                processing was performed; otherwise, an ERESULT_* error code.
     */
    ERESULT         appl_ProcessOptions(
        APPL_DATA       *this
    );
    
    
    ERESULT         appl_PropertyAdd(
        APPL_DATA       *this,
        NODE_DATA       *pData
    );
    
    
    NODE_DATA *     appl_PropertyFind(
        APPL_DATA       *this,
        const
        char            *pName
    );
    
    
    /*!
     Set up to parse the given input resetting any prior parse data.
     @param     this        object pointer
     @param     cArgs       number of charater strings in ppArgs
     @param     ppArgV      pointer to a charater string array
     @param     pPgmOptDefns pointer to an array of APPL_CLO elements
                            and 
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code
     */
    ERESULT         appl_SetupFromArgV(
        APPL_DATA       *this,
        uint16_t        cArgs,
        char            *ppArgV[],
        char            **ppEnv,
        CMDUTL_OPTION   *pPgmOptDefns
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = appl_ToDebugString(this,4);
     @endcode
     @param     this    APPL object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     appl_ToDebugString(
        APPL_DATA       *this,
        int             indent
    );
    
    
    void            appl_Usage(
        APPL_DATA       *this,
        char            *pMsg,
        ...
    );
    
    
    /*!
     Increase the Verbosity level by 1 allowing the program to increase it if necessary.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code
     */
    ERESULT         appl_VerboseIncrease(
        APPL_DATA       *this
    );

    
#ifdef	__cplusplus
}
#endif

#endif	/* APPL_H */

