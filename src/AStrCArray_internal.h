// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   AStrCArray_internal.h
 *	Generated 11/07/2019 08:58:19
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




#include        <AStrCArray.h>
#include        <JsonIn.h>
#include        <ObjArray.h>


#ifndef ASTRCARRAY_INTERNAL_H
#define	ASTRCARRAY_INTERNAL_H



#define     PROPERTY_ARRAY_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct AStrCArray_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    OBJARRAY_DATA   *pArray;

};
#pragma pack(pop)

    extern
    struct AStrCArray_class_data_s  AStrCArray_ClassObj;

    extern
    const
    ASTRCARRAY_VTBL         AStrCArray_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  ASTRCARRAY_SINGLETON
    ASTRCARRAY_DATA * AStrCArray_getSingleton (
        void
    );

    bool            AStrCArray_setSingleton (
     ASTRCARRAY_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  AStrCArray_getSuperVtbl (
        ASTRCARRAY_DATA     *this
    );


    void            AStrCArray_Dealloc (
        OBJ_ID          objId
    );


    ASTRCARRAY_DATA * AStrCArray_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    void *          AStrCArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     AStrCArray_ToJson (
        ASTRCARRAY_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			AStrCArray_Validate (
        ASTRCARRAY_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* ASTRCARRAY_INTERNAL_H */

