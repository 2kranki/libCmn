// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'NodeField'
//	Generated 12/18/2019 23:31:24


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




#define			NODEFIELD_OBJECT_C	    1
#include        <NodeField_internal.h>
#ifdef  NODEFIELD_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeField_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEFIELD_SINGLETON
    volatile
    NODEFIELD_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeFieldClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeField_Info;            // Forward Reference




static
bool            NodeFieldClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NODEFIELD_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NodeField_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		NodeFieldClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEFIELD_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEFIELD_CLASS_VTBL    class_Vtbl = {
    {
        &NodeField_Info,
        NodeFieldClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeField_Class,
        NodeFieldClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeFieldClass_QueryInfo,
        NULL                        // NodeFieldClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODEFIELD_CLASS_DATA  NodeField_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODEFIELD_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEFIELD_SINGLETON
NODEFIELD_DATA *     NodeField_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeField_ClassObj.pSingleton);
}


bool            NodeField_setSingleton (
    NODEFIELD_DATA       *pValue
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
    if (NodeField_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeField_ClassObj.pSingleton));
    }
    NodeField_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEFIELD_DATA *     NodeField_Shared (
    void
)
{
    NODEFIELD_DATA       *this = (OBJ_ID)(NodeField_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeField_New( );
        NodeField_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeField_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeField_SharedReset (
    void
)
{
    NODEFIELD_DATA       *this = (OBJ_ID)(NodeField_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        NodeField_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeFieldClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEFIELD_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEFIELD_DATA);
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
                        return (void *)&NodeField_Info;
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
                        return NodeField_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return NodeField_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeFieldClass_WhoAmI;
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
bool            NodeField_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NODEFIELD == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NodeField_Class())->pClassSuperObject;
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
void            NodeField_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeField_Class (
    void
)
{
    return (OBJ_ID)&NodeField_ClassObj;
}


static
uint16_t		NodeField_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODEFIELD;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODEFIELD_VTBL     NodeField_Vtbl = {
    {
        &NodeField_Info,
        NodeField_IsKindOf,
#ifdef  NODEFIELD_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        NodeField_Dealloc,
        NodeField_Class,
        NodeField_WhoAmI,
        (P_OBJ_QUERYINFO)NodeField_QueryInfo,
        (P_OBJ_TOSTRING)NodeField_ToDebugString,
        NULL,			// NodeField_Enable,
        NULL,			// NodeField_Disable,
        NULL,			// (P_OBJ_ASSIGN)NodeField_Assign,
        NULL,			// (P_OBJ_COMPARE)NodeField_Compare,
        NULL, 			// (P_OBJ_PTR)NodeField_Copy,
        NULL, 			// (P_OBJ_PTR)NodeField_DeepCopy,
        NULL 			// (P_OBJ_HASH)NodeField_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeField_IsEnabled,
 
};



static
const
OBJ_INFO        NodeField_Info = {
    "NodeField",
    "NodeField",	// <-- Fill in description
    (OBJ_DATA *)&NodeField_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&NodeField_Vtbl,
    sizeof(NODEFIELD_DATA)
};





