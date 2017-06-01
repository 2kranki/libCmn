// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'WStrC'
//	Generated 02/19/2016 09:34:06

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


#define			WSTRC_OBJECT_C	    1
#include        "obj.h"
#include        "WStrC_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct WStrC_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct WStrC_class_data_s WSTRC_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        WStrC_Info;            // Forward Reference



OBJ_ID          WStrC_Class(
    OBJ_ID          objId
);



static
bool            WStrC_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_WSTRC_CLASS == classID) {
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
    return OBJ_IDENT_WSTRC_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&WStrC_Info,
    WStrC_ClassIsKindOf,
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
WSTRC_CLASS_DATA  WStrC_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_WSTRC_CLASS, 0, 1},
	//0
};



static
bool            WStrC_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_WSTRC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            WStrC_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          WStrC_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&WStrC_ClassObj;
}


static
uint16_t		WStrC_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_WSTRC;
}


const
WSTRC_VTBL_INTERNAL WStrC_Vtbl = {
    {
        {
            &WStrC_Info,
            WStrC_IsKindOf,
            obj_RetainStandard,
            obj_ReleaseStandard,
            WStrC_Dealloc,
            WStrC_Class,
            WStrC_WhoAmI,
            NULL,           // (P_OBJ_QUERYINFO)
            (P_OBJ_TOSTRING)WStrC_ToDebugString,
            NULL,			// WStrC_Enable,
            NULL,			// WStrC_Disable,
            NULL,			// (P_OBJ_ASSIGN)WStrC_Assign,
            (P_OBJ_COMPARE)WStrC_Compare,
            (P_OBJ_PTR)WStrC_Copy,
            (P_OBJ_HASH)WStrC_Hash
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        WStrC_getData,
        WStrC_getLength
    },
#ifdef NDEBUG
#else
    WStrC_Validate
#endif
 
};



static
const
OBJ_INFO        WStrC_Info = {
    "WStrC",
    "Constant Wide String",
    (OBJ_DATA *)&WStrC_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};
//#warning -- adjust super class object in Info above
//			if object inherits from another class





