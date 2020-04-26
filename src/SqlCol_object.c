// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'SqlCol'
//	Generated 04/25/2020 18:28:59


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




#define			SQLCOL_OBJECT_C	    1
#include        <SqlCol_internal.h>
#ifdef  SQLCOL_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SqlCol_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SQLCOL_SINGLETON
    volatile
    SQLCOL_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SqlColClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SqlCol_Info;            // Forward Reference




static
bool            SqlColClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SQLCOL_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SqlCol_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		SqlColClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SQLCOL_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SQLCOL_CLASS_VTBL    class_Vtbl = {
    {
        &SqlCol_Info,
        SqlColClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SqlCol_Class,
        SqlColClass_WhoAmI,
        (P_OBJ_QUERYINFO)SqlColClass_QueryInfo,
        NULL                        // SqlColClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SQLCOL_CLASS_DATA  SqlCol_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SQLCOL_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SQLCOL_SINGLETON
extern
const
SQLCOL_VTBL       SqlCol_VtblShared;


SQLCOL_DATA *     SqlCol_getSingleton (
    void
)
{
    return (OBJ_ID)(SqlCol_ClassObj.pSingleton);
}


bool            SqlCol_setSingleton (
    SQLCOL_DATA       *pValue
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
    if (SqlCol_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SqlCol_ClassObj.pSingleton));
    }
    SqlCol_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SQLCOL_DATA *     SqlCol_Shared (
    void
)
{
    SQLCOL_DATA       *this = (OBJ_ID)(SqlCol_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SqlCol_New( );
        obj_setVtbl(this, (void *)&SqlCol_VtblShared);
        SqlCol_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SqlCol_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SqlCol_SharedReset (
    void
)
{
    SQLCOL_DATA       *this = (OBJ_ID)(SqlCol_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SqlCol_Vtbl);
        obj_Release(this);
        SqlCol_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SqlColClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SQLCOL_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SQLCOL_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&SqlCol_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&SqlCol_Info.pClassSuperObject;
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
                        return SqlCol_New;
                    }
                    break;
                    
				case 'P':
#ifdef  SQLCOL_JSON_SUPPORT
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return SqlCol_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return SqlCol_ParseJsonObject;
					}
#endif
					break;

				case 'T':
#ifdef  SQLCOL_JSON_SUPPORT
					if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
						return SqlCol_ToJsonFields;
					}
					if (str_Compare("ToJson", (char *)pStr) == 0) {
						return SqlCol_ToJson;
					}
#endif
					break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SqlColClass_WhoAmI;
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
bool            SqlCol_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SQLCOL == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SqlCol_Class())->pClassSuperObject;
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
void            SqlCol_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SqlCol_Class (
    void
)
{
    return (OBJ_ID)&SqlCol_ClassObj;
}


static
uint16_t		SqlCol_WhoAmI (
    void
)
{
    return OBJ_IDENT_SQLCOL;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SQLCOL_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SQLCOL_VTBL     SqlCol_VtblShared = {
    {
        &SqlCol_Info,
        SqlCol_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SqlCol_Dealloc,
        SqlCol_Class,
        SqlCol_WhoAmI,
        (P_OBJ_QUERYINFO)SqlCol_QueryInfo,
        (P_OBJ_TOSTRING)SqlCol_ToDebugString,
        NULL,			// SqlCol_Enable,
        NULL,			// SqlCol_Disable,
        NULL,			// (P_OBJ_ASSIGN)SqlCol_Assign,
        NULL,			// (P_OBJ_COMPARE)SqlCol_Compare,
        NULL, 			// (P_OBJ_PTR)SqlCol_Copy,
        NULL, 			// (P_OBJ_PTR)SqlCol_DeepCopy,
        NULL 			// (P_OBJ_HASH)SqlCol_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SqlCol_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SQLCOL_VTBL     SqlCol_Vtbl = {
    {
        &SqlCol_Info,
        SqlCol_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SqlCol_Dealloc,
        SqlCol_Class,
        SqlCol_WhoAmI,
        (P_OBJ_QUERYINFO)SqlCol_QueryInfo,
        (P_OBJ_TOSTRING)SqlCol_ToDebugString,
        NULL,			// SqlCol_Enable,
        NULL,			// SqlCol_Disable,
        NULL,			// (P_OBJ_ASSIGN)SqlCol_Assign,
        NULL,			// (P_OBJ_COMPARE)SqlCol_Compare,
        NULL, 			// (P_OBJ_PTR)SqlCol_Copy,
        NULL, 			// (P_OBJ_PTR)SqlCol_DeepCopy,
        NULL 			// (P_OBJ_HASH)SqlCol_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SqlCol_IsEnabled,
 
};



static
const
OBJ_INFO        SqlCol_Info = {
    "SqlCol",
    "SQL Column Support",
    (OBJ_DATA *)&SqlCol_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&SqlCol_Vtbl,
    sizeof(SQLCOL_DATA)
};





