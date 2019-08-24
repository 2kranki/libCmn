// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'rtnNode'
//	Generated 08/19/2019 01:14:40


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




#define			RTNNODE_OBJECT_C	    1
#include        <rtnNode_internal.h>
#ifdef  RTNNODE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct rtnNode_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  RTNNODE_SINGLETON
    volatile
    RTNNODE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          rtnNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        rtnNode_Info;            // Forward Reference




static
bool            rtnNodeClass_IsKindOf (
    uint16_t		classID
)
{
    if (MAIN_IDENT_RTNNODE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		rtnNodeClass_WhoAmI (
    void
)
{
    return MAIN_IDENT_RTNNODE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
RTNNODE_CLASS_VTBL    class_Vtbl = {
    {
        &rtnNode_Info,
        rtnNodeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        rtnNode_Class,
        rtnNodeClass_WhoAmI,
        (P_OBJ_QUERYINFO)rtnNodeClass_QueryInfo,
        NULL                        // rtnNodeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

RTNNODE_CLASS_DATA  rtnNode_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(RTNNODE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  RTNNODE_SINGLETON
RTNNODE_DATA *     rtnNode_getSingleton (
    void
)
{
    return (OBJ_ID)(rtnNode_ClassObj.pSingleton);
}


bool            rtnNode_setSingleton (
    RTNNODE_DATA       *pValue
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
    if (rtnNode_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(rtnNode_ClassObj.pSingleton));
    }
    rtnNode_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



RTNNODE_DATA *     rtnNode_Shared (
    void
)
{
    RTNNODE_DATA       *this = (OBJ_ID)(rtnNode_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = rtnNode_New( );
        rtnNode_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // rtnNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            rtnNode_SharedReset (
    void
)
{
    RTNNODE_DATA       *this = (OBJ_ID)(rtnNode_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        rtnNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          rtnNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    RTNNODE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(RTNNODE_DATA);
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
                        return (void *)&rtnNode_Info;
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
                        return rtnNode_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return rtnNodeClass_WhoAmI;
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
bool            rtnNode_IsKindOf (
    uint16_t		classID
)
{
    if (MAIN_IDENT_RTNNODE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            rtnNode_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          rtnNode_Class (
    void
)
{
    return (OBJ_ID)&rtnNode_ClassObj;
}


static
uint16_t		rtnNode_WhoAmI (
    void
)
{
    return MAIN_IDENT_RTNNODE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
RTNNODE_VTBL     rtnNode_Vtbl = {
    {
        &rtnNode_Info,
        rtnNode_IsKindOf,
#ifdef  RTNNODE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        rtnNode_Dealloc,
        rtnNode_Class,
        rtnNode_WhoAmI,
        (P_OBJ_QUERYINFO)rtnNode_QueryInfo,
        (P_OBJ_TOSTRING)rtnNode_ToDebugString,
        NULL,			// rtnNode_Enable,
        NULL,			// rtnNode_Disable,
        NULL,			// (P_OBJ_ASSIGN)rtnNode_Assign,
        NULL,			// (P_OBJ_COMPARE)rtnNode_Compare,
        NULL, 			// (P_OBJ_PTR)rtnNode_Copy,
        NULL, 			// (P_OBJ_PTR)rtnNode_DeepCopy,
        NULL 			// (P_OBJ_HASH)rtnNode_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //rtnNode_IsEnabled,
 
};



static
const
OBJ_INFO        rtnNode_Info = {
    "rtnNode",
    "rtnNode",
    (OBJ_DATA *)&rtnNode_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&rtnNode_Vtbl,
    sizeof(RTNNODE_DATA)
};





