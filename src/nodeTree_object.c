// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeTree'
//	Generated 10/02/2017 12:10:57


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



#define			NODETREE_OBJECT_C	    1
#include        <nodeTree_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct nodeTree_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct nodeTree_class_data_s NODETREE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        nodeTree_Info;            // Forward Reference



OBJ_ID          nodeTree_Class(
    void
);



static
bool            nodeTree_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODETREE_CLASS == classID) {
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
    return OBJ_IDENT_NODETREE_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&nodeTree_Info,
    nodeTree_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    nodeTree_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
NODETREE_CLASS_DATA  nodeTree_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(NODETREE_CLASS_DATA),        // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            nodeTree_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODETREE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            nodeTree_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeTree_Class(
    void
)
{
    return (OBJ_ID)&nodeTree_ClassObj;
}


static
uint16_t		nodeTree_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODETREE;
}


const
NODETREE_VTBL     nodeTree_Vtbl = {
    {
        &nodeTree_Info,
        nodeTree_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        nodeTree_Dealloc,
        nodeTree_Class,
        nodeTree_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)nodeTree_QueryInfo,
        (P_OBJ_TOSTRING)nodeTree_ToDebugString,
        NULL,			// nodeTree_Enable,
        NULL,			// nodeTree_Disable,
        NULL,			// (P_OBJ_ASSIGN)nodeTree_Assign,
        NULL,			// (P_OBJ_COMPARE)nodeTree_Compare,
        NULL, 			// (P_OBJ_PTR)nodeTree_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)nodeTree_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    (void *)nodeTree_getCloseNode,
    (void *)nodeTree_getNodeArrayClass,
    (void *)nodeTree_setNodeArrayClass,
    (void *)nodeTree_getOpenNode,
    (void *)nodeTree_getRootIndex,
    (void *)nodeTree_getSize,
    (void *)nodeTree_Child,
    (void *)nodeTree_ChildAdd,
    (void *)nodeTree_ChildCount,
    (void *)nodeTree_ChildrenAdd,
    (void *)nodeTree_ChildrenMove,
    (void *)nodeTree_Node,
    (void *)nodeTree_NodeDelete,
    (void *)nodeTree_NodeLinkChild,
    (void *)nodeTree_NodeNew,
    (void *)nodeTree_NodeNewUTF8,
    (void *)nodeTree_NodeParent,
    (void *)nodeTree_Nodes,
    (void *)nodeTree_PrintTree,
    (void *)nodeTree_SiblingAdd,
    (void *)nodeTree_SiblingCount,
    (void *)nodeTree_SiblingNext,
    (void *)nodeTree_SiblingsAdd,
    (void *)nodeTree_ToLinearizationPost,
    (void *)nodeTree_ToLinearizationPre,
    (void *)nodeTree_VisitBreadthFirst,
    (void *)nodeTree_VisitPostorder,
    (void *)nodeTree_VisitPreorder,
};



static
const
OBJ_INFO        nodeTree_Info = {
    "nodeTree",
    "Tree of Nodes",
    (OBJ_DATA *)&nodeTree_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&nodeTree_Vtbl,
    sizeof(NODETREE_DATA)
};





