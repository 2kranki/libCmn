// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'ClassItem'
//  Generated 11/23/2021 12:46:23


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




#define         CLASSITEM_OBJECT_C       1
#include        <ClassItem_internal.h>
#ifdef  CLASSITEM_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ClassItem_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  CLASSITEM_SINGLETON
    volatile
    CLASSITEM_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ClassItemClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ClassItem_Info;            // Forward Reference




static
bool            ClassItemClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_CLASSITEM_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(ClassItem_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        ClassItemClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_CLASSITEM_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
CLASSITEM_CLASS_VTBL    class_Vtbl = {
    {
        &ClassItem_Info,
        ClassItemClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ClassItem_Class,
        ClassItemClass_WhoAmI,
        (P_OBJ_QUERYINFO)ClassItemClass_QueryInfo,
        NULL                        // ClassItemClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

CLASSITEM_CLASS_DATA  ClassItem_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(CLASSITEM_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  CLASSITEM_SINGLETON
extern
const
CLASSITEM_VTBL       ClassItem_VtblShared;


CLASSITEM_DATA *     ClassItem_getSingleton (
    void
)
{
    return (OBJ_ID)(ClassItem_ClassObj.pSingleton);
}


bool            ClassItem_setSingleton (
    CLASSITEM_DATA       *pValue
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
    if (ClassItem_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ClassItem_ClassObj.pSingleton));
    }
    ClassItem_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



CLASSITEM_DATA *     ClassItem_Shared (
    void
)
{
    CLASSITEM_DATA       *this = (OBJ_ID)(ClassItem_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ClassItem_New( );
        obj_setVtbl(this, (void *)&ClassItem_VtblShared);
        ClassItem_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ClassItem_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ClassItem_SharedReset (
    void
)
{
    CLASSITEM_DATA       *this = (OBJ_ID)(ClassItem_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&ClassItem_Vtbl);
        obj_Release(this);
        ClassItem_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ClassItemClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    CLASSITEM_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(CLASSITEM_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&ClassItem_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&ClassItem_Info.pClassSuperObject;
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
                        return ClassItem_New;
                    }
                    break;
                    
                case 'P':
#ifdef  CLASSITEM_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return ClassItem_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return ClassItem_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  CLASSITEM_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return ClassItem_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return ClassItem_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ClassItemClass_WhoAmI;
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
bool            ClassItem_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_CLASSITEM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(ClassItem_Class())->pClassSuperObject;
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
void            ClassItem_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ClassItem_Class (
    void
)
{
    return (OBJ_ID)&ClassItem_ClassObj;
}


static
uint16_t        ClassItem_WhoAmI (
    void
)
{
    return OBJ_IDENT_CLASSITEM;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  CLASSITEM_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
CLASSITEM_VTBL     ClassItem_VtblShared = {
    {
        &ClassItem_Info,
        ClassItem_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        ClassItem_Dealloc,
        ClassItem_Class,
        ClassItem_WhoAmI,
        (P_OBJ_QUERYINFO)ClassItem_QueryInfo,
        (P_OBJ_TOSTRING)ClassItem_ToDebugString,
        NULL,           // ClassItem_Enable,
        NULL,           // ClassItem_Disable,
        NULL,           // (P_OBJ_ASSIGN)ClassItem_Assign,
        NULL,           // (P_OBJ_COMPARE)ClassItem_Compare,
        NULL,           // (P_OBJ_PTR)ClassItem_Copy,
        NULL,           // (P_OBJ_PTR)ClassItem_DeepCopy,
        NULL            // (P_OBJ_HASH)ClassItem_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ClassItem_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
CLASSITEM_VTBL     ClassItem_Vtbl = {
    {
        &ClassItem_Info,
        ClassItem_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        ClassItem_Dealloc,
        ClassItem_Class,
        ClassItem_WhoAmI,
        (P_OBJ_QUERYINFO)ClassItem_QueryInfo,
        (P_OBJ_TOSTRING)ClassItem_ToDebugString,
        NULL,           // ClassItem_Enable,
        NULL,           // ClassItem_Disable,
        NULL,           // (P_OBJ_ASSIGN)ClassItem_Assign,
        NULL,           // (P_OBJ_COMPARE)ClassItem_Compare,
        NULL,           // (P_OBJ_PTR)ClassItem_Copy,
        NULL,           // (P_OBJ_PTR)ClassItem_DeepCopy,
        NULL            // (P_OBJ_HASH)ClassItem_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ClassItem_IsEnabled,
 
};



static
const
OBJ_INFO        ClassItem_Info = {
    "ClassItem",
    "Class Item",
    (OBJ_DATA *)&ClassItem_ClassObj,
    (OBJ_DATA *)&ClassItem_ClassObj,
    (OBJ_IUNKNOWN *)&ClassItem_Vtbl,
    sizeof(CLASSITEM_DATA)
};





