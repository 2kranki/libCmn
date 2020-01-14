// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          I32ARRAY Console Transmit Task (i32Array) Header
//****************************************************************
/*
 * Program
 *			Separate i32Array (i32Array)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate i32Array to run things without complications
 *          of interfering with the main i32Array. A i32Array may be 
 *          called a i32Array on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	01/20/2018 Generated
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


#ifndef         I32ARRAY_H
#define         I32ARRAY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct i32Array_data_s	I32ARRAY_DATA;    // Inherits from OBJ.

    typedef struct i32Array_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in i32Array_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(I32ARRAY_DATA *);
    } I32ARRAY_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to i32Array object if successful, otherwise OBJ_NIL.
     */
    I32ARRAY_DATA *     i32Array_Alloc(
        void
    );
    
    
    OBJ_ID              i32Array_Class(
        void
    );
    
    
    I32ARRAY_DATA *     i32Array_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            i32Array_setBigEndian(
        I32ARRAY_DATA   *this,
        bool            value
    );
    
    
    int32_t *       i32Array_getData(
        I32ARRAY_DATA    *this
    );
    
    
    uint32_t        i32Array_getSize(
        I32ARRAY_DATA    *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         i32Array_AppendData(
        I32ARRAY_DATA   *this,
        int32_t         data
    );
    
    
    ERESULT         i32Array_Assign(
        I32ARRAY_DATA   *this,
        I32ARRAY_DATA   *pOther
    );
    
    
    I32ARRAY_DATA * i32Array_Copy(
        I32ARRAY_DATA   *this
    );
    
    
    int32_t         i32Array_Delete(
        I32ARRAY_DATA   *this,
        uint32_t        index
    );
    
    
    int32_t         i32Array_DeleteFirst(
        I32ARRAY_DATA   *this
    );
    
    
    int32_t         i32Array_DeleteLast(
        I32ARRAY_DATA   *this
    );
    
    
    // If an error occurs, Get() returns 0.
    int32_t         i32Array_Get(
        I32ARRAY_DATA   *this,
        uint32_t        index
    );
    
    
    int32_t         i32Array_GetFirst(
        I32ARRAY_DATA   *this
    );
    
    int32_t         i32Array_GetLast(
        I32ARRAY_DATA   *this
    );
    
    
    I32ARRAY_DATA * i32Array_Init(
        I32ARRAY_DATA   *this
    );


    ERESULT         i32Array_InsertData(
        I32ARRAY_DATA   *this,
        uint32_t        index,
        int32_t         data
    );
    
    
    ERESULT         i32Array_SetData(
        I32ARRAY_DATA   *this,
        uint32_t        index,
        int32_t         data
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = i32Array_ToDebugString(this,4);
     @endcode 
     @param     this    I32ARRAY object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    i32Array_ToDebugString(
        I32ARRAY_DATA     *this,
        int             indent
    );
    
    
    ERESULT         i32Array_WriteToFile(
        I32ARRAY_DATA   *this,
        PATH_DATA       *pPath
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* I32ARRAY_H */

