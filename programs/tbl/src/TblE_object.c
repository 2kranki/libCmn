// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'TblE'
//	Generated 02/22/2020 22:19:59


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




#define			TBLE_OBJECT_C	    1
#include        <TblE_internal.h>
#ifdef  TBLE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct TblE_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TBLE_SINGLETON
    volatile
    TBLE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          TblEClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        TblE_Info;            // Forward Reference




static
bool            TblEClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_TBLE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(TblE_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		TblEClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_TBLE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TBLE_CLASS_VTBL    class_Vtbl = {
    {
        &TblE_Info,
        TblEClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        TblE_Class,
        TblEClass_WhoAmI,
        (P_OBJ_QUERYINFO)TblEClass_QueryInfo,
        NULL                        // TblEClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

TBLE_CLASS_DATA  TblE_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TBLE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TBLE_SINGLETON
TBLE_DATA *     TblE_getSingleton (
    void
)
{
    return (OBJ_ID)(TblE_ClassObj.pSingleton);
}


bool            TblE_setSingleton (
    TBLE_DATA       *pValue
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
    if (TblE_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(TblE_ClassObj.pSingleton));
    }
    TblE_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TBLE_DATA *     TblE_Shared (
    void
)
{
    TBLE_DATA       *this = (OBJ_ID)(TblE_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = TblE_New( );
        TblE_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // TblE_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            TblE_SharedReset (
    void
)
{
    TBLE_DATA       *this = (OBJ_ID)(TblE_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        TblE_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          TblEClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TBLE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TBLE_DATA);
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
                        return (void *)&TblE_Info;
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
                        return TblE_New;
                    }
                    break;
                    
#ifdef  TBLE_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return TblE_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return TblE_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return TblEClass_WhoAmI;
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
bool            TblE_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_TBLE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(TblE_Class())->pClassSuperObject;
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
void            TblE_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          TblE_Class (
    void
)
{
    return (OBJ_ID)&TblE_ClassObj;
}


static
uint16_t		TblE_WhoAmI (
    void
)
{
    return OBJ_IDENT_TBLE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
TBLE_VTBL     TblE_Vtbl = {
    {
        &TblE_Info,
        TblE_IsKindOf,
#ifdef  TBLE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        TblE_Dealloc,
        TblE_Class,
        TblE_WhoAmI,
        (P_OBJ_QUERYINFO)TblE_QueryInfo,
        (P_OBJ_TOSTRING)TblE_ToDebugString,
        NULL,			// TblE_Enable,
        NULL,			// TblE_Disable,
        NULL,			// (P_OBJ_ASSIGN)TblE_Assign,
        NULL,			// (P_OBJ_COMPARE)TblE_Compare,
        NULL, 			// (P_OBJ_PTR)TblE_Copy,
        NULL, 			// (P_OBJ_PTR)TblE_DeepCopy,
        NULL 			// (P_OBJ_HASH)TblE_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //TblE_IsEnabled,
 
};



static
const
OBJ_INFO        TblE_Info = {
    "TblE",
    "TBL Machine Emulator",
    (OBJ_DATA *)&TblE_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&TblE_Vtbl,
    sizeof(TBLE_DATA)
};





