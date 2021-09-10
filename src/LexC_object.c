// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'LexC'
//  Generated 09/02/2021 08:48:25


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




#define         LEXC_OBJECT_C       1
#include        <LexC_internal.h>
#ifdef  LEXC_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct LexC_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LEXC_SINGLETON
    volatile
    LEXC_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          LexCClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        LexC_Info;            // Forward Reference




static
bool            LexCClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LEXC_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(LexC_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        LexCClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEXC_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LEXC_CLASS_VTBL    class_Vtbl = {
    {
        &LexC_Info,
        LexCClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        LexC_Class,
        LexCClass_WhoAmI,
        (P_OBJ_QUERYINFO)LexCClass_QueryInfo,
        NULL                        // LexCClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LEXC_CLASS_DATA  LexC_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LEXC_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LEXC_SINGLETON
extern
const
LEXC_VTBL       LexC_VtblShared;


LEXC_DATA *     LexC_getSingleton (
    void
)
{
    return (OBJ_ID)(LexC_ClassObj.pSingleton);
}


bool            LexC_setSingleton (
    LEXC_DATA       *pValue
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
    if (LexC_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(LexC_ClassObj.pSingleton));
    }
    LexC_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LEXC_DATA *     LexC_Shared (
    void
)
{
    LEXC_DATA       *this = (OBJ_ID)(LexC_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = LexC_New( );
        obj_setVtbl(this, (void *)&LexC_VtblShared);
        LexC_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // LexC_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            LexC_SharedReset (
    void
)
{
    LEXC_DATA       *this = (OBJ_ID)(LexC_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&LexC_Vtbl);
        obj_Release(this);
        LexC_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          LexCClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LEXC_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LEXC_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&LexC_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&LexC_Info.pClassSuperObject;
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
                        return LexC_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LEXC_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return LexC_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return LexC_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LEXC_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return LexC_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return LexC_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return LexCClass_WhoAmI;
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
bool            LexC_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LEXC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(LexC_Class())->pClassSuperObject;
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
void            LexC_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          LexC_Class (
    void
)
{
    return (OBJ_ID)&LexC_ClassObj;
}


static
uint16_t        LexC_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEXC;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LEXC_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LEXC_VTBL     LexC_VtblShared = {
    {
        &LexC_Info,
        LexC_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        LexC_Dealloc,
        LexC_Class,
        LexC_WhoAmI,
        (P_OBJ_QUERYINFO)LexC_QueryInfo,
        (P_OBJ_TOSTRING)LexC_ToDebugString,
        NULL,           // LexC_Enable,
        NULL,           // LexC_Disable,
        NULL,           // (P_OBJ_ASSIGN)LexC_Assign,
        NULL,           // (P_OBJ_COMPARE)LexC_Compare,
        NULL,           // (P_OBJ_PTR)LexC_Copy,
        NULL,           // (P_OBJ_PTR)LexC_DeepCopy,
        NULL            // (P_OBJ_HASH)LexC_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //LexC_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LEXC_VTBL     LexC_Vtbl = {
    {
        &LexC_Info,
        LexC_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        LexC_Dealloc,
        LexC_Class,
        LexC_WhoAmI,
        (P_OBJ_QUERYINFO)LexC_QueryInfo,
        (P_OBJ_TOSTRING)LexC_ToDebugString,
        NULL,           // LexC_Enable,
        NULL,           // LexC_Disable,
        NULL,           // (P_OBJ_ASSIGN)LexC_Assign,
        NULL,           // (P_OBJ_COMPARE)LexC_Compare,
        NULL,           // (P_OBJ_PTR)LexC_Copy,
        NULL,           // (P_OBJ_PTR)LexC_DeepCopy,
        NULL            // (P_OBJ_HASH)LexC_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //LexC_IsEnabled,
 
};



static
const
OBJ_INFO        LexC_Info = {
    "LexC",
    "C Lexical Scanner",
    (OBJ_DATA *)&LexC_ClassObj,
    (OBJ_DATA *)&Lex_ClassObj,
    (OBJ_IUNKNOWN *)&LexC_Vtbl,
    sizeof(LEXC_DATA)
};





