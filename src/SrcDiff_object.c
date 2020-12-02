// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'SrcDiff'
//  Generated 12/01/2020 15:31:46


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




#define         SRCDIFF_OBJECT_C       1
#include        <SrcDiff_internal.h>
#ifdef  SRCDIFF_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SrcDiff_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SRCDIFF_SINGLETON
    volatile
    SRCDIFF_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SrcDiffClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SrcDiff_Info;            // Forward Reference




static
bool            SrcDiffClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SRCDIFF_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SrcDiff_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        SrcDiffClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCDIFF_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SRCDIFF_CLASS_VTBL    class_Vtbl = {
    {
        &SrcDiff_Info,
        SrcDiffClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SrcDiff_Class,
        SrcDiffClass_WhoAmI,
        (P_OBJ_QUERYINFO)SrcDiffClass_QueryInfo,
        NULL                        // SrcDiffClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

SRCDIFF_CLASS_DATA  SrcDiff_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SRCDIFF_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SRCDIFF_SINGLETON
extern
const
SRCDIFF_VTBL       SrcDiff_VtblShared;


SRCDIFF_DATA *     SrcDiff_getSingleton (
    void
)
{
    return (OBJ_ID)(SrcDiff_ClassObj.pSingleton);
}


bool            SrcDiff_setSingleton (
    SRCDIFF_DATA       *pValue
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
    if (SrcDiff_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SrcDiff_ClassObj.pSingleton));
    }
    SrcDiff_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SRCDIFF_DATA *     SrcDiff_Shared (
    void
)
{
    SRCDIFF_DATA       *this = (OBJ_ID)(SrcDiff_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SrcDiff_New( );
        obj_setVtbl(this, (void *)&SrcDiff_VtblShared);
        SrcDiff_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SrcDiff_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SrcDiff_SharedReset (
    void
)
{
    SRCDIFF_DATA       *this = (OBJ_ID)(SrcDiff_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SrcDiff_Vtbl);
        obj_Release(this);
        SrcDiff_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SrcDiffClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SRCDIFF_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCDIFF_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&SrcDiff_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&SrcDiff_Info.pClassSuperObject;
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
                        return SrcDiff_New;
                    }
                    break;
                    
                case 'P':
#ifdef  SRCDIFF_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return SrcDiff_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return SrcDiff_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  SRCDIFF_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return SrcDiff_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return SrcDiff_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SrcDiffClass_WhoAmI;
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
bool            SrcDiff_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SRCDIFF == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SrcDiff_Class())->pClassSuperObject;
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
void            SrcDiff_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SrcDiff_Class (
    void
)
{
    return (OBJ_ID)&SrcDiff_ClassObj;
}


static
uint16_t        SrcDiff_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCDIFF;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SRCDIFF_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SRCDIFF_VTBL     SrcDiff_VtblShared = {
    {
        &SrcDiff_Info,
        SrcDiff_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SrcDiff_Dealloc,
        SrcDiff_Class,
        SrcDiff_WhoAmI,
        (P_OBJ_QUERYINFO)SrcDiff_QueryInfo,
        (P_OBJ_TOSTRING)SrcDiff_ToDebugString,
        NULL,           // SrcDiff_Enable,
        NULL,           // SrcDiff_Disable,
        NULL,           // (P_OBJ_ASSIGN)SrcDiff_Assign,
        NULL,           // (P_OBJ_COMPARE)SrcDiff_Compare,
        NULL,           // (P_OBJ_PTR)SrcDiff_Copy,
        NULL,           // (P_OBJ_PTR)SrcDiff_DeepCopy,
        NULL            // (P_OBJ_HASH)SrcDiff_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SrcDiff_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SRCDIFF_VTBL     SrcDiff_Vtbl = {
    {
        &SrcDiff_Info,
        SrcDiff_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SrcDiff_Dealloc,
        SrcDiff_Class,
        SrcDiff_WhoAmI,
        (P_OBJ_QUERYINFO)SrcDiff_QueryInfo,
        (P_OBJ_TOSTRING)SrcDiff_ToDebugString,
        NULL,           // SrcDiff_Enable,
        NULL,           // SrcDiff_Disable,
        NULL,           // (P_OBJ_ASSIGN)SrcDiff_Assign,
        NULL,           // (P_OBJ_COMPARE)SrcDiff_Compare,
        NULL,           // (P_OBJ_PTR)SrcDiff_Copy,
        NULL,           // (P_OBJ_PTR)SrcDiff_DeepCopy,
        NULL            // (P_OBJ_HASH)SrcDiff_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SrcDiff_IsEnabled,
 
};



static
const
OBJ_INFO        SrcDiff_Info = {
    "SrcDiff",
    "Source Difference Finder",
    (OBJ_DATA *)&SrcDiff_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&SrcDiff_Vtbl,
    sizeof(SRCDIFF_DATA)
};





