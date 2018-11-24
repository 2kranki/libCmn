// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeList'
//	Generated 11/23/2018 17:15:11


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




#define			NODELIST_OBJECT_C	    1
#include        <nodeList_internal.h>
#ifdef  NODELIST_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct nodeList_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODELIST_SINGLETON
    volatile
    NODELIST_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          nodeListClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        nodeList_Info;            // Forward Reference




static
bool            nodeListClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODELIST_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJLIST_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_BLOCKS_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		nodeListClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODELIST_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODELIST_CLASS_VTBL    class_Vtbl = {
    {
        &nodeList_Info,
        nodeListClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        nodeList_Class,
        nodeListClass_WhoAmI,
        (P_OBJ_QUERYINFO)nodeListClass_QueryInfo,
        NULL                        // nodeListClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODELIST_CLASS_DATA  nodeList_ClassObj = {
    {(const OBJ_IUNKNOWN *)&class_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_NODELIST_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODELIST_SINGLETON
NODELIST_DATA *     nodeList_getSingleton(
    void
)
{
    return (OBJ_ID)(nodeList_ClassObj.pSingleton);
}


bool            nodeList_setSingleton(
    NODELIST_DATA       *pValue
)
{
    PSXLOCK_DATA    *pLock = OBJ_NIL;
    bool            fRc;
    
    pLock = psxLock_New();
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
    if (nodeList_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(nodeList_ClassObj.pSingleton));
    }
    nodeList_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODELIST_DATA *     nodeList_Shared(
    void
)
{
    NODELIST_DATA       *this = (OBJ_ID)(nodeList_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = nodeList_New( );
        nodeList_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // nodeList_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            nodeList_SharedReset(
    void
)
{
    NODELIST_DATA       *this = (OBJ_ID)(nodeList_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        nodeList_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          nodeListClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODELIST_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODELIST_DATA);
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
                        return (void *)&nodeList_Info;
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
                        return nodeList_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return nodeListClass_WhoAmI;
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
bool            nodeList_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODELIST == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJLIST == classID) {
        return true;
    }
    if (OBJ_IDENT_BLOCKS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            nodeList_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeList_Class(
    void
)
{
    return (OBJ_ID)&nodeList_ClassObj;
}


static
uint16_t		nodeList_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODELIST;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODELIST_VTBL     nodeList_Vtbl = {
    {
        &nodeList_Info,
        nodeList_IsKindOf,
#ifdef  NODELIST_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        nodeList_Dealloc,
        nodeList_Class,
        nodeList_WhoAmI,
        (P_OBJ_QUERYINFO)nodeList_QueryInfo,
        (P_OBJ_TOSTRING)nodeList_ToDebugString,
        NULL,			// nodeList_Enable,
        NULL,			// nodeList_Disable,
        NULL,			// (P_OBJ_ASSIGN)nodeList_Assign,
        NULL,			// (P_OBJ_COMPARE)nodeList_Compare,
        NULL, 			// (P_OBJ_PTR)nodeList_Copy,
        NULL, 			// (P_OBJ_PTR)nodeList_DeepCopy,
        NULL 			// (P_OBJ_HASH)nodeList_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //nodeList_IsEnabled,
 
};



static
const
OBJ_INFO        nodeList_Info = {
    "nodeList",
    "List of Nodes",
    (OBJ_DATA *)&nodeList_ClassObj,
    (OBJ_DATA *)&objList_ClassObj,
    (OBJ_IUNKNOWN *)&nodeList_Vtbl,
    sizeof(NODELIST_DATA)

};





