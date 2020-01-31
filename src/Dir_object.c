// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Dir'
//	Generated 01/31/2020 10:23:30


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




#define			DIR_OBJECT_C	    1
#include        <Dir_internal.h>
#ifdef  DIR_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Dir_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  DIR_SINGLETON
    volatile
    DIR_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          DirClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Dir_Info;            // Forward Reference




static
bool            DirClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_DIR_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Dir_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		DirClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_DIR_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
DIR_CLASS_VTBL    class_Vtbl = {
    {
        &Dir_Info,
        DirClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Dir_Class,
        DirClass_WhoAmI,
        (P_OBJ_QUERYINFO)DirClass_QueryInfo,
        NULL                        // DirClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

DIR_CLASS_DATA  Dir_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(DIR_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  DIR_SINGLETON
DIR_DATA *     Dir_getSingleton (
    void
)
{
    return (OBJ_ID)(Dir_ClassObj.pSingleton);
}


bool            Dir_setSingleton (
    DIR_DATA       *pValue
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
    if (Dir_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Dir_ClassObj.pSingleton));
    }
    Dir_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



DIR_DATA *     Dir_Shared (
    void
)
{
    DIR_DATA       *this = (OBJ_ID)(Dir_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Dir_New( );
        Dir_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Dir_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Dir_SharedReset (
    void
)
{
    DIR_DATA       *this = (OBJ_ID)(Dir_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Dir_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          DirClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    DIR_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(DIR_DATA);
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
                        return (void *)&Dir_Info;
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
                        return Dir_New;
                    }
                    break;
                    
#ifdef  DIR_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Dir_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Dir_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return DirClass_WhoAmI;
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
bool            Dir_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_DIR == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Dir_Class())->pClassSuperObject;
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
void            Dir_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Dir_Class (
    void
)
{
    return (OBJ_ID)&Dir_ClassObj;
}


static
uint16_t		Dir_WhoAmI (
    void
)
{
    return OBJ_IDENT_DIR;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
DIR_VTBL     Dir_Vtbl = {
    {
        &Dir_Info,
        Dir_IsKindOf,
#ifdef  DIR_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Dir_Dealloc,
        Dir_Class,
        Dir_WhoAmI,
        (P_OBJ_QUERYINFO)Dir_QueryInfo,
        (P_OBJ_TOSTRING)Dir_ToDebugString,
        NULL,			// Dir_Enable,
        NULL,			// Dir_Disable,
        NULL,			// (P_OBJ_ASSIGN)Dir_Assign,
        NULL,			// (P_OBJ_COMPARE)Dir_Compare,
        NULL, 			// (P_OBJ_PTR)Dir_Copy,
        NULL, 			// (P_OBJ_PTR)Dir_DeepCopy,
        NULL 			// (P_OBJ_HASH)Dir_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Dir_IsEnabled,
 
};



static
const
OBJ_INFO        Dir_Info = {
    "Dir",
    "Disk Directory Entries",
    (OBJ_DATA *)&Dir_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Dir_Vtbl,
    sizeof(DIR_DATA)
};





