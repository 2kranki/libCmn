// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Unsigned 16-Bit Matrix (U16Matrix) Header
//****************************************************************
/*
 * Program
 *			Unsigned 16-Bit Matrix (U16Matrix)
 * Purpose
 *			This object provides an unsigned 16-bit element Matrix.
 *
 * Remarks
 *  1.      A matrix of M X N size has Y rows (height) and X columns
 *          (width). (i,j) is used to access each element of the matrix.
 *          Rules, 1 <= i <= Y and 1 <= j <= X, must hold true. If M == N
 *          then we have a square matrix. Initial matrices are always
 *          zeroed or nulled. As in mathematics, we assume that the
 *          upper-left corner is (1,1) and as i increases we are going
 *          downwards and as j increases we are going towards the right.
 *  2.      Dragon book is "Compiler Principles, Techniques, and Tools" by
 *          Alfred Aho, Ravi Sethi and Jeffrey Ullman. The compressed table
 *          technique is derived from the end of the Lexical Analysis chapter.
 *
 * History
 *  07/30/2015 Generated.
 *  12/18/2016 Corrected M X N definitions as well as element access. Added
 *              scalar addition and multiplication plus inner product.
 *	02/18/2020 Regenerated and added JSON support.
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
    U16MATRIX_DATA * U16Matrix_Shared (
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
    U16MATRIX_DATA * U16Matrix_Alloc (
        void
    );
    
    
    OBJ_ID          U16Matrix_Class (
        void
    );
    
    
    U16MATRIX_DATA * U16Matrix_New (
        void
    );
    
    
    U16MATRIX_DATA * U16Matrix_NewWithSizes (
        uint32_t        mSize,          // Height (y-axis, Number of Rows, i)
        uint32_t        nSize           // Width (x-axis, Number of Columns, j)
    );


    // Returns an N X N Identity Matrix.
    U16MATRIX_DATA * U16Matrix_NewIdentity (
        uint32_t        nSize           // Width (x-axis, Number of Columns, j)
    );


    // Returns an N X N Zeroed Matrix.
    U16MATRIX_DATA * U16Matrix_NewSquare (
        uint32_t        nSize           // Width (x-axis, Number of Columns, j)
    );


#ifdef  U16MATRIX_JSON_SUPPORT
    U16MATRIX_DATA * U16Matrix_NewFromJsonString (
        ASTR_DATA       *pString
    );

    U16MATRIX_DATA * U16Matrix_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        U16Matrix_getM (
        U16MATRIX_DATA  *this
    );


    uint32_t        U16Matrix_getN (
        U16MATRIX_DATA  *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add other matrix to this one. Both must have the same sizes.
     @param     this    object pointer
     @param     pOther  a pointer to another U16MATRIX object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         U16Matrix_Add (
        U16MATRIX_DATA  *this,
        U16MATRIX_DATA  *pOther
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = U16Matrix_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another U16MATRIX object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         U16Matrix_Assign (
        U16MATRIX_DATA  *this,
        U16MATRIX_DATA  *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other,
                otherwise ERESULT_SUCCESS_UNEQUAL
     */
    ERESULT         U16Matrix_Compare (
        U16MATRIX_DATA     *this,
        U16MATRIX_DATA     *pOther
    );


    /*!
     Generates a C compilable module that will search the compressed table
     for i, j and return the value or zero if not available. Compression is
     based on removing zero entries from the table and is derived from the
     end of the Lexical Analysis Chapter in the Dragon Book.
     @param     this    object pointer
     @param     pPrefix Prefix for the Get Routine Name
     @return    If successful, an AStr object which must be released.
                Otherwise, OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     U16Matrix_CompressedTable (
        U16MATRIX_DATA  *this,
        const
        char            *pPrefix        // Prefix for the Get Routine Name
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        U16Matrix      *pCopy = U16Matrix_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a U16MATRIX object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    U16MATRIX_DATA * U16Matrix_Copy (
        U16MATRIX_DATA  *this
    );


    /*!
     Return a matrix element.
     @param     this    object pointer
     @param     i       0 < i < m
     @param     j       0 < j < n
     @return    If successful, the matrix element, otherwise 0.
     */
    uint16_t        U16Matrix_Get (
        U16MATRIX_DATA  *this,
        uint32_t        i,
        uint32_t        j
    );

   
    U16MATRIX_DATA * U16Matrix_Init (
        U16MATRIX_DATA     *this
    );


    /*!
     Multiply is matrix multiplication as in newMatrix = this X other
     which creates an n x p matrix where this matrix is n x m and
     other matrix is m x p. The multiplication is not commutative.
     this X other may not equal other X this.
     @param     this    U16MATRIX_DATA object pointer
     @param     pOther  U16MATRIX_DATA object pointer
     @return    If successful, a new matrix, otherwise OBJ_NIL and
                getLastError() ERESULT_* error code
     */
    U16MATRIX_DATA * U16Matrix_Multiply (
        U16MATRIX_DATA   *this,
        U16MATRIX_DATA   *pOther
    );


    /*!
     Scalar Addition is adding a value to each element of the array.
     @param     this    U16MATRIX_DATA object pointer
     @param     value   value to be added to each element
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error
                code
     */
    ERESULT         U16Matrix_ScalarAdd (
        U16MATRIX_DATA  *this,
        uint16_t        value
    );


    /*!
     Scalar Multiply is multipling a value to each element of the array.
     @param     this    U16MATRIX_DATA object pointer
     @param     value   value to be multiplied to each element
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error
                code
     */
    ERESULT         U16Matrix_ScalarMultiply (
        U16MATRIX_DATA  *this,
        uint16_t        value
    );


    /*!
     Replace a matrix element with the given value.
     @param     this    object pointer
     @param     i       0 < i < m
     @param     j       0 < j < n
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error
                code
     */
    ERESULT         U16Matrix_Set (
        U16MATRIX_DATA  *this,
        uint32_t        i,
        uint32_t        j,
        uint16_t        value
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
        U16MATRIX_DATA  *this,
        int             indent
    );
    
    
    /*!
     Replace all matrix elements with zero.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error
                code
     */
    ERESULT         U16Matrix_Zero (
        U16MATRIX_DATA  *this
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* U16MATRIX_H */

