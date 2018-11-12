// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeBTree'
//	Generated 11/12/2018 09:44:16


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




#define			NODEBTREE_OBJECT_C	    1
#include        <nodeBTree_internal.h>
#ifdef  NODEBTREE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct nodeBTree_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEBTREE_SINGLETON
    volatile
    NODEBTREE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          nodeBTreeClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        nodeBTree_Info;            // Forward Reference




static
bool            nodeBTreeClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEBTREE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		nodeBTreeClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODEBTREE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEBTREE_CLASS_VTBL    class_Vtbl = {
    {
        &nodeBTree_Info,
        nodeBTreeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        nodeBTree_Class,
        nodeBTreeClass_WhoAmI,
        (P_OBJ_QUERYINFO)nodeBTreeClass_QueryInfo,
        NULL                        // nodeBTreeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODEBTREE_CLASS_DATA  nodeBTree_ClassObj = {
    {(const OBJ_IUNKNOWN *)&class_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_NODEBTREE_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEBTREE_SINGLETON
NODEBTREE_DATA *     nodeBTree_getSingleton(
    void
)
{
    return (OBJ_ID)(nodeBTree_ClassObj.pSingleton);
}


bool            nodeBTree_setSingleton(
    NODEBTREE_DATA       *pValue
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
    if (nodeBTree_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(nodeBTree_ClassObj.pSingleton));
    }
    nodeBTree_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEBTREE_DATA *     nodeBTree_Shared(
    void
)
{
    NODEBTREE_DATA       *this = (OBJ_ID)(nodeBTree_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = nodeBTree_New( );
        nodeBTree_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // nodeBTree_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            nodeBTree_SharedReset(
    void
)
{
    NODEBTREE_DATA       *this = (OBJ_ID)(nodeBTree_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        nodeBTree_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          nodeBTreeClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEBTREE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
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
                        return (void *)&nodeBTree_Info;
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
                        return nodeBTree_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return nodeBTreeClass_WhoAmI;
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
bool            nodeBTree_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEBTREE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            nodeBTree_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeBTree_Class(
    void
)
{
    return (OBJ_ID)&nodeBTree_ClassObj;
}


static
uint16_t		nodeBTree_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODEBTREE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODEBTREE_VTBL     nodeBTree_Vtbl = {
    {
        &nodeBTree_Info,
        nodeBTree_IsKindOf,
#ifdef  NODEBTREE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        nodeBTree_Dealloc,
        nodeBTree_Class,
        nodeBTree_WhoAmI,
        (P_OBJ_QUERYINFO)nodeBTree_QueryInfo,
        (P_OBJ_TOSTRING)nodeBTree_ToDebugString,
        NULL,			// nodeBTree_Enable,
        NULL,			// nodeBTree_Disable,
        NULL,			// (P_OBJ_ASSIGN)nodeBTree_Assign,
        NULL,			// (P_OBJ_COMPARE)nodeBTree_Compare,
        NULL, 			// (P_OBJ_PTR)nodeBTree_Copy,
        NULL, 			// (P_OBJ_PTR)nodeBTree_DeepCopy,
        NULL 			// (P_OBJ_HASH)nodeBTree_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //nodeBTree_IsEnabled,
 
};



static
const
OBJ_INFO        nodeBTree_Info = {
    "nodeBTree",
    "Binary Tree of Nodes",
    (OBJ_DATA *)&nodeBTree_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&nodeBTree_Vtbl
};





