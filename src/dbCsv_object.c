// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'dbCsv'
//	Generated 01/25/2016 11:10:18

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
#include        "dbCsv_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct dbCsv_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct dbCsv_class_data_s DBCSV_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        dbCsv_Info;            // Forward Reference



OBJ_ID          dbCsv_Class(
    void
);



static
bool            dbCsv_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DBCSV_CLASS == classID) {
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
    return OBJ_IDENT_DBCSV_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&dbCsv_Info,
    dbCsv_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    dbCsv_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
DBCSV_CLASS_DATA  dbCsv_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_DBCSV_CLASS, 0, 1},
	//0
};



static
bool            dbCsv_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DBCSV == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            dbCsv_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          dbCsv_Class(
    void
)
{
    return (OBJ_ID)&dbCsv_ClassObj;
}


static
uint16_t		dbCsv_WhoAmI(
    void
)
{
    return OBJ_IDENT_DBCSV;
}


const
DBCSV_VTBL      dbCsv_Vtbl = {
    {
        &dbCsv_Info,
        dbCsv_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        dbCsv_Dealloc,
        dbCsv_Class,
        dbCsv_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)dbCsv_ToDebugString,
        NULL,            // dbCsv_Enable,
        NULL,            // dbCsv_Disable,
        NULL,            // (P_OBJ_ASSIGN)dbCsv_Assign,
        NULL,            // (P_OBJ_COMPARE)dbCsv_Compare,
        NULL,             // (P_OBJ_PTR)dbCsv_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL             // (P_OBJ_HASH)dbCsv_Hash
    }
};



static
const
OBJ_INFO        dbCsv_Info = {
    "dbCsv",
    "Read CSV Files",
    (OBJ_DATA *)&dbCsv_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





