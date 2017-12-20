// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'u12Array'
//	Generated 10/08/2016 21:04:05

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


#define			U12ARRAY_OBJECT_C	    1
#include        "u12Array_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct u12Array_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct u12Array_class_data_s U12ARRAY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        u12Array_Info;            // Forward Reference



OBJ_ID          u12Array_Class(
    void
);



static
bool            u12Array_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U12ARRAY_CLASS == classID) {
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
    return OBJ_IDENT_U12ARRAY_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&u12Array_Info,
    u12Array_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    u12Array_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
U12ARRAY_CLASS_DATA  u12Array_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_U12ARRAY_CLASS, 0, 1},
	//0
};



static
bool            u12Array_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U12ARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            u12Array_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          u12Array_Class(
    void
)
{
    return (OBJ_ID)&u12Array_ClassObj;
}


static
uint16_t		u12Array_WhoAmI(
    void
)
{
    return OBJ_IDENT_U12ARRAY;
}


const
U12ARRAY_VTBL     u12Array_Vtbl = {
    {
        &u12Array_Info,
        u12Array_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        u12Array_Dealloc,
        u12Array_Class,
        u12Array_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)u12Array_ToDebugString,
        NULL,			// u12Array_Enable,
        NULL,			// u12Array_Disable,
        NULL,			// (P_OBJ_ASSIGN)u12Array_Assign,
        NULL,			// (P_OBJ_COMPARE)u12Array_Compare,
        NULL, 			// (P_OBJ_PTR)u12Array_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)u12Array_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //u12Array_IsEnabled,
 
};



static
const
OBJ_INFO        u12Array_Info = {
    "u12Array",
    "Unsigned 12-bit Array",
    (OBJ_DATA *)&u12Array_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&u12Array_Vtbl
};





