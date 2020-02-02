// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeBase'
//	Generated 12/18/2019 23:30:06


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




#define			NODEBASE_OBJECT_C	    1
#include        <NodeBase_internal.h>
#ifdef  NODEBASE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeBase_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEBASE_SINGLETON
    volatile
    NODEBASE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeBaseClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeBase_Info;            // Forward Reference




static
bool            NodeBaseClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NODEBASE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NodeBase_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		NodeBaseClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEBASE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEBASE_CLASS_VTBL    class_Vtbl = {
    {
        &NodeBase_Info,
        NodeBaseClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeBase_Class,
        NodeBaseClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeBaseClass_QueryInfo,
        NULL                        // NodeBaseClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODEBASE_CLASS_DATA  NodeBase_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODEBASE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEBASE_SINGLETON
NODEBASE_DATA *     NodeBase_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeBase_ClassObj.pSingleton);
}


bool            NodeBase_setSingleton (
    NODEBASE_DATA       *pValue
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
    if (NodeBase_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeBase_ClassObj.pSingleton));
    }
    NodeBase_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEBASE_DATA *     NodeBase_Shared (
    void
)
{
    NODEBASE_DATA       *this = (OBJ_ID)(NodeBase_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeBase_New( );
        NodeBase_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeBase_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeBase_SharedReset (
    void
)
{
    NODEBASE_DATA       *this = (OBJ_ID)(NodeBase_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeBase_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeBaseClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEBASE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEBASE_DATA);
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
                        return (void *)&NodeBase_Info;
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
                        return NodeBase_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return NodeBase_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeBaseClass_WhoAmI;
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
bool            NodeBase_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NODEBASE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NodeBase_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        pInfo = obj_getInfo(pObj);
        return pInfo->pDefaultVtbls->pIsKindOf(classID);
    }
    
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            NodeBase_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeBase_Class (
    void
)
{
    return (OBJ_ID)&NodeBase_ClassObj;
}


static
uint16_t		NodeBase_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEBASE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODEBASE_VTBL     NodeBase_Vtbl = {
    {
        &NodeBase_Info,
        NodeBase_IsKindOf,
#ifdef  NODEBASE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeBase_Dealloc,
        NodeBase_Class,
        NodeBase_WhoAmI,
        (P_OBJ_QUERYINFO)NodeBase_QueryInfo,
        (P_OBJ_TOSTRING)NodeBase_ToDebugString,
        NULL,			// NodeBase_Enable,
        NULL,			// NodeBase_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeBase_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeBase_Compare,
        NULL, 			// (P_OBJ_PTR)NodeBase_Copy,
        NULL, 			// (P_OBJ_PTR)NodeBase_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeBase_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeBase_IsEnabled,
 
};



static
const
OBJ_INFO        NodeBase_Info = {
    "NodeBase",
    "NodeBase",	// <-- Fill in description
    (OBJ_DATA *)&NodeBase_ClassObj,
    (OBJ_DATA *)&Node_ClassObj,
    (OBJ_IUNKNOWN *)&NodeBase_Vtbl,
    sizeof(NODEBASE_DATA)
};





