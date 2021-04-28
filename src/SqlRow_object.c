// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'SqlRow'
//  Generated 04/14/2021 10:28:06


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




#define         SQLROW_OBJECT_C       1
#include        <SqlRow_internal.h>
#ifdef  SQLROW_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SqlRow_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SQLROW_SINGLETON
    volatile
    SQLROW_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SqlRowClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SqlRow_Info;            // Forward Reference




static
bool            SqlRowClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SQLROW_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SqlRow_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        SqlRowClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SQLROW_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SQLROW_CLASS_VTBL    class_Vtbl = {
    {
        &SqlRow_Info,
        SqlRowClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SqlRow_Class,
        SqlRowClass_WhoAmI,
        (P_OBJ_QUERYINFO)SqlRowClass_QueryInfo,
        NULL                        // SqlRowClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

SQLROW_CLASS_DATA  SqlRow_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SQLROW_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SQLROW_SINGLETON
extern
const
SQLROW_VTBL       SqlRow_VtblShared;


SQLROW_DATA *     SqlRow_getSingleton (
    void
)
{
    return (OBJ_ID)(SqlRow_ClassObj.pSingleton);
}


bool            SqlRow_setSingleton (
    SQLROW_DATA       *pValue
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
    if (SqlRow_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SqlRow_ClassObj.pSingleton));
    }
    SqlRow_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SQLROW_DATA *     SqlRow_Shared (
    void
)
{
    SQLROW_DATA       *this = (OBJ_ID)(SqlRow_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SqlRow_New( );
        obj_setVtbl(this, (void *)&SqlRow_VtblShared);
        SqlRow_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SqlRow_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SqlRow_SharedReset (
    void
)
{
    SQLROW_DATA       *this = (OBJ_ID)(SqlRow_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SqlRow_Vtbl);
        obj_Release(this);
        SqlRow_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SqlRowClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SQLROW_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SQLROW_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&SqlRow_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&SqlRow_Info.pClassSuperObject;
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
                        return SqlRow_New;
                    }
                    break;
                    
                case 'P':
#ifdef  SQLROW_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return SqlRow_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return SqlRow_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  SQLROW_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return SqlRow_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return SqlRow_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SqlRowClass_WhoAmI;
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
bool            SqlRow_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SQLROW == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SqlRow_Class())->pClassSuperObject;
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
void            SqlRow_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SqlRow_Class (
    void
)
{
    return (OBJ_ID)&SqlRow_ClassObj;
}


static
uint16_t        SqlRow_WhoAmI (
    void
)
{
    return OBJ_IDENT_SQLROW;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SQLROW_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SQLROW_VTBL     SqlRow_VtblShared = {
    {
        &SqlRow_Info,
        SqlRow_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SqlRow_Dealloc,
        SqlRow_Class,
        SqlRow_WhoAmI,
        (P_OBJ_QUERYINFO)SqlRow_QueryInfo,
        (P_OBJ_TOSTRING)SqlRow_ToDebugString,
        NULL,           // SqlRow_Enable,
        NULL,           // SqlRow_Disable,
        NULL,           // (P_OBJ_ASSIGN)SqlRow_Assign,
        NULL,           // (P_OBJ_COMPARE)SqlRow_Compare,
        NULL,           // (P_OBJ_PTR)SqlRow_Copy,
        NULL,           // (P_OBJ_PTR)SqlRow_DeepCopy,
        NULL            // (P_OBJ_HASH)SqlRow_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SqlRow_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SQLROW_VTBL     SqlRow_Vtbl = {
    {
        &SqlRow_Info,
        SqlRow_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SqlRow_Dealloc,
        SqlRow_Class,
        SqlRow_WhoAmI,
        (P_OBJ_QUERYINFO)SqlRow_QueryInfo,
        (P_OBJ_TOSTRING)SqlRow_ToDebugString,
        NULL,           // SqlRow_Enable,
        NULL,           // SqlRow_Disable,
        (P_OBJ_ASSIGN)SqlRow_Assign,
        NULL,           // (P_OBJ_COMPARE)SqlRow_Compare,
        (P_OBJ_PTR)SqlRow_Copy,
        NULL,           // (P_OBJ_PTR)SqlRow_DeepCopy,
        NULL            // (P_OBJ_HASH)SqlRow_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SqlRow_IsEnabled,
 
};



static
const
OBJ_INFO        SqlRow_Info = {
    "SqlRow",
    "SQL Row Support",
    (OBJ_DATA *)&SqlRow_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&SqlRow_Vtbl,
    sizeof(SQLROW_DATA)
};





