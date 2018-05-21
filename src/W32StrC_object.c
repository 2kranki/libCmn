// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'W32StrC'
//	Generated 02/19/2016 09:34:06

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


#define			W32STRC_OBJECT_C	    1
#include        <obj.h>
#include        <W32StrC_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct W32StrC_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct W32StrC_class_data_s W32STRC_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        W32StrC_Info;          // Forward Reference



OBJ_ID          W32StrC_Class(
    void
);



static
bool            W32StrC_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_W32STRC_CLASS == classID) {
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
    return OBJ_IDENT_W32STRC_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&W32StrC_Info,
    W32StrC_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    W32StrC_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
W32STRC_CLASS_DATA  W32StrC_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_W32STRC_CLASS, 0, 1},
	//0
};



static
bool            W32StrC_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_W32STRC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            W32StrC_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          W32StrC_Class(
    void
)
{
    return (OBJ_ID)&W32StrC_ClassObj;
}


static
uint16_t		W32StrC_WhoAmI(
    void
)
{
    return OBJ_IDENT_W32STRC;
}


const
W32STRC_VTBL_INTERNAL W32StrC_Vtbl = {
    {
        {
            &W32StrC_Info,
            W32StrC_IsKindOf,
            obj_RetainStandard,
            obj_ReleaseStandard,
            W32StrC_Dealloc,
            W32StrC_Class,
            W32StrC_WhoAmI,
            NULL,           // (P_OBJ_QUERYINFO)
            (P_OBJ_TOSTRING)W32StrC_ToDebugString,
            NULL,			// WStrC_Enable,
            NULL,			// WStrC_Disable,
            NULL,			// (P_OBJ_ASSIGN)WStrC_Assign,
            (P_OBJ_COMPARE)W32StrC_Compare,
            (P_OBJ_PTR)W32StrC_Copy,
            NULL,           // (P_OBJ_DEEPCOPY)
            (P_OBJ_HASH)W32StrC_Hash
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        W32StrC_getData,
        W32StrC_getLength
    },
#ifdef NDEBUG
#else
    W32StrC_Validate
#endif
 
};



static
const
OBJ_INFO        W32StrC_Info = {
    "W32StrC",
    "Constant Wide String",
    (OBJ_DATA *)&W32StrC_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





