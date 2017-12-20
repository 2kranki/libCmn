// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'blocks'
//	Generated 09/04/2016 13:13:56

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


#define			BLOCKS_OBJECT_C	    1
#include        "blocks_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct blocks_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct blocks_class_data_s BLOCKS_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        blocks_Info;            // Forward Reference



OBJ_ID          blocks_Class(
    void
);



static
bool            blocks_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BLOCKS_CLASS == classID) {
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
    return OBJ_IDENT_BLOCKS_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&blocks_Info,
    blocks_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    blocks_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
BLOCKS_CLASS_DATA  blocks_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_BLOCKS_CLASS, 0, 1},
	//0
};



static
bool            blocks_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BLOCKS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            blocks_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          blocks_Class(
    void
)
{
    return (OBJ_ID)&blocks_ClassObj;
}


static
uint16_t		blocks_WhoAmI(
    void
)
{
    return OBJ_IDENT_BLOCKS;
}


const
BLOCKS_VTBL     blocks_Vtbl = {
    {
        &blocks_Info,
        blocks_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        blocks_Dealloc,
        blocks_Class,
        blocks_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)blocks_ToDebugString,
        NULL,			// blocks_Enable,
        NULL,			// blocks_Disable,
        NULL,			// (P_OBJ_ASSIGN)blocks_Assign,
        NULL,			// (P_OBJ_COMPARE)blocks_Compare,
        NULL, 			// (P_OBJ_PTR)blocks_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)blocks_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //blocks_IsEnabled,
 
};



static
const
OBJ_INFO        blocks_Info = {
    "blocks",
    "A List of Blocks/Buffers",
    (OBJ_DATA *)&blocks_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&blocks_Vtbl
};





