// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeHash'
//	Generated 01/24/2016 22:36:19

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


#include        "obj.h"
#include        "nodeHash_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct nodeHash_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct nodeHash_class_data_s NODEHASH_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        nodeHash_Info;            // Forward Reference



OBJ_ID          nodeHash_Class(
    void
);



static
bool            nodeHash_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEHASH_CLASS == classID) {
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
    return OBJ_IDENT_NODEHASH_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&nodeHash_Info,
    nodeHash_ClassIsKindOf,
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
NODEHASH_CLASS_DATA  nodeHash_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_NODEHASH_CLASS, 0, 1},
	//0
};



static
bool            nodeHash_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEHASH == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            nodeHash_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeHash_Class(
    void
)
{
    return (OBJ_ID)&nodeHash_ClassObj;
}


static
uint16_t		nodeHash_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODEHASH;
}


const
NODEHASH_VTBL   nodeHash_Vtbl = {
    {
        &nodeHash_Info,
        nodeHash_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        nodeHash_Dealloc,
        nodeHash_Class,
        nodeHash_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)nodeHash_ToDebugString,
        NULL,			// nodeHash_Enable,
        NULL,			// nodeHash_Disable,
        NULL,			// (P_OBJ_ASSIGN)nodeHash_Assign,
        NULL,			// (P_OBJ_COMPARE)nodeHash_Compare,
        (P_OBJ_PTR)nodeHash_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)nodeHash_Hash
    },
};



static
const
OBJ_INFO        nodeHash_Info = {
    "nodeHash",
    "nodeHash",				// <-- Fill in description
    (OBJ_DATA *)&nodeHash_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





