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
 *  0.      We parse "--" switches using HJSON. So, the format of
 *          "--" switch is:
 *              "--".name('='.HJSON_text)?
 *          or
 *              "--".name HJSON_text
 *	1.      Argument switches, --force, --debug(-d), --verbose(-v),
 *          and --help(-?,-h), are handled by this object.
 *  2.      --debug will cause this object's trace flag to be turned
 *          on.
 *  3.      This object is intended to be inherited by another
 *          object which would add the specialization needed by
 *          the particular application.
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
        //                          // associated value (default is 0);
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
        uint32_t        offset;             // Offset of Argument Data (NULL == do
        //                                  // not use this)
        ERESULT         (*pExec)(           // Method to execute if APPL_ARG_EXEC
                            OBJ_ID,
                            ASTR_DATA *         // Data Ptr for arg
                        );
        //                                  // of APPL_DATA
        const
        char            *pDesc;             // Argument Description
    } APPL_CLO;
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to appl object if successful, otherwise OBJ_NIL.
     */
    APPL_DATA *     appl_Alloc(
        void
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
        uint16_t        cProgramArgs,
        APPL_CLO        *pProgramArgs,
        uint16_t        cGroupArgs,
        APPL_CLO        *pGroupArgs
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
    
    
    ERESULT         appl_getLastError(
        APPL_DATA		*this
    );


    bool            appl_setParseArgs(
        APPL_DATA       *this,
        OBJ_ID          pExit,
        ERESULT         (*pValueDefaults)(OBJ_ID),
        ERESULT         (*pValueLong)(
                                      OBJ_ID          this,
                                      bool            fTrue,
                                      ASTR_DATA       *pName,
                                      ASTR_DATA       *pWrk,
                                      uint32_t        index,
                                      ASTRARRAY_DATA  *pArgs
                        ),
        ERESULT         (*pValueShort)(
                                       OBJ_ID, int *, const char ***
                        )
    );
    
    
    bool            appl_setProcessArgs(
        APPL_DATA       *this,
        OBJ_ID          pObj,
        ERESULT         (*pProcessInit)(OBJ_ID),
        ERESULT         (*pProcessArg)(OBJ_ID, ASTR_DATA *)
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

    
    APPL_DATA *     appl_Init(
        APPL_DATA       *this
    );


    ASTR_DATA *     appl_NextArg(
        APPL_DATA       *this
    );
    
    
    uint16_t        appl_NumberOfProperties(
        APPL_DATA       *this
    );

    
    ERESULT         appl_ParseArgs(
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
     @param     this    object pointer
     @param     cArgs   number of charater strings in ppArgs
     @param     ppArgV  point to a charater string array
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code
     */
    ERESULT         appl_SetupFromArgV(
        APPL_DATA       *this,
        uint16_t        cArgs,
        const
        char            *ppArgV[],
        const
        char            **ppEnv
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
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* APPL_H */

