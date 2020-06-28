// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Lex03'
//  Generated 05/30/2020 14:52:23


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




#define         LEX03_OBJECT_C       1
#include        <Lex03_internal.h>
#ifdef  LEX03_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Lex03_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LEX03_SINGLETON
    volatile
    LEX03_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Lex03Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Lex03_Info;            // Forward Reference




static
bool            Lex03Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LEX03_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Lex03_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        Lex03Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEX03_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LEX03_CLASS_VTBL    class_Vtbl = {
    {
        &Lex03_Info,
        Lex03Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Lex03_Class,
        Lex03Class_WhoAmI,
        (P_OBJ_QUERYINFO)Lex03Class_QueryInfo,
        NULL                        // Lex03Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LEX03_CLASS_DATA  Lex03_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LEX03_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LEX03_SINGLETON
extern
const
LEX03_VTBL       Lex03_VtblShared;


LEX03_DATA *     Lex03_getSingleton (
    void
)
{
    return (OBJ_ID)(Lex03_ClassObj.pSingleton);
}


bool            Lex03_setSingleton (
    LEX03_DATA       *pValue
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
    if (Lex03_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Lex03_ClassObj.pSingleton));
    }
    Lex03_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LEX03_DATA *     Lex03_Shared (
    void
)
{
    LEX03_DATA       *this = (OBJ_ID)(Lex03_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Lex03_New( );
        obj_setVtbl(this, (void *)&Lex03_VtblShared);
        Lex03_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Lex03_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Lex03_SharedReset (
    void
)
{
    LEX03_DATA       *this = (OBJ_ID)(Lex03_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Lex03_Vtbl);
        obj_Release(this);
        Lex03_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Lex03Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LEX03_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LEX03_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Lex03_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Lex03_Info.pClassSuperObject;
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
                        return Lex03_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LEX03_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Lex03_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Lex03_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LEX03_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Lex03_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Lex03_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return Lex03Class_WhoAmI;
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
bool            Lex03_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LEX03 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Lex03_Class())->pClassSuperObject;
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
void            Lex03_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Lex03_Class (
    void
)
{
    return (OBJ_ID)&Lex03_ClassObj;
}


static
uint16_t        Lex03_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEX03;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LEX03_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LEX03_VTBL     Lex03_VtblShared = {
    {
        &Lex03_Info,
        Lex03_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Lex03_Dealloc,
        Lex03_Class,
        Lex03_WhoAmI,
        (P_OBJ_QUERYINFO)Lex03_QueryInfo,
        (P_OBJ_TOSTRING)Lex03_ToDebugString,
        NULL,           // Lex03_Enable,
        NULL,           // Lex03_Disable,
        NULL,           // (P_OBJ_ASSIGN)Lex03_Assign,
        NULL,           // (P_OBJ_COMPARE)Lex03_Compare,
        NULL,           // (P_OBJ_PTR)Lex03_Copy,
        NULL,           // (P_OBJ_PTR)Lex03_DeepCopy,
        NULL            // (P_OBJ_HASH)Lex03_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Lex03_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LEX03_VTBL     Lex03_Vtbl = {
    {
        &Lex03_Info,
        Lex03_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Lex03_Dealloc,
        Lex03_Class,
        Lex03_WhoAmI,
        (P_OBJ_QUERYINFO)Lex03_QueryInfo,
        (P_OBJ_TOSTRING)Lex03_ToDebugString,
        NULL,           // Lex03_Enable,
        NULL,           // Lex03_Disable,
        NULL,           // (P_OBJ_ASSIGN)Lex03_Assign,
        NULL,           // (P_OBJ_COMPARE)Lex03_Compare,
        NULL,           // (P_OBJ_PTR)Lex03_Copy,
        NULL,           // (P_OBJ_PTR)Lex03_DeepCopy,
        NULL            // (P_OBJ_HASH)Lex03_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Lex03_IsEnabled,
 
};



static
const
OBJ_INFO        Lex03_Info = {
    "Lex03",
    "JSON Lexical Scanner",
    (OBJ_DATA *)&Lex03_ClassObj,
    (OBJ_DATA *)&Lex_ClassObj,
    (OBJ_IUNKNOWN *)&Lex03_Vtbl,
    sizeof(LEX03_DATA)
};





