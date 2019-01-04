// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'u16Array'
//	Generated 10/02/2017 11:29:14


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



#define			U16ARRAY_OBJECT_C	    1
#include        <u16Array_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct u16Array_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct u16Array_class_data_s U16ARRAY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        u16Array_Info;            // Forward Reference



OBJ_ID          u16Array_Class(
    void
);



static
bool            u16Array_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U16ARRAY_CLASS == classID) {
       return true;
    }
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
    return OBJ_IDENT_U16ARRAY_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&u16Array_Info,
    u16Array_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    u16Array_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
U16ARRAY_CLASS_DATA  u16Array_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(U16ARRAY_CLASS_DATA),        // cbSize
        OBJ_IDENT_U16ARRAY_CLASS,           // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            u16Array_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U16ARRAY == classID) {
       return true;
    }
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
void            u16Array_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          u16Array_Class(
    void
)
{
    return (OBJ_ID)&u16Array_ClassObj;
}


static
uint16_t		u16Array_WhoAmI(
    void
)
{
    return OBJ_IDENT_U16ARRAY;
}


const
U16ARRAY_VTBL     u16Array_Vtbl = {
    {
        &u16Array_Info,
        u16Array_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        u16Array_Dealloc,
        u16Array_Class,
        u16Array_WhoAmI,
        (P_OBJ_QUERYINFO)u16Array_QueryInfo,
        (P_OBJ_TOSTRING)u16Array_ToDebugString,
        NULL,			// u16Array_Enable,
        NULL,			// u16Array_Disable,
        NULL,			// (P_OBJ_ASSIGN)u16Array_Assign,
        NULL,			// (P_OBJ_COMPARE)u16Array_Compare,
        NULL, 			// (P_OBJ_PTR)u16Array_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)u16Array_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //u16Array_IsEnabled,
 
};



static
const
OBJ_INFO        u16Array_Info = {
    "u16Array",
    "uint16 Array",
    (OBJ_DATA *)&u16Array_ClassObj,
    (OBJ_DATA *)&array_ClassObj,
    (OBJ_IUNKNOWN *)&u16Array_Vtbl
};





