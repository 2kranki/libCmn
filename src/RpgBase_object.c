// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'RpgBase'
//  Generated 03/22/2021 07:15:24


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




#define         RPGBASE_OBJECT_C       1
#include        <RpgBase_internal.h>
#ifdef  RPGBASE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct RpgBase_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  RPGBASE_SINGLETON
    volatile
    RPGBASE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          RpgBaseClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        RpgBase_Info;            // Forward Reference




static
bool            RpgBaseClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_RPGBASE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(RpgBase_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        RpgBaseClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_RPGBASE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
RPGBASE_CLASS_VTBL    class_Vtbl = {
    {
        &RpgBase_Info,
        RpgBaseClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        RpgBase_Class,
        RpgBaseClass_WhoAmI,
        (P_OBJ_QUERYINFO)RpgBaseClass_QueryInfo,
        NULL                        // RpgBaseClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

RPGBASE_CLASS_DATA  RpgBase_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(RPGBASE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  RPGBASE_SINGLETON
extern
const
RPGBASE_VTBL       RpgBase_VtblShared;


RPGBASE_DATA *     RpgBase_getSingleton (
    void
)
{
    return (OBJ_ID)(RpgBase_ClassObj.pSingleton);
}


bool            RpgBase_setSingleton (
    RPGBASE_DATA       *pValue
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
    if (RpgBase_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(RpgBase_ClassObj.pSingleton));
    }
    RpgBase_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



RPGBASE_DATA *     RpgBase_Shared (
    void
)
{
    RPGBASE_DATA       *this = (OBJ_ID)(RpgBase_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = RpgBase_New( );
        obj_setVtbl(this, (void *)&RpgBase_VtblShared);
        RpgBase_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // RpgBase_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            RpgBase_SharedReset (
    void
)
{
    RPGBASE_DATA       *this = (OBJ_ID)(RpgBase_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&RpgBase_Vtbl);
        obj_Release(this);
        RpgBase_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          RpgBaseClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    RPGBASE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(RPGBASE_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&RpgBase_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&RpgBase_Info.pClassSuperObject;
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
                        return RpgBase_New;
                    }
                    break;
                    
                case 'P':
#ifdef  RPGBASE_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return RpgBase_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return RpgBase_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  RPGBASE_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return RpgBase_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return RpgBase_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return RpgBaseClass_WhoAmI;
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
bool            RpgBase_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_RPGBASE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(RpgBase_Class())->pClassSuperObject;
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
void            RpgBase_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          RpgBase_Class (
    void
)
{
    return (OBJ_ID)&RpgBase_ClassObj;
}


static
uint16_t        RpgBase_WhoAmI (
    void
)
{
    return OBJ_IDENT_RPGBASE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  RPGBASE_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
RPGBASE_VTBL     RpgBase_VtblShared = {
    {
        &RpgBase_Info,
        RpgBase_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        RpgBase_Dealloc,
        RpgBase_Class,
        RpgBase_WhoAmI,
        (P_OBJ_QUERYINFO)RpgBase_QueryInfo,
        (P_OBJ_TOSTRING)RpgBase_ToDebugString,
        NULL,           // RpgBase_Enable,
        NULL,           // RpgBase_Disable,
        NULL,           // (P_OBJ_ASSIGN)RpgBase_Assign,
        NULL,           // (P_OBJ_COMPARE)RpgBase_Compare,
        NULL,           // (P_OBJ_PTR)RpgBase_Copy,
        NULL,           // (P_OBJ_PTR)RpgBase_DeepCopy,
        NULL            // (P_OBJ_HASH)RpgBase_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //RpgBase_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
RPGBASE_VTBL     RpgBase_Vtbl = {
    {
        &RpgBase_Info,
        RpgBase_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        RpgBase_Dealloc,
        RpgBase_Class,
        RpgBase_WhoAmI,
        (P_OBJ_QUERYINFO)RpgBase_QueryInfo,
        (P_OBJ_TOSTRING)RpgBase_ToDebugString,
        NULL,           // RpgBase_Enable,
        NULL,           // RpgBase_Disable,
        NULL,           // (P_OBJ_ASSIGN)RpgBase_Assign,
        NULL,           // (P_OBJ_COMPARE)RpgBase_Compare,
        NULL,           // (P_OBJ_PTR)RpgBase_Copy,
        NULL,           // (P_OBJ_PTR)RpgBase_DeepCopy,
        NULL            // (P_OBJ_HASH)RpgBase_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //RpgBase_IsEnabled,
 
};



static
const
OBJ_INFO        RpgBase_Info = {
    "RpgBase",
    "Report Program Generator (RPG) Base",
    (OBJ_DATA *)&RpgBase_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&RpgBase_Vtbl,
    sizeof(RPGBASE_DATA)
};





