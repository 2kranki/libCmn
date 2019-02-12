// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'array'
//	Generated 11/08/2017 09:27:01


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



#define			ARRAY_OBJECT_C	    1
#include        <array_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct array_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct array_class_data_s ARRAY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        array_Info;            // Forward Reference



OBJ_ID          array_Class(
    void
);



static
bool            array_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ARRAY_CLASS == classID) {
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
    return OBJ_IDENT_ARRAY_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&array_Info,
    array_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    array_Class,
    obj_ClassWhoAmI,
    NULL,                       // arrayClass_QueryInfo
    NULL                        // arrayClass_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
ARRAY_CLASS_DATA  array_ClassObj = {
    {
        &obj_Vtbl,                      // pVtbl
        sizeof(ARRAY_CLASS_DATA),       // cbSize
        0,                              // cbFlags
        1,                              // cbRetainCount
        {0}                             // cbMisc
    },
	//0
};



static
bool            array_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            array_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          array_Class(
    void
)
{
    return (OBJ_ID)&array_ClassObj;
}


static
uint16_t		array_WhoAmI(
    void
)
{
    return OBJ_IDENT_ARRAY;
}


const
ARRAY_VTBL     array_Vtbl = {
    {
        &array_Info,
        array_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        array_Dealloc,
        array_Class,
        array_WhoAmI,
        (P_OBJ_QUERYINFO)array_QueryInfo,
        (P_OBJ_TOSTRING)array_ToDebugString,
        NULL,			// array_Enable,
        NULL,			// array_Disable,
        NULL,			// (P_OBJ_ASSIGN)array_Assign,
        NULL,			// (P_OBJ_COMPARE)array_Compare,
        (P_OBJ_COPY)array_Copy,
        (P_OBJ_DEEPCOPY)array_DeepCopy,
        NULL 			// (P_OBJ_HASH)array_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //array_IsEnabled,
 
};



static
const
OBJ_INFO        array_Info = {
    "array",
    "Array",
    (OBJ_DATA *)&array_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&array_Vtbl,
    sizeof(ARRAY_DATA)
};





