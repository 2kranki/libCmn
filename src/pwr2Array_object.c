// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'pwr2Array'
//	Generated 01/24/2016 22:34:47

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
#include        "pwr2Array_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct pwr2Array_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct pwr2Array_class_data_s PWR2ARRAY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        pwr2Array_Info;            // Forward Reference



OBJ_ID          pwr2Array_Class(
    OBJ_ID          objId
);



static
bool            pwr2Array_ClassIsKindOf(
    uint16_t		classID
)
{
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
    OBJ_ID          objId
)
{
    return OBJ_IDENT_PWR2ARRAY_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&pwr2Array_Info,
    pwr2Array_ClassIsKindOf,
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
PWR2ARRAY_CLASS_DATA  pwr2Array_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_PWR2ARRAY_CLASS, 0, 1},
	//0
};



static
bool            pwr2Array_IsKindOf(
    uint16_t		classID
)
{
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
void            pwr2Array_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          pwr2Array_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&pwr2Array_ClassObj;
}


static
uint16_t		pwr2Array_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_PWR2ARRAY;
}


const
PWR2ARRAY_VTBL  pwr2Array_Vtbl = {
    {
        &pwr2Array_Info,
        pwr2Array_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        pwr2Array_Dealloc,
        pwr2Array_Class,
        pwr2Array_WhoAmI,
        NULL,			// pwr2Array_Enable,
        NULL,			// pwr2Array_Disable,
        (P_OBJ_TOSTRING)pwr2Array_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)pwr2Array_Assign,
        NULL,			// (P_OBJ_COMPARE)pwr2Array_Compare,
        NULL, 			// (P_OBJ_PTR)pwr2Array_Copy,
        NULL 			// (P_OBJ_HASH)pwr2Array_Hash
    },
};



static
const
OBJ_INFO        pwr2Array_Info = {
    "pwr2Array",
    "Power of 2 Array",
    (OBJ_DATA *)&pwr2Array_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&pwr2Array_Vtbl
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





