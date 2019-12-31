// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'GenBase'
//	Generated 11/23/2019 12:07:15


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




#define			GENBASE_OBJECT_C	    1
#include        <GenBase_internal.h>
#ifdef  GENBASE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct GenBase_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  GENBASE_SINGLETON
    volatile
    GENBASE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          GenBaseClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        GenBase_Info;            // Forward Reference




static
bool            GenBaseClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_GENBASE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		GenBaseClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_GENBASE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
GENBASE_CLASS_VTBL    class_Vtbl = {
    {
        &GenBase_Info,
        GenBaseClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        GenBase_Class,
        GenBaseClass_WhoAmI,
        (P_OBJ_QUERYINFO)GenBaseClass_QueryInfo,
        NULL                        // GenBaseClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

GENBASE_CLASS_DATA  GenBase_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(GENBASE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  GENBASE_SINGLETON
GENBASE_DATA *     GenBase_getSingleton (
    void
)
{
    return (OBJ_ID)(GenBase_ClassObj.pSingleton);
}


bool            GenBase_setSingleton (
    GENBASE_DATA       *pValue
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
    if (GenBase_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(GenBase_ClassObj.pSingleton));
    }
    GenBase_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



GENBASE_DATA *     GenBase_Shared (
    void
)
{
    GENBASE_DATA       *this = (OBJ_ID)(GenBase_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = GenBase_New( );
        GenBase_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // GenBase_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            GenBase_SharedReset (
    void
)
{
    GENBASE_DATA       *this = (OBJ_ID)(GenBase_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        GenBase_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          GenBaseClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    GENBASE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(GENBASE_DATA);
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
                        return (void *)&GenBase_Info;
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
                        return GenBase_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return GenBaseClass_WhoAmI;
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
bool            GenBase_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_GENBASE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            GenBase_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          GenBase_Class (
    void
)
{
    return (OBJ_ID)&GenBase_ClassObj;
}


static
uint16_t		GenBase_WhoAmI (
    void
)
{
    return OBJ_IDENT_GENBASE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
GENBASE_VTBL     GenBase_Vtbl = {
    {
        &GenBase_Info,
        GenBase_IsKindOf,
#ifdef  GENBASE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        GenBase_Dealloc,
        GenBase_Class,
        GenBase_WhoAmI,
        (P_OBJ_QUERYINFO)GenBase_QueryInfo,
        (P_OBJ_TOSTRING)GenBase_ToDebugString,
        NULL,			// GenBase_Enable,
        NULL,			// GenBase_Disable,
        NULL,			// (P_OBJ_ASSIGN)GenBase_Assign,
        NULL,			// (P_OBJ_COMPARE)GenBase_Compare,
        NULL, 			// (P_OBJ_PTR)GenBase_Copy,
        NULL, 			// (P_OBJ_PTR)GenBase_DeepCopy,
        NULL 			// (P_OBJ_HASH)GenBase_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //GenBase_IsEnabled,
 
};



static
const
OBJ_INFO        GenBase_Info = {
    "GenBase",
    "Base Makefile Generation",
    (OBJ_DATA *)&GenBase_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&GenBase_Vtbl,
    sizeof(GENBASE_DATA)
};





