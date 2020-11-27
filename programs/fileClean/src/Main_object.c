// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'main'
//	Generated 07/17/2017 14:59:49


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



#define			MAIN_OBJECT_C	    1
#include        <Main_internal.h>
#ifdef          MAIN_SINGLETON
#include        <psxLock.h>
#endif



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct Main_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  MAIN_SINGLETON
    volatile
    MAIN_DATA       *pSingleton;
#endif
};
typedef struct Main_class_data_s MAIN_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        Main_Info;            // Forward Reference



OBJ_ID          Main_Class(
    void
);



static
bool            Main_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_MAIN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_APPL_CLASS == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		obj_ClassWhoAmI(
    void
)
{
    return OBJ_IDENT_MAIN_CLASS;
}


//===========================================================
//              Class Object Vtbl Definition
//===========================================================

static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&Main_Info,
    Main_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    Main_Class,
    obj_ClassWhoAmI,
    (P_OBJ_QUERYINFO)MainClass_QueryInfo,
    NULL                        // $PClass_ToDebugString
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

MAIN_CLASS_DATA  Main_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(MAIN_CLASS_DATA),            // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  MAIN_SINGLETON
MAIN_DATA *     Main_getSingleton(
    void
)
{
    return (OBJ_ID)(Main_ClassObj.pSingleton);
}


bool            Main_setSingleton(
    MAIN_DATA       *pValue
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
    if (Main_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Main_ClassObj.pSingleton));
    }
    Main_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



MAIN_DATA *     Main_Shared(
    void
)
{
    MAIN_DATA       *this = (OBJ_ID)(Main_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Main_New( );
        Main_setSingleton(this);
        Appl_setSingleton((APPL_DATA *)this);
        obj_Release(this);          // Shared controls object retention now.
    }
    
    return this;
}



void            Main_SharedReset(
    void
)
{
    MAIN_DATA       *this = (OBJ_ID)(Main_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Main_ClassObj.pSingleton = NULL;
    }
    
}
#endif



static
bool            Main_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_MAIN == classID) {
       return true;
    }
    if (OBJ_IDENT_APPL == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            Main_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          Main_Class(
    void
)
{
    return (OBJ_ID)&Main_ClassObj;
}


static
uint16_t		Main_WhoAmI(
    void
)
{
    return OBJ_IDENT_MAIN;
}


//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

void *          MainClass_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    MAIN_CLASS_DATA *this = objId;
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
                        return (void *)&Main_Info;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case OBJ_QUERYINFO_TYPE_INFO:
            return (void *)obj_getInfo(this);
            break;
            
#ifdef XYZZY
        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {
                    
                case 'P':
                    if (str_Compare("ParseObject", (char *)pStr) == 0) {
                        return $P_ParseObject;
                    }
                    break;
                    
                case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return $PClass_WhoAmI;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
            
        default:
            break;
    }
    
    return NULL;
}



//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
MAIN_VTBL     Main_Vtbl = {
    {
        &Main_Info,
        Main_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Main_Dealloc,
        Main_Class,
        Main_WhoAmI,
        (P_OBJ_QUERYINFO)Main_QueryInfo,
        (P_OBJ_TOSTRING)Main_ToDebugString,
        NULL,			// Main_Enable,
        NULL,			// Main_Disable,
        NULL,			// (P_OBJ_ASSIGN)Main_Assign,
        NULL,			// (P_OBJ_COMPARE)Main_Compare,
        NULL, 			// (P_OBJ_PTR)Main_Copy,
        NULL 			// (P_OBJ_HASH)Main_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Main_IsEnabled,
 
};



static
const
OBJ_INFO        Main_Info = {
    "Main",
    "Main Program Object",
    (OBJ_DATA *)&Main_ClassObj,
    (OBJ_DATA *)&Appl_ClassObj,
    (OBJ_IUNKNOWN *)&Main_Vtbl
};





