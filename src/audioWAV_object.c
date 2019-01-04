// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'audioWAV'
//	Generated 09/19/2016 20:13:13

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


#define			AUDIOWAV_OBJECT_C	    1
#include        "audioWAV_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct audioWAV_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct audioWAV_class_data_s AUDIOWAV_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        audioWAV_Info;            // Forward Reference



OBJ_ID          audioWAV_Class(
    void
);



static
bool            audioWAV_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_AUDIOWAV_CLASS == classID) {
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
    return OBJ_IDENT_AUDIOWAV_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&audioWAV_Info,
    audioWAV_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    audioWAV_Class,
    obj_ClassWhoAmI,
    NULL,                       // class_QueryInfo
    NULL                        // class_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
AUDIOWAV_CLASS_DATA  audioWAV_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(AUDIOWAV_CLASS_DATA),        // cbSize
        OBJ_IDENT_AUDIOWAV_CLASS,           // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            audioWAV_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_AUDIOWAV == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            audioWAV_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          audioWAV_Class(
    void
)
{
    return (OBJ_ID)&audioWAV_ClassObj;
}


static
uint16_t		audioWAV_WhoAmI(
    void
)
{
    return OBJ_IDENT_AUDIOWAV;
}


const
AUDIOWAV_VTBL     audioWAV_Vtbl = {
    {
        &audioWAV_Info,
        audioWAV_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        audioWAV_Dealloc,
        audioWAV_Class,
        audioWAV_WhoAmI,
        NULL,
        (P_OBJ_TOSTRING)audioWAV_ToDebugString,
        NULL,			// audioWAV_Enable,
        NULL,			// audioWAV_Disable,
        NULL,			// (P_OBJ_ASSIGN)audioWAV_Assign,
        NULL,			// (P_OBJ_COMPARE)audioWAV_Compare,
        NULL, 			// (P_OBJ_PTR)audioWAV_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)audioWAV_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //audioWAV_IsEnabled,
 
};



static
const
OBJ_INFO        audioWAV_Info = {
    "audioWAV",
    "WAV File Audio",
    (OBJ_DATA *)&audioWAV_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&audioWAV_Vtbl,
    sizeof(AUDIOWAV_DATA)
};





