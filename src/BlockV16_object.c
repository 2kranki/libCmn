// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'BlockV16'
//  Generated 10/22/2021 11:40:32


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




#define         BLOCKV16_OBJECT_C       1
#include        <BlockV16_internal.h>
#ifdef  BLOCKV16_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct BlockV16_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BLOCKV16_SINGLETON
    volatile
    BLOCKV16_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BlockV16Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        BlockV16_Info;            // Forward Reference




static
bool            BlockV16Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BLOCKV16_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(BlockV16_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        BlockV16Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_BLOCKV16_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BLOCKV16_CLASS_VTBL    class_Vtbl = {
    {
        &BlockV16_Info,
        BlockV16Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        BlockV16_Class,
        BlockV16Class_WhoAmI,
        (P_OBJ_QUERYINFO)BlockV16Class_QueryInfo,
        NULL                        // BlockV16Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

BLOCKV16_CLASS_DATA  BlockV16_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BLOCKV16_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BLOCKV16_SINGLETON
extern
const
BLOCKV16_VTBL       BlockV16_VtblShared;


BLOCKV16_DATA *     BlockV16_getSingleton (
    void
)
{
    return (OBJ_ID)(BlockV16_ClassObj.pSingleton);
}


bool            BlockV16_setSingleton (
    BLOCKV16_DATA       *pValue
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
    if (BlockV16_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(BlockV16_ClassObj.pSingleton));
    }
    BlockV16_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BLOCKV16_DATA *     BlockV16_Shared (
    void
)
{
    BLOCKV16_DATA       *this = (OBJ_ID)(BlockV16_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = BlockV16_New( );
        obj_setVtbl(this, (void *)&BlockV16_VtblShared);
        BlockV16_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // BlockV16_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            BlockV16_SharedReset (
    void
)
{
    BLOCKV16_DATA       *this = (OBJ_ID)(BlockV16_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&BlockV16_Vtbl);
        obj_Release(this);
        BlockV16_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BlockV16Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BLOCKV16_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BLOCKV16_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&BlockV16_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&BlockV16_Info.pClassSuperObject;
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
                        return BlockV16_New;
                    }
                    break;
                    
                case 'P':
#ifdef  BLOCKV16_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return BlockV16_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return BlockV16_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  BLOCKV16_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return BlockV16_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return BlockV16_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return BlockV16Class_WhoAmI;
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
bool            BlockV16_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BLOCKV16 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(BlockV16_Class())->pClassSuperObject;
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
void            BlockV16_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          BlockV16_Class (
    void
)
{
    return (OBJ_ID)&BlockV16_ClassObj;
}


static
uint16_t        BlockV16_WhoAmI (
    void
)
{
    return OBJ_IDENT_BLOCKV16;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  BLOCKV16_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
BLOCKV16_VTBL     BlockV16_VtblShared = {
    {
        &BlockV16_Info,
        BlockV16_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        BlockV16_Dealloc,
        BlockV16_Class,
        BlockV16_WhoAmI,
        (P_OBJ_QUERYINFO)BlockV16_QueryInfo,
        (P_OBJ_TOSTRING)BlockV16_ToDebugString,
        NULL,           // BlockV16_Enable,
        NULL,           // BlockV16_Disable,
        NULL,           // (P_OBJ_ASSIGN)BlockV16_Assign,
        NULL,           // (P_OBJ_COMPARE)BlockV16_Compare,
        NULL,           // (P_OBJ_PTR)BlockV16_Copy,
        NULL,           // (P_OBJ_PTR)BlockV16_DeepCopy,
        NULL            // (P_OBJ_HASH)BlockV16_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BlockV16_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
BLOCKV16_VTBL     BlockV16_Vtbl = {
    {
        &BlockV16_Info,
        BlockV16_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        BlockV16_Dealloc,
        BlockV16_Class,
        BlockV16_WhoAmI,
        (P_OBJ_QUERYINFO)BlockV16_QueryInfo,
        (P_OBJ_TOSTRING)BlockV16_ToDebugString,
        NULL,           // BlockV16_Enable,
        NULL,           // BlockV16_Disable,
        NULL,           // (P_OBJ_ASSIGN)BlockV16_Assign,
        NULL,           // (P_OBJ_COMPARE)BlockV16_Compare,
        NULL,           // (P_OBJ_PTR)BlockV16_Copy,
        NULL,           // (P_OBJ_PTR)BlockV16_DeepCopy,
        NULL            // (P_OBJ_HASH)BlockV16_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BlockV16_IsEnabled,
 
};



static
const
OBJ_INFO        BlockV16_Info = {
    "BlockV16",
    "Variable Length Records within 16-bit sized Block",
    (OBJ_DATA *)&BlockV16_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&BlockV16_Vtbl,
    sizeof(BLOCKV16_DATA)
};





