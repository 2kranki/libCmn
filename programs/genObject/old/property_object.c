// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'property'
//	Generated 12/02/2018 23:32:21


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




#define			PROPERTY_OBJECT_C	    1
#include        <property_internal.h>
#ifdef  PROPERTY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct property_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  PROPERTY_SINGLETON
    volatile
    PROPERTY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          propertyClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        property_Info;            // Forward Reference




static
bool            propertyClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_PROPERTY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		propertyClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_PROPERTY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
PROPERTY_CLASS_VTBL    class_Vtbl = {
    {
        &property_Info,
        propertyClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        property_Class,
        propertyClass_WhoAmI,
        (P_OBJ_QUERYINFO)propertyClass_QueryInfo,
        NULL                        // propertyClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

PROPERTY_CLASS_DATA  property_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(PROPERTY_CLASS_DATA),        // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  PROPERTY_SINGLETON
PROPERTY_DATA *     property_getSingleton (
    void
)
{
    return (OBJ_ID)(property_ClassObj.pSingleton);
}


bool            property_setSingleton (
    PROPERTY_DATA       *pValue
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
    if (property_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(property_ClassObj.pSingleton));
    }
    property_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



PROPERTY_DATA *     property_Shared (
    void
)
{
    PROPERTY_DATA       *this = (OBJ_ID)(property_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = property_New( );
        property_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // property_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            property_SharedReset (
    void
)
{
    PROPERTY_DATA       *this = (OBJ_ID)(property_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        property_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          propertyClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PROPERTY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PROPERTY_DATA);
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
                        return (void *)&property_Info;
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
                        return property_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return propertyClass_WhoAmI;
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
bool            property_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_PROPERTY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            property_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          property_Class (
    void
)
{
    return (OBJ_ID)&property_ClassObj;
}


static
uint16_t		property_WhoAmI (
    void
)
{
    return OBJ_IDENT_PROPERTY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
PROPERTY_VTBL     property_Vtbl = {
    {
        &property_Info,
        property_IsKindOf,
#ifdef  PROPERTY_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        property_Dealloc,
        property_Class,
        property_WhoAmI,
        (P_OBJ_QUERYINFO)property_QueryInfo,
        (P_OBJ_TOSTRING)property_ToDebugString,
        NULL,			// property_Enable,
        NULL,			// property_Disable,
        NULL,			// (P_OBJ_ASSIGN)property_Assign,
        NULL,			// (P_OBJ_COMPARE)property_Compare,
        NULL, 			// (P_OBJ_PTR)property_Copy,
        NULL, 			// (P_OBJ_PTR)property_DeepCopy,
        NULL 			// (P_OBJ_HASH)property_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //property_IsEnabled,
 
};



static
const
OBJ_INFO        property_Info = {
    "property",
    "Property",
    (OBJ_DATA *)&property_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&property_Vtbl,
    sizeof(PROPERTY_DATA)
};





