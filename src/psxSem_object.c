// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'psxSem'
//	Generated 02/11/2016 10:46:36

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
#include        "psxSem_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct psxSem_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    uint32_t        unique;
};
typedef struct psxSem_class_data_s PSXSEM_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        psxSem_Info;            // Forward Reference



OBJ_ID          psxSem_Class(
    void
);



static
bool            psxSem_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PSXSEM_CLASS == classID) {
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
    return OBJ_IDENT_PSXSEM_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&psxSem_Info,
    psxSem_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    psxSem_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
PSXSEM_CLASS_DATA  psxSem_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(PSXSEM_CLASS_DATA),          // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            psxSem_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PSXSEM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            psxSem_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          psxSem_Class(
    void
)
{
    return (OBJ_ID)&psxSem_ClassObj;
}


static
uint16_t		psxSem_WhoAmI(
    void
)
{
    return OBJ_IDENT_PSXSEM;
}


const
PSXSEM_VTBL     psxSem_Vtbl = {
    {
        &psxSem_Info,
        psxSem_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        psxSem_Dealloc,
        psxSem_Class,
        psxSem_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)psxSem_ToDebugString,
        NULL,			// psxSem_Enable,
        NULL,			// psxSem_Disable,
        NULL,			// (P_OBJ_ASSIGN)psxSem_Assign,
        NULL,			// (P_OBJ_COMPARE)psxSem_Compare,
        NULL, 			// (P_OBJ_PTR)psxSem_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)psxSem_Hash
    },
};



static
const
OBJ_INFO        psxSem_Info = {
    "psxSem",
    "Posix Semaphore",
    (OBJ_DATA *)&psxSem_ClassObj,
    (OBJ_DATA *)&obj_ClassObj
};





