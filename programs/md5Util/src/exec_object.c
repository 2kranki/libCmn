// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'exec'
//	Generated 04/10/2018 09:21:38


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



//#define   EXEC_IS_SINGLETON     1

#define			EXEC_OBJECT_C	    1
#include        <exec_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct exec_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct exec_class_data_s EXEC_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          execClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        exec_Info;            // Forward Reference




static
bool            execClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_EXEC_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		execClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_EXEC_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&exec_Info,
    execClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    exec_Class,
    execClass_WhoAmI,
    (P_OBJ_QUERYINFO)execClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
EXEC_CLASS_DATA  exec_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(EXEC_CLASS_DATA),            // cbSize
        OBJ_IDENT_EXEC_CLASS,               // cbIdent
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
void *          execClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    EXEC_CLASS_DATA *this = objId;
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
                        return execClass_WhoAmI;
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
bool            exec_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_EXEC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            exec_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          exec_Class(
    void
)
{
    return (OBJ_ID)&exec_ClassObj;
}


static
uint16_t		exec_WhoAmI(
    void
)
{
    return OBJ_IDENT_EXEC;
}


const
EXEC_VTBL     exec_Vtbl = {
    {
        &exec_Info,
        exec_IsKindOf,
#ifdef  EXEC_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        exec_Dealloc,
        exec_Class,
        exec_WhoAmI,
        (P_OBJ_QUERYINFO)exec_QueryInfo,
        (P_OBJ_TOSTRING)exec_ToDebugString,
        NULL,			// exec_Enable,
        NULL,			// exec_Disable,
        NULL,			// (P_OBJ_ASSIGN)exec_Assign,
        NULL,			// (P_OBJ_COMPARE)exec_Compare,
        NULL, 			// (P_OBJ_PTR)exec_Copy,
        NULL, 			// (P_OBJ_PTR)exec_DeepCopy,
        NULL 			// (P_OBJ_HASH)exec_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //exec_IsEnabled,
 
};



static
const
OBJ_INFO        exec_Info = {
    "exec",
    "MD5 Utility Execution",
    (OBJ_DATA *)&exec_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&exec_Vtbl
};





