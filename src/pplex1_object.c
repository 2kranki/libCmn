// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'pplex1'
//	Generated 03/22/2017 10:35:37


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



#define			PPLEX1_OBJECT_C	    1
#include        "pplex1_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct pplex1_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct pplex1_class_data_s PPLEX1_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        pplex1_Info;            // Forward Reference



OBJ_ID          pplex1_Class(
    void
);



static
bool            pplex1_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PPLEX1_CLASS == classID) {
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
    return OBJ_IDENT_PPLEX1_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&pplex1_Info,
    pplex1_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    pplex1_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
PPLEX1_CLASS_DATA  pplex1_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(PPLEX1_CLASS_DATA),          // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            pplex1_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PPLEX1 == classID) {
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
void            pplex1_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          pplex1_Class(
    void
)
{
    return (OBJ_ID)&pplex1_ClassObj;
}


static
uint16_t		pplex1_WhoAmI(
    void
)
{
    return OBJ_IDENT_PPLEX1;
}


const
PPLEX1_VTBL     pplex1_Vtbl = {
    {
        &pplex1_Info,
        pplex1_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        pplex1_Dealloc,
        pplex1_Class,
        pplex1_WhoAmI,
        (P_OBJ_QUERYINFO)pplex1_QueryInfo,
        (P_OBJ_TOSTRING)pplex1_ToDebugString,
        NULL,			// pplex1_Enable,
        NULL,			// pplex1_Disable,
        NULL,			// (P_OBJ_ASSIGN)pplex1_Assign,
        NULL,			// (P_OBJ_COMPARE)pplex1_Compare,
        NULL, 			// (P_OBJ_PTR)pplex1_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)pplex1_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //pplex1_IsEnabled,
 
};



static
const
OBJ_INFO        pplex1_Info = {
    "pplex1",
    "Preprocessor Lexical Analyzer - Phase 1",
    (OBJ_DATA *)&pplex1_ClassObj,
    (OBJ_DATA *)&lex_ClassObj,
    (OBJ_IUNKNOWN *)&pplex1_Vtbl
};





