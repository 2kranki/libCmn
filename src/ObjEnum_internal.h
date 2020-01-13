// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ObjEnum_internal.h
 *	Generated 12/16/2019 11:38:07
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




#include        <ObjEnum.h>
#include        <ObjArray.h>
#include        <JsonIn.h>


#ifndef OBJENUM_INTERNAL_H
#define	OBJENUM_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct ObjEnum_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define OBJENUM_SORTED  OBJ_FLAG_USER1  // File Path is open

    // Common Data
    OBJARRAY_DATA   *pArray;
    uint32_t        current;
    uint32_t        rsvd32;         // (sizeof(OBJENUM) % 8) == 0

};
#pragma pack(pop)

    extern
    struct ObjEnum_class_data_s  ObjEnum_ClassObj;

    extern
    const
    OBJENUM_VTBL         ObjEnum_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OBJENUM_SINGLETON
    OBJENUM_DATA *  ObjEnum_getSingleton (
        void
    );

    bool            ObjEnum_setSingleton (
     OBJENUM_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJARRAY_DATA * ObjEnum_getArray(
        OBJENUM_DATA    *this
    );
    
    bool            ObjEnum_setArray(
        OBJENUM_DATA    *this,
        OBJARRAY_DATA   *pValue
    );
    

    OBJ_IUNKNOWN *  ObjEnum_getSuperVtbl (
        OBJENUM_DATA     *this
    );


    ERESULT         ObjEnum_AppendObj(
        OBJENUM_DATA    *this,
        OBJ_ID          pObject
    );


    void            ObjEnum_Dealloc (
        OBJ_ID          objId
    );


#ifdef  OBJENUM_JSON_SUPPORT
    OBJENUM_DATA *       ObjEnum_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          ObjEnum_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


   ERESULT         ObjEnum_SortAscending(
       OBJENUM_DATA    *this
   );
   
#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     ObjEnum_ToJson (
        OBJENUM_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			ObjEnum_Validate (
        OBJENUM_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJENUM_INTERNAL_H */

