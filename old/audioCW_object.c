// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'audioCW'
//	Generated 09/19/2016 20:11:01

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


#define			AUDIOCW_OBJECT_C	    1
#include        "audioCW_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct audioCW_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct audioCW_class_data_s AUDIOCW_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        audioCW_Info;            // Forward Reference



OBJ_ID          audioCW_Class(
    void
);



static
bool            audioCW_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_AUDIOCW_CLASS == classID) {
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
    return OBJ_IDENT_AUDIOCW_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&audioCW_Info,
    audioCW_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    audioCW_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
AUDIOCW_CLASS_DATA  audioCW_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(AUDIOCW_CLASS_DATA),         // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            audioCW_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_AUDIOCW == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            audioCW_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          audioCW_Class(
    void
)
{
    return (OBJ_ID)&audioCW_ClassObj;
}


static
uint16_t		audioCW_WhoAmI(
    void
)
{
    return OBJ_IDENT_AUDIOCW;
}


const
AUDIOCW_VTBL     audioCW_Vtbl = {
    {
        &audioCW_Info,
        audioCW_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        audioCW_Dealloc,
        audioCW_Class,
        audioCW_WhoAmI,
        NULL,
        (P_OBJ_TOSTRING)audioCW_ToDebugString,
        NULL,			// audioCW_Enable,
        NULL,			// audioCW_Disable,
        NULL,			// (P_OBJ_ASSIGN)audioCW_Assign,
        NULL,			// (P_OBJ_COMPARE)audioCW_Compare,
        NULL, 			// (P_OBJ_PTR)audioCW_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)audioCW_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //audioCW_IsEnabled,
 
};



static
const
OBJ_INFO        audioCW_Info = {
    "audioCW",
    "Morse Code Audio",
    (OBJ_DATA *)&audioCW_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&audioCW_Vtbl,
    sizeof(AUDIOCW_DATA)
};





