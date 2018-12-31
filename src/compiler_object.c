// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'compiler'
//	Generated 01/23/2016 23:29:11

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


#include        "compiler_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct compiler_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct compiler_class_data_s COMPILER_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        compiler_Info;            // Forward Reference



OBJ_ID          compiler_Class(
    void
);



static
bool            compiler_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_COMPILER_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		compiler_ClassWhoAmI(
    void
)
{
    return OBJ_IDENT_COMPILER_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
    &compiler_Info,
    compiler_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    compiler_Class,
    compiler_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
COMPILER_CLASS_DATA  compiler_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_COMPILER_CLASS, 0, 1},
	//0
};



static
bool            compiler_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_COMPILER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            compiler_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          compiler_Class(
    void
)
{
    return (OBJ_ID)&compiler_ClassObj;
}


static
uint16_t		compiler_WhoAmI(
    void
)
{
    return OBJ_IDENT_COMPILER;
}


const
COMPILER_VTBL   compiler_Vtbl = {
    {
        &compiler_Info,
        compiler_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        compiler_Dealloc,
        compiler_Class,
        compiler_WhoAmI,
        (P_OBJ_QUERYINFO)compiler_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)compiler_ToDebugString,
        NULL,			// compiler_Enable,
        NULL,			// compiler_Disable,
        NULL,			// (P_OBJ_ASSIGN)compiler_Assign,
        NULL,			// (P_OBJ_COMPARE)compiler_Compare,
        NULL, 			// (P_OBJ_PTR)compiler_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)compiler_Hash
    }
};



static
const
OBJ_INFO        compiler_Info = {
    "compiler",
    "Compiler Base",				
    (OBJ_DATA *)&compiler_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&compiler_Vtbl,
    sizeof(COMPILER_DATA)
};





