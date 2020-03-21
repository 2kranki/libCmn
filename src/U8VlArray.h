// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//        uint8_t variable length array (U8VlArray) Header
//****************************************************************
/*
 * Program
 *			uint8_t variable length array (U8VlArray)
 * Purpose
 *			This object uses a fixed size uint8_t space and sub-
 *          divides it into an array of variable length entries.
 *          The maximum size for the space is 256 bytes. The
 *          first byte is the size of the entire space and the
 *          second byte is the amount currently being used.  Each
 *          entry in the array has its first byte as the length
 *          of that entry including the length byte.
 *
 *          When a new area to be managed is initialized, the
 *          first byte should be the size of the entire area
 *          to be managed including the first two bytes and the
 *          second byte should be 2 denoting the usage of the
 *          first two bytes.
 *
 * Remarks
 *  2.      Warning: This object uses OBJ_FLAG_USER1 internally.
 *
 * History
 *	03/20/2020 Generated
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


#ifndef         U8VLARRAY_H
#define         U8VLARRAY_H


//#define   U8VLARRAY_IS_IMMUTABLE     1
#define   U8VLARRAY_JSON_SUPPORT     1
//#define   U8VLARRAY_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct U8VlArray_data_s	U8VLARRAY_DATA;            // Inherits from OBJ
    typedef struct U8VlArray_class_data_s U8VLARRAY_CLASS_DATA;   // Inherits from OBJ

    typedef struct U8VlArray_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in U8VlArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(U8VLARRAY_DATA *);
    } U8VLARRAY_VTBL;

    typedef struct U8VlArray_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in U8VlArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(U8VLARRAY_DATA *);
    } U8VLARRAY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  U8VLARRAY_SINGLETON
    U8VLARRAY_DATA * U8VlArray_Shared (
        void
    );

    void            U8VlArray_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to U8VlArray object if successful, otherwise OBJ_NIL.
     */
    U8VLARRAY_DATA * U8VlArray_Alloc (
        void
    );
    
    
    OBJ_ID          U8VlArray_Class (
        void
    );
    
    
    U8VLARRAY_DATA * U8VlArray_New (
        void
    );
    
    
    /*!
      Create a new Object and initialize it with External data which it
      will not control (ie free). It is assumed that the first two bytes
      of the data area already contains the maximum size and amount used
      respectively. When it was initialized, the first byte should be the
      size of the entrie area to be managed and the second byte should be
      2.
      @return    pointer to U8VlArray object if successful, otherwise OBJ_NIL.
      */
    U8VLARRAY_DATA * U8VlArray_NewExternal (
        uint8_t         *pData
    );


#ifdef  U8VLARRAY_JSON_SUPPORT
    U8VLARRAY_DATA * U8VlArray_NewFromJsonString (
        ASTR_DATA       *pString
    );

    U8VLARRAY_DATA * U8VlArray_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Append a data element to the array. The first byte of the element
     must be its length including the first byte.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         U8VlArray_AppendData (
        U8VLARRAY_DATA  *this,
        uint8_t         *pData
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = U8VlArray_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another U8VLARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         U8VlArray_Assign (
        U8VLARRAY_DATA  *this,
        U8VLARRAY_DATA  *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         U8VlArray_Compare (
        U8VLARRAY_DATA     *this,
        U8VLARRAY_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        U8VlArray      *pCopy = U8VlArray_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a U8VLARRAY object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    U8VLARRAY_DATA * U8VlArray_Copy (
        U8VLARRAY_DATA  *this
    );


    /*!
     Get a data element in the array given its index (relative to 1).
     The first byte of the element will be its length including the
     first byte.
     @param     this    object pointer
     @param     index   data element number relative to 1
     @return    if successful, the address of the data element;
                otherwise, NULL.
     @warning   The data element returned should NOT be changed in
                length.
     */
    uint8_t *       U8VlArray_Get (
        U8VLARRAY_DATA	*this,
        uint32_t        index
    );

   
    U8VLARRAY_DATA *   U8VlArray_Init (
        U8VLARRAY_DATA     *this
    );


    ERESULT         U8VlArray_InsertData (
        U8VLARRAY_DATA  *this,
        uint32_t        index,
        uint8_t         *pData
    );


    /*!
     Set up a previously existing managed space for this object.
     @param     this    object pointer
     @param     pData   pointer to space to be managed
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         U8VlArray_SetupExternal (
        U8VLARRAY_DATA  *this,
        uint8_t         *pData
    );
    
 
    /*!
     Set up a new managed space controlled by this object.
     @param     this    object pointer
     @param     size    total size of the managed space, (> 1 and < 256)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         U8VlArray_SetupSize (
        U8VLARRAY_DATA  *this,
        uint32_t        size
    );


#ifdef  U8VLARRAY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = U8VlArray_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     U8VlArray_ToJson (
        U8VLARRAY_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = U8VlArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    U8VlArray_ToDebugString (
        U8VLARRAY_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* U8VLARRAY_H */

