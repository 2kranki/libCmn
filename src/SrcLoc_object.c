// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'srcLoc'
//	Generated 01/01/2016 08:01:11

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
#include        "SrcLoc_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct SrcLoc_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct SrcLoc_class_data_s SRCLOC_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------


static
const
OBJ_INFO        SrcLoc_Info;            // Forward Reference




static
bool            SrcLoc_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCLOC_CLASS == classID) {
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
    return OBJ_IDENT_SRCLOC_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
    &SrcLoc_Info,
    SrcLoc_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    SrcLoc_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
SRCLOC_CLASS_DATA  SrcLoc_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(SRCLOC_CLASS_DATA),          // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            SrcLoc_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCLOC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            SrcLoc_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          SrcLoc_Class(
    void
)
{
    return (OBJ_ID)&SrcLoc_ClassObj;
}


static
uint16_t		SrcLoc_WhoAmI(
    void
)
{
    return OBJ_IDENT_SRCLOC;
}


const
OBJ_IUNKNOWN    SrcLoc_Vtbl = {
    &SrcLoc_Info,
    SrcLoc_IsKindOf,
    obj_RetainStandard,
    obj_ReleaseStandard,
    SrcLoc_Dealloc,
    SrcLoc_Class,
    SrcLoc_WhoAmI,
    (P_OBJ_QUERYINFO)SrcLoc_QueryInfo,
    (P_OBJ_TOSTRING)SrcLoc_ToDebugString,
    NULL,			// SrcLoc_Enable,
    NULL,			// SrcLoc_Disable,
    NULL,			// (P_OBJ_ASSIGN)SrcLoc_Assign,
    NULL,			// (P_OBJ_COMPARE)SrcLoc_Compare,
    NULL, 			// (P_OBJ_PTR)SrcLoc_Copy,
    NULL,           // (P_OBJ_DEEPCOPY)
    NULL 			// (P_OBJ_HASH)SrcLoc_Hash
};



static
const
OBJ_INFO        SrcLoc_Info = {
    "srcLoc",
    "Source File Location including column and line numbers",
    (OBJ_DATA *)&SrcLoc_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};






