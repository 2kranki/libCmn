// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Signed 16-Bit Matrix (I16Matrix) Header
//****************************************************************
/*
 * Program
 *			Signed 16-Bit Matrix (I16Matrix)
 * Purpose
 *            This object provides an signed 16-bit element Matrix.
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


#ifndef         I16MATRIX_H
#define         I16MATRIX_H


//#define   I16MATRIX_IS_IMMUTABLE     1
#define   I16MATRIX_JSON_SUPPORT     1
//#define   I16MATRIX_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct I16Matrix_data_s	I16MATRIX_DATA;            // Inherits from OBJ
    typedef struct I16Matrix_class_data_s I16MATRIX_CLASS_DATA;   // Inherits from OBJ

    typedef struct I16Matrix_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in I16Matrix_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(I16MATRIX_DATA *);
    } I16MATRIX_VTBL;

    typedef struct I16Matrix_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in I16Matrix_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(I16MATRIX_DATA *);
    } I16MATRIX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  I16MATRIX_SINGLETON
    I16MATRIX_DATA * I16Matrix_Shared (
        void
    );

    void            I16Matrix_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to I16Matrix object if successful, otherwise OBJ_NIL.
     */
    I16MATRIX_DATA * I16Matrix_Alloc (
        void
    );
    
    
    OBJ_ID          I16Matrix_Class (
        void
    );
    
    
    I16MATRIX_DATA * I16Matrix_New (
        void
    );
    
    
    I16MATRIX_DATA * I16Matrix_NewWithSizes (
        uint32_t        mSize,          // Height (y-axis, Number of Rows, i)
        uint32_t        nSize           // Width (x-axis, Number of Columns, j)
    );


    // Returns an N X N Identity Matrix.
    I16MATRIX_DATA * I16Matrix_NewIdentity (
        uint32_t        nSize           // Width (x-axis, Number of Columns, j)
    );


    // Returns an N X N Zeroed Matrix.
    I16MATRIX_DATA * I16Matrix_NewSquare (
        uint32_t        nSize           // Width (x-axis, Number of Columns, j)
    );


#ifdef  I16MATRIX_JSON_SUPPORT
    I16MATRIX_DATA * I16Matrix_NewFromJsonString (
        ASTR_DATA       *pString
    );

    I16MATRIX_DATA * I16Matrix_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        I16Matrix_getM (
        I16MATRIX_DATA  *this
    );


    uint32_t        I16Matrix_getN (
        I16MATRIX_DATA  *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

     /*!
      Add other matrix to this one. Both must have the same sizes.
      @param     this    object pointer
      @param     pOther  a pointer to another I16MATRIX object
      @return    If successful, ERESULT_SUCCESS otherwise an
                 ERESULT_* error
      */
     ERESULT         I16Matrix_Add (
         I16MATRIX_DATA  *this,
         I16MATRIX_DATA  *pOther
     );


     /*!
      Assign the contents of this object to the other object (ie
      this -> other).  Any objects in other will be released before
      a copy of the object is performed.
      Example:
      @code
         ERESULT eRc = I16Matrix_Assign(this,pOther);
      @endcode
      @param     this    object pointer
      @param     pOther  a pointer to another I16MATRIX object
      @return    If successful, ERESULT_SUCCESS otherwise an
                 ERESULT_* error
      */
     ERESULT         I16Matrix_Assign (
         I16MATRIX_DATA  *this,
         I16MATRIX_DATA  *pOther
     );


     /*!
      Compare the two provided objects.
      @return    0  if this == other
                 1  if this != other
      */
     ERESULT         I16Matrix_Compare (
         I16MATRIX_DATA     *this,
         I16MATRIX_DATA     *pOther
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
     ASTR_DATA *     I16Matrix_CompressedTable (
         I16MATRIX_DATA  *this,
         const
         char            *pPrefix        // Prefix for the Get Routine Name
     );


     /*!
      Copy the current object creating a new object.
      Example:
      @code
         I16Matrix      *pCopy = I16Matrix_Copy(this);
      @endcode
      @param     this    object pointer
      @return    If successful, a I16MATRIX object which must be
                 released, otherwise OBJ_NIL.
      @warning   Remember to release the returned object.
      */
     I16MATRIX_DATA * I16Matrix_Copy (
         I16MATRIX_DATA  *this
     );


     /*!
      Calculate the least path weights using an n X n weighted
      matrix with positive weights.
      @param     this    object pointer
      @return    If successful, a I16MATRIX object which must be
                 released, otherwise OBJ_NIL.
      @warning   Remember to release the returned object.
      */
     I16MATRIX_DATA * I16Matrix_Floyd (
         I16MATRIX_DATA  *this
     );


     /*!
      Return a matrix element.
      @param     this    object pointer
      @param     i       0 < i <= m
      @param     j       0 < j <= n
      @return    If successful, the matrix element, otherwise 0.
      */
     int16_t        I16Matrix_Get (
        I16MATRIX_DATA  *this,
        uint32_t        i,
        uint32_t        j
     );


    I16MATRIX_DATA * I16Matrix_Init (
        I16MATRIX_DATA  *this
    );


    /*!
     Multiply is matrix multiplication as in newMatrix = this X other
     which creates an n x p matrix where this matrix is n x m and
     other matrix is m x p. The multiplication is not commutative.
     this X other may not equal other X this.
     @param     this    I16MATRIX_DATA object pointer
     @param     pOther  I16MATRIX_DATA object pointer
     @return    If successful, a new matrix, otherwise OBJ_NIL and
                getLastError() ERESULT_* error code
     */
    I16MATRIX_DATA * I16Matrix_Multiply (
        I16MATRIX_DATA   *this,
        I16MATRIX_DATA   *pOther
    );


    /*!
     Scalar Addition is adding a value to each element of the array.
     @param     this    I16MATRIX_DATA object pointer
     @param     value   value to be added to each element
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error
                code
     */
    ERESULT         I16Matrix_ScalarAdd (
        I16MATRIX_DATA  *this,
        int16_t         value
    );


    /*!
     Scalar Multiply is multipling a value to each element of the array.
     @param     this    I16MATRIX_DATA object pointer
     @param     value   value to be multiplied to each element
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error
                code
     */
    ERESULT         I16Matrix_ScalarMultiply (
        I16MATRIX_DATA  *this,
        int16_t         value
    );


    /*!
     Replace a matrix element with the given value.
     @param     this    object pointer
     @param     i       0 < i <= m
     @param     j       0 < j <= n
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error
                code
     */
    ERESULT         I16Matrix_Set (
        I16MATRIX_DATA  *this,
        uint32_t        i,
        uint32_t        j,
        int16_t         value
    );


#ifdef  I16MATRIX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = I16Matrix_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     I16Matrix_ToJson (
        I16MATRIX_DATA  *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = I16Matrix_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    I16Matrix_ToDebugString (
        I16MATRIX_DATA  *this,
        int             indent
    );
    
    
    /*!
     Replace all matrix elements with zero.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error
                code
     */
    ERESULT         I16Matrix_Zero (
        I16MATRIX_DATA  *this
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* I16MATRIX_H */

