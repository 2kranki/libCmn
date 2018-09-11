// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'execArray'
//	Generated 05/09/2016 11:04:12

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


#define			EXECARRAY_OBJECT_C	    1
#include        "execArray_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct execArray_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct execArray_class_data_s EXECARRAY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        execArray_Info;            // Forward Reference



OBJ_ID          execArray_Class(
    void
);



static
bool            execArray_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_EXECARRAY_CLASS == classID) {
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
    return OBJ_IDENT_EXECARRAY_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&execArray_Info,
    execArray_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    execArray_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
EXECARRAY_CLASS_DATA  execArray_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_EXECARRAY_CLASS, 0, 1},
	//0
};



static
bool            execArray_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_EXECARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            execArray_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          execArray_Class(
    void
)
{
    return (OBJ_ID)&execArray_ClassObj;
}


static
uint16_t		execArray_WhoAmI(
    void
)
{
    return OBJ_IDENT_EXECARRAY;
}


const
EXECARRAY_VTBL     execArray_Vtbl = {
    {
        &execArray_Info,
        execArray_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        execArray_Dealloc,
        execArray_Class,
        execArray_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)execArray_ToDebugString,
        NULL,			// execArray_Enable,
        NULL,			// execArray_Disable,
        NULL,			// (P_OBJ_ASSIGN)execArray_Assign,
        NULL,			// (P_OBJ_COMPARE)execArray_Compare,
        NULL, 			// (P_OBJ_PTR)execArray_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)execArray_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
 
};



static
const
OBJ_INFO        execArray_Info = {
    "execArray",
    "Execution Array or an array of methods and objects which can be executed en mass",
    (OBJ_DATA *)&execArray_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&execArray_Vtbl
};





