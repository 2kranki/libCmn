// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeLink'
//	Generated 01/12/2020 10:31:46


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




#define			NODELINK_OBJECT_C	    1
#include        <NodeLink_internal.h>
#ifdef  NODELINK_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeLink_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODELINK_SINGLETON
    volatile
    NODELINK_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeLinkClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeLink_Info;            // Forward Reference




static
bool            NodeLinkClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NODELINK_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NodeLink_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		NodeLinkClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODELINK_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODELINK_CLASS_VTBL    class_Vtbl = {
    {
        &NodeLink_Info,
        NodeLinkClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeLink_Class,
        NodeLinkClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeLinkClass_QueryInfo,
        NULL                        // NodeLinkClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODELINK_CLASS_DATA  NodeLink_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODELINK_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODELINK_SINGLETON
NODELINK_DATA *     NodeLink_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeLink_ClassObj.pSingleton);
}


bool            NodeLink_setSingleton (
    NODELINK_DATA       *pValue
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
    if (NodeLink_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeLink_ClassObj.pSingleton));
    }
    NodeLink_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODELINK_DATA *     NodeLink_Shared (
    void
)
{
    NODELINK_DATA       *this = (OBJ_ID)(NodeLink_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeLink_New( );
        NodeLink_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeLink_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeLink_SharedReset (
    void
)
{
    NODELINK_DATA       *this = (OBJ_ID)(NodeLink_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeLink_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeLinkClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODELINK_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODELINK_DATA);
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
                        return (void *)&NodeLink_Info;
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
                        return NodeLink_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return NodeLink_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeLinkClass_WhoAmI;
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
bool            NodeLink_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NODELINK == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NodeLink_Class())->pClassSuperObject;
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
void            NodeLink_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeLink_Class (
    void
)
{
    return (OBJ_ID)&NodeLink_ClassObj;
}


static
uint16_t		NodeLink_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODELINK;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODELINK_VTBL     NodeLink_Vtbl = {
    {
        &NodeLink_Info,
        NodeLink_IsKindOf,
#ifdef  NODELINK_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeLink_Dealloc,
        NodeLink_Class,
        NodeLink_WhoAmI,
        (P_OBJ_QUERYINFO)NodeLink_QueryInfo,
        (P_OBJ_TOSTRING)NodeLink_ToDebugString,
        NULL,			// NodeLink_Enable,
        NULL,			// NodeLink_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeLink_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeLink_Compare,
        NULL, 			// (P_OBJ_PTR)NodeLink_Copy,
        NULL, 			// (P_OBJ_PTR)NodeLink_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeLink_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeLink_IsEnabled,
 
};



static
const
OBJ_INFO        NodeLink_Info = {
    "NodeLink",
    "A Node with Integer Links",
    (OBJ_DATA *)&NodeLink_ClassObj,
    (OBJ_DATA *)&Node_ClassObj,
    (OBJ_IUNKNOWN *)&NodeLink_Vtbl,
    sizeof(NODELINK_DATA)
};





