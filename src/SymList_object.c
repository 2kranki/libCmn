// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'SymList'
//  Generated 07/13/2021 03:07:27


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




#define         SYMLIST_OBJECT_C       1
#include        <SymList_internal.h>
#ifdef  SYMLIST_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SymList_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SYMLIST_SINGLETON
    volatile
    SYMLIST_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SymListClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SymList_Info;            // Forward Reference




static
bool            SymListClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SYMLIST_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SymList_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        SymListClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SYMLIST_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SYMLIST_CLASS_VTBL    class_Vtbl = {
    {
        &SymList_Info,
        SymListClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SymList_Class,
        SymListClass_WhoAmI,
        (P_OBJ_QUERYINFO)SymListClass_QueryInfo,
        NULL                        // SymListClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

SYMLIST_CLASS_DATA  SymList_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SYMLIST_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SYMLIST_SINGLETON
extern
const
SYMLIST_VTBL       SymList_VtblShared;


SYMLIST_DATA *     SymList_getSingleton (
    void
)
{
    return (OBJ_ID)(SymList_ClassObj.pSingleton);
}


bool            SymList_setSingleton (
    SYMLIST_DATA       *pValue
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
    if (SymList_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SymList_ClassObj.pSingleton));
    }
    SymList_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SYMLIST_DATA *     SymList_Shared (
    void
)
{
    SYMLIST_DATA       *this = (OBJ_ID)(SymList_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SymList_New( );
        obj_setVtbl(this, (void *)&SymList_VtblShared);
        SymList_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SymList_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SymList_SharedReset (
    void
)
{
    SYMLIST_DATA       *this = (OBJ_ID)(SymList_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SymList_Vtbl);
        obj_Release(this);
        SymList_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SymListClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SYMLIST_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SYMLIST_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&SymList_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&SymList_Info.pClassSuperObject;
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
                        return SymList_New;
                    }
                    break;
                    
                case 'P':
#ifdef  SYMLIST_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return SymList_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return SymList_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  SYMLIST_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return SymList_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return SymList_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SymListClass_WhoAmI;
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
bool            SymList_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SYMLIST == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SymList_Class())->pClassSuperObject;
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
void            SymList_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SymList_Class (
    void
)
{
    return (OBJ_ID)&SymList_ClassObj;
}


static
uint16_t        SymList_WhoAmI (
    void
)
{
    return OBJ_IDENT_SYMLIST;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SYMLIST_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SYMLIST_VTBL     SymList_VtblShared = {
    {
        &SymList_Info,
        SymList_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SymList_Dealloc,
        SymList_Class,
        SymList_WhoAmI,
        (P_OBJ_QUERYINFO)SymList_QueryInfo,
        (P_OBJ_TOSTRING)SymList_ToDebugString,
        NULL,           // SymList_Enable,
        NULL,           // SymList_Disable,
        NULL,           // (P_OBJ_ASSIGN)SymList_Assign,
        NULL,           // (P_OBJ_COMPARE)SymList_Compare,
        NULL,           // (P_OBJ_PTR)SymList_Copy,
        NULL,           // (P_OBJ_PTR)SymList_DeepCopy,
        NULL            // (P_OBJ_HASH)SymList_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SymList_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SYMLIST_VTBL     SymList_Vtbl = {
    {
        &SymList_Info,
        SymList_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SymList_Dealloc,
        SymList_Class,
        SymList_WhoAmI,
        (P_OBJ_QUERYINFO)SymList_QueryInfo,
        (P_OBJ_TOSTRING)SymList_ToDebugString,
        NULL,           // SymList_Enable,
        NULL,           // SymList_Disable,
        NULL,           // (P_OBJ_ASSIGN)SymList_Assign,
        NULL,           // (P_OBJ_COMPARE)SymList_Compare,
        NULL,           // (P_OBJ_PTR)SymList_Copy,
        NULL,           // (P_OBJ_PTR)SymList_DeepCopy,
        NULL            // (P_OBJ_HASH)SymList_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SymList_IsEnabled,
 
};



static
const
OBJ_INFO        SymList_Info = {
    "SymList",
    "List of Symbol Table Entries",
    (OBJ_DATA *)&SymList_ClassObj,
    (OBJ_DATA *)&ObjList_ClassObj,
    (OBJ_IUNKNOWN *)&SymList_Vtbl,
    sizeof(SYMLIST_DATA)
};





