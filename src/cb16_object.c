// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'cb16'
//	Generated 10/02/2017 12:42:11


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



#define			CB16_OBJECT_C	    1
#include        <cb16_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct cb16_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct cb16_class_data_s CB16_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        cb16_Info;            // Forward Reference



OBJ_ID          cb16_Class(
    void
);



static
bool            cb16_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CB16_CLASS == classID) {
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
    return OBJ_IDENT_CB16_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&cb16_Info,
    cb16_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
CB16_CLASS_DATA  cb16_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_CB16_CLASS, 0, 1},
	//0
};



static
bool            cb16_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CB16 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            cb16_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          cb16_Class(
    void
)
{
    return (OBJ_ID)&cb16_ClassObj;
}


static
uint16_t		cb16_WhoAmI(
    void
)
{
    return OBJ_IDENT_CB16;
}


const
CB16_VTBL     cb16_Vtbl = {
    {
        &cb16_Info,
        cb16_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        cb16_Dealloc,
        cb16_Class,
        cb16_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)cb16_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)cb16_ToDebugString,
        NULL,			// cb16_Enable,
        NULL,			// cb16_Disable,
        NULL,			// (P_OBJ_ASSIGN)cb16_Assign,
        NULL,			// (P_OBJ_COMPARE)cb16_Compare,
        NULL, 			// (P_OBJ_PTR)cb16_Copy,
        NULL 			// (P_OBJ_HASH)cb16_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //cb16_IsEnabled,
 
};



static
const
OBJ_INFO        cb16_Info = {
    "cb16",
    "16 Bit Circular Buffer",
    (OBJ_DATA *)&cb16_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&cb16_Vtbl
};





