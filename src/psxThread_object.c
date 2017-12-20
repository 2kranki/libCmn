// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'psxThread'
//	Generated 02/11/2016 10:46:18

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
#include        "psxThread_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct psxThread_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct psxThread_class_data_s PSXTHREAD_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        psxThread_Info;            // Forward Reference



OBJ_ID          psxThread_Class(
    void
);



static
bool            psxThread_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PSXTHREAD_CLASS == classID) {
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
    return OBJ_IDENT_PSXTHREAD_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&psxThread_Info,
    psxThread_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    psxThread_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
PSXTHREAD_CLASS_DATA  psxThread_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_PSXTHREAD_CLASS, 0, 1},
	//0
};



static
bool            psxThread_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PSXTHREAD == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            psxThread_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          psxThread_Class(
    void
)
{
    return (OBJ_ID)&psxThread_ClassObj;
}


static
uint16_t		psxThread_WhoAmI(
    void
)
{
    return OBJ_IDENT_PSXTHREAD;
}


const
PSXTHREAD_VTBL  psxThread_Vtbl = {
    {
        &psxThread_Info,
        psxThread_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        psxThread_Dealloc,
        psxThread_Class,
        psxThread_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)psxThread_ToDebugString,
        NULL,			// psxThread_Enable,
        NULL,			// psxThread_Disable,
        NULL,			// (P_OBJ_ASSIGN)psxThread_Assign,
        NULL,			// (P_OBJ_COMPARE)psxThread_Compare,
        NULL, 			// (P_OBJ_PTR)psxThread_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)psxThread_Hash
    },
};



static
const
OBJ_INFO        psxThread_Info = {
    "psxThread",
    "Posix Thread",	
    (OBJ_DATA *)&psxThread_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





