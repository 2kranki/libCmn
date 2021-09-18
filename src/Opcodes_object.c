// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Opcodes'
//	Generated 02/27/2020 16:46:25


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




#define			OPCODES_OBJECT_C	    1
#include        <Opcodes_internal.h>
#ifdef  OPCODES_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Opcodes_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OPCODES_SINGLETON
    volatile
    OPCODES_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          OpcodesClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Opcodes_Info;            // Forward Reference




static
bool            OpcodesClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OPCODES_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Opcodes_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		OpcodesClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OPCODES_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OPCODES_CLASS_VTBL    class_Vtbl = {
    {
        &Opcodes_Info,
        OpcodesClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Opcodes_Class,
        OpcodesClass_WhoAmI,
        (P_OBJ_QUERYINFO)OpcodesClass_QueryInfo,
        NULL                        // OpcodesClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

OPCODES_CLASS_DATA  Opcodes_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OPCODES_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OPCODES_SINGLETON
OPCODES_DATA *     Opcodes_getSingleton (
    void
)
{
    return (OBJ_ID)(Opcodes_ClassObj.pSingleton);
}


bool            Opcodes_setSingleton (
    OPCODES_DATA       *pValue
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
    if (Opcodes_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Opcodes_ClassObj.pSingleton));
    }
    Opcodes_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OPCODES_DATA *     Opcodes_Shared (
    void
)
{
    OPCODES_DATA       *this = (OBJ_ID)(Opcodes_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Opcodes_New( );
        Opcodes_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Opcodes_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Opcodes_SharedReset (
    void
)
{
    OPCODES_DATA       *this = (OBJ_ID)(Opcodes_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Opcodes_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          OpcodesClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OPCODES_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OPCODES_DATA);
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
                        return (void *)&Opcodes_Info;
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
                        return Opcodes_New;
                    }
                    break;
                    
#ifdef  OPCODES_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Opcodes_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Opcodes_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return OpcodesClass_WhoAmI;
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
bool            Opcodes_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OPCODES == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Opcodes_Class())->pClassSuperObject;
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
void            Opcodes_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Opcodes_Class (
    void
)
{
    return (OBJ_ID)&Opcodes_ClassObj;
}


static
uint16_t		Opcodes_WhoAmI (
    void
)
{
    return OBJ_IDENT_OPCODES;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
OPCODES_VTBL     Opcodes_Vtbl = {
    {
        &Opcodes_Info,
        Opcodes_IsKindOf,
#ifdef  OPCODES_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Opcodes_Dealloc,
        Opcodes_Class,
        Opcodes_WhoAmI,
        (P_OBJ_QUERYINFO)Opcodes_QueryInfo,
        (P_OBJ_TOSTRING)Opcodes_ToDebugString,
        NULL,			// Opcodes_Enable,
        NULL,			// Opcodes_Disable,
        NULL,			// (P_OBJ_ASSIGN)Opcodes_Assign,
        NULL,			// (P_OBJ_COMPARE)Opcodes_Compare,
        NULL, 			// (P_OBJ_PTR)Opcodes_Copy,
        NULL, 			// (P_OBJ_PTR)Opcodes_DeepCopy,
        NULL 			// (P_OBJ_HASH)Opcodes_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    Opcodes_FindA,
 
};



static
const
OBJ_INFO        Opcodes_Info = {
    "Opcodes",
    "Universal Opcode Table",
    (OBJ_DATA *)&Opcodes_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Opcodes_Vtbl,
    sizeof(OPCODES_DATA)
};





