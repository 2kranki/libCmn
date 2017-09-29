// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'bitSet'
//	Generated 05/10/2016 22:49:28

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


#define			BITSET_OBJECT_C	    1
#include        "bitSet_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct bitSet_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct bitSet_class_data_s BITSET_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        bitSet_Info;            // Forward Reference



OBJ_ID          bitSet_Class(
    void
);



static
bool            bitSet_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BITSET_CLASS == classID) {
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
    return OBJ_IDENT_BITSET_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&bitSet_Info,
    bitSet_ClassIsKindOf,
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
BITSET_CLASS_DATA  bitSet_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_BITSET_CLASS, 0, 1},
	//0
};



static
bool            bitSet_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BITSET == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            bitSet_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          bitSet_Class(
    void
)
{
    return (OBJ_ID)&bitSet_ClassObj;
}


static
uint16_t		bitSet_WhoAmI(
    void
)
{
    return OBJ_IDENT_BITSET;
}


const
BITSET_VTBL     bitSet_Vtbl = {
    {
        &bitSet_Info,
        bitSet_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        bitSet_Dealloc,
        bitSet_Class,
        bitSet_WhoAmI,
        NULL,
        (P_OBJ_TOSTRING)bitSet_ToDebugString,
        NULL,			// bitSet_Enable,
        NULL,			// bitSet_Disable,
        NULL,			// (P_OBJ_ASSIGN)bitSet_Assign,
        NULL,			// (P_OBJ_COMPARE)bitSet_Compare,
        NULL, 			// (P_OBJ_PTR)bitSet_Copy,
        NULL 			// (P_OBJ_HASH)bitSet_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
 
};



static
const
OBJ_INFO        bitSet_Info = {
    "bitSet",
    "Set of Bits",
    (OBJ_DATA *)&bitSet_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&bitSet_Vtbl
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





