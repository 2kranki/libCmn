// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'ObjHash'
//	Generated 02/02/2020 09:55:43


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




#define			OBJHASH_OBJECT_C	    1
#include        <ObjHash_internal.h>
#ifdef  OBJHASH_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ObjHash_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OBJHASH_SINGLETON
    volatile
    OBJHASH_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ObjHashClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ObjHash_Info;            // Forward Reference




static
bool            ObjHashClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OBJHASH_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(ObjHash_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		ObjHashClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJHASH_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OBJHASH_CLASS_VTBL    class_Vtbl = {
    {
        &ObjHash_Info,
        ObjHashClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ObjHash_Class,
        ObjHashClass_WhoAmI,
        (P_OBJ_QUERYINFO)ObjHashClass_QueryInfo,
        NULL                        // ObjHashClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

OBJHASH_CLASS_DATA  ObjHash_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OBJHASH_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OBJHASH_SINGLETON
OBJHASH_DATA *     ObjHash_getSingleton (
    void
)
{
    return (OBJ_ID)(ObjHash_ClassObj.pSingleton);
}


bool            ObjHash_setSingleton (
    OBJHASH_DATA       *pValue
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
    if (ObjHash_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ObjHash_ClassObj.pSingleton));
    }
    ObjHash_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OBJHASH_DATA *     ObjHash_Shared (
    void
)
{
    OBJHASH_DATA       *this = (OBJ_ID)(ObjHash_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ObjHash_New( );
        ObjHash_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ObjHash_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ObjHash_SharedReset (
    void
)
{
    OBJHASH_DATA       *this = (OBJ_ID)(ObjHash_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        ObjHash_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ObjHashClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OBJHASH_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJHASH_DATA);
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
                        return (void *)&ObjHash_Info;
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
                        return ObjHash_New;
                    }
                    break;
                    
#ifdef  OBJHASH_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return ObjHash_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return ObjHash_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ObjHashClass_WhoAmI;
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
bool            ObjHash_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OBJHASH == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(ObjHash_Class())->pClassSuperObject;
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
void            ObjHash_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ObjHash_Class (
    void
)
{
    return (OBJ_ID)&ObjHash_ClassObj;
}


static
uint16_t		ObjHash_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJHASH;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
OBJHASH_VTBL     ObjHash_Vtbl = {
    {
        &ObjHash_Info,
        ObjHash_IsKindOf,
#ifdef  OBJHASH_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        ObjHash_Dealloc,
        ObjHash_Class,
        ObjHash_WhoAmI,
        (P_OBJ_QUERYINFO)ObjHash_QueryInfo,
        (P_OBJ_TOSTRING)ObjHash_ToDebugString,
        NULL,			// ObjHash_Enable,
        NULL,			// ObjHash_Disable,
        NULL,			// (P_OBJ_ASSIGN)ObjHash_Assign,
        NULL,			// (P_OBJ_COMPARE)ObjHash_Compare,
        NULL, 			// (P_OBJ_PTR)ObjHash_Copy,
        NULL, 			// (P_OBJ_PTR)ObjHash_DeepCopy,
        NULL 			// (P_OBJ_HASH)ObjHash_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ObjHash_IsEnabled,
 
};



static
const
OBJ_INFO        ObjHash_Info = {
    "ObjHash",
    "Hash Table of Objects",
    (OBJ_DATA *)&ObjHash_ClassObj,
    (OBJ_DATA *)&Blocks_ClassObj,
    (OBJ_IUNKNOWN *)&ObjHash_Vtbl,
    sizeof(OBJHASH_DATA)
};





