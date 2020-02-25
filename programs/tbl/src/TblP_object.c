// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'TblP'
//	Generated 02/22/2020 23:45:29


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




#define			TBLP_OBJECT_C	    1
#include        <TblP_internal.h>
#ifdef  TBLP_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct TblP_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TBLP_SINGLETON
    volatile
    TBLP_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          TblPClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        TblP_Info;            // Forward Reference




static
bool            TblPClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_TBLP_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(TblP_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		TblPClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_TBLP_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TBLP_CLASS_VTBL    class_Vtbl = {
    {
        &TblP_Info,
        TblPClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        TblP_Class,
        TblPClass_WhoAmI,
        (P_OBJ_QUERYINFO)TblPClass_QueryInfo,
        NULL                        // TblPClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

TBLP_CLASS_DATA  TblP_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TBLP_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TBLP_SINGLETON
TBLP_DATA *     TblP_getSingleton (
    void
)
{
    return (OBJ_ID)(TblP_ClassObj.pSingleton);
}


bool            TblP_setSingleton (
    TBLP_DATA       *pValue
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
    if (TblP_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(TblP_ClassObj.pSingleton));
    }
    TblP_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TBLP_DATA *     TblP_Shared (
    void
)
{
    TBLP_DATA       *this = (OBJ_ID)(TblP_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = TblP_New( );
        TblP_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // TblP_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            TblP_SharedReset (
    void
)
{
    TBLP_DATA       *this = (OBJ_ID)(TblP_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        TblP_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          TblPClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TBLP_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TBLP_DATA);
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
                        return (void *)&TblP_Info;
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
                        return TblP_New;
                    }
                    break;
                    
#ifdef  TBLP_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return TblP_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return TblP_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return TblPClass_WhoAmI;
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
bool            TblP_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_TBLP == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(TblP_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        pInfo = obj_getInfo(pObj);
        return pInfo->pDefaultVtbls->pIsKindOf(classID);
    }
    
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            TblP_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          TblP_Class (
    void
)
{
    return (OBJ_ID)&TblP_ClassObj;
}


static
uint16_t		TblP_WhoAmI (
    void
)
{
    return OBJ_IDENT_TBLP;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
TBLP_VTBL     TblP_Vtbl = {
    {
        &TblP_Info,
        TblP_IsKindOf,
#ifdef  TBLP_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        TblP_Dealloc,
        TblP_Class,
        TblP_WhoAmI,
        (P_OBJ_QUERYINFO)TblP_QueryInfo,
        (P_OBJ_TOSTRING)TblP_ToDebugString,
        NULL,			// TblP_Enable,
        NULL,			// TblP_Disable,
        NULL,			// (P_OBJ_ASSIGN)TblP_Assign,
        NULL,			// (P_OBJ_COMPARE)TblP_Compare,
        NULL, 			// (P_OBJ_PTR)TblP_Copy,
        NULL, 			// (P_OBJ_PTR)TblP_DeepCopy,
        NULL 			// (P_OBJ_HASH)TblP_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //TblP_IsEnabled,
 
};



static
const
OBJ_INFO        TblP_Info = {
    "TblP",
    "TBL Language Parser",
    (OBJ_DATA *)&TblP_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&TblP_Vtbl,
    sizeof(TBLP_DATA)
};





