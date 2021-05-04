// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Producer'
//  Generated 05/04/2021 09:23:11


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




#define         PRODUCER_OBJECT_C       1
#include        <Producer_internal.h>
#ifdef  PRODUCER_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Producer_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  PRODUCER_SINGLETON
    volatile
    PRODUCER_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ProducerClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Producer_Info;            // Forward Reference




static
bool            ProducerClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_PRODUCER_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Producer_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        ProducerClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_PRODUCER_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
PRODUCER_CLASS_VTBL    class_Vtbl = {
    {
        &Producer_Info,
        ProducerClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Producer_Class,
        ProducerClass_WhoAmI,
        (P_OBJ_QUERYINFO)ProducerClass_QueryInfo,
        NULL                        // ProducerClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

PRODUCER_CLASS_DATA  Producer_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(PRODUCER_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  PRODUCER_SINGLETON
extern
const
PRODUCER_VTBL       Producer_VtblShared;


PRODUCER_DATA *     Producer_getSingleton (
    void
)
{
    return (OBJ_ID)(Producer_ClassObj.pSingleton);
}


bool            Producer_setSingleton (
    PRODUCER_DATA       *pValue
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
    if (Producer_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Producer_ClassObj.pSingleton));
    }
    Producer_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



PRODUCER_DATA *     Producer_Shared (
    void
)
{
    PRODUCER_DATA       *this = (OBJ_ID)(Producer_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Producer_New( );
        obj_setVtbl(this, (void *)&Producer_VtblShared);
        Producer_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Producer_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Producer_SharedReset (
    void
)
{
    PRODUCER_DATA       *this = (OBJ_ID)(Producer_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Producer_Vtbl);
        obj_Release(this);
        Producer_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ProducerClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PRODUCER_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PRODUCER_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Producer_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Producer_Info.pClassSuperObject;
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
                        return Producer_New;
                    }
                    break;
                    
                case 'P':
#ifdef  PRODUCER_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Producer_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Producer_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  PRODUCER_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Producer_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Producer_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ProducerClass_WhoAmI;
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
bool            Producer_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_PRODUCER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Producer_Class())->pClassSuperObject;
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
void            Producer_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Producer_Class (
    void
)
{
    return (OBJ_ID)&Producer_ClassObj;
}


static
uint16_t        Producer_WhoAmI (
    void
)
{
    return OBJ_IDENT_PRODUCER;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  PRODUCER_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
PRODUCER_VTBL     Producer_VtblShared = {
    {
        &Producer_Info,
        Producer_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Producer_Dealloc,
        Producer_Class,
        Producer_WhoAmI,
        (P_OBJ_QUERYINFO)Producer_QueryInfo,
        (P_OBJ_TOSTRING)Producer_ToDebugString,
        NULL,           // Producer_Enable,
        NULL,           // Producer_Disable,
        NULL,           // (P_OBJ_ASSIGN)Producer_Assign,
        NULL,           // (P_OBJ_COMPARE)Producer_Compare,
        NULL,           // (P_OBJ_PTR)Producer_Copy,
        NULL,           // (P_OBJ_PTR)Producer_DeepCopy,
        NULL            // (P_OBJ_HASH)Producer_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Producer_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
PRODUCER_VTBL     Producer_Vtbl = {
    {
        &Producer_Info,
        Producer_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Producer_Dealloc,
        Producer_Class,
        Producer_WhoAmI,
        (P_OBJ_QUERYINFO)Producer_QueryInfo,
        (P_OBJ_TOSTRING)Producer_ToDebugString,
        NULL,           // Producer_Enable,
        NULL,           // Producer_Disable,
        NULL,           // (P_OBJ_ASSIGN)Producer_Assign,
        NULL,           // (P_OBJ_COMPARE)Producer_Compare,
        NULL,           // (P_OBJ_PTR)Producer_Copy,
        NULL,           // (P_OBJ_PTR)Producer_DeepCopy,
        NULL            // (P_OBJ_HASH)Producer_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Producer_IsEnabled,
 
};



static
const
OBJ_INFO        Producer_Info = {
    "Producer",
    "Producer side of Producer/Consumer",
    (OBJ_DATA *)&Producer_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Producer_Vtbl,
    sizeof(PRODUCER_DATA)
};
#warning -- adjust super class object in Info above 
//          if object inherits from another class
//          Also, update description





