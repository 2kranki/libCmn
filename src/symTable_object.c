// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'symTable'
//	Generated 11/04/2018 21:13:12


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




#define			SYMTABLE_OBJECT_C	    1
#include        <symTable_internal.h>
#ifdef  SYMTABLE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct symTable_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SYMTABLE_SINGLETON
    volatile
    SYMTABLE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          symTableClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        symTable_Info;            // Forward Reference




static
bool            symTableClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SYMTABLE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		symTableClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_SYMTABLE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SYMTABLE_CLASS_VTBL    class_Vtbl = {
    {
        &symTable_Info,
        symTableClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        symTable_Class,
        symTableClass_WhoAmI,
        (P_OBJ_QUERYINFO)symTableClass_QueryInfo,
        NULL                        // symTableClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SYMTABLE_CLASS_DATA  symTable_ClassObj = {
    {(const OBJ_IUNKNOWN *)&class_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_SYMTABLE_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SYMTABLE_SINGLETON
SYMTABLE_DATA *     symTable_getSingleton(
    void
)
{
    return (OBJ_ID)(symTable_ClassObj.pSingleton);
}


bool            symTable_setSingleton(
    SYMTABLE_DATA       *pValue
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
    if (symTable_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(symTable_ClassObj.pSingleton));
    }
    symTable_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SYMTABLE_DATA *     symTable_Shared(
    void
)
{
    SYMTABLE_DATA       *this = (OBJ_ID)(symTable_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = symTable_New( );
        symTable_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // symTable_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            symTable_SharedReset(
    void
)
{
    SYMTABLE_DATA       *this = (OBJ_ID)(symTable_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        symTable_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          symTableClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SYMTABLE_CLASS_DATA *this = objId;
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
                        return (void *)&symTable_Info;
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
                        return symTable_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return symTableClass_WhoAmI;
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
bool            symTable_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SYMTABLE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            symTable_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          symTable_Class(
    void
)
{
    return (OBJ_ID)&symTable_ClassObj;
}


static
uint16_t		symTable_WhoAmI(
    void
)
{
    return OBJ_IDENT_SYMTABLE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
SYMTABLE_VTBL     symTable_Vtbl = {
    {
        &symTable_Info,
        symTable_IsKindOf,
#ifdef  SYMTABLE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        symTable_Dealloc,
        symTable_Class,
        symTable_WhoAmI,
        (P_OBJ_QUERYINFO)symTable_QueryInfo,
        (P_OBJ_TOSTRING)symTable_ToDebugString,
        NULL,			// symTable_Enable,
        NULL,			// symTable_Disable,
        NULL,			// (P_OBJ_ASSIGN)symTable_Assign,
        NULL,			// (P_OBJ_COMPARE)symTable_Compare,
        NULL, 			// (P_OBJ_PTR)symTable_Copy,
        NULL, 			// (P_OBJ_PTR)symTable_DeepCopy,
        NULL 			// (P_OBJ_HASH)symTable_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //symTable_IsEnabled,
 
};



static
const
OBJ_INFO        symTable_Info = {
    "symTable",
    "Symbol Table",
    (OBJ_DATA *)&symTable_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&symTable_Vtbl
};





