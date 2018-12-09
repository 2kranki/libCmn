// vi:nu:et:sts=4 ts=4 sw=4 tw=90

//****************************************************************
//          An Array of AStr Objects (AStrArray) Header
//****************************************************************
/*
 * Program
 *			An Array of AStr Objects (AStrArray)
 * Purpose
 *			This object provides an array of AStr objects.
 *
 * Remarks
 *    1.    The Object User flags and Misc data are not used in
 *          this object.
 *
 * History
 *	Copied from NodeArray 09/25/2015
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
#include        <objArray.h>


#ifndef         ASTRARRAY_H
#define         ASTRARRAY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // ASTRARRAY_DATA and ASTRARRAY_VTBL is defined in "cmn_defs.h"

    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    ASTRARRAY_DATA * AStrArray_Alloc(
        void
    );
    
    
    ASTRARRAY_DATA * AStrArray_New(
        void
    );
    
    
    ASTRARRAY_DATA *    AStrArray_NewFromArgV(
        int             cArgs,
        const
        char            *ppArgV[]
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     @param     ppArgV  pointer to NULL-terminated array of strings
     @return    If successful, an AStrArray object which must be released
                containing the array of strings, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTRARRAY_DATA *    AStrArray_NewFromArrayA(
        const
        char            *ppArgV[]
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJARRAY_DATA *  AStrArray_getArray(
        ASTRARRAY_DATA  *this
    );
    
    
    uint32_t        AStrArray_getSize(
        ASTRARRAY_DATA	*this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Append the given string to the array and return its index.
     @param     this    Object Pointer
     @param     pObject String Object to be added
     @param     pIndex  (Optional) Index Pointer
     @return    If successful, ERESULT_SUCCESS and the index in pIndex
                if it is not NULL.  Otherwise, an ERESULT_* error.
     */
    ERESULT         AStrArray_AppendStr(
        ASTRARRAY_DATA	*this,
        ASTR_DATA       *pObject,
        uint32_t        *pIndex
    );
    
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
     ERESULT eRc = AStrArray_Assign(this, pOther);
     @endcode
     @param     this    ASTRARRAY_DATA object pointer
     @param     pOther  a pointer to another ASTRARRAY_DATA object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         AStrArray_Assign(
        ASTRARRAY_DATA  *this,
        ASTRARRAY_DATA  *pOther
    );
    
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
     appl      *pCopy = AStrArray_Copy(this);
     @endcode
     @param     this    ASTRARRAY_DATA object pointer
     @return    If successful, a ASTRARRAY_DATA object which must
     be released, otherwise OBJ_NIL.
     @warning   Remember to release the returned the returned object.
     */
    ASTRARRAY_DATA * AStrArray_Copy(
        ASTRARRAY_DATA  *this
    );
    
    
    // DeleteFromBottom() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    ASTR_DATA *     AStrArray_DeleteFirst(
        ASTRARRAY_DATA	*this
    );
    
    
    // DeleteFromTop() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    ASTR_DATA *     AStrArray_DeleteLast(
        ASTRARRAY_DATA	*this
    );
    
    
    ASTR_DATA *     AStrArray_Get(
        ASTRARRAY_DATA	*this,
        uint32_t        index       // Relative to 1
    );
    
    ASTR_DATA *     AStrArray_GetFirst(
        ASTRARRAY_DATA  *this
    );
    
    ASTR_DATA *     AStrArray_GetLast(
        ASTRARRAY_DATA	*this
    );
    
    
    ASTRARRAY_DATA * AStrArray_Init(
        ASTRARRAY_DATA  *this
    );


    ERESULT         AStrArray_InsertStr(
        ASTRARRAY_DATA	*this,
        uint32_t        index,
        ASTR_DATA       *pObject
    );
    
    
    ERESULT         AStrArray_SortAscending(
        ASTRARRAY_DATA	*this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = AStrArray_ToDebugString(this, 4);
     @endcode
     @param     this    ASTRARRAY_DATA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AStrArray_ToDebugString(
        ASTRARRAY_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* ASTRARRAY_H */

