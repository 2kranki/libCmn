// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'symEntry'
//	Generated 11/04/2018 21:12:53


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




#define			SYMENTRY_OBJECT_C	    1
#include        <symEntry_internal.h>
#ifdef  SYMENTRY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct symEntry_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SYMENTRY_SINGLETON
    volatile
    SYMENTRY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          symEntryClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        symEntry_Info;            // Forward Reference




static
bool            symEntryClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SYMENTRY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_NODELINK_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_NODE_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		symEntryClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_SYMENTRY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SYMENTRY_CLASS_VTBL    class_Vtbl = {
    {
        &symEntry_Info,
        symEntryClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        symEntry_Class,
        symEntryClass_WhoAmI,
        (P_OBJ_QUERYINFO)symEntryClass_QueryInfo,
        NULL                        // symEntryClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SYMENTRY_CLASS_DATA  symEntry_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(SYMENTRY_CLASS_DATA),        // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SYMENTRY_SINGLETON
SYMENTRY_DATA *     symEntry_getSingleton(
    void
)
{
    return (OBJ_ID)(symEntry_ClassObj.pSingleton);
}


bool            symEntry_setSingleton(
    SYMENTRY_DATA       *pValue
)
{
    PSXLOCK_DATA    *pLock = OBJ_NIL;
    bool            fRc;
    
    pLock = psxLock_New();
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
    if (symEntry_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(symEntry_ClassObj.pSingleton));
    }
    symEntry_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SYMENTRY_DATA *     symEntry_Shared(
    void
)
{
    SYMENTRY_DATA       *this = (OBJ_ID)(symEntry_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = symEntry_New( );
        symEntry_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // symEntry_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            symEntry_SharedReset(
    void
)
{
    SYMENTRY_DATA       *this = (OBJ_ID)(symEntry_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        symEntry_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          symEntryClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SYMENTRY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
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
                        return (void *)&symEntry_Info;
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
                        return symEntry_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return symEntryClass_WhoAmI;
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
bool            symEntry_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SYMENTRY == classID) {
       return true;
    }
    if (OBJ_IDENT_NODELINK == classID) {
        return true;
    }
    if (OBJ_IDENT_NODE == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            symEntry_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          symEntry_Class(
    void
)
{
    return (OBJ_ID)&symEntry_ClassObj;
}


static
uint16_t		symEntry_WhoAmI(
    void
)
{
    return OBJ_IDENT_SYMENTRY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
SYMENTRY_VTBL     symEntry_Vtbl = {
    {
        &symEntry_Info,
        symEntry_IsKindOf,
#ifdef  SYMENTRY_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        symEntry_Dealloc,
        symEntry_Class,
        symEntry_WhoAmI,
        (P_OBJ_QUERYINFO)symEntry_QueryInfo,
        (P_OBJ_TOSTRING)symEntry_ToDebugString,
        NULL,			// symEntry_Enable,
        NULL,			// symEntry_Disable,
        NULL,			// (P_OBJ_ASSIGN)symEntry_Assign,
        NULL,			// (P_OBJ_COMPARE)symEntry_Compare,
        NULL, 			// (P_OBJ_PTR)symEntry_Copy,
        NULL, 			// (P_OBJ_PTR)symEntry_DeepCopy,
        NULL 			// (P_OBJ_HASH)symEntry_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //symEntry_IsEnabled,
 
};



static
const
OBJ_INFO        symEntry_Info = {
    "symEntry",
    "Base Entry for Symbol Table",
    (OBJ_DATA *)&symEntry_ClassObj,
    (OBJ_DATA *)&node_ClassObj,
    (OBJ_IUNKNOWN *)&symEntry_Vtbl
};





