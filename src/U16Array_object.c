// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'U16Array'
//	Generated 02/18/2020 11:52:34


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




#define			U16ARRAY_OBJECT_C	    1
#include        <U16Array_internal.h>
#ifdef  U16ARRAY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct U16Array_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  U16ARRAY_SINGLETON
    volatile
    U16ARRAY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          U16ArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        U16Array_Info;            // Forward Reference




static
bool            U16ArrayClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_U16ARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(U16Array_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		U16ArrayClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_U16ARRAY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
U16ARRAY_CLASS_VTBL    class_Vtbl = {
    {
        &U16Array_Info,
        U16ArrayClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        U16Array_Class,
        U16ArrayClass_WhoAmI,
        (P_OBJ_QUERYINFO)U16ArrayClass_QueryInfo,
        NULL                        // U16ArrayClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

U16ARRAY_CLASS_DATA  U16Array_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(U16ARRAY_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  U16ARRAY_SINGLETON
U16ARRAY_DATA *     U16Array_getSingleton (
    void
)
{
    return (OBJ_ID)(U16Array_ClassObj.pSingleton);
}


bool            U16Array_setSingleton (
    U16ARRAY_DATA       *pValue
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
    if (U16Array_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(U16Array_ClassObj.pSingleton));
    }
    U16Array_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



U16ARRAY_DATA *     U16Array_Shared (
    void
)
{
    U16ARRAY_DATA       *this = (OBJ_ID)(U16Array_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = U16Array_New( );
        U16Array_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // U16Array_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            U16Array_SharedReset (
    void
)
{
    U16ARRAY_DATA       *this = (OBJ_ID)(U16Array_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        U16Array_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          U16ArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    U16ARRAY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(U16ARRAY_DATA);
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
                        return (void *)&U16Array_Info;
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
                        return U16Array_New;
                    }
                    break;
                    
#ifdef  U16ARRAY_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return U16Array_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return U16Array_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return U16ArrayClass_WhoAmI;
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
bool            U16Array_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_U16ARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(U16Array_Class())->pClassSuperObject;
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
void            U16Array_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          U16Array_Class (
    void
)
{
    return (OBJ_ID)&U16Array_ClassObj;
}


static
uint16_t		U16Array_WhoAmI (
    void
)
{
    return OBJ_IDENT_U16ARRAY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
U16ARRAY_VTBL     U16Array_Vtbl = {
    {
        &U16Array_Info,
        U16Array_IsKindOf,
#ifdef  U16ARRAY_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        U16Array_Dealloc,
        U16Array_Class,
        U16Array_WhoAmI,
        (P_OBJ_QUERYINFO)U16Array_QueryInfo,
        (P_OBJ_TOSTRING)U16Array_ToDebugString,
        NULL,			// U16Array_Enable,
        NULL,			// U16Array_Disable,
        (P_OBJ_ASSIGN)U16Array_Assign,
        (P_OBJ_COMPARE)U16Array_Compare,
        (P_OBJ_PTR)U16Array_Copy,
        NULL, 			// (P_OBJ_PTR)U16Array_DeepCopy,
        NULL 			// (P_OBJ_HASH)U16Array_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //U16Array_IsEnabled,
 
};



static
const
OBJ_INFO        U16Array_Info = {
    "U16Array",
    "Unsigned 16-Bit Dynamic Array",
    (OBJ_DATA *)&U16Array_ClassObj,
    (OBJ_DATA *)&array_ClassObj,
    (OBJ_IUNKNOWN *)&U16Array_Vtbl,
    sizeof(U16ARRAY_DATA)
};





