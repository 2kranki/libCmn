// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Net'
//  Generated 07/03/2021 07:04:16


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




#define         NET_OBJECT_C       1
#include        <Net_internal.h>
#ifdef  NET_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Net_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NET_SINGLETON
    volatile
    NET_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NetClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Net_Info;            // Forward Reference




static
bool            NetClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NET_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Net_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        NetClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NET_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NET_CLASS_VTBL    class_Vtbl = {
    {
        &Net_Info,
        NetClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Net_Class,
        NetClass_WhoAmI,
        (P_OBJ_QUERYINFO)NetClass_QueryInfo,
        NULL                        // NetClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

NET_CLASS_DATA  Net_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NET_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NET_SINGLETON
extern
const
NET_VTBL       Net_VtblShared;


NET_DATA *     Net_getSingleton (
    void
)
{
    return (OBJ_ID)(Net_ClassObj.pSingleton);
}


bool            Net_setSingleton (
    NET_DATA       *pValue
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
    if (Net_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Net_ClassObj.pSingleton));
    }
    Net_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NET_DATA *     Net_Shared (
    void
)
{
    NET_DATA       *this = (OBJ_ID)(Net_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Net_New( );
        obj_setVtbl(this, (void *)&Net_VtblShared);
        Net_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Net_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Net_SharedReset (
    void
)
{
    NET_DATA       *this = (OBJ_ID)(Net_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Net_Vtbl);
        obj_Release(this);
        Net_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NetClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NET_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NET_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Net_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Net_Info.pClassSuperObject;
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
                        return Net_New;
                    }
                    break;
                    
                case 'P':
#ifdef  NET_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Net_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Net_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  NET_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Net_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Net_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NetClass_WhoAmI;
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
bool            Net_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NET == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Net_Class())->pClassSuperObject;
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
void            Net_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Net_Class (
    void
)
{
    return (OBJ_ID)&Net_ClassObj;
}


static
uint16_t        Net_WhoAmI (
    void
)
{
    return OBJ_IDENT_NET;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  NET_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
NET_VTBL     Net_VtblShared = {
    {
        &Net_Info,
        Net_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Net_Dealloc,
        Net_Class,
        Net_WhoAmI,
        (P_OBJ_QUERYINFO)Net_QueryInfo,
        (P_OBJ_TOSTRING)Net_ToDebugString,
        NULL,           // Net_Enable,
        NULL,           // Net_Disable,
        NULL,           // (P_OBJ_ASSIGN)Net_Assign,
        NULL,           // (P_OBJ_COMPARE)Net_Compare,
        NULL,           // (P_OBJ_PTR)Net_Copy,
        NULL,           // (P_OBJ_PTR)Net_DeepCopy,
        NULL            // (P_OBJ_HASH)Net_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Net_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
NET_VTBL     Net_Vtbl = {
    {
        &Net_Info,
        Net_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Net_Dealloc,
        Net_Class,
        Net_WhoAmI,
        (P_OBJ_QUERYINFO)Net_QueryInfo,
        (P_OBJ_TOSTRING)Net_ToDebugString,
        NULL,           // Net_Enable,
        NULL,           // Net_Disable,
        NULL,           // (P_OBJ_ASSIGN)Net_Assign,
        NULL,           // (P_OBJ_COMPARE)Net_Compare,
        NULL,           // (P_OBJ_PTR)Net_Copy,
        NULL,           // (P_OBJ_PTR)Net_DeepCopy,
        NULL            // (P_OBJ_HASH)Net_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Net_IsEnabled,
 
};



static
const
OBJ_INFO        Net_Info = {
    "Net",
    "TCP/IP Network Support",
    (OBJ_DATA *)&Net_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Net_Vtbl,
    sizeof(NET_DATA)
};





