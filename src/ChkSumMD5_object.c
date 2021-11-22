// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'ChkSumMD5'
//  Generated 11/21/2021 14:37:54


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




#define         CHKSUMMD5_OBJECT_C       1
#include        <ChkSumMD5_internal.h>
#ifdef  CHKSUMMD5_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ChkSumMD5_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  CHKSUMMD5_SINGLETON
    volatile
    CHKSUMMD5_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ChkSumMD5Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ChkSumMD5_Info;            // Forward Reference




static
bool            ChkSumMD5Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_CHKSUMMD5_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(ChkSumMD5_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        ChkSumMD5Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_CHKSUMMD5_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
CHKSUMMD5_CLASS_VTBL    class_Vtbl = {
    {
        &ChkSumMD5_Info,
        ChkSumMD5Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ChkSumMD5_Class,
        ChkSumMD5Class_WhoAmI,
        (P_OBJ_QUERYINFO)ChkSumMD5Class_QueryInfo,
        NULL                        // ChkSumMD5Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

CHKSUMMD5_CLASS_DATA  ChkSumMD5_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(CHKSUMMD5_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  CHKSUMMD5_SINGLETON
extern
const
CHKSUMMD5_VTBL       ChkSumMD5_VtblShared;


CHKSUMMD5_DATA *     ChkSumMD5_getSingleton (
    void
)
{
    return (OBJ_ID)(ChkSumMD5_ClassObj.pSingleton);
}


bool            ChkSumMD5_setSingleton (
    CHKSUMMD5_DATA       *pValue
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
    if (ChkSumMD5_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ChkSumMD5_ClassObj.pSingleton));
    }
    ChkSumMD5_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



CHKSUMMD5_DATA *     ChkSumMD5_Shared (
    void
)
{
    CHKSUMMD5_DATA       *this = (OBJ_ID)(ChkSumMD5_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ChkSumMD5_New( );
        obj_setVtbl(this, (void *)&ChkSumMD5_VtblShared);
        ChkSumMD5_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ChkSumMD5_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ChkSumMD5_SharedReset (
    void
)
{
    CHKSUMMD5_DATA       *this = (OBJ_ID)(ChkSumMD5_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&ChkSumMD5_Vtbl);
        obj_Release(this);
        ChkSumMD5_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ChkSumMD5Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    CHKSUMMD5_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(CHKSUMMD5_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&ChkSumMD5_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&ChkSumMD5_Info.pClassSuperObject;
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
                        return ChkSumMD5_New;
                    }
                    break;
                    
                case 'P':
#ifdef  CHKSUMMD5_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return ChkSumMD5_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return ChkSumMD5_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  CHKSUMMD5_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return ChkSumMD5_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return ChkSumMD5_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ChkSumMD5Class_WhoAmI;
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
bool            ChkSumMD5_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_CHKSUMMD5 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(ChkSumMD5_Class())->pClassSuperObject;
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
void            ChkSumMD5_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ChkSumMD5_Class (
    void
)
{
    return (OBJ_ID)&ChkSumMD5_ClassObj;
}


static
uint16_t        ChkSumMD5_WhoAmI (
    void
)
{
    return OBJ_IDENT_CHKSUMMD5;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  CHKSUMMD5_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
CHKSUMMD5_VTBL     ChkSumMD5_VtblShared = {
    {
        &ChkSumMD5_Info,
        ChkSumMD5_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        ChkSumMD5_Dealloc,
        ChkSumMD5_Class,
        ChkSumMD5_WhoAmI,
        (P_OBJ_QUERYINFO)ChkSumMD5_QueryInfo,
        (P_OBJ_TOSTRING)ChkSumMD5_ToDebugString,
        NULL,           // ChkSumMD5_Enable,
        NULL,           // ChkSumMD5_Disable,
        NULL,           // (P_OBJ_ASSIGN)ChkSumMD5_Assign,
        NULL,           // (P_OBJ_COMPARE)ChkSumMD5_Compare,
        NULL,           // (P_OBJ_PTR)ChkSumMD5_Copy,
        NULL,           // (P_OBJ_PTR)ChkSumMD5_DeepCopy,
        NULL            // (P_OBJ_HASH)ChkSumMD5_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ChkSumMD5_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
CHKSUMMD5_VTBL     ChkSumMD5_Vtbl = {
    {
        &ChkSumMD5_Info,
        ChkSumMD5_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        ChkSumMD5_Dealloc,
        ChkSumMD5_Class,
        ChkSumMD5_WhoAmI,
        (P_OBJ_QUERYINFO)ChkSumMD5_QueryInfo,
        (P_OBJ_TOSTRING)ChkSumMD5_ToDebugString,
        NULL,           // ChkSumMD5_Enable,
        NULL,           // ChkSumMD5_Disable,
        NULL,           // (P_OBJ_ASSIGN)ChkSumMD5_Assign,
        NULL,           // (P_OBJ_COMPARE)ChkSumMD5_Compare,
        NULL,           // (P_OBJ_PTR)ChkSumMD5_Copy,
        NULL,           // (P_OBJ_PTR)ChkSumMD5_DeepCopy,
        NULL            // (P_OBJ_HASH)ChkSumMD5_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ChkSumMD5_IsEnabled,
 
};



static
const
OBJ_INFO        ChkSumMD5_Info = {
    "ChkSumMD5",
    "MD5 Check Sum Support",
    (OBJ_DATA *)&ChkSumMD5_ClassObj,
    (OBJ_DATA *)&ChkSumMD5_ClassObj,
    (OBJ_IUNKNOWN *)&ChkSumMD5_Vtbl,
    sizeof(CHKSUMMD5_DATA)
};





