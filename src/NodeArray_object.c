// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeArray'
//	Generated 01/10/2020 13:58:02


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




#define			NODEARRAY_OBJECT_C	    1
#include        <NodeArray_internal.h>
#ifdef  NODEARRAY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeArray_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEARRAY_SINGLETON
    volatile
    NODEARRAY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeArray_Info;            // Forward Reference




static
bool            NodeArrayClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NODEARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NodeArray_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		NodeArrayClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEARRAY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEARRAY_CLASS_VTBL    class_Vtbl = {
    {
        &NodeArray_Info,
        NodeArrayClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeArray_Class,
        NodeArrayClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeArrayClass_QueryInfo,
        NULL                        // NodeArrayClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODEARRAY_CLASS_DATA  NodeArray_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODEARRAY_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEARRAY_SINGLETON
NODEARRAY_DATA *     NodeArray_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeArray_ClassObj.pSingleton);
}


bool            NodeArray_setSingleton (
    NODEARRAY_DATA       *pValue
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
    if (NodeArray_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeArray_ClassObj.pSingleton));
    }
    NodeArray_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEARRAY_DATA *     NodeArray_Shared (
    void
)
{
    NODEARRAY_DATA       *this = (OBJ_ID)(NodeArray_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeArray_New( );
        NodeArray_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeArray_SharedReset (
    void
)
{
    NODEARRAY_DATA       *this = (OBJ_ID)(NodeArray_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEARRAY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEARRAY_DATA);
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
                        return (void *)&NodeArray_Info;
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
                        return NodeArray_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return NodeArray_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeArrayClass_WhoAmI;
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
bool            NodeArray_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NODEARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NodeArray_Class())->pClassSuperObject;
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
void            NodeArray_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeArray_Class (
    void
)
{
    return (OBJ_ID)&NodeArray_ClassObj;
}


static
uint16_t		NodeArray_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEARRAY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODEARRAY_VTBL     NodeArray_Vtbl = {
    {
        &NodeArray_Info,
        NodeArray_IsKindOf,
#ifdef  NODEARRAY_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeArray_Dealloc,
        NodeArray_Class,
        NodeArray_WhoAmI,
        (P_OBJ_QUERYINFO)NodeArray_QueryInfo,
        (P_OBJ_TOSTRING)NodeArray_ToDebugString,
        NULL,			// NodeArray_Enable,
        NULL,			// NodeArray_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeArray_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeArray_Compare,
        NULL, 			// (P_OBJ_PTR)NodeArray_Copy,
        NULL, 			// (P_OBJ_PTR)NodeArray_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeArray_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeArray_IsEnabled,
 
};



static
const
OBJ_INFO        NodeArray_Info = {
    "NodeArray",
    "An Array of Nodes",
    (OBJ_DATA *)&NodeArray_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&NodeArray_Vtbl,
    sizeof(NODEARRAY_DATA)
};





