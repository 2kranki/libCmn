// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'ObjEnum'
//	Generated 12/16/2019 11:38:07


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




#define			OBJENUM_OBJECT_C	    1
#include        <ObjEnum_internal.h>
#ifdef  OBJENUM_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ObjEnum_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OBJENUM_SINGLETON
    volatile
    OBJENUM_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ObjEnumClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ObjEnum_Info;            // Forward Reference




static
bool            ObjEnumClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OBJENUM_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(ObjEnum_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		ObjEnumClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJENUM_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OBJENUM_CLASS_VTBL    class_Vtbl = {
    {
        &ObjEnum_Info,
        ObjEnumClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ObjEnum_Class,
        ObjEnumClass_WhoAmI,
        (P_OBJ_QUERYINFO)ObjEnumClass_QueryInfo,
        NULL                        // ObjEnumClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

OBJENUM_CLASS_DATA  ObjEnum_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OBJENUM_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OBJENUM_SINGLETON
OBJENUM_DATA *     ObjEnum_getSingleton (
    void
)
{
    return (OBJ_ID)(ObjEnum_ClassObj.pSingleton);
}


bool            ObjEnum_setSingleton (
    OBJENUM_DATA       *pValue
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
    if (ObjEnum_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ObjEnum_ClassObj.pSingleton));
    }
    ObjEnum_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OBJENUM_DATA *     ObjEnum_Shared (
    void
)
{
    OBJENUM_DATA       *this = (OBJ_ID)(ObjEnum_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ObjEnum_New( );
        ObjEnum_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ObjEnum_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ObjEnum_SharedReset (
    void
)
{
    OBJENUM_DATA       *this = (OBJ_ID)(ObjEnum_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        ObjEnum_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ObjEnumClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OBJENUM_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJENUM_DATA);
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
                        return (void *)&ObjEnum_Info;
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
                        return ObjEnum_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return ObjEnum_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ObjEnumClass_WhoAmI;
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
bool            ObjEnum_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OBJENUM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(ObjEnum_Class())->pClassSuperObject;
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
void            ObjEnum_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ObjEnum_Class (
    void
)
{
    return (OBJ_ID)&ObjEnum_ClassObj;
}


static
uint16_t		ObjEnum_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJENUM;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
OBJENUM_VTBL     ObjEnum_Vtbl = {
    {
        &ObjEnum_Info,
        ObjEnum_IsKindOf,
#ifdef  OBJENUM_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        ObjEnum_Dealloc,
        ObjEnum_Class,
        ObjEnum_WhoAmI,
        (P_OBJ_QUERYINFO)ObjEnum_QueryInfo,
        (P_OBJ_TOSTRING)ObjEnum_ToDebugString,
        NULL,			// ObjEnum_Enable,
        NULL,			// ObjEnum_Disable,
        NULL,			// (P_OBJ_ASSIGN)ObjEnum_Assign,
        NULL,			// (P_OBJ_COMPARE)ObjEnum_Compare,
        NULL, 			// (P_OBJ_PTR)ObjEnum_Copy,
        NULL, 			// (P_OBJ_PTR)ObjEnum_DeepCopy,
        NULL 			// (P_OBJ_HASH)ObjEnum_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ObjEnum_IsEnabled,
 
};



static
const
OBJ_INFO        ObjEnum_Info = {
    "ObjEnum",
    "Object Enumerator",
    (OBJ_DATA *)&ObjEnum_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&ObjEnum_Vtbl,
    sizeof(OBJENUM_DATA)
};





