// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  An Array of AStr(ings) (AStrArray) Header
//****************************************************************
/*
 * Program
 *          An Array of AStr(ings) (AStrArray)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate AStrArray to run things without complications
 *          of interfering with the main AStrArray. A AStrArray may be 
 *          called a AStrArray on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  04/11/2021 Generated
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
#include        <Path.h>
#include        <ObjArray.h>
#include        <ObjEnum.h>


#ifndef         ASTRARRAY_H
#define         ASTRARRAY_H


//#define   ASTRARRAY_IS_IMMUTABLE     1
#define   ASTRARRAY_JSON_SUPPORT       1
//#define   ASTRARRAY_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // ASTRARRAY_DATA and ASTRARRAY_VTBL is defined in "cmn_defs.h"

    //typedef struct AStrArray_data_s  ASTRARRAY_DATA;            // Inherits from OBJ
    typedef struct AStrArray_class_data_s ASTRARRAY_CLASS_DATA;   // Inherits from OBJ

#ifdef CMN_DEF_DEFINED_ASTRARRAY
    typedef struct AStrArray_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in AStrArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ASTRARRAY_DATA *);
    } ASTRARRAY_VTBL;
#endif

    typedef struct AStrArray_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in AStrArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ASTRARRAY_DATA *);
    } ASTRARRAY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ASTRARRAY_SINGLETON
    ASTRARRAY_DATA * AStrArray_Shared (
        void
    );

    void            AStrArray_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to AStrArray object if successful, otherwise OBJ_NIL.
     */
    ASTRARRAY_DATA * AStrArray_Alloc (
        void
    );
    
    
    OBJ_ID          AStrArray_Class (
        void
    );
    
    
    ASTRARRAY_DATA *  AStrArray_New (
        void
    );
    
    
    ASTRARRAY_DATA * AStrArray_NewFromArgV (
        int             cArgs,
        const
        char            *ppArgV[]
    );


    /*!
     Create an array of strings from the provided array of strings.
     @param     ppArgV  pointer to NULL-terminated array of strings
     @return    If successful, an AStrArray object which must be released
                containing the array of strings, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTRARRAY_DATA * AStrArray_NewFromArrayA (
        const
        char            *ppArgV[]
    );


    /*!
     Create an array of strings from the provided list of strings which
     must have a trailing NULL.
     @param     pStrA  pointer to first NUL-terminated string
     @return    If successful, an AStrArray object which must be released
                containing the array of strings, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTRARRAY_DATA * AStrArray_NewFromListA (
        const
        char            *pStrA,
        ...
    );

    ASTRARRAY_DATA * AStrArray_NewFromList (
        va_list         pList
    );


#ifdef  ASTRARRAY_JSON_SUPPORT
    ASTRARRAY_DATA * AStrArray_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ASTRARRAY_DATA * AStrArray_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    ASTRARRAY_DATA * AStrArray_NewFromUtf8File (
        PATH_DATA       *pPath,
        int             maxLineLength
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJARRAY_DATA * AStrArray_getArray (
        ASTRARRAY_DATA  *this
    );


    uint32_t        AStrArray_getSize (
        ASTRARRAY_DATA  *this
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
    ERESULT         AStrArray_AppendStr (
        ASTRARRAY_DATA  *this,
        ASTR_DATA       *pObject,
        uint32_t        *pIndex
    );

    ERESULT         AStrArray_AppendUtf8File (
        ASTRARRAY_DATA  *this,
        PATH_DATA       *pPath,
        int             maxLineLength
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
    ERESULT         AStrArray_Assign (
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
    ASTRARRAY_DATA * AStrArray_Copy (
        ASTRARRAY_DATA  *this
    );


    // DeleteFromBottom() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    ASTR_DATA *     AStrArray_DeleteFirst (
        ASTRARRAY_DATA  *this
    );


    // DeleteFromTop() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    ASTR_DATA *     AStrArray_DeleteLast (
        ASTRARRAY_DATA  *this
    );


    /*!
     Create an enumerator for the array in ascending order.
     @param     this    object pointer
     @return    If successful, an Enumerator object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned Enum object.
     */
    OBJENUM_DATA *  AStrArray_Enum (
        ASTRARRAY_DATA  *this
    );


    /*!
     Get the i'th entry from the array if it exists.
     @param     this    object pointer
     @param     index   entry index relattive to 1
     @return    If successful, an AStr object,  otherwise OBJ_NIL;
     */
    ASTR_DATA *     AStrArray_Get (
        ASTRARRAY_DATA  *this,
        uint32_t        index       // Relative to 1
    );

    ASTR_DATA *     AStrArray_GetFirst (
        ASTRARRAY_DATA  *this
    );

    ASTR_DATA *     AStrArray_GetLast (
        ASTRARRAY_DATA  *this
    );


    ASTRARRAY_DATA * AStrArray_Init (
        ASTRARRAY_DATA  *this
    );


    ERESULT         AStrArray_InsertStr (
        ASTRARRAY_DATA  *this,
        uint32_t        index,
        ASTR_DATA       *pObject
    );


    ERESULT         AStrArray_SortAscending (
        ASTRARRAY_DATA    *this
    );


#ifdef  ASTRARRAY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = AStrArray_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AStrArray_ToJson (
        ASTRARRAY_DATA  *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = AStrArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AStrArray_ToDebugString (
        ASTRARRAY_DATA  *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ASTRARRAY_H */

