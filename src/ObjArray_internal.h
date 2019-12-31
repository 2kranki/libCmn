// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ObjArray_internal.h
 *	Generated 12/29/2019 20:07:08
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




#include        <ObjArray.h>
#include        <array_internal.h>
#include        <JsonIn.h>


#ifndef OBJARRAY_INTERNAL_H
#define	OBJARRAY_INTERNAL_H



#define     PROPERTY_OTHER_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



    typedef struct ArrayEntry_s {
        OBJ_ID          pObj;
    } ARRAY_ENTRY;




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct ObjArray_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    ARRAY_DATA      super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    OBJ_ID          pOther;

};
#pragma pack(pop)

    extern
    struct ObjArray_class_data_s  ObjArray_ClassObj;

    extern
    const
    OBJARRAY_VTBL         ObjArray_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OBJARRAY_SINGLETON
    OBJARRAY_DATA *     ObjArray_getSingleton (
        void
    );

    bool            ObjArray_setSingleton (
     OBJARRAY_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  ObjArray_getSuperVtbl (
        OBJARRAY_DATA     *this
    );


    void            ObjArray_Dealloc (
        OBJ_ID          objId
    );


#ifdef  OBJARRAY_JSON_SUPPORT
    OBJARRAY_DATA *       ObjArray_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          ObjArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     ObjArray_ToJson (
        OBJARRAY_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			ObjArray_Validate (
        OBJARRAY_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJARRAY_INTERNAL_H */

