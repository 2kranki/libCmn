// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'szHash'
//	Generated 01/24/2016 22:37:57

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
#include        "szHash_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct szHash_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct szHash_class_data_s SZHASH_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        szHash_Info;            // Forward Reference



OBJ_ID          szHash_Class(
    OBJ_ID          objId
);



static
bool            szHash_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SZHASH_CLASS == classID) {
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
    return OBJ_IDENT_SZHASH_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&szHash_Info,
    szHash_ClassIsKindOf,
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
SZHASH_CLASS_DATA  szHash_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_SZHASH_CLASS, 0, 1},
	//0
};



static
bool            szHash_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SZHASH == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            szHash_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          szHash_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&szHash_ClassObj;
}


static
uint16_t		szHash_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_SZHASH;
}


const
OBJ_IUNKNOWN    szHash_Vtbl = {
	&szHash_Info,
    szHash_IsKindOf,
    obj_RetainStandard,
    obj_ReleaseStandard,
    szHash_Dealloc,
    szHash_Class,
    szHash_WhoAmI,
    NULL,			// szHash_Enable,
    NULL,			// szHash_Disable,
    (P_OBJ_TOSTRING)szHash_ToDebugString,
    NULL,			// (P_OBJ_ASSIGN)szHash_Assign,
    NULL,			// (P_OBJ_COMPARE)szHash_Compare,
    NULL, 			// (P_OBJ_PTR)szHash_Copy,
    NULL 			// (P_OBJ_HASH)szHash_Hash
};



static
const
OBJ_INFO        szHash_Info = {
    "szHash",
    "szHash",				// <-- Fill in description
    (OBJ_DATA *)&szHash_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





