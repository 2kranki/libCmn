// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'jsonPP'
//	Generated 08/27/2019 21:35:44


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




#define			JSONPP_OBJECT_C	    1
#include        <jsonPP_internal.h>
#ifdef  JSONPP_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct jsonPP_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  JSONPP_SINGLETON
    volatile
    JSONPP_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          jsonPPClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        jsonPP_Info;            // Forward Reference




static
bool            jsonPPClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_JSONPP_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		jsonPPClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_JSONPP_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
JSONPP_CLASS_VTBL    class_Vtbl = {
    {
        &jsonPP_Info,
        jsonPPClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        jsonPP_Class,
        jsonPPClass_WhoAmI,
        (P_OBJ_QUERYINFO)jsonPPClass_QueryInfo,
        NULL                        // jsonPPClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

JSONPP_CLASS_DATA  jsonPP_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(JSONPP_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  JSONPP_SINGLETON
JSONPP_DATA *     jsonPP_getSingleton (
    void
)
{
    return (OBJ_ID)(jsonPP_ClassObj.pSingleton);
}


bool            jsonPP_setSingleton (
    JSONPP_DATA       *pValue
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
    if (jsonPP_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(jsonPP_ClassObj.pSingleton));
    }
    jsonPP_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



JSONPP_DATA *     jsonPP_Shared (
    void
)
{
    JSONPP_DATA       *this = (OBJ_ID)(jsonPP_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = jsonPP_New( );
        jsonPP_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // jsonPP_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            jsonPP_SharedReset (
    void
)
{
    JSONPP_DATA       *this = (OBJ_ID)(jsonPP_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        jsonPP_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          jsonPPClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    JSONPP_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(JSONPP_DATA);
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
                        return (void *)&jsonPP_Info;
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
                        return jsonPP_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return jsonPPClass_WhoAmI;
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
bool            jsonPP_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_JSONPP == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            jsonPP_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          jsonPP_Class (
    void
)
{
    return (OBJ_ID)&jsonPP_ClassObj;
}


static
uint16_t		jsonPP_WhoAmI (
    void
)
{
    return OBJ_IDENT_JSONPP;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
JSONPP_VTBL     jsonPP_Vtbl = {
    {
        &jsonPP_Info,
        jsonPP_IsKindOf,
#ifdef  JSONPP_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        jsonPP_Dealloc,
        jsonPP_Class,
        jsonPP_WhoAmI,
        (P_OBJ_QUERYINFO)jsonPP_QueryInfo,
        (P_OBJ_TOSTRING)jsonPP_ToDebugString,
        NULL,			// jsonPP_Enable,
        NULL,			// jsonPP_Disable,
        NULL,			// (P_OBJ_ASSIGN)jsonPP_Assign,
        NULL,			// (P_OBJ_COMPARE)jsonPP_Compare,
        NULL, 			// (P_OBJ_PTR)jsonPP_Copy,
        NULL, 			// (P_OBJ_PTR)jsonPP_DeepCopy,
        NULL 			// (P_OBJ_HASH)jsonPP_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //jsonPP_IsEnabled,
 
};



static
const
OBJ_INFO        jsonPP_Info = {
    "jsonPP",
    "Pretty print a JSON Structure",
    (OBJ_DATA *)&jsonPP_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&jsonPP_Vtbl,
    sizeof(JSONPP_DATA)
};





