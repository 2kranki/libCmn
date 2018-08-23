// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'cloprs'
//	Generated 08/22/2018 12:43:41


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



//#define   CLOPRS_IS_SINGLETON     1

#define			CLOPRS_OBJECT_C	    1
#include        <cloprs_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct cloprs_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct cloprs_class_data_s CLOPRS_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          cloprsClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        cloprs_Info;            // Forward Reference




static
bool            cloprsClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CLOPRS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		cloprsClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_CLOPRS_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&cloprs_Info,
    cloprsClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    cloprs_Class,
    cloprsClass_WhoAmI,
    (P_OBJ_QUERYINFO)cloprsClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
CLOPRS_CLASS_DATA  cloprs_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_CLOPRS_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          cloprsClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    CLOPRS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
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
                        return (void *)&cloprs_Info;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case OBJ_QUERYINFO_TYPE_INFO:
            return (void *)obj_getInfo(this);
            break;
            
#ifdef XYZZY
        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {
                    
                case 'P':
                    if (str_Compare("ParseObject", (char *)pStr) == 0) {
                        return cloprs_ParseObject;
                    }
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return cloprsClass_WhoAmI;
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
bool            cloprs_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_CLOPRS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            cloprs_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          cloprs_Class(
    void
)
{
    return (OBJ_ID)&cloprs_ClassObj;
}


static
uint16_t		cloprs_WhoAmI(
    void
)
{
    return OBJ_IDENT_CLOPRS;
}


const
CLOPRS_VTBL     cloprs_Vtbl = {
    {
        &cloprs_Info,
        cloprs_IsKindOf,
#ifdef  CLOPRS_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        cloprs_Dealloc,
        cloprs_Class,
        cloprs_WhoAmI,
        (P_OBJ_QUERYINFO)cloprs_QueryInfo,
        (P_OBJ_TOSTRING)cloprs_ToDebugString,
        NULL,			// cloprs_Enable,
        NULL,			// cloprs_Disable,
        NULL,			// (P_OBJ_ASSIGN)cloprs_Assign,
        NULL,			// (P_OBJ_COMPARE)cloprs_Compare,
        NULL, 			// (P_OBJ_PTR)cloprs_Copy,
        NULL, 			// (P_OBJ_PTR)cloprs_DeepCopy,
        NULL 			// (P_OBJ_HASH)cloprs_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //cloprs_IsEnabled,
 
};



static
const
OBJ_INFO        cloprs_Info = {
    "cloprs",
    "Command Line Option Parser",
    (OBJ_DATA *)&cloprs_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&cloprs_Vtbl
};





