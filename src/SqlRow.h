// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  SQL Row Support (SqlRow) Header
//****************************************************************
/*
 * Program
 *          SQL Row Support (SqlRow)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate SqlRow to run things without complications
 *          of interfering with the main SqlRow. A SqlRow may be 
 *          called a SqlRow on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  04/14/2021 Generated
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
#include        <SqlCol.h>
#include        <SqlColData.h>


#ifndef         SQLROW_H
#define         SQLROW_H


//#define   SQLROW_IS_IMMUTABLE     1
#define   SQLROW_JSON_SUPPORT       1
//#define   SQLROW_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SqlRow_data_s  SQLROW_DATA;            // Inherits from OBJ
    typedef struct SqlRow_class_data_s SQLROW_CLASS_DATA;   // Inherits from OBJ

    typedef struct SqlRow_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlRow_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLROW_DATA *);
    } SQLROW_VTBL;

    typedef struct SqlRow_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlRow_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLROW_DATA *);
    } SQLROW_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SQLROW_SINGLETON
    SQLROW_DATA *   SqlRow_Shared (
        void
    );

    void            SqlRow_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SqlRow object if successful, otherwise OBJ_NIL.
     */
    SQLROW_DATA *  SqlRow_Alloc (
        void
    );
    
    
    OBJ_ID         SqlRow_Class (
        void
    );
    
    
    SQLROW_DATA *  SqlRow_New (
        void
    );
    
    
    /*!
     Setup columns from Column Structs.
     @param     num         number of structs in array
     @param     pStructs    column struct array pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    SQLROW_DATA *  SqlRow_NewFromColumnStructs (
        int             num,
        SQLCOL_STRUCT   *pStructs
    );


#ifdef  SQLROW_JSON_SUPPORT
    SQLROW_DATA *   SqlRow_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SQLROW_DATA *   SqlRow_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        SqlRow_getSize (
        SQLROW_DATA       *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given column to the end of the row array.
     @param     this    object pointer
     @param     pCol    Column pointer
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         SqlRow_AppendCol (
        SQLROW_DATA     *this,
        SQLCOL_DATA     *pCol
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = SqlRow_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another SQLROW object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         SqlRow_Assign (
        SQLROW_DATA     *this,
        SQLROW_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        SqlRow      *pCopy = SqlRow_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a SQLROW object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SQLROW_DATA *     SqlRow_Copy (
        SQLROW_DATA       *this
    );


    /*!
     Remove the index'th column from the row array and return it.
     @param     this    object pointer
     @param     index   column array index
     @return    If successful, an column pointer, otherwise OBJ_NIL.
     @warning   Remember to release the returned column object.
     */
    SQLCOL_DATA *   SqlRow_Delete (
        SQLROW_DATA     *this,
        uint32_t        index
    );


    /*!
     Find the column object for the given name.
     @param     this    object pointer
     @param     pNameA  column name
     @return    If successful, an column object pointer, otherwise OBJ_NIL.
                The returned column object should not be released.
     */
    SQLCOL_DATA *   SqlRow_FindNameA (
        SQLROW_DATA     *this,
        const
        char            *pNameA
    );


    /*!
     Find the index'th column in the row array.
     @param     this    object pointer
     @param     index   column array index
     @return    If successful, an columnobject pointer, otherwise OBJ_NIL.
                The returned column object should not be released.
     */
    SQLCOL_DATA *   SqlRow_Get (
        SQLROW_DATA     *this,
        uint32_t        index
    );


    SQLROW_DATA *   SqlRow_Init (
        SQLROW_DATA     *this
    );


    ERESULT         SqlRow_IsEnabled (
        SQLROW_DATA     *this
    );
    
 
    /*!
     Setup columns from Column Structs.
     @param     this        object pointer
     @param     num         number of structs in array
     @param     pStructs    column struct array pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SqlRow_SetupFromColumnStructs (
        SQLROW_DATA     *this,
        int             num,
        const
        SQLCOL_STRUCT   *pStructs
    );


    /*!
     Sort Column array by column name.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SqlRow_SortAscending (
        SQLROW_DATA     *this
    );


#ifdef  SQLROW_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SqlRow_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlRow_ToJson (
        SQLROW_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SqlRow_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlRow_ToDebugString (
        SQLROW_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SQLROW_H */

