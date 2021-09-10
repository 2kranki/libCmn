// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'LexTri'
//  Generated 09/02/2021 20:32:47


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




#define         LEXTRI_OBJECT_C       1
#include        <LexTri_internal.h>
#ifdef  LEXTRI_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct LexTri_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LEXTRI_SINGLETON
    volatile
    LEXTRI_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          LexTriClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        LexTri_Info;            // Forward Reference




static
bool            LexTriClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LEXTRI_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(LexTri_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        LexTriClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEXTRI_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LEXTRI_CLASS_VTBL    class_Vtbl = {
    {
        &LexTri_Info,
        LexTriClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        LexTri_Class,
        LexTriClass_WhoAmI,
        (P_OBJ_QUERYINFO)LexTriClass_QueryInfo,
        NULL                        // LexTriClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LEXTRI_CLASS_DATA  LexTri_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LEXTRI_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LEXTRI_SINGLETON
extern
const
LEXTRI_VTBL       LexTri_VtblShared;


LEXTRI_DATA *     LexTri_getSingleton (
    void
)
{
    return (OBJ_ID)(LexTri_ClassObj.pSingleton);
}


bool            LexTri_setSingleton (
    LEXTRI_DATA       *pValue
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
    if (LexTri_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(LexTri_ClassObj.pSingleton));
    }
    LexTri_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LEXTRI_DATA *     LexTri_Shared (
    void
)
{
    LEXTRI_DATA       *this = (OBJ_ID)(LexTri_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = LexTri_New( );
        obj_setVtbl(this, (void *)&LexTri_VtblShared);
        LexTri_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // LexTri_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            LexTri_SharedReset (
    void
)
{
    LEXTRI_DATA       *this = (OBJ_ID)(LexTri_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&LexTri_Vtbl);
        obj_Release(this);
        LexTri_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          LexTriClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LEXTRI_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LEXTRI_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&LexTri_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&LexTri_Info.pClassSuperObject;
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
                        return LexTri_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LEXTRI_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return LexTri_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return LexTri_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LEXTRI_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return LexTri_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return LexTri_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return LexTriClass_WhoAmI;
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
bool            LexTri_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LEXTRI == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(LexTri_Class())->pClassSuperObject;
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
void            LexTri_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          LexTri_Class (
    void
)
{
    return (OBJ_ID)&LexTri_ClassObj;
}


static
uint16_t        LexTri_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEXTRI;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LEXTRI_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LEXTRI_VTBL     LexTri_VtblShared = {
    {
        &LexTri_Info,
        LexTri_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        LexTri_Dealloc,
        LexTri_Class,
        LexTri_WhoAmI,
        (P_OBJ_QUERYINFO)LexTri_QueryInfo,
        (P_OBJ_TOSTRING)LexTri_ToDebugString,
        NULL,           // LexTri_Enable,
        NULL,           // LexTri_Disable,
        NULL,           // (P_OBJ_ASSIGN)LexTri_Assign,
        NULL,           // (P_OBJ_COMPARE)LexTri_Compare,
        NULL,           // (P_OBJ_PTR)LexTri_Copy,
        NULL,           // (P_OBJ_PTR)LexTri_DeepCopy,
        NULL            // (P_OBJ_HASH)LexTri_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //LexTri_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LEXTRI_VTBL     LexTri_Vtbl = {
    {
        &LexTri_Info,
        LexTri_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        LexTri_Dealloc,
        LexTri_Class,
        LexTri_WhoAmI,
        (P_OBJ_QUERYINFO)LexTri_QueryInfo,
        (P_OBJ_TOSTRING)LexTri_ToDebugString,
        NULL,           // LexTri_Enable,
        NULL,           // LexTri_Disable,
        NULL,           // (P_OBJ_ASSIGN)LexTri_Assign,
        NULL,           // (P_OBJ_COMPARE)LexTri_Compare,
        NULL,           // (P_OBJ_PTR)LexTri_Copy,
        NULL,           // (P_OBJ_PTR)LexTri_DeepCopy,
        NULL            // (P_OBJ_HASH)LexTri_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //LexTri_IsEnabled,
 
};



static
const
OBJ_INFO        LexTri_Info = {
    "LexTri",
    "C Trigraph Lexical Scanner",
    (OBJ_DATA *)&LexTri_ClassObj,
    (OBJ_DATA *)&Lex_ClassObj,
    (OBJ_IUNKNOWN *)&LexTri_Vtbl,
    sizeof(LEXTRI_DATA)
};





