// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   W32Str_internal.h
 *	Generated 08/14/2015 07:22:10
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




#ifndef W32STR_INTERNAL_H
#define	W32STR_INTERNAL_H


#include        <W32Str.h>
#include        <array_internal.h>
#include        <JsonIn.h>
#include        <Path.h>

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct W32Str_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    ARRAY_DATA      super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data

};
#pragma pack(pop)

    extern
    const
    W32STR_VTBL     W32Str_Vtbl;



    // Internal Functions
    void            W32Str_Dealloc(
        OBJ_ID          objId
    );

    
    /*!
     Parse the object from an established parser.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT     W32Str_ParseJsonFields (
        JSONIN_DATA     *pParser,
        W32STR_DATA     *pObject
    );


    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    W32STR_DATA *   W32Str_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    void *          W32Str_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );

    
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = W32Str_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Str_ToJson (
        W32STR_DATA     *this
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
    ERESULT         W32Str_ToJsonFields (
        W32STR_DATA     *this,
        ASTR_DATA       *pStr
    );


#ifdef NDEBUG
#else
    bool			W32Str_Validate(
        W32STR_DATA     *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* WSTR_INTERNAL_H */

