// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'path'
//	Generated 02/05/2016 14:29:04

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
#include        "path_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct path_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct path_class_data_s PATH_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        path_Info;            // Forward Reference



OBJ_ID          path_Class(
    void
);



static
bool            path_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PATH_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_ASTR_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_PWR2ARRAY_CLASS == classID) {
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
    return OBJ_IDENT_PATH_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&path_Info,
    path_ClassIsKindOf,
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
PATH_CLASS_DATA  path_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_PATH_CLASS, 0, 1},
	//0
};



static
bool            path_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PATH == classID) {
       return true;
    }
    if (OBJ_IDENT_ASTR == classID) {
        return true;
    }
    if (OBJ_IDENT_PWR2ARRAY == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            path_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          path_Class(
    void
)
{
    return (OBJ_ID)&path_ClassObj;
}


static
uint16_t		path_WhoAmI(
    void
)
{
    return OBJ_IDENT_PATH;
}


const
OBJ_IUNKNOWN    path_Vtbl = {
	&path_Info,
    path_IsKindOf,
    obj_RetainStandard,
    obj_ReleaseStandard,
    path_Dealloc,
    path_Class,
    path_WhoAmI,
    NULL,           // (P_OBJ_QUERYINFO)
    (P_OBJ_TOSTRING)path_ToDebugString,
    NULL,			// path_Enable,
    NULL,			// path_Disable,
    (P_OBJ_ASSIGN)AStr_Assign,
    (P_OBJ_COMPARE)AStr_Compare,
    (P_OBJ_PTR)AStr_Copy,
    (P_OBJ_HASH)AStr_Hash
};


static
const
OBJ_INFO        path_Info = {
    "path",
    "path",				// <-- Fill in description
    (OBJ_DATA *)&path_ClassObj,
    (OBJ_DATA *)&AStr_ClassObj
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





