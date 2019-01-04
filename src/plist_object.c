// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'plist'
//	Generated 10/02/2017 11:48:01


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



#define			PLIST_OBJECT_C	    1
#include        <plist_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct plist_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct plist_class_data_s PLIST_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        plist_Info;            // Forward Reference



OBJ_ID          plist_Class(
    void
);



static
bool            plist_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PLIST_CLASS == classID) {
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
    return OBJ_IDENT_PLIST_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&plist_Info,
    plist_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    plist_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
PLIST_CLASS_DATA  plist_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(PLIST_CLASS_DATA),           // cbSize
        OBJ_IDENT_PLIST_CLASS,              // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            plist_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PLIST == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            plist_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          plist_Class(
    void
)
{
    return (OBJ_ID)&plist_ClassObj;
}


static
uint16_t		plist_WhoAmI(
    void
)
{
    return OBJ_IDENT_PLIST;
}


const
PLIST_VTBL     plist_Vtbl = {
    {
        &plist_Info,
        plist_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        plist_Dealloc,
        plist_Class,
        plist_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)plist_QueryInfo,
        (P_OBJ_TOSTRING)plist_ToDebugString,
        NULL,			// plist_Enable,
        NULL,			// plist_Disable,
        NULL,			// (P_OBJ_ASSIGN)plist_Assign,
        NULL,			// (P_OBJ_COMPARE)plist_Compare,
        NULL, 			// (P_OBJ_PTR)plist_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)plist_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //plist_IsEnabled,
 
};



static
const
OBJ_INFO        plist_Info = {
    "plist",
    "plist",
    (OBJ_DATA *)&plist_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&plist_Vtbl
};





