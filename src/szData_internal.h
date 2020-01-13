// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   szData_internal.h
 *	Generated 02/07/2018 09:15:58
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




#include    <szData.h>
#include    <JsonIn.h>


#ifndef SZDATA_INTERNAL_H
#define	SZDATA_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct szData_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        token;          // szTbl token

    int32_t         cls;
    OBJ_ID          pData;

};
#pragma pack(pop)

    extern
    const
    struct szData_class_data_s  szData_ClassObj;

    extern
    const
    SZDATA_VTBL         szData_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            szData_setLastError(
        SZDATA_DATA     *this,
        ERESULT         value
    );


    OBJ_IUNKNOWN *  szData_getSuperVtbl(
        SZDATA_DATA     *this
    );


    void            szData_Dealloc(
        OBJ_ID          objId
    );


    SZDATA_DATA *   szData_New(
        void
    );
    
    
    SZDATA_DATA *   szData_ParseObject(
        JSONIN_DATA     *pParser
    );
    
    
    void *          szData_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     szData_ToJSON(
        SZDATA_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			szData_Validate(
        SZDATA_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SZDATA_INTERNAL_H */

