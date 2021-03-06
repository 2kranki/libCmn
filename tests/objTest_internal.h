// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   objTest_internal.h
 *	Generated 11/01/2017 08:45:27
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




#include    <objTest.h>
#include    <Appl_internal.h>
#include    <Number.h>
#include    <ObjArray.h>
#include    <Path.h>
#include    <psxLock.h>


#ifndef OBJTEST_INTERNAL_H
#define	OBJTEST_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct objTest_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    APPL_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint32_t        unique;
    PSXLOCK_DATA    *pLock;
    OBJARRAY_DATA   *pArray;

    // Options and Arguments
    uint16_t        fArchive;
    uint16_t        rsvd16;
    NUMBER_DATA     *pArgLen;
    PATH_DATA       *pInFilePath;      // ("-f" | "--file=")<string> or ("-f" | "--file") <string>
    PATH_DATA       *pOutFilePath;     // ("-o" | "--out=")<string> or ("-o" | "--out") <string>

};
#pragma pack(pop)

    extern
    struct objTest_class_data_s  objTest_ClassObj;

    extern
    const
    OBJTEST_VTBL         objTest_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            objTest_setLastError(
        OBJTEST_DATA     *this,
        ERESULT         value
    );


    void            objTest_Dealloc(
        OBJ_ID          objId
    );


    void *          objTest_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     objTest_ToJSON(
        OBJTEST_DATA      *this
    );


    uint32_t		objTest_Unique(
        void
    );


#ifdef NDEBUG
#else
    bool			objTest_Validate(
        OBJTEST_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJTEST_INTERNAL_H */

