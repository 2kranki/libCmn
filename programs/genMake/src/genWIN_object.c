// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'genWIN'
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



//#define   GENWIN_IS_SINGLETON     1

#define			GENWIN_OBJECT_C	    1
#include        <genWIN_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct genWIN_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct genWIN_class_data_s GENWIN_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          genWINClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        genWIN_Info;            // Forward Reference




static
bool            genWINClass_IsKindOf(
    uint16_t		classID
)
{
    if (MAIN_IDENT_GENWIN_CLASS == classID) {
       return true;
    }
    if (MAIN_IDENT_GENBASE_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		genWINClass_WhoAmI(
    void
)
{
    return MAIN_IDENT_GENWIN_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&genWIN_Info,
    genWINClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    genWIN_Class,
    genWINClass_WhoAmI,
    (P_OBJ_QUERYINFO)genWINClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
GENWIN_CLASS_DATA  genWIN_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), MAIN_IDENT_GENWIN_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          genWINClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    GENWIN_CLASS_DATA *this = objId;
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
                    if (str_Compare("ClassObject", (char *)pStr) == 0) {
                        return (void *)&genWIN_ClassObj;
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
                    
                case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return genWINClass_WhoAmI;
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
bool            genWIN_IsKindOf(
    uint16_t		classID
)
{
    if (MAIN_IDENT_GENWIN == classID) {
       return true;
    }
    if (MAIN_IDENT_GENBASE == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            genWIN_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          genWIN_Class(
    void
)
{
    return (OBJ_ID)&genWIN_ClassObj;
}


static
uint16_t		genWIN_WhoAmI(
    void
)
{
    return MAIN_IDENT_GENWIN;
}


const
GENWIN_VTBL     genWIN_Vtbl = {
    {
        {
            &genWIN_Info,
            genWIN_IsKindOf,
    #ifdef  GENWIN_IS_SINGLETON
            obj_RetainNull,
            obj_ReleaseNull,
    #else
            obj_RetainStandard,
            obj_ReleaseStandard,
    #endif
            genWIN_Dealloc,
            genWIN_Class,
            genWIN_WhoAmI,
            (P_OBJ_QUERYINFO)genWIN_QueryInfo,
            (P_OBJ_TOSTRING)genWIN_ToDebugString,
            NULL,			// genWIN_Enable,
            NULL,			// genWIN_Disable,
            NULL,			// (P_OBJ_ASSIGN)genWIN_Assign,
            NULL,			// (P_OBJ_COMPARE)genWIN_Compare,
            NULL, 			// (P_OBJ_PTR)genWIN_Copy,
            NULL, 			// (P_OBJ_PTR)genWIN_DeepCopy,
            NULL 			// (P_OBJ_HASH)genWIN_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        (void *)genWIN_GenCompileRoutine,
        (void *)genWIN_GenCompileJson,
        (void *)genWIN_GenCompileObject,
        (void *)genWIN_GenCompileTest,
    }

};



static
const
OBJ_INFO        genWIN_Info = {
    "genWIN",
    "Generate Makefile for WIN32",
    (OBJ_DATA *)&genWIN_ClassObj,
    (OBJ_DATA *)&genBase_ClassObj,
    (OBJ_IUNKNOWN *)&genWIN_Vtbl
};





