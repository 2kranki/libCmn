// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          BITMATRIX Console Transmit Task (BitMatrix) Header
//****************************************************************
/*
 * Program
 *			Separate BitMatrix (BitMatrix)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate BitMatrix to run things without complications
 *          of interfering with the main BitMatrix. A BitMatrix may be 
 *          called a BitMatrix on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/18/2019 Generated
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
#include        <BitSet.h>
#include        <u32Array.h>


#ifndef         BITMATRIX_H
#define         BITMATRIX_H


#define   BITMATRIX_JSON_SUPPORT 1
//#define   BITMATRIX_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BitMatrix_data_s	BITMATRIX_DATA;            // Inherits from OBJ
    typedef struct BitMatrix_class_data_s BITMATRIX_CLASS_DATA;   // Inherits from OBJ

    typedef struct BitMatrix_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BitMatrix_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BITMATRIX_DATA *);
    } BITMATRIX_VTBL;

    typedef struct BitMatrix_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BitMatrix_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BITMATRIX_DATA *);
    } BITMATRIX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BITMATRIX_SINGLETON
    BITMATRIX_DATA * BitMatrix_Shared (
        void
    );

    bool            BitMatrix_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BitMatrix object if successful, otherwise OBJ_NIL.
     */
    BITMATRIX_DATA * BitMatrix_Alloc (
        void
    );
    
    
    OBJ_ID          BitMatrix_Class (
        void
    );
    
    
    BITMATRIX_DATA * BitMatrix_New (
        void
    );
    
    BITMATRIX_DATA * BitMatrix_NewWithSizes (
        uint32_t        ySize,
        uint32_t        xSize
    );
    
    BITMATRIX_DATA * BitMatrix_NewFromJsonString(
        ASTR_DATA       *pString
    );
    
    
    BITMATRIX_DATA * BitMatrix_NewFromJsonStringA(
        const
        char            *pString
    );
    
    
    /*!
     Create a new identity matrix of the given size.  The matrix must be
     square (ie xSize == ySize).
     @param     xSize   x-axis and y-axis size in bits
     @return    If successful, an Identity Matrix.  Otherwise, OBJ_NIL.
     */
    BITMATRIX_DATA * BitMatrix_NewIdentity(
        uint32_t        xSize
    );
    
    
    BITMATRIX_DATA * BitMatrix_NewSquare(
        uint32_t        xSize
    );
    
    



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        BitMatrix_getXSize(
        BITMATRIX_DATA  *this
    );


    uint32_t        BitMatrix_getYSize(
        BITMATRIX_DATA  *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = BitMatrix_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another BITMATRIX object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         BitMatrix_Assign (
        BITMATRIX_DATA  *this,
        BITMATRIX_DATA  *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        BitMatrix      *pCopy = BitMatrix_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a BITMATRIX object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BITMATRIX_DATA * BitMatrix_Copy (
        BITMATRIX_DATA  *this
    );


    /*!
     Zero all elements of the matrix.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BitMatrix_Empty (
        BITMATRIX_DATA  *this
    );


    ERESULT         BitMatrix_Get (
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x
    );
    
    
    /*!
     Get all or part of a Column and put it into a bitset
     (ie x stays static and y is varied from y to max of
     y+len or ySize).
     @param     this    object pointer
     @param     y       Column number (relative to 1)
     @param     x       Row number (relative to 1)
     @param     len     number of bits to get (max of ySize),
                        0 == ySize
     @return    If successful, bitSet object.  Otherwise,
                OBJ_NIL and an ERESULT_* error code is set.
     */
    BITSET_DATA *   BitMatrix_GetCol (
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        uint32_t        len
    );
    
    
    /*!
     Get all or part of a Column and put it into a u32Array
     (ie x stays static and y is varied from y to max of
     y+len or ySize).  If any bit is true, then the array
     entry will contain a 1.  Otherwise, it will contain a
     0.
     @param     this    object pointer
     @param     y       Column number (relative to 1)
     @param     x       Row number (relative to 1)
     @param     len     number of bits to get (max of ySize),
                        0 == ySize
     @return    If successful, u32Array object.  Otherwise,
     OBJ_NIL and an ERESULT_* error code is set.
     */
    U32ARRAY_DATA * BitMatrix_GetColU32 (
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        uint32_t        len
    );
    
    
    /*!
     Get all or part of a Row and put it into a bitset
     (ie y stays static and x is varied from x to max of
     x+len or xSize).
     @param     this    object pointer
     @param     y       Column number (relative to 1)
     @param     x       Row number (relative to 1)
     @param     len     number of bits to get (max of xSize),
                        0 == xSize
     @return    If successful, bitSet object.  Otherwise,
                OBJ_NIL and an ERESULT_* error code is set.
     */
    BITSET_DATA *   BitMatrix_GetRow (
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        uint32_t        len
    );
    
    
    /*!
     Get all or part of a Row and put it into a u32Array
     (ie y stays static and x is varied from x to max of
     x+len or xSize).  If any bit is true, then the array
     entry will contain a 1.  Otherwise, it will contain a
     0.
     @param     this    object pointer
     @param     y       Column number (relative to 1)
     @param     x       Row number (relative to 1)
     @param     len     number of bits to get (max of xSize),
                        0 == xSize
     @return    If successful, u32Array object.  Otherwise,
                OBJ_NIL and an ERESULT_* error code is set.
     */
    U32ARRAY_DATA * BitMatrix_GetRowU32 (
        BITMATRIX_DATA  *this,
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
    ERESULT         BitMatrix_InflateX(
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
    ERESULT         BitMatrix_InflateY(
        BITMATRIX_DATA  *this,
        uint32_t        amt
    );
    
    
    BITMATRIX_DATA * BitMatrix_Init (
        BITMATRIX_DATA  *this
    );


    ERESULT         BitMatrix_Intersect (
        BITMATRIX_DATA  *this,
        BITMATRIX_DATA  *pOther
    );
    
    
    ERESULT         BitMatrix_Invert (
        BITMATRIX_DATA  *this
    );
    
    
    /*!
     Check the matrix to see if it is empty.
     @param     this    object pointer
     @return    If empty, ERESULT_SUCCESS_TRUE.  If not empty,
                ERESULT_FAILURE_FALSE.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BitMatrix_IsEmpty (
        BITMATRIX_DATA  *this
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
    BITMATRIX_DATA * BitMatrix_Product(
        BITMATRIX_DATA  *this,
        BITMATRIX_DATA  *pOther
    );
    
    
    ERESULT         BitMatrix_ReflectiveTransitiveClosure(
        BITMATRIX_DATA  *this
    );
    
    
    ERESULT         BitMatrix_Set(
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        bool            value
    );

    
    ASTR_DATA *     BitMatrix_ToJson(
        BITMATRIX_DATA  *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BitMatrix_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BitMatrix_ToDebugString (
        BITMATRIX_DATA  *this,
        int             indent
    );
    
    
    ERESULT         BitMatrix_TransitiveClosure (
        BITMATRIX_DATA  *this
    );


    ERESULT         BitMatrix_Union (
        BITMATRIX_DATA  *this,
        BITMATRIX_DATA  *pOther
    );


    /*!
     Zero all elements of the matrix.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BitMatrix_Zero (
        BITMATRIX_DATA  *this
    );




    
#ifdef	__cplusplus
}
#endif

#endif	/* BITMATRIX_H */

