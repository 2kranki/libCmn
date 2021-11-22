// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Props'
//  Generated 11/21/2021 13:40:01


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




#define         PROPS_OBJECT_C       1
#include        <Props_internal.h>
#ifdef  PROPS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Props_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  PROPS_SINGLETON
    volatile
    PROPS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          PropsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Props_Info;            // Forward Reference




static
bool            PropsClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_PROPS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Props_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        PropsClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_PROPS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
PROPS_CLASS_VTBL    class_Vtbl = {
    {
        &Props_Info,
        PropsClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Props_Class,
        PropsClass_WhoAmI,
        (P_OBJ_QUERYINFO)PropsClass_QueryInfo,
        NULL                        // PropsClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

PROPS_CLASS_DATA  Props_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(PROPS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  PROPS_SINGLETON
extern
const
PROPS_VTBL       Props_VtblShared;


PROPS_DATA *     Props_getSingleton (
    void
)
{
    return (OBJ_ID)(Props_ClassObj.pSingleton);
}


bool            Props_setSingleton (
    PROPS_DATA       *pValue
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
    if (Props_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Props_ClassObj.pSingleton));
    }
    Props_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



PROPS_DATA *     Props_Shared (
    void
)
{
    PROPS_DATA       *this = (OBJ_ID)(Props_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Props_New( );
        obj_setVtbl(this, (void *)&Props_VtblShared);
        Props_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Props_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Props_SharedReset (
    void
)
{
    PROPS_DATA       *this = (OBJ_ID)(Props_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Props_Vtbl);
        obj_Release(this);
        Props_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          PropsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PROPS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PROPS_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Props_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Props_Info.pClassSuperObject;
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
                        return Props_New;
                    }
                    break;
                    
                case 'P':
#ifdef  PROPS_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Props_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Props_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  PROPS_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Props_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Props_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return PropsClass_WhoAmI;
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
bool            Props_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_PROPS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Props_Class())->pClassSuperObject;
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
void            Props_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Props_Class (
    void
)
{
    return (OBJ_ID)&Props_ClassObj;
}


static
uint16_t        Props_WhoAmI (
    void
)
{
    return OBJ_IDENT_PROPS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  PROPS_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
PROPS_VTBL     Props_VtblShared = {
    {
        &Props_Info,
        Props_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Props_Dealloc,
        Props_Class,
        Props_WhoAmI,
        (P_OBJ_QUERYINFO)Props_QueryInfo,
        (P_OBJ_TOSTRING)Props_ToDebugString,
        NULL,           // Props_Enable,
        NULL,           // Props_Disable,
        NULL,           // (P_OBJ_ASSIGN)Props_Assign,
        NULL,           // (P_OBJ_COMPARE)Props_Compare,
        NULL,           // (P_OBJ_PTR)Props_Copy,
        NULL,           // (P_OBJ_PTR)Props_DeepCopy,
        NULL            // (P_OBJ_HASH)Props_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Props_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
PROPS_VTBL     Props_Vtbl = {
    {
        &Props_Info,
        Props_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Props_Dealloc,
        Props_Class,
        Props_WhoAmI,
        (P_OBJ_QUERYINFO)Props_QueryInfo,
        (P_OBJ_TOSTRING)Props_ToDebugString,
        NULL,           // Props_Enable,
        NULL,           // Props_Disable,
        NULL,           // (P_OBJ_ASSIGN)Props_Assign,
        NULL,           // (P_OBJ_COMPARE)Props_Compare,
        NULL,           // (P_OBJ_PTR)Props_Copy,
        NULL,           // (P_OBJ_PTR)Props_DeepCopy,
        NULL            // (P_OBJ_HASH)Props_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Props_IsEnabled,
 
};



static
const
OBJ_INFO        Props_Info = {
    "Props",
    "Property File Generation",
    (OBJ_DATA *)&Props_ClassObj,
    (OBJ_DATA *)&Props_ClassObj,
    (OBJ_IUNKNOWN *)&Props_Vtbl,
    sizeof(PROPS_DATA)
};





