// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'pgmNode'
//	Generated 08/19/2019 01:14:29


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




#define			PGMNODE_OBJECT_C	    1
#include        <pgmNode_internal.h>
#ifdef  PGMNODE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct pgmNode_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  PGMNODE_SINGLETON
    volatile
    PGMNODE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          pgmNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        pgmNode_Info;            // Forward Reference




static
bool            pgmNodeClass_IsKindOf (
    uint16_t		classID
)
{
    if (MAIN_IDENT_PGMNODE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		pgmNodeClass_WhoAmI (
    void
)
{
    return MAIN_IDENT_PGMNODE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
PGMNODE_CLASS_VTBL    class_Vtbl = {
    {
        &pgmNode_Info,
        pgmNodeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        pgmNode_Class,
        pgmNodeClass_WhoAmI,
        (P_OBJ_QUERYINFO)pgmNodeClass_QueryInfo,
        NULL                        // pgmNodeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

PGMNODE_CLASS_DATA  pgmNode_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(PGMNODE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  PGMNODE_SINGLETON
PGMNODE_DATA *     pgmNode_getSingleton (
    void
)
{
    return (OBJ_ID)(pgmNode_ClassObj.pSingleton);
}


bool            pgmNode_setSingleton (
    PGMNODE_DATA       *pValue
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
    if (pgmNode_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(pgmNode_ClassObj.pSingleton));
    }
    pgmNode_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



PGMNODE_DATA *     pgmNode_Shared (
    void
)
{
    PGMNODE_DATA       *this = (OBJ_ID)(pgmNode_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = pgmNode_New( );
        pgmNode_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // pgmNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            pgmNode_SharedReset (
    void
)
{
    PGMNODE_DATA       *this = (OBJ_ID)(pgmNode_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        pgmNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          pgmNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PGMNODE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PGMNODE_DATA);
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
                        return (void *)&pgmNode_Info;
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
                        return pgmNode_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return pgmNodeClass_WhoAmI;
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
bool            pgmNode_IsKindOf (
    uint16_t		classID
)
{
    if (MAIN_IDENT_PGMNODE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            pgmNode_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          pgmNode_Class (
    void
)
{
    return (OBJ_ID)&pgmNode_ClassObj;
}


static
uint16_t		pgmNode_WhoAmI (
    void
)
{
    return MAIN_IDENT_PGMNODE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
PGMNODE_VTBL     pgmNode_Vtbl = {
    {
        &pgmNode_Info,
        pgmNode_IsKindOf,
#ifdef  PGMNODE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        pgmNode_Dealloc,
        pgmNode_Class,
        pgmNode_WhoAmI,
        (P_OBJ_QUERYINFO)pgmNode_QueryInfo,
        (P_OBJ_TOSTRING)pgmNode_ToDebugString,
        NULL,			// pgmNode_Enable,
        NULL,			// pgmNode_Disable,
        NULL,			// (P_OBJ_ASSIGN)pgmNode_Assign,
        NULL,			// (P_OBJ_COMPARE)pgmNode_Compare,
        NULL, 			// (P_OBJ_PTR)pgmNode_Copy,
        NULL, 			// (P_OBJ_PTR)pgmNode_DeepCopy,
        NULL 			// (P_OBJ_HASH)pgmNode_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //pgmNode_IsEnabled,
 
};



static
const
OBJ_INFO        pgmNode_Info = {
    "pgmNode",
    "pgmNode",	
    (OBJ_DATA *)&pgmNode_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&pgmNode_Vtbl,
    sizeof(PGMNODE_DATA)
};





