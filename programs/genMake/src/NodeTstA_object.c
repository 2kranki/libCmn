// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeTstA'
//	Generated 11/10/2019 17:54:48


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




#define			NODETSTA_OBJECT_C	    1
#include        <NodeTstA_internal.h>
#ifdef  NODETSTA_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeTstA_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODETSTA_SINGLETON
    volatile
    NODETSTA_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeTstAClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeTstA_Info;            // Forward Reference




static
bool            NodeTstAClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODETSTA_CLASS == classID) {
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
uint16_t		NodeTstAClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODETSTA_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODETSTA_CLASS_VTBL    class_Vtbl = {
    {
        &NodeTstA_Info,
        NodeTstAClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeTstA_Class,
        NodeTstAClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeTstAClass_QueryInfo,
        NULL                        // NodeTstAClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODETSTA_CLASS_DATA  NodeTstA_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODETSTA_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODETSTA_SINGLETON
NODETSTA_DATA *     NodeTstA_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeTstA_ClassObj.pSingleton);
}


bool            NodeTstA_setSingleton (
    NODETSTA_DATA       *pValue
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
    if (NodeTstA_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeTstA_ClassObj.pSingleton));
    }
    NodeTstA_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODETSTA_DATA *     NodeTstA_Shared (
    void
)
{
    NODETSTA_DATA       *this = (OBJ_ID)(NodeTstA_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeTstA_New( );
        NodeTstA_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeTstA_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeTstA_SharedReset (
    void
)
{
    NODETSTA_DATA       *this = (OBJ_ID)(NodeTstA_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeTstA_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeTstAClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODETSTA_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODETSTA_DATA);
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
                        return (void *)&NodeTstA_Info;
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
                        return NodeTstA_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeTstAClass_WhoAmI;
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
bool            NodeTstA_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODETSTA == classID) {
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
void            NodeTstA_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeTstA_Class (
    void
)
{
    return (OBJ_ID)&NodeTstA_ClassObj;
}


static
uint16_t		NodeTstA_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODETSTA;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODETSTA_VTBL     NodeTstA_Vtbl = {
    {
        &NodeTstA_Info,
        NodeTstA_IsKindOf,
#ifdef  NODETSTA_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeTstA_Dealloc,
        NodeTstA_Class,
        NodeTstA_WhoAmI,
        (P_OBJ_QUERYINFO)NodeTstA_QueryInfo,
        (P_OBJ_TOSTRING)NodeTstA_ToDebugString,
        NULL,			// NodeTstA_Enable,
        NULL,			// NodeTstA_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeTstA_Assign,
        (P_OBJ_COMPARE)NodeTstA_Compare,
        NULL, 			// (P_OBJ_PTR)NodeTstA_Copy,
        NULL, 			// (P_OBJ_PTR)NodeTstA_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeTstA_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeTstA_IsEnabled,
 
};



static
const
OBJ_INFO        NodeTstA_Info = {
    "NodeTstA",
    "Node Test A",
    (OBJ_DATA *)&NodeTstA_ClassObj,
    (OBJ_DATA *)&NodeBase_ClassObj,
    (OBJ_IUNKNOWN *)&NodeTstA_Vtbl,
    sizeof(NODETSTA_DATA)
};





