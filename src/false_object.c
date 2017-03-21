// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'false'
//	Generated 01/24/2016 22:39:42

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
#include        "false_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct false_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct false_class_data_s FALSE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        false_Info;            // Forward Reference



OBJ_ID          false_Class(
    OBJ_ID          objId
);



static
bool            false_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_FALSE_CLASS == classID) {
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
    return OBJ_IDENT_FALSE_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&false_Info,
    false_ClassIsKindOf,
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
FALSE_CLASS_DATA  false_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_FALSE_CLASS, 0, 1},
	//0
};



static
bool            false_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_FALSE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            false_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          false_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&false_ClassObj;
}


static
uint16_t		false_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_FALSE;
}


const
FALSE_VTBL      false_Vtbl = {
    {
        &false_Info,
        false_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        false_Class,
        false_WhoAmI,
        NULL,			// false_Enable,
        NULL,			// false_Disable,
        (P_OBJ_TOSTRING)false_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)false_Assign,
        NULL,			// (P_OBJ_COMPARE)false_Compare,
        NULL, 			// (P_OBJ_PTR)false_Copy,
        NULL 			// (P_OBJ_HASH)false_Hash
    },
};



static
const
OBJ_INFO        false_Info = {
    "false",
    "false",				// <-- Fill in description
    (OBJ_DATA *)&false_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





