// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Bit Matrix (bitMatrix) Header
//****************************************************************
/*
 * Program
 *			Bit Matrix (bitMatrix)
 * Purpose
 *			This object provides a standardized way of handling
 *          a Bit Matrix.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	07/21/2015 Generated
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
#include        <bitSet.h>
#include        <AStr.h>
#include        <u16Matrix.h>


#ifndef         BITMATRIX_H
#define         BITMATRIX_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct bitMatrix_data_s	BITMATRIX_DATA;

    typedef struct bitMatrix_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        // Methods:
    } BITMATRIX_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    BITMATRIX_DATA * bitMatrix_Alloc(
        uint16_t        x,
        uint16_t        y
    );
    
    
    OBJ_ID          bitMatrix_Class(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     bitMatrix_getLastError(
        BITMATRIX_DATA	*this
    );
    
    
    uint16_t        bitMatrix_getXMax(
        BITMATRIX_DATA  *this
    );
    
    
    uint16_t        bitMatrix_getYMax(
        BITMATRIX_DATA  *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    // cbp <- pOther
    ERESULT         bitMatrix_Assign(
        BITMATRIX_DATA	*this,
        BITMATRIX_DATA	*pOther
    );
    
    
    BITMATRIX_DATA * bitMatrix_Copy(
        BITMATRIX_DATA	*this
    );
    
    
    ERESULT         bitMatrix_Empty(
        BITMATRIX_DATA	*this
    );


    ERESULT         bitMatrix_Get(
        BITMATRIX_DATA	*this,
        uint16_t        x,
        uint16_t        y
    );
    
    
    BITSET_DATA *   bitMatrix_GetColumn(
        BITMATRIX_DATA	*this,
        uint16_t        x,
        uint16_t        y,
        uint16_t        len
    );
    
    
    BITSET_DATA *   bitMatrix_GetRow(
        BITMATRIX_DATA	*this,
        uint16_t        x,
        uint16_t        y,
        uint16_t        len
    );
    
    
    BITMATRIX_DATA * bitMatrix_Init(
        BITMATRIX_DATA  *this
    );


    ERESULT         bitMatrix_Intersect(
        BITMATRIX_DATA	*this,
        BITMATRIX_DATA	*pOther
    );
    
    
    ERESULT         bitMatrix_Invert(
        BITMATRIX_DATA	*this
    );
    
    
    ERESULT         bitMatrix_IsEmpty(
        BITMATRIX_DATA	*this
    );
    
    
    // Matrix(Product) = Matrix(cbp) X Matrix(pOther)
    // (Must be N X N matrices and all the same size!)
    BITMATRIX_DATA * bitMatrix_Product(
        BITMATRIX_DATA	*this,
        BITMATRIX_DATA	*pOther
    );
    
    
    ERESULT         bitMatrix_ReflectiveTransitiveClosure(
        BITMATRIX_DATA	*this
    );
    
    
    ERESULT         bitMatrix_Set(
        BITMATRIX_DATA	*this,
        uint16_t        x,
        uint16_t        y,
        bool            value
    );

    
    ASTR_DATA *     bitMatrix_ToDebugString(
        BITMATRIX_DATA	*this,
        int             indent
    );
    
    
    U16MATRIX_DATA * bitMatrix_ToU16Matrix(
        BITMATRIX_DATA	*this
    );
    
    
    ERESULT         bitMatrix_TransitiveClosure(
        BITMATRIX_DATA	*this
    );
    
    
    ERESULT         bitMatrix_Union(
        BITMATRIX_DATA	*this,
        BITMATRIX_DATA	*pOther
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* BITMATRIX_H */

