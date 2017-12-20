// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'true'
//	Generated 01/24/2016 22:39:23

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


#include        "true_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct true_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct true_class_data_s TRUE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        true_Info;            // Forward Reference



OBJ_ID          true_Class(
    void
);



static
bool            true_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TRUE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_SHARED_CLASS == classID) {
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
    return OBJ_IDENT_TRUE_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&true_Info,
    true_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    true_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
TRUE_CLASS_DATA  true_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_TRUE_CLASS, 0, 1},
	//0
};



static
bool            true_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TRUE == classID) {
       return true;
    }
    if (OBJ_IDENT_SHARED == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            true_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          true_Class(
    void
)
{
    return (OBJ_ID)&true_ClassObj;
}


static
uint16_t		true_WhoAmI(
    void
)
{
    return OBJ_IDENT_TRUE;
}


const
OBJ_IUNKNOWN    true_Vtbl = {
	&true_Info,
    true_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    true_Class,
    true_WhoAmI,
    (P_OBJ_QUERYINFO)true_QueryInfo,
    (P_OBJ_TOSTRING)true_ToDebugString,
    NULL,			// true_Enable,
    NULL,			// true_Disable,
    NULL,			// (P_OBJ_ASSIGN)true_Assign,
    NULL,			// (P_OBJ_COMPARE)true_Compare,
    NULL, 			// (P_OBJ_PTR)true_Copy,
    NULL,           // (P_OBJ_DEEPCOPY)
    NULL 			// (P_OBJ_HASH)true_Hash
};



static
const
OBJ_INFO        true_Info = {
    "true",
    "true",				// <-- Fill in description
    (OBJ_DATA *)&true_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





