// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'name'
//	Generated 02/07/2016 15:50:27

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
#include        "name_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct name_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    uint32_t        unique;
};
typedef struct name_class_data_s NAME_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        name_Info;            // Forward Reference



OBJ_ID          name_Class(
    OBJ_ID          objId
);



static
bool            name_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NAME_CLASS == classID) {
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
    return OBJ_IDENT_NAME_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&name_Info,
    name_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NAME_CLASS_DATA  name_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_NAME_CLASS, 0, 1},
	0
};



static
bool            name_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NAME == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            name_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          name_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&name_ClassObj;
}


uint32_t        name_NewUnique(
    OBJ_ID          objId
)
{
    return ++name_ClassObj.unique;
}


static
uint16_t		name_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_NAME;
}


const
NAME_VTBL       name_Vtbl = {
    {
        &name_Info,
        name_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        name_Dealloc,
        name_Class,
        name_WhoAmI,
        NULL,			// name_Enable,
        NULL,			// name_Disable,
        (P_OBJ_TOSTRING)name_ToDebugString,
        (P_OBJ_ASSIGN)name_Assign,
        (P_OBJ_COMPARE)name_Compare,
        (P_OBJ_PTR)name_Copy,
        (P_OBJ_HASH)name_Hash
    },
};



static
const
OBJ_INFO        name_Info = {
    "name",
    "Name",				// <-- Fill in description
    (OBJ_DATA *)&name_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





