// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'scanner'
//	Generated 07/26/2018 19:55:39


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



//#define   SCANNER_IS_SINGLETON     1

#define			SCANNER_OBJECT_C	    1
#include        <scanner_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct scanner_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct scanner_class_data_s SCANNER_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          scannerClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        scanner_Info;            // Forward Reference




static
bool            scannerClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SCANNER_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		scannerClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_SCANNER_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&scanner_Info,
    scannerClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    scanner_Class,
    scannerClass_WhoAmI,
    (P_OBJ_QUERYINFO)scannerClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
SCANNER_CLASS_DATA  scanner_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(SCANNER_CLASS_DATA),         // cbSize
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
void *          scannerClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SCANNER_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SCANNER_DATA);
            break;
            
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
                        return (void *)&scanner_Info;
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
                        return scanner_ParseObject;
                    }
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return scannerClass_WhoAmI;
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
bool            scanner_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_SCANNER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            scanner_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          scanner_Class(
    void
)
{
    return (OBJ_ID)&scanner_ClassObj;
}


static
uint16_t		scanner_WhoAmI(
    void
)
{
    return OBJ_IDENT_SCANNER;
}


const
SCANNER_VTBL     scanner_Vtbl = {
    {
        &scanner_Info,
        scanner_IsKindOf,
#ifdef  SCANNER_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        scanner_Dealloc,
        scanner_Class,
        scanner_WhoAmI,
        (P_OBJ_QUERYINFO)scanner_QueryInfo,
        (P_OBJ_TOSTRING)scanner_ToDebugString,
        NULL,			// scanner_Enable,
        NULL,			// scanner_Disable,
        NULL,			// (P_OBJ_ASSIGN)scanner_Assign,
        NULL,			// (P_OBJ_COMPARE)scanner_Compare,
        NULL, 			// (P_OBJ_PTR)scanner_Copy,
        NULL, 			// (P_OBJ_PTR)scanner_DeepCopy,
        NULL 			// (P_OBJ_HASH)scanner_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //scanner_IsEnabled,
 
};



static
const
OBJ_INFO        scanner_Info = {
    "scanner",
    "Command Line Scanner",
    (OBJ_DATA *)&scanner_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&scanner_Vtbl,
    sizeof(SCANNER_DATA)
};





