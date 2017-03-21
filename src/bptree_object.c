// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'bptree'
//	Generated 03/05/2017 10:40:41


/*
 * COPYRIGHT  - (C) Copyright 2016  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */


#define			BPTREE_OBJECT_C	    1
#include        "bptree_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct bptree_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct bptree_class_data_s BPTREE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        bptree_Info;            // Forward Reference



OBJ_ID          bptree_Class(
    OBJ_ID          objId
);



static
bool            bptree_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPTREE_CLASS == classID) {
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
    return OBJ_IDENT_BPTREE_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&bptree_Info,
    bptree_ClassIsKindOf,
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
BPTREE_CLASS_DATA  bptree_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_BPTREE_CLASS, 0, 1},
	//0
};



static
bool            bptree_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPTREE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            bptree_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          bptree_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&bptree_ClassObj;
}


static
uint16_t		bptree_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_BPTREE;
}


const
BPTREE_VTBL     bptree_Vtbl = {
    {
        &bptree_Info,
        bptree_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        bptree_Dealloc,
        bptree_Class,
        bptree_WhoAmI,
        NULL,			// bptree_Enable,
        NULL,			// bptree_Disable,
        (P_OBJ_TOSTRING)bptree_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)bptree_Assign,
        NULL,			// (P_OBJ_COMPARE)bptree_Compare,
        NULL, 			// (P_OBJ_PTR)bptree_Copy,
        NULL 			// (P_OBJ_HASH)bptree_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //bptree_IsEnabled,
 
};



static
const
OBJ_INFO        bptree_Info = {
    "bptree",
    "B+ Tree (bptree)",
    (OBJ_DATA *)&bptree_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&bptree_Vtbl
};





