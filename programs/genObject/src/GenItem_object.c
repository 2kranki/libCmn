// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'GenItem'
//  Generated 11/21/2021 11:15:18


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




#define         GENITEM_OBJECT_C       1
#include        <GenItem_internal.h>
#ifdef  GENITEM_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct GenItem_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  GENITEM_SINGLETON
    volatile
    GENITEM_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          GenItemClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        GenItem_Info;            // Forward Reference




static
bool            GenItemClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_GENITEM_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(GenItem_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        GenItemClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_GENITEM_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
GENITEM_CLASS_VTBL    class_Vtbl = {
    {
        &GenItem_Info,
        GenItemClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        GenItem_Class,
        GenItemClass_WhoAmI,
        (P_OBJ_QUERYINFO)GenItemClass_QueryInfo,
        NULL                        // GenItemClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

GENITEM_CLASS_DATA  GenItem_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(GENITEM_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  GENITEM_SINGLETON
extern
const
GENITEM_VTBL       GenItem_VtblShared;


GENITEM_DATA *     GenItem_getSingleton (
    void
)
{
    return (OBJ_ID)(GenItem_ClassObj.pSingleton);
}


bool            GenItem_setSingleton (
    GENITEM_DATA       *pValue
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
    if (GenItem_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(GenItem_ClassObj.pSingleton));
    }
    GenItem_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



GENITEM_DATA *     GenItem_Shared (
    void
)
{
    GENITEM_DATA       *this = (OBJ_ID)(GenItem_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = GenItem_New( );
        obj_setVtbl(this, (void *)&GenItem_VtblShared);
        GenItem_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // GenItem_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            GenItem_SharedReset (
    void
)
{
    GENITEM_DATA       *this = (OBJ_ID)(GenItem_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&GenItem_Vtbl);
        obj_Release(this);
        GenItem_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          GenItemClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    GENITEM_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(GENITEM_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&GenItem_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&GenItem_Info.pClassSuperObject;
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
                        return GenItem_New;
                    }
                    break;
                    
                case 'P':
#ifdef  GENITEM_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return GenItem_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return GenItem_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  GENITEM_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return GenItem_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return GenItem_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return GenItemClass_WhoAmI;
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
bool            GenItem_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_GENITEM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(GenItem_Class())->pClassSuperObject;
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
void            GenItem_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          GenItem_Class (
    void
)
{
    return (OBJ_ID)&GenItem_ClassObj;
}


static
uint16_t        GenItem_WhoAmI (
    void
)
{
    return OBJ_IDENT_GENITEM;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  GENITEM_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
GENITEM_VTBL     GenItem_VtblShared = {
    {
        &GenItem_Info,
        GenItem_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        GenItem_Dealloc,
        GenItem_Class,
        GenItem_WhoAmI,
        (P_OBJ_QUERYINFO)GenItem_QueryInfo,
        (P_OBJ_TOSTRING)GenItem_ToDebugString,
        NULL,           // GenItem_Enable,
        NULL,           // GenItem_Disable,
        NULL,           // (P_OBJ_ASSIGN)GenItem_Assign,
        NULL,           // (P_OBJ_COMPARE)GenItem_Compare,
        NULL,           // (P_OBJ_PTR)GenItem_Copy,
        NULL,           // (P_OBJ_PTR)GenItem_DeepCopy,
        NULL            // (P_OBJ_HASH)GenItem_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //GenItem_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
GENITEM_VTBL     GenItem_Vtbl = {
    {
        &GenItem_Info,
        GenItem_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        GenItem_Dealloc,
        GenItem_Class,
        GenItem_WhoAmI,
        (P_OBJ_QUERYINFO)GenItem_QueryInfo,
        (P_OBJ_TOSTRING)GenItem_ToDebugString,
        NULL,           // GenItem_Enable,
        NULL,           // GenItem_Disable,
        NULL,           // (P_OBJ_ASSIGN)GenItem_Assign,
        NULL,           // (P_OBJ_COMPARE)GenItem_Compare,
        NULL,           // (P_OBJ_PTR)GenItem_Copy,
        NULL,           // (P_OBJ_PTR)GenItem_DeepCopy,
        NULL            // (P_OBJ_HASH)GenItem_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //GenItem_IsEnabled,
 
};



static
const
OBJ_INFO        GenItem_Info = {
    "GenItem",
    "An Item to be generated",
    (OBJ_DATA *)&GenItem_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&GenItem_Vtbl,
    sizeof(GENITEM_DATA)
};





