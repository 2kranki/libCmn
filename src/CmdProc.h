// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Command Processor (CmdProc) Header
//****************************************************************
/*
 * Program
 *          Command Processor (CmdProc)
 * Purpose
 *          This object provides a standardized way of handling
 *          a command from the console or input file.  The options
 *          are parsed from the supplied command definition, CMDPROC_CMD,
 *          using CmdUtl.
 *
 *          Undo/Redo is one of the nicest things to implement in
 *          commands that cause changes.  To support this, a change
 *          stack must be maintained which contains the before state
 *          of what is being changed. JSON is easy to implement and
 *          makes saving and restoring state relatively easy. We
 *          define the state stack using NodeList objects so that
 *          the state can be saved in Nodes maybe using JSON AStr's.
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
#include        <NodeList.h>
#include        <Value.h>


#ifndef         CMDPROC_H
#define         CMDPROC_H


//#define   CMDPROC_IS_IMMUTABLE     1
#define   CMDPROC_JSON_SUPPORT       1
//#define   CMDPROC_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct CmdProc_data_s  CMDPROC_DATA;            // Inherits from OBJ
    typedef struct CmdProc_class_data_s CMDPROC_CLASS_DATA;   // Inherits from OBJ

    typedef struct CmdProc_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in CmdProc_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CMDPROC_DATA *);
    } CMDPROC_VTBL;

    typedef struct CmdProc_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in CmdProc_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CMDPROC_DATA *);
    } CMDPROC_CLASS_VTBL;


    // An option must have at a minimum either a short name or a long name. Both
    // may be provided.  CmdUtl_ProcessOption() will correctly handle these
    // three situations.
    // Note - The end of an option table is denoted by a pLongName of NULL
    // and a shortName of 0.
    typedef struct CmdProc_option_s {
        char            *pLongName;         // command full name (optional, may be NULL)
        W32CHR_T        shortName;          // command short name (optional, may be '\0')
        // Note - either a long or short name must be specified. Both may be specified.
        CMDUTL_OPTION   *pOptions;          // Pointer to CMDUTL_OPTION list ended with
        //                                  // an entry of NULL in pLongName and 0 in
        //                                  // shortName.
        uint16_t        optSize;            // Option Area Size
        const
        char            *pDesc;             // Command Description
    } CMDPROC_CMD;


    /*!         Execution Interface
     This object is supplied externally and defines the execution
     interface exit points that will be called at the appropriate
     times in the RPG cycle.
     */
    typedef struct CmdProc_Exec_interface_s CMDPROC_EXEC_INTERFACE;

    typedef struct CmdProc_Exec_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // All methods must be defined to return bool.
        // Properties:
        // Methods:
        // LevelBreakN methods are called when a break for that
        // level occurs or a higher level.
        ERESULT     (*pExec)(CMDPROC_EXEC_INTERFACE *, void *pOptions);
        ERESULT     (*pRedo)(CMDPROC_EXEC_INTERFACE *);
        ERESULT     (*pUndo)(CMDPROC_EXEC_INTERFACE *);
    } CMDPROC_EXEC_VTBL;

#pragma pack(push, 1)
    struct CmdProc_Exec_interface_s    {
        CMDPROC_EXEC_VTBL   *pVtbl;
    };
#pragma pack(pop)

#define Rpg_ExecVtbl(ptr)   ((RPGBASE_EXEC_INTERFACE *)ptr)->pVtbl





    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  CMDPROC_SINGLETON
    CMDPROC_DATA *  CmdProc_Shared (
        void
    );

    void            CmdProc_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to CmdProc object if successful, otherwise OBJ_NIL.
     */
    CMDPROC_DATA *  CmdProc_Alloc (
        void
    );
    
    
    OBJ_ID          CmdProc_Class (
        void
    );
    
    
    CMDPROC_DATA *  CmdProc_New (
        void
    );
    
    
#ifdef  CMDPROC_JSON_SUPPORT
    CMDPROC_DATA *  CmdProc_NewFromJsonString (
        ASTR_DATA       *pString
    );

    CMDPROC_DATA *  CmdProc_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    CMDPROC_EXEC_INTERFACE *
                    CmdProc_getExec (
        CMDPROC_DATA    *this
    );

    bool            CmdProc_setExec (
        CMDPROC_DATA    *this,
        CMDPROC_EXEC_INTERFACE
                        *pValue
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         CmdProc_Disable (
        CMDPROC_DATA    *this
    );


    ERESULT         CmdProc_Enable (
        CMDPROC_DATA    *this
    );


    /*!
     Perform the speficic command supported by this object. Insure
     that the change state is pushed onto the undo stack before
     actually making the changes if undo/redo is supported.
     The Options for the command are parsed by CmdUtl and returned
     in pOptions which needs to be freed by mem_Free().
     @param     this        object pointer
     @param     pOptions    Option Area pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, return an
                ERESULT_* error code.
     */
    ERESULT         CmdProc_Exec (
        CMDPROC_DATA    *this,
        void            *pOptions
    );


    /*!
     Indicate whether this command support undo/redo.
     @param     this    object pointer
     @return    If this command supports undo, return true. Otherwise, return
                false.
     */
    bool            CmdProc_HasUndo (
        CMDPROC_DATA    *this
    );


    CMDPROC_DATA *  CmdProc_Init (
        CMDPROC_DATA    *this
    );


    ERESULT         CmdProc_IsEnabled (
        CMDPROC_DATA    *this
    );
    
 
    ERESULT         CmdProc_Redo (
        CMDPROC_DATA    *this
    );


    VALUE_DATA *    CmdProc_RedoPop (
        CMDPROC_DATA    *this
    );


    ERESULT         CmdProc_RedoPush (
        CMDPROC_DATA    *this,
        VALUE_DATA      *pData
    );


#ifdef  CMDPROC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = CmdProc_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     CmdProc_ToJson (
        CMDPROC_DATA    *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = CmdProc_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     CmdProc_ToDebugString (
        CMDPROC_DATA    *this,
        int             indent
    );
    
    
    ERESULT         CmdProc_Undo (
        CMDPROC_DATA    *this
    );


    VALUE_DATA *     CmdProc_UndoPop (
        CMDPROC_DATA    *this
    );


    ERESULT         CmdProc_UndoPush (
        CMDPROC_DATA    *this,
        VALUE_DATA      *pData
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* CMDPROC_H */

