// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'JsonPP'
//	Generated 01/31/2020 23:01:53


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




#define			JSONPP_OBJECT_C	    1
#include        <JsonPP_internal.h>
#ifdef  JSONPP_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct JsonPP_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  JSONPP_SINGLETON
    volatile
    JSONPP_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          JsonPPClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        JsonPP_Info;            // Forward Reference




static
bool            JsonPPClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_JSONPP_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(JsonPP_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		JsonPPClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_JSONPP_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
JSONPP_CLASS_VTBL    class_Vtbl = {
    {
        &JsonPP_Info,
        JsonPPClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        JsonPP_Class,
        JsonPPClass_WhoAmI,
        (P_OBJ_QUERYINFO)JsonPPClass_QueryInfo,
        NULL                        // JsonPPClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

JSONPP_CLASS_DATA  JsonPP_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(JSONPP_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  JSONPP_SINGLETON
JSONPP_DATA *     JsonPP_getSingleton (
    void
)
{
    return (OBJ_ID)(JsonPP_ClassObj.pSingleton);
}


bool            JsonPP_setSingleton (
    JSONPP_DATA       *pValue
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
    if (JsonPP_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(JsonPP_ClassObj.pSingleton));
    }
    JsonPP_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



JSONPP_DATA *     JsonPP_Shared (
    void
)
{
    JSONPP_DATA       *this = (OBJ_ID)(JsonPP_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = JsonPP_New( );
        JsonPP_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // JsonPP_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            JsonPP_SharedReset (
    void
)
{
    JSONPP_DATA       *this = (OBJ_ID)(JsonPP_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        JsonPP_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          JsonPPClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    JSONPP_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(JSONPP_DATA);
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
                        return (void *)&JsonPP_Info;
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
                        return JsonPP_New;
                    }
                    break;
                    
#ifdef  JSONPP_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return JsonPP_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return JsonPP_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return JsonPPClass_WhoAmI;
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
bool            JsonPP_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_JSONPP == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(JsonPP_Class())->pClassSuperObject;
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
void            JsonPP_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          JsonPP_Class (
    void
)
{
    return (OBJ_ID)&JsonPP_ClassObj;
}


static
uint16_t		JsonPP_WhoAmI (
    void
)
{
    return OBJ_IDENT_JSONPP;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
JSONPP_VTBL     JsonPP_Vtbl = {
    {
        &JsonPP_Info,
        JsonPP_IsKindOf,
#ifdef  JSONPP_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        JsonPP_Dealloc,
        JsonPP_Class,
        JsonPP_WhoAmI,
        (P_OBJ_QUERYINFO)JsonPP_QueryInfo,
        (P_OBJ_TOSTRING)JsonPP_ToDebugString,
        NULL,			// JsonPP_Enable,
        NULL,			// JsonPP_Disable,
        NULL,			// (P_OBJ_ASSIGN)JsonPP_Assign,
        NULL,			// (P_OBJ_COMPARE)JsonPP_Compare,
        NULL, 			// (P_OBJ_PTR)JsonPP_Copy,
        NULL, 			// (P_OBJ_PTR)JsonPP_DeepCopy,
        NULL 			// (P_OBJ_HASH)JsonPP_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //JsonPP_IsEnabled,
 
};



static
const
OBJ_INFO        JsonPP_Info = {
    "JsonPP",
    "JsonPP",	// <-- Fill in description
    (OBJ_DATA *)&JsonPP_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&JsonPP_Vtbl,
    sizeof(JSONPP_DATA)
};
#warning -- adjust super class object in Info above 
//			if object inherits from another class





