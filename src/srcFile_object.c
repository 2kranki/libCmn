// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'srcFile'
//	Generated 01/27/2016 09:05:00

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
#include        "srcFile_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct srcFile_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct srcFile_class_data_s SRCFILE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        srcFile_Info;            // Forward Reference



OBJ_ID          srcFile_Class(
    void
);



static
bool            srcFile_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCFILE_CLASS == classID) {
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
    return OBJ_IDENT_SRCFILE_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&srcFile_Info,
    srcFile_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
SRCFILE_CLASS_DATA  srcFile_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_SRCFILE_CLASS, 0, 1},
	//0
};



static
bool            srcFile_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCFILE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            srcFile_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          srcFile_Class(
    void
)
{
    return (OBJ_ID)&srcFile_ClassObj;
}


static
uint16_t		srcFile_WhoAmI(
    void
)
{
    return OBJ_IDENT_SRCFILE;
}


const
SRCFILE_VTBL    srcFile_Vtbl = {
    {
        &srcFile_Info,
        srcFile_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        srcFile_Dealloc,
        srcFile_Class,
        srcFile_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)srcFile_ToDebugString,
        NULL,			// srcFile_Enable,
        NULL,			// srcFile_Disable,
        NULL,			// (P_OBJ_ASSIGN)srcFile_Assign,
        NULL,			// (P_OBJ_COMPARE)srcFile_Compare,
        NULL, 			// (P_OBJ_PTR)srcFile_Copy,
        NULL 			// (P_OBJ_HASH)srcFile_Hash
    },
};



static
const
OBJ_INFO        srcFile_Info = {
    "srcFile",
    "Read a Source File",
    (OBJ_DATA *)&srcFile_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





