// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'u32Matrix'
//	Generated 08/12/2018 23:54:40


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



//#define   U32MATRIX_IS_SINGLETON     1

#define			U32MATRIX_OBJECT_C	    1
#include        <u32Matrix_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct u32Matrix_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct u32Matrix_class_data_s U32MATRIX_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          u32MatrixClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        u32Matrix_Info;            // Forward Reference




static
bool            u32MatrixClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U32MATRIX_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		u32MatrixClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_U32MATRIX_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&u32Matrix_Info,
    u32MatrixClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    u32Matrix_Class,
    u32MatrixClass_WhoAmI,
    (P_OBJ_QUERYINFO)u32MatrixClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
U32MATRIX_CLASS_DATA  u32Matrix_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_U32MATRIX_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          u32MatrixClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    U32MATRIX_CLASS_DATA *this = objId;
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
                        return (void *)&u32Matrix_Info;
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
                        return u32Matrix_ParseObject;
                    }
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return u32MatrixClass_WhoAmI;
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
bool            u32Matrix_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_U32MATRIX == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            u32Matrix_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          u32Matrix_Class(
    void
)
{
    return (OBJ_ID)&u32Matrix_ClassObj;
}


static
uint16_t		u32Matrix_WhoAmI(
    void
)
{
    return OBJ_IDENT_U32MATRIX;
}


const
U32MATRIX_VTBL     u32Matrix_Vtbl = {
    {
        &u32Matrix_Info,
        u32Matrix_IsKindOf,
#ifdef  U32MATRIX_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        u32Matrix_Dealloc,
        u32Matrix_Class,
        u32Matrix_WhoAmI,
        (P_OBJ_QUERYINFO)u32Matrix_QueryInfo,
        (P_OBJ_TOSTRING)u32Matrix_ToDebugString,
        NULL,			// u32Matrix_Enable,
        NULL,			// u32Matrix_Disable,
        NULL,			// (P_OBJ_ASSIGN)u32Matrix_Assign,
        NULL,			// (P_OBJ_COMPARE)u32Matrix_Compare,
        NULL, 			// (P_OBJ_PTR)u32Matrix_Copy,
        NULL, 			// (P_OBJ_PTR)u32Matrix_DeepCopy,
        NULL 			// (P_OBJ_HASH)u32Matrix_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //u32Matrix_IsEnabled,
 
};



static
const
OBJ_INFO        u32Matrix_Info = {
    "u32Matrix",
    "Matrix of uint32_t",
    (OBJ_DATA *)&u32Matrix_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&u32Matrix_Vtbl
};





