// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'SrcError'
//	Generated 12/28/2019 09:57:21


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




#define			SRCERROR_OBJECT_C	    1
#include        <SrcError_internal.h>
#ifdef  SRCERROR_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SrcError_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SRCERROR_SINGLETON
    volatile
    SRCERROR_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SrcErrorClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SrcError_Info;            // Forward Reference




static
bool            SrcErrorClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SRCERROR_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SrcError_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		SrcErrorClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCERROR_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SRCERROR_CLASS_VTBL    class_Vtbl = {
    {
        &SrcError_Info,
        SrcErrorClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SrcError_Class,
        SrcErrorClass_WhoAmI,
        (P_OBJ_QUERYINFO)SrcErrorClass_QueryInfo,
        NULL                        // SrcErrorClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SRCERROR_CLASS_DATA  SrcError_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SRCERROR_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SRCERROR_SINGLETON
SRCERROR_DATA *     SrcError_getSingleton (
    void
)
{
    return (OBJ_ID)(SrcError_ClassObj.pSingleton);
}


bool            SrcError_setSingleton (
    SRCERROR_DATA       *pValue
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
    if (SrcError_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SrcError_ClassObj.pSingleton));
    }
    SrcError_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SRCERROR_DATA *     SrcError_Shared (
    void
)
{
    SRCERROR_DATA       *this = (OBJ_ID)(SrcError_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SrcError_New( );
        SrcError_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SrcError_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SrcError_SharedReset (
    void
)
{
    SRCERROR_DATA       *this = (OBJ_ID)(SrcError_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        SrcError_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SrcErrorClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SRCERROR_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCERROR_DATA);
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
                        return (void *)&SrcError_Info;
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
                        return SrcError_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return SrcError_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SrcErrorClass_WhoAmI;
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
bool            SrcError_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SRCERROR == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SrcError_Class())->pClassSuperObject;
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
void            SrcError_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SrcError_Class (
    void
)
{
    return (OBJ_ID)&SrcError_ClassObj;
}


static
uint16_t		SrcError_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCERROR;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
SRCERROR_VTBL     SrcError_Vtbl = {
    {
        &SrcError_Info,
        SrcError_IsKindOf,
#ifdef  SRCERROR_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        SrcError_Dealloc,
        SrcError_Class,
        SrcError_WhoAmI,
        (P_OBJ_QUERYINFO)SrcError_QueryInfo,
        (P_OBJ_TOSTRING)SrcError_ToDebugString,
        NULL,			// SrcError_Enable,
        NULL,			// SrcError_Disable,
        (P_OBJ_ASSIGN)SrcError_Assign,
        (P_OBJ_COMPARE)SrcError_Compare,
        (P_OBJ_PTR)SrcError_Copy,
        NULL, 			// (P_OBJ_PTR)SrcError_DeepCopy,
        NULL 			// (P_OBJ_HASH)SrcError_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SrcError_IsEnabled,
 
};



static
const
OBJ_INFO        SrcError_Info = {
    "SrcError",
    "Source File Error",
    (OBJ_DATA *)&SrcError_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&SrcError_Vtbl,
    sizeof(SRCERROR_DATA)
};





