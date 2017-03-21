// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'dec'
//	Generated 02/12/2017 23:00:27

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





#define			DEC_OBJECT_C	    1
#include        "dec_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct dec_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct dec_class_data_s DEC_CLASS_DATA;




//-----------------------------------------------------------
//                  Internal Methods
//-----------------------------------------------------------



static
bool            dec_putChar(
    char            data,
    uint32_t        *pLen,              // Remaining length of buffer
    //                                  // (Decremented if char added)
    char            **ppBuffer          // Ascii representation of digit stored
    //                                  // at ptr and ptr is advanced
)
{
    
    // Do initialization.
    if (*pLen > 0) {
        **ppBuffer = data;
        ++*ppBuffer;
        --*pLen;
        return true;
    }
    
    // Return to caller.
    return false;
}




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        dec_Info;            // Forward Reference



OBJ_ID          dec_Class(
    OBJ_ID          objId
);



static
bool            dec_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DEC_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		obj_ClassWhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_DEC_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&dec_Info,
    dec_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
DEC_CLASS_DATA  dec_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_DEC_CLASS, 0, 1},
	//0
};



//----------------------------------------------------------------
//                      G e t  I n t 3 2
//----------------------------------------------------------------

int32_t          dec_getInt32A(
    const
    char            *pStr
)
{
    int32_t         i = 0;
    int32_t         sign = 1;
    
    // Do initialization.
    if( NULL == pStr ) {
        return i;
    }
    
    // Get the sign if present.
    if( *pStr == '-' ) {
        sign = -1;
        ++pStr;
    }
    else if( *pStr == '+' ) {
        ++pStr;
    }
    
    while (*pStr) {
        if ((*pStr >= '0') && (*pStr <= '9')) {
            i = (i * 10) + *pStr - '0';
            ++pStr;
        }
        else
            break;
    }
    
    // Return to caller.
    i *= sign;
    return i;
}



int32_t          dec_getInt32W(
    const
    uint32_t        *pStr
)
{
    int32_t         i = 0;
    int32_t         sign = 1;
    
    // Do initialization.
    if( NULL == pStr ) {
        return i;
    }
    
    // Get the sign if present.
    if( *pStr == '-' ) {
        sign = -1;
        ++pStr;
    }
    else if( *pStr == '+' ) {
        ++pStr;
    }
    
    while (*pStr) {
        if ((*pStr >= '0') && (*pStr <= '9')) {
            i = (i * 10) + *pStr - '0';
            ++pStr;
        }
        else
            break;
    }
    
    // Return to caller.
    i *= sign;
    return i;
}


int64_t          dec_getInt64A(
    const
    char            *pStr
)
{
    int64_t         i = 0;
    int64_t         sign = 1;
    
    // Do initialization.
    if( NULL == pStr ) {
        return i;
    }
    
    // Get the sign if present.
    if( *pStr == '-' ) {
        sign = -1;
        ++pStr;
    }
    else if( *pStr == '+' ) {
        ++pStr;
    }
    
    while (*pStr) {
        if ((*pStr >= '0') && (*pStr <= '9')) {
            i = (i * 10) + *pStr - '0';
            ++pStr;
        }
        else
            break;
    }
    
    // Return to caller.
    i *= sign;
    return i;
}





//----------------------------------------------------------------
//						dec_putInt32
//----------------------------------------------------------------

// Maximum values should be -2,147,483,648 to 2,147,483,647.

void            dec_putInt32A(
    int32_t			input,
    uint32_t        *pLen,              // Remaining length of buffer
    //                                  // (Decremented if char added)
    char            **ppBuffer          // buffer ptr which will be advanced
)
{
    bool            fRc;
    
    // Do initialization.
    if( (NULL == ppBuffer) || (NULL == pLen) || (0 == *pLen) ) {
        return;
    }
    
    // Initialize the output area.
    if( input < 0 ) {
        fRc = dec_putChar('-', pLen, ppBuffer);
        input = -input;
    }
    else {
        fRc = dec_putChar(' ', pLen, ppBuffer);
    }
    
    // set the value;
    dec_putUint32A( input, pLen, ppBuffer );
    
    // Return to caller.
}



//----------------------------------------------------------------
//						dec_putInt64
//----------------------------------------------------------------

// Maximum values should be -9,223,372,036,854,775,807 to 9,223,372,036,854,775,807.

void            dec_putInt64A(
    int64_t			input,
    uint32_t        *pLen,              // Remaining length of buffer
    //                                  // (Decremented if char added)
    char            **ppBuffer          // buffer ptr which will be advanced
)
{
    bool            fRc;
    
    // Do initialization.
    if( (NULL == ppBuffer) || (NULL == pLen) || (0 == *pLen) ) {
        return;
    }
    
    // Initialize the output area.
    if( input < 0 ) {
        fRc = dec_putChar('-', pLen, ppBuffer);
        input = -input;
    }
    else {
        fRc = dec_putChar(' ', pLen, ppBuffer);
    }
    
    // set the value;
    dec_putUint64A(input, pLen, ppBuffer);
    
    // Return to caller.
}



