// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ObjVLink_internal.h
 *	Generated 01/14/2020 16:31:30
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




#include        <ObjVLink.h>
#include        <i32Array.h>
#include        <JsonIn.h>


#ifndef OBJVLINK_INTERNAL_H
#define	OBJVLINK_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct ObjVLink_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    OBJ_DATA        *pObj;
    int32_t         index;
    int32_t         left;
    int32_t         middle;
    int32_t         misc;
    int32_t         parent;
    int32_t         right;
    I32ARRAY_DATA   *pArray;

};
#pragma pack(pop)

    extern
    struct ObjVLink_class_data_s  ObjVLink_ClassObj;

    extern
    const
    OBJVLINK_VTBL         ObjVLink_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OBJVLINK_SINGLETON
    OBJVLINK_DATA *     ObjVLink_getSingleton (
        void
    );

    bool            ObjVLink_setSingleton (
     OBJVLINK_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  ObjVLink_getSuperVtbl (
        OBJVLINK_DATA     *this
    );


    OBJVLINK_DATA *     ObjVLink_Copy (
        OBJVLINK_DATA     *this
    );


    void            ObjVLink_Dealloc (
        OBJ_ID          objId
    );


#ifdef  OBJVLINK_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    OBJVLINK_DATA *       ObjVLink_ParseJsonObject (
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
    ERESULT     ObjVLink_ParseJsonFields(
        JSONIN_DATA     *pParser,
        OBJVLINK_DATA     *pObject
    );
#endif


    void *          ObjVLink_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  OBJVLINK_JSON_SUPPORT
    ASTR_DATA *     ObjVLink_ToJson (
        OBJVLINK_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			ObjVLink_Validate (
        OBJVLINK_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJVLINK_INTERNAL_H */

