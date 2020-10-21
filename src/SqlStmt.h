// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  SQL Statement (SqlStmt) Header
//****************************************************************
/*
 * Program
 *          SQL Statement (SqlStmt)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate SqlStmt to run things without complications
 *          of interfering with the main SqlStmt. A SqlStmt may be 
 *          called a SqlStmt on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  10/20/2020 Generated
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


#ifndef         SQLSTMT_H
#define         SQLSTMT_H


//#define   SQLSTMT_IS_IMMUTABLE     1
//#define   SQLSTMT_JSON_SUPPORT     1
//#define   SQLSTMT_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SqlStmt_data_s  SQLSTMT_DATA;            // Inherits from OBJ
    typedef struct SqlStmt_class_data_s SQLSTMT_CLASS_DATA;   // Inherits from OBJ

    typedef struct SqlStmt_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlStmt_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLSTMT_DATA *);
    } SQLSTMT_VTBL;

    typedef struct SqlStmt_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlStmt_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLSTMT_DATA *);
    } SQLSTMT_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SQLSTMT_SINGLETON
    SQLSTMT_DATA *  SqlStmt_Shared (
        void
    );

    void            SqlStmt_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SqlStmt object if successful, otherwise OBJ_NIL.
     */
    SQLSTMT_DATA *  SqlStmt_Alloc (
        void
    );
    
    
    OBJ_ID          SqlStmt_Class (
        void
    );
    
    
    SQLSTMT_DATA *  SqlStmt_New (
        void
    );
    
    
    SQLSTMT_DATA *  SqlStmt_NewStmt (
        SQLITE_DATA     *pDB,
        ASTR_DATA       *pStmt
    );
    
    
#ifdef  SQLSTMT_JSON_SUPPORT
    SQLSTMT_DATA *  SqlStmt_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SQLSTMT_DATA *  SqlStmt_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    SQLITE_DATA *   SqlStmt_getDB (
        SQLSTMT_DATA    *this
    );

    bool            SqlStmt_setDB (
        SQLSTMT_DATA    *this,
        SQLITE_DATA     *pValue
    );


    ASTR_DATA *     SqlStmt_getStmt (
        SQLSTMT_DATA    *this
    );
    
    bool            SqlStmt_setStmt (
        SQLSTMT_DATA    *this,
        ASTR_DATA       *pValue
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     SqlStmt_Enable (
        SQLSTMT_DATA       *this
    );

   
    SQLSTMT_DATA *   SqlStmt_Init (
        SQLSTMT_DATA     *this
    );


    ERESULT         SqlStmt_Setup (
        SQLSTMT_DATA    *this,
        SQLITE_DATA     *pDB,
        ASTR_DATA       *pStmt
    );


#ifdef  SQLSTMT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SqlStmt_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlStmt_ToJson (
        SQLSTMT_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SqlStmt_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlStmt_ToDebugString (
        SQLSTMT_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SQLSTMT_H */

