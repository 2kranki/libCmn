// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'number'
//	Generated 10/02/2017 12:04:00


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



#define			NUMBER_OBJECT_C	    1
#include        <number_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct number_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct number_class_data_s NUMBER_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        number_Info;            // Forward Reference




static
bool            number_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NUMBER_CLASS == classID) {
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
    return OBJ_IDENT_NUMBER_CLASS;
}


//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          obj_ClassQueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    const
    char            *pStr = pData;
    
    switch (type) {
            
        case OBJ_QUERYINFO_TYPE_INFO:
            return (void *)&number_Info;
            break;
            
        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {
                    
                case 'N':
                    if (str_Compare("New", (char *)pStr) == 0) {
                        return number_New;
                    }
                    break;
                    
                case 'T':
                    if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                        return number_ToDebugString;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return number_ToJSON;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    return NULL;
}



static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&number_Info,
    number_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    number_Class,
    obj_ClassWhoAmI,
    obj_ClassQueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
NUMBER_CLASS_DATA  number_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(NUMBER_CLASS_DATA),          // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            number_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NUMBER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            number_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          number_Class(
    void
)
{
    return (OBJ_ID)&number_ClassObj;
}


static
uint16_t		number_WhoAmI(
    void
)
{
    return OBJ_IDENT_NUMBER;
}


const
NUMBER_VTBL     number_Vtbl = {
    {
        &number_Info,
        number_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        number_Dealloc,
        number_Class,
        number_WhoAmI,
        (P_OBJ_QUERYINFO)number_QueryInfo,
        (P_OBJ_TOSTRING)number_ToDebugString,
        NULL,			// number_Enable,
        NULL,			// number_Disable,
        NULL,			// (P_OBJ_ASSIGN)number_Assign,
        NULL,			// (P_OBJ_COMPARE)number_Compare,
        NULL, 			// (P_OBJ_PTR)number_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)number_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //number_IsEnabled,
 
};



static
const
OBJ_INFO        number_Info = {
    "number",
    "Number",
    (OBJ_DATA *)&number_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&number_Vtbl,
    sizeof(NUMBER_DATA)
};





