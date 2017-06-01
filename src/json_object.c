// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'json'
//	Generated 01/28/2016 13:49:21

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
#include        "json_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct json_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct json_class_data_s JSON_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        json_Info;            // Forward Reference



OBJ_ID          json_Class(
    OBJ_ID          objId
);



static
bool            json_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_JSON_CLASS == classID) {
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
    return OBJ_IDENT_JSON_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&json_Info,
    json_ClassIsKindOf,
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
JSON_CLASS_DATA  json_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_JSON_CLASS, 0, 1},
	//0
};



static
bool            json_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_JSON == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            json_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          json_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&json_ClassObj;
}


static
uint16_t		json_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_JSON;
}


const
OBJ_IUNKNOWN    json_Vtbl = {
	&json_Info,
    json_IsKindOf,
    obj_RetainStandard,
    obj_ReleaseStandard,
    json_Dealloc,
    json_Class,
    json_WhoAmI,
    NULL,           // (P_OBJ_QUERYINFO)
    (P_OBJ_TOSTRING)json_ToDebugString,
    NULL,			// json_Enable,
    NULL,			// json_Disable,
    NULL,			// (P_OBJ_ASSIGN)json_Assign,
    NULL,			// (P_OBJ_COMPARE)json_Compare,
    NULL, 			// (P_OBJ_PTR)json_Copy,
    NULL 			// (P_OBJ_HASH)json_Hash
};



static
const
OBJ_INFO        json_Info = {
    "json",
    "json file input",		
    (OBJ_DATA *)&json_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





