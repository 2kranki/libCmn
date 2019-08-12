// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'AStrCReader'
//	Generated 08/11/2019 13:04:20


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




#define			ASTRCREADER_OBJECT_C	    1
#include        <AStrCReader_internal.h>
#ifdef  ASTRCREADER_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct AStrCReader_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  ASTRCREADER_SINGLETON
    volatile
    ASTRCREADER_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          AStrCReaderClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        AStrCReader_Info;            // Forward Reference




static
bool            AStrCReaderClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTRCREADER_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		AStrCReaderClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_ASTRCREADER_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
ASTRCREADER_CLASS_VTBL    class_Vtbl = {
    {
        &AStrCReader_Info,
        AStrCReaderClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        AStrCReader_Class,
        AStrCReaderClass_WhoAmI,
        (P_OBJ_QUERYINFO)AStrCReaderClass_QueryInfo,
        NULL                        // AStrCReaderClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

ASTRCREADER_CLASS_DATA  AStrCReader_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(ASTRCREADER_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  ASTRCREADER_SINGLETON
ASTRCREADER_DATA *     AStrCReader_getSingleton (
    void
)
{
    return (OBJ_ID)(AStrCReader_ClassObj.pSingleton);
}


bool            AStrCReader_setSingleton (
    ASTRCREADER_DATA       *pValue
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
    if (AStrCReader_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(AStrCReader_ClassObj.pSingleton));
    }
    AStrCReader_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



ASTRCREADER_DATA *     AStrCReader_Shared (
    void
)
{
    ASTRCREADER_DATA       *this = (OBJ_ID)(AStrCReader_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = AStrCReader_New( );
        AStrCReader_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // AStrCReader_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            AStrCReader_SharedReset (
    void
)
{
    ASTRCREADER_DATA       *this = (OBJ_ID)(AStrCReader_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        AStrCReader_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          AStrCReaderClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    ASTRCREADER_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(ASTRCREADER_DATA);
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
                        return (void *)&AStrCReader_Info;
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
                        return AStrCReader_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return AStrCReaderClass_WhoAmI;
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
bool            AStrCReader_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_ASTRCREADER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            AStrCReader_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          AStrCReader_Class (
    void
)
{
    return (OBJ_ID)&AStrCReader_ClassObj;
}


static
uint16_t		AStrCReader_WhoAmI (
    void
)
{
    return OBJ_IDENT_ASTRCREADER;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
ASTRCREADER_VTBL     AStrCReader_Vtbl = {
    {
        &AStrCReader_Info,
        AStrCReader_IsKindOf,
#ifdef  ASTRCREADER_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        AStrCReader_Dealloc,
        AStrCReader_Class,
        AStrCReader_WhoAmI,
        (P_OBJ_QUERYINFO)AStrCReader_QueryInfo,
        (P_OBJ_TOSTRING)AStrCReader_ToDebugString,
        NULL,			// AStrCReader_Enable,
        NULL,			// AStrCReader_Disable,
        NULL,			// (P_OBJ_ASSIGN)AStrCReader_Assign,
        NULL,			// (P_OBJ_COMPARE)AStrCReader_Compare,
        NULL, 			// (P_OBJ_PTR)AStrCReader_Copy,
        NULL, 			// (P_OBJ_PTR)AStrCReader_DeepCopy,
        NULL 			// (P_OBJ_HASH)AStrCReader_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    (void *)AStrCReader_Next,
    (void *)AStrCReader_Peek,
    (void *)AStrCReader_Rescan,

};



static
const
OBJ_INFO        AStrCReader_Info = {
    "AStrCReader",
    "AStrC Reader",
    (OBJ_DATA *)&AStrCReader_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&AStrCReader_Vtbl,
    sizeof(ASTRCREADER_DATA)
};





