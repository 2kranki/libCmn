// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeRtnA'
//	Generated 11/10/2019 10:31:05


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




#define			NODERTNA_OBJECT_C	    1
#include        <NodeRtnA_internal.h>
#ifdef  NODERTNA_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeRtnA_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODERTNA_SINGLETON
    volatile
    NODERTNA_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeRtnAClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeRtnA_Info;            // Forward Reference




static
bool            NodeRtnAClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODERTNA_CLASS == classID) {
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
uint16_t		NodeRtnAClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODERTNA_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODERTNA_CLASS_VTBL    class_Vtbl = {
    {
        &NodeRtnA_Info,
        NodeRtnAClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeRtnA_Class,
        NodeRtnAClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeRtnAClass_QueryInfo,
        NULL                        // NodeRtnAClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODERTNA_CLASS_DATA  NodeRtnA_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODERTNA_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODERTNA_SINGLETON
NODERTNA_DATA *     NodeRtnA_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeRtnA_ClassObj.pSingleton);
}


bool            NodeRtnA_setSingleton (
    NODERTNA_DATA       *pValue
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
    if (NodeRtnA_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeRtnA_ClassObj.pSingleton));
    }
    NodeRtnA_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODERTNA_DATA *     NodeRtnA_Shared (
    void
)
{
    NODERTNA_DATA       *this = (OBJ_ID)(NodeRtnA_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeRtnA_New( );
        NodeRtnA_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeRtnA_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeRtnA_SharedReset (
    void
)
{
    NODERTNA_DATA       *this = (OBJ_ID)(NodeRtnA_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeRtnA_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeRtnAClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODERTNA_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODERTNA_DATA);
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
                        return (void *)&NodeRtnA_Info;
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
                        return NodeRtnA_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeRtnAClass_WhoAmI;
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
bool            NodeRtnA_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODERTNA == classID) {
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
void            NodeRtnA_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeRtnA_Class (
    void
)
{
    return (OBJ_ID)&NodeRtnA_ClassObj;
}


static
uint16_t		NodeRtnA_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODERTNA;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODERTNA_VTBL     NodeRtnA_Vtbl = {
    {
        &NodeRtnA_Info,
        NodeRtnA_IsKindOf,
#ifdef  NODERTNA_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeRtnA_Dealloc,
        NodeRtnA_Class,
        NodeRtnA_WhoAmI,
        (P_OBJ_QUERYINFO)NodeRtnA_QueryInfo,
        (P_OBJ_TOSTRING)NodeRtnA_ToDebugString,
        NULL,			// NodeRtnA_Enable,
        NULL,			// NodeRtnA_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeRtnA_Assign,
        (P_OBJ_COMPARE)NodeRtnA_Compare,
        NULL, 			// (P_OBJ_PTR)NodeRtnA_Copy,
        NULL, 			// (P_OBJ_PTR)NodeRtnA_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeRtnA_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeRtnA_IsEnabled,
 
};



static
const
OBJ_INFO        NodeRtnA_Info = {
    "NodeRtnA",
    "Routine Node",
    (OBJ_DATA *)&NodeRtnA_ClassObj,
    (OBJ_DATA *)&NodeBase_ClassObj,
    (OBJ_IUNKNOWN *)&NodeRtnA_Vtbl,
    sizeof(NODERTNA_DATA)
};





