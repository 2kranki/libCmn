// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   i32Array_internal.h
 *	Generated 01/20/2018 22:51:51
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




#include    <i32Array.h>
#include    <array_internal.h>


#ifndef I32ARRAY_INTERNAL_H
#define	I32ARRAY_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct i32Array_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    ARRAY_DATA      super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define I32ARRAY_FLAG_BIGENDIAN OBJ_FLAG_USER1

    // Common Data

};
#pragma pack(pop)

    extern
    const
    struct i32Array_class_data_s  i32Array_ClassObj;

    extern
    const
    I32ARRAY_VTBL         i32Array_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            i32Array_setLastError(
        I32ARRAY_DATA     *this,
        ERESULT         value
    );


    OBJ_IUNKNOWN *  i32Array_getSuperVtbl(
        I32ARRAY_DATA     *this
    );


    void            i32Array_Dealloc(
        OBJ_ID          objId
    );


    void *          i32Array_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     i32Array_ToJSON(
        I32ARRAY_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			i32Array_Validate(
        I32ARRAY_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* I32ARRAY_INTERNAL_H */

