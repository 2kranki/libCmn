// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'bptLeaf'
//	Generated 07/08/2018 09:42:01


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



//#define   BPTLEAF_IS_SINGLETON     1

#define			BPTLEAF_OBJECT_C	    1
#include        <bptLeaf_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct bptLeaf_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct bptLeaf_class_data_s BPTLEAF_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          bptLeafClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        bptLeaf_Info;            // Forward Reference




static
bool            bptLeafClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPTLEAF_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		bptLeafClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_BPTLEAF_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&bptLeaf_Info,
    bptLeafClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    bptLeaf_Class,
    bptLeafClass_WhoAmI,
    (P_OBJ_QUERYINFO)bptLeafClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
BPTLEAF_CLASS_DATA  bptLeaf_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(BPTLEAF_CLASS_DATA),         // cbSize
        OBJ_IDENT_BPTLEAF_CLASS,            // cbIdent
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
void *          bptLeafClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BPTLEAF_CLASS_DATA *this = objId;
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
                        return (void *)&bptLeaf_Info;
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
                        return bptLeaf_ParseObject;
                    }
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return bptLeafClass_WhoAmI;
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
bool            bptLeaf_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_BPTLEAF == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            bptLeaf_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          bptLeaf_Class(
    void
)
{
    return (OBJ_ID)&bptLeaf_ClassObj;
}


static
uint16_t		bptLeaf_WhoAmI(
    void
)
{
    return OBJ_IDENT_BPTLEAF;
}


const
BPTLEAF_VTBL     bptLeaf_Vtbl = {
    {
        &bptLeaf_Info,
        bptLeaf_IsKindOf,
#ifdef  BPTLEAF_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        bptLeaf_Dealloc,
        bptLeaf_Class,
        bptLeaf_WhoAmI,
        (P_OBJ_QUERYINFO)bptLeaf_QueryInfo,
        (P_OBJ_TOSTRING)bptLeaf_ToDebugString,
        NULL,			// bptLeaf_Enable,
        NULL,			// bptLeaf_Disable,
        NULL,			// (P_OBJ_ASSIGN)bptLeaf_Assign,
        NULL,			// (P_OBJ_COMPARE)bptLeaf_Compare,
        NULL, 			// (P_OBJ_PTR)bptLeaf_Copy,
        NULL, 			// (P_OBJ_PTR)bptLeaf_DeepCopy,
        NULL 			// (P_OBJ_HASH)bptLeaf_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //bptLeaf_IsEnabled,
 
};



static
const
OBJ_INFO        bptLeaf_Info = {
    "bptLeaf",
    "B-Plus Tree Leaf Block",
    (OBJ_DATA *)&bptLeaf_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&bptLeaf_Vtbl
};





