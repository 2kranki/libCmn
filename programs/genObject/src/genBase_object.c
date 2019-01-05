// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'genBase'
//	Generated 04/10/2018 10:49:33


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



//#define   GENBASE_IS_SINGLETON     1

#define			GENBASE_OBJECT_C	    1
#include        <genBase_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct genBase_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct genBase_class_data_s GENBASE_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          genBaseClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        genBase_Info;            // Forward Reference




static
bool            genBaseClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_GENBASE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		genBaseClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_GENBASE_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&genBase_Info,
    genBaseClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    genBase_Class,
    genBaseClass_WhoAmI,
    (P_OBJ_QUERYINFO)genBaseClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
GENBASE_CLASS_DATA  genBase_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(GENBASE_CLASS_DATA),         // cbSize
        OBJ_IDENT_GENBASE_CLASS,            // cbIdent
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
void *          genBaseClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    GENBASE_CLASS_DATA *this = objId;
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
                        return (void *)&genBase_Info;
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
                        return genBaseClass_WhoAmI;
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
bool            genBase_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_GENBASE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            genBase_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          genBase_Class(
    void
)
{
    return (OBJ_ID)&genBase_ClassObj;
}


static
uint16_t		genBase_WhoAmI(
    void
)
{
    return OBJ_IDENT_GENBASE;
}


const
GENBASE_VTBL     genBase_Vtbl = {
    {
        &genBase_Info,
        genBase_IsKindOf,
#ifdef  GENMAKE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        genBase_Dealloc,
        genBase_Class,
        genBase_WhoAmI,
        (P_OBJ_QUERYINFO)genBase_QueryInfo,
        (P_OBJ_TOSTRING)genBase_ToDebugString,
        NULL,			// genBase_Enable,
        NULL,			// genBase_Disable,
        NULL,			// (P_OBJ_ASSIGN)genBase_Assign,
        NULL,			// (P_OBJ_COMPARE)genBase_Compare,
        NULL, 			// (P_OBJ_PTR)genBase_Copy,
        NULL, 			// (P_OBJ_PTR)genBase_DeepCopy,
        NULL 			// (P_OBJ_HASH)genBase_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    NULL,               // pGenCompileRoutine
    NULL,               // pGenCompileJson
    NULL,               // pGenCompileObject
    NULL,               // pGenCompileTest
    (void *)genBase_GenFinal,
    (void *)genBase_GenInitial
};



static
const
OBJ_INFO        genBase_Info = {
    "genBase",
    "Generate portions of a Makefile",
    (OBJ_DATA *)&genBase_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&genBase_Vtbl,
    sizeof(GENBASE_DATA)
};





