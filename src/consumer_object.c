// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'consumer'
//	Generated 06/29/2016 10:31:45

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


#define			CONSUMER_OBJECT_C	    1
#include        "consumer_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct consumer_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct consumer_class_data_s CONSUMER_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        consumer_Info;            // Forward Reference



OBJ_ID          consumer_Class(
    OBJ_ID          objId
);



static
bool            consumer_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CONSUMER_CLASS == classID) {
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
    return OBJ_IDENT_CONSUMER_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&consumer_Info,
    consumer_ClassIsKindOf,
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
CONSUMER_CLASS_DATA  consumer_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_CONSUMER_CLASS, 0, 1},
	//0
};



static
bool            consumer_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CONSUMER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            consumer_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          consumer_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&consumer_ClassObj;
}


static
uint16_t		consumer_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_CONSUMER;
}


const
CONSUMER_VTBL     consumer_Vtbl = {
    {
        &consumer_Info,
        consumer_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        consumer_Dealloc,
        consumer_Class,
        consumer_WhoAmI,
        NULL,			// consumer_Enable,
        NULL,			// consumer_Disable,
        (P_OBJ_TOSTRING)consumer_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)consumer_Assign,
        NULL,			// (P_OBJ_COMPARE)consumer_Compare,
        NULL, 			// (P_OBJ_PTR)consumer_Copy,
        NULL 			// (P_OBJ_HASH)consumer_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
 
};



static
const
OBJ_INFO        consumer_Info = {
    "consumer",
    "Consumer Message Queue Task",
    (OBJ_DATA *)&consumer_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&consumer_Vtbl
};





