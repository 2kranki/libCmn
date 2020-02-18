// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Unsigned 16-Bit Matrix (U16Matrix) Header
//****************************************************************
/*
 * Program
 *			Unsigned 16-Bit Matrix (U16Matrix)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate U16Matrix to run things without complications
 *          of interfering with the main U16Matrix. A U16Matrix may be 
 *          called a U16Matrix on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/18/2020 Generated
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


#ifndef         U16MATRIX_H
#define         U16MATRIX_H


//#define   U16MATRIX_IS_IMMUTABLE     1
#define   U16MATRIX_JSON_SUPPORT     1
//#define   U16MATRIX_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct U16Matrix_data_s	U16MATRIX_DATA;            // Inherits from OBJ
    typedef struct U16Matrix_class_data_s U16MATRIX_CLASS_DATA;   // Inherits from OBJ

    typedef struct U16Matrix_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in U16Matrix_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(U16MATRIX_DATA *);
    } U16MATRIX_VTBL;

    typedef struct U16Matrix_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in U16Matrix_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(U16MATRIX_DATA *);
    } U16MATRIX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  U16MATRIX_SINGLETON
    U16MATRIX_DATA *     U16Matrix_Shared (
        void
    );

    void            U16Matrix_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to U16Matrix object if successful, otherwise OBJ_NIL.
     */
    U16MATRIX_DATA *     U16Matrix_Alloc (
        void
    );
    
    
    OBJ_ID          U16Matrix_Class (
        void
    );
    
    
    U16MATRIX_DATA *     U16Matrix_New (
        void
    );
    
    
#ifdef  U16MATRIX_JSON_SUPPORT
    U16MATRIX_DATA *   U16Matrix_NewFromJsonString (
        ASTR_DATA       *pString
    );

    U16MATRIX_DATA *   U16Matrix_NewFromJsonStringA (
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

    ERESULT     U16Matrix_Disable (
        U16MATRIX_DATA		*this
    );


    ERESULT     U16Matrix_Enable (
        U16MATRIX_DATA		*this
    );

   
    U16MATRIX_DATA *   U16Matrix_Init (
        U16MATRIX_DATA     *this
    );


    ERESULT     U16Matrix_IsEnabled (
        U16MATRIX_DATA		*this
    );
    
 
#ifdef  U16MATRIX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = U16Matrix_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     U16Matrix_ToJson (
        U16MATRIX_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = U16Matrix_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    U16Matrix_ToDebugString (
        U16MATRIX_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* U16MATRIX_H */

