// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   symTable_internal.h
 *	Generated 11/04/2018 21:13:12
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




#include        <symTable.h>
#include        <jsonIn.h>
#include        <nodeHash_internal.h>
#include        <objArray.h>


#ifndef SYMTABLE_INTERNAL_H
#define	SYMTABLE_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct symTable_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        cHashes;    // number of nodeHashes in pStack
    uint16_t        reserved;
    ASTR_DATA       *pStr;
    OBJARRAY_DATA   *pStack;

};
#pragma pack(pop)

    extern
    struct symTable_class_data_s  symTable_ClassObj;

    extern
    const
    SYMTABLE_VTBL         symTable_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SYMTABLE_SINGLETON
    SYMTABLE_DATA *     symTable_getSingleton(
        void
    );

    bool            symTable_setSingleton(
     SYMTABLE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  symTable_getSuperVtbl(
        SYMTABLE_DATA     *this
    );


    void            symTable_Dealloc(
        OBJ_ID          objId
    );


    SYMTABLE_DATA *       symTable_ParseObject(
        JSONIN_DATA     *pParser
    );


    void *          symTable_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     symTable_ToJSON(
        SYMTABLE_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			symTable_Validate(
        SYMTABLE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SYMTABLE_INTERNAL_H */

