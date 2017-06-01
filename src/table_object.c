// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'table'
//	Generated 05/10/2016 13:42:56

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


#define			TABLE_OBJECT_C	    1
#include        "table_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct table_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct table_class_data_s TABLE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        table_Info;            // Forward Reference



OBJ_ID          table_Class(
    OBJ_ID          objId
);



static
bool            table_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TABLE_CLASS == classID) {
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
    return OBJ_IDENT_TABLE_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&table_Info,
    table_ClassIsKindOf,
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
TABLE_CLASS_DATA  table_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_TABLE_CLASS, 0, 1},
	//0
};



static
bool            table_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TABLE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            table_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          table_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&table_ClassObj;
}


static
uint16_t		table_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_TABLE;
}


const
TABLE_VTBL     table_Vtbl = {
    {
        &table_Info,
        table_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        table_Dealloc,
        table_Class,
        table_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)table_ToDebugString,
        NULL,			// table_Enable,
        NULL,			// table_Disable,
        NULL,			// (P_OBJ_ASSIGN)table_Assign,
        NULL,			// (P_OBJ_COMPARE)table_Compare,
        NULL, 			// (P_OBJ_PTR)table_Copy,
        NULL 			// (P_OBJ_HASH)table_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
 
};



static
const
OBJ_INFO        table_Info = {
    "table",
    "Generalized Table of fixed size entries",
    (OBJ_DATA *)&table_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&table_Vtbl
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





