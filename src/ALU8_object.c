// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'ALU8'
//  Generated 12/06/2020 10:50:20


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




#define         ALU8_OBJECT_C       1
#include        <ALU8_internal.h>
#ifdef  ALU8_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ALU8_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  ALU8_SINGLETON
    volatile
    ALU8_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ALU8Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ALU8_Info;            // Forward Reference




static
bool            ALU8Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_ALU8_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(ALU8_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        ALU8Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_ALU8_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
ALU8_CLASS_VTBL    class_Vtbl = {
    {
        &ALU8_Info,
        ALU8Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ALU8_Class,
        ALU8Class_WhoAmI,
        (P_OBJ_QUERYINFO)ALU8Class_QueryInfo,
        NULL                        // ALU8Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

ALU8_CLASS_DATA  ALU8_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(ALU8_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  ALU8_SINGLETON
extern
const
ALU8_VTBL       ALU8_VtblShared;


ALU8_DATA *     ALU8_getSingleton (
    void
)
{
    return (OBJ_ID)(ALU8_ClassObj.pSingleton);
}


bool            ALU8_setSingleton (
    ALU8_DATA       *pValue
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
    if (ALU8_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ALU8_ClassObj.pSingleton));
    }
    ALU8_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



ALU8_DATA *     ALU8_Shared (
    void
)
{
    ALU8_DATA       *this = (OBJ_ID)(ALU8_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ALU8_New( );
        obj_setVtbl(this, (void *)&ALU8_VtblShared);
        ALU8_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ALU8_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ALU8_SharedReset (
    void
)
{
    ALU8_DATA       *this = (OBJ_ID)(ALU8_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&ALU8_Vtbl);
        obj_Release(this);
        ALU8_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ALU8Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    ALU8_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(ALU8_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&ALU8_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&ALU8_Info.pClassSuperObject;
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
                        return ALU8_New;
                    }
                    break;
                    
                case 'P':
#ifdef  ALU8_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return ALU8_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return ALU8_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  ALU8_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return ALU8_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return ALU8_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ALU8Class_WhoAmI;
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
bool            ALU8_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_ALU8 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(ALU8_Class())->pClassSuperObject;
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
void            ALU8_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ALU8_Class (
    void
)
{
    return (OBJ_ID)&ALU8_ClassObj;
}


static
uint16_t        ALU8_WhoAmI (
    void
)
{
    return OBJ_IDENT_ALU8;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  ALU8_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
ALU8_VTBL     ALU8_VtblShared = {
    {
        &ALU8_Info,
        ALU8_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        ALU8_Dealloc,
        ALU8_Class,
        ALU8_WhoAmI,
        (P_OBJ_QUERYINFO)ALU8_QueryInfo,
        (P_OBJ_TOSTRING)ALU8_ToDebugString,
        NULL,           // ALU8_Enable,
        NULL,           // ALU8_Disable,
        NULL,           // (P_OBJ_ASSIGN)ALU8_Assign,
        NULL,           // (P_OBJ_COMPARE)ALU8_Compare,
        NULL,           // (P_OBJ_PTR)ALU8_Copy,
        NULL,           // (P_OBJ_PTR)ALU8_DeepCopy,
        NULL            // (P_OBJ_HASH)ALU8_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ALU8_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
ALU8_VTBL     ALU8_Vtbl = {
    {
        &ALU8_Info,
        ALU8_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        ALU8_Dealloc,
        ALU8_Class,
        ALU8_WhoAmI,
        (P_OBJ_QUERYINFO)ALU8_QueryInfo,
        (P_OBJ_TOSTRING)ALU8_ToDebugString,
        NULL,           // ALU8_Enable,
        NULL,           // ALU8_Disable,
        NULL,           // (P_OBJ_ASSIGN)ALU8_Assign,
        NULL,           // (P_OBJ_COMPARE)ALU8_Compare,
        NULL,           // (P_OBJ_PTR)ALU8_Copy,
        NULL,           // (P_OBJ_PTR)ALU8_DeepCopy,
        NULL            // (P_OBJ_HASH)ALU8_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ALU8_IsEnabled,
 
};



static
const
OBJ_INFO        ALU8_Info = {
    "ALU8",
    "8-bit Arithmetic Logic Unit",
    (OBJ_DATA *)&ALU8_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&ALU8_Vtbl,
    sizeof(ALU8_DATA)
};





