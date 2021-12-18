// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'SrcFiles'
//  Generated 10/19/2020 16:14:31


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




#define         SRCFILES_OBJECT_C       1
#include        <SrcFiles_internal.h>
#ifdef  SRCFILES_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SrcFiles_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SRCFILES_SINGLETON
    volatile
    SRCFILES_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SrcFilesClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SrcFiles_Info;            // Forward Reference




static
bool            SrcFilesClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SRCFILES_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SrcFiles_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        SrcFilesClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCFILES_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SRCFILES_CLASS_VTBL    class_Vtbl = {
    {
        &SrcFiles_Info,
        SrcFilesClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SrcFiles_Class,
        SrcFilesClass_WhoAmI,
        (P_OBJ_QUERYINFO)SrcFilesClass_QueryInfo,
        NULL                        // SrcFilesClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

SRCFILES_CLASS_DATA  SrcFiles_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SRCFILES_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SRCFILES_SINGLETON
extern
const
SRCFILES_VTBL       SrcFiles_VtblShared;


SRCFILES_DATA *     SrcFiles_getSingleton (
    void
)
{
    return (OBJ_ID)(SrcFiles_ClassObj.pSingleton);
}


bool            SrcFiles_setSingleton (
    SRCFILES_DATA       *pValue
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
    if (SrcFiles_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SrcFiles_ClassObj.pSingleton));
    }
    SrcFiles_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SRCFILES_DATA *     SrcFiles_Shared (
    void
)
{
    SRCFILES_DATA       *this = (OBJ_ID)(SrcFiles_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SrcFiles_New( );
        obj_setVtbl(this, (void *)&SrcFiles_VtblShared);
        SrcFiles_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SrcFiles_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SrcFiles_SharedReset (
    void
)
{
    SRCFILES_DATA       *this = (OBJ_ID)(SrcFiles_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SrcFiles_Vtbl);
        obj_Release(this);
        SrcFiles_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SrcFilesClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SRCFILES_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCFILES_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&SrcFiles_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&SrcFiles_Info.pClassSuperObject;
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
                        return SrcFiles_New;
                    }
                    break;
                    
                case 'P':
#ifdef  SRCFILES_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return SrcFiles_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return SrcFiles_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  SRCFILES_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return SrcFiles_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return SrcFiles_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SrcFilesClass_WhoAmI;
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
bool            SrcFiles_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SRCFILES == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SrcFiles_Class())->pClassSuperObject;
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
void            SrcFiles_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SrcFiles_Class (
    void
)
{
    return (OBJ_ID)&SrcFiles_ClassObj;
}


static
uint16_t        SrcFiles_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCFILES;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SRCFILES_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SRCFILES_VTBL     SrcFiles_VtblShared = {
    {
        &SrcFiles_Info,
        SrcFiles_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SrcFiles_Dealloc,
        SrcFiles_Class,
        SrcFiles_WhoAmI,
        (P_OBJ_QUERYINFO)SrcFiles_QueryInfo,
        (P_OBJ_TOSTRING)SrcFiles_ToDebugString,
        NULL,           // SrcFiles_Enable,
        NULL,           // SrcFiles_Disable,
        NULL,           // (P_OBJ_ASSIGN)SrcFiles_Assign,
        NULL,           // (P_OBJ_COMPARE)SrcFiles_Compare,
        NULL,           // (P_OBJ_PTR)SrcFiles_Copy,
        NULL,           // (P_OBJ_PTR)SrcFiles_DeepCopy,
        NULL            // (P_OBJ_HASH)SrcFiles_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SrcFiles_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SRCFILES_VTBL     SrcFiles_Vtbl = {
    {
        &SrcFiles_Info,
        SrcFiles_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SrcFiles_Dealloc,
        SrcFiles_Class,
        SrcFiles_WhoAmI,
        (P_OBJ_QUERYINFO)SrcFiles_QueryInfo,
        (P_OBJ_TOSTRING)SrcFiles_ToDebugString,
        NULL,           // SrcFiles_Enable,
        NULL,           // SrcFiles_Disable,
        NULL,           // (P_OBJ_ASSIGN)SrcFiles_Assign,
        NULL,           // (P_OBJ_COMPARE)SrcFiles_Compare,
        NULL,           // (P_OBJ_PTR)SrcFiles_Copy,
        NULL,           // (P_OBJ_PTR)SrcFiles_DeepCopy,
        NULL            // (P_OBJ_HASH)SrcFiles_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    /* The following must conform to the laInterface.
     */
    (void *)SrcFiles_InputAdvance2,
    (void *)SrcFiles_InputLookAhead2,
    (void *)SrcFiles_getQueueSize,

};



static
const
OBJ_INFO        SrcFiles_Info = {
    "SrcFiles",
    "Tokenize a TextIn Streams (SrcFiles) Header",
    (OBJ_DATA *)&SrcFiles_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&SrcFiles_Vtbl,
    sizeof(SRCFILES_DATA)
};


