// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'BlkdRcds16'
//	Generated 12/22/2019 10:06:17


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




#define			BLKDRCDS16_OBJECT_C	    1
#include        <BlkdRcds16_internal.h>
#ifdef  BLKDRCDS16_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct BlkdRcds16_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BLKDRCDS16_SINGLETON
    volatile
    BLKDRCDS16_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BlkdRcds16Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        BlkdRcds16_Info;            // Forward Reference




static
bool            BlkdRcds16Class_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BLKDRCDS16_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(BlkdRcds16_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		BlkdRcds16Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_BLKDRCDS16_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BLKDRCDS16_CLASS_VTBL    class_Vtbl = {
    {
        &BlkdRcds16_Info,
        BlkdRcds16Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        BlkdRcds16_Class,
        BlkdRcds16Class_WhoAmI,
        (P_OBJ_QUERYINFO)BlkdRcds16Class_QueryInfo,
        NULL                        // BlkdRcds16Class_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

BLKDRCDS16_CLASS_DATA  BlkdRcds16_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BLKDRCDS16_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BLKDRCDS16_SINGLETON
BLKDRCDS16_DATA *     BlkdRcds16_getSingleton (
    void
)
{
    return (OBJ_ID)(BlkdRcds16_ClassObj.pSingleton);
}


bool            BlkdRcds16_setSingleton (
    BLKDRCDS16_DATA       *pValue
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
    if (BlkdRcds16_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(BlkdRcds16_ClassObj.pSingleton));
    }
    BlkdRcds16_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BLKDRCDS16_DATA *     BlkdRcds16_Shared (
    void
)
{
    BLKDRCDS16_DATA       *this = (OBJ_ID)(BlkdRcds16_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = BlkdRcds16_New( );
        BlkdRcds16_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // BlkdRcds16_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            BlkdRcds16_SharedReset (
    void
)
{
    BLKDRCDS16_DATA       *this = (OBJ_ID)(BlkdRcds16_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        BlkdRcds16_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BlkdRcds16Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BLKDRCDS16_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BLKDRCDS16_DATA);
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
                        return (void *)&BlkdRcds16_Info;
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
                        return BlkdRcds16_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return BlkdRcds16_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return BlkdRcds16Class_WhoAmI;
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
bool            BlkdRcds16_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BLKDRCDS16 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(BlkdRcds16_Class())->pClassSuperObject;
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
void            BlkdRcds16_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          BlkdRcds16_Class (
    void
)
{
    return (OBJ_ID)&BlkdRcds16_ClassObj;
}


static
uint16_t		BlkdRcds16_WhoAmI (
    void
)
{
    return OBJ_IDENT_BLKDRCDS16;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
BLKDRCDS16_VTBL     BlkdRcds16_Vtbl = {
    {
        &BlkdRcds16_Info,
        BlkdRcds16_IsKindOf,
#ifdef  BLKDRCDS16_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        BlkdRcds16_Dealloc,
        BlkdRcds16_Class,
        BlkdRcds16_WhoAmI,
        (P_OBJ_QUERYINFO)BlkdRcds16_QueryInfo,
        (P_OBJ_TOSTRING)BlkdRcds16_ToDebugString,
        NULL,			// BlkdRcds16_Enable,
        NULL,			// BlkdRcds16_Disable,
        NULL,			// (P_OBJ_ASSIGN)BlkdRcds16_Assign,
        NULL,			// (P_OBJ_COMPARE)BlkdRcds16_Compare,
        NULL, 			// (P_OBJ_PTR)BlkdRcds16_Copy,
        NULL, 			// (P_OBJ_PTR)BlkdRcds16_DeepCopy,
        NULL 			// (P_OBJ_HASH)BlkdRcds16_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BlkdRcds16_IsEnabled,
 
};



static
const
OBJ_INFO        BlkdRcds16_Info = {
    "BlkdRcds16",
    "Block of Variable Length Records w/16 bit offsets",
    (OBJ_DATA *)&BlkdRcds16_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&BlkdRcds16_Vtbl,
    sizeof(BLKDRCDS16_DATA)
};





