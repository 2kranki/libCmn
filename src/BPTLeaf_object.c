// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'BPTLeaf'
//  Generated 09/23/2021 12:52:17


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




#define         BPTLEAF_OBJECT_C       1
#include        <BPTLeaf_internal.h>
#ifdef  BPTLEAF_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct BPTLeaf_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BPTLEAF_SINGLETON
    volatile
    BPTLEAF_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BPTLeafClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        BPTLeaf_Info;            // Forward Reference




static
bool            BPTLeafClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BPTLEAF_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(BPTLeaf_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        BPTLeafClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPTLEAF_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BPTLEAF_CLASS_VTBL    class_Vtbl = {
    {
        &BPTLeaf_Info,
        BPTLeafClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        BPTLeaf_Class,
        BPTLeafClass_WhoAmI,
        (P_OBJ_QUERYINFO)BPTLeafClass_QueryInfo,
        NULL                        // BPTLeafClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

BPTLEAF_CLASS_DATA  BPTLeaf_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BPTLEAF_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BPTLEAF_SINGLETON
extern
const
BPTLEAF_VTBL       BPTLeaf_VtblShared;


BPTLEAF_DATA *     BPTLeaf_getSingleton (
    void
)
{
    return (OBJ_ID)(BPTLeaf_ClassObj.pSingleton);
}


bool            BPTLeaf_setSingleton (
    BPTLEAF_DATA       *pValue
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
    if (BPTLeaf_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(BPTLeaf_ClassObj.pSingleton));
    }
    BPTLeaf_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BPTLEAF_DATA *     BPTLeaf_Shared (
    void
)
{
    BPTLEAF_DATA       *this = (OBJ_ID)(BPTLeaf_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = BPTLeaf_New( );
        obj_setVtbl(this, (void *)&BPTLeaf_VtblShared);
        BPTLeaf_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // BPTLeaf_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            BPTLeaf_SharedReset (
    void
)
{
    BPTLEAF_DATA       *this = (OBJ_ID)(BPTLeaf_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&BPTLeaf_Vtbl);
        obj_Release(this);
        BPTLeaf_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BPTLeafClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BPTLEAF_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPTLEAF_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&BPTLeaf_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&BPTLeaf_Info.pClassSuperObject;
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
                        return BPTLeaf_New;
                    }
                    break;
                    
                case 'P':
#ifdef  BPTLEAF_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return BPTLeaf_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return BPTLeaf_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  BPTLEAF_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return BPTLeaf_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return BPTLeaf_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return BPTLeafClass_WhoAmI;
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
bool            BPTLeaf_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BPTLEAF == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(BPTLeaf_Class())->pClassSuperObject;
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
void            BPTLeaf_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          BPTLeaf_Class (
    void
)
{
    return (OBJ_ID)&BPTLeaf_ClassObj;
}


static
uint16_t        BPTLeaf_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPTLEAF;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  BPTLEAF_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
BPTLEAF_VTBL     BPTLeaf_VtblShared = {
    {
        &BPTLeaf_Info,
        BPTLeaf_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        BPTLeaf_Dealloc,
        BPTLeaf_Class,
        BPTLeaf_WhoAmI,
        (P_OBJ_QUERYINFO)BPTLeaf_QueryInfo,
        (P_OBJ_TOSTRING)BPTLeaf_ToDebugString,
        NULL,           // BPTLeaf_Enable,
        NULL,           // BPTLeaf_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPTLeaf_Assign,
        NULL,           // (P_OBJ_COMPARE)BPTLeaf_Compare,
        NULL,           // (P_OBJ_PTR)BPTLeaf_Copy,
        NULL,           // (P_OBJ_PTR)BPTLeaf_DeepCopy,
        NULL            // (P_OBJ_HASH)BPTLeaf_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BPTLeaf_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
BPTLEAF_VTBL     BPTLeaf_Vtbl = {
    {
        &BPTLeaf_Info,
        BPTLeaf_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        BPTLeaf_Dealloc,
        BPTLeaf_Class,
        BPTLeaf_WhoAmI,
        (P_OBJ_QUERYINFO)BPTLeaf_QueryInfo,
        (P_OBJ_TOSTRING)BPTLeaf_ToDebugString,
        NULL,           // BPTLeaf_Enable,
        NULL,           // BPTLeaf_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPTLeaf_Assign,
        NULL,           // (P_OBJ_COMPARE)BPTLeaf_Compare,
        NULL,           // (P_OBJ_PTR)BPTLeaf_Copy,
        NULL,           // (P_OBJ_PTR)BPTLeaf_DeepCopy,
        NULL            // (P_OBJ_HASH)BPTLeaf_Hash,
    },
    // Put other object method names below this.
    // Properties:
    (void *)BPTLeaf_getBlock,
    (void *)BPTLeaf_getLBN,
    // Methods:
    //BPTLeaf_IsEnabled,
 
};



static
const
OBJ_INFO        BPTLeaf_Info = {
    "BPTLeaf",
    "B-Plus Tree Leaf",
    (OBJ_DATA *)&BPTLeaf_ClassObj,
    (OBJ_DATA *)&BlkdRcds16_ClassObj,
    (OBJ_IUNKNOWN *)&BPTLeaf_Vtbl,
    sizeof(BPTLEAF_DATA)
};





