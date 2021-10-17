// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'BPT'
//  Generated 09/25/2021 10:01:15


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




#define         BPT_OBJECT_C       1
#include        <BPT_internal.h>
#ifdef  BPT_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct BPT_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BPT_SINGLETON
    volatile
    BPT_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BPTClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        BPT_Info;            // Forward Reference




static
bool            BPTClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BPT_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(BPT_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        BPTClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPT_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BPT_CLASS_VTBL    class_Vtbl = {
    {
        &BPT_Info,
        BPTClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        BPT_Class,
        BPTClass_WhoAmI,
        (P_OBJ_QUERYINFO)BPTClass_QueryInfo,
        NULL                        // BPTClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

BPT_CLASS_DATA  BPT_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BPT_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BPT_SINGLETON
extern
const
BPT_VTBL       BPT_VtblShared;


BPT_DATA *     BPT_getSingleton (
    void
)
{
    return (OBJ_ID)(BPT_ClassObj.pSingleton);
}


bool            BPT_setSingleton (
    BPT_DATA       *pValue
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
    if (BPT_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(BPT_ClassObj.pSingleton));
    }
    BPT_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BPT_DATA *     BPT_Shared (
    void
)
{
    BPT_DATA       *this = (OBJ_ID)(BPT_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = BPT_New( );
        obj_setVtbl(this, (void *)&BPT_VtblShared);
        BPT_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // BPT_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            BPT_SharedReset (
    void
)
{
    BPT_DATA       *this = (OBJ_ID)(BPT_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&BPT_Vtbl);
        obj_Release(this);
        BPT_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BPTClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BPT_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPT_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&BPT_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&BPT_Info.pClassSuperObject;
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
                    
                case 'B':
                    if (str_Compare("BlockRequest", (char *)pStr) == 0) {
                        return BPT_BlockRequest;
                    }
                    break;

                case 'N':
                    if (str_Compare("New", (char *)pStr) == 0) {
                        return BPT_New;
                    }
                    break;
                    
                case 'P':
#ifdef  BPT_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return BPT_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return BPT_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  BPT_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return BPT_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return BPT_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return BPTClass_WhoAmI;
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
bool            BPT_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BPT == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(BPT_Class())->pClassSuperObject;
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
void            BPT_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          BPT_Class (
    void
)
{
    return (OBJ_ID)&BPT_ClassObj;
}


static
uint16_t        BPT_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPT;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  BPT_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
BPT_VTBL     BPT_VtblShared = {
    {
        &BPT_Info,
        BPT_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        BPT_Dealloc,
        BPT_Class,
        BPT_WhoAmI,
        (P_OBJ_QUERYINFO)BPT_QueryInfo,
        (P_OBJ_TOSTRING)BPT_ToDebugString,
        NULL,           // BPT_Enable,
        NULL,           // BPT_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPT_Assign,
        NULL,           // (P_OBJ_COMPARE)BPT_Compare,
        NULL,           // (P_OBJ_PTR)BPT_Copy,
        NULL,           // (P_OBJ_PTR)BPT_DeepCopy,
        NULL            // (P_OBJ_HASH)BPT_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BPT_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
BPT_VTBL     BPT_Vtbl = {
    {
        &BPT_Info,
        BPT_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        BPT_Dealloc,
        BPT_Class,
        BPT_WhoAmI,
        (P_OBJ_QUERYINFO)BPT_QueryInfo,
        (P_OBJ_TOSTRING)BPT_ToDebugString,
        NULL,           // BPT_Enable,
        NULL,           // BPT_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPT_Assign,
        NULL,           // (P_OBJ_COMPARE)BPT_Compare,
        NULL,           // (P_OBJ_PTR)BPT_Copy,
        NULL,           // (P_OBJ_PTR)BPT_DeepCopy,
        NULL            // (P_OBJ_HASH)BPT_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BPT_IsEnabled,
 
};



static
const
OBJ_INFO        BPT_Info = {
    "BPT",
    "B-Plus Tree",
    (OBJ_DATA *)&BPT_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&BPT_Vtbl,
    sizeof(BPT_DATA)
};





