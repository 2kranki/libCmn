// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeList'
//	Generated 07/12/2016 22:44:32

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


#define			NODELIST_OBJECT_C	    1
#include        "nodeList_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct nodeList_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct nodeList_class_data_s NODELIST_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        nodeList_Info;            // Forward Reference



OBJ_ID          nodeList_Class(
    void
);



static
bool            nodeList_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODELIST_CLASS == classID) {
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
    return OBJ_IDENT_NODELIST_CLASS;
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
    NODELIST_CLASS_DATA 
                    *this = objId;
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
                        return (void *)&nodeList_Info;
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
                        return nodeList_New;
                    }
                    break;

#ifdef XYZZY
                case 'P':
                    if (str_Compare("ParseObject", (char *)pStr) == 0) {
                        return nodeList_ParseObject;
                    }
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return obj_WhoAmI;
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
	&nodeList_Info,
    nodeList_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    nodeList_Class,
    obj_ClassWhoAmI,
    class_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
NODELIST_CLASS_DATA  nodeList_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_NODELIST_CLASS, 0, 1},
	//0
};



static
bool            nodeList_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODELIST == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            nodeList_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeList_Class(
    void
)
{
    return (OBJ_ID)&nodeList_ClassObj;
}


static
uint16_t		nodeList_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODELIST;
}


const
NODELIST_VTBL     nodeList_Vtbl = {
    {
        &nodeList_Info,
        nodeList_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        nodeList_Dealloc,
        nodeList_Class,
        nodeList_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)nodeList_ToDebugString,
        NULL,			// nodeList_Enable,
        NULL,			// nodeList_Disable,
        NULL,			// (P_OBJ_ASSIGN)nodeList_Assign,
        NULL,			// (P_OBJ_COMPARE)nodeList_Compare,
        NULL, 			// (P_OBJ_PTR)nodeList_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)nodeList_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
 
};



static
const
OBJ_INFO        nodeList_Info = {
    "nodeList",
    "A List of Nodes",
    (OBJ_DATA *)&nodeList_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&nodeList_Vtbl
};





