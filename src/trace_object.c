// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'trace'
//	Generated 01/24/2016 22:39:00

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
#include        "trace_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct trace_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct trace_class_data_s TRACE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        trace_Info;            // Forward Reference



OBJ_ID          trace_Class(
    void
);



static
bool            trace_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TRACE_CLASS == classID) {
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
    return OBJ_IDENT_TRACE_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&trace_Info,
    trace_ClassIsKindOf,
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
TRACE_CLASS_DATA  trace_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_TRACE_CLASS, 0, 1},
	//0
};



static
bool            trace_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TRACE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            trace_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          trace_Class(
    void
)
{
    return (OBJ_ID)&trace_ClassObj;
}


static
uint16_t		trace_WhoAmI(
    void
)
{
    return OBJ_IDENT_TRACE;
}


const
OBJ_IUNKNOWN    trace_Vtbl = {
	&trace_Info,
    trace_IsKindOf,
    obj_RetainStandard,
    obj_ReleaseStandard,
    trace_Dealloc,
    trace_Class,
    trace_WhoAmI,
    NULL,           // (P_OBJ_QUERYINFO)
    NULL,           // (P_OBJ_TOSTRING)trace_ToDebugString,
    NULL,			// trace_Enable,
    NULL,			// trace_Disable,
    NULL,			// (P_OBJ_ASSIGN)trace_Assign,
    NULL,			// (P_OBJ_COMPARE)trace_Compare,
    NULL, 			// (P_OBJ_PTR)trace_Copy,
    NULL 			// (P_OBJ_HASH)trace_Hash
};



static
const
OBJ_INFO        trace_Info = {
    "trace",
    "trace",				// <-- Fill in description
    (OBJ_DATA *)&trace_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





