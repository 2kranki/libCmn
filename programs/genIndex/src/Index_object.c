// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Index'
//  Generated 12/22/2021 13:33:31


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




#define         INDEX_OBJECT_C       1
#include        <Index_internal.h>
#ifdef  INDEX_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Index_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  INDEX_SINGLETON
    volatile
    INDEX_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          IndexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Index_Info;            // Forward Reference




static
bool            IndexClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_INDEX_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Index_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        IndexClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_INDEX_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
INDEX_CLASS_VTBL    class_Vtbl = {
    {
        &Index_Info,
        IndexClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Index_Class,
        IndexClass_WhoAmI,
        (P_OBJ_QUERYINFO)IndexClass_QueryInfo,
        NULL                        // IndexClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

INDEX_CLASS_DATA  Index_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(INDEX_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  INDEX_SINGLETON
extern
const
INDEX_VTBL       Index_VtblShared;


INDEX_DATA *     Index_getSingleton (
    void
)
{
    return (OBJ_ID)(Index_ClassObj.pSingleton);
}


bool            Index_setSingleton (
    INDEX_DATA       *pValue
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
    if (Index_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Index_ClassObj.pSingleton));
    }
    Index_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



INDEX_DATA *     Index_Shared (
    void
)
{
    INDEX_DATA       *this = (OBJ_ID)(Index_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Index_New( );
        obj_setVtbl(this, (void *)&Index_VtblShared);
        Index_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Index_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Index_SharedReset (
    void
)
{
    INDEX_DATA       *this = (OBJ_ID)(Index_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Index_Vtbl);
        obj_Release(this);
        Index_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          IndexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    INDEX_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(INDEX_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Index_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Index_Info.pClassSuperObject;
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
                        return Index_New;
                    }
                    break;
                    
                case 'P':
#ifdef  INDEX_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Index_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Index_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  INDEX_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Index_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Index_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return IndexClass_WhoAmI;
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
bool            Index_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_INDEX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Index_Class())->pClassSuperObject;
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
void            Index_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Index_Class (
    void
)
{
    return (OBJ_ID)&Index_ClassObj;
}


static
uint16_t        Index_WhoAmI (
    void
)
{
    return OBJ_IDENT_INDEX;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  INDEX_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
INDEX_VTBL     Index_VtblShared = {
    {
        &Index_Info,
        Index_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Index_Dealloc,
        Index_Class,
        Index_WhoAmI,
        (P_OBJ_QUERYINFO)Index_QueryInfo,
        (P_OBJ_TOSTRING)Index_ToDebugString,
        NULL,           // Index_Enable,
        NULL,           // Index_Disable,
        NULL,           // (P_OBJ_ASSIGN)Index_Assign,
        NULL,           // (P_OBJ_COMPARE)Index_Compare,
        NULL,           // (P_OBJ_PTR)Index_Copy,
        NULL,           // (P_OBJ_PTR)Index_DeepCopy,
        NULL            // (P_OBJ_HASH)Index_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Index_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
INDEX_VTBL     Index_Vtbl = {
    {
        &Index_Info,
        Index_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Index_Dealloc,
        Index_Class,
        Index_WhoAmI,
        (P_OBJ_QUERYINFO)Index_QueryInfo,
        (P_OBJ_TOSTRING)Index_ToDebugString,
        NULL,           // Index_Enable,
        NULL,           // Index_Disable,
        NULL,           // (P_OBJ_ASSIGN)Index_Assign,
        NULL,           // (P_OBJ_COMPARE)Index_Compare,
        NULL,           // (P_OBJ_PTR)Index_Copy,
        NULL,           // (P_OBJ_PTR)Index_DeepCopy,
        NULL            // (P_OBJ_HASH)Index_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Index_IsEnabled,
 
};



static
const
OBJ_INFO        Index_Info = {
    "Index",
    "Generate an index for a subdirectory",
    (OBJ_DATA *)&Index_ClassObj,
    (OBJ_DATA *)&Index_ClassObj,
    (OBJ_IUNKNOWN *)&Index_Vtbl,
    sizeof(INDEX_DATA)
};





