// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'hashtbl'
//	Generated 01/12/2019 11:49:43


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




#define			HASHTBL_OBJECT_C	    1
#include        <hashtbl_internal.h>
#ifdef  HASHTBL_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct hashtbl_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  HASHTBL_SINGLETON
    volatile
    HASHTBL_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          hashtblClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        hashtbl_Info;            // Forward Reference




static
bool            hashtblClass_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_HASHTBL_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		hashtblClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_HASHTBL_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
HASHTBL_CLASS_VTBL    class_Vtbl = {
    {
        &hashtbl_Info,
        hashtblClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        hashtbl_Class,
        hashtblClass_WhoAmI,
        (P_OBJ_QUERYINFO)hashtblClass_QueryInfo,
        NULL                        // hashtblClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

HASHTBL_CLASS_DATA  hashtbl_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(HASHTBL_CLASS_DATA),                  // cbSize
        OBJ_IDENT_HASHTBL_CLASS,                     // cbIdent
        0,                                      // cbFlags
        0,                                      // eRc
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  HASHTBL_SINGLETON
HASHTBL_DATA *     hashtbl_getSingleton (
    void
)
{
    return (OBJ_ID)(hashtbl_ClassObj.pSingleton);
}


bool            hashtbl_setSingleton (
    HASHTBL_DATA       *pValue
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
    if (hashtbl_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(hashtbl_ClassObj.pSingleton));
    }
    hashtbl_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



HASHTBL_DATA *     hashtbl_Shared (
    void
)
{
    HASHTBL_DATA       *this = (OBJ_ID)(hashtbl_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = hashtbl_New( );
        hashtbl_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // hashtbl_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            hashtbl_SharedReset (
    void
)
{
    HASHTBL_DATA       *this = (OBJ_ID)(hashtbl_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        hashtbl_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          hashtblClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    HASHTBL_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(HASHTBL_DATA);
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
                        return (void *)&hashtbl_Info;
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
                        return hashtbl_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return hashtblClass_WhoAmI;
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
bool            hashtbl_IsKindOf (
    uint16_t		classID
)
{
    if (OBJ_IDENT_HASHTBL == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            hashtbl_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          hashtbl_Class (
    void
)
{
    return (OBJ_ID)&hashtbl_ClassObj;
}


static
uint16_t		hashtbl_WhoAmI (
    void
)
{
    return OBJ_IDENT_HASHTBL;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
HASHTBL_VTBL     hashtbl_Vtbl = {
    {
        &hashtbl_Info,
        hashtbl_IsKindOf,
#ifdef  HASHTBL_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        hashtbl_Dealloc,
        hashtbl_Class,
        hashtbl_WhoAmI,
        (P_OBJ_QUERYINFO)hashtbl_QueryInfo,
        (P_OBJ_TOSTRING)hashtbl_ToDebugString,
        NULL,			// hashtbl_Enable,
        NULL,			// hashtbl_Disable,
        NULL,			// (P_OBJ_ASSIGN)hashtbl_Assign,
        NULL,			// (P_OBJ_COMPARE)hashtbl_Compare,
        NULL, 			// (P_OBJ_PTR)hashtbl_Copy,
        NULL, 			// (P_OBJ_PTR)hashtbl_DeepCopy,
        NULL 			// (P_OBJ_HASH)hashtbl_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //hashtbl_IsEnabled,
 
};



static
const
OBJ_INFO        hashtbl_Info = {
    "hashtbl",
    "Hash Table Base",
    (OBJ_DATA *)&hashtbl_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&hashtbl_Vtbl,
    sizeof(HASHTBL_DATA)
};





