// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'ObjBT'
//	Generated 03/01/2020 21:30:29


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




#define			OBJBT_OBJECT_C	    1
#include        <ObjBT_internal.h>
#ifdef  OBJBT_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ObjBT_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OBJBT_SINGLETON
    volatile
    OBJBT_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ObjBTClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ObjBT_Info;            // Forward Reference




static
bool            ObjBTClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OBJBT_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(ObjBT_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		ObjBTClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJBT_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OBJBT_CLASS_VTBL    class_Vtbl = {
    {
        &ObjBT_Info,
        ObjBTClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ObjBT_Class,
        ObjBTClass_WhoAmI,
        (P_OBJ_QUERYINFO)ObjBTClass_QueryInfo,
        NULL                        // ObjBTClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

OBJBT_CLASS_DATA  ObjBT_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OBJBT_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OBJBT_SINGLETON
OBJBT_DATA *     ObjBT_getSingleton (
    void
)
{
    return (OBJ_ID)(ObjBT_ClassObj.pSingleton);
}


bool            ObjBT_setSingleton (
    OBJBT_DATA       *pValue
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
    if (ObjBT_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ObjBT_ClassObj.pSingleton));
    }
    ObjBT_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OBJBT_DATA *     ObjBT_Shared (
    void
)
{
    OBJBT_DATA       *this = (OBJ_ID)(ObjBT_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ObjBT_New( );
        ObjBT_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ObjBT_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ObjBT_SharedReset (
    void
)
{
    OBJBT_DATA       *this = (OBJ_ID)(ObjBT_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        ObjBT_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ObjBTClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OBJBT_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJBT_DATA);
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
                        return (void *)&ObjBT_Info;
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
                        return ObjBT_New;
                    }
                    break;
                    
#ifdef  OBJBT_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return ObjBT_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return ObjBT_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ObjBTClass_WhoAmI;
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
bool            ObjBT_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OBJBT == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(ObjBT_Class())->pClassSuperObject;
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
void            ObjBT_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ObjBT_Class (
    void
)
{
    return (OBJ_ID)&ObjBT_ClassObj;
}


static
uint16_t		ObjBT_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJBT;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
OBJBT_VTBL     ObjBT_Vtbl = {
    {
        &ObjBT_Info,
        ObjBT_IsKindOf,
#ifdef  OBJBT_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        ObjBT_Dealloc,
        ObjBT_Class,
        ObjBT_WhoAmI,
        (P_OBJ_QUERYINFO)ObjBT_QueryInfo,
        (P_OBJ_TOSTRING)ObjBT_ToDebugString,
        NULL,			// ObjBT_Enable,
        NULL,			// ObjBT_Disable,
        (P_OBJ_ASSIGN)ObjBT_Assign,
        NULL,           // (P_OBJ_COMPARE)ObjBT_Compare,
        (P_OBJ_PTR)ObjBT_Copy,
        NULL, 			// (P_OBJ_PTR)ObjBT_DeepCopy,
        NULL 			// (P_OBJ_HASH)ObjBT_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ObjBT_IsEnabled,
 
};



static
const
OBJ_INFO        ObjBT_Info = {
    "ObjBT",
    "Balanced Binary Tree for Objects",
    (OBJ_DATA *)&ObjBT_ClassObj,
    (OBJ_DATA *)&Blocks_ClassObj,
    (OBJ_IUNKNOWN *)&ObjBT_Vtbl,
    sizeof(OBJBT_DATA)
};





