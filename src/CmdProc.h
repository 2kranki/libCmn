// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Command Processor (CmdProc) Header
//****************************************************************
/*
 * Program
 *          Command Processor (CmdProc)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate CmdProc to run things without complications
 *          of interfering with the main CmdProc. A CmdProc may be 
 *          called a CmdProc on other O/S's.
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




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  CMDPROC_SINGLETON
    CMDPROC_DATA *     CmdProc_Shared (
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
    CMDPROC_DATA *     CmdProc_Alloc (
        void
    );
    
    
    OBJ_ID          CmdProc_Class (
        void
    );
    
    
    CMDPROC_DATA *     CmdProc_New (
        void
    );
    
    
#ifdef  CMDPROC_JSON_SUPPORT
    CMDPROC_DATA *   CmdProc_NewFromJsonString (
        ASTR_DATA       *pString
    );

    CMDPROC_DATA *   CmdProc_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     CmdProc_Disable (
        CMDPROC_DATA       *this
    );


    ERESULT     CmdProc_Enable (
        CMDPROC_DATA       *this
    );

   
    CMDPROC_DATA *   CmdProc_Init (
        CMDPROC_DATA     *this
    );


    ERESULT     CmdProc_IsEnabled (
        CMDPROC_DATA       *this
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
        CMDPROC_DATA   *this
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
        CMDPROC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* CMDPROC_H */

