// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'memrrds'
//	Generated 01/16/2019 16:27:57


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




#define			MEMRRDS_OBJECT_C	    1
#include        <memrrds_internal.h>
#ifdef  MEMRRDS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct memrrds_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  MEMRRDS_SINGLETON
    volatile
    MEMRRDS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          memrrdsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        memrrds_Info;            // Forward Reference




static
bool            memrrdsClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_MEMRRDS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_BLKS_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		memrrdsClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_MEMRRDS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
MEMRRDS_CLASS_VTBL    class_Vtbl = {
    {
        &memrrds_Info,
        memrrdsClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        memrrds_Class,
        memrrdsClass_WhoAmI,
        (P_OBJ_QUERYINFO)memrrdsClass_QueryInfo,
        NULL                        // memrrdsClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

MEMRRDS_CLASS_DATA  memrrds_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(MEMRRDS_CLASS_DATA),                  // cbSize
        OBJ_IDENT_MEMRRDS_CLASS,                     // cbIdent
        0,                                      // cbFlags
        0,                                      // eRc
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  MEMRRDS_SINGLETON
MEMRRDS_DATA *     memrrds_getSingleton (
    void
)
{
    return (OBJ_ID)(memrrds_ClassObj.pSingleton);
}


bool            memrrds_setSingleton (
    MEMRRDS_DATA       *pValue
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
    if (memrrds_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(memrrds_ClassObj.pSingleton));
    }
    memrrds_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



MEMRRDS_DATA *     memrrds_Shared (
    void
)
{
    MEMRRDS_DATA       *this = (OBJ_ID)(memrrds_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = memrrds_New( );
        memrrds_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // memrrds_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            memrrds_SharedReset (
    void
)
{
    MEMRRDS_DATA       *this = (OBJ_ID)(memrrds_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        memrrds_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          memrrdsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    MEMRRDS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(MEMRRDS_DATA);
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
                        return (void *)&memrrds_Info;
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
                        return memrrds_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return memrrdsClass_WhoAmI;
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
bool            memrrds_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_MEMRRDS == classID) {
       return true;
    }
    if (OBJ_IDENT_BLKS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            memrrds_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          memrrds_Class (
    void
)
{
    return (OBJ_ID)&memrrds_ClassObj;
}


static
uint16_t		memrrds_WhoAmI (
    void
)
{
    return OBJ_IDENT_MEMRRDS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
MEMRRDS_VTBL     memrrds_Vtbl = {
    {
        &memrrds_Info,
        memrrds_IsKindOf,
#ifdef  MEMRRDS_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        memrrds_Dealloc,
        memrrds_Class,
        memrrds_WhoAmI,
        (P_OBJ_QUERYINFO)memrrds_QueryInfo,
        (P_OBJ_TOSTRING)memrrds_ToDebugString,
        NULL,			// memrrds_Enable,
        NULL,			// memrrds_Disable,
        NULL,			// (P_OBJ_ASSIGN)memrrds_Assign,
        NULL,			// (P_OBJ_COMPARE)memrrds_Compare,
        NULL, 			// (P_OBJ_PTR)memrrds_Copy,
        NULL, 			// (P_OBJ_PTR)memrrds_DeepCopy,
        NULL 			// (P_OBJ_HASH)memrrds_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //memrrds_IsEnabled,
 
};



static
const
OBJ_INFO        memrrds_Info = {
    "memrrds",
    "Memory-Based Relative Record Dataset/File",
    (OBJ_DATA *)&memrrds_ClassObj,
    (OBJ_DATA *)&blks_ClassObj,
    (OBJ_IUNKNOWN *)&memrrds_Vtbl,
    sizeof(MEMRRDS_DATA)
};





