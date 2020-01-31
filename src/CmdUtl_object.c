// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'CmdUtl'
//	Generated 01/31/2020 13:17:41


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




#define			CMDUTL_OBJECT_C	    1
#include        <CmdUtl_internal.h>
#ifdef  CMDUTL_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct CmdUtl_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  CMDUTL_SINGLETON
    volatile
    CMDUTL_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          CmdUtlClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        CmdUtl_Info;            // Forward Reference




static
bool            CmdUtlClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_CMDUTL_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(CmdUtl_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		CmdUtlClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_CMDUTL_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
CMDUTL_CLASS_VTBL    class_Vtbl = {
    {
        &CmdUtl_Info,
        CmdUtlClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        CmdUtl_Class,
        CmdUtlClass_WhoAmI,
        (P_OBJ_QUERYINFO)CmdUtlClass_QueryInfo,
        NULL                        // CmdUtlClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

CMDUTL_CLASS_DATA  CmdUtl_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(CMDUTL_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  CMDUTL_SINGLETON
CMDUTL_DATA *     CmdUtl_getSingleton (
    void
)
{
    return (OBJ_ID)(CmdUtl_ClassObj.pSingleton);
}


bool            CmdUtl_setSingleton (
    CMDUTL_DATA       *pValue
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
    if (CmdUtl_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(CmdUtl_ClassObj.pSingleton));
    }
    CmdUtl_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



CMDUTL_DATA *     CmdUtl_Shared (
    void
)
{
    CMDUTL_DATA       *this = (OBJ_ID)(CmdUtl_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = CmdUtl_New( );
        CmdUtl_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // CmdUtl_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            CmdUtl_SharedReset (
    void
)
{
    CMDUTL_DATA       *this = (OBJ_ID)(CmdUtl_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        CmdUtl_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          CmdUtlClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    CMDUTL_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(CMDUTL_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&CmdUtl_Info;
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
                        return CmdUtl_New;
                    }
                    break;
                    
#ifdef  CMDUTL_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return CmdUtl_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return CmdUtl_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return CmdUtlClass_WhoAmI;
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
bool            CmdUtl_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_CMDUTL == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(CmdUtl_Class())->pClassSuperObject;
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
void            CmdUtl_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          CmdUtl_Class (
    void
)
{
    return (OBJ_ID)&CmdUtl_ClassObj;
}


static
uint16_t		CmdUtl_WhoAmI (
    void
)
{
    return OBJ_IDENT_CMDUTL;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
CMDUTL_VTBL     CmdUtl_Vtbl = {
    {
        &CmdUtl_Info,
        CmdUtl_IsKindOf,
#ifdef  CMDUTL_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        CmdUtl_Dealloc,
        CmdUtl_Class,
        CmdUtl_WhoAmI,
        (P_OBJ_QUERYINFO)CmdUtl_QueryInfo,
        (P_OBJ_TOSTRING)CmdUtl_ToDebugString,
        NULL,			// CmdUtl_Enable,
        NULL,			// CmdUtl_Disable,
        NULL,			// (P_OBJ_ASSIGN)CmdUtl_Assign,
        NULL,			// (P_OBJ_COMPARE)CmdUtl_Compare,
        NULL, 			// (P_OBJ_PTR)CmdUtl_Copy,
        NULL, 			// (P_OBJ_PTR)CmdUtl_DeepCopy,
        NULL 			// (P_OBJ_HASH)CmdUtl_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //CmdUtl_IsEnabled,
 
};



static
const
OBJ_INFO        CmdUtl_Info = {
    "CmdUtl",
    "Command Line Utilities",
    (OBJ_DATA *)&CmdUtl_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&CmdUtl_Vtbl,
    sizeof(CMDUTL_DATA)
};





