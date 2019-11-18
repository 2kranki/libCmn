// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeRtn'
//	Generated 11/03/2019 08:11:37


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




#define			NODERTN_OBJECT_C	    1
#include        <NodeRtn_internal.h>
#ifdef  NODERTN_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeRtn_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODERTN_SINGLETON
    volatile
    NODERTN_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeRtnClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeRtn_Info;            // Forward Reference




static
bool            NodeRtnClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODERTN_CLASS == classID) {
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
uint16_t		NodeRtnClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODERTN_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODERTN_CLASS_VTBL    class_Vtbl = {
    {
        &NodeRtn_Info,
        NodeRtnClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeRtn_Class,
        NodeRtnClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeRtnClass_QueryInfo,
        NULL                        // NodeRtnClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODERTN_CLASS_DATA  NodeRtn_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODERTN_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODERTN_SINGLETON
NODERTN_DATA *     NodeRtn_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeRtn_ClassObj.pSingleton);
}


bool            NodeRtn_setSingleton (
    NODERTN_DATA       *pValue
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
    if (NodeRtn_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeRtn_ClassObj.pSingleton));
    }
    NodeRtn_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODERTN_DATA *     NodeRtn_Shared (
    void
)
{
    NODERTN_DATA       *this = (OBJ_ID)(NodeRtn_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeRtn_New( );
        NodeRtn_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeRtn_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeRtn_SharedReset (
    void
)
{
    NODERTN_DATA       *this = (OBJ_ID)(NodeRtn_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeRtn_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeRtnClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODERTN_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODERTN_DATA);
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
                        return (void *)&NodeRtn_Info;
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
                        return NodeRtn_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeRtnClass_WhoAmI;
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
bool            NodeRtn_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODERTN == classID) {
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
void            NodeRtn_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeRtn_Class (
    void
)
{
    return (OBJ_ID)&NodeRtn_ClassObj;
}


static
uint16_t		NodeRtn_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODERTN;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODERTN_VTBL     NodeRtn_Vtbl = {
    {
        &NodeRtn_Info,
        NodeRtn_IsKindOf,
#ifdef  NODERTN_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeRtn_Dealloc,
        NodeRtn_Class,
        NodeRtn_WhoAmI,
        (P_OBJ_QUERYINFO)NodeRtn_QueryInfo,
        (P_OBJ_TOSTRING)NodeRtn_ToDebugString,
        NULL,			// NodeRtn_Enable,
        NULL,			// NodeRtn_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeRtn_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeRtn_Compare,
        NULL, 			// (P_OBJ_PTR)NodeRtn_Copy,
        NULL, 			// (P_OBJ_PTR)NodeRtn_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeRtn_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeRtn_IsEnabled,
 
};



static
const
OBJ_INFO        NodeRtn_Info = {
    "NodeRtn",
    "NodeRtn",	// <-- Fill in description
    (OBJ_DATA *)&NodeRtn_ClassObj,
    (OBJ_DATA *)&NodeBase_ClassObj,
    (OBJ_IUNKNOWN *)&NodeRtn_Vtbl,
    sizeof(NODERTN_DATA)
};





