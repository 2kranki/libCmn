// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'genWIN32'
//	Generated 04/18/2018 09:07:15


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



//#define   GENWIN32_IS_SINGLETON     1

#define			GENWIN32_OBJECT_C	    1
#include        <genWIN32_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct genWIN32_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct genWIN32_class_data_s GENWIN32_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          genWIN32Class_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        genWIN32_Info;            // Forward Reference




static
bool            genWIN32Class_IsKindOf(
    uint16_t		classID
)
{
    if (MAIN_IDENT_GENWIN32_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		genWIN32Class_WhoAmI(
    void
)
{
    return MAIN_IDENT_GENWIN32_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&genWIN32_Info,
    genWIN32Class_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    genWIN32_Class,
    genWIN32Class_WhoAmI,
    (P_OBJ_QUERYINFO)genWIN32Class_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
GENWIN32_CLASS_DATA  genWIN32_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), MAIN_IDENT_GENWIN32_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          genWIN32Class_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    GENWIN32_CLASS_DATA *this = objId;
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
                        return genWIN32Class_WhoAmI;
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
bool            genWIN32_IsKindOf(
    uint16_t		classID
)
{
    if (MAIN_IDENT_GENWIN32 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            genWIN32_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          genWIN32_Class(
    void
)
{
    return (OBJ_ID)&genWIN32_ClassObj;
}


static
uint16_t		genWIN32_WhoAmI(
    void
)
{
    return MAIN_IDENT_GENWIN32;
}


const
GENWIN32_VTBL     genWIN32_Vtbl = {
    {
        &genWIN32_Info,
        genWIN32_IsKindOf,
#ifdef  GENWIN32_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        genWIN32_Dealloc,
        genWIN32_Class,
        genWIN32_WhoAmI,
        (P_OBJ_QUERYINFO)genWIN32_QueryInfo,
        (P_OBJ_TOSTRING)genWIN32_ToDebugString,
        NULL,			// genWIN32_Enable,
        NULL,			// genWIN32_Disable,
        NULL,			// (P_OBJ_ASSIGN)genWIN32_Assign,
        NULL,			// (P_OBJ_COMPARE)genWIN32_Compare,
        NULL, 			// (P_OBJ_PTR)genWIN32_Copy,
        NULL, 			// (P_OBJ_PTR)genWIN32_DeepCopy,
        NULL 			// (P_OBJ_HASH)genWIN32_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //genWIN32_IsEnabled,
 
};



static
const
OBJ_INFO        genWIN32_Info = {
    "genWIN32",
    "Generate Makefile for WIN32",
    (OBJ_DATA *)&genWIN32_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&genWIN32_Vtbl
};





