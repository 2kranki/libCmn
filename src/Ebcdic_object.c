// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'Ebcdic'
//	Generated 01/25/2020 14:41:25


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




#define			EBCDIC_OBJECT_C	    1
#include        <Ebcdic_internal.h>
#ifdef  EBCDIC_SINGLETON
#include        <psxLock.h>
#endif




static
const
uint8_t     Ascii2EbcdicTable[128] = {
    0x00,0x01,0x02,0x03,0x04,0x2D,0x2E,0x2F,    /* 000-007 */
    0x16,0x05,0x25,0x0B,0x0C,0x0D,0x0E,0x0F,    /* 008-015 */
    0x10,0x11,0x12,0x13,0x14,0x3D,0x32,0x26,    /* 016-023 */
    0x18,0x19,0x3F,0x27,0x1C,0x1D,0x1E,0x1F,    /* 024-031 */
    0x40,0x5A,0x7F,0x7B,0x5B,0x6C,0x50,0x7D,    /* 032-039 */
    0x4D,0x5D,0x5C,0x4E,0x6B,0x60,0x4B,0x61,    /* 040-047 */
    0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,    /* 048-055 */
    0xF8,0xF9,0x7A,0x5E,0x4C,0x7E,0x6E,0x6F,    /* 056-063 */
    0x7C,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,    /* 064-071 */
    0xC8,0xC9,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,    /* 072-079 */
    0xD7,0xD8,0xD9,0xE2,0xE3,0xE4,0xE5,0xE6,    /* 080-087 */
    0xE7,0xE8,0xE9,0xAD,0xE0,0xBD,0x5F,0x6D,    /* 088-095 */
    0x79,0x81,0x82,0x83,0x84,0x85,0x86,0x87,    /* 096-103 */
    0x88,0x89,0x91,0x92,0x93,0x94,0x95,0x96,    /* 104-111 */
    0x97,0x98,0x99,0xA2,0xA3,0xA4,0xA5,0xA6,    /* 112-119 */
    0xA7,0xA8,0xA9,0xC0,0x6A,0xD0,0xA1,0x07     /* 120-127 */
};


static
const
uint8_t     Ebcdic2AsciiTable[256] = {
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 00-07 */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 08-0F */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 10-17 */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 18-1F */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 20-27 */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 28-2F */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 30-37 */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 38-3F */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 40-47 */
    0x20,0x20,0x20,0x2E,0x3C,0x28,0x2B,0x7C,    /* 48-4F */
    0x26,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 50-57 */
    0x20,0x20,0x21,0x24,0x2A,0x29,0x3B,0x7E,    /* 58-5F */
    0x2D,0x2F,0x20,0x20,0x20,0x20,0x20,0x20,    /* 60-67 */
    0x20,0x20,0x20,0x2C,0x25,0x5F,0x3E,0x3F,    /* 68-6F */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 70-77 */
    0x20,0x20,0x3A,0x23,0x40,0x27,0x3D,0x22,    /* 78-7F */
    0x24,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 80-87 */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 88-8F */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 90-97 */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 98-9F */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* A0-A7 */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* A8-AF */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* B0-B7 */
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* B8-BF */
    0x20,0x41,0x42,0x43,0x44,0x45,0x46,0x47,    /* C0-C7 */
    0x48,0x49,0x20,0x20,0x20,0x20,0x20,0x20,    /* C8-CF */
    0x20,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,    /* D0-D7 */
    0x51,0x52,0x20,0x20,0x20,0x20,0x20,0x20,    /* D8-DF */
    0x20,0x20,0x53,0x54,0x55,0x56,0x57,0x58,    /* E0-E7 */
    0x59,0x5A,0x20,0x20,0x20,0x20,0x20,0x20,    /* E8-EF */
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,    /* F0-F7 */
    0x38,0x39,0x20,0x20,0x20,0x20,0x20,0x20     /* F8-FF */
};






//===========================================================
//                  Class Object Definition
//===========================================================

struct Ebcdic_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  EBCDIC_SINGLETON
    volatile
    EBCDIC_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------


uint8_t         Ebcdic_AsciiToEbcdicA(
    char            asciiChar
)
{
    uint8_t         ebcdicChar;

    ebcdicChar = (wchar_t)(Ascii2EbcdicTable[(asciiChar & 0x7F)]);

    return( ebcdicChar );
}



char            Ebcdic_EbcdicToAsciiA(
    uint8_t         ebcdicChar
)
{
    char            asciiChar;

    asciiChar = (Ebcdic2AsciiTable[(ebcdicChar & 0xFF)]);
    return( asciiChar );
}



