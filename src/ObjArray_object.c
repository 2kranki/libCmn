// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'ObjArray'
//	Generated 12/29/2019 20:07:08


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




#define			OBJARRAY_OBJECT_C	    1
#include        <ObjArray_internal.h>
#ifdef  OBJARRAY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ObjArray_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OBJARRAY_SINGLETON
    volatile
    OBJARRAY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ObjArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ObjArray_Info;            // Forward Reference




static
bool            ObjArrayClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OBJARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(ObjArray_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		ObjArrayClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJARRAY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OBJARRAY_CLASS_VTBL    class_Vtbl = {
    {
        &ObjArray_Info,
        ObjArrayClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ObjArray_Class,
        ObjArrayClass_WhoAmI,
        (P_OBJ_QUERYINFO)ObjArrayClass_QueryInfo,
        NULL                        // ObjArrayClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

OBJARRAY_CLASS_DATA  ObjArray_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OBJARRAY_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OBJARRAY_SINGLETON
OBJARRAY_DATA *     ObjArray_getSingleton (
    void
)
{
    return (OBJ_ID)(ObjArray_ClassObj.pSingleton);
}


bool            ObjArray_setSingleton (
    OBJARRAY_DATA       *pValue
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
    if (ObjArray_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ObjArray_ClassObj.pSingleton));
    }
    ObjArray_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OBJARRAY_DATA *     ObjArray_Shared (
    void
)
{
    OBJARRAY_DATA       *this = (OBJ_ID)(ObjArray_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ObjArray_New( );
        ObjArray_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ObjArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ObjArray_SharedReset (
    void
)
{
    OBJARRAY_DATA       *this = (OBJ_ID)(ObjArray_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        ObjArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ObjArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OBJARRAY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJARRAY_DATA);
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
                        return (void *)&ObjArray_Info;
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
                        return ObjArray_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return ObjArray_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ObjArrayClass_WhoAmI;
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
bool            ObjArray_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OBJARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(ObjArray_Class())->pClassSuperObject;
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
void            ObjArray_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ObjArray_Class (
    void
)
{
    return (OBJ_ID)&ObjArray_ClassObj;
}


static
uint16_t		ObjArray_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJARRAY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
OBJARRAY_VTBL     ObjArray_Vtbl = {
    {
        &ObjArray_Info,
        ObjArray_IsKindOf,
#ifdef  OBJARRAY_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        ObjArray_Dealloc,
        ObjArray_Class,
        ObjArray_WhoAmI,
        (P_OBJ_QUERYINFO)ObjArray_QueryInfo,
        (P_OBJ_TOSTRING)ObjArray_ToDebugString,
        NULL,			// ObjArray_Enable,
        NULL,			// ObjArray_Disable,
        (P_OBJ_ASSIGN)ObjArray_Assign,
        NULL,			// (P_OBJ_COMPARE)ObjArray_Compare,
        (P_OBJ_PTR)ObjArray_Copy,
        (P_OBJ_PTR)ObjArray_DeepCopy,
        NULL 			// (P_OBJ_HASH)ObjArray_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ObjArray_IsEnabled,
 
};



static
const
OBJ_INFO        ObjArray_Info = {
    "ObjArray",
    "Array of Objects",
    (OBJ_DATA *)&ObjArray_ClassObj,
    (OBJ_DATA *)&array_ClassObj,
    (OBJ_IUNKNOWN *)&ObjArray_Vtbl,
    sizeof(OBJARRAY_DATA)
};





