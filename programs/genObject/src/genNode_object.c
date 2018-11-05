// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'genNode'
//	Generated 11/04/2018 19:07:17


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




#define			GENNODE_OBJECT_C	    1
#include        <genNode_internal.h>
#ifdef  GENNODE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct genNode_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  GENNODE_SINGLETON
    volatile
    GENNODE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          genNodeClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        genNode_Info;            // Forward Reference




static
bool            genNodeClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_GENNODE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		genNodeClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_GENNODE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
GENNODE_CLASS_VTBL    class_Vtbl = {
    {
        &genNode_Info,
        genNodeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        genNode_Class,
        genNodeClass_WhoAmI,
        (P_OBJ_QUERYINFO)genNodeClass_QueryInfo,
        NULL                        // genNodeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

GENNODE_CLASS_DATA  genNode_ClassObj = {
    {(const OBJ_IUNKNOWN *)&class_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_GENNODE_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  GENNODE_SINGLETON
GENNODE_DATA *     genNode_getSingleton(
    void
)
{
    return (OBJ_ID)(genNode_ClassObj.pSingleton);
}


bool            genNode_setSingleton(
    GENNODE_DATA       *pValue
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
    if (genNode_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(genNode_ClassObj.pSingleton));
    }
    genNode_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



GENNODE_DATA *     genNode_Shared(
    void
)
{
    GENNODE_DATA       *this = (OBJ_ID)(genNode_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = genNode_New( );
        genNode_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // genNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            genNode_SharedReset(
    void
)
{
    GENNODE_DATA       *this = (OBJ_ID)(genNode_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        genNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          genNodeClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    GENNODE_CLASS_DATA *this = objId;
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
                        return (void *)&genNode_Info;
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
                        return genNode_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return genNodeClass_WhoAmI;
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
bool            genNode_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_GENNODE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            genNode_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          genNode_Class(
    void
)
{
    return (OBJ_ID)&genNode_ClassObj;
}


static
uint16_t		genNode_WhoAmI(
    void
)
{
    return OBJ_IDENT_GENNODE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
GENNODE_VTBL     genNode_Vtbl = {
    {
        &genNode_Info,
        genNode_IsKindOf,
#ifdef  GENNODE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        genNode_Dealloc,
        genNode_Class,
        genNode_WhoAmI,
        (P_OBJ_QUERYINFO)genNode_QueryInfo,
        (P_OBJ_TOSTRING)genNode_ToDebugString,
        NULL,			// genNode_Enable,
        NULL,			// genNode_Disable,
        NULL,			// (P_OBJ_ASSIGN)genNode_Assign,
        NULL,			// (P_OBJ_COMPARE)genNode_Compare,
        NULL, 			// (P_OBJ_PTR)genNode_Copy,
        NULL, 			// (P_OBJ_PTR)genNode_DeepCopy,
        NULL 			// (P_OBJ_HASH)genNode_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //genNode_IsEnabled,
 
};



static
const
OBJ_INFO        genNode_Info = {
    "genNode",
    "genNode",	// <-- Fill in description
    (OBJ_DATA *)&genNode_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&genNode_Vtbl
};
#warning -- adjust super class object in Info above 
//			if object inherits from another class





