// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'WStr'
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
#include        <WStr_internal.h>
#include        <array_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct WStr_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct WStr_class_data_s WSTR_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        WStr_Info;            // Forward Reference



OBJ_ID          WStr_Class(
    void
);



static
bool            WStr_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_WSTR_CLASS == classID) {
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
    return OBJ_IDENT_WSTR_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&WStr_Info,
    WStr_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
WSTR_CLASS_DATA  WStr_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_WSTR_CLASS, 0, 1},
	//0
};



static
bool            WStr_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_WSTR == classID) {
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
void            WStr_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          WStr_Class(
    void
)
{
    return (OBJ_ID)&WStr_ClassObj;
}


static
uint16_t		WStr_WhoAmI(
    void
)
{
    return OBJ_IDENT_WSTR;
}


const
WSTR_VTBL   WStr_Vtbl = {
    {
        &WStr_Info,
        WStr_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        WStr_Dealloc,
        WStr_Class,
        WStr_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)WStr_ToDebugString,
        NULL,            // WStr_Enable,
        NULL,            // WStr_Disable,
        (P_OBJ_ASSIGN)WStr_Assign,
        (P_OBJ_COMPARE)WStr_Compare,
        (P_OBJ_PTR)WStr_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        (P_OBJ_HASH)WStr_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    WStr_getData,
    WStr_getLength
};




static
const
OBJ_INFO        WStr_Info = {
    "WStr",
    "Wide String (int32)",		
    (OBJ_DATA *)&WStr_ClassObj,
    (OBJ_DATA *)&array_ClassObj
};





