// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'u8Array'
//	Generated 07/30/2016 22:31:00

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


#define			U8ARRAY_OBJECT_C	    1
#include        "u8Array_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct u8Array_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct u8Array_class_data_s U8ARRAY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        u8Array_Info;            // Forward Reference




static
bool            u8Array_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U8ARRAY_CLASS == classID) {
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
    return OBJ_IDENT_U8ARRAY_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&u8Array_Info,
    u8Array_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    u8Array_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

U8ARRAY_CLASS_DATA  u8Array_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(U8ARRAY_CLASS_DATA),         // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            u8Array_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U8ARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            u8Array_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          u8Array_Class(
    void
)
{
    return (OBJ_ID)&u8Array_ClassObj;
}


static
uint16_t		u8Array_WhoAmI(
    void
)
{
    return OBJ_IDENT_U8ARRAY;
}


const
U8ARRAY_VTBL     u8Array_Vtbl = {
    {
        &u8Array_Info,
        u8Array_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        u8Array_Dealloc,
        u8Array_Class,
        u8Array_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)u8Array_ToDebugString,
        NULL,			// u8Array_Enable,
        NULL,			// u8Array_Disable,
        NULL,			// (P_OBJ_ASSIGN)u8Array_Assign,
        NULL,			// (P_OBJ_COMPARE)u8Array_Compare,
        NULL, 			// (P_OBJ_PTR)u8Array_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)u8Array_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //u8Array_IsEnabled,
 
};



static
const
OBJ_INFO        u8Array_Info = {
    "u8Array",
    "Unsigned 8-bit Array",
    (OBJ_DATA *)&u8Array_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&u8Array_Vtbl
};





