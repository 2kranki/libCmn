// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'objEnum'
//	Generated 10/15/2017 09:38:35


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



#define			OBJENUM_OBJECT_C	    1
#include        <objEnum_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct objEnum_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct objEnum_class_data_s OBJENUM_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        objEnum_Info;            // Forward Reference



OBJ_ID          objEnum_Class(
    void
);



static
bool            objEnum_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJENUM_CLASS == classID) {
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
    return OBJ_IDENT_OBJENUM_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&objEnum_Info,
    objEnum_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    objEnum_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
OBJENUM_CLASS_DATA  objEnum_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(OBJENUM_CLASS_DATA),         // cbSize
        OBJ_IDENT_OBJENUM_CLASS,            // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            objEnum_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_OBJENUM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            objEnum_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          objEnum_Class(
    void
)
{
    return (OBJ_ID)&objEnum_ClassObj;
}


static
uint16_t		objEnum_WhoAmI(
    void
)
{
    return OBJ_IDENT_OBJENUM;
}


const
OBJENUM_VTBL     objEnum_Vtbl = {
    {
        &objEnum_Info,
        objEnum_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        objEnum_Dealloc,
        objEnum_Class,
        objEnum_WhoAmI,
        (P_OBJ_QUERYINFO)objEnum_QueryInfo,
        (P_OBJ_TOSTRING)objEnum_ToDebugString,
        NULL,			// objEnum_Enable,
        NULL,			// objEnum_Disable,
        (P_OBJ_ASSIGN)objEnum_Assign,
        NULL,			// (P_OBJ_COMPARE)objEnum_Compare,
        (P_OBJ_PTR)objEnum_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)objEnum_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    objEnum_Next,
    objEnum_Skip,
    objEnum_Reset,
    objEnum_LookAhead,
    objEnum_Remaining

};



static
const
OBJ_INFO        objEnum_Info = {
    "objEnum",
    "Object Enumerator",
    (OBJ_DATA *)&objEnum_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&objEnum_Vtbl
};





