// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'dbprs'
//	Generated 09/04/2018 13:50:27


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



//#define   DBPRS_IS_SINGLETON     1

#define			DBPRS_OBJECT_C	    1
#include        <dbprs_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct dbprs_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct dbprs_class_data_s DBPRS_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          dbprsClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        dbprs_Info;            // Forward Reference




static
bool            dbprsClass_IsKindOf(
    uint16_t		classID
)
{
    if (MAIN_IDENT_DBPRS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		dbprsClass_WhoAmI(
    void
)
{
    return MAIN_IDENT_DBPRS_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&dbprs_Info,
    dbprsClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    dbprs_Class,
    dbprsClass_WhoAmI,
    (P_OBJ_QUERYINFO)dbprsClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
DBPRS_CLASS_DATA  dbprs_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), MAIN_IDENT_DBPRS_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          dbprsClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    DBPRS_CLASS_DATA *this = objId;
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
                        return (void *)&dbprs_Info;
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
                        return dbprs_ParseObject;
                    }
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return dbprsClass_WhoAmI;
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
bool            dbprs_IsKindOf(
    uint16_t		classID
)
{
    if (MAIN_IDENT_DBPRS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            dbprs_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          dbprs_Class(
    void
)
{
    return (OBJ_ID)&dbprs_ClassObj;
}


static
uint16_t		dbprs_WhoAmI(
    void
)
{
    return MAIN_IDENT_DBPRS;
}


const
DBPRS_VTBL     dbprs_Vtbl = {
    {
        &dbprs_Info,
        dbprs_IsKindOf,
#ifdef  DBPRS_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        dbprs_Dealloc,
        dbprs_Class,
        dbprs_WhoAmI,
        (P_OBJ_QUERYINFO)dbprs_QueryInfo,
        (P_OBJ_TOSTRING)dbprs_ToDebugString,
        NULL,			// dbprs_Enable,
        NULL,			// dbprs_Disable,
        NULL,			// (P_OBJ_ASSIGN)dbprs_Assign,
        NULL,			// (P_OBJ_COMPARE)dbprs_Compare,
        NULL, 			// (P_OBJ_PTR)dbprs_Copy,
        NULL, 			// (P_OBJ_PTR)dbprs_DeepCopy,
        NULL 			// (P_OBJ_HASH)dbprs_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //dbprs_IsEnabled,
 
};



static
const
OBJ_INFO        dbprs_Info = {
    "dbprs",
    "genMake Database Parser",
    (OBJ_DATA *)&dbprs_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&dbprs_Vtbl
};




