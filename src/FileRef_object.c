// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'FileRef'
//	Generated 12/06/2019 21:02:56


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




#define			FILEREF_OBJECT_C	    1
#include        <FileRef_internal.h>
#ifdef  FILEREF_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct FileRef_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  FILEREF_SINGLETON
    volatile
    FILEREF_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          FileRefClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        FileRef_Info;            // Forward Reference




static
bool            FileRefClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_FILEREF_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		FileRefClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_FILEREF_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
FILEREF_CLASS_VTBL    class_Vtbl = {
    {
        &FileRef_Info,
        FileRefClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        FileRef_Class,
        FileRefClass_WhoAmI,
        (P_OBJ_QUERYINFO)FileRefClass_QueryInfo,
        NULL                        // FileRefClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

FILEREF_CLASS_DATA  FileRef_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(FILEREF_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  FILEREF_SINGLETON
FILEREF_DATA *     FileRef_getSingleton (
    void
)
{
    return (OBJ_ID)(FileRef_ClassObj.pSingleton);
}


bool            FileRef_setSingleton (
    FILEREF_DATA       *pValue
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
    if (FileRef_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(FileRef_ClassObj.pSingleton));
    }
    FileRef_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



FILEREF_DATA *     FileRef_Shared (
    void
)
{
    FILEREF_DATA       *this = (OBJ_ID)(FileRef_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = FileRef_New( );
        FileRef_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // FileRef_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            FileRef_SharedReset (
    void
)
{
    FILEREF_DATA       *this = (OBJ_ID)(FileRef_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        FileRef_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          FileRefClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    FILEREF_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(FILEREF_DATA);
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
                        return (void *)&FileRef_Info;
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
                        return FileRef_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return FileRef_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return FileRefClass_WhoAmI;
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
bool            FileRef_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_FILEREF == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            FileRef_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          FileRef_Class (
    void
)
{
    return (OBJ_ID)&FileRef_ClassObj;
}


static
uint16_t		FileRef_WhoAmI (
    void
)
{
    return OBJ_IDENT_FILEREF;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
FILEREF_VTBL     FileRef_Vtbl = {
    {
        &FileRef_Info,
        FileRef_IsKindOf,
#ifdef  FILEREF_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        FileRef_Dealloc,
        FileRef_Class,
        FileRef_WhoAmI,
        (P_OBJ_QUERYINFO)FileRef_QueryInfo,
        (P_OBJ_TOSTRING)FileRef_ToDebugString,
        NULL,			// FileRef_Enable,
        NULL,			// FileRef_Disable,
        NULL,			// (P_OBJ_ASSIGN)FileRef_Assign,
        NULL,			// (P_OBJ_COMPARE)FileRef_Compare,
        NULL, 			// (P_OBJ_PTR)FileRef_Copy,
        NULL, 			// (P_OBJ_PTR)FileRef_DeepCopy,
        NULL 			// (P_OBJ_HASH)FileRef_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //FileRef_IsEnabled,
 
};



static
const
OBJ_INFO        FileRef_Info = {
    "FileRef",
    "File Reference",
    (OBJ_DATA *)&FileRef_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&FileRef_Vtbl,
    sizeof(FILEREF_DATA)
};





