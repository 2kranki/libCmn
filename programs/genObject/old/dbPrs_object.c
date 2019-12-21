// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'dbPrs'
//	Generated 11/30/2018 16:55:05


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




#define			DBPRS_OBJECT_C	    1
#include        <dbPrs_internal.h>
#ifdef  DBPRS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct dbPrs_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  DBPRS_SINGLETON
    volatile
    DBPRS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          dbPrsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        dbPrs_Info;            // Forward Reference




static
bool            dbPrsClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_DBPRS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		dbPrsClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_DBPRS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
DBPRS_CLASS_VTBL    class_Vtbl = {
    {
        &dbPrs_Info,
        dbPrsClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        dbPrs_Class,
        dbPrsClass_WhoAmI,
        (P_OBJ_QUERYINFO)dbPrsClass_QueryInfo,
        NULL                        // dbPrsClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

DBPRS_CLASS_DATA  dbPrs_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(DBPRS_CLASS_DATA),           // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  DBPRS_SINGLETON
DBPRS_DATA *     dbPrs_getSingleton (
    void
)
{
    return (OBJ_ID)(dbPrs_ClassObj.pSingleton);
}


bool            dbPrs_setSingleton (
    DBPRS_DATA       *pValue
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
    if (dbPrs_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(dbPrs_ClassObj.pSingleton));
    }
    dbPrs_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



DBPRS_DATA *     dbPrs_Shared (
    void
)
{
    DBPRS_DATA       *this = (OBJ_ID)(dbPrs_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = dbPrs_New( );
        dbPrs_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // dbPrs_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            dbPrs_SharedReset (
    void
)
{
    DBPRS_DATA       *this = (OBJ_ID)(dbPrs_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        dbPrs_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          dbPrsClass_QueryInfo (
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
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(DBPRS_DATA);
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
                        return (void *)&dbPrs_Info;
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
                        return dbPrs_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return dbPrsClass_WhoAmI;
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
bool            dbPrs_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_DBPRS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            dbPrs_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          dbPrs_Class (
    void
)
{
    return (OBJ_ID)&dbPrs_ClassObj;
}


static
uint16_t		dbPrs_WhoAmI (
    void
)
{
    return OBJ_IDENT_DBPRS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
DBPRS_VTBL     dbPrs_Vtbl = {
    {
        &dbPrs_Info,
        dbPrs_IsKindOf,
#ifdef  DBPRS_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        dbPrs_Dealloc,
        dbPrs_Class,
        dbPrs_WhoAmI,
        (P_OBJ_QUERYINFO)dbPrs_QueryInfo,
        (P_OBJ_TOSTRING)dbPrs_ToDebugString,
        NULL,			// dbPrs_Enable,
        NULL,			// dbPrs_Disable,
        NULL,			// (P_OBJ_ASSIGN)dbPrs_Assign,
        NULL,			// (P_OBJ_COMPARE)dbPrs_Compare,
        NULL, 			// (P_OBJ_PTR)dbPrs_Copy,
        NULL, 			// (P_OBJ_PTR)dbPrs_DeepCopy,
        NULL 			// (P_OBJ_HASH)dbPrs_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //dbPrs_IsEnabled,
 
};



static
const
OBJ_INFO        dbPrs_Info = {
    "dbPrs",
    "Database Parser",
    (OBJ_DATA *)&dbPrs_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&dbPrs_Vtbl,
    sizeof(DBPRS_DATA)
};





