// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'libNode'
//	Generated 08/19/2019 01:15:03


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




#define			LIBNODE_OBJECT_C	    1
#include        <libNode_internal.h>
#ifdef  LIBNODE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct libNode_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LIBNODE_SINGLETON
    volatile
    LIBNODE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          libNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        libNode_Info;            // Forward Reference




static
bool            libNodeClass_IsKindOf (
    uint16_t		classID
)
{
    if (MAIN_IDENT_LIBNODE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		libNodeClass_WhoAmI (
    void
)
{
    return MAIN_IDENT_LIBNODE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LIBNODE_CLASS_VTBL    class_Vtbl = {
    {
        &libNode_Info,
        libNodeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        libNode_Class,
        libNodeClass_WhoAmI,
        (P_OBJ_QUERYINFO)libNodeClass_QueryInfo,
        NULL                        // libNodeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

LIBNODE_CLASS_DATA  libNode_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LIBNODE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LIBNODE_SINGLETON
LIBNODE_DATA *     libNode_getSingleton (
    void
)
{
    return (OBJ_ID)(libNode_ClassObj.pSingleton);
}


bool            libNode_setSingleton (
    LIBNODE_DATA       *pValue
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
    if (libNode_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(libNode_ClassObj.pSingleton));
    }
    libNode_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LIBNODE_DATA *     libNode_Shared (
    void
)
{
    LIBNODE_DATA       *this = (OBJ_ID)(libNode_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = libNode_New( );
        libNode_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // libNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            libNode_SharedReset (
    void
)
{
    LIBNODE_DATA       *this = (OBJ_ID)(libNode_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        libNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          libNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LIBNODE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LIBNODE_DATA);
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
                        return (void *)&libNode_Info;
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
                        return libNode_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return libNodeClass_WhoAmI;
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
bool            libNode_IsKindOf (
    uint16_t		classID
)
{
    if (MAIN_IDENT_LIBNODE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            libNode_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          libNode_Class (
    void
)
{
    return (OBJ_ID)&libNode_ClassObj;
}


static
uint16_t		libNode_WhoAmI (
    void
)
{
    return MAIN_IDENT_LIBNODE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
LIBNODE_VTBL     libNode_Vtbl = {
    {
        &libNode_Info,
        libNode_IsKindOf,
#ifdef  LIBNODE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        libNode_Dealloc,
        libNode_Class,
        libNode_WhoAmI,
        (P_OBJ_QUERYINFO)libNode_QueryInfo,
        (P_OBJ_TOSTRING)libNode_ToDebugString,
        NULL,			// libNode_Enable,
        NULL,			// libNode_Disable,
        NULL,			// (P_OBJ_ASSIGN)libNode_Assign,
        NULL,			// (P_OBJ_COMPARE)libNode_Compare,
        NULL, 			// (P_OBJ_PTR)libNode_Copy,
        NULL, 			// (P_OBJ_PTR)libNode_DeepCopy,
        NULL 			// (P_OBJ_HASH)libNode_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //libNode_IsEnabled,
 
};



static
const
OBJ_INFO        libNode_Info = {
    "libNode",
    "libNode",	
    (OBJ_DATA *)&libNode_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&libNode_Vtbl,
    sizeof(LIBNODE_DATA)
};





