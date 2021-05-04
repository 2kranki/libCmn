// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Consumer'
//  Generated 05/04/2021 09:30:56


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




#define         CONSUMER_OBJECT_C       1
#include        <Consumer_internal.h>
#ifdef  CONSUMER_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Consumer_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  CONSUMER_SINGLETON
    volatile
    CONSUMER_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ConsumerClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Consumer_Info;            // Forward Reference




static
bool            ConsumerClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_CONSUMER_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Consumer_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        ConsumerClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_CONSUMER_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
CONSUMER_CLASS_VTBL    class_Vtbl = {
    {
        &Consumer_Info,
        ConsumerClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Consumer_Class,
        ConsumerClass_WhoAmI,
        (P_OBJ_QUERYINFO)ConsumerClass_QueryInfo,
        NULL                        // ConsumerClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

CONSUMER_CLASS_DATA  Consumer_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(CONSUMER_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  CONSUMER_SINGLETON
extern
const
CONSUMER_VTBL       Consumer_VtblShared;


CONSUMER_DATA *     Consumer_getSingleton (
    void
)
{
    return (OBJ_ID)(Consumer_ClassObj.pSingleton);
}


bool            Consumer_setSingleton (
    CONSUMER_DATA       *pValue
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
    if (Consumer_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Consumer_ClassObj.pSingleton));
    }
    Consumer_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



CONSUMER_DATA *     Consumer_Shared (
    void
)
{
    CONSUMER_DATA       *this = (OBJ_ID)(Consumer_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Consumer_New( );
        obj_setVtbl(this, (void *)&Consumer_VtblShared);
        Consumer_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Consumer_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Consumer_SharedReset (
    void
)
{
    CONSUMER_DATA       *this = (OBJ_ID)(Consumer_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Consumer_Vtbl);
        obj_Release(this);
        Consumer_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ConsumerClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    CONSUMER_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(CONSUMER_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Consumer_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Consumer_Info.pClassSuperObject;
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
                        return Consumer_New;
                    }
                    break;
                    
                case 'P':
#ifdef  CONSUMER_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Consumer_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Consumer_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  CONSUMER_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Consumer_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Consumer_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ConsumerClass_WhoAmI;
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
bool            Consumer_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_CONSUMER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Consumer_Class())->pClassSuperObject;
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
void            Consumer_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Consumer_Class (
    void
)
{
    return (OBJ_ID)&Consumer_ClassObj;
}


static
uint16_t        Consumer_WhoAmI (
    void
)
{
    return OBJ_IDENT_CONSUMER;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  CONSUMER_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
CONSUMER_VTBL     Consumer_VtblShared = {
    {
        &Consumer_Info,
        Consumer_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Consumer_Dealloc,
        Consumer_Class,
        Consumer_WhoAmI,
        (P_OBJ_QUERYINFO)Consumer_QueryInfo,
        (P_OBJ_TOSTRING)Consumer_ToDebugString,
        NULL,           // Consumer_Enable,
        NULL,           // Consumer_Disable,
        NULL,           // (P_OBJ_ASSIGN)Consumer_Assign,
        NULL,           // (P_OBJ_COMPARE)Consumer_Compare,
        NULL,           // (P_OBJ_PTR)Consumer_Copy,
        NULL,           // (P_OBJ_PTR)Consumer_DeepCopy,
        NULL            // (P_OBJ_HASH)Consumer_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Consumer_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
CONSUMER_VTBL     Consumer_Vtbl = {
    {
        &Consumer_Info,
        Consumer_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Consumer_Dealloc,
        Consumer_Class,
        Consumer_WhoAmI,
        (P_OBJ_QUERYINFO)Consumer_QueryInfo,
        (P_OBJ_TOSTRING)Consumer_ToDebugString,
        NULL,           // Consumer_Enable,
        NULL,           // Consumer_Disable,
        NULL,           // (P_OBJ_ASSIGN)Consumer_Assign,
        NULL,           // (P_OBJ_COMPARE)Consumer_Compare,
        NULL,           // (P_OBJ_PTR)Consumer_Copy,
        NULL,           // (P_OBJ_PTR)Consumer_DeepCopy,
        NULL            // (P_OBJ_HASH)Consumer_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Consumer_IsEnabled,
 
};



static
const
OBJ_INFO        Consumer_Info = {
    "Consumer",
    "Consumer side of Producer/Consumer",
    (OBJ_DATA *)&Consumer_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Consumer_Vtbl,
    sizeof(CONSUMER_DATA)
};
#warning -- adjust super class object in Info above 
//          if object inherits from another class
//          Also, update description





