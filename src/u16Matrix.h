// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          U16MATRIX Console Transmit Task (u16Matrix) Header
//****************************************************************
/*
 * Program
 *				Separate u16Matrix (u16Matrix)
 * Purpose
 *				This object provides a standardized way of handling
 *              a separate u16Matrix to run things without complications
 *              of interfering with the main u16Matrix. A u16Matrix may be 
 *              called a u16Matrix on other O/S's.
 *
 * Remarks
 *	1.      A matrix of M X N size has M rows (height) and N columns (width).
 *          (i,j) is used to access each element of the matrix. Rules, 1 <= i <= M
 *          and 1 <= j <= N, must hold true. If M == N then we have a square
 *          matrix. Initial matrices are always zeroed or nulled. As in
 *          mathematics, we assume that the upper-left corner is (1,1) and
 *          as i increases we are going downwards and as j increases we are
 *          going towards the right.
 *  2.      Dragon book is "Compiler Principles, Techniques, and Tools" by
 *          Alfred Aho, Ravi Sethi and Jeffrey Ullman. The compressed table
 *          technique is derived from the end of the Lexical Analysis chapter.
 *
 * History
 *	07/30/2015 Generated.
 *  12/18/2016 Corrected M X N definitions as well as element access. Added
 *              scalar addition and multiplication plus inner product.
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



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct u16Matrix_data_s	U16MATRIX_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    U16MATRIX_DATA * u16Matrix_Alloc(
        void
    );
    
    
    U16MATRIX_DATA * u16Matrix_New(
        uint32_t        m,              // Height (Number of Rows, i)
        uint32_t        n               // Width (Number of Columns, j)
    );
    
    
    // Returns an N X N Identity Matrix.
    U16MATRIX_DATA * u16Matrix_NewIdentity(
        uint32_t        n
    );
    
    
    // Returns an N X N Zeroed Matrix.
    U16MATRIX_DATA * u16Matrix_NewSquare(
        uint32_t        n
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         u16Matrix_getLastError(
        U16MATRIX_DATA  *this
    );
    
    
    uint32_t        u16Matrix_getM(
        U16MATRIX_DATA  *this
    );
    
    
    uint32_t        u16Matrix_getN(
        U16MATRIX_DATA  *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    // this = this + pOther (both must be the same n X m).
    ERESULT         u16Matrix_Add(
        U16MATRIX_DATA	*this,
        U16MATRIX_DATA	*pOther
    );
    
    
    // this <- pOther
    ERESULT         u16Matrix_Assign(
        U16MATRIX_DATA	*this,
        U16MATRIX_DATA	*pOther
    );
    
    
    // CompressedTable() generates a C compilable module
    // that will search the compressed table for i, j
    // and return the value or zero if not available.
    // Compression is based on removing zero entries
    // from the table and is derived from the end of the
    // Lexical Analysis Chapter in the Dragon Book.
    
    ASTR_DATA *     u16Matrix_CompressedTable(
        U16MATRIX_DATA  *this,
        const
        char            *pPrefix        // Prefix for the Get Routine Name
    );
    
    
    U16MATRIX_DATA * u16Matrix_Copy(
        U16MATRIX_DATA	*this
    );
    
 
    uint16_t        u16Matrix_Get(
        U16MATRIX_DATA	*this,
        uint32_t        i,
        uint32_t        j
    );
    
    
    U16MATRIX_DATA * u16Matrix_Init(
        U16MATRIX_DATA  *this,
        uint32_t        m,              // Height (Number of Rows, i)
        uint32_t        n               // Width (Number of Columns, j)
    );


    /*!
     Multiply is matrix multiplication as in newMatrix = this X other
     which creates an n x p matrix where this matrix is n x m and
     other matrix is m x p. The multiplication is not commutative.
     this X other may not equal other X this.
     @param:    this    U16MATRIX_DATA object pointer
     @param:    other   U16MATRIX_DATA object pointer
     @return:   If successful, a new matrix, otherwise OBJ_NIL and
                getLastError() ERESULT_* error code
     */
    U16MATRIX_DATA *          u16Matrix_Multiply(
        U16MATRIX_DATA	*this,
        U16MATRIX_DATA	*pOther
    );
    
    
    /*!
     Scalar Addition is adding a value to each element of the array.
     @param:    this    U16MATRIX_DATA object pointer
     @param:    value   value to be added to each element
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_* error
                code
     */
    ERESULT         u16Matrix_ScalarAdd(
        U16MATRIX_DATA	*this,
        uint16_t        value
    );
    
    
    /*!
     Scalar Multiply is multipling a value to each element of the array.
     @param:    this    U16MATRIX_DATA object pointer
     @param:    value   value to be multiplied to each element
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_* error
                code
     */
    ERESULT         u16Matrix_ScalarMultiply(
        U16MATRIX_DATA	*this,
        uint16_t        value
    );
    
    
    ERESULT         u16Matrix_Set(
        U16MATRIX_DATA	*this,
        uint32_t        i,
        uint32_t        j,
        uint16_t        value
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = u16Matrix_ToDebugString(this, 4);
     @endcode:
     @param:    this    U16MATRIX_DATA object pointer
     @param:    indent  number of characters to indent every line of output, 
                        can be 0
     @return:   If successful, an AStr object which must be released containing 
                the description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     u16Matrix_ToDebugString(
        U16MATRIX_DATA	*this,
        int             indent
    );
    
    
    // Set all values to zero.
    ERESULT         u16Matrix_Zero(
        U16MATRIX_DATA	*this
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* U16MATRIX_H */

