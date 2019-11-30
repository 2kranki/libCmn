// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'textOut'
//	Generated 12/08/2017 10:18:28


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



#define			TEXTOUT_OBJECT_C	    1
#include        <TextOut_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct TextOut_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct TextOut_class_data_s TEXTOUT_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        TextOut_Info;            // Forward Reference



OBJ_ID          TextOut_Class(
    void
);



static
bool            TextOut_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TEXTOUT_CLASS == classID) {
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
    return OBJ_IDENT_TEXTOUT_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&TextOut_Info,
    TextOut_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    TextOut_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
TEXTOUT_CLASS_DATA  TextOut_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(TEXTOUT_CLASS_DATA),         // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            TextOut_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TEXTOUT == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            TextOut_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          TextOut_Class(
    void
)
{
    return (OBJ_ID)&TextOut_ClassObj;
}


static
uint16_t		TextOut_WhoAmI(
    void
)
{
    return OBJ_IDENT_TEXTOUT;
}


const
TEXTOUT_VTBL     TextOut_Vtbl = {
    {
        &TextOut_Info,
        TextOut_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        TextOut_Dealloc,
        TextOut_Class,
        TextOut_WhoAmI,
        (P_OBJ_QUERYINFO)TextOut_QueryInfo,
        (P_OBJ_TOSTRING)TextOut_ToDebugString,
        NULL,			// TextOut_Enable,
        NULL,			// TextOut_Disable,
        NULL,			// (P_OBJ_ASSIGN)TextOut_Assign,
        NULL,			// (P_OBJ_COMPARE)TextOut_Compare,
        NULL, 			// (P_OBJ_PTR)TextOut_Copy,
        NULL 			// (P_OBJ_HASH)TextOut_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //TextOut_IsEnabled,
 
};



static
const
OBJ_INFO        TextOut_Info = {
    "textOut",
    "Text Output",
    (OBJ_DATA *)&TextOut_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&TextOut_Vtbl
};





