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
    void
)
{
    return OBJ_IDENT_NODE_CLASS;
}


//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          class_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODE_CLASS_DATA *this = objId;
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
                        return (void *)&node_Info;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case OBJ_QUERYINFO_TYPE_INFO:
            return (void *)obj_getInfo(this);
            break;
            
        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {
                    
                case 'N':
                    if (str_Compare("New", (char *)pStr) == 0) {
                        return node_New;
                    }
                    break;

#ifdef XYZZY
                case 'P':
                    if (str_Compare("ParseObject", (char *)pStr) == 0) {
                        return node_ParseObject;
                    }
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return obj_ClassWhoAmI;
                    }
                    break;
#endif
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    return NULL;
}



static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&node_Info,
    node_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    node_Class,
    obj_ClassWhoAmI,
    class_QueryInfo,
    NULL                        // class_ToDebugString
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
    void
)
{
    return (OBJ_ID)&node_ClassObj;
}


static
uint16_t		node_WhoAmI(
    void
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
        (P_OBJ_QUERYINFO)node_QueryInfo,
        (P_OBJ_TOSTRING)node_ToDebugString,
        NULL,			// node_Enable,
        NULL,			// node_Disable,
        NULL,			// (P_OBJ_ASSIGN)node_Assign,
        (P_OBJ_COMPARE)node_Compare,
        NULL, 			// (P_OBJ_PTR)node_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)node_Hash
    },
    node_getType,
    node_setType,
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
    node_PropertyA,
    node_PropertyAddA,
    node_PropertyCount,
    node_Properties
};



static
const
OBJ_INFO        node_Info = {
    "node",
    "Generic Node with Properties",
    (OBJ_DATA *)&node_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&node_Vtbl,
    sizeof(NODE_DATA)
};





