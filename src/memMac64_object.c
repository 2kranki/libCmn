// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'memMac64'
//  Generated 02/15/2021 16:01:03


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




#define         MEMMAC64_OBJECT_C       1
#include        <memMac64_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct memMac64_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  MEMMAC64_SINGLETON
    volatile
    MEMMAC64_DATA   *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
    MEMMAC64_DATA   obj;
    pthread_mutex_t mutex;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          memMac64Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        memMac64_Info;            // Forward Reference




static
bool            memMac64Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_MEMMAC64_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(memMac64_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        memMac64Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_MEMMAC64_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
MEMMAC64_CLASS_VTBL    class_Vtbl = {
    {
        &memMac64_Info,
        memMac64Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        memMac64_Class,
        memMac64Class_WhoAmI,
        (P_OBJ_QUERYINFO)memMac64Class_QueryInfo,
        NULL                        // memMac64Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

MEMMAC64_CLASS_DATA  memMac64_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(MEMMAC64_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    NULL,
    {0},
    PTHREAD_MUTEX_DEFAULT
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  MEMMAC64_SINGLETON
extern
const
MEMMAC64_VTBL       memMac64_VtblShared;


MEMMAC64_DATA *     memMac64_getSingleton (
    void
)
{
    return (OBJ_ID)(memMac64_ClassObj.pSingleton);
}


bool            memMac64_setSingleton (
    MEMMAC64_DATA   *pValue
)
{
    int             iRc;

    iRc = pthread_mutex_lock(&memMac64_ClassObj.mutex);

    obj_Retain(pValue);
    if (memMac64_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(memMac64_ClassObj.pSingleton));
    }
    memMac64_ClassObj.pSingleton = pValue;
    
    iRc = pthread_mutex_unlock(&memMac64_ClassObj.mutex);
    return true;
}



MEMMAC64_DATA * memMac64_Shared (
    void
)
{
    MEMMAC64_DATA   *this = (OBJ_ID)(memMac64_ClassObj.pSingleton);
    int             iRc;

    if (NULL == this) {
        iRc = pthread_mutex_lock(&memMac64_ClassObj.mutex);
        this = memMac64_Init(&memMac64_ClassObj.obj);
        obj_setVtbl(this, (void *)&memMac64_VtblShared);
        memMac64_setSingleton(this);
        obj_Release(this);
        memMac64_ClassObj.pSingleton = &memMac64_ClassObj.obj;
        iRc = pthread_mutex_unlock(&memMac64_ClassObj.mutex);
    }
    
    return this;
}



void            memMac64_SharedReset (
    void
)
{
    MEMMAC64_DATA       *this = (OBJ_ID)(memMac64_ClassObj.pSingleton);
    
    if (this) {
        //obj_setVtbl(this, (void *)&memMac64_Vtbl);
        //obj_Release(this);
        //memMac64_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          memMac64Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    MEMMAC64_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(MEMMAC64_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&memMac64_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&memMac64_Info.pClassSuperObject;
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
                        return memMac64_New;
                    }
                    break;
                    
                case 'P':
#ifdef  MEMMAC64_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return memMac64_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return memMac64_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  MEMMAC64_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return memMac64_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return memMac64_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return memMac64Class_WhoAmI;
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
bool            memMac64_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_MEMMAC64 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(memMac64_Class())->pClassSuperObject;
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
void            memMac64_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          memMac64_Class (
    void
)
{
    return (OBJ_ID)&memMac64_ClassObj;
}


static
uint16_t        memMac64_WhoAmI (
    void
)
{
    return OBJ_IDENT_MEMMAC64;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  MEMMAC64_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
MEMMAC64_VTBL     memMac64_VtblShared = {
    {
        &memMac64_Info,
        memMac64_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        memMac64_Dealloc,
        memMac64_Class,
        memMac64_WhoAmI,
        (P_OBJ_QUERYINFO)memMac64_QueryInfo,
        (P_OBJ_TOSTRING)memMac64_ToDebugString,
        NULL,           // memMac64_Enable,
        NULL,           // memMac64_Disable,
        NULL,           // (P_OBJ_ASSIGN)memMac64_Assign,
        NULL,           // (P_OBJ_COMPARE)memMac64_Compare,
        NULL,           // (P_OBJ_PTR)memMac64_Copy,
        NULL,           // (P_OBJ_PTR)memMac64_DeepCopy,
        NULL            // (P_OBJ_HASH)memMac64_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //memMac64_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
MEMMAC64_VTBL     memMac64_Vtbl = {
    {
        &memMac64_Info,
        memMac64_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        memMac64_Dealloc,
        memMac64_Class,
        memMac64_WhoAmI,
        (P_OBJ_QUERYINFO)memMac64_QueryInfo,
        (P_OBJ_TOSTRING)memMac64_ToDebugString,
        NULL,           // memMac64_Enable,
        NULL,           // memMac64_Disable,
        NULL,           // (P_OBJ_ASSIGN)memMac64_Assign,
        NULL,           // (P_OBJ_COMPARE)memMac64_Compare,
        NULL,           // (P_OBJ_PTR)memMac64_Copy,
        NULL,           // (P_OBJ_PTR)memMac64_DeepCopy,
        NULL            // (P_OBJ_HASH)memMac64_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //memMac64_IsEnabled,
 
};



static
const
OBJ_INFO        memMac64_Info = {
    "memMac64",
    "MacOS 64-Bit Memory Debug",
    (OBJ_DATA *)&memMac64_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&memMac64_Vtbl,
    sizeof(MEMMAC64_DATA)
};





