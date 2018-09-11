// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'btp'
//	Generated 06/27/2016 22:32:29


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


#define			BTP_OBJECT_C	    1
#include        "btp_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct btp_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct btp_class_data_s BTP_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        btp_Info;            // Forward Reference



OBJ_ID          btp_Class(
    void
);



static
bool            btp_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BTP_CLASS == classID) {
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
    return OBJ_IDENT_BTP_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&btp_Info,
    btp_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    btp_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
BTP_CLASS_DATA  btp_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_BTP_CLASS, 0, 1},
	//0
};



static
bool            btp_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BTP == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            btp_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          btp_Class(
    void
)
{
    return (OBJ_ID)&btp_ClassObj;
}


static
uint16_t		btp_WhoAmI(
    void
)
{
    return OBJ_IDENT_BTP;
}


const
BTP_VTBL     btp_Vtbl = {
    {
        &btp_Info,
        btp_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        btp_Dealloc,
        btp_Class,
        btp_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        NULL,           // (P_OBJ_TOSTRING)btp_ToDebugString,
        NULL,			// btp_Enable,
        NULL,			// btp_Disable,
        NULL,			// (P_OBJ_ASSIGN)btp_Assign,
        NULL,			// (P_OBJ_COMPARE)btp_Compare,
        NULL, 			// (P_OBJ_PTR)btp_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)btp_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
 
};



static
const
OBJ_INFO        btp_Info = {
    "btp",
    "Binary Search Tree w/Pointers for data",
    (OBJ_DATA *)&btp_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&btp_Vtbl
};





