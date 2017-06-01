// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'node'
//	Generated 02/02/2016 13:39:39

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
#include        "node_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct node_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct node_class_data_s NODE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        node_Info;            // Forward Reference



OBJ_ID          node_Class(
    OBJ_ID          objId
);



static
bool            node_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODE_CLASS == classID) {
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
    return OBJ_IDENT_NODE_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&node_Info,
    node_ClassIsKindOf,
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
NODE_CLASS_DATA  node_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_NODE_CLASS, 0, 1},
	//0
};



static
bool            node_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            node_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          node_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&node_ClassObj;
}


static
uint16_t		node_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_NODE;
}


const
NODE_VTBL       node_Vtbl = {
    {
        &node_Info,
        node_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        node_Dealloc,
        node_Class,
        node_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)node_ToDebugString,
        NULL,			// node_Enable,
        NULL,			// node_Disable,
        NULL,			// (P_OBJ_ASSIGN)node_Assign,
        NULL,			// (P_OBJ_COMPARE)node_Compare,
        NULL, 			// (P_OBJ_PTR)node_Copy,
        NULL 			// (P_OBJ_HASH)node_Hash
    },
    node_getClass,
    node_setClass,
    node_getData,
    node_setData,
    node_getMisc,
    node_setMisc,
    node_getName,
    node_getOther,
    node_setOther,
    node_Compare,
    node_Property,
    node_PropertyAdd,
    node_PropertyCount,
    node_Properties
};



static
const
OBJ_INFO        node_Info = {
    "node",
    "Generic Node with Properties",
    (OBJ_DATA *)&node_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





