// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Item'
//  Generated 11/12/2021 13:39:34


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




#define         ITEM_OBJECT_C       1
#include        <Item_internal.h>
#ifdef  ITEM_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Item_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  ITEM_SINGLETON
    volatile
    ITEM_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ItemClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Item_Info;            // Forward Reference




static
bool            ItemClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_ITEM_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Item_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        ItemClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_ITEM_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
ITEM_CLASS_VTBL    class_Vtbl = {
    {
        &Item_Info,
        ItemClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Item_Class,
        ItemClass_WhoAmI,
        (P_OBJ_QUERYINFO)ItemClass_QueryInfo,
        NULL                        // ItemClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

ITEM_CLASS_DATA  Item_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(ITEM_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  ITEM_SINGLETON
extern
const
ITEM_VTBL       Item_VtblShared;


ITEM_DATA *     Item_getSingleton (
    void
)
{
    return (OBJ_ID)(Item_ClassObj.pSingleton);
}


bool            Item_setSingleton (
    ITEM_DATA       *pValue
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
    if (Item_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Item_ClassObj.pSingleton));
    }
    Item_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



ITEM_DATA *     Item_Shared (
    void
)
{
    ITEM_DATA       *this = (OBJ_ID)(Item_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Item_New( );
        obj_setVtbl(this, (void *)&Item_VtblShared);
        Item_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Item_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Item_SharedReset (
    void
)
{
    ITEM_DATA       *this = (OBJ_ID)(Item_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Item_Vtbl);
        obj_Release(this);
        Item_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ItemClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    ITEM_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(ITEM_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Item_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Item_Info.pClassSuperObject;
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
                        return Item_New;
                    }
                    break;
                    
                case 'P':
#ifdef  ITEM_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Item_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Item_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  ITEM_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Item_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Item_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ItemClass_WhoAmI;
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
bool            Item_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_ITEM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Item_Class())->pClassSuperObject;
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
void            Item_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Item_Class (
    void
)
{
    return (OBJ_ID)&Item_ClassObj;
}


static
uint16_t        Item_WhoAmI (
    void
)
{
    return OBJ_IDENT_ITEM;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  ITEM_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
ITEM_VTBL     Item_VtblShared = {
    {
        &Item_Info,
        Item_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Item_Dealloc,
        Item_Class,
        Item_WhoAmI,
        (P_OBJ_QUERYINFO)Item_QueryInfo,
        (P_OBJ_TOSTRING)Item_ToDebugString,
        NULL,           // Item_Enable,
        NULL,           // Item_Disable,
        NULL,           // (P_OBJ_ASSIGN)Item_Assign,
        NULL,           // (P_OBJ_COMPARE)Item_Compare,
        NULL,           // (P_OBJ_PTR)Item_Copy,
        NULL,           // (P_OBJ_PTR)Item_DeepCopy,
        NULL            // (P_OBJ_HASH)Item_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Item_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
ITEM_VTBL     Item_Vtbl = {
    {
        &Item_Info,
        Item_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Item_Dealloc,
        Item_Class,
        Item_WhoAmI,
        (P_OBJ_QUERYINFO)Item_QueryInfo,
        (P_OBJ_TOSTRING)Item_ToDebugString,
        NULL,           // Item_Enable,
        NULL,           // Item_Disable,
        (P_OBJ_ASSIGN)Item_Assign,
        (P_OBJ_COMPARE)Item_Compare,
        (P_OBJ_PTR)Item_Copy,
        NULL,           // (P_OBJ_PTR)Item_DeepCopy,
        NULL            // (P_OBJ_HASH)Item_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Item_IsEnabled,
 
};



static
const
OBJ_INFO        Item_Info = {
    "Item",
    "Description Item",
    (OBJ_DATA *)&Item_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Item_Vtbl,
    sizeof(ITEM_DATA)
};





