// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  SQL Table Support (SqlTbl) Header
//****************************************************************
/*
 * Program
 *          SQL Table Support (SqlTbl)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate SqlTbl to run things without complications
 *          of interfering with the main SqlTbl. A SqlTbl may be 
 *          called a SqlTbl on other O/S's.
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


#ifndef         SQLTBL_H
#define         SQLTBL_H


//#define   SQLTBL_IS_IMMUTABLE     1
#define   SQLTBL_JSON_SUPPORT       1
//#define   SQLTBL_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SqlTbl_data_s  SQLTBL_DATA;            // Inherits from OBJ
    typedef struct SqlTbl_class_data_s SQLTBL_CLASS_DATA;   // Inherits from OBJ

    typedef struct SqlTbl_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlTbl_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLTBL_DATA *);
    } SQLTBL_VTBL;

    typedef struct SqlTbl_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlTbl_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLTBL_DATA *);
    } SQLTBL_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SQLTBL_SINGLETON
    SQLTBL_DATA *     SqlTbl_Shared (
        void
    );

    void            SqlTbl_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SqlTbl object if successful, otherwise OBJ_NIL.
     */
    SQLTBL_DATA *     SqlTbl_Alloc (
        void
    );
    
    
    OBJ_ID          SqlTbl_Class (
        void
    );
    
    
    SQLTBL_DATA *     SqlTbl_New (
        void
    );
    
    
#ifdef  SQLTBL_JSON_SUPPORT
    SQLTBL_DATA *   SqlTbl_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SQLTBL_DATA *   SqlTbl_NewFromJsonStringA (
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

    ERESULT     SqlTbl_Disable (
        SQLTBL_DATA       *this
    );


    ERESULT     SqlTbl_Enable (
        SQLTBL_DATA       *this
    );

   
    SQLTBL_DATA *   SqlTbl_Init (
        SQLTBL_DATA     *this
    );


    ERESULT     SqlTbl_IsEnabled (
        SQLTBL_DATA       *this
    );
    
 
#ifdef  SQLTBL_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SqlTbl_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlTbl_ToJson (
        SQLTBL_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SqlTbl_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlTbl_ToDebugString (
        SQLTBL_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SQLTBL_H */

