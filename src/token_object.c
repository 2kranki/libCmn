// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'token'
//	Generated 11/26/2016 00:43:12

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


#define			TOKEN_OBJECT_C	    1
#include        "token_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct token_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct token_class_data_s TOKEN_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        token_Info;            // Forward Reference




static
bool            token_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TOKEN_CLASS == classID) {
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
    return OBJ_IDENT_TOKEN_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&token_Info,
    token_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    token_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
TOKEN_CLASS_DATA  token_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_TOKEN_CLASS, 0, 1},
	//0
};



static
bool            token_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TOKEN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            token_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          token_Class(
    void
)
{
    return (OBJ_ID)&token_ClassObj;
}


static
uint16_t		token_WhoAmI(
    void
)
{
    return OBJ_IDENT_TOKEN;
}


const
TOKEN_VTBL     token_Vtbl = {
    {
        &token_Info,
        token_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        token_Dealloc,
        token_Class,
        token_WhoAmI,
        (P_OBJ_QUERYINFO)token_QueryInfo,
        (P_OBJ_TOSTRING)token_ToDebugString,
        NULL,			// token_Enable,
        NULL,			// token_Disable,
        (P_OBJ_ASSIGN)token_Assign,
        NULL,           // (P_OBJ_COMPARE)token_Compare,
        (P_OBJ_PTR)token_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)token_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //token_IsEnabled,
 
};



static
const
OBJ_INFO        token_Info = {
    "token",
    "Generic Token",
    (OBJ_DATA *)&token_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&token_Vtbl
};





