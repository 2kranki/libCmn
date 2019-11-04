// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeHdr'
//	Generated 11/03/2019 08:11:54


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




#define			NODEHDR_OBJECT_C	    1
#include        <NodeHdr_internal.h>
#ifdef  NODEHDR_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeHdr_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEHDR_SINGLETON
    volatile
    NODEHDR_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeHdrClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeHdr_Info;            // Forward Reference




static
bool            NodeHdrClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEHDR_CLASS == classID) {
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
uint16_t		NodeHdrClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEHDR_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEHDR_CLASS_VTBL    class_Vtbl = {
    {
        &NodeHdr_Info,
        NodeHdrClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeHdr_Class,
        NodeHdrClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeHdrClass_QueryInfo,
        NULL                        // NodeHdrClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODEHDR_CLASS_DATA  NodeHdr_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODEHDR_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEHDR_SINGLETON
NODEHDR_DATA *     NodeHdr_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeHdr_ClassObj.pSingleton);
}


bool            NodeHdr_setSingleton (
    NODEHDR_DATA       *pValue
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
    if (NodeHdr_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeHdr_ClassObj.pSingleton));
    }
    NodeHdr_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEHDR_DATA *     NodeHdr_Shared (
    void
)
{
    NODEHDR_DATA       *this = (OBJ_ID)(NodeHdr_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeHdr_New( );
        NodeHdr_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeHdr_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeHdr_SharedReset (
    void
)
{
    NODEHDR_DATA       *this = (OBJ_ID)(NodeHdr_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeHdr_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeHdrClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEHDR_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEHDR_DATA);
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
                        return (void *)&NodeHdr_Info;
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
                        return NodeHdr_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeHdrClass_WhoAmI;
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
bool            NodeHdr_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEHDR == classID) {
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
void            NodeHdr_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeHdr_Class (
    void
)
{
    return (OBJ_ID)&NodeHdr_ClassObj;
}


static
uint16_t		NodeHdr_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEHDR;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODEHDR_VTBL     NodeHdr_Vtbl = {
    {
        &NodeHdr_Info,
        NodeHdr_IsKindOf,
#ifdef  NODEHDR_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeHdr_Dealloc,
        NodeHdr_Class,
        NodeHdr_WhoAmI,
        (P_OBJ_QUERYINFO)NodeHdr_QueryInfo,
        (P_OBJ_TOSTRING)NodeHdr_ToDebugString,
        NULL,			// NodeHdr_Enable,
        NULL,			// NodeHdr_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeHdr_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeHdr_Compare,
        NULL, 			// (P_OBJ_PTR)NodeHdr_Copy,
        NULL, 			// (P_OBJ_PTR)NodeHdr_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeHdr_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeHdr_IsEnabled,
 
};



static
const
OBJ_INFO        NodeHdr_Info = {
    "NodeHdr",
    "NodeHdr",	// <-- Fill in description
    (OBJ_DATA *)&NodeHdr_ClassObj,
    (OBJ_DATA *)&node_ClassObj,
    (OBJ_IUNKNOWN *)&NodeHdr_Vtbl,
    sizeof(NODEHDR_DATA)
};





