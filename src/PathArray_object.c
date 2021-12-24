// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'PathArray'
//  Generated 12/23/2021 16:41:21


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




#define         PATHARRAY_OBJECT_C       1
#include        <PathArray_internal.h>
#ifdef  PATHARRAY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct PathArray_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  PATHARRAY_SINGLETON
    volatile
    PATHARRAY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          PathArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        PathArray_Info;            // Forward Reference




static
bool            PathArrayClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_PATHARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(PathArray_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        PathArrayClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_PATHARRAY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
PATHARRAY_CLASS_VTBL    class_Vtbl = {
    {
        &PathArray_Info,
        PathArrayClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        PathArray_Class,
        PathArrayClass_WhoAmI,
        (P_OBJ_QUERYINFO)PathArrayClass_QueryInfo,
        NULL                        // PathArrayClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

PATHARRAY_CLASS_DATA  PathArray_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(PATHARRAY_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  PATHARRAY_SINGLETON
extern
const
PATHARRAY_VTBL       PathArray_VtblShared;


PATHARRAY_DATA *     PathArray_getSingleton (
    void
)
{
    return (OBJ_ID)(PathArray_ClassObj.pSingleton);
}


bool            PathArray_setSingleton (
    PATHARRAY_DATA       *pValue
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
    if (PathArray_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(PathArray_ClassObj.pSingleton));
    }
    PathArray_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



PATHARRAY_DATA *     PathArray_Shared (
    void
)
{
    PATHARRAY_DATA       *this = (OBJ_ID)(PathArray_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = PathArray_New( );
        obj_setVtbl(this, (void *)&PathArray_VtblShared);
        PathArray_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // PathArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            PathArray_SharedReset (
    void
)
{
    PATHARRAY_DATA       *this = (OBJ_ID)(PathArray_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&PathArray_Vtbl);
        obj_Release(this);
        PathArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          PathArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PATHARRAY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PATHARRAY_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&PathArray_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&PathArray_Info.pClassSuperObject;
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
                        return PathArray_New;
                    }
                    break;
                    
                case 'P':
#ifdef  PATHARRAY_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return PathArray_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return PathArray_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  PATHARRAY_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return PathArray_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return PathArray_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return PathArrayClass_WhoAmI;
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
bool            PathArray_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_PATHARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(PathArray_Class())->pClassSuperObject;
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
void            PathArray_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          PathArray_Class (
    void
)
{
    return (OBJ_ID)&PathArray_ClassObj;
}


static
uint16_t        PathArray_WhoAmI (
    void
)
{
    return OBJ_IDENT_PATHARRAY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  PATHARRAY_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
PATHARRAY_VTBL     PathArray_VtblShared = {
    {
        &PathArray_Info,
        PathArray_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        PathArray_Dealloc,
        PathArray_Class,
        PathArray_WhoAmI,
        (P_OBJ_QUERYINFO)PathArray_QueryInfo,
        (P_OBJ_TOSTRING)PathArray_ToDebugString,
        NULL,           // PathArray_Enable,
        NULL,           // PathArray_Disable,
        NULL,           // (P_OBJ_ASSIGN)PathArray_Assign,
        NULL,           // (P_OBJ_COMPARE)PathArray_Compare,
        NULL,           // (P_OBJ_PTR)PathArray_Copy,
        NULL,           // (P_OBJ_PTR)PathArray_DeepCopy,
        NULL            // (P_OBJ_HASH)PathArray_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //PathArray_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
PATHARRAY_VTBL     PathArray_Vtbl = {
    {
        &PathArray_Info,
        PathArray_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        PathArray_Dealloc,
        PathArray_Class,
        PathArray_WhoAmI,
        (P_OBJ_QUERYINFO)PathArray_QueryInfo,
        (P_OBJ_TOSTRING)PathArray_ToDebugString,
        NULL,           // PathArray_Enable,
        NULL,           // PathArray_Disable,
        NULL,           // (P_OBJ_ASSIGN)PathArray_Assign,
        NULL,           // (P_OBJ_COMPARE)PathArray_Compare,
        NULL,           // (P_OBJ_PTR)PathArray_Copy,
        NULL,           // (P_OBJ_PTR)PathArray_DeepCopy,
        NULL            // (P_OBJ_HASH)PathArray_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //PathArray_IsEnabled,
 
};



static
const
OBJ_INFO        PathArray_Info = {
    "PathArray",
    "An array of Paths",
    (OBJ_DATA *)&PathArray_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&PathArray_Vtbl,
    sizeof(PATHARRAY_DATA)
};





