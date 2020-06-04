// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Lex00'
//  Generated 05/30/2020 14:51:43


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




#define         LEX00_OBJECT_C       1
#include        <Lex00_internal.h>
#ifdef  LEX00_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Lex00_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LEX00_SINGLETON
    volatile
    LEX00_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Lex00Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Lex00_Info;            // Forward Reference




static
bool            Lex00Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LEX00_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Lex00_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        Lex00Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEX00_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LEX00_CLASS_VTBL    class_Vtbl = {
    {
        &Lex00_Info,
        Lex00Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Lex00_Class,
        Lex00Class_WhoAmI,
        (P_OBJ_QUERYINFO)Lex00Class_QueryInfo,
        NULL                        // Lex00Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LEX00_CLASS_DATA  Lex00_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LEX00_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LEX00_SINGLETON
extern
const
LEX00_VTBL       Lex00_VtblShared;


LEX00_DATA *     Lex00_getSingleton (
    void
)
{
    return (OBJ_ID)(Lex00_ClassObj.pSingleton);
}


bool            Lex00_setSingleton (
    LEX00_DATA       *pValue
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
    if (Lex00_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Lex00_ClassObj.pSingleton));
    }
    Lex00_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LEX00_DATA *     Lex00_Shared (
    void
)
{
    LEX00_DATA       *this = (OBJ_ID)(Lex00_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Lex00_New( );
        obj_setVtbl(this, (void *)&Lex00_VtblShared);
        Lex00_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Lex00_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Lex00_SharedReset (
    void
)
{
    LEX00_DATA       *this = (OBJ_ID)(Lex00_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Lex00_Vtbl);
        obj_Release(this);
        Lex00_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Lex00Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LEX00_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LEX00_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Lex00_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Lex00_Info.pClassSuperObject;
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
                        return Lex00_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LEX00_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Lex00_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Lex00_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LEX00_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Lex00_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Lex00_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return Lex00Class_WhoAmI;
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
bool            Lex00_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LEX00 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Lex00_Class())->pClassSuperObject;
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
void            Lex00_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Lex00_Class (
    void
)
{
    return (OBJ_ID)&Lex00_ClassObj;
}


static
uint16_t        Lex00_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEX00;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LEX00_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LEX00_VTBL     Lex00_VtblShared = {
    {
        &Lex00_Info,
        Lex00_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Lex00_Dealloc,
        Lex00_Class,
        Lex00_WhoAmI,
        (P_OBJ_QUERYINFO)Lex00_QueryInfo,
        (P_OBJ_TOSTRING)Lex00_ToDebugString,
        NULL,           // Lex00_Enable,
        NULL,           // Lex00_Disable,
        NULL,           // (P_OBJ_ASSIGN)Lex00_Assign,
        NULL,           // (P_OBJ_COMPARE)Lex00_Compare,
        NULL,           // (P_OBJ_PTR)Lex00_Copy,
        NULL,           // (P_OBJ_PTR)Lex00_DeepCopy,
        NULL            // (P_OBJ_HASH)Lex00_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Lex00_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LEX00_VTBL     Lex00_Vtbl = {
    {
        &Lex00_Info,
        Lex00_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Lex00_Dealloc,
        Lex00_Class,
        Lex00_WhoAmI,
        (P_OBJ_QUERYINFO)Lex00_QueryInfo,
        (P_OBJ_TOSTRING)Lex00_ToDebugString,
        NULL,           // Lex00_Enable,
        NULL,           // Lex00_Disable,
        NULL,           // (P_OBJ_ASSIGN)Lex00_Assign,
        NULL,           // (P_OBJ_COMPARE)Lex00_Compare,
        NULL,           // (P_OBJ_PTR)Lex00_Copy,
        NULL,           // (P_OBJ_PTR)Lex00_DeepCopy,
        NULL            // (P_OBJ_HASH)Lex00_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Lex00_IsEnabled,
 
};



static
const
OBJ_INFO        Lex00_Info = {
    "Lex00",
    "Lex00",
    (OBJ_DATA *)&Lex00_ClassObj,
    (OBJ_DATA *)&Lex_ClassObj,
    (OBJ_IUNKNOWN *)&Lex00_Vtbl,
    sizeof(LEX00_DATA)
};





