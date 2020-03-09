// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'W32StrC'
//	Generated 01/23/2020 22:22:04


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




#define			W32STRC_OBJECT_C	    1
#include        <W32StrC_internal.h>
#ifdef  W32STRC_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct W32StrC_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  W32STRC_SINGLETON
    volatile
    W32STRC_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          W32StrCClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        W32StrC_Info;            // Forward Reference




static
bool            W32StrCClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_W32STRC_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(W32StrC_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		W32StrCClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_W32STRC_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
W32STRC_CLASS_VTBL    class_Vtbl = {
    {
        &W32StrC_Info,
        W32StrCClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        W32StrC_Class,
        W32StrCClass_WhoAmI,
        (P_OBJ_QUERYINFO)W32StrCClass_QueryInfo,
        NULL                        // W32StrCClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

W32STRC_CLASS_DATA  W32StrC_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(W32STRC_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  W32STRC_SINGLETON
W32STRC_DATA *     W32StrC_getSingleton (
    void
)
{
    return (OBJ_ID)(W32StrC_ClassObj.pSingleton);
}


bool            W32StrC_setSingleton (
    W32STRC_DATA       *pValue
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
    if (W32StrC_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(W32StrC_ClassObj.pSingleton));
    }
    W32StrC_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



W32STRC_DATA *     W32StrC_Shared (
    void
)
{
    W32STRC_DATA       *this = (OBJ_ID)(W32StrC_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = W32StrC_New( );
        W32StrC_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // W32StrC_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            W32StrC_SharedReset (
    void
)
{
    W32STRC_DATA       *this = (OBJ_ID)(W32StrC_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        W32StrC_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          W32StrCClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    W32STRC_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(W32STRC_DATA);
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
                        return (void *)&W32StrC_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&W32StrC_Info.pClassSuperObject;
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
                        return W32StrC_New;
                    }
                    break;
                    
				case 'P':
#ifdef  W32STRC_JSON_SUPPORT
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return W32StrC_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return W32StrC_ParseJsonObject;
					}
#endif
					break;

				case 'T':
#ifdef  W32STRC_JSON_SUPPORT
					if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
						return W32StrC_ToJsonFields;
					}
					if (str_Compare("ToJson", (char *)pStr) == 0) {
						return W32StrC_ToJson;
					}
#endif
					break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return W32StrCClass_WhoAmI;
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
bool            W32StrC_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_W32STRC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(W32StrC_Class())->pClassSuperObject;
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
void            W32StrC_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          W32StrC_Class (
    void
)
{
    return (OBJ_ID)&W32StrC_ClassObj;
}


static
uint16_t		W32StrC_WhoAmI (
    void
)
{
    return OBJ_IDENT_W32STRC;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
W32STRC_VTBL     W32StrC_Vtbl = {
    {
        &W32StrC_Info,
        W32StrC_IsKindOf,
#ifdef  W32STRC_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        W32StrC_Dealloc,
        W32StrC_Class,
        W32StrC_WhoAmI,
        (P_OBJ_QUERYINFO)W32StrC_QueryInfo,
        (P_OBJ_TOSTRING)W32StrC_ToDebugString,
        NULL,			// W32StrC_Enable,
        NULL,			// W32StrC_Disable,
        (P_OBJ_ASSIGN)W32StrC_Assign,
        (P_OBJ_COMPARE)W32StrC_Compare,
        (P_OBJ_PTR)W32StrC_Copy,
        NULL, 			// (P_OBJ_PTR)W32StrC_DeepCopy,
        (P_OBJ_HASH)W32StrC_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    W32StrC_getData,
    W32StrC_getLength

};



static
const
OBJ_INFO        W32StrC_Info = {
    "W32StrC",
    "Constant Wide String",
    (OBJ_DATA *)&W32StrC_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&W32StrC_Vtbl,
    sizeof(W32STRC_DATA)
};





