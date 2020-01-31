// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   I32Array_internal.h
 *	Generated 01/14/2020 18:29:58
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




#include        <I32Array.h>
#include        <array_internal.h>
#include        <JsonIn.h>
#include        <Path_internal.h>


#ifndef I32ARRAY_INTERNAL_H
#define	I32ARRAY_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct I32Array_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    ARRAY_DATA      super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define I32ARRAY_FLAG_BIGENDIAN OBJ_FLAG_USER1

    // Common Data

};
#pragma pack(pop)

    extern
    struct I32Array_class_data_s  I32Array_ClassObj;

    extern
    const
    I32ARRAY_VTBL         I32Array_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  I32ARRAY_SINGLETON
    I32ARRAY_DATA * I32Array_getSingleton (
        void
    );

    bool            I32Array_setSingleton (
     I32ARRAY_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  I32Array_getSuperVtbl (
        I32ARRAY_DATA     *this
    );


    I32ARRAY_DATA *     I32Array_Copy (
        I32ARRAY_DATA     *this
    );


    void            I32Array_Dealloc (
        OBJ_ID          objId
    );


#ifdef  I32ARRAY_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    I32ARRAY_DATA * I32Array_ParseJsonObject (
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
    ERESULT         I32Array_ParseJsonFields(
        JSONIN_DATA     *pParser,
        I32ARRAY_DATA   *pObject
    );
#endif


    void *          I32Array_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  I32ARRAY_JSON_SUPPORT
    ASTR_DATA *     I32Array_ToJson (
        I32ARRAY_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			I32Array_Validate (
        I32ARRAY_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* I32ARRAY_INTERNAL_H */

