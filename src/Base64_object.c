// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Base64'
//  Generated 07/08/2021 09:13:40


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




#define         BASE64_OBJECT_C       1
#include        <Base64_internal.h>
#ifdef  BASE64_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Base64_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BASE64_SINGLETON
    volatile
    BASE64_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Base64Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Base64_Info;            // Forward Reference




static
bool            Base64Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BASE64_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Base64_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        Base64Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_BASE64_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BASE64_CLASS_VTBL    class_Vtbl = {
    {
        &Base64_Info,
        Base64Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Base64_Class,
        Base64Class_WhoAmI,
        (P_OBJ_QUERYINFO)Base64Class_QueryInfo,
        NULL                        // Base64Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

BASE64_CLASS_DATA  Base64_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BASE64_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BASE64_SINGLETON
extern
const
BASE64_VTBL       Base64_VtblShared;


BASE64_DATA *     Base64_getSingleton (
    void
)
{
    return (OBJ_ID)(Base64_ClassObj.pSingleton);
}


bool            Base64_setSingleton (
    BASE64_DATA       *pValue
)
{
    PSXLOCK_DATA    *pLock = OBJ_NIL;
    bool            fRc;
    
    pLock = psxLock_New( );
    if (OBJ_NIL == pLock) {
        DEBUG_BREAK();
        return false;
    }
    fRc = psxLock_Lock(pLock);
    if (!fRc) {
        DEBUG_BREAK();
        obj_Release(pLock);
        pLock = OBJ_NIL;
        return false;
    }
    
    obj_Retain(pValue);
    if (Base64_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Base64_ClassObj.pSingleton));
    }
    Base64_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BASE64_DATA *     Base64_Shared (
    void
)
{
    BASE64_DATA       *this = (OBJ_ID)(Base64_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Base64_New( );
        obj_setVtbl(this, (void *)&Base64_VtblShared);
        Base64_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Base64_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Base64_SharedReset (
    void
)
{
    BASE64_DATA       *this = (OBJ_ID)(Base64_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Base64_Vtbl);
        obj_Release(this);
        Base64_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Base64Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BASE64_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BASE64_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Base64_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Base64_Info.pClassSuperObject;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case OBJ_QUERYINFO_TYPE_INFO:
            return (void *)obj_getInfo(this);
            break;
            
        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {
                    
                case 'N':
                    if (str_Compare("New", (char *)pStr) == 0) {
                        return Base64_New;
                    }
                    break;
                    
                case 'P':
#ifdef  BASE64_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Base64_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Base64_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  BASE64_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Base64_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Base64_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return Base64Class_WhoAmI;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    return NULL;
}




static
bool            Base64_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BASE64 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Base64_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        pInfo = obj_getInfo(pObj);
        return pInfo->pDefaultVtbls->pIsKindOf(classID);
    }
    
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            Base64_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Base64_Class (
    void
)
{
    return (OBJ_ID)&Base64_ClassObj;
}


static
uint16_t        Base64_WhoAmI (
    void
)
{
    return OBJ_IDENT_BASE64;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  BASE64_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
BASE64_VTBL     Base64_VtblShared = {
    {
        &Base64_Info,
        Base64_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Base64_Dealloc,
        Base64_Class,
        Base64_WhoAmI,
        (P_OBJ_QUERYINFO)Base64_QueryInfo,
        (P_OBJ_TOSTRING)Base64_ToDebugString,
        NULL,           // Base64_Enable,
        NULL,           // Base64_Disable,
        NULL,           // (P_OBJ_ASSIGN)Base64_Assign,
        NULL,           // (P_OBJ_COMPARE)Base64_Compare,
        NULL,           // (P_OBJ_PTR)Base64_Copy,
        NULL,           // (P_OBJ_PTR)Base64_DeepCopy,
        NULL            // (P_OBJ_HASH)Base64_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Base64_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
BASE64_VTBL     Base64_Vtbl = {
    {
        &Base64_Info,
        Base64_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Base64_Dealloc,
        Base64_Class,
        Base64_WhoAmI,
        (P_OBJ_QUERYINFO)Base64_QueryInfo,
        (P_OBJ_TOSTRING)Base64_ToDebugString,
        NULL,           // Base64_Enable,
        NULL,           // Base64_Disable,
        NULL,           // (P_OBJ_ASSIGN)Base64_Assign,
        NULL,           // (P_OBJ_COMPARE)Base64_Compare,
        NULL,           // (P_OBJ_PTR)Base64_Copy,
        NULL,           // (P_OBJ_PTR)Base64_DeepCopy,
        NULL            // (P_OBJ_HASH)Base64_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Base64_IsEnabled,
 
};



static
const
OBJ_INFO        Base64_Info = {
    "Base64",
    "Base64 Encoding/Decoding",
    (OBJ_DATA *)&Base64_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Base64_Vtbl,
    sizeof(BASE64_DATA)
};





