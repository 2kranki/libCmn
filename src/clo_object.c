// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'clo'
//	Generated 06/05/2017 21:57:10


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



#define			CLO_OBJECT_C	    1
#include        <clo_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct clo_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct clo_class_data_s CLO_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        clo_Info;            // Forward Reference



OBJ_ID          clo_Class(
    OBJ_ID          objId
);



static
bool            clo_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CLO_CLASS == classID) {
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
    return OBJ_IDENT_CLO_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&clo_Info,
    clo_ClassIsKindOf,
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
CLO_CLASS_DATA  clo_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_CLO_CLASS, 0, 1},
	//0
};



static
bool            clo_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CLO == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            clo_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          clo_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&clo_ClassObj;
}


static
uint16_t		clo_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_CLO;
}


const
CLO_VTBL     clo_Vtbl = {
    {
        &clo_Info,
        clo_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        clo_Dealloc,
        clo_Class,
        clo_WhoAmI,
        (P_OBJ_QUERYINFO)clo_QueryInfo,
        (P_OBJ_TOSTRING)clo_ToDebugString,
        NULL,			// clo_Enable,
        NULL,			// clo_Disable,
        NULL,			// (P_OBJ_ASSIGN)clo_Assign,
        NULL,			// (P_OBJ_COMPARE)clo_Compare,
        NULL, 			// (P_OBJ_PTR)clo_Copy,
        NULL 			// (P_OBJ_HASH)clo_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //clo_IsEnabled,
 
};



static
const
OBJ_INFO        clo_Info = {
    "clo",
    "Command Line Option Manager",
    (OBJ_DATA *)&clo_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&clo_Vtbl
};





