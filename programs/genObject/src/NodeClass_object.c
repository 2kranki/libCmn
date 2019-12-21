// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeClass'
//	Generated 12/18/2019 23:30:16


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




#define			NODECLASS_OBJECT_C	    1
#include        <NodeClass_internal.h>
#ifdef  NODECLASS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeClass_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODECLASS_SINGLETON
    volatile
    NODECLASS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeClassClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeClass_Info;            // Forward Reference




static
bool            NodeClassClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NODECLASS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NodeClass_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		NodeClassClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODECLASS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODECLASS_CLASS_VTBL    class_Vtbl = {
    {
        &NodeClass_Info,
        NodeClassClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeClass_Class,
        NodeClassClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeClassClass_QueryInfo,
        NULL                        // NodeClassClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODECLASS_CLASS_DATA  NodeClass_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODECLASS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODECLASS_SINGLETON
NODECLASS_DATA *     NodeClass_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeClass_ClassObj.pSingleton);
}


bool            NodeClass_setSingleton (
    NODECLASS_DATA       *pValue
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
    if (NodeClass_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeClass_ClassObj.pSingleton));
    }
    NodeClass_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODECLASS_DATA *     NodeClass_Shared (
    void
)
{
    NODECLASS_DATA       *this = (OBJ_ID)(NodeClass_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeClass_New( );
        NodeClass_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeClass_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeClass_SharedReset (
    void
)
{
    NODECLASS_DATA       *this = (OBJ_ID)(NodeClass_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeClass_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeClassClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODECLASS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODECLASS_DATA);
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
                        return (void *)&NodeClass_Info;
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
                        return NodeClass_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return NodeClass_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeClassClass_WhoAmI;
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
bool            NodeClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NODECLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NodeClass_Class())->pClassSuperObject;
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
void            NodeClass_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeClass_Class (
    void
)
{
    return (OBJ_ID)&NodeClass_ClassObj;
}


static
uint16_t		NodeClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODECLASS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODECLASS_VTBL     NodeClass_Vtbl = {
    {
        &NodeClass_Info,
        NodeClass_IsKindOf,
#ifdef  NODECLASS_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeClass_Dealloc,
        NodeClass_Class,
        NodeClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeClass_QueryInfo,
        (P_OBJ_TOSTRING)NodeClass_ToDebugString,
        NULL,			// NodeClass_Enable,
        NULL,			// NodeClass_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeClass_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeClass_Compare,
        NULL, 			// (P_OBJ_PTR)NodeClass_Copy,
        NULL, 			// (P_OBJ_PTR)NodeClass_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeClass_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeClass_IsEnabled,
 
};



static
const
OBJ_INFO        NodeClass_Info = {
    "NodeClass",
    "NodeClass",	// <-- Fill in description
    (OBJ_DATA *)&NodeClass_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&NodeClass_Vtbl,
    sizeof(NODECLASS_DATA)
};





