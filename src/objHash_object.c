// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'objHash'
//	Generated 01/24/2016 22:35:13

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


#include        "obj.h"
#include        "objHash_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct objHash_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct objHash_class_data_s OBJHASH_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        objHash_Info;            // Forward Reference



OBJ_ID          objHash_Class(
    void
);



static
bool            objHash_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJHASH_CLASS == classID) {
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
    return OBJ_IDENT_OBJHASH_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&objHash_Info,
    objHash_ClassIsKindOf,
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
OBJHASH_CLASS_DATA  objHash_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_OBJHASH_CLASS, 0, 1},
	//0
};



static
bool            objHash_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJHASH == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            objHash_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          objHash_Class(
    void
)
{
    return (OBJ_ID)&objHash_ClassObj;
}


static
uint16_t		objHash_WhoAmI(
    void
)
{
    return OBJ_IDENT_OBJHASH;
}


const
OBJHASH_VTBL    objHash_Vtbl = {
    {
        &objHash_Info,
        objHash_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        objHash_Dealloc,
        objHash_Class,
        objHash_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)objHash_ToDebugString,
        NULL,            // objHash_Enable,
        NULL,            // objHash_Disable,
        NULL,            // (P_OBJ_ASSIGN)objHash_Assign,
        NULL,            // (P_OBJ_COMPARE)objHash_Compare,
        NULL,             // (P_OBJ_PTR)objHash_Copy,
        NULL             // (P_OBJ_HASH)objHash_Hash
    }
};



static
const
OBJ_INFO        objHash_Info = {
    "objHash",
    "Object Hash",
    (OBJ_DATA *)&objHash_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





