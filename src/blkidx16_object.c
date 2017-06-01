// vi:nu:et:sts=4 ts=4 sw=4

//	Class Object Metods and Tables for 'blkidx16'
//	Generated 03/05/2017 09:37:30


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



#define			BLKIDX16_OBJECT_C	    1
#include        "blkidx16_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct blkidx16_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct blkidx16_class_data_s BLKIDX16_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        blkidx16_Info;            // Forward Reference



OBJ_ID          blkidx16_Class(
    OBJ_ID          objId
);



static
bool            blkidx16_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BLKIDX16_CLASS == classID) {
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
    return OBJ_IDENT_BLKIDX16_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&blkidx16_Info,
    blkidx16_ClassIsKindOf,
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
BLKIDX16_CLASS_DATA  blkidx16_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_BLKIDX16_CLASS, 0, 1},
	//0
};



static
bool            blkidx16_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BLKIDX16 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            blkidx16_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          blkidx16_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&blkidx16_ClassObj;
}


static
uint16_t		blkidx16_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_BLKIDX16;
}


const
BLKIDX16_VTBL     blkidx16_Vtbl = {
    {
        &blkidx16_Info,
        blkidx16_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        blkidx16_Dealloc,
        blkidx16_Class,
        blkidx16_WhoAmI,
        NULL,
        (P_OBJ_TOSTRING)blkidx16_ToDebugString,
        NULL,			// blkidx16_Enable,
        NULL,			// blkidx16_Disable,
        NULL,			// (P_OBJ_ASSIGN)blkidx16_Assign,
        NULL,			// (P_OBJ_COMPARE)blkidx16_Compare,
        NULL, 			// (P_OBJ_PTR)blkidx16_Copy,
        NULL 			// (P_OBJ_HASH)blkidx16_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //blkidx16_IsEnabled,
 
};



static
const
OBJ_INFO        blkidx16_Info = {
    "blkidx16",
    "Indexed Data Block (blkidx16)",
    (OBJ_DATA *)&blkidx16_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&blkidx16_Vtbl
};





