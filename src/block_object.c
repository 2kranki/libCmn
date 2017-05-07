// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'block'
//	Generated 01/05/2016 07:38:50

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


#include        "obj.h"
#include        "block_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct block_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct block_class_data_s BLOCK_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        block_Info;            // Forward Reference



OBJ_ID          block_Class(
    OBJ_ID          objId
);



static
bool            block_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BLOCK_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		obj_ClassWhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_BLOCK_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&block_Info,
    block_ClassIsKindOf,
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
BLOCK_CLASS_DATA  block_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_BLOCK_CLASS, 0, 1},
	//0
};



static
bool            block_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BLOCK == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            block_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          block_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&block_ClassObj;
}


static
uint16_t		block_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_BLOCK;
}


const
OBJ_IUNKNOWN    block_Vtbl = {
	&block_Info,
    block_IsKindOf,
    obj_RetainStandard,
    obj_ReleaseStandard,
    block_Dealloc,
    block_Class,
    block_WhoAmI,
    NULL,			// block_Enable,
    NULL,			// block_Disable,
    (P_OBJ_TOSTRING)block_ToDebugString,
    NULL,			// (P_OBJ_ASSIGN)block_Assign,
    NULL,			// (P_OBJ_COMPARE)block_Compare,
    NULL, 			// (P_OBJ_PTR)block_Copy,
    NULL 			// (P_OBJ_HASH)block_Hash
};



static
const
OBJ_INFO        block_Info = {
    "block",
    "Data Block with optional Header",
    (OBJ_DATA *)&block_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





