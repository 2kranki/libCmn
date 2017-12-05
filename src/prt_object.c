// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'prt'
//	Generated 10/02/2017 11:44:50


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



#define			PRT_OBJECT_C	    1
#include        <prt_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct prt_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct prt_class_data_s PRT_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        prt_Info;            // Forward Reference



OBJ_ID          prt_Class(
    void
);



static
bool            prt_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PRT_CLASS == classID) {
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
    return OBJ_IDENT_PRT_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&prt_Info,
    prt_ClassIsKindOf,
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
PRT_CLASS_DATA  prt_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_PRT_CLASS, 0, 1},
	//0
};



static
bool            prt_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PRT == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            prt_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          prt_Class(
    void
)
{
    return (OBJ_ID)&prt_ClassObj;
}


static
uint16_t		prt_WhoAmI(
    void
)
{
    return OBJ_IDENT_PRT;
}


const
PRT_VTBL     prt_Vtbl = {
    {
        &prt_Info,
        prt_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        prt_Dealloc,
        prt_Class,
        prt_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)prt_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)prt_ToDebugString,
        NULL,			// prt_Enable,
        NULL,			// prt_Disable,
        NULL,			// (P_OBJ_ASSIGN)prt_Assign,
        NULL,			// (P_OBJ_COMPARE)prt_Compare,
        NULL, 			// (P_OBJ_PTR)prt_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)prt_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //prt_IsEnabled,
 
};



static
const
OBJ_INFO        prt_Info = {
    "prt",
    "prt",
    (OBJ_DATA *)&prt_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&prt_Vtbl
};





