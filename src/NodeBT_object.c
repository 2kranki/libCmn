// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeBT'
//	Generated 01/10/2020 16:43:13


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




#define			NODEBT_OBJECT_C	    1
#include        <NodeBT_internal.h>
#ifdef  NODEBT_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeBT_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEBT_SINGLETON
    volatile
    NODEBT_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeBTClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeBT_Info;            // Forward Reference




static
bool            NodeBTClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NODEBT_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NodeBT_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		NodeBTClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEBT_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEBT_CLASS_VTBL    class_Vtbl = {
    {
        &NodeBT_Info,
        NodeBTClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeBT_Class,
        NodeBTClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeBTClass_QueryInfo,
        NULL                        // NodeBTClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODEBT_CLASS_DATA  NodeBT_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODEBT_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEBT_SINGLETON
NODEBT_DATA *     NodeBT_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeBT_ClassObj.pSingleton);
}


bool            NodeBT_setSingleton (
    NODEBT_DATA       *pValue
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
    if (NodeBT_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeBT_ClassObj.pSingleton));
    }
    NodeBT_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEBT_DATA *     NodeBT_Shared (
    void
)
{
    NODEBT_DATA       *this = (OBJ_ID)(NodeBT_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeBT_New( );
        NodeBT_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeBT_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeBT_SharedReset (
    void
)
{
    NODEBT_DATA       *this = (OBJ_ID)(NodeBT_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeBT_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeBTClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEBT_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEBT_DATA);
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
                        return (void *)&NodeBT_Info;
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
                        return NodeBT_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return NodeBT_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeBTClass_WhoAmI;
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
bool            NodeBT_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NODEBT == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NodeBT_Class())->pClassSuperObject;
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
void            NodeBT_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeBT_Class (
    void
)
{
    return (OBJ_ID)&NodeBT_ClassObj;
}


static
uint16_t		NodeBT_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEBT;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODEBT_VTBL     NodeBT_Vtbl = {
    {
        &NodeBT_Info,
        NodeBT_IsKindOf,
#ifdef  NODEBT_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeBT_Dealloc,
        NodeBT_Class,
        NodeBT_WhoAmI,
        (P_OBJ_QUERYINFO)NodeBT_QueryInfo,
        (P_OBJ_TOSTRING)NodeBT_ToDebugString,
        NULL,			// NodeBT_Enable,
        NULL,			// NodeBT_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeBT_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeBT_Compare,
        NULL, 			// (P_OBJ_PTR)NodeBT_Copy,
        NULL, 			// (P_OBJ_PTR)NodeBT_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeBT_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeBT_IsEnabled,
 
};



static
const
OBJ_INFO        NodeBT_Info = {
    "NodeBT",
    "A Red-Black Binary Tree of Nodes",
    (OBJ_DATA *)&NodeBT_ClassObj,
    (OBJ_DATA *)&Blocks_ClassObj,
    (OBJ_IUNKNOWN *)&NodeBT_Vtbl,
    sizeof(NODEBT_DATA)
};





