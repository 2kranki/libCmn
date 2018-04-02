// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'szData'
//	Generated 02/07/2018 09:15:58


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



//#define   SZDATA_IS_SINGLETON     1

#define			SZDATA_OBJECT_C	    1
#include        <szData_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct szData_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct szData_class_data_s SZDATA_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          szDataClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        szData_Info;            // Forward Reference




static
bool            szDataClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SZDATA_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		szDataClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_SZDATA_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&szData_Info,
    szDataClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    szData_Class,
    szDataClass_WhoAmI,
    (P_OBJ_QUERYINFO)szDataClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
SZDATA_CLASS_DATA  szData_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_SZDATA_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          szDataClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SZDATA_CLASS_DATA *this = objId;
#ifdef XYZZY
    const
    char            *pStr = pData;
#endif
    
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
                        return szDataClass_WhoAmI;
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
bool            szData_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SZDATA == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            szData_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          szData_Class(
    void
)
{
    return (OBJ_ID)&szData_ClassObj;
}


static
uint16_t		szData_WhoAmI(
    void
)
{
    return OBJ_IDENT_SZDATA;
}


const
SZDATA_VTBL     szData_Vtbl = {
    {
        &szData_Info,
        szData_IsKindOf,
#ifdef  SZDATA_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        szData_Dealloc,
        szData_Class,
        szData_WhoAmI,
        (P_OBJ_QUERYINFO)szData_QueryInfo,
        (P_OBJ_TOSTRING)szData_ToDebugString,
        NULL,			// szData_Enable,
        NULL,			// szData_Disable,
        (P_OBJ_ASSIGN)szData_Assign,
        (P_OBJ_COMPARE)szData_Compare,
        (P_OBJ_PTR)szData_Copy,
        NULL,           // (P_OBJ_PTR)szData_DeepCopy,
        (P_OBJ_HASH)szData_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //szData_IsEnabled,
 
};



static
const
OBJ_INFO        szData_Info = {
    "szData",
    "Static String W/ Data",
    (OBJ_DATA *)&szData_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&szData_Vtbl
};





