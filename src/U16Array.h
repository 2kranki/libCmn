// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Unsigned 16-Bit Dynamic Array (U16Array) Header
//****************************************************************
/*
 * Program
 *			Unsigned 16-Bit Dynamic Array (U16Array)
 * Purpose
 *			This object provides a dynamic array of uint16_t data
 *          elements.
 *
 * Remarks
 *    1.    All offsets or indices are relative to 1, not 0. 0 is
 *          considered before the beginning of the array if used
 *          as an offset otherwise an error.
 *
 * History
 *  08/07/2015 Generated
 *	02/18/2020 Rgenerated and JSON support added
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


#ifndef         U16ARRAY_H
#define         U16ARRAY_H


//#define   U16ARRAY_IS_IMMUTABLE     1
#define   U16ARRAY_JSON_SUPPORT     1
//#define   U16ARRAY_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct U16Array_data_s	U16ARRAY_DATA;            // Inherits from OBJ
    typedef struct U16Array_class_data_s U16ARRAY_CLASS_DATA;   // Inherits from OBJ

    typedef struct U16Array_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in U16Array_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(U16ARRAY_DATA *);
    } U16ARRAY_VTBL;

    typedef struct U16Array_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in U16Array_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(U16ARRAY_DATA *);
    } U16ARRAY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  U16ARRAY_SINGLETON
    U16ARRAY_DATA * U16Array_Shared (
        void
    );

    void            U16Array_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to U16Array object if successful, otherwise OBJ_NIL.
     */
    U16ARRAY_DATA * U16Array_Alloc (
        void
    );
    
    
    OBJ_ID          U16Array_Class (
        void
    );
    
    
    U16ARRAY_DATA * U16Array_New (
        void
    );
    
    
#ifdef  U16ARRAY_JSON_SUPPORT
    U16ARRAY_DATA * U16Array_NewFromJsonString (
        ASTR_DATA       *pString
    );

    U16ARRAY_DATA * U16Array_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            U16Array_setBigEndian(
        U16ARRAY_DATA   *this,
        bool            value
    );


    uint32_t        U16Array_getSize(
        U16ARRAY_DATA    *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         U16Array_AppendData (
        U16ARRAY_DATA   *this,
        uint16_t        data
    );


    ERESULT         U16Array_AppendFile (
        U16ARRAY_DATA    *this,
        PATH_DATA       *pPath
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = U16Array_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another U16ARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         U16Array_Assign (
        U16ARRAY_DATA   *this,
        U16ARRAY_DATA   *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other,
                otherwise ERESULT_SUCCESS_UNEQUAL
     */
    ERESULT         U16Array_Compare (
        U16ARRAY_DATA     *this,
        U16ARRAY_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        U16Array      *pCopy = U16Array_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a U16ARRAY object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    U16ARRAY_DATA * U16Array_Copy (
        U16ARRAY_DATA   *this
    );


    uint16_t        U16Array_Delete (
        U16ARRAY_DATA   *this,
        uint32_t        index
    );


    uint16_t        U16Array_DeleteFirst (
        U16ARRAY_DATA   *this
    );


    uint16_t        U16Array_DeleteLast (
        U16ARRAY_DATA    *this
    );


    // If an error occurs, Get() returns 0.
    uint16_t        U16Array_Get (
        U16ARRAY_DATA   *this,
        uint32_t        index
    );


    uint16_t        U16Array_GetFirst (
        U16ARRAY_DATA    *this
    );

    uint16_t        U16Array_GetLast (
        U16ARRAY_DATA    *this
    );


    U16ARRAY_DATA *   U16Array_Init (
        U16ARRAY_DATA     *this
    );


    ERESULT         U16Array_InsertData (
        U16ARRAY_DATA   *this,
        uint32_t        index,
        uint16_t        data
    );


    ERESULT         U16Array_SetData (
        U16ARRAY_DATA   *this,
        uint32_t        index,
        uint16_t        data
    );


#ifdef  U16ARRAY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = U16Array_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     U16Array_ToJson (
        U16ARRAY_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = U16Array_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     U16Array_ToDebugString (
        U16ARRAY_DATA   *this,
        int             indent
    );
    
    
    ERESULT         U16Array_WriteToFile(
        U16ARRAY_DATA   *this,
        PATH_DATA       *pPath
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* U16ARRAY_H */

