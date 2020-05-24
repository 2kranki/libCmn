// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Number'
//  Generated 05/23/11 11:24:01


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




#define         NUMBER_OBJECT_C       1
#include        <Number_internal.h>
#ifdef  NUMBER_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Number_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NUMBER_SINGLETON
    volatile
    NUMBER_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NumberClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Number_Info;            // Forward Reference




static
bool            NumberClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NUMBER_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Number_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        NumberClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NUMBER_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NUMBER_CLASS_VTBL    class_Vtbl = {
    {
        &Number_Info,
        NumberClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Number_Class,
        NumberClass_WhoAmI,
        (P_OBJ_QUERYINFO)NumberClass_QueryInfo,
        NULL                        // NumberClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

NUMBER_CLASS_DATA  Number_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NUMBER_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NUMBER_SINGLETON
extern
const
NUMBER_VTBL       Number_VtblShared;


NUMBER_DATA *     Number_getSingleton (
    void
)
{
    return (OBJ_ID)(Number_ClassObj.pSingleton);
}


bool            Number_setSingleton (
    NUMBER_DATA       *pValue
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
    if (Number_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Number_ClassObj.pSingleton));
    }
    Number_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NUMBER_DATA *     Number_Shared (
    void
)
{
    NUMBER_DATA       *this = (OBJ_ID)(Number_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Number_New( );
        obj_setVtbl(this, (void *)&Number_VtblShared);
        Number_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Number_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Number_SharedReset (
    void
)
{
    NUMBER_DATA       *this = (OBJ_ID)(Number_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Number_Vtbl);
        obj_Release(this);
        Number_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NumberClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NUMBER_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NUMBER_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Number_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Number_Info.pClassSuperObject;
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
                        return Number_New;
                    }
                    break;
                    
                case 'P':
#ifdef  NUMBER_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Number_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Number_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  NUMBER_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Number_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Number_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NumberClass_WhoAmI;
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
bool            Number_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NUMBER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Number_Class())->pClassSuperObject;
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
void            Number_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Number_Class (
    void
)
{
    return (OBJ_ID)&Number_ClassObj;
}


static
uint16_t        Number_WhoAmI (
    void
)
{
    return OBJ_IDENT_NUMBER;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  NUMBER_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
NUMBER_VTBL     Number_VtblShared = {
    {
        &Number_Info,
        Number_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Number_Dealloc,
        Number_Class,
        Number_WhoAmI,
        (P_OBJ_QUERYINFO)Number_QueryInfo,
        (P_OBJ_TOSTRING)Number_ToDebugString,
        NULL,           // Number_Enable,
        NULL,           // Number_Disable,
        NULL,           // (P_OBJ_ASSIGN)Number_Assign,
        NULL,           // (P_OBJ_COMPARE)Number_Compare,
        NULL,           // (P_OBJ_PTR)Number_Copy,
        NULL,           // (P_OBJ_PTR)Number_DeepCopy,
        NULL            // (P_OBJ_HASH)Number_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Number_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
NUMBER_VTBL     Number_Vtbl = {
    {
        &Number_Info,
        Number_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Number_Dealloc,
        Number_Class,
        Number_WhoAmI,
        (P_OBJ_QUERYINFO)Number_QueryInfo,
        (P_OBJ_TOSTRING)Number_ToDebugString,
        NULL,           // Number_Enable,
        NULL,           // Number_Disable,
        (P_OBJ_ASSIGN)Number_Assign,
        (P_OBJ_COMPARE)Number_Compare,
        (P_OBJ_PTR)Number_Copy,
        NULL,           // (P_OBJ_PTR)Number_DeepCopy,
        NULL            // (P_OBJ_HASH)Number_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Number_IsEnabled,
 
};



static
const
OBJ_INFO        Number_Info = {
    "Number",
    "Number",
    (OBJ_DATA *)&Number_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Number_Vtbl,
    sizeof(NUMBER_DATA)
};





