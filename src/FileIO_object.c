// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'FileIO'
//  Generated 07/10/2021 11:26:44


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




#define         FILEIO_OBJECT_C       1
#include        <FileIO_internal.h>
#ifdef  FILEIO_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct FileIO_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  FILEIO_SINGLETON
    volatile
    FILEIO_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          FileIOClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        FileIO_Info;            // Forward Reference




static
bool            FileIOClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_FILEIO_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(FileIO_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        FileIOClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_FILEIO_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
FILEIO_CLASS_VTBL    class_Vtbl = {
    {
        &FileIO_Info,
        FileIOClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        FileIO_Class,
        FileIOClass_WhoAmI,
        (P_OBJ_QUERYINFO)FileIOClass_QueryInfo,
        NULL                        // FileIOClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

FILEIO_CLASS_DATA  FileIO_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(FILEIO_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  FILEIO_SINGLETON
extern
const
FILEIO_VTBL       FileIO_VtblShared;


FILEIO_DATA *     FileIO_getSingleton (
    void
)
{
    return (OBJ_ID)(FileIO_ClassObj.pSingleton);
}


bool            FileIO_setSingleton (
    FILEIO_DATA       *pValue
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
    if (FileIO_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(FileIO_ClassObj.pSingleton));
    }
    FileIO_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



FILEIO_DATA *     FileIO_Shared (
    void
)
{
    FILEIO_DATA       *this = (OBJ_ID)(FileIO_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = FileIO_New( );
        obj_setVtbl(this, (void *)&FileIO_VtblShared);
        FileIO_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // FileIO_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            FileIO_SharedReset (
    void
)
{
    FILEIO_DATA       *this = (OBJ_ID)(FileIO_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&FileIO_Vtbl);
        obj_Release(this);
        FileIO_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          FileIOClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    FILEIO_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(FILEIO_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&FileIO_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&FileIO_Info.pClassSuperObject;
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
                        return FileIO_New;
                    }
                    break;
                    
                case 'P':
#ifdef  FILEIO_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return FileIO_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return FileIO_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  FILEIO_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return FileIO_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return FileIO_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return FileIOClass_WhoAmI;
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
bool            FileIO_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_FILEIO == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(FileIO_Class())->pClassSuperObject;
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
void            FileIO_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          FileIO_Class (
    void
)
{
    return (OBJ_ID)&FileIO_ClassObj;
}


static
uint16_t        FileIO_WhoAmI (
    void
)
{
    return OBJ_IDENT_FILEIO;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  FILEIO_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
FILEIO_VTBL     FileIO_VtblShared = {
    {
        &FileIO_Info,
        FileIO_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        FileIO_Dealloc,
        FileIO_Class,
        FileIO_WhoAmI,
        (P_OBJ_QUERYINFO)FileIO_QueryInfo,
        (P_OBJ_TOSTRING)FileIO_ToDebugString,
        NULL,           // FileIO_Enable,
        NULL,           // FileIO_Disable,
        NULL,           // (P_OBJ_ASSIGN)FileIO_Assign,
        NULL,           // (P_OBJ_COMPARE)FileIO_Compare,
        NULL,           // (P_OBJ_PTR)FileIO_Copy,
        NULL,           // (P_OBJ_PTR)FileIO_DeepCopy,
        NULL            // (P_OBJ_HASH)FileIO_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //FileIO_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
FILEIO_VTBL     FileIO_Vtbl = {
    {
        &FileIO_Info,
        FileIO_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        FileIO_Dealloc,
        FileIO_Class,
        FileIO_WhoAmI,
        (P_OBJ_QUERYINFO)FileIO_QueryInfo,
        (P_OBJ_TOSTRING)FileIO_ToDebugString,
        NULL,           // FileIO_Enable,
        NULL,           // FileIO_Disable,
        NULL,           // (P_OBJ_ASSIGN)FileIO_Assign,
        NULL,           // (P_OBJ_COMPARE)FileIO_Compare,
        NULL,           // (P_OBJ_PTR)FileIO_Copy,
        NULL,           // (P_OBJ_PTR)FileIO_DeepCopy,
        NULL            // (P_OBJ_HASH)FileIO_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //============= I/O Interface Compatibility ===============
    (void *)FileIO_Close,
    (void *)FileIO_Flush,
    (void *)FileIO_ReadIO,
    (void *)FileIO_Seek,
    (void *)FileIO_Tell,
    (void *)FileIO_WriteIO,
    //=========== End of I/O Interface Compatibility =============

};



static
const
OBJ_INFO        FileIO_Info = {
    "FileIO",
    "Generic Dataset/File Input/Output",
    (OBJ_DATA *)&FileIO_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&FileIO_Vtbl,
    sizeof(FILEIO_DATA)
};





