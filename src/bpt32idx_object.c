// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'bpt32idx'
//	Generated 01/12/2019 14:04:35


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




#define			BPT32IDX_OBJECT_C	    1
#include        <bpt32idx_internal.h>
#ifdef  BPT32IDX_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct bpt32idx_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BPT32IDX_SINGLETON
    volatile
    BPT32IDX_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          bpt32idxClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        bpt32idx_Info;            // Forward Reference




static
bool            bpt32idxClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPT32IDX_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		bpt32idxClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPT32IDX_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BPT32IDX_CLASS_VTBL    class_Vtbl = {
    {
        &bpt32idx_Info,
        bpt32idxClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        bpt32idx_Class,
        bpt32idxClass_WhoAmI,
        (P_OBJ_QUERYINFO)bpt32idxClass_QueryInfo,
        NULL                        // bpt32idxClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

BPT32IDX_CLASS_DATA  bpt32idx_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BPT32IDX_CLASS_DATA),                  // cbSize
        OBJ_IDENT_BPT32IDX_CLASS,                     // cbIdent
        0,                                      // cbFlags
        0,                                      // eRc
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BPT32IDX_SINGLETON
BPT32IDX_DATA *     bpt32idx_getSingleton (
    void
)
{
    return (OBJ_ID)(bpt32idx_ClassObj.pSingleton);
}


bool            bpt32idx_setSingleton (
    BPT32IDX_DATA       *pValue
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
    if (bpt32idx_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(bpt32idx_ClassObj.pSingleton));
    }
    bpt32idx_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BPT32IDX_DATA *     bpt32idx_Shared (
    void
)
{
    BPT32IDX_DATA       *this = (OBJ_ID)(bpt32idx_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = bpt32idx_New( );
        bpt32idx_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // bpt32idx_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            bpt32idx_SharedReset (
    void
)
{
    BPT32IDX_DATA       *this = (OBJ_ID)(bpt32idx_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        bpt32idx_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          bpt32idxClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BPT32IDX_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPT32IDX_DATA);
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
                        return (void *)&bpt32idx_Info;
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
                        return bpt32idx_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return bpt32idxClass_WhoAmI;
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
bool            bpt32idx_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPT32IDX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            bpt32idx_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          bpt32idx_Class (
    void
)
{
    return (OBJ_ID)&bpt32idx_ClassObj;
}


static
uint16_t		bpt32idx_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPT32IDX;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
BPT32IDX_VTBL     bpt32idx_Vtbl = {
    {
        &bpt32idx_Info,
        bpt32idx_IsKindOf,
#ifdef  BPT32IDX_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        bpt32idx_Dealloc,
        bpt32idx_Class,
        bpt32idx_WhoAmI,
        (P_OBJ_QUERYINFO)bpt32idx_QueryInfo,
        (P_OBJ_TOSTRING)bpt32idx_ToDebugString,
        NULL,			// bpt32idx_Enable,
        NULL,			// bpt32idx_Disable,
        NULL,			// (P_OBJ_ASSIGN)bpt32idx_Assign,
        NULL,			// (P_OBJ_COMPARE)bpt32idx_Compare,
        NULL, 			// (P_OBJ_PTR)bpt32idx_Copy,
        NULL, 			// (P_OBJ_PTR)bpt32idx_DeepCopy,
        NULL 			// (P_OBJ_HASH)bpt32idx_Hash,
    },
    // Put other object method names below this.
    // Properties:
    (void *)bpt32idx_getBlock,
    (void *)bpt32idx_getIndex,
    (void *)bpt32idx_setManager,
    // Methods:
    (void *)bpt32idx_Get,
    (void *)bpt32idx_Insert,
    (void *)bpt32idx_Setup

};



static
const
OBJ_INFO        bpt32idx_Info = {
    "bpt32idx",
    "B-Plus 32-Bit Tree Index Node",
    (OBJ_DATA *)&bpt32idx_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&bpt32idx_Vtbl,
    sizeof(BPT32IDX_DATA)
};





