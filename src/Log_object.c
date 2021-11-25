// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Log'
//  Generated 11/24/2021 08:34:30


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




#define         LOG_OBJECT_C       1
#include        <Log_internal.h>
#ifdef  LOG_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Log_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LOG_SINGLETON
    volatile
    LOG_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          LogClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Log_InfoData;            // Forward Reference




static
bool            LogClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LOG_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Log_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        LogClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_LOG_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LOG_CLASS_VTBL    class_Vtbl = {
    {
        &Log_InfoData,
        LogClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Log_Class,
        LogClass_WhoAmI,
        (P_OBJ_QUERYINFO)LogClass_QueryInfo,
        NULL                        // LogClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LOG_CLASS_DATA  Log_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LOG_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LOG_SINGLETON
extern
const
LOG_VTBL       Log_VtblShared;


LOG_DATA *     Log_getSingleton (
    void
)
{
    return (OBJ_ID)(Log_ClassObj.pSingleton);
}


bool            Log_setSingleton (
    LOG_DATA       *pValue
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
    if (Log_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Log_ClassObj.pSingleton));
    }
    Log_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LOG_DATA *     Log_Shared (
    void
)
{
    LOG_DATA       *this = (OBJ_ID)(Log_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Log_New( );
        obj_setVtbl(this, (void *)&Log_VtblShared);
        Log_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Log_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Log_SharedReset (
    void
)
{
    LOG_DATA       *this = (OBJ_ID)(Log_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Log_Vtbl);
        obj_Release(this);
        Log_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          LogClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LOG_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LOG_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Log_InfoData;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Log_InfoData.pClassSuperObject;
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
                        return Log_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LOG_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Log_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Log_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LOG_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Log_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Log_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return LogClass_WhoAmI;
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
bool            Log_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LOG == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Log_Class())->pClassSuperObject;
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
void            Log_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Log_Class (
    void
)
{
    return (OBJ_ID)&Log_ClassObj;
}


static
uint16_t        Log_WhoAmI (
    void
)
{
    return OBJ_IDENT_LOG;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LOG_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LOG_VTBL     Log_VtblShared = {
    {
        &Log_Info,
        Log_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Log_Dealloc,
        Log_Class,
        Log_WhoAmI,
        (P_OBJ_QUERYINFO)Log_QueryInfo,
        (P_OBJ_TOSTRING)Log_ToDebugString,
        NULL,           // Log_Enable,
        NULL,           // Log_Disable,
        NULL,           // (P_OBJ_ASSIGN)Log_Assign,
        NULL,           // (P_OBJ_COMPARE)Log_Compare,
        NULL,           // (P_OBJ_PTR)Log_Copy,
        NULL,           // (P_OBJ_PTR)Log_DeepCopy,
        NULL            // (P_OBJ_HASH)Log_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Log_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LOG_VTBL     Log_Vtbl = {
    {
        &Log_InfoData,
        Log_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Log_Dealloc,
        Log_Class,
        Log_WhoAmI,
        (P_OBJ_QUERYINFO)Log_QueryInfo,
        (P_OBJ_TOSTRING)Log_ToDebugString,
        NULL,           // Log_Enable,
        NULL,           // Log_Disable,
        NULL,           // (P_OBJ_ASSIGN)Log_Assign,
        NULL,           // (P_OBJ_COMPARE)Log_Compare,
        NULL,           // (P_OBJ_PTR)Log_Copy,
        NULL,           // (P_OBJ_PTR)Log_DeepCopy,
        NULL            // (P_OBJ_HASH)Log_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    (void *)Log_Debug,
    (void *)Log_Fatal,
    (void *)Log_Info,
    (void *)Log_Warn,
    (void *)Log_Close,

};



static
const
OBJ_INFO        Log_InfoData = {
    "Log",
    "Log File Support",
    (OBJ_DATA *)&Log_ClassObj,
    (OBJ_DATA *)&Log_ClassObj,
    (OBJ_IUNKNOWN *)&Log_Vtbl,
    sizeof(LOG_DATA)
};





