// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'TRegex'
//	Generated 12/19/2019 23:08:58


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




#define			TREGEX_OBJECT_C	    1
#include        <TRegex_internal.h>
#ifdef  TREGEX_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct TRegex_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TREGEX_SINGLETON
    volatile
    TREGEX_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          TRegexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        TRegex_Info;            // Forward Reference




static
bool            TRegexClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_TREGEX_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(TRegex_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		TRegexClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_TREGEX_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TREGEX_CLASS_VTBL    class_Vtbl = {
    {
        &TRegex_Info,
        TRegexClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        TRegex_Class,
        TRegexClass_WhoAmI,
        (P_OBJ_QUERYINFO)TRegexClass_QueryInfo,
        NULL                        // TRegexClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

TREGEX_CLASS_DATA  TRegex_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TREGEX_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TREGEX_SINGLETON
TREGEX_DATA *     TRegex_getSingleton (
    void
)
{
    return (OBJ_ID)(TRegex_ClassObj.pSingleton);
}


bool            TRegex_setSingleton (
    TREGEX_DATA       *pValue
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
    if (TRegex_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(TRegex_ClassObj.pSingleton));
    }
    TRegex_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TREGEX_DATA *     TRegex_Shared (
    void
)
{
    TREGEX_DATA       *this = (OBJ_ID)(TRegex_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = TRegex_New( );
        TRegex_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // TRegex_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            TRegex_SharedReset (
    void
)
{
    TREGEX_DATA       *this = (OBJ_ID)(TRegex_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        TRegex_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          TRegexClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TREGEX_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TREGEX_DATA);
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
                        return (void *)&TRegex_Info;
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
                        return TRegex_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return TRegex_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return TRegexClass_WhoAmI;
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
bool            TRegex_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_TREGEX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(TRegex_Class())->pClassSuperObject;
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
void            TRegex_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          TRegex_Class (
    void
)
{
    return (OBJ_ID)&TRegex_ClassObj;
}


static
uint16_t		TRegex_WhoAmI (
    void
)
{
    return OBJ_IDENT_TREGEX;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
TREGEX_VTBL     TRegex_Vtbl = {
    {
        &TRegex_Info,
        TRegex_IsKindOf,
#ifdef  TREGEX_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        TRegex_Dealloc,
        TRegex_Class,
        TRegex_WhoAmI,
        (P_OBJ_QUERYINFO)TRegex_QueryInfo,
        (P_OBJ_TOSTRING)TRegex_ToDebugString,
        NULL,			// TRegex_Enable,
        NULL,			// TRegex_Disable,
        NULL,			// (P_OBJ_ASSIGN)TRegex_Assign,
        NULL,			// (P_OBJ_COMPARE)TRegex_Compare,
        NULL, 			// (P_OBJ_PTR)TRegex_Copy,
        NULL, 			// (P_OBJ_PTR)TRegex_DeepCopy,
        NULL 			// (P_OBJ_HASH)TRegex_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //TRegex_IsEnabled,
 
};



static
const
OBJ_INFO        TRegex_Info = {
    "TRegex",
    "Tiny Regex",
    (OBJ_DATA *)&TRegex_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&TRegex_Vtbl,
    sizeof(TREGEX_DATA)
};





