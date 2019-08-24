// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'hdrNode'
//	Generated 08/19/2019 01:19:34


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




#define			HDRNODE_OBJECT_C	    1
#include        <hdrNode_internal.h>
#ifdef  HDRNODE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct hdrNode_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  HDRNODE_SINGLETON
    volatile
    HDRNODE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          hdrNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        hdrNode_Info;            // Forward Reference




static
bool            hdrNodeClass_IsKindOf (
    uint16_t		classID
)
{
    if (MAIN_IDENT_HDRNODE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		hdrNodeClass_WhoAmI (
    void
)
{
    return MAIN_IDENT_HDRNODE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
HDRNODE_CLASS_VTBL    class_Vtbl = {
    {
        &hdrNode_Info,
        hdrNodeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        hdrNode_Class,
        hdrNodeClass_WhoAmI,
        (P_OBJ_QUERYINFO)hdrNodeClass_QueryInfo,
        NULL                        // hdrNodeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

HDRNODE_CLASS_DATA  hdrNode_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(HDRNODE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  HDRNODE_SINGLETON
HDRNODE_DATA *     hdrNode_getSingleton (
    void
)
{
    return (OBJ_ID)(hdrNode_ClassObj.pSingleton);
}


bool            hdrNode_setSingleton (
    HDRNODE_DATA       *pValue
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
    if (hdrNode_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(hdrNode_ClassObj.pSingleton));
    }
    hdrNode_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



HDRNODE_DATA *     hdrNode_Shared (
    void
)
{
    HDRNODE_DATA       *this = (OBJ_ID)(hdrNode_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = hdrNode_New( );
        hdrNode_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // hdrNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            hdrNode_SharedReset (
    void
)
{
    HDRNODE_DATA       *this = (OBJ_ID)(hdrNode_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        hdrNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          hdrNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    HDRNODE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(HDRNODE_DATA);
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
                        return (void *)&hdrNode_Info;
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
                        return hdrNode_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return hdrNodeClass_WhoAmI;
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
bool            hdrNode_IsKindOf (
    uint16_t		classID
)
{
    if (MAIN_IDENT_HDRNODE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            hdrNode_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          hdrNode_Class (
    void
)
{
    return (OBJ_ID)&hdrNode_ClassObj;
}


static
uint16_t		hdrNode_WhoAmI (
    void
)
{
    return MAIN_IDENT_HDRNODE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
HDRNODE_VTBL     hdrNode_Vtbl = {
    {
        &hdrNode_Info,
        hdrNode_IsKindOf,
#ifdef  HDRNODE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        hdrNode_Dealloc,
        hdrNode_Class,
        hdrNode_WhoAmI,
        (P_OBJ_QUERYINFO)hdrNode_QueryInfo,
        (P_OBJ_TOSTRING)hdrNode_ToDebugString,
        NULL,			// hdrNode_Enable,
        NULL,			// hdrNode_Disable,
        NULL,			// (P_OBJ_ASSIGN)hdrNode_Assign,
        NULL,			// (P_OBJ_COMPARE)hdrNode_Compare,
        NULL, 			// (P_OBJ_PTR)hdrNode_Copy,
        NULL, 			// (P_OBJ_PTR)hdrNode_DeepCopy,
        NULL 			// (P_OBJ_HASH)hdrNode_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //hdrNode_IsEnabled,
 
};



static
const
OBJ_INFO        hdrNode_Info = {
    "hdrNode",
    "hdrNode",	
    (OBJ_DATA *)&hdrNode_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&hdrNode_Vtbl,
    sizeof(HDRNODE_DATA)
};





