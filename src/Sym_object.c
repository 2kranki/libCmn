// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Sym'
//	Generated 02/22/2020 20:18:12


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




#define			SYM_OBJECT_C	    1
#include        <Sym_internal.h>
#ifdef  SYM_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Sym_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SYM_SINGLETON
    volatile
    SYM_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SymClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Sym_Info;            // Forward Reference




static
bool            SymClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SYM_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Sym_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		SymClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SYM_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SYM_CLASS_VTBL    class_Vtbl = {
    {
        &Sym_Info,
        SymClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Sym_Class,
        SymClass_WhoAmI,
        (P_OBJ_QUERYINFO)SymClass_QueryInfo,
        NULL                        // SymClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SYM_CLASS_DATA  Sym_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SYM_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SYM_SINGLETON
SYM_DATA *     Sym_getSingleton (
    void
)
{
    return (OBJ_ID)(Sym_ClassObj.pSingleton);
}


bool            Sym_setSingleton (
    SYM_DATA       *pValue
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
    if (Sym_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Sym_ClassObj.pSingleton));
    }
    Sym_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SYM_DATA *     Sym_Shared (
    void
)
{
    SYM_DATA       *this = (OBJ_ID)(Sym_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Sym_New( );
        Sym_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Sym_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Sym_SharedReset (
    void
)
{
    SYM_DATA       *this = (OBJ_ID)(Sym_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Sym_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SymClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SYM_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SYM_DATA);
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
                        return (void *)&Sym_Info;
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
                        return Sym_New;
                    }
                    break;
                    
#ifdef  SYM_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Sym_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Sym_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SymClass_WhoAmI;
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
bool            Sym_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SYM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Sym_Class())->pClassSuperObject;
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
void            Sym_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Sym_Class (
    void
)
{
    return (OBJ_ID)&Sym_ClassObj;
}


static
uint16_t		Sym_WhoAmI (
    void
)
{
    return OBJ_IDENT_SYM;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
SYM_VTBL     Sym_Vtbl = {
    {
        &Sym_Info,
        Sym_IsKindOf,
#ifdef  SYM_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Sym_Dealloc,
        Sym_Class,
        Sym_WhoAmI,
        (P_OBJ_QUERYINFO)Sym_QueryInfo,
        (P_OBJ_TOSTRING)Sym_ToDebugString,
        NULL,			// Sym_Enable,
        NULL,			// Sym_Disable,
        (P_OBJ_ASSIGN)Sym_Assign,
        (P_OBJ_COMPARE)Sym_Compare,
        (P_OBJ_PTR)Sym_Copy,
        NULL, 			// (P_OBJ_PTR)Sym_DeepCopy,
        NULL 			// (P_OBJ_HASH)Sym_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Sym_IsEnabled,
 
};



static
const
OBJ_INFO        Sym_Info = {
    "Sym",
    "Simple Symbol Table Entry",
    (OBJ_DATA *)&Sym_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Sym_Vtbl,
    sizeof(SYM_DATA)
};





