// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Uri'
//  Generated 10/13/2020 10:59:50


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




#define         URI_OBJECT_C       1
#include        <Uri_internal.h>
#ifdef  URI_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Uri_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  URI_SINGLETON
    volatile
    URI_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          UriClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Uri_Info;            // Forward Reference




static
bool            UriClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_URI_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Uri_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        UriClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_URI_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
URI_CLASS_VTBL    class_Vtbl = {
    {
        &Uri_Info,
        UriClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Uri_Class,
        UriClass_WhoAmI,
        (P_OBJ_QUERYINFO)UriClass_QueryInfo,
        NULL                        // UriClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

URI_CLASS_DATA  Uri_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(URI_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  URI_SINGLETON
extern
const
URI_VTBL       Uri_VtblShared;


URI_DATA *     Uri_getSingleton (
    void
)
{
    return (OBJ_ID)(Uri_ClassObj.pSingleton);
}


bool            Uri_setSingleton (
    URI_DATA       *pValue
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
    if (Uri_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Uri_ClassObj.pSingleton));
    }
    Uri_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



URI_DATA *     Uri_Shared (
    void
)
{
    URI_DATA       *this = (OBJ_ID)(Uri_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Uri_New( );
        obj_setVtbl(this, (void *)&Uri_VtblShared);
        Uri_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Uri_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Uri_SharedReset (
    void
)
{
    URI_DATA       *this = (OBJ_ID)(Uri_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Uri_Vtbl);
        obj_Release(this);
        Uri_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          UriClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    URI_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(URI_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Uri_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Uri_Info.pClassSuperObject;
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
                        return Uri_New;
                    }
                    break;
                    
                case 'P':
#ifdef  URI_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Uri_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Uri_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  URI_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Uri_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Uri_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return UriClass_WhoAmI;
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
bool            Uri_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_URI == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Uri_Class())->pClassSuperObject;
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
void            Uri_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Uri_Class (
    void
)
{
    return (OBJ_ID)&Uri_ClassObj;
}


static
uint16_t        Uri_WhoAmI (
    void
)
{
    return OBJ_IDENT_URI;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  URI_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
URI_VTBL     Uri_VtblShared = {
    {
        &Uri_Info,
        Uri_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Uri_Dealloc,
        Uri_Class,
        Uri_WhoAmI,
        (P_OBJ_QUERYINFO)Uri_QueryInfo,
        (P_OBJ_TOSTRING)Uri_ToDebugString,
        NULL,           // Uri_Enable,
        NULL,           // Uri_Disable,
        NULL,           // (P_OBJ_ASSIGN)Uri_Assign,
        NULL,           // (P_OBJ_COMPARE)Uri_Compare,
        NULL,           // (P_OBJ_PTR)Uri_Copy,
        NULL,           // (P_OBJ_PTR)Uri_DeepCopy,
        NULL            // (P_OBJ_HASH)Uri_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Uri_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
URI_VTBL     Uri_Vtbl = {
    {
        &Uri_Info,
        Uri_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Uri_Dealloc,
        Uri_Class,
        Uri_WhoAmI,
        (P_OBJ_QUERYINFO)Uri_QueryInfo,
        (P_OBJ_TOSTRING)Uri_ToDebugString,
        NULL,           // Uri_Enable,
        NULL,           // Uri_Disable,
        NULL,           // (P_OBJ_ASSIGN)Uri_Assign,
        NULL,           // (P_OBJ_COMPARE)Uri_Compare,
        NULL,           // (P_OBJ_PTR)Uri_Copy,
        NULL,           // (P_OBJ_PTR)Uri_DeepCopy,
        NULL            // (P_OBJ_HASH)Uri_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Uri_IsEnabled,
 
};



static
const
OBJ_INFO        Uri_Info = {
    "Uri",
    "Uri - Uniform Resource Identifier - RFC 3986",
    (OBJ_DATA *)&Uri_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Uri_Vtbl,
    sizeof(URI_DATA)
};





