// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  SqlCurs (SqlCurs) Header
//****************************************************************
/*
 * Program
 *          SqlCurs (SqlCurs)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate SqlCurs to run things without complications
 *          of interfering with the main SqlCurs. A SqlCurs may be 
 *          called a SqlCurs on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  10/11/2020 Generated
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


#ifndef         SQLCURS_H
#define         SQLCURS_H


//#define   SQLCURS_IS_IMMUTABLE     1
#define   SQLCURS_JSON_SUPPORT       1
//#define   SQLCURS_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SqlCurs_data_s  SQLCURS_DATA;            // Inherits from OBJ
    typedef struct SqlCurs_class_data_s SQLCURS_CLASS_DATA;   // Inherits from OBJ

    typedef struct SqlCurs_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlCurs_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLCURS_DATA *);
    } SQLCURS_VTBL;

    typedef struct SqlCurs_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlCurs_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLCURS_DATA *);
    } SQLCURS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SQLCURS_SINGLETON
    SQLCURS_DATA *     SqlCurs_Shared (
        void
    );

    void            SqlCurs_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SqlCurs object if successful, otherwise OBJ_NIL.
     */
    SQLCURS_DATA *     SqlCurs_Alloc (
        void
    );
    
    
    OBJ_ID          SqlCurs_Class (
        void
    );
    
    
    SQLCURS_DATA *     SqlCurs_New (
        void
    );
    
    
#ifdef  SQLCURS_JSON_SUPPORT
    SQLCURS_DATA *   SqlCurs_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SQLCURS_DATA *   SqlCurs_NewFromJsonStringA (
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

    ERESULT     SqlCurs_Disable (
        SQLCURS_DATA       *this
    );


    ERESULT     SqlCurs_Enable (
        SQLCURS_DATA       *this
    );

   
    SQLCURS_DATA *   SqlCurs_Init (
        SQLCURS_DATA     *this
    );


    ERESULT     SqlCurs_IsEnabled (
        SQLCURS_DATA       *this
    );
    
 
#ifdef  SQLCURS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SqlCurs_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCurs_ToJson (
        SQLCURS_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SqlCurs_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCurs_ToDebugString (
        SQLCURS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SQLCURS_H */

