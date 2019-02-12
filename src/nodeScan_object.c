// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeScan'
//	Generated 07/10/2016 16:11:02


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




#define			NODESCAN_OBJECT_C	    1
#include        "nodeScan_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct nodeScan_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct nodeScan_class_data_s NODESCAN_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        nodeScan_Info;            // Forward Reference



OBJ_ID          nodeScan_Class(
    void
);



static
bool            nodeScan_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODESCAN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t        obj_ClassWhoAmI(
    void
)
{
    return OBJ_IDENT_NODESCAN_CLASS;
}


//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          nodeScanClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODESCAN_CLASS_DATA
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
                        return (void *)&nodeScan_Info;
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
                        return nodeScan_New;
                    }
                    break;
                    
                case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return obj_ClassWhoAmI;
                    }
                    break;
                    
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
OBJ_IUNKNOWN    class_Vtbl = {
	&nodeScan_Info,
    nodeScan_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    nodeScan_Class,
    obj_ClassWhoAmI,
    nodeScanClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
NODESCAN_CLASS_DATA  nodeScan_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(NODESCAN_CLASS_DATA),       // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            nodeScan_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODESCAN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            nodeScan_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeScan_Class(
    void
)
{
    return (OBJ_ID)&nodeScan_ClassObj;
}


static
uint16_t		nodeScan_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODESCAN;
}


const
NODESCAN_VTBL     nodeScan_Vtbl = {
    {
        &nodeScan_Info,
        nodeScan_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        nodeScan_Dealloc,
        nodeScan_Class,
        nodeScan_WhoAmI,
        (P_OBJ_QUERYINFO)nodeScan_QueryInfo,
        (P_OBJ_TOSTRING)nodeScan_ToDebugString,
        NULL,			// nodeScan_Enable,
        NULL,			// nodeScan_Disable,
        NULL,			// (P_OBJ_ASSIGN)nodeScan_Assign,
        NULL,			// (P_OBJ_COMPARE)nodeScan_Compare,
        NULL, 			// (P_OBJ_PTR)nodeScan_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)nodeScan_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
 
};



static
const
OBJ_INFO        nodeScan_Info = {
    "nodeScan",
    "Node Scanner",
    (OBJ_DATA *)&nodeScan_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&nodeScan_Vtbl,
    sizeof(NODESCAN_DATA)
};





