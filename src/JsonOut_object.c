// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'JsonOut'
//	Generated 01/25/2020 21:31:26


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




#define			JSONOUT_OBJECT_C	    1
#include        <JsonOut_internal.h>
#ifdef  JSONOUT_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct JsonOut_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  JSONOUT_SINGLETON
    volatile
    JSONOUT_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          JsonOutClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        JsonOut_Info;            // Forward Reference




static
bool            JsonOutClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_JSONOUT_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(JsonOut_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		JsonOutClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_JSONOUT_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
JSONOUT_CLASS_VTBL    class_Vtbl = {
    {
        &JsonOut_Info,
        JsonOutClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        JsonOut_Class,
        JsonOutClass_WhoAmI,
        (P_OBJ_QUERYINFO)JsonOutClass_QueryInfo,
        NULL                        // JsonOutClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

JSONOUT_CLASS_DATA  JsonOut_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(JSONOUT_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  JSONOUT_SINGLETON
JSONOUT_DATA *     JsonOut_getSingleton (
    void
)
{
    return (OBJ_ID)(JsonOut_ClassObj.pSingleton);
}


bool            JsonOut_setSingleton (
    JSONOUT_DATA       *pValue
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
    if (JsonOut_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(JsonOut_ClassObj.pSingleton));
    }
    JsonOut_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



JSONOUT_DATA *     JsonOut_Shared (
    void
)
{
    JSONOUT_DATA       *this = (OBJ_ID)(JsonOut_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = JsonOut_New( );
        JsonOut_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // JsonOut_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            JsonOut_SharedReset (
    void
)
{
    JSONOUT_DATA       *this = (OBJ_ID)(JsonOut_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        JsonOut_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          JsonOutClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    JSONOUT_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(JSONOUT_DATA);
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
                        return (void *)&JsonOut_Info;
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
                        return JsonOut_New;
                    }
                    break;
                    
#ifdef  JSONOUT_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return JsonOut_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return JsonOut_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return JsonOutClass_WhoAmI;
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
bool            JsonOut_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_JSONOUT == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(JsonOut_Class())->pClassSuperObject;
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
void            JsonOut_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          JsonOut_Class (
    void
)
{
    return (OBJ_ID)&JsonOut_ClassObj;
}


static
uint16_t		JsonOut_WhoAmI (
    void
)
{
    return OBJ_IDENT_JSONOUT;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
JSONOUT_VTBL     JsonOut_Vtbl = {
    {
        &JsonOut_Info,
        JsonOut_IsKindOf,
#ifdef  JSONOUT_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        JsonOut_Dealloc,
        JsonOut_Class,
        JsonOut_WhoAmI,
        (P_OBJ_QUERYINFO)JsonOut_QueryInfo,
        (P_OBJ_TOSTRING)JsonOut_ToDebugString,
        NULL,			// JsonOut_Enable,
        NULL,			// JsonOut_Disable,
        NULL,			// (P_OBJ_ASSIGN)JsonOut_Assign,
        NULL,			// (P_OBJ_COMPARE)JsonOut_Compare,
        NULL, 			// (P_OBJ_PTR)JsonOut_Copy,
        NULL, 			// (P_OBJ_PTR)JsonOut_DeepCopy,
        NULL 			// (P_OBJ_HASH)JsonOut_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //JsonOut_IsEnabled,
 
};



static
const
OBJ_INFO        JsonOut_Info = {
    "JsonOut",
    "JSON Standardized Output",
    (OBJ_DATA *)&JsonOut_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&JsonOut_Vtbl,
    sizeof(JSONOUT_DATA)
};





