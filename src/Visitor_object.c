// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Visitor'
//	Generated 04/26/2020 19:33:02


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




#define			VISITOR_OBJECT_C	    1
#include        <Visitor_internal.h>
#ifdef  VISITOR_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Visitor_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  VISITOR_SINGLETON
    volatile
    VISITOR_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          VisitorClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Visitor_Info;            // Forward Reference




static
bool            VisitorClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_VISITOR_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Visitor_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		VisitorClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_VISITOR_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
VISITOR_CLASS_VTBL    class_Vtbl = {
    {
        &Visitor_Info,
        VisitorClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Visitor_Class,
        VisitorClass_WhoAmI,
        (P_OBJ_QUERYINFO)VisitorClass_QueryInfo,
        NULL                        // VisitorClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

VISITOR_CLASS_DATA  Visitor_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(VISITOR_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  VISITOR_SINGLETON
extern
const
VISITOR_VTBL       Visitor_VtblShared;


VISITOR_DATA *     Visitor_getSingleton (
    void
)
{
    return (OBJ_ID)(Visitor_ClassObj.pSingleton);
}


bool            Visitor_setSingleton (
    VISITOR_DATA       *pValue
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
    if (Visitor_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Visitor_ClassObj.pSingleton));
    }
    Visitor_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



VISITOR_DATA *     Visitor_Shared (
    void
)
{
    VISITOR_DATA       *this = (OBJ_ID)(Visitor_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Visitor_New( );
        obj_setVtbl(this, (void *)&Visitor_VtblShared);
        Visitor_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Visitor_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Visitor_SharedReset (
    void
)
{
    VISITOR_DATA       *this = (OBJ_ID)(Visitor_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Visitor_Vtbl);
        obj_Release(this);
        Visitor_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          VisitorClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    VISITOR_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(VISITOR_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Visitor_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Visitor_Info.pClassSuperObject;
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
                        return Visitor_New;
                    }
                    break;
                    
				case 'P':
#ifdef  VISITOR_JSON_SUPPORT
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Visitor_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Visitor_ParseJsonObject;
					}
#endif
					break;

				case 'T':
#ifdef  VISITOR_JSON_SUPPORT
					if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
						return Visitor_ToJsonFields;
					}
					if (str_Compare("ToJson", (char *)pStr) == 0) {
						return Visitor_ToJson;
					}
#endif
					break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return VisitorClass_WhoAmI;
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
bool            Visitor_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_VISITOR == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Visitor_Class())->pClassSuperObject;
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
void            Visitor_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Visitor_Class (
    void
)
{
    return (OBJ_ID)&Visitor_ClassObj;
}


static
uint16_t		Visitor_WhoAmI (
    void
)
{
    return OBJ_IDENT_VISITOR;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  VISITOR_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
VISITOR_VTBL     Visitor_VtblShared = {
    {
        &Visitor_Info,
        Visitor_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Visitor_Dealloc,
        Visitor_Class,
        Visitor_WhoAmI,
        (P_OBJ_QUERYINFO)Visitor_QueryInfo,
        (P_OBJ_TOSTRING)Visitor_ToDebugString,
        NULL,			// Visitor_Enable,
        NULL,			// Visitor_Disable,
        NULL,			// (P_OBJ_ASSIGN)Visitor_Assign,
        NULL,			// (P_OBJ_COMPARE)Visitor_Compare,
        NULL, 			// (P_OBJ_PTR)Visitor_Copy,
        NULL, 			// (P_OBJ_PTR)Visitor_DeepCopy,
        NULL 			// (P_OBJ_HASH)Visitor_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Visitor_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
VISITOR_VTBL     Visitor_Vtbl = {
    {
        &Visitor_Info,
        Visitor_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Visitor_Dealloc,
        Visitor_Class,
        Visitor_WhoAmI,
        (P_OBJ_QUERYINFO)Visitor_QueryInfo,
        (P_OBJ_TOSTRING)Visitor_ToDebugString,
        NULL,			// Visitor_Enable,
        NULL,			// Visitor_Disable,
        NULL,			// (P_OBJ_ASSIGN)Visitor_Assign,
        NULL,			// (P_OBJ_COMPARE)Visitor_Compare,
        NULL, 			// (P_OBJ_PTR)Visitor_Copy,
        NULL, 			// (P_OBJ_PTR)Visitor_DeepCopy,
        NULL 			// (P_OBJ_HASH)Visitor_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Visitor_IsEnabled,
 
};



static
const
OBJ_INFO        Visitor_Info = {
    "Visitor",
    "Separate Visitor",
    (OBJ_DATA *)&Visitor_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Visitor_Vtbl,
    sizeof(VISITOR_DATA)
};





