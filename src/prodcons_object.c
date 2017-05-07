// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'prodcons'
//	Generated 06/27/2016 23:55:42

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



#define			PRODCONS_OBJECT_C	    1
#include        "prodcons_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct prodcons_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct prodcons_class_data_s PRODCONS_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        prodcons_Info;            // Forward Reference



OBJ_ID          prodcons_Class(
    OBJ_ID          objId
);



static
bool            prodcons_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PRODCONS_CLASS == classID) {
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
    return OBJ_IDENT_PRODCONS_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&prodcons_Info,
    prodcons_ClassIsKindOf,
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
PRODCONS_CLASS_DATA  prodcons_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_PRODCONS_CLASS, 0, 1},
	//0
};



static
bool            prodcons_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PRODCONS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            prodcons_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          prodcons_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&prodcons_ClassObj;
}


static
uint16_t		prodcons_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_PRODCONS;
}


const
PRODCONS_VTBL     prodcons_Vtbl = {
	&prodcons_Info,
    prodcons_IsKindOf,
    obj_RetainStandard,
    obj_ReleaseStandard,
    prodcons_Dealloc,
    prodcons_Class,
    prodcons_WhoAmI,
    NULL,			// prodcons_Enable,
    NULL,			// prodcons_Disable,
    (P_OBJ_TOSTRING)prodcons_ToDebugString,
    NULL,			// (P_OBJ_ASSIGN)prodcons_Assign,
    NULL,			// (P_OBJ_COMPARE)prodcons_Compare,
    NULL, 			// (P_OBJ_PTR)prodcons_Copy,
    NULL, 			// (P_OBJ_HASH)prodcons_Hash,
    // Put other object method names below this.
    // Properties:
    // Methods:
 
};



static
const
OBJ_INFO        prodcons_Info = {
    "prodcons",
    "Producer/Consumer Pattern",
    (OBJ_DATA *)&prodcons_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&prodcons_Vtbl
};





