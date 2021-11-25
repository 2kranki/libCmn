// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Appl'
//	Generated 01/31/2020 13:16:48


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




#define			APPL_OBJECT_C	    1
#include        <Appl_internal.h>
#ifdef  APPL_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Appl_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  APPL_SINGLETON
    volatile
    APPL_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ApplClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Appl_Info;            // Forward Reference




static
bool            ApplClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_APPL_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Appl_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		ApplClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_APPL_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
APPL_CLASS_VTBL    class_Vtbl = {
    {
        &Appl_Info,
        ApplClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Appl_Class,
        ApplClass_WhoAmI,
        (P_OBJ_QUERYINFO)ApplClass_QueryInfo,
        NULL                        // ApplClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

APPL_CLASS_DATA  Appl_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(APPL_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  APPL_SINGLETON
APPL_DATA *     Appl_getSingleton (
    void
)
{
    return (OBJ_ID)(Appl_ClassObj.pSingleton);
}


bool            Appl_setSingleton (
    APPL_DATA       *pValue
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
    if (Appl_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Appl_ClassObj.pSingleton));
    }
    Appl_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



APPL_DATA *     Appl_Shared (
    void
)
{
    APPL_DATA       *this = (OBJ_ID)(Appl_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Appl_New( );
        Appl_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Appl_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Appl_SharedReset (
    void
)
{
    APPL_DATA       *this = (OBJ_ID)(Appl_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Appl_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ApplClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    APPL_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(APPL_DATA);
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
                        return (void *)&Appl_Info;
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
                        return Appl_New;
                    }
                    break;
                    
#ifdef  APPL_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Appl_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Appl_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ApplClass_WhoAmI;
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
bool            Appl_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_APPL == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Appl_Class())->pClassSuperObject;
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
void            Appl_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Appl_Class (
    void
)
{
    return (OBJ_ID)&Appl_ClassObj;
}


static
uint16_t		Appl_WhoAmI (
    void
)
{
    return OBJ_IDENT_APPL;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
APPL_VTBL     Appl_Vtbl = {
    {
        &Appl_Info,
        Appl_IsKindOf,
#ifdef  APPL_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Appl_Dealloc,
        Appl_Class,
        Appl_WhoAmI,
        (P_OBJ_QUERYINFO)Appl_QueryInfo,
        (P_OBJ_TOSTRING)Appl_ToDebugString,
        NULL,			// Appl_Enable,
        NULL,			// Appl_Disable,
        NULL,			// (P_OBJ_ASSIGN)Appl_Assign,
        NULL,			// (P_OBJ_COMPARE)Appl_Compare,
        NULL, 			// (P_OBJ_PTR)Appl_Copy,
        NULL, 			// (P_OBJ_PTR)Appl_DeepCopy,
        NULL 			// (P_OBJ_HASH)Appl_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    (void *)Appl_getDebug,
    (void *)Appl_getForce,
    (void *)Appl_getQuiet,
    (void *)Appl_getVerbose,
    (void *)Appl_Exit,

};



static
const
OBJ_INFO        Appl_Info = {
    "Appl",
    "Application Base Object",
    (OBJ_DATA *)&Appl_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Appl_Vtbl,
    sizeof(APPL_DATA)
};





