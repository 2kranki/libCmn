// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Posix Task Execution (psxExec) Header
//****************************************************************
/*
 * Program
 *			Posix Task Execution (psxExec)
 * Purpose
 *			This object provides a standardized way of executing
 *          separate tasks (ie scipts, programs, etc.)
 *
 * Remarks
 *	1.      None
 *
 * History
 *	06/14/2018 Generated
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


#ifndef         PSXEXEC_H
#define         PSXEXEC_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct psxExec_data_s	PSXEXEC_DATA;    // Inherits from OBJ.

    typedef struct psxExec_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in psxExec_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PSXEXEC_DATA *);
    } PSXEXEC_VTBL;



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
     @return    pointer to psxExec object if successful, otherwise OBJ_NIL.
     */
    PSXEXEC_DATA *     psxExec_Alloc(
        void
    );
    
    
    OBJ_ID          psxExec_Class(
        void
    );
    
    
    PSXEXEC_DATA *     psxExec_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     psxExec_getLastError(
        PSXEXEC_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     psxExec_Disable(
        PSXEXEC_DATA		*this
    );


    ERESULT     psxExec_Enable(
        PSXEXEC_DATA		*this
    );

   
    PSXEXEC_DATA *   psxExec_Init(
        PSXEXEC_DATA     *this
    );


    ERESULT     psxExec_IsEnabled(
        PSXEXEC_DATA		*this
    );
    
 
    /*!
     Execute a command returning the output of that commannd.
     @param     this        object pointer
     @param     pCommand    command to be executed
     @param     ppOutput    Pointer to ASTR pointer to be returned if
                            successful command completion
     @return    If successful, the comand's return code and an AStr object
                which must be released containing the command output.
                Otherwise EOF and ppOutput set to OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    int             psxExec_SystemWithOutput(
        PSXEXEC_DATA    *this,
        ASTR_DATA       *pCommand,
        ASTR_DATA       **ppOutput
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = psxExec_ToDebugString(this,4);
     @endcode 
     @param     this    PSXEXEC object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    psxExec_ToDebugString(
        PSXEXEC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PSXEXEC_H */

