// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'objTest'
//	Generated 11/01/2017 08:45:27


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



#define			OBJTEST_OBJECT_C	    1
#include        <objTest_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct objTest_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct objTest_class_data_s OBJTEST_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        objTest_Info;            // Forward Reference



OBJ_ID          objTest_Class(
    void
);



static
bool            objTest_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJTEST_CLASS == classID) {
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
    return OBJ_IDENT_OBJTEST_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&objTest_Info,
    objTest_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    objTest_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
OBJTEST_CLASS_DATA  objTest_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_OBJTEST_CLASS, 0, 1},
	//0
};



static
bool            objTest_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJTEST == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            objTest_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          objTest_Class(
    void
)
{
    return (OBJ_ID)&objTest_ClassObj;
}


static
uint16_t		objTest_WhoAmI(
    void
)
{
    return OBJ_IDENT_OBJTEST;
}


const
OBJTEST_VTBL     objTest_Vtbl = {
    {
        &objTest_Info,
        objTest_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        objTest_Dealloc,
        objTest_Class,
        objTest_WhoAmI,
        (P_OBJ_QUERYINFO)objTest_QueryInfo,
        (P_OBJ_TOSTRING)objTest_ToDebugString,
        NULL,			// objTest_Enable,
        NULL,			// objTest_Disable,
        NULL,			// (P_OBJ_ASSIGN)objTest_Assign,
        NULL,			// (P_OBJ_COMPARE)objTest_Compare,
        NULL, 			// (P_OBJ_PTR)objTest_Copy,
        NULL 			// (P_OBJ_HASH)objTest_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //objTest_IsEnabled,
 
};



static
const
OBJ_INFO        objTest_Info = {
    "objTest",
    "Test Object",
    (OBJ_DATA *)&objTest_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&objTest_Vtbl
};





