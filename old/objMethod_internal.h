// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   objMethod_internal.h
 *	Generated 10/28/2017 08:51:04
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




#include    <objMethod.h>


#ifndef OBJMETHOD_INTERNAL_H
#define	OBJMETHOD_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct objMethod_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    OBJ_ID          *pObject;       // Object Pointer
    void            *pMethod;       // Method Pointer
    ASTR_DATA       *pObjectName;   // Object Name as provided in objInfo
    ASTR_DATA       *pMethodName;   // Method Name which must be available
    //                              // the object's QueryInfo method
    ASTR_DATA       *pDesc;         // Optional Description
    uint32_t        user32;         // Optional 32-bit User Data

};
#pragma pack(pop)

    extern
    const
    struct objMethod_class_data_s  objMethod_ClassObj;

    extern
    const
    OBJMETHOD_VTBL         objMethod_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool        objMethod_setDesc(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    );
    
    
   bool            objMethod_setLastError(
        OBJMETHOD_DATA     *this,
        ERESULT         value
    );


    bool        objMethod_setMethodName(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    );
    
    
    bool            objMethod_setObject(
        OBJMETHOD_DATA  *this,
        OBJ_ID          pValue
    );
    
    
    bool        objMethod_setObjectName(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    );
    
    
    void            objMethod_Dealloc(
        OBJ_ID          objId
    );


    void *          objMethod_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     objMethod_ToJSON(
        OBJMETHOD_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			objMethod_Validate(
        OBJMETHOD_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJMETHOD_INTERNAL_H */

