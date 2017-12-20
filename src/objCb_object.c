// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'objCb'
//	Generated 10/02/2017 11:59:09


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



#define			OBJCB_OBJECT_C	    1
#include        <objCb_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct objCb_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct objCb_class_data_s OBJCB_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        objCb_Info;            // Forward Reference



OBJ_ID          objCb_Class(
    void
);



static
bool            objCb_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJCB_CLASS == classID) {
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
    return OBJ_IDENT_OBJCB_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&objCb_Info,
    objCb_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    objCb_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
OBJCB_CLASS_DATA  objCb_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_OBJCB_CLASS, 0, 1},
	//0
};



static
bool            objCb_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJCB == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            objCb_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          objCb_Class(
    void
)
{
    return (OBJ_ID)&objCb_ClassObj;
}


static
uint16_t		objCb_WhoAmI(
    void
)
{
    return OBJ_IDENT_OBJCB;
}


const
OBJCB_VTBL     objCb_Vtbl = {
    {
        &objCb_Info,
        objCb_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        objCb_Dealloc,
        objCb_Class,
        objCb_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)objCb_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)objCb_ToDebugString,
        NULL,			// objCb_Enable,
        NULL,			// objCb_Disable,
        NULL,			// (P_OBJ_ASSIGN)objCb_Assign,
        NULL,			// (P_OBJ_COMPARE)objCb_Compare,
        NULL, 			// (P_OBJ_PTR)objCb_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)objCb_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //objCb_IsEnabled,
 
};



static
const
OBJ_INFO        objCb_Info = {
    "objCb",
    "Circular Buffer of Objects",
    (OBJ_DATA *)&objCb_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&objCb_Vtbl
};




