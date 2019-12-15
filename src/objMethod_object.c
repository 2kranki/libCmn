// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'ObjMethod'
//	Generated 12/15/2019 14:20:32


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




#define			OBJMETHOD_OBJECT_C	    1
#include        <ObjMethod_internal.h>
#ifdef  OBJMETHOD_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ObjMethod_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OBJMETHOD_SINGLETON
    volatile
    OBJMETHOD_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ObjMethodClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ObjMethod_Info;            // Forward Reference




static
bool            ObjMethodClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OBJMETHOD_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(ObjMethod_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		ObjMethodClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJMETHOD_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OBJMETHOD_CLASS_VTBL    class_Vtbl = {
    {
        &ObjMethod_Info,
        ObjMethodClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ObjMethod_Class,
        ObjMethodClass_WhoAmI,
        (P_OBJ_QUERYINFO)ObjMethodClass_QueryInfo,
        NULL                        // ObjMethodClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

OBJMETHOD_CLASS_DATA  ObjMethod_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OBJMETHOD_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OBJMETHOD_SINGLETON
OBJMETHOD_DATA *     ObjMethod_getSingleton (
    void
)
{
    return (OBJ_ID)(ObjMethod_ClassObj.pSingleton);
}


bool            ObjMethod_setSingleton (
    OBJMETHOD_DATA       *pValue
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
    if (ObjMethod_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ObjMethod_ClassObj.pSingleton));
    }
    ObjMethod_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OBJMETHOD_DATA *     ObjMethod_Shared (
    void
)
{
    OBJMETHOD_DATA       *this = (OBJ_ID)(ObjMethod_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ObjMethod_New( );
        ObjMethod_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ObjMethod_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ObjMethod_SharedReset (
    void
)
{
    OBJMETHOD_DATA       *this = (OBJ_ID)(ObjMethod_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        ObjMethod_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ObjMethodClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OBJMETHOD_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJMETHOD_DATA);
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
                        return (void *)&ObjMethod_Info;
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
                        return ObjMethod_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return ObjMethod_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ObjMethodClass_WhoAmI;
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
bool            ObjMethod_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OBJMETHOD == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(ObjMethod_Class())->pClassSuperObject;
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
void            ObjMethod_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ObjMethod_Class (
    void
)
{
    return (OBJ_ID)&ObjMethod_ClassObj;
}


static
uint16_t		ObjMethod_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJMETHOD;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
OBJMETHOD_VTBL     ObjMethod_Vtbl = {
    {
        &ObjMethod_Info,
        ObjMethod_IsKindOf,
#ifdef  OBJMETHOD_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        ObjMethod_Dealloc,
        ObjMethod_Class,
        ObjMethod_WhoAmI,
        (P_OBJ_QUERYINFO)ObjMethod_QueryInfo,
        (P_OBJ_TOSTRING)ObjMethod_ToDebugString,
        NULL,			// ObjMethod_Enable,
        NULL,			// ObjMethod_Disable,
        NULL,			// (P_OBJ_ASSIGN)ObjMethod_Assign,
        NULL,			// (P_OBJ_COMPARE)ObjMethod_Compare,
        NULL, 			// (P_OBJ_PTR)ObjMethod_Copy,
        NULL, 			// (P_OBJ_PTR)ObjMethod_DeepCopy,
        NULL 			// (P_OBJ_HASH)ObjMethod_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ObjMethod_IsEnabled,
 
};



static
const
OBJ_INFO        ObjMethod_Info = {
    "ObjMethod",
    "Object Method Container",
    (OBJ_DATA *)&ObjMethod_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&ObjMethod_Vtbl,
    sizeof(OBJMETHOD_DATA)
};





