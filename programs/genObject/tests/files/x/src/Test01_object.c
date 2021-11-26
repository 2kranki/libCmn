// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Test01'
//  Generated 11/26/2021 18:53:11


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




#define         TEST01_OBJECT_C       1
#include        <Test01_internal.h>
#ifdef  TEST01_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Test01_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TEST01_SINGLETON
    volatile
    TEST01_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Test01Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Test01_Info;            // Forward Reference




static
bool            Test01Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_TEST01_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Test01_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        Test01Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_TEST01_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TEST01_CLASS_VTBL    class_Vtbl = {
    {
        &Test01_Info,
        Test01Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Test01_Class,
        Test01Class_WhoAmI,
        (P_OBJ_QUERYINFO)Test01Class_QueryInfo,
        NULL                        // Test01Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

TEST01_CLASS_DATA  Test01_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TEST01_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TEST01_SINGLETON
extern
const
TEST01_VTBL       Test01_VtblShared;


TEST01_DATA *     Test01_getSingleton (
    void
)
{
    return (OBJ_ID)(Test01_ClassObj.pSingleton);
}


bool            Test01_setSingleton (
    TEST01_DATA       *pValue
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
    if (Test01_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Test01_ClassObj.pSingleton));
    }
    Test01_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TEST01_DATA *     Test01_Shared (
    void
)
{
    TEST01_DATA       *this = (OBJ_ID)(Test01_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Test01_New( );
        obj_setVtbl(this, (void *)&Test01_VtblShared);
        Test01_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Test01_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Test01_SharedReset (
    void
)
{
    TEST01_DATA       *this = (OBJ_ID)(Test01_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Test01_Vtbl);
        obj_Release(this);
        Test01_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Test01Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TEST01_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TEST01_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Test01_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Test01_Info.pClassSuperObject;
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
                        return Test01_New;
                    }
                    break;
                    
                case 'P':
#ifdef  TEST01_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Test01_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Test01_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  TEST01_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Test01_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Test01_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return Test01Class_WhoAmI;
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
bool            Test01_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_TEST01 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Test01_Class())->pClassSuperObject;
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
void            Test01_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Test01_Class (
    void
)
{
    return (OBJ_ID)&Test01_ClassObj;
}


static
uint16_t        Test01_WhoAmI (
    void
)
{
    return OBJ_IDENT_TEST01;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  TEST01_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
TEST01_VTBL     Test01_VtblShared = {
    {
        &Test01_Info,
        Test01_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Test01_Dealloc,
        Test01_Class,
        Test01_WhoAmI,
        (P_OBJ_QUERYINFO)Test01_QueryInfo,
        (P_OBJ_TOSTRING)Test01_ToDebugString,
        NULL,           // Test01_Enable,
        NULL,           // Test01_Disable,
        NULL,           // (P_OBJ_ASSIGN)Test01_Assign,
        NULL,           // (P_OBJ_COMPARE)Test01_Compare,
        NULL,           // (P_OBJ_PTR)Test01_Copy,
        NULL,           // (P_OBJ_PTR)Test01_DeepCopy,
        NULL            // (P_OBJ_HASH)Test01_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Test01_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
TEST01_VTBL     Test01_Vtbl = {
    {
        &Test01_Info,
        Test01_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Test01_Dealloc,
        Test01_Class,
        Test01_WhoAmI,
        (P_OBJ_QUERYINFO)Test01_QueryInfo,
        (P_OBJ_TOSTRING)Test01_ToDebugString,
        NULL,           // Test01_Enable,
        NULL,           // Test01_Disable,
        NULL,           // (P_OBJ_ASSIGN)Test01_Assign,
        NULL,           // (P_OBJ_COMPARE)Test01_Compare,
        NULL,           // (P_OBJ_PTR)Test01_Copy,
        NULL,           // (P_OBJ_PTR)Test01_DeepCopy,
        NULL            // (P_OBJ_HASH)Test01_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Test01_IsEnabled,
 
};



static
const
OBJ_INFO        Test01_Info = {
    "Test01",
    "A Good Test Object",
    (OBJ_DATA *)&Test01_ClassObj,
    (OBJ_DATA *)&Test01_ClassObj,
    (OBJ_IUNKNOWN *)&Test01_Vtbl,
    sizeof(TEST01_DATA)
};





