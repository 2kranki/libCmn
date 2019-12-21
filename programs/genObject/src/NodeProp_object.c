// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeProp'
//	Generated 12/18/2019 23:31:17


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




#define			NODEPROP_OBJECT_C	    1
#include        <NodeProp_internal.h>
#ifdef  NODEPROP_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeProp_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEPROP_SINGLETON
    volatile
    NODEPROP_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodePropClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeProp_Info;            // Forward Reference




static
bool            NodePropClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NODEPROP_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NodeProp_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		NodePropClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEPROP_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEPROP_CLASS_VTBL    class_Vtbl = {
    {
        &NodeProp_Info,
        NodePropClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeProp_Class,
        NodePropClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodePropClass_QueryInfo,
        NULL                        // NodePropClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODEPROP_CLASS_DATA  NodeProp_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODEPROP_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEPROP_SINGLETON
NODEPROP_DATA *     NodeProp_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeProp_ClassObj.pSingleton);
}


bool            NodeProp_setSingleton (
    NODEPROP_DATA       *pValue
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
    if (NodeProp_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeProp_ClassObj.pSingleton));
    }
    NodeProp_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEPROP_DATA *     NodeProp_Shared (
    void
)
{
    NODEPROP_DATA       *this = (OBJ_ID)(NodeProp_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeProp_New( );
        NodeProp_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeProp_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeProp_SharedReset (
    void
)
{
    NODEPROP_DATA       *this = (OBJ_ID)(NodeProp_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeProp_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodePropClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEPROP_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEPROP_DATA);
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
                        return (void *)&NodeProp_Info;
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
                        return NodeProp_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return NodeProp_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodePropClass_WhoAmI;
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
bool            NodeProp_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NODEPROP == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NodeProp_Class())->pClassSuperObject;
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
void            NodeProp_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeProp_Class (
    void
)
{
    return (OBJ_ID)&NodeProp_ClassObj;
}


static
uint16_t		NodeProp_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEPROP;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODEPROP_VTBL     NodeProp_Vtbl = {
    {
        &NodeProp_Info,
        NodeProp_IsKindOf,
#ifdef  NODEPROP_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeProp_Dealloc,
        NodeProp_Class,
        NodeProp_WhoAmI,
        (P_OBJ_QUERYINFO)NodeProp_QueryInfo,
        (P_OBJ_TOSTRING)NodeProp_ToDebugString,
        NULL,			// NodeProp_Enable,
        NULL,			// NodeProp_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeProp_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeProp_Compare,
        NULL, 			// (P_OBJ_PTR)NodeProp_Copy,
        NULL, 			// (P_OBJ_PTR)NodeProp_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeProp_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeProp_IsEnabled,
 
};



static
const
OBJ_INFO        NodeProp_Info = {
    "NodeProp",
    "NodeProp",	// <-- Fill in description
    (OBJ_DATA *)&NodeProp_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&NodeProp_Vtbl,
    sizeof(NODEPROP_DATA)
};





