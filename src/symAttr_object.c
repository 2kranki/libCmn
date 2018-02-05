// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'symAttr'
//	Generated 02/02/2018 10:14:55


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



//#define   SYMATTR_IS_SINGLETON     1

#define			SYMATTR_OBJECT_C	    1
#include        <symAttr_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct symAttr_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct symAttr_class_data_s SYMATTR_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          symAttrClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        symAttr_Info;            // Forward Reference




static
bool            symAttrClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SYMATTR_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		symAttrClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_SYMATTR_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&symAttr_Info,
    symAttrClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    symAttr_Class,
    symAttrClass_WhoAmI,
    (P_OBJ_QUERYINFO)symAttrClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
SYMATTR_CLASS_DATA  symAttr_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_SYMATTR_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          symAttrClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SYMATTR_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
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
#endif
            
        case OBJ_QUERYINFO_TYPE_INFO:
            return (void *)obj_getInfo(this);
            break;
            
#ifdef XYZZY
        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {
                    
                case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return symAttrClass_WhoAmI;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
            
        default:
            break;
    }
    
    return NULL;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

static
bool            symAttr_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SYMATTR == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            symAttr_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          symAttr_Class(
    void
)
{
    return (OBJ_ID)&symAttr_ClassObj;
}


static
uint16_t		symAttr_WhoAmI(
    void
)
{
    return OBJ_IDENT_SYMATTR;
}


const
SYMATTR_VTBL     symAttr_Vtbl = {
    {
        &symAttr_Info,
        symAttr_IsKindOf,
#ifdef  SYMATTR_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        symAttr_Dealloc,
        symAttr_Class,
        symAttr_WhoAmI,
        (P_OBJ_QUERYINFO)symAttr_QueryInfo,
        (P_OBJ_TOSTRING)symAttr_ToDebugString,
        NULL,			// symAttr_Enable,
        NULL,			// symAttr_Disable,
        NULL,			// (P_OBJ_ASSIGN)symAttr_Assign,
        NULL,			// (P_OBJ_COMPARE)symAttr_Compare,
        NULL, 			// (P_OBJ_PTR)symAttr_Copy,
        NULL 			// (P_OBJ_HASH)symAttr_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //symAttr_IsEnabled,
 
};



static
const
OBJ_INFO        symAttr_Info = {
    "symAttr",
    "Symbol Entry Attributes",
    (OBJ_DATA *)&symAttr_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&symAttr_Vtbl
};





