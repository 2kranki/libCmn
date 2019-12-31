// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ObjMethod_internal.h
 *	Generated 12/15/2019 14:20:32
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




#include        <ObjMethod.h>
#include        <JsonIn.h>


#ifndef OBJMETHOD_INTERNAL_H
#define	OBJMETHOD_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct ObjMethod_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    OBJ_ID          *pObject;       // Object Pointer
    void            *pMethod;       // Method Pointer
    ASTR_DATA       *pObjectName;   // Object Name as provided in objInfo
    ASTR_DATA       *pMethodName;   // Method Name which must be available
    //                              // the object's QueryInfo method
    ASTR_DATA       *pDesc;         // Optional Description
    OBJ_ID          *pOther;        // Optional User Object Pointer

};
#pragma pack(pop)

    extern
    struct ObjMethod_class_data_s  ObjMethod_ClassObj;

    extern
    const
    OBJMETHOD_VTBL         ObjMethod_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OBJMETHOD_SINGLETON
    OBJMETHOD_DATA * ObjMethod_getSingleton (
        void
    );

    bool            ObjMethod_setSingleton (
     OBJMETHOD_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            ObjMethod_setDesc(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    );
    
    
    bool            ObjMethod_setMethodName(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    );
    
    
    bool            ObjMethod_setObject(
        OBJMETHOD_DATA  *this,
        OBJ_ID          pValue
    );
    
    
    bool            ObjMethod_setObjectName(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    );
    
    
    OBJ_IUNKNOWN *  ObjMethod_getSuperVtbl (
        OBJMETHOD_DATA     *this
    );


    void            ObjMethod_Dealloc (
        OBJ_ID          objId
    );


#ifdef  OBJMETHOD_JSON_SUPPORT
    OBJMETHOD_DATA * ObjMethod_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          ObjMethod_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     ObjMethod_ToJson (
        OBJMETHOD_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			ObjMethod_Validate (
        OBJMETHOD_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJMETHOD_INTERNAL_H */

