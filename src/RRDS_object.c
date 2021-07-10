// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'RRDS'
//  Generated 07/10/2021 09:44:02


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




#define         RRDS_OBJECT_C       1
#include        <RRDS_internal.h>
#ifdef  RRDS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct RRDS_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  RRDS_SINGLETON
    volatile
    RRDS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          RRDSClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        RRDS_Info;            // Forward Reference




static
bool            RRDSClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_RRDS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(RRDS_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        RRDSClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_RRDS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
RRDS_CLASS_VTBL    class_Vtbl = {
    {
        &RRDS_Info,
        RRDSClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        RRDS_Class,
        RRDSClass_WhoAmI,
        (P_OBJ_QUERYINFO)RRDSClass_QueryInfo,
        NULL                        // RRDSClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

RRDS_CLASS_DATA  RRDS_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(RRDS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  RRDS_SINGLETON
extern
const
RRDS_VTBL       RRDS_VtblShared;


RRDS_DATA *     RRDS_getSingleton (
    void
)
{
    return (OBJ_ID)(RRDS_ClassObj.pSingleton);
}


bool            RRDS_setSingleton (
    RRDS_DATA       *pValue
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
    if (RRDS_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(RRDS_ClassObj.pSingleton));
    }
    RRDS_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



RRDS_DATA *     RRDS_Shared (
    void
)
{
    RRDS_DATA       *this = (OBJ_ID)(RRDS_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = RRDS_New( );
        obj_setVtbl(this, (void *)&RRDS_VtblShared);
        RRDS_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // RRDS_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            RRDS_SharedReset (
    void
)
{
    RRDS_DATA       *this = (OBJ_ID)(RRDS_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&RRDS_Vtbl);
        obj_Release(this);
        RRDS_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          RRDSClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    RRDS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(RRDS_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&RRDS_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&RRDS_Info.pClassSuperObject;
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
                        return RRDS_New;
                    }
                    break;
                    
                case 'P':
#ifdef  RRDS_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return RRDS_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return RRDS_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  RRDS_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return RRDS_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return RRDS_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return RRDSClass_WhoAmI;
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
bool            RRDS_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_RRDS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(RRDS_Class())->pClassSuperObject;
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
void            RRDS_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          RRDS_Class (
    void
)
{
    return (OBJ_ID)&RRDS_ClassObj;
}


static
uint16_t        RRDS_WhoAmI (
    void
)
{
    return OBJ_IDENT_RRDS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  RRDS_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
RRDS_VTBL     RRDS_VtblShared = {
    {
        &RRDS_Info,
        RRDS_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        RRDS_Dealloc,
        RRDS_Class,
        RRDS_WhoAmI,
        (P_OBJ_QUERYINFO)RRDS_QueryInfo,
        (P_OBJ_TOSTRING)RRDS_ToDebugString,
        NULL,           // RRDS_Enable,
        NULL,           // RRDS_Disable,
        NULL,           // (P_OBJ_ASSIGN)RRDS_Assign,
        NULL,           // (P_OBJ_COMPARE)RRDS_Compare,
        NULL,           // (P_OBJ_PTR)RRDS_Copy,
        NULL,           // (P_OBJ_PTR)RRDS_DeepCopy,
        NULL            // (P_OBJ_HASH)RRDS_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //RRDS_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
RRDS_VTBL     RRDS_Vtbl = {
    {
        &RRDS_Info,
        RRDS_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        RRDS_Dealloc,
        RRDS_Class,
        RRDS_WhoAmI,
        (P_OBJ_QUERYINFO)RRDS_QueryInfo,
        (P_OBJ_TOSTRING)RRDS_ToDebugString,
        NULL,           // RRDS_Enable,
        NULL,           // RRDS_Disable,
        NULL,           // (P_OBJ_ASSIGN)RRDS_Assign,
        NULL,           // (P_OBJ_COMPARE)RRDS_Compare,
        NULL,           // (P_OBJ_PTR)RRDS_Copy,
        NULL,           // (P_OBJ_PTR)RRDS_DeepCopy,
        NULL            // (P_OBJ_HASH)RRDS_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //RRDS_IsEnabled,
 
};



static
const
OBJ_INFO        RRDS_Info = {
    "RRDS",
    "Relative Record Dataset (ie Fixed size records indexed by record number)",
    (OBJ_DATA *)&RRDS_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&RRDS_Vtbl,
    sizeof(RRDS_DATA)
};





