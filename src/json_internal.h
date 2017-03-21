// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   json_internal.h
 *	Generated 10/18/2015 19:44:45
 *
 * Notes:
 *  --	N/A
 *
 */

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




#ifndef JSON_INTERNAL_H
#define	JSON_INTERNAL_H


#include    <json.h>
#include    <node_internal.h>
#include    <nodeArray.h>
#include    <nodeHash.h>
#include    <nodeTree.h>
#include    <path.h>
#include    <stdio.h>
#include    <wchar.h>

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct json_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;

    // Common Data
    PATH_DATA       *pPath;
    uint16_t        inputType;
    union {
        ASTR_DATA           *pAStr;
        //FBSI_DATA           *pFbsi;
        FILE                *pFile;
        //U8ARRAY_DATA        *pU8Array;
        WSTR_DATA           *pWStr;
    };
    uint32_t        lineNo;     // Current Line Number
    uint16_t        colNo;      // Current Column Number
    uint16_t        tabSize;
    uint32_t        fileOffset;
    NODE_DATA       *pFileObject;

    // Field being built
    uint16_t        sizeFld;            // Size of pFld including NUL
    uint16_t        lenFld;             // Used Length in pFld excluding NUL
    int32_t         *pFld;              // Work String
    
    // Look-ahead Wide Char Input
    uint16_t        sizeInputs;
    uint16_t        curInputs;
    int32_t         *pInputs;
    
};
#pragma pack(pop)

    extern
    const
    OBJ_IUNKNOWN    json_Vtbl;



    // Internal Functions
    ERESULT         json_AppendCharToField(
        JSON_DATA      *cbp,
        int32_t        chr
    );
    
    void            json_Dealloc(
        OBJ_ID          objId
    );

    JSON_DATA *     json_Init(
        JSON_DATA       *cbp
    );
    
    int32_t         json_InputAdvance(
        JSON_DATA       *cbp,
        uint16_t        numChrs
    );
    
    int32_t         json_InputLookAhead(
        JSON_DATA       *cbp,
        uint16_t        num
    );
    
    ERESULT         json_InputNextChar(
        JSON_DATA       *cbp
    );
    
    NODE_DATA *     json_ParseArray(
        JSON_DATA       *cbp
    );
    
    int32_t         json_ParseDigit0To9(
        JSON_DATA       *cbp
    );
    
    int32_t         json_ParseDigit1To9(
        JSON_DATA       *cbp
    );
    
    int32_t         json_ParseDigitHex(
        JSON_DATA       *cbp
    );
    
    int32_t         json_ParseDigitOctal(
        JSON_DATA       *cbp
    );
    
    bool            json_ParseEOF(
        JSON_DATA       *cbp
    );
    
    NODE_DATA *     json_ParseFileObject(
        JSON_DATA       *cbp
    );
    
    NODE_DATA *     json_ParseHash(
        JSON_DATA       *cbp
    );

    NODE_DATA *     json_ParsePair(
        JSON_DATA       *cbp
    );
    
    NODE_DATA *     json_ParseString(
        JSON_DATA       *cbp
    );
    
    NODE_DATA *     json_ParseValue(
        JSON_DATA       *cbp
    );
    
    int32_t         json_UnicodeGetc(
        JSON_DATA       *cbp
    );
    
    NODE_DATA *     json_ParseValue(
        JSON_DATA       *cbp
    );
    
    bool            json_ParseWS(
        JSON_DATA       *cbp
    );
    
#ifdef NDEBUG
#else
    bool			json_Validate(
        JSON_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* JSON_INTERNAL_H */

