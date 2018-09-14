// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   jsonIn_internal.h
 *	Generated 12/21/2017 05:41:06
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




#include    <jsonIn.h>
#include    <hjson.h>
#include    <objList.h>


#ifndef JSONIN_INTERNAL_H
#define	JSONIN_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct jsonIn_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    NODEHASH_DATA   *pHash;
    OBJLIST_DATA    *pList;
    uint32_t        index;          // Current index into array.

};
#pragma pack(pop)

    extern
    const
    struct jsonIn_class_data_s  jsonIn_ClassObj;

    extern
    const
    JSONIN_VTBL         jsonIn_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  jsonIn_getSuperVtbl(
        JSONIN_DATA     *this
    );


    void            jsonIn_Dealloc(
        OBJ_ID          objId
    );


    void *          jsonIn_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     jsonIn_ToJSON(
        JSONIN_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			jsonIn_Validate(
        JSONIN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* JSONIN_INTERNAL_H */

