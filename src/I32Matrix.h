// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Signed 32-Bit Matrix (I32Matrix) Header
//****************************************************************
/*
 * Program
 *			Signed 32-Bit Matrix (I32Matrix)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate I32Matrix to run things without complications
 *          of interfering with the main I32Matrix. A I32Matrix may be 
 *          called a I32Matrix on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/19/2020 Generated
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


#ifndef         I32MATRIX_H
#define         I32MATRIX_H


//#define   I32MATRIX_IS_IMMUTABLE     1
#define   I32MATRIX_JSON_SUPPORT     1
//#define   I32MATRIX_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct I32Matrix_data_s	I32MATRIX_DATA;            // Inherits from OBJ
    typedef struct I32Matrix_class_data_s I32MATRIX_CLASS_DATA;   // Inherits from OBJ

    typedef struct I32Matrix_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in I32Matrix_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(I32MATRIX_DATA *);
    } I32MATRIX_VTBL;

    typedef struct I32Matrix_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in I32Matrix_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(I32MATRIX_DATA *);
    } I32MATRIX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  I32MATRIX_SINGLETON
    I32MATRIX_DATA *     I32Matrix_Shared (
        void
    );

    void            I32Matrix_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to I32Matrix object if successful, otherwise OBJ_NIL.
     */
    I32MATRIX_DATA *     I32Matrix_Alloc (
        void
    );
    
    
    OBJ_ID          I32Matrix_Class (
        void
    );
    
    
    I32MATRIX_DATA *     I32Matrix_New (
        void
    );
    
    
#ifdef  I32MATRIX_JSON_SUPPORT
    I32MATRIX_DATA *   I32Matrix_NewFromJsonString (
        ASTR_DATA       *pString
    );

    I32MATRIX_DATA *   I32Matrix_NewFromJsonStringA (
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

    ERESULT     I32Matrix_Disable (
        I32MATRIX_DATA		*this
    );


    ERESULT     I32Matrix_Enable (
        I32MATRIX_DATA		*this
    );

   
    I32MATRIX_DATA *   I32Matrix_Init (
        I32MATRIX_DATA     *this
    );


    ERESULT     I32Matrix_IsEnabled (
        I32MATRIX_DATA		*this
    );
    
 
#ifdef  I32MATRIX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = I32Matrix_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     I32Matrix_ToJson (
        I32MATRIX_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = I32Matrix_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    I32Matrix_ToDebugString (
        I32MATRIX_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* I32MATRIX_H */

