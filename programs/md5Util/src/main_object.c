// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'main'
//	Generated 07/17/2017 14:59:49


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



#define			MAIN_OBJECT_C	    1
#include        <main_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct main_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct main_class_data_s MAIN_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        main_Info;            // Forward Reference



OBJ_ID          main_Class(
    void
);



static
bool            main_ClassIsKindOf(
    uint16_t		classID
)
{
    if (MAIN_IDENT_MAIN_CLASS == classID) {
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
    return MAIN_IDENT_MAIN_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&main_Info,
    main_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    main_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
MAIN_CLASS_DATA  main_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), MAIN_IDENT_MAIN_CLASS, 0, 1},
	//0
};



static
bool            main_IsKindOf(
    uint16_t		classID
)
{
    if (MAIN_IDENT_MAIN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            main_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          main_Class(
    void
)
{
    return (OBJ_ID)&main_ClassObj;
}


static
uint16_t		main_WhoAmI(
    void
)
{
    return MAIN_IDENT_MAIN;
}


const
MAIN_VTBL     main_Vtbl = {
    {
        &main_Info,
        main_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        main_Dealloc,
        main_Class,
        main_WhoAmI,
        (P_OBJ_QUERYINFO)main_QueryInfo,
        (P_OBJ_TOSTRING)main_ToDebugString,
        NULL,			// main_Enable,
        NULL,			// main_Disable,
        NULL,			// (P_OBJ_ASSIGN)main_Assign,
        NULL,			// (P_OBJ_COMPARE)main_Compare,
        NULL, 			// (P_OBJ_PTR)main_Copy,
        NULL 			// (P_OBJ_HASH)main_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //main_IsEnabled,
 
};



static
const
OBJ_INFO        main_Info = {
    "main",
    "Main Program Object",
    (OBJ_DATA *)&main_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&main_Vtbl
};





