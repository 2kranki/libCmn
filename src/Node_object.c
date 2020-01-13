// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Node'
//	Generated 01/12/2020 16:09:18


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




#define			NODE_OBJECT_C	    1
#include        <Node_internal.h>
#ifdef  NODE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Node_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODE_SINGLETON
    volatile
    NODE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Node_Info;            // Forward Reference




static
bool            NodeClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NODE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Node_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		NodeClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODE_CLASS_VTBL    class_Vtbl = {
    {
        &Node_Info,
        NodeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Node_Class,
        NodeClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeClass_QueryInfo,
        NULL                        // NodeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

NODE_CLASS_DATA  Node_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODE_SINGLETON
NODE_DATA *     Node_getSingleton (
    void
)
{
    return (OBJ_ID)(Node_ClassObj.pSingleton);
}


bool            Node_setSingleton (
    NODE_DATA       *pValue
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
    if (Node_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Node_ClassObj.pSingleton));
    }
    Node_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODE_DATA *     Node_Shared (
    void
)
{
    NODE_DATA       *this = (OBJ_ID)(Node_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Node_New( );
        Node_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Node_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Node_SharedReset (
    void
)
{
    NODE_DATA       *this = (OBJ_ID)(Node_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Node_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODE_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODE_DATA);
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
                        return (void *)&Node_Info;
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
                        return Node_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return Node_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return NodeClass_WhoAmI;
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
bool            Node_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NODE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Node_Class())->pClassSuperObject;
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
void            Node_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Node_Class (
    void
)
{
    return (OBJ_ID)&Node_ClassObj;
}


static
uint16_t		Node_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
NODE_VTBL     Node_Vtbl = {
    {
        &Node_Info,
        Node_IsKindOf,
#ifdef  NODE_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Node_Dealloc,
        Node_Class,
        Node_WhoAmI,
        (P_OBJ_QUERYINFO)Node_QueryInfo,
        (P_OBJ_TOSTRING)Node_ToDebugString,
        NULL,			// Node_Enable,
        NULL,			// Node_Disable,
        (P_OBJ_ASSIGN)Node_Assign,
        (P_OBJ_COMPARE)Node_Compare,
        (P_OBJ_PTR)Node_Copy,
        NULL,           // (P_OBJ_PTR)Node_DeepCopy,
        NULL,           // (P_OBJ_HASH)Node_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Node_IsEnabled,
 
};



static
const
OBJ_INFO        Node_Info = {
    "Node",
    "A Generic Node with Properties",
    (OBJ_DATA *)&Node_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Node_Vtbl,
    sizeof(NODE_DATA)
};



const
uint32_t        node_cProps = 8;

const
OBJ_PROP        node_pProps[] = {
    { "cls","","","Class Categorization","int32_t","","public","NODE_DATA",
        offsetof(NODE_DATA,cls),(sizeof(int32_t) << 3), 0},
    { "type","","","???","int32_t","","public","NODE_DATA",
        offsetof(NODE_DATA,type),(sizeof(int32_t) << 3), 0},
    { "unique","","","unique integer identifier","uint32_t","","ro","NODE_DATA",
        offsetof(NODE_DATA,unique),(sizeof(uint32_t) << 3), 0},
    { "name","pName","","Name Identifier","NAME_DATA","","ro","NODE_DATA",
        offsetof(NODE_DATA,pName),(sizeof(NAME_DATA *) << 3), 0},
    { "data","pData","","associated data object","OBJ_ID","","public","NODE_DATA",
        offsetof(NODE_DATA,pData),(sizeof(OBJ_ID) << 3), 0},
    { "extra","pExtra","","an optional extra associated object","OBJ_ID","",
        "public","NODE_DATA",
        offsetof(NODE_DATA,pExtra),(sizeof(OBJ_ID) << 3), 0},
    { "other","pOther","","an optional extra associated object","OBJ_ID","",
        "public","NODE_DATA",
        offsetof(NODE_DATA,pOther),(sizeof(OBJ_ID) << 3), 0},
    { "properties","pProperties","","Associated Properties","NODEBTP_DATA","",
        "public","NODE_DATA",
        offsetof(NODE_DATA,pProperties),(sizeof(NODEBT_DATA *) << 3), 0},

    {NULL}
};





