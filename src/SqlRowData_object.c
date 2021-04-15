// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'SqlRowData'
//  Generated 04/14/2021 21:08:08


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




#define         SQLROWDATA_OBJECT_C       1
#include        <SqlRowData_internal.h>
#ifdef  SQLROWDATA_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SqlRowData_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SQLROWDATA_SINGLETON
    volatile
    SQLROWDATA_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SqlRowDataClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SqlRowData_Info;            // Forward Reference




static
bool            SqlRowDataClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SQLROWDATA_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SqlRowData_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        SqlRowDataClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SQLROWDATA_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SQLROWDATA_CLASS_VTBL    class_Vtbl = {
    {
        &SqlRowData_Info,
        SqlRowDataClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SqlRowData_Class,
        SqlRowDataClass_WhoAmI,
        (P_OBJ_QUERYINFO)SqlRowDataClass_QueryInfo,
        NULL                        // SqlRowDataClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

SQLROWDATA_CLASS_DATA  SqlRowData_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SQLROWDATA_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SQLROWDATA_SINGLETON
extern
const
SQLROWDATA_VTBL       SqlRowData_VtblShared;


SQLROWDATA_DATA *     SqlRowData_getSingleton (
    void
)
{
    return (OBJ_ID)(SqlRowData_ClassObj.pSingleton);
}


bool            SqlRowData_setSingleton (
    SQLROWDATA_DATA       *pValue
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
    if (SqlRowData_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SqlRowData_ClassObj.pSingleton));
    }
    SqlRowData_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SQLROWDATA_DATA *     SqlRowData_Shared (
    void
)
{
    SQLROWDATA_DATA       *this = (OBJ_ID)(SqlRowData_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SqlRowData_New( );
        obj_setVtbl(this, (void *)&SqlRowData_VtblShared);
        SqlRowData_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SqlRowData_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SqlRowData_SharedReset (
    void
)
{
    SQLROWDATA_DATA       *this = (OBJ_ID)(SqlRowData_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SqlRowData_Vtbl);
        obj_Release(this);
        SqlRowData_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SqlRowDataClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SQLROWDATA_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SQLROWDATA_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&SqlRowData_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&SqlRowData_Info.pClassSuperObject;
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
                        return SqlRowData_New;
                    }
                    break;
                    
                case 'P':
#ifdef  SQLROWDATA_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return SqlRowData_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return SqlRowData_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  SQLROWDATA_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return SqlRowData_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return SqlRowData_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SqlRowDataClass_WhoAmI;
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
bool            SqlRowData_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SQLROWDATA == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SqlRowData_Class())->pClassSuperObject;
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
void            SqlRowData_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SqlRowData_Class (
    void
)
{
    return (OBJ_ID)&SqlRowData_ClassObj;
}


static
uint16_t        SqlRowData_WhoAmI (
    void
)
{
    return OBJ_IDENT_SQLROWDATA;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SQLROWDATA_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SQLROWDATA_VTBL     SqlRowData_VtblShared = {
    {
        &SqlRowData_Info,
        SqlRowData_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SqlRowData_Dealloc,
        SqlRowData_Class,
        SqlRowData_WhoAmI,
        (P_OBJ_QUERYINFO)SqlRowData_QueryInfo,
        (P_OBJ_TOSTRING)SqlRowData_ToDebugString,
        NULL,           // SqlRowData_Enable,
        NULL,           // SqlRowData_Disable,
        NULL,           // (P_OBJ_ASSIGN)SqlRowData_Assign,
        NULL,           // (P_OBJ_COMPARE)SqlRowData_Compare,
        NULL,           // (P_OBJ_PTR)SqlRowData_Copy,
        NULL,           // (P_OBJ_PTR)SqlRowData_DeepCopy,
        NULL            // (P_OBJ_HASH)SqlRowData_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SqlRowData_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SQLROWDATA_VTBL     SqlRowData_Vtbl = {
    {
        &SqlRowData_Info,
        SqlRowData_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SqlRowData_Dealloc,
        SqlRowData_Class,
        SqlRowData_WhoAmI,
        (P_OBJ_QUERYINFO)SqlRowData_QueryInfo,
        (P_OBJ_TOSTRING)SqlRowData_ToDebugString,
        NULL,           // SqlRowData_Enable,
        NULL,           // SqlRowData_Disable,
        NULL,           // (P_OBJ_ASSIGN)SqlRowData_Assign,
        NULL,           // (P_OBJ_COMPARE)SqlRowData_Compare,
        NULL,           // (P_OBJ_PTR)SqlRowData_Copy,
        NULL,           // (P_OBJ_PTR)SqlRowData_DeepCopy,
        NULL            // (P_OBJ_HASH)SqlRowData_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SqlRowData_IsEnabled,
 
};



static
const
OBJ_INFO        SqlRowData_Info = {
    "SqlRowData",
    "SQL Row Data",
    (OBJ_DATA *)&SqlRowData_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&SqlRowData_Vtbl,
    sizeof(SQLROWDATA_DATA)
};





