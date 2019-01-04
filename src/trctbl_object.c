// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'trctbl'
//	Generated 09/30/2015 16:13:49

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
#include        "trctbl_internal.h"


//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct trctbl_class_data_s    {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct trctbl_class_data_s TRCTBL_CLASS_DATA;






OBJ_ID          trctbl_Class(
    void
);



static
bool            trctbl_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TRCTBL_CLASS == classID) {
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
    return OBJ_IDENT_TRCTBL_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
    NULL,
    trctbl_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    trctbl_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						trctbl Class Object
//-----------------------------------------------------------

static
const
TRCTBL_CLASS_DATA   trctbl_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(TRCTBL_CLASS_DATA),          // cbSize
        OBJ_IDENT_TRCTBL_CLASS,             // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
};



static
bool            trctbl_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TRCTBL == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            trctbl_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          trctbl_Class(
    void
)
{
    return (OBJ_ID)&trctbl_ClassObj;
}


static
uint16_t		trctbl_WhoAmI(
    void
)
{
    return OBJ_IDENT_TRCTBL;
}


const
OBJ_IUNKNOWN    trctbl_Vtbl = {
    NULL,
    trctbl_IsKindOf,
    obj_RetainStandard,
    obj_ReleaseStandard,
    trctbl_Dealloc,
    trctbl_Class,
    trctbl_WhoAmI,
    NULL,			// trctbl_Enable()
    NULL,			// trctbl_Disable(
    NULL, // (OBJ_ID (*)(OBJ_ID,int))trctbl_ToDebugString,
    NULL,			// trctbl_Assign()
    NULL,			// trctbl_Compare()
    NULL 			// trctbl_Copy()
};






