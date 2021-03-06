// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   AStr_internal.h
 *	Generated 09/19/2015 10:15:50
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




#ifndef ASTR_INTERNAL_H
#define	ASTR_INTERNAL_H


#include    <AStr.h>
#include    <File.h>
#include    <JsonIn.h>
#include    <Path.h>
#include    <str.h>
#include    <ObjArray.h>
#include    <array_internal.h>
#include    <utf8.h>

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct AStr_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    ARRAY_DATA      *pData;
};
#pragma pack(pop)

    extern
    const
    ASTR_VTBL       AStr_Vtbl;
    extern
    const
    struct AStr_class_data_s   AStr_ClassObj;


    // Internal Functions
    void            AStr_Dealloc(
        OBJ_ID          objId
    );

    
#ifdef  ASTR_JSON_SUPPORT
    /*!
     Parse the object from an established parser.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         AStr_ParseJsonFields(
        JSONIN_DATA     *pParser,
        ASTR_DATA       *pObject
    );


    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new null object if successful, otherwise, OBJ_NIL
     @warning   Returned null object must be released.
     */
    ASTR_DATA *     AStr_ParseJsonObject(
        JSONIN_DATA     *pParser
    );


    /*!
     Append the json representation of the object's fields to the given
     string.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         AStr_ToJsonFields(
        ASTR_DATA       *this,
        ASTR_DATA       *pStr

    );
#endif
    
    
    void *          AStr_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );

    
#ifdef NDEBUG
#else
    bool			AStr_Validate(
        ASTR_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* ASTR_INTERNAL_H */

