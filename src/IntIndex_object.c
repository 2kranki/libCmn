// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'IntIndex'
//  Generated 01/03/2021 13:14:35


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




#define         INTINDEX_OBJECT_C       1
#include        <IntIndex_internal.h>
#ifdef  INTINDEX_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct IntIndex_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  INTINDEX_SINGLETON
    volatile
    INTINDEX_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          IntIndexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        IntIndex_Info;            // Forward Reference




static
bool            IntIndexClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_INTINDEX_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(IntIndex_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        IntIndexClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_INTINDEX_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
INTINDEX_CLASS_VTBL    class_Vtbl = {
    {
        &IntIndex_Info,
        IntIndexClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        IntIndex_Class,
        IntIndexClass_WhoAmI,
        (P_OBJ_QUERYINFO)IntIndexClass_QueryInfo,
        NULL                        // IntIndexClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

INTINDEX_CLASS_DATA  IntIndex_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(INTINDEX_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  INTINDEX_SINGLETON
extern
const
INTINDEX_VTBL       IntIndex_VtblShared;


INTINDEX_DATA *     IntIndex_getSingleton (
    void
)
{
    return (OBJ_ID)(IntIndex_ClassObj.pSingleton);
}


bool            IntIndex_setSingleton (
    INTINDEX_DATA       *pValue
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
    if (IntIndex_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(IntIndex_ClassObj.pSingleton));
    }
    IntIndex_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



INTINDEX_DATA *     IntIndex_Shared (
    void
)
{
    INTINDEX_DATA       *this = (OBJ_ID)(IntIndex_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = IntIndex_New( );
        obj_setVtbl(this, (void *)&IntIndex_VtblShared);
        IntIndex_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // IntIndex_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            IntIndex_SharedReset (
    void
)
{
    INTINDEX_DATA       *this = (OBJ_ID)(IntIndex_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&IntIndex_Vtbl);
        obj_Release(this);
        IntIndex_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          IntIndexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    INTINDEX_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(INTINDEX_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&IntIndex_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&IntIndex_Info.pClassSuperObject;
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
                        return IntIndex_New;
                    }
                    break;
                    
                case 'P':
#ifdef  INTINDEX_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return IntIndex_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return IntIndex_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  INTINDEX_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return IntIndex_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return IntIndex_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return IntIndexClass_WhoAmI;
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
bool            IntIndex_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_INTINDEX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(IntIndex_Class())->pClassSuperObject;
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
void            IntIndex_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          IntIndex_Class (
    void
)
{
    return (OBJ_ID)&IntIndex_ClassObj;
}


static
uint16_t        IntIndex_WhoAmI (
    void
)
{
    return OBJ_IDENT_INTINDEX;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  INTINDEX_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
INTINDEX_VTBL     IntIndex_VtblShared = {
    {
        &IntIndex_Info,
        IntIndex_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        IntIndex_Dealloc,
        IntIndex_Class,
        IntIndex_WhoAmI,
        (P_OBJ_QUERYINFO)IntIndex_QueryInfo,
        (P_OBJ_TOSTRING)IntIndex_ToDebugString,
        NULL,           // IntIndex_Enable,
        NULL,           // IntIndex_Disable,
        NULL,           // (P_OBJ_ASSIGN)IntIndex_Assign,
        NULL,           // (P_OBJ_COMPARE)IntIndex_Compare,
        NULL,           // (P_OBJ_PTR)IntIndex_Copy,
        NULL,           // (P_OBJ_PTR)IntIndex_DeepCopy,
        NULL            // (P_OBJ_HASH)IntIndex_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //IntIndex_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
INTINDEX_VTBL     IntIndex_Vtbl = {
    {
        &IntIndex_Info,
        IntIndex_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        IntIndex_Dealloc,
        IntIndex_Class,
        IntIndex_WhoAmI,
        (P_OBJ_QUERYINFO)IntIndex_QueryInfo,
        (P_OBJ_TOSTRING)IntIndex_ToDebugString,
        NULL,           // IntIndex_Enable,
        NULL,           // IntIndex_Disable,
        NULL,           // (P_OBJ_ASSIGN)IntIndex_Assign,
        NULL,           // (P_OBJ_COMPARE)IntIndex_Compare,
        NULL,           // (P_OBJ_PTR)IntIndex_Copy,
        NULL,           // (P_OBJ_PTR)IntIndex_DeepCopy,
        NULL            // (P_OBJ_HASH)IntIndex_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //IntIndex_IsEnabled,
 
};



static
const
OBJ_INFO        IntIndex_Info = {
    "IntIndex",
    "Integer Index",
    (OBJ_DATA *)&IntIndex_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&IntIndex_Vtbl,
    sizeof(INTINDEX_DATA)
};





