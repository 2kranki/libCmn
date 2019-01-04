// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'cb32'
//	Generated 10/02/2017 12:40:26


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



#define			CB32_OBJECT_C	    1
#include        <cb32_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct cb32_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct cb32_class_data_s CB32_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        cb32_Info;            // Forward Reference



OBJ_ID          cb32_Class(
    void
);



static
bool            cb32_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CB32_CLASS == classID) {
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
    return OBJ_IDENT_CB32_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&cb32_Info,
    cb32_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    cb32_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
CB32_CLASS_DATA  cb32_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(CB32_CLASS_DATA),            // cbSize
        OBJ_IDENT_CB32_CLASS,               // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            cb32_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CB32 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            cb32_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          cb32_Class(
    void
)
{
    return (OBJ_ID)&cb32_ClassObj;
}


static
uint16_t		cb32_WhoAmI(
    void
)
{
    return OBJ_IDENT_CB32;
}


const
CB32_VTBL     cb32_Vtbl = {
    {
        &cb32_Info,
        cb32_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        cb32_Dealloc,
        cb32_Class,
        cb32_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)cb32_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)cb32_ToDebugString,
        NULL,			// cb32_Enable,
        NULL,			// cb32_Disable,
        NULL,			// (P_OBJ_ASSIGN)cb32_Assign,
        NULL,			// (P_OBJ_COMPARE)cb32_Compare,
        NULL, 			// (P_OBJ_PTR)cb32_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)cb32_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //cb32_IsEnabled,
 
};



static
const
OBJ_INFO        cb32_Info = {
    "cb32",
    "32 bit Circular Buffer",
    (OBJ_DATA *)&cb32_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&cb32_Vtbl
};





