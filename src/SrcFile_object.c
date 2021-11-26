// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'SrcFile'
//  Generated 06/06/2020 10:44:03


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




#define         SRCFILE_OBJECT_C       1
#include        <SrcFile_internal.h>
#ifdef  SRCFILE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SrcFile_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SRCFILE_SINGLETON
    volatile
    SRCFILE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SrcFileClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SrcFile_Info;            // Forward Reference




static
bool            SrcFileClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SRCFILE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SrcFile_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        SrcFileClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCFILE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SRCFILE_CLASS_VTBL    class_Vtbl = {
    {
        &SrcFile_Info,
        SrcFileClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SrcFile_Class,
        SrcFileClass_WhoAmI,
        (P_OBJ_QUERYINFO)SrcFileClass_QueryInfo,
        NULL                        // SrcFileClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

SRCFILE_CLASS_DATA  SrcFile_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SRCFILE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SRCFILE_SINGLETON
extern
const
SRCFILE_VTBL       SrcFile_VtblShared;


SRCFILE_DATA *     SrcFile_getSingleton (
    void
)
{
    return (OBJ_ID)(SrcFile_ClassObj.pSingleton);
}


bool            SrcFile_setSingleton (
    SRCFILE_DATA       *pValue
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
    if (SrcFile_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SrcFile_ClassObj.pSingleton));
    }
    SrcFile_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SRCFILE_DATA *     SrcFile_Shared (
    void
)
{
    SRCFILE_DATA       *this = (OBJ_ID)(SrcFile_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SrcFile_New( );
        obj_setVtbl(this, (void *)&SrcFile_VtblShared);
        SrcFile_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SrcFile_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SrcFile_SharedReset (
    void
)
{
    SRCFILE_DATA       *this = (OBJ_ID)(SrcFile_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SrcFile_Vtbl);
        obj_Release(this);
        SrcFile_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SrcFileClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SRCFILE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCFILE_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&SrcFile_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&SrcFile_Info.pClassSuperObject;
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
                        return SrcFile_New;
                    }
                    break;
                    
                case 'P':
#ifdef  SRCFILE_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return SrcFile_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return SrcFile_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  SRCFILE_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return SrcFile_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return SrcFile_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SrcFileClass_WhoAmI;
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
bool            SrcFile_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SRCFILE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SrcFile_Class())->pClassSuperObject;
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
void            SrcFile_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SrcFile_Class (
    void
)
{
    return (OBJ_ID)&SrcFile_ClassObj;
}


static
uint16_t        SrcFile_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCFILE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SRCFILE_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SRCFILE_VTBL     SrcFile_VtblShared = {
    {
        &SrcFile_Info,
        SrcFile_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SrcFile_Dealloc,
        SrcFile_Class,
        SrcFile_WhoAmI,
        (P_OBJ_QUERYINFO)SrcFile_QueryInfo,
        (P_OBJ_TOSTRING)SrcFile_ToDebugString,
        NULL,           // SrcFile_Enable,
        NULL,           // SrcFile_Disable,
        NULL,           // (P_OBJ_ASSIGN)SrcFile_Assign,
        NULL,           // (P_OBJ_COMPARE)SrcFile_Compare,
        NULL,           // (P_OBJ_PTR)SrcFile_Copy,
        NULL,           // (P_OBJ_PTR)SrcFile_DeepCopy,
        NULL            // (P_OBJ_HASH)SrcFile_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SrcFile_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SRCFILE_VTBL     SrcFile_Vtbl = {
    {
        &SrcFile_Info,
        SrcFile_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SrcFile_Dealloc,
        SrcFile_Class,
        SrcFile_WhoAmI,
        (P_OBJ_QUERYINFO)SrcFile_QueryInfo,
        (P_OBJ_TOSTRING)SrcFile_ToDebugString,
        NULL,           // SrcFile_Enable,
        NULL,           // SrcFile_Disable,
        NULL,           // (P_OBJ_ASSIGN)SrcFile_Assign,
        NULL,           // (P_OBJ_COMPARE)SrcFile_Compare,
        NULL,           // (P_OBJ_PTR)SrcFile_Copy,
        NULL,           // (P_OBJ_PTR)SrcFile_DeepCopy,
        NULL            // (P_OBJ_HASH)SrcFile_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    (void *)SrcFile_InputAdvance,
    (void *)SrcFile_InputLookAhead,

};



static
const
OBJ_INFO        SrcFile_Info = {
    "SrcFile",
    "Tokenize a TextIn Stream with Look-ahead and Backup Recovery",
    (OBJ_DATA *)&SrcFile_ClassObj,
    (OBJ_DATA *)&TextIn_ClassObj,
    (OBJ_IUNKNOWN *)&SrcFile_Vtbl,
    sizeof(SRCFILE_DATA)
};





