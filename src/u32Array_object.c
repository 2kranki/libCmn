// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'u32Array'
//	Generated 08/25/2016 16:39:40

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


#define			U32ARRAY_OBJECT_C	    1
#include        "u32Array_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct u32Array_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct u32Array_class_data_s U32ARRAY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        u32Array_Info;            // Forward Reference




static
bool            u32Array_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U32ARRAY_CLASS == classID) {
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
uint16_t		obj_ClassWhoAmI(
    void
)
{
    return OBJ_IDENT_U32ARRAY_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&u32Array_Info,
    u32Array_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    u32Array_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
U32ARRAY_CLASS_DATA  u32Array_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(U32ARRAY_CLASS_DATA),        // cbSize
        OBJ_IDENT_U32ARRAY_CLASS,           // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            u32Array_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U32ARRAY == classID) {
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
void            u32Array_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          u32Array_Class(
    void
)
{
    return (OBJ_ID)&u32Array_ClassObj;
}


static
uint16_t		u32Array_WhoAmI(
    void
)
{
    return OBJ_IDENT_U32ARRAY;
}


const
U32ARRAY_VTBL     u32Array_Vtbl = {
    {
        &u32Array_Info,
        u32Array_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        u32Array_Dealloc,
        u32Array_Class,
        u32Array_WhoAmI,
        (P_OBJ_QUERYINFO)u32Array_QueryInfo,
        (P_OBJ_TOSTRING)u32Array_ToDebugString,
        NULL,			// u32Array_Enable,
        NULL,			// u32Array_Disable,
        NULL,			// (P_OBJ_ASSIGN)u32Array_Assign,
        NULL,			// (P_OBJ_COMPARE)u32Array_Compare,
        NULL, 			// (P_OBJ_PTR)u32Array_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL, 			// (P_OBJ_HASH)u32Array_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //u32Array_IsEnabled,
 
};



static
const
OBJ_INFO        u32Array_Info = {
    "u32Array",
    "Array of uint32_t",
    (OBJ_DATA *)&u32Array_ClassObj,
    (OBJ_DATA *)&array_ClassObj,
    (OBJ_IUNKNOWN *)&u32Array_Vtbl
};





