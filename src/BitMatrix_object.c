// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'BitMatrix'
//	Generated 12/18/2019 08:00:28


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




#define			BITMATRIX_OBJECT_C	    1
#include        <BitMatrix_internal.h>
#ifdef  BITMATRIX_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct BitMatrix_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BITMATRIX_SINGLETON
    volatile
    BITMATRIX_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BitMatrixClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        BitMatrix_Info;            // Forward Reference




static
bool            BitMatrixClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BITMATRIX_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(BitMatrix_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		BitMatrixClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_BITMATRIX_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BITMATRIX_CLASS_VTBL    class_Vtbl = {
    {
        &BitMatrix_Info,
        BitMatrixClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        BitMatrix_Class,
        BitMatrixClass_WhoAmI,
        (P_OBJ_QUERYINFO)BitMatrixClass_QueryInfo,
        NULL                        // BitMatrixClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

BITMATRIX_CLASS_DATA  BitMatrix_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BITMATRIX_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BITMATRIX_SINGLETON
BITMATRIX_DATA *     BitMatrix_getSingleton (
    void
)
{
    return (OBJ_ID)(BitMatrix_ClassObj.pSingleton);
}


bool            BitMatrix_setSingleton (
    BITMATRIX_DATA       *pValue
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
    if (BitMatrix_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(BitMatrix_ClassObj.pSingleton));
    }
    BitMatrix_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BITMATRIX_DATA *     BitMatrix_Shared (
    void
)
{
    BITMATRIX_DATA       *this = (OBJ_ID)(BitMatrix_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = BitMatrix_New( );
        BitMatrix_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // BitMatrix_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            BitMatrix_SharedReset (
    void
)
{
    BITMATRIX_DATA       *this = (OBJ_ID)(BitMatrix_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        BitMatrix_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BitMatrixClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BITMATRIX_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BITMATRIX_DATA);
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
                        return (void *)&BitMatrix_Info;
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
                        return BitMatrix_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return BitMatrix_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return BitMatrixClass_WhoAmI;
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
bool            BitMatrix_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BITMATRIX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(BitMatrix_Class())->pClassSuperObject;
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
void            BitMatrix_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          BitMatrix_Class (
    void
)
{
    return (OBJ_ID)&BitMatrix_ClassObj;
}


static
uint16_t		BitMatrix_WhoAmI (
    void
)
{
    return OBJ_IDENT_BITMATRIX;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
BITMATRIX_VTBL     BitMatrix_Vtbl = {
    {
        &BitMatrix_Info,
        BitMatrix_IsKindOf,
#ifdef  BITMATRIX_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        BitMatrix_Dealloc,
        BitMatrix_Class,
        BitMatrix_WhoAmI,
        (P_OBJ_QUERYINFO)BitMatrix_QueryInfo,
        (P_OBJ_TOSTRING)BitMatrix_ToDebugString,
        NULL,			// BitMatrix_Enable,
        NULL,			// BitMatrix_Disable,
        NULL,			// (P_OBJ_ASSIGN)BitMatrix_Assign,
        NULL,			// (P_OBJ_COMPARE)BitMatrix_Compare,
        NULL, 			// (P_OBJ_PTR)BitMatrix_Copy,
        NULL, 			// (P_OBJ_PTR)BitMatrix_DeepCopy,
        NULL 			// (P_OBJ_HASH)BitMatrix_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BitMatrix_IsEnabled,
 
};



static
const
OBJ_INFO        BitMatrix_Info = {
    "BitMatrix",
    "Matrix of Bits",
    (OBJ_DATA *)&BitMatrix_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&BitMatrix_Vtbl,
    sizeof(BITMATRIX_DATA)
};





