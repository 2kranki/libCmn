// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'PropItem'
//  Generated 11/22/2021 12:43:21


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




#define         PROPITEM_OBJECT_C       1
#include        <PropItem_internal.h>
#ifdef  PROPITEM_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct PropItem_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  PROPITEM_SINGLETON
    volatile
    PROPITEM_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          PropItemClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        PropItem_Info;            // Forward Reference




static
bool            PropItemClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_PROPITEM_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(PropItem_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        PropItemClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_PROPITEM_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
PROPITEM_CLASS_VTBL    class_Vtbl = {
    {
        &PropItem_Info,
        PropItemClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        PropItem_Class,
        PropItemClass_WhoAmI,
        (P_OBJ_QUERYINFO)PropItemClass_QueryInfo,
        NULL                        // PropItemClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

PROPITEM_CLASS_DATA  PropItem_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(PROPITEM_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  PROPITEM_SINGLETON
extern
const
PROPITEM_VTBL       PropItem_VtblShared;


PROPITEM_DATA *     PropItem_getSingleton (
    void
)
{
    return (OBJ_ID)(PropItem_ClassObj.pSingleton);
}


bool            PropItem_setSingleton (
    PROPITEM_DATA       *pValue
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
    if (PropItem_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(PropItem_ClassObj.pSingleton));
    }
    PropItem_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



PROPITEM_DATA *     PropItem_Shared (
    void
)
{
    PROPITEM_DATA       *this = (OBJ_ID)(PropItem_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = PropItem_New( );
        obj_setVtbl(this, (void *)&PropItem_VtblShared);
        PropItem_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // PropItem_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            PropItem_SharedReset (
    void
)
{
    PROPITEM_DATA       *this = (OBJ_ID)(PropItem_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&PropItem_Vtbl);
        obj_Release(this);
        PropItem_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          PropItemClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PROPITEM_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PROPITEM_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&PropItem_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&PropItem_Info.pClassSuperObject;
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
                        return PropItem_New;
                    }
                    break;
                    
                case 'P':
#ifdef  PROPITEM_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return PropItem_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return PropItem_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  PROPITEM_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return PropItem_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return PropItem_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return PropItemClass_WhoAmI;
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
bool            PropItem_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_PROPITEM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(PropItem_Class())->pClassSuperObject;
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
void            PropItem_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          PropItem_Class (
    void
)
{
    return (OBJ_ID)&PropItem_ClassObj;
}


static
uint16_t        PropItem_WhoAmI (
    void
)
{
    return OBJ_IDENT_PROPITEM;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  PROPITEM_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
PROPITEM_VTBL     PropItem_VtblShared = {
    {
        &PropItem_Info,
        PropItem_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        PropItem_Dealloc,
        PropItem_Class,
        PropItem_WhoAmI,
        (P_OBJ_QUERYINFO)PropItem_QueryInfo,
        (P_OBJ_TOSTRING)PropItem_ToDebugString,
        NULL,           // PropItem_Enable,
        NULL,           // PropItem_Disable,
        NULL,           // (P_OBJ_ASSIGN)PropItem_Assign,
        NULL,           // (P_OBJ_COMPARE)PropItem_Compare,
        NULL,           // (P_OBJ_PTR)PropItem_Copy,
        NULL,           // (P_OBJ_PTR)PropItem_DeepCopy,
        NULL            // (P_OBJ_HASH)PropItem_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //PropItem_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
PROPITEM_VTBL     PropItem_Vtbl = {
    {
        &PropItem_Info,
        PropItem_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        PropItem_Dealloc,
        PropItem_Class,
        PropItem_WhoAmI,
        (P_OBJ_QUERYINFO)PropItem_QueryInfo,
        (P_OBJ_TOSTRING)PropItem_ToDebugString,
        NULL,           // PropItem_Enable,
        NULL,           // PropItem_Disable,
        (P_OBJ_ASSIGN)PropItem_Assign,
        (P_OBJ_COMPARE)PropItem_Compare,
        (P_OBJ_PTR)PropItem_Copy,
        NULL,           // (P_OBJ_PTR)PropItem_DeepCopy,
        NULL            // (P_OBJ_HASH)PropItem_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //PropItem_IsEnabled,
 
};



static
const
OBJ_INFO        PropItem_Info = {
    "PropItem",
    "Property Item",
    (OBJ_DATA *)&PropItem_ClassObj,
    (OBJ_DATA *)&PropItem_ClassObj,
    (OBJ_IUNKNOWN *)&PropItem_Vtbl,
    sizeof(PROPITEM_DATA)
};





