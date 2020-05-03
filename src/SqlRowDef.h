// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Separate SqlRowDef (SqlRowDef) Header
//****************************************************************
/*
 * Program
 *			Separate SqlRowDef (SqlRowDef)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate SqlRowDef to run things without complications
 *          of interfering with the main SqlRowDef. A SqlRowDef may be 
 *          called a SqlRowDef on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/26/2020 Generated
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


#ifndef         SQLROWDEF_H
#define         SQLROWDEF_H


//#define   SQLROWDEF_IS_IMMUTABLE     1
#define   SQLROWDEF_JSON_SUPPORT     1
//#define   SQLROWDEF_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SqlRowDef_data_s	SQLROWDEF_DATA;            // Inherits from OBJ
    typedef struct SqlRowDef_class_data_s SQLROWDEF_CLASS_DATA;   // Inherits from OBJ

    typedef struct SqlRowDef_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlRowDef_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLROWDEF_DATA *);
    } SQLROWDEF_VTBL;

    typedef struct SqlRowDef_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlRowDef_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLROWDEF_DATA *);
    } SQLROWDEF_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SQLROWDEF_SINGLETON
    SQLROWDEF_DATA *     SqlRowDef_Shared (
        void
    );

    void            SqlRowDef_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SqlRowDef object if successful, otherwise OBJ_NIL.
     */
    SQLROWDEF_DATA *     SqlRowDef_Alloc (
        void
    );
    
    
    OBJ_ID          SqlRowDef_Class (
        void
    );
    
    
    SQLROWDEF_DATA *     SqlRowDef_New (
        void
    );
    
    
#ifdef  SQLROWDEF_JSON_SUPPORT
    SQLROWDEF_DATA *   SqlRowDef_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SQLROWDEF_DATA *   SqlRowDef_NewFromJsonStringA (
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

    ERESULT     SqlRowDef_Disable (
        SQLROWDEF_DATA		*this
    );


    ERESULT     SqlRowDef_Enable (
        SQLROWDEF_DATA		*this
    );

   
    SQLROWDEF_DATA *   SqlRowDef_Init (
        SQLROWDEF_DATA     *this
    );


    ERESULT     SqlRowDef_IsEnabled (
        SQLROWDEF_DATA		*this
    );
    
 
#ifdef  SQLROWDEF_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SqlRowDef_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlRowDef_ToJson (
        SQLROWDEF_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SqlRowDef_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlRowDef_ToDebugString (
        SQLROWDEF_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SQLROWDEF_H */

