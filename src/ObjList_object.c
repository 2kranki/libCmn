// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'ObjList'
//	Generated 12/15/2019 12:58:04


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




#define			OBJLIST_OBJECT_C	    1
#include        <ObjList_internal.h>
#ifdef  OBJLIST_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct ObjList_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OBJLIST_SINGLETON
    volatile
    OBJLIST_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ObjListClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        ObjList_Info;            // Forward Reference




static
bool            ObjListClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OBJLIST_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(ObjList_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		ObjListClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJLIST_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OBJLIST_CLASS_VTBL    class_Vtbl = {
    {
        &ObjList_Info,
        ObjListClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        ObjList_Class,
        ObjListClass_WhoAmI,
        (P_OBJ_QUERYINFO)ObjListClass_QueryInfo,
        NULL                        // ObjListClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

OBJLIST_CLASS_DATA  ObjList_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OBJLIST_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OBJLIST_SINGLETON
OBJLIST_DATA *     ObjList_getSingleton (
    void
)
{
    return (OBJ_ID)(ObjList_ClassObj.pSingleton);
}


bool            ObjList_setSingleton (
    OBJLIST_DATA       *pValue
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
    if (ObjList_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(ObjList_ClassObj.pSingleton));
    }
    ObjList_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OBJLIST_DATA *     ObjList_Shared (
    void
)
{
    OBJLIST_DATA       *this = (OBJ_ID)(ObjList_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = ObjList_New( );
        ObjList_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // ObjList_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            ObjList_SharedReset (
    void
)
{
    OBJLIST_DATA       *this = (OBJ_ID)(ObjList_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        ObjList_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ObjListClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OBJLIST_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJLIST_DATA);
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
                        return (void *)&ObjList_Info;
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
                        return ObjList_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return ObjList_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ObjListClass_WhoAmI;
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
bool            ObjList_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OBJLIST == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(ObjList_Class())->pClassSuperObject;
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
void            ObjList_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          ObjList_Class (
    void
)
{
    return (OBJ_ID)&ObjList_ClassObj;
}


static
uint16_t		ObjList_WhoAmI (
    void
)
{
    return OBJ_IDENT_OBJLIST;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
OBJLIST_VTBL     ObjList_Vtbl = {
    {
        &ObjList_Info,
        ObjList_IsKindOf,
#ifdef  OBJLIST_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        ObjList_Dealloc,
        ObjList_Class,
        ObjList_WhoAmI,
        (P_OBJ_QUERYINFO)ObjList_QueryInfo,
        (P_OBJ_TOSTRING)ObjList_ToDebugString,
        NULL,			// ObjList_Enable,
        NULL,			// ObjList_Disable,
        (P_OBJ_ASSIGN)ObjList_Assign,
        NULL,			// (P_OBJ_COMPARE)ObjList_Compare,
        (P_OBJ_PTR)ObjList_Copy,
        (P_OBJ_PTR)ObjList_DeepCopy,
        NULL 			// (P_OBJ_HASH)ObjList_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //ObjList_IsEnabled,
 
};



static
const
OBJ_INFO        ObjList_Info = {
    "ObjList",
    "List of Objects",
    (OBJ_DATA *)&ObjList_ClassObj,
    (OBJ_DATA *)&Blocks_ClassObj,
    (OBJ_IUNKNOWN *)&ObjList_Vtbl,
    sizeof(OBJLIST_DATA)
};





