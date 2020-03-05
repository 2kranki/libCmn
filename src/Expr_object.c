// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Expr'
//	Generated 03/03/2020 17:03:28


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




#define			EXPR_OBJECT_C	    1
#include        <Expr_internal.h>
#ifdef  EXPR_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Expr_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  EXPR_SINGLETON
    volatile
    EXPR_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ExprClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Expr_Info;            // Forward Reference




static
bool            ExprClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_EXPR_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Expr_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		ExprClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_EXPR_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
EXPR_CLASS_VTBL    class_Vtbl = {
    {
        &Expr_Info,
        ExprClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Expr_Class,
        ExprClass_WhoAmI,
        (P_OBJ_QUERYINFO)ExprClass_QueryInfo,
        NULL                        // ExprClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

EXPR_CLASS_DATA  Expr_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(EXPR_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  EXPR_SINGLETON
EXPR_DATA *     Expr_getSingleton (
    void
)
{
    return (OBJ_ID)(Expr_ClassObj.pSingleton);
}


bool            Expr_setSingleton (
    EXPR_DATA       *pValue
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
    if (Expr_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Expr_ClassObj.pSingleton));
    }
    Expr_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



EXPR_DATA *     Expr_Shared (
    void
)
{
    EXPR_DATA       *this = (OBJ_ID)(Expr_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Expr_New( );
        Expr_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Expr_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Expr_SharedReset (
    void
)
{
    EXPR_DATA       *this = (OBJ_ID)(Expr_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Expr_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ExprClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    EXPR_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(EXPR_DATA);
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
                        return (void *)&Expr_Info;
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
                        return Expr_New;
                    }
                    break;
                    
#ifdef  EXPR_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Expr_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Expr_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ExprClass_WhoAmI;
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
bool            Expr_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_EXPR == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Expr_Class())->pClassSuperObject;
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
void            Expr_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Expr_Class (
    void
)
{
    return (OBJ_ID)&Expr_ClassObj;
}


static
uint16_t		Expr_WhoAmI (
    void
)
{
    return OBJ_IDENT_EXPR;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
EXPR_VTBL     Expr_Vtbl = {
    {
        &Expr_Info,
        Expr_IsKindOf,
#ifdef  EXPR_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Expr_Dealloc,
        Expr_Class,
        Expr_WhoAmI,
        (P_OBJ_QUERYINFO)Expr_QueryInfo,
        (P_OBJ_TOSTRING)Expr_ToDebugString,
        NULL,			// Expr_Enable,
        NULL,			// Expr_Disable,
        NULL,			// (P_OBJ_ASSIGN)Expr_Assign,
        NULL,			// (P_OBJ_COMPARE)Expr_Compare,
        NULL, 			// (P_OBJ_PTR)Expr_Copy,
        NULL, 			// (P_OBJ_PTR)Expr_DeepCopy,
        NULL 			// (P_OBJ_HASH)Expr_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Expr_IsEnabled,
 
};



static
const
OBJ_INFO        Expr_Info = {
    "Expr",
    "Universal Expression Parser",
    (OBJ_DATA *)&Expr_ClassObj,
    (OBJ_DATA *)&Parser_ClassObj,
    (OBJ_IUNKNOWN *)&Expr_Vtbl,
    sizeof(EXPR_DATA)
};





