// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'lru'
//	Generated 10/21/2016 23:23:20

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


#define			LRU_OBJECT_C	    1
#include        "lru_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct lru_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct lru_class_data_s LRU_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        lru_Info;            // Forward Reference



OBJ_ID          lru_Class(
    OBJ_ID          objId
);



static
bool            lru_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_LRU_CLASS == classID) {
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
    return OBJ_IDENT_LRU_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&lru_Info,
    lru_ClassIsKindOf,
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
LRU_CLASS_DATA  lru_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_LRU_CLASS, 0, 1},
	//0
};



static
bool            lru_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_LRU == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            lru_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          lru_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&lru_ClassObj;
}


static
uint16_t		lru_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_LRU;
}


const
LRU_VTBL     lru_Vtbl = {
    {
        &lru_Info,
        lru_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        lru_Dealloc,
        lru_Class,
        lru_WhoAmI,
        NULL,			// lru_Enable,
        NULL,			// lru_Disable,
        (P_OBJ_TOSTRING)lru_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)lru_Assign,
        NULL,			// (P_OBJ_COMPARE)lru_Compare,
        NULL, 			// (P_OBJ_PTR)lru_Copy,
        NULL 			// (P_OBJ_HASH)lru_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    lru_Read,
    lru_Write
};



static
const
OBJ_INFO        lru_Info = {
    "lru",
    "Least Recently Used Cache",
    (OBJ_DATA *)&lru_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&lru_Vtbl
};





