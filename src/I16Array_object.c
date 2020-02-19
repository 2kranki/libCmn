// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'I16Array'
//	Generated 02/19/2020 09:52:11


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




#define			I16ARRAY_OBJECT_C	    1
#include        <I16Array_internal.h>
#ifdef  I16ARRAY_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct I16Array_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  I16ARRAY_SINGLETON
    volatile
    I16ARRAY_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          I16ArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        I16Array_Info;            // Forward Reference




static
bool            I16ArrayClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_I16ARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(I16Array_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		I16ArrayClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_I16ARRAY_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
I16ARRAY_CLASS_VTBL    class_Vtbl = {
    {
        &I16Array_Info,
        I16ArrayClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        I16Array_Class,
        I16ArrayClass_WhoAmI,
        (P_OBJ_QUERYINFO)I16ArrayClass_QueryInfo,
        NULL                        // I16ArrayClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

I16ARRAY_CLASS_DATA  I16Array_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(I16ARRAY_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  I16ARRAY_SINGLETON
I16ARRAY_DATA *     I16Array_getSingleton (
    void
)
{
    return (OBJ_ID)(I16Array_ClassObj.pSingleton);
}


bool            I16Array_setSingleton (
    I16ARRAY_DATA       *pValue
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
    if (I16Array_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(I16Array_ClassObj.pSingleton));
    }
    I16Array_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



I16ARRAY_DATA *     I16Array_Shared (
    void
)
{
    I16ARRAY_DATA       *this = (OBJ_ID)(I16Array_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = I16Array_New( );
        I16Array_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // I16Array_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            I16Array_SharedReset (
    void
)
{
    I16ARRAY_DATA       *this = (OBJ_ID)(I16Array_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        I16Array_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          I16ArrayClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    I16ARRAY_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(I16ARRAY_DATA);
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
                        return (void *)&I16Array_Info;
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
                        return I16Array_New;
                    }
                    break;
                    
#ifdef  I16ARRAY_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return I16Array_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return I16Array_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return I16ArrayClass_WhoAmI;
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
bool            I16Array_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_I16ARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(I16Array_Class())->pClassSuperObject;
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
void            I16Array_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          I16Array_Class (
    void
)
{
    return (OBJ_ID)&I16Array_ClassObj;
}


static
uint16_t		I16Array_WhoAmI (
    void
)
{
    return OBJ_IDENT_I16ARRAY;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
I16ARRAY_VTBL     I16Array_Vtbl = {
    {
        &I16Array_Info,
        I16Array_IsKindOf,
#ifdef  I16ARRAY_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        I16Array_Dealloc,
        I16Array_Class,
        I16Array_WhoAmI,
        (P_OBJ_QUERYINFO)I16Array_QueryInfo,
        (P_OBJ_TOSTRING)I16Array_ToDebugString,
        NULL,			// I16Array_Enable,
        NULL,			// I16Array_Disable,
        (P_OBJ_ASSIGN)I16Array_Assign,
        (P_OBJ_COMPARE)I16Array_Compare,
        (P_OBJ_PTR)I16Array_Copy,
        NULL, 			// (P_OBJ_PTR)I16Array_DeepCopy,
        NULL 			// (P_OBJ_HASH)I16Array_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //I16Array_IsEnabled,
 
};



static
const
OBJ_INFO        I16Array_Info = {
    "I16Array",
    "Signed 16-Bit Array",
    (OBJ_DATA *)&I16Array_ClassObj,
    (OBJ_DATA *)&array_ClassObj,
    (OBJ_IUNKNOWN *)&I16Array_Vtbl,
    sizeof(I16ARRAY_DATA)
};





