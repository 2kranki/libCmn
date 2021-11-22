// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Enum'
//  Generated 11/21/2021 11:59:11


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




#define         ENUM_OBJECT_C       1
#include        <Enum_internal.h>
#ifdef  ENUM_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Enum_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  ENUM_SINGLETON
    volatile
    ENUM_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          EnumClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Enum_Info;            // Forward Reference




static
bool            EnumClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_ENUM_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Enum_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        EnumClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_ENUM_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
ENUM_CLASS_VTBL    class_Vtbl = {
    {
        &Enum_Info,
        EnumClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Enum_Class,
        EnumClass_WhoAmI,
        (P_OBJ_QUERYINFO)EnumClass_QueryInfo,
        NULL                        // EnumClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

ENUM_CLASS_DATA  Enum_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(ENUM_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  ENUM_SINGLETON
extern
const
ENUM_VTBL       Enum_VtblShared;


ENUM_DATA *     Enum_getSingleton (
    void
)
{
    return (OBJ_ID)(Enum_ClassObj.pSingleton);
}


bool            Enum_setSingleton (
    ENUM_DATA       *pValue
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
    if (Enum_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Enum_ClassObj.pSingleton));
    }
    Enum_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



ENUM_DATA *     Enum_Shared (
    void
)
{
    ENUM_DATA       *this = (OBJ_ID)(Enum_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Enum_New( );
        obj_setVtbl(this, (void *)&Enum_VtblShared);
        Enum_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Enum_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Enum_SharedReset (
    void
)
{
    ENUM_DATA       *this = (OBJ_ID)(Enum_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Enum_Vtbl);
        obj_Release(this);
        Enum_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          EnumClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    ENUM_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(ENUM_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Enum_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Enum_Info.pClassSuperObject;
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
                        return Enum_New;
                    }
                    break;
                    
                case 'P':
#ifdef  ENUM_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Enum_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Enum_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  ENUM_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Enum_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Enum_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return EnumClass_WhoAmI;
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
bool            Enum_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_ENUM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Enum_Class())->pClassSuperObject;
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
void            Enum_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Enum_Class (
    void
)
{
    return (OBJ_ID)&Enum_ClassObj;
}


static
uint16_t        Enum_WhoAmI (
    void
)
{
    return OBJ_IDENT_ENUM;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  ENUM_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
ENUM_VTBL     Enum_VtblShared = {
    {
        &Enum_Info,
        Enum_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Enum_Dealloc,
        Enum_Class,
        Enum_WhoAmI,
        (P_OBJ_QUERYINFO)Enum_QueryInfo,
        (P_OBJ_TOSTRING)Enum_ToDebugString,
        NULL,           // Enum_Enable,
        NULL,           // Enum_Disable,
        NULL,           // (P_OBJ_ASSIGN)Enum_Assign,
        NULL,           // (P_OBJ_COMPARE)Enum_Compare,
        NULL,           // (P_OBJ_PTR)Enum_Copy,
        NULL,           // (P_OBJ_PTR)Enum_DeepCopy,
        NULL            // (P_OBJ_HASH)Enum_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Enum_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
ENUM_VTBL     Enum_Vtbl = {
    {
        &Enum_Info,
        Enum_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Enum_Dealloc,
        Enum_Class,
        Enum_WhoAmI,
        (P_OBJ_QUERYINFO)Enum_QueryInfo,
        (P_OBJ_TOSTRING)Enum_ToDebugString,
        NULL,           // Enum_Enable,
        NULL,           // Enum_Disable,
        (P_OBJ_ASSIGN)Enum_Assign,
        NULL,           // (P_OBJ_COMPARE)Enum_Compare,
        (P_OBJ_PTR)Enum_Copy,
        NULL,           // (P_OBJ_PTR)Enum_DeepCopy,
        NULL            // (P_OBJ_HASH)Enum_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    Enum_Next,
    Enum_Skip,
    Enum_Reset,
    Enum_LookAhead,
    Enum_Remaining

};



static
const
OBJ_INFO        Enum_Info = {
    "Enum",
    "Enumerator Base Class",
    (OBJ_DATA *)&Enum_ClassObj,
    (OBJ_DATA *)&Enum_ClassObj,
    (OBJ_IUNKNOWN *)&Enum_Vtbl,
    sizeof(ENUM_DATA)
};





