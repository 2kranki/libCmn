// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'DirEntry'
//	Generated 01/28/2020 23:56:00


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




#define			DIRENTRY_OBJECT_C	    1
#include        <DirEntry_internal.h>
#ifdef  DIRENTRY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct DirEntry_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  DIRENTRY_SINGLETON
    volatile
    DIRENTRY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          DirEntryClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        DirEntry_Info;            // Forward Reference




static
bool            DirEntryClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_DIRENTRY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(DirEntry_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		DirEntryClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_DIRENTRY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
DIRENTRY_CLASS_VTBL    class_Vtbl = {
    {
        &DirEntry_Info,
        DirEntryClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        DirEntry_Class,
        DirEntryClass_WhoAmI,
        (P_OBJ_QUERYINFO)DirEntryClass_QueryInfo,
        NULL                        // DirEntryClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

DIRENTRY_CLASS_DATA  DirEntry_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(DIRENTRY_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  DIRENTRY_SINGLETON
DIRENTRY_DATA *     DirEntry_getSingleton (
    void
)
{
    return (OBJ_ID)(DirEntry_ClassObj.pSingleton);
}


bool            DirEntry_setSingleton (
    DIRENTRY_DATA       *pValue
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
    if (DirEntry_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(DirEntry_ClassObj.pSingleton));
    }
    DirEntry_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



DIRENTRY_DATA *     DirEntry_Shared (
    void
)
{
    DIRENTRY_DATA       *this = (OBJ_ID)(DirEntry_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = DirEntry_New( );
        DirEntry_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // DirEntry_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            DirEntry_SharedReset (
    void
)
{
    DIRENTRY_DATA       *this = (OBJ_ID)(DirEntry_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        DirEntry_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          DirEntryClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    DIRENTRY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(DIRENTRY_DATA);
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
                        return (void *)&DirEntry_Info;
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
                        return DirEntry_New;
                    }
                    break;
                    
#ifdef  DIRENTRY_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return DirEntry_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return DirEntry_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return DirEntryClass_WhoAmI;
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
bool            DirEntry_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_DIRENTRY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(DirEntry_Class())->pClassSuperObject;
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
void            DirEntry_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          DirEntry_Class (
    void
)
{
    return (OBJ_ID)&DirEntry_ClassObj;
}


static
uint16_t		DirEntry_WhoAmI (
    void
)
{
    return OBJ_IDENT_DIRENTRY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
DIRENTRY_VTBL     DirEntry_Vtbl = {
    {
        &DirEntry_Info,
        DirEntry_IsKindOf,
#ifdef  DIRENTRY_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        DirEntry_Dealloc,
        DirEntry_Class,
        DirEntry_WhoAmI,
        (P_OBJ_QUERYINFO)DirEntry_QueryInfo,
        (P_OBJ_TOSTRING)DirEntry_ToDebugString,
        NULL,			// DirEntry_Enable,
        NULL,			// DirEntry_Disable,
        NULL,			// (P_OBJ_ASSIGN)DirEntry_Assign,
        NULL,			// (P_OBJ_COMPARE)DirEntry_Compare,
        NULL, 			// (P_OBJ_PTR)DirEntry_Copy,
        NULL, 			// (P_OBJ_PTR)DirEntry_DeepCopy,
        NULL 			// (P_OBJ_HASH)DirEntry_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //DirEntry_IsEnabled,
 
};



static
const
OBJ_INFO        DirEntry_Info = {
    "DirEntry",
    "Disk Directory Entry",
    (OBJ_DATA *)&DirEntry_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&DirEntry_Vtbl,
    sizeof(DIRENTRY_DATA)
};





