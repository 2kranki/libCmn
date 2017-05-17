// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'lex'
//	Generated 01/28/2016 13:46:58

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


#include        "lex_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct lex_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct lex_class_data_s LEX_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        lex_Info;            // Forward Reference



OBJ_ID          lex_Class(
    OBJ_ID          objId
);



static
bool            lex_ClassIsKindOf(
    uint16_t		classID
)
{
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
    OBJ_ID          objId
)
{
    return OBJ_IDENT_LEX_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&lex_Info,
    lex_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
LEX_CLASS_DATA  lex_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_LEX_CLASS, 0, 1},
	//0
};



static
bool            lex_IsKindOf(
    uint16_t		classID
)
{
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
void            lex_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          lex_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&lex_ClassObj;
}


static
uint16_t		lex_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_LEX;
}


const
LEX_VTBL        lex_Vtbl = {
    {
        &lex_Info,
        lex_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        lex_Dealloc,
        lex_Class,
        lex_WhoAmI,
        NULL,			// lex_Enable,
        NULL,			// lex_Disable,
        (P_OBJ_TOSTRING)lex_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)lex_Assign,
        NULL,			// (P_OBJ_COMPARE)lex_Compare,
        NULL, 			// (P_OBJ_PTR)lex_Copy,
        NULL 			// (P_OBJ_HASH)lex_Hash
    },
    lex_getErrors,
    lex_setErrors,
    lex_setParserFunction,
    lex_setSourceFunction,
    lex_getString,
    lex_getToken,
    lex_Error,
    lex_ErrorFatal,
    lex_InputAdvance,
    lex_InputLookAhead,
    lex_PushToken
};



static
const
OBJ_INFO        lex_Info = {
    "lex",
    "Lexical Analyzer Base",				// <-- Fill in description
    (OBJ_DATA *)&lex_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class




