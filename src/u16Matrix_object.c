// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'u16Matrix'
//	Generated 10/02/2017 10:51:31


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



#define			U16MATRIX_OBJECT_C	    1
#include        <u16Matrix_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct u16Matrix_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct u16Matrix_class_data_s U16MATRIX_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        u16Matrix_Info;            // Forward Reference



OBJ_ID          u16Matrix_Class(
    void
);



static
bool            u16Matrix_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U16MATRIX_CLASS == classID) {
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
    return OBJ_IDENT_U16MATRIX_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&u16Matrix_Info,
    u16Matrix_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    u16Matrix_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
U16MATRIX_CLASS_DATA  u16Matrix_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_U16MATRIX_CLASS, 0, 1},
	//0
};



static
bool            u16Matrix_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U16MATRIX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            u16Matrix_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          u16Matrix_Class(
    void
)
{
    return (OBJ_ID)&u16Matrix_ClassObj;
}


static
uint16_t		u16Matrix_WhoAmI(
    void
)
{
    return OBJ_IDENT_U16MATRIX;
}


const
U16MATRIX_VTBL     u16Matrix_Vtbl = {
    {
        &u16Matrix_Info,
        u16Matrix_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        u16Matrix_Dealloc,
        u16Matrix_Class,
        u16Matrix_WhoAmI,
        (P_OBJ_QUERYINFO)u16Matrix_QueryInfo,
        (P_OBJ_TOSTRING)u16Matrix_ToDebugString,
        NULL,			// u16Matrix_Enable,
        NULL,			// u16Matrix_Disable,
        NULL,			// (P_OBJ_ASSIGN)u16Matrix_Assign,
        NULL,			// (P_OBJ_COMPARE)u16Matrix_Compare,
        NULL, 			// (P_OBJ_PTR)u16Matrix_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)u16Matrix_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //u16Matrix_IsEnabled,
 
};



static
const
OBJ_INFO        u16Matrix_Info = {
    "u16Matrix",
    "uint16 Matrix",
    (OBJ_DATA *)&u16Matrix_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&u16Matrix_Vtbl
};





