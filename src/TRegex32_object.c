// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'TRegex32'
//	Generated 12/19/2019 23:09:03


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




#define			TREGEX32_OBJECT_C	    1
#include        <TRegex32_internal.h>
#ifdef  TREGEX32_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct TRegex32_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TREGEX32_SINGLETON
    volatile
    TREGEX32_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          TRegex32Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        TRegex32_Info;            // Forward Reference




static
bool            TRegex32Class_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_TREGEX32_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(TRegex32_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		TRegex32Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_TREGEX32_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TREGEX32_CLASS_VTBL    class_Vtbl = {
    {
        &TRegex32_Info,
        TRegex32Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        TRegex32_Class,
        TRegex32Class_WhoAmI,
        (P_OBJ_QUERYINFO)TRegex32Class_QueryInfo,
        NULL                        // TRegex32Class_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

TREGEX32_CLASS_DATA  TRegex32_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TREGEX32_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TREGEX32_SINGLETON
TREGEX32_DATA *     TRegex32_getSingleton (
    void
)
{
    return (OBJ_ID)(TRegex32_ClassObj.pSingleton);
}


bool            TRegex32_setSingleton (
    TREGEX32_DATA       *pValue
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
    if (TRegex32_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(TRegex32_ClassObj.pSingleton));
    }
    TRegex32_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TREGEX32_DATA *     TRegex32_Shared (
    void
)
{
    TREGEX32_DATA       *this = (OBJ_ID)(TRegex32_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = TRegex32_New( );
        TRegex32_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // TRegex32_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            TRegex32_SharedReset (
    void
)
{
    TREGEX32_DATA       *this = (OBJ_ID)(TRegex32_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        TRegex32_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          TRegex32Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TREGEX32_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TREGEX32_DATA);
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
                        return (void *)&TRegex32_Info;
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
                        return TRegex32_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return TRegex32_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return TRegex32Class_WhoAmI;
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
bool            TRegex32_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_TREGEX32 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(TRegex32_Class())->pClassSuperObject;
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
void            TRegex32_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          TRegex32_Class (
    void
)
{
    return (OBJ_ID)&TRegex32_ClassObj;
}


static
uint16_t		TRegex32_WhoAmI (
    void
)
{
    return OBJ_IDENT_TREGEX32;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
TREGEX32_VTBL     TRegex32_Vtbl = {
    {
        &TRegex32_Info,
        TRegex32_IsKindOf,
#ifdef  TREGEX32_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        TRegex32_Dealloc,
        TRegex32_Class,
        TRegex32_WhoAmI,
        (P_OBJ_QUERYINFO)TRegex32_QueryInfo,
        (P_OBJ_TOSTRING)TRegex32_ToDebugString,
        NULL,			// TRegex32_Enable,
        NULL,			// TRegex32_Disable,
        NULL,			// (P_OBJ_ASSIGN)TRegex32_Assign,
        NULL,			// (P_OBJ_COMPARE)TRegex32_Compare,
        NULL, 			// (P_OBJ_PTR)TRegex32_Copy,
        NULL, 			// (P_OBJ_PTR)TRegex32_DeepCopy,
        NULL 			// (P_OBJ_HASH)TRegex32_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //TRegex32_IsEnabled,
 
};



static
const
OBJ_INFO        TRegex32_Info = {
    "TRegex32",
    "Tiny Regex - int32_t",
    (OBJ_DATA *)&TRegex32_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&TRegex32_Vtbl,
    sizeof(TREGEX32_DATA)
};





