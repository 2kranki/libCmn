// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Lex04'
//  Generated 05/30/2020 14:52:33


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




#define         LEX04_OBJECT_C       1
#include        <Lex04_internal.h>
#ifdef  LEX04_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Lex04_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LEX04_SINGLETON
    volatile
    LEX04_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Lex04Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Lex04_Info;            // Forward Reference




static
bool            Lex04Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LEX04_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Lex04_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        Lex04Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEX04_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LEX04_CLASS_VTBL    class_Vtbl = {
    {
        &Lex04_Info,
        Lex04Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Lex04_Class,
        Lex04Class_WhoAmI,
        (P_OBJ_QUERYINFO)Lex04Class_QueryInfo,
        NULL                        // Lex04Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LEX04_CLASS_DATA  Lex04_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LEX04_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LEX04_SINGLETON
extern
const
LEX04_VTBL       Lex04_VtblShared;


LEX04_DATA *     Lex04_getSingleton (
    void
)
{
    return (OBJ_ID)(Lex04_ClassObj.pSingleton);
}


bool            Lex04_setSingleton (
    LEX04_DATA       *pValue
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
    if (Lex04_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Lex04_ClassObj.pSingleton));
    }
    Lex04_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LEX04_DATA *     Lex04_Shared (
    void
)
{
    LEX04_DATA       *this = (OBJ_ID)(Lex04_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Lex04_New( );
        obj_setVtbl(this, (void *)&Lex04_VtblShared);
        Lex04_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Lex04_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Lex04_SharedReset (
    void
)
{
    LEX04_DATA       *this = (OBJ_ID)(Lex04_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Lex04_Vtbl);
        obj_Release(this);
        Lex04_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Lex04Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LEX04_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LEX04_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Lex04_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Lex04_Info.pClassSuperObject;
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
                        return Lex04_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LEX04_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Lex04_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Lex04_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LEX04_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Lex04_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Lex04_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return Lex04Class_WhoAmI;
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
bool            Lex04_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LEX04 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Lex04_Class())->pClassSuperObject;
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
void            Lex04_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Lex04_Class (
    void
)
{
    return (OBJ_ID)&Lex04_ClassObj;
}


static
uint16_t        Lex04_WhoAmI (
    void
)
{
    return OBJ_IDENT_LEX04;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LEX04_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LEX04_VTBL     Lex04_VtblShared = {
    {
        &Lex04_Info,
        Lex04_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Lex04_Dealloc,
        Lex04_Class,
        Lex04_WhoAmI,
        (P_OBJ_QUERYINFO)Lex04_QueryInfo,
        (P_OBJ_TOSTRING)Lex04_ToDebugString,
        NULL,           // Lex04_Enable,
        NULL,           // Lex04_Disable,
        NULL,           // (P_OBJ_ASSIGN)Lex04_Assign,
        NULL,           // (P_OBJ_COMPARE)Lex04_Compare,
        NULL,           // (P_OBJ_PTR)Lex04_Copy,
        NULL,           // (P_OBJ_PTR)Lex04_DeepCopy,
        NULL            // (P_OBJ_HASH)Lex04_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Lex04_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LEX04_VTBL     Lex04_Vtbl = {
    {
        &Lex04_Info,
        Lex04_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Lex04_Dealloc,
        Lex04_Class,
        Lex04_WhoAmI,
        (P_OBJ_QUERYINFO)Lex04_QueryInfo,
        (P_OBJ_TOSTRING)Lex04_ToDebugString,
        NULL,           // Lex04_Enable,
        NULL,           // Lex04_Disable,
        NULL,           // (P_OBJ_ASSIGN)Lex04_Assign,
        NULL,           // (P_OBJ_COMPARE)Lex04_Compare,
        NULL,           // (P_OBJ_PTR)Lex04_Copy,
        NULL,           // (P_OBJ_PTR)Lex04_DeepCopy,
        NULL            // (P_OBJ_HASH)Lex04_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Lex04_IsEnabled,
 
};



static
const
OBJ_INFO        Lex04_Info = {
    "Lex04",
    "Assembler Lexical Scanner",
    (OBJ_DATA *)&Lex04_ClassObj,
    (OBJ_DATA *)&Lex_ClassObj,
    (OBJ_IUNKNOWN *)&Lex04_Vtbl,
    sizeof(LEX04_DATA)
};





