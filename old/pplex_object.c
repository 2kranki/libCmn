// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'pplex'
//	Generated 02/13/2016 14:56:10

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


#define			PPLEX_OBJECT_FILE	1
#include        "pplex_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct pplex_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct pplex_class_data_s PPLEX_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        pplex_Info;            // Forward Reference




static
bool            pplex_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PPLEX_CLASS == classID) {
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
    return OBJ_IDENT_PPLEX_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&pplex_Info,
    pplex_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    pplex_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
PPLEX_CLASS_DATA  pplex_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(PPLEX_CLASS_DATA),           // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            pplex_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PPLEX == classID) {
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
void            pplex_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          pplex_Class(
    void
)
{
    return (OBJ_ID)&pplex_ClassObj;
}


static
uint16_t		pplex_WhoAmI(
    void
)
{
    return OBJ_IDENT_PPLEX;
}


const
PPLEX_VTBL      pplex_Vtbl = {
    {
        &pplex_Info,
        pplex_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        pplex_Dealloc,
        pplex_Class,
        pplex_WhoAmI,
        (P_OBJ_QUERYINFO)pplex_QueryInfo,
        (P_OBJ_TOSTRING)pplex_ToDebugString,
        NULL,			// pplex_Enable,
        NULL,			// pplex_Disable,
        NULL,			// (P_OBJ_ASSIGN)pplex_Assign,
        NULL,			// (P_OBJ_COMPARE)pplex_Compare,
        NULL, 			// (P_OBJ_PTR)pplex_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)pplex_DeepCopy,
        NULL 			// (P_OBJ_HASH)pplex_Hash
    },
};



static
const
OBJ_INFO        pplex_Info = {
    "pplex",
    "Preprocessor Lexical Analyzer/Scanner",
    (OBJ_DATA *)&pplex_ClassObj,
    (OBJ_DATA *)&Lex_ClassObj,
    (OBJ_IUNKNOWN *)&pplex_Vtbl,
    sizeof(PPLEX_DATA)
};





