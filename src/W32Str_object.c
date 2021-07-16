// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'W32Str'
//  Generated 07/15/2021 16:05:13


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




#define         W32STR_OBJECT_C       1
#include        <W32Str_internal.h>
#ifdef  W32STR_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct W32Str_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  W32STR_SINGLETON
    volatile
    W32STR_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          W32StrClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        W32Str_Info;            // Forward Reference




static
bool            W32StrClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_W32STR_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(W32Str_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        W32StrClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_W32STR_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
W32STR_CLASS_VTBL    class_Vtbl = {
    {
        &W32Str_Info,
        W32StrClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        W32Str_Class,
        W32StrClass_WhoAmI,
        (P_OBJ_QUERYINFO)W32StrClass_QueryInfo,
        NULL                        // W32StrClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

W32STR_CLASS_DATA  W32Str_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(W32STR_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  W32STR_SINGLETON
extern
const
W32STR_VTBL       W32Str_VtblShared;


W32STR_DATA *     W32Str_getSingleton (
    void
)
{
    return (OBJ_ID)(W32Str_ClassObj.pSingleton);
}


bool            W32Str_setSingleton (
    W32STR_DATA       *pValue
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
    if (W32Str_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(W32Str_ClassObj.pSingleton));
    }
    W32Str_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



W32STR_DATA *     W32Str_Shared (
    void
)
{
    W32STR_DATA       *this = (OBJ_ID)(W32Str_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = W32Str_New( );
        obj_setVtbl(this, (void *)&W32Str_VtblShared);
        W32Str_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // W32Str_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            W32Str_SharedReset (
    void
)
{
    W32STR_DATA       *this = (OBJ_ID)(W32Str_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&W32Str_Vtbl);
        obj_Release(this);
        W32Str_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          W32StrClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    W32STR_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(W32STR_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&W32Str_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&W32Str_Info.pClassSuperObject;
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
                        return W32Str_New;
                    }
                    break;
                    
                case 'P':
#ifdef  W32STR_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return W32Str_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return W32Str_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  W32STR_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return W32Str_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return W32Str_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return W32StrClass_WhoAmI;
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
bool            W32Str_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_W32STR == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(W32Str_Class())->pClassSuperObject;
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
void            W32Str_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          W32Str_Class (
    void
)
{
    return (OBJ_ID)&W32Str_ClassObj;
}


static
uint16_t        W32Str_WhoAmI (
    void
)
{
    return OBJ_IDENT_W32STR;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  W32STR_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
W32STR_VTBL     W32Str_VtblShared = {
    {
        &W32Str_Info,
        W32Str_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        W32Str_Dealloc,
        W32Str_Class,
        W32Str_WhoAmI,
        (P_OBJ_QUERYINFO)W32Str_QueryInfo,
        (P_OBJ_TOSTRING)W32Str_ToDebugString,
        NULL,           // W32Str_Enable,
        NULL,           // W32Str_Disable,
        NULL,           // (P_OBJ_ASSIGN)W32Str_Assign,
        NULL,           // (P_OBJ_COMPARE)W32Str_Compare,
        NULL,           // (P_OBJ_PTR)W32Str_Copy,
        NULL,           // (P_OBJ_PTR)W32Str_DeepCopy,
        NULL            // (P_OBJ_HASH)W32Str_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //W32Str_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
W32STR_VTBL     W32Str_Vtbl = {
    {
        &W32Str_Info,
        W32Str_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        W32Str_Dealloc,
        W32Str_Class,
        W32Str_WhoAmI,
        (P_OBJ_QUERYINFO)W32Str_QueryInfo,
        (P_OBJ_TOSTRING)W32Str_ToDebugString,
        NULL,           // W32Str_Enable,
        NULL,           // W32Str_Disable,
        (P_OBJ_ASSIGN)W32Str_Assign,
        (P_OBJ_COMPARE)W32Str_Compare,
        (P_OBJ_PTR)W32Str_Copy,
        NULL,           // (P_OBJ_PTR)W32Str_DeepCopy,
        (P_OBJ_HASH)W32Str_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //W32Str_IsEnabled,
 
};



static
const
OBJ_INFO        W32Str_Info = {
    "W32Str",
    "Mutable Wide (W32CHR_T) NUL-terminated String",
    (OBJ_DATA *)&W32Str_ClassObj,
    (OBJ_DATA *)&array_ClassObj,
    (OBJ_IUNKNOWN *)&W32Str_Vtbl,
    sizeof(W32STR_DATA)
};