//----------------------------------------------------------------
//						dec_putUint32
//----------------------------------------------------------------

// Maximum values should be 0 to 4,294,967,295.

void            dec_putUint32A(
    uint32_t        input,
    uint32_t        *pLen,              // Remaining length of buffer
    //                                  // (Decremented if char added)
    char            **ppBuffer          // buffer ptr which will be advanced
)
{
    uint32_t		i;
    char			*pChr;
    char            buffer[11];
    bool            fRc;
    
    // Do initialization.
    if( (NULL == ppBuffer) || (NULL == pLen) || (0 == *pLen) ) {
        return;
    }
    
    // Initialize the output area.
    pChr = buffer;
    for( i=0; i<10; ++i )
        *pChr++ = '0';
    *pChr = '\0';
    
    // set the value;
    pChr = buffer + 10 - 1;
    while( input ) {
        *pChr-- = (input % 10) + '0';
        input /= 10;
    }
    
    pChr = buffer;
    for( i=0; i<10; ++i ) {
        fRc = dec_putChar(*pChr++, pLen, ppBuffer);
    }
    
    // Return to caller.
}


void            dec_putUint32AObj(
    uint32_t        input,
    void            *pObject,
    bool            (*pPutChar)(void *, uint8_t)
)
{
    uint32_t		i;
    char			*pChr;
    char            buffer[11];
    bool            fRc;
    
    // Do initialization.
    if( (NULL == pPutChar) ) {
        return;
    }
    
    // Initialize the output area.
    pChr = buffer;
    for( i=0; i<10; ++i )
        *pChr++ = '0';
    *pChr = '\0';
    
    // set the value;
    pChr = buffer + 10 - 1;
    while( input ) {
        *pChr-- = (input % 10) + '0';
        input /= 10;
    }
    
    pChr = buffer;
    for( i=0; i<10; ++i ) {
        fRc = pPutChar(pObject, *pChr++);
    }
    
    // Return to caller.
}



//----------------------------------------------------------------
//						dec_putUint64
//----------------------------------------------------------------

// Maximum values should be 0 to 18446744073709551615.

void            dec_putUint64A(
    uint64_t        input,
    uint32_t        *pLen,              // Remaining length of buffer
    //                                  // (Decremented if char added)
    char            **ppBuffer          // buffer ptr which will be advanced
)
{
    uint64_t		i;
    char			*pChr;
    char            buffer[21];
    bool            fRc;
    
    // Do initialization.
    if( (NULL == ppBuffer) || (NULL == pLen) || (0 == *pLen) ) {
        return;
    }
    
    // Initialize the output area.
    pChr = buffer;
    for( i=0; i<20; ++i )
        *pChr++ = '0';
    *pChr = '\0';
    
    // set the value;
    pChr = buffer + 20 - 1;
    while( input ) {
        *pChr-- = (input % 10) + '0';
        input /= 10;
    }
    
    pChr = buffer;
    for( i=0; i<21; ++i ) {
        fRc = dec_putChar(*pChr++, pLen, ppBuffer);
    }
    
    // Return to caller.
}


void            dec_putUint64AObj(
    uint64_t        input,
    void            *pObject,
    bool            (*pPutChar)(void *, uint8_t)
)
{
    uint64_t		i;
    char			*pChr;
    char            buffer[21];
    bool            fRc;
    
    // Do initialization.
    if( (NULL == pPutChar) ) {
        return;
    }
    
    // Initialize the output area.
    pChr = buffer;
    for( i=0; i<20; ++i )
        *pChr++ = '0';
    *pChr = '\0';
    
    // set the value;
    pChr = buffer + 20 - 1;
    while( input ) {
        *pChr-- = (input % 10) + '0';
        input /= 10;
    }
    
    pChr = buffer;
    for( i=0; i<20; ++i ) {
        fRc = pPutChar(pObject, *pChr++);
    }
    
    // Return to caller.
}



static
bool            dec_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_DEC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            dec_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          dec_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&dec_ClassObj;
}


static
uint16_t		dec_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_DEC;
}


const
DEC_VTBL     dec_Vtbl = {
    {
        &dec_Info,
        dec_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        dec_Dealloc,
        dec_Class,
        dec_WhoAmI,
        NULL,			// dec_Enable,
        NULL,			// dec_Disable,
        (P_OBJ_TOSTRING)dec_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)dec_Assign,
        NULL,			// (P_OBJ_COMPARE)dec_Compare,
        NULL, 			// (P_OBJ_PTR)dec_Copy,
        NULL 			// (P_OBJ_HASH)dec_Hash
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //dec_IsEnabled,
 
};



static
const
OBJ_INFO        dec_Info = {
    "dec",
    "decimal number i/o",
    (OBJ_DATA *)&dec_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&dec_Vtbl
};





