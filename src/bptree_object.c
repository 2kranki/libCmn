// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'bptree'
//	Generated 03/05/2017 10:40:41


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




#define			BPTREE_OBJECT_C	    1
#include        "bptree_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct bptree_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct bptree_class_data_s BPTREE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        bptree_Info;            // Forward Reference



OBJ_ID          bptree_Class(
    void
);



static
bool            bptree_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPTREE_CLASS == classID) {
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
    return OBJ_IDENT_BPTREE_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&bptree_Info,
    bptree_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    bptree_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
BPTREE_CLASS_DATA  bptree_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_BPTREE_CLASS, 0, 1},
	//0
};



static
bool            bptree_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPTREE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            bptree_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          bptree_Class(
    void
)
{
    return (OBJ_ID)&bptree_ClassObj;
}


static
uint16_t		bptree_WhoAmI(
    void
)
{
    return OBJ_IDENT_BPTREE;
}


const
BPTREE_VTBL     bptree_Vtbl = {
    {
        &bptree_Info,
        bptree_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        bptree_Dealloc,
        bptree_Class,
        bptree_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)bptree_ToDebugString,
        NULL,			// bptree_Enable,
        NULL,			// bptree_Disable,
        NULL,			// (P_OBJ_ASSIGN)bptree_Assign,
        NULL,			// (P_OBJ_COMPARE)bptree_Compare,
        NULL, 			// (P_OBJ_PTR)bptree_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)bptree_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //bptree_IsEnabled,
 
};



static
const
OBJ_INFO        bptree_Info = {
    "bptree",
    "B+ Tree (bptree)",
    (OBJ_DATA *)&bptree_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&bptree_Vtbl
};





