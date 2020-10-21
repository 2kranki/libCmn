// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'SqlStmt'
//  Generated 10/20/2020 13:49:42


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




#define         SQLSTMT_OBJECT_C       1
#include        <SqlStmt_internal.h>
#ifdef  SQLSTMT_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SqlStmt_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SQLSTMT_SINGLETON
    volatile
    SQLSTMT_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SqlStmtClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SqlStmt_Info;            // Forward Reference




static
bool            SqlStmtClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SQLSTMT_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SqlStmt_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        SqlStmtClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SQLSTMT_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SQLSTMT_CLASS_VTBL    class_Vtbl = {
    {
        &SqlStmt_Info,
        SqlStmtClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SqlStmt_Class,
        SqlStmtClass_WhoAmI,
        (P_OBJ_QUERYINFO)SqlStmtClass_QueryInfo,
        NULL                        // SqlStmtClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

SQLSTMT_CLASS_DATA  SqlStmt_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SQLSTMT_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SQLSTMT_SINGLETON
extern
const
SQLSTMT_VTBL       SqlStmt_VtblShared;


SQLSTMT_DATA *     SqlStmt_getSingleton (
    void
)
{
    return (OBJ_ID)(SqlStmt_ClassObj.pSingleton);
}


bool            SqlStmt_setSingleton (
    SQLSTMT_DATA       *pValue
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
    if (SqlStmt_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SqlStmt_ClassObj.pSingleton));
    }
    SqlStmt_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SQLSTMT_DATA *     SqlStmt_Shared (
    void
)
{
    SQLSTMT_DATA       *this = (OBJ_ID)(SqlStmt_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SqlStmt_New( );
        obj_setVtbl(this, (void *)&SqlStmt_VtblShared);
        SqlStmt_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SqlStmt_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SqlStmt_SharedReset (
    void
)
{
    SQLSTMT_DATA       *this = (OBJ_ID)(SqlStmt_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SqlStmt_Vtbl);
        obj_Release(this);
        SqlStmt_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SqlStmtClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SQLSTMT_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SQLSTMT_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&SqlStmt_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&SqlStmt_Info.pClassSuperObject;
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
                        return SqlStmt_New;
                    }
                    break;
                    
                case 'P':
#ifdef  SQLSTMT_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return SqlStmt_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return SqlStmt_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  SQLSTMT_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return SqlStmt_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return SqlStmt_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SqlStmtClass_WhoAmI;
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
bool            SqlStmt_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SQLSTMT == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SqlStmt_Class())->pClassSuperObject;
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
void            SqlStmt_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SqlStmt_Class (
    void
)
{
    return (OBJ_ID)&SqlStmt_ClassObj;
}


static
uint16_t        SqlStmt_WhoAmI (
    void
)
{
    return OBJ_IDENT_SQLSTMT;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SQLSTMT_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SQLSTMT_VTBL     SqlStmt_VtblShared = {
    {
        &SqlStmt_Info,
        SqlStmt_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SqlStmt_Dealloc,
        SqlStmt_Class,
        SqlStmt_WhoAmI,
        (P_OBJ_QUERYINFO)SqlStmt_QueryInfo,
        (P_OBJ_TOSTRING)SqlStmt_ToDebugString,
        NULL,           // SqlStmt_Enable,
        NULL,           // SqlStmt_Disable,
        NULL,           // (P_OBJ_ASSIGN)SqlStmt_Assign,
        NULL,           // (P_OBJ_COMPARE)SqlStmt_Compare,
        NULL,           // (P_OBJ_PTR)SqlStmt_Copy,
        NULL,           // (P_OBJ_PTR)SqlStmt_DeepCopy,
        NULL            // (P_OBJ_HASH)SqlStmt_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SqlStmt_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SQLSTMT_VTBL     SqlStmt_Vtbl = {
    {
        &SqlStmt_Info,
        SqlStmt_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SqlStmt_Dealloc,
        SqlStmt_Class,
        SqlStmt_WhoAmI,
        (P_OBJ_QUERYINFO)SqlStmt_QueryInfo,
        (P_OBJ_TOSTRING)SqlStmt_ToDebugString,
        NULL,           // SqlStmt_Enable,
        NULL,           // SqlStmt_Disable,
        NULL,           // (P_OBJ_ASSIGN)SqlStmt_Assign,
        NULL,           // (P_OBJ_COMPARE)SqlStmt_Compare,
        NULL,           // (P_OBJ_PTR)SqlStmt_Copy,
        NULL,           // (P_OBJ_PTR)SqlStmt_DeepCopy,
        NULL            // (P_OBJ_HASH)SqlStmt_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SqlStmt_IsEnabled,
 
};



static
const
OBJ_INFO        SqlStmt_Info = {
    "SqlStmt",
    "SQL Statement",
    (OBJ_DATA *)&SqlStmt_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&SqlStmt_Vtbl,
    sizeof(SQLSTMT_DATA)
};





