// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'TokenList'
//	Generated 01/02/2020 15:56:31


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




#define			TOKENLIST_OBJECT_C	    1
#include        <TokenList_internal.h>
#ifdef  TOKENLIST_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct TokenList_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TOKENLIST_SINGLETON
    volatile
    TOKENLIST_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          TokenListClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        TokenList_Info;            // Forward Reference




static
bool            TokenListClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_TOKENLIST_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(TokenList_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		TokenListClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_TOKENLIST_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TOKENLIST_CLASS_VTBL    class_Vtbl = {
    {
        &TokenList_Info,
        TokenListClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        TokenList_Class,
        TokenListClass_WhoAmI,
        (P_OBJ_QUERYINFO)TokenListClass_QueryInfo,
        NULL                        // TokenListClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

TOKENLIST_CLASS_DATA  TokenList_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TOKENLIST_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TOKENLIST_SINGLETON
TOKENLIST_DATA *     TokenList_getSingleton (
    void
)
{
    return (OBJ_ID)(TokenList_ClassObj.pSingleton);
}


bool            TokenList_setSingleton (
    TOKENLIST_DATA       *pValue
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
    if (TokenList_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(TokenList_ClassObj.pSingleton));
    }
    TokenList_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TOKENLIST_DATA *     TokenList_Shared (
    void
)
{
    TOKENLIST_DATA       *this = (OBJ_ID)(TokenList_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = TokenList_New( );
        TokenList_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // TokenList_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            TokenList_SharedReset (
    void
)
{
    TOKENLIST_DATA       *this = (OBJ_ID)(TokenList_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        TokenList_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          TokenListClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TOKENLIST_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TOKENLIST_DATA);
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
                        return (void *)&TokenList_Info;
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
                        return TokenList_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return TokenList_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return TokenListClass_WhoAmI;
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
bool            TokenList_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_TOKENLIST == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(TokenList_Class())->pClassSuperObject;
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
void            TokenList_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          TokenList_Class (
    void
)
{
    return (OBJ_ID)&TokenList_ClassObj;
}


static
uint16_t		TokenList_WhoAmI (
    void
)
{
    return OBJ_IDENT_TOKENLIST;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
TOKENLIST_VTBL     TokenList_Vtbl = {
    {
        &TokenList_Info,
        TokenList_IsKindOf,
#ifdef  TOKENLIST_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        TokenList_Dealloc,
        TokenList_Class,
        TokenList_WhoAmI,
        (P_OBJ_QUERYINFO)TokenList_QueryInfo,
        (P_OBJ_TOSTRING)TokenList_ToDebugString,
        NULL,			// TokenList_Enable,
        NULL,			// TokenList_Disable,
        NULL,			// (P_OBJ_ASSIGN)TokenList_Assign,
        NULL,			// (P_OBJ_COMPARE)TokenList_Compare,
        NULL, 			// (P_OBJ_PTR)TokenList_Copy,
        NULL, 			// (P_OBJ_PTR)TokenList_DeepCopy,
        NULL 			// (P_OBJ_HASH)TokenList_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //TokenList_IsEnabled,
 
};



static
const
OBJ_INFO        TokenList_Info = {
    "TokenList",
    "List of Source Tokens",
    (OBJ_DATA *)&TokenList_ClassObj,
    (OBJ_DATA *)&ObjList_ClassObj,
    (OBJ_IUNKNOWN *)&TokenList_Vtbl,
    sizeof(TOKENLIST_DATA)
};





