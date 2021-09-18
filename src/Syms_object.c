// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Syms'
//	Generated 02/22/2020 20:18:16


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




#define			SYMS_OBJECT_C	    1
#include        <Syms_internal.h>
#ifdef  SYMS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Syms_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SYMS_SINGLETON
    volatile
    SYMS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SymsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Syms_Info;            // Forward Reference




static
bool            SymsClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SYMS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Syms_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		SymsClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SYMS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SYMS_CLASS_VTBL    class_Vtbl = {
    {
        &Syms_Info,
        SymsClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Syms_Class,
        SymsClass_WhoAmI,
        (P_OBJ_QUERYINFO)SymsClass_QueryInfo,
        NULL                        // SymsClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SYMS_CLASS_DATA  Syms_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SYMS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SYMS_SINGLETON
SYMS_DATA *     Syms_getSingleton (
    void
)
{
    return (OBJ_ID)(Syms_ClassObj.pSingleton);
}


bool            Syms_setSingleton (
    SYMS_DATA       *pValue
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
    if (Syms_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Syms_ClassObj.pSingleton));
    }
    Syms_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SYMS_DATA *     Syms_Shared (
    void
)
{
    SYMS_DATA       *this = (OBJ_ID)(Syms_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Syms_New( );
        Syms_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Syms_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Syms_SharedReset (
    void
)
{
    SYMS_DATA       *this = (OBJ_ID)(Syms_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Syms_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SymsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SYMS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SYMS_DATA);
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
                        return (void *)&Syms_Info;
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
                        return Syms_New;
                    }
                    break;
                    
#ifdef  SYMS_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Syms_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Syms_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SymsClass_WhoAmI;
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
bool            Syms_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SYMS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Syms_Class())->pClassSuperObject;
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
void            Syms_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Syms_Class (
    void
)
{
    return (OBJ_ID)&Syms_ClassObj;
}


static
uint16_t		Syms_WhoAmI (
    void
)
{
    return OBJ_IDENT_SYMS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
SYMS_VTBL     Syms_Vtbl = {
    {
        &Syms_Info,
        Syms_IsKindOf,
#ifdef  SYMS_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Syms_Dealloc,
        Syms_Class,
        Syms_WhoAmI,
        (P_OBJ_QUERYINFO)Syms_QueryInfo,
        (P_OBJ_TOSTRING)Syms_ToDebugString,
        NULL,			// Syms_Enable,
        NULL,			// Syms_Disable,
        NULL,			// (P_OBJ_ASSIGN)Syms_Assign,
        NULL,			// (P_OBJ_COMPARE)Syms_Compare,
        NULL, 			// (P_OBJ_PTR)Syms_Copy,
        NULL, 			// (P_OBJ_PTR)Syms_DeepCopy,
        NULL 			// (P_OBJ_HASH)Syms_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    Syms_FindA,
    Syms_FindAddr,
 
};



static
const
OBJ_INFO        Syms_Info = {
    "Syms",
    "Simple Symbol Table",
    (OBJ_DATA *)&Syms_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Syms_Vtbl,
    sizeof(SYMS_DATA)
};





