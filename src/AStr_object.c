// vi:nu:et:sts=4 ts=4 sw=4

//	Class Object Metods and Tables for 'AStr'
//	Generated 01/29/2016 22:02:37

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


#include        "AStr_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct AStr_class_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct AStr_class_data_s ASTR_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          AStrClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        AStr_Info;            // Forward Reference




static
bool            AStr_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTR_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_ARRAY_CLASS == classID) {
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
    return OBJ_IDENT_ASTR_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&AStr_Info,
    AStr_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    AStr_Class,
    obj_ClassWhoAmI,
    (P_OBJ_QUERYINFO)AStrClass_QueryInfo,
    NULL                        // aStrClass_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
ASTR_CLASS_DATA  AStr_ClassObj = {
    {
        &obj_Vtbl,                  // pVtbl
        sizeof(ASTR_CLASS_DATA),    // cbSize
        0,                          // cbFlags
        1,                          // cbRetainCount
        {0}                         // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          AStrClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    ASTR_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
            
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(ASTR_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
            // Query for an address to specific data within the object.
            // This should be used very sparingly since it breaks the
            // object's encapsulation.
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
                    
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&AStr_Info;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case OBJ_QUERYINFO_TYPE_INFO:
            return (void *)obj_getInfo(this);
            break;
            
        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {
                    
                case 'N':
                    if (str_Compare("New", (char *)pStr) == 0) {
                        return AStr_New;
                    }
                    break;
                    
#ifdef  ASTR_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return AStr_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return AStr_ParseJsonObject;
                        }
                        break;
#endif
                case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return obj_ClassWhoAmI;
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
bool            AStr_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTR == classID) {
       return true;
    }
    if (OBJ_IDENT_ARRAY == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            AStr_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          AStr_Class(
    void
)
{
    return (OBJ_ID)&AStr_ClassObj;
}


static
uint16_t		AStr_WhoAmI(
    void
)
{
    return OBJ_IDENT_ASTR;
}


const
ASTR_VTBL       AStr_Vtbl = {
    {
        &AStr_Info,
        AStr_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        AStr_Dealloc,
        AStr_Class,
        AStr_WhoAmI,
        (P_OBJ_QUERYINFO)AStr_QueryInfo,
        (P_OBJ_TOSTRING)AStr_ToDebugString,
        NULL,            // AStr_Enable,
        NULL,            // AStr_Disable,
        (P_OBJ_ASSIGN)AStr_Assign,
        (P_OBJ_COMPARE)AStr_Compare,
        (P_OBJ_COPY)AStr_Copy,
        (P_OBJ_DEEPCOPY)AStr_DeepCopy,
        (P_OBJ_HASH)AStr_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    AStr_getData,
    AStr_getLength
};




static
const
OBJ_INFO        AStr_Info = {
    "AStr",
    "Ascii String (UTF-8)",
    (OBJ_DATA *)&AStr_ClassObj,
    (OBJ_DATA *)&array_ClassObj,
    (OBJ_IUNKNOWN *)&AStr_Vtbl,
    sizeof(ASTR_DATA)
};





