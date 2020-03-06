// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Scanner'
//	Generated 03/04/2020 21:17:29


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




#define			SCANNER_OBJECT_C	    1
#include        <Scanner_internal.h>
#ifdef  SCANNER_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Scanner_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SCANNER_SINGLETON
    volatile
    SCANNER_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ScannerClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Scanner_Info;            // Forward Reference




static
bool            ScannerClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SCANNER_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Scanner_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		ScannerClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SCANNER_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SCANNER_CLASS_VTBL    class_Vtbl = {
    {
        &Scanner_Info,
        ScannerClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Scanner_Class,
        ScannerClass_WhoAmI,
        (P_OBJ_QUERYINFO)ScannerClass_QueryInfo,
        NULL                        // ScannerClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SCANNER_CLASS_DATA  Scanner_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SCANNER_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SCANNER_SINGLETON
SCANNER_DATA *     Scanner_getSingleton (
    void
)
{
    return (OBJ_ID)(Scanner_ClassObj.pSingleton);
}


bool            Scanner_setSingleton (
    SCANNER_DATA       *pValue
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
    if (Scanner_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Scanner_ClassObj.pSingleton));
    }
    Scanner_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SCANNER_DATA *     Scanner_Shared (
    void
)
{
    SCANNER_DATA       *this = (OBJ_ID)(Scanner_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Scanner_New( );
        Scanner_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Scanner_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Scanner_SharedReset (
    void
)
{
    SCANNER_DATA       *this = (OBJ_ID)(Scanner_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Scanner_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ScannerClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SCANNER_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SCANNER_DATA);
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
                        return (void *)&Scanner_Info;
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
                        return Scanner_New;
                    }
                    break;
                    
#ifdef  SCANNER_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Scanner_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Scanner_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ScannerClass_WhoAmI;
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
bool            Scanner_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SCANNER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Scanner_Class())->pClassSuperObject;
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
void            Scanner_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Scanner_Class (
    void
)
{
    return (OBJ_ID)&Scanner_ClassObj;
}


static
uint16_t		Scanner_WhoAmI (
    void
)
{
    return OBJ_IDENT_SCANNER;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
SCANNER_VTBL     Scanner_Vtbl = {
    {
        &Scanner_Info,
        Scanner_IsKindOf,
#ifdef  SCANNER_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Scanner_Dealloc,
        Scanner_Class,
        Scanner_WhoAmI,
        (P_OBJ_QUERYINFO)Scanner_QueryInfo,
        (P_OBJ_TOSTRING)Scanner_ToDebugString,
        NULL,			// Scanner_Enable,
        NULL,			// Scanner_Disable,
        (P_OBJ_ASSIGN)Scanner_Assign,
        (P_OBJ_COMPARE)Scanner_Compare,
        (P_OBJ_PTR)Scanner_Copy,
        NULL, 			// (P_OBJ_PTR)Scanner_DeepCopy,
        (P_OBJ_HASH)Scanner_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Scanner_IsEnabled,
 
};



static
const
OBJ_INFO        Scanner_Info = {
    "Scanner",
    "String Scanner",
    (OBJ_DATA *)&Scanner_ClassObj,
    (OBJ_DATA *)&W32StrC_ClassObj,
    (OBJ_IUNKNOWN *)&Scanner_Vtbl,
    sizeof(SCANNER_DATA)
};





