// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'blks'
//	Generated 01/13/2019 16:16:32


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




#define			BLKS_OBJECT_C	    1
#include        <blks_internal.h>
#ifdef  BLKS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct blks_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BLKS_SINGLETON
    volatile
    BLKS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          blksClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        blks_Info;            // Forward Reference




static
bool            blksClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_BLKS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		blksClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_BLKS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BLKS_CLASS_VTBL    class_Vtbl = {
    {
        &blks_Info,
        blksClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        blks_Class,
        blksClass_WhoAmI,
        (P_OBJ_QUERYINFO)blksClass_QueryInfo,
        NULL                        // blksClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

BLKS_CLASS_DATA  blks_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BLKS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BLKS_SINGLETON
BLKS_DATA *     blks_getSingleton (
    void
)
{
    return (OBJ_ID)(blks_ClassObj.pSingleton);
}


bool            blks_setSingleton (
    BLKS_DATA       *pValue
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
    if (blks_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(blks_ClassObj.pSingleton));
    }
    blks_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BLKS_DATA *     blks_Shared (
    void
)
{
    BLKS_DATA       *this = (OBJ_ID)(blks_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = blks_New( );
        blks_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // blks_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            blks_SharedReset (
    void
)
{
    BLKS_DATA       *this = (OBJ_ID)(blks_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        blks_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          blksClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BLKS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BLKS_DATA);
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
                        return (void *)&blks_Info;
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
                        return blks_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return blksClass_WhoAmI;
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
bool            blks_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_BLKS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            blks_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          blks_Class (
    void
)
{
    return (OBJ_ID)&blks_ClassObj;
}


static
uint16_t		blks_WhoAmI (
    void
)
{
    return OBJ_IDENT_BLKS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
BLKS_VTBL     blks_Vtbl = {
    {
        &blks_Info,
        blks_IsKindOf,
#ifdef  BLKS_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        blks_Dealloc,
        blks_Class,
        blks_WhoAmI,
        (P_OBJ_QUERYINFO)blks_QueryInfo,
        (P_OBJ_TOSTRING)blks_ToDebugString,
        NULL,			// blks_Enable,
        NULL,			// blks_Disable,
        NULL,			// (P_OBJ_ASSIGN)blks_Assign,
        NULL,			// (P_OBJ_COMPARE)blks_Compare,
        NULL, 			// (P_OBJ_PTR)blks_Copy,
        NULL, 			// (P_OBJ_PTR)blks_DeepCopy,
        NULL 			// (P_OBJ_HASH)blks_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //blks_IsEnabled,
 
};



static
const
OBJ_INFO        blks_Info = {
    "blks",
    "A List of Memory Blocks",
    (OBJ_DATA *)&blks_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&blks_Vtbl,
    sizeof(BLKS_DATA)
};





