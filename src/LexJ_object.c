// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'LexJ'
//  Generated 12/09/2020 23:26:59


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




#define         LEXJ_OBJECT_C       1
#include        <LexJ_internal.h>
#ifdef  LEXJ_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct LexJ_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LEXJ_SINGLETON
    volatile
    LEXJ_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          LexJClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        LexJ_Info;            // Forward Reference




static
bool            LexJClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LEXJ_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(LexJ_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        LexJClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEXJ_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LEXJ_CLASS_VTBL    class_Vtbl = {
    {
        &LexJ_Info,
        LexJClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        LexJ_Class,
        LexJClass_WhoAmI,
        (P_OBJ_QUERYINFO)LexJClass_QueryInfo,
        NULL                        // LexJClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LEXJ_CLASS_DATA  LexJ_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LEXJ_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LEXJ_SINGLETON
extern
const
LEXJ_VTBL       LexJ_VtblShared;


LEXJ_DATA *     LexJ_getSingleton (
    void
)
{
    return (OBJ_ID)(LexJ_ClassObj.pSingleton);
}


bool            LexJ_setSingleton (
    LEXJ_DATA       *pValue
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
    if (LexJ_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(LexJ_ClassObj.pSingleton));
    }
    LexJ_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LEXJ_DATA *     LexJ_Shared (
    void
)
{
    LEXJ_DATA       *this = (OBJ_ID)(LexJ_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = LexJ_New( );
        obj_setVtbl(this, (void *)&LexJ_VtblShared);
        LexJ_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // LexJ_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            LexJ_SharedReset (
    void
)
{
    LEXJ_DATA       *this = (OBJ_ID)(LexJ_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&LexJ_Vtbl);
        obj_Release(this);
        LexJ_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          LexJClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LEXJ_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LEXJ_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&LexJ_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&LexJ_Info.pClassSuperObject;
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
                        return LexJ_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LEXJ_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return LexJ_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return LexJ_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LEXJ_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return LexJ_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return LexJ_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return LexJClass_WhoAmI;
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
bool            LexJ_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LEXJ == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(LexJ_Class())->pClassSuperObject;
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
void            LexJ_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          LexJ_Class (
    void
)
{
    return (OBJ_ID)&LexJ_ClassObj;
}


static
uint16_t        LexJ_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEXJ;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LEXJ_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LEXJ_VTBL     LexJ_VtblShared = {
    {
        &LexJ_Info,
        LexJ_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        LexJ_Dealloc,
        LexJ_Class,
        LexJ_WhoAmI,
        (P_OBJ_QUERYINFO)LexJ_QueryInfo,
        (P_OBJ_TOSTRING)LexJ_ToDebugString,
        NULL,           // LexJ_Enable,
        NULL,           // LexJ_Disable,
        NULL,           // (P_OBJ_ASSIGN)LexJ_Assign,
        NULL,           // (P_OBJ_COMPARE)LexJ_Compare,
        NULL,           // (P_OBJ_PTR)LexJ_Copy,
        NULL,           // (P_OBJ_PTR)LexJ_DeepCopy,
        NULL            // (P_OBJ_HASH)LexJ_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //LexJ_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LEXJ_VTBL     LexJ_Vtbl = {
    {
        &LexJ_Info,
        LexJ_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        LexJ_Dealloc,
        LexJ_Class,
        LexJ_WhoAmI,
        (P_OBJ_QUERYINFO)LexJ_QueryInfo,
        (P_OBJ_TOSTRING)LexJ_ToDebugString,
        NULL,           // LexJ_Enable,
        NULL,           // LexJ_Disable,
        NULL,           // (P_OBJ_ASSIGN)LexJ_Assign,
        NULL,           // (P_OBJ_COMPARE)LexJ_Compare,
        NULL,           // (P_OBJ_PTR)LexJ_Copy,
        NULL,           // (P_OBJ_PTR)LexJ_DeepCopy,
        NULL            // (P_OBJ_HASH)LexJ_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    /* The following must conform to the laInterface.
     */
    (void *)Lex_TokenAdvance2,
    (void *)Lex_TokenLookAhead2,
    (void *)Lex_getSize

};



static
const
OBJ_INFO        LexJ_Info = {
    "LexJ",
    "HJSON Lexical Analyzer",
    (OBJ_DATA *)&LexJ_ClassObj,
    (OBJ_DATA *)&Lex_ClassObj,
    (OBJ_IUNKNOWN *)&LexJ_Vtbl,
    sizeof(LEXJ_DATA)
};





