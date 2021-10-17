// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'BPTIndex'
//  Generated 09/25/2021 10:00:36


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




#define         BPTINDEX_OBJECT_C       1
#include        <BPTIndex_internal.h>
#ifdef  BPTINDEX_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct BPTIndex_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BPTINDEX_SINGLETON
    volatile
    BPTINDEX_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BPTIndexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        BPTIndex_Info;            // Forward Reference




static
bool            BPTIndexClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BPTINDEX_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(BPTIndex_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        BPTIndexClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPTINDEX_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BPTINDEX_CLASS_VTBL    class_Vtbl = {
    {
        &BPTIndex_Info,
        BPTIndexClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        BPTIndex_Class,
        BPTIndexClass_WhoAmI,
        (P_OBJ_QUERYINFO)BPTIndexClass_QueryInfo,
        NULL                        // BPTIndexClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

BPTINDEX_CLASS_DATA  BPTIndex_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BPTINDEX_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BPTINDEX_SINGLETON
extern
const
BPTINDEX_VTBL       BPTIndex_VtblShared;


BPTINDEX_DATA *     BPTIndex_getSingleton (
    void
)
{
    return (OBJ_ID)(BPTIndex_ClassObj.pSingleton);
}


bool            BPTIndex_setSingleton (
    BPTINDEX_DATA       *pValue
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
    if (BPTIndex_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(BPTIndex_ClassObj.pSingleton));
    }
    BPTIndex_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BPTINDEX_DATA *     BPTIndex_Shared (
    void
)
{
    BPTINDEX_DATA       *this = (OBJ_ID)(BPTIndex_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = BPTIndex_New( );
        obj_setVtbl(this, (void *)&BPTIndex_VtblShared);
        BPTIndex_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // BPTIndex_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            BPTIndex_SharedReset (
    void
)
{
    BPTINDEX_DATA       *this = (OBJ_ID)(BPTIndex_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&BPTIndex_Vtbl);
        obj_Release(this);
        BPTIndex_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BPTIndexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BPTINDEX_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPTINDEX_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&BPTIndex_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&BPTIndex_Info.pClassSuperObject;
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
                        return BPTIndex_New;
                    }
                    break;
                    
                case 'P':
#ifdef  BPTINDEX_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return BPTIndex_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return BPTIndex_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  BPTINDEX_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return BPTIndex_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return BPTIndex_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return BPTIndexClass_WhoAmI;
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
bool            BPTIndex_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BPTINDEX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(BPTIndex_Class())->pClassSuperObject;
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
void            BPTIndex_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          BPTIndex_Class (
    void
)
{
    return (OBJ_ID)&BPTIndex_ClassObj;
}


static
uint16_t        BPTIndex_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPTINDEX;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  BPTINDEX_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
BPTINDEX_VTBL     BPTIndex_VtblShared = {
    {
        &BPTIndex_Info,
        BPTIndex_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        BPTIndex_Dealloc,
        BPTIndex_Class,
        BPTIndex_WhoAmI,
        (P_OBJ_QUERYINFO)BPTIndex_QueryInfo,
        (P_OBJ_TOSTRING)BPTIndex_ToDebugString,
        NULL,           // BPTIndex_Enable,
        NULL,           // BPTIndex_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPTIndex_Assign,
        NULL,           // (P_OBJ_COMPARE)BPTIndex_Compare,
        NULL,           // (P_OBJ_PTR)BPTIndex_Copy,
        NULL,           // (P_OBJ_PTR)BPTIndex_DeepCopy,
        NULL            // (P_OBJ_HASH)BPTIndex_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BPTIndex_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
BPTINDEX_VTBL     BPTIndex_Vtbl = {
    {
        &BPTIndex_Info,
        BPTIndex_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        BPTIndex_Dealloc,
        BPTIndex_Class,
        BPTIndex_WhoAmI,
        (P_OBJ_QUERYINFO)BPTIndex_QueryInfo,
        (P_OBJ_TOSTRING)BPTIndex_ToDebugString,
        NULL,           // BPTIndex_Enable,
        NULL,           // BPTIndex_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPTIndex_Assign,
        NULL,           // (P_OBJ_COMPARE)BPTIndex_Compare,
        NULL,           // (P_OBJ_PTR)BPTIndex_Copy,
        NULL,           // (P_OBJ_PTR)BPTIndex_DeepCopy,
        NULL            // (P_OBJ_HASH)BPTIndex_Hash,
    },
    // Put other object method names below this.
    // Properties:
    (void *)BPTIndex_getBlock,
    (void *)BPTIndex_getLBN,
    // Methods:
    //BPTIndex_IsEnabled,
 
};



static
const
OBJ_INFO        BPTIndex_Info = {
    "BPTIndex",
    "B-Plus Tree Index Block",
    (OBJ_DATA *)&BPTIndex_ClassObj,
    (OBJ_DATA *)&BlkdRcds16_ClassObj,
    (OBJ_IUNKNOWN *)&BPTIndex_Vtbl,
    sizeof(BPTINDEX_DATA)
};





