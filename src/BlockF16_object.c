// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'BlockF16'
//  Generated 10/22/2021 08:20:43


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




#define         BLOCKF16_OBJECT_C       1
#include        <BlockF16_internal.h>
#ifdef  BLOCKF16_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct BlockF16_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BLOCKF16_SINGLETON
    volatile
    BLOCKF16_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BlockF16Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        BlockF16_Info;            // Forward Reference




static
bool            BlockF16Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BLOCKF16_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(BlockF16_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        BlockF16Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_BLOCKF16_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BLOCKF16_CLASS_VTBL    class_Vtbl = {
    {
        &BlockF16_Info,
        BlockF16Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        BlockF16_Class,
        BlockF16Class_WhoAmI,
        (P_OBJ_QUERYINFO)BlockF16Class_QueryInfo,
        NULL                        // BlockF16Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

BLOCKF16_CLASS_DATA  BlockF16_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BLOCKF16_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BLOCKF16_SINGLETON
extern
const
BLOCKF16_VTBL       BlockF16_VtblShared;


BLOCKF16_DATA *     BlockF16_getSingleton (
    void
)
{
    return (OBJ_ID)(BlockF16_ClassObj.pSingleton);
}


bool            BlockF16_setSingleton (
    BLOCKF16_DATA       *pValue
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
    if (BlockF16_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(BlockF16_ClassObj.pSingleton));
    }
    BlockF16_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BLOCKF16_DATA *     BlockF16_Shared (
    void
)
{
    BLOCKF16_DATA       *this = (OBJ_ID)(BlockF16_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = BlockF16_New( );
        obj_setVtbl(this, (void *)&BlockF16_VtblShared);
        BlockF16_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // BlockF16_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            BlockF16_SharedReset (
    void
)
{
    BLOCKF16_DATA       *this = (OBJ_ID)(BlockF16_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&BlockF16_Vtbl);
        obj_Release(this);
        BlockF16_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BlockF16Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BLOCKF16_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BLOCKF16_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&BlockF16_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&BlockF16_Info.pClassSuperObject;
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
                        return BlockF16_New;
                    }
                    break;
                    
                case 'P':
#ifdef  BLOCKF16_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return BlockF16_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return BlockF16_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  BLOCKF16_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return BlockF16_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return BlockF16_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return BlockF16Class_WhoAmI;
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
bool            BlockF16_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BLOCKF16 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(BlockF16_Class())->pClassSuperObject;
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
void            BlockF16_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          BlockF16_Class (
    void
)
{
    return (OBJ_ID)&BlockF16_ClassObj;
}


static
uint16_t        BlockF16_WhoAmI (
    void
)
{
    return OBJ_IDENT_BLOCKF16;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  BLOCKF16_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
BLOCKF16_VTBL     BlockF16_VtblShared = {
    {
        &BlockF16_Info,
        BlockF16_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        BlockF16_Dealloc,
        BlockF16_Class,
        BlockF16_WhoAmI,
        (P_OBJ_QUERYINFO)BlockF16_QueryInfo,
        (P_OBJ_TOSTRING)BlockF16_ToDebugString,
        NULL,           // BlockF16_Enable,
        NULL,           // BlockF16_Disable,
        NULL,           // (P_OBJ_ASSIGN)BlockF16_Assign,
        NULL,           // (P_OBJ_COMPARE)BlockF16_Compare,
        NULL,           // (P_OBJ_PTR)BlockF16_Copy,
        NULL,           // (P_OBJ_PTR)BlockF16_DeepCopy,
        NULL            // (P_OBJ_HASH)BlockF16_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BlockF16_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
BLOCKF16_VTBL     BlockF16_Vtbl = {
    {
        &BlockF16_Info,
        BlockF16_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        BlockF16_Dealloc,
        BlockF16_Class,
        BlockF16_WhoAmI,
        (P_OBJ_QUERYINFO)BlockF16_QueryInfo,
        (P_OBJ_TOSTRING)BlockF16_ToDebugString,
        NULL,           // BlockF16_Enable,
        NULL,           // BlockF16_Disable,
        NULL,           // (P_OBJ_ASSIGN)BlockF16_Assign,
        NULL,           // (P_OBJ_COMPARE)BlockF16_Compare,
        NULL,           // (P_OBJ_PTR)BlockF16_Copy,
        NULL,           // (P_OBJ_PTR)BlockF16_DeepCopy,
        NULL            // (P_OBJ_HASH)BlockF16_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BlockF16_IsEnabled,
 
};



static
const
OBJ_INFO        BlockF16_Info = {
    "BlockF16",
    "Fixed Length Records within 16-bit sized Block",
    (OBJ_DATA *)&BlockF16_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&BlockF16_Vtbl,
    sizeof(BLOCKF16_DATA)
};





