// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'utf8'
//	Generated 02/07/2016 10:06:56

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


#include        "utf8_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct utf8_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct utf8_class_data_s UTF8_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        utf8_Info;            // Forward Reference



OBJ_ID          utf8_Class(
    OBJ_ID          objId
);



static
bool            utf8_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_UTF8_CLASS == classID) {
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
    return OBJ_IDENT_UTF8_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&utf8_Info,
    utf8_ClassIsKindOf,
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
UTF8_CLASS_DATA  utf8_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_UTF8_CLASS, 0, 1},
	//0
};



static
bool            utf8_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_UTF8 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            utf8_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          utf8_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&utf8_ClassObj;
}


static
uint16_t		utf8_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_UTF8;
}


const
UTF8_VTBL       utf8_Vtbl = {
    {
        &utf8_Info,
        utf8_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        utf8_Dealloc,
        utf8_Class,
        utf8_WhoAmI,
        NULL,			// utf8_Enable,
        NULL,			// utf8_Disable,
        (P_OBJ_TOSTRING)utf8_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)utf8_Assign,
        NULL,			// (P_OBJ_COMPARE)utf8_Compare,
        NULL, 			// (P_OBJ_PTR)utf8_Copy,
        NULL 			// (P_OBJ_HASH)utf8_Hash
    }
};



static
const
OBJ_INFO        utf8_Info = {
    "utf8",
    "UTF-8 Support",		
    (OBJ_DATA *)&utf8_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&utf8_Vtbl
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





