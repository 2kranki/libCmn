// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'disks'
//	Generated 10/27/2018 13:52:11


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



//#define   DISKS_IS_SINGLETON     1

#define			DISKS_OBJECT_C	    1
#include        <disks_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct disks_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct disks_class_data_s DISKS_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          disksClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        disks_Info;            // Forward Reference




static
bool            disksClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DISKS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		disksClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_DISKS_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&disks_Info,
    disksClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    disks_Class,
    disksClass_WhoAmI,
    (P_OBJ_QUERYINFO)disksClass_QueryInfo,
    NULL                        // disksClass_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
DISKS_CLASS_DATA  disks_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(DISKS_CLASS_DATA),           // cbSize
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
void *          disksClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    DISKS_CLASS_DATA *this = objId;
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
                        return (void *)&disks_Info;
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
                        return disks_ParseObject;
                    }
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return disksClass_WhoAmI;
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
bool            disks_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DISKS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            disks_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          disks_Class(
    void
)
{
    return (OBJ_ID)&disks_ClassObj;
}


static
uint16_t		disks_WhoAmI(
    void
)
{
    return OBJ_IDENT_DISKS;
}


const
DISKS_VTBL     disks_Vtbl = {
    {
        &disks_Info,
        disks_IsKindOf,
#ifdef  DISKS_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        disks_Dealloc,
        disks_Class,
        disks_WhoAmI,
        (P_OBJ_QUERYINFO)disks_QueryInfo,
        (P_OBJ_TOSTRING)disks_ToDebugString,
        NULL,			// disks_Enable,
        NULL,			// disks_Disable,
        NULL,			// (P_OBJ_ASSIGN)disks_Assign,
        NULL,			// (P_OBJ_COMPARE)disks_Compare,
        NULL, 			// (P_OBJ_PTR)disks_Copy,
        NULL, 			// (P_OBJ_PTR)disks_DeepCopy,
        NULL 			// (P_OBJ_HASH)disks_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //disks_IsEnabled,
 
};



static
const
OBJ_INFO        disks_Info = {
    "disks",
    "Information/Management of Mounted Disks",
    (OBJ_DATA *)&disks_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&disks_Vtbl
};





