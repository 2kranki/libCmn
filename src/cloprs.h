// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          CLOPRS Console Transmit Task (cloprs) Header
//****************************************************************
/*
 * Program
 *			Separate cloprs (cloprs)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate cloprs to run things without complications
 *          of interfering with the main cloprs. A cloprs may be 
 *          called a cloprs on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	08/22/2018 Generated
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
#include        <path.h>


#ifndef         CLOPRS_H
#define         CLOPRS_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct cloprs_data_s	CLOPRS_DATA;    // Inherits from OBJ.

    typedef struct cloprs_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in cloprs_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CLOPRS_DATA *);
    } CLOPRS_VTBL;



    typedef enum clo_arg_class_e {
        CLO_ARG_UNKNOWN=0,
        CLO_ARG_OPTIONAL,
        CLO_ARG_REQUIRED
    } CLO_ARG_CLASS;
    
    typedef enum clo_arg_type_e {
        //CLO_ARG_UNKNOWN=0,
        CLO_ARG_ARRAY=1,            // Object Array of Numbers, Paths or Strings parameter
        CLO_ARG_BOOL,               // uint8_t - 0 or 1 (No other parameters)
        CLO_ARG_EXEC,               // Execute given routine w/o parameter
        CLO_ARG_EXEC_PARM,          // Execute given routine w/parameter (either
        //                          // from '=' or following parameter
        CLO_ARG_INCR,               // uint16_t - Every occurence increases the
        //                          // associated value (default is 0). This
        //                          // should be used for boolean parameters as
        //                          // well as integer parameters such as Verbose
        //                          // and when no argument is expected.
        CLO_ARG_NUMBER,             // Number object parameter
        CLO_ARG_PATH,               // Path object parameter
        CLO_ARG_STRING,             // AStr object parameter
    } CLO_ARG_TYPE;

    
    typedef struct clo_option_s    {
        const
        char            *pArgLong;          // UTF-8 Long Argument Name (required)
        W32CHR_T        argChr;             // UTF-8 Argument Character (optional)
        //                                  // (Use 0 if not needed.)
        uint16_t        cls;                // Argument Class (See CLO_ARG_CLASS above.)
        uint16_t        type;               // Argument Type (See CLO_ARG_TYPE above.)
        uint32_t        offset;             // Offset of Argument Data
        //                                  // (0 == do not use this)
        ERESULT         (*pExec)(           // Method to execute if APPL_ARG_EXEC
                                 OBJ_ID,
                                 ASTR_DATA *         // Data Ptr for arg
                                 );
        //                                  // of APPL_DATA
        const
        char            *pDesc;             // Argument Description
    } CLO_OPTION;
    
    
    
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
     @return    pointer to cloprs object if successful, otherwise OBJ_NIL.
     */
    CLOPRS_DATA *   cloprs_Alloc(
        void
    );
    
    
    /*! Convert an ArgC/ArgV array to a command line string.
     @param     cArgs       Number of arguments in ppArgs
     @param     ppArgs      Pointer to an array of UTF-8 Arguments
     @return    If successful, an AStr object which must be
     released containing the Argument Array as a string.
     Otherwise, OBJ_NIL if an error occurred.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     cloprs_ArgvToAStr(
        int             cArgs,
        const
        char            **ppArgs
    );
    
    
    OBJ_ID          cloprs_Class(
        void
    );
    
    
    CLOPRS_DATA *   cloprs_New(
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
    //FIXME:   We need to make this aware of the Array and Hash allowed in
    //FIXME:   in parameters since they may have whitespace between elements.
    ASTRARRAY_DATA * cloprs_StringToArray(
        const
        char            *pCmdStrA
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     cloprs_Disable(
        CLOPRS_DATA		*this
    );


    ERESULT     cloprs_Enable(
        CLOPRS_DATA		*this
    );

   
    CLOPRS_DATA *   cloprs_Init(
        CLOPRS_DATA     *this
    );


    ERESULT     cloprs_IsEnabled(
        CLOPRS_DATA		*this
    );
    
 
    /*!
     Set up to parse the given input resetting any prior parse data.
     @param     this    object pointer
     @param     cArgs   number of charater strings in ppArgs
     @param     ppArgV  point to a charater string array
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code.
     */
    ERESULT         cloprs_SetupFromArgV(
        CLOPRS_DATA     *this,
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
        ASTR_DATA      *pDesc = cloprs_ToDebugString(this,4);
     @endcode 
     @param     this    CLOPRS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    cloprs_ToDebugString(
        CLOPRS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* CLOPRS_H */

