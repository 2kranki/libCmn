// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          BITMATRIX Console Transmit Task (bitMatrix) Header
//****************************************************************
/*
 * Program
 *			Separate bitMatrix (bitMatrix)
 * Purpose
 *			This object provides a standardized way of handling
 *          a Bit Matrix. There is one bit per (x,y) address that
 *          can be 1 or 0.  Usually, the x-axis is horizontal and
 *          the y-axis is vertical.  The upper left-hand corner is
 *          (0,0).
 *
 * Remarks
 *	1.      None
 *
 * History
 *	07/21/2015  Generated
 *	08/12/2018  Generated again and source merged from old bitMatrix.
 *  08/12/2018  Changed matrix to be dynamically allocated instead
 *              of being an extension of the object which limited
 *              its size to less than 64k.
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
#include        <bitSet.h>
#include        <u16Matrix.h>


#ifndef         BITMATRIX_H
#define         BITMATRIX_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct bitMatrix_data_s	BITMATRIX_DATA;    // Inherits from OBJ.

    typedef struct bitMatrix_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bitMatrix_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BITMATRIX_DATA *);
    } BITMATRIX_VTBL;



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
     @return    pointer to bitMatrix object if successful, otherwise OBJ_NIL.
     */
    BITMATRIX_DATA * bitMatrix_Alloc(
        void
    );
    
    
    OBJ_ID          bitMatrix_Class(
        void
    );
    
    
    BITMATRIX_DATA * bitMatrix_New(
        uint32_t        ySize,
        uint32_t        xSize
    );
    
    
    BITMATRIX_DATA * bitMatrix_NewFromJSONString(
        ASTR_DATA       *pString
    );
    
    
    BITMATRIX_DATA * bitMatrix_NewFromJSONStringA(
        const
        char            *pString
    );
    
    
    /*!
     Create a new identity matrix of the given size.  The matrix must be
     square (ie xSize == ySize).
     @param     xSize   x-axis and y-axis size in bits
     @return    If successful, an Identity Matrix.  Otherwise, OBJ_NIL.
     */
    BITMATRIX_DATA * bitMatrix_NewIdentity(
        uint32_t        xSize
    );
    
    
    BITMATRIX_DATA * bitMatrix_NewSquare(
        uint32_t        xSize
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        bitMatrix_getXSize(
        BITMATRIX_DATA  *this
    );
    
    
    uint32_t        bitMatrix_getYSize(
        BITMATRIX_DATA  *this
    );
    
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         bitMatrix_Assign(
        BITMATRIX_DATA	*this,
        BITMATRIX_DATA	*pOther
    );
    
    
    BITMATRIX_DATA * bitMatrix_Copy(
        BITMATRIX_DATA	*this
    );
    
    
    /*!
     Zero all elements of the matrix.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         bitMatrix_Empty(
        BITMATRIX_DATA	*this
    );


    ERESULT         bitMatrix_Get(
        BITMATRIX_DATA	*this,
        uint32_t        y,
        uint32_t        x
    );
    
    
    BITSET_DATA *   bitMatrix_GetColumn(
        BITMATRIX_DATA	*this,
        uint32_t        y,
        uint32_t        x,
        uint32_t        len
    );
    
    
    BITSET_DATA *   bitMatrix_GetRow(
        BITMATRIX_DATA	*this,
        uint32_t        y,
        uint32_t        x,
        uint32_t        len
    );
    
    
    /*!
     Increase the size of the matrix in the x-axis by the amount
     of bits given.
     @param     this    object pointer
     @param     amt     number of bits to increase by
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         bitMatrix_InflateX(
        BITMATRIX_DATA  *this,
        uint32_t        amt
    );
    
    
    /*!
     Increase the size of the matrix in the y-axis by the amount
     of bits given.
     @param     this    object pointer
     @param     amt     number of bits to increase by
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         bitMatrix_InflateY(
        BITMATRIX_DATA  *this,
        uint32_t        amt
    );
    
    
    BITMATRIX_DATA * bitMatrix_Init(
        BITMATRIX_DATA  *this,
        uint32_t        ySize,
        uint32_t        xSize
    );


    ERESULT         bitMatrix_Intersect(
        BITMATRIX_DATA	*this,
        BITMATRIX_DATA	*pOther
    );
    
    
    ERESULT         bitMatrix_Invert(
        BITMATRIX_DATA	*this
    );
    
    
    /*!
     Check the matrix to see if it is empty.
     @param     this    object pointer
     @return    If empty, ERESULT_SUCCESS_TRUE.  If not empty,
                ERESULT_FAILURE_FALSE.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         bitMatrix_IsEmpty(
        BITMATRIX_DATA	*this
    );
    
    
    // Matrix(Product) = Matrix(this) X Matrix(pOther)
    // (Must be N X N matrices and all the same size!)
    /*!
     Create a new matrix which is the product of the two given
     matrices.  The matrices must be N X N matrices and all
     the same size.
     @param     this    object pointer
     @param     pOther  object pointer
     @return    If successful, a new product matrix.  Otherwise,
                an ERESULT_* error code.
     */
    BITMATRIX_DATA * bitMatrix_Product(
        BITMATRIX_DATA	*this,
        BITMATRIX_DATA	*pOther
    );
    
    
    ERESULT         bitMatrix_ReflectiveTransitiveClosure(
        BITMATRIX_DATA	*this
    );
    
    
    ERESULT         bitMatrix_Set(
        BITMATRIX_DATA	*this,
        uint32_t        y,
        uint32_t        x,
        bool            value
    );

    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = bitMatrix_ToDebugString(this,4);
     @endcode 
     @param     this    BITMATRIX object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     bitMatrix_ToDebugString(
        BITMATRIX_DATA  *this,
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
    
    
    /*!
     Zero all elements of the matrix.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         bitMatrix_Zero(
        BITMATRIX_DATA  *this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BITMATRIX_H */

