// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'cmdutl'
//	Generated 03/21/2016 12:13:49

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


#define			CMDUTL_OBJECT_C	    1
#include        "cmdutl_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct cmdutl_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct cmdutl_class_data_s CMDUTL_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        cmdutl_Info;            // Forward Reference



OBJ_ID          cmdutl_Class(
    void
);



static
bool            cmdutl_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CMDUTL_CLASS == classID) {
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
    return OBJ_IDENT_CMDUTL_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&cmdutl_Info,
    cmdutl_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    cmdutl_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
CMDUTL_CLASS_DATA  cmdutl_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(CMDUTL_CLASS_DATA),          // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            cmdutl_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CMDUTL == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            cmdutl_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          cmdutl_Class(
    void
)
{
    return (OBJ_ID)&cmdutl_ClassObj;
}


static
uint16_t		cmdutl_WhoAmI(
    void
)
{
    return OBJ_IDENT_CMDUTL;
}


const
CMDUTL_VTBL     cmdutl_Vtbl = {
    {
        &cmdutl_Info,
        cmdutl_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        cmdutl_Dealloc,
        cmdutl_Class,
        cmdutl_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)cmdutl_ToDebugString,
        NULL,			// cmdutl_Enable,
        NULL,			// cmdutl_Disable,
        NULL,			// (P_OBJ_ASSIGN)cmdutl_Assign,
        NULL,			// (P_OBJ_COMPARE)cmdutl_Compare,
        NULL, 			// (P_OBJ_PTR)cmdutl_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)cmdutl_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
};



static
const
OBJ_INFO        cmdutl_Info = {
    "cmdutl",
    "Command Line Utilities",
    (OBJ_DATA *)&cmdutl_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&cmdutl_Vtbl
};





