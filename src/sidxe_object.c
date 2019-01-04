// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'sidxe'
//	Generated 12/18/2018 10:26:03


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




#define			SIDXE_OBJECT_C	    1
#include        <sidxe_internal.h>
#ifdef  SIDXE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct sidxe_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SIDXE_SINGLETON
    volatile
    SIDXE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          sidxeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        sidxe_Info;            // Forward Reference




static
bool            sidxeClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_SIDXE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		sidxeClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SIDXE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SIDXE_CLASS_VTBL    class_Vtbl = {
    {
        &sidxe_Info,
        sidxeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        sidxe_Class,
        sidxeClass_WhoAmI,
        (P_OBJ_QUERYINFO)sidxeClass_QueryInfo,
        NULL                        // sidxeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SIDXE_CLASS_DATA  sidxe_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(SIDXE_CLASS_DATA),        // cbSize
        OBJ_IDENT_SIDXE_CLASS,           // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SIDXE_SINGLETON
SIDXE_DATA *     sidxe_getSingleton (
    void
)
{
    return (OBJ_ID)(sidxe_ClassObj.pSingleton);
}


bool            sidxe_setSingleton (
    SIDXE_DATA       *pValue
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
    if (sidxe_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(sidxe_ClassObj.pSingleton));
    }
    sidxe_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SIDXE_DATA *     sidxe_Shared (
    void
)
{
    SIDXE_DATA       *this = (OBJ_ID)(sidxe_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = sidxe_New( );
        sidxe_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // sidxe_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            sidxe_SharedReset (
    void
)
{
    SIDXE_DATA       *this = (OBJ_ID)(sidxe_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        sidxe_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          sidxeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SIDXE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SIDXE_DATA);
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
                        return (void *)&sidxe_Info;
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
                        return sidxe_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return sidxeClass_WhoAmI;
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
bool            sidxe_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_SIDXE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            sidxe_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          sidxe_Class (
    void
)
{
    return (OBJ_ID)&sidxe_ClassObj;
}


static
uint16_t		sidxe_WhoAmI (
    void
)
{
    return OBJ_IDENT_SIDXE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
SIDXE_VTBL     sidxe_Vtbl = {
    {
        &sidxe_Info,
        sidxe_IsKindOf,
#ifdef  SIDXE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        sidxe_Dealloc,
        sidxe_Class,
        sidxe_WhoAmI,
        (P_OBJ_QUERYINFO)sidxe_QueryInfo,
        (P_OBJ_TOSTRING)sidxe_ToDebugString,
        NULL,			// sidxe_Enable,
        NULL,			// sidxe_Disable,
        NULL,			// (P_OBJ_ASSIGN)sidxe_Assign,
        NULL,			// (P_OBJ_COMPARE)sidxe_Compare,
        NULL, 			// (P_OBJ_PTR)sidxe_Copy,
        NULL, 			// (P_OBJ_PTR)sidxe_DeepCopy,
        NULL 			// (P_OBJ_HASH)sidxe_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //sidxe_IsEnabled,
 
};



static
const
OBJ_INFO        sidxe_Info = {
    "sidxe",
    "Simple Index with Extended Information",
    (OBJ_DATA *)&sidxe_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&sidxe_Vtbl,
    sizeof(SIDXE_DATA)
};





