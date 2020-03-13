// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'False'
//	Generated 03/11/2020 10:01:47


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




#define			FALSE_OBJECT_C	    1
#include        <False_internal.h>
#ifdef  FALSE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct False_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  FALSE_SINGLETON
    volatile
    FALSE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          FalseClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        False_Info;            // Forward Reference




static
bool            FalseClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_FALSE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(False_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		FalseClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_FALSE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
FALSE_CLASS_VTBL    class_Vtbl = {
    {
        &False_Info,
        FalseClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        False_Class,
        FalseClass_WhoAmI,
        (P_OBJ_QUERYINFO)FalseClass_QueryInfo,
        NULL                        // FalseClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

FALSE_CLASS_DATA  False_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(FALSE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  FALSE_SINGLETON
extern
const
FALSE_VTBL       False_VtblShared;


FALSE_DATA *     False_getSingleton (
    void
)
{
    return (OBJ_ID)(False_ClassObj.pSingleton);
}


bool            False_setSingleton (
    FALSE_DATA       *pValue
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
    if (False_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(False_ClassObj.pSingleton));
    }
    False_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



FALSE_DATA *     False_Shared (
    void
)
{
    FALSE_DATA       *this = (OBJ_ID)(False_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = False_New( );
        obj_setVtbl(this, (void *)&False_VtblShared);
        False_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // False_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            False_SharedReset (
    void
)
{
    FALSE_DATA       *this = (OBJ_ID)(False_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&False_Vtbl);
        obj_Release(this);
        False_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          FalseClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    FALSE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(FALSE_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&False_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&False_Info.pClassSuperObject;
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
                        return False_New;
                    }
                    break;
                    
				case 'P':
#ifdef  FALSE_JSON_SUPPORT
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return False_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return False_ParseJsonObject;
					}
#endif
					break;

				case 'T':
#ifdef  FALSE_JSON_SUPPORT
					if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
						return False_ToJsonFields;
					}
					if (str_Compare("ToJson", (char *)pStr) == 0) {
						return False_ToJson;
					}
#endif
					break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return FalseClass_WhoAmI;
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
bool            False_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_FALSE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(False_Class())->pClassSuperObject;
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
void            False_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          False_Class (
    void
)
{
    return (OBJ_ID)&False_ClassObj;
}


static
uint16_t		False_WhoAmI (
    void
)
{
    return OBJ_IDENT_FALSE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  FALSE_SINGLETON
const
FALSE_VTBL     False_VtblShared = {
    {
        &False_Info,
        False_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        False_Dealloc,
        False_Class,
        False_WhoAmI,
        (P_OBJ_QUERYINFO)False_QueryInfo,
        (P_OBJ_TOSTRING)False_ToDebugString,
        NULL,            // False_Enable,
        NULL,            // False_Disable,
        (P_OBJ_ASSIGN)False_Assign,
        (P_OBJ_COMPARE)False_Compare,
        (P_OBJ_PTR)False_Copy,
        NULL,             // (P_OBJ_PTR)False_DeepCopy,
        NULL             // (P_OBJ_HASH)False_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //False_IsEnabled,

};
#endif


const
FALSE_VTBL     False_Vtbl = {
    {
        &False_Info,
        False_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        False_Dealloc,
        False_Class,
        False_WhoAmI,
        (P_OBJ_QUERYINFO)False_QueryInfo,
        (P_OBJ_TOSTRING)False_ToDebugString,
        NULL,			// False_Enable,
        NULL,			// False_Disable,
        (P_OBJ_ASSIGN)False_Assign,
        (P_OBJ_COMPARE)False_Compare,
        (P_OBJ_PTR)False_Copy,
        NULL, 			// (P_OBJ_PTR)False_DeepCopy,
        NULL 			// (P_OBJ_HASH)False_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //False_IsEnabled,
 
};



static
const
OBJ_INFO        False_Info = {
    "False",
    "False",
    (OBJ_DATA *)&False_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&False_Vtbl,
    sizeof(FALSE_DATA)
};