void            Ebcdic_TranslateAsciiToEbcdicA (
    uint32_t        cBuffer,
    uint8_t         *pBuffer
)
{
    while (cBuffer--) {
        if (*pBuffer == '\0')
            break;
        *pBuffer = Ebcdic_AsciiToEbcdicA(*pBuffer);
        ++pBuffer;
    }
}



void            Ebcdic_TranslateEbcdicToAsciiA (
    uint32_t        cBuffer,
    uint8_t         *pBuffer
)
{
    while (cBuffer--) {
        if (*pBuffer == '\0')
            break;
        *pBuffer = Ebcdic_EbcdicToAsciiA(*pBuffer);
        ++pBuffer;
    }
}




static
void *          EbcdicClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Ebcdic_Info;            // Forward Reference




static
bool            EbcdicClass_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_EBCDIC_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Ebcdic_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t		EbcdicClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_EBCDIC_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
EBCDIC_CLASS_VTBL    class_Vtbl = {
    {
        &Ebcdic_Info,
        EbcdicClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Ebcdic_Class,
        EbcdicClass_WhoAmI,
        (P_OBJ_QUERYINFO)EbcdicClass_QueryInfo,
        NULL                        // EbcdicClass_ToDebugString
    },
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

EBCDIC_CLASS_DATA  Ebcdic_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(EBCDIC_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
	//0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  EBCDIC_SINGLETON
EBCDIC_DATA *     Ebcdic_getSingleton (
    void
)
{
    return (OBJ_ID)(Ebcdic_ClassObj.pSingleton);
}


bool            Ebcdic_setSingleton (
    EBCDIC_DATA       *pValue
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
    if (Ebcdic_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Ebcdic_ClassObj.pSingleton));
    }
    Ebcdic_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



EBCDIC_DATA *     Ebcdic_Shared (
    void
)
{
    EBCDIC_DATA       *this = (OBJ_ID)(Ebcdic_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Ebcdic_New( );
        Ebcdic_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Ebcdic_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Ebcdic_SharedReset (
    void
)
{
    EBCDIC_DATA       *this = (OBJ_ID)(Ebcdic_ClassObj.pSingleton);
    
    if (this) {
        obj_Release(this);
        Ebcdic_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          EbcdicClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    EBCDIC_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(EBCDIC_DATA);
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
                        return (void *)&Ebcdic_Info;
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
                        return Ebcdic_New;
                    }
                    break;
                    
#ifdef  EBCDIC_JSON_SUPPORT
				case 'P':
					if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
						return Ebcdic_ParseJsonFields;
					}
					if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
						return Ebcdic_ParseJsonObject;
					}
					break;
#endif

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return EbcdicClass_WhoAmI;
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
bool            Ebcdic_IsKindOf (
    uint16_t		classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_EBCDIC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Ebcdic_Class())->pClassSuperObject;
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
void            Ebcdic_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Ebcdic_Class (
    void
)
{
    return (OBJ_ID)&Ebcdic_ClassObj;
}


static
uint16_t		Ebcdic_WhoAmI (
    void
)
{
    return OBJ_IDENT_EBCDIC;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

const
EBCDIC_VTBL     Ebcdic_Vtbl = {
    {
        &Ebcdic_Info,
        Ebcdic_IsKindOf,
#ifdef  EBCDIC_IS_SINGLETON
        obj_RetainNull,
        obj_ReleaseNull,
#else
        obj_RetainStandard,
        obj_ReleaseStandard,
#endif
        Ebcdic_Dealloc,
        Ebcdic_Class,
        Ebcdic_WhoAmI,
        (P_OBJ_QUERYINFO)Ebcdic_QueryInfo,
        (P_OBJ_TOSTRING)Ebcdic_ToDebugString,
        NULL,			// Ebcdic_Enable,
        NULL,			// Ebcdic_Disable,
        NULL,			// (P_OBJ_ASSIGN)Ebcdic_Assign,
        NULL,			// (P_OBJ_COMPARE)Ebcdic_Compare,
        NULL, 			// (P_OBJ_PTR)Ebcdic_Copy,
        NULL, 			// (P_OBJ_PTR)Ebcdic_DeepCopy,
        NULL 			// (P_OBJ_HASH)Ebcdic_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Ebcdic_IsEnabled,
 
};



static
const
OBJ_INFO        Ebcdic_Info = {
    "Ebcdic",
    "ebcdic/ascii translation",
    (OBJ_DATA *)&Ebcdic_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Ebcdic_Vtbl,
    sizeof(EBCDIC_DATA)
};





