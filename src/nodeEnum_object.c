// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeEnum'
//	Generated 11/23/2018 21:35:43


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




#define			NODEENUM_OBJECT_C	    1
#include        <nodeEnum_internal.h>
#ifdef  NODEENUM_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct nodeEnum_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEENUM_SINGLETON
    volatile
    NODEENUM_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          nodeEnumClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        nodeEnum_Info;            // Forward Reference




static
bool            nodeEnumClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEENUM_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJENUM_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		nodeEnumClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODEENUM_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEENUM_CLASS_VTBL    class_Vtbl = {
    {
        &nodeEnum_Info,
        nodeEnumClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        nodeEnum_Class,
        nodeEnumClass_WhoAmI,
        (P_OBJ_QUERYINFO)nodeEnumClass_QueryInfo,
        NULL                        // nodeEnumClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODEENUM_CLASS_DATA  nodeEnum_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(NODEENUM_CLASS_DATA),        // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEENUM_SINGLETON
NODEENUM_DATA *     nodeEnum_getSingleton(
    void
)
{
    return (OBJ_ID)(nodeEnum_ClassObj.pSingleton);
}


bool            nodeEnum_setSingleton(
    NODEENUM_DATA       *pValue
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
    if (nodeEnum_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(nodeEnum_ClassObj.pSingleton));
    }
    nodeEnum_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEENUM_DATA *     nodeEnum_Shared(
    void
)
{
    NODEENUM_DATA       *this = (OBJ_ID)(nodeEnum_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = nodeEnum_New( );
        nodeEnum_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // nodeEnum_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            nodeEnum_SharedReset(
    void
)
{
    NODEENUM_DATA       *this = (OBJ_ID)(nodeEnum_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        nodeEnum_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          nodeEnumClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEENUM_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEENUM_DATA);
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
                        return (void *)&nodeEnum_Info;
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
                        return nodeEnum_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return nodeEnumClass_WhoAmI;
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
bool            nodeEnum_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEENUM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJENUM == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            nodeEnum_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeEnum_Class(
    void
)
{
    return (OBJ_ID)&nodeEnum_ClassObj;
}


static
uint16_t		nodeEnum_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODEENUM;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODEENUM_VTBL     nodeEnum_Vtbl = {
    {
        &nodeEnum_Info,
        nodeEnum_IsKindOf,
#ifdef  NODEENUM_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        nodeEnum_Dealloc,
        nodeEnum_Class,
        nodeEnum_WhoAmI,
        (P_OBJ_QUERYINFO)nodeEnum_QueryInfo,
        (P_OBJ_TOSTRING)nodeEnum_ToDebugString,
        NULL,			// nodeEnum_Enable,
        NULL,			// nodeEnum_Disable,
        NULL,			// (P_OBJ_ASSIGN)nodeEnum_Assign,
        NULL,			// (P_OBJ_COMPARE)nodeEnum_Compare,
        NULL, 			// (P_OBJ_PTR)nodeEnum_Copy,
        NULL, 			// (P_OBJ_PTR)nodeEnum_DeepCopy,
        NULL 			// (P_OBJ_HASH)nodeEnum_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //nodeEnum_IsEnabled,
 
};



static
const
OBJ_INFO        nodeEnum_Info = {
    "nodeEnum",
    "Node Emumerator",
    (OBJ_DATA *)&nodeEnum_ClassObj,
    (OBJ_DATA *)&objEnum_ClassObj,
    (OBJ_IUNKNOWN *)&nodeEnum_Vtbl,
    sizeof(NODEENUM_DATA)
};





