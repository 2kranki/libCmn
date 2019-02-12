// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'srcErrors'
//	Generated 12/17/2017 07:12:35


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



#define			SRCERRORS_OBJECT_C	    1
#include        <srcErrors_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct srcErrors_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct srcErrors_class_data_s SRCERRORS_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        srcErrors_Info;            // Forward Reference



OBJ_ID          srcErrors_Class(
    void
);



static
bool            srcErrors_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCERRORS_CLASS == classID) {
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
    return OBJ_IDENT_SRCERRORS_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&srcErrors_Info,
    srcErrors_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    srcErrors_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
SRCERRORS_CLASS_DATA  srcErrors_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(SRCERRORS_CLASS_DATA),       // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            srcErrors_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCERRORS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            srcErrors_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          srcErrors_Class(
    void
)
{
    return (OBJ_ID)&srcErrors_ClassObj;
}


static
uint16_t		srcErrors_WhoAmI(
    void
)
{
    return OBJ_IDENT_SRCERRORS;
}


const
SRCERRORS_VTBL     srcErrors_Vtbl = {
    {
        &srcErrors_Info,
        srcErrors_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        srcErrors_Dealloc,
        srcErrors_Class,
        srcErrors_WhoAmI,
        (P_OBJ_QUERYINFO)srcErrors_QueryInfo,
        (P_OBJ_TOSTRING)srcErrors_ToDebugString,
        NULL,			// srcErrors_Enable,
        NULL,			// srcErrors_Disable,
        NULL,			// (P_OBJ_ASSIGN)srcErrors_Assign,
        NULL,			// (P_OBJ_COMPARE)srcErrors_Compare,
        NULL, 			// (P_OBJ_PTR)srcErrors_Copy,
        NULL 			// (P_OBJ_HASH)srcErrors_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //srcErrors_IsEnabled,
 
};



static
const
OBJ_INFO        srcErrors_Info = {
    "srcErrors",
    "A Collection of Source Errors",
    (OBJ_DATA *)&srcErrors_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&srcErrors_Vtbl
};





