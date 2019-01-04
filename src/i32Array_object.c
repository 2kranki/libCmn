// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'i32Array'
//	Generated 01/20/2018 22:51:51


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



//#define   I32ARRAY_IS_SINGLETON     1

#define			I32ARRAY_OBJECT_C	    1
#include        <i32Array_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct i32Array_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct i32Array_class_data_s I32ARRAY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          i32ArrayClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        i32Array_Info;            // Forward Reference




static
bool            i32ArrayClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_I32ARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_ARRAY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		i32ArrayClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_I32ARRAY_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&i32Array_Info,
    i32ArrayClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    i32Array_Class,
    i32ArrayClass_WhoAmI,
    (P_OBJ_QUERYINFO)i32ArrayClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
I32ARRAY_CLASS_DATA  i32Array_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(I32ARRAY_CLASS_DATA),        // cbSize
        OBJ_IDENT_I32ARRAY_CLASS,           // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          i32ArrayClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    I32ARRAY_CLASS_DATA *this = objId;
#ifdef XYZZY
    const
    char            *pStr = pData;
#endif

    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'O':
                    if (str_Compare("ObjectCatalog", (char *)pStr) == 0) {
                        return &this->pObjCatalog;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
            
        case OBJ_QUERYINFO_TYPE_INFO:
            return (void *)obj_getInfo(this);
            break;
            
#ifdef XYZZY
        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {
                    
                case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return i32ArrayClass_WhoAmI;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
            
        default:
            break;
    }
    
    return NULL;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

static
bool            i32Array_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_I32ARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_ARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            i32Array_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          i32Array_Class(
    void
)
{
    return (OBJ_ID)&i32Array_ClassObj;
}


static
uint16_t		i32Array_WhoAmI(
    void
)
{
    return OBJ_IDENT_I32ARRAY;
}


const
I32ARRAY_VTBL     i32Array_Vtbl = {
    {
        &i32Array_Info,
        i32Array_IsKindOf,
#ifdef  I32ARRAY_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        i32Array_Dealloc,
        i32Array_Class,
        i32Array_WhoAmI,
        (P_OBJ_QUERYINFO)i32Array_QueryInfo,
        (P_OBJ_TOSTRING)i32Array_ToDebugString,
        NULL,			// i32Array_Enable,
        NULL,			// i32Array_Disable,
        NULL,			// (P_OBJ_ASSIGN)i32Array_Assign,
        NULL,			// (P_OBJ_COMPARE)i32Array_Compare,
        NULL, 			// (P_OBJ_PTR)i32Array_Copy,
        NULL 			// (P_OBJ_HASH)i32Array_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //i32Array_IsEnabled,
 
};



static
const
OBJ_INFO        i32Array_Info = {
    "i32Array",
    "Array of int32_t",
    (OBJ_DATA *)&i32Array_ClassObj,
    (OBJ_DATA *)&array_ClassObj,
    (OBJ_IUNKNOWN *)&i32Array_Vtbl
};





