// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'W32Str'
//	Generated 01/29/2016 22:02:46

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


#include        <obj.h>
#include        <W32Str_internal.h>
#include        <array_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct W32Str_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct W32Str_class_data_s W32STR_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        W32Str_Info;            // Forward Reference




static
bool            W32Str_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_W32STR_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_ARRAY_CLASS == classID) {
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
    return OBJ_IDENT_W32STR_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&W32Str_Info,
    W32Str_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    W32Str_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
W32STR_CLASS_DATA  W32Str_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(W32STR_CLASS_DATA),          // cbSize
        OBJ_IDENT_W32STR_CLASS,             // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            W32Str_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_W32STR == classID) {
       return true;
    }
    if (OBJ_IDENT_ARRAY == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            W32Str_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          W32Str_Class(
    void
)
{
    return (OBJ_ID)&W32Str_ClassObj;
}


static
uint16_t		W32Str_WhoAmI(
    void
)
{
    return OBJ_IDENT_W32STR;
}


const
W32STR_VTBL   W32Str_Vtbl = {
    {
        &W32Str_Info,
        W32Str_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        W32Str_Dealloc,
        W32Str_Class,
        W32Str_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)W32Str_ToDebugString,
        NULL,            // W32Str_Enable,
        NULL,            // W32Str_Disable,
        (P_OBJ_ASSIGN)W32Str_Assign,
        (P_OBJ_COMPARE)W32Str_Compare,
        (P_OBJ_PTR)W32Str_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        (P_OBJ_HASH)W32Str_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    W32Str_getData,
    W32Str_getLength
};




static
const
OBJ_INFO        W32Str_Info = {
    "WStr",
    "Wide String (int32)",		
    (OBJ_DATA *)&W32Str_ClassObj,
    (OBJ_DATA *)&array_ClassObj
};





