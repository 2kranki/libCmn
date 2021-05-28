// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'psxExec'
//  Generated 05/28/2021 13:56:42


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




#define         PSXEXEC_OBJECT_C       1
#include        <psxExec_internal.h>
#ifdef  PSXEXEC_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct psxExec_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  PSXEXEC_SINGLETON
    volatile
    PSXEXEC_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          psxExecClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        psxExec_Info;            // Forward Reference




static
bool            psxExecClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_PSXEXEC_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(psxExec_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        psxExecClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_PSXEXEC_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
PSXEXEC_CLASS_VTBL    class_Vtbl = {
    {
        &psxExec_Info,
        psxExecClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        psxExec_Class,
        psxExecClass_WhoAmI,
        (P_OBJ_QUERYINFO)psxExecClass_QueryInfo,
        NULL                        // psxExecClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

PSXEXEC_CLASS_DATA  psxExec_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(PSXEXEC_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  PSXEXEC_SINGLETON
extern
const
PSXEXEC_VTBL       psxExec_VtblShared;


PSXEXEC_DATA *     psxExec_getSingleton (
    void
)
{
    return (OBJ_ID)(psxExec_ClassObj.pSingleton);
}


bool            psxExec_setSingleton (
    PSXEXEC_DATA       *pValue
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
    if (psxExec_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(psxExec_ClassObj.pSingleton));
    }
    psxExec_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



PSXEXEC_DATA *     psxExec_Shared (
    void
)
{
    PSXEXEC_DATA       *this = (OBJ_ID)(psxExec_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = psxExec_New( );
        obj_setVtbl(this, (void *)&psxExec_VtblShared);
        psxExec_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // psxExec_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            psxExec_SharedReset (
    void
)
{
    PSXEXEC_DATA       *this = (OBJ_ID)(psxExec_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&psxExec_Vtbl);
        obj_Release(this);
        psxExec_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          psxExecClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PSXEXEC_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PSXEXEC_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&psxExec_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&psxExec_Info.pClassSuperObject;
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
                        return psxExec_New;
                    }
                    break;
                    
                case 'P':
#ifdef  PSXEXEC_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return psxExec_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return psxExec_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  PSXEXEC_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return psxExec_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return psxExec_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return psxExecClass_WhoAmI;
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
bool            psxExec_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_PSXEXEC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(psxExec_Class())->pClassSuperObject;
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
void            psxExec_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          psxExec_Class (
    void
)
{
    return (OBJ_ID)&psxExec_ClassObj;
}


static
uint16_t        psxExec_WhoAmI (
    void
)
{
    return OBJ_IDENT_PSXEXEC;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  PSXEXEC_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
PSXEXEC_VTBL     psxExec_VtblShared = {
    {
        &psxExec_Info,
        psxExec_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        psxExec_Dealloc,
        psxExec_Class,
        psxExec_WhoAmI,
        (P_OBJ_QUERYINFO)psxExec_QueryInfo,
        (P_OBJ_TOSTRING)psxExec_ToDebugString,
        NULL,           // psxExec_Enable,
        NULL,           // psxExec_Disable,
        NULL,           // (P_OBJ_ASSIGN)psxExec_Assign,
        NULL,           // (P_OBJ_COMPARE)psxExec_Compare,
        NULL,           // (P_OBJ_PTR)psxExec_Copy,
        NULL,           // (P_OBJ_PTR)psxExec_DeepCopy,
        NULL            // (P_OBJ_HASH)psxExec_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //psxExec_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
PSXEXEC_VTBL     psxExec_Vtbl = {
    {
        &psxExec_Info,
        psxExec_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        psxExec_Dealloc,
        psxExec_Class,
        psxExec_WhoAmI,
        (P_OBJ_QUERYINFO)psxExec_QueryInfo,
        (P_OBJ_TOSTRING)psxExec_ToDebugString,
        NULL,           // psxExec_Enable,
        NULL,           // psxExec_Disable,
        NULL,           // (P_OBJ_ASSIGN)psxExec_Assign,
        NULL,           // (P_OBJ_COMPARE)psxExec_Compare,
        NULL,           // (P_OBJ_PTR)psxExec_Copy,
        NULL,           // (P_OBJ_PTR)psxExec_DeepCopy,
        NULL            // (P_OBJ_HASH)psxExec_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //psxExec_IsEnabled,
 
};



static
const
OBJ_INFO        psxExec_Info = {
    "psxExec",
    "Execute Posix Shell Commands",
    (OBJ_DATA *)&psxExec_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&psxExec_Vtbl,
    sizeof(PSXEXEC_DATA)
};





