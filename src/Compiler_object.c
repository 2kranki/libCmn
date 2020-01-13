// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Compiler'
//	Generated 01/04/2020 23:19:02


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




#define			COMPILER_OBJECT_C	    1
#include        <Compiler_internal.h>
#ifdef  COMPILER_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Compiler_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  COMPILER_SINGLETON
    volatile
    COMPILER_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          CompilerClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Compiler_Info;            // Forward Reference




static
bool            CompilerClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_COMPILER_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Compiler_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		CompilerClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_COMPILER_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
COMPILER_CLASS_VTBL    class_Vtbl = {
    {
        &Compiler_Info,
        CompilerClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Compiler_Class,
        CompilerClass_WhoAmI,
        (P_OBJ_QUERYINFO)CompilerClass_QueryInfo,
        NULL                        // CompilerClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

COMPILER_CLASS_DATA  Compiler_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(COMPILER_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  COMPILER_SINGLETON
COMPILER_DATA *     Compiler_getSingleton (
    void
)
{
    return (OBJ_ID)(Compiler_ClassObj.pSingleton);
}


bool            Compiler_setSingleton (
    COMPILER_DATA       *pValue
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
    if (Compiler_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Compiler_ClassObj.pSingleton));
    }
    Compiler_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



COMPILER_DATA *     Compiler_Shared (
    void
)
{
    COMPILER_DATA       *this = (OBJ_ID)(Compiler_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Compiler_New( );
        Compiler_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Compiler_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Compiler_SharedReset (
    void
)
{
    COMPILER_DATA       *this = (OBJ_ID)(Compiler_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Compiler_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          CompilerClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    COMPILER_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(COMPILER_DATA);
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
                        return (void *)&Compiler_Info;
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
                        return Compiler_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return Compiler_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return CompilerClass_WhoAmI;
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
bool            Compiler_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_COMPILER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Compiler_Class())->pClassSuperObject;
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
void            Compiler_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Compiler_Class (
    void
)
{
    return (OBJ_ID)&Compiler_ClassObj;
}


static
uint16_t		Compiler_WhoAmI (
    void
)
{
    return OBJ_IDENT_COMPILER;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
COMPILER_VTBL     Compiler_Vtbl = {
    {
        &Compiler_Info,
        Compiler_IsKindOf,
#ifdef  COMPILER_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Compiler_Dealloc,
        Compiler_Class,
        Compiler_WhoAmI,
        (P_OBJ_QUERYINFO)Compiler_QueryInfo,
        (P_OBJ_TOSTRING)Compiler_ToDebugString,
        NULL,			// Compiler_Enable,
        NULL,			// Compiler_Disable,
        NULL,			// (P_OBJ_ASSIGN)Compiler_Assign,
        NULL,			// (P_OBJ_COMPARE)Compiler_Compare,
        NULL, 			// (P_OBJ_PTR)Compiler_Copy,
        NULL, 			// (P_OBJ_PTR)Compiler_DeepCopy,
        NULL 			// (P_OBJ_HASH)Compiler_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Compiler_IsEnabled,
 
};



static
const
OBJ_INFO        Compiler_Info = {
    "Compiler",
    "Compiler Base",
    (OBJ_DATA *)&Compiler_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Compiler_Vtbl,
    sizeof(COMPILER_DATA)
};





