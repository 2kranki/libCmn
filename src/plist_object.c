// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'plist'
//	Generated 10/18/2015 10:02:08

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
#include        "plist_internal.h"





OBJ_ID          plist_Class(
    OBJ_ID          objId
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
    OBJ_ID          objId
)
{
    return OBJ_IDENT_PLIST_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
    NULL,
    plist_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						plist Class Object
//-----------------------------------------------------------

static
const
OBJ_DATA        plist_ClassObj = {
    &obj_Vtbl,
    sizeof(OBJ_DATA),
    OBJ_IDENT_PLIST_CLASS,
    0,
    1
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
    OBJ_ID          objId
)
{
    return (OBJ_ID)&plist_ClassObj;
}


static
uint16_t		plist_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_PLIST;
}


const
OBJ_IUNKNOWN    plist_Vtbl = {
    NULL,
    plist_IsKindOf,
    obj_RetainStandard,
    obj_ReleaseStandard,
    plist_Dealloc,
    plist_Class,
    plist_WhoAmI,
    NULL,			// plist_Enable()
    NULL,			// plist_Disable(
    (OBJ_ID (*)(OBJ_ID,int))plist_ToDebugString,
    NULL,			// plist_Assign()
    NULL,			// plist_Compare()
    NULL 			// plist_Copy()
};






