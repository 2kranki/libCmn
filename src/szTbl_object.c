// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'szTbl'
//	Generated 07/24/2017 09:16:37


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



#define			SZTBL_OBJECT_C	    1
#include        <szTbl_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct szTbl_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    SZTBL_DATA      *pShared;
};
typedef struct szTbl_class_data_s SZTBL_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        szTbl_Info;            // Forward Reference



static
void *          szTblClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);




static
bool            szTbl_ClassIsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_SZTBL_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		obj_ClassWhoAmI (
    void
)
{
    return OBJ_IDENT_SZTBL_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&szTbl_Info,
    szTbl_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    szTbl_Class,
    obj_ClassWhoAmI,
    szTblClass_QueryInfo
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
SZTBL_CLASS_DATA  szTbl_ClassObj = {
    {
        &obj_Vtbl,                  // pVtbl
        sizeof(SZTBL_CLASS_DATA),   // cbSize
        0,                          // cbFlags
        1,                          // cbRetainCount
        {0}                         // cbMisc
    },
	OBJ_NIL                     // pShared
};



SZTBL_DATA *     szTbl_getShared (
)
{
    SZTBL_CLASS_DATA    *pClass;
    SZTBL_DATA          *pShared = OBJ_NIL;
    
    pClass = szTbl_Class( );
    if (pClass->pShared) {
        pShared = pClass->pShared;
    }
    
    return pShared;
}


bool            szTbl_setShared (
    SZTBL_DATA      *pValue
)
{
    SZTBL_CLASS_DATA    *pClass;
    
    pClass = szTbl_Class( );

    obj_Retain(pValue);
    if (pClass->pShared) {
        obj_Release(pClass->pShared);
    }
    pClass->pShared = pValue;
    
    return true;
}



static
bool            szTbl_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_SZTBL == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            szTbl_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          szTbl_Class (
    void
)
{
    return (OBJ_ID)&szTbl_ClassObj;
}


//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          szTblClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SZTBL_CLASS_DATA *this = objId;
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
            
        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {
                    
                case 'P':
                    if (str_Compare("ParseObject", (char *)pStr) == 0) {
                        return szTbl_ParseObject;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    return NULL;
}



SZTBL_DATA *     szTbl_Shared (
)
{
    SZTBL_CLASS_DATA    *pClass;
    
    pClass = szTbl_Class( );
    BREAK_NULL(pClass);
    if (OBJ_NIL == pClass->pShared) {
        pClass->pShared = szTbl_New( );
    }
    BREAK_NULL(pClass->pShared);
    return pClass->pShared;
}



SZTBL_DATA *     szTbl_SharedReplace (
    SZTBL_DATA      *this
)
{
    szTbl_setShared(this);
    return this;
}


SZTBL_DATA *     szTbl_SharedReset (
)
{
    szTbl_setShared(OBJ_NIL);
    return OBJ_NIL;
}



static
uint16_t		szTbl_WhoAmI (
    void
)
{
    return OBJ_IDENT_SZTBL;
}


const
SZTBL_VTBL     szTbl_Vtbl = {
    {
        &szTbl_Info,
        szTbl_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        szTbl_Dealloc,
        szTbl_Class,
        szTbl_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)szTbl_QueryInfo,
        (P_OBJ_TOSTRING)szTbl_ToDebugString,
        NULL,			// szTbl_Enable,
        NULL,			// szTbl_Disable,
        NULL,			// (P_OBJ_ASSIGN)szTbl_Assign,
        NULL,			// (P_OBJ_COMPARE)szTbl_Compare,
        NULL, 			// (P_OBJ_PTR)szTbl_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)szTbl_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //szTbl_IsEnabled,
 
};



static
const
OBJ_INFO        szTbl_Info = {
    "szTbl",
    "Static String Table",
    (OBJ_DATA *)&szTbl_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&szTbl_Vtbl
};





