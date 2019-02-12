// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'parser'
//	Generated 01/23/2016 23:28:57

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


#include        "parser_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct parser_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct parser_class_data_s PARSER_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        parser_Info;            // Forward Reference



OBJ_ID          parser_Class(
    void
);



static
bool            parser_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PARSER_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		parser_ClassWhoAmI(
    void
)
{
    return OBJ_IDENT_PARSER_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&parser_Info,
    parser_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    parser_Class,
    parser_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
PARSER_CLASS_DATA  parser_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(PARSER_CLASS_DATA),          // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            parser_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PARSER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            parser_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          parser_Class(
    void
)
{
    return (OBJ_ID)&parser_ClassObj;
}


static
uint16_t		parser_WhoAmI(
    void
)
{
    return OBJ_IDENT_PARSER;
}


const
PARSER_VTBL     parser_Vtbl = {
    {
        &parser_Info,
        parser_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        parser_Dealloc,
        parser_Class,
        parser_WhoAmI,
        (P_OBJ_QUERYINFO)parser_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)parser_ToDebugString,
        NULL,			// parser_Enable,
        NULL,			// parser_Disable,
        NULL,			// (P_OBJ_ASSIGN)parser_Assign,
        NULL,			// (P_OBJ_COMPARE)parser_Compare,
        NULL, 			// (P_OBJ_PTR)parser_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)parser_Hash
    },
};



static
const
OBJ_INFO        parser_Info = {
    "parser",
    "parser",	
    (OBJ_DATA *)&parser_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&parser_Vtbl
};





