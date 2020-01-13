// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'md5ChkSum'
//	Generated 04/01/2018 21:11:43


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



//#define   MD5CHKSUM_IS_SINGLETON     1

#define			MD5CHKSUM_OBJECT_C	    1
#include        <md5ChkSum_internal.h>



//===========================================================
//                  Class Object Definition
//===========================================================

struct md5ChkSum_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};
typedef struct md5ChkSum_class_data_s MD5CHKSUM_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          md5ChkSumClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        md5ChkSum_Info;            // Forward Reference




static
bool            md5ChkSumClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_MD5CHKSUM_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		md5ChkSumClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_MD5CHKSUM_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&md5ChkSum_Info,
    md5ChkSumClass_IsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    md5ChkSum_Class,
    md5ChkSumClass_WhoAmI,
    (P_OBJ_QUERYINFO)md5ChkSumClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
MD5CHKSUM_CLASS_DATA  md5ChkSum_ClassObj = {
    {
        &obj_Vtbl,                          // pVtbl
        sizeof(MD5CHKSUM_CLASS_DATA),       // cbSize
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
void *          md5ChkSumClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    MD5CHKSUM_CLASS_DATA *this = objId;
#ifdef XYZZY
    const
    char            *pStr = pData;
#endif
    
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
                        return md5ChkSumClass_WhoAmI;
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
bool            md5ChkSum_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_MD5CHKSUM == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            md5ChkSum_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          md5ChkSum_Class(
    void
)
{
    return (OBJ_ID)&md5ChkSum_ClassObj;
}


static
uint16_t		md5ChkSum_WhoAmI(
    void
)
{
    return OBJ_IDENT_MD5CHKSUM;
}


const
MD5CHKSUM_VTBL     md5ChkSum_Vtbl = {
    {
        &md5ChkSum_Info,
        md5ChkSum_IsKindOf,
#ifdef  MD5CHKSUM_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        md5ChkSum_Dealloc,
        md5ChkSum_Class,
        md5ChkSum_WhoAmI,
        (P_OBJ_QUERYINFO)md5ChkSum_QueryInfo,
        (P_OBJ_TOSTRING)md5ChkSum_ToDebugString,
        NULL,			// md5ChkSum_Enable,
        NULL,			// md5ChkSum_Disable,
        NULL,			// (P_OBJ_ASSIGN)md5ChkSum_Assign,
        NULL,			// (P_OBJ_COMPARE)md5ChkSum_Compare,
        NULL, 			// (P_OBJ_PTR)md5ChkSum_Copy,
        NULL, 			// (P_OBJ_PTR)md5ChkSum_DeepCopy,
        NULL 			// (P_OBJ_HASH)md5ChkSum_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //md5ChkSum_IsEnabled,
 
};



static
const
OBJ_INFO        md5ChkSum_Info = {
    "md5ChkSum",
    "MD5 Check Sum",	
    (OBJ_DATA *)&md5ChkSum_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&md5ChkSum_Vtbl
};





