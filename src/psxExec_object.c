// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'psxExec'
//	Generated 06/14/2018 08:13:54


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



//#define   PSXEXEC_IS_SINGLETON     1

#define			PSXEXEC_OBJECT_C	    1
#include        <psxExec_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct psxExec_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct psxExec_class_data_s PSXEXEC_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          psxExecClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        psxExec_Info;            // Forward Reference




static
bool            psxExecClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PSXEXEC_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		psxExecClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_PSXEXEC_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&psxExec_Info,
    psxExecClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    psxExec_Class,
    psxExecClass_WhoAmI,
    (P_OBJ_QUERYINFO)psxExecClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
PSXEXEC_CLASS_DATA  psxExec_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(PSXEXEC_CLASS_DATA),         // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          psxExecClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PSXEXEC_CLASS_DATA *this = objId;
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
                        return (void *)&psxExec_ClassObj;
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
                        return psxExecClass_WhoAmI;
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
bool            psxExec_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_PSXEXEC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            psxExec_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          psxExec_Class(
    void
)
{
    return (OBJ_ID)&psxExec_ClassObj;
}


static
uint16_t		psxExec_WhoAmI(
    void
)
{
    return OBJ_IDENT_PSXEXEC;
}


const
PSXEXEC_VTBL     psxExec_Vtbl = {
    {
        &psxExec_Info,
        psxExec_IsKindOf,
#ifdef  PSXEXEC_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        psxExec_Dealloc,
        psxExec_Class,
        psxExec_WhoAmI,
        (P_OBJ_QUERYINFO)psxExec_QueryInfo,
        (P_OBJ_TOSTRING)psxExec_ToDebugString,
        NULL,			// psxExec_Enable,
        NULL,			// psxExec_Disable,
        NULL,			// (P_OBJ_ASSIGN)psxExec_Assign,
        NULL,			// (P_OBJ_COMPARE)psxExec_Compare,
        NULL, 			// (P_OBJ_PTR)psxExec_Copy,
        NULL, 			// (P_OBJ_PTR)psxExec_DeepCopy,
        NULL 			// (P_OBJ_HASH)psxExec_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //psxExec_IsEnabled,
 
};



static
const
OBJ_INFO        psxExec_Info = {
    "psxExec",
    "Posix Task Execution",
    (OBJ_DATA *)&psxExec_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&psxExec_Vtbl
};





