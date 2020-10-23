// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  SQLiteCurs (SQLiteCurs) Header
//****************************************************************
/*
 * Program
 *          SQLiteCurs (SQLiteCurs)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate SQLiteCurs to run things without complications
 *          of interfering with the main SQLiteCurs. A SQLiteCurs may be 
 *          called a SQLiteCurs on other O/S's.
 *
 * Remarks
 *  1.      None
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


#ifndef         SQLITECURS_H
#define         SQLITECURS_H


//#define   SQLITECURS_IS_IMMUTABLE     1
//#define   SQLITECURS_JSON_SUPPORT     1
//#define   SQLITECURS_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SQLiteCurs_data_s  SQLITECURS_DATA;            // Inherits from OBJ
    typedef struct SQLiteCurs_class_data_s SQLITECURS_CLASS_DATA;   // Inherits from OBJ

    typedef struct SQLiteCurs_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SQLiteCurs_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLITECURS_DATA *);
    } SQLITECURS_VTBL;

    typedef struct SQLiteCurs_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SQLiteCurs_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLITECURS_DATA *);
    } SQLITECURS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SQLITECURS_SINGLETON
    SQLITECURS_DATA *     SQLiteCurs_Shared (
        void
    );

    void            SQLiteCurs_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SQLiteCurs object if successful, otherwise OBJ_NIL.
     */
    SQLITECURS_DATA *     SQLiteCurs_Alloc (
        void
    );
    
    
    OBJ_ID          SQLiteCurs_Class (
        void
    );
    
    
    SQLITECURS_DATA *     SQLiteCurs_New (
        void
    );
    
    
#ifdef  SQLITECURS_JSON_SUPPORT
    SQLITECURS_DATA *   SQLiteCurs_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SQLITECURS_DATA *   SQLiteCurs_NewFromJsonStringA (
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

    ERESULT     SQLiteCurs_Disable (
        SQLITECURS_DATA       *this
    );


    ERESULT     SQLiteCurs_Enable (
        SQLITECURS_DATA       *this
    );

   
    SQLITECURS_DATA *   SQLiteCurs_Init (
        SQLITECURS_DATA     *this
    );


    ERESULT     SQLiteCurs_IsEnabled (
        SQLITECURS_DATA       *this
    );
    
 
#ifdef  SQLITECURS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SQLiteCurs_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SQLiteCurs_ToJson (
        SQLITECURS_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SQLiteCurs_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SQLiteCurs_ToDebugString (
        SQLITECURS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SQLITECURS_H */

