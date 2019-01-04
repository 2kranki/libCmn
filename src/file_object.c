// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'file'
//	Generated 07/30/2016 19:36:58

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


#define			FILE_OBJECT_C	    1
#include        "file_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct file_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct file_class_data_s FILE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        file_Info;            // Forward Reference



OBJ_ID          file_Class(
    void
);



static
bool            file_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_FILE_CLASS == classID) {
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
    return OBJ_IDENT_FILE_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&file_Info,
    file_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    file_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
FILE_CLASS_DATA  file_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(FILE_CLASS_DATA),            // cbSize
        OBJ_IDENT_FILE_CLASS,               // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            file_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_FILE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            file_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          file_Class(
    void
)
{
    return (OBJ_ID)&file_ClassObj;
}


static
uint16_t		file_WhoAmI(
    void
)
{
    return OBJ_IDENT_FILE;
}


const
FILE_VTBL     file_Vtbl = {
    {
        &file_Info,
        file_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        file_Dealloc,
        file_Class,
        file_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)file_ToDebugString,
        NULL,			// file_Enable,
        NULL,			// file_Disable,
        NULL,			// (P_OBJ_ASSIGN)file_Assign,
        NULL,			// (P_OBJ_COMPARE)file_Compare,
        NULL, 			// (P_OBJ_PTR)file_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)file_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //file_IsEnabled,
 
};



static
const
OBJ_INFO        file_Info = {
    "file",
    "file",	// <-- Fill in description
    (OBJ_DATA *)&file_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&file_Vtbl
};





