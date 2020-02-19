// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'I16Matrix'
//	Generated 02/19/2020 09:50:41


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




#define			I16MATRIX_OBJECT_C	    1
#include        <I16Matrix_internal.h>
#ifdef  I16MATRIX_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct I16Matrix_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  I16MATRIX_SINGLETON
    volatile
    I16MATRIX_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          I16MatrixClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        I16Matrix_Info;            // Forward Reference




static
bool            I16MatrixClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_I16MATRIX_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(I16Matrix_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		I16MatrixClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_I16MATRIX_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
I16MATRIX_CLASS_VTBL    class_Vtbl = {
    {
        &I16Matrix_Info,
        I16MatrixClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        I16Matrix_Class,
        I16MatrixClass_WhoAmI,
        (P_OBJ_QUERYINFO)I16MatrixClass_QueryInfo,
        NULL                        // I16MatrixClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

I16MATRIX_CLASS_DATA  I16Matrix_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(I16MATRIX_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  I16MATRIX_SINGLETON
I16MATRIX_DATA *     I16Matrix_getSingleton (
    void
)
{
    return (OBJ_ID)(I16Matrix_ClassObj.pSingleton);
}


bool            I16Matrix_setSingleton (
    I16MATRIX_DATA       *pValue
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
    if (I16Matrix_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(I16Matrix_ClassObj.pSingleton));
    }
    I16Matrix_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



I16MATRIX_DATA *     I16Matrix_Shared (
    void
)
{
    I16MATRIX_DATA       *this = (OBJ_ID)(I16Matrix_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = I16Matrix_New( );
        I16Matrix_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // I16Matrix_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            I16Matrix_SharedReset (
    void
)
{
    I16MATRIX_DATA       *this = (OBJ_ID)(I16Matrix_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        I16Matrix_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          I16MatrixClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    I16MATRIX_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(I16MATRIX_DATA);
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
                        return (void *)&I16Matrix_Info;
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
                        return I16Matrix_New;
                    }
                    break;
                    
#ifdef  I16MATRIX_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return I16Matrix_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return I16Matrix_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return I16MatrixClass_WhoAmI;
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
bool            I16Matrix_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_I16MATRIX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(I16Matrix_Class())->pClassSuperObject;
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
void            I16Matrix_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          I16Matrix_Class (
    void
)
{
    return (OBJ_ID)&I16Matrix_ClassObj;
}


static
uint16_t		I16Matrix_WhoAmI (
    void
)
{
    return OBJ_IDENT_I16MATRIX;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
I16MATRIX_VTBL     I16Matrix_Vtbl = {
    {
        &I16Matrix_Info,
        I16Matrix_IsKindOf,
#ifdef  I16MATRIX_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        I16Matrix_Dealloc,
        I16Matrix_Class,
        I16Matrix_WhoAmI,
        (P_OBJ_QUERYINFO)I16Matrix_QueryInfo,
        (P_OBJ_TOSTRING)I16Matrix_ToDebugString,
        NULL,			// I16Matrix_Enable,
        NULL,			// I16Matrix_Disable,
        NULL,			// (P_OBJ_ASSIGN)I16Matrix_Assign,
        NULL,			// (P_OBJ_COMPARE)I16Matrix_Compare,
        NULL, 			// (P_OBJ_PTR)I16Matrix_Copy,
        NULL, 			// (P_OBJ_PTR)I16Matrix_DeepCopy,
        NULL 			// (P_OBJ_HASH)I16Matrix_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //I16Matrix_IsEnabled,
 
};



static
const
OBJ_INFO        I16Matrix_Info = {
    "I16Matrix",
    "Signed 16-Bit Matrix",
    (OBJ_DATA *)&I16Matrix_ClassObj,
    (OBJ_DATA *)&array_ClassObj,
    (OBJ_IUNKNOWN *)&I16Matrix_Vtbl,
    sizeof(I16MATRIX_DATA)
};





