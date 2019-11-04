// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeTest'
//	Generated 11/03/2019 08:12:57


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




#define			NODETEST_OBJECT_C	    1
#include        <NodeTest_internal.h>
#ifdef  NODETEST_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeTest_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODETEST_SINGLETON
    volatile
    NODETEST_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeTestClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeTest_Info;            // Forward Reference




static
bool            NodeTestClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODETEST_CLASS == classID) {
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
uint16_t		NodeTestClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODETEST_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODETEST_CLASS_VTBL    class_Vtbl = {
    {
        &NodeTest_Info,
        NodeTestClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeTest_Class,
        NodeTestClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeTestClass_QueryInfo,
        NULL                        // NodeTestClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODETEST_CLASS_DATA  NodeTest_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODETEST_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODETEST_SINGLETON
NODETEST_DATA *     NodeTest_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeTest_ClassObj.pSingleton);
}


bool            NodeTest_setSingleton (
    NODETEST_DATA       *pValue
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
    if (NodeTest_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeTest_ClassObj.pSingleton));
    }
    NodeTest_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODETEST_DATA *     NodeTest_Shared (
    void
)
{
    NODETEST_DATA       *this = (OBJ_ID)(NodeTest_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeTest_New( );
        NodeTest_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeTest_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeTest_SharedReset (
    void
)
{
    NODETEST_DATA       *this = (OBJ_ID)(NodeTest_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeTest_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeTestClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODETEST_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODETEST_DATA);
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
                        return (void *)&NodeTest_Info;
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
                        return NodeTest_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeTestClass_WhoAmI;
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
bool            NodeTest_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODETEST == classID) {
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
void            NodeTest_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeTest_Class (
    void
)
{
    return (OBJ_ID)&NodeTest_ClassObj;
}


static
uint16_t		NodeTest_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODETEST;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODETEST_VTBL     NodeTest_Vtbl = {
    {
        &NodeTest_Info,
        NodeTest_IsKindOf,
#ifdef  NODETEST_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeTest_Dealloc,
        NodeTest_Class,
        NodeTest_WhoAmI,
        (P_OBJ_QUERYINFO)NodeTest_QueryInfo,
        (P_OBJ_TOSTRING)NodeTest_ToDebugString,
        NULL,			// NodeTest_Enable,
        NULL,			// NodeTest_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeTest_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeTest_Compare,
        NULL, 			// (P_OBJ_PTR)NodeTest_Copy,
        NULL, 			// (P_OBJ_PTR)NodeTest_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeTest_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeTest_IsEnabled,
 
};



static
const
OBJ_INFO        NodeTest_Info = {
    "NodeTest",
    "NodeTest",	// <-- Fill in description
    (OBJ_DATA *)&NodeTest_ClassObj,
    (OBJ_DATA *)&node_ClassObj,
    (OBJ_IUNKNOWN *)&NodeTest_Vtbl,
    sizeof(NODETEST_DATA)
};





