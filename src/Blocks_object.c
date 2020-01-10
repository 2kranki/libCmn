// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Blocks'
//	Generated 01/10/2020 11:54:27


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




#define			BLOCKS_OBJECT_C	    1
#include        <Blocks_internal.h>
#ifdef  BLOCKS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Blocks_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BLOCKS_SINGLETON
    volatile
    BLOCKS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BlocksClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Blocks_Info;            // Forward Reference




static
bool            BlocksClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BLOCKS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Blocks_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		BlocksClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_BLOCKS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BLOCKS_CLASS_VTBL    class_Vtbl = {
    {
        &Blocks_Info,
        BlocksClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Blocks_Class,
        BlocksClass_WhoAmI,
        (P_OBJ_QUERYINFO)BlocksClass_QueryInfo,
        NULL                        // BlocksClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

BLOCKS_CLASS_DATA  Blocks_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BLOCKS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BLOCKS_SINGLETON
BLOCKS_DATA *     Blocks_getSingleton (
    void
)
{
    return (OBJ_ID)(Blocks_ClassObj.pSingleton);
}


bool            Blocks_setSingleton (
    BLOCKS_DATA       *pValue
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
    if (Blocks_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Blocks_ClassObj.pSingleton));
    }
    Blocks_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BLOCKS_DATA *     Blocks_Shared (
    void
)
{
    BLOCKS_DATA       *this = (OBJ_ID)(Blocks_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Blocks_New( );
        Blocks_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Blocks_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Blocks_SharedReset (
    void
)
{
    BLOCKS_DATA       *this = (OBJ_ID)(Blocks_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Blocks_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BlocksClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BLOCKS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BLOCKS_DATA);
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
                        return (void *)&Blocks_Info;
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
                        return Blocks_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return Blocks_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return BlocksClass_WhoAmI;
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
bool            Blocks_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BLOCKS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Blocks_Class())->pClassSuperObject;
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
void            Blocks_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Blocks_Class (
    void
)
{
    return (OBJ_ID)&Blocks_ClassObj;
}


static
uint16_t		Blocks_WhoAmI (
    void
)
{
    return OBJ_IDENT_BLOCKS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
BLOCKS_VTBL     Blocks_Vtbl = {
    {
        &Blocks_Info,
        Blocks_IsKindOf,
#ifdef  BLOCKS_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Blocks_Dealloc,
        Blocks_Class,
        Blocks_WhoAmI,
        (P_OBJ_QUERYINFO)Blocks_QueryInfo,
        (P_OBJ_TOSTRING)Blocks_ToDebugString,
        NULL,			// Blocks_Enable,
        NULL,			// Blocks_Disable,
        NULL,			// (P_OBJ_ASSIGN)Blocks_Assign,
        NULL,			// (P_OBJ_COMPARE)Blocks_Compare,
        NULL, 			// (P_OBJ_PTR)Blocks_Copy,
        NULL, 			// (P_OBJ_PTR)Blocks_DeepCopy,
        NULL 			// (P_OBJ_HASH)Blocks_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Blocks_IsEnabled,
 
};



static
const
OBJ_INFO        Blocks_Info = {
    "Blocks",
    "A List of Memory Blocks/Buffers",
    (OBJ_DATA *)&Blocks_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Blocks_Vtbl,
    sizeof(BLOCKS_DATA)
};





