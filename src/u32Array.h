// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Dynamic Array of uint32_t (u32Array) Header
//****************************************************************
/*
 * Program
 *          Dynamic Array of uint32_t (u32Array)
 * Purpose
 *			This object provides a dynamic array of uint32_t entries.
 *
 * Remarks
 *	1.      All offsets or indices are relative to 1, not 0. 0 is
 *          considered before the beginning of the array if used
 *          as an offset otherwise an error.
 *  2.      This object uses OBJ_FLAG_USER1.
 *
 * History
 *	08/07/2015 Generated
 *  03/16/2020 Added Zero() and User property.
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


#ifndef         U32ARRAY_H
#define         U32ARRAY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct u32Array_data_s	U32ARRAY_DATA;

    typedef struct u32Array_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fat16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FBSI_DATA *);
    } U32ARRAY_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    U32ARRAY_DATA * u32Array_Alloc(
        void
    );
    
    
    OBJ_ID          u32Array_Class(
        void
    );
    
    
    U32ARRAY_DATA * u32Array_New(
        void
    );
    
    U32ARRAY_DATA * u32Array_NewWithSize(
        uint32_t        size
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            u32Array_setBigEndian(
        U32ARRAY_DATA   *this,
        bool            value
    );
    
    
    uint32_t *      u32Array_getData(
        U32ARRAY_DATA    *this
    );
    
    
    uint32_t        u32Array_getSize(
        U32ARRAY_DATA    *this
    );
    
    /*! Property: User Data Pointer
     This property is completely optional. It is used
     to link other data to this array.
     */
    void *          u32Array_getUser(
        U32ARRAY_DATA   *this
    );

    bool            u32Array_setUser(
        U32ARRAY_DATA   *this,
        void            *pValue
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         u32Array_AppendData(
        U32ARRAY_DATA	*this,
        uint32_t        data
    );
    
    
    ERESULT         u32Array_Assign(
        U32ARRAY_DATA	*this,
        U32ARRAY_DATA	*pOther
    );
    
    
    U32ARRAY_DATA * u32Array_Copy(
        U32ARRAY_DATA	*this
    );
    
    
    uint32_t        u32Array_Delete(
        U32ARRAY_DATA	*this,
        uint32_t        index
    );
    
    
    uint32_t        u32Array_DeleteFirst(
        U32ARRAY_DATA	*this
    );
    
    
    uint32_t        u32Array_DeleteLast(
        U32ARRAY_DATA	*this
    );
    
    
    // If an error occurs, Get() returns 0.
    uint32_t        u32Array_Get(
        U32ARRAY_DATA	*this,
        uint32_t        index
    );


    uint32_t        u32Array_GetFirst(
        U32ARRAY_DATA	*this
    );
    
    uint32_t        u32Array_GetLast(
        U32ARRAY_DATA	*this
    );
    
    
    U32ARRAY_DATA *  u32Array_Init(
        U32ARRAY_DATA   *this
    );


    ERESULT         u32Array_InsertData(
        U32ARRAY_DATA   *this,
        uint32_t        index,
        uint32_t        data
    );
    
    
    /*!
     Copy and sort both arrays given and then merge the two new
     arrays in numerical order removing duplicates.
     @param     this    object pointer
     @param     pOther  object pointer
     @return    If successful, a new u32Array object which must
                be released, otherwise OBJ_NIL.
     */
    U32ARRAY_DATA * u32Array_Merge(
        U32ARRAY_DATA    *this,
        U32ARRAY_DATA    *pOther
    );
    
    
    ERESULT         u32Array_SetData(
        U32ARRAY_DATA   *this,
        uint32_t        index,
        uint32_t        data
    );
    
    
    ERESULT         u32Array_SortAscending(
        U32ARRAY_DATA   *this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = u32Array_ToDebugString(pObj,4);
     @endcode
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     u32Array_ToDebugString(
        U32ARRAY_DATA   *this,
        int             indent
    );

    
    ERESULT         u32Array_WriteToFile(
        U32ARRAY_DATA   *this,
        PATH_DATA       *pPath
    );
    
    
    /*!
     Zero the entire array.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error code.
     */
    ERESULT         u32Array_Zero(
        U32ARRAY_DATA   *this
    );


    
#ifdef	__cplusplus
}
#endif

#endif	/* U32ARRAY_H */

