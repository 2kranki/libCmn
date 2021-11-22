// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Enums'
//  Generated 11/21/2021 13:39:34


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




#define         ENUMS_OBJECT_C       1
#include        <Enums_internal.h>
#ifdef  ENUMS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Enums_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  ENUMS_SINGLETON
    volatile
    ENUMS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          EnumsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Enums_Info;            // Forward Reference




static
bool            EnumsClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_ENUMS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Enums_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        EnumsClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_ENUMS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
ENUMS_CLASS_VTBL    class_Vtbl = {
    {
        &Enums_Info,
        EnumsClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Enums_Class,
        EnumsClass_WhoAmI,
        (P_OBJ_QUERYINFO)EnumsClass_QueryInfo,
        NULL                        // EnumsClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

ENUMS_CLASS_DATA  Enums_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(ENUMS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  ENUMS_SINGLETON
extern
const
ENUMS_VTBL       Enums_VtblShared;


ENUMS_DATA *     Enums_getSingleton (
    void
)
{
    return (OBJ_ID)(Enums_ClassObj.pSingleton);
}


bool            Enums_setSingleton (
    ENUMS_DATA       *pValue
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
    if (Enums_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Enums_ClassObj.pSingleton));
    }
    Enums_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



ENUMS_DATA *     Enums_Shared (
    void
)
{
    ENUMS_DATA       *this = (OBJ_ID)(Enums_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Enums_New( );
        obj_setVtbl(this, (void *)&Enums_VtblShared);
        Enums_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Enums_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Enums_SharedReset (
    void
)
{
    ENUMS_DATA       *this = (OBJ_ID)(Enums_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Enums_Vtbl);
        obj_Release(this);
        Enums_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          EnumsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    ENUMS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(ENUMS_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Enums_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Enums_Info.pClassSuperObject;
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
                        return Enums_New;
                    }
                    break;
                    
                case 'P':
#ifdef  ENUMS_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Enums_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Enums_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  ENUMS_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Enums_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Enums_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return EnumsClass_WhoAmI;
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
bool            Enums_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_ENUMS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Enums_Class())->pClassSuperObject;
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
void            Enums_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Enums_Class (
    void
)
{
    return (OBJ_ID)&Enums_ClassObj;
}


static
uint16_t        Enums_WhoAmI (
    void
)
{
    return OBJ_IDENT_ENUMS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  ENUMS_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
ENUMS_VTBL     Enums_VtblShared = {
    {
        &Enums_Info,
        Enums_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Enums_Dealloc,
        Enums_Class,
        Enums_WhoAmI,
        (P_OBJ_QUERYINFO)Enums_QueryInfo,
        (P_OBJ_TOSTRING)Enums_ToDebugString,
        NULL,           // Enums_Enable,
        NULL,           // Enums_Disable,
        NULL,           // (P_OBJ_ASSIGN)Enums_Assign,
        NULL,           // (P_OBJ_COMPARE)Enums_Compare,
        NULL,           // (P_OBJ_PTR)Enums_Copy,
        NULL,           // (P_OBJ_PTR)Enums_DeepCopy,
        NULL            // (P_OBJ_HASH)Enums_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Enums_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
ENUMS_VTBL     Enums_Vtbl = {
    {
        &Enums_Info,
        Enums_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Enums_Dealloc,
        Enums_Class,
        Enums_WhoAmI,
        (P_OBJ_QUERYINFO)Enums_QueryInfo,
        (P_OBJ_TOSTRING)Enums_ToDebugString,
        NULL,           // Enums_Enable,
        NULL,           // Enums_Disable,
        NULL,           // (P_OBJ_ASSIGN)Enums_Assign,
        NULL,           // (P_OBJ_COMPARE)Enums_Compare,
        NULL,           // (P_OBJ_PTR)Enums_Copy,
        NULL,           // (P_OBJ_PTR)Enums_DeepCopy,
        NULL            // (P_OBJ_HASH)Enums_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Enums_IsEnabled,
 
};



static
const
OBJ_INFO        Enums_Info = {
    "Enums",
    "Enum File Generation",
    (OBJ_DATA *)&Enums_ClassObj,
    (OBJ_DATA *)&Enums_ClassObj,
    (OBJ_IUNKNOWN *)&Enums_Vtbl,
    sizeof(ENUMS_DATA)
};





