// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'GenWin'
//	Generated 11/23/2019 12:07:31


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




#define			GENWIN_OBJECT_C	    1
#include        <GenWin_internal.h>
#ifdef  GENWIN_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct GenWin_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  GENWIN_SINGLETON
    volatile
    GENWIN_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          GenWinClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        GenWin_Info;            // Forward Reference




static
bool            GenWinClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_GENWIN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		GenWinClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_GENWIN_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
GENWIN_CLASS_VTBL    class_Vtbl = {
    {
        &GenWin_Info,
        GenWinClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        GenWin_Class,
        GenWinClass_WhoAmI,
        (P_OBJ_QUERYINFO)GenWinClass_QueryInfo,
        NULL                        // GenWinClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

GENWIN_CLASS_DATA  GenWin_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(GENWIN_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  GENWIN_SINGLETON
GENWIN_DATA *     GenWin_getSingleton (
    void
)
{
    return (OBJ_ID)(GenWin_ClassObj.pSingleton);
}


bool            GenWin_setSingleton (
    GENWIN_DATA       *pValue
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
    if (GenWin_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(GenWin_ClassObj.pSingleton));
    }
    GenWin_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



GENWIN_DATA *     GenWin_Shared (
    void
)
{
    GENWIN_DATA       *this = (OBJ_ID)(GenWin_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = GenWin_New( );
        GenWin_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // GenWin_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            GenWin_SharedReset (
    void
)
{
    GENWIN_DATA       *this = (OBJ_ID)(GenWin_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        GenWin_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          GenWinClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    GENWIN_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(GENWIN_DATA);
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
                        return (void *)&GenWin_Info;
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
                        return GenWin_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return GenWinClass_WhoAmI;
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
bool            GenWin_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_GENWIN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            GenWin_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          GenWin_Class (
    void
)
{
    return (OBJ_ID)&GenWin_ClassObj;
}


static
uint16_t		GenWin_WhoAmI (
    void
)
{
    return OBJ_IDENT_GENWIN;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
GENWIN_VTBL     GenWin_Vtbl = {
    {
        &GenWin_Info,
        GenWin_IsKindOf,
#ifdef  GENWIN_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        GenWin_Dealloc,
        GenWin_Class,
        GenWin_WhoAmI,
        (P_OBJ_QUERYINFO)GenWin_QueryInfo,
        (P_OBJ_TOSTRING)GenWin_ToDebugString,
        NULL,			// GenWin_Enable,
        NULL,			// GenWin_Disable,
        NULL,			// (P_OBJ_ASSIGN)GenWin_Assign,
        NULL,			// (P_OBJ_COMPARE)GenWin_Compare,
        NULL, 			// (P_OBJ_PTR)GenWin_Copy,
        NULL, 			// (P_OBJ_PTR)GenWin_DeepCopy,
        NULL 			// (P_OBJ_HASH)GenWin_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //GenWin_IsEnabled,
 
};



static
const
OBJ_INFO        GenWin_Info = {
    "GenWin",
    "Windows Makefile Generation",
    (OBJ_DATA *)&GenWin_ClassObj,
    (OBJ_DATA *)&GenBase_ClassObj,
    (OBJ_IUNKNOWN *)&GenWin_Vtbl,
    sizeof(GENWIN_DATA)
};





