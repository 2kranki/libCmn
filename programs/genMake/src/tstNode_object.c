// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'tstNode'
//	Generated 08/19/2019 01:14:23


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




#define			TSTNODE_OBJECT_C	    1
#include        <tstNode_internal.h>
#ifdef  TSTNODE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct tstNode_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TSTNODE_SINGLETON
    volatile
    TSTNODE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          tstNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        tstNode_Info;            // Forward Reference




static
bool            tstNodeClass_IsKindOf (
    uint16_t		classID
)
{
    if (MAIN_IDENT_TSTNODE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		tstNodeClass_WhoAmI (
    void
)
{
    return MAIN_IDENT_TSTNODE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TSTNODE_CLASS_VTBL    class_Vtbl = {
    {
        &tstNode_Info,
        tstNodeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        tstNode_Class,
        tstNodeClass_WhoAmI,
        (P_OBJ_QUERYINFO)tstNodeClass_QueryInfo,
        NULL                        // tstNodeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

TSTNODE_CLASS_DATA  tstNode_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TSTNODE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TSTNODE_SINGLETON
TSTNODE_DATA *     tstNode_getSingleton (
    void
)
{
    return (OBJ_ID)(tstNode_ClassObj.pSingleton);
}


bool            tstNode_setSingleton (
    TSTNODE_DATA       *pValue
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
    if (tstNode_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(tstNode_ClassObj.pSingleton));
    }
    tstNode_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TSTNODE_DATA *     tstNode_Shared (
    void
)
{
    TSTNODE_DATA       *this = (OBJ_ID)(tstNode_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = tstNode_New( );
        tstNode_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // tstNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            tstNode_SharedReset (
    void
)
{
    TSTNODE_DATA       *this = (OBJ_ID)(tstNode_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        tstNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          tstNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TSTNODE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TSTNODE_DATA);
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
                        return (void *)&tstNode_Info;
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
                        return tstNode_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return tstNodeClass_WhoAmI;
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
bool            tstNode_IsKindOf (
    uint16_t		classID
)
{
    if (MAIN_IDENT_TSTNODE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            tstNode_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          tstNode_Class (
    void
)
{
    return (OBJ_ID)&tstNode_ClassObj;
}


static
uint16_t		tstNode_WhoAmI (
    void
)
{
    return MAIN_IDENT_TSTNODE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
TSTNODE_VTBL     tstNode_Vtbl = {
    {
        &tstNode_Info,
        tstNode_IsKindOf,
#ifdef  TSTNODE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        tstNode_Dealloc,
        tstNode_Class,
        tstNode_WhoAmI,
        (P_OBJ_QUERYINFO)tstNode_QueryInfo,
        (P_OBJ_TOSTRING)tstNode_ToDebugString,
        NULL,			// tstNode_Enable,
        NULL,			// tstNode_Disable,
        NULL,			// (P_OBJ_ASSIGN)tstNode_Assign,
        NULL,			// (P_OBJ_COMPARE)tstNode_Compare,
        NULL, 			// (P_OBJ_PTR)tstNode_Copy,
        NULL, 			// (P_OBJ_PTR)tstNode_DeepCopy,
        NULL 			// (P_OBJ_HASH)tstNode_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //tstNode_IsEnabled,
 
};



static
const
OBJ_INFO        tstNode_Info = {
    "tstNode",
    "tstNode",	
    (OBJ_DATA *)&tstNode_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&tstNode_Vtbl,
    sizeof(TSTNODE_DATA)
};





