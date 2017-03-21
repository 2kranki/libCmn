// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Dynamic Array of uint32_t (u16Array) Header
//****************************************************************
/*
 * Program
 *          Dynamic Array of uint32_t (u16Array)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate u16Array to run things without complications
 *          of interfering with the main u16Array. A u16Array may be
 *          called a u16Array on other O/S's.
 *
 * Remarks
 *	1.      All offsets or indices are relative to 1, not 0. 0 is
 *          considered before the beginning of the array if used
 *          as an offset otherwise an error.
 *
 * History
 *	08/07/2015 Generated
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



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct u16Array_data_s	U16ARRAY_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    U16ARRAY_DATA * u16Array_Alloc(
    );
    
    
    U16ARRAY_DATA * u16Array_New(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            u16Array_setBigEndian(
        U16ARRAY_DATA   *this,
        bool            value
    );
    
    
    uint16_t *      u16Array_getData(
        U16ARRAY_DATA    *this
    );
    
    
    uint32_t        u16Array_getSize(
        U16ARRAY_DATA    *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         u16Array_AppendData(
        U16ARRAY_DATA	*this,
        uint16_t        data
    );
    
    
    ERESULT         u16Array_AppendFile(
        U16ARRAY_DATA	*this,
        PATH_DATA       *pPath
    );
    
    
    ERESULT         u16Array_Assign(
        U16ARRAY_DATA	*this,
        U16ARRAY_DATA	*pOther
    );
    
    
    U16ARRAY_DATA * u16Array_Copy(
        U16ARRAY_DATA	*this
    );
    
    
    uint16_t        u16Array_Delete(
        U16ARRAY_DATA	*this,
        uint32_t        index
    );
    
    
    uint16_t        u16Array_DeleteFirst(
        U16ARRAY_DATA	*this
    );
    
    
    uint16_t        u16Array_DeleteLast(
        U16ARRAY_DATA	*this
    );
    
    
    // If an error occurs, Get() returns 0.
    uint16_t        u16Array_Get(
        U16ARRAY_DATA	*this,
        uint32_t        index
    );


    uint16_t        u16Array_GetFirst(
        U16ARRAY_DATA	*this
    );
    
    uint16_t        u16Array_GetLast(
        U16ARRAY_DATA	*this
    );
    
    
    U16ARRAY_DATA *  u16Array_Init(
        U16ARRAY_DATA   *this
    );


    ERESULT         u16Array_InsertData(
        U16ARRAY_DATA   *this,
        uint32_t        index,
        uint16_t        data
    );
    
    
    ERESULT         u16Array_SetData(
        U16ARRAY_DATA   *this,
        uint32_t        index,
        uint16_t        data
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     u16Array_ToDebugString(
        U16ARRAY_DATA   *this,
        int             indent
    );

    
    ERESULT         u16Array_WriteToFile(
        U16ARRAY_DATA   *this,
        PATH_DATA       *pPath
    );
    
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* U16ARRAY_H */

