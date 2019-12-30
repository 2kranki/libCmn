// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Array of Objects (ObjArray) Header
//****************************************************************
/*
 * Program
 *			Array of Objects (ObjArray)
 * Purpose
 *			This object provides an resizeable array of objects.
 *
 * Remarks
 *	1.      None
 *
 * History
 *  03/22/2016 Generated
 *	12/29/2019 Regenerated
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
#include        <array.h>
#include        <AStr.h>
#include        <ObjEnum.h>


#ifndef         OBJARRAY_H
#define         OBJARRAY_H


//#define   OBJARRAY_JSON_SUPPORT 1
//#define   OBJARRAY_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ObjArray_data_s	OBJARRAY_DATA;            // Inherits from OBJ
    typedef struct ObjArray_class_data_s OBJARRAY_CLASS_DATA;   // Inherits from OBJ

    typedef struct ObjArray_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJARRAY_DATA *);
    } OBJARRAY_VTBL;

    typedef struct ObjArray_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJARRAY_DATA *);
    } OBJARRAY_CLASS_VTBL;


    typedef ERESULT         (*OBJ_COMPARE)(OBJ_ID p0, OBJ_ID p1);


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OBJARRAY_SINGLETON
    OBJARRAY_DATA * ObjArray_Shared (
        void
    );

    void            ObjArray_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ObjArray object if successful, otherwise OBJ_NIL.
     */
    OBJARRAY_DATA * ObjArray_Alloc (
        void
    );
    
    
    OBJ_ID          ObjArray_Class (
        void
    );
    
    
    OBJARRAY_DATA * ObjArray_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ARRAY_DATA *    ObjArray_getArray (
        OBJARRAY_DATA   *this
    );


    /*!
        Other is a property to hold any object that the user of this
        object may want to put in it.
     */
    OBJ_ID          ObjArray_getOther (
        OBJARRAY_DATA   *this
    );

    bool            ObjArray_setOther (
        OBJARRAY_DATA   *this,
        OBJ_ID          pValue
    );


    uint32_t        ObjArray_getSize (
        OBJARRAY_DATA   *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the elements from the other array to the end of the array.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         ObjArray_Append (
        OBJARRAY_DATA   *this,
        OBJARRAY_DATA   *pOther
    );
    
    
    /*!
     Add the given element to the end of the array.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         ObjArray_AppendObj (
        OBJARRAY_DATA   *this,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    );
    
    
    /*!
     Assign the contents of this array to the other array. The
     contents of the other array are released. Then we simply
     retain them so that they are in both arrays.
     @param     this    object pointer
     @return    If successful, return ERESULT_SUCCESS
                otherwise an eResult error code.
     */
    ERESULT         ObjArray_Assign (
        OBJARRAY_DATA    *this,
        OBJARRAY_DATA    *pOther
    );
    
    
    /*!
     Copy this array. All elements of the array will be retained for
     use in the new array.
     @param     this    object pointer
     @return    If successful, return a new array that must be released
                otherwise return OBJ_NIL.
     */
    OBJARRAY_DATA * ObjArray_Copy (
        OBJARRAY_DATA    *this
    );
    
    
    /*!
     Copy this array. Any element of the array that has a DeepCopy or
     Copy method will have that used to create a new object. Otherwise,
     the object is just retained and added to the new array.
     @param     this    object pointer
     @return    If successful, return a new array that must be released
     otherwise return OBJ_NIL.
     */
    OBJARRAY_DATA * ObjArray_DeepCopy (
        OBJARRAY_DATA   *this
    );
    
    
    /*!
     Remove the index'th element from the array and return it.
     @param     this    object pointer
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJ_ID          ObjArray_Delete (
        OBJARRAY_DATA   *this,
        uint32_t        index
    );
    
    
    /*!
     Delete all objects in this array.
     @param     this    object pointer
     @return    If successful, return ERESULT_SUCCESS
                otherwise an eResult error code.
     */
    ERESULT         ObjArray_DeleteAll (
        OBJARRAY_DATA   *this
    );
    
    
    /*!
     Remove the first element from the array and return it.
     @param     this    object pointer
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJ_ID          ObjArray_DeleteFirst (
        OBJARRAY_DATA   *this
    );
    
    
    /*!
     Remove the last element from the array and return it.
     @param     this    object pointer
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJ_ID          ObjArray_DeleteLast (
        OBJARRAY_DATA   *this
    );
    
    
    /*!
     Create an enumerator for the Hash in ascending order
     if the object contains a compare() method.
     @param     this    object pointer
     @return    If successful, an Enumerator object which must be
     released, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    OBJENUM_DATA *  ObjArray_Enum (
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
    ERESULT         ObjArray_ForEach (
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
    OBJ_ID          ObjArray_Get (
        OBJARRAY_DATA   *this,
        uint32_t        index       // Relative to 1
    );

    
    /*!
     Find entry 1 in the array.
     @param     this    objArray object pointer
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     */
    OBJ_ID          ObjArray_GetFirst (
        OBJARRAY_DATA   *this
    );
    
    /*!
     Find entry 1 in the array.
     @param     this    objArray object pointer
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     */
    OBJ_ID          ObjArray_GetLast (
        OBJARRAY_DATA   *this
    );
    
    
    OBJARRAY_DATA * ObjArray_Init (
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
    ERESULT         ObjArray_InsertObj (
        OBJARRAY_DATA   *this,
        uint32_t        index,
        OBJ_ID          pObject
    );
    
    
    /*!
     Delete the last object from the array and return it.
     @param     this    object pointer
     @return    If successful, last object of the array, otherwise OBJ_NIL.
     */
    OBJ_ID          ObjArray_Pop (
        OBJARRAY_DATA   *this
    );
    
    
    /*!
     Add the given object to the end of the array.
     @param     this    object pointer
     @param     pObject object pointer to be pushed
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         ObjArray_Push (
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
    ERESULT         ObjArray_Put (
        OBJARRAY_DATA    *this,
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
    ERESULT         ObjArray_SortAscending (
        OBJARRAY_DATA    *this,
        OBJ_COMPARE     pCompare
    );
    
    
    /*!
     Return the top of the stack (last object in the array).
     @param     this    object pointer
     @return    If successful, last object of the array, otherwise OBJ_NIL.
     */
    OBJ_ID          ObjArray_Top (
        OBJARRAY_DATA   *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    ObjArray_ToDebugString (
        OBJARRAY_DATA     *this,
        int             indent
    );
    
    
    /*!
     Exchange the two array entries specified.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         ObjArray_Xchg (
        OBJARRAY_DATA   *this,
        uint32_t        index1,         // Relative to 1
        uint32_t        index2          // Relative to 1
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJARRAY_H */

