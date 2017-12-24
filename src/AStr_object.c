// vi:nu:et:sts=4 ts=4 sw=4

//	Class Object Metods and Tables for 'AStr'
//	Generated 01/29/2016 22:02:37

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


#include        "AStr_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct AStr_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct AStr_class_data_s ASTR_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        AStr_Info;            // Forward Reference




static
bool            AStr_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTR_CLASS == classID) {
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
    return OBJ_IDENT_ASTR_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&AStr_Info,
    AStr_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    AStr_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
ASTR_CLASS_DATA  AStr_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_ASTR_CLASS, 0, 1},
	//0
};



static
bool            AStr_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTR == classID) {
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
void            AStr_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          AStr_Class(
    void
)
{
    return (OBJ_ID)&AStr_ClassObj;
}


static
uint16_t		AStr_WhoAmI(
    void
)
{
    return OBJ_IDENT_ASTR;
}


const
ASTR_VTBL       AStr_Vtbl = {
    {
        &AStr_Info,
        AStr_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        AStr_Dealloc,
        AStr_Class,
        AStr_WhoAmI,
        (P_OBJ_QUERYINFO)AStr_QueryInfo,
        (P_OBJ_TOSTRING)AStr_ToDebugString,
        NULL,            // AStr_Enable,
        NULL,            // AStr_Disable,
        (P_OBJ_ASSIGN)AStr_Assign,
        (P_OBJ_COMPARE)AStr_Compare,
        (P_OBJ_COPY)AStr_Copy,
        (P_OBJ_DEEPCOPY)AStr_DeepCopy,
        (P_OBJ_HASH)AStr_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    AStr_getData,
    AStr_getLength
};




static
const
OBJ_INFO        AStr_Info = {
    "AStr",
    "Ascii String (UTF-8)",
    (OBJ_DATA *)&AStr_ClassObj,
    (OBJ_DATA *)&array_ClassObj
};





