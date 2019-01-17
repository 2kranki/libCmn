// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'rrds'
//	Generated 01/05/2019 23:32:39


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




#define			RRDS_OBJECT_C	    1
#include        <rrds_internal.h>
#ifdef  RRDS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct rrds_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  RRDS_SINGLETON
    volatile
    RRDS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          rrdsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        rrds_Info;            // Forward Reference




static
bool            rrdsClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_RRDS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		rrdsClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_RRDS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
RRDS_CLASS_VTBL    class_Vtbl = {
    {
        &rrds_Info,
        rrdsClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        rrds_Class,
        rrdsClass_WhoAmI,
        (P_OBJ_QUERYINFO)rrdsClass_QueryInfo,
        NULL                        // rrdsClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

RRDS_CLASS_DATA  rrds_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(RRDS_CLASS_DATA),                  // cbSize
        OBJ_IDENT_RRDS_CLASS,                     // cbIdent
        0,                                      // cbFlags
        0,                                      // eRc
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  RRDS_SINGLETON
RRDS_DATA *     rrds_getSingleton (
    void
)
{
    return (OBJ_ID)(rrds_ClassObj.pSingleton);
}


bool            rrds_setSingleton (
    RRDS_DATA       *pValue
)
{
    PSXLOCK_DATA    *pLock = OBJ_NIL;
    bool            fRc;
    
    pLock = psxLock_New( );
    if (OBJ_NIL == pLock) {
        DEBUG_BREAK();
        return false;
    }
    fRc = psxLock_Lock(pLock);
    if (!fRc) {
        DEBUG_BREAK();
        obj_Release(pLock);
        pLock = OBJ_NIL;
        return false;
    }
    
    obj_Retain(pValue);
    if (rrds_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(rrds_ClassObj.pSingleton));
    }
    rrds_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



RRDS_DATA *     rrds_Shared (
    void
)
{
    RRDS_DATA       *this = (OBJ_ID)(rrds_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = rrds_New( );
        rrds_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // rrds_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            rrds_SharedReset (
    void
)
{
    RRDS_DATA       *this = (OBJ_ID)(rrds_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        rrds_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          rrdsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    RRDS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(RRDS_DATA);
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
                        return (void *)&rrds_Info;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case OBJ_QUERYINFO_TYPE_INFO:
            return (void *)obj_getInfo(this);
            break;
            
        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {
                    
                case 'N':
                    if (str_Compare("New", (char *)pStr) == 0) {
                        return rrds_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return rrdsClass_WhoAmI;
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




static
bool            rrds_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_RRDS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            rrds_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          rrds_Class (
    void
)
{
    return (OBJ_ID)&rrds_ClassObj;
}


static
uint16_t		rrds_WhoAmI (
    void
)
{
    return OBJ_IDENT_RRDS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
RRDS_VTBL     rrds_Vtbl = {
    {
        &rrds_Info,
        rrds_IsKindOf,
#ifdef  RRDS_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        rrds_Dealloc,
        rrds_Class,
        rrds_WhoAmI,
        (P_OBJ_QUERYINFO)rrds_QueryInfo,
        (P_OBJ_TOSTRING)rrds_ToDebugString,
        NULL,			// rrds_Enable,
        NULL,			// rrds_Disable,
        NULL,			// (P_OBJ_ASSIGN)rrds_Assign,
        NULL,			// (P_OBJ_COMPARE)rrds_Compare,
        NULL, 			// (P_OBJ_PTR)rrds_Copy,
        NULL, 			// (P_OBJ_PTR)rrds_DeepCopy,
        NULL 			// (P_OBJ_HASH)rrds_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    (void *)rrds_Close,
    (void *)rrds_Create,
    (void *)rrds_Open,
    (void *)rrds_RecordRead,
    (void *)rrds_RecordWrite,

};



static
const
OBJ_INFO        rrds_Info = {
    "rrds",
    "Relative Record Dataset/File",
    (OBJ_DATA *)&rrds_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&rrds_Vtbl,
    sizeof(RRDS_DATA)
};





