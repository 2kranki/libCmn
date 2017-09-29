// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'blkdrcds16'
//	Generated 03/10/2017 19:43:23


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




#define			BLKDRCDS16_OBJECT_C	    1
#include        "blkdrcds16_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct blkdrcds16_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct blkdrcds16_class_data_s BLKDRCDS16_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        blkdrcds16_Info;            // Forward Reference



OBJ_ID          blkdrcds16_Class(
    void
);



static
bool            blkdrcds16_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BLKDRCDS16_CLASS == classID) {
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
    return OBJ_IDENT_BLKDRCDS16_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&blkdrcds16_Info,
    blkdrcds16_ClassIsKindOf,
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
BLKDRCDS16_CLASS_DATA  blkdrcds16_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_BLKDRCDS16_CLASS, 0, 1},
	//0
};



static
bool            blkdrcds16_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BLKDRCDS16 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            blkdrcds16_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          blkdrcds16_Class(
    void
)
{
    return (OBJ_ID)&blkdrcds16_ClassObj;
}


static
uint16_t		blkdrcds16_WhoAmI(
    void
)
{
    return OBJ_IDENT_BLKDRCDS16;
}


const
BLKDRCDS16_VTBL     blkdrcds16_Vtbl = {
    {
        &blkdrcds16_Info,
        blkdrcds16_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        blkdrcds16_Dealloc,
        blkdrcds16_Class,
        blkdrcds16_WhoAmI,
        NULL,
        (P_OBJ_TOSTRING)blkdrcds16_ToDebugString,
        NULL,			// blkdrcds16_Enable,
        NULL,			// blkdrcds16_Disable,
        NULL,			// (P_OBJ_ASSIGN)blkdrcds16_Assign,
        NULL,			// (P_OBJ_COMPARE)blkdrcds16_Compare,
        NULL, 			// (P_OBJ_PTR)blkdrcds16_Copy,
        NULL 			// (P_OBJ_HASH)blkdrcds16_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //blkdrcds16_IsEnabled,
 
};



static
const
OBJ_INFO        blkdrcds16_Info = {
    "blkdrcds16",
    "16-Bit Block of Variable Length Records (blkdrcds16)",
    (OBJ_DATA *)&blkdrcds16_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&blkdrcds16_Vtbl
};





