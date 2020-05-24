// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Number_internal.h
 *  Generated 05/23/11 11:24:01
 *
 * Notes:
 *  --  N/A
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




#include        <Number.h>
#include        <JsonIn.h>


#ifndef NUMBER_INTERNAL_H
#define NUMBER_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Number_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
    #define NUMBER_FLAG_SIGNED  OBJ_FLAG_USER1

    // Common Data
    uint16_t        reserved;
    uint16_t        type;               // See NUMBER_TYPE;
    union {
        int16_t         i16;                // int16
        int32_t         i32;                // int32
        int64_t            i64;                // int64
//        int128_t        i128;               // int128
        uint16_t        u16;                // uint16
        uint32_t        u32;                // uint32
        uint64_t        u64;                // uint64
//        uint128_t        u128;               // uint128
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        double          flt;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        double          flt;
#endif
    };

};
#pragma pack(pop)

    extern
    struct Number_class_data_s  Number_ClassObj;

    extern
    const
    NUMBER_VTBL         Number_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NUMBER_SINGLETON
    NUMBER_DATA *   Number_getSingleton (
        void
    );

    bool            Number_setSingleton (
     NUMBER_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Number_getSuperVtbl (
        NUMBER_DATA     *this
    );


    ERESULT         Number_Assign (
        NUMBER_DATA    *this,
        NUMBER_DATA    *pOther
    );


    NUMBER_DATA *   Number_Copy (
        NUMBER_DATA     *this
    );


    void            Number_Dealloc (
        OBJ_ID          objId
    );


    uint32_t        Number_DescToType(
        const char      *pValue
    );


#ifdef  NUMBER_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    NUMBER_DATA *   Number_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Number_ParseJsonFields (
        JSONIN_DATA     *pParser,
        NUMBER_DATA     *pObject
    );
#endif


    void *          Number_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  NUMBER_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Number_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Number_ToJson (
        NUMBER_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Number_ToJsonFields (
        NUMBER_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif


    const char *   Number_TypeToDesc(
        uint32_t        value
    );


#ifdef NDEBUG
#else
    bool            Number_Validate (
        NUMBER_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* NUMBER_INTERNAL_H */

