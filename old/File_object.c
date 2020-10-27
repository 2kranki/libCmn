// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'File'
//  Generated 10/27/2020 09:53:08


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




#define         FILE_OBJECT_C       1
#include        <File_internal.h>
#ifdef  FILE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct File_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  FILE_SINGLETON
    volatile
    FILE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          FileClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        File_Info;            // Forward Reference




static
bool            FileClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_FILE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(File_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        FileClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_FILE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
FILE_CLASS_VTBL    class_Vtbl = {
    {
        &File_Info,
        FileClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        File_Class,
        FileClass_WhoAmI,
        (P_OBJ_QUERYINFO)FileClass_QueryInfo,
        NULL                        // FileClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

FILE_CLASS_DATA  File_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(FILE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  FILE_SINGLETON
extern
const
FILE_VTBL       File_VtblShared;


FILE_DATA *     File_getSingleton (
    void
)
{
    return (OBJ_ID)(File_ClassObj.pSingleton);
}


bool            File_setSingleton (
    FILE_DATA       *pValue
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
    if (File_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(File_ClassObj.pSingleton));
    }
    File_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



FILE_DATA *     File_Shared (
    void
)
{
    FILE_DATA       *this = (OBJ_ID)(File_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = File_New( );
        obj_setVtbl(this, (void *)&File_VtblShared);
        File_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // File_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            File_SharedReset (
    void
)
{
    FILE_DATA       *this = (OBJ_ID)(File_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&File_Vtbl);
        obj_Release(this);
        File_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          FileClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    FILE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(FILE_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&File_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&File_Info.pClassSuperObject;
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
                        return File_New;
                    }
                    break;
                    
                case 'P':
#ifdef  FILE_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return File_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return File_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  FILE_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return File_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return File_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return FileClass_WhoAmI;
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
bool            File_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_FILE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(File_Class())->pClassSuperObject;
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
void            File_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          File_Class (
    void
)
{
    return (OBJ_ID)&File_ClassObj;
}


static
uint16_t        File_WhoAmI (
    void
)
{
    return OBJ_IDENT_FILE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  FILE_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
FILE_VTBL     File_VtblShared = {
    {
        &File_Info,
        File_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        File_Dealloc,
        File_Class,
        File_WhoAmI,
        (P_OBJ_QUERYINFO)File_QueryInfo,
        (P_OBJ_TOSTRING)File_ToDebugString,
        NULL,           // File_Enable,
        NULL,           // File_Disable,
        NULL,           // (P_OBJ_ASSIGN)File_Assign,
        NULL,           // (P_OBJ_COMPARE)File_Compare,
        NULL,           // (P_OBJ_PTR)File_Copy,
        NULL,           // (P_OBJ_PTR)File_DeepCopy,
        NULL            // (P_OBJ_HASH)File_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //File_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
FILE_VTBL     File_Vtbl = {
    {
        &File_Info,
        File_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        File_Dealloc,
        File_Class,
        File_WhoAmI,
        (P_OBJ_QUERYINFO)File_QueryInfo,
        (P_OBJ_TOSTRING)File_ToDebugString,
        NULL,           // File_Enable,
        NULL,           // File_Disable,
        NULL,           // (P_OBJ_ASSIGN)File_Assign,
        NULL,           // (P_OBJ_COMPARE)File_Compare,
        NULL,           // (P_OBJ_PTR)File_Copy,
        NULL,           // (P_OBJ_PTR)File_DeepCopy,
        NULL            // (P_OBJ_HASH)File_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //File_IsEnabled,
 
};



static
const
OBJ_INFO        File_Info = {
    "File",
    "Disk File Management",
    (OBJ_DATA *)&File_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&File_Vtbl,
    sizeof(FILE_DATA)
};





