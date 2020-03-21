// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'U8VlArray'
//	Generated 03/20/2020 11:56:58


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




#define			U8VLARRAY_OBJECT_C	    1
#include        <U8VlArray_internal.h>
#ifdef  U8VLARRAY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct U8VlArray_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  U8VLARRAY_SINGLETON
    volatile
    U8VLARRAY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          U8VlArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        U8VlArray_Info;            // Forward Reference




static
bool            U8VlArrayClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_U8VLARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(U8VlArray_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		U8VlArrayClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_U8VLARRAY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
U8VLARRAY_CLASS_VTBL    class_Vtbl = {
    {
        &U8VlArray_Info,
        U8VlArrayClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        U8VlArray_Class,
        U8VlArrayClass_WhoAmI,
        (P_OBJ_QUERYINFO)U8VlArrayClass_QueryInfo,
        NULL                        // U8VlArrayClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

U8VLARRAY_CLASS_DATA  U8VlArray_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(U8VLARRAY_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  U8VLARRAY_SINGLETON
extern
const
U8VLARRAY_VTBL       U8VlArray_VtblShared;


U8VLARRAY_DATA *     U8VlArray_getSingleton (
    void
)
{
    return (OBJ_ID)(U8VlArray_ClassObj.pSingleton);
}


bool            U8VlArray_setSingleton (
    U8VLARRAY_DATA       *pValue
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
    if (U8VlArray_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(U8VlArray_ClassObj.pSingleton));
    }
    U8VlArray_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



U8VLARRAY_DATA *     U8VlArray_Shared (
    void
)
{
    U8VLARRAY_DATA       *this = (OBJ_ID)(U8VlArray_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = U8VlArray_New( );
        obj_setVtbl(this, (void *)&U8VlArray_VtblShared);
        U8VlArray_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // U8VlArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            U8VlArray_SharedReset (
    void
)
{
    U8VLARRAY_DATA       *this = (OBJ_ID)(U8VlArray_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&U8VlArray_Vtbl);
        obj_Release(this);
        U8VlArray_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          U8VlArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    U8VLARRAY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(U8VLARRAY_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&U8VlArray_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&U8VlArray_Info.pClassSuperObject;
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
                        return U8VlArray_New;
                    }
                    break;
                    
				case 'P':
#ifdef  U8VLARRAY_JSON_SUPPORT
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return U8VlArray_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return U8VlArray_ParseJsonObject;
					}
#endif
					break;

				case 'T':
#ifdef  U8VLARRAY_JSON_SUPPORT
					if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
						return U8VlArray_ToJsonFields;
					}
					if (str_Compare("ToJson", (char *)pStr) == 0) {
						return U8VlArray_ToJson;
					}
#endif
					break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return U8VlArrayClass_WhoAmI;
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
bool            U8VlArray_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_U8VLARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(U8VlArray_Class())->pClassSuperObject;
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
void            U8VlArray_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          U8VlArray_Class (
    void
)
{
    return (OBJ_ID)&U8VlArray_ClassObj;
}


static
uint16_t		U8VlArray_WhoAmI (
    void
)
{
    return OBJ_IDENT_U8VLARRAY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  U8VLARRAY_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
U8VLARRAY_VTBL     U8VlArray_VtblShared = {
    {
        &U8VlArray_Info,
        U8VlArray_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        U8VlArray_Dealloc,
        U8VlArray_Class,
        U8VlArray_WhoAmI,
        (P_OBJ_QUERYINFO)U8VlArray_QueryInfo,
        (P_OBJ_TOSTRING)U8VlArray_ToDebugString,
        NULL,			// U8VlArray_Enable,
        NULL,			// U8VlArray_Disable,
        NULL,			// (P_OBJ_ASSIGN)U8VlArray_Assign,
        NULL,			// (P_OBJ_COMPARE)U8VlArray_Compare,
        NULL, 			// (P_OBJ_PTR)U8VlArray_Copy,
        NULL, 			// (P_OBJ_PTR)U8VlArray_DeepCopy,
        NULL 			// (P_OBJ_HASH)U8VlArray_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //U8VlArray_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
U8VLARRAY_VTBL     U8VlArray_Vtbl = {
    {
        &U8VlArray_Info,
        U8VlArray_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        U8VlArray_Dealloc,
        U8VlArray_Class,
        U8VlArray_WhoAmI,
        (P_OBJ_QUERYINFO)U8VlArray_QueryInfo,
        (P_OBJ_TOSTRING)U8VlArray_ToDebugString,
        NULL,			// U8VlArray_Enable,
        NULL,			// U8VlArray_Disable,
        (P_OBJ_ASSIGN)U8VlArray_Assign,
        (P_OBJ_COMPARE)U8VlArray_Compare,
        (P_OBJ_PTR)U8VlArray_Copy,
        NULL, 			// (P_OBJ_PTR)U8VlArray_DeepCopy,
        NULL 			// (P_OBJ_HASH)U8VlArray_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //U8VlArray_IsEnabled,
 
};



static
const
OBJ_INFO        U8VlArray_Info = {
    "U8VlArray",
    "uint8_t variable length array",
    (OBJ_DATA *)&U8VlArray_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&U8VlArray_Vtbl,
    sizeof(U8VLARRAY_DATA)
};





