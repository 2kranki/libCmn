// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'PropItems'
//  Generated 11/22/2021 12:42:57


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




#define         PROPITEMS_OBJECT_C       1
#include        <PropItems_internal.h>
#ifdef  PROPITEMS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct PropItems_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  PROPITEMS_SINGLETON
    volatile
    PROPITEMS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          PropItemsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        PropItems_Info;            // Forward Reference




static
bool            PropItemsClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_PROPITEMS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(PropItems_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        PropItemsClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_PROPITEMS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
PROPITEMS_CLASS_VTBL    class_Vtbl = {
    {
        &PropItems_Info,
        PropItemsClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        PropItems_Class,
        PropItemsClass_WhoAmI,
        (P_OBJ_QUERYINFO)PropItemsClass_QueryInfo,
        NULL                        // PropItemsClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

PROPITEMS_CLASS_DATA  PropItems_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(PROPITEMS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  PROPITEMS_SINGLETON
extern
const
PROPITEMS_VTBL       PropItems_VtblShared;


PROPITEMS_DATA *     PropItems_getSingleton (
    void
)
{
    return (OBJ_ID)(PropItems_ClassObj.pSingleton);
}


bool            PropItems_setSingleton (
    PROPITEMS_DATA       *pValue
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
    if (PropItems_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(PropItems_ClassObj.pSingleton));
    }
    PropItems_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



PROPITEMS_DATA *     PropItems_Shared (
    void
)
{
    PROPITEMS_DATA       *this = (OBJ_ID)(PropItems_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = PropItems_New( );
        obj_setVtbl(this, (void *)&PropItems_VtblShared);
        PropItems_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // PropItems_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            PropItems_SharedReset (
    void
)
{
    PROPITEMS_DATA       *this = (OBJ_ID)(PropItems_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&PropItems_Vtbl);
        obj_Release(this);
        PropItems_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          PropItemsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PROPITEMS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PROPITEMS_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&PropItems_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&PropItems_Info.pClassSuperObject;
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
                        return PropItems_New;
                    }
                    break;
                    
                case 'P':
#ifdef  PROPITEMS_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return PropItems_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return PropItems_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  PROPITEMS_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return PropItems_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return PropItems_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return PropItemsClass_WhoAmI;
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
bool            PropItems_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_PROPITEMS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(PropItems_Class())->pClassSuperObject;
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
void            PropItems_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          PropItems_Class (
    void
)
{
    return (OBJ_ID)&PropItems_ClassObj;
}


static
uint16_t        PropItems_WhoAmI (
    void
)
{
    return OBJ_IDENT_PROPITEMS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  PROPITEMS_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
PROPITEMS_VTBL     PropItems_VtblShared = {
    {
        &PropItems_Info,
        PropItems_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        PropItems_Dealloc,
        PropItems_Class,
        PropItems_WhoAmI,
        (P_OBJ_QUERYINFO)PropItems_QueryInfo,
        (P_OBJ_TOSTRING)PropItems_ToDebugString,
        NULL,           // PropItems_Enable,
        NULL,           // PropItems_Disable,
        NULL,           // (P_OBJ_ASSIGN)PropItems_Assign,
        NULL,           // (P_OBJ_COMPARE)PropItems_Compare,
        NULL,           // (P_OBJ_PTR)PropItems_Copy,
        NULL,           // (P_OBJ_PTR)PropItems_DeepCopy,
        NULL            // (P_OBJ_HASH)PropItems_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //PropItems_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
PROPITEMS_VTBL     PropItems_Vtbl = {
    {
        &PropItems_Info,
        PropItems_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        PropItems_Dealloc,
        PropItems_Class,
        PropItems_WhoAmI,
        (P_OBJ_QUERYINFO)PropItems_QueryInfo,
        (P_OBJ_TOSTRING)PropItems_ToDebugString,
        NULL,           // PropItems_Enable,
        NULL,           // PropItems_Disable,
        NULL,           // (P_OBJ_ASSIGN)PropItems_Assign,
        NULL,           // (P_OBJ_COMPARE)PropItems_Compare,
        NULL,           // (P_OBJ_PTR)PropItems_Copy,
        NULL,           // (P_OBJ_PTR)PropItems_DeepCopy,
        NULL            // (P_OBJ_HASH)PropItems_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //PropItems_IsEnabled,
 
};



static
const
OBJ_INFO        PropItems_Info = {
    "PropItems",
    "Property File Generation",
    (OBJ_DATA *)&PropItems_ClassObj,
    (OBJ_DATA *)&PropItems_ClassObj,
    (OBJ_IUNKNOWN *)&PropItems_Vtbl,
    sizeof(PROPITEMS_DATA)
};





