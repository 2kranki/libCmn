// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   cmdutl_internal.h
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




#ifndef CMDUTL_INTERNAL_H
#define	CMDUTL_INTERNAL_H


#include    <cmdutl.h>
#include    <node_internal.h>
#include    <nodeArray.h>
#include    <nodeHash.h>
#include    <nodeTree.h>
#include    <path.h>
#include    <srcFile.h>
#include    <stdio.h>
#include    <wchar.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
    
    typedef struct cmdutl_entry_s {
        OBJ_ID              pArg;
        WSTR_DATA           *pLongName;
        WSTR_DATA           *pShortName;
    } CMDUTL_ENTRY;
    
    
    typedef struct cmdutl_ref_s {
        OBJ_ID              pEntry;
        OBJ_ID              pValue;
    } CMDUTL_REF;
    
    
    
    


#pragma pack(push, 1)
struct cmdutl_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;
#define OBJ_FLAG_EOF        4           /* At EOF */

    // Common Data
    SRCFILE_DATA    *pSrc;
    PATH_DATA       *pPath;
    uint16_t        inputType;
    union {
        ASTR_DATA           *pAStr;
        //FBSI_DATA           *pFbsi;
        FILE                *pFile;
        //U8ARRAY_DATA        *pU8Array;
        WSTR_DATA           *pWStr;
    };
    uint32_t        lineNo;             // Current Line Number
    uint16_t        colNo;              // Current Column Number
    uint16_t        tabSize;
    uint32_t        fileOffset;
    NODE_DATA       *pFileObject;

    // Field being built
    uint16_t        sizeFld;            // Size of pFld including NUL
    uint16_t        lenFld;             // Used Length in pFld excluding NUL
    W32CHR_T        *pFld;              // Work String
    
    // Look-ahead Wide Char Input
    uint16_t        sizeInputs;
    uint16_t        curInputs;
    W32CHR_T        *pInputs;

    // ArgC/ArgV Stuff
    int             cArg;               // Copy of Original Arguments
    char            **ppArg;
};
#pragma pack(pop)

    extern
    const
    CMDUTL_VTBL     cmdutl_Vtbl;



    // Internal Functions
    ERESULT         cmdutl_AppendCharToField(
        CMDUTL_DATA     *cbp,
        W32CHR_T        chr
    );
    
    void            cmdutl_Dealloc(
        OBJ_ID          objId
    );

    CMDUTL_DATA *   cmdutl_Init(
        CMDUTL_DATA     *cbp
    );
    
    W32CHR_T        cmdutl_InputAdvance(
        CMDUTL_DATA       *cbp,
        uint16_t        numChrs
    );
    
    W32CHR_T        cmdutl_InputLookAhead(
        CMDUTL_DATA       *cbp,
        uint16_t        num
    );
    
    ERESULT         cmdutl_InputNextChar(
        CMDUTL_DATA       *cbp
    );
    
    NODE_DATA *     cmdutl_ParseArray(
        CMDUTL_DATA       *cbp
    );
    
    W32CHR_T        cmdutl_ParseDigit0To9(
        CMDUTL_DATA       *cbp
    );
    
    W32CHR_T        cmdutl_ParseDigit1To9(
        CMDUTL_DATA       *cbp
    );
    
    W32CHR_T        cmdutl_ParseDigitHex(
        CMDUTL_DATA       *cbp
    );
    
    W32CHR_T        cmdutl_ParseDigitOctal(
        CMDUTL_DATA       *cbp
    );
    
    bool            cmdutl_ParseEOF(
        CMDUTL_DATA       *cbp
    );
    
    NODE_DATA *     cmdutl_ParseFileObject(
        CMDUTL_DATA       *cbp
    );
    
    NODE_DATA *     cmdutl_ParseHash(
        CMDUTL_DATA       *cbp
    );

    NODE_DATA *     cmdutl_ParsePair(
        CMDUTL_DATA       *cbp
    );
    
    NODE_DATA *     cmdutl_ParseString(
        CMDUTL_DATA       *cbp
    );
    
    NODE_DATA *     cmdutl_ParseValue(
        CMDUTL_DATA       *cbp
    );
    
    W32CHR_T        cmdutl_UnicodeGetc(
        CMDUTL_DATA       *cbp
    );
    
    NODE_DATA *     cmdutl_ParseValue(
        CMDUTL_DATA       *cbp
    );
    
    bool            cmdutl_ParseWS(
        CMDUTL_DATA       *cbp
    );
    
#ifdef NDEBUG
#else
    bool			cmdutl_Validate(
        CMDUTL_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* CMDUTL_INTERNAL_H */

