// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'SrcRef'
//	Generated 12/05/2019 14:04:10


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




#define			SRCREF_OBJECT_C	    1
#include        <SrcRef_internal.h>
#ifdef  SRCREF_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SrcRef_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SRCREF_SINGLETON
    volatile
    SRCREF_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SrcRefClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SrcRef_Info;            // Forward Reference




static
bool            SrcRefClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCREF_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		SrcRefClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCREF_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SRCREF_CLASS_VTBL    class_Vtbl = {
    {
        &SrcRef_Info,
        SrcRefClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SrcRef_Class,
        SrcRefClass_WhoAmI,
        (P_OBJ_QUERYINFO)SrcRefClass_QueryInfo,
        NULL                        // SrcRefClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SRCREF_CLASS_DATA  SrcRef_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SRCREF_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SRCREF_SINGLETON
SRCREF_DATA *     SrcRef_getSingleton (
    void
)
{
    return (OBJ_ID)(SrcRef_ClassObj.pSingleton);
}


bool            SrcRef_setSingleton (
    SRCREF_DATA       *pValue
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
    if (SrcRef_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SrcRef_ClassObj.pSingleton));
    }
    SrcRef_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SRCREF_DATA *     SrcRef_Shared (
    void
)
{
    SRCREF_DATA       *this = (OBJ_ID)(SrcRef_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SrcRef_New( );
        SrcRef_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SrcRef_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SrcRef_SharedReset (
    void
)
{
    SRCREF_DATA       *this = (OBJ_ID)(SrcRef_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        SrcRef_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SrcRefClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SRCREF_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCREF_DATA);
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
                        return (void *)&SrcRef_Info;
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
                        return SrcRef_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return SrcRef_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SrcRefClass_WhoAmI;
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
bool            SrcRef_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCREF == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            SrcRef_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SrcRef_Class (
    void
)
{
    return (OBJ_ID)&SrcRef_ClassObj;
}


static
uint16_t		SrcRef_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCREF;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
SRCREF_VTBL     SrcRef_Vtbl = {
    {
        &SrcRef_Info,
        SrcRef_IsKindOf,
#ifdef  SRCREF_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        SrcRef_Dealloc,
        SrcRef_Class,
        SrcRef_WhoAmI,
        (P_OBJ_QUERYINFO)SrcRef_QueryInfo,
        (P_OBJ_TOSTRING)SrcRef_ToDebugString,
        NULL,			// SrcRef_Enable,
        NULL,			// SrcRef_Disable,
        NULL,			// (P_OBJ_ASSIGN)SrcRef_Assign,
        NULL,			// (P_OBJ_COMPARE)SrcRef_Compare,
        NULL, 			// (P_OBJ_PTR)SrcRef_Copy,
        NULL, 			// (P_OBJ_PTR)SrcRef_DeepCopy,
        NULL 			// (P_OBJ_HASH)SrcRef_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SrcRef_IsEnabled,
 
};



static
const
OBJ_INFO        SrcRef_Info = {
    "SrcRef",
    "Source Reference",
    (OBJ_DATA *)&SrcRef_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&SrcRef_Vtbl,
    sizeof(SRCREF_DATA)
};





