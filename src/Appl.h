// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Application Base Object (Appl) Header
//****************************************************************
/*
 * Program
 *			Application Base Object (Appl)
 * Purpose
 *          This object provides the basis for an Application.
 *          It helps in scanning the arguments given and provides
 *          various support functions needed by most Applications.
 *          It is meant to be inherited by an object which is
 *          specialized for the actual Application.
 *
 * Remarks
 *    1.    Argument switches, --force(f), --debug(-d), --verbose(-v),
 *          and --help(-?,-h), are handled by this object. However,
 *          the supplied options provided will override these in the
 *          search.
 *  2.      --debug will cause this object's trace flag to be turned
 *          on.
 *  3.      This object is intended to be inherited by another
 *          object which would add the specialization needed by
 *          the particular Application.
 *  4.      Normal Program flow looks like:
 *                Appl_SetupFromArgV()
 *                ParseArgsDefaults()       // Parse options and do option
 *                                          // execs() per cmdutl
 *                do {
 *                    Appl_ProcessOptions() // Merge in the next set of options
 *                    if (!Appl_IsMore())
 *                        break
 *                    Appl_NextArg()
 *                    // process this argument
 *                } (forever)
 *
 * History
 *  06/05/2017 Generated
 *	01/31/2020 Regenerated
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
#include        <AStrC.h>
#include        <AStrCArray.h>
#include        <CmdUtl.h>
#include        <DateTime.h>
#include        <Node.h>


#ifndef         APPL_H
#define         APPL_H


//#define   APPL_IS_IMMUTABLE     1
//#define   APPL_JSON_SUPPORT     1
#define   APPL_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Appl_data_s	APPL_DATA;            // Inherits from OBJ
    typedef struct Appl_class_data_s APPL_CLASS_DATA;   // Inherits from OBJ

    typedef struct Appl_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Appl_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(APPL_DATA *);
    } APPL_VTBL;

    typedef struct Appl_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Appl_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(APPL_DATA *);
    } APPL_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  APPL_SINGLETON
    APPL_DATA *     Appl_Shared (
        void
    );

    void            Appl_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Appl object if successful, otherwise OBJ_NIL.
     */
    APPL_DATA *     Appl_Alloc (
        void
    );
    
    
    OBJ_ID          Appl_Class (
        void
    );
    
    
    void            Appl_ErrorFatal (
        const
        char            *fmt,
        ...
    );

    void            Appl_ErrorFatalArg (
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
    void            Appl_ErrorFatalArgOnEresult (
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
    void            Appl_ErrorFatalOnBool (
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
    void            Appl_ErrorFatalOnEresult (
        ERESULT         eRc,
        const
        char            *fmt,
        ...
    );

    void            Appl_ErrorFatalFLC (
        const
        char            *pFileName,
        uint32_t        linnum,
        uint16_t        colnum,
        const
        char            *fmt,
        ...
    );

    void            Appl_ErrorFatalFLCArg (
        const
        char            *pFileName,
        uint32_t        linnum,
        uint16_t        colnum,
        const
        char            *fmt,
        va_list         argsp
    );


    APPL_DATA *     Appl_New (
        void
    );
    
    
    APPL_DATA *     Appl_NewFromArgV (
        int             cArgs,
        const
        char            *ppArgs[],
        const
        char            **ppEnv
    );


#ifdef  APPL_JSON_SUPPORT
    APPL_DATA *     Appl_NewFromJsonString (
        ASTR_DATA       *pString
    );

    APPL_DATA *     Appl_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    /*! ParseProgramLine parses the program command line breaking it
     up into substrings forming an argv/argc structure. Arguments are
     separated by whitespace. An AStrC Array is used for argv/argc.
     We don't have to completely parse the command line, just break
     it up being coznizant of the quoted strings which assumes that
     they should either be by themselves or at the end of an argument.
     Note: we currently do not handle embedded quotes.
     @param     pCmdStr UTF-8 Command String
     @param     ppArgV  An eresult success/failure code (see eresult.h)
     */
    ERESULT         Appl_ParseProgramLine (
        const
        char            *pCmdStr,           // UTF-8 Command String
        ASTRCARRAY_DATA **ppArgV            // Output ArgV Array
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            Appl_setArgDefs (
        APPL_DATA       *this,
        CMDUTL_OPTION   *pProgramArgs
    );


    CMDUTL_DATA *   Appl_getCmd (
        APPL_DATA       *this
    );


    DATETIME_DATA * Appl_getDateTime (
        APPL_DATA       *this
    );


    bool            Appl_getDebug (
        APPL_DATA       *this
    );


    bool            Appl_getForce (
        APPL_DATA       *this
    );


    PATH_DATA *     Appl_getProgramPath (
        APPL_DATA       *this
    );

    bool            Appl_setProgramPath (
        APPL_DATA       *this,
        PATH_DATA       *pValue
    );


    bool            Appl_getQuiet (
        APPL_DATA       *this
    );


    bool            Appl_setUsage (
        APPL_DATA       *this,
        OBJ_ID          pObj,
        ERESULT         (*pUsageDesc)(OBJ_ID, FILE *, PATH_DATA *),
        ERESULT         (*pUsageProgLine)(OBJ_ID, FILE *, PATH_DATA *, const char *),
        ERESULT         (*pUsageOptions)(OBJ_ID, FILE *)
    );


    int             Appl_getVerbose (
        APPL_DATA     *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    int             Appl_Exec (
        APPL_DATA       *this
    );


    /*!
     Exit from the Application performing any cleanup needed.
     @param     this        Object Pointer
     @param     exitCode    exit code passed to O/S
     */
    void            Appl_Exit (
        APPL_DATA       *this,
        int             exitCode
    );


    APPL_DATA *     Appl_Init (
        APPL_DATA       *this
    );


    /*!
     Check to see if there are more options or arguments left to parse.
     @param     this        Object Pointer
     @return:   true if there are more options or arguments to parse,
                otherwise, false.
     */
    bool            Appl_IsMore (
        APPL_DATA       *this
    );


    /*!
     Issue a Warning messages if the Quiet property is false (default).
     @param     this        Object Pointer
     @param     fmt         fprint type format     */
    void            Appl_MsgInfo(
        APPL_DATA       *this,
        const
        char            *fmt,
        ...
    );


    /*!
     Issue a Warning messages if the Quiet property is false (default)
     and the Verbose property is greater than or equal to iVerbose
     (default 0).
     @param     this        Object Pointer
     @param     iVerbose    Verbose Level
     @param     fmt         fprint type format
     */
    void            Appl_MsgWarn(
        APPL_DATA       *this,
        uint16_t        iVerbose,
        const
        char            *fmt,
        ...
    );


    char *          Appl_NextArg (
        APPL_DATA       *this
    );


    uint16_t        Appl_NumberOfProperties (
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
    ERESULT         Appl_ProcessOptions (
        APPL_DATA       *this
    );


    ERESULT         Appl_PropertyAdd (
        APPL_DATA       *this,
        NODE_DATA       *pData
    );


    NODE_DATA *     Appl_PropertyFind (
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
    ERESULT         Appl_SetupFromArgV (
        APPL_DATA       *this,
        uint16_t        cArgs,
        char            *ppArgV[],
        char            **ppEnv,
        CMDUTL_OPTION   *pPgmOptDefns
    );


#ifdef  APPL_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Appl_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Appl_ToJson (
        APPL_DATA       *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Appl_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Appl_ToDebugString (
        APPL_DATA       *this,
        int             indent
    );
    
    
    void            Appl_Usage (
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
    ERESULT         Appl_VerboseIncrease (
        APPL_DATA       *this
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* APPL_H */

