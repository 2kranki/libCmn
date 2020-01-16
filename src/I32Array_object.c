// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'I32Array'
//	Generated 01/14/2020 18:29:58


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




#define			I32ARRAY_OBJECT_C	    1
#include        <I32Array_internal.h>
#ifdef  I32ARRAY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct I32Array_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  I32ARRAY_SINGLETON
    volatile
    I32ARRAY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          I32ArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        I32Array_Info;            // Forward Reference




static
bool            I32ArrayClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_I32ARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(I32Array_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		I32ArrayClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_I32ARRAY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
I32ARRAY_CLASS_VTBL    class_Vtbl = {
    {
        &I32Array_Info,
        I32ArrayClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        I32Array_Class,
        I32ArrayClass_WhoAmI,
        (P_OBJ_QUERYINFO)I32ArrayClass_QueryInfo,
        NULL                        // I32ArrayClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

I32ARRAY_CLASS_DATA  I32Array_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(I32ARRAY_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  I32ARRAY_SINGLETON
I32ARRAY_DATA *     I32Array_getSingleton (
    void
)
{
    return (OBJ_ID)(I32Array_ClassObj.pSingleton);
}


bool            I32Array_setSingleton (
    I32ARRAY_DATA       *pValue
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
    if (I32Array_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(I32Array_ClassObj.pSingleton));
    }
    I32Array_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



I32ARRAY_DATA *     I32Array_Shared (
    void
)
{
    I32ARRAY_DATA       *this = (OBJ_ID)(I32Array_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = I32Array_New( );
        I32Array_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // I32Array_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            I32Array_SharedReset (
    void
)
{
    I32ARRAY_DATA       *this = (OBJ_ID)(I32Array_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        I32Array_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          I32ArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    I32ARRAY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(I32ARRAY_DATA);
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
                        return (void *)&I32Array_Info;
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
                        return I32Array_New;
                    }
                    break;
                    
#ifdef  I32ARRAY_JSON_SUPPORT
                case 'P':
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return I32Array_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return I32Array_ParseJsonObject;
                    }
                    break;
#endif
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return I32ArrayClass_WhoAmI;
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
bool            I32Array_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_I32ARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(I32Array_Class())->pClassSuperObject;
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
void            I32Array_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          I32Array_Class (
    void
)
{
    return (OBJ_ID)&I32Array_ClassObj;
}


static
uint16_t		I32Array_WhoAmI (
    void
)
{
    return OBJ_IDENT_I32ARRAY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
I32ARRAY_VTBL     I32Array_Vtbl = {
    {
        &I32Array_Info,
        I32Array_IsKindOf,
#ifdef  I32ARRAY_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        I32Array_Dealloc,
        I32Array_Class,
        I32Array_WhoAmI,
        (P_OBJ_QUERYINFO)I32Array_QueryInfo,
        (P_OBJ_TOSTRING)I32Array_ToDebugString,
        NULL,			// I32Array_Enable,
        NULL,			// I32Array_Disable,
        (P_OBJ_ASSIGN)I32Array_Assign,
        NULL,			// (P_OBJ_COMPARE)I32Array_Compare,
        (P_OBJ_PTR)I32Array_Copy,
        NULL, 			// (P_OBJ_PTR)I32Array_DeepCopy,
        NULL 			// (P_OBJ_HASH)I32Array_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //I32Array_IsEnabled,
 
};



static
const
OBJ_INFO        I32Array_Info = {
    "I32Array",
    "Variable Array of int32_t",
    (OBJ_DATA *)&I32Array_ClassObj,
    (OBJ_DATA *)&array_ClassObj,
    (OBJ_IUNKNOWN *)&I32Array_Vtbl,
    sizeof(I32ARRAY_DATA)
};





