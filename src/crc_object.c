// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'crc'
//	Generated 07/25/2017 10:42:33


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



#define			CRC_OBJECT_C	    1
#include        <crc_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct crc_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct crc_class_data_s CRC_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        crc_Info;            // Forward Reference



OBJ_ID          crc_Class(
    void
);



static
bool            crc_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CRC_CLASS == classID) {
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
    return OBJ_IDENT_CRC_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&crc_Info,
    crc_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
CRC_CLASS_DATA  crc_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_CRC_CLASS, 0, 1},
	//0
};



static
bool            crc_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CRC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            crc_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          crc_Class(
    void
)
{
    return (OBJ_ID)&crc_ClassObj;
}


static
uint16_t		crc_WhoAmI(
    void
)
{
    return OBJ_IDENT_CRC;
}


const
CRC_VTBL     crc_Vtbl = {
    {
        &crc_Info,
        crc_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        crc_Dealloc,
        crc_Class,
        crc_WhoAmI,
        (P_OBJ_QUERYINFO)crc_QueryInfo,
        (P_OBJ_TOSTRING)crc_ToDebugString,
        NULL,			// crc_Enable,
        NULL,			// crc_Disable,
        NULL,			// (P_OBJ_ASSIGN)crc_Assign,
        NULL,			// (P_OBJ_COMPARE)crc_Compare,
        NULL, 			// (P_OBJ_PTR)crc_Copy,
        NULL 			// (P_OBJ_HASH)crc_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //crc_IsEnabled,
 
};



static
const
OBJ_INFO        crc_Info = {
    "crc",
    "Cyclic Redundancy Checksum",
    (OBJ_DATA *)&crc_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&crc_Vtbl
};





