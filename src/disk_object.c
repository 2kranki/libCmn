// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'disk'
//	Generated 10/27/2018 13:52:20


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



//#define   DISK_IS_SINGLETON     1

#define			DISK_OBJECT_C	    1
#include        <disk_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct disk_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct disk_class_data_s DISK_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          diskClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        disk_Info;            // Forward Reference




static
bool            diskClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DISK_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		diskClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_DISK_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&disk_Info,
    diskClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    disk_Class,
    diskClass_WhoAmI,
    (P_OBJ_QUERYINFO)diskClass_QueryInfo,
    NULL                        // diskClass_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
DISK_CLASS_DATA  disk_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_DISK_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          diskClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    DISK_CLASS_DATA *this = objId;
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
                        return (void *)&disk_Info;
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
                        return disk_ParseObject;
                    }
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return diskClass_WhoAmI;
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
bool            disk_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DISK == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            disk_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          disk_Class(
    void
)
{
    return (OBJ_ID)&disk_ClassObj;
}


static
uint16_t		disk_WhoAmI(
    void
)
{
    return OBJ_IDENT_DISK;
}


const
DISK_VTBL     disk_Vtbl = {
    {
        &disk_Info,
        disk_IsKindOf,
#ifdef  DISK_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        disk_Dealloc,
        disk_Class,
        disk_WhoAmI,
        (P_OBJ_QUERYINFO)disk_QueryInfo,
        (P_OBJ_TOSTRING)disk_ToDebugString,
        NULL,			// disk_Enable,
        NULL,			// disk_Disable,
        NULL,			// (P_OBJ_ASSIGN)disk_Assign,
        NULL,			// (P_OBJ_COMPARE)disk_Compare,
        NULL, 			// (P_OBJ_PTR)disk_Copy,
        NULL, 			// (P_OBJ_PTR)disk_DeepCopy,
        NULL 			// (P_OBJ_HASH)disk_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //disk_IsEnabled,
 
};



static
const
OBJ_INFO        disk_Info = {
    "disk",
    "Information/Management of a Mounted Disk",
    (OBJ_DATA *)&disk_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&disk_Vtbl
};





