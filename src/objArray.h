// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          OBJARRAY Console Transmit Task (objArray) Header
//****************************************************************
/*
 * Program
 *			Separate objArray (objArray)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate objArray to run things without complications
 *          of interfering with the main objArray. A objArray may be 
 *          called a objArray on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	03/22/2016 Generated
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
#include        <objEnum.h>


#ifndef         OBJARRAY_H
#define         OBJARRAY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct objArray_data_s	OBJARRAY_DATA;    // Inherits from OBJ.

    typedef struct objArray_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in objArray_object.c.
        // Properties:
        // Methods:
    } OBJARRAY_VTBL;

    
    typedef ERESULT         (*OBJ_COMPARE)(OBJ_ID p0, OBJ_ID p1);


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    OBJARRAY_DATA *     objArray_Alloc(
        void
    );
    
    
    OBJARRAY_DATA *     objArray_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         objArray_getLastError(
        OBJARRAY_DATA   *this
    );
    
    
    uint32_t        objArray_getSize(
        OBJARRAY_DATA   *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given element to the end of the array.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         objArray_AppendObj(
        OBJARRAY_DATA   *this,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    );
    
    
    /*!
     Add the elements from the other array to the end of the array.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         objArray_Append(
        OBJARRAY_DATA   *this,
        OBJARRAY_DATA   *pOther
    );
    
    
    /*!
     Assign the contents of this array to the other array. The
     contents of the other array are released. Then we simply
     retain them so that they are in both arrays.
     @param     this    object pointer
     @return    If successful, return ERESULT_SUCCESS
                otherwise an eResult error code.
     */
    ERESULT         objArray_Assign(
        OBJARRAY_DATA	*this,
        OBJARRAY_DATA	*pOther
    );
    
    
    /*!
     Copy this array. All elements of the array will be retained for
     use in the new array.
     @param     this    object pointer
     @return    If successful, return a new array that must be released
                otherwise return OBJ_NIL.
     */
    OBJARRAY_DATA * objArray_Copy(
        OBJARRAY_DATA	*this
    );
    
    
    /*!
     Copy this array. Any element of the array that has a DeepCopy or
     Copy method will have that used to create a new object. Otherwise,
     the object is just retained and added to the new array.
     @param     this    object pointer
     @return    If successful, return a new array that must be released
     otherwise return OBJ_NIL.
     */
    OBJARRAY_DATA * objArray_DeepCopy(
        OBJARRAY_DATA    *this
    );
    
    
    /*!
     Remove the index'th element from the array and return it.
     @param     this    object pointer
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJ_ID          objArray_Delete(
        OBJARRAY_DATA	*this,
        uint32_t        index
    );
    
    
    /*!
     Delete all objects in this array.
     @param     this    object pointer
     @return    If successful, return ERESULT_SUCCESS
                otherwise an eResult error code.
     */
    ERESULT         objArray_DeleteAll(
        OBJARRAY_DATA    *this
    );
    
    
    /*!
     Remove the first element from the array and return it.
     @param     this    object pointer
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJ_ID          objArray_DeleteFirst(
        OBJARRAY_DATA	*this
    );
    
    
    /*!
     Remove the last element from the array and return it.
     @param     this    object pointer
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJ_ID          objArray_DeleteLast(
        OBJARRAY_DATA	*this
    );
    
    
    /*!
     Create an enumerator for the Hash in ascending order
     if the object contains a compare() method.
     @param     this    object pointer
     @return    If successful, an Enumerator object which must be
     released, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    OBJENUM_DATA *  objArray_Enum(
        OBJARRAY_DATA   *this
    );
    
    
    /*!
     Scan the array applying the given routine to each member of the
     array.  Second parameter to the Scan routine is the actual array
     entry address. Halt the scan if an error return code is returned
     by the scan routine.
     @param     this    Object Pointer
     @param     pScan   Scan Routine Address, Second parameter for the
                        Scan Routine is the Object pointer from the
                        current array entry
     @param     pObj    First Parameter for the Scan Routine (optional)
     @param     pArg3   Third Parameter for the Scan Routine (optional)
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
     error.
     */
    ERESULT         objArray_ForEach(
        OBJARRAY_DATA   *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    
    /*!
     Find the index'th entry in the array.
     @param     this    objArray object pointer
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     */
    OBJ_ID          objArray_Get(
        OBJARRAY_DATA	*this,
        uint32_t        index       // Relative to 1
    );

    
    /*!
     Find entry 1 in the array.
     @param     this    objArray object pointer
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     */
    OBJ_ID          objArray_GetFirst(
        OBJARRAY_DATA	*this
    );
    
    /*!
     Find entry 1 in the array.
     @param     this    objArray object pointer
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     */
    OBJ_ID          objArray_GetLast(
        OBJARRAY_DATA	*this
    );
    
    
    OBJARRAY_DATA * objArray_Init(
        OBJARRAY_DATA   *this
    );
    
    
    /*!
     Add the given element after the index'th element of the array.
     @param     this    object pointer
     @param     index   range is 0 to Size. If 0, then object is added before
                        the first object in the array.
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         objArray_InsertObj(
        OBJARRAY_DATA   *this,
        uint32_t        index,
        OBJ_ID          pObject
    );
    
    
    /*!
     Delete the last object from the array and return it.
     @param     this    object pointer
     @return    If successful, last object of the array, otherwise OBJ_NIL.
     */
    OBJ_ID          objArray_Pop(
        OBJARRAY_DATA   *this
    );
    
    
    /*!
     Add the given object to the end of the array.
     @param     this    object pointer
     @param     pObject object pointer to be pushed
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         objArray_Push(
        OBJARRAY_DATA   *this,
        OBJ_ID          pObject
    );
    
    
    /*!
     Replace index'th element with the given element expanding the array if
     necessary. after the index'th element of the array.
     @param     this    object pointer
     @param     index   1 to Size.
     @param     pObj    Object Pointer or OBJ_NIL.
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         objArray_Put(
        OBJARRAY_DATA	*this,
        uint32_t        index,          // Relative to 1
        OBJ_ID          pObj
    );
    
    
    /*!
     Sort the array in ascending sequence. This only works if 
     the objects have a comparison routine that returns the
     ERESULT values of ERESULT_SUCCESS_EQUAL, ERESULT_SUCCESS_LESS_THAN
     or ERESULT_SUCCESS_GREATER_THAN.
     @param     this    object pointer
     @param     pCompare Optional Comparison routine mentioned above. If
                         not present, then the comparison routine in the
                         first array element is used if present.
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         objArray_SortAscending(
        OBJARRAY_DATA	*this,
        OBJ_COMPARE     pCompare
    );
    
    
    /*!
     Return the top of the stack (last object in the array).
     @param     this    object pointer
     @return    If successful, last object of the array, otherwise OBJ_NIL.
     */
    OBJ_ID          objArray_Top(
        OBJARRAY_DATA   *this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *    objArray_ToDebugString(
        OBJARRAY_DATA   *this,
        int             indent
    );
    
    
    /*!
     Exchange the two array entries specified.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         objArray_Xchg(
        OBJARRAY_DATA   *this,
        uint16_t        index1,         // Relative to 1
        uint16_t        index2          // Relative to 1
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJARRAY_H */

