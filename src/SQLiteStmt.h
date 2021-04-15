// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  SQLiteStmt (SQLiteStmt) Header
//****************************************************************
/*
 * Program
 *          SQLite Statement (SQLiteStmt)
 * Purpose
 *          SQLite via its prep interface stores the statement
 *          internally. The common method of executing sql is
 *          to create the statement via prep(), bind data to it,
 *          execute it via step() and gather the results via a
 *          multitude of row functions which return the column data.
 *
 *          Error checking must be done at each level within the
 *          execution transitions and appropriate actions taken
 *          before moving to the next phase or terminating.
 * Remarks
 *  1.      None
 *
 * References
 *  -   "Using SQLite", Jay Kreibich, 2010, O'Reilly Media
 *  -   "The Definitive Guide to SQLite, Second Eidtion",
 *      Grant Owens and Mike Owens, 2010, Apress
 *
 * History
 *  10/23/2020 Generated
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
#include        <SQLite.h>


#ifndef         SQLITESTMT_H
#define         SQLITESTMT_H


//#define   SQLITESTMT_IS_IMMUTABLE     1
//#define   SQLITESTMT_JSON_SUPPORT     1
//#define   SQLITESTMT_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SQLiteStmt_data_s  SQLITESTMT_DATA;            // Inherits from OBJ
    typedef struct SQLiteStmt_class_data_s SQLITESTMT_CLASS_DATA;   // Inherits from OBJ

    typedef struct SQLiteStmt_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SQLiteStmt_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLITESTMT_DATA *);
    } SQLITESTMT_VTBL;

    typedef struct SQLiteStmt_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SQLiteStmt_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLITESTMT_DATA *);
    } SQLITESTMT_CLASS_VTBL;


    enum SQLITESTMT_STATE {
        SQLITESTMT_STATE_INITIAL=0,
        SQLITESTMT_STATE_PREPARED,
        SQLITESTMT_STATE_ROW,
        SQLITESTMT_STATE_DONE
    };

    /*      State Description

            INITIAL
              |
              V
            prep()
              | <---------------+<-----+
              |                 ^      ^
              V                 |      |
           PREPARED  -> bind() -+      |
              |                        |
              | <--------------------+ |
              V                      | |
            step() -> ROW -> row() ->+ |
              +-------> reset() ------>+
              |                        ^
              V                        |
             DONE -> reset() ----------+
              |
              V
            finalize()
     */




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SQLITESTMT_SINGLETON
    SQLITESTMT_DATA * SQLiteStmt_Shared (
        void
    );

    void            SQLiteStmt_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SQLiteStmt object if successful, otherwise OBJ_NIL.
     */
    SQLITESTMT_DATA * SQLiteStmt_Alloc (
        void
    );
    
    
    OBJ_ID          SQLiteStmt_Class (
        void
    );
    
    
    SQLITESTMT_DATA * SQLiteStmt_New (
        void
    );
    
    
    SQLITESTMT_DATA * SQLiteStmt_NewStmt (
        SQLITE_DATA     *pDB,
        ASTR_DATA       *pStmt
    );


#ifdef  SQLITESTMT_JSON_SUPPORT
    SQLITESTMT_DATA * SQLiteStmt_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SQLITESTMT_DATA * SQLiteStmt_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    SQLITE_DATA *   SQLiteStmt_getDB (
        SQLITESTMT_DATA *this
    );


    /*! See SQLSTMT_STATE enum above.
     */
    uint32_t        SQLiteStmt_getState (
        SQLITESTMT_DATA *this
    );


    ASTR_DATA *     SQLiteStmt_getStmt (
        SQLITESTMT_DATA *this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Finalize a prepared statement releasing any internal memory resources
     and deallocates any memory. Once finalized, the statement cannot be
     reused, it must go through the preparation stage again.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLiteStmt_Finalize (
        SQLITESTMT_DATA *this
    );


    ERESULT         SQLiteStmt_Enable (
        SQLITESTMT_DATA *this
    );

   
    SQLITESTMT_DATA * SQLiteStmt_Init (
        SQLITESTMT_DATA *this
    );


    /*!
     Reset a prepared statement making it available for further
     execution.  This should follow Step().
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLiteStmt_Reset (
        SQLITESTMT_DATA *this
    );


    ERESULT         SQLiteStmt_Setup (
        SQLITESTMT_DATA *this,
        SQLITE_DATA     *pDB,
        ASTR_DATA       *pStmt
    );


    /*!
     Execute a prepared statement.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS or ERESULT_SUCCESS_PARTIAL_DATA.
                Otherwise, an ERESULT_* error code.
     */
    ERESULT         SQLiteStmt_Step (
        SQLITESTMT_DATA *this
    );


#ifdef  SQLITESTMT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SQLiteStmt_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SQLiteStmt_ToJson (
        SQLITESTMT_DATA *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SQLiteStmt_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SQLiteStmt_ToDebugString (
        SQLITESTMT_DATA *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SQLITESTMT_H */

