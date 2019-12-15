// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'AStrCArray'
//	Generated 11/07/2019 08:58:19


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




#define			ASTRCARRAY_OBJECT_C	    1
#include        <AStrCArray_internal.h>
#ifdef  ASTRCARRAY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct AStrCArray_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  ASTRCARRAY_SINGLETON
    volatile
    ASTRCARRAY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          AStrCArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        AStrCArray_Info;            // Forward Reference




static
bool            AStrCArrayClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTRCARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		AStrCArrayClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_ASTRCARRAY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
ASTRCARRAY_CLASS_VTBL    class_Vtbl = {
    {
        &AStrCArray_Info,
        AStrCArrayClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        AStrCArray_Class,
        AStrCArrayClass_WhoAmI,
        (P_OBJ_QUERYINFO)AStrCArrayClass_QueryInfo,
        NULL                        // AStrCArrayClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

ASTRCARRAY_CLASS_DATA  AStrCArray_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(ASTRCARRAY_CLASS_DATA),          // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  ASTRCARRAY_SINGLETON
ASTRCARRAY_DATA *     AStrCArray_getSingleton (
    void
)
{
    return (OBJ_ID)(AStrCArray_ClassObj.pSingleton);
}


bool            AStrCArray_setSingleton (
    ASTRCARRAY_DATA       *pValue
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
    if (AStrCArray_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(AStrCArray_ClassObj.pSingleton));
    }
    AStrCArray_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



ASTRCARRAY_DATA *     AStrCArray_Shared (
    void
)
{
    ASTRCARRAY_DATA       *this = (OBJ_ID)(AStrCArray_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = AStrCArray_New( );
        AStrCArray_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // AStrCArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            AStrCArray_SharedReset (
    void
)
{
    ASTRCARRAY_DATA       *this = (OBJ_ID)(AStrCArray_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        AStrCArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          AStrCArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    ASTRCARRAY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(ASTRCARRAY_DATA);
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
                        return (void *)&AStrCArray_Info;
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
                        return AStrCArray_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return AStrCArrayClass_WhoAmI;
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
bool            AStrCArray_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTRCARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            AStrCArray_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          AStrCArray_Class (
    void
)
{
    return (OBJ_ID)&AStrCArray_ClassObj;
}


static
uint16_t		AStrCArray_WhoAmI (
    void
)
{
    return OBJ_IDENT_ASTRCARRAY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
ASTRCARRAY_VTBL     AStrCArray_Vtbl = {
    {
        &AStrCArray_Info,
        AStrCArray_IsKindOf,
#ifdef  ASTRCARRAY_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        AStrCArray_Dealloc,
        AStrCArray_Class,
        AStrCArray_WhoAmI,
        (P_OBJ_QUERYINFO)AStrCArray_QueryInfo,
        (P_OBJ_TOSTRING)AStrCArray_ToDebugString,
        NULL,			// AStrCArray_Enable,
        NULL,			// AStrCArray_Disable,
        (P_OBJ_ASSIGN)AStrCArray_Assign,
        NULL,			// (P_OBJ_COMPARE)AStrCArray_Compare,
        (P_OBJ_PTR)AStrCArray_Copy,
        NULL, 			// (P_OBJ_PTR)AStrCArray_DeepCopy,
        NULL 			// (P_OBJ_HASH)AStrCArray_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //AStrCArray_IsEnabled,
 
};



static
const
OBJ_INFO        AStrCArray_Info = {
    "AStrCArray",
    "Array of AStrC objects",
    (OBJ_DATA *)&AStrCArray_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&AStrCArray_Vtbl,
    sizeof(ASTRCARRAY_DATA)
};





