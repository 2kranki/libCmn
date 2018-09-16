// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'genOSX'
//	Generated 04/18/2018 09:07:03


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



//#define   GENOSX_IS_SINGLETON     1

#define			GENOSX_OBJECT_C	    1
#include        <genOSX_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct genOSX_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct genOSX_class_data_s GENOSX_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          genOSXClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        genOSX_Info;            // Forward Reference




static
bool            genOSXClass_IsKindOf(
    uint16_t		classID
)
{
    if (MAIN_IDENT_GENOSX_CLASS == classID) {
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
uint16_t		genOSXClass_WhoAmI(
    void
)
{
    return MAIN_IDENT_GENOSX_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&genOSX_Info,
    genOSXClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    genOSX_Class,
    genOSXClass_WhoAmI,
    (P_OBJ_QUERYINFO)genOSXClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
GENOSX_CLASS_DATA  genOSX_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), MAIN_IDENT_GENOSX_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          genOSXClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    GENOSX_CLASS_DATA *this = objId;
    //const
    //char            *pStr = pData;
    
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
                        return genOSXClass_WhoAmI;
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
bool            genOSX_IsKindOf(
    uint16_t		classID
)
{
    if (MAIN_IDENT_GENOSX == classID) {
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
void            genOSX_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          genOSX_Class(
    void
)
{
    return (OBJ_ID)&genOSX_ClassObj;
}


static
uint16_t		genOSX_WhoAmI(
    void
)
{
    return MAIN_IDENT_GENOSX;
}


const
GENOSX_VTBL     genOSX_Vtbl = {
    {
        {
            &genOSX_Info,
            genOSX_IsKindOf,
    #ifdef  GENOSX_IS_SINGLETON
            obj_RetainNull,
            obj_ReleaseNull,
    #else
            obj_RetainStandard,
            obj_ReleaseStandard,
    #endif
            genOSX_Dealloc,
            genOSX_Class,
            genOSX_WhoAmI,
            (P_OBJ_QUERYINFO)genOSX_QueryInfo,
            (P_OBJ_TOSTRING)genOSX_ToDebugString,
            NULL,			// genOSX_Enable,
            NULL,			// genOSX_Disable,
            NULL,			// (P_OBJ_ASSIGN)genOSX_Assign,
            NULL,			// (P_OBJ_COMPARE)genOSX_Compare,
            NULL, 			// (P_OBJ_PTR)genOSX_Copy,
            NULL, 			// (P_OBJ_PTR)genOSX_DeepCopy,
            NULL 			// (P_OBJ_HASH)genOSX_Hash,
        },
        (void *)genOSX_GenCompileRoutine,
        (void *)genOSX_GenCompileJson,
        (void *)genOSX_GenCompileObject,
        (void *)genOSX_GenCompileTest,
        (void *)genBase_GenFinal,
        (void *)genOSX_GenInitial,
        (void *)genBase_GenLibrary,
        (void *)genBase_GenObjects,
        (void *)genBase_GenOSSpecific,
        NULL,
        (void *)genBase_GenRoutines,
        (void *)genBase_GenTests,
    }
    // Put other object method names below this.
    // Properties:
    // Methods:

};



static
const
OBJ_INFO        genOSX_Info = {
    "genOSX",
    "Generate Makefile for OSX",
    (OBJ_DATA *)&genOSX_ClassObj,
    (OBJ_DATA *)&genBase_ClassObj,
    (OBJ_IUNKNOWN *)&genOSX_Vtbl
};





