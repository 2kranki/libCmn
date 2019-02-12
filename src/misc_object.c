// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'misc'
//	Generated 10/15/2016 09:30:16

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


#define			MISC_OBJECT_C	    1
#include        "misc_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct misc_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct misc_class_data_s MISC_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        misc_Info;            // Forward Reference



OBJ_ID          misc_Class(
    void
);



static
bool            misc_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_MISC_CLASS == classID) {
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
    return OBJ_IDENT_MISC_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&misc_Info,
    misc_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    misc_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
MISC_CLASS_DATA  misc_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(MISC_CLASS_DATA),            // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            misc_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_MISC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            misc_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          misc_Class(
    void
)
{
    return (OBJ_ID)&misc_ClassObj;
}


static
uint16_t		misc_WhoAmI(
    void
)
{
    return OBJ_IDENT_MISC;
}


const
MISC_VTBL     misc_Vtbl = {
    {
        &misc_Info,
        misc_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        misc_Dealloc,
        misc_Class,
        misc_WhoAmI,
        (P_OBJ_QUERYINFO)misc_QueryInfo,
        (P_OBJ_TOSTRING)misc_ToDebugString,
        NULL,			// misc_Enable,
        NULL,			// misc_Disable,
        NULL,			// (P_OBJ_ASSIGN)misc_Assign,
        NULL,			// (P_OBJ_COMPARE)misc_Compare,
        NULL, 			// (P_OBJ_PTR)misc_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)misc_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //misc_IsEnabled,
 
};



static
const
OBJ_INFO        misc_Info = {
    "misc",
    "Miscellaneous Routines",
    (OBJ_DATA *)&misc_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&misc_Vtbl
};





