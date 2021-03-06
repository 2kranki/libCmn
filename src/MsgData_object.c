// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'MsgData'
//	Generated 12/31/2019 10:05:08


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




#define			MSGDATA_OBJECT_C	    1
#include        <MsgData_internal.h>
#ifdef  MSGDATA_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct MsgData_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  MSGDATA_SINGLETON
    volatile
    MSGDATA_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          MsgDataClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        MsgData_Info;            // Forward Reference




static
bool            MsgDataClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_MSGDATA_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(MsgData_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		MsgDataClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_MSGDATA_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
MSGDATA_CLASS_VTBL    class_Vtbl = {
    {
        &MsgData_Info,
        MsgDataClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        MsgData_Class,
        MsgDataClass_WhoAmI,
        (P_OBJ_QUERYINFO)MsgDataClass_QueryInfo,
        NULL                        // MsgDataClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

MSGDATA_CLASS_DATA  MsgData_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(MSGDATA_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  MSGDATA_SINGLETON
MSGDATA_DATA *     MsgData_getSingleton (
    void
)
{
    return (OBJ_ID)(MsgData_ClassObj.pSingleton);
}


bool            MsgData_setSingleton (
    MSGDATA_DATA       *pValue
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
    if (MsgData_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(MsgData_ClassObj.pSingleton));
    }
    MsgData_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



MSGDATA_DATA *     MsgData_Shared (
    void
)
{
    MSGDATA_DATA       *this = (OBJ_ID)(MsgData_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = MsgData_New( );
        MsgData_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // MsgData_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            MsgData_SharedReset (
    void
)
{
    MSGDATA_DATA       *this = (OBJ_ID)(MsgData_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        MsgData_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          MsgDataClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    MSGDATA_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(MSGDATA_DATA);
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
                        return (void *)&MsgData_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&MsgData_Info.pClassSuperObject;
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
                        return MsgData_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return MsgData_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return MsgDataClass_WhoAmI;
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
bool            MsgData_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_MSGDATA == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(MsgData_Class())->pClassSuperObject;
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
void            MsgData_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          MsgData_Class (
    void
)
{
    return (OBJ_ID)&MsgData_ClassObj;
}


static
uint16_t		MsgData_WhoAmI (
    void
)
{
    return OBJ_IDENT_MSGDATA;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
MSGDATA_VTBL     MsgData_Vtbl = {
    {
        &MsgData_Info,
        MsgData_IsKindOf,
#ifdef  MSGDATA_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        MsgData_Dealloc,
        MsgData_Class,
        MsgData_WhoAmI,
        (P_OBJ_QUERYINFO)MsgData_QueryInfo,
        (P_OBJ_TOSTRING)MsgData_ToDebugString,
        NULL,			// MsgData_Enable,
        NULL,			// MsgData_Disable,
        (P_OBJ_ASSIGN)MsgData_Assign,
        NULL,			// (P_OBJ_COMPARE)MsgData_Compare,
        (P_OBJ_PTR)MsgData_Copy,
        NULL, 			// (P_OBJ_PTR)MsgData_DeepCopy,
        NULL 			// (P_OBJ_HASH)MsgData_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //MsgData_IsEnabled,
 
};



static
const
OBJ_INFO        MsgData_Info = {
    "MsgData",
    "Message Data",
    (OBJ_DATA *)&MsgData_ClassObj,
    (OBJ_DATA *)&Value_ClassObj,
    (OBJ_IUNKNOWN *)&MsgData_Vtbl,
    sizeof(MSGDATA_DATA)
};





