// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'pplex2'
//	Generated 03/22/2017 10:35:58


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



#define			PPLEX2_OBJECT_C	    1
#include        "pplex2_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct pplex2_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct pplex2_class_data_s PPLEX2_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        pplex2_Info;            // Forward Reference



OBJ_ID          pplex2_Class(
    void
);



static
bool            pplex2_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PPLEX2_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_LEX_CLASS == classID) {
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
    return OBJ_IDENT_PPLEX2_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&pplex2_Info,
    pplex2_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    pplex2_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
PPLEX2_CLASS_DATA  pplex2_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_PPLEX2_CLASS, 0, 1},
	//0
};



static
bool            pplex2_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PPLEX2 == classID) {
       return true;
    }
    if (OBJ_IDENT_LEX == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            pplex2_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          pplex2_Class(
    void
)
{
    return (OBJ_ID)&pplex2_ClassObj;
}


static
uint16_t		pplex2_WhoAmI(
    void
)
{
    return OBJ_IDENT_PPLEX2;
}


const
PPLEX2_VTBL     pplex2_Vtbl = {
    {
        &pplex2_Info,
        pplex2_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        pplex2_Dealloc,
        pplex2_Class,
        pplex2_WhoAmI,
        (P_OBJ_QUERYINFO)pplex2_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)pplex2_ToDebugString,
        NULL,			// pplex2_Enable,
        NULL,			// pplex2_Disable,
        NULL,			// (P_OBJ_ASSIGN)pplex2_Assign,
        NULL,			// (P_OBJ_COMPARE)pplex2_Compare,
        NULL, 			// (P_OBJ_PTR)pplex2_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)pplex2_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //pplex2_IsEnabled,
 
};



static
const
OBJ_INFO        pplex2_Info = {
    "pplex2",
    "Preprocessor Lexical Analyzer - Phase 2",
    (OBJ_DATA *)&pplex2_ClassObj,
    (OBJ_DATA *)&lex_ClassObj,
    (OBJ_IUNKNOWN *)&pplex2_Vtbl
};





