// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'hex'
//	Generated 10/08/2016 09:17:56

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


#define			HEX_OBJECT_C	    1
#include        "hex_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct hex_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct hex_class_data_s HEX_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        hex_Info;            // Forward Reference



OBJ_ID          hex_Class(
    void
);



static
bool            hex_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_HEX_CLASS == classID) {
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
    return OBJ_IDENT_HEX_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&hex_Info,
    hex_ClassIsKindOf,
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
HEX_CLASS_DATA  hex_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_HEX_CLASS, 0, 1},
	//0
};



static
bool            hex_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_HEX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            hex_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          hex_Class(
    void
)
{
    return (OBJ_ID)&hex_ClassObj;
}


static
uint16_t		hex_WhoAmI(
    void
)
{
    return OBJ_IDENT_HEX;
}


const
HEX_VTBL     hex_Vtbl = {
    {
        &hex_Info,
        hex_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        hex_Dealloc,
        hex_Class,
        hex_WhoAmI,
        (P_OBJ_QUERYINFO)hex_QueryInfo,
        (P_OBJ_TOSTRING)hex_ToDebugString,
        NULL,			// hex_Enable,
        NULL,			// hex_Disable,
        NULL,			// (P_OBJ_ASSIGN)hex_Assign,
        NULL,			// (P_OBJ_COMPARE)hex_Compare,
        NULL, 			// (P_OBJ_PTR)hex_Copy,
        NULL 			// (P_OBJ_HASH)hex_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //hex_IsEnabled,
 
};



static
const
OBJ_INFO        hex_Info = {
    "hex",
    "Hexadecimal Conversion",
    (OBJ_DATA *)&hex_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&hex_Vtbl
};





