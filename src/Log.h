// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Log File Support (Log) Header
//****************************************************************
/*
 * Program
 *          Log File Support (Log)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Log to run things without complications
 *          of interfering with the main Log. A Log may be 
 *          called a Log on other O/S's.
 *
 * Remarks
 *  1.      This object requires the Appl interface, APPL_VTBL.
 *
 * History
 *  11/24/2021 Generated
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
#include        <FileIO.h>


#ifndef         LOG_H
#define         LOG_H


//#define   LOG_IS_IMMUTABLE     1
//#define   LOG_JSON_SUPPORT     1
//#define   LOG_SINGLETON        1
//#define       LOG_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Log_data_s  LOG_DATA;          // Inherits from LOG
    typedef struct Log_class_data_s LOG_CLASS_DATA;  // Inherits from OBJ

    // Warning - this VTBL must stay consisttant with logInterface!
    typedef struct Log_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Log_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Log_object.c.
        // Properties:
        // Methods:
        void        (*pLogDebug)(OBJ_ID, const char *, ...);
        void        (*pLogFatal)(OBJ_ID, const char *, ...);
        void        (*pLogInfo)(OBJ_ID, const char *, ...);
        void        (*pLogWarn)(OBJ_ID, const char *, ...);
        ERESULT     (*pClose)(OBJ_ID);
    } LOG_VTBL;

    typedef struct Log_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Log_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LOG_DATA *);
    } LOG_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LOG_SINGLETON
    LOG_DATA *      Log_Shared (
        void
    );

    void            Log_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Log object if successful, otherwise OBJ_NIL.
     */
    LOG_DATA *      Log_Alloc (
        void
    );
    
    
    OBJ_ID          Log_Class (
        void
    );
    
    
    LOG_DATA *      Log_New (
        void
    );
    
    LOG_DATA *      Log_NewWithPath (
        PATH_DATA       *pPath
    );


#ifdef  LOG_JSON_SUPPORT
    LOG_DATA *      Log_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LOG_DATA *      Log_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJ_ID          Log_getAppl (
        LOG_DATA        *this
    );

    bool            Log_setAppl (
        LOG_DATA        *this,
        OBJ_ID          pValue
    );


    uint16_t        Log_getWarnMax (
        LOG_DATA        *this
    );

    bool            Log_setWarnMax (
        LOG_DATA        *this,
        uint16_t        value
    );

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Close the log file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Log_Close (
        LOG_DATA        *this
    );


    /*!
     Create a log file. If a previous log file was open, it is closed.
     @param     this    object pointer
     @param     pPath   Path object pointer of the log file to create
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Log_Create (
        LOG_DATA        *this,
        PATH_DATA       *pPath
    );


    /*!
     Write the given message if debug flag is set and quiet flag is off.
     @param     this        object pointer
     @param     pFormatA    printf-like message format which should end with '\n'
     */
    void            Log_Debug(
        LOG_DATA        *this,
        const
        char            *pFormatA,
        ...
    );


    /*!
     Write the given message and terminate the application with an exit code of 8.
     Since Fatal is so important, we allow "this" to be OBJ_NIL and we will still
     issue the message to stderr then exit(8). Normally, we want the termination
     to go through the application object if possible. That way, it can perform
     clean up.
     @param     this        object pointer (may be NULL/OBJ_NIL)
     @param     pFormatA    printf-like message format which should end with '\n'
     */
    void            Log_Fatal(
        LOG_DATA        *this,
        const
        char            *pFormatA,
        ...
    );


    /*!
     Write the given message if the quiet flag is off.
     @param     this        object pointer
     @param     pFormatA    printf-like message format which should end with '\n'
     */
    void            Log_Info(
        LOG_DATA        *this,
        const
        char            *pFormatA,
        ...
    );


    LOG_DATA *      Log_Init (
        LOG_DATA        *this
    );


#ifdef  LOG_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Log_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Log_ToJson (
        LOG_DATA        *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Log_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Log_ToDebugString (
        LOG_DATA        *this,
        int             indent
    );
    
    
    /*!
     Write the given message if the verbose count is greater than or equal to
     the supplied verbose count. When the maximum warning count is reached,
     the application is terminated.
     @param     this        object pointer
     @param     iVerbose    Supplied verbose count
     @param     pFormatA    printf-like message format which should end with '\n'
     */
    void            Log_Warn(
        LOG_DATA        *this,
        uint16_t        iVerbose,
        const
        char            *pFormatA,
        ...
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* LOG_H */

