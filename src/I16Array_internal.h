// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   I16Array_internal.h
 *	Generated 02/19/2020 09:52:11
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




#include        <I16Array.h>
#include        <array_internal.h>
#include        <JsonIn.h>


#ifndef I16ARRAY_INTERNAL_H
#define	I16ARRAY_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct I16Array_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    ARRAY_DATA      super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint8_t         fBigEndian;     // FALSE == little endian, TRUE == Big Endian
    uint8_t         rsvd8;
    uint16_t        rsvd16;

};
#pragma pack(pop)

    extern
    struct I16Array_class_data_s  I16Array_ClassObj;

    extern
    const
    I16ARRAY_VTBL         I16Array_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  I16ARRAY_SINGLETON
    I16ARRAY_DATA * I16Array_getSingleton (
        void
    );

    bool            I16Array_setSingleton (
     I16ARRAY_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    ARRAY_DATA *    I16Array_getArray (
        I16ARRAY_DATA   *this
    );


    OBJ_IUNKNOWN *  I16Array_getSuperVtbl (
        I16ARRAY_DATA     *this
    );


    ERESULT         I16Array_Assign (
        I16ARRAY_DATA    *this,
        I16ARRAY_DATA    *pOther
    );


    I16ARRAY_DATA * I16Array_Copy (
        I16ARRAY_DATA     *this
    );


    void            I16Array_Dealloc (
        OBJ_ID          objId
    );


#ifdef  I16ARRAY_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    I16ARRAY_DATA * I16Array_ParseJsonObject (
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
    ERESULT         I16Array_ParseJsonFields (
        JSONIN_DATA     *pParser,
        I16ARRAY_DATA     *pObject
    );
#endif


    void *          I16Array_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
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


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         I16Array_ToJsonFields (
        I16ARRAY_DATA   *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			I16Array_Validate (
        I16ARRAY_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* I16ARRAY_INTERNAL_H */

