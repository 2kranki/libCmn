// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeObj'
//	Generated 11/03/2019 08:11:26


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




#define			NODEOBJ_OBJECT_C	    1
#include        <NodeObj_internal.h>
#ifdef  NODEOBJ_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeObj_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEOBJ_SINGLETON
    volatile
    NODEOBJ_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeObjClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeObj_Info;            // Forward Reference




static
bool            NodeObjClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEOBJ_CLASS == classID) {
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
uint16_t		NodeObjClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEOBJ_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEOBJ_CLASS_VTBL    class_Vtbl = {
    {
        &NodeObj_Info,
        NodeObjClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeObj_Class,
        NodeObjClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeObjClass_QueryInfo,
        NULL                        // NodeObjClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODEOBJ_CLASS_DATA  NodeObj_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODEOBJ_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEOBJ_SINGLETON
NODEOBJ_DATA *     NodeObj_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeObj_ClassObj.pSingleton);
}


bool            NodeObj_setSingleton (
    NODEOBJ_DATA       *pValue
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
    if (NodeObj_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeObj_ClassObj.pSingleton));
    }
    NodeObj_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEOBJ_DATA *     NodeObj_Shared (
    void
)
{
    NODEOBJ_DATA       *this = (OBJ_ID)(NodeObj_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeObj_New( );
        NodeObj_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeObj_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeObj_SharedReset (
    void
)
{
    NODEOBJ_DATA       *this = (OBJ_ID)(NodeObj_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeObj_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeObjClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEOBJ_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEOBJ_DATA);
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
                        return (void *)&NodeObj_Info;
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
                        return NodeObj_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeObjClass_WhoAmI;
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
bool            NodeObj_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEOBJ == classID) {
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
void            NodeObj_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeObj_Class (
    void
)
{
    return (OBJ_ID)&NodeObj_ClassObj;
}


static
uint16_t		NodeObj_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEOBJ;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODEOBJ_VTBL     NodeObj_Vtbl = {
    {
        &NodeObj_Info,
        NodeObj_IsKindOf,
#ifdef  NODEOBJ_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeObj_Dealloc,
        NodeObj_Class,
        NodeObj_WhoAmI,
        (P_OBJ_QUERYINFO)NodeObj_QueryInfo,
        (P_OBJ_TOSTRING)NodeObj_ToDebugString,
        NULL,			// NodeObj_Enable,
        NULL,			// NodeObj_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeObj_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeObj_Compare,
        NULL, 			// (P_OBJ_PTR)NodeObj_Copy,
        NULL, 			// (P_OBJ_PTR)NodeObj_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeObj_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeObj_IsEnabled,
 
};



static
const
OBJ_INFO        NodeObj_Info = {
    "NodeObj",
    "Object Node",
    (OBJ_DATA *)&NodeObj_ClassObj,
    (OBJ_DATA *)&NodeBase_ClassObj,
    (OBJ_IUNKNOWN *)&NodeObj_Vtbl,
    sizeof(NODEOBJ_DATA)
};





