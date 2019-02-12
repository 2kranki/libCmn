// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'memFile'
//	Generated 01/13/2019 15:55:16


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




#define			MEMFILE_OBJECT_C	    1
#include        <memFile_internal.h>
#ifdef  MEMFILE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct memFile_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  MEMFILE_SINGLETON
    volatile
    MEMFILE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          memFileClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        memFile_Info;            // Forward Reference




static
bool            memFileClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_MEMFILE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_BLKS_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		memFileClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_MEMFILE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
MEMFILE_CLASS_VTBL    class_Vtbl = {
    {
        &memFile_Info,
        memFileClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        memFile_Class,
        memFileClass_WhoAmI,
        (P_OBJ_QUERYINFO)memFileClass_QueryInfo,
        NULL                        // memFileClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

MEMFILE_CLASS_DATA  memFile_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(MEMFILE_CLASS_DATA),             // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  MEMFILE_SINGLETON
MEMFILE_DATA *     memFile_getSingleton (
    void
)
{
    return (OBJ_ID)(memFile_ClassObj.pSingleton);
}


bool            memFile_setSingleton (
    MEMFILE_DATA       *pValue
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
    if (memFile_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(memFile_ClassObj.pSingleton));
    }
    memFile_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



MEMFILE_DATA *     memFile_Shared (
    void
)
{
    MEMFILE_DATA       *this = (OBJ_ID)(memFile_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = memFile_New( );
        memFile_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // memFile_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            memFile_SharedReset (
    void
)
{
    MEMFILE_DATA       *this = (OBJ_ID)(memFile_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        memFile_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          memFileClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    MEMFILE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(MEMFILE_DATA);
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
                        return (void *)&memFile_Info;
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
                        return memFile_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return memFileClass_WhoAmI;
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
bool            memFile_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_MEMFILE == classID) {
       return true;
    }
    if (OBJ_IDENT_BLKS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            memFile_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          memFile_Class (
    void
)
{
    return (OBJ_ID)&memFile_ClassObj;
}


static
uint16_t		memFile_WhoAmI (
    void
)
{
    return OBJ_IDENT_MEMFILE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
MEMFILE_VTBL     memFile_Vtbl = {
    {
        &memFile_Info,
        memFile_IsKindOf,
#ifdef  MEMFILE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        memFile_Dealloc,
        memFile_Class,
        memFile_WhoAmI,
        (P_OBJ_QUERYINFO)memFile_QueryInfo,
        (P_OBJ_TOSTRING)memFile_ToDebugString,
        NULL,			// memFile_Enable,
        NULL,			// memFile_Disable,
        NULL,			// (P_OBJ_ASSIGN)memFile_Assign,
        NULL,			// (P_OBJ_COMPARE)memFile_Compare,
        NULL, 			// (P_OBJ_PTR)memFile_Copy,
        NULL, 			// (P_OBJ_PTR)memFile_DeepCopy,
        NULL 			// (P_OBJ_HASH)memFile_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    (void *)memFile_Close,
    (void *)memFile_Create,
    (void *)memFile_Gets,
    (void *)memFile_Open,
    (void *)memFile_Read,
    (void *)memFile_SeekBegin,
    (void *)memFile_SeekCur,
    (void *)memFile_SeekEnd,
    (void *)memFile_Size,
    (void *)memFile_Tell,
    (void *)memFile_Write,
};



static
const
OBJ_INFO        memFile_Info = {
    "memFile",
    "Memory Based File",
    (OBJ_DATA *)&memFile_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&memFile_Vtbl,
    sizeof(MEMFILE_DATA)
};





