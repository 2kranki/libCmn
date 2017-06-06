// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'appl'
//	Generated 06/05/2017 10:38:38


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



#define			APPL_OBJECT_C	    1
#include        <appl_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct appl_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct appl_class_data_s APPL_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        appl_Info;            // Forward Reference



OBJ_ID          appl_Class(
    OBJ_ID          objId
);



static
bool            appl_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_APPL_CLASS == classID) {
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
    return OBJ_IDENT_APPL_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&appl_Info,
    appl_ClassIsKindOf,
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
APPL_CLASS_DATA  appl_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_APPL_CLASS, 0, 1},
	//0
};



static
bool            appl_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_APPL == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            appl_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          appl_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&appl_ClassObj;
}


static
uint16_t		appl_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_APPL;
}


const
APPL_VTBL     appl_Vtbl = {
    {
        &appl_Info,
        appl_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        appl_Dealloc,
        appl_Class,
        appl_WhoAmI,
        (P_OBJ_QUERYINFO)appl_QueryInfo,
        (P_OBJ_TOSTRING)appl_ToDebugString,
        NULL,			// appl_Enable,
        NULL,			// appl_Disable,
        NULL,			// (P_OBJ_ASSIGN)appl_Assign,
        NULL,			// (P_OBJ_COMPARE)appl_Compare,
        NULL, 			// (P_OBJ_PTR)appl_Copy,
        NULL 			// (P_OBJ_HASH)appl_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //appl_IsEnabled,
 
};



static
const
OBJ_INFO        appl_Info = {
    "appl",
    "Application Base Object",
    (OBJ_DATA *)&appl_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&appl_Vtbl
};





