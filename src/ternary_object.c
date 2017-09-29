// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'ternary'
//	Generated 09/02/2016 23:13:42

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


#define			TERNARY_OBJECT_C	    1
#include        "ternary_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct ternary_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct ternary_class_data_s TERNARY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        ternary_Info;            // Forward Reference



OBJ_ID          ternary_Class(
    void
);



static
bool            ternary_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TERNARY_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_BLOCKS_CLASS == classID) {
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
    return OBJ_IDENT_TERNARY_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&ternary_Info,
    ternary_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
TERNARY_CLASS_DATA  ternary_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_TERNARY_CLASS, 0, 1},
	//0
};



static
bool            ternary_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TERNARY == classID) {
       return true;
    }
    if (OBJ_IDENT_BLOCKS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            ternary_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          ternary_Class(
    void
)
{
    return (OBJ_ID)&ternary_ClassObj;
}


static
uint16_t		ternary_WhoAmI(
    void
)
{
    return OBJ_IDENT_TERNARY;
}


const
TERNARY_VTBL     ternary_Vtbl = {
    {
        &ternary_Info,
        ternary_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        ternary_Dealloc,
        ternary_Class,
        ternary_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)ternary_ToDebugString,
        NULL,			// ternary_Enable,
        NULL,			// ternary_Disable,
        NULL,			// (P_OBJ_ASSIGN)ternary_Assign,
        NULL,			// (P_OBJ_COMPARE)ternary_Compare,
        NULL, 			// (P_OBJ_PTR)ternary_Copy,
        NULL 			// (P_OBJ_HASH)ternary_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ternary_IsEnabled,
 
};



static
const
OBJ_INFO        ternary_Info = {
    "ternary",
    "Ternary Search Tree",
    (OBJ_DATA *)&ternary_ClassObj,
    (OBJ_DATA *)&blocks_ClassObj,
    (OBJ_IUNKNOWN *)&ternary_Vtbl
};





