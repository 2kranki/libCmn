// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'SqlColDef'
//	Generated 04/26/2020 11:52:28


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




#define			SQLCOLDEF_OBJECT_C	    1
#include        <SqlColDef_internal.h>
#ifdef  SQLCOLDEF_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SqlColDef_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SQLCOLDEF_SINGLETON
    volatile
    SQLCOLDEF_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SqlColDefClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SqlColDef_Info;            // Forward Reference




static
bool            SqlColDefClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SQLCOLDEF_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SqlColDef_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		SqlColDefClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SQLCOLDEF_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SQLCOLDEF_CLASS_VTBL    class_Vtbl = {
    {
        &SqlColDef_Info,
        SqlColDefClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SqlColDef_Class,
        SqlColDefClass_WhoAmI,
        (P_OBJ_QUERYINFO)SqlColDefClass_QueryInfo,
        NULL                        // SqlColDefClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SQLCOLDEF_CLASS_DATA  SqlColDef_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SQLCOLDEF_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SQLCOLDEF_SINGLETON
extern
const
SQLCOLDEF_VTBL       SqlColDef_VtblShared;


SQLCOLDEF_DATA *     SqlColDef_getSingleton (
    void
)
{
    return (OBJ_ID)(SqlColDef_ClassObj.pSingleton);
}


bool            SqlColDef_setSingleton (
    SQLCOLDEF_DATA       *pValue
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
    if (SqlColDef_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SqlColDef_ClassObj.pSingleton));
    }
    SqlColDef_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SQLCOLDEF_DATA *     SqlColDef_Shared (
    void
)
{
    SQLCOLDEF_DATA       *this = (OBJ_ID)(SqlColDef_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SqlColDef_New( );
        obj_setVtbl(this, (void *)&SqlColDef_VtblShared);
        SqlColDef_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SqlColDef_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SqlColDef_SharedReset (
    void
)
{
    SQLCOLDEF_DATA       *this = (OBJ_ID)(SqlColDef_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SqlColDef_Vtbl);
        obj_Release(this);
        SqlColDef_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SqlColDefClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SQLCOLDEF_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SQLCOLDEF_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&SqlColDef_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&SqlColDef_Info.pClassSuperObject;
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
                        return SqlColDef_New;
                    }
                    break;
                    
				case 'P':
#ifdef  SQLCOLDEF_JSON_SUPPORT
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return SqlColDef_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return SqlColDef_ParseJsonObject;
					}
#endif
					break;

				case 'T':
#ifdef  SQLCOLDEF_JSON_SUPPORT
					if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
						return SqlColDef_ToJsonFields;
					}
					if (str_Compare("ToJson", (char *)pStr) == 0) {
						return SqlColDef_ToJson;
					}
#endif
					break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SqlColDefClass_WhoAmI;
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
bool            SqlColDef_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SQLCOLDEF == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SqlColDef_Class())->pClassSuperObject;
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
void            SqlColDef_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SqlColDef_Class (
    void
)
{
    return (OBJ_ID)&SqlColDef_ClassObj;
}


static
uint16_t		SqlColDef_WhoAmI (
    void
)
{
    return OBJ_IDENT_SQLCOLDEF;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SQLCOLDEF_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SQLCOLDEF_VTBL     SqlColDef_VtblShared = {
    {
        &SqlColDef_Info,
        SqlColDef_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SqlColDef_Dealloc,
        SqlColDef_Class,
        SqlColDef_WhoAmI,
        (P_OBJ_QUERYINFO)SqlColDef_QueryInfo,
        (P_OBJ_TOSTRING)SqlColDef_ToDebugString,
        NULL,			// SqlColDef_Enable,
        NULL,			// SqlColDef_Disable,
        NULL,			// (P_OBJ_ASSIGN)SqlColDef_Assign,
        NULL,			// (P_OBJ_COMPARE)SqlColDef_Compare,
        NULL, 			// (P_OBJ_PTR)SqlColDef_Copy,
        NULL, 			// (P_OBJ_PTR)SqlColDef_DeepCopy,
        NULL 			// (P_OBJ_HASH)SqlColDef_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SqlColDef_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SQLCOLDEF_VTBL     SqlColDef_Vtbl = {
    {
        &SqlColDef_Info,
        SqlColDef_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SqlColDef_Dealloc,
        SqlColDef_Class,
        SqlColDef_WhoAmI,
        (P_OBJ_QUERYINFO)SqlColDef_QueryInfo,
        (P_OBJ_TOSTRING)SqlColDef_ToDebugString,
        NULL,			// SqlColDef_Enable,
        NULL,			// SqlColDef_Disable,
        NULL,			// (P_OBJ_ASSIGN)SqlColDef_Assign,
        NULL,			// (P_OBJ_COMPARE)SqlColDef_Compare,
        NULL, 			// (P_OBJ_PTR)SqlColDef_Copy,
        NULL, 			// (P_OBJ_PTR)SqlColDef_DeepCopy,
        NULL 			// (P_OBJ_HASH)SqlColDef_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SqlColDef_IsEnabled,
 
};



static
const
OBJ_INFO        SqlColDef_Info = {
    "SqlColDef",
    "Separate SqlColDef",
    (OBJ_DATA *)&SqlColDef_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&SqlColDef_Vtbl,
    sizeof(SQLCOLDEF_DATA)
};
#warning -- adjust super class object in Info above 
//			if object inherits from another class
//			Also, update description





