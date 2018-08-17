// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          U32MATRIX Console Transmit Task (u32Matrix) Header
//****************************************************************
/*
 * Program
 *			Separate u32Matrix (u32Matrix)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate u32Matrix to run things without complications
 *          of interfering with the main u32Matrix. A u32Matrix may be 
 *          called a u32Matrix on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	08/12/2018 Generated
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


#ifndef         U32MATRIX_H
#define         U32MATRIX_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct u32Matrix_data_s	U32MATRIX_DATA;    // Inherits from OBJ.

    typedef struct u32Matrix_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in u32Matrix_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(U32MATRIX_DATA *);
    } U32MATRIX_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to u32Matrix object if successful, otherwise OBJ_NIL.
     */
    U32MATRIX_DATA * u32Matrix_Alloc(
        void
    );
    
    
    OBJ_ID          u32Matrix_Class(
        void
    );
    
    
    U32MATRIX_DATA * u32Matrix_New(
        uint32_t        ySize,
        uint32_t        xSize
    );
    
    
    U32MATRIX_DATA * u32Matrix_NewIdentity(
        uint32_t        xSize
    );
    
    
    U32MATRIX_DATA * u32Matrix_NewSquare(
        uint32_t        xSize
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        u32Matrix_getXSize(
        U32MATRIX_DATA  *this
    );
    
    
    uint32_t        u32Matrix_getYSize(
        U32MATRIX_DATA  *this
    );
    
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    uint32_t        u32Matrix_Get(
        U32MATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x
    );

   
    U32MATRIX_DATA * u32Matrix_Init(
        U32MATRIX_DATA  *this,
        uint32_t        ySize,
        uint32_t        xSize
    );


    ERESULT         u32Matrix_Set(
        U32MATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        uint16_t        value
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = u32Matrix_ToDebugString(this,4);
     @endcode 
     @param     this    U32MATRIX object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    u32Matrix_ToDebugString(
        U32MATRIX_DATA  *this,
        int             indent
    );
    
    
    /*!
     Set all elements of the matrix to zero.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         u32Matrix_Zero(
        U32MATRIX_DATA *this
    );

    
#ifdef	__cplusplus
}
#endif

#endif	/* U32MATRIX_H */

