// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Path'
//	Generated 01/29/2020 13:19:38


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




#define			PATH_OBJECT_C	    1
#include        <Path_internal.h>
#ifdef  PATH_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Path_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  PATH_SINGLETON
    volatile
    PATH_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          PathClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Path_Info;            // Forward Reference




static
bool            PathClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_PATH_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Path_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		PathClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_PATH_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
PATH_CLASS_VTBL    class_Vtbl = {
    {
        &Path_Info,
        PathClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Path_Class,
        PathClass_WhoAmI,
        (P_OBJ_QUERYINFO)PathClass_QueryInfo,
        NULL                        // PathClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

PATH_CLASS_DATA  Path_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(PATH_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  PATH_SINGLETON
PATH_DATA *     Path_getSingleton (
    void
)
{
    return (OBJ_ID)(Path_ClassObj.pSingleton);
}


bool            Path_setSingleton (
    PATH_DATA       *pValue
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
    if (Path_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Path_ClassObj.pSingleton));
    }
    Path_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



PATH_DATA *     Path_Shared (
    void
)
{
    PATH_DATA       *this = (OBJ_ID)(Path_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Path_New( );
        Path_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Path_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Path_SharedReset (
    void
)
{
    PATH_DATA       *this = (OBJ_ID)(Path_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Path_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          PathClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PATH_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PATH_DATA);
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
                        return (void *)&Path_Info;
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
                        return Path_New;
                    }
                    break;
                    
#ifdef  PATH_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Path_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Path_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return PathClass_WhoAmI;
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
bool            Path_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_PATH == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Path_Class())->pClassSuperObject;
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
void            Path_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Path_Class (
    void
)
{
    return (OBJ_ID)&Path_ClassObj;
}


static
uint16_t		Path_WhoAmI (
    void
)
{
    return OBJ_IDENT_PATH;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
PATH_VTBL     Path_Vtbl = {
    {
        &Path_Info,
        Path_IsKindOf,
#ifdef  PATH_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Path_Dealloc,
        Path_Class,
        Path_WhoAmI,
        (P_OBJ_QUERYINFO)Path_QueryInfo,
        (P_OBJ_TOSTRING)Path_ToDebugString,
        NULL,			// Path_Enable,
        NULL,			// Path_Disable,
        (P_OBJ_ASSIGN)Path_Assign,
        (P_OBJ_COMPARE)Path_Compare,
        (P_OBJ_PTR)Path_Copy,
        NULL, 			// (P_OBJ_PTR)Path_DeepCopy,
        NULL 			// (P_OBJ_HASH)Path_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Path_IsEnabled,
 
};



static
const
OBJ_INFO        Path_Info = {
    "Path",
    "Disk Directory or File Path",
    (OBJ_DATA *)&Path_ClassObj,
    (OBJ_DATA *)&AStr_ClassObj,
    (OBJ_IUNKNOWN *)&Path_Vtbl,
    sizeof(PATH_DATA)
};





