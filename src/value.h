// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Value  (value) Header
//****************************************************************
/*
 * Program
 *			Value (value)
 * Purpose
 *			This object provides a way to create an object from
 *          the most common forms of data including just raw 
 *          memory.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal value. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	08/26/2017 Generated
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


#ifndef         VALUE_H
#define         VALUE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct value_data_s	VALUE_DATA;    // Inherits from OBJ.

    typedef struct value_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in value_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(VALUE_DATA *);
    } VALUE_VTBL;


    typedef enum value_type_e {
        VALUE_TYPE_UNKNOWN=0,
        VALUE_TYPE_FLOAT,           // 32-bit Float
        VALUE_TYPE_DOUBLE,          // 64-bit Float
        VALUE_TYPE_INT16,           // int16_t
        VALUE_TYPE_INT32,           // int32_t
        VALUE_TYPE_INT64,           // int64_t
        VALUE_TYPE_UINT16,          // int16_t
        VALUE_TYPE_UINT32,          // int32_t
        VALUE_TYPE_UINT64,          // int64_t
        VALUE_TYPE_OBJECT,          // Any object
        VALUE_TYPE_DATA,            // Any data (pointer and length) (pointer and length
        //                          // must be valid for life of object)
        VALUE_TYPE_DATA_FREE,       // Any data (pointer and length) which will be freed
        //                          // using mem_Free() when no longer needed (pointer
        //                          // and length must be valid for life of object)
        VALUE_TYPE_HIGHEST
    } VALUE_TYPE;
    
    

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
     @return:   pointer to value object if successful, otherwise OBJ_NIL.
     */
    VALUE_DATA *     value_Alloc(
        void
    );
    
    
    VALUE_DATA *     value_New(
        void
    );
    
    VALUE_DATA *    value_NewData(
        int32_t         length,
        void            *pData
    );
    
    VALUE_DATA *    value_NewDataFree(
        int32_t         length,
        void            *pData
    );
    
    VALUE_DATA *    value_NewI16(
        int16_t         value
    );
    
    VALUE_DATA *    value_NewI32(
        int32_t         value
    );
    
    VALUE_DATA *    value_NewI64(
        int64_t         value
    );
    
    VALUE_DATA *    value_NewObject(
        OBJ_DATA        *pValue
    );
    
    VALUE_DATA *    value_NewU16(
        uint16_t        value
    );
    
    VALUE_DATA *    value_NewU32(
        uint32_t        value
    );
    
    VALUE_DATA *    value_NewU64(
        uint64_t        value
    );
    
    
    VALUE_DATA *    value_NewFromJSONString(
        ASTR_DATA       *pString
    );
    
    VALUE_DATA *    value_NewFromJSONStringA(
        const
        char            *pString
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    int16_t         value_getI16(
        VALUE_DATA      *this
    );
    
    bool            value_setI16(
        VALUE_DATA      *this,
        int16_t         value
    );
    
    
    int32_t         value_getI32(
        VALUE_DATA      *this
    );
    
    bool            value_setI32(
        VALUE_DATA      *this,
        int32_t         value
    );
    
    
    int64_t         value_getI64(
        VALUE_DATA      *this
    );
    
    bool            value_setI64(
        VALUE_DATA      *this,
        int64_t         value
    );
    
    
    ERESULT         value_getLastError(
        VALUE_DATA      *this
    );


    OBJ_DATA *      value_getObject(
        VALUE_DATA      *this
    );
    
    bool            value_setObject(
        VALUE_DATA      *this,
        OBJ_DATA        *pValue
    );
    
    
    uint16_t        value_getType(
        VALUE_DATA      *this
    );
    
    
    uint16_t        value_getU16(
        VALUE_DATA      *this
    );
    
    bool            value_setU16(
        VALUE_DATA      *this,
        uint16_t        value
    );
    
    
    uint32_t        value_getU32(
        VALUE_DATA      *this
    );
    
    bool            value_setU32(
        VALUE_DATA      *this,
        uint32_t        value
    );
    
    
    uint64_t        value_getU64(
        VALUE_DATA      *this
    );
    
    bool            value_setU64(
        VALUE_DATA      *this,
        uint64_t        value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    VALUE_DATA *   value_Init(
        VALUE_DATA     *this
    );

    VALUE_DATA *    value_InitData(
        VALUE_DATA      *this,
        int32_t         length,
        void            *pData
    );
    
    VALUE_DATA *    value_InitDataFree(
        VALUE_DATA      *this,
        int32_t         length,
        void            *pData
    );
    
    VALUE_DATA *    value_InitI16(
        VALUE_DATA      *this,
        int16_t         value
    );
    
    VALUE_DATA *    value_InitI32(
        VALUE_DATA      *this,
        int32_t         value
    );
    
    VALUE_DATA *    value_InitI64(
        VALUE_DATA      *this,
        int64_t         value
    );
    
    VALUE_DATA *    value_InitObject(
        VALUE_DATA      *this,
        OBJ_DATA        *pValue
    );
    
    VALUE_DATA *    value_InitU16(
        VALUE_DATA      *this,
        uint16_t        value
    );
    
    VALUE_DATA *    value_InitU32(
        VALUE_DATA      *this,
        uint32_t        value
    );
    
    VALUE_DATA *    value_InitU64(
        VALUE_DATA      *this,
        uint64_t        value
    );
    

    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = value_ToDebugString(this,4);
     @endcode:
     @param:    this    VALUE object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    value_ToDebugString(
        VALUE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* VALUE_H */

