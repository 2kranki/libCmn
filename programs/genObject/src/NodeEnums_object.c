// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'NodeEnums'
//  Generated 11/22/2021 12:36:34


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




#define         NODEENUMS_OBJECT_C       1
#include        <NodeEnums_internal.h>
#ifdef  NODEENUMS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeEnums_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEENUMS_SINGLETON
    volatile
    NODEENUMS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeEnumsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeEnums_Info;            // Forward Reference




static
bool            NodeEnumsClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NODEENUMS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NodeEnums_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        NodeEnumsClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEENUMS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEENUMS_CLASS_VTBL    class_Vtbl = {
    {
        &NodeEnums_Info,
        NodeEnumsClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeEnums_Class,
        NodeEnumsClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeEnumsClass_QueryInfo,
        NULL                        // NodeEnumsClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

NODEENUMS_CLASS_DATA  NodeEnums_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODEENUMS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEENUMS_SINGLETON
extern
const
NODEENUMS_VTBL       NodeEnums_VtblShared;


NODEENUMS_DATA *     NodeEnums_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeEnums_ClassObj.pSingleton);
}


bool            NodeEnums_setSingleton (
    NODEENUMS_DATA       *pValue
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
    if (NodeEnums_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeEnums_ClassObj.pSingleton));
    }
    NodeEnums_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEENUMS_DATA *     NodeEnums_Shared (
    void
)
{
    NODEENUMS_DATA       *this = (OBJ_ID)(NodeEnums_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeEnums_New( );
        obj_setVtbl(this, (void *)&NodeEnums_VtblShared);
        NodeEnums_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeEnums_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeEnums_SharedReset (
    void
)
{
    NODEENUMS_DATA       *this = (OBJ_ID)(NodeEnums_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&NodeEnums_Vtbl);
        obj_Release(this);
        NodeEnums_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeEnumsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEENUMS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEENUMS_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&NodeEnums_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&NodeEnums_Info.pClassSuperObject;
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
                        return NodeEnums_New;
                    }
                    break;
                    
                case 'P':
#ifdef  NODEENUMS_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return NodeEnums_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return NodeEnums_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  NODEENUMS_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return NodeEnums_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return NodeEnums_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeEnumsClass_WhoAmI;
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
bool            NodeEnums_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NODEENUMS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NodeEnums_Class())->pClassSuperObject;
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
void            NodeEnums_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeEnums_Class (
    void
)
{
    return (OBJ_ID)&NodeEnums_ClassObj;
}


static
uint16_t        NodeEnums_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEENUMS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  NODEENUMS_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
NODEENUMS_VTBL     NodeEnums_VtblShared = {
    {
        &NodeEnums_Info,
        NodeEnums_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NodeEnums_Dealloc,
        NodeEnums_Class,
        NodeEnums_WhoAmI,
        (P_OBJ_QUERYINFO)NodeEnums_QueryInfo,
        (P_OBJ_TOSTRING)NodeEnums_ToDebugString,
        NULL,           // NodeEnums_Enable,
        NULL,           // NodeEnums_Disable,
        NULL,           // (P_OBJ_ASSIGN)NodeEnums_Assign,
        NULL,           // (P_OBJ_COMPARE)NodeEnums_Compare,
        NULL,           // (P_OBJ_PTR)NodeEnums_Copy,
        NULL,           // (P_OBJ_PTR)NodeEnums_DeepCopy,
        NULL            // (P_OBJ_HASH)NodeEnums_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeEnums_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
NODEENUMS_VTBL     NodeEnums_Vtbl = {
    {
        &NodeEnums_Info,
        NodeEnums_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        NodeEnums_Dealloc,
        NodeEnums_Class,
        NodeEnums_WhoAmI,
        (P_OBJ_QUERYINFO)NodeEnums_QueryInfo,
        (P_OBJ_TOSTRING)NodeEnums_ToDebugString,
        NULL,           // NodeEnums_Enable,
        NULL,           // NodeEnums_Disable,
        NULL,           // (P_OBJ_ASSIGN)NodeEnums_Assign,
        NULL,           // (P_OBJ_COMPARE)NodeEnums_Compare,
        NULL,           // (P_OBJ_PTR)NodeEnums_Copy,
        NULL,           // (P_OBJ_PTR)NodeEnums_DeepCopy,
        NULL            // (P_OBJ_HASH)NodeEnums_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeEnums_IsEnabled,
 
};



static
const
OBJ_INFO        NodeEnums_Info = {
    "NodeEnums",
    "Enumeration File Generation",
    (OBJ_DATA *)&NodeEnums_ClassObj,
    (OBJ_DATA *)&NodeEnums_ClassObj,
    (OBJ_IUNKNOWN *)&NodeEnums_Vtbl,
    sizeof(NODEENUMS_DATA)
};





