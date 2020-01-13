// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'hash32'
//	Generated 01/12/2019 11:49:55


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




#define			HASH32_OBJECT_C	    1
#include        <hash32_internal.h>
#ifdef  HASH32_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct hash32_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  HASH32_SINGLETON
    volatile
    HASH32_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          hash32Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        hash32_Info;            // Forward Reference




static
bool            hash32Class_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_HASH32_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		hash32Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_HASH32_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
HASH32_CLASS_VTBL    class_Vtbl = {
    {
        &hash32_Info,
        hash32Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        hash32_Class,
        hash32Class_WhoAmI,
        (P_OBJ_QUERYINFO)hash32Class_QueryInfo,
        NULL                        // hash32Class_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

HASH32_CLASS_DATA  hash32_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(HASH32_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  HASH32_SINGLETON
HASH32_DATA *     hash32_getSingleton (
    void
)
{
    return (OBJ_ID)(hash32_ClassObj.pSingleton);
}


bool            hash32_setSingleton (
    HASH32_DATA       *pValue
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
    if (hash32_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(hash32_ClassObj.pSingleton));
    }
    hash32_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



HASH32_DATA *     hash32_Shared (
    void
)
{
    HASH32_DATA       *this = (OBJ_ID)(hash32_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = hash32_New( );
        hash32_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // hash32_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            hash32_SharedReset (
    void
)
{
    HASH32_DATA       *this = (OBJ_ID)(hash32_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        hash32_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          hash32Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    HASH32_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(HASH32_DATA);
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
                        return (void *)&hash32_Info;
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
                        return hash32_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return hash32Class_WhoAmI;
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
bool            hash32_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_HASH32 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            hash32_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          hash32_Class (
    void
)
{
    return (OBJ_ID)&hash32_ClassObj;
}


static
uint16_t		hash32_WhoAmI (
    void
)
{
    return OBJ_IDENT_HASH32;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
HASH32_VTBL     hash32_Vtbl = {
    {
        &hash32_Info,
        hash32_IsKindOf,
#ifdef  HASH32_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        hash32_Dealloc,
        hash32_Class,
        hash32_WhoAmI,
        (P_OBJ_QUERYINFO)hash32_QueryInfo,
        (P_OBJ_TOSTRING)hash32_ToDebugString,
        NULL,			// hash32_Enable,
        NULL,			// hash32_Disable,
        NULL,			// (P_OBJ_ASSIGN)hash32_Assign,
        NULL,			// (P_OBJ_COMPARE)hash32_Compare,
        NULL, 			// (P_OBJ_PTR)hash32_Copy,
        NULL, 			// (P_OBJ_PTR)hash32_DeepCopy,
        NULL 			// (P_OBJ_HASH)hash32_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //hash32_IsEnabled,
 
};



static
const
OBJ_INFO        hash32_Info = {
    "hash32",
    "32-Bit Hash Table",
    (OBJ_DATA *)&hash32_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&hash32_Vtbl,
    sizeof(HASH32_DATA)
};





