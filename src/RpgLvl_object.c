// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'RpgLvl'
//  Generated 05/23/2021 00:37:45


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




#define         RPGLVL_OBJECT_C       1
#include        <RpgLvl_internal.h>
#ifdef  RPGLVL_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct RpgLvl_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  RPGLVL_SINGLETON
    volatile
    RPGLVL_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          RpgLvlClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        RpgLvl_Info;            // Forward Reference




static
bool            RpgLvlClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_RPGLVL_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(RpgLvl_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        RpgLvlClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_RPGLVL_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
RPGLVL_CLASS_VTBL    class_Vtbl = {
    {
        &RpgLvl_Info,
        RpgLvlClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        RpgLvl_Class,
        RpgLvlClass_WhoAmI,
        (P_OBJ_QUERYINFO)RpgLvlClass_QueryInfo,
        NULL                        // RpgLvlClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

RPGLVL_CLASS_DATA  RpgLvl_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(RPGLVL_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  RPGLVL_SINGLETON
extern
const
RPGLVL_VTBL       RpgLvl_VtblShared;


RPGLVL_DATA *     RpgLvl_getSingleton (
    void
)
{
    return (OBJ_ID)(RpgLvl_ClassObj.pSingleton);
}


bool            RpgLvl_setSingleton (
    RPGLVL_DATA       *pValue
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
    if (RpgLvl_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(RpgLvl_ClassObj.pSingleton));
    }
    RpgLvl_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



RPGLVL_DATA *     RpgLvl_Shared (
    void
)
{
    RPGLVL_DATA       *this = (OBJ_ID)(RpgLvl_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = RpgLvl_New( );
        obj_setVtbl(this, (void *)&RpgLvl_VtblShared);
        RpgLvl_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // RpgLvl_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            RpgLvl_SharedReset (
    void
)
{
    RPGLVL_DATA       *this = (OBJ_ID)(RpgLvl_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&RpgLvl_Vtbl);
        obj_Release(this);
        RpgLvl_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          RpgLvlClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    RPGLVL_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(RPGLVL_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&RpgLvl_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&RpgLvl_Info.pClassSuperObject;
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
                        return RpgLvl_New;
                    }
                    break;
                    
                case 'P':
#ifdef  RPGLVL_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return RpgLvl_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return RpgLvl_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  RPGLVL_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return RpgLvl_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return RpgLvl_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return RpgLvlClass_WhoAmI;
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
bool            RpgLvl_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_RPGLVL == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(RpgLvl_Class())->pClassSuperObject;
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
void            RpgLvl_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          RpgLvl_Class (
    void
)
{
    return (OBJ_ID)&RpgLvl_ClassObj;
}


static
uint16_t        RpgLvl_WhoAmI (
    void
)
{
    return OBJ_IDENT_RPGLVL;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  RPGLVL_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
RPGLVL_VTBL     RpgLvl_VtblShared = {
    {
        &RpgLvl_Info,
        RpgLvl_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        RpgLvl_Dealloc,
        RpgLvl_Class,
        RpgLvl_WhoAmI,
        (P_OBJ_QUERYINFO)RpgLvl_QueryInfo,
        (P_OBJ_TOSTRING)RpgLvl_ToDebugString,
        NULL,           // RpgLvl_Enable,
        NULL,           // RpgLvl_Disable,
        NULL,           // (P_OBJ_ASSIGN)RpgLvl_Assign,
        NULL,           // (P_OBJ_COMPARE)RpgLvl_Compare,
        NULL,           // (P_OBJ_PTR)RpgLvl_Copy,
        NULL,           // (P_OBJ_PTR)RpgLvl_DeepCopy,
        NULL            // (P_OBJ_HASH)RpgLvl_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //RpgLvl_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
RPGLVL_VTBL     RpgLvl_Vtbl = {
    {
        &RpgLvl_Info,
        RpgLvl_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        RpgLvl_Dealloc,
        RpgLvl_Class,
        RpgLvl_WhoAmI,
        (P_OBJ_QUERYINFO)RpgLvl_QueryInfo,
        (P_OBJ_TOSTRING)RpgLvl_ToDebugString,
        NULL,           // RpgLvl_Enable,
        NULL,           // RpgLvl_Disable,
        NULL,           // (P_OBJ_ASSIGN)RpgLvl_Assign,
        NULL,           // (P_OBJ_COMPARE)RpgLvl_Compare,
        NULL,           // (P_OBJ_PTR)RpgLvl_Copy,
        NULL,           // (P_OBJ_PTR)RpgLvl_DeepCopy,
        NULL            // (P_OBJ_HASH)RpgLvl_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //RpgLvl_IsEnabled,
 
};



static
const
OBJ_INFO        RpgLvl_Info = {
    "RpgLvl",
    "Rpg Level Handler",
    (OBJ_DATA *)&RpgLvl_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&RpgLvl_Vtbl,
    sizeof(RPGLVL_DATA)
};





