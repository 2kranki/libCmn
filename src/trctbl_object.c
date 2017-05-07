// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'trctbl'
//	Generated 09/30/2015 16:13:49

/*
 * COPYRIGHT  - (C) Copyright 2015  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */


#include        "obj.h"
#include        "trctbl_internal.h"





OBJ_ID          trctbl_Class(
    OBJ_ID          objId
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
    OBJ_ID          objId
)
{
    return OBJ_IDENT_TRCTBL_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
    NULL,
    trctbl_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						trctbl Class Object
//-----------------------------------------------------------

static
const
OBJ_DATA        trctbl_ClassObj = {
    &obj_Vtbl,
    sizeof(OBJ_DATA),
    OBJ_IDENT_TRCTBL_CLASS,
    0,
    1
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
    OBJ_ID          objId
)
{
    return (OBJ_ID)&trctbl_ClassObj;
}


static
uint16_t		trctbl_WhoAmI(
    OBJ_ID          objId
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






