// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'value'
//	Generated 08/26/2017 09:50:28


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



#define			VALUE_OBJECT_C	    1
#include        <value_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct value_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    OBJ_ID          pObjCatalog;
};
typedef struct value_class_data_s VALUE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          valueClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        value_Info;            // Forward Reference




static
bool            valueClass_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_VALUE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		valueClass_ClassWhoAmI(
    void
)
{
    return OBJ_IDENT_VALUE_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&value_Info,
    valueClass_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,               // Dealloc
    value_Class,
    valueClass_ClassWhoAmI,
    (P_OBJ_QUERYINFO)valueClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
VALUE_CLASS_DATA  value_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(VALUE_CLASS_DATA),           // cbSize
        OBJ_IDENT_VALUE_CLASS,              // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          valueClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    VALUE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
                    
                case 'O':
                    if (str_Compare("ObjectCatalog", (char *)pStr) == 0) {
                        return &this->pObjCatalog;
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
                    
                case 'T':
                    if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                        return value_ToDebugString;
                    }
#ifdef XYZZY
                    if (str_Compare("ToJSON", (char *)pStr) == 0) {
                        return value_ToJSON;
                    }
#endif
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



//===========================================================
//                  Object Vtbl Definition
//===========================================================

static
bool            value_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_VALUE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            value_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          value_Class(
    void
)
{
    return (OBJ_ID)&value_ClassObj;
}


static
uint16_t		value_WhoAmI(
    void
)
{
    return OBJ_IDENT_VALUE;
}


const
VALUE_VTBL     value_Vtbl = {
    {
        &value_Info,
        value_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        value_Dealloc,
        value_Class,
        value_WhoAmI,
        (P_OBJ_QUERYINFO)value_QueryInfo,
        (P_OBJ_TOSTRING)value_ToDebugString,
        NULL,			// value_Enable,
        NULL,			// value_Disable,
        NULL,			// (P_OBJ_ASSIGN)value_Assign,
        NULL,			// (P_OBJ_COMPARE)value_Compare,
        NULL, 			// (P_OBJ_PTR)value_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)value_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //value_IsEnabled,
 
};



static
const
OBJ_INFO        value_Info = {
    "value",
    "Primitive Value",
    (OBJ_DATA *)&value_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&value_Vtbl
};





