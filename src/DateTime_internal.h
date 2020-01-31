// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   DateTime_internal.h
 *	Generated 01/29/2020 13:34:28
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




#include        <DateTime.h>
#include        <JsonIn.h>


#ifndef DATETIME_INTERNAL_H
#define	DATETIME_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct DateTime_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint64_t        time;           // UTC Date & Time encoded to binary
    //                              // See DateTime_FromUInt64() & DateTime_ToUInt64()
    //                              // for details.

};
#pragma pack(pop)

    extern
    struct DateTime_class_data_s  DateTime_ClassObj;

    extern
    const
    DATETIME_VTBL         DateTime_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  DATETIME_SINGLETON
    DATETIME_DATA *     DateTime_getSingleton (
        void
    );

    bool            DateTime_setSingleton (
     DATETIME_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  DateTime_getSuperVtbl (
        DATETIME_DATA     *this
    );


    ERESULT         DateTime_Assign (
        DATETIME_DATA    *this,
        DATETIME_DATA    *pOther
    );


    DATETIME_DATA *       DateTime_Copy (
        DATETIME_DATA     *this
    );


    void            DateTime_Dealloc (
        OBJ_ID          objId
    );


#ifdef  DATETIME_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    DATETIME_DATA *       DateTime_ParseJsonObject (
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
    ERESULT         DateTime_ParseJsonFields(
        JSONIN_DATA     *pParser,
        DATETIME_DATA     *pObject
    );
#endif


    void *          DateTime_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  DATETIME_JSON_SUPPORT
    ASTR_DATA *     DateTime_ToJson (
        DATETIME_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			DateTime_Validate (
        DATETIME_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* DATETIME_INTERNAL_H */

