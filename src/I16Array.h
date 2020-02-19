// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Signed 16-Bit Array (I16Array) Header
//****************************************************************
/*
 * Program
 *			Signed 16-Bit Array (I16Array)
 * Purpose
 *          This object provides a dynamic array of int16_t data
 *          elements.
 *
 * Remarks
 *    1.    All offsets or indices are relative to 1, not 0. 0 is
 *          considered before the beginning of the array if used
 *          as an offset otherwise an error.
 *
 * History
 *	02/19/2020 Generated
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


#ifndef         I16ARRAY_H
#define         I16ARRAY_H


//#define   I16ARRAY_IS_IMMUTABLE     1
#define   I16ARRAY_JSON_SUPPORT     1
//#define   I16ARRAY_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct I16Array_data_s	I16ARRAY_DATA;            // Inherits from OBJ
    typedef struct I16Array_class_data_s I16ARRAY_CLASS_DATA;   // Inherits from OBJ

    typedef struct I16Array_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in I16Array_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(I16ARRAY_DATA *);
    } I16ARRAY_VTBL;

    typedef struct I16Array_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in I16Array_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(I16ARRAY_DATA *);
    } I16ARRAY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  I16ARRAY_SINGLETON
    I16ARRAY_DATA * I16Array_Shared (
        void
    );

    void            I16Array_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to I16Array object if successful, otherwise OBJ_NIL.
     */
    I16ARRAY_DATA * I16Array_Alloc (
        void
    );
    
    
    OBJ_ID          I16Array_Class (
        void
    );
    
    
    I16ARRAY_DATA * I16Array_New (
        void
    );
    
    
#ifdef  I16ARRAY_JSON_SUPPORT
    I16ARRAY_DATA * I16Array_NewFromJsonString (
        ASTR_DATA       *pString
    );

    I16ARRAY_DATA * I16Array_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            I16Array_setBigEndian(
        I16ARRAY_DATA   *this,
        bool            value
    );


    uint32_t        I16Array_getSize(
        I16ARRAY_DATA    *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         I16Array_AppendData (
        I16ARRAY_DATA   *this,
        uint16_t        data
    );


    ERESULT         I16Array_AppendFile (
        I16ARRAY_DATA    *this,
        PATH_DATA       *pPath
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = I16Array_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another I16ARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         I16Array_Assign (
        I16ARRAY_DATA   *this,
        I16ARRAY_DATA   *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other,
                otherwise ERESULT_SUCCESS_UNEQUAL
     */
    ERESULT         I16Array_Compare (
        I16ARRAY_DATA     *this,
        I16ARRAY_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        I16Array      *pCopy = I16Array_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a I16ARRAY object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    I16ARRAY_DATA * I16Array_Copy (
        I16ARRAY_DATA   *this
    );


    uint16_t        I16Array_Delete (
        I16ARRAY_DATA   *this,
        uint32_t        index
    );


    uint16_t        I16Array_DeleteFirst (
        I16ARRAY_DATA   *this
    );


    uint16_t        I16Array_DeleteLast (
        I16ARRAY_DATA    *this
    );


    // If an error occurs, Get() returns 0.
    uint16_t        I16Array_Get (
        I16ARRAY_DATA   *this,
        uint32_t        index
    );


    uint16_t        I16Array_GetFirst (
        I16ARRAY_DATA    *this
    );

    uint16_t        I16Array_GetLast (
        I16ARRAY_DATA    *this
    );


    I16ARRAY_DATA *   I16Array_Init (
        I16ARRAY_DATA     *this
    );


    ERESULT         I16Array_InsertData (
        I16ARRAY_DATA   *this,
        uint32_t        index,
        uint16_t        data
    );


    ERESULT         I16Array_SetData (
        I16ARRAY_DATA   *this,
        uint32_t        index,
        uint16_t        data
    );


#ifdef  I16ARRAY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = I16Array_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     I16Array_ToJson (
        I16ARRAY_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = I16Array_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    I16Array_ToDebugString (
        I16ARRAY_DATA     *this,
        int             indent
    );
    
    
    ERESULT         I16Array_WriteToFile(
        I16ARRAY_DATA   *this,
        PATH_DATA       *pPath
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* I16ARRAY_H */

