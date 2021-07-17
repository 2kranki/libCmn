// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'CsvRcd'
//  Generated 07/16/2021 23:40:28


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




#define         CSVRCD_OBJECT_C       1
#include        <CsvRcd_internal.h>
#ifdef  CSVRCD_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct CsvRcd_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  CSVRCD_SINGLETON
    volatile
    CSVRCD_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          CsvRcdClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        CsvRcd_Info;            // Forward Reference




static
bool            CsvRcdClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_CSVRCD_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(CsvRcd_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        CsvRcdClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_CSVRCD_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
CSVRCD_CLASS_VTBL    class_Vtbl = {
    {
        &CsvRcd_Info,
        CsvRcdClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        CsvRcd_Class,
        CsvRcdClass_WhoAmI,
        (P_OBJ_QUERYINFO)CsvRcdClass_QueryInfo,
        NULL                        // CsvRcdClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

CSVRCD_CLASS_DATA  CsvRcd_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(CSVRCD_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  CSVRCD_SINGLETON
extern
const
CSVRCD_VTBL       CsvRcd_VtblShared;


CSVRCD_DATA *     CsvRcd_getSingleton (
    void
)
{
    return (OBJ_ID)(CsvRcd_ClassObj.pSingleton);
}


bool            CsvRcd_setSingleton (
    CSVRCD_DATA       *pValue
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
    if (CsvRcd_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(CsvRcd_ClassObj.pSingleton));
    }
    CsvRcd_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



CSVRCD_DATA *     CsvRcd_Shared (
    void
)
{
    CSVRCD_DATA       *this = (OBJ_ID)(CsvRcd_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = CsvRcd_New( );
        obj_setVtbl(this, (void *)&CsvRcd_VtblShared);
        CsvRcd_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // CsvRcd_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            CsvRcd_SharedReset (
    void
)
{
    CSVRCD_DATA       *this = (OBJ_ID)(CsvRcd_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&CsvRcd_Vtbl);
        obj_Release(this);
        CsvRcd_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          CsvRcdClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    CSVRCD_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(CSVRCD_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&CsvRcd_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&CsvRcd_Info.pClassSuperObject;
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
                        return CsvRcd_New;
                    }
                    break;
                    
                case 'P':
#ifdef  CSVRCD_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return CsvRcd_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return CsvRcd_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  CSVRCD_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return CsvRcd_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return CsvRcd_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return CsvRcdClass_WhoAmI;
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
bool            CsvRcd_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_CSVRCD == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(CsvRcd_Class())->pClassSuperObject;
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
void            CsvRcd_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          CsvRcd_Class (
    void
)
{
    return (OBJ_ID)&CsvRcd_ClassObj;
}


static
uint16_t        CsvRcd_WhoAmI (
    void
)
{
    return OBJ_IDENT_CSVRCD;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  CSVRCD_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
CSVRCD_VTBL     CsvRcd_VtblShared = {
    {
        &CsvRcd_Info,
        CsvRcd_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        CsvRcd_Dealloc,
        CsvRcd_Class,
        CsvRcd_WhoAmI,
        (P_OBJ_QUERYINFO)CsvRcd_QueryInfo,
        (P_OBJ_TOSTRING)CsvRcd_ToDebugString,
        NULL,           // CsvRcd_Enable,
        NULL,           // CsvRcd_Disable,
        NULL,           // (P_OBJ_ASSIGN)CsvRcd_Assign,
        NULL,           // (P_OBJ_COMPARE)CsvRcd_Compare,
        NULL,           // (P_OBJ_PTR)CsvRcd_Copy,
        NULL,           // (P_OBJ_PTR)CsvRcd_DeepCopy,
        NULL            // (P_OBJ_HASH)CsvRcd_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //CsvRcd_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
CSVRCD_VTBL     CsvRcd_Vtbl = {
    {
        &CsvRcd_Info,
        CsvRcd_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        CsvRcd_Dealloc,
        CsvRcd_Class,
        CsvRcd_WhoAmI,
        (P_OBJ_QUERYINFO)CsvRcd_QueryInfo,
        (P_OBJ_TOSTRING)CsvRcd_ToDebugString,
        NULL,           // CsvRcd_Enable,
        NULL,           // CsvRcd_Disable,
        NULL,           // (P_OBJ_ASSIGN)CsvRcd_Assign,
        NULL,           // (P_OBJ_COMPARE)CsvRcd_Compare,
        NULL,           // (P_OBJ_PTR)CsvRcd_Copy,
        NULL,           // (P_OBJ_PTR)CsvRcd_DeepCopy,
        NULL            // (P_OBJ_HASH)CsvRcd_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //CsvRcd_IsEnabled,
 
};



static
const
OBJ_INFO        CsvRcd_Info = {
    "CsvRcd",
    "Comma Delimited Record",
    (OBJ_DATA *)&CsvRcd_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&CsvRcd_Vtbl,
    sizeof(CSVRCD_DATA)
};





