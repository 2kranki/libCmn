// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Array of AStrC objects (AStrCArray) Header
//****************************************************************
/*
 * Program
 *			Array of AStrC objects (AStrCArray)
 * Purpose
 *			This object provides an Array of AStrC objects.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/07/2019 Generated
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
#include        <AStrC.h>
#include        <objArray.h>


#ifndef         ASTRCARRAY_H
#define         ASTRCARRAY_H


//#define   ASTRCARRAY_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct AStrCArray_data_s	ASTRCARRAY_DATA;            // Inherits from OBJ
    typedef struct AStrCArray_class_data_s ASTRCARRAY_CLASS_DATA;   // Inherits from OBJ

    typedef struct AStrCArray_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in AStrCArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ASTRCARRAY_DATA *);
    } ASTRCARRAY_VTBL;

    typedef struct AStrCArray_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in AStrCArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ASTRCARRAY_DATA *);
    } ASTRCARRAY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ASTRCARRAY_SINGLETON
    ASTRCARRAY_DATA * AStrCArray_Shared (
        void
    );

    bool            AStrCArray_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to AStrCArray object if successful, otherwise OBJ_NIL.
     */
    ASTRCARRAY_DATA * AStrCArray_Alloc (
        void
    );
    
    
    OBJ_ID          AStrCArray_Class (
        void
    );
    
    
    ASTRCARRAY_DATA * AStrCArray_New (
        void
    );
    
    
    ASTRCARRAY_DATA * AStrCArray_NewFromArgV(
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
    ASTRCARRAY_DATA * AStrCArray_NewFromArrayA(
        const
        char            *ppArgV[]
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJARRAY_DATA * AStrCArray_getArray(
        ASTRCARRAY_DATA *this
    );


    uint32_t        AStrCArray_getSize(
        ASTRCARRAY_DATA *this
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
    ERESULT         AStrCArray_AppendAStr(
        ASTRCARRAY_DATA *this,
        ASTR_DATA       *pObject,
        uint32_t        *pIndex
    );

    ERESULT         AStrCArray_AppendAStrC(
        ASTRCARRAY_DATA *this,
        ASTRC_DATA      *pObject,
        uint32_t        *pIndex
    );
    
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = AStrCArray_Assign(this,pOther);
     @endcode
     @param     this    ASTRCARRAY object pointer
     @param     pOther  a pointer to another ASTRCARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         AStrCArray_Assign (
        ASTRCARRAY_DATA *this,
        ASTRCARRAY_DATA *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        AStrCArray      *pCopy = AStrCArray_Copy(this);
     @endcode
     @param     this    ASTRCARRAY object pointer
     @return    If successful, a ASTRCARRAY object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ASTRCARRAY_DATA * AStrCArray_Copy (
        ASTRCARRAY_DATA *this
    );

   
    // DeleteFromBottom() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    ASTRC_DATA *     AStrCArray_DeleteFirst(
        ASTRCARRAY_DATA *this
    );
    
    
    // DeleteFromTop() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    ASTRC_DATA *     AStrCArray_DeleteLast(
        ASTRCARRAY_DATA *this
    );
    
    
    ASTRC_DATA *    AStrCArray_Get(
        ASTRCARRAY_DATA *this,
        uint32_t        index       // Relative to 1
    );
    
    ASTRC_DATA *    AStrCArray_GetFirst(
        ASTRCARRAY_DATA *this
    );
    
    ASTRC_DATA *    AStrCArray_GetLast(
        ASTRCARRAY_DATA *this
    );
    
    
    /*!
     Find the first matching string in the Array.
     @param     this    object pointer
     @return    if found, index to element.  Otherwise, 0.
     */
    uint32_t        AStrCArray_Find (
        ASTRCARRAY_DATA *this,
        ASTRC_DATA      *pStrC
    );


    ASTRCARRAY_DATA * AStrCArray_Init (
        ASTRCARRAY_DATA *this
    );


    ERESULT         AStrCArray_InsertStr(
        ASTRCARRAY_DATA *this,
        uint32_t        index,
        ASTRC_DATA      *pObject
    );
    
    
    ERESULT         AStrCArray_SortAscending(
        ASTRCARRAY_DATA *this
    );
    
    
    ASTR_DATA *     AStrCArray_ToStringSep (
        ASTRCARRAY_DATA *this,
        const
        char            *pSep,
        const
        char            *pPrefix,           // Optional
        const
        char            *pSuffix            // Optional
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = AStrCArray_ToDebugString(this,4);
     @endcode 
     @param     this    ASTRCARRAY object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    AStrCArray_ToDebugString (
        ASTRCARRAY_DATA *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* ASTRCARRAY_H */

