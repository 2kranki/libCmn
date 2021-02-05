// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'U32Index'
//  Generated 01/04/2021 10:35:59


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




#define         U32INDEX_OBJECT_C       1
#include        <U32Index_internal.h>
#ifdef  U32INDEX_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct U32Index_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  U32INDEX_SINGLETON
    volatile
    U32INDEX_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          U32IndexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        U32Index_Info;            // Forward Reference




static
bool            U32IndexClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_U32INDEX_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(U32Index_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        U32IndexClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_U32INDEX_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
U32INDEX_CLASS_VTBL    class_Vtbl = {
    {
        &U32Index_Info,
        U32IndexClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        U32Index_Class,
        U32IndexClass_WhoAmI,
        (P_OBJ_QUERYINFO)U32IndexClass_QueryInfo,
        NULL                        // U32IndexClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

U32INDEX_CLASS_DATA  U32Index_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(U32INDEX_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  U32INDEX_SINGLETON
extern
const
U32INDEX_VTBL       U32Index_VtblShared;


U32INDEX_DATA *     U32Index_getSingleton (
    void
)
{
    return (OBJ_ID)(U32Index_ClassObj.pSingleton);
}


bool            U32Index_setSingleton (
    U32INDEX_DATA       *pValue
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
    if (U32Index_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(U32Index_ClassObj.pSingleton));
    }
    U32Index_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



U32INDEX_DATA *     U32Index_Shared (
    void
)
{
    U32INDEX_DATA       *this = (OBJ_ID)(U32Index_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = U32Index_New( );
        obj_setVtbl(this, (void *)&U32Index_VtblShared);
        U32Index_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // U32Index_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            U32Index_SharedReset (
    void
)
{
    U32INDEX_DATA       *this = (OBJ_ID)(U32Index_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&U32Index_Vtbl);
        obj_Release(this);
        U32Index_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          U32IndexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    U32INDEX_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(U32INDEX_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&U32Index_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&U32Index_Info.pClassSuperObject;
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
                        return U32Index_New;
                    }
                    break;
                    
                case 'P':
#ifdef  U32INDEX_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return U32Index_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return U32Index_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  U32INDEX_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return U32Index_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return U32Index_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return U32IndexClass_WhoAmI;
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
bool            U32Index_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_U32INDEX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(U32Index_Class())->pClassSuperObject;
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
void            U32Index_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          U32Index_Class (
    void
)
{
    return (OBJ_ID)&U32Index_ClassObj;
}


static
uint16_t        U32Index_WhoAmI (
    void
)
{
    return OBJ_IDENT_U32INDEX;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  U32INDEX_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
U32INDEX_VTBL     U32Index_VtblShared = {
    {
        &U32Index_Info,
        U32Index_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        U32Index_Dealloc,
        U32Index_Class,
        U32Index_WhoAmI,
        (P_OBJ_QUERYINFO)U32Index_QueryInfo,
        (P_OBJ_TOSTRING)U32Index_ToDebugString,
        NULL,           // U32Index_Enable,
        NULL,           // U32Index_Disable,
        NULL,           // (P_OBJ_ASSIGN)U32Index_Assign,
        NULL,           // (P_OBJ_COMPARE)U32Index_Compare,
        NULL,           // (P_OBJ_PTR)U32Index_Copy,
        NULL,           // (P_OBJ_PTR)U32Index_DeepCopy,
        NULL            // (P_OBJ_HASH)U32Index_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //U32Index_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
U32INDEX_VTBL     U32Index_Vtbl = {
    {
        &U32Index_Info,
        U32Index_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        U32Index_Dealloc,
        U32Index_Class,
        U32Index_WhoAmI,
        (P_OBJ_QUERYINFO)U32Index_QueryInfo,
        (P_OBJ_TOSTRING)U32Index_ToDebugString,
        NULL,           // U32Index_Enable,
        NULL,           // U32Index_Disable,
        NULL,           // (P_OBJ_ASSIGN)U32Index_Assign,
        NULL,           // (P_OBJ_COMPARE)U32Index_Compare,
        NULL,           // (P_OBJ_PTR)U32Index_Copy,
        NULL,           // (P_OBJ_PTR)U32Index_DeepCopy,
        NULL            // (P_OBJ_HASH)U32Index_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //U32Index_IsEnabled,
 
};



static
const
OBJ_INFO        U32Index_Info = {
    "U32Index",
    "uint32_t Integer Index",
    (OBJ_DATA *)&U32Index_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&U32Index_Vtbl,
    sizeof(U32INDEX_DATA)
};





