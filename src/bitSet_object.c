// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'BitSet'
//	Generated 12/18/2019 08:00:17


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




#define			BITSET_OBJECT_C	    1
#include        <BitSet_internal.h>
#ifdef  BITSET_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct BitSet_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BITSET_SINGLETON
    volatile
    BITSET_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BitSetClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        BitSet_Info;            // Forward Reference




static
bool            BitSetClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BITSET_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(BitSet_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		BitSetClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_BITSET_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BITSET_CLASS_VTBL    class_Vtbl = {
    {
        &BitSet_Info,
        BitSetClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        BitSet_Class,
        BitSetClass_WhoAmI,
        (P_OBJ_QUERYINFO)BitSetClass_QueryInfo,
        NULL                        // BitSetClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

BITSET_CLASS_DATA  BitSet_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BITSET_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BITSET_SINGLETON
BITSET_DATA *     BitSet_getSingleton (
    void
)
{
    return (OBJ_ID)(BitSet_ClassObj.pSingleton);
}


bool            BitSet_setSingleton (
    BITSET_DATA       *pValue
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
    if (BitSet_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(BitSet_ClassObj.pSingleton));
    }
    BitSet_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BITSET_DATA *     BitSet_Shared (
    void
)
{
    BITSET_DATA       *this = (OBJ_ID)(BitSet_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = BitSet_New( );
        BitSet_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // BitSet_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            BitSet_SharedReset (
    void
)
{
    BITSET_DATA       *this = (OBJ_ID)(BitSet_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        BitSet_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BitSetClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BITSET_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BITSET_DATA);
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
                        return (void *)&BitSet_Info;
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
                        return BitSet_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return BitSet_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return BitSetClass_WhoAmI;
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
bool            BitSet_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BITSET == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(BitSet_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        pInfo = obj_getInfo(pObj);
        return pInfo->pDefaultVtbls->pIsKindOf(classID);
    }
    
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            BitSet_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          BitSet_Class (
    void
)
{
    return (OBJ_ID)&BitSet_ClassObj;
}


static
uint16_t		BitSet_WhoAmI (
    void
)
{
    return OBJ_IDENT_BITSET;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
BITSET_VTBL     BitSet_Vtbl = {
    {
        &BitSet_Info,
        BitSet_IsKindOf,
#ifdef  BITSET_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        BitSet_Dealloc,
        BitSet_Class,
        BitSet_WhoAmI,
        (P_OBJ_QUERYINFO)BitSet_QueryInfo,
        (P_OBJ_TOSTRING)BitSet_ToDebugString,
        NULL,			// BitSet_Enable,
        NULL,			// BitSet_Disable,
        NULL,			// (P_OBJ_ASSIGN)BitSet_Assign,
        NULL,			// (P_OBJ_COMPARE)BitSet_Compare,
        NULL, 			// (P_OBJ_PTR)BitSet_Copy,
        NULL, 			// (P_OBJ_PTR)BitSet_DeepCopy,
        NULL 			// (P_OBJ_HASH)BitSet_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BitSet_IsEnabled,
 
};



static
const
OBJ_INFO        BitSet_Info = {
    "BitSet",
    "Set of Bits",
    (OBJ_DATA *)&BitSet_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&BitSet_Vtbl,
    sizeof(BITSET_DATA)
};





