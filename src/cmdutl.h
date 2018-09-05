// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Command Utilities (cmdutl) Header
//****************************************************************
/*
 * Program
 *			Command Utilities (cmdutl)
 * Purpose
 *			This object provides a standardized way of parsing or
 *          constructing command line data.
 *
 *
 *
 *
 * Remarks
 *	1.      The internals are based on a public domain version of optparse.
 *          It has been extened to fit our environment and needs.
 *          See http://github.com/skeeto/optparse for details
 *
 * History
 *	10/18/2015 Generated
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
#include        <AStrArray.h>
#include        <number.h>
#include        <objArray.h>
#include        <path.h>
#include        <AStr.h>


#ifndef         CMDUTL_H
#define         CMDUTL_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


#ifndef         CMDUTL_FIELD_MAX
#define         CMDUTL_FIELD_MAX  512
#endif

    
    typedef struct cmdutl_data_s	CMDUTL_DATA;


    typedef struct cmdutl_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        
        // Properties:
        
        // Methods:
        
    } CMDUTL_VTBL;
    
    
    typedef enum cmdutl_arg_option_e {
        CMDUTL_ARG_OPTION_UNKNOWN=0,
        CMDUTL_ARG_OPTION_NONE,
        CMDUTL_ARG_OPTION_OPTIONAL,
        CMDUTL_ARG_OPTION_REQUIRED,
    }   CMDUTL_ARG_OPTION;
    
    
    typedef enum cmdutl_type_e {
        CMDUTL_TYPE_UNKNOWN=0,
        CMDUTL_TYPE_BOOL,               // uint16_t - 0 == false, > 0 == true
        //                              // (same as CMDUTL_TYPE_INCR)
        CMDUTL_TYPE_EXEC,               // Execute given routine
        //                              // (with argument if available)
        CMDUTL_TYPE_HJSON,              // Node pointer - HJSON will be used
        //                              // to parse the Argument's parameter
        //                              // looking for a "value" not a "hash".
        //                              // (Argument parameter is required)
        CMDUTL_TYPE_INCR,               // uint16_t - Every occurence increases the
        //                              // associated value (default is 0);
        CMDUTL_TYPE_NUMBER,             // Number pointer
        //                              // (Argument parameter is required)
        CMDUTL_TYPE_PATH,               // Path pointer
        //                              // (Argument parameter is required)
        CMDUTL_TYPE_STRING,             // AStr pointer
        //                              // (Argument parameter is required)
        CMDUTL_TYPE_VALUE,              // Value pointer
        //                              // (Argument parameter is required)
    }   CMDUTL_TYPE;
    
    // An option must have at a minimum either a short name or a long name,
    // as well as both.  cmdutl_ProcessOption() will correctly handle these
    // three situations.
    // Note - The end of an option table is denoted by a pLongName of NULL
    // and a shortName of 0.
    typedef struct cmdutl_option_s {
        char            *pLongName;         // "--" option_name (optional, may be NULL)
        W32CHR_T        shortName;          // "-" option_name (required)
        uint16_t        argOption;          // See CMDUTIL_ARG_OPTION above.
        uint16_t        argType;            // See CMDUTIL_TYPE above.
        uint32_t        offset;             // Option Offset
        ERESULT         (*pExec)(           // Method to execute if APPL_ARG_EXEC
                                 OBJ_ID,
                                 const
                                 char *              // Arg Ptr if present or NULL
        );
        const
        char            *pDesc;             // Option Description
    } CMDUTL_OPTION;
        


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    CMDUTL_DATA *   cmdutl_Alloc(
        void
    );
    
    
    /*! Set up an ArgC/ArgV type array given a command line string
     excluding the program name.
     @param     pCmdStrA    Pointer to a UTF-8 Argument character string
     @return    If successful, an AStrArray object which must be
                released containing the Argument Array, otherwise
                OBJ_NIL if an error occurred.
     @warning   Remember to release the returned AStrArray object.
     */
    ASTRARRAY_DATA * cmdutl_CommandStringToArray(
        const
        char            *pCmdStrA
    );
    
    
    /*! Convert an ArgC/ArgV array to a command line string.
     @param     argc        Number of arguments in argv
     @param     argv        Pointer to an array of UTF-8 Arguments
     @return    If successful, an AStr object which must be
                released containing the Argument Array as a string.
                Otherwise, OBJ_NIL if an error occurred.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     cmdutl_ArgvToAStr(
        int             argc,
        const
        char            *argv[]
    );
    
    
    CMDUTL_DATA *   cmdutl_New(
        int             cArgs,
        char            **ppArgs
    );

    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJ_ID      cmdutl_getObject(
        CMDUTL_DATA *this
    );
    
    bool        cmdutl_setObject(
        CMDUTL_DATA *this,
        OBJ_ID      pValue
    );

    
    CMDUTL_OPTION * cmdutl_getOptionDefinitions(
        CMDUTL_DATA *this
    );
    
    
    PATH_DATA *     cmdutl_getPath(
        CMDUTL_DATA     *this
    );

    bool            cmdutl_setPath(
        CMDUTL_DATA     *this,
        PATH_DATA       *pValue
    );
    
    
    bool            cmdutl_getPermute(
        CMDUTL_DATA     *this
    );

    bool            cmdutl_setPermute(
        CMDUTL_DATA     *this,
        bool            fValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    CMDUTL_DATA *     cmdutl_Init(
        CMDUTL_DATA     *this,
        int             cArgs,
        char            **ppArgs
    );
    
    
    /*!
     Check to see if there are more options or arguments left to parse.
     @param     this        Object Pointer
     @return:   true if there are more options or arguments to parse,
                otherwise, false.
     */
    bool            cmdutl_IsMore(
        CMDUTL_DATA     *this
    );
    
    
    /*!
     Return the next argument if present.
     @param     this        Object Pointer
     @return:   If there is another argument, return the address of it's
                character string, otherwise, return NULL.
     */
    char *          cmdutl_NextArg(
        CMDUTL_DATA     *this
    );
    
    
    /*!
     After an option is found, it must be handled according to the
     argType in the CMDUTL_OPTION.  This method does that processing.
     @param     this        Object Pointer
     @param     pOption     Pointer to CMDUTL_OPTION of option found
     @return:   If successful, true and the appropriate argument processing
     was performed; otherwise, false.
     */
    ERESULT         cmdutl_ProcessOption(
        CMDUTL_DATA     *this,
        CMDUTL_OPTION   *pOption
    );
    
    
    /*!
     Parse and process all options up until the next argument using the
     supplied object definitions.
     @param     this        Object Pointer
      @return:   If successful, ERESULT_SUCCESS and the appropriate argument
                processing was performed; otherwise, an ERESULT_* error code.
     */
    ERESULT         cmdutl_ProcessOptions(
        CMDUTL_DATA     *this
    );
    
    
    bool            cmdutl_Reset(
        CMDUTL_DATA     *this,
        int             cArgs,
        char            **ppArgs
    );
    
    
    /*!
     Set up the options to be used in the parsing phase from two optional sources.
     @param     this        Object Pointer
     @param     pDefaultOptions
                            Pointer to CMDUTL_OPTION list ended with an
                            entry of NULL in pLongName and 0 in shortName.
     @param     pProgramOptions
                            Pointer to CMDUTL_OPTION list ended with an
                            entry of NULL in pLongName and 0 in shortName.
     @return:   If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error code.
     */
    ERESULT         cmdutl_SetupOptions(
        CMDUTL_DATA     *this,
        CMDUTL_OPTION   *pDefaultOptions,
        CMDUTL_OPTION   *pProgramOptions
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     cmdutl_ToDebugString(
        CMDUTL_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* CMDUTL_H */

