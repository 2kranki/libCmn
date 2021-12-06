// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'NodeTree'
//  Generated 11/26/2021 19:19:16


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




#define         NODETREE_OBJECT_C       1
#include        <NodeTree_internal.h>
#ifdef  NODETREE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeTree_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODETREE_SINGLETON
    volatile
    NODETREE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeTreeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeTree_Info;            // Forward Reference




static
bool            NodeTreeClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NODETREE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NodeTree_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        NodeTreeClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODETREE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODETREE_CLASS_VTBL    class_Vtbl = {
    {
        &NodeTree_Info,
        NodeTreeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeTree_Class,
        NodeTreeClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeTreeClass_QueryInfo,
        NULL                        // NodeTreeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

NODETREE_CLASS_DATA  NodeTree_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODETREE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODETREE_SINGLETON
extern
const
NODETREE_VTBL       NodeTree_VtblShared;


NODETREE_DATA *     NodeTree_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeTree_ClassObj.pSingleton);
}


bool            NodeTree_setSingleton (
    NODETREE_DATA       *pValue
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
    if (NodeTree_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeTree_ClassObj.pSingleton));
    }
    NodeTree_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODETREE_DATA *     NodeTree_Shared (
    void
)
{
    NODETREE_DATA       *this = (OBJ_ID)(NodeTree_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeTree_New( );
        obj_setVtbl(this, (void *)&NodeTree_VtblShared);
        NodeTree_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeTree_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeTree_SharedReset (
    void
)
{
    NODETREE_DATA       *this = (OBJ_ID)(NodeTree_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&NodeTree_Vtbl);
        obj_Release(this);
        NodeTree_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeTreeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODETREE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODETREE_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&NodeTree_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&NodeTree_Info.pClassSuperObject;
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
                        return NodeTree_New;
                    }
                    break;
                    
                case 'P':
#ifdef  NODETREE_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return NodeTree_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return NodeTree_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  NODETREE_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return NodeTree_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return NodeTree_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeTreeClass_WhoAmI;
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
bool            NodeTree_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NODETREE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NodeTree_Class())->pClassSuperObject;
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
void            NodeTree_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeTree_Class (
    void
)
{
    return (OBJ_ID)&NodeTree_ClassObj;
}


static
uint16_t        NodeTree_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODETREE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  NODETREE_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
NODETREE_VTBL     NodeTree_VtblShared = {
    {
        &NodeTree_Info,
        NodeTree_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NodeTree_Dealloc,
        NodeTree_Class,
        NodeTree_WhoAmI,
        (P_OBJ_QUERYINFO)NodeTree_QueryInfo,
        (P_OBJ_TOSTRING)NodeTree_ToDebugString,
        NULL,           // NodeTree_Enable,
        NULL,           // NodeTree_Disable,
        NULL,           // (P_OBJ_ASSIGN)NodeTree_Assign,
        NULL,           // (P_OBJ_COMPARE)NodeTree_Compare,
        NULL,           // (P_OBJ_PTR)NodeTree_Copy,
        NULL,           // (P_OBJ_PTR)NodeTree_DeepCopy,
        NULL            // (P_OBJ_HASH)NodeTree_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeTree_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
NODETREE_VTBL     NodeTree_Vtbl = {
    {
        &NodeTree_Info,
        NodeTree_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        NodeTree_Dealloc,
        NodeTree_Class,
        NodeTree_WhoAmI,
        (P_OBJ_QUERYINFO)NodeTree_QueryInfo,
        (P_OBJ_TOSTRING)NodeTree_ToDebugString,
        NULL,           // NodeTree_Enable,
        NULL,           // NodeTree_Disable,
        NULL,           // (P_OBJ_ASSIGN)NodeTree_Assign,
        NULL,           // (P_OBJ_COMPARE)NodeTree_Compare,
        NULL,           // (P_OBJ_PTR)NodeTree_Copy,
        NULL,           // (P_OBJ_PTR)NodeTree_DeepCopy,
        NULL            // (P_OBJ_HASH)NodeTree_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeTree_IsEnabled,
 
};



static
const
OBJ_INFO        NodeTree_Info = {
    "NodeTree",
    "An Unordered Tree of Nodes",
    (OBJ_DATA *)&NodeTree_ClassObj,
    (OBJ_DATA *)&Blocks_ClassObj,
    (OBJ_IUNKNOWN *)&NodeTree_Vtbl,
    sizeof(NODETREE_DATA)
};





