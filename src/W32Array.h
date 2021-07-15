// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  An Array of W32Str(s) (W32Array) Header
//****************************************************************
/*
 * Program
 *          An Array of W32Str(s) (W32Array)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate W32Array to run things without complications
 *          of interfering with the main W32Array. A W32Array may be 
 *          called a W32Array on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  07/15/2021 Generated
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
#include        <W32Str.h>


#ifndef         W32ARRAY_H
#define         W32ARRAY_H


//#define   W32ARRAY_IS_IMMUTABLE     1
#define   W32ARRAY_JSON_SUPPORT       1
//#define   W32ARRAY_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct W32Array_data_s  W32ARRAY_DATA;            // Inherits from OBJ
    typedef struct W32Array_class_data_s W32ARRAY_CLASS_DATA;   // Inherits from OBJ

    typedef struct W32Array_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in W32Array_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(W32ARRAY_DATA *);
    } W32ARRAY_VTBL;

    typedef struct W32Array_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in W32Array_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(W32ARRAY_DATA *);
    } W32ARRAY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  W32ARRAY_SINGLETON
    W32ARRAY_DATA * W32Array_Shared (
        void
    );

    void            W32Array_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to W32Array object if successful, otherwise OBJ_NIL.
     */
    W32ARRAY_DATA * W32Array_Alloc (
        void
    );
    
    
    OBJ_ID          W32Array_Class (
        void
    );
    
    
    W32ARRAY_DATA * W32Array_New (
        void
    );


    W32ARRAY_DATA * W32Array_NewFromArgV(
        int             cArgs,
        const
        char            *ppArgV[]
    );


#ifdef  W32ARRAY_JSON_SUPPORT
    W32ARRAY_DATA * W32Array_NewFromJsonString (
        ASTR_DATA       *pString
    );

    W32ARRAY_DATA * W32Array_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        W32Array_getSize(
        W32ARRAY_DATA   *this
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
    ERESULT         W32Array_AppendStr(
        W32ARRAY_DATA   *this,
        W32STR_DATA     *pObject,
        uint32_t        *pIndex
    );

    ERESULT         W32Array_AppendUtf8File(
        W32ARRAY_DATA   *this,
        PATH_DATA       *pPath
    );

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = W32Array_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another W32ARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         W32Array_Assign (
        W32ARRAY_DATA   *this,
        W32ARRAY_DATA   *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        W32Array      *pCopy = W32Array_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a W32ARRAY object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    W32ARRAY_DATA * W32Array_Copy (
        W32ARRAY_DATA   *this
    );

   
    // DeleteFromBottom() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    W32STR_DATA *   W32Array_DeleteFirst(
        W32ARRAY_DATA   *this
    );


    // DeleteFromTop() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    W32STR_DATA *   W32Array_DeleteLast(
        W32ARRAY_DATA   *this
    );


    W32STR_DATA *   W32Array_Get(
        W32ARRAY_DATA   *this,
        uint32_t        index       // Relative to 1
    );

    W32STR_DATA *   W32Array_GetFirst(
        W32ARRAY_DATA   *this
    );

    W32STR_DATA *   W32Array_GetLast(
        W32ARRAY_DATA   *this
    );


    W32ARRAY_DATA * W32Array_Init (
        W32ARRAY_DATA   *this
    );


    ERESULT         W32Array_InsertStr(
        W32ARRAY_DATA   *this,
        uint32_t        index,
        W32STR_DATA     *pObject
    );


    ERESULT         W32Array_SortAscending(
        W32ARRAY_DATA    *this
    );


#ifdef  W32ARRAY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = W32Array_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Array_ToJson (
        W32ARRAY_DATA    *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = W32Array_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Array_ToDebugString (
        W32ARRAY_DATA   *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* W32ARRAY_H */

