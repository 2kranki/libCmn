// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  SQLite Interface (SQLite) Header
//****************************************************************
/*
 * Program
 *          SQLite Interface (SQLite)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate SQLite to run things without complications
 *          of interfering with the main SQLite. A SQLite may be 
 *          called a SQLite on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  07/26/2020 Generated
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
#include        <AStrCArray.h>
#include        <sqlite3.h>


#ifndef         SQLITE_H
#define         SQLITE_H


//#define   SQLITE_IS_IMMUTABLE     1
//#define   SQLITE_JSON_SUPPORT     1
//#define   SQLITE_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SQLite_data_s  SQLITE_DATA;            // Inherits from OBJ
    typedef struct SQLite_class_data_s SQLITE_CLASS_DATA;   // Inherits from OBJ

    typedef struct SQLite_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SQLite_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLITE_DATA *);
    } SQLITE_VTBL;

    typedef struct SQLite_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SQLite_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLITE_DATA *);
    } SQLITE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SQLITE_SINGLETON
    SQLITE_DATA *     SQLite_Shared (
        void
    );

    void            SQLite_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SQLite object if successful, otherwise OBJ_NIL.
     */
    SQLITE_DATA *   SQLite_Alloc (
        void
    );
    
    
    OBJ_ID          SQLite_Class (
        void
    );
    
    
    SQLITE_DATA *   SQLite_New (
        void
    );
    
    SQLITE_DATA *   SQLite_NewPath (
        PATH_DATA       *pPath
    );


#ifdef  SQLITE_JSON_SUPPORT
    SQLITE_DATA *   SQLite_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SQLITE_DATA *   SQLite_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    sqlite3 *       SQLite_getConn (
        SQLITE_DATA     *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Close a connection to an open SQLite3 database.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLite_Close (
        SQLITE_DATA     *this
    );


    ERESULT         SQLite_Enable (
        SQLITE_DATA     *this
    );

   
    /*!
     Execute an SQL Statement.
     @param     this        object pointer
     @param     pCallback   optional callback address
     @param     pParm1      optional 1st parameter pass to callback
     @param     pSqlA       sql statement
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLite_Exec (
        SQLITE_DATA     *this,
        int             (*pCallback)(void*, int, char**, char**),
        void            *pParm1,
        const
        char            *pSqlA
    );

    ERESULT         SQLite_ExecPrint (
        SQLITE_DATA     *this,
        int             (*pCallback)(void*, int, char**, char**),
        void            *pParm1,
        const
        char            *pFormatA,
        ...
    );


    SQLITE_DATA *   SQLite_Init (
        SQLITE_DATA     *this
    );


    /*!
     Open/create an SQLite3 database file and create a connection to it.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLite_Open (
        SQLITE_DATA     *this,
        PATH_DATA       *pPath
    );
    
 
    /*!
     Get an array of the permanent table names in this database.
     @param     this    object pointer
     @return    if successful, an array of table names.  Otherwise,
                OBJ_NIL.
     */
    ASTRCARRAY_DATA * SQLite_TableNames (
        SQLITE_DATA     *this
    );


#ifdef  SQLITE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SQLite_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SQLite_ToJson (
        SQLITE_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SQLite_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SQLite_ToDebugString (
        SQLITE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SQLITE_H */

