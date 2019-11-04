// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeLib'
//	Generated 11/03/2019 08:12:07


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




#define			NODELIB_OBJECT_C	    1
#include        <NodeLib_internal.h>
#ifdef  NODELIB_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeLib_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODELIB_SINGLETON
    volatile
    NODELIB_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeLibClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeLib_Info;            // Forward Reference




static
bool            NodeLibClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODELIB_CLASS == classID) {
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
uint16_t		NodeLibClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODELIB_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODELIB_CLASS_VTBL    class_Vtbl = {
    {
        &NodeLib_Info,
        NodeLibClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeLib_Class,
        NodeLibClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeLibClass_QueryInfo,
        NULL                        // NodeLibClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODELIB_CLASS_DATA  NodeLib_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODELIB_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODELIB_SINGLETON
NODELIB_DATA *     NodeLib_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeLib_ClassObj.pSingleton);
}


bool            NodeLib_setSingleton (
    NODELIB_DATA       *pValue
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
    if (NodeLib_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeLib_ClassObj.pSingleton));
    }
    NodeLib_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODELIB_DATA *     NodeLib_Shared (
    void
)
{
    NODELIB_DATA       *this = (OBJ_ID)(NodeLib_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeLib_New( );
        NodeLib_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeLib_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeLib_SharedReset (
    void
)
{
    NODELIB_DATA       *this = (OBJ_ID)(NodeLib_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeLib_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeLibClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODELIB_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODELIB_DATA);
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
                        return (void *)&NodeLib_Info;
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
                        return NodeLib_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeLibClass_WhoAmI;
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
bool            NodeLib_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODELIB == classID) {
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
void            NodeLib_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeLib_Class (
    void
)
{
    return (OBJ_ID)&NodeLib_ClassObj;
}


static
uint16_t		NodeLib_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODELIB;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODELIB_VTBL     NodeLib_Vtbl = {
    {
        &NodeLib_Info,
        NodeLib_IsKindOf,
#ifdef  NODELIB_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeLib_Dealloc,
        NodeLib_Class,
        NodeLib_WhoAmI,
        (P_OBJ_QUERYINFO)NodeLib_QueryInfo,
        (P_OBJ_TOSTRING)NodeLib_ToDebugString,
        NULL,			// NodeLib_Enable,
        NULL,			// NodeLib_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeLib_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeLib_Compare,
        NULL, 			// (P_OBJ_PTR)NodeLib_Copy,
        NULL, 			// (P_OBJ_PTR)NodeLib_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeLib_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeLib_IsEnabled,
 
};



static
const
OBJ_INFO        NodeLib_Info = {
    "NodeLib",
    "NodeLib",	// <-- Fill in description
    (OBJ_DATA *)&NodeLib_ClassObj,
    (OBJ_DATA *)&node_ClassObj,
    (OBJ_IUNKNOWN *)&NodeLib_Vtbl,
    sizeof(NODELIB_DATA)
};





