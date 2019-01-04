// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'hash32'
//	Generated 07/24/2017 08:23:20


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



#define			HASH32_OBJECT_C	    1
#include        <hash32_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct hash32_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct hash32_class_data_s HASH32_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        hash32_Info;            // Forward Reference



OBJ_ID          hash32_Class(
    void
);



static
bool            hash32_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_HASH32_CLASS == classID) {
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
    return OBJ_IDENT_HASH32_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&hash32_Info,
    hash32_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    hash32_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
HASH32_CLASS_DATA  hash32_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(HASH32_CLASS_DATA),          // cbSize
        OBJ_IDENT_HASH32_CLASS,             // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            hash32_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_HASH32 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            hash32_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          hash32_Class(
    void
)
{
    return (OBJ_ID)&hash32_ClassObj;
}


static
uint16_t		hash32_WhoAmI(
    void
)
{
    return OBJ_IDENT_HASH32;
}


const
HASH32_VTBL     hash32_Vtbl = {
    {
        &hash32_Info,
        hash32_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        hash32_Dealloc,
        hash32_Class,
        hash32_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)hash32_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)hash32_ToDebugString,
        NULL,			// hash32_Enable,
        NULL,			// hash32_Disable,
        NULL,			// (P_OBJ_ASSIGN)hash32_Assign,
        NULL,			// (P_OBJ_COMPARE)hash32_Compare,
        NULL, 			// (P_OBJ_PTR)hash32_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)hash32_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //hash32_IsEnabled,
 
};



static
const
OBJ_INFO        hash32_Info = {
    "hash32",
    "Open Chained Hash with uint32_t Keys",
    (OBJ_DATA *)&hash32_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&hash32_Vtbl
};





