// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'True'
//	Generated 03/11/2020 10:01:59


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




#define			TRUE_OBJECT_C	    1
#include        <True_internal.h>
#ifdef  TRUE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct True_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TRUE_SINGLETON
    volatile
    TRUE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          TrueClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        True_Info;            // Forward Reference




static
bool            TrueClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_TRUE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(True_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		TrueClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_TRUE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TRUE_CLASS_VTBL    class_Vtbl = {
    {
        &True_Info,
        TrueClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        True_Class,
        TrueClass_WhoAmI,
        (P_OBJ_QUERYINFO)TrueClass_QueryInfo,
        NULL                        // TrueClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

TRUE_CLASS_DATA  True_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TRUE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TRUE_SINGLETON
extern
const
TRUE_VTBL       True_VtblShared;


TRUE_DATA *     True_getSingleton (
    void
)
{
    return (OBJ_ID)(True_ClassObj.pSingleton);
}


bool            True_setSingleton (
    TRUE_DATA       *pValue
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
    if (True_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(True_ClassObj.pSingleton));
    }
    True_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TRUE_DATA *     True_Shared (
    void
)
{
    TRUE_DATA       *this = (OBJ_ID)(True_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = True_New( );
        obj_setVtbl(this, (void *)&True_VtblShared);
        True_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // True_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            True_SharedReset (
    void
)
{
    TRUE_DATA       *this = (OBJ_ID)(True_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&True_Vtbl);
        obj_Release(this);
        True_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          TrueClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TRUE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TRUE_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&True_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&True_Info.pClassSuperObject;
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
                        return True_New;
                    }
                    break;
                    
				case 'P':
#ifdef  TRUE_JSON_SUPPORT
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return True_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return True_ParseJsonObject;
					}
#endif
					break;

				case 'T':
#ifdef  TRUE_JSON_SUPPORT
					if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
						return True_ToJsonFields;
					}
					if (str_Compare("ToJson", (char *)pStr) == 0) {
						return True_ToJson;
					}
#endif
					break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return TrueClass_WhoAmI;
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
bool            True_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_TRUE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(True_Class())->pClassSuperObject;
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
void            True_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          True_Class (
    void
)
{
    return (OBJ_ID)&True_ClassObj;
}


static
uint16_t		True_WhoAmI (
    void
)
{
    return OBJ_IDENT_TRUE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  TRUE_SINGLETON
const
TRUE_VTBL     True_VtblShared = {
    {
        &True_Info,
        True_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        True_Dealloc,
        True_Class,
        True_WhoAmI,
        (P_OBJ_QUERYINFO)True_QueryInfo,
        (P_OBJ_TOSTRING)True_ToDebugString,
        NULL,            // True_Enable,
        NULL,            // True_Disable,
        (P_OBJ_ASSIGN)True_Assign,
        (P_OBJ_COMPARE)True_Compare,
        (P_OBJ_PTR)True_Copy,
        NULL,             // (P_OBJ_PTR)True_DeepCopy,
        NULL             // (P_OBJ_HASH)True_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //True_IsEnabled,

};
#endif


const
TRUE_VTBL     True_Vtbl = {
    {
        &True_Info,
        True_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        True_Dealloc,
        True_Class,
        True_WhoAmI,
        (P_OBJ_QUERYINFO)True_QueryInfo,
        (P_OBJ_TOSTRING)True_ToDebugString,
        NULL,			// True_Enable,
        NULL,			// True_Disable,
        (P_OBJ_ASSIGN)True_Assign,
        (P_OBJ_COMPARE)True_Compare,
        (P_OBJ_PTR)True_Copy,
        NULL, 			// (P_OBJ_PTR)True_DeepCopy,
        NULL 			// (P_OBJ_HASH)True_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //True_IsEnabled,
 
};



static
const
OBJ_INFO        True_Info = {
    "True",
    "True",
    (OBJ_DATA *)&True_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&True_Vtbl,
    sizeof(TRUE_DATA)
};





