// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'objHash'
//	Generated 11/27/2018 11:34:09


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




#define			OBJHASH_OBJECT_C	    1
#include        <objHash_internal.h>
#ifdef  OBJHASH_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct objHash_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OBJHASH_SINGLETON
    volatile
    OBJHASH_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          objHashClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        objHash_Info;            // Forward Reference




static
bool            objHashClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJHASH_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_BLOCKS_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		objHashClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJHASH_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OBJHASH_CLASS_VTBL    class_Vtbl = {
    {
        &objHash_Info,
        objHashClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        objHash_Class,
        objHashClass_WhoAmI,
        (P_OBJ_QUERYINFO)objHashClass_QueryInfo,
        NULL                        // objHashClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

OBJHASH_CLASS_DATA  objHash_ClassObj = {
    {(const OBJ_IUNKNOWN *)&class_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_OBJHASH_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OBJHASH_SINGLETON
OBJHASH_DATA *     objHash_getSingleton (
    void
)
{
    return (OBJ_ID)(objHash_ClassObj.pSingleton);
}


bool            objHash_setSingleton (
    OBJHASH_DATA       *pValue
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
    if (objHash_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(objHash_ClassObj.pSingleton));
    }
    objHash_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OBJHASH_DATA *     objHash_Shared (
    void
)
{
    OBJHASH_DATA       *this = (OBJ_ID)(objHash_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = objHash_New( );
        objHash_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // objHash_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            objHash_SharedReset (
    void
)
{
    OBJHASH_DATA       *this = (OBJ_ID)(objHash_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        objHash_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          objHashClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OBJHASH_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJHASH_DATA);
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
                        return (void *)&objHash_Info;
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
                        return objHash_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return objHashClass_WhoAmI;
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
bool            objHash_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJHASH == classID) {
       return true;
    }
    if (OBJ_IDENT_BLOCKS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            objHash_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          objHash_Class (
    void
)
{
    return (OBJ_ID)&objHash_ClassObj;
}


static
uint16_t		objHash_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJHASH;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
OBJHASH_VTBL     objHash_Vtbl = {
    {
        &objHash_Info,
        objHash_IsKindOf,
#ifdef  OBJHASH_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        objHash_Dealloc,
        objHash_Class,
        objHash_WhoAmI,
        (P_OBJ_QUERYINFO)objHash_QueryInfo,
        (P_OBJ_TOSTRING)objHash_ToDebugString,
        NULL,			// objHash_Enable,
        NULL,			// objHash_Disable,
        NULL,			// (P_OBJ_ASSIGN)objHash_Assign,
        NULL,			// (P_OBJ_COMPARE)objHash_Compare,
        NULL, 			// (P_OBJ_PTR)objHash_Copy,
        NULL, 			// (P_OBJ_PTR)objHash_DeepCopy,
        NULL 			// (P_OBJ_HASH)objHash_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //objHash_IsEnabled,
 
};



static
const
OBJ_INFO        objHash_Info = {
    "objHash",
    "Hash of Objects",
    (OBJ_DATA *)&objHash_ClassObj,
    (OBJ_DATA *)&blocks_ClassObj,
    (OBJ_IUNKNOWN *)&objHash_Vtbl,
    sizeof(OBJHASH_DATA)
};





