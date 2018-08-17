// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'sgraph'
//	Generated 08/12/2018 14:34:38


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



//#define   SGRAPH_IS_SINGLETON     1

#define			SGRAPH_OBJECT_C	    1
#include        <sgraph_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct sgraph_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct sgraph_class_data_s SGRAPH_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          sgraphClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        sgraph_Info;            // Forward Reference




static
bool            sgraphClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SGRAPH_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		sgraphClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_SGRAPH_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&sgraph_Info,
    sgraphClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    sgraph_Class,
    sgraphClass_WhoAmI,
    (P_OBJ_QUERYINFO)sgraphClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
SGRAPH_CLASS_DATA  sgraph_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_SGRAPH_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          sgraphClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SGRAPH_CLASS_DATA *this = objId;
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
                        return (void *)&sgraph_Info;
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
                        return sgraph_ParseObject;
                    }
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return sgraphClass_WhoAmI;
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
bool            sgraph_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SGRAPH == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            sgraph_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          sgraph_Class(
    void
)
{
    return (OBJ_ID)&sgraph_ClassObj;
}


static
uint16_t		sgraph_WhoAmI(
    void
)
{
    return OBJ_IDENT_SGRAPH;
}


const
SGRAPH_VTBL     sgraph_Vtbl = {
    {
        &sgraph_Info,
        sgraph_IsKindOf,
#ifdef  SGRAPH_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        sgraph_Dealloc,
        sgraph_Class,
        sgraph_WhoAmI,
        (P_OBJ_QUERYINFO)sgraph_QueryInfo,
        (P_OBJ_TOSTRING)sgraph_ToDebugString,
        NULL,			// sgraph_Enable,
        NULL,			// sgraph_Disable,
        NULL,			// (P_OBJ_ASSIGN)sgraph_Assign,
        NULL,			// (P_OBJ_COMPARE)sgraph_Compare,
        NULL, 			// (P_OBJ_PTR)sgraph_Copy,
        NULL, 			// (P_OBJ_PTR)sgraph_DeepCopy,
        NULL 			// (P_OBJ_HASH)sgraph_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //sgraph_IsEnabled,
 
};



static
const
OBJ_INFO        sgraph_Info = {
    "sgraph",
    "Simple Graph",
    (OBJ_DATA *)&sgraph_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&sgraph_Vtbl
};





