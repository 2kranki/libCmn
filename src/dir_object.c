// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'dir'
//	Generated 10/11/2016 11:57:48

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


#define			DIR_OBJECT_C	    1
#include        "dir_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct dir_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct dir_class_data_s DIR_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        dir_Info;            // Forward Reference



OBJ_ID          dir_Class(
    void
);



static
bool            dir_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DIR_CLASS == classID) {
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
    return OBJ_IDENT_DIR_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&dir_Info,
    dir_ClassIsKindOf,
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
DIR_CLASS_DATA  dir_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_DIR_CLASS, 0, 1},
	//0
};



static
bool            dir_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DIR == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            dir_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          dir_Class(
    void
)
{
    return (OBJ_ID)&dir_ClassObj;
}


static
uint16_t		dir_WhoAmI(
    void
)
{
    return OBJ_IDENT_DIR;
}


const
DIR_VTBL     dir_Vtbl = {
    {
        &dir_Info,
        dir_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        dir_Dealloc,
        dir_Class,
        dir_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)dir_ToDebugString,
        NULL,			// dir_Enable,
        NULL,			// dir_Disable,
        NULL,			// (P_OBJ_ASSIGN)dir_Assign,
        NULL,			// (P_OBJ_COMPARE)dir_Compare,
        NULL, 			// (P_OBJ_PTR)dir_Copy,
        NULL 			// (P_OBJ_HASH)dir_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //dir_IsEnabled,
 
};



static
const
OBJ_INFO        dir_Info = {
    "dir",
    "Disk Directory",
    (OBJ_DATA *)&dir_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&dir_Vtbl
};





