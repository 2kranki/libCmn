// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Parser'
//	Generated 12/15/2019 15:07:38


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




#define			PARSER_OBJECT_C	    1
#include        <Parser_internal.h>
#ifdef  PARSER_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Parser_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  PARSER_SINGLETON
    volatile
    PARSER_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          ParserClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Parser_Info;            // Forward Reference




static
bool            ParserClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_PARSER_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Parser_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		ParserClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_PARSER_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
PARSER_CLASS_VTBL    class_Vtbl = {
    {
        &Parser_Info,
        ParserClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Parser_Class,
        ParserClass_WhoAmI,
        (P_OBJ_QUERYINFO)ParserClass_QueryInfo,
        NULL                        // ParserClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

PARSER_CLASS_DATA  Parser_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(PARSER_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  PARSER_SINGLETON
PARSER_DATA *     Parser_getSingleton (
    void
)
{
    return (OBJ_ID)(Parser_ClassObj.pSingleton);
}


bool            Parser_setSingleton (
    PARSER_DATA       *pValue
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
    if (Parser_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Parser_ClassObj.pSingleton));
    }
    Parser_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



PARSER_DATA *     Parser_Shared (
    void
)
{
    PARSER_DATA       *this = (OBJ_ID)(Parser_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Parser_New( );
        Parser_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Parser_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Parser_SharedReset (
    void
)
{
    PARSER_DATA       *this = (OBJ_ID)(Parser_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Parser_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          ParserClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PARSER_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PARSER_DATA);
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
                        return (void *)&Parser_Info;
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
                        return Parser_New;
                    }
                    break;
                    
                case 'P':
                    if (str_Compare("ParseJson", (char *)pStr) == 0) {
                        //return Parser_ParseJsonObject;
                    }
                    break;
 
                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return ParserClass_WhoAmI;
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
bool            Parser_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_PARSER == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Parser_Class())->pClassSuperObject;
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
void            Parser_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Parser_Class (
    void
)
{
    return (OBJ_ID)&Parser_ClassObj;
}


static
uint16_t		Parser_WhoAmI (
    void
)
{
    return OBJ_IDENT_PARSER;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
PARSER_VTBL     Parser_Vtbl = {
    {
        &Parser_Info,
        Parser_IsKindOf,
#ifdef  PARSER_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Parser_Dealloc,
        Parser_Class,
        Parser_WhoAmI,
        (P_OBJ_QUERYINFO)Parser_QueryInfo,
        (P_OBJ_TOSTRING)Parser_ToDebugString,
        NULL,			// Parser_Enable,
        NULL,			// Parser_Disable,
        NULL,			// (P_OBJ_ASSIGN)Parser_Assign,
        NULL,			// (P_OBJ_COMPARE)Parser_Compare,
        NULL, 			// (P_OBJ_PTR)Parser_Copy,
        NULL, 			// (P_OBJ_PTR)Parser_DeepCopy,
        NULL 			// (P_OBJ_HASH)Parser_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Parser_IsEnabled,
 
};



static
const
OBJ_INFO        Parser_Info = {
    "Parser",
    "Parser Base",
    (OBJ_DATA *)&Parser_ClassObj,
    (OBJ_DATA *)&lex_ClassObj,
    (OBJ_IUNKNOWN *)&Parser_Vtbl,
    sizeof(PARSER_DATA)
};





