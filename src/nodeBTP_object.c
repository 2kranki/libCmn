// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'nodeBTP'
//	Generated 11/22/2018 23:21:01


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




#define			NODEBTP_OBJECT_C	    1
#include        <nodeBTP_internal.h>
#ifdef  NODEBTP_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct nodeBTP_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODEBTP_SINGLETON
    volatile
    NODEBTP_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          nodeBTPClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        nodeBTP_Info;            // Forward Reference




static
bool            nodeBTPClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEBTP_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_BLOCKS_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		nodeBTPClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODEBTP_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODEBTP_CLASS_VTBL    class_Vtbl = {
    {
        &nodeBTP_Info,
        nodeBTPClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        nodeBTP_Class,
        nodeBTPClass_WhoAmI,
        (P_OBJ_QUERYINFO)nodeBTPClass_QueryInfo,
        NULL                        // nodeBTPClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODEBTP_CLASS_DATA  nodeBTP_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(NODEBTP_CLASS_DATA),         // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODEBTP_SINGLETON
NODEBTP_DATA *     nodeBTP_getSingleton(
    void
)
{
    return (OBJ_ID)(nodeBTP_ClassObj.pSingleton);
}


bool            nodeBTP_setSingleton(
    NODEBTP_DATA       *pValue
)
{
    PSXLOCK_DATA    *pLock = OBJ_NIL;
    bool            fRc;
    
    pLock = psxLock_New();
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
    if (nodeBTP_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(nodeBTP_ClassObj.pSingleton));
    }
    nodeBTP_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODEBTP_DATA *     nodeBTP_Shared(
    void
)
{
    NODEBTP_DATA       *this = (OBJ_ID)(nodeBTP_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = nodeBTP_New( );
        nodeBTP_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // nodeBTP_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            nodeBTP_SharedReset(
    void
)
{
    NODEBTP_DATA       *this = (OBJ_ID)(nodeBTP_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        nodeBTP_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          nodeBTPClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODEBTP_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEBTP_DATA);
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
                        return (void *)&nodeBTP_Info;
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
                        return nodeBTP_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return nodeBTPClass_WhoAmI;
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
bool            nodeBTP_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_NODEBTP == classID) {
       return true;
    }
    if (OBJ_IDENT_BLOCKS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            nodeBTP_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          nodeBTP_Class(
    void
)
{
    return (OBJ_ID)&nodeBTP_ClassObj;
}


static
uint16_t		nodeBTP_WhoAmI(
    void
)
{
    return OBJ_IDENT_NODEBTP;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODEBTP_VTBL     nodeBTP_Vtbl = {
    {
        &nodeBTP_Info,
        nodeBTP_IsKindOf,
#ifdef  NODEBTP_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        nodeBTP_Dealloc,
        nodeBTP_Class,
        nodeBTP_WhoAmI,
        (P_OBJ_QUERYINFO)nodeBTP_QueryInfo,
        (P_OBJ_TOSTRING)nodeBTP_ToDebugString,
        NULL,			// nodeBTP_Enable,
        NULL,			// nodeBTP_Disable,
        NULL,			// (P_OBJ_ASSIGN)nodeBTP_Assign,
        NULL,			// (P_OBJ_COMPARE)nodeBTP_Compare,
        NULL, 			// (P_OBJ_PTR)nodeBTP_Copy,
        NULL, 			// (P_OBJ_PTR)nodeBTP_DeepCopy,
        NULL 			// (P_OBJ_HASH)nodeBTP_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //nodeBTP_IsEnabled,
 
};



static
const
OBJ_INFO        nodeBTP_Info = {
    "nodeBTP",
    "Binary Tree of nodes using pointers",
    (OBJ_DATA *)&nodeBTP_ClassObj,
    (OBJ_DATA *)&blocks_ClassObj,
    (OBJ_IUNKNOWN *)&nodeBTP_Vtbl,
    sizeof(NODEBTP_DATA)
};





