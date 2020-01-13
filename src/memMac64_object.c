// vi:nu:et:sts=4 ts=4 sw=4

//	Class Object Metods and Tables for 'memOSX'
//	Generated 02/08/2016 19:45:14

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
#include        <memOSX_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct memOSX_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct memOSX_class_data_s MEMOSX_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        memOSX_Info;            // Forward Reference



OBJ_ID          memOSX_Class(
    void
);



static
bool            memOSX_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_MEMOSX_CLASS == classID) {
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
    return OBJ_IDENT_MEMOSX_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&memOSX_Info,
    memOSX_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    memOSX_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
MEMOSX_CLASS_DATA  memOSX_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_MEMOSX_CLASS, 0, 1},
	//0
};



static
bool            memOSX_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_MEMOSX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            memOSX_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          memOSX_Class(
    void
)
{
    return (OBJ_ID)&memOSX_ClassObj;
}


static
uint16_t		memOSX_WhoAmI(
    void
)
{
    return OBJ_IDENT_MEMOSX;
}


const
OBJ_IUNKNOWN    memOSX_Vtbl = {
	&memOSX_Info,
    memOSX_IsKindOf,
    obj_RetainStandard,
    obj_ReleaseStandard,
    memOSX_Dealloc,
    memOSX_Class,
    memOSX_WhoAmI,
    NULL,
    (P_OBJ_TOSTRING)memOSX_ToDebugString,
    NULL,			// memOSX_Enable,
    NULL,			// memOSX_Disable,
    NULL,			// (P_OBJ_ASSIGN)memOSX_Assign,
    NULL,			// (P_OBJ_COMPARE)memOSX_Compare,
    NULL, 			// (P_OBJ_PTR)memOSX_Copy,
    NULL 			// (P_OBJ_HASH)memOSX_Hash
};



static
const
OBJ_INFO        memOSX_Info = {
    "memOSX",
    "OSX Memory Allocation Checker",
    (OBJ_DATA *)&memOSX_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





