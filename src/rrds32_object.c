// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'rrds'
//	Generated 05/10/2016 23:02:20

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


#define			RRDS_OBJECT_C	    1
#include        <rrds32_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct rrds32_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct rrds32_class_data_s RRDS32_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        rrds32_Info;            // Forward Reference




static
bool            rrds32_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_RRDS32_CLASS == classID) {
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
    return OBJ_IDENT_RRDS32_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&rrds32_Info,
    rrds32_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    rrds32_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
RRDS32_CLASS_DATA  rrds32_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(RRDS32_CLASS_DATA),          // cbSize
        OBJ_IDENT_RRDS32_CLASS,             // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            rrds32_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_RRDS32 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            rrds32_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          rrds32_Class(
    void
)
{
    return (OBJ_ID)&rrds32_ClassObj;
}


static
uint16_t		rrds32_WhoAmI(
    void
)
{
    return OBJ_IDENT_RRDS32;
}


const
RRDS32_VTBL     rrds32_Vtbl = {
    {
        &rrds32_Info,
        rrds32_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        rrds32_Dealloc,
        rrds32_Class,
        rrds32_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)rrds32_ToDebugString,
        NULL,			// rrds_Enable,
        NULL,			// rrds_Disable,
        NULL,			// (P_OBJ_ASSIGN)rrds_Assign,
        NULL,			// (P_OBJ_COMPARE)rrds_Compare,
        NULL, 			// (P_OBJ_PTR)rrds_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)rrds_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    rrds32_RecordRead,
    rrds32_RecordWrite
};



static
const
OBJ_INFO        rrds32_Info = {
    "rrds32",
    "Relative Record Dataset - 32 bit logical record number",
    (OBJ_DATA *)&rrds32_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&rrds32_Vtbl
};





