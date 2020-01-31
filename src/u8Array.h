// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Dynamic Array of uint8_t (u8Array) Header
//****************************************************************
/*
 * Program
 *          Dynamic Array of uint8_t (u8Array)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate u8Array to run things without complications
 *          of interfering with the main u8Array. A u8Array may be
 *          called a u8Array on other O/S's.
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
#include        <Path.h>


#ifndef         U8ARRAY_H
#define         U8ARRAY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // U8ARRAY_DATA and U8ARRAY_VTBL are defined in "cmn.h"



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    U8ARRAY_DATA *  u8Array_Alloc(
        void
    );
    
    
    OBJ_ID          u8Array_Class(
        void
    );
    
    
    U8ARRAY_DATA *  u8Array_New(
        void
    );
    
    
    U8ARRAY_DATA *  u8Array_NewFromBuffer(
        uint32_t        size,
        uint8_t         *pData
    );
    
    
    U8ARRAY_DATA *  u8Array_NewFromFile(
        PATH_DATA       *pPath
    );
    
    
    U8ARRAY_DATA *  u8Array_NewFromJsonString(
        ASTR_DATA       *pString
    );

    
    U8ARRAY_DATA *  u8Array_NewFromJsonStringA(
        const
        char            *pString
    );

    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            u8Array_setBigEndian(
        U8ARRAY_DATA    *this,
        bool            value
    );
    
    
    uint8_t *       u8Array_getData(
        U8ARRAY_DATA    *this
    );
    
    
    uint16_t        u8Array_getMisc(
        U8ARRAY_DATA    *this
    );
    
    bool            u8Array_setMisc(
        U8ARRAY_DATA    *this,
        uint32_t        value
    );
    
    
    uint32_t        u8Array_getSize(
        U8ARRAY_DATA    *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Append Data to the top of the array.
     @param     this    object pointer
     @param     pOther  address of the u8Array data (must not be NULL)
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_ error.
     */
    ERESULT         u8Array_Append(
        U8ARRAY_DATA	*this,
        U8ARRAY_DATA	*pOther
    );
    
    
    /*!
     Append Buffer to the end of the array.
     @param     this    object pointer
     @param     length  length of the uint8_t data
     @param     pData   address of the uint8_t data (must not be NULL)
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_ error.
     */
    ERESULT         u8Array_AppendBuffer(
        U8ARRAY_DATA	*this,
        uint32_t        length,
        uint8_t         *pData
    );
    
    
    ERESULT         u8Array_AppendData(
        U8ARRAY_DATA	*this,
        uint8_t         data
    );
    
    
    ERESULT         u8Array_AppendFile(
        U8ARRAY_DATA    *this,
        PATH_DATA       *pPath
    );
    
    
    ERESULT         u8Array_Assign(
        U8ARRAY_DATA	*this,
        U8ARRAY_DATA	*pOther
    );
    
    
    U8ARRAY_DATA *  u8Array_Copy(
        U8ARRAY_DATA	*this
    );
    
    
    uint8_t         u8Array_Delete(
        U8ARRAY_DATA	*this,
        uint32_t        index
    );
    
    
    uint8_t         u8Array_DeleteFirst(
        U8ARRAY_DATA	*this
    );
    
    
    uint8_t         u8Array_DeleteLast(
        U8ARRAY_DATA	*this
    );
    
    
    // If an error occurs, Get() returns 0.
    uint8_t         u8Array_Get(
        U8ARRAY_DATA	*this,
        uint32_t        index
    );


    /*!
     Get a uint8_t from the index given and return to *pValue. The
     number is extracted in Little or Big Endian format given the
     Endian Property setting.
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_ error.
     */
    ERESULT         u8Array_GetU8(
        U8ARRAY_DATA	*this,
        uint32_t        index,
        uint8_t         *pValue
    );
    
    
    /*!
     Get a uint16_t from the index given and return to *pValue. The
     number is extracted in Little or Big Endian format given the
     Endian Property setting.
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_ error.
     */
    ERESULT         u8Array_GetU16(
        U8ARRAY_DATA	*this,
        uint32_t        index,
        uint16_t        *pValue
    );
    
    
    /*!
     Get a uint24_t from the index given and return to *pValue. The
     number is extracted in Little or Big Endian format given the
     Endian Property setting.
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_ error.
     */
    ERESULT         u8Array_GetU24(
        U8ARRAY_DATA	*this,
        uint32_t        index,
        uint32_t        *pValue
    );
    
    
    /*!
     Get a uint32_t from the index given and return to *pValue. The
     number is extracted in Little or Big Endian format given the
     Endian Property setting.
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_ error.
     */
    ERESULT         u8Array_GetU32(
        U8ARRAY_DATA	*this,
        uint32_t        index,
        uint32_t        *pValue
    );
    
    
    uint8_t         u8Array_GetFirst(
        U8ARRAY_DATA	*this
    );
    
    uint8_t         u8Array_GetLast(
        U8ARRAY_DATA	*this
    );
    
    
    U8ARRAY_DATA *  u8Array_Init(
        U8ARRAY_DATA    *this
    );


    ERESULT         u8Array_Insert(
        U8ARRAY_DATA    *this,
        uint32_t        index,
        uint8_t         data
    );
    
    
    // Insert Data at the specified index.
    // Index of 1 is same as at bottom and
    // Index of size+1 is same as at the top.
    ERESULT         u8Array_InsertData(
        U8ARRAY_DATA    *this,
        uint32_t        index,
        uint32_t        len,
        const
        uint8_t         *pData
    );
    
    
    /*!
     Put the given data into the array at the specified location.
     if the array needs to be expanded, '\0' are added as fill.
     Also, if the data size is too big for one byte, break the data
     up into multiple bytes using the endian type.
     @param     this    object pointer
     @param     index   index into the array (relative to 1)
     @param     data    data to be put into the array
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         u8Array_PutU8(
        U8ARRAY_DATA    *this,
        const
        uint32_t        index,
        const
        uint8_t         data
    );
    
    ERESULT         u8Array_PutU16(
        U8ARRAY_DATA    *this,
        const
        uint32_t        index,
        const
        uint16_t        data
    );
    
    ERESULT         u8Array_PutU24(
        U8ARRAY_DATA    *this,
        const
        uint32_t        index,
        const
        uint32_t        data
    );
    
    ERESULT         u8Array_PutU32(
        U8ARRAY_DATA    *this,
        const
        uint32_t        index,
        const
        uint32_t        data
    );
    
    
    ASTR_DATA *     u8Array_ToConstantString(
        U8ARRAY_DATA    *this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = u8Array_ToDebugString(pObj,4);
     @endcode
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     u8Array_ToDebugString(
        U8ARRAY_DATA    *this,
        int             indent
    );

    
    ASTR_DATA *     u8Array_ToJson (
        U8ARRAY_DATA    *this
    );

    
    bool            u8Array_Truncate (
        U8ARRAY_DATA    *this,
        uint32_t        value
    );


    ERESULT         u8Array_WriteToFile(
        U8ARRAY_DATA    *this,
        PATH_DATA       *pPath
    );
    
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* U8ARRAY_H */

