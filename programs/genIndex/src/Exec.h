// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Execute a Command (Exec) Header
//****************************************************************
/*
 * Program
 *          Execute a Command (Exec)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Exec to run things without complications
 *          of interfering with the main Exec. A Exec may be 
 *          called a Exec on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  10/31/2021 Generated
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
#include        <Path.h>


#ifndef         EXEC_H
#define         EXEC_H


//#define   EXEC_IS_IMMUTABLE     1
//#define   EXEC_JSON_SUPPORT     1
//#define   EXEC_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Exec_data_s  EXEC_DATA;            // Inherits from OBJ
    typedef struct Exec_class_data_s EXEC_CLASS_DATA;   // Inherits from OBJ

    typedef struct Exec_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Exec_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(EXEC_DATA *);
    } EXEC_VTBL;

    typedef struct Exec_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Exec_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(EXEC_DATA *);
    } EXEC_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  EXEC_SINGLETON
    EXEC_DATA *     Exec_Shared (
        void
    );

    void            Exec_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Exec object if successful, otherwise OBJ_NIL.
     */
    EXEC_DATA *     Exec_Alloc (
        void
    );
    
    
    OBJ_ID          Exec_Class (
        void
    );
    
    
    EXEC_DATA *     Exec_New (
        void
    );
    
    
#ifdef  EXEC_JSON_SUPPORT
    EXEC_DATA *   Exec_NewFromJsonString (
        ASTR_DATA       *pString
    );

    EXEC_DATA *   Exec_NewFromJsonStringA (
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

    /*!
     Build the index that cross-references the enumeeration number to
     the sorted table number.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Exec_BuildIndex (
        EXEC_DATA       *this
    );


    /*!
     Create the document.
     @param     this        object pointer
     @param     pInputPath  input path pointer
     @param     pOutputPath output path pointer
     @param     pPrefixA    object name prefix
     @param     pNameA      enumeration name
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Exec_Exec (
        EXEC_DATA       *this,
        PATH_DATA       *pInputPath,
        PATH_DATA       *pOutputPath,
        const
        char            *pPrefixA,
        const
        char            *pNameA
    );


    /*!
     Generate the enum constant.
     @param     this        object pointer
     @param     pInputPath  input path pointer
     @param     pPrefixA    object name prefix
     @param     pNameA      enumeration name
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Exec_GenEnum (
        EXEC_DATA       *this,
        PATH_DATA       *pInputPath,
        const
        char            *pPrefixA,
        const
        char            *pNameA
    );


    /*!
     Generate the routines for the tables.
     @param     this        object pointer
     @param     pPrefixA    object name prefix
     @param     pNameA      enumeration name
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Exec_GenRoutines (
        EXEC_DATA       *this,
        PATH_DATA       *pInputPath,
        const
        char            *pPrefixA,
        const
        char            *pNameA
    );


    /*!
     Generate the constant tables.
     @param     this        object pointer
     @param     pInputPath  input path pointer
     @param     pPrefixA    object name prefix
     @param     pNameA      enumeration name
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Exec_GenTables (
        EXEC_DATA       *this,
        PATH_DATA       *pInputPath,
        const
        char            *pPrefixA,
        const
        char            *pNameA
    );


    EXEC_DATA *     Exec_Init (
        EXEC_DATA       *this
    );


#ifdef  EXEC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Exec_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Exec_ToJson (
        EXEC_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Exec_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Exec_ToDebugString (
        EXEC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* EXEC_H */

