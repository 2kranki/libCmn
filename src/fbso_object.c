// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'fbso'
//	Generated 09/20/2016 10:31:21

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


#define			FBSO_OBJECT_C	    1
#include        "fbso_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct fbso_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct fbso_class_data_s FBSO_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        fbso_Info;            // Forward Reference



OBJ_ID          fbso_Class(
    void
);



static
bool            fbso_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_FBSO_CLASS == classID) {
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
    return OBJ_IDENT_FBSO_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&fbso_Info,
    fbso_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    fbso_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
FBSO_CLASS_DATA  fbso_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_FBSO_CLASS, 0, 1},
	//0
};



static
bool            fbso_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_FBSO == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            fbso_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          fbso_Class(
    void
)
{
    return (OBJ_ID)&fbso_ClassObj;
}


static
uint16_t		fbso_WhoAmI(
    void
)
{
    return OBJ_IDENT_FBSO;
}


const
FBSO_VTBL     fbso_Vtbl = {
    {
        &fbso_Info,
        fbso_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        fbso_Dealloc,
        fbso_Class,
        fbso_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        NULL,           // (P_OBJ_TOSTRING)fbso_ToDebugString,
        NULL,			// fbso_Enable,
        NULL,			// fbso_Disable,
        NULL,			// (P_OBJ_ASSIGN)fbso_Assign,
        NULL,			// (P_OBJ_COMPARE)fbso_Compare,
        NULL, 			// (P_OBJ_PTR)fbso_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)fbso_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //fbso_IsEnabled,
 
};



static
const
OBJ_INFO        fbso_Info = {
    "fbso",
    "Buffered Output File",
    (OBJ_DATA *)&fbso_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&fbso_Vtbl
};





