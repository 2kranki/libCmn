// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'ObjCb'
//	Generated 02/21/2020 14:01:14


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




#define			OBJCB_OBJECT_C	    1
#include        <ObjCb_internal.h>
#ifdef  OBJCB_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ObjCb_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OBJCB_SINGLETON
    volatile
    OBJCB_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ObjCbClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ObjCb_Info;            // Forward Reference




static
bool            ObjCbClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OBJCB_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(ObjCb_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		ObjCbClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJCB_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OBJCB_CLASS_VTBL    class_Vtbl = {
    {
        &ObjCb_Info,
        ObjCbClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ObjCb_Class,
        ObjCbClass_WhoAmI,
        (P_OBJ_QUERYINFO)ObjCbClass_QueryInfo,
        NULL                        // ObjCbClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

OBJCB_CLASS_DATA  ObjCb_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OBJCB_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OBJCB_SINGLETON
OBJCB_DATA *     ObjCb_getSingleton (
    void
)
{
    return (OBJ_ID)(ObjCb_ClassObj.pSingleton);
}


bool            ObjCb_setSingleton (
    OBJCB_DATA       *pValue
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
    if (ObjCb_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ObjCb_ClassObj.pSingleton));
    }
    ObjCb_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OBJCB_DATA *     ObjCb_Shared (
    void
)
{
    OBJCB_DATA       *this = (OBJ_ID)(ObjCb_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ObjCb_New( );
        ObjCb_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ObjCb_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ObjCb_SharedReset (
    void
)
{
    OBJCB_DATA       *this = (OBJ_ID)(ObjCb_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        ObjCb_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ObjCbClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OBJCB_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJCB_DATA);
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
                        return (void *)&ObjCb_Info;
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
                        return ObjCb_New;
                    }
                    break;
                    
#ifdef  OBJCB_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return ObjCb_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return ObjCb_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ObjCbClass_WhoAmI;
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
bool            ObjCb_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OBJCB == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(ObjCb_Class())->pClassSuperObject;
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
void            ObjCb_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ObjCb_Class (
    void
)
{
    return (OBJ_ID)&ObjCb_ClassObj;
}


static
uint16_t		ObjCb_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJCB;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
OBJCB_VTBL     ObjCb_Vtbl = {
    {
        &ObjCb_Info,
        ObjCb_IsKindOf,
#ifdef  OBJCB_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        ObjCb_Dealloc,
        ObjCb_Class,
        ObjCb_WhoAmI,
        (P_OBJ_QUERYINFO)ObjCb_QueryInfo,
        (P_OBJ_TOSTRING)ObjCb_ToDebugString,
        NULL,			// ObjCb_Enable,
        NULL,			// ObjCb_Disable,
        NULL,			// (P_OBJ_ASSIGN)ObjCb_Assign,
        NULL,			// (P_OBJ_COMPARE)ObjCb_Compare,
        NULL, 			// (P_OBJ_PTR)ObjCb_Copy,
        NULL, 			// (P_OBJ_PTR)ObjCb_DeepCopy,
        NULL 			// (P_OBJ_HASH)ObjCb_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ObjCb_IsEnabled,
 
};



static
const
OBJ_INFO        ObjCb_Info = {
    "ObjCb",
    "Posix Protected Object Circular Buffer",
    (OBJ_DATA *)&ObjCb_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&ObjCb_Vtbl,
    sizeof(OBJCB_DATA)
};





