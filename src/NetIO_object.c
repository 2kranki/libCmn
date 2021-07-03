// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'NetIO'
//  Generated 07/02/2021 14:27:06


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




#define         NETIO_OBJECT_C       1
#include        <NetIO_internal.h>
#ifdef  NETIO_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NetIO_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NETIO_SINGLETON
    volatile
    NETIO_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NetIOClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NetIO_Info;            // Forward Reference




static
bool            NetIOClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NETIO_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NetIO_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        NetIOClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NETIO_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NETIO_CLASS_VTBL    class_Vtbl = {
    {
        &NetIO_Info,
        NetIOClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NetIO_Class,
        NetIOClass_WhoAmI,
        (P_OBJ_QUERYINFO)NetIOClass_QueryInfo,
        NULL                        // NetIOClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

NETIO_CLASS_DATA  NetIO_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NETIO_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NETIO_SINGLETON
extern
const
NETIO_VTBL       NetIO_VtblShared;


NETIO_DATA *     NetIO_getSingleton (
    void
)
{
    return (OBJ_ID)(NetIO_ClassObj.pSingleton);
}


bool            NetIO_setSingleton (
    NETIO_DATA       *pValue
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
    if (NetIO_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NetIO_ClassObj.pSingleton));
    }
    NetIO_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NETIO_DATA *     NetIO_Shared (
    void
)
{
    NETIO_DATA       *this = (OBJ_ID)(NetIO_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NetIO_New( );
        obj_setVtbl(this, (void *)&NetIO_VtblShared);
        NetIO_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NetIO_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NetIO_SharedReset (
    void
)
{
    NETIO_DATA       *this = (OBJ_ID)(NetIO_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&NetIO_Vtbl);
        obj_Release(this);
        NetIO_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NetIOClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NETIO_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NETIO_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&NetIO_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&NetIO_Info.pClassSuperObject;
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
                        return NetIO_New;
                    }
                    break;
                    
                case 'P':
#ifdef  NETIO_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return NetIO_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return NetIO_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  NETIO_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return NetIO_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return NetIO_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NetIOClass_WhoAmI;
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
bool            NetIO_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NETIO == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NetIO_Class())->pClassSuperObject;
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
void            NetIO_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NetIO_Class (
    void
)
{
    return (OBJ_ID)&NetIO_ClassObj;
}


static
uint16_t        NetIO_WhoAmI (
    void
)
{
    return OBJ_IDENT_NETIO;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  NETIO_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
NETIO_VTBL     NetIO_VtblShared = {
    {
        &NetIO_Info,
        NetIO_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NetIO_Dealloc,
        NetIO_Class,
        NetIO_WhoAmI,
        (P_OBJ_QUERYINFO)NetIO_QueryInfo,
        (P_OBJ_TOSTRING)NetIO_ToDebugString,
        NULL,           // NetIO_Enable,
        NULL,           // NetIO_Disable,
        NULL,           // (P_OBJ_ASSIGN)NetIO_Assign,
        NULL,           // (P_OBJ_COMPARE)NetIO_Compare,
        NULL,           // (P_OBJ_PTR)NetIO_Copy,
        NULL,           // (P_OBJ_PTR)NetIO_DeepCopy,
        NULL            // (P_OBJ_HASH)NetIO_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NetIO_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
NETIO_VTBL     NetIO_Vtbl = {
    {
        &NetIO_Info,
        NetIO_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        NetIO_Dealloc,
        NetIO_Class,
        NetIO_WhoAmI,
        (P_OBJ_QUERYINFO)NetIO_QueryInfo,
        (P_OBJ_TOSTRING)NetIO_ToDebugString,
        NULL,           // NetIO_Enable,
        NULL,           // NetIO_Disable,
        NULL,           // (P_OBJ_ASSIGN)NetIO_Assign,
        NULL,           // (P_OBJ_COMPARE)NetIO_Compare,
        NULL,           // (P_OBJ_PTR)NetIO_Copy,
        NULL,           // (P_OBJ_PTR)NetIO_DeepCopy,
        NULL            // (P_OBJ_HASH)NetIO_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NetIO_IsEnabled,
 
};



static
const
OBJ_INFO        NetIO_Info = {
    "NetIO",
    "Network I/O using Unix Sockets",
    (OBJ_DATA *)&NetIO_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&NetIO_Vtbl,
    sizeof(NETIO_DATA)
};





