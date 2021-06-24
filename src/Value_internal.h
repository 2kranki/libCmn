// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Value_internal.h
 *	Generated 12/31/2019 15:27:11
 *
 * Notes:
 *  --	N/A
 *
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




#include        <Value.h>
#include        <JsonIn.h>


#ifndef VALUE_INTERNAL_H
#define	VALUE_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Value_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        type;           // Value Type (see VALUE_TYPE)
    uint16_t        misc16;
    uint32_t        user;           // User Specified
    OBJ_ID          pOther;
    union {
        int8_t          i8;
        int16_t         i16;
        int32_t         i32;
        int64_t         i64;
        //        int128_t        i128;
        uint8_t         u8;
        uint16_t        u16;
        uint32_t        u32;
        uint64_t        u64;
        //        uint128_t        u128;
        double          flt;
        OBJ_ID          pObject;
        struct {
            uint32_t        length;
            uint8_t         *pData;
        } data;
    } value;

};
#pragma pack(pop)

    extern
    struct Value_class_data_s  Value_ClassObj;

    extern
    const
    VALUE_VTBL         Value_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  VALUE_SINGLETON
    VALUE_DATA *     Value_getSingleton (
        void
    );

    bool            Value_setSingleton (
     VALUE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Value_getSuperVtbl (
        VALUE_DATA     *this
    );


    void            Value_Dealloc (
        OBJ_ID          objId
    );


#ifdef  VALUE_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    VALUE_DATA *    Value_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Value_ParseJsonFields(
        JSONIN_DATA     *pParser,
        VALUE_DATA      *pObject
    );
#endif


    void *          Value_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  VALUE_JSON_SUPPORT
    ASTR_DATA *     Value_ToJson (
        VALUE_DATA      *this
    );


    ERESULT         Value_ToJsonFields (
        VALUE_DATA      *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			Value_Validate (
        VALUE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* VALUE_INTERNAL_H */

