// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'ioRcd'
//	Generated 01/12/2017 00:06:08

/*
 * COPYRIGHT  - (C) Copyright 2016  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */


#define			IORCD_OBJECT_C	    1
#include        "ioRcd_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct ioRcd_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct ioRcd_class_data_s IORCD_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        ioRcd_Info;            // Forward Reference



OBJ_ID          ioRcd_Class(
    OBJ_ID          objId
);



static
bool            ioRcd_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_IORCD_CLASS == classID) {
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
    return OBJ_IDENT_IORCD_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&ioRcd_Info,
    ioRcd_ClassIsKindOf,
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
IORCD_CLASS_DATA  ioRcd_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_IORCD_CLASS, 0, 1},
	//0
};



static
bool            ioRcd_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_IORCD == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            ioRcd_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          ioRcd_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&ioRcd_ClassObj;
}


static
uint16_t		ioRcd_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_IORCD;
}


const
IORCD_VTBL     ioRcd_Vtbl = {
    {
        &ioRcd_Info,
        ioRcd_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        ioRcd_Dealloc,
        ioRcd_Class,
        ioRcd_WhoAmI,
        NULL,			// ioRcd_Enable,
        NULL,			// ioRcd_Disable,
        (P_OBJ_TOSTRING)ioRcd_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)ioRcd_Assign,
        NULL,			// (P_OBJ_COMPARE)ioRcd_Compare,
        NULL, 			// (P_OBJ_PTR)ioRcd_Copy,
        NULL 			// (P_OBJ_HASH)ioRcd_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ioRcd_IsEnabled,
 
};



static
const
OBJ_INFO        ioRcd_Info = {
    "ioRcd",
    "ioRcd",
    (OBJ_DATA *)&ioRcd_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&ioRcd_Vtbl
};





