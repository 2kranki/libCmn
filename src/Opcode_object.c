// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Opcode'
//	Generated 02/27/2020 14:36:27


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




#define			OPCODE_OBJECT_C	    1
#include        <Opcode_internal.h>
#ifdef  OPCODE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Opcode_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OPCODE_SINGLETON
    volatile
    OPCODE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          OpcodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Opcode_Info;            // Forward Reference




static
bool            OpcodeClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OPCODE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Opcode_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		OpcodeClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OPCODE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OPCODE_CLASS_VTBL    class_Vtbl = {
    {
        &Opcode_Info,
        OpcodeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Opcode_Class,
        OpcodeClass_WhoAmI,
        (P_OBJ_QUERYINFO)OpcodeClass_QueryInfo,
        NULL                        // OpcodeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

OPCODE_CLASS_DATA  Opcode_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OPCODE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OPCODE_SINGLETON
OPCODE_DATA *     Opcode_getSingleton (
    void
)
{
    return (OBJ_ID)(Opcode_ClassObj.pSingleton);
}


bool            Opcode_setSingleton (
    OPCODE_DATA       *pValue
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
    if (Opcode_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Opcode_ClassObj.pSingleton));
    }
    Opcode_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OPCODE_DATA *     Opcode_Shared (
    void
)
{
    OPCODE_DATA       *this = (OBJ_ID)(Opcode_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Opcode_New( );
        Opcode_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Opcode_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Opcode_SharedReset (
    void
)
{
    OPCODE_DATA       *this = (OBJ_ID)(Opcode_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Opcode_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          OpcodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OPCODE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OPCODE_DATA);
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
                        return (void *)&Opcode_Info;
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
                        return Opcode_New;
                    }
                    break;
                    
#ifdef  OPCODE_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Opcode_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Opcode_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return OpcodeClass_WhoAmI;
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
bool            Opcode_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OPCODE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Opcode_Class())->pClassSuperObject;
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
void            Opcode_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Opcode_Class (
    void
)
{
    return (OBJ_ID)&Opcode_ClassObj;
}


static
uint16_t		Opcode_WhoAmI (
    void
)
{
    return OBJ_IDENT_OPCODE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
OPCODE_VTBL     Opcode_Vtbl = {
    {
        &Opcode_Info,
        Opcode_IsKindOf,
#ifdef  OPCODE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Opcode_Dealloc,
        Opcode_Class,
        Opcode_WhoAmI,
        (P_OBJ_QUERYINFO)Opcode_QueryInfo,
        (P_OBJ_TOSTRING)Opcode_ToDebugString,
        NULL,			// Opcode_Enable,
        NULL,			// Opcode_Disable,
        (P_OBJ_ASSIGN)Opcode_Assign,
        (P_OBJ_COMPARE)Opcode_Compare,
        (P_OBJ_PTR)Opcode_Copy,
        NULL, 			// (P_OBJ_PTR)Opcode_DeepCopy,
        (P_OBJ_HASH)Opcode_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Opcode_IsEnabled,
 
};



static
const
OBJ_INFO        Opcode_Info = {
    "Opcode",
    "Universal Opcode Table Entry",
    (OBJ_DATA *)&Opcode_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    //(OBJ_DATA *)&Node_ClassObj,
    (OBJ_IUNKNOWN *)&Opcode_Vtbl,
    sizeof(OPCODE_DATA)
};





