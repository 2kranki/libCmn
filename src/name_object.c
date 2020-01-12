// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Name'
//	Generated 01/11/2020 10:01:40


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




#define			NAME_OBJECT_C	    1
#include        <Name_internal.h>
#ifdef  NAME_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Name_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NAME_SINGLETON
    volatile
    NAME_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NameClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Name_Info;            // Forward Reference




static
bool            NameClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NAME_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Name_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		NameClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NAME_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NAME_CLASS_VTBL    class_Vtbl = {
    {
        &Name_Info,
        NameClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Name_Class,
        NameClass_WhoAmI,
        (P_OBJ_QUERYINFO)NameClass_QueryInfo,
        NULL                        // NameClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NAME_CLASS_DATA  Name_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NAME_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NAME_SINGLETON
NAME_DATA *     Name_getSingleton (
    void
)
{
    return (OBJ_ID)(Name_ClassObj.pSingleton);
}


bool            Name_setSingleton (
    NAME_DATA       *pValue
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
    if (Name_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Name_ClassObj.pSingleton));
    }
    Name_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NAME_DATA *     Name_Shared (
    void
)
{
    NAME_DATA       *this = (OBJ_ID)(Name_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Name_New( );
        Name_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Name_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Name_SharedReset (
    void
)
{
    NAME_DATA       *this = (OBJ_ID)(Name_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Name_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NameClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NAME_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NAME_DATA);
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
                        return (void *)&Name_Info;
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
                        return Name_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return Name_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NameClass_WhoAmI;
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
bool            Name_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NAME == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Name_Class())->pClassSuperObject;
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
void            Name_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Name_Class (
    void
)
{
    return (OBJ_ID)&Name_ClassObj;
}


static
uint16_t		Name_WhoAmI (
    void
)
{
    return OBJ_IDENT_NAME;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NAME_VTBL     Name_Vtbl = {
    {
        &Name_Info,
        Name_IsKindOf,
#ifdef  NAME_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Name_Dealloc,
        Name_Class,
        Name_WhoAmI,
        (P_OBJ_QUERYINFO)Name_QueryInfo,
        (P_OBJ_TOSTRING)Name_ToDebugString,
        NULL,			// Name_Enable,
        NULL,			// Name_Disable,
        (P_OBJ_ASSIGN)Name_Assign,
        (P_OBJ_COMPARE)Name_Compare,
        (P_OBJ_PTR)Name_Copy,
        (P_OBJ_PTR)Name_DeepCopy,
        (P_OBJ_HASH)Name_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Name_IsEnabled,
 
};



static
const
OBJ_INFO        Name_Info = {
    "Name",
    "Name",
    (OBJ_DATA *)&Name_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Name_Vtbl,
    sizeof(NAME_DATA)
};





