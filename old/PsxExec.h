// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//     Execute Posix Shell Command (PsxExec) Header
//****************************************************************
/*
 * Program
 *          Execute Posix Shell Command (PsxExec)
 * Purpose
 *          This object provides a standardized way of executing
 *          separate Posix tasks (ie scipts, programs, etc.)
 *
 * Remarks
 *  1.      None
 *
 * History
 *  06/14/2018 Generated
 *  05/13/2020 Regenerated
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


//#define   PSXEXEC_IS_IMMUTABLE     1
//#define   PSXEXEC_JSON_SUPPORT     1
//#define   PSXEXEC_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct PsxExec_data_s  PSXEXEC_DATA;            // Inherits from OBJ
    typedef struct PsxExec_class_data_s PSXEXEC_CLASS_DATA;   // Inherits from OBJ

    typedef struct PsxExec_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PsxExec_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PSXEXEC_DATA *);
    } PSXEXEC_VTBL;

    typedef struct PsxExec_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PsxExec_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PSXEXEC_DATA *);
    } PSXEXEC_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  PSXEXEC_SINGLETON
    PSXEXEC_DATA *  PsxExec_Shared (
        void
    );

    void            PsxExec_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to PsxExec object if successful, otherwise OBJ_NIL.
     */
    PSXEXEC_DATA *  PsxExec_Alloc (
        void
    );
    
    
    OBJ_ID          PsxExec_Class (
        void
    );
    
    
    PSXEXEC_DATA *  PsxExec_New (
        void
    );
    
    
#ifdef  PSXEXEC_JSON_SUPPORT
    PSXEXEC_DATA *  PsxExec_NewFromJsonString (
        ASTR_DATA       *pString
    );

    PSXEXEC_DATA *  PsxExec_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    /*!
     Execute a posix shell command.
     @param     pCommand    command to be executed
     @return    If successful, the comand's return code.
     */
    int             PsxExec_System(
        ASTR_DATA       *pCommand
    );


    /*!
     Execute a posix shell command returning the output of that commannd.
     @param     pCommand    command to be executed
     @param     ppOutput    Pointer to ASTR pointer to be returned if
                            successful command completion
     @return    If successful, the comand's return code and an AStr object
                which must be released containing the command output.
                Otherwise EOF and ppOutput set to OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    int             PsxExec_SystemWithOutput(
        ASTR_DATA       *pCommand,
        ASTR_DATA       **ppOutput
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    PSXEXEC_DATA *  PsxExec_Init (
        PSXEXEC_DATA    *this
    );


#ifdef  PSXEXEC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = PsxExec_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PsxExec_ToJson (
        PSXEXEC_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = PsxExec_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PsxExec_ToDebugString (
        PSXEXEC_DATA    *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* PSXEXEC_H */

