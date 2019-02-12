// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'tokenList'
//	Generated 01/30/2016 08:13:28

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
#include        "tokenList_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct tokenList_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct tokenList_class_data_s TOKENLIST_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        tokenList_Info;            // Forward Reference



OBJ_ID          tokenList_Class(
    void
);



static
bool            tokenList_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TOKENLIST_CLASS == classID) {
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
    return OBJ_IDENT_TOKENLIST_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&tokenList_Info,
    tokenList_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    tokenList_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
TOKENLIST_CLASS_DATA  tokenList_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(TOKENLIST_CLASS_DATA),       // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            tokenList_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TOKENLIST == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            tokenList_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          tokenList_Class(
    void
)
{
    return (OBJ_ID)&tokenList_ClassObj;
}


static
uint16_t		tokenList_WhoAmI(
    void
)
{
    return OBJ_IDENT_TOKENLIST;
}


const
TOKENLIST_VTBL  tokenList_Vtbl = {
    {
        &tokenList_Info,
        tokenList_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        tokenList_Dealloc,
        tokenList_Class,
        tokenList_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)tokenList_ToDebugString,
        NULL,            // tokenList_Enable,
        NULL,            // tokenList_Disable,
        NULL,            // (P_OBJ_ASSIGN)tokenList_Assign,
        NULL,            // (P_OBJ_COMPARE)tokenList_Compare,
        NULL,             // (P_OBJ_PTR)tokenList_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL             // (P_OBJ_HASH)tokenList_Hash
    }
};



static
const
OBJ_INFO        tokenList_Info = {
    "tokenList",
    "A List of Tokens",
    (OBJ_DATA *)&tokenList_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





