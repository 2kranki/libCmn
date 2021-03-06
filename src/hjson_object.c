// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'hjson'
//	Generated 07/08/2017 17:18:30


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



#define			HJSON_OBJECT_C	    1
#include        <hjson_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct hjson_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct hjson_class_data_s HJSON_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        hjson_Info;            // Forward Reference



OBJ_ID          hjson_Class(
    void
);



static
bool            hjson_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_HJSON_CLASS == classID) {
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
    return OBJ_IDENT_HJSON_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&hjson_Info,
    hjson_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    hjson_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
HJSON_CLASS_DATA  hjson_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(HJSON_CLASS_DATA),           // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            hjson_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_HJSON == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            hjson_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          hjson_Class(
    void
)
{
    return (OBJ_ID)&hjson_ClassObj;
}


static
uint16_t		hjson_WhoAmI(
    void
)
{
    return OBJ_IDENT_HJSON;
}


const
HJSON_VTBL     hjson_Vtbl = {
    {
        &hjson_Info,
        hjson_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        hjson_Dealloc,
        hjson_Class,
        hjson_WhoAmI,
        (P_OBJ_QUERYINFO)hjson_QueryInfo,
        (P_OBJ_TOSTRING)hjson_ToDebugString,
        NULL,			// hjson_Enable,
        NULL,			// hjson_Disable,
        NULL,			// (P_OBJ_ASSIGN)hjson_Assign,
        NULL,			// (P_OBJ_COMPARE)hjson_Compare,
        NULL, 			// (P_OBJ_PTR)hjson_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)hjson_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //hjson_IsEnabled,
 
};



static
const
OBJ_INFO        hjson_Info = {
    "hjson",
    "Human JSON Parser",
    (OBJ_DATA *)&hjson_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&hjson_Vtbl
};





