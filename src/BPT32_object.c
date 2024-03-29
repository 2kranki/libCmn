// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'BPT32'
//	Generated 01/12/2019 14:04:44


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




#define			BPT32_OBJECT_C	    1
#include        <BPT32_internal.h>
#ifdef  BPT32_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct BPT32_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BPT32_SINGLETON
    volatile
    BPT32_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BPT32Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        BPT32_Info;            // Forward Reference




static
bool            BPT32Class_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPT32_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_RRDS_CLASS == classID) {
        return true;
    }
   if (OBJ_IDENT_LRU_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		BPT32Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPT32_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BPT32_CLASS_VTBL    class_Vtbl = {
    {
        &BPT32_Info,
        BPT32Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        BPT32_Class,
        BPT32Class_WhoAmI,
        (P_OBJ_QUERYINFO)BPT32Class_QueryInfo,
        NULL                        // BPT32Class_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

BPT32_CLASS_DATA  BPT32_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BPT32_CLASS_DATA),               // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BPT32_SINGLETON
BPT32_DATA *     BPT32_getSingleton (
    void
)
{
    return (OBJ_ID)(BPT32_ClassObj.pSingleton);
}


bool            BPT32_setSingleton (
    BPT32_DATA       *pValue
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
    if (BPT32_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(BPT32_ClassObj.pSingleton));
    }
    BPT32_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BPT32_DATA *     BPT32_Shared (
    void
)
{
    BPT32_DATA       *this = (OBJ_ID)(BPT32_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = BPT32_New( );
        BPT32_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // BPT32_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            BPT32_SharedReset (
    void
)
{
    BPT32_DATA       *this = (OBJ_ID)(BPT32_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        BPT32_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BPT32Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BPT32_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPT32_DATA);
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
                        return (void *)&BPT32_Info;
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
                        return BPT32_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return BPT32Class_WhoAmI;
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
bool            BPT32_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPT32 == classID) {
       return true;
    }
    if (OBJ_IDENT_RRDS == classID) {
        return true;
    }
    if (OBJ_IDENT_LRU == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            BPT32_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          BPT32_Class (
    void
)
{
    return (OBJ_ID)&BPT32_ClassObj;
}


static
uint16_t		BPT32_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPT32;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
BPT32_VTBL     BPT32_Vtbl = {
    {
        &BPT32_Info,
        BPT32_IsKindOf,
#ifdef  BPT32_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        BPT32_Dealloc,
        BPT32_Class,
        BPT32_WhoAmI,
        (P_OBJ_QUERYINFO)BPT32_QueryInfo,
        (P_OBJ_TOSTRING)BPT32_ToDebugString,
        NULL,			// BPT32_Enable,
        NULL,			// BPT32_Disable,
        NULL,			// (P_OBJ_ASSIGN)BPT32_Assign,
        NULL,			// (P_OBJ_COMPARE)BPT32_Compare,
        NULL, 			// (P_OBJ_PTR)BPT32_Copy,
        NULL, 			// (P_OBJ_PTR)BPT32_DeepCopy,
        NULL 			// (P_OBJ_HASH)BPT32_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BPT32_IsEnabled,
 
};



static
const
OBJ_INFO        BPT32_Info = {
    "BPT32",
    "B-Plus 32-Bit Tree",
    (OBJ_DATA *)&BPT32_ClassObj,
    (OBJ_DATA *)&lru_ClassObj,
    (OBJ_IUNKNOWN *)&BPT32_Vtbl,
    sizeof(BPT32_DATA)
};





