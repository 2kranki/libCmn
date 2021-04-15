// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  SQL Column Data (SqlColData) Header
//****************************************************************
/*
 * Program
 *          SQL Column Data (SqlColData)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate SqlColData to run things without complications
 *          of interfering with the main SqlColData. A SqlColData may be 
 *          called a SqlColData on other O/S's.
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
#include        <Value.h>


#ifndef         SQLCOLDATA_H
#define         SQLCOLDATA_H


//#define   SQLCOLDATA_IS_IMMUTABLE     1
#define   SQLCOLDATA_JSON_SUPPORT       1
//#define   SQLCOLDATA_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SqlColData_data_s  SQLCOLDATA_DATA;            // Inherits from OBJ
    typedef struct SqlColData_class_data_s SQLCOLDATA_CLASS_DATA;   // Inherits from OBJ

    typedef struct SqlColData_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlColData_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLCOLDATA_DATA *);
    } SQLCOLDATA_VTBL;

    typedef struct SqlColData_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlColData_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLCOLDATA_DATA *);
    } SQLCOLDATA_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SQLCOLDATA_SINGLETON
    SQLCOLDATA_DATA * SqlColData_Shared (
        void
    );

    void            SqlColData_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SqlColData object if successful, otherwise OBJ_NIL.
     */
    SQLCOLDATA_DATA * SqlColData_Alloc (
        void
    );
    
    
    OBJ_ID          SqlColData_Class (
        void
    );
    
    
    SQLCOLDATA_DATA * SqlColData_New (
        void
    );
    
    
#ifdef  SQLCOLDATA_JSON_SUPPORT
    SQLCOLDATA_DATA * SqlColData_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SQLCOLDATA_DATA * SqlColData_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    SQLCOL_DATA *   SqlColData_getCol (
        SQLCOLDATA_DATA *this
    );

    bool            SqlColData_setCol (
        SQLCOLDATA_DATA *this,
        SQLCOL_DATA     *pValue
    );


    VALUE_DATA *    SqlColData_getValue (
        SQLCOLDATA_DATA *this
    );

    bool            SqlColData_setValue (
        SQLCOLDATA_DATA *this,
        VALUE_DATA      *pValue
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         SqlColData_Disable (
        SQLCOLDATA_DATA *this
    );


    ERESULT         SqlColData_Enable (
        SQLCOLDATA_DATA *this
    );

   
    SQLCOLDATA_DATA * SqlColData_Init (
        SQLCOLDATA_DATA *this
    );


    ERESULT         SqlColData_IsEnabled (
        SQLCOLDATA_DATA *this
    );
    
 
#ifdef  SQLCOLDATA_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SqlColData_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlColData_ToJson (
        SQLCOLDATA_DATA *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SqlColData_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlColData_ToDebugString (
        SQLCOLDATA_DATA *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SQLCOLDATA_H */

