// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Sects'
//  Generated 12/27/2020 14:57:52


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




#define         SECTS_OBJECT_C       1
#include        <Sects_internal.h>
#ifdef  SECTS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Sects_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SECTS_SINGLETON
    volatile
    SECTS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SectsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Sects_Info;            // Forward Reference




static
bool            SectsClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SECTS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Sects_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        SectsClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SECTS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SECTS_CLASS_VTBL    class_Vtbl = {
    {
        &Sects_Info,
        SectsClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Sects_Class,
        SectsClass_WhoAmI,
        (P_OBJ_QUERYINFO)SectsClass_QueryInfo,
        NULL                        // SectsClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

SECTS_CLASS_DATA  Sects_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SECTS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SECTS_SINGLETON
extern
const
SECTS_VTBL       Sects_VtblShared;


SECTS_DATA *     Sects_getSingleton (
    void
)
{
    return (OBJ_ID)(Sects_ClassObj.pSingleton);
}


bool            Sects_setSingleton (
    SECTS_DATA       *pValue
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
    if (Sects_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Sects_ClassObj.pSingleton));
    }
    Sects_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SECTS_DATA *     Sects_Shared (
    void
)
{
    SECTS_DATA       *this = (OBJ_ID)(Sects_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Sects_New( );
        obj_setVtbl(this, (void *)&Sects_VtblShared);
        Sects_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Sects_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Sects_SharedReset (
    void
)
{
    SECTS_DATA       *this = (OBJ_ID)(Sects_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Sects_Vtbl);
        obj_Release(this);
        Sects_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SectsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SECTS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SECTS_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Sects_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Sects_Info.pClassSuperObject;
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
                        return Sects_New;
                    }
                    break;
                    
                case 'P':
#ifdef  SECTS_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Sects_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Sects_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  SECTS_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Sects_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Sects_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SectsClass_WhoAmI;
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
bool            Sects_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SECTS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Sects_Class())->pClassSuperObject;
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
void            Sects_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Sects_Class (
    void
)
{
    return (OBJ_ID)&Sects_ClassObj;
}


static
uint16_t        Sects_WhoAmI (
    void
)
{
    return OBJ_IDENT_SECTS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SECTS_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SECTS_VTBL     Sects_VtblShared = {
    {
        &Sects_Info,
        Sects_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Sects_Dealloc,
        Sects_Class,
        Sects_WhoAmI,
        (P_OBJ_QUERYINFO)Sects_QueryInfo,
        (P_OBJ_TOSTRING)Sects_ToDebugString,
        NULL,           // Sects_Enable,
        NULL,           // Sects_Disable,
        NULL,           // (P_OBJ_ASSIGN)Sects_Assign,
        NULL,           // (P_OBJ_COMPARE)Sects_Compare,
        NULL,           // (P_OBJ_PTR)Sects_Copy,
        NULL,           // (P_OBJ_PTR)Sects_DeepCopy,
        NULL            // (P_OBJ_HASH)Sects_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Sects_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SECTS_VTBL     Sects_Vtbl = {
    {
        &Sects_Info,
        Sects_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Sects_Dealloc,
        Sects_Class,
        Sects_WhoAmI,
        (P_OBJ_QUERYINFO)Sects_QueryInfo,
        (P_OBJ_TOSTRING)Sects_ToDebugString,
        NULL,           // Sects_Enable,
        NULL,           // Sects_Disable,
        NULL,           // (P_OBJ_ASSIGN)Sects_Assign,
        NULL,           // (P_OBJ_COMPARE)Sects_Compare,
        NULL,           // (P_OBJ_PTR)Sects_Copy,
        NULL,           // (P_OBJ_PTR)Sects_DeepCopy,
        NULL            // (P_OBJ_HASH)Sects_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Sects_IsEnabled,
 
};



static
const
OBJ_INFO        Sects_Info = {
    "Sects",
    "Section Table",
    (OBJ_DATA *)&Sects_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Sects_Vtbl,
    sizeof(SECTS_DATA)
};





