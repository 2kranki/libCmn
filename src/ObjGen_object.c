// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'ObjGen'
//  Generated 11/19/2021 06:00:58


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




#define         OBJGEN_OBJECT_C       1
#include        <ObjGen_internal.h>
#ifdef  OBJGEN_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ObjGen_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OBJGEN_SINGLETON
    volatile
    OBJGEN_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ObjGenClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ObjGen_Info;            // Forward Reference




static
bool            ObjGenClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OBJGEN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(ObjGen_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        ObjGenClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJGEN_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OBJGEN_CLASS_VTBL    class_Vtbl = {
    {
        &ObjGen_Info,
        ObjGenClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ObjGen_Class,
        ObjGenClass_WhoAmI,
        (P_OBJ_QUERYINFO)ObjGenClass_QueryInfo,
        NULL                        // ObjGenClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

OBJGEN_CLASS_DATA  ObjGen_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OBJGEN_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OBJGEN_SINGLETON
extern
const
OBJGEN_VTBL       ObjGen_VtblShared;


OBJGEN_DATA *     ObjGen_getSingleton (
    void
)
{
    return (OBJ_ID)(ObjGen_ClassObj.pSingleton);
}


bool            ObjGen_setSingleton (
    OBJGEN_DATA       *pValue
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
    if (ObjGen_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ObjGen_ClassObj.pSingleton));
    }
    ObjGen_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OBJGEN_DATA *     ObjGen_Shared (
    void
)
{
    OBJGEN_DATA       *this = (OBJ_ID)(ObjGen_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ObjGen_New( );
        obj_setVtbl(this, (void *)&ObjGen_VtblShared);
        ObjGen_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ObjGen_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ObjGen_SharedReset (
    void
)
{
    OBJGEN_DATA       *this = (OBJ_ID)(ObjGen_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&ObjGen_Vtbl);
        obj_Release(this);
        ObjGen_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ObjGenClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OBJGEN_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJGEN_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&ObjGen_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&ObjGen_Info.pClassSuperObject;
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
                        return ObjGen_New;
                    }
                    break;
                    
                case 'P':
#ifdef  OBJGEN_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return ObjGen_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return ObjGen_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  OBJGEN_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return ObjGen_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return ObjGen_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ObjGenClass_WhoAmI;
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
bool            ObjGen_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OBJGEN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(ObjGen_Class())->pClassSuperObject;
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
void            ObjGen_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ObjGen_Class (
    void
)
{
    return (OBJ_ID)&ObjGen_ClassObj;
}


static
uint16_t        ObjGen_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJGEN;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  OBJGEN_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
OBJGEN_VTBL     ObjGen_VtblShared = {
    {
        &ObjGen_Info,
        ObjGen_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        ObjGen_Dealloc,
        ObjGen_Class,
        ObjGen_WhoAmI,
        (P_OBJ_QUERYINFO)ObjGen_QueryInfo,
        (P_OBJ_TOSTRING)ObjGen_ToDebugString,
        NULL,           // ObjGen_Enable,
        NULL,           // ObjGen_Disable,
        NULL,           // (P_OBJ_ASSIGN)ObjGen_Assign,
        NULL,           // (P_OBJ_COMPARE)ObjGen_Compare,
        NULL,           // (P_OBJ_PTR)ObjGen_Copy,
        NULL,           // (P_OBJ_PTR)ObjGen_DeepCopy,
        NULL            // (P_OBJ_HASH)ObjGen_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ObjGen_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
OBJGEN_VTBL     ObjGen_Vtbl = {
    {
        &ObjGen_Info,
        ObjGen_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        ObjGen_Dealloc,
        ObjGen_Class,
        ObjGen_WhoAmI,
        (P_OBJ_QUERYINFO)ObjGen_QueryInfo,
        (P_OBJ_TOSTRING)ObjGen_ToDebugString,
        NULL,           // ObjGen_Enable,
        NULL,           // ObjGen_Disable,
        NULL,           // (P_OBJ_ASSIGN)ObjGen_Assign,
        NULL,           // (P_OBJ_COMPARE)ObjGen_Compare,
        NULL,           // (P_OBJ_PTR)ObjGen_Copy,
        NULL,           // (P_OBJ_PTR)ObjGen_DeepCopy,
        NULL            // (P_OBJ_HASH)ObjGen_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ObjGen_IsEnabled,
 
};



static
const
OBJ_INFO        ObjGen_Info = {
    "ObjGen",
    "Object Generation Helper Methods",
    (OBJ_DATA *)&ObjGen_ClassObj,
    (OBJ_DATA *)&ObjGen_ClassObj,
    (OBJ_IUNKNOWN *)&ObjGen_Vtbl,
    sizeof(OBJGEN_DATA)
};





