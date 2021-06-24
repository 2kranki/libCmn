// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  An Array of Value Objects (ValueArray) Header
//****************************************************************
/*
 * Program
 *          An Array of Value Objects (ValueArray)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate ValueArray to run things without complications
 *          of interfering with the main ValueArray. A ValueArray may be 
 *          called a ValueArray on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  06/17/2021 Generated
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
#include        <Value.h>


#ifndef         VALUEARRAY_H
#define         VALUEARRAY_H


//#define   VALUEARRAY_IS_IMMUTABLE     1
#define   VALUEARRAY_JSON_SUPPORT       1
//#define   VALUEARRAY_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ValueArray_data_s  VALUEARRAY_DATA;            // Inherits from OBJ
    typedef struct ValueArray_class_data_s VALUEARRAY_CLASS_DATA;   // Inherits from OBJ

    typedef struct ValueArray_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ValueArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(VALUEARRAY_DATA *);
    } VALUEARRAY_VTBL;

    typedef struct ValueArray_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ValueArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(VALUEARRAY_DATA *);
    } VALUEARRAY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  VALUEARRAY_SINGLETON
    VALUEARRAY_DATA * ValueArray_Shared (
        void
    );

    void            ValueArray_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ValueArray object if successful, otherwise OBJ_NIL.
     */
    VALUEARRAY_DATA * ValueArray_Alloc (
        void
    );
    
    
    OBJ_ID          ValueArray_Class (
        void
    );
    
    
    VALUEARRAY_DATA * ValueArray_New (
        void
    );
    
    
#ifdef  VALUEARRAY_JSON_SUPPORT
    VALUEARRAY_DATA * ValueArray_NewFromJsonString (
        ASTR_DATA       *pString
    );

    VALUEARRAY_DATA * ValueArray_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        ValueArray_getSize (
        VALUEARRAY_DATA *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the elements from the other array to the end of this array.
     @param     this    object pointer
     @param     pOther  array object pointer to be appended
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         ValueArray_Append (
        VALUEARRAY_DATA *this,
        VALUEARRAY_DATA *pOther
    );


    /*!
     Add the given element to the end of the array.
     @param     this    object pointer
     @param     pValue  value object to be added
     @param     pIndex  optional index of object added
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         ValueArray_AppendValue (
        VALUEARRAY_DATA *this,
        VALUE_DATA      *pValue,
        uint32_t        *pIndex
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        ValueArray      *pCopy = ValueArray_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a VALUEARRAY object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    VALUEARRAY_DATA * ValueArray_Copy (
        VALUEARRAY_DATA *this
    );

   
    /*!
     Get the index'th entry in the array.
     @param     this    objArray object pointer
     @param     index   index (relative to 1)
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     */
    VALUE_DATA *    ValueArray_Get (
        VALUEARRAY_DATA *this,
        uint32_t        index       // Relative to 1
    );


    VALUEARRAY_DATA * ValueArray_Init (
        VALUEARRAY_DATA *this
    );


#ifdef  VALUEARRAY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ValueArray_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ValueArray_ToJson (
        VALUEARRAY_DATA *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ValueArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ValueArray_ToDebugString (
        VALUEARRAY_DATA *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* VALUEARRAY_H */

