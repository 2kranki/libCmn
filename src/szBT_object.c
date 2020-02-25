// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'szBT'
//	Generated 02/25/2020 10:00:28


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




#define			SZBT_OBJECT_C	    1
#include        <szBT_internal.h>
#ifdef  SZBT_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct szBT_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SZBT_SINGLETON
    volatile
    SZBT_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          szBTClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        szBT_Info;            // Forward Reference




static
bool            szBTClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SZBT_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(szBT_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		szBTClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SZBT_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SZBT_CLASS_VTBL    class_Vtbl = {
    {
        &szBT_Info,
        szBTClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        szBT_Class,
        szBTClass_WhoAmI,
        (P_OBJ_QUERYINFO)szBTClass_QueryInfo,
        NULL                        // szBTClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SZBT_CLASS_DATA  szBT_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SZBT_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SZBT_SINGLETON
SZBT_DATA *     szBT_getSingleton (
    void
)
{
    return (OBJ_ID)(szBT_ClassObj.pSingleton);
}


bool            szBT_setSingleton (
    SZBT_DATA       *pValue
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
    if (szBT_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(szBT_ClassObj.pSingleton));
    }
    szBT_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SZBT_DATA *     szBT_Shared (
    void
)
{
    SZBT_DATA       *this = (OBJ_ID)(szBT_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = szBT_New( );
        szBT_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // szBT_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            szBT_SharedReset (
    void
)
{
    SZBT_DATA       *this = (OBJ_ID)(szBT_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        szBT_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          szBTClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SZBT_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SZBT_DATA);
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
                        return (void *)&szBT_Info;
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
                        return szBT_New;
                    }
                    break;
                    
#ifdef  SZBT_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return szBT_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return szBT_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return szBTClass_WhoAmI;
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
bool            szBT_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SZBT == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(szBT_Class())->pClassSuperObject;
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
void            szBT_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          szBT_Class (
    void
)
{
    return (OBJ_ID)&szBT_ClassObj;
}


static
uint16_t		szBT_WhoAmI (
    void
)
{
    return OBJ_IDENT_SZBT;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
SZBT_VTBL     szBT_Vtbl = {
    {
        &szBT_Info,
        szBT_IsKindOf,
#ifdef  SZBT_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        szBT_Dealloc,
        szBT_Class,
        szBT_WhoAmI,
        (P_OBJ_QUERYINFO)szBT_QueryInfo,
        (P_OBJ_TOSTRING)szBT_ToDebugString,
        NULL,			// szBT_Enable,
        NULL,			// szBT_Disable,
        NULL,			// (P_OBJ_ASSIGN)szBT_Assign,
        NULL,			// (P_OBJ_COMPARE)szBT_Compare,
        NULL, 			// (P_OBJ_PTR)szBT_Copy,
        NULL, 			// (P_OBJ_PTR)szBT_DeepCopy,
        NULL 			// (P_OBJ_HASH)szBT_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //szBT_IsEnabled,
 
};



static
const
OBJ_INFO        szBT_Info = {
    "szBT",
    "Static String Binary Tree",
    (OBJ_DATA *)&szBT_ClassObj,
    (OBJ_DATA *)&Blocks_ClassObj,
    (OBJ_IUNKNOWN *)&szBT_Vtbl,
    sizeof(SZBT_DATA)
};





