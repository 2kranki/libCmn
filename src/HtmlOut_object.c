// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'HtmlOut'
//  Generated 03/30/2021 20:24:21


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




#define         HTMLOUT_OBJECT_C       1
#include        <HtmlOut_internal.h>
#ifdef  HTMLOUT_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct HtmlOut_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  HTMLOUT_SINGLETON
    volatile
    HTMLOUT_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          HtmlOutClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        HtmlOut_Info;            // Forward Reference




static
bool            HtmlOutClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_HTMLOUT_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(HtmlOut_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        HtmlOutClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_HTMLOUT_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
HTMLOUT_CLASS_VTBL    class_Vtbl = {
    {
        &HtmlOut_Info,
        HtmlOutClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        HtmlOut_Class,
        HtmlOutClass_WhoAmI,
        (P_OBJ_QUERYINFO)HtmlOutClass_QueryInfo,
        NULL                        // HtmlOutClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

HTMLOUT_CLASS_DATA  HtmlOut_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(HTMLOUT_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  HTMLOUT_SINGLETON
extern
const
HTMLOUT_VTBL       HtmlOut_VtblShared;


HTMLOUT_DATA *     HtmlOut_getSingleton (
    void
)
{
    return (OBJ_ID)(HtmlOut_ClassObj.pSingleton);
}


bool            HtmlOut_setSingleton (
    HTMLOUT_DATA       *pValue
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
    if (HtmlOut_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(HtmlOut_ClassObj.pSingleton));
    }
    HtmlOut_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



HTMLOUT_DATA *     HtmlOut_Shared (
    void
)
{
    HTMLOUT_DATA       *this = (OBJ_ID)(HtmlOut_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = HtmlOut_New( );
        obj_setVtbl(this, (void *)&HtmlOut_VtblShared);
        HtmlOut_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // HtmlOut_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            HtmlOut_SharedReset (
    void
)
{
    HTMLOUT_DATA       *this = (OBJ_ID)(HtmlOut_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&HtmlOut_Vtbl);
        obj_Release(this);
        HtmlOut_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          HtmlOutClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    HTMLOUT_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(HTMLOUT_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&HtmlOut_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&HtmlOut_Info.pClassSuperObject;
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
                        return HtmlOut_New;
                    }
                    break;
                    
                case 'P':
#ifdef  HTMLOUT_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return HtmlOut_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return HtmlOut_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  HTMLOUT_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return HtmlOut_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return HtmlOut_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return HtmlOutClass_WhoAmI;
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
bool            HtmlOut_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_HTMLOUT == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(HtmlOut_Class())->pClassSuperObject;
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
void            HtmlOut_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          HtmlOut_Class (
    void
)
{
    return (OBJ_ID)&HtmlOut_ClassObj;
}


static
uint16_t        HtmlOut_WhoAmI (
    void
)
{
    return OBJ_IDENT_HTMLOUT;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  HTMLOUT_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
HTMLOUT_VTBL     HtmlOut_VtblShared = {
    {
        &HtmlOut_Info,
        HtmlOut_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        HtmlOut_Dealloc,
        HtmlOut_Class,
        HtmlOut_WhoAmI,
        (P_OBJ_QUERYINFO)HtmlOut_QueryInfo,
        (P_OBJ_TOSTRING)HtmlOut_ToDebugString,
        NULL,           // HtmlOut_Enable,
        NULL,           // HtmlOut_Disable,
        NULL,           // (P_OBJ_ASSIGN)HtmlOut_Assign,
        NULL,           // (P_OBJ_COMPARE)HtmlOut_Compare,
        NULL,           // (P_OBJ_PTR)HtmlOut_Copy,
        NULL,           // (P_OBJ_PTR)HtmlOut_DeepCopy,
        NULL            // (P_OBJ_HASH)HtmlOut_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //HtmlOut_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
HTMLOUT_VTBL     HtmlOut_Vtbl = {
    {
        &HtmlOut_Info,
        HtmlOut_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        HtmlOut_Dealloc,
        HtmlOut_Class,
        HtmlOut_WhoAmI,
        (P_OBJ_QUERYINFO)HtmlOut_QueryInfo,
        (P_OBJ_TOSTRING)HtmlOut_ToDebugString,
        NULL,           // HtmlOut_Enable,
        NULL,           // HtmlOut_Disable,
        NULL,           // (P_OBJ_ASSIGN)HtmlOut_Assign,
        NULL,           // (P_OBJ_COMPARE)HtmlOut_Compare,
        NULL,           // (P_OBJ_PTR)HtmlOut_Copy,
        NULL,           // (P_OBJ_PTR)HtmlOut_DeepCopy,
        NULL            // (P_OBJ_HASH)HtmlOut_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //HtmlOut_IsEnabled,
 
};



static
const
OBJ_INFO        HtmlOut_Info = {
    "HtmlOut",
    "HTML Output Helper",
    (OBJ_DATA *)&HtmlOut_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&HtmlOut_Vtbl,
    sizeof(HTMLOUT_DATA)
};





