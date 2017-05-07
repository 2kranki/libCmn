// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeEntry'
//	Generated 08/29/2016 11:26:27

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


#define			NODEENTRY_OBJECT_C	    1
#include        "nodeEntry_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct nodeEntry_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct nodeEntry_class_data_s NODEENTRY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        nodeEntry_Info;            // Forward Reference



OBJ_ID          nodeEntry_Class(
    OBJ_ID          objId
);



static
bool            nodeEntry_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEENTRY_CLASS == classID) {
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
    return OBJ_IDENT_NODEENTRY_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&nodeEntry_Info,
    nodeEntry_ClassIsKindOf,
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
NODEENTRY_CLASS_DATA  nodeEntry_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_NODEENTRY_CLASS, 0, 1},
	//0
};



static
bool            nodeEntry_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEENTRY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            nodeEntry_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeEntry_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&nodeEntry_ClassObj;
}


static
uint16_t		nodeEntry_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_NODEENTRY;
}


const
NODEENTRY_VTBL     nodeEntry_Vtbl = {
    {
        {
            &nodeEntry_Info,
            nodeEntry_IsKindOf,
            obj_RetainStandard,
            obj_ReleaseStandard,
            nodeEntry_Dealloc,
            nodeEntry_Class,
            nodeEntry_WhoAmI,
            NULL,			// nodeEntry_Enable,
            NULL,			// nodeEntry_Disable,
            (P_OBJ_TOSTRING)nodeEntry_ToDebugString,
            NULL,			// (P_OBJ_ASSIGN)nodeEntry_Assign,
            NULL,			// (P_OBJ_COMPARE)nodeEntry_Compare,
            NULL, 			// (P_OBJ_PTR)nodeEntry_Copy,
            NULL 			// (P_OBJ_HASH)nodeEntry_Hash
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
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
    },
    nodeEntry_getLeft,
    nodeEntry_setLeft,
    nodeEntry_getParent,
    nodeEntry_setParent,
    nodeEntry_getRight,
    nodeEntry_setRight
 
};



static
const
OBJ_INFO        nodeEntry_Info = {
    "nodeEntry",
    "Node Entry which gives Node linkage fields",
    (OBJ_DATA *)&nodeEntry_ClassObj,
    (OBJ_DATA *)&node_ClassObj,
    (OBJ_IUNKNOWN *)&nodeEntry_Vtbl
};





