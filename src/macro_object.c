// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'macro'
//	Generated 08/29/2016 09:41:48

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


#define			MACRO_OBJECT_C	    1
#include        "macro_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct macro_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct macro_class_data_s MACRO_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        macro_Info;            // Forward Reference



OBJ_ID          macro_Class(
    void
);



static
bool            macro_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_MACRO_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_NODE_CLASS == classID) {
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
    return OBJ_IDENT_MACRO_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&macro_Info,
    macro_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    macro_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
MACRO_CLASS_DATA  macro_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_MACRO_CLASS, 0, 1},
	//0
};



static
bool            macro_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_MACRO == classID) {
       return true;
    }
    if (OBJ_IDENT_NODE == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            macro_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          macro_Class(
    void
)
{
    return (OBJ_ID)&macro_ClassObj;
}


static
uint16_t		macro_WhoAmI(
    void
)
{
    return OBJ_IDENT_MACRO;
}


const
MACRO_VTBL     macro_Vtbl = {
    {
        &macro_Info,
        macro_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        macro_Dealloc,
        macro_Class,
        macro_WhoAmI,
        (P_OBJ_QUERYINFO)macro_QueryInfo,
        (P_OBJ_TOSTRING)macro_ToDebugString,
        NULL,			// macro_Enable,
        NULL,			// macro_Disable,
        NULL,			// (P_OBJ_ASSIGN)macro_Assign,
        NULL,			// (P_OBJ_COMPARE)macro_Compare,
        NULL, 			// (P_OBJ_PTR)macro_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)macro_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //macro_IsEnabled,
 
};



static
const
OBJ_INFO        macro_Info = {
    "macro",
    "Macro Entry",
    (OBJ_DATA *)&macro_ClassObj,
    (OBJ_DATA *)&node_ClassObj,
    (OBJ_IUNKNOWN *)&macro_Vtbl
};





