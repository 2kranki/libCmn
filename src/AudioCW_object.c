// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'AudioCW'
//  Generated 06/28/2020 10:01:55


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




#define         AUDIOCW_OBJECT_C       1
#include        <AudioCW_internal.h>
#ifdef  AUDIOCW_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct AudioCW_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  AUDIOCW_SINGLETON
    volatile
    AUDIOCW_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          AudioCWClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        AudioCW_Info;            // Forward Reference




static
bool            AudioCWClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_AUDIOCW_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(AudioCW_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        AudioCWClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_AUDIOCW_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
AUDIOCW_CLASS_VTBL    class_Vtbl = {
    {
        &AudioCW_Info,
        AudioCWClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        AudioCW_Class,
        AudioCWClass_WhoAmI,
        (P_OBJ_QUERYINFO)AudioCWClass_QueryInfo,
        NULL                        // AudioCWClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

AUDIOCW_CLASS_DATA  AudioCW_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(AUDIOCW_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  AUDIOCW_SINGLETON
extern
const
AUDIOCW_VTBL       AudioCW_VtblShared;


AUDIOCW_DATA *     AudioCW_getSingleton (
    void
)
{
    return (OBJ_ID)(AudioCW_ClassObj.pSingleton);
}


bool            AudioCW_setSingleton (
    AUDIOCW_DATA       *pValue
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
    if (AudioCW_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(AudioCW_ClassObj.pSingleton));
    }
    AudioCW_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



AUDIOCW_DATA *     AudioCW_Shared (
    void
)
{
    AUDIOCW_DATA       *this = (OBJ_ID)(AudioCW_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = AudioCW_New( );
        obj_setVtbl(this, (void *)&AudioCW_VtblShared);
        AudioCW_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // AudioCW_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            AudioCW_SharedReset (
    void
)
{
    AUDIOCW_DATA       *this = (OBJ_ID)(AudioCW_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&AudioCW_Vtbl);
        obj_Release(this);
        AudioCW_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          AudioCWClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    AUDIOCW_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(AUDIOCW_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&AudioCW_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&AudioCW_Info.pClassSuperObject;
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
                        return AudioCW_New;
                    }
                    break;
                    
                case 'P':
#ifdef  AUDIOCW_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return AudioCW_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return AudioCW_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  AUDIOCW_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return AudioCW_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return AudioCW_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return AudioCWClass_WhoAmI;
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
bool            AudioCW_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_AUDIOCW == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(AudioCW_Class())->pClassSuperObject;
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
void            AudioCW_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          AudioCW_Class (
    void
)
{
    return (OBJ_ID)&AudioCW_ClassObj;
}


static
uint16_t        AudioCW_WhoAmI (
    void
)
{
    return OBJ_IDENT_AUDIOCW;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  AUDIOCW_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
AUDIOCW_VTBL     AudioCW_VtblShared = {
    {
        &AudioCW_Info,
        AudioCW_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        AudioCW_Dealloc,
        AudioCW_Class,
        AudioCW_WhoAmI,
        (P_OBJ_QUERYINFO)AudioCW_QueryInfo,
        (P_OBJ_TOSTRING)AudioCW_ToDebugString,
        NULL,           // AudioCW_Enable,
        NULL,           // AudioCW_Disable,
        NULL,           // (P_OBJ_ASSIGN)AudioCW_Assign,
        NULL,           // (P_OBJ_COMPARE)AudioCW_Compare,
        NULL,           // (P_OBJ_PTR)AudioCW_Copy,
        NULL,           // (P_OBJ_PTR)AudioCW_DeepCopy,
        NULL            // (P_OBJ_HASH)AudioCW_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //AudioCW_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
AUDIOCW_VTBL     AudioCW_Vtbl = {
    {
        &AudioCW_Info,
        AudioCW_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        AudioCW_Dealloc,
        AudioCW_Class,
        AudioCW_WhoAmI,
        (P_OBJ_QUERYINFO)AudioCW_QueryInfo,
        (P_OBJ_TOSTRING)AudioCW_ToDebugString,
        NULL,           // AudioCW_Enable,
        NULL,           // AudioCW_Disable,
        NULL,           // (P_OBJ_ASSIGN)AudioCW_Assign,
        NULL,           // (P_OBJ_COMPARE)AudioCW_Compare,
        NULL,           // (P_OBJ_PTR)AudioCW_Copy,
        NULL,           // (P_OBJ_PTR)AudioCW_DeepCopy,
        NULL            // (P_OBJ_HASH)AudioCW_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //AudioCW_IsEnabled,
 
};



static
const
OBJ_INFO        AudioCW_Info = {
    "AudioCW",
    "Morse Code (CW) Generation",
    (OBJ_DATA *)&AudioCW_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&AudioCW_Vtbl,
    sizeof(AUDIOCW_DATA)
};





