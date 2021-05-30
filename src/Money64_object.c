// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Money64'
//  Generated 05/29/2021 13:57:23


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




#define         MONEY64_OBJECT_C       1
#include        <Money64_internal.h>
#ifdef  MONEY64_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Money64_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  MONEY64_SINGLETON
    volatile
    MONEY64_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Money64Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Money64_Info;            // Forward Reference




static
bool            Money64Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_MONEY64_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Money64_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        Money64Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_MONEY64_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
MONEY64_CLASS_VTBL    class_Vtbl = {
    {
        &Money64_Info,
        Money64Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Money64_Class,
        Money64Class_WhoAmI,
        (P_OBJ_QUERYINFO)Money64Class_QueryInfo,
        NULL                        // Money64Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

MONEY64_CLASS_DATA  Money64_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(MONEY64_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  MONEY64_SINGLETON
extern
const
MONEY64_VTBL       Money64_VtblShared;


MONEY64_DATA *     Money64_getSingleton (
    void
)
{
    return (OBJ_ID)(Money64_ClassObj.pSingleton);
}


bool            Money64_setSingleton (
    MONEY64_DATA       *pValue
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
    if (Money64_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Money64_ClassObj.pSingleton));
    }
    Money64_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



MONEY64_DATA *     Money64_Shared (
    void
)
{
    MONEY64_DATA       *this = (OBJ_ID)(Money64_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Money64_New( );
        obj_setVtbl(this, (void *)&Money64_VtblShared);
        Money64_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Money64_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Money64_SharedReset (
    void
)
{
    MONEY64_DATA       *this = (OBJ_ID)(Money64_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Money64_Vtbl);
        obj_Release(this);
        Money64_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Money64Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    MONEY64_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(MONEY64_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Money64_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Money64_Info.pClassSuperObject;
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
                        return Money64_New;
                    }
                    break;
                    
                case 'P':
#ifdef  MONEY64_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Money64_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Money64_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  MONEY64_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Money64_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Money64_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return Money64Class_WhoAmI;
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
bool            Money64_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_MONEY64 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Money64_Class())->pClassSuperObject;
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
void            Money64_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Money64_Class (
    void
)
{
    return (OBJ_ID)&Money64_ClassObj;
}


static
uint16_t        Money64_WhoAmI (
    void
)
{
    return OBJ_IDENT_MONEY64;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  MONEY64_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
MONEY64_VTBL     Money64_VtblShared = {
    {
        &Money64_Info,
        Money64_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Money64_Dealloc,
        Money64_Class,
        Money64_WhoAmI,
        (P_OBJ_QUERYINFO)Money64_QueryInfo,
        (P_OBJ_TOSTRING)Money64_ToDebugString,
        NULL,           // Money64_Enable,
        NULL,           // Money64_Disable,
        NULL,           // (P_OBJ_ASSIGN)Money64_Assign,
        NULL,           // (P_OBJ_COMPARE)Money64_Compare,
        NULL,           // (P_OBJ_PTR)Money64_Copy,
        NULL,           // (P_OBJ_PTR)Money64_DeepCopy,
        NULL            // (P_OBJ_HASH)Money64_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Money64_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
MONEY64_VTBL     Money64_Vtbl = {
    {
        &Money64_Info,
        Money64_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Money64_Dealloc,
        Money64_Class,
        Money64_WhoAmI,
        (P_OBJ_QUERYINFO)Money64_QueryInfo,
        (P_OBJ_TOSTRING)Money64_ToDebugString,
        NULL,           // Money64_Enable,
        NULL,           // Money64_Disable,
        (P_OBJ_ASSIGN)Money64_Assign,
        NULL,           // (P_OBJ_COMPARE)Money64_Compare,
        (P_OBJ_PTR)Money64_Copy,
        NULL,           // (P_OBJ_PTR)Money64_DeepCopy,
        NULL            // (P_OBJ_HASH)Money64_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Money64_IsEnabled,
 
};



static
const
OBJ_INFO        Money64_Info = {
    "Money64",
    "Monetary Amounts based on 64-bit Signed Integer",
    (OBJ_DATA *)&Money64_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Money64_Vtbl,
    sizeof(MONEY64_DATA)
};





