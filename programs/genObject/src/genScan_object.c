// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'genScan'
//	Generated 11/04/2018 19:07:28


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




#define			GENSCAN_OBJECT_C	    1
#include        <genScan_internal.h>
#ifdef  GENSCAN_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct genScan_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  GENSCAN_SINGLETON
    volatile
    GENSCAN_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          genScanClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        genScan_Info;            // Forward Reference




static
bool            genScanClass_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_GENSCAN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		genScanClass_WhoAmI(
    void
)
{
    return OBJ_IDENT_GENSCAN_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
GENSCAN_CLASS_VTBL    class_Vtbl = {
    {
        &genScan_Info,
        genScanClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        genScan_Class,
        genScanClass_WhoAmI,
        (P_OBJ_QUERYINFO)genScanClass_QueryInfo,
        NULL                        // genScanClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

GENSCAN_CLASS_DATA  genScan_ClassObj = {
    {(const OBJ_IUNKNOWN *)&class_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_GENSCAN_CLASS, 0, 1},
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  GENSCAN_SINGLETON
GENSCAN_DATA *     genScan_getSingleton(
    void
)
{
    return (OBJ_ID)(genScan_ClassObj.pSingleton);
}


bool            genScan_setSingleton(
    GENSCAN_DATA       *pValue
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
    if (genScan_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(genScan_ClassObj.pSingleton));
    }
    genScan_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



GENSCAN_DATA *     genScan_Shared(
    void
)
{
    GENSCAN_DATA       *this = (OBJ_ID)(genScan_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = genScan_New( );
        genScan_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // genScan_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            genScan_SharedReset(
    void
)
{
    GENSCAN_DATA       *this = (OBJ_ID)(genScan_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        genScan_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          genScanClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    GENSCAN_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
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
                        return (void *)&genScan_Info;
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
                        return genScan_New;
                    }
                    break;
                    
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return genScanClass_WhoAmI;
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
bool            genScan_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_GENSCAN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            genScan_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          genScan_Class(
    void
)
{
    return (OBJ_ID)&genScan_ClassObj;
}


static
uint16_t		genScan_WhoAmI(
    void
)
{
    return OBJ_IDENT_GENSCAN;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
GENSCAN_VTBL     genScan_Vtbl = {
    {
        &genScan_Info,
        genScan_IsKindOf,
#ifdef  GENSCAN_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        genScan_Dealloc,
        genScan_Class,
        genScan_WhoAmI,
        (P_OBJ_QUERYINFO)genScan_QueryInfo,
        (P_OBJ_TOSTRING)genScan_ToDebugString,
        NULL,			// genScan_Enable,
        NULL,			// genScan_Disable,
        NULL,			// (P_OBJ_ASSIGN)genScan_Assign,
        NULL,			// (P_OBJ_COMPARE)genScan_Compare,
        NULL, 			// (P_OBJ_PTR)genScan_Copy,
        NULL, 			// (P_OBJ_PTR)genScan_DeepCopy,
        NULL 			// (P_OBJ_HASH)genScan_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //genScan_IsEnabled,
 
};



static
const
OBJ_INFO        genScan_Info = {
    "genScan",
    "genScan",	// <-- Fill in description
    (OBJ_DATA *)&genScan_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&genScan_Vtbl
};
#warning -- adjust super class object in Info above 
//			if object inherits from another class





