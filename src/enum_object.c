// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'enum'
//	Generated 06/30/2017 09:01:13


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



#define			ENUM_OBJECT_C	    1
#include        <enum_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct enum_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct enum_class_data_s ENUM_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        enum_Info;            // Forward Reference



OBJ_ID          enum_Class(
    void
);



static
bool            enum_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ENUM_CLASS == classID) {
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
    return OBJ_IDENT_ENUM_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&enum_Info,
    enum_ClassIsKindOf,
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
ENUM_CLASS_DATA  enum_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_ENUM_CLASS, 0, 1},
	//0
};



static
bool            enum_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ENUM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            enum_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          enum_Class(
    void
)
{
    return (OBJ_ID)&enum_ClassObj;
}


static
uint16_t		enum_WhoAmI(
    void
)
{
    return OBJ_IDENT_ENUM;
}


const
ENUM_VTBL     enum_Vtbl = {
    {
        &enum_Info,
        enum_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        enum_Dealloc,
        enum_Class,
        enum_WhoAmI,
        (P_OBJ_QUERYINFO)enum_QueryInfo,
        (P_OBJ_TOSTRING)enum_ToDebugString,
        NULL,			// enum_Enable,
        NULL,			// enum_Disable,
        NULL,			// (P_OBJ_ASSIGN)enum_Assign,
        NULL,			// (P_OBJ_COMPARE)enum_Compare,
        NULL, 			// (P_OBJ_PTR)enum_Copy,
        NULL 			// (P_OBJ_HASH)enum_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    enum_Next,
    enum_Skip,
    enum_Reset,
    enum_LookAhead,
    enum_Remaining
};



static
const
OBJ_INFO        enum_Info = {
    "enum",
    "Enumerator Base Class",
    (OBJ_DATA *)&enum_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&enum_Vtbl
};





