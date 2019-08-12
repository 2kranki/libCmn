// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'scanReader'
//	Generated 08/11/2019 14:55:03


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




#define			SCANREADER_OBJECT_C	    1
#include        <scanReader_internal.h>
#ifdef  SCANREADER_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct scanReader_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SCANREADER_SINGLETON
    volatile
    SCANREADER_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          scanReaderClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        scanReader_Info;            // Forward Reference




static
bool            scanReaderClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_SCANREADER_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		scanReaderClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SCANREADER_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SCANREADER_CLASS_VTBL    class_Vtbl = {
    {
        &scanReader_Info,
        scanReaderClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        scanReader_Class,
        scanReaderClass_WhoAmI,
        (P_OBJ_QUERYINFO)scanReaderClass_QueryInfo,
        NULL                        // scanReaderClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SCANREADER_CLASS_DATA  scanReader_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SCANREADER_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SCANREADER_SINGLETON
SCANREADER_DATA *     scanReader_getSingleton (
    void
)
{
    return (OBJ_ID)(scanReader_ClassObj.pSingleton);
}


bool            scanReader_setSingleton (
    SCANREADER_DATA       *pValue
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
    if (scanReader_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(scanReader_ClassObj.pSingleton));
    }
    scanReader_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SCANREADER_DATA *     scanReader_Shared (
    void
)
{
    SCANREADER_DATA       *this = (OBJ_ID)(scanReader_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = scanReader_New( );
        scanReader_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // scanReader_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            scanReader_SharedReset (
    void
)
{
    SCANREADER_DATA       *this = (OBJ_ID)(scanReader_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        scanReader_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          scanReaderClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SCANREADER_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SCANREADER_DATA);
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
                        return (void *)&scanReader_Info;
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
                        return scanReader_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return scanReaderClass_WhoAmI;
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
bool            scanReader_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_SCANREADER == classID) {
       return true;
    }
    if (OBJ_IDENT_W32_READER == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            scanReader_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          scanReader_Class (
    void
)
{
    return (OBJ_ID)&scanReader_ClassObj;
}


static
uint16_t		scanReader_WhoAmI (
    void
)
{
    return OBJ_IDENT_SCANREADER;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
SCANREADER_VTBL     scanReader_Vtbl = {
    {
        &scanReader_Info,
        scanReader_IsKindOf,
#ifdef  SCANREADER_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        scanReader_Dealloc,
        scanReader_Class,
        scanReader_WhoAmI,
        (P_OBJ_QUERYINFO)scanReader_QueryInfo,
        (P_OBJ_TOSTRING)scanReader_ToDebugString,
        NULL,			// scanReader_Enable,
        NULL,			// scanReader_Disable,
        NULL,			// (P_OBJ_ASSIGN)scanReader_Assign,
        NULL,			// (P_OBJ_COMPARE)scanReader_Compare,
        NULL, 			// (P_OBJ_PTR)scanReader_Copy,
        NULL, 			// (P_OBJ_PTR)scanReader_DeepCopy,
        NULL 			// (P_OBJ_HASH)scanReader_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    (void *)scanReader_Next,
    (void *)scanReader_Peek,
    (void *)scanReader_Rescan,

};



static
const
OBJ_INFO        scanReader_Info = {
    "scanReader",
    "scan Reader",
    (OBJ_DATA *)&scanReader_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&scanReader_Vtbl,
    sizeof(SCANREADER_DATA)
};





