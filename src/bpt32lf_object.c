// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'bpt32lf'
//	Generated 01/12/2019 14:04:41


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




#define			BPT32LF_OBJECT_C	    1
#include        <bpt32lf_internal.h>
#ifdef  BPT32LF_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct bpt32lf_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BPT32LF_SINGLETON
    volatile
    BPT32LF_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          bpt32lfClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        bpt32lf_Info;            // Forward Reference




static
bool            bpt32lfClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPT32LF_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		bpt32lfClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPT32LF_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BPT32LF_CLASS_VTBL    class_Vtbl = {
    {
        &bpt32lf_Info,
        bpt32lfClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        bpt32lf_Class,
        bpt32lfClass_WhoAmI,
        (P_OBJ_QUERYINFO)bpt32lfClass_QueryInfo,
        NULL                        // bpt32lfClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

BPT32LF_CLASS_DATA  bpt32lf_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BPT32LF_CLASS_DATA),             // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BPT32LF_SINGLETON
BPT32LF_DATA *     bpt32lf_getSingleton (
    void
)
{
    return (OBJ_ID)(bpt32lf_ClassObj.pSingleton);
}


bool            bpt32lf_setSingleton (
    BPT32LF_DATA       *pValue
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
    if (bpt32lf_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(bpt32lf_ClassObj.pSingleton));
    }
    bpt32lf_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BPT32LF_DATA *     bpt32lf_Shared (
    void
)
{
    BPT32LF_DATA       *this = (OBJ_ID)(bpt32lf_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = bpt32lf_New( );
        bpt32lf_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // bpt32lf_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            bpt32lf_SharedReset (
    void
)
{
    BPT32LF_DATA       *this = (OBJ_ID)(bpt32lf_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        bpt32lf_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          bpt32lfClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BPT32LF_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPT32LF_DATA);
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
                        return (void *)&bpt32lf_Info;
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
                        return bpt32lf_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return bpt32lfClass_WhoAmI;
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
bool            bpt32lf_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPT32LF == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            bpt32lf_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          bpt32lf_Class (
    void
)
{
    return (OBJ_ID)&bpt32lf_ClassObj;
}


static
uint16_t		bpt32lf_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPT32LF;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
BPT32LF_VTBL     bpt32lf_Vtbl = {
    {
        &bpt32lf_Info,
        bpt32lf_IsKindOf,
#ifdef  BPT32LF_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        bpt32lf_Dealloc,
        bpt32lf_Class,
        bpt32lf_WhoAmI,
        (P_OBJ_QUERYINFO)bpt32lf_QueryInfo,
        (P_OBJ_TOSTRING)bpt32lf_ToDebugString,
        NULL,			// bpt32lf_Enable,
        NULL,			// bpt32lf_Disable,
        NULL,			// (P_OBJ_ASSIGN)bpt32lf_Assign,
        NULL,			// (P_OBJ_COMPARE)bpt32lf_Compare,
        NULL, 			// (P_OBJ_PTR)bpt32lf_Copy,
        NULL, 			// (P_OBJ_PTR)bpt32lf_DeepCopy,
        NULL 			// (P_OBJ_HASH)bpt32lf_Hash,
    },
    // Put other object method names below this.
    // Properties:
    (void *)bpt32lf_getBlock,
    (void *)bpt32lf_getIndex,
    (void *)bpt32lf_setManager,
    // Methods:
    (void *)bpt32lf_Get,
    (void *)bpt32lf_Insert,
    (void *)bpt32lf_Setup

};



static
const
OBJ_INFO        bpt32lf_Info = {
    "bpt32lf",
    "B-Plus 32-Bit Tree Leaf Block",
    (OBJ_DATA *)&bpt32lf_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&bpt32lf_Vtbl,
    sizeof(BPT32LF_DATA)
};





