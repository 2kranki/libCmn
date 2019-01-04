// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'srcError'
//	Generated 12/17/2017 07:12:31


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



#define			SRCERROR_OBJECT_C	    1
#include        <srcError_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct srcError_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct srcError_class_data_s SRCERROR_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        srcError_Info;            // Forward Reference



OBJ_ID          srcError_Class(
    void
);



static
bool            srcError_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCERROR_CLASS == classID) {
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
    return OBJ_IDENT_SRCERROR_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&srcError_Info,
    srcError_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    srcError_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
SRCERROR_CLASS_DATA  srcError_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(SRCERROR_CLASS_DATA),        // cbSize
        OBJ_IDENT_SRCERROR_CLASS,           // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            srcError_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCERROR == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            srcError_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          srcError_Class(
    void
)
{
    return (OBJ_ID)&srcError_ClassObj;
}


static
uint16_t		srcError_WhoAmI(
    void
)
{
    return OBJ_IDENT_SRCERROR;
}


const
SRCERROR_VTBL     srcError_Vtbl = {
    {
        &srcError_Info,
        srcError_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        srcError_Dealloc,
        srcError_Class,
        srcError_WhoAmI,
        (P_OBJ_QUERYINFO)srcError_QueryInfo,
        (P_OBJ_TOSTRING)srcError_ToDebugString,
        NULL,			// srcError_Enable,
        NULL,			// srcError_Disable,
        (P_OBJ_ASSIGN)srcError_Assign,
        (P_OBJ_COMPARE)srcError_Compare,
        (P_OBJ_PTR)srcError_Copy,
        NULL 			// (P_OBJ_HASH)srcError_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //srcError_IsEnabled,
 
};



static
const
OBJ_INFO        srcError_Info = {
    "srcError",
    "Source File Error",
    (OBJ_DATA *)&srcError_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&srcError_Vtbl
};





