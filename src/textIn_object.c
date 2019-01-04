// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'textIn'
//	Generated 11/23/2017 23:46:18


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



#define			TEXTIN_OBJECT_C	    1
#include        <textIn_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct textIn_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct textIn_class_data_s TEXTIN_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        textIn_Info;            // Forward Reference



OBJ_ID          textIn_Class(
    void
);



static
bool            textIn_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TEXTIN_CLASS == classID) {
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
    return OBJ_IDENT_TEXTIN_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&textIn_Info,
    textIn_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    textIn_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
TEXTIN_CLASS_DATA  textIn_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(TEXTIN_CLASS_DATA),          // cbSize
        OBJ_IDENT_TEXTIN_CLASS,             // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            textIn_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TEXTIN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            textIn_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          textIn_Class(
    void
)
{
    return (OBJ_ID)&textIn_ClassObj;
}


static
uint16_t		textIn_WhoAmI(
    void
)
{
    return OBJ_IDENT_TEXTIN;
}


const
TEXTIN_VTBL     textIn_Vtbl = {
    {
        &textIn_Info,
        textIn_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        textIn_Dealloc,
        textIn_Class,
        textIn_WhoAmI,
        (P_OBJ_QUERYINFO)textIn_QueryInfo,
        (P_OBJ_TOSTRING)textIn_ToDebugString,
        NULL,			// textIn_Enable,
        NULL,			// textIn_Disable,
        NULL,			// (P_OBJ_ASSIGN)textIn_Assign,
        NULL,			// (P_OBJ_COMPARE)textIn_Compare,
        NULL, 			// (P_OBJ_PTR)textIn_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)textIn_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //textIn_IsEnabled,
 
};



static
const
OBJ_INFO        textIn_Info = {
    "textIn",
    "Text Input",
    (OBJ_DATA *)&textIn_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&textIn_Vtbl
};





