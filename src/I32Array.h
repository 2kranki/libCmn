// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Variable Array of int32_t (I32Array) Header
//****************************************************************
/*
 * Program
 *			Variable Array of int32_t (I32Array)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate I32Array to run things without complications
 *          of interfering with the main I32Array. A I32Array may be 
 *          called a I32Array on other O/S's.
 *
 * Remarks
 *	1.      This object uses OBJ_FLAG_USER1.
 *
 * History
 *	01/14/2020 Generated
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


#ifndef         I32ARRAY_H
#define         I32ARRAY_H


#define   I32ARRAY_JSON_SUPPORT 1
//#define   I32ARRAY_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct I32Array_data_s	I32ARRAY_DATA;            // Inherits from OBJ
    typedef struct I32Array_class_data_s I32ARRAY_CLASS_DATA;   // Inherits from OBJ

    typedef struct I32Array_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in I32Array_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(I32ARRAY_DATA *);
    } I32ARRAY_VTBL;

    typedef struct I32Array_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in I32Array_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(I32ARRAY_DATA *);
    } I32ARRAY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  I32ARRAY_SINGLETON
    I32ARRAY_DATA * I32Array_Shared (
        void
    );

    void            I32Array_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to I32Array object if successful, otherwise OBJ_NIL.
     */
    I32ARRAY_DATA * I32Array_Alloc (
        void
    );
    
    
    OBJ_ID          I32Array_Class (
        void
    );
    
    
    I32ARRAY_DATA * I32Array_New (
        void
    );
    
    
#ifdef  I32ARRAY_JSON_SUPPORT
    I32ARRAY_DATA * I32Array_NewFromJsonString(
        ASTR_DATA       *pString
    );

    I32ARRAY_DATA * I32Array_NewFromJsonStringA(
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            I32Array_setBigEndian(
        I32ARRAY_DATA   *this,
        bool            value
    );


    int32_t *       I32Array_getData(
        I32ARRAY_DATA    *this
    );


    uint32_t        I32Array_getSize(
        I32ARRAY_DATA    *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         I32Array_AppendData(
        I32ARRAY_DATA   *this,
        int32_t         data
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = I32Array_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another I32ARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         I32Array_Assign (
        I32ARRAY_DATA   *this,
        I32ARRAY_DATA   *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        I32Array      *pCopy = I32Array_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a I32ARRAY object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    I32ARRAY_DATA * I32Array_Copy (
        I32ARRAY_DATA   *this
    );


    int32_t         I32Array_Delete(
        I32ARRAY_DATA   *this,
        uint32_t        index
    );


    int32_t         I32Array_DeleteFirst(
        I32ARRAY_DATA   *this
    );


    int32_t         I32Array_DeleteLast(
        I32ARRAY_DATA   *this
    );


    // If an error occurs, Get() returns 0.
    int32_t         I32Array_Get(
        I32ARRAY_DATA   *this,
        uint32_t        index
    );


    int32_t         I32Array_GetFirst(
        I32ARRAY_DATA   *this
    );

    int32_t         I32Array_GetLast(
        I32ARRAY_DATA   *this
    );


    I32ARRAY_DATA * I32Array_Init (
        I32ARRAY_DATA   *this
    );


    /*!
     Inserts the data before the index given.
     @param     this    object pointer
     @param     index   index into array (0 < index <= array_size)
     @param     data    data to insert
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
    */
    ERESULT         I32Array_InsertData(
        I32ARRAY_DATA   *this,
        uint32_t        index,
        int32_t         data
    );


    ERESULT         I32Array_SetData(
        I32ARRAY_DATA   *this,
        uint32_t        index,
        int32_t         data
    );


    ERESULT         I32Array_SortAscending(
        I32ARRAY_DATA   *this
    );


#ifdef  I32ARRAY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = I32Array_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     I32Array_ToJson(
        I32ARRAY_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = I32Array_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    I32Array_ToDebugString (
        I32ARRAY_DATA     *this,
        int             indent
    );
    
    
    ERESULT         I32Array_WriteToFile(
        I32ARRAY_DATA   *this,
        PATH_DATA       *pPath
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* I32ARRAY_H */

