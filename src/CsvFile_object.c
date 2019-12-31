// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'CsvFile'
//	Generated 12/30/2019 11:06:40


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




#define			CSVFILE_OBJECT_C	    1
#include        <CsvFile_internal.h>
#ifdef  CSVFILE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct CsvFile_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  CSVFILE_SINGLETON
    volatile
    CSVFILE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          CsvFileClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        CsvFile_Info;            // Forward Reference




static
bool            CsvFileClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_CSVFILE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(CsvFile_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		CsvFileClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_CSVFILE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
CSVFILE_CLASS_VTBL    class_Vtbl = {
    {
        &CsvFile_Info,
        CsvFileClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        CsvFile_Class,
        CsvFileClass_WhoAmI,
        (P_OBJ_QUERYINFO)CsvFileClass_QueryInfo,
        NULL                        // CsvFileClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

CSVFILE_CLASS_DATA  CsvFile_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(CSVFILE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  CSVFILE_SINGLETON
CSVFILE_DATA *     CsvFile_getSingleton (
    void
)
{
    return (OBJ_ID)(CsvFile_ClassObj.pSingleton);
}


bool            CsvFile_setSingleton (
    CSVFILE_DATA       *pValue
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
    if (CsvFile_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(CsvFile_ClassObj.pSingleton));
    }
    CsvFile_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



CSVFILE_DATA *     CsvFile_Shared (
    void
)
{
    CSVFILE_DATA       *this = (OBJ_ID)(CsvFile_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = CsvFile_New( );
        CsvFile_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // CsvFile_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            CsvFile_SharedReset (
    void
)
{
    CSVFILE_DATA       *this = (OBJ_ID)(CsvFile_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        CsvFile_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          CsvFileClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    CSVFILE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(CSVFILE_DATA);
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
                        return (void *)&CsvFile_Info;
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
                        return CsvFile_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return CsvFile_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return CsvFileClass_WhoAmI;
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
bool            CsvFile_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_CSVFILE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(CsvFile_Class())->pClassSuperObject;
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
void            CsvFile_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          CsvFile_Class (
    void
)
{
    return (OBJ_ID)&CsvFile_ClassObj;
}


static
uint16_t		CsvFile_WhoAmI (
    void
)
{
    return OBJ_IDENT_CSVFILE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
CSVFILE_VTBL     CsvFile_Vtbl = {
    {
        &CsvFile_Info,
        CsvFile_IsKindOf,
#ifdef  CSVFILE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        CsvFile_Dealloc,
        CsvFile_Class,
        CsvFile_WhoAmI,
        (P_OBJ_QUERYINFO)CsvFile_QueryInfo,
        (P_OBJ_TOSTRING)CsvFile_ToDebugString,
        NULL,			// CsvFile_Enable,
        NULL,			// CsvFile_Disable,
        NULL,			// (P_OBJ_ASSIGN)CsvFile_Assign,
        NULL,			// (P_OBJ_COMPARE)CsvFile_Compare,
        NULL, 			// (P_OBJ_PTR)CsvFile_Copy,
        NULL, 			// (P_OBJ_PTR)CsvFile_DeepCopy,
        NULL 			// (P_OBJ_HASH)CsvFile_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //CsvFile_IsEnabled,
 
};



static
const
OBJ_INFO        CsvFile_Info = {
    "CsvFile",
    "Comma-delimited (csv) File Processing",
    (OBJ_DATA *)&CsvFile_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&CsvFile_Vtbl,
    sizeof(CSVFILE_DATA)
};





