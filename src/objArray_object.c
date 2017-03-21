// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'objArray'
//	Generated 03/22/2016 17:01:56

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


#define			OBJARRAY_OBJECT_C	    1
#include        "objArray_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct objArray_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct objArray_class_data_s OBJARRAY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        objArray_Info;            // Forward Reference



OBJ_ID          objArray_Class(
    OBJ_ID          objId
);



static
bool            objArray_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJARRAY_CLASS == classID) {
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
    return OBJ_IDENT_OBJARRAY_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&objArray_Info,
    objArray_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
OBJARRAY_CLASS_DATA  objArray_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_OBJARRAY_CLASS, 0, 1},
	//0
};



static
bool            objArray_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            objArray_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          objArray_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&objArray_ClassObj;
}


static
uint16_t		objArray_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_OBJARRAY;
}


const
OBJARRAY_VTBL     objArray_Vtbl = {
    {
        &objArray_Info,
        objArray_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        objArray_Dealloc,
        objArray_Class,
        objArray_WhoAmI,
        NULL,			// objArray_Enable,
        NULL,			// objArray_Disable,
        (P_OBJ_TOSTRING)objArray_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)objArray_Assign,
        NULL,			// (P_OBJ_COMPARE)objArray_Compare,
        NULL, 			// (P_OBJ_PTR)objArray_Copy,
        NULL 			// (P_OBJ_HASH)objArray_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
 
};



static
const
OBJ_INFO        objArray_Info = {
    "objArray",
    "objArray",				// <-- Fill in description
    (OBJ_DATA *)&objArray_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





