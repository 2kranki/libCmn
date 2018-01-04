// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   value_internal.h
 *	Generated 08/26/2017 09:50:28
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




#include    <value.h>
#include    <jsonIn.h>


#ifndef VALUE_INTERNAL_H
#define	VALUE_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct value_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint16_t        type;           // Value Type (see VALUE_TYPE)
    uint16_t        reserved;
    union {
        int8_t          i8;
        int16_t         i16;
        int32_t         i32;
        int64_t			i64;
        //        int128_t		i128;
        uint8_t         u8;
        uint16_t        u16;
        uint32_t        u32;
        uint64_t		u64;
        //        uint128_t		u128;
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
    const
    struct value_class_data_s  value_ClassObj;

    extern
    const
    VALUE_VTBL         value_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            value_setLastError(
        VALUE_DATA     *this,
        ERESULT         value
    );


    void            value_Dealloc(
        OBJ_ID          objId
    );


    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    VALUE_DATA *    value_ParseObject(
        JSONIN_DATA     *pParser
    );
    
    
    void *          value_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     value_ToJSON(
        VALUE_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			value_Validate(
        VALUE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* VALUE_INTERNAL_H */

