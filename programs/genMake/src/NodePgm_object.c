// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodePgm'
//	Generated 11/03/2019 08:11:49


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




#define			NODEPGM_OBJECT_C	    1
#include        <NodePgm_internal.h>
#ifdef  NODEPGM_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodePgm_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEPGM_SINGLETON
    volatile
    NODEPGM_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodePgmClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodePgm_Info;            // Forward Reference




static
bool            NodePgmClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEPGM_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_NODEBASE_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_NODE_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		NodePgmClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEPGM_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEPGM_CLASS_VTBL    class_Vtbl = {
    {
        &NodePgm_Info,
        NodePgmClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodePgm_Class,
        NodePgmClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodePgmClass_QueryInfo,
        NULL                        // NodePgmClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODEPGM_CLASS_DATA  NodePgm_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODEPGM_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEPGM_SINGLETON
NODEPGM_DATA *     NodePgm_getSingleton (
    void
)
{
    return (OBJ_ID)(NodePgm_ClassObj.pSingleton);
}


bool            NodePgm_setSingleton (
    NODEPGM_DATA       *pValue
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
    if (NodePgm_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodePgm_ClassObj.pSingleton));
    }
    NodePgm_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEPGM_DATA *     NodePgm_Shared (
    void
)
{
    NODEPGM_DATA       *this = (OBJ_ID)(NodePgm_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodePgm_New( );
        NodePgm_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodePgm_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodePgm_SharedReset (
    void
)
{
    NODEPGM_DATA       *this = (OBJ_ID)(NodePgm_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodePgm_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodePgmClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEPGM_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEPGM_DATA);
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
                        return (void *)&NodePgm_Info;
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
                        return NodePgm_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodePgmClass_WhoAmI;
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
bool            NodePgm_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEPGM == classID) {
       return true;
    }
    if (OBJ_IDENT_NODEBASE == classID) {
        return true;
    }
    if (OBJ_IDENT_NODE == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            NodePgm_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodePgm_Class (
    void
)
{
    return (OBJ_ID)&NodePgm_ClassObj;
}


static
uint16_t		NodePgm_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEPGM;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODEPGM_VTBL     NodePgm_Vtbl = {
    {
        &NodePgm_Info,
        NodePgm_IsKindOf,
#ifdef  NODEPGM_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodePgm_Dealloc,
        NodePgm_Class,
        NodePgm_WhoAmI,
        (P_OBJ_QUERYINFO)NodePgm_QueryInfo,
        (P_OBJ_TOSTRING)NodePgm_ToDebugString,
        NULL,			// NodePgm_Enable,
        NULL,			// NodePgm_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodePgm_Assign,
        NULL,			// (P_OBJ_COMPARE)NodePgm_Compare,
        NULL, 			// (P_OBJ_PTR)NodePgm_Copy,
        NULL, 			// (P_OBJ_PTR)NodePgm_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodePgm_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodePgm_IsEnabled,
 
};



static
const
OBJ_INFO        NodePgm_Info = {
    "NodePgm",
    "NodePgm",	// <-- Fill in description
    (OBJ_DATA *)&NodePgm_ClassObj,
    (OBJ_DATA *)&node_ClassObj,
    (OBJ_IUNKNOWN *)&NodePgm_Vtbl,
    sizeof(NODEPGM_DATA)
};





