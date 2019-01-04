// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'lexj'
//	Generated 07/02/2017 09:15:13


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



#define			LEXJ_OBJECT_C	    1
#include        <lexj_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct lexj_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct lexj_class_data_s LEXJ_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        lexj_Info;            // Forward Reference



OBJ_ID          lexj_Class(
    void
);



static
bool            lexj_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_LEXJ_CLASS == classID) {
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
    return OBJ_IDENT_LEXJ_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&lexj_Info,
    lexj_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    lexj_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
LEXJ_CLASS_DATA  lexj_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(LEXJ_CLASS_DATA),            // cbSize
        OBJ_IDENT_LEXJ_CLASS,               // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            lexj_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_LEXJ == classID) {
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
void            lexj_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          lexj_Class(
    void
)
{
    return (OBJ_ID)&lexj_ClassObj;
}


static
uint16_t		lexj_WhoAmI(
    void
)
{
    return OBJ_IDENT_LEXJ;
}


const
LEXJ_VTBL     lexj_Vtbl = {
    {
        &lexj_Info,
        lexj_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        lexj_Dealloc,
        lexj_Class,
        lexj_WhoAmI,
        (P_OBJ_QUERYINFO)lexj_QueryInfo,
        (P_OBJ_TOSTRING)lexj_ToDebugString,
        NULL,			// lexj_Enable,
        NULL,			// lexj_Disable,
        NULL,			// (P_OBJ_ASSIGN)lexj_Assign,
        NULL,			// (P_OBJ_COMPARE)lexj_Compare,
        NULL, 			// (P_OBJ_PTR)lexj_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)lexj_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //lexj_IsEnabled,
 
};



static
const
OBJ_INFO        lexj_Info = {
    "lexj",
    "lexical scanner for HJSON",
    (OBJ_DATA *)&lexj_ClassObj,
    (OBJ_DATA *)&lex_ClassObj,
    (OBJ_IUNKNOWN *)&lexj_Vtbl
};





