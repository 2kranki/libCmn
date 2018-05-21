// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   genWIN64_internal.h
 *	Generated 04/18/2018 09:07:22
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




#include    <genWIN64.h>


#ifndef GENWIN64_INTERNAL_H
#define	GENWIN64_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct genWIN64_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint16_t        size;		    // maximum number of elements
    uint16_t        reserved;
    GENBASE_DATA    *pBase;
    SZHASH_DATA     *pDict;
    ASTR_DATA       *pStr;

    volatile
    int32_t         numRead;
    // WARNING - 'elems' must be last element of this structure!
    uint32_t        elems[0];

};
#pragma pack(pop)

    extern
    const
    struct genWIN64_class_data_s  genWIN64_ClassObj;

    extern
    const
    GENWIN64_VTBL         genWIN64_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            genWIN64_setLastError(
        GENWIN64_DATA     *this,
        ERESULT         value
    );


    OBJ_IUNKNOWN *  genWIN64_getSuperVtbl(
        GENWIN64_DATA     *this
    );


    void            genWIN64_Dealloc(
        OBJ_ID          objId
    );


    void *          genWIN64_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     genWIN64_ToJSON(
        GENWIN64_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			genWIN64_Validate(
        GENWIN64_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* GENWIN64_INTERNAL_H */

