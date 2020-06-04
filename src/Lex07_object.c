// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Lex07'
//  Generated 05/30/2020 14:53:23


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




#define         LEX07_OBJECT_C       1
#include        <Lex07_internal.h>
#ifdef  LEX07_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Lex07_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LEX07_SINGLETON
    volatile
    LEX07_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Lex07Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Lex07_Info;            // Forward Reference




static
bool            Lex07Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LEX07_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Lex07_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        Lex07Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEX07_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LEX07_CLASS_VTBL    class_Vtbl = {
    {
        &Lex07_Info,
        Lex07Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Lex07_Class,
        Lex07Class_WhoAmI,
        (P_OBJ_QUERYINFO)Lex07Class_QueryInfo,
        NULL                        // Lex07Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LEX07_CLASS_DATA  Lex07_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LEX07_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LEX07_SINGLETON
extern
const
LEX07_VTBL       Lex07_VtblShared;


LEX07_DATA *     Lex07_getSingleton (
    void
)
{
    return (OBJ_ID)(Lex07_ClassObj.pSingleton);
}


bool            Lex07_setSingleton (
    LEX07_DATA       *pValue
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
    if (Lex07_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Lex07_ClassObj.pSingleton));
    }
    Lex07_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LEX07_DATA *     Lex07_Shared (
    void
)
{
    LEX07_DATA       *this = (OBJ_ID)(Lex07_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Lex07_New( );
        obj_setVtbl(this, (void *)&Lex07_VtblShared);
        Lex07_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Lex07_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Lex07_SharedReset (
    void
)
{
    LEX07_DATA       *this = (OBJ_ID)(Lex07_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Lex07_Vtbl);
        obj_Release(this);
        Lex07_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Lex07Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LEX07_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LEX07_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Lex07_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Lex07_Info.pClassSuperObject;
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
                        return Lex07_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LEX07_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Lex07_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Lex07_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LEX07_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Lex07_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Lex07_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return Lex07Class_WhoAmI;
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
bool            Lex07_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LEX07 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Lex07_Class())->pClassSuperObject;
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
void            Lex07_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Lex07_Class (
    void
)
{
    return (OBJ_ID)&Lex07_ClassObj;
}


static
uint16_t        Lex07_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEX07;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LEX07_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LEX07_VTBL     Lex07_VtblShared = {
    {
        &Lex07_Info,
        Lex07_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Lex07_Dealloc,
        Lex07_Class,
        Lex07_WhoAmI,
        (P_OBJ_QUERYINFO)Lex07_QueryInfo,
        (P_OBJ_TOSTRING)Lex07_ToDebugString,
        NULL,           // Lex07_Enable,
        NULL,           // Lex07_Disable,
        NULL,           // (P_OBJ_ASSIGN)Lex07_Assign,
        NULL,           // (P_OBJ_COMPARE)Lex07_Compare,
        NULL,           // (P_OBJ_PTR)Lex07_Copy,
        NULL,           // (P_OBJ_PTR)Lex07_DeepCopy,
        NULL            // (P_OBJ_HASH)Lex07_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Lex07_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LEX07_VTBL     Lex07_Vtbl = {
    {
        &Lex07_Info,
        Lex07_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Lex07_Dealloc,
        Lex07_Class,
        Lex07_WhoAmI,
        (P_OBJ_QUERYINFO)Lex07_QueryInfo,
        (P_OBJ_TOSTRING)Lex07_ToDebugString,
        NULL,           // Lex07_Enable,
        NULL,           // Lex07_Disable,
        NULL,           // (P_OBJ_ASSIGN)Lex07_Assign,
        NULL,           // (P_OBJ_COMPARE)Lex07_Compare,
        NULL,           // (P_OBJ_PTR)Lex07_Copy,
        NULL,           // (P_OBJ_PTR)Lex07_DeepCopy,
        NULL            // (P_OBJ_HASH)Lex07_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Lex07_IsEnabled,
 
};



static
const
OBJ_INFO        Lex07_Info = {
    "Lex07",
    "Lex07",
    (OBJ_DATA *)&Lex07_ClassObj,
    (OBJ_DATA *)&Lex_ClassObj,
    (OBJ_IUNKNOWN *)&Lex07_Vtbl,
    sizeof(LEX07_DATA)
};





