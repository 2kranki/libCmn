// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'visitor'
//	Generated 02/03/2018 14:29:56


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



//#define   VISITOR_IS_SINGLETON     1

#define			VISITOR_OBJECT_C	    1
#include        <visitor_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct visitor_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct visitor_class_data_s VISITOR_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          visitorClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        visitor_Info;            // Forward Reference




static
bool            visitorClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_VISITOR_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		visitorClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_VISITOR_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&visitor_Info,
    visitorClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    visitor_Class,
    visitorClass_WhoAmI,
    (P_OBJ_QUERYINFO)visitorClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
VISITOR_CLASS_DATA  visitor_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(VISITOR_CLASS_DATA),         // cbSize
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
void *          visitorClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    VISITOR_CLASS_DATA *this = objId;
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
                        return visitorClass_WhoAmI;
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
bool            visitor_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_VISITOR == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            visitor_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          visitor_Class(
    void
)
{
    return (OBJ_ID)&visitor_ClassObj;
}


static
uint16_t		visitor_WhoAmI(
    void
)
{
    return OBJ_IDENT_VISITOR;
}


const
VISITOR_VTBL     visitor_Vtbl = {
    {
        &visitor_Info,
        visitor_IsKindOf,
#ifdef  VISITOR_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        visitor_Dealloc,
        visitor_Class,
        visitor_WhoAmI,
        (P_OBJ_QUERYINFO)visitor_QueryInfo,
        (P_OBJ_TOSTRING)visitor_ToDebugString,
        NULL,			// visitor_Enable,
        NULL,			// visitor_Disable,
        NULL,			// (P_OBJ_ASSIGN)visitor_Assign,
        NULL,			// (P_OBJ_COMPARE)visitor_Compare,
        NULL, 			// (P_OBJ_PTR)visitor_Copy,
        NULL 			// (P_OBJ_HASH)visitor_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //visitor_IsEnabled,
 
};



static
const
OBJ_INFO        visitor_Info = {
    "visitor",
    "Visitor Pattern Base Class",
    (OBJ_DATA *)&visitor_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&visitor_Vtbl
};





