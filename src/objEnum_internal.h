// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   objEnum_internal.h
 *	Generated 10/15/2017 09:38:35
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




#include    <objEnum.h>
#include    <objArray.h>


#ifndef OBJENUM_INTERNAL_H
#define	OBJENUM_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct objEnum_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;     // Needed for Inheritance
    #define OBJENUM_SORTED  8        // File Path is open

    // Common Data
    ERESULT         eRc;
    OBJARRAY_DATA   *pArray;
    uint32_t        current;
    uint32_t        rsvd32;         // (sizeof(OBJENUM) % 8) == 0

};
#pragma pack(pop)

    extern
    const
    struct objEnum_class_data_s  objEnum_ClassObj;

    extern
    const
    OBJENUM_VTBL         objEnum_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJARRAY_DATA * objEnum_getArray(
        OBJENUM_DATA    *this
    );
    
    bool            objEnum_setArray(
        OBJENUM_DATA    *this,
        OBJARRAY_DATA   *pValue
    );
    

   bool            objEnum_setLastError(
        OBJENUM_DATA     *this,
        ERESULT         value
    );


    ERESULT         objEnum_Append(
        OBJENUM_DATA    *this,
        OBJ_ID          pObject
    );
    
    
    void            objEnum_Dealloc(
        OBJ_ID          objId
    );


    void *          objEnum_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );


    ASTR_DATA *     objEnum_ToJSON(
        OBJENUM_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			objEnum_Validate(
        OBJENUM_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJENUM_INTERNAL_H */

