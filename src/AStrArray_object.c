// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'AStrArray'
//	Generated 10/02/2017 13:26:39


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



#define			ASTRARRAY_OBJECT_C	    1
#include        <AStrArray_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct AStrArray_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct AStrArray_class_data_s ASTRARRAY_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        AStrArray_Info;            // Forward Reference



OBJ_ID          AStrArray_Class(
    void
);



static
bool            AStrArray_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTRARRAY_CLASS == classID) {
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
    return OBJ_IDENT_ASTRARRAY_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&AStrArray_Info,
    AStrArray_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    AStrArray_Class,
    obj_ClassWhoAmI,
    NULL,                       // aStrArrayClass_QueryInfo
    NULL                        // aStrArrayClass_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
ASTRARRAY_CLASS_DATA  AStrArray_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_ASTRARRAY_CLASS, 0, 1},
	//0
};



static
bool            AStrArray_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTRARRAY == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            AStrArray_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          AStrArray_Class(
    void
)
{
    return (OBJ_ID)&AStrArray_ClassObj;
}


static
uint16_t		AStrArray_WhoAmI(
    void
)
{
    return OBJ_IDENT_ASTRARRAY;
}


const
ASTRARRAY_VTBL     AStrArray_Vtbl = {
    {
        &AStrArray_Info,
        AStrArray_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        AStrArray_Dealloc,
        AStrArray_Class,
        AStrArray_WhoAmI,
        (P_OBJ_QUERYINFO)AStrArray_QueryInfo,
        (P_OBJ_TOSTRING)AStrArray_ToDebugString,
        NULL,			// AStrArray_Enable,
        NULL,			// AStrArray_Disable,
        NULL,			// (P_OBJ_ASSIGN)AStrArray_Assign,
        NULL,			// (P_OBJ_COMPARE)AStrArray_Compare,
        NULL, 			// (P_OBJ_PTR)AStrArray_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)AStrArray_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //AStrArray_IsEnabled,
 
};



static
const
OBJ_INFO        AStrArray_Info = {
    "AStrArray",
    "Array of Ascii Strings",
    (OBJ_DATA *)&AStrArray_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&AStrArray_Vtbl
};





