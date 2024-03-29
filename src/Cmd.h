// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Command Base (Cmd) Header
//****************************************************************
/*
 * Program
 *          Command Base (Cmd)
 * Purpose
 *          This object accepts command requests, creates the
 *          appropriate command processor and optionally sup-
 *          ports undo/redo. Command requests are made in
 *          textual format.  It is assumed that they come from
 *          a file or keyboard, but that processing is extraneous
 *          to this object.  The command input is parsed using
 *          CmdUtl and then delegated to the appropriate command
 *          processor (CmdProc).
 *
 *          Part of command process support is the ability to
 *          undo/redo any command. If this is to be implemented,
 *          there are generally two techniques that can be used.
 *          The first is to implement the command with a "not"
 *          command name and implement that as a separate
 *          command. The other way is to implement a "not" flag
 *          within the command that tells it to undo/redo itself.
 *
 *          In the first case above, the undo/redo stacks need
 *          to be implemented within this object.  The latter
 *          technique allows the undo/redo stacks to be im-
 *          plemented within the command process object.
 *
 *
 * Remarks
 *  1.      None
 *
 * History
 *  12/29/2020 Generated
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
#include        <CmdUtl.h>
#include        <Node.h>


#ifndef         CMD_H
#define         CMD_H


//#define   CMD_IS_IMMUTABLE     1
#define   CMD_JSON_SUPPORT       1
//#define   CMD_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Cmd_data_s  CMD_DATA;            // Inherits from OBJ
    typedef struct Cmd_class_data_s CMD_CLASS_DATA;   // Inherits from OBJ

    typedef struct Cmd_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Cmd_object.c.
        // Properties:
        // Methods:
        ERESULT         (*pExec) (OBJ_ID);
        ERESULT         (*pRedo) (OBJ_ID);
        ERESULT         (*pUndo) (OBJ_ID);
    } CMD_VTBL;


    typedef struct Cmd_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Cmd_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CMD_DATA *);
    } CMD_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  CMD_SINGLETON
    CMD_DATA *      Cmd_Shared (
        void
    );

    void            Cmd_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Cmd object if successful, otherwise OBJ_NIL.
     */
    CMD_DATA *      Cmd_Alloc (
        void
    );
    
    
    OBJ_ID          Cmd_Class (
        void
    );
    
    
    CMD_DATA *      Cmd_New (
        void
    );
    
    
#ifdef  CMD_JSON_SUPPORT
    CMD_DATA *      Cmd_NewFromJsonString (
        ASTR_DATA       *pString
    );

    CMD_DATA *      Cmd_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! @property String
     is the command string to be executed if it is in string format.
     */
    ASTR_DATA * Cmd_getStr (
        CMD_DATA     *this
    );

    bool        Cmd_setStr (
        CMD_DATA     *this,
        ASTR_DATA   *pValue
    );


    NODE_DATA * Cmd_getSuper (
        CMD_DATA    *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Execute the command.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmd_Exec (
        CMD_DATA        *this
    );


    CMD_DATA *      Cmd_Init (
        CMD_DATA        *this
    );


    /*!
     Redo a previously undone command.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmd_Redo (
        CMD_DATA        *this
    );
    
 
#ifdef  CMD_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Cmd_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Cmd_ToJson (
        CMD_DATA        *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Cmd_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Cmd_ToDebugString (
        CMD_DATA        *this,
        int             indent
    );
    
    
    /*!
     Undo a previously executed command.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmd_Undo (
        CMD_DATA        *this
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* CMD_H */

