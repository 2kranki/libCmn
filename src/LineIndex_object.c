// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'LineIndex'
//  Generated 06/04/2020 10:44:19


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




#define         LINEINDEX_OBJECT_C       1
#include        <LineIndex_internal.h>
#ifdef  LINEINDEX_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct LineIndex_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LINEINDEX_SINGLETON
    volatile
    LINEINDEX_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          LineIndexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        LineIndex_Info;            // Forward Reference




static
bool            LineIndexClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LINEINDEX_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(LineIndex_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        LineIndexClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_LINEINDEX_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LINEINDEX_CLASS_VTBL    class_Vtbl = {
    {
        &LineIndex_Info,
        LineIndexClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        LineIndex_Class,
        LineIndexClass_WhoAmI,
        (P_OBJ_QUERYINFO)LineIndexClass_QueryInfo,
        NULL                        // LineIndexClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LINEINDEX_CLASS_DATA  LineIndex_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LINEINDEX_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LINEINDEX_SINGLETON
extern
const
LINEINDEX_VTBL       LineIndex_VtblShared;


LINEINDEX_DATA *     LineIndex_getSingleton (
    void
)
{
    return (OBJ_ID)(LineIndex_ClassObj.pSingleton);
}


bool            LineIndex_setSingleton (
    LINEINDEX_DATA       *pValue
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
    if (LineIndex_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(LineIndex_ClassObj.pSingleton));
    }
    LineIndex_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LINEINDEX_DATA *     LineIndex_Shared (
    void
)
{
    LINEINDEX_DATA       *this = (OBJ_ID)(LineIndex_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = LineIndex_New( );
        obj_setVtbl(this, (void *)&LineIndex_VtblShared);
        LineIndex_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // LineIndex_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            LineIndex_SharedReset (
    void
)
{
    LINEINDEX_DATA       *this = (OBJ_ID)(LineIndex_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&LineIndex_Vtbl);
        obj_Release(this);
        LineIndex_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          LineIndexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LINEINDEX_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LINEINDEX_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&LineIndex_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&LineIndex_Info.pClassSuperObject;
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
                        return LineIndex_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LINEINDEX_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return LineIndex_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return LineIndex_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LINEINDEX_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return LineIndex_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return LineIndex_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return LineIndexClass_WhoAmI;
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
bool            LineIndex_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LINEINDEX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(LineIndex_Class())->pClassSuperObject;
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
void            LineIndex_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          LineIndex_Class (
    void
)
{
    return (OBJ_ID)&LineIndex_ClassObj;
}


static
uint16_t        LineIndex_WhoAmI (
    void
)
{
    return OBJ_IDENT_LINEINDEX;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LINEINDEX_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LINEINDEX_VTBL     LineIndex_VtblShared = {
    {
        &LineIndex_Info,
        LineIndex_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        LineIndex_Dealloc,
        LineIndex_Class,
        LineIndex_WhoAmI,
        (P_OBJ_QUERYINFO)LineIndex_QueryInfo,
        (P_OBJ_TOSTRING)LineIndex_ToDebugString,
        NULL,           // LineIndex_Enable,
        NULL,           // LineIndex_Disable,
        NULL,           // (P_OBJ_ASSIGN)LineIndex_Assign,
        NULL,           // (P_OBJ_COMPARE)LineIndex_Compare,
        NULL,           // (P_OBJ_PTR)LineIndex_Copy,
        NULL,           // (P_OBJ_PTR)LineIndex_DeepCopy,
        NULL            // (P_OBJ_HASH)LineIndex_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //LineIndex_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LINEINDEX_VTBL     LineIndex_Vtbl = {
    {
        &LineIndex_Info,
        LineIndex_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        LineIndex_Dealloc,
        LineIndex_Class,
        LineIndex_WhoAmI,
        (P_OBJ_QUERYINFO)LineIndex_QueryInfo,
        (P_OBJ_TOSTRING)LineIndex_ToDebugString,
        NULL,           // LineIndex_Enable,
        NULL,           // LineIndex_Disable,
        NULL,           // (P_OBJ_ASSIGN)LineIndex_Assign,
        NULL,           // (P_OBJ_COMPARE)LineIndex_Compare,
        NULL,           // (P_OBJ_PTR)LineIndex_Copy,
        NULL,           // (P_OBJ_PTR)LineIndex_DeepCopy,
        NULL            // (P_OBJ_HASH)LineIndex_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //LineIndex_IsEnabled,
 
};



static
const
OBJ_INFO        LineIndex_Info = {
    "LineIndex",
    "LineIndex",
    (OBJ_DATA *)&LineIndex_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&LineIndex_Vtbl,
    sizeof(LINEINDEX_DATA)
};
#warning -- adjust super class object in Info above 
//          if object inherits from another class
//          Also, update description





