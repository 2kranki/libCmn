// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeLnkP'
//	Generated 11/19/2018 07:52:23


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




#define			NODELNKP_OBJECT_C	    1
#include        <nodeLnkP_internal.h>
#ifdef  NODELNKP_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct nodeLnkP_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODELNKP_SINGLETON
    volatile
    NODELNKP_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          nodeLnkPClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        nodeLnkP_Info;            // Forward Reference




static
bool            nodeLnkPClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODELNKP_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_NODE_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		nodeLnkPClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODELNKP_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODELNKP_CLASS_VTBL    class_Vtbl = {
    {
        &nodeLnkP_Info,
        nodeLnkPClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        nodeLnkP_Class,
        nodeLnkPClass_WhoAmI,
        (P_OBJ_QUERYINFO)nodeLnkPClass_QueryInfo,
        NULL                        // nodeLnkPClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODELNKP_CLASS_DATA  nodeLnkP_ClassObj = {
    {(const OBJ_IUNKNOWN *)&class_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_NODELNKP_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODELNKP_SINGLETON
NODELNKP_DATA *     nodeLnkP_getSingleton(
    void
)
{
    return (OBJ_ID)(nodeLnkP_ClassObj.pSingleton);
}


bool            nodeLnkP_setSingleton(
    NODELNKP_DATA       *pValue
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
    if (nodeLnkP_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(nodeLnkP_ClassObj.pSingleton));
    }
    nodeLnkP_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODELNKP_DATA *     nodeLnkP_Shared(
    void
)
{
    NODELNKP_DATA       *this = (OBJ_ID)(nodeLnkP_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = nodeLnkP_New( );
        nodeLnkP_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // nodeLnkP_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            nodeLnkP_SharedReset(
    void
)
{
    NODELNKP_DATA       *this = (OBJ_ID)(nodeLnkP_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        nodeLnkP_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          nodeLnkPClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODELNKP_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODELNKP_DATA);
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
                        return (void *)&nodeLnkP_Info;
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
                        return nodeLnkP_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return nodeLnkPClass_WhoAmI;
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
bool            nodeLnkP_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODELNKP == classID) {
       return true;
    }
    if (OBJ_IDENT_NODE == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            nodeLnkP_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeLnkP_Class(
    void
)
{
    return (OBJ_ID)&nodeLnkP_ClassObj;
}


static
uint16_t		nodeLnkP_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODELNKP;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODELNKP_VTBL     nodeLnkP_Vtbl = {
    {
        &nodeLnkP_Info,
        nodeLnkP_IsKindOf,
#ifdef  NODELNKP_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        nodeLnkP_Dealloc,
        nodeLnkP_Class,
        nodeLnkP_WhoAmI,
        (P_OBJ_QUERYINFO)nodeLnkP_QueryInfo,
        (P_OBJ_TOSTRING)nodeLnkP_ToDebugString,
        NULL,			// nodeLnkP_Enable,
        NULL,			// nodeLnkP_Disable,
        NULL,			// (P_OBJ_ASSIGN)nodeLnkP_Assign,
        NULL,			// (P_OBJ_COMPARE)nodeLnkP_Compare,
        NULL, 			// (P_OBJ_PTR)nodeLnkP_Copy,
        NULL, 			// (P_OBJ_PTR)nodeLnkP_DeepCopy,
        NULL 			// (P_OBJ_HASH)nodeLnkP_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //nodeLnkP_IsEnabled,
 
};



static
const
OBJ_INFO        nodeLnkP_Info = {
    "nodeLnkP",
    "node w/Pointer Links",
    (OBJ_DATA *)&nodeLnkP_ClassObj,
    (OBJ_DATA *)&node_ClassObj,
    (OBJ_IUNKNOWN *)&nodeLnkP_Vtbl,
    sizeof(NODELNKP_DATA)
};





