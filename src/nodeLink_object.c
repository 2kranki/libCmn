// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeLink'
//	Generated 06/30/2018 19:10:48


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



//#define   NODELINK_IS_SINGLETON     1

#define			NODELINK_OBJECT_C	    1
#include        <nodeLink_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct nodeLink_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct nodeLink_class_data_s NODELINK_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          nodeLinkClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        nodeLink_Info;            // Forward Reference




static
bool            nodeLinkClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODELINK_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_NODE_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		nodeLinkClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODELINK_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&nodeLink_Info,
    nodeLinkClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    nodeLink_Class,
    nodeLinkClass_WhoAmI,
    (P_OBJ_QUERYINFO)nodeLinkClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
NODELINK_CLASS_DATA  nodeLink_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_NODELINK_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          nodeLinkClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODELINK_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&nodeLink_Info;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case OBJ_QUERYINFO_TYPE_INFO:
            return (void *)obj_getInfo(this);
            break;
            
#ifdef XYZZY
        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {
                    
                case 'P':
                    if (str_Compare("ParseObject", (char *)pStr) == 0) {
                        return nodeLink_ParseObject;
                    }
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return nodeLinkClass_WhoAmI;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
            
        default:
            break;
    }
    
    return NULL;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

static
bool            nodeLink_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODELINK == classID) {
       return true;
    }
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
void            nodeLink_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeLink_Class(
    void
)
{
    return (OBJ_ID)&nodeLink_ClassObj;
}


static
uint16_t		nodeLink_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODELINK;
}


const
NODELINK_VTBL     nodeLink_Vtbl = {
    {
        {
            &nodeLink_Info,
            nodeLink_IsKindOf,
    #ifdef  NODELINK_IS_SINGLETON
            obj_RetainNull,
            obj_ReleaseNull,
    #else
            obj_RetainStandard,
            obj_ReleaseStandard,
    #endif
            nodeLink_Dealloc,
            nodeLink_Class,
            nodeLink_WhoAmI,
            (P_OBJ_QUERYINFO)nodeLink_QueryInfo,
            (P_OBJ_TOSTRING)nodeLink_ToDebugString,
            NULL,			// nodeLink_Enable,
            NULL,			// nodeLink_Disable,
            NULL,			// (P_OBJ_ASSIGN)nodeLink_Assign,
            NULL,			// (P_OBJ_COMPARE)nodeLink_Compare,
            NULL, 			// (P_OBJ_PTR)nodeLink_Copy,
            NULL, 			// (P_OBJ_PTR)nodeLink_DeepCopy,
            NULL 			// (P_OBJ_HASH)nodeLink_Hash,
        },
        node_getClass,
        node_setClass,
        node_getData,
        node_setData,
        node_getMisc1,
        node_setMisc1,
        node_getMisc2,
        node_setMisc2,
        node_getName,
        node_getOther,
        node_setOther,
        node_Property,
        node_PropertyAdd,
        node_PropertyCount,
        node_PropertyKeys
    },
    nodeLink_getIndex,
    nodeLink_setIndex,
    nodeLink_getLeft,
    nodeLink_setLeft,
    nodeLink_getMiddle,
    nodeLink_setMiddle,
    nodeLink_getParent,
    nodeLink_setParent,
    nodeLink_getRight,
    nodeLink_setRight,
};



static
const
OBJ_INFO        nodeLink_Info = {
    "nodeLink",
    "A Node with Integer Links",
    (OBJ_DATA *)&nodeLink_ClassObj,
    (OBJ_DATA *)&node_ClassObj,
    (OBJ_IUNKNOWN *)&nodeLink_Vtbl
};





