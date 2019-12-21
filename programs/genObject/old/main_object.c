// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'main'
//	Generated 11/30/2018 16:54:35


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




#define			MAIN_OBJECT_C	    1
#include        <main_internal.h>
#ifdef  MAIN_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct main_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  MAIN_SINGLETON
    volatile
    MAIN_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          mainClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        main_Info;            // Forward Reference




static
bool            mainClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_MAIN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_APPL_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		mainClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_MAIN_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
MAIN_CLASS_VTBL    class_Vtbl = {
    {
        &main_Info,
        mainClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        main_Class,
        mainClass_WhoAmI,
        (P_OBJ_QUERYINFO)mainClass_QueryInfo,
        NULL                        // mainClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

MAIN_CLASS_DATA  main_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(MAIN_CLASS_DATA),            // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  MAIN_SINGLETON
MAIN_DATA *     main_getSingleton (
    void
)
{
    return (OBJ_ID)(main_ClassObj.pSingleton);
}


bool            main_setSingleton (
    MAIN_DATA       *pValue
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
    if (main_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(main_ClassObj.pSingleton));
    }
    main_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



MAIN_DATA *     main_Shared (
    void
)
{
    MAIN_DATA       *this = (OBJ_ID)(main_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = main_New( );
        main_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // main_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            main_SharedReset (
    void
)
{
    MAIN_DATA       *this = (OBJ_ID)(main_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        main_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          mainClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    MAIN_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(MAIN_DATA);
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
                        return (void *)&main_Info;
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
                        return main_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return mainClass_WhoAmI;
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
bool            main_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_MAIN == classID) {
       return true;
    }
    if (OBJ_IDENT_APPL == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            main_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          main_Class (
    void
)
{
    return (OBJ_ID)&main_ClassObj;
}


static
uint16_t		main_WhoAmI (
    void
)
{
    return OBJ_IDENT_MAIN;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
MAIN_VTBL     main_Vtbl = {
    {
        &main_Info,
        main_IsKindOf,
#ifdef  MAIN_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        main_Dealloc,
        main_Class,
        main_WhoAmI,
        (P_OBJ_QUERYINFO)main_QueryInfo,
        (P_OBJ_TOSTRING)main_ToDebugString,
        NULL,			// main_Enable,
        NULL,			// main_Disable,
        NULL,			// (P_OBJ_ASSIGN)main_Assign,
        NULL,			// (P_OBJ_COMPARE)main_Compare,
        NULL, 			// (P_OBJ_PTR)main_Copy,
        NULL, 			// (P_OBJ_PTR)main_DeepCopy,
        NULL 			// (P_OBJ_HASH)main_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //main_IsEnabled,
 
};



static
const
OBJ_INFO        main_Info = {
    "main",
    "Main Object for Object Generation Program",
    (OBJ_DATA *)&main_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&main_Vtbl,
    sizeof(MAIN_DATA)
};





