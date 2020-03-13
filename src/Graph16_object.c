// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Graph16'
//	Generated 03/11/2020 17:37:49


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




#define			GRAPH16_OBJECT_C	    1
#include        <Graph16_internal.h>
#ifdef  GRAPH16_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Graph16_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  GRAPH16_SINGLETON
    volatile
    GRAPH16_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Graph16Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Graph16_Info;            // Forward Reference




static
bool            Graph16Class_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_GRAPH16_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Graph16_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		Graph16Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_GRAPH16_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
GRAPH16_CLASS_VTBL    class_Vtbl = {
    {
        &Graph16_Info,
        Graph16Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Graph16_Class,
        Graph16Class_WhoAmI,
        (P_OBJ_QUERYINFO)Graph16Class_QueryInfo,
        NULL                        // Graph16Class_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

GRAPH16_CLASS_DATA  Graph16_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(GRAPH16_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  GRAPH16_SINGLETON
extern
const
GRAPH16_VTBL       Graph16_VtblShared;


GRAPH16_DATA *     Graph16_getSingleton (
    void
)
{
    return (OBJ_ID)(Graph16_ClassObj.pSingleton);
}


bool            Graph16_setSingleton (
    GRAPH16_DATA       *pValue
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
    if (Graph16_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Graph16_ClassObj.pSingleton));
    }
    Graph16_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



GRAPH16_DATA *     Graph16_Shared (
    void
)
{
    GRAPH16_DATA       *this = (OBJ_ID)(Graph16_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Graph16_New( );
        obj_setVtbl(this, (void *)&Graph16_VtblShared);
        Graph16_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Graph16_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Graph16_SharedReset (
    void
)
{
    GRAPH16_DATA       *this = (OBJ_ID)(Graph16_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Graph16_Vtbl);
        obj_Release(this);
        Graph16_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Graph16Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    GRAPH16_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(GRAPH16_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Graph16_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Graph16_Info.pClassSuperObject;
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
                        return Graph16_New;
                    }
                    break;
                    
				case 'P':
#ifdef  GRAPH16_JSON_SUPPORT
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Graph16_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Graph16_ParseJsonObject;
					}
#endif
					break;

				case 'T':
#ifdef  GRAPH16_JSON_SUPPORT
					if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
						return Graph16_ToJsonFields;
					}
					if (str_Compare("ToJson", (char *)pStr) == 0) {
						return Graph16_ToJson;
					}
#endif
					break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return Graph16Class_WhoAmI;
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
bool            Graph16_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_GRAPH16 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Graph16_Class())->pClassSuperObject;
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
void            Graph16_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Graph16_Class (
    void
)
{
    return (OBJ_ID)&Graph16_ClassObj;
}


static
uint16_t		Graph16_WhoAmI (
    void
)
{
    return OBJ_IDENT_GRAPH16;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  GRAPH16_SINGLETON
const
GRAPH16_VTBL     Graph16_VtblShared = {
    {
        &Graph16_Info,
        Graph16_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Graph16_Dealloc,
        Graph16_Class,
        Graph16_WhoAmI,
        (P_OBJ_QUERYINFO)Graph16_QueryInfo,
        (P_OBJ_TOSTRING)Graph16_ToDebugString,
        NULL,			// Graph16_Enable,
        NULL,			// Graph16_Disable,
        NULL,			// (P_OBJ_ASSIGN)Graph16_Assign,
        NULL,			// (P_OBJ_COMPARE)Graph16_Compare,
        NULL, 			// (P_OBJ_PTR)Graph16_Copy,
        NULL, 			// (P_OBJ_PTR)Graph16_DeepCopy,
        NULL 			// (P_OBJ_HASH)Graph16_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Graph16_IsEnabled,
 
};
#endif


const
GRAPH16_VTBL     Graph16_Vtbl = {
    {
        &Graph16_Info,
        Graph16_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Graph16_Dealloc,
        Graph16_Class,
        Graph16_WhoAmI,
        (P_OBJ_QUERYINFO)Graph16_QueryInfo,
        (P_OBJ_TOSTRING)Graph16_ToDebugString,
        NULL,			// Graph16_Enable,
        NULL,			// Graph16_Disable,
        NULL,			// (P_OBJ_ASSIGN)Graph16_Assign,
        NULL,			// (P_OBJ_COMPARE)Graph16_Compare,
        NULL, 			// (P_OBJ_PTR)Graph16_Copy,
        NULL, 			// (P_OBJ_PTR)Graph16_DeepCopy,
        NULL 			// (P_OBJ_HASH)Graph16_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Graph16_IsEnabled,
 
};



static
const
OBJ_INFO        Graph16_Info = {
    "Graph16",
    "Graph with 16-Bit Indices",
    (OBJ_DATA *)&Graph16_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Graph16_Vtbl,
    sizeof(GRAPH16_DATA)
};





