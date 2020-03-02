// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Opc360'
//	Generated 02/29/2020 23:01:22


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




#define			OPC360_OBJECT_C	    1
#include        <Opc360_internal.h>
#ifdef  OPC360_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Opc360_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OPC360_SINGLETON
    volatile
    OPC360_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Opc360Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Opc360_Info;            // Forward Reference




static
bool            Opc360Class_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OPC360_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Opc360_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		Opc360Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_OPC360_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OPC360_CLASS_VTBL    class_Vtbl = {
    {
        &Opc360_Info,
        Opc360Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Opc360_Class,
        Opc360Class_WhoAmI,
        (P_OBJ_QUERYINFO)Opc360Class_QueryInfo,
        NULL                        // Opc360Class_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

OPC360_CLASS_DATA  Opc360_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OPC360_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OPC360_SINGLETON
OPC360_DATA *     Opc360_getSingleton (
    void
)
{
    return (OBJ_ID)(Opc360_ClassObj.pSingleton);
}


bool            Opc360_setSingleton (
    OPC360_DATA       *pValue
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
    if (Opc360_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Opc360_ClassObj.pSingleton));
    }
    Opc360_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OPC360_DATA *     Opc360_Shared (
    void
)
{
    OPC360_DATA       *this = (OBJ_ID)(Opc360_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Opc360_New( );
        Opc360_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Opc360_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Opc360_SharedReset (
    void
)
{
    OPC360_DATA       *this = (OBJ_ID)(Opc360_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Opc360_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Opc360Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OPC360_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OPC360_DATA);
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
                        return (void *)&Opc360_Info;
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
                        return Opc360_New;
                    }
                    break;
                    
#ifdef  OPC360_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Opc360_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Opc360_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return Opc360Class_WhoAmI;
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
bool            Opc360_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OPC360 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Opc360_Class())->pClassSuperObject;
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
void            Opc360_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Opc360_Class (
    void
)
{
    return (OBJ_ID)&Opc360_ClassObj;
}


static
uint16_t		Opc360_WhoAmI (
    void
)
{
    return OBJ_IDENT_OPC360;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
OPC360_VTBL     Opc360_Vtbl = {
    {
        &Opc360_Info,
        Opc360_IsKindOf,
#ifdef  OPC360_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Opc360_Dealloc,
        Opc360_Class,
        Opc360_WhoAmI,
        (P_OBJ_QUERYINFO)Opc360_QueryInfo,
        (P_OBJ_TOSTRING)Opc360_ToDebugString,
        NULL,			// Opc360_Enable,
        NULL,			// Opc360_Disable,
        (P_OBJ_ASSIGN)Opc360_Assign,
        (P_OBJ_COMPARE)Opc360_Compare,
        (P_OBJ_PTR)Opc360_Copy,
        NULL, 			// (P_OBJ_PTR)Opc360_DeepCopy,
        NULL 			// (P_OBJ_HASH)Opc360_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Opc360_IsEnabled,
 
};



static
const
OBJ_INFO        Opc360_Info = {
    "Opc360",
    "IBM 360 Opcode",
    (OBJ_DATA *)&Opc360_ClassObj,
    (OBJ_DATA *)&Opcode_ClassObj,
    (OBJ_IUNKNOWN *)&Opc360_Vtbl,
    sizeof(OPC360_DATA)
};





