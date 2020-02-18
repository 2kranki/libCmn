// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'TextIns'
//	Generated 02/12/2020 09:43:59


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




#define			TEXTINS_OBJECT_C	    1
#include        <TextIns_internal.h>
#ifdef  TEXTINS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct TextIns_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TEXTINS_SINGLETON
    volatile
    TEXTINS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          TextInsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        TextIns_Info;            // Forward Reference




static
bool            TextInsClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_TEXTINS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(TextIns_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		TextInsClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_TEXTINS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TEXTINS_CLASS_VTBL    class_Vtbl = {
    {
        &TextIns_Info,
        TextInsClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        TextIns_Class,
        TextInsClass_WhoAmI,
        (P_OBJ_QUERYINFO)TextInsClass_QueryInfo,
        NULL                        // TextInsClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

TEXTINS_CLASS_DATA  TextIns_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TEXTINS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TEXTINS_SINGLETON
TEXTINS_DATA *     TextIns_getSingleton (
    void
)
{
    return (OBJ_ID)(TextIns_ClassObj.pSingleton);
}


bool            TextIns_setSingleton (
    TEXTINS_DATA       *pValue
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
    if (TextIns_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(TextIns_ClassObj.pSingleton));
    }
    TextIns_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TEXTINS_DATA *     TextIns_Shared (
    void
)
{
    TEXTINS_DATA       *this = (OBJ_ID)(TextIns_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = TextIns_New( );
        TextIns_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // TextIns_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            TextIns_SharedReset (
    void
)
{
    TEXTINS_DATA       *this = (OBJ_ID)(TextIns_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        TextIns_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          TextInsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TEXTINS_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TEXTINS_DATA);
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
                        return (void *)&TextIns_Info;
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
                        return TextIns_New;
                    }
                    break;
                    
#ifdef  TEXTINS_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return TextIns_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return TextIns_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return TextInsClass_WhoAmI;
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
bool            TextIns_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_TEXTINS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(TextIns_Class())->pClassSuperObject;
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
void            TextIns_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          TextIns_Class (
    void
)
{
    return (OBJ_ID)&TextIns_ClassObj;
}


static
uint16_t		TextIns_WhoAmI (
    void
)
{
    return OBJ_IDENT_TEXTINS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
TEXTINS_VTBL     TextIns_Vtbl = {
    {
        &TextIns_Info,
        TextIns_IsKindOf,
#ifdef  TEXTINS_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        TextIns_Dealloc,
        TextIns_Class,
        TextIns_WhoAmI,
        (P_OBJ_QUERYINFO)TextIns_QueryInfo,
        (P_OBJ_TOSTRING)TextIns_ToDebugString,
        NULL,			// TextIns_Enable,
        NULL,			// TextIns_Disable,
        NULL,			// (P_OBJ_ASSIGN)TextIns_Assign,
        NULL,			// (P_OBJ_COMPARE)TextIns_Compare,
        NULL, 			// (P_OBJ_PTR)TextIns_Copy,
        NULL, 			// (P_OBJ_PTR)TextIns_DeepCopy,
        NULL 			// (P_OBJ_HASH)TextIns_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //TextIns_IsEnabled,
 
};



static
const
OBJ_INFO        TextIns_Info = {
    "TextIns",
    "Stacked Text Input Files",
    (OBJ_DATA *)&TextIns_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&TextIns_Vtbl,
    sizeof(TEXTINS_DATA)
};





