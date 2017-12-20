// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'jsonOut'
//	Generated 08/27/2017 10:50:36


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



#define			JSONOUT_OBJECT_C	    1
#include        <jsonOut_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct jsonOut_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct jsonOut_class_data_s JSONOUT_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        jsonOut_Info;            // Forward Reference



OBJ_ID          jsonOut_Class(
    void
);



static
bool            jsonOut_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_JSONOUT_CLASS == classID) {
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
    return OBJ_IDENT_JSONOUT_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&jsonOut_Info,
    jsonOut_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    jsonOut_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
JSONOUT_CLASS_DATA  jsonOut_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_JSONOUT_CLASS, 0, 1},
	//0
};



static
bool            jsonOut_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_JSONOUT == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            jsonOut_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          jsonOut_Class(
    void
)
{
    return (OBJ_ID)&jsonOut_ClassObj;
}


static
uint16_t		jsonOut_WhoAmI(
    void
)
{
    return OBJ_IDENT_JSONOUT;
}


const
JSONOUT_VTBL     jsonOut_Vtbl = {
    {
        &jsonOut_Info,
        jsonOut_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        jsonOut_Dealloc,
        jsonOut_Class,
        jsonOut_WhoAmI,
        (P_OBJ_QUERYINFO)jsonOut_QueryInfo,
        (P_OBJ_TOSTRING)jsonOut_ToDebugString,
        NULL,			// jsonOut_Enable,
        NULL,			// jsonOut_Disable,
        NULL,			// (P_OBJ_ASSIGN)jsonOut_Assign,
        NULL,			// (P_OBJ_COMPARE)jsonOut_Compare,
        NULL, 			// (P_OBJ_PTR)jsonOut_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)jsonOut_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //jsonOut_IsEnabled,
 
};



static
const
OBJ_INFO        jsonOut_Info = {
    "jsonOut",
    "JSON Standardized Output",
    (OBJ_DATA *)&jsonOut_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&jsonOut_Vtbl
};





