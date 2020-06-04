// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Lex06'
//  Generated 05/30/2020 14:53:10


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




#define         LEX06_OBJECT_C       1
#include        <Lex06_internal.h>
#ifdef  LEX06_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Lex06_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LEX06_SINGLETON
    volatile
    LEX06_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Lex06Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Lex06_Info;            // Forward Reference




static
bool            Lex06Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LEX06_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Lex06_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        Lex06Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEX06_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LEX06_CLASS_VTBL    class_Vtbl = {
    {
        &Lex06_Info,
        Lex06Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Lex06_Class,
        Lex06Class_WhoAmI,
        (P_OBJ_QUERYINFO)Lex06Class_QueryInfo,
        NULL                        // Lex06Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LEX06_CLASS_DATA  Lex06_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LEX06_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LEX06_SINGLETON
extern
const
LEX06_VTBL       Lex06_VtblShared;


LEX06_DATA *     Lex06_getSingleton (
    void
)
{
    return (OBJ_ID)(Lex06_ClassObj.pSingleton);
}


bool            Lex06_setSingleton (
    LEX06_DATA       *pValue
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
    if (Lex06_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Lex06_ClassObj.pSingleton));
    }
    Lex06_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LEX06_DATA *     Lex06_Shared (
    void
)
{
    LEX06_DATA       *this = (OBJ_ID)(Lex06_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Lex06_New( );
        obj_setVtbl(this, (void *)&Lex06_VtblShared);
        Lex06_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Lex06_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Lex06_SharedReset (
    void
)
{
    LEX06_DATA       *this = (OBJ_ID)(Lex06_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Lex06_Vtbl);
        obj_Release(this);
        Lex06_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Lex06Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LEX06_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LEX06_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Lex06_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Lex06_Info.pClassSuperObject;
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
                        return Lex06_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LEX06_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Lex06_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Lex06_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LEX06_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Lex06_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Lex06_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return Lex06Class_WhoAmI;
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
bool            Lex06_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LEX06 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Lex06_Class())->pClassSuperObject;
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
void            Lex06_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Lex06_Class (
    void
)
{
    return (OBJ_ID)&Lex06_ClassObj;
}


static
uint16_t        Lex06_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEX06;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LEX06_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LEX06_VTBL     Lex06_VtblShared = {
    {
        &Lex06_Info,
        Lex06_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Lex06_Dealloc,
        Lex06_Class,
        Lex06_WhoAmI,
        (P_OBJ_QUERYINFO)Lex06_QueryInfo,
        (P_OBJ_TOSTRING)Lex06_ToDebugString,
        NULL,           // Lex06_Enable,
        NULL,           // Lex06_Disable,
        NULL,           // (P_OBJ_ASSIGN)Lex06_Assign,
        NULL,           // (P_OBJ_COMPARE)Lex06_Compare,
        NULL,           // (P_OBJ_PTR)Lex06_Copy,
        NULL,           // (P_OBJ_PTR)Lex06_DeepCopy,
        NULL            // (P_OBJ_HASH)Lex06_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Lex06_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LEX06_VTBL     Lex06_Vtbl = {
    {
        &Lex06_Info,
        Lex06_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Lex06_Dealloc,
        Lex06_Class,
        Lex06_WhoAmI,
        (P_OBJ_QUERYINFO)Lex06_QueryInfo,
        (P_OBJ_TOSTRING)Lex06_ToDebugString,
        NULL,           // Lex06_Enable,
        NULL,           // Lex06_Disable,
        NULL,           // (P_OBJ_ASSIGN)Lex06_Assign,
        NULL,           // (P_OBJ_COMPARE)Lex06_Compare,
        NULL,           // (P_OBJ_PTR)Lex06_Copy,
        NULL,           // (P_OBJ_PTR)Lex06_DeepCopy,
        NULL            // (P_OBJ_HASH)Lex06_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Lex06_IsEnabled,
 
};



static
const
OBJ_INFO        Lex06_Info = {
    "Lex06",
    "Lex06",
    (OBJ_DATA *)&Lex06_ClassObj,
    (OBJ_DATA *)&Lex_ClassObj,
    (OBJ_IUNKNOWN *)&Lex06_Vtbl,
    sizeof(LEX06_DATA)
};





