// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'AStrC'
//	Generated 02/19/2016 09:32:40

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


#define			ASTRC_OBJECT_C	    1
#include        "obj.h"
#include        "AStrC_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct AStrC_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct AStrC_class_data_s ASTRC_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        AStrC_Info;            // Forward Reference



OBJ_ID          AStrC_Class(
    void
);



static
bool            AStrC_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTRC_CLASS == classID) {
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
    return OBJ_IDENT_ASTRC_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&AStrC_Info,
    AStrC_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    AStrC_Class,
    obj_ClassWhoAmI,
    NULL,                       // aStrCClass_QueryInfo
    NULL                        // aStrCClass_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
ASTRC_CLASS_DATA  AStrC_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_ASTRC_CLASS, 0, 1},
	//0
};



static
bool            AStrC_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTRC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            AStrC_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          AStrC_Class(
    void
)
{
    return (OBJ_ID)&AStrC_ClassObj;
}


static
uint16_t		AStrC_WhoAmI(
    void
)
{
    return OBJ_IDENT_ASTRC;
}


const
ASTRC_VTBL      AStrC_Vtbl = {
    {
        &AStrC_Info,
        AStrC_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        AStrC_Dealloc,
        AStrC_Class,
        AStrC_WhoAmI,
        NULL,
        (P_OBJ_TOSTRING)AStrC_ToDebugString,
        NULL,			// AStrC_Enable,
        NULL,			// AStrC_Disable,
        NULL,			// (P_OBJ_ASSIGN)AStrC_Assign,
        (P_OBJ_COMPARE)AStrC_Compare,
        (P_OBJ_COPY)AStrC_Copy,
        (P_OBJ_DEEPCOPY)AStrC_DeepCopy,
        (P_OBJ_HASH)AStrC_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    AStrC_getData,
    AStrC_getLength
};



static
const
OBJ_INFO        AStrC_Info = {
    "AStrC",
    "Constant Ascii/UTF-8 String",
    (OBJ_DATA *)&AStrC_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





