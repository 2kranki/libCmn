// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'wav'
//	Generated 11/23/2015 06:58:45

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
#include        "wav_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct wav_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct wav_class_data_s WAV_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        wav_Info;               // Forward Reference



OBJ_ID          wav_Class(
    void
);



static
bool            wav_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_WAV_CLASS == classID) {
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
    return OBJ_IDENT_WAV_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
    &wav_Info,
    wav_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    wav_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
WAV_CLASS_DATA  wav_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_WAV_CLASS, 0, 1},
	//0
};



static
bool            wav_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_WAV == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            wav_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          wav_Class(
    void
)
{
    return (OBJ_ID)&wav_ClassObj;
}


static
uint16_t		wav_WhoAmI(
    void
)
{
    return OBJ_IDENT_WAV;
}


const
WAV_VTBL        wav_Vtbl = {
    {
        &wav_Info,
        wav_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        wav_Dealloc,
        wav_Class,
        wav_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)wav_ToDebugString,
        NULL,			// wav_Enable,
        NULL,			// wav_Disable(
        NULL,			// (P_OBJ_ASSIGN)wav_Assign,
        NULL,			// (P_OBJ_COMPARE)wav_Compare,
        NULL, 			// (P_OBJ_PTR)wav_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)wav_Hash
    }
};



static
const
OBJ_INFO        wav_Info = {
    "wav",
    "WAV file",
    (OBJ_DATA *)&wav_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&wav_Vtbl
};






