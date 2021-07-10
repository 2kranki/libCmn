// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'NetHTTPA'
//  Generated 07/07/2021 09:55:22


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




#define         NETHTTPA_OBJECT_C       1
#include        <NetHTTPA_internal.h>
#ifdef  NETHTTPA_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NetHTTPA_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NETHTTPA_SINGLETON
    volatile
    NETHTTPA_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NetHTTPAClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NetHTTPA_Info;            // Forward Reference




static
bool            NetHTTPAClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NETHTTPA_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NetHTTPA_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        NetHTTPAClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NETHTTPA_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NETHTTPA_CLASS_VTBL    class_Vtbl = {
    {
        &NetHTTPA_Info,
        NetHTTPAClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NetHTTPA_Class,
        NetHTTPAClass_WhoAmI,
        (P_OBJ_QUERYINFO)NetHTTPAClass_QueryInfo,
        NULL                        // NetHTTPAClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

NETHTTPA_CLASS_DATA  NetHTTPA_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NETHTTPA_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NETHTTPA_SINGLETON
extern
const
NETHTTPA_VTBL       NetHTTPA_VtblShared;


NETHTTPA_DATA *     NetHTTPA_getSingleton (
    void
)
{
    return (OBJ_ID)(NetHTTPA_ClassObj.pSingleton);
}


bool            NetHTTPA_setSingleton (
    NETHTTPA_DATA       *pValue
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
    if (NetHTTPA_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NetHTTPA_ClassObj.pSingleton));
    }
    NetHTTPA_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NETHTTPA_DATA *     NetHTTPA_Shared (
    void
)
{
    NETHTTPA_DATA       *this = (OBJ_ID)(NetHTTPA_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NetHTTPA_New( );
        obj_setVtbl(this, (void *)&NetHTTPA_VtblShared);
        NetHTTPA_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NetHTTPA_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NetHTTPA_SharedReset (
    void
)
{
    NETHTTPA_DATA       *this = (OBJ_ID)(NetHTTPA_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&NetHTTPA_Vtbl);
        obj_Release(this);
        NetHTTPA_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NetHTTPAClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NETHTTPA_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NETHTTPA_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&NetHTTPA_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&NetHTTPA_Info.pClassSuperObject;
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
                        return NetHTTPA_New;
                    }
                    break;
                    
                case 'P':
#ifdef  NETHTTPA_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return NetHTTPA_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return NetHTTPA_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  NETHTTPA_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return NetHTTPA_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return NetHTTPA_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NetHTTPAClass_WhoAmI;
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
bool            NetHTTPA_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NETHTTPA == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NetHTTPA_Class())->pClassSuperObject;
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
void            NetHTTPA_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NetHTTPA_Class (
    void
)
{
    return (OBJ_ID)&NetHTTPA_ClassObj;
}


static
uint16_t        NetHTTPA_WhoAmI (
    void
)
{
    return OBJ_IDENT_NETHTTPA;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  NETHTTPA_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
NETHTTPA_VTBL     NetHTTPA_VtblShared = {
    {
        &NetHTTPA_Info,
        NetHTTPA_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NetHTTPA_Dealloc,
        NetHTTPA_Class,
        NetHTTPA_WhoAmI,
        (P_OBJ_QUERYINFO)NetHTTPA_QueryInfo,
        (P_OBJ_TOSTRING)NetHTTPA_ToDebugString,
        NULL,           // NetHTTPA_Enable,
        NULL,           // NetHTTPA_Disable,
        NULL,           // (P_OBJ_ASSIGN)NetHTTPA_Assign,
        NULL,           // (P_OBJ_COMPARE)NetHTTPA_Compare,
        NULL,           // (P_OBJ_PTR)NetHTTPA_Copy,
        NULL,           // (P_OBJ_PTR)NetHTTPA_DeepCopy,
        NULL            // (P_OBJ_HASH)NetHTTPA_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NetHTTPA_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
NETHTTPA_VTBL     NetHTTPA_Vtbl = {
    {
        &NetHTTPA_Info,
        NetHTTPA_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        NetHTTPA_Dealloc,
        NetHTTPA_Class,
        NetHTTPA_WhoAmI,
        (P_OBJ_QUERYINFO)NetHTTPA_QueryInfo,
        (P_OBJ_TOSTRING)NetHTTPA_ToDebugString,
        NULL,           // NetHTTPA_Enable,
        NULL,           // NetHTTPA_Disable,
        NULL,           // (P_OBJ_ASSIGN)NetHTTPA_Assign,
        NULL,           // (P_OBJ_COMPARE)NetHTTPA_Compare,
        NULL,           // (P_OBJ_PTR)NetHTTPA_Copy,
        NULL,           // (P_OBJ_PTR)NetHTTPA_DeepCopy,
        NULL            // (P_OBJ_HASH)NetHTTPA_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NetHTTPA_IsEnabled,
 
};



static
const
OBJ_INFO        NetHTTPA_Info = {
    "NetHTTPA",
    "TCP/IP Network HTTP Response/Answer",
    (OBJ_DATA *)&NetHTTPA_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&NetHTTPA_Vtbl,
    sizeof(NETHTTPA_DATA)
};





