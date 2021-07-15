// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'W32Array'
//  Generated 07/15/2021 10:35:28


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




#define         W32ARRAY_OBJECT_C       1
#include        <W32Array_internal.h>
#ifdef  W32ARRAY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct W32Array_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  W32ARRAY_SINGLETON
    volatile
    W32ARRAY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          W32ArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        W32Array_Info;            // Forward Reference




static
bool            W32ArrayClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_W32ARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(W32Array_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        W32ArrayClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_W32ARRAY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
W32ARRAY_CLASS_VTBL    class_Vtbl = {
    {
        &W32Array_Info,
        W32ArrayClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        W32Array_Class,
        W32ArrayClass_WhoAmI,
        (P_OBJ_QUERYINFO)W32ArrayClass_QueryInfo,
        NULL                        // W32ArrayClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

W32ARRAY_CLASS_DATA  W32Array_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(W32ARRAY_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  W32ARRAY_SINGLETON
extern
const
W32ARRAY_VTBL       W32Array_VtblShared;


W32ARRAY_DATA *     W32Array_getSingleton (
    void
)
{
    return (OBJ_ID)(W32Array_ClassObj.pSingleton);
}


bool            W32Array_setSingleton (
    W32ARRAY_DATA       *pValue
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
    if (W32Array_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(W32Array_ClassObj.pSingleton));
    }
    W32Array_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



W32ARRAY_DATA *     W32Array_Shared (
    void
)
{
    W32ARRAY_DATA       *this = (OBJ_ID)(W32Array_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = W32Array_New( );
        obj_setVtbl(this, (void *)&W32Array_VtblShared);
        W32Array_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // W32Array_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            W32Array_SharedReset (
    void
)
{
    W32ARRAY_DATA       *this = (OBJ_ID)(W32Array_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&W32Array_Vtbl);
        obj_Release(this);
        W32Array_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          W32ArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    W32ARRAY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(W32ARRAY_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&W32Array_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&W32Array_Info.pClassSuperObject;
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
                        return W32Array_New;
                    }
                    break;
                    
                case 'P':
#ifdef  W32ARRAY_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return W32Array_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return W32Array_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  W32ARRAY_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return W32Array_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return W32Array_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return W32ArrayClass_WhoAmI;
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
bool            W32Array_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_W32ARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(W32Array_Class())->pClassSuperObject;
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
void            W32Array_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          W32Array_Class (
    void
)
{
    return (OBJ_ID)&W32Array_ClassObj;
}


static
uint16_t        W32Array_WhoAmI (
    void
)
{
    return OBJ_IDENT_W32ARRAY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  W32ARRAY_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
W32ARRAY_VTBL     W32Array_VtblShared = {
    {
        &W32Array_Info,
        W32Array_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        W32Array_Dealloc,
        W32Array_Class,
        W32Array_WhoAmI,
        (P_OBJ_QUERYINFO)W32Array_QueryInfo,
        (P_OBJ_TOSTRING)W32Array_ToDebugString,
        NULL,           // W32Array_Enable,
        NULL,           // W32Array_Disable,
        NULL,           // (P_OBJ_ASSIGN)W32Array_Assign,
        NULL,           // (P_OBJ_COMPARE)W32Array_Compare,
        NULL,           // (P_OBJ_PTR)W32Array_Copy,
        NULL,           // (P_OBJ_PTR)W32Array_DeepCopy,
        NULL            // (P_OBJ_HASH)W32Array_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //W32Array_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
W32ARRAY_VTBL     W32Array_Vtbl = {
    {
        &W32Array_Info,
        W32Array_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        W32Array_Dealloc,
        W32Array_Class,
        W32Array_WhoAmI,
        (P_OBJ_QUERYINFO)W32Array_QueryInfo,
        (P_OBJ_TOSTRING)W32Array_ToDebugString,
        NULL,           // W32Array_Enable,
        NULL,           // W32Array_Disable,
        (P_OBJ_ASSIGN)W32Array_Assign,
        NULL,           // (P_OBJ_COMPARE)W32Array_Compare,
        (P_OBJ_PTR)W32Array_Copy,
        NULL,           // (P_OBJ_PTR)W32Array_DeepCopy,
        NULL            // (P_OBJ_HASH)W32Array_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //W32Array_IsEnabled,
 
};



static
const
OBJ_INFO        W32Array_Info = {
    "W32Array",
    "An Array of W32Str(s)",
    (OBJ_DATA *)&W32Array_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&W32Array_Vtbl,
    sizeof(W32ARRAY_DATA)
};





