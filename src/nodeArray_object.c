// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeArray'
//	Generated 01/24/2016 22:36:02

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


#include        <nodeArray_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct nodeArray_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct nodeArray_class_data_s NODEARRAY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        nodeArray_Info;            // Forward Reference



OBJ_ID          nodeArray_Class(
    void
);



static
bool            nodeArray_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEARRAY_CLASS == classID) {
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
    return OBJ_IDENT_NODEARRAY_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&nodeArray_Info,
    nodeArray_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    nodeArray_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
NODEARRAY_CLASS_DATA  nodeArray_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_NODEARRAY_CLASS, 0, 1},
	//0
};



static
bool            nodeArray_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            nodeArray_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeArray_Class(
    void
)
{
    return (OBJ_ID)&nodeArray_ClassObj;
}


static
uint16_t		nodeArray_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODEARRAY;
}


const
NODEARRAY_VTBL  nodeArray_Vtbl = {
    {
        &nodeArray_Info,
        nodeArray_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        nodeArray_Dealloc,
        nodeArray_Class,
        nodeArray_WhoAmI,
        (P_OBJ_QUERYINFO)nodeArray_QueryInfo,
        (P_OBJ_TOSTRING)nodeArray_ToDebugString,
        NULL,			// nodeArray_Enable,
        NULL,			// nodeArray_Disable,
        (P_OBJ_ASSIGN)nodeArray_Assign,
        NULL,           // (P_OBJ_COMPARE)nodeArray_Compare,
        (P_OBJ_PTR)nodeArray_Copy,
        (P_OBJ_DEEPCOPY)nodeArray_DeepCopy,
        NULL 			// (P_OBJ_HASH)nodeArray_Hash
    },
};



static
const
OBJ_INFO        nodeArray_Info = {
    "nodeArray",
    "Array of Nodes",				
    (OBJ_DATA *)&nodeArray_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





