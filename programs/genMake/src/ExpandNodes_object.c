// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'ExpandNodes'
//	Generated 11/10/2019 17:43:09


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




#define			EXPANDNODES_OBJECT_C	    1
#include        <ExpandNodes_internal.h>
#ifdef  EXPANDNODES_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ExpandNodes_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  EXPANDNODES_SINGLETON
    volatile
    EXPANDNODES_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ExpandNodesClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ExpandNodes_Info;            // Forward Reference




static
bool            ExpandNodesClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_EXPANDNODES_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		ExpandNodesClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_EXPANDNODES_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
EXPANDNODES_CLASS_VTBL    class_Vtbl = {
    {
        &ExpandNodes_Info,
        ExpandNodesClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ExpandNodes_Class,
        ExpandNodesClass_WhoAmI,
        (P_OBJ_QUERYINFO)ExpandNodesClass_QueryInfo,
        NULL                        // ExpandNodesClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

EXPANDNODES_CLASS_DATA  ExpandNodes_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(EXPANDNODES_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  EXPANDNODES_SINGLETON
EXPANDNODES_DATA *     ExpandNodes_getSingleton (
    void
)
{
    return (OBJ_ID)(ExpandNodes_ClassObj.pSingleton);
}


bool            ExpandNodes_setSingleton (
    EXPANDNODES_DATA       *pValue
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
    if (ExpandNodes_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ExpandNodes_ClassObj.pSingleton));
    }
    ExpandNodes_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



EXPANDNODES_DATA *     ExpandNodes_Shared (
    void
)
{
    EXPANDNODES_DATA       *this = (OBJ_ID)(ExpandNodes_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ExpandNodes_New( );
        ExpandNodes_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ExpandNodes_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ExpandNodes_SharedReset (
    void
)
{
    EXPANDNODES_DATA       *this = (OBJ_ID)(ExpandNodes_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        ExpandNodes_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ExpandNodesClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    EXPANDNODES_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(EXPANDNODES_DATA);
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
                        return (void *)&ExpandNodes_Info;
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
                        return ExpandNodes_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ExpandNodesClass_WhoAmI;
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
bool            ExpandNodes_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_EXPANDNODES == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            ExpandNodes_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ExpandNodes_Class (
    void
)
{
    return (OBJ_ID)&ExpandNodes_ClassObj;
}


static
uint16_t		ExpandNodes_WhoAmI (
    void
)
{
    return OBJ_IDENT_EXPANDNODES;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
EXPANDNODES_VTBL     ExpandNodes_Vtbl = {
    {
        &ExpandNodes_Info,
        ExpandNodes_IsKindOf,
#ifdef  EXPANDNODES_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        ExpandNodes_Dealloc,
        ExpandNodes_Class,
        ExpandNodes_WhoAmI,
        (P_OBJ_QUERYINFO)ExpandNodes_QueryInfo,
        (P_OBJ_TOSTRING)ExpandNodes_ToDebugString,
        NULL,			// ExpandNodes_Enable,
        NULL,			// ExpandNodes_Disable,
        NULL,			// (P_OBJ_ASSIGN)ExpandNodes_Assign,
        NULL,			// (P_OBJ_COMPARE)ExpandNodes_Compare,
        NULL, 			// (P_OBJ_PTR)ExpandNodes_Copy,
        NULL, 			// (P_OBJ_PTR)ExpandNodes_DeepCopy,
        NULL 			// (P_OBJ_HASH)ExpandNodes_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ExpandNodes_IsEnabled,
 
};



static
const
OBJ_INFO        ExpandNodes_Info = {
    "ExpandNodes",
    "Expand Obj/Rtn/Test Nodes to Hdr/RtnA/TstA Nodes",
    (OBJ_DATA *)&ExpandNodes_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&ExpandNodes_Vtbl,
    sizeof(EXPANDNODES_DATA)
};





