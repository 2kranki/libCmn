// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'srcParse'
//	Generated 08/19/2019 01:17:17


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




#define			SRCPARSE_OBJECT_C	    1
#include        <SrcParse_internal.h>
#ifdef  SRCPARSE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SrcParse_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SRCPARSE_SINGLETON
    volatile
    SRCPARSE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SrcParseClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SrcParse_Info;            // Forward Reference




static
bool            SrcParseClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCPARSE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		SrcParseClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCPARSE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SRCPARSE_CLASS_VTBL    class_Vtbl = {
    {
        &SrcParse_Info,
        SrcParseClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SrcParse_Class,
        SrcParseClass_WhoAmI,
        (P_OBJ_QUERYINFO)SrcParseClass_QueryInfo,
        NULL                        // srcParseClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

SRCPARSE_CLASS_DATA  SrcParse_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SRCPARSE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SRCPARSE_SINGLETON
SRCPARSE_DATA *     SrcParse_getSingleton (
    void
)
{
    return (OBJ_ID)(SrcParse_ClassObj.pSingleton);
}


bool            SrcParse_setSingleton (
    SRCPARSE_DATA       *pValue
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
    if (SrcParse_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SrcParse_ClassObj.pSingleton));
    }
    SrcParse_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SRCPARSE_DATA *     SrcParse_Shared (
    void
)
{
    SRCPARSE_DATA       *this = (OBJ_ID)(SrcParse_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SrcParse_New( );
        SrcParse_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SrcParse_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SrcParse_SharedReset (
    void
)
{
    SRCPARSE_DATA       *this = (OBJ_ID)(SrcParse_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        SrcParse_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SrcParseClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SRCPARSE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCPARSE_DATA);
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
                        return (void *)&SrcParse_Info;
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
                        return SrcParse_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return SrcParseClass_WhoAmI;
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
bool            SrcParse_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_SRCPARSE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            SrcParse_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SrcParse_Class (
    void
)
{
    return (OBJ_ID)&SrcParse_ClassObj;
}


static
uint16_t		SrcParse_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCPARSE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
SRCPARSE_VTBL     SrcParse_Vtbl = {
    {
        &SrcParse_Info,
        SrcParse_IsKindOf,
#ifdef  SRCPARSE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        SrcParse_Dealloc,
        SrcParse_Class,
        SrcParse_WhoAmI,
        (P_OBJ_QUERYINFO)SrcParse_QueryInfo,
        (P_OBJ_TOSTRING)SrcParse_ToDebugString,
        NULL,			// SrcParse_Enable,
        NULL,			// SrcParse_Disable,
        NULL,			// (P_OBJ_ASSIGN)SrcParse_Assign,
        NULL,			// (P_OBJ_COMPARE)SrcParse_Compare,
        NULL, 			// (P_OBJ_PTR)SrcParse_Copy,
        NULL, 			// (P_OBJ_PTR)SrcParse_DeepCopy,
        NULL 			// (P_OBJ_HASH)SrcParse_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SrcParse_IsEnabled,
 
};



static
const
OBJ_INFO        SrcParse_Info = {
    "SrcParse",
    "Parse the JSON Source creating internal node tree",	
    (OBJ_DATA *)&SrcParse_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&SrcParse_Vtbl,
    sizeof(SRCPARSE_DATA)
};





