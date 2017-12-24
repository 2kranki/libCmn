// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'jsonIn'
//	Generated 12/21/2017 05:41:06


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



#define			JSONIN_OBJECT_C	    1
#include        <jsonIn_internal.h>
#include        <dec.h>
#include        <hex.h>
#include        <name.h>
#include        <node.h>
#include        <nodeHash.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct jsonIn_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct jsonIn_class_data_s JSONIN_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        jsonIn_Info;            // Forward Reference




static
bool            jsonIn_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_JSONIN_CLASS == classID) {
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
    return OBJ_IDENT_JSONIN_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&jsonIn_Info,
    jsonIn_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    jsonIn_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
JSONIN_CLASS_DATA  jsonIn_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_JSONIN_CLASS, 0, 1},
	//0
};



static
bool            jsonIn_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_JSONIN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            jsonIn_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          jsonIn_Class(
    void
)
{
    return (OBJ_ID)&jsonIn_ClassObj;
}


static
uint16_t		jsonIn_WhoAmI(
    void
)
{
    return OBJ_IDENT_JSONIN;
}


const
JSONIN_VTBL     jsonIn_Vtbl = {
    {
        &jsonIn_Info,
        jsonIn_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        jsonIn_Dealloc,
        jsonIn_Class,
        jsonIn_WhoAmI,
        (P_OBJ_QUERYINFO)jsonIn_QueryInfo,
        (P_OBJ_TOSTRING)jsonIn_ToDebugString,
        NULL,			// jsonIn_Enable,
        NULL,			// jsonIn_Disable,
        NULL,			// (P_OBJ_ASSIGN)jsonIn_Assign,
        NULL,			// (P_OBJ_COMPARE)jsonIn_Compare,
        NULL, 			// (P_OBJ_PTR)jsonIn_Copy,
        NULL 			// (P_OBJ_HASH)jsonIn_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //jsonIn_IsEnabled,
 
};



static
const
OBJ_INFO        jsonIn_Info = {
    "jsonIn",
    "JSON Input Parse Assistance",
    (OBJ_DATA *)&jsonIn_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&jsonIn_Vtbl
};




