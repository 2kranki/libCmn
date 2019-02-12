// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'dbf'
//	Generated 10/02/2017 12:31:18


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



#define			DBF_OBJECT_C	    1
#include        <dbf_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct dbf_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct dbf_class_data_s DBF_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        dbf_Info;            // Forward Reference



OBJ_ID          dbf_Class(
    void
);



static
bool            dbf_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DBF_CLASS == classID) {
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
    return OBJ_IDENT_DBF_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&dbf_Info,
    dbf_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    dbf_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
DBF_CLASS_DATA  dbf_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(DBF_CLASS_DATA),             // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            dbf_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DBF == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            dbf_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          dbf_Class(
    void
)
{
    return (OBJ_ID)&dbf_ClassObj;
}


static
uint16_t		dbf_WhoAmI(
    void
)
{
    return OBJ_IDENT_DBF;
}


const
DBF_VTBL     dbf_Vtbl = {
    {
        &dbf_Info,
        dbf_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        dbf_Dealloc,
        dbf_Class,
        dbf_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)dbf_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)dbf_ToDebugString,
        NULL,			// dbf_Enable,
        NULL,			// dbf_Disable,
        NULL,			// (P_OBJ_ASSIGN)dbf_Assign,
        NULL,			// (P_OBJ_COMPARE)dbf_Compare,
        NULL, 			// (P_OBJ_PTR)dbf_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)dbf_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //dbf_IsEnabled,
 
};



static
const
OBJ_INFO        dbf_Info = {
    "dbf",
    "Data Base File",	
    (OBJ_DATA *)&dbf_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&dbf_Vtbl
};





