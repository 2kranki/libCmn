// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'AStrArray'
//  Generated 04/11/2021 10:41:38


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




#define         ASTRARRAY_OBJECT_C       1
#include        <AStrArray_internal.h>
#ifdef  ASTRARRAY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct AStrArray_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  ASTRARRAY_SINGLETON
    volatile
    ASTRARRAY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          AStrArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        AStrArray_Info;            // Forward Reference




static
bool            AStrArrayClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_ASTRARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(AStrArray_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        AStrArrayClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_ASTRARRAY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
ASTRARRAY_CLASS_VTBL    class_Vtbl = {
    {
        &AStrArray_Info,
        AStrArrayClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        AStrArray_Class,
        AStrArrayClass_WhoAmI,
        (P_OBJ_QUERYINFO)AStrArrayClass_QueryInfo,
        NULL                        // AStrArrayClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

ASTRARRAY_CLASS_DATA  AStrArray_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(ASTRARRAY_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  ASTRARRAY_SINGLETON
extern
const
ASTRARRAY_VTBL       AStrArray_VtblShared;


ASTRARRAY_DATA *     AStrArray_getSingleton (
    void
)
{
    return (OBJ_ID)(AStrArray_ClassObj.pSingleton);
}


bool            AStrArray_setSingleton (
    ASTRARRAY_DATA       *pValue
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
    if (AStrArray_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(AStrArray_ClassObj.pSingleton));
    }
    AStrArray_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



ASTRARRAY_DATA *     AStrArray_Shared (
    void
)
{
    ASTRARRAY_DATA       *this = (OBJ_ID)(AStrArray_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = AStrArray_New( );
        obj_setVtbl(this, (void *)&AStrArray_VtblShared);
        AStrArray_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // AStrArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            AStrArray_SharedReset (
    void
)
{
    ASTRARRAY_DATA       *this = (OBJ_ID)(AStrArray_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&AStrArray_Vtbl);
        obj_Release(this);
        AStrArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          AStrArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    ASTRARRAY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(ASTRARRAY_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&AStrArray_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&AStrArray_Info.pClassSuperObject;
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
                        return AStrArray_New;
                    }
                    break;
                    
                case 'P':
#ifdef  ASTRARRAY_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return AStrArray_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return AStrArray_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  ASTRARRAY_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return AStrArray_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return AStrArray_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return AStrArrayClass_WhoAmI;
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
bool            AStrArray_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_ASTRARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(AStrArray_Class())->pClassSuperObject;
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
void            AStrArray_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          AStrArray_Class (
    void
)
{
    return (OBJ_ID)&AStrArray_ClassObj;
}


static
uint16_t        AStrArray_WhoAmI (
    void
)
{
    return OBJ_IDENT_ASTRARRAY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  ASTRARRAY_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
ASTRARRAY_VTBL     AStrArray_VtblShared = {
    {
        &AStrArray_Info,
        AStrArray_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        AStrArray_Dealloc,
        AStrArray_Class,
        AStrArray_WhoAmI,
        (P_OBJ_QUERYINFO)AStrArray_QueryInfo,
        (P_OBJ_TOSTRING)AStrArray_ToDebugString,
        NULL,           // AStrArray_Enable,
        NULL,           // AStrArray_Disable,
        NULL,           // (P_OBJ_ASSIGN)AStrArray_Assign,
        NULL,           // (P_OBJ_COMPARE)AStrArray_Compare,
        NULL,           // (P_OBJ_PTR)AStrArray_Copy,
        NULL,           // (P_OBJ_PTR)AStrArray_DeepCopy,
        NULL            // (P_OBJ_HASH)AStrArray_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //AStrArray_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
ASTRARRAY_VTBL     AStrArray_Vtbl = {
    {
        &AStrArray_Info,
        AStrArray_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        AStrArray_Dealloc,
        AStrArray_Class,
        AStrArray_WhoAmI,
        (P_OBJ_QUERYINFO)AStrArray_QueryInfo,
        (P_OBJ_TOSTRING)AStrArray_ToDebugString,
        NULL,           // AStrArray_Enable,
        NULL,           // AStrArray_Disable,
        NULL,           // (P_OBJ_ASSIGN)AStrArray_Assign,
        NULL,           // (P_OBJ_COMPARE)AStrArray_Compare,
        NULL,           // (P_OBJ_PTR)AStrArray_Copy,
        NULL,           // (P_OBJ_PTR)AStrArray_DeepCopy,
        NULL            // (P_OBJ_HASH)AStrArray_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //AStrArray_IsEnabled,
 
};



static
const
OBJ_INFO        AStrArray_Info = {
    "AStrArray",
    "An Array of AStr(ings)",
    (OBJ_DATA *)&AStrArray_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&AStrArray_Vtbl,
    sizeof(ASTRARRAY_DATA)
};





