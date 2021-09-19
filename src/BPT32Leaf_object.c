// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'BPT32Leaf'
//  Generated 09/18/2021 16:00:38


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




#define         BPT32LEAF_OBJECT_C       1
#include        <BPT32Leaf_internal.h>
#ifdef  BPT32LEAF_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct BPT32Leaf_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BPT32LEAF_SINGLETON
    volatile
    BPT32LEAF_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BPT32LeafClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        BPT32Leaf_Info;            // Forward Reference




static
bool            BPT32LeafClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BPT32LEAF_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(BPT32Leaf_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        BPT32LeafClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPT32LEAF_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BPT32LEAF_CLASS_VTBL    class_Vtbl = {
    {
        &BPT32Leaf_Info,
        BPT32LeafClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        BPT32Leaf_Class,
        BPT32LeafClass_WhoAmI,
        (P_OBJ_QUERYINFO)BPT32LeafClass_QueryInfo,
        NULL                        // BPT32LeafClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

BPT32LEAF_CLASS_DATA  BPT32Leaf_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BPT32LEAF_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BPT32LEAF_SINGLETON
extern
const
BPT32LEAF_VTBL       BPT32Leaf_VtblShared;


BPT32LEAF_DATA *     BPT32Leaf_getSingleton (
    void
)
{
    return (OBJ_ID)(BPT32Leaf_ClassObj.pSingleton);
}


bool            BPT32Leaf_setSingleton (
    BPT32LEAF_DATA       *pValue
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
    if (BPT32Leaf_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(BPT32Leaf_ClassObj.pSingleton));
    }
    BPT32Leaf_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BPT32LEAF_DATA *     BPT32Leaf_Shared (
    void
)
{
    BPT32LEAF_DATA       *this = (OBJ_ID)(BPT32Leaf_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = BPT32Leaf_New( );
        obj_setVtbl(this, (void *)&BPT32Leaf_VtblShared);
        BPT32Leaf_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // BPT32Leaf_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            BPT32Leaf_SharedReset (
    void
)
{
    BPT32LEAF_DATA       *this = (OBJ_ID)(BPT32Leaf_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&BPT32Leaf_Vtbl);
        obj_Release(this);
        BPT32Leaf_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BPT32LeafClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BPT32LEAF_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPT32LEAF_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&BPT32Leaf_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&BPT32Leaf_Info.pClassSuperObject;
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
                        return BPT32Leaf_New;
                    }
                    break;
                    
                case 'P':
#ifdef  BPT32LEAF_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return BPT32Leaf_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return BPT32Leaf_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  BPT32LEAF_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return BPT32Leaf_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return BPT32Leaf_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return BPT32LeafClass_WhoAmI;
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
bool            BPT32Leaf_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BPT32LEAF == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(BPT32Leaf_Class())->pClassSuperObject;
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
void            BPT32Leaf_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          BPT32Leaf_Class (
    void
)
{
    return (OBJ_ID)&BPT32Leaf_ClassObj;
}


static
uint16_t        BPT32Leaf_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPT32LEAF;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  BPT32LEAF_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
BPT32LEAF_VTBL     BPT32Leaf_VtblShared = {
    {
        &BPT32Leaf_Info,
        BPT32Leaf_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        BPT32Leaf_Dealloc,
        BPT32Leaf_Class,
        BPT32Leaf_WhoAmI,
        (P_OBJ_QUERYINFO)BPT32Leaf_QueryInfo,
        (P_OBJ_TOSTRING)BPT32Leaf_ToDebugString,
        NULL,           // BPT32Leaf_Enable,
        NULL,           // BPT32Leaf_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPT32Leaf_Assign,
        NULL,           // (P_OBJ_COMPARE)BPT32Leaf_Compare,
        NULL,           // (P_OBJ_PTR)BPT32Leaf_Copy,
        NULL,           // (P_OBJ_PTR)BPT32Leaf_DeepCopy,
        NULL            // (P_OBJ_HASH)BPT32Leaf_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BPT32Leaf_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
BPT32LEAF_VTBL     BPT32Leaf_Vtbl = {
    {
        &BPT32Leaf_Info,
        BPT32Leaf_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        BPT32Leaf_Dealloc,
        BPT32Leaf_Class,
        BPT32Leaf_WhoAmI,
        (P_OBJ_QUERYINFO)BPT32Leaf_QueryInfo,
        (P_OBJ_TOSTRING)BPT32Leaf_ToDebugString,
        NULL,           // BPT32Leaf_Enable,
        NULL,           // BPT32Leaf_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPT32Leaf_Assign,
        NULL,           // (P_OBJ_COMPARE)BPT32Leaf_Compare,
        NULL,           // (P_OBJ_PTR)BPT32Leaf_Copy,
        NULL,           // (P_OBJ_PTR)BPT32Leaf_DeepCopy,
        NULL            // (P_OBJ_HASH)BPT32Leaf_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BPT32Leaf_IsEnabled,
 
};



static
const
OBJ_INFO        BPT32Leaf_Info = {
    "BPT32Leaf",
    "32-Bit Index B-Plus Tree Leaf Block",
    (OBJ_DATA *)&BPT32Leaf_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&BPT32Leaf_Vtbl,
    sizeof(BPT32LEAF_DATA)
};





